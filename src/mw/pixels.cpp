#include "pixels.h"

void setupNeopixels(CRGB *pixels, int count, bool dither, uint8_t brightness)
{
    FastLED.addLeds<NEOPIXEL, MWPIN_NEOPIXEL>(pixels, count);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setDither(dither ? 1 : 0);
    FastLED.setBrightness(brightness);
    FastLED.show();
}

void printColor(Stream *out, CRGB *color)
{
    out->printf("{r:%d g:%d b:%d}", color->r, color->g, color->b);
}

void printPixels(Stream *out, Pixels *pixels)
{
    for (int i = 0; i < pixels->count; i++)
    {
        printColor(out, &pixels->colors[i]);
        if (i < pixels->count - 1)
        {
            out->print(",");
        }
    }
    out->println();
}
