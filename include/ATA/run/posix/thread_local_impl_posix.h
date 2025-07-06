#ifndef ATA_THREAD_LOCAL_IMPL_POSIX_H
#define ATA_THREAD_LOCAL_IMPL_POSIX_H
#include "ATA/run/impl/thread_local_impl.h"
#include <pthread.h>

namespace ata
{
    class ThreadLocal;
    namespace detail
    {
        class ThreadLocalImplPosix final : public ThreadLocalImpl
        {
            private:
                friend class ata::ThreadLocal;
                ThreadLocalImplPosix();
               ~ThreadLocalImplPosix();

                virtual void  setValue(void* value) override;
                virtual void* getValue() const override;

                pthread_key_t m_key;
        };
    }
}
#endif