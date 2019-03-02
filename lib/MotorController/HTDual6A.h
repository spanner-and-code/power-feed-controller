#ifndef HT_DUAL_6A_H
#define HT_DUAL_6A_H

#include <Arduino.h>
#include <MotorController.h>

class HTDual6A : public MotorController
{
  public:
    HTDual6A(uint8_t dir, uint8_t pwm) : _dir_pin(dir), _pwm_pin(pwm)
    {
      pinMode(_dir_pin, OUTPUT);
      pinMode(_pwm_pin, OUTPUT);

      analogWrite(_pwm_pin, 0);
    };

    void setDirection(uint8_t dir)
    {
      digitalWrite(_dir_pin, dir == CW ? LOW : HIGH);
    };
    
    void setPWM(uint8_t pwm)
    {
      analogWrite(_pwm_pin, pwm);
    };
  private:
    uint8_t _dir_pin;
    uint8_t _pwm_pin;
};

#endif
