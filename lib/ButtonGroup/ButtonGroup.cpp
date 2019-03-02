#include <stdarg.h>
#include "ButtonGroup.h"

/**
 * Setup an array of `Button`s
 */
ButtonGroup::ButtonGroup(uint8_t arg_count, ...)
{
  va_list args;
  va_start(args, arg_count);

  _buttons = new Button*[arg_count];
  _count = arg_count;

  for (uint8_t i = 0; i < arg_count; i++) {
    _buttons[i] = va_arg(args, Button *);
  }
  va_end(args);
}

/**
 * Turn group button LEDs off
 */
void ButtonGroup::off(int8_t ignore)
{
  for (uint8_t i = 0; i < _count; i++) {
    if (i != ignore) {
      _buttons[i]->off();
    }
  }
}

/**
 * Has a button in the group been pressed?
 */
void ButtonGroup::onPress(buttonFn fn)
{
  for (uint8_t i = 0; i < _count; i++) {
    if (_buttons[i]->isPressed()) {
      off(i);
      fn(_buttons[i]->getBtnPin());
    }
  }
}
