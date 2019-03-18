/**
 * Receiving and sending commands:
 *  - 1 byte  | Command id 
 *  - 1 byte  | Data length
 *  - n bytes | Data
 */


#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "config.h"


#define PWD_LOCATION   (BLUETOOTH_EEPROM_LOCATION + 0)
#define PWD_LEN        (4)
// Note: the Bluetooth module does indeed store the name, but I'm not sure
// yet how I should read the data back
#define NAME_LOCATION  (BLUETOOTH_EEPROM_LOCATION + PWD_LEN)
#define NAME_LEN       (20 + 1) // Include a null-terminator


namespace Bluetooth {
  
  SoftwareSerial hc06(BLUETOOTH_IN, BLUETOOTH_OUT);

  void (*callbacks[BLUETOOTH_CALLBACKS_LEN])(char *data, unsigned len);


  // Receive handler
  // See https://www.teachmemicro.com/arduino-timer-interrupt-tutorial/ for the magic
  unsigned char _poll_id    = 0xFF;
  unsigned char _poll_len   = 0;
  unsigned char _poll_index = 0;
  unsigned char _timeout_counter = 0;
  char _poll_data[256];
  ISR(TIMER2_OVF_vect) {
    // Is sufficient info available to start receiving data?
    if (_poll_id == 0xFF && hc06.available() >= 2) {
      _poll_id  = hc06.read();
      _poll_len = hc06.read();
    }
    // Are we currently receiving data for a command?
    if (_poll_id != 0xFF) {
      // Are we still reading data?
      if (_poll_index < _poll_len) {
        if (!hc06.available()) {
          _timeout_counter++;
          // Prevent being stuck in a loop without ever receiving enough data
          // 32 * 30 = 960ms ~ 1 second, which should be plenty
          if (_timeout_counter > 30) {
            send("TIMEOUT", sizeof("TIMEOUT") - 1);
            _poll_id = 0xFF;
          }
        } else {
          while (hc06.available()) {
            _poll_data[_poll_index] = hc06.read();
            Serial.write(_poll_data[_poll_index]);
            _poll_index++;
            _timeout_counter = 0;
          }
        }
      // Execute the command
      } else {
        if (callbacks[_poll_id] != NULL) {
          callbacks[_poll_id](_poll_data, _poll_len);
          _poll_index = 0;
          _poll_id    = 0xFF;
        } else {
          send("UNDEFINED", sizeof("UNDEFINED") - 1);
        }
      }
    }
  }

  
  void init() {
  
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
  
    // Set the Timer2 interrupt to poll incoming data
    TCCR2B = (TCCR2B & B11111000) | 0x03; // Divide by 32 --> 32ms between calls
    TIMSK2 = (TIMSK2 & B11111110) | 0x01; // Enable Timer2 overflow
  }


  void setCallback(char id, void (*callback)(char *data, unsigned char len)) {
    callbacks[id] = callback;
  }


  void send(char *data, unsigned char len) {
    hc06.write(len);
    hc06.write(data, len);
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
