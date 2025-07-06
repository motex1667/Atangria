#include "ATA/run/thread.h"
#if defined(ATA_PLATFORM_WINDOWS)
    #include "ATA/run/win32/thread_impl_win32.h"
    typedef ata::detail::ThreadImplWin32 ThreadImplPlatform;
#else
	#include <errno.h>
	#include <time.h>
    #include "ATA/run/posix/thread_impl_posix.h"
    typedef ata::detail::ThreadImplPosix ThreadImplPlatform;
#endif
//#include "ATA/utils/timer.h"

namespace ata
{
    Thread::~Thread()
    {
        wait();
        delete m_thread_impl;
    }

    void Thread::launch()
    {
        wait();
        m_thread_impl = new ThreadImplPlatform(this);
    }

    void Thread::wait()
    {
        if(m_thread_impl)
        {
            m_thread_impl->wait();
            delete m_thread_impl;
            m_thread_impl = nullptr;
        }
    }

    void Thread::terminate()
    {
        assert(m_thread_impl != nullptr && "Thread unavailable");
        m_thread_impl->terminate();
        delete m_thread_impl;
        m_thread_impl = nullptr;
    }

    void Thread::run()
    {
        m_entry_point->run();
    }
}
