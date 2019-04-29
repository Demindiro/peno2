#ifndef BLUETOOTH_H
#define BLUETOOTH_H


/**
 * TODO:
 *  - What's a PDA service? Apparently it can be used to read the name back ( = no need to store the name in EEPROM)
 */
#include "config.h"

namespace Bluetooth {

  /**
   * Setup
   */

  void init(void);

  void setCallback(char id, void (*callback)(char *data, unsigned char len));

  void isModuleConnected(void); // TODO


  /**
   * Wireless
   */
   
  bool isConnected();

  void send(char *data, unsigned char len, unsigned char code = 0);


   /**
    * We can't use a timer :D /s
    */
   void listen(unsigned long listenTimeout, unsigned long acceptTimeout = BLUETOOTH_DEFAULT_TIMEOUT);


  /**
   * Configuration
   * 
   * These are stored in EEPROM memory
   */
  void getPassword(char *out);

  void getName(char *out);
   
  void setPassword(char *pin);

  void setName(char *name);
}


#endif
