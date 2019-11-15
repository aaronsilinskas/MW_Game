/* lamp.cpp Example sketch for a lamp
 */
#include <Arduino.h>
#include <mw/time.h>
#include <mw/magic.h>
#include <mw/pixels.h>

/////////////////////////// State

typedef struct Flame
{
    bool lit;
    uint8_t brightness;
    MagicAmount burnedPerSecond;
} Flame;

/////////////////////////// Behaviors
// should only take structs, no primitives
// main state should be first word for easier discovery

void flameBurnsMagic(Flame *flame, Magic *fuel, Time *time)
{
    if (!flame->lit)
    {
        return;
    }
    uint64_t fuelBurned = flame->burnedPerSecond * time->ellapsedMs / 1000;
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

void flameBrightnessChanges(Flame *flame, Time *time)
{
    if (flame->lit)
    {
        if (flame->brightness < 255)
        {
            uint32_t brighten = 255 * time->ellapsedMs / 2000;
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
            flame->brightness -= random(128);
        }
    }
    else if (flame->brightness > 0)
    {
        uint32_t dim = 255 * time->ellapsedMs / 5000; // go out in 5 seconds
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

void flameOnPixels(Flame *flame, Pixels *pixels, Time *time)
{
    printPixels(&Serial, pixels);
}

/////////////////////////// Entity

Time time;

Flame flame{
    .lit = true,
    .brightness = 0,
    .burnedPerSecond = 5};

Magic fuel{
    .type = Fire,
    .amount = 1000};

#define NEOPIXEL_PIN 5
#define NEOPIXEL_COUNT 3
CRGB neopixels[NEOPIXEL_COUNT]; // = {CRGB::Red, CRGB::Green, CRGB::Blue};

Pixels flamePixels{
    .count = NEOPIXEL_COUNT,
    .colors = neopixels};

void setup()
{
    Serial.begin(9600);

    randomSeed(micros());

    setupNeopixels<NEOPIXEL_PIN>(neopixels, NEOPIXEL_COUNT, true, 32);
}

void loop()
{
    timeEllapsed(&time);
    flameBurnsMagic(&flame, &fuel, &time);
    flameBrightnessChanges(&flame, &time);
    flameOnPixels(&flame, &flamePixels, &time);

    Serial.printf("Fuel remaining: %d\n", fuel.amount);

    delay(750);
}
