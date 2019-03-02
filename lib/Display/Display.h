#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal_I2C.h>

class Display : public LiquidCrystal_I2C
{
  public:
    enum Status {
      STATUS_STOPPED,
      STATUS_RUNNING
    };
    enum Direction {
      DIRECTION_LEFT,
      DIRECTION_RIGHT
    };
    enum Speed {
      SPEED_1 = '1',
      SPEED_2 = '2',
      SPEED_3 = '3',
      SPEED_ROTARY = 'R'
    };

    Display(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void init();
    void printStatus(uint8_t status);
    void printDirection(uint8_t dir);
    void printSpeed(uint8_t speed);
    void printPwm(uint8_t pwm);
  private:
    // https://mattgadient.com/2018/01/08/arudino-workaround-backslash-shows-on-liquidcrystal-as-the-yen-symbol/
    uint8_t _backslash[8] = {
      0b00000,
      0b10000,
      0b01000,
      0b00100,
      0b00010,
      0b00001,
      0b00000,
      0b00000
    };

    unsigned long _status_timer = 0;
    const uint8_t _status_text[5] = { 1, '|', '/', '-' };
    uint8_t _status_index = 0;
};

#endif
