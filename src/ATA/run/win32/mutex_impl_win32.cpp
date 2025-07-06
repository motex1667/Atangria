#include "ATA/run/win32/mutex_impl_win32.h"

namespace ata
{
	namespace detail
	{
		MutexImplWin32::MutexImplWin32()
		{
			InitializeCriticalSection(&m_section);
		}
		
		MutexImplWin32::~MutexImplWin32()
		{
			DeleteCriticalSection(&m_section);
		}
		
		void MutexImplWin32::lock()
		{
			EnterCriticalSection(&m_section);
		}
		
		void MutexImplWin32::unlock()
		{
			LeaveCriticalSection(&m_section);
		}
	}
}