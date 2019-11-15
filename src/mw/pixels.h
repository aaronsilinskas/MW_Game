#ifndef __INC_MW_PIXELS_H__
#define __INC_MW_PIXELS_H__

#include <FastLED.h>

#ifndef MWPIN_NEOPIXEL
#define MWPIN_NEOPIXEL 5
#endif

typedef struct Pixels
{
    uint16_t count;
    CRGB *colors;
} Pixels;

void setupNeopixels(CRGB *pixels, int count, bool dither, uint8_t brightness);

void printColor(Stream *out, CRGB *color);
void printPixels(Stream *out, Pixels *pixels);

#endif
