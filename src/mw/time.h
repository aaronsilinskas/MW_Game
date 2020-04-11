#ifndef __INC_MW_TIME_H__
#define __INC_MW_TIME_H__

#include <Arduino.h>

typedef struct Time
{
    uint64_t currentTimeMs = 0;
    uint64_t ellapsedMs = 0;
} Time;

void timeEllapsed(Time *time);

#endif
