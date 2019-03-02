#ifndef ENCODER_H
#define ENCODER_H

#include <Button.h>

typedef void(*encoderButtonFn)();
typedef void(*encoderRotateFn)(bool);

class Encoder
{
  public:
    enum Rotate {
      ROTATE_CW,
      ROTATE_CCW
    };

    Encoder(uint8_t encoder_a, uint8_t encoder_b, uint8_t btn, uint8_t btn_flags);
    void onPress(encoderButtonFn fn);
    void onRotate(encoderRotateFn fn);
  private:
    Button *_btn;

    uint8_t _encoder_pin_a;
    uint8_t _encoder_pin_b;

    uint8_t _last = 0;
};

#endif
