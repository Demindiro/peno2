#ifndef CONFIG_H
#define CONFIG_H

int none; // TODO

/************************
 * Bluetooth
 */

// NOTE: these values aren't
#define PIN_BLUETOOTH_RX  8
#define PIN_BLUETOOTH_TX  9

#define BLUETOOTH_EEPROM_LOCATION 1
#define BLUETOOTH_EEPROM_LENGTH   32

#define BLUETOOTH_CALLBACKS_LEN   256

#define BLUETOOTH_DEFAULT_TIMEOUT 200


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
#define PIN_SERVO_PLATFORM   7
#define PIN_SERVO_FEED       0
#define PIN_MOTOR_LEFT       5
#define PIN_MOTOR_RIGHT      6
#define PIN_EMPTY_ANALOG     A0

#define MOTOR_SPINUP      1000 // In milliseconds
#define SERVO_TURN_TIME    340  // In milliseconds
#define VELOCITY_FRONT     200
#define VELOCITY_BACK       50
#define ANGLE_LEFT_FRONT  (-20)
#define ANGLE_RIGHT_FRONT ( 20)
#define ANGLE_LEFT_BACK   (-30)
#define ANGLE_RIGHT_BACK  ( 30)
#define SERVO_FEED_OPEN     30
#define SERVO_FEED_CLOSED  -30

#define VELOCITY_SLOW     4000
#define VELOCITY_MEDIAN   3000
#define VELOCITY_FAST     2000

#endif
