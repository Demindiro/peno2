/**
 * TODO:
 *  - What's a PDA service? Apparently it can be used to read the name back ( = no need to store the name in EEPROM)
 */

namespace Bluetooth {

  /**
   * Setup
   */

  void init();

  void setCallback(char id, void (*callback)(char *data, unsigned char len));

  void isModuleConnected();


  /**
   * Wireless
   */
   
  bool isConnected();

  void send(char *data, unsigned char len);


   /**
    * We can't use a timer :D /s
    */
   void listen(int timeout);


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
