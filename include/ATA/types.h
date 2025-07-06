#ifndef ATA_TYPES_H
#define ATA_TYPES_H

#define ATA_FALSE 0
#define ATA_TRUE 1

#ifdef __cplusplus
extern "C" {
#endif
typedef float SPfloat;
typedef double SPdouble;

typedef char SPchar;
typedef unsigned char SPuchar;
typedef signed char SPint8;
typedef unsigned char SPuint8;
typedef SPint8 SPbyte;
typedef SPuint8 SPubyte;

typedef signed short SPint16;
typedef unsigned short SPuint16;
typedef SPint16 SPshort;
typedef SPuint16 SPushort;

#define ATA_FALSE 0
#define ATA_TRUE 1
typedef signed int SPint32;
typedef unsigned int SPuint32;
typedef SPint32 SPint;
typedef SPuint32 SPuint;
typedef SPint SPbool;

#if defined(ATA_MSC_VER)
typedef signed __int64 SPint64;
typedef unsigned __int64 SPuint64;
#else
typedef signed long long SPint64;
typedef unsigned long long SPuint64;
#endif // defined
typedef SPint64 SPlong;
typedef SPuint64 SPulong;

typedef SPulong SPsize;
typedef SPsize SPindex;
typedef SPulong SPhash;
typedef void (*SPproc)(void);
typedef SPuint64 SPtime;
#ifdef __cplusplus
}
#endif
#endif