#include "ATA/run/sleep.h"
//#include "ATA/utils/timer.h"
#include <windows.h>

namespace ata
{
    void sleep(ATA_int64 duration)
    {
        if(duration >= 0)
        {
            assert(0 && "Sleep implementation not available");
            /*
            TIMECAPS tc;
            timeGetDevCaps(&tc, sizeof(TIMECAPS));
            timeBeginPeriod(tc.wPeriodMin);
            Sleep(asMilliseconds(duration));
            timeEndPeriod(tc.wPeriodMin);
            */
        }
    }
}