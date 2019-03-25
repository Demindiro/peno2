#include <Servo.h>

Servo SERVO_H;

void setup() {
  // put your setup code here, to run once:
SERVO_H.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:
SERVO_H.writeMicroseconds(1350);
delay(5000);

//
//SERVO_H.writeMicroseconds(2300);
//delay(5000);

}
