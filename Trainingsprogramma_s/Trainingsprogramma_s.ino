/*
 * TO-DO's:
 *  - een waarde per servo die aangeeft of de servo al juiststaat
 *  - overbodige code verwijderen van de servos
 */
    
    
    
    // Importeer de software PWM library
#include <PWMSoft.h>
#include <SoftPWM_timer.h>

/*
 * Trainingsprogrammas voor de PPP.
 *  Methods linksVoor(), rechtsVoor(), linksAchter() en rechtsAchter().
 *  Alle posities zijn gegeven vanuit het standpunt van de PPP. 
 */

int none;
/*
 * *************************************DEFINITIE VAN WAARDEN****************************************
 */
#define PIN_SERVO_HORIZONTAL_ANGLE none
#define PIN_SERVO_FEED none
#define PIN_MOTOR_UPPER none
#define PIN_MOTOR_LOWER none
#define PIN_EMPTY_ANALOG none

#define MOTOR_SPINUP none  // tijd voordat de motoren op toerental zijn
#define SERVO_TURN_LIMIT 340  // tijd voordat de servo op positie staat
#define POWER_VOORAAN none
#define POWER_ACHTERAAN none
#define ANGLE_LV none  // hoek om linksvoor te spelen
#define ANGLE_LA none  // hoek om linksachter te spelen
#define ANGLE_RV none  // hoek om rechtsvoor te spelen
#define ANGLE_RA none  // hoek om rechtsachter te spelen
#define FEED_LO none // SERVO_FEED open stand
#define FEED_UP none // SERVO_FEED gesloten stand
/*
 * **************************************************************************************************
 */
int SERVO_HORIZONTAL_ANGLE; //maak een servo-object voor de servo die de hoek bestuurt
int SERVO_FEED; //maak een servo-object voor de servo die de ballen aanvoert

  //schietsnelheid (milliseconden)
const int TRAAG = 4000;
const int GEMIDDELD = 3000;
const int SNEL = 2000;

/*
 * class met alle trainingsprogrammas:
 *  - linksVoor(), linksAchter(), rechtsVoor() en rechtsAchter(): Schiet een bal op de gespecifieerde plaats
 *  - willekeurig()
 */
class Trainingsprogrammas{
    public:
    
