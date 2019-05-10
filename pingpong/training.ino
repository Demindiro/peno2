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
  

  void setFireSpeed(int velocityLeft, int velocityRight) {
    _stopMotors = false;
    analogWrite(PIN_MOTOR_LEFT, constrain(velocityLeft , 0, 255 * MOTOR_LEFT_SCALING));
    analogWrite(PIN_MOTOR_RIGHT, constrain(velocityRight, 0, 255 * MOTOR_RIGHT_SCALING));
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
    setFireSpeed(0, 0);
    //_stopMotors = true;
  }


  // Nomnomnom
  void feed(void){
      setServo(PIN_SERVO_FEED, SERVO_FEED_OPEN);
      Bluetooth::listen(SERVO_TURN_TIME);
      setServo(PIN_SERVO_FEED, SERVO_FEED_CLOSED);
  }


  //__attribute__((constructor))
  void init(void) {
    pinMode(PIN_MOTOR_LEFT, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT, OUTPUT);
    randomSeed(analogRead(PIN_EMPTY_ANALOG));
    //SoftPWMSetFadeTime(PIN_SERVO_PLATFORM)
  }


  void fire(int angle, int velocityLeft, int velocityRight, int count = 1, int feedDelay = VELOCITY_SLOW, bool spinUp = true) {          
    if (Led::ballCountFeedback() <= 0) {
      DEBUGLN(F("No balls. Won't run"));
      return;
    }
      
    DEBUG(F("Angle: "));
    DEBUGLN(angle);
    DEBUG(F("Relative velocities: "));
    DEBUG(velocityLeft);
    DEBUG(F(", "));
    DEBUGLN(velocityRight);
    
    setFireSpeed(velocityLeft, velocityRight);
    if (spinUp)
      delay(MOTOR_SPINUP_TIME);
    setServo(PIN_SERVO_PLATFORM, angle);

    for(int i = 0; i < count; i++) {
      Bluetooth::listen(feedDelay);
      feed();
      
      float velocity = Speedometer::measureVelocity();
      DEBUG(F("Velocity: "));
      DEBUGLN(velocity);
      char buf[32];
      dtostrf(velocity, 4, 2, buf);
      Bluetooth::sendRaw(buf, strlen(buf));
      
      if (Led::ballCountFeedback() <= 0) {
        DEBUGLN(F("Out of balls. Stopping"));
        return;
      }
      
      Bluetooth::listen(SERVO_TURN_TIME);
      
      if (_stopMotors) {
        DEBUGLN(F("Stopped training"));
        return;
      }
    }
  }

  
  void fireDirection(enum DIRECTION direction, int count = 1, int feedDelay = VELOCITY_SLOW, int spin = 0, bool spinUp = true){
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

    int velL = velocity, velR = velocity;
    if (spin < 0) {
      velL /= 0.83;
      velR *= 0.83;      
    } else if (spin > 0) {
      velL *= 0.83;
      velR /= 0.83;
    }

    //velL = 100;
    //velR = 255;

    fire(angle, velL, velR, count, feedDelay, spinUp);
  }
  
  void fireRandom(int count = 1, int feedDelay = VELOCITY_SLOW) {
    fireDirection((enum DIRECTION)random(0,4), 1, feedDelay, random(-1,2), true);
    for(int i = 1; i < count; i++)
      fireDirection((enum DIRECTION)random(0,4), 1, feedDelay, random(-1,2), false);
    stopMotors();
  }
  
  void fireLeftRight(int count = 2, int feedDelay = VELOCITY_SLOW) {
    fireDirection((enum DIRECTION)random(0,2), 1, feedDelay, random(-1,2), true);
    for(int i = 1; i < count; i += 2) {
      fireDirection((enum DIRECTION)random(2,4), 1, feedDelay, random(-1,2), false);
      fireDirection((enum DIRECTION)random(0,2), 1, feedDelay, random(-1,2), false);
    }
    fireDirection((enum DIRECTION)random(2,4), 1, feedDelay, random(-1,2), false);
    stopMotors();
  }
}
