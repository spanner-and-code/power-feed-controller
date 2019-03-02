#include <Arduino.h>
#include "Display.h"

Display::Display(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{

}

/**
 * Setup the display and some default display options
 */
void Display::init()
{
  LiquidCrystal_I2C::init();
  LiquidCrystal_I2C::backlight();

  LiquidCrystal_I2C::createChar(1, _backslash);

  LiquidCrystal_I2C::setCursor(0, 0);
  LiquidCrystal_I2C::print("STS:*; ");
  LiquidCrystal_I2C::print("DIR:None");
  
  LiquidCrystal_I2C::setCursor(0, 1);
  
  LiquidCrystal_I2C::print("SPD:0; ");
  LiquidCrystal_I2C::print("PWM:0");
}

/**
 * Print the current status
 * A '*' indicates stopped and running will show an animation
 */
void Display::printStatus(uint8_t status)
{
  LiquidCrystal_I2C::setCursor(4, 0);
  if (status == STATUS_STOPPED) {
    LiquidCrystal_I2C::print("*");
  } else if (status == STATUS_RUNNING && millis() > _status_timer) {
    _status_timer = millis() + 250;
    _status_index++;
    if (_status_index >= 4) {
      _status_index = 0;
    }
    LiquidCrystal_I2C::write(_status_text[_status_index]);
  }
}

/**
 * Print the current direction
 */
void Display::printDirection(uint8_t dir)
{
  LiquidCrystal_I2C::setCursor(11, 0);
  if (dir == DIRECTION_LEFT) {
    LiquidCrystal_I2C::print("Left ");
  } else if (dir == DIRECTION_RIGHT) {
    LiquidCrystal_I2C::print("Right");
  }
}

/**
 * Print the speed option.
 * Can be 1, 2, 3 or R
 */
void Display::printSpeed(uint8_t speed)
{
  LiquidCrystal_I2C::setCursor(4, 1);
  LiquidCrystal_I2C::print((char)speed);
}

/**
 * Print the PWM
 */
void Display::printPwm(uint8_t pwm)
{
  LiquidCrystal_I2C::setCursor(11, 1);
  LiquidCrystal_I2C::print("   ");
  LiquidCrystal_I2C::setCursor(11, 1);
  LiquidCrystal_I2C::print(pwm);
}
