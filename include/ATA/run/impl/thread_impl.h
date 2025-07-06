#ifndef ATA_THREAD_IMPL_H
#define ATA_THREAD_IMPL_H
#include "ATA/run/thread.h"

namespace ata
{
    namespace detail
    {
        class ThreadImpl
        {
            public:
                ThreadImpl(Thread* user) :
                    m_user{user}
                {
                }

                virtual ~ThreadImpl(){}
                virtual void wait() = 0;
                virtual void terminate() = 0;

            protected:
                static void run(Thread* user);
                Thread* m_user;
        };
    }
}

#endif
