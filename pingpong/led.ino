#include "led.h"
#include <SoftPWM.h>
#include "balls.h"
#include "config.h"


namespace Led {

  //__attribute__((constructor))
  void init(void) {
    pinMode(LED_PIN_RED  , OUTPUT);
    pinMode(LED_PIN_GREEN, OUTPUT);
    pinMode(LED_PIN_BLUE , OUTPUT);
  }

  void set(int r, int g, int b) {
    SoftPWMSet(LED_PIN_RED  , r);
    SoftPWMSet(LED_PIN_GREEN, map(g, 0, 255, 0, 50));
    SoftPWMSet(LED_PIN_BLUE , b);
  }

  // TODO: move this to another module
  int ballCountFeedback(void) {
    int count = Balls::count();
    Serial.println(count);
    int r = map(MAX_BALL_COUNT - count, 0, MAX_BALL_COUNT, 0, 255);
    int g = map(count, 0, MAX_BALL_COUNT, 0, 255);
    set(r, g, 0);
    return count;
  }
}
