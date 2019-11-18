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
    MagicAmount burnedPerMs;
} Flame;

/////////////////////////// Behaviors
// should only take structs, no primitives
// main state should be first word for easier discovery

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

void flameOnPixel(Flame &flame, Pixels *pixels, int index)
{
    pixels->colors[index] = CRGB::Yellow;
    pixels->colors[index] = pixels->colors[index].nscale8(flame.brightness);
}

/////////////////////////// Entity

Time time;

Flame flame{
    .lit = true,
    .brightness = 0,
    .burnedPerMs = 1};

Magic fuel{
    .type = Fire,
    .amount = 10000};

#define NEOPIXEL_PIN 5
const uint16_t NEOPIXEL_COUNT = 12;
CRGB neopixels[NEOPIXEL_COUNT];

Pixels flamePixels{
    .count = 1,
    .colors = &neopixels[3]};

void setup()
{
    Serial.begin(9600);

    randomSeed(micros());

    setupNeopixels<NEOPIXEL_PIN>(neopixels, NEOPIXEL_COUNT, true, 32);
}

void loop()
{
    timeEllapsed(&time);
    flameBurnsMagic(&flame, &fuel, time);
    flameBrightnessChanges(&flame, time);
    flameOnPixel(flame, &flamePixels, 0);

    EVERY_N_MILLIS(750)
    {
        printMagic(&Serial, "Fuel remaining", fuel);
    }

    FastLED.show();

    FastLED.delay(20);
    //FastLED.delay(750);
}
