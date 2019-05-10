/** @file */ 

#ifndef CONFIG_H
#define CONFIG_H


/************************
 * Bluetooth
 */

#define PIN_BLUETOOTH_RX  8
#define PIN_BLUETOOTH_TX  9

#define BLUETOOTH_EEPROM_LOCATION 1
#define BLUETOOTH_EEPROM_LENGTH   32

#define BLUETOOTH_CALLBACKS_LEN   256

#define BLUETOOTH_DEFAULT_TIMEOUT 2000


/************************
 * Speedometer
 */
#define SPEEDOMETER_LDR_FIRST              A0
#define SPEEDOMETER_LDR_SECOND             A1
#define SPEEDOMETER_DISTANCE                0.11 // In meters
#define SPEEDOMETER_THRESHOLD_FIRST       200
#define SPEEDOMETER_THRESHOLD_SECOND       20
#define SPEEDOMETER_TIMEOUT           1000000  // In microseconds -- Prevent being stuck if for some reason the threshold is not reached


/************************
 * Training
 */
#define PIN_SERVO_PLATFORM   7
#define PIN_SERVO_FEED      11
#define PIN_MOTOR_LEFT       6
#define PIN_MOTOR_RIGHT      5
#define MOTOR_LEFT_SCALING   1
#define MOTOR_RIGHT_SCALING  0.84
#define PIN_EMPTY_ANALOG     A6
#define SERVO_SCALING        (30.0f / 60.0f) // 

#define MOTOR_SPINUP_TIME 2000  // In milliseconds
#define SERVO_TURN_TIME    900  // In milliseconds
#define VELOCITY_FRONT     175
#define VELOCITY_BACK      220
#define ANGLE_LEFT_FRONT    10
#define ANGLE_RIGHT_FRONT  -10
#define ANGLE_LEFT_BACK      8
#define ANGLE_RIGHT_BACK    -8
#define SERVO_FEED_OPEN    -70
#define SERVO_FEED_CLOSED   30

#define VELOCITY_SLOW     4000
#define VELOCITY_MEDIAN   3000
#define VELOCITY_FAST     2000


/*************
 * LED
 */
#define LED_PIN_RED       3
#define LED_PIN_GREEN     4
#define LED_PIN_BLUE      2


/********
 * Balls
 */
#define MAX_BALL_COUNT             10
#define BALLS_TRIG_PIN             A3
#define BALLS_ECHO_PIN             A2
#define BALLS_CALIBRATION_FACTOR   (1 / 40.0 / 4.6)


/*********
 * Serial
 */
#define SERIAL_BAUD_RATE   230400


#endif
