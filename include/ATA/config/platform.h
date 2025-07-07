#ifndef ATA_PLATFORM_H
#define ATA_PLATFORM_H

/* #undef ATA_PLATFORM_WINDOWS */
/* #undef ATA_PLATFORM_UNIX */
#define ATA_PLATFORM_MACOSX
#define ATA_DYNAMIC_BUILD

#ifdef ATA_DYNAMIC_BUILD
    #if defined(ATA_PLATFORM_WINDOWS)
        #define ATA_API __declspec(dllexport)
    #else
        #define ATA_API __attribute__((visibility("default")))
    #endif
#else
    #define ATA_API
#endif

#ifndef ATA_NO_DEBUG
	#if defined(ATA_COMPILER_MSC)
		#define ATA_DEPRECATED __declspec(deprecated)
	#elif defined(ATA_COMPILER_GNUC) || defined(ATA_COMPILER_CLANG)
		#define ATA_DEPRECATED __attribute__((deprecated))
	#else
		#pragma message("ATA_DEPRECATED is not supported for this compiler..")
		#define ATA_DEPRECATED
	#endif
#else
#define ATA_DEPRECATED
#endif

#endif
