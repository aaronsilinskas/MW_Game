#ifndef __INC_MW_MAGIC_H__
#define __INC_MW_MAGIC_H__

#include <Arduino.h>

typedef enum MagicType
{
    None,
    Fire,
    Water,
    Lightning,
    Air,
    Earth,
    Matter,
    Light
} MagicType;

const char *magicTypeName(MagicType type);

typedef uint32_t MagicAmount;

typedef struct Magic
{
    MagicType type;
    MagicAmount amount;

} Magic;

uint8_t magicBitmask(MagicType type);
MagicType bitmaskToMagic(uint8_t bitmask);
MagicType combineMagic(MagicType type1, MagicType type2);

#define MAGIC_TYPES_PER_STORAGE 4

typedef struct MagicStorage
{
    Magic magics[MAGIC_TYPES_PER_STORAGE];

} MagicStorage;

void printMagic(Stream *out, const char *name, Magic &magic);

#endif
