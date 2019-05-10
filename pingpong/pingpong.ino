#include <SoftPWM_timer.h>
#include <SoftPWM.h>

//#define NDEBUG

#include <assert.h>
#include <SoftPWM.h>
#include "bluetooth.h"
#include "training.h"
#include "led.h"


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
  Training::fire(data[1] & (data[2] << 1), data[0]);
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
  Serial.println("Stopping motor");
}



/************************
 * Main
 */

void setup() {
  Serial.begin(9600);
  SoftPWMBegin(SOFTPWM_NORMAL);
  Bluetooth::setCallback(0, trainingDefault);
  Bluetooth::setCallback(1, trainingManual);
  Bluetooth::setCallback(3, trainingRandom);
  Bluetooth::setCallback('A', echo);
  Bluetooth::setCallback('P', setPassword);
  Bluetooth::setCallback('S', setPlatformServo);
  Bluetooth::setCallback('S', setFireSpeed);  
  Bluetooth::setCallback('T', trainingRandom);
  Bluetooth::setCallback('Z', stopMotors);
}


void loop() {
  Bluetooth::listen(-1);
  //Led::ballCountFeedback();
}
