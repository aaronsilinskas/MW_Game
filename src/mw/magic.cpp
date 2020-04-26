#include "magic.h"

const char *magicTypeName(MagicType type)
{
    switch (type)
    {
    case None:
        return "None";
    case Fire:
        return "Fire";
    case Water:
        return "Water";
    case Lightning:
        return "Lightning";
    case Air:
        return "Air";
    case Earth:
        return "Earth";
    case Matter:
        return "Matter";
    case Light:
        return "Light";
    }
    return "Unknown";
}

uint8_t magicBitmask(MagicType type)
{
    switch (type)
    {
    case None:
        return 0;
    case Fire:
        return 0b100;
    case Water:
        return 0b010;
    case Lightning:
        return 0b001;
    case Air:
        return 0b110;
    case Earth:
        return 0b011;
    case Matter:
        return 0b101;
    case Light:
        return 0b111;
    }
    return 0;
}

MagicType bitmaskToMagic(uint8_t bitmask)
{
    switch (bitmask)
    {
    case 0:
        return None;
    case 0b100:
        return Fire;
    case 0b010:
        return Water;
    case 0b001:
        return Lightning;
    case 0b110:
        return Air;
    case 0b011:
        return Earth;
    case 0b101:
        return Matter;
    case 0b111:
        return Light;
    }
    return None;
}

MagicType combineMagic(MagicType type1, MagicType type2)
{
    if (type1 == type2) {
        return type1;
    }

    uint8_t type1Bitmask = magicBitmask(type1);
    uint8_t type2Bitmask = magicBitmask(type2);
    uint8_t combinedBitmask = type1Bitmask ^ type2Bitmask;
    return bitmaskToMagic(combinedBitmask);
}

void printMagic(Stream *out, const char *name, Magic &magic)
{
    out->printf("%s: %s - %d\n",
                name,
                magicTypeName(magic.type),
                magic.amount);
}
