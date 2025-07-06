#ifndef ATA_THREAD_LOCAL_IMPL_WIN32_H
#define ATA_THREAD_LOCAL_IMPL_WIN32_H
#include "ATA/run/impl/thread_local_impl.h"
#include <windows.h>

namespace ata
{
	class ThreadLocal;
	namespace detail
	{
        class ThreadLocalImplWin32 final : public ThreadLocalImpl
        {
            private:
                friend class ata::ThreadLocal;
                ThreadLocalImplWin32();
               ~ThreadLocalImplWin32();

                virtual void  setValue(void* value) override;
                virtual void* getValue() const override;

                DWORD m_index;
        };
	}
}
#endif