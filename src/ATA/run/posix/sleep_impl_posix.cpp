#include "ATA/run/sleep.h"
#include <time.h>
#include <errno.h>

namespace ata
{
    void sleep(ATA_int64 duration)
    {
        if(duration >= 0)
        {
            ATA_uint64 usecs = (ATA_uint64) duration;
            timespec ti;
            ti.tv_nsec = (usecs % 1000000) * 1000;
            ti.tv_sec = usecs / 1000000;
            while((nanosleep(&ti, &ti) == -1) && (errno == EINTR));
        }
    }
}