/* Tool 3 Hardware Test
 */
#include <Arduino.h>
#include <mw/time.h>
#include <mw/pixels.h>

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

void blinkUntilSerialReady()
{
    pinMode(LED_BUILTIN, OUTPUT);
    bool on = true;
    while (!Serial)
    {
        digitalWrite(LED_BUILTIN, on ? HIGH : LOW);
        delay(500);
        on = !on;
    }
    digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
    blinkUntilSerialReady();

    Serial.begin(9600);
    Serial.println("Hardware diagnostics starting...");

    randomSeed(micros());

    // TODO - DFPlayer
    // TODO - IMU connect
    // TODO - IR send
    // TODO - NeoPixels
    // TODO - buttons
    // TODO - potentiometer

    setupNeopixels<NEOPIXEL_PIN>(neopixels, NEOPIXEL_COUNT, true, NEOPIXEL_BRIGHTNESS);
}

void loop()
{
    timeEllapsed(&time);

    FastLED.show();
    FastLED.delay(40);
}
