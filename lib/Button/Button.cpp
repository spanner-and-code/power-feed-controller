#include <Arduino.h>
#include "Button.h"

/**
 * Button without LED
 */
Button::Button(uint8_t btn, uint8_t flags) : Button(btn, false, flags)
{

}

/**
 * Button with LED
 */
Button::Button(uint8_t btn, uint8_t led, uint8_t flags) : _btn_pin(btn), _led_pin(led), _flags(flags)
{
  // Allow for pullup and pulldown buttons
  if (flags & PULLDOWN) {
    _pressed_logic = HIGH;
    _last_button_state = LOW;
    pinMode(btn, INPUT);
  } else if (flags & PULLUP) {
    _pressed_logic = LOW;
    _last_button_state = HIGH;
    pinMode(btn, INPUT_PULLUP);
  }

  if (led != false) {
    pinMode(led, OUTPUT);
  }
}

/**
 * Turn the LED on
 */
void Button::on()
{
  _state = BTN_ON;
  if (_led_pin != false) {
    digitalWrite(_led_pin, HIGH);
  }
}

/**
 * Turn the LED off
 */
void Button::off()
{
  _state = BTN_OFF;
  if (_led_pin != false) {
    digitalWrite(_led_pin, LOW);
  }
}

/**
 * Toggle the LED
 */
void Button::toggle()
{
  if (_state == BTN_ON && _flags & TOGGLE) {
    _state = BTN_OFF;
    off();
  } else {
    _state = BTN_ON;
    on();
  }
}

// https://www.arduino.cc/en/tutorial/debounce
/**
 * Is the button pressed?
 */
bool Button::isPressed()
{
  bool pressed = false;
  uint8_t reading = digitalRead(_btn_pin);

  if (reading != _last_button_state) {
    _last_debounce_time = millis();
  }

  if ((millis() - _last_debounce_time) > DEBOUNCE_DELAY && reading != _button_state) {
    _button_state = reading;
    if (_button_state == _pressed_logic) {
      pressed = true;
      toggle();
    }
  }

  _last_button_state = reading;

  return pressed;
}

/**
 * Return the button pin
 */
uint8_t Button::getBtnPin()
{
  return _btn_pin;
}
