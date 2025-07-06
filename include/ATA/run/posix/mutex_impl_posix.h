#ifndef ATA_MUTEX_IMPL_POSIX_H
#define ATA_MUTEX_IMPL_POSIX_H
#include "ATA/run/impl/mutex_impl.h"
#include <pthread.h>

namespace ata
{
    class Mutex;
    namespace detail
    {
        class MutexImplPosix final : public MutexImpl
        {
            private:
                friend class ata::Mutex;
                 MutexImplPosix();
                ~MutexImplPosix();

                virtual void lock() override;
                virtual void unlock() override;

                pthread_mutex_t m_mutex;
        };
    }
}

#endif