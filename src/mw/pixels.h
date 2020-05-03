#ifndef __INC_MW_PIXELS_H__
#define __INC_MW_PIXELS_H__

#include <FastLED.h>

typedef struct Pixels
{
    uint16_t count;
    CRGB *colors;
} Pixels;

template <uint8_t DATA_PIN>
void setupNeopixels(CRGB *pixels, int count, bool dither, uint8_t brightness)
{
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(pixels, count);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setDither(dither ? 1 : 0);
    FastLED.setBrightness(brightness);
    FastLED.show();
}

typedef struct BasicAnimation
{
    BasicAnimation(Pixels *pixels, uint8_t minIncrement, uint8_t maxIncrement) : pixels(pixels), minIncrement(minIncrement), maxIncrement(maxIncrement) {}
    Pixels *pixels;
    uint8_t minIncrement;
    uint8_t maxIncrement;
    uint8_t *indexes = NULL;
} BasicAnimation;

void basicAnimation(const TProgmemRGBPalette16 *palette, BasicAnimation *animation);

void printColor(Stream *out, CRGB &color);
void printPixels(Stream *out, Pixels &pixels);

#endif
