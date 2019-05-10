/** @file */ 

__attribute__((constructor))
static void _setup(void) {
  pinMode(BALLS_TRIG_PIN, OUTPUT);
  pinMode(BALLS_ECHO_PIN, INPUT);
}

namespace Balls {
  int count(void){
    digitalWrite(BALLS_TRIG_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(BALLS_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(BALLS_TRIG_PIN, LOW);
  
    pinMode(BALLS_ECHO_PIN, INPUT);
    long duration = pulseIn(BALLS_ECHO_PIN, HIGH);
  
    int balls = MAX_BALL_COUNT - duration * BALLS_CALIBRATION_FACTOR;
    return balls > 0 ? balls : 0;
  }
}
