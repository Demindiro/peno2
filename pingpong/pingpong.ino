#include <SoftPWM_timer.h>
#include <SoftPWM.h>

//#define NDEBUG

#include <assert.h>
#include <SoftPWM.h>
#include "bluetooth.h"
#include "training.h"
#include "led.h"

#define BLUETOOTH_ASSERT(x, msg) do {           \
  if (!(x)) {                                   \
    Bluetooth::send(msg, sizeof(msg) - 1, -1);  \
    return;                                     \
  }                                             \
} while (0)


/************************
 * Bluetooth Commands
 */


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
void trainingDefault(char *data, unsigned char len) {
  BLUETOOTH_ASSERT(len == 3, "Length is incorrect (expected len == 3)");
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
void trainingManual(char *data, unsigned char len) {
  BLUETOOTH_ASSERT(len == 3, "Length is incorrect (expected len == 3)");
  Training::fire(data[2], data[1], data[0]);
}


/**
 * ID: 2
 * Payload length: 1 byte
 * - Byte 0:
 *   - <n>: Fire <n> balls
 */
void trainingRandom(char *data, unsigned char len) {
  BLUETOOTH_ASSERT(len == 1, "Length is incorrect (expected len == 1)");
  Training::fireRandom(data[0]);
}


/**************
 * Debugging commands
 */

#ifndef NDEBUG

void setPlatformServo(char *data, unsigned char len) {
  //assert(len == 1);
  Serial.print("Platform Servo: ");
  Serial.println((int)data[0]);
  Training::setServo(7, data[0]);
}


void setFireSpeed(char *data, unsigned char len) {
  Serial.print("Fire Speed: ");
  Serial.println((int)data[0]);
  Training::setFireSpeed(data[0], data[0]);
}


void stopMotors(char *data, unsigned char len) {
  Serial.println("Stopping motor");
}

void echo(char *data, unsigned char len) {
  Bluetooth::send(data, len);
}


void setPassword(char *data, unsigned char len) {
  // TODO
}

#endif


/************************
 * Main
 */

__attribute__((constructor))
static void _init() {
}


void setup() {
  Serial.begin(9600);
  SoftPWMBegin(SOFTPWM_NORMAL);
  Bluetooth::_init();
  Bluetooth::setCallback(0, trainingDefault);
  Bluetooth::setCallback(1, trainingManual);
  Bluetooth::setCallback(2, trainingRandom);
#ifndef NDEBUG
  Bluetooth::setCallback('A', echo);
  Bluetooth::setCallback('B', setPassword);
  Bluetooth::setCallback('C', setPlatformServo);
  Bluetooth::setCallback('D', setFireSpeed);
  Bluetooth::setCallback('E', trainingRandom);
  Bluetooth::setCallback('F', stopMotors);
#endif
}


int _vel = 0;
void loop() {
  Bluetooth::listen(-1);
  /*
  if (Serial.available()) {
    _vel = Serial.parseInt();
    Serial.println(_vel);
  }
  Training::setFireSpeed(_vel, _vel);
  */
}
