/* Tool 3 Hardware Test
 */
#include <Arduino.h>
#include <Wire.h>
#include <mw/time.h>
#include <mw/pixels.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <DFRobotDFPlayerMini.h>

// DF Player Mini
DFRobotDFPlayerMini dfPlayerMini;
#define PIN_SOUND_PLAYING 10

// IMU
#define LIS3DH_CS 9
#define CLICKTHRESHHOLD 60
Adafruit_LIS3DH lis3dh = Adafruit_LIS3DH();

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

void setupSuccess(const String message)
{
    Serial.print(F("Ready: "));
    Serial.println(message);
}

void setupFailed(const String message)
{
    Serial.print(F("Setup failed: "));
    Serial.println(message);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Halting.");
    while (1)
        ;
}

void setupDFPlayerMini()
{
    pinMode(PIN_SOUND_PLAYING, INPUT_PULLUP);
    Serial1.begin(9600);
    delay(100);
    if (!dfPlayerMini.begin(Serial1))
    {
        setupFailed(F("DFPlayer Mini not found. Please recheck the connection and/or insert the SD card!"));
    }
    else
    {
        pinMode(PIN_SOUND_PLAYING, INPUT_PULLUP);
        dfPlayerMini.volume(10);
        setupSuccess(F("DFPlayer Mini"));
    }
}

void setupMotionSensor()
{
    if (!lis3dh.begin(0x18))
    {
        setupFailed(F("LIS3DH not found."));
    }
    lis3dh.setRange(LIS3DH_RANGE_2_G);
    lis3dh.setClick(2, CLICKTHRESHHOLD);
    delay(100);
    setupSuccess(F("LIS3DH"));
}

void setupNeopixels()
{
    setupNeopixels<NEOPIXEL_PIN>(neopixels, NEOPIXEL_COUNT, true, NEOPIXEL_BRIGHTNESS);
    setupSuccess(F("Neopixels"));
}

void setup()
{
    blinkUntilSerialReady();

    Serial.begin(9600);
    Serial.println("Hardware diagnostics starting...");

    randomSeed(micros());
    setupDFPlayerMini();
    setupMotionSensor();
    setupNeopixels();

    // TODO - IR send
    // TODO - buttons
    // TODO - potentiometer
    // TODO - piezo (optional)
    // TODO - verify sound and neopixels at same time


}

void loop()
{
    timeEllapsed(&time);

    FastLED.show();
    FastLED.delay(40);
}
