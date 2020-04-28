/* Tool 3 prototype
 */
#include <Arduino.h>
#include <mw/time.h>
#include <mw/pixels.h>
#include <mw/magic.h>
#include <mw/pixels_magic.h>

// Buttons //
#define PIN_BUTTON_FIRE A3
#define PIN_BUTTON_WATER A4
#define PIN_BUTTON_LIGHTING A5

// LEDs //
#define NEOPIXEL_PIN 5
#define NEOPIXEL_BRIGHTNESS 32
const uint16_t NEOPIXEL_COUNT = 12;
CRGB neopixels[NEOPIXEL_COUNT];

Pixels pixels{
    .count = NEOPIXEL_COUNT,
    .colors = &neopixels[0]};

// Game State //
Time time;

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
    setupNeopixels<NEOPIXEL_PIN>(neopixels, NEOPIXEL_COUNT, true, NEOPIXEL_BRIGHTNESS);
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
        updatePixelsForMagic(1, colorForMagic(selectedMagic));
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
            updatePixelsForMagic(2, colorForMagic(selectedMagic));
            magicSteps++;
        }
    }
    else
    {
        castType = magic;
        updatePixelsForMagic(3, colorForMagic(castType));
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

void testPalette(MagicType magicType)
{
    static bool initialized = false;
    static uint8_t colorIndex[NEOPIXEL_COUNT];
    if (!initialized)
    {
        initialized = true;
        for (int i = 0; i < NEOPIXEL_COUNT; i++)
        {
            colorIndex[i] += random(256);
        }
    }
    for (int i = 3; i < NEOPIXEL_COUNT; i++)
    {
        colorIndex[i] += random(4);
        pixels.colors[i] = ColorFromPalette(*paletteForMagic(magicType), colorIndex[i], 255, LINEARBLEND);
    }
}

void loop()
{
    // TODO remove - for testing
    testPalette(Fire);

    timeEllapsed(&time);

    // if ready for input, read buttons
    // update state (magic charge, decay, casting)
    // update pixel animations
    // update sounds
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
    FastLED.delay(40);
}
