/** @file */ 

#ifndef BLUETOOTH_H
#define BLUETOOTH_H


//
// TODO:
//  - What's a PDA service? Apparently it can be used to read the name back ( = no need to store the name in EEPROM)
//
#include "config.h"

namespace Bluetooth {

  //
  // Setup
  //

  /**
   * Initialize the Bluetooth module
   */
  void init(void);

  /**
   * Register a callback
   * 
   * @param id is the byte by which the callback can be called
   * @param callback is the function which will be called
   */
  void setCallback(char id, void (*callback)(char *data, unsigned char len));

  /**
   * WIP: Check if the module is connected
   * 
   * NOT IMPLEMENTED
   * 
   * @returns true if connected, otherwise false
   */
  bool isModuleConnected(void);


  //
  // Wireless
  //

  /**
   * WIP: Check if a controller is connected
   * 
   * @returns true if connected, otherwise false
   */
  bool isConnected();

  /**
   * Send data back to the controller
   * 
   * @param data is a pointer to the data to send
   * @param len is the length of the data to send (in bytes)
   * @param code is the status code to return
   */
  void send(char *data, unsigned char len, unsigned char code = 0);


   /**
    * Wait for input from the controller
    * 
    * We can't use a timer :D /s
    * 
    * @param listenTimeout is the delay to wait for a message before timing out
    * @param acceptTimeout is the delay to wait between bytes sent before returning E_TIMEOUT
    */
   void listen(unsigned long listenTimeout, unsigned long acceptTimeout = BLUETOOTH_DEFAULT_TIMEOUT);


   //
   // Configuration
   //
   // These are stored in EEPROM memory
   //

  /**
   * Get the password of the Bluetooth module
   * 
   * @param out is a 4 bytes long buffer to copy the password to
   */
  void getPassword(char *out);

  /**
   * Get the name of the Bluetooth module
   * 
   * @param out is a 21 bytes long buffer to copy the name to
   */
  void getName(char *out);

  /**
   * Set the password of the Bluetooth module
   * 
   * @param pin is a 4 bytes long buffer 
   */
  void setPassword(char *pin);

  /**
   * Set the name of the Bluetooth module
   * 
   * @param name is a null-terminated string. If the string is longer than 20
   * bytes (excluding null-terminator), the remainder of the string is truncated
   */
  void setName(char *name);
}


#endif
