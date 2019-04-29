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

  void setFireSpeed(int pin, int velocity){
    analogWrite(pin, constrain(velocity, 0, 255));
  }


  void setServo(int servo, float angle) {
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" --> Mapped angle: ");
    Serial.println(constrain(map(angle, -90, 90, 14, 35), 14, 35));
    SoftPWMSet(servo, constrain(map(angle, -90, 90, 14, 35), 14, 35));
  }


  void stopMotors() {
    setFireSpeed(PIN_MOTOR_LEFT, 0);
    setFireSpeed(PIN_MOTOR_RIGHT, 0);
  }


  // Nomnomnom
  static void feed(void){
      setServo(PIN_SERVO_FEED, SERVO_FEED_OPEN);
      //Bluetooth::listen(SERVO_TURN_TIME);
      delay(SERVO_TURN_TIME);
      setServo(PIN_SERVO_FEED, SERVO_FEED_CLOSED);
      //Bluetooth::listen(SERVO_TURN_TIME);
      delay(SERVO_TURN_TIME);
  }


  __attribute__((constructor))
  static void _init(void) {
    pinMode(PIN_MOTOR_LEFT, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT, OUTPUT);
    randomSeed(analogRead(PIN_EMPTY_ANALOG));
  }


  void fire(int angle, int velocity, int count = 1, int feedDelay = VELOCITY_SLOW) {
    setFireSpeed(PIN_MOTOR_LEFT, velocity);
    setFireSpeed(PIN_MOTOR_RIGHT, velocity);

    setServo(PIN_SERVO_PLATFORM, angle);
          
    for(int i = 0; i < count; i++) {
      feed();
      delay(feedDelay);
      //Bluetooth::listen(feedDelay);
    }
  }

  
  void fireDirection(enum DIRECTION direction, int count = 1, int feedDelay = VELOCITY_SLOW){
    int velocity, angle;

    switch (direction) {
      case LEFT_FRONT:
        Serial.println("LF");
        angle    = ANGLE_LEFT_FRONT;
        velocity = VELOCITY_FRONT;
        break;
      case LEFT_BACK:
        Serial.println("LB");
        angle    = ANGLE_LEFT_BACK;
        velocity = VELOCITY_FRONT;
        break;
      case RIGHT_FRONT:
        Serial.println("RF");
        angle    = ANGLE_RIGHT_FRONT;
        velocity = VELOCITY_BACK;
        break;
      case RIGHT_BACK:
        Serial.println("RB");
        angle    = ANGLE_RIGHT_BACK;
        velocity = VELOCITY_BACK;
        break;
      default:
        Serial.println("This cannot happen :o");
        delay(1000);
        assert(0);
    }

    fire(angle, velocity, count, feedDelay);
  }
  
  void fireRandom(int count = 1, int feedDelay = VELOCITY_SLOW){
    for(int i = 0; i <= count; i++)
      fireDirection((enum DIRECTION)random(0,4), 1, feedDelay);
    stopMotors();
  }
  
  void fireLeftRight(int count = 1, int feedDelay = VELOCITY_SLOW){
    for(int i = 0; i <= count; i++) {
      fireDirection((enum DIRECTION)random(0,2), 1, feedDelay);
      fireDirection((enum DIRECTION)random(2,4), 1, feedDelay);
    }
    stopMotors();
  }
}
