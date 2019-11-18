#include "pixels.h"

CRGB colorFromMagic(Magic &magic)
{
    switch (magic.type)
    {
    case Fire:
        return CRGB::Red;
    case Water:
        return CRGB::Blue;
    case Air:
        return CRGB::White;
    case Earth:
        return CRGB::Green;
    case Lightning:
        return CRGB::Yellow;
    }
    return CRGB::Black;
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
