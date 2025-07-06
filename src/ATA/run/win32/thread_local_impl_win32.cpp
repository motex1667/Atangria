#include "ATA/run/win32/thread_local_impl_win32.h"

namespace ata
{
	namespace detail
	{
		ThreadLocalImplWin32::ThreadLocalImplWin32()
		{
			m_index = TlsAlloc();
		}
		
		ThreadLocalImplWin32::~ThreadLocalImplWin32()
		{
			TlsFree(m_index);
		}
		
		void ThreadLocalImplWin32::setValue(void* value)
		{
			TlsSetValue(m_index, value);
		}
		
		void* ThreadLocalImplWin32::getValue() const
		{
			return TlsGetValue(m_index);
		}
	}
}