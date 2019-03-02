#ifndef BTN_GROUP_H
#define BTN_GROUP_H

#include <Button.h>

typedef void(*buttonFn)(uint8_t);

class ButtonGroup
{
  public:
    ButtonGroup(uint8_t arg_count, ...);
    void off(int8_t ignore = -1);
    void onPress(buttonFn fn);
  private:
    Button** _buttons;
    uint8_t _count;
};

#endif
