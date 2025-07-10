#include "ATA/gfx/glresource.h"
#include "ATA/core/context.h"

namespace ata
{
    GLResource::GLResource()
    {
        ContextManager::initSharedContext();
    }

    GLResource::~GLResource()
    {
        ContextManager::destroySharedContext();
    }

    GLResource::ContextLock::ContextLock()
    {
        ContextManager::acquireContext();
    }

    GLResource::ContextLock::~ContextLock()
    {
        ContextManager::releaseContext();
    }	
}