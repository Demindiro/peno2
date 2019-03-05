/**
 * TODO:
 *  - What's a PDA service? Apparently it can be used to read the name back ( = no need to store the name in EEPROM)
 */

namespace Bluetooth {

  /**
   * Setup
   */

  void init();

  void setCallback(char id, void (*callback)(char *data, size_t len));

  void isModuleConnected();


  /**
   * Wireless
   */
   
  bool isConnected();

  void send(char *data, size_t len);

  void listenOnce();

  void listenOnce(int ms);


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
