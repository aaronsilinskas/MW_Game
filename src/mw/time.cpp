#include "time.h"

void timeEllapsed(Time *time)
{
    uint64_t updatedTimeMs = millis();
    if (time->currentTimeMs == 0)
    {
        time->currentTimeMs = updatedTimeMs;
        time->ellapsedMs = 0;
    }
    else
    {
        time->ellapsedMs = updatedTimeMs - time->currentTimeMs;
        time->currentTimeMs = updatedTimeMs;
    }
}
