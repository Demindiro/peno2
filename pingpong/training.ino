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

/*
 * Trainingsprogrammas voor de PPP.
 *  Methods linksVoor(), rechtsVoor(), linksAchter() en rechtsAchter().
 *  Alle posities zijn gegeven vanuit het standpunt van de PPP. 
 */



/*
 * class met alle trainingsprogrammas:
 *  - linksVoor(), linksAchter(), rechtsVoor() en rechtsAchter(): Schiet een bal op de gespecifieerde plaats
 *  - willekeurig()
 */
namespace Training {

  static void setFireSpeed(int motor, int snelheid){
    analogWrite(motor, constrain(snelheid, 0, 255));
  }


  static void setServo(int servo, int angle) {
    SoftPWMSet(servo, map(angle, -90, 90, 7, 38));
  }


  // Nomnomnom
  static void feed(void){
      setServo(PIN_TRAINING_SERVO_FEED, SERVO_FEED_OPEN);
      delay(SERVO_TURN_TIME);
      setServo(PIN_TRAINING_SERVO_FEED, SERVO_FEED_CLOSED);
      delay(SERVO_TURN_TIME);
  }


  void init(void) {
    pinMode(PIN_MOTOR_LEFT, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT, OUTPUT);
    randomSeed(analogRead(PIN_EMPTY_ANALOG));
  }


  void fire(int angle, int velocity, int count = 1, int feedDelay = TRAAG) {
    setFireSpeed(PIN_MOTOR_UPPER, velocity);
    setFireSpeed(PIN_MOTOR_LOWER, velocity);

    setServo(SERVO_HORIZONTAL_ANGLE, ANGLE_LV);
          
    for(int i = 0; i < count; i++) {
      feed();
      delay(feedDelay);
    }
  }

  
  void fireDirection(enum DIRECTION direction, int count = 1, int feedDelay = TRAAG){
    int velocity, angle;

    switch (direction) {
      case LEFT_FRONT:
        angle    = ANGLE_LV;
        velocity = VELOCITY_FRONT;
        break;
      case LEFT_BACK:
        angle    = ANGLE_LA;
        velocity = VELOCITY_FRONT;
        break;
      case RIGHT_FRONT:
        angle    = ANGLE_LV;
        velocity = VELOCITY_BACK;
        break;
      case RIGHT_BACK:
        angle    = ANGLE_RA;
        velocity = VELOCITY_BACK;
        break;
      default:
        assert(0);
    }

    fire(velocity, angle, count, feedDelay);
  }
  
  void fireRandom(int count = 1, int feedDelay = TRAAG){
    for(int i = 0; i <= count; i++)
      fire((enum DIRECTION)random(1,5), feedDelay = feedDelay);
  }
  
  void fireLeftRight(int count = 1, int feedDelay = TRAAG){
    for(int i = 0; i <= count; i++) {
      fire((enum DIRECTION)random(1,3), feedDelay = feedDelay);
      fire((enum DIRECTION)random(3,5), feedDelay = feedDelay);
    }
  }
}
