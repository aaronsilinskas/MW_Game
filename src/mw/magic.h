#ifndef __INC_MW_MAGIC_H__
#define __INC_MW_MAGIC_H__

#include <Arduino.h>

typedef enum MagicType
{
    Fire,
    Water,
    Air,
    Earth,
    Lightning
} MagicType;

const char *magicTypeName(MagicType type);

typedef uint32_t MagicAmount;

typedef struct Magic
{
    MagicType type;
    MagicAmount amount;

} Magic;

#define MAGIC_TYPES_PER_STORAGE 4

typedef struct MagicStorage
{
    Magic magics[MAGIC_TYPES_PER_STORAGE];

} MagicStorage;

void printMagic(Stream *out, const char *name, Magic &magic);

#endif
