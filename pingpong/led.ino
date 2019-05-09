/** @file */ 

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
    set(0, 0, 0);
  }

  void set(int r, int g, int b) {
    SoftPWMSet(LED_PIN_RED  , 255 - r);
    SoftPWMSet(LED_PIN_GREEN, 255 - map(g, 0, 255, 0, 50)); // too bright  without scaling
    SoftPWMSet(LED_PIN_BLUE , 255 - b);
  }

  // TODO: move this to another module
  int ballCountFeedback(void) {
    int count = Balls::count();
    DEBUG(F("Balls available: "));
    DEBUGLN(count);
    int r = map(MAX_BALL_COUNT - count, 0, MAX_BALL_COUNT, 0, 255);
    int g = map(count, 0, MAX_BALL_COUNT, 0, 255);
    set(r, g, 0);
    return count;
  }
}
