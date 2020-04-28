#include "pixels_magic.h"

CRGB colorForMagic(MagicType magicType)
{
    switch (magicType)
    {
    case None:
        return CRGB::Black;
    case Fire:
        return CRGB::Red;
    case Water:
        return CRGB::Blue;
    case Lightning:
        return CRGB::Yellow;
    case Air:
        return CRGB::Purple;
    case Earth:
        return CRGB::Green;
    case Matter:
        return CRGB::OrangeRed;
    case Light:
        return CRGB::White;
    }
    return CRGB::Black;
}

const TProgmemRGBPalette16 *paletteForMagic(MagicType magicType)
{
    switch (magicType)
    {
    case None:
        return &NoneColors_p;
    case Fire:
        return &FireColors_p;
    case Water:
        return &WaterColors_p;
    case Lightning:
        return &LightningColors_p;
    case Air:
        return &AirColors_p;
    case Earth:
        return &EarthColors_p;
    case Matter:
        return &MatterColors_p;
    case Light:
        return &LightColors_p;
    }
    return &NoneColors_p;
}

// Magic color palettes
extern const TProgmemRGBPalette16 NoneColors_p FL_PROGMEM = {
    CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
    CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
    CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
    CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black};
extern const TProgmemRGBPalette16 FireColors_p FL_PROGMEM = {
    CRGB::Red, CRGB::OrangeRed, CRGB::Red, CRGB::OrangeRed,
    CRGB::Yellow, CRGB::DarkRed, CRGB::Red, CRGB::OrangeRed,
    CRGB::Black, CRGB::Yellow, CRGB::Black, CRGB::Yellow,
    CRGB::OrangeRed, CRGB::DarkOrange, CRGB::Red, CRGB::Black};
extern const TProgmemRGBPalette16 WaterColors_p FL_PROGMEM = {
    CRGB::Blue, CRGB::LightSeaGreen, CRGB::MediumBlue, CRGB::DarkBlue,
    CRGB::Blue, CRGB::DarkBlue, CRGB::MediumBlue, CRGB::LightSeaGreen,
    CRGB::Cyan, CRGB::Blue, CRGB::DarkCyan, CRGB::DarkBlue,
    CRGB::Blue, CRGB::LightSeaGreen, CRGB::Cyan, CRGB::DarkCyan};
extern const TProgmemRGBPalette16 LightningColors_p FL_PROGMEM = {
    CRGB::Yellow, CRGB::Black, CRGB::Black, CRGB::Black,
    CRGB::White, CRGB::Black, CRGB::Yellow, CRGB::Black,
    CRGB::Black, CRGB::White, CRGB::Yellow, CRGB::Black,
    CRGB::Black, CRGB::Black, CRGB::Yellow, CRGB::Black};
extern const TProgmemRGBPalette16 AirColors_p FL_PROGMEM = {
    CRGB::Purple, CRGB::DarkMagenta, CRGB::Maroon, CRGB::White,
    CRGB::Purple, CRGB::DarkMagenta, CRGB::Maroon, CRGB::White,
    CRGB::Purple, CRGB::DarkMagenta, CRGB::Maroon, CRGB::White,
    CRGB::Purple, CRGB::DarkMagenta, CRGB::Maroon, CRGB::White};
extern const TProgmemRGBPalette16 EarthColors_p FL_PROGMEM = {
    CRGB::Green, CRGB::SaddleBrown, CRGB::DarkGreen, CRGB::DarkOrange,
    CRGB::Green, CRGB::DarkKhaki, CRGB::DarkGreen, CRGB::DarkOrange,
    CRGB::Green, CRGB::SaddleBrown, CRGB::DarkGreen, CRGB::DarkOrange,
    CRGB::Green, CRGB::DarkKhaki, CRGB::DarkGreen, CRGB::DarkOrange};
extern const TProgmemRGBPalette16 MatterColors_p FL_PROGMEM = {
    CRGB::OrangeRed, CRGB::DarkOrange, CRGB::Black, CRGB::Yellow,
    CRGB::OrangeRed, CRGB::DarkOrange, CRGB::Black, CRGB::Yellow,
    CRGB::OrangeRed, CRGB::DarkOrange, CRGB::Black, CRGB::Yellow,
    CRGB::OrangeRed, CRGB::DarkOrange, CRGB::Black, CRGB::Yellow};
extern const TProgmemRGBPalette16 LightColors_p FL_PROGMEM = {
    CRGB::White, CRGB::LightCyan, CRGB::LightCoral, CRGB::LightSeaGreen,
    CRGB::White, CRGB::LightCyan, CRGB::LightCoral, CRGB::LightSeaGreen,
    CRGB::White, CRGB::LightCyan, CRGB::LightCoral, CRGB::LightSeaGreen,
    CRGB::White, CRGB::LightCyan, CRGB::LightCoral, CRGB::LightSeaGreen};
