#include "magic.h"

const char *magicTypeName(MagicType type)
{
    switch (type)
    {
    case Fire:
        return "Fire";
    case Water:
        return "Water";
    case Air:
        return "Air";
    case Earth:
        return "Earth";
    case Lightning:
        return "Lightning";
    default:
        return "Unknown";
    }
}

void printMagic(Stream *out, const char *name, Magic *magic)
{
    out->printf("%s: %s - %d\n",
                name,
                magicTypeName(magic->type),
                magic->amount);
}
