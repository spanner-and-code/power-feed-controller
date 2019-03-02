#ifndef POLOLU_G2_H
#define POLOLU_G2_H

#include <Arduino.h>
#include <MotorController.h>

class PololuG2 : public MotorController
{
  public:
    PololuG2(uint8_t dir, uint8_t pwm, uint8_t slp) : _dir_pin(dir), _pwm_pin(pwm), _slp_pin(slp)
    {
      pinMode(_dir_pin, OUTPUT);
      pinMode(_pwm_pin, OUTPUT);
      pinMode(_slp_pin, OUTPUT);
    };

    void setDirection(uint8_t dir)
    {
      digitalWrite(_dir_pin, dir == CW ? LOW : HIGH);
    };

    void setPWM(uint8_t pwm)
    {
      if (pwm == 0) {
        setSleep(true);
      } else if (pwm > 0) {
        setSleep(false);
      }
  
      analogWrite(_pwm_pin, pwm);
    };
    
    void setSleep(bool state)
    {
      digitalWrite(_slp_pin, state ? LOW : HIGH);
    };
  private:
    uint8_t _dir_pin;
    uint8_t _pwm_pin;
    uint8_t _slp_pin;
};

#endif
