#include "config.h"

namespace Speedometer {

  float measureVelocity(void) {
    unsigned long firstTime, secondTime, start;
    int analogValue;
  
    // Wait for a value change in the first sensor
    analogValue = analogRead(SPEEDOMETER_LDR_FIRST);
    start = millis();
    // The signal *should* go from high to low
    while (analogValue - analogRead(SPEEDOMETER_LDR_FIRST) > SPEEDOMETER_THRESHOLD) {
      if (millis() - start > SPEEDOMETER_TIMEOUT)
        return -1;
    }
    firstTime = millis();
  
    // Wait for a change in the second sensor
    analogValue = analogRead(SPEEDOMETER_LDR_SECOND);
    start = millis();
    // The signal *should* go from high to low
    while (analogValue - analogRead(SPEEDOMETER_LDR_SECOND) > SPEEDOMETER_THRESHOLD) {
      if (millis() - start > SPEEDOMETER_TIMEOUT)
        return -1;
    }
    secondTime = millis();
  
    // Calculate the final velocity
    return SPEEDOMETER_DISTANCE / ((secondTime - firstTime) / 1000.0f);
  }

}
