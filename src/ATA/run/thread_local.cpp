#include "ATA/run/thread_local.h"
#if defined(ATA_PLATFORM_WINDOWS)
    #include "ATA/run/win32/thread_local_impl_win32.h"
    typedef ata::detail::ThreadLocalImplWin32 ThreadLocalImplPlatform;
#else
    #include "ATA/run/posix/thread_local_impl_posix.h"
    typedef ata::detail::ThreadLocalImplPosix ThreadLocalImplPlatform;
#endif

namespace ata
{
    ThreadLocal::ThreadLocal(void* value) :
        m_thread_local_impl{nullptr}
    {
        m_thread_local_impl = new ThreadLocalImplPlatform;
        assert(m_thread_local_impl && "Expected thread-local implementation");
    }

    void ThreadLocal::setValue(void* value)
    {
        m_thread_local_impl->setValue(value);
    }

    void* ThreadLocal::getValue() const
    {
        return m_thread_local_impl->getValue();
    }

    ThreadLocal::~ThreadLocal()
    {
        delete m_thread_local_impl;
    }
}