#include "ATA/run/lock.h"

namespace ata
{
    Lock::Lock(ata::Mutex& mutex) :
        m_mutex{mutex}
    {
        m_mutex.lock();
    }
    Lock::~Lock()
    {
        m_mutex.unlock();
    }
}