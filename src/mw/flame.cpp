#include "flame.h"

void flameBurnsMagic(Flame *flame, Magic *fuel, Time &time)
{
    if (!flame->lit)
    {
        return;
    }
    uint64_t fuelBurned = flame->burnedPerMs * time.ellapsedMs;
    if (fuel->amount > fuelBurned)
    {
        fuel->amount -= fuelBurned;
    }
    else
    {
        fuel->amount = 0;
        flame->lit = false;
    }
}

void flameBrightnessChanges(Flame *flame, Time &time)
{
    if (flame->lit)
    {
        if (flame->brightness < 255)
        {
            uint32_t brighten = 255 * time.ellapsedMs / 1000;
            if (flame->brightness + brighten < 255)
            {
                flame->brightness += brighten;
            }
            else
            {
                flame->brightness = 255;
            }
        }
        else
        {
            flame->brightness -= random(255);
        }
    }
    else if (flame->brightness > 0)
    {
        uint32_t dim = 255 * time.ellapsedMs / 5000; // go out in 5 seconds
        if (flame->brightness > dim)
        {
            flame->brightness -= dim;
        }
        else
        {
            flame->brightness = 0;
        }
    }
}

void flameOnPixel(Flame &flame, CRGB &color, Pixels *pixels, int index)
{
    pixels->colors[index] = color;
    pixels->colors[index] = pixels->colors[index].nscale8(flame.brightness);
}
