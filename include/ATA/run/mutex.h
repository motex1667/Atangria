#ifndef ATA_MUTEX_H
#define ATA_MUTEX_H
#include "ATA/config.h"
#include "ATA/core/no_copy.h"

namespace ata
{
    namespace detail
    {
        class MutexImpl;
    }

    class ATA_API Mutex : public NonCopyable
    {
        public:
            Mutex();
           ~Mutex();

            void lock();
            void unlock();

        private:
            detail::MutexImpl* m_mutex_impl;
            //SPmutex m_mutex;
    };
}

#endif