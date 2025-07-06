#ifndef ATA_DEBUG_H
#define ATA_DEBUG_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef NDEBUG
#define ATA_NO_DEBUG
#endif

/*
#define ATA_WARNING(msg, ...) spWarning(msg, ##__VA_ARGS__);
#define ATA_ASSERT(c, msg, ...) 			\
	if(!(c))							\
	{									\
		ATA_WARNING(msg, ##__VA_ARGS__);	\
		assert(0);						\
	}

#ifdef __cplusplus
extern "C" {
#endif

ATA_API void spWarning(const char* format, ...);

#ifdef __cplusplus
}
#endif
*/


#define ATA_OUTPUT(stream, notif, msg, ...)          \
do													\
{                                                   \
    fprintf((stream), "%-16s", (notif));            \
    fprintf((stream), msg, ##__VA_ARGS__);          \
    fprintf((stream), "..\n");                      \
} while(0)

/*
#define ATA_WARNING(msg, ...)                        \
    ATA_OUTPUT(stderr, "[SP WARNING]:",              \
              msg, ##__VA_ARGS__)                   \
*/

//#define ATA_ASSERT(c, msg, ...)  assert((c) && (msg))

#ifndef ATA_NO_DEBUG
#define ATA_INFO(msg, ...)                           \
    ATA_OUTPUT(stdout, "[SP INFO]:",                 \
              msg, ##__VA_ARGS__)                   \

#define ATA_DEBUG(msg, ...)                          \
    ATA_OUTPUT(stdout, "[SP DEBUG]:",                \
              msg, ##__VA_ARGS__)
			  
#define ATA_PRINT(notif, msg, ...)					\
	ATA_OUTPUT(stdout, notif, msg, ##__VA_ARGS__)	\
	
#else
#define ATA_INFO(msg, ...) ;
#define ATA_DEBUG(msg, ...) ;
#define ATA_PRINT(msg, ...);
#endif


#endif
