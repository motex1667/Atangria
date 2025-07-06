#ifndef ATA_THREAD_IMPL_POSIX_H
#define ATA_THREAD_IMPL_POSIX_H
#include "ATA/run/impl/thread_impl.h"
#include <pthread.h>

namespace ata
{
    namespace detail
    {
        void sleepImplPosix(SPint64 duration);
        class ThreadImplPosix final : public ThreadImpl
        {
            public:
                ThreadImplPosix(Thread* owner);
               ~ThreadImplPosix();

                virtual void wait() override;
                virtual void terminate() override;

            private:
                static void* entryPoint(void* userData);
                pthread_t m_thread;
                bool m_is_active;
        };
    }
}

#endif
