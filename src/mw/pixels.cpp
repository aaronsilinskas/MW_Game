#include "pixels.h"

void basicAnimation(const TProgmemRGBPalette16 *palette, BasicAnimation *animation)
{
    Pixels *pixels = animation->pixels;
    uint16_t pixelCount = pixels->count;
    if (animation->indexes == NULL)
    {
        animation->indexes = (uint8_t *)malloc(pixelCount);
        for (int i = 0; i < pixelCount; i++)
        {
            animation->indexes[i] = random(256);
        }
    }

    uint8_t incRange = animation->maxIncrement - animation->minIncrement;
    for (int i = 0; i < pixelCount; i++)
    {
        animation->indexes[i] += animation->minIncrement + random(incRange);
        pixels->colors[i] = ColorFromPalette(*palette, animation->indexes[i], 255, LINEARBLEND);
    }
}

void printColor(Stream *out, CRGB &color)
{
    out->printf("{r:%d g:%d b:%d}", color.r, color.g, color.b);
}

void printPixels(Stream *out, Pixels &pixels)
{
    for (int i = 0; i < pixels.count; i++)
    {
        printColor(out, pixels.colors[i]);
        if (i < pixels.count - 1)
        {
            out->print(",");
        }
    }
    out->println();
}
