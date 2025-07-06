#include "ATA/run/posix/thread_local_impl_posix.h"

namespace ata
{
    namespace detail
    {
        ThreadLocalImplPosix::ThreadLocalImplPosix() :
            m_key(0)
        {
            pthread_key_create(&m_key, NULL);
        }

        ThreadLocalImplPosix::~ThreadLocalImplPosix()
        {
            pthread_key_delete(m_key);
        }

        void ThreadLocalImplPosix::setValue(void* value)
        {
            pthread_setspecific(m_key, value);
        }

        void* ThreadLocalImplPosix::getValue() const
        {
            return pthread_getspecific(m_key);
        }
    }
}