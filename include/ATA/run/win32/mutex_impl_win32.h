#ifndef ATA_MUTEX_IMPL_WIN32_H
#define ATA_MUTEX_IMPL_WIN32_H
#include "ATA/run/impl/mutex_impl.h"
#include <windows.h>

namespace ata
{
	class Mutex;
	namespace detail
	{
        class MutexImplWin32 final : public MutexImpl
        {
            private:
                friend class ata::Mutex;
                 MutexImplWin32();
                ~MutexImplWin32();

                virtual void lock() override;
                virtual void unlock() override;

                CRITICAL_SECTION m_section;
        };
	}
}
#endif