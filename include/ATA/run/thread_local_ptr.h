#ifndef ATA_THREAD_LOCAL_PTR_H
#define ATA_THREAD_LOCAL_PTR_H
#include "ATA/config.h"
#include "ATA/run/thread_local.h"

namespace ata
{
    template<typename T>
    class ATA_API ThreadLocalPtr : private ThreadLocal
    {
        public:
            ThreadLocalPtr(T* value = NULL);
            T& operator*() const;
            T* operator->() const;
            operator T*() const;
            ThreadLocalPtr<T>& operator=(T* value);
            ThreadLocalPtr<T>& operator=(const ThreadLocalPtr<T>& other);
    };

#include "ATA/run/thread_local_ptr.inl"

}

#endif
