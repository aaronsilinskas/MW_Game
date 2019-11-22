/* flame.cpp Example sketch for a flame
 */
#include <Arduino.h>
#include <mw/time.h>
#include <mw/magic.h>
#include <mw/pixels.h>
#include <mw/flame.h>

Time time;

Flame flame{
    .lit = true,
    .brightness = 0,
    .burnedPerMs = 1};

Magic fuel{
    .type = Lightning,
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
    CRGB flameColor = colorFromMagic(fuel);
    flameOnPixel(flame, flameColor, &flamePixels, 0);

    EVERY_N_MILLIS(750)
    {
        printMagic(&Serial, "Fuel remaining", fuel);
    }

    FastLED.show();

    FastLED.delay(20);
    //FastLED.delay(750);
}
