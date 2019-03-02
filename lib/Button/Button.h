#ifndef BTN_H
#define BTN_H

#include <Arduino.h>

#define DEBOUNCE_DELAY 50

class Button
{
  public:
    enum Flags {
      PULLDOWN = 1 << 0,
      PULLUP = 1 << 1,
      TOGGLE = 1 << 2
    };
    enum State {
      BTN_ON,
      BTN_OFF
    };

    Button(uint8_t btn, uint8_t flags);
    Button(uint8_t btn, uint8_t led, uint8_t flags);
    void on();
    void off();
    void toggle();
    bool isPressed();

    uint8_t getBtnPin();
  private:

    uint8_t _btn_pin;
    uint8_t _led_pin;
    uint8_t _flags;
    uint8_t _pressed_logic;

    State _state = BTN_OFF;

    uint8_t _button_state;
    uint8_t _last_button_state;
    unsigned long _last_debounce_time = 0;
};

#endif
