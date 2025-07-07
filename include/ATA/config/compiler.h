#ifndef ATA_COMPILER_H
#define ATA_COMPILER_H

#define ATA_COMPILER_CLANG
/* #undef ATA_COMPILER_GCC */
/* #undef ATA_COMPILER_MSVC */

#ifdef __cplusplus
	#if defined(_MSVC_LANG)
		#define ATA_CPP_VERSION _MSVC_LANG
	#else
		#define ATA_CPP_VERSION __cplusplus
	#endif
	#if (ATA_CPP_VERSION < 201103L)
		#error C++11 or later required to compile API.
	#endif // __cplusplus
#endif

#if defined(ATA_COMPILER_GCC)
/* #undef ATA_COMPILER_GCC_W64 */
#elif defined(ATA_COMPILER_MSVC)
#define ATA_MSVC_VERSION 
#endif

#if defined(__clang__)
	#define ATA_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUC__)
	#define ATA_COMPILER_GNUC
#elif defined(_MSC_VER)
	#define ATA_COMPILER_MSC
#endif

#ifdef ATA_COMPILER_GNUC
	#define ATA_MAYBE_UNUSED __attribute__((__unused__))
#elif defined(ATA_COMPILER_MSC)
	#define ATA_MAYBE_UNUSED __pragma(warning(suppress:4100))
#elif defined(ATA_COMPILER_CLANG)
	#define ATA_MAYBE_UNUSED [[maybe_unused]]
#else
	#define ATA_MAYBE_UNUSED
#endif

#if defined(ATA_PLATFORM_WINDOWS) && (defined(ATA_COMPILER_CLANG) || defined(ATA_COMPILER_GNUC))
    #define ATA_ALIGN_STACK __attribute__((__force_align_arg_pointer__))
#else
    #define ATA_ALIGN_STACK
#endif

#endif
