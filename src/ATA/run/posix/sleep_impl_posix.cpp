#include "ATA/run/sleep.h"
#include <time.h>
#include <errno.h>

namespace ata
{
    void sleep(SPint64 duration)
    {
        if(duration >= 0)
        {
            SPuint64 usecs = (SPuint64) duration;
            timespec ti;
            ti.tv_nsec = (usecs % 1000000) * 1000;
            ti.tv_sec = usecs / 1000000;
            while((nanosleep(&ti, &ti) == -1) && (errno == EINTR));
        }
    }
}