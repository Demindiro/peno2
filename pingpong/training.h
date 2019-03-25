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

  void init(void);

  void fire(int angle, int velocity, int count = 1, int feedDelay = TRAAG);

  void fireDirection(enum DIRECTION direction, int count = 1, int feedDelay = TRAAG);
  
  void fireRandom(int count = 1, int snelheid = TRAAG);
  
  void fireLeftRight(int aantal = 1, int snelheid = TRAAG);
}


#endif
