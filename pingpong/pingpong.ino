#include <SoftPWM_timer.h>
#include <SoftPWM.h>

//#define NDEBUG

#include <assert.h>
#include <SoftPWM.h>
#include "bluetooth.h"
#include "training.h"
#include "led.h"
#include "speedometer.h"


/************************
 * Bluetooth Commands
 */

void echo(char *data, size_t len) {
  Bluetooth::send(data, len);
}


void setPassword(char *data, size_t len) {
  // TODO
}


/**
 * ID: 0
 * Payload length: 3 bytes
 * - Byte 0:
 *   - n: Fire <n> balls
 * - Byte 1:
 *   - 0: Fire near the net
 *   - 1: Fire far from the net
 * - Byte 2:
 *   - 0: Fire to the left
 *   - 1: Fire to the right
 */
void trainingDefault(char *data, size_t len) {
  assert(len == 3);
  // LSB first:
  // - Bit 0: Back/front
  // - Bit 1: Left/right
  Training::fireDirection(data[1] & (data[2] << 1), data[0]);
}


/**
 * ID: 1
 * Payload length: 3 bytes
 * - Byte 0:
 *   - n: Fire <n> balls
 * - Byte 1:
 *   - theta: Set the angle to <theta> degrees
 * - Byte 2:
 *   - v: Set the ball velocity to <v>
 */
void trainingManual(char *data, size_t len) {
  assert(len == 3);
  Training::fire(data[2], data[1], data[0]);
}


/**
 * ID: 3
 * Payload length: 1 byte
 * - Byte 0:
 *   - <n>: Fire <n> balls
 */
void trainingRandom(char *data, size_t len) {
  //assert(len == 1);
  Training::fireRandom(data[0]);
}


/**************
 * Debugging commands
 */

void setPlatformServo(char *data, unsigned char len) {
  //assert(len == 1);
  Serial.print("Platform Servo: ");
  Serial.println((int)data[0]);
  Training::setServo(7, data[0]);
}

void setFireSpeed(char *data, unsigned char len) {
  Serial.print("Fire Speed: ");
  Serial.println((int)data[0]);
  Training::setFireSpeed(5, data[0]);
  Training::setFireSpeed(6, data[0]);
}

void stopMotors(char *data, unsigned char len) {
#ifndef NDEBUG
  Serial.println("Stopping motor");
#endif
}



/************************
 * Main
 */

void setup() {
  Serial.begin(9600);
  SoftPWMBegin(SOFTPWM_NORMAL);
  /*
  Bluetooth::init();
  Training::init();
  Led::init();
  */
  /*
  Bluetooth::setCallback( 0, trainingDefault);
  Bluetooth::setCallback( 1, trainingManual);
  Bluetooth::setCallback( 2, trainingRandom);
  Bluetooth::setCallback(60, stopMotors);
  Bluetooth::setCallback('A', echo);
  Bluetooth::setCallback('P', setPassword);
  Bluetooth::setCallback('S', setPlatformServo);
  Bluetooth::setCallback('S', setFireSpeed);  
  Bluetooth::setCallback('T', trainingRandom);
  */
}


void loop() {
  //Bluetooth::listen(-1);
  /*
  Training::setServo(PIN_SERVO_PLATFORM, 60);
  delay(4500);
  Training::setServo(PIN_SERVO_PLATFORM, -60);
  delay(4500);
  */
//  while (1) {
/*    Serial.println(analogRead(SPEEDOMETER_LDR_FIRST));
    Serial.println(analogRead(SPEEDOMETER_LDR_SECOND));
    Serial.println("======");*/
    //Serial.println(Speedometer::measureVelocity());
    //delay(1000);
  //}      setServo(PIN_SERVO_FEED, SERVO_FEED_OPEN);
    //Bluetooth::listen(SERVO_TURN_TIME);
    delay(SERVO_TURN_TIME);
    Training::setServo(PIN_SERVO_PLATFORM, SERVO_FEED_CLOSED);
    //Bluetooth::listen(SERVO_TURN_TIME);
    delay(SERVO_TURN_TIME);
    Training::setServo(PIN_SERVO_PLATFORM, SERVO_FEED_OPEN);
}
