/* Tool 3 prototype
 */
#include <Arduino.h>
#include <mw/time.h>
#include <mw/pixels.h>
#include <mw/magic.h>

// General
Time time;

// Buttons
#define PIN_BUTTON_FIRE A3
#define PIN_BUTTON_WATER A4
#define PIN_BUTTON_LIGHTING A5

// LEDs
#define NEOPIXEL_PIN 5
const uint16_t NEOPIXEL_COUNT = 12;
CRGB neopixels[NEOPIXEL_COUNT];

Pixels pixels{
    .count = 3,
    .colors = &neopixels[0]};

MagicType selectedMagic;
MagicType castType;
uint8_t magicSteps;

#define ACTION_DELAY 750
uint64_t nextActionMs;

void setupButtons()
{
    pinMode(PIN_BUTTON_FIRE, INPUT_PULLUP);
    pinMode(PIN_BUTTON_WATER, INPUT_PULLUP);
    pinMode(PIN_BUTTON_LIGHTING, INPUT_PULLUP);
}

void setupMagic()
{
    magicSteps = 0;
    nextActionMs = 0;
}

void setup()
{
    Serial.begin(9600);

    randomSeed(micros());

    setupButtons();
    setupNeopixels<NEOPIXEL_PIN>(neopixels, NEOPIXEL_COUNT, true, 32);
    setupMagic();
}

bool buttonPressed(uint32_t pin)
{
    return digitalRead(pin) == 0;
}

void updatePixelsForMagic(uint8_t steps, CRGB color)
{
    if (steps == 0)
    {
        for (int i = 0; i < pixels.count; i++)
        {
            pixels.colors[i] = color;
        }
        return;
    }
    else if (steps == 1)
    {
        pixels.colors[0] = color;
    }
    else if (steps == 2)
    {
        pixels.colors[0] = color;
        pixels.colors[1] = color;
    }
    else
    {
        pixels.colors[2] = color;
    }
}

void addMagic(MagicType magic)
{
    if (magicSteps == 0)
    {
        selectedMagic = magic;
        updatePixelsForMagic(1, colorFromMagic(selectedMagic));
        magicSteps++;
    }
    else if (magicSteps == 1)
    {
        Serial.print(magicTypeName(selectedMagic));
        Serial.print(" + ");
        Serial.print(magicTypeName(magic));
        Serial.print(" = ");
        Serial.println(magicTypeName(combineMagic(selectedMagic, magic)));

        selectedMagic = combineMagic(selectedMagic, magic);
        if (selectedMagic == None)
        {
            updatePixelsForMagic(0, CRGB::Black);
            magicSteps = 0;
        }
        else
        {
            updatePixelsForMagic(2, colorFromMagic(selectedMagic));
            magicSteps++;
        }
    }
    else
    {
        castType = magic;
        updatePixelsForMagic(3, colorFromMagic(castType));
        magicSteps++;
    }
}

bool spellComplete()
{
    return magicSteps >= 3;
}

void castSpell()
{
    // TODO cast the spell based on selectedMagic and castType

    magicSteps = 0;
}

void loop()
{
    timeEllapsed(&time);

    if (nextActionMs < time.currentTimeMs)
    {
        if (buttonPressed(PIN_BUTTON_FIRE))
        {
            addMagic(Fire);
            nextActionMs = time.currentTimeMs + ACTION_DELAY;
        }
        else if (buttonPressed(PIN_BUTTON_WATER))
        {
            addMagic(Water);
            nextActionMs = time.currentTimeMs + ACTION_DELAY;
        }
        else if (buttonPressed(PIN_BUTTON_LIGHTING))
        {
            addMagic(Lightning);
            nextActionMs = time.currentTimeMs + ACTION_DELAY;
        }
    }
    if (spellComplete())
    {
        castSpell();
    }

    FastLED.show();
    FastLED.delay(20);
}
