#include "ATA/run/impl/thread_impl.h"

namespace ata
{
    namespace detail
    {
        void ThreadImpl::run(Thread* user)
        {
            user->run();
        }
    }
}
