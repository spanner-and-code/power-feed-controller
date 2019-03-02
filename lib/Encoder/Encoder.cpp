#include "Encoder.h"

/**
 * Setup the encoder
 */
Encoder::Encoder(uint8_t encoder_a, uint8_t encoder_b, uint8_t btn, uint8_t btn_flags) : _encoder_pin_a(encoder_a), _encoder_pin_b(encoder_b)
{
  _btn = new Button(btn, btn_flags);

  pinMode(encoder_a, INPUT_PULLUP);
  pinMode(encoder_b, INPUT_PULLUP);
}

/**
 * Has the encoder been pressed?
 */
void Encoder::onPress(encoderButtonFn fn)
{
  if (_btn->isPressed()) {
    fn();
  }
}

// http://www.hobbytronics.co.uk/arduino-tutorial6-rotary-encoder
/**
 * Is the encoder rotating?
 */
void Encoder::onRotate(encoderRotateFn fn)
{
  uint8_t encoder_A = digitalRead(_encoder_pin_a);
  uint8_t encoder_B = digitalRead(_encoder_pin_b);
  if (!encoder_A && _last) {
    fn(encoder_B ? ROTATE_CW : ROTATE_CCW);
  }
  _last = encoder_A;
}