    /*
     * linksvoor(), linksAchter(), rechtsVoor(), rechtsAchter() en willekeurig():
     *  - aantal: Aantal af te vuren ballen
     *  - snelheid: Snelheid van opeenvolgende ballen
     */
    void linksVoor(int aantal = 1, int snelheid = TRAAG){
      
      setFireSpeed(PIN_MOTOR_UPPER, POWER_VOORAAN);
      setFireSpeed(PIN_MOTOR_LOWER, POWER_VOORAAN);
            
//      if(SERVO_HORIZONTAL_ANGLE.read()!=ANGLE_LV){
//        SERVO_HORIZONTAL_ANGLE.writeMicroseconds(ANGLE_LV);
//        delay(SERVO_TURN_LIMIT);
//      }else{
//        delay(MOTOR_SPINUP); //tijd nodig voordat de motoren op toerental zijn
//      }
      setServo(SERVO_HORIZONTAL_ANGLE, ANGLE_LV);
      delay(SERVO_TURN_LIMIT);
      
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
      }
    }
    
    void linksAchter(int aantal = 1, int snelheid = TRAAG){
    
      setFireSpeed(PIN_MOTOR_UPPER, POWER_ACHTERAAN);
      setFireSpeed(PIN_MOTOR_LOWER, POWER_ACHTERAAN);
      
//      if(SERVO_HORIZONTAL_ANGLE.read()!=ANGLE_LA){
//        SERVO_HORIZONTAL_ANGLE.writeMicroseconds(ANGLE_LA);
//        delay(SERVO_TURN_LIMIT);
//      }else{
//        delay(MOTOR_SPINUP); //tijd nodig voordat de motoren op toerental zijn
//      }
      setServo(SERVO_HORIZONTAL_ANGLE, ANGLE_LA);
      delay(SERVO_TURN_LIMIT);      
      
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
      }
    }
    
    void rechtsVoor(int aantal = 1, int snelheid = TRAAG){
      
      setFireSpeed(PIN_MOTOR_UPPER, POWER_VOORAAN);
      setFireSpeed(PIN_MOTOR_LOWER, POWER_VOORAAN); 
           
//      if(SERVO_HORIZONTAL_ANGLE.read()!=ANGLE_RV){
//        SERVO_HORIZONTAL_ANGLE.writeMicroseconds(ANGLE_RV);
//        delay(SERVO_TURN_LIMIT);
//      }else{
//        delay(MOTOR_SPINUP); //tijd nodig voordat de motoren op toerental zijn 
//      }
      setServo(SERVO_HORIZONTAL_ANGLE, ANGLE_RV);
      delay(SERVO_TURN_LIMIT);  
           
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
      }
    }
    
    void rechtsAchter(int aantal = 1, int snelheid = TRAAG){
    
      setFireSpeed(PIN_MOTOR_UPPER, POWER_ACHTERAAN);
      setFireSpeed(PIN_MOTOR_LOWER, POWER_ACHTERAAN);
      
//      if(SERVO_HORIZONTAL_ANGLE.read()!=ANGLE_RA){
//        SERVO_HORIZONTAL_ANGLE.writeMicroseconds(ANGLE_RA);
//        delay(SERVO_TURN_LIMIT);
//      }else{
//        delay(MOTOR_SPINUP); //tijd nodig voordat de motoren op toerental zijn
//      }

      setServo(SERVO_HORIZONTAL_ANGLE, ANGLE_RA);
      delay(SERVO_TURN_LIMIT);
      
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
      }
    }
    
    void willekeurig(int aantal = 1, int snelheid = TRAAG){
      for(int i; i<=aantal; i++){
        switch(random(1,5)){
          case 1:
            linksVoor(snelheid = snelheid);
            break;
          case 2:
            rechtsVoor(snelheid = snelheid);
            break;
          case 3:
            linksAchter(snelheid = snelheid);
            break;
          case 4:
            rechtsAchter(snelheid = snelheid);
            break;
          default:
            break;
        }
      }
    }
    
    void linksRechts(int aantal = 1, int snelheid = TRAAG){
      for(int i; i<=aantal; i++){
        switch(random(1,3)){
          case 1:
            linksVoor(snelheid = snelheid);
          case 2:
            linksAchter(snelheid = snelheid);
          default:
            linksVoor(snelheid = snelheid);
        }
        switch(random(1,3)){
          case 1:
            rechtsVoor(snelheid = snelheid);
          case 2:
            rechtsAchter(snelheid = snelheid);
          default:
            rechtsVoor(snelheid = snelheid);
        }
      }
    }
          
    private:
      /*
       * setFireSpeed:
       *  - motor: Kies een motor waarvan de snelheid aangepast moet worden
       *  - rate: Geef een snelheid (tussen 0 en 255)
       */
      void setFireSpeed(int motor, int snelheid){
        if(0<=snelheid<=255){
          analogWrite(motor, snelheid);
        }else if(snelheid<=0){
          analogWrite(motor, 0);
        }else if(255<=snelheid){
          analogWrite(motor, 255);
        }
      }
    
      /*
       * feedBall:
       *  - servo: Kies de servo
       *  - snelheid: Tijd tussen ballen (TRAAG, GEMIDDELD, SNEL)
       */
      void feedBall(int servo, int snelheid){
          setServo(servo, FEED_UP);
          delay(SERVO_TURN_LIMIT);       
          setServo(servo, FEED_LO);
          delay(SERVO_TURN_LIMIT);
          delay(snelheid);
    
      }
      
        /*
         * setServo:
         *  - servo: Kies de servo
         *  - angle: Kies de hoek (van 7 tot en met 38)
         */
      void setServo(int servo, int angle){
        if(***servo nog niet juist*** && 7<=angle<=38){
            softPWMSet(servo, angle);
        }else if(***servo nog niet juist*** && angle<7){
            softPWMSet(servo, 7);
        }else if(***servo nog niet juist*** && 38<angle){
            softPWMSet(servo, 38);
        }
      }
 };


void setup() {
  pinMode(PIN_MOTOR_UPPER, OUTPUT);
  pinMode(PIN_MOTOR_LOWER, OUTPUT);
  randomSeed(analogRead(PIN_EMPTY_ANALOG));
  }
  
void loop() {
  Trainingsprogrammas control;
  control.linksVoor();
  control.rechtsVoor();
  control.linksAchter();
  control.rechtsAchter();
  control.willekeurig();
  }
