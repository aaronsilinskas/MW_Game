#ifndef __INC_MW_FLAME_H__
#define __INC_MW_FLAME_H__

#include "time.h"
#include "pixels.h"
#include "magic.h"

#ifndef MWPIN_NEOPIXEL
#define MWPIN_NEOPIXEL 5
#endif

typedef struct Flame
{
    bool lit;
    uint8_t brightness;
    MagicAmount burnedPerMs;
} Flame;

void flameBurnsMagic(Flame *flame, Magic *fuel, Time &time);
void flameBrightnessChanges(Flame *flame, Time &time);
void flameOnPixel(Flame &flame, CRGB &color, Pixels *pixels, int index);

#endif
