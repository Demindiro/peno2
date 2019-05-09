/** @file */ 

#ifndef LED_H
#define LED_H


namespace Led {

  /**
   * Initialize the pins to control the LEDs
   */
  void init(void);

  /**
   * Set the colors of the RGB LED
   * 
   * @param r the value of the red color
   * @param g the value of the green color
   * @param r the value of the blue color
   */
  void set(int r, int g, int b);

  /**
   * Set the colors of the RGB LED based on the amount of balls loaded
   * 
   * @return the amount of balls
   */
  int ballCountFeedback(void);
 
}


#endif
