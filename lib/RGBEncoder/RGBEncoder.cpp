#include "RGBEncoder.h"

/**
 * Setup the RGB encoder
 * Need input pulldown for the encoder button
 */
RGBEncoder::RGBEncoder(uint8_t encoder_a, uint8_t encoder_b, uint8_t rgb_r, uint8_t rgb_g, uint8_t rgb_b, uint8_t btn, uint8_t btn_flags) : Encoder(encoder_a, encoder_b, btn, btn_flags)
{
  _rgb_pin_r = rgb_r;
  _rgb_pin_g = rgb_g;
  _rgb_pin_b = rgb_b;

  pinMode(rgb_r, OUTPUT);
  pinMode(rgb_g, OUTPUT);
  pinMode(rgb_b, OUTPUT);

  setRGB(B111);
}

/**
 * Update the RGB LED
 */
void RGBEncoder::setRGB(uint8_t r, uint8_t g, uint8_t b)
{
  digitalWrite(_rgb_pin_r, r);
  digitalWrite(_rgb_pin_g, g);
  digitalWrite(_rgb_pin_b, b);
}

void RGBEncoder::setRGB(uint8_t rgb)
{
  setRGB(rgb & B001, rgb & B010, rgb & B100);
}
