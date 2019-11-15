#ifndef __INC_MW_PIXELS_H__
#define __INC_MW_PIXELS_H__

#include <FastLED.h>

typedef struct Pixels
{
    uint16_t count;
    CRGB *colors;
} Pixels;

void printColor(Stream *out, CRGB *color);
void printPixels(Stream *out, Pixels *pixels);

#endif
