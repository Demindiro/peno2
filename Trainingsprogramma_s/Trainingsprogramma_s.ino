/*
 * Trainingsprogrammas voor de PPP.
 *  Methods linksVoor(), rechtsVoor(), linksAchter() en rechtsAchter().
 *  Alle posities zijn gegeven vanuit het standpunt van de PPP.
 *   
 */
#include <Servo.h>  //importeer de servo class

const Servo SERVO_H; //maak een horizontaal servo object
const Servo SERVO_FEED; //maak een verticaal servo object
const int MOTOR_U;  //zet de bovenmotor op een pin
const int MOTOR_L;  //zet de ondermotor op een pin
  //schietsnelheid (milliseconden)
const int TRAAG = 4000;
const int GEMIDDELD = 3000;
const int SNEL = 2000;


class Trainingsprogrammas{
  public:

    //de functies zetten de servo in de juiste stand en zetten de motoren op de juiste snelheid
    void linksVoor(int aantal = 1, int snelheid = TRAAG){
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
        servoSet(SERVO_H, ANGLE_LV);
        setFireSpeed(MOTOR_U, POWER_V);
        setFireSpeed(MOTOR_L, POWER_V);
      }
    }
  
    void linksAchter(int aantal = 1, int snelheid = TRAAG){
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
        servoSet(SERVO_H, ANGLE_LA);
        setFireSpeed(MOTOR_U, POWER_A);
        setFireSpeed(MOTOR_L, POWER_A);
      }
    }
  
    void rechtsVoor(int aantal = 1, int snelheid = TRAAG){
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
        servoSet(SERVO_H, ANGLE_RV);
        setFireSpeed(MOTOR_U, POWER_V);
        setFireSpeed(MOTOR_L, POWER_V);
      }
    }
  
    void rechtsAchter(int aantal = 1, int snelheid = TRAAG){
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
        servoSet(SERVO_H, ANGLE_RA);
        setFireSpeed(MOTOR_U, POWER_A);
        setFireSpeed(MOTOR_L, POWER_A);
      }
    }
    
    private:
      
        //servo onder- en bovenlimiet(graden) en draaisnelheidslimiet (milliseconden)
      const int SERVO_LO_LIMIT = 30;
      const int SERVO_UP_LIMIT = 150;
      const int SERVO_TURN_LIMIT = 340;
        //aanvoerservo onder- en bovenlimiet (graden)
      const int FEED_LO = 30;
      const int FEED_UP = 150;
        //horizontale servo hoek (graden)(linksvoor, linksachter, rechtsvoor, rechtsachter)
      const int ANGLE_LV = 30;
      const int ANGLE_LA = 40;
      const int ANGLE_RV = 140;
      const int ANGLE_RA = 150;
        //afschietsnelheid (0-255)(vooraan, achteraan)
      const int POWER_V = 100;
      const int POWER_A = 200;

      //kijkt na of de ingevoerde waarde kan en zet de servo juist
      void servoSet(Servo servo, int angle){
        if(SERVO_LO_LIMIT<=angle<=SERVO_UP_LIMIT){
          servo.write(angle);
        }else if(angle<=SERVO_LO_LIMIT){
          servo.write(SERVO_LO_LIMIT);
        }else if(SERVO_UP_LIMIT<=angle){
          servo.write(SERVO_UP_LIMIT);
        }
      }

      //kijkt na of de ingevoerde waarde kan en zet de motorsnelheid juist
      void setFireSpeed(int motor, int rate){
        if(0<=rate<=255){
          analogWrite(motor, rate);
        }else if(rate<=0){
          analogWrite(motor, 0);
        }else if(255<=rate){
          analogWrite(motor, 255);
        }
      }

      /*
       * feedBall:
       *  servo: Kies de servo
       *  snelheid: Tijd tussen ballen (TRAAG, GEMIDDELD, SNEL)
       */
      void feedBall(Servo servo, int snelheid){
          servoSet(servo, FEED_LO);
          delay(SERVO_TURN_LIMIT);
          delay(snelheid);
          servoSet(servo, FEED_UP);
          delay(SERVO_TURN_LIMIT);
      }
};


void setup() {}
void loop() {
  Trainingsprogrammas control;
  control.linksVoor();
  control.rechtsVoor();
  control.linksAchter();
  control.rechtsAchter();
  }
