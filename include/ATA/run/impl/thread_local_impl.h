#ifndef ATA_THREAD_LOCAL_IMPL_H
#define ATA_THREAD_LOCAL_IMPL_H

namespace ata
{
    namespace detail
    {
        class ThreadLocalImpl
        {
            public:
                         ThreadLocalImpl() = default;
                virtual ~ThreadLocalImpl() = default;

                virtual void setValue(void* value) = 0;
                virtual void* getValue() const = 0;
        };
    }
}

#endif