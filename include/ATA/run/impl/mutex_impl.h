#ifndef ATA_MUTEX_IMPL_H
#define ATA_MUTEX_IMPL_H

namespace ata
{
    namespace detail
    {
        class MutexImpl
        {
            public:
                         MutexImpl() = default;
                virtual ~MutexImpl() = default;

                virtual void lock() = 0;
                virtual void unlock() = 0;
        };
    }
}

#endif