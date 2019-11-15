#ifndef __INC_MW_TIME_H__
#define __INC_MW_TIME_H__

#include <Arduino.h>

typedef struct Time
{
    uint64_t currentTimeMs;
    uint64_t ellapsedMs;
} Time;

void timeEllapsed(Time *time);

#endif
