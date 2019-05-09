/** @file */ 

#include <SoftPWM_timer.h>
#include <SoftPWM.h>

//#define NDEBUG

#include <assert.h>
#include <SoftPWM.h>
#include "bluetooth.h"
#include "training.h"
#include "led.h"
#include "speedometer.h"
#include "debug.h"


//#ifndef NDEBUG
#if 0
// TODO: figure out why the 
void __assert(const char *__func, const char *__file, int __lineno, const char *expr) {
  char strline[8];
  itoa(__lineno, strline, 8);
  const char **s = {"Assertion failure: ", __func, " @ ", __file, ":", __lineno, " (", expr, " )\n", NULL};
  for (const char *s = *strs; s != NULL; s++)
    Serial.print(s);
  Serial.flush();
  abort();
}
#endif



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
  // LSB first:
  // - Bit 0: Back/front
  // - Bit 1: Left/right
  char near = data[1];
  char left = data[2];
  signed char spin = data[3];
  int  translated = near | (left << 1);
  DEBUG(translated, BIN);
  Training::fireDirection(translated, data[0], VELOCITY_SLOW, spin);
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
  //assert(len == 3);
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
  DEBUG(F("Platform Servo: "));
  DEBUGLN((int)data[0]);
  Training::setServo(7, data[0]);
}

void setFireSpeed(char *data, unsigned char len) {
  DEBUG(F("Fire Speed: "));
  DEBUGLN((int)data[0]);
  Training::setFireSpeed(5, data[0]);
  Training::setFireSpeed(6, data[0]);
}

void stopMotors(char *data, unsigned char len) {
  DEBUGLN(F("Stopping motor"));
  Training::stopMotors();
}



/************************
 * Main
 */

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  DEBUGLN(F("Initializing..."));
  SoftPWMBegin(SOFTPWM_NORMAL);
  Bluetooth::init();
  Training::init();
  Led::init();
  Bluetooth::setCallback( 0, trainingDefault);
  Bluetooth::setCallback( 1, trainingManual);
  Bluetooth::setCallback( 2, trainingRandom);
  Bluetooth::setCallback(60, stopMotors);
  Bluetooth::setCallback('A', echo);
  Bluetooth::setCallback('P', setPassword);
  Bluetooth::setCallback('S', setPlatformServo);
  Bluetooth::setCallback('S', setFireSpeed);  
  Bluetooth::setCallback('T', trainingRandom);
}


void loop() {
  //Training::setServo(PIN_SERVO_PLATFORM, 0);
  //Bluetooth::listen(-1);
  delay(100);
  Led::ballCountFeedback();
}
