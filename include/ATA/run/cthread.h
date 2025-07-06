#ifndef ATA_CTHREAD_H
#define ATA_CTHREAD_H
#include "ATA/config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SPtls* SPtls;
typedef struct _SPmutex* SPmutex;

SPtls spCreateTls();
void spDestroyTls(SPtls tls);
void* spGetTls(SPtls tls);
void spSetTls(SPtls tls, void* value);

SPmutex spCreateMutex();
void spDestroyMutex(SPmutex mutex);
void spLockMutex(SPmutex mutex);
void spUnlockMutex(SPmutex mutex);

#ifdef __cplusplus
}
#endif

#endif