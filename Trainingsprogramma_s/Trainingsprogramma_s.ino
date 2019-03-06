const int ONBEPAALD;  //plaatsvervanger voor waarden die nog ingevuld moeten worden
/*
 * Trainingsprogrammas voor de PPP.
 *  Methods linksVoor(), rechtsVoor(), linksAchter() en rechtsAchter().
 *  Alle posities zijn gegeven vanuit het standpunt van de PPP.
 *   
 */
 
#include <Servo.h>  //importeer de servo class

Servo SERVO_H; //maak een horizontaal servo object
Servo SERVO_FEED; //maak een servo object dat ballen aanvoert

const int EMPTY_ANALOG = ONBEPAALD; //Zet een ongebruikte analoge pin
const int SERVO_1 = ONBEPAALD;  //Zet SERVO_H op een pin
const int SERVO_2 = ONBEPAALD;  //Zet SERVO_FEED op een pin
const int MOTOR_U = ONBEPAALD;  //zet de bovenmotor op een pin
const int MOTOR_L = ONBEPAALD;  //zet de ondermotor op een pin
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
     * linksvoor(), linksAchter(), rechtsVoor(), rechtsAchter() en willekeurig:
     *  - aantal: Aantal af te vuren ballen
     *  - snelheid: Snelheid waarmee de ballen aangevoerd worden
     */
    void linksVoor(int aantal = 1, int snelheid = TRAAG){
      
      setFireSpeed(MOTOR_U, POWER_V);
      setFireSpeed(MOTOR_L, POWER_V);
            
      if(SERVO_H.read()!=ANGLE_LV){
        SERVO_H.write(ANGLE_LV);
        delay(SERVO_TURN_LIMIT);
      }else{
        delay(ONBEPAALD); //tijd nodig voordat de motoren op toerental zijn
      }
      
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
      }
    }
  
    void linksAchter(int aantal = 1, int snelheid = TRAAG){

      setFireSpeed(MOTOR_U, POWER_A);
      setFireSpeed(MOTOR_L, POWER_A);
      
      if(SERVO_H.read()!=ANGLE_LA){
        SERVO_H.write(ANGLE_LA);
        delay(SERVO_TURN_LIMIT);
      }else{
        delay(ONBEPAALD); //tijd nodig voordat de motoren op toerental zijn
      }

      
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
      }
    }
  
    void rechtsVoor(int aantal = 1, int snelheid = TRAAG){
      
      setFireSpeed(MOTOR_U, POWER_V);
      setFireSpeed(MOTOR_L, POWER_V); 
           
      if(SERVO_H.read()!=ANGLE_RV){
        SERVO_H.write(ANGLE_RV);
        delay(SERVO_TURN_LIMIT);
      }else{
        delay(ONBEPAALD); //tijd nodig voordat de motoren op toerental zijn 
      }
           
      for(int i; i<aantal; i++){
        feedBall(SERVO_FEED, snelheid);
      }
    }
  
    void rechtsAchter(int aantal = 1, int snelheid = TRAAG){

      setFireSpeed(MOTOR_U, POWER_A);
      setFireSpeed(MOTOR_L, POWER_A);
      
      if(SERVO_H.read()!=ANGLE_RA){
        SERVO_H.write(ANGLE_RA);
        delay(SERVO_TURN_LIMIT);
      }else{
        delay(ONBEPAALD); //tijd nodig voordat de motoren op toerental zijn
      }
      
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
          
    private:

      const int SERVO_TURN_LIMIT = 340; //draaisnelheid van de servo
        //aanvoerservo onder- en bovenlimiet (graden)
      const int FEED_LO = ONBEPAALD;
      const int FEED_UP = ONBEPAALD;
        //horizontale servo hoek (graden)(linksvoor, linksachter, rechtsvoor, rechtsachter)
      const int ANGLE_LV = map(ONBEPAALD, -60, 60, 0, 180);
      const int ANGLE_LA = map(ONBEPAALD, -60, 60, 0, 180);
      const int ANGLE_RV = map(ONBEPAALD, -60, 60, 0, 180);
      const int ANGLE_RA = map(ONBEPAALD, -60, 60, 0, 180);
        //afschietsnelheid (0-255)(vooraan, achteraan)
      const int POWER_V = ONBEPAALD;
      const int POWER_A = ONBEPAALD;

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
      void feedBall(Servo servo, int snelheid){
          servo.write(FEED_UP);
          delay(SERVO_TURN_LIMIT);       
          servo.write(FEED_LO);
          delay(SERVO_TURN_LIMIT);
          delay(snelheid);

      }
 };


void setup() {
    //bevestig de twee servos aan de arduino pinnen
  SERVO_H.attach(SERVO_1, 1000, 2000);
  SERVO_FEED.attach(SERVO_2, 1000, 2000);
  pinMode(MOTOR_U, OUTPUT);
  pinMode(MOTOR_L, OUTPUT);
  randomSeed(analogRead(EMPTY_ANALOG));
  }
  
void loop() {
  Trainingsprogrammas control;
  control.linksVoor();
  control.rechtsVoor();
  control.linksAchter();
  control.rechtsAchter();
  }
