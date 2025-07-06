#include "ATA/run/mutex.h"
#if defined(ATA_PLATFORM_WINDOWS)
    #include "ATA/run/win32/mutex_impl_win32.h"
    typedef ata::detail::MutexImplWin32 MutexImplPlatform;
#else
    #include "ATA/run/posix/mutex_impl_posix.h"
    typedef ata::detail::MutexImplPosix MutexImplPlatform;
#endif

namespace ata
{
    Mutex::Mutex() :
        m_mutex_impl{nullptr}
    {
        m_mutex_impl = new MutexImplPlatform;
        assert(m_mutex_impl && "Expected mutex implementation");
    }

    void Mutex::lock()
    {
        m_mutex_impl->lock();
    }

    void Mutex::unlock()
    {
        m_mutex_impl->unlock();
    }

    Mutex::~Mutex()
    {
        delete m_mutex_impl;
    }
}