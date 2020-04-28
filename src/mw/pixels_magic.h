#ifndef __INC_MW_PIXELS_MAGIC_H__
#define __INC_MW_PIXELS_MAGIC_H__

#include "pixels.h"
#include "magic.h"

CRGB colorForMagic(MagicType magicType);
const TProgmemRGBPalette16 *paletteForMagic(MagicType magicType);

// Magic color palettes
extern const TProgmemRGBPalette16 NoneColors_p FL_PROGMEM;
extern const TProgmemRGBPalette16 FireColors_p FL_PROGMEM;
extern const TProgmemRGBPalette16 WaterColors_p FL_PROGMEM;
extern const TProgmemRGBPalette16 LightningColors_p FL_PROGMEM;
extern const TProgmemRGBPalette16 AirColors_p FL_PROGMEM;
extern const TProgmemRGBPalette16 EarthColors_p FL_PROGMEM;
extern const TProgmemRGBPalette16 MatterColors_p FL_PROGMEM;
extern const TProgmemRGBPalette16 LightColors_p FL_PROGMEM;

#endif
