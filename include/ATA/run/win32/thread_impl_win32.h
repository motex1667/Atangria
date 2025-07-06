#ifndef ATA_THREAD_IMPL_WIN32_H
#define ATA_THREAD_IMPL_WIN32_H
#include "ATA/run/impl/thread_impl.h"
//#include "ATA/config/windows.h"
#include <windows.h>

namespace ata
{
    namespace detail
    {
        void sleepImplWin32(SPint64 duration);

        class ThreadImplWin32 final : public ThreadImpl
        {
            public:
                ThreadImplWin32(Thread* owner);
               ~ThreadImplWin32();

                virtual void wait() override;
                virtual void terminate() override;

            private:
                ATA_ALIGN_STACK static unsigned int __stdcall entryPoint(void* userData);
                HANDLE m_thread;
                unsigned int m_thread_id;
        };
    }
}

#endif
