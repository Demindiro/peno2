#include "config.h"

namespace Speedometer {

  static unsigned long waitForChange(int pin) {
    int analogValue = analogRead(pin);
#ifndef NDEBUG
    Serial.print("Value:      ");
    Serial.println(analogValue);
#endif

    unsigned long start = millis();

    // The signal *should* go from high to low
    while (analogValue - analogRead(pin) < SPEEDOMETER_THRESHOLD) {

#ifndef NDEBUG
    Serial.print("New value:  ");
    Serial.println(analogRead(pin));
#endif

      if (millis() - start > SPEEDOMETER_TIMEOUT) {
#ifndef NDEBUG
        Serial.println("Timeout");
#endif
        return -1;
      }
    }

#ifndef NDEBUG
    Serial.print("Last value: ");
    Serial.println(analogRead(pin));
#endif
    
    return millis();
  }


  /******************\
   *                *
   *     >(o )_     *
   *      (___/     *
   *                *
   *  The  magical  *
   *    duckling    *
   *   gives  you   *
   * its  blessings *
   *                *
  \******************/


  float measureVelocity(void) {
    unsigned long firstTime, secondTime, start;
    int analogValue;

    firstTime  = waitForChange(SPEEDOMETER_LDR_FIRST);
    if (firstTime == -1)
      return -1;

#ifndef NDEBUG
    Serial.print("First  sensor time: ");
    Serial.println(firstTime);
#endif

    secondTime = waitForChange(SPEEDOMETER_LDR_SECOND);  
    if (secondTime == -1)
      return -1;

#ifndef NDEBUG
    Serial.print("Second sensor time: ");
    Serial.println(secondTime);
#endif
  
    // Calculate the final velocity
    return SPEEDOMETER_DISTANCE / ((secondTime - firstTime) / 1000.0f);
  }

}
