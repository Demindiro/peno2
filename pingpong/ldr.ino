int ldr1=0;
int ldr2=0;
float dist= 1.0;
float speed;

unsigned long timer1;
unsigned long timer2;
float timer3;


float speedometer()
{
  ldr1= analogRead(A4);
  ldr2= analogRead(A5);
  if (ldr1 > 100){
    timer1=millis();
  }
  if ((ldr2 > 100) && (timer1 != 0)){
  	timer2=millis(); 
  }
  if ((timer1 != 0) && (timer2 !=0)){
  	timer3=((timer2-timer1)*0.001);
    speed=(dist/timer3);
    timer1=0.0;
    timer2=0.0;
  }
  return speed;
}


