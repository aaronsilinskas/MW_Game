#ifndef __INC_MW_PIXELS_H__
#define __INC_MW_PIXELS_H__

#include <FastLED.h>
#include "magic.h"

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

void printColor(Stream *out, CRGB &color);
void printPixels(Stream *out, Pixels &pixels);

#endif
