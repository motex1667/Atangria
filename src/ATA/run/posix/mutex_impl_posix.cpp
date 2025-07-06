#include "ATA/run/posix/mutex_impl_posix.h"

namespace ata
{
    namespace detail
    {
        MutexImplPosix::MutexImplPosix()
        {
            pthread_mutexattr_t attributes;
            pthread_mutexattr_init(&attributes);
            pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_RECURSIVE);

            pthread_mutex_init(&m_mutex, &attributes);
        }

        MutexImplPosix::~MutexImplPosix()
        {
            pthread_mutex_destroy(&m_mutex);
        }

        void MutexImplPosix::lock()
        {
            pthread_mutex_lock(&m_mutex);
        }

        void MutexImplPosix::unlock()
        {
            pthread_mutex_unlock(&m_mutex);
        }
    }
}