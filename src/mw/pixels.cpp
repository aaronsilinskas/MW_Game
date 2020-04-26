#include "pixels.h"

CRGB colorFromMagic(MagicType magicType)
{
    switch (magicType)
    {
    case None:
        return CRGB::Black;
    case Fire:
        return CRGB::Red;
    case Water:
        return CRGB::Blue;
    case Lightning:
        return CRGB::Yellow;
    case Air:
        return CRGB::Purple;
    case Earth:
        return CRGB::Green;
    case Matter:
        return CRGB::OrangeRed;
    case Light:
        return CRGB::White;
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
