#ifndef CONFIG_H
#define CONFIG_H

int none; // TODO

/************************
 * Bluetooth
 */

// NOTE: these values aren't
#define BLUETOOTH_RX  8
#define BLUETOOTH_TX  9

#define BLUETOOTH_EEPROM_LOCATION 1
#define BLUETOOTH_EEPROM_LENGTH   32

#define BLUETOOTH_CALLBACKS_LEN   256


/************************
 * Speedometer
 */
#define SPEEDOMETER_LDR_FIRST    A4
#define SPEEDOMETER_LDR_SECOND   A5
#define SPEEDOMETER_DISTANCE     none // In meters
#define SPEEDOMETER_THRESHOLD    100
#define SPEEDOMETER_TIMEOUT      1    // In seconds -- Prevent being stuck if for some reason the threshold is not reached


/************************
 * Training
 */
#define PIN_SERVO_HORIZONTAL_ANGLE none
#define PIN_SERVO_FEED none
#define PIN_MOTOR_UPPER none
#define PIN_MOTOR_LOWER none
#define PIN_EMPTY_ANALOG none

#define MOTOR_SPINUP none  // tijd voordat de motoren op toerental zijn
#define SERVO_TURN_LIMIT 340  // tijd voordat de servo op positie staat
#define POWER_VOORAAN none
#define POWER_ACHTERAAN none
#define ANGLE_LV none  // hoek om linksvoor te spelen
#define ANGLE_LA none  // hoek om linksachter te spelen
#define ANGLE_RV none  // hoek om rechtsvoor te spelen
#define ANGLE_RA none  // hoek om rechtsachter te spelen
#define FEED_LO none // SERVO_FEED open stand
#define FEED_UP none // SERVO_FEED gesloten stand

const int TRAAG = 4000;
const int GEMIDDELD = 3000;
const int SNEL = 2000;

#endif
