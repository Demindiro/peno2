/**
 * Receiving and sending commands:
 *  - 1 byte  | Command id 
 *  - 1 byte  | Data length
 *  - n bytes | Data
 */


#include <AltSoftSerial.h>
#include <EEPROM.h>
#include "config.h"


#if PIN_BLUETOOTH_RX != 8 || PIN_BLUETOOTH_TX != 9
#error "Bluetooth uses AltSoftSerial, which MUST use ping 8 for RX and pin 9 for TX\nPlease check config.h"
#endif


#define PWD_LOCATION   (BLUETOOTH_EEPROM_LOCATION + 0)
#define PWD_LEN        (4)
// Note: the Bluetooth module does indeed store the name, but I'm not sure
// yet how I should read the data back
#define NAME_LOCATION  (BLUETOOTH_EEPROM_LOCATION + PWD_LEN)
#define NAME_LEN       (20 + 1) // Include a null-terminator



namespace Bluetooth {
  
  AltSoftSerial hc06;

  void (*callbacks[BLUETOOTH_CALLBACKS_LEN])(char *data, unsigned len);



  __attribute__((constructor))
  static void _init(void) {

#ifndef NDEBUG
    Serial.println("Initializing Bluetooth...");
#endif

    hc06.begin(9600);

    unsigned char pin[PWD_LEN];
    unsigned char name[NAME_LEN];

    getPassword(pin);
    getName(name);

    // AFAIK only '0' to '9' are valid values
    // An extra check shouldn't be needed, but let's prevent bricking anything
    for (size_t i = 0; i < PWD_LEN; i++)
      if (pin[i] < '0' || pin[i] > '9')
        goto invalid_pin;
    Serial.write(pin, 4);
    hc06.write("AT+PIN");
    hc06.write(pin, 4);
  invalid_pin:
  
    // 0xFF == No data has been written yet
    if (name[0] != 0xFF) {
      // Note: this only works after a reboot because reasons: https://picaxeforum.co.uk/threads/hc-06-rename-issue.28561/
      hc06.write("AT+NAME");
      hc06.write(name, strlen(name));
    }
    hc06.write("AT+NAMEquack");

#ifndef NDEBUG
    Serial.println("Initialized Bluetooth");
#endif
  }
  


  static bool waitForData(int timeout) {
    unsigned long lastRcvTime = millis();
    while (!hc06.available()) {
      if (millis() - lastRcvTime > timeout) {
        send("E_TIMEOUT", sizeof("E_TIMEOUT") - 1, -1);
#ifndef NDEBUG
        Serial.print("Timeout exceeded: ");
        Serial.println(timeout);
#endif
        return false;
      }
    }
    return true;
  }


  static void checkForMessage(int timeout) {
    if (!hc06.available())
      return;

#ifndef NDEBUG
    Serial.println("Receiving message");
#endif

    unsigned char id  = hc06.read();
    if (!waitForData(timeout))
      return;
#ifndef NDEBUG
    Serial.print("ID: ");
    Serial.println((int)id);
#endif
    unsigned char len = hc06.read();
    if (!waitForData(timeout))
      return;
#ifndef NDEBUG
    Serial.print("Length: ");
    Serial.println((int)len);
#endif

    unsigned char index = 0;
    char buf[len];

    if (callbacks[id] == NULL) {
      send("E_UNDEFINED", sizeof("E_UNDEFINED") - 1);
      return;
    }

    while (index < len) {
      if (!waitForData(timeout))
        return;
      while (hc06.available()) {
        buf[index] = hc06.read();
#ifndef NDEBUG
      Serial.print("Received '");
      Serial.print(buf[index]);
      Serial.print("' (");
      Serial.print((int)buf[index]);
      Serial.println(")");
#endif
        index++;
        if (index >= len)
          break;
      }
    }
    
    callbacks[id](buf, len);
  }


  void setCallback(char id, void (*callback)(char *data, unsigned char len)) {
    callbacks[id] = callback;
  }


  void send(char *data, unsigned char len, unsigned char code = 0) {
    hc06.write(code);
    hc06.write(len);
    hc06.write(data, len);
#ifndef NDEBUG
    Serial.print("Sending: ");
    Serial.write(data, len);
    Serial.print("\nStatus: ");
    Serial.println(code);
#endif
  }


  void listen(unsigned long listenTimeout, unsigned long acceptTimeout = BLUETOOTH_DEFAULT_TIMEOUT) {
#ifndef NDEBUG
    Serial.println("Listening for packet...");
#endif
    unsigned long t = millis();
    while (millis() - t < listenTimeout)
      checkForMessage(acceptTimeout);
#ifndef NDEBUG
    Serial.println("Done listening");
#endif
  }


  void getPassword(char *out) {
    for (size_t i = 0; i < PWD_LEN; i++)
      out[i] = EEPROM.read(PWD_LOCATION + i);
  }


  void getName(char *out) {
    size_t i = 0;
    for (; i < NAME_LEN; i++) {
      out[i] = EEPROM.read(PWD_LOCATION + i);
      if (out[i] == 0)
        break;
    }
    out[i] = 0;
  }


  void setPassword(const char *pin) {
    for (size_t i = 0; i < PWD_LEN; i++)
      EEPROM.write(PWD_LOCATION + i, pin[i]);
  }


  void setName(const char *name) {
    size_t i = 0;
    for ( ; i < NAME_LEN; i++) {
      EEPROM.write(NAME_LOCATION + i, name[i]);
      if (name[i] == 0)
        break;
    }
    EEPROM.write(NAME_LOCATION + i, 0);
  }
}
