#ifndef RGB_ENCODER_H
#define RGB_ENCODER_H

#include <Encoder.h>
#include <Button.h>

class RGBEncoder : public Encoder
{
  public:
    RGBEncoder(uint8_t encoder_a, uint8_t encoder_b, uint8_t rgb_r, uint8_t rgb_g, uint8_t rgb_b, uint8_t btn, uint8_t btn_flags);
    void setRGB(uint8_t r, uint8_t g, uint8_t b);
    void setRGB(uint8_t rgb);
  private:
    uint8_t _rgb_pin_r;
    uint8_t _rgb_pin_g;
    uint8_t _rgb_pin_b;
};

#endif
