/** @file */ 

/*
 * TO-DO's:
 *  - een waarde per servo die aangeeft of de servo al juiststaat
 *  - overbodige code verwijderen van de servos
 */

#include "training.h"
#include <assert.h>
#include <SoftPWM.h>
#include <SoftPWM_timer.h>
#include "config.h"
#include "bluetooth.h"
#include "speedometer.h"


/*
 * class met alle trainingsprogrammas:
 *  - linksVoor(), linksAchter(), rechtsVoor() en rechtsAchter(): Schiet een bal op de gespecifieerde plaats
 *  - willekeurig()
 */
namespace Training {

  static bool _stopMotors = false;
  
  
  void setFireSpeed(int pin, int velocity){
    analogWrite(pin, constrain(velocity, 0, 255));
  }

  void _setFireSpeed(int velocityLeft, int velocityRight){
    analogWrite(PIN_MOTOR_LEFT, constrain(velocityLeft , 0, 255));
    analogWrite(PIN_MOTOR_LEFT, constrain(velocityRight, 0, 255));
  }


  void setServo(int servo, float angle) {
    float scaled = constrain(map(angle, -90 * SERVO_SCALING, 90 * SERVO_SCALING, 14, 35), 14 - 100, 35 + 100);
    DEBUG(F("Angle: "));
    DEBUG(angle);
    DEBUG(F(" --> Mapped angle: "));
    DEBUGLN(scaled);
    SoftPWMSet(servo, scaled);
  }


  void stopMotors() {
    setFireSpeed(PIN_MOTOR_LEFT, 0);
    setFireSpeed(PIN_MOTOR_RIGHT, 0);
    _stopMotors = true;
  }


  // Nomnomnom
  void feed(void){
      setServo(PIN_SERVO_FEED, SERVO_FEED_OPEN);
      delay(SERVO_TURN_TIME);
//      Bluetooth::listen(SERVO_TURN_TIME);
      setServo(PIN_SERVO_FEED, SERVO_FEED_CLOSED);
  }


  //__attribute__((constructor))
  void init(void) {
    pinMode(PIN_MOTOR_LEFT, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT, OUTPUT);
    randomSeed(analogRead(PIN_EMPTY_ANALOG));
    //SoftPWMSetFadeTime(PIN_SERVO_PLATFORM)
  }


  void fire(int angle, int velocityLeft, int velocityRight, int count = 1, int feedDelay = VELOCITY_SLOW) {
#ifndef NDEBUG
    DEBUG(F("Angle: "));
    DEBUGLN(angle);
    DEBUG(F("Relative velocities: "));
    DEBUG(velocityLeft);
    DEBUG(F(", "));
    DEBUG(velocityRight);
#endif
    setFireSpeed(PIN_MOTOR_LEFT, velocityLeft);
    setFireSpeed(PIN_MOTOR_RIGHT, velocityRight);

    setServo(PIN_SERVO_PLATFORM, angle);

    for(int i = 0; i < count; i++) {
      Bluetooth::listen(feedDelay);
      feed();
      float velocity = Speedometer::measureVelocity();
#ifndef NDEBUG
      DEBUG(F("Velocity: "));
      DEBUGLN(velocity);
#endif
      char buf[32];
      dtostrf(velocity, 8, 2, buf);
      Bluetooth::sendRaw(buf, strlen(buf));
      delay(SERVO_TURN_TIME);
      //Bluetooth::listen(SERVO_TURN_TIME);
      if (_stopMotors) {
        _stopMotors = false;
        return;
      }
    }
  }

  
  void fireDirection(enum DIRECTION direction, int count = 1, int feedDelay = VELOCITY_SLOW, int spin = 0){
    int velocity, angle;

    switch (direction) {
      case LEFT_FRONT:
        DEBUGLN(F("LF"));
        angle    = ANGLE_LEFT_FRONT;
        velocity = VELOCITY_FRONT;
        break;
      case LEFT_BACK:
        DEBUGLN(F("LB"));
        angle    = ANGLE_LEFT_BACK;
        velocity = VELOCITY_BACK;
        break;
      case RIGHT_FRONT:
        DEBUGLN(F("RF"));
        angle    = ANGLE_RIGHT_FRONT;
        velocity = VELOCITY_FRONT;
        break;
      case RIGHT_BACK:
        DEBUGLN(F("RB"));
        angle    = ANGLE_RIGHT_BACK;
        velocity = VELOCITY_BACK;
        break;
      default:
        DEBUGLN(F("This cannot happen :o"));
        Serial.flush();
        assert(0);
    }

    int velocityLeft  = spin <= 0 ? velocity : 0;
    int velocityRight = spin >= 0 ? velocity : 0;

    fire(angle, velocityLeft, velocityRight, count, feedDelay);
  }
  
  void fireRandom(int count = 1, int feedDelay = VELOCITY_SLOW){
    for(int i = 0; i <= count; i++)
      fireDirection((enum DIRECTION)random(0,4), 1, feedDelay, random(-1,2));
    stopMotors();
  }
  
  void fireLeftRight(int count = 2, int feedDelay = VELOCITY_SLOW){
    for(int i = 0; i <= count; i++) {
      fireDirection((enum DIRECTION)random(0,2), 1, feedDelay, random(-1,2));
      fireDirection((enum DIRECTION)random(2,4), 1, feedDelay, random(-1,2));
    }
    stopMotors();
  }
}
