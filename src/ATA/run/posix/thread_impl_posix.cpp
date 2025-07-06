#include "ATA/run/posix/thread_impl_posix.h"
#include "ATA/core/log.h"
#include <errno.h>
#include <time.h>

namespace ata
{
    namespace detail
    {
        ThreadImplPosix::ThreadImplPosix(Thread* user) :
            ThreadImpl(user),
            m_is_active{false}
        {
            m_is_active = pthread_create(&m_thread, NULL, &ThreadImplPosix::entryPoint, user) == 0;
            if(!m_is_active)
                err() << "Failed to create pthread" << std::endl;
        }

        ThreadImplPosix::~ThreadImplPosix()
        {
        }

        void ThreadImplPosix::wait()
        {
            if(m_is_active)
            {
                assert((pthread_equal(pthread_self(), m_thread) == 0) && "Thread cannot wait for itself");
                pthread_join(m_thread, NULL);
            }
        }

        void ThreadImplPosix::terminate()
        {
            if(m_is_active)
            {
                pthread_cancel(m_thread);
            }
        }

        void* ThreadImplPosix::entryPoint(void* userData)
        {
            pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
            ThreadImpl::run(static_cast<Thread*>(userData));

            return NULL;
        }
    }
}
