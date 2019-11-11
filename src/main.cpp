/* lamp.cpp Example sketch for a lamp
 *
 * Entity - Lamp

Components

- IR
- Events
- Lights (FastLED dep)
  - NeoPixels
- Sound
  - Piezo
- Input
  - Piezo
- Flame
  - Lights
  - Sound

Behaviors

- FlameOn(Flame)
- FlameOff(Flame)
- FlameUpdate(Flame)
-

 */
#include <Arduino.h>

/////////////////////////// State

typedef struct Time
{
    uint64_t currentTimeMs;
    uint64_t ellapsedMs;
} Time;

void setupTime(Time *time)
{
    time->currentTimeMs = millis();
    time->ellapsedMs = 0;
}

typedef enum MagicType
{
    Fire,
    Water,
    Air,
    Earth,
    Lightning
} MagicType;

typedef struct Magic
{
    MagicType type;
    uint32_t amount;

} Magic;

typedef struct Lamp
{
    bool lit;
    uint32_t magicPerSecond;
} Lamp;

/////////////////////////// Behaviors
// should only take structs, no primitives
// main state should be first word for easier discovery

void timeEllapsed(Time *time)
{
    uint64_t updatedTimeMs = millis();
    time->ellapsedMs = updatedTimeMs - time->currentTimeMs;
    time->currentTimeMs = updatedTimeMs;
}

void lampBurnsMagic(Lamp *lamp, Magic *fuel, Time *time)
{
    if (!lamp->lit)
    {
        return;
    }
    uint64_t fuelBurned = lamp->magicPerSecond * time->ellapsedMs / 1000;
    fuel->amount -= fuelBurned;
}

/////////////////////////// Entity

Time time;

Lamp lamp{
    .lit = true,
    .magicPerSecond = 5};

Magic fuel{
    .type = Fire,
    .amount = 1000};

void setup()
{
    Serial.begin(9600);

    // TODO manually wire up behaviors with structs and manually execute in order?
    setupTime(&time);
}

void loop()
{
    timeEllapsed(&time);
    lampBurnsMagic(&lamp, &fuel, &time);

    Serial.printf("Fuel remaining: %d\n", fuel.amount);

    delay(500);
}
