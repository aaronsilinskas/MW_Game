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

void printMagic(Stream *out, const char *name, Magic &magic);

#endif
