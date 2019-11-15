/* lamp.cpp Example sketch for a lamp
 */
#include <Arduino.h>
#include <FastLED.h>

/////////////////////////// State

typedef struct Time
{
    uint64_t currentTimeMs;
    uint64_t ellapsedMs;
} Time;

typedef enum MagicType
{
    Fire,
    Water,
    Air,
    Earth,
    Lightning
} MagicType;

typedef uint32_t MagicAmount;

typedef struct Magic
{
    MagicType type;
    MagicAmount amount;

} Magic;

typedef struct Flame
{
    bool lit;
    uint8_t brightness;
    MagicAmount burnedPerSecond;
} Flame;

typedef struct Pixels
{
    uint16_t count;
    CRGB *colors;
} Pixels;

/////////////////////////// Behaviors
// should only take structs, no primitives
// main state should be first word for easier discovery

void timeEllapsed(Time *time)
{
    uint64_t updatedTimeMs = millis();
    if (time->currentTimeMs == 0)
    {
        time->currentTimeMs = updatedTimeMs;
        time->ellapsedMs = 0;
    }
    else
    {
        time->ellapsedMs = updatedTimeMs - time->currentTimeMs;
        time->currentTimeMs = updatedTimeMs;
    }
}

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

void flameBrightnessFlickers(Flame *flame, Time *time)
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

Pixels flamePixels{
    .count = 12,
    .colors = (CRGB *)malloc(12 * sizeof(CRGB))};

void setup()
{
    Serial.begin(9600);

    randomSeed(micros());
}

void loop()
{
    timeEllapsed(&time);
    flameBurnsMagic(&flame, &fuel, &time);
    flameBrightnessFlickers(&flame, &time);

    Serial.printf("Fuel remaining: %d\n", fuel.amount);

    delay(500);
}
