#ifndef ATA_LOCK_H
#define ATA_LOCK_H
#include "ATA/config.h"
#include "ATA/run/mutex.h"

namespace ata
{
    class ATA_API Lock
    {
        public:
            Lock(ata::Mutex& mutex);
           ~Lock();

            ata::Mutex& m_mutex;
    };
}
#endif