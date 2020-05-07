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

BasicAnimation magicAnimation{
    .pixels = &pixels,
    .minIncrement = 0,
    .maxIncrement = 4};

enum GameState
{
    WaitingForPlayer,
    ButtonPressed,
    CorrectButton,
    IncorrectButton,
    WaitingForRelease,
    Unlocked
};
GameState gameState;

MagicType selectedMagic;
MagicType castType;
uint8_t magicSteps;

#define ACTION_DELAY 500
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

void addMagic(MagicType magic)
{
    if (magicSteps == 0)
    {
        selectedMagic = magic;
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
            magicSteps = 0;
        }
        else
        {
            magicSteps++;
        }
    }
    else
    {
        castType = magic;
        selectedMagic = None;
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
    // TODO remove - for testing
    const TProgmemRGBPalette16 *palette = paletteForMagic(selectedMagic);
    basicAnimation(palette, &magicAnimation);

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
