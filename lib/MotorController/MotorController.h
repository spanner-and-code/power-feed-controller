#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

//#define DIRECTION_CW 1
//#define DIRECTION_CCW 2

class MotorController
{
  public:
    enum Direction {
      CW,
      CCW
    };

    virtual void setDirection(uint8_t dir) = 0;
    virtual void setPWM(uint8_t pwm) = 0;
};

#endif
