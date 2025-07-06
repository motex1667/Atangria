#ifndef ATA_CPP_H
#define ATA_CPP_H

#ifdef __cplusplus
#if defined(__cpp_constexpr) && (__cpp_constexpr >= 201304L)
    #define ATA_CONSTEXPR constexpr
#else
    #define ATA_CONSTEXPR inline
#endif

#if defined(__cpp_nodiscard) && (__cpp_nodiscard >= 201606L)
	#define ATA_NODISCARD [[nodiscard]]
#else
	#define ATA_NODISCARD
#endif

#endif

#endif
