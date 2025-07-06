#include "ATA/run/cthread.h"
#if defined(ATA_PLATFORM_WINDOWS)
#include <windows.h>
#else
#include <pthread.h>
#endif

struct _SPtls
{
#if defined(ATA_PLATFORM_WINDOWS)
    SPbool allocated;
    DWORD index;
#else
    SPbool allocated;
    pthread_key_t key;
#endif
};

// POSIX-specific mutex data
//
struct _SPmutex
{
#if defined(ATA_PLATFORM_WINDOWS)
    SPbool allocated;
    CRITICAL_SECTION section;
#else
    SPbool allocated;
    pthread_mutex_t handle;
#endif
};

SPtls spCreateTls()
{
    SPtls tls = calloc(1, sizeof(struct _SPtls));

#if defined(ATA_PLATFORM_WINDOWS)
    if(tls->index == TLS_OUT_OF_INDEXES)
#else
    if(pthread_key_create(&tls->key, NULL) != 0)
#endif
    {
        free(tls);
        return NULL;
    }

    tls->allocated = ATA_TRUE;
    return tls;
}

void spDestroyTls(SPtls tls)
{
    if (tls->allocated)
    {
#if defined(ATA_PLATFORM_WINDOWS)
        TlsFree(tls->index);
#else
        pthread_key_delete(tls->key);
#endif
    }

    free(tls);
}

void* spGetTls(SPtls tls)
{
    return (tls->allocated) ?
#if defined(ATA_PLATFORM_WINDOWS)
     TlsGetValue(tls->index)
#else
    pthread_getspecific(tls->key)
#endif
    : NULL;
}

void spSetTls(SPtls tls, void* value)
{
    if(tls->allocated)
    {
#if defined(ATA_PLATFORM_WINDOWS)
        TlsSetValue(tls->index, value);
#else
        pthread_setspecific(tls->key, value);
#endif
    }
}

SPmutex spCreateMutex()
{
    SPmutex mutex = calloc(1, sizeof(struct _SPmutex));

#if defined(ATA_PLATFORM_WINDOWS)
    InitializeCriticalSection(&mutex->section);
#else
    if (pthread_mutex_init(&mutex->handle, NULL) != 0)
    {
        free(mutex);
        return NULL;
    }
#endif
    mutex->allocated = ATA_TRUE;
    return mutex;
}

void spDestroyMutex(SPmutex mutex)
{
    if (mutex->allocated)
    {
#if defined(ATA_PLATFORM_WINDOWS)
        DeleteCriticalSection(&mutex->section);
#else
        pthread_mutex_destroy(&mutex->handle);
#endif
    }
    free(mutex);
}

void spLockMutex(SPmutex mutex)
{
    assert(mutex->allocated == ATA_TRUE);
#if defined(ATA_PLATFORM_WINDOWS)
    EnterCriticalSection(&mutex->section);
#else
    pthread_mutex_lock(&mutex->handle);
#endif
}

void spUnlockMutex(SPmutex mutex)
{
    assert(mutex->allocated == ATA_TRUE);
#if defined(ATA_PLATFORM_WINDOWS)
    LeaveCriticalSection(&mutex->section);
#else
    pthread_mutex_unlock(&mutex->handle);
#endif
}
