/**
 * Receiving and sending commands:
 *  - 1 byte  | Command id 
 *  - 2 bytes | Data length
 *  - n bytes | Data
 */


#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "config.h"


#define PWD_LOCATION   (BLUETOOTH_EEPROM_LOCATION + 0)
#define PWD_LEN        (4)
#define NAME_LOCATION  (BLUETOOTH_EEPROM_LOCATION + PWD_LEN)
#define NAME_LEN       (20 + 1) // Include a null-terminator


namespace Bluetooth {
  
  SoftwareSerial hc06(BLUETOOTH_IN, BLUETOOTH_OUT);

  void (*callbacks[256])(char *data, size_t len);


  void _receiveHandler() {
    unsigned char  id  = hc06.read();
    unsigned short len = (hc06.read() << 8) + hc06.read();
    char data[len];
    for (size_t i = 0; i < len; i++)
      data[i] = hc06.read();
    if (callbacks[id] != NULL)
      callbacks[id](data, len);
  }

  
  void init() {
    hc06.begin(9600);
    
    char pin[PWD_LEN];
    char name[NAME_LEN];

    getPassword(pin);
    getName(name);

    // AFAIk only '0' to '9' are valid values
    // An extra check shouldn't be needed, but let's prevent bricking anything
    for (size_t i = 0; i < PWD_LEN; i++)
      if (pin[i] < '0' || pin[i] > '9')
        goto invalid_pin;
    hc06.write("AT+PIN");
    hc06.write(pin, 4);
  invalid_pin:
  
    // 0xFF == No data has been written yet
    if (name[0] != 0xFF) {
      hc06.write("AT+NAME");
      hc06.write(name, strlen(name));
    }

    // Listen for incoming data
    attachInterrupt(digitalPinToInterrupt(BLUETOOTH_IN), _receiveHandler, CHANGE);
  }


  void setCallback(char id, void (*callback)(char *data, size_t len)) {
    callbacks[id] = callback;
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
