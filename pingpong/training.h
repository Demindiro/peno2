/** @file */ 

#ifndef TRAINING_H
#define TRAINING_H

#include "config.h"

namespace Training {

  /**
   * An enum to indicate the direction the robot should fire to
   * 
   * This is especially useful in conjuction with random(min, max)
   */
  enum DIRECTION {
    LEFT_BACK   = 0b00,
    LEFT_FRONT  = 0b01,
    RIGHT_BACK  = 0b10,
    RIGHT_FRONT = 0b11,
  };

  /**
   * Set the speed of one of the motors
   * 
   * @param motor is the pin of the motor of which the velocity should be set
   * @param velocity a value f-ranging from 0 to 255 indicating the relative
   *   speed at which the motor should turn
   */
  void setFireSpeed(int motor, int velocity);

  /**
   * Set the angle of one of the servos
   * 
   * @param servo is the pin of the servo of which the angle should be set
   * @param angle is the angle the servo will be set to
   */
  void setServo(int servo, float angle);

  /**
   * Stop the motors
   */
  void stopMotors(void);

  /**
   * Initialize the motor and servo pins
   */
  void init(void);

  /**
   * Feed a single ball to fire
   */
  void feed(void);

  /**
   * Fire a ball
   * 
   * @param angle is the angle at which the ball should be fired
   * @param velocity is the relative velocity the ball should be fired at
   * @param count is the amount of balls that should be fired
   * @param feedDelay is the amount of time in milliseconds between each reload
   */
  void fire(int angle, int velocityLeft, int velocityRight, int count = 1, int feedDelay = VELOCITY_SLOW);

  /**
   * Fire a ball in a predefined direction
   * 
   * @param direction is the location on the field where the ball should land
   * @param count is the amount of balls that should be fired
   * @param feedDelay is the amount of time in milliseconds between each reload
   */
  void fireDirection(enum DIRECTION direction, int count = 1, int feedDelay = VELOCITY_SLOW, int spin = 0);

  /**
   * Fire a ball in a random direction
   * 
   * @param count is the amount of balls that should be fired
   * @param feedDelay is the amount of time in milliseconds between each reload
   */
  void fireRandom(int count = 1, int snelheid = VELOCITY_SLOW);
  
  /**
   * Alternate between the left and right direction but fire randomly further
   * or closer by.
   * 
   * @param count is the amount of balls that should be fired
   * @param feedDelay is the amount of time in milliseconds between each reload
   */
  void fireLeftRight(int count = 2, int velocity = VELOCITY_SLOW);
}


#endif
