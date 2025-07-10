#ifndef ATA_TYPES_H
#define ATA_TYPES_H
#define ATA_FALSE 0
#define ATA_TRUE 1

#ifdef __cplusplus
extern "C" {
#endif
typedef float ATA_float;
typedef double ATA_double;

typedef char ATA_char;
typedef unsigned char ATA_uchar;
typedef signed char ATA_int8;
typedef unsigned char ATA_uint8;
typedef ATA_int8 ATA_byte;
typedef ATA_uint8 ATA_ubyte;

typedef signed short ATA_int16;
typedef unsigned short ATA_uint16;
typedef ATA_int16 ATA_short;
typedef ATA_uint16 ATA_ushort;

typedef signed int ATA_int32;
typedef unsigned int ATA_uint32;
typedef ATA_int32 ATA_int;
typedef ATA_uint32 ATA_uint;
typedef ATA_int ATA_bool;

#if defined(ATA_MSC_VER)
typedef signed __int64 ATA_int64;
typedef unsigned __int64 ATA_uint64;
#else
typedef signed long long ATA_int64;
typedef unsigned long long ATA_uint64;
#endif // defined
typedef ATA_int64 ATA_long;
typedef ATA_uint64 ATA_ulong;

typedef ATA_ulong ATA_size;
typedef ATA_size ATA_index;
typedef void (*ATA_proc)(void);
typedef ATA_uint64 ATA_time;
#ifdef __cplusplus
}
#endif
#endif