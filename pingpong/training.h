#ifndef TRAINING_H
#define TRAINING_H

#include "config.h"

namespace Training {

  enum DIRECTION {
    LEFT_BACK   = 0b00,
    RIGHT_BACK  = 0b01,
    LEFT_FRONT  = 0b10,
    RIGHT_FRONT = 0b11,
  };

  void setFireSpeed(int servo, int velocity);

  void setServo(int servo, float angle);

  void stopMotors();

  void fire(int angle, int velocity, int count = 1, int feedDelay = VELOCITY_SLOW);

  void fireDirection(enum DIRECTION direction, int count = 1, int feedDelay = VELOCITY_SLOW);
  
  void fireRandom(int count = 1, int snelheid = VELOCITY_SLOW);
  
  void fireLeftRight(int aantal = 1, int snelheid = VELOCITY_SLOW);
}


#endif
