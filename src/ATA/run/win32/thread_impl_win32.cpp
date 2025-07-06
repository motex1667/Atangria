#include <windows.h>
#include <process.h>
#include "ATA/run/win32/thread_impl_win32.h"
//#include "ATA/utils/timer.h"

namespace ata
{
    namespace detail
    {
        ThreadImplWin32::ThreadImplWin32(Thread* user) : ThreadImpl(user)
        {
            m_thread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &ThreadImplWin32::entryPoint, user, 0, &m_thread_id));
        }

        ThreadImplWin32::~ThreadImplWin32()
        {
            if(m_thread)
                CloseHandle(m_thread);
        }

        void ThreadImplWin32::wait()
        {
            if(m_thread)
            {
                assert(m_thread_id != GetCurrentThreadId() && "Thread cannot wait for itself");
                WaitForSingleObject(m_thread, INFINITE);
            }
        }

        void ThreadImplWin32::terminate()
        {
            if(m_thread)
                TerminateThread(m_thread, 0);
        }

        unsigned int __stdcall ThreadImplWin32::entryPoint(void* userData)
        {
            ThreadImpl::run(static_cast<Thread*>(userData));
            _endthreadex(0);
            return 0;
        }
    }
}
