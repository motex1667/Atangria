#ifndef ATA_THREAD_LOCAL_H
#define ATA_THREAD_LOCAL_H
#include "ATA/config.h"
#include "ATA/core/no_copy.h"

namespace ata
{
    namespace detail
    {
        class ThreadLocalImpl;
    }

    class ATA_API ThreadLocal : public NonCopyable
    {
        public:
            ThreadLocal(void* value = NULL);
           ~ThreadLocal();

            void  setValue(void* value);
            void* getValue() const;

        private:
            detail::ThreadLocalImpl* m_thread_local_impl;
            //SPtls m_tls;
    };
}
#endif