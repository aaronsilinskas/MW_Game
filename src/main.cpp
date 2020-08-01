/* Tool 3 Hardware Test
 */
#include <Arduino.h>
#include <Adafruit_DotStar.h>
#include <mw/time.h>
#include <mw/pixels.h>

// Built-in Dot for status
Adafruit_DotStar statusDot(1, 41, 40, DOTSTAR_BGR);

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

void setStatus(uint8_t r, uint8_t g, uint8_t b)
{
    statusDot.setPixelColor(0, r, g, b);
    statusDot.show();
}

void clearStatus()
{
    setStatus(0, 0, 0);
}

void blinkStatusUntilSerialReady()
{
    bool on = true;
    while (!Serial)
    {
        if (on)
        {
            setStatus(255, 192, 0);
        }
        else
        {
            clearStatus();
        }
        delay(500);
        on = !on;
    }
    clearStatus();
}

void setup()
{
    statusDot.begin();
    statusDot.setBrightness(50);

    blinkStatusUntilSerialReady();

    Serial.begin(9600);
    Serial.println("Hardware diagnostics starting...");

    randomSeed(micros());

    setupNeopixels<NEOPIXEL_PIN>(neopixels, NEOPIXEL_COUNT, true, NEOPIXEL_BRIGHTNESS);
}

void loop()
{
    timeEllapsed(&time);

    FastLED.show();
    FastLED.delay(40);
}
