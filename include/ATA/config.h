#ifndef ATA_CONFIG_H
#define ATA_CONFIG_H

#if defined(__cplusplus) && (__cplusplus < 201103L)
#error C++11 or later required to compile API.
#endif // __cplusplus

#define ATA_VERSION_MAJOR 2
#define ATA_VERSION_MINOR 1
#define ATA_VERSION_PATCH 0

#define ATA_BUILD_PLATFORM_WINDOWS
/* #undef ATA_BUILD_PLATFORM_UNIX */
/* #undef ATA_BUILD_PLATFORM_MACOSX */

#endif
