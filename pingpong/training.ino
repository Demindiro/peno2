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

int SERVO_HORIZONTAL_ANGLE; //maak een servo-object voor de servo die de hoek bestuurt
int SERVO_FEED; //maak een servo-object voor de servo die de en aanvoert



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
      SoftPWMSet(servo, constrain(angle, 7, 38));
    }

    // Nomnomnom
    static void feed(void){
        setServo(SERVO_FEED, FEED_UP);
        delay(SERVO_TURN_LIMIT);       
        setServo(SERVO_FEED, FEED_LO);
        delay(SERVO_TURN_LIMIT);
    }


    void init(void) {
      pinMode(PIN_MOTOR_UPPER, OUTPUT);
      pinMode(PIN_MOTOR_LOWER, OUTPUT);
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
          velocity = POWER_VOORAAN;
          break;
        case LEFT_BACK:
          angle    = ANGLE_LA;
          velocity = POWER_VOORAAN;
          break;
        case RIGHT_FRONT:
          angle    = ANGLE_LV;
          velocity = POWER_ACHTERAAN;
          break;
        case RIGHT_BACK:
          angle    = ANGLE_RA;
          velocity = POWER_ACHTERAAN;
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
