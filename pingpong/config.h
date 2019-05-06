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

#define BLUETOOTH_DEFAULT_TIMEOUT 2000


/************************
 * Speedometer
 */
#define SPEEDOMETER_LDR_FIRST    A0
#define SPEEDOMETER_LDR_SECOND   A1
#define SPEEDOMETER_DISTANCE     none // In meters
#define SPEEDOMETER_THRESHOLD    100
#define SPEEDOMETER_TIMEOUT      100  // In milliseconds -- Prevent being stuck if for some reason the threshold is not reached


/************************
 * Training
 */
#define PIN_SERVO_PLATFORM   7
#define PIN_SERVO_FEED       0
#define PIN_MOTOR_LEFT       5
#define PIN_MOTOR_RIGHT      6
#define PIN_EMPTY_ANALOG     A6
#define SERVO_SCALING        (30.0f / 60.0f) // 

#define MOTOR_SPINUP      1000  // In milliseconds
#define SERVO_TURN_TIME   4000  // In milliseconds
#define VELOCITY_FRONT     200
#define VELOCITY_BACK       50
#define ANGLE_LEFT_FRONT   -20
#define ANGLE_RIGHT_FRONT   20
#define ANGLE_LEFT_BACK    -30
#define ANGLE_RIGHT_BACK    30
#define SERVO_FEED_OPEN     60
#define SERVO_FEED_CLOSED  -60

#define VELOCITY_SLOW     4000
#define VELOCITY_MEDIAN   3000
#define VELOCITY_FAST     2000


/*************
 * LED
 */
#define LED_PIN_RED       2
#define LED_PIN_GREEN     4
#define LED_PIN_BLUE      3


/*******
 * Balls
 */
#define MAX_BALL_COUNT             10
#define BALLS_TRIG_PIN             A3
#define BALLS_ECHO_PIN             A2
#define BALLS_CALIBRATION_FACTOR   (0.5 / 29.1 * (45.0 / 28.0))



#endif
