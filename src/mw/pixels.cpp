#include "pixels.h"

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
