/** @file */ 

#include "config.h"

namespace Speedometer {

  static unsigned long waitForChange(int pin, int threshold) {
    int analogValue = analogRead(pin);

    DEBUG(F("Value:      "));
    DEBUGLN(analogValue);

    unsigned long start = micros();

    // The signal *should* go from high to low
    while (analogValue - analogRead(pin) < threshold) {

      if (micros() - start > SPEEDOMETER_TIMEOUT) {
        DEBUGLN(F("Timeout"));
        return -1;
      }
    }

    DEBUG(F("Last value: "));
    DEBUGLN(analogRead(pin));
    
    return micros();
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

    firstTime  = waitForChange(SPEEDOMETER_LDR_FIRST , SPEEDOMETER_THRESHOLD_FIRST);
    if (firstTime == -1)
      return -1;

    DEBUG(F("First  sensor time: "));
    DEBUGLN(firstTime);

    secondTime = waitForChange(SPEEDOMETER_LDR_SECOND, SPEEDOMETER_THRESHOLD_SECOND);  
    if (secondTime == -1)
      return -1;

    DEBUG(F("Second sensor time: "));
    DEBUGLN(secondTime);
  
    // Calculate the final velocity
    return SPEEDOMETER_DISTANCE / ((secondTime - firstTime) / 1000000.0);
  }

}
