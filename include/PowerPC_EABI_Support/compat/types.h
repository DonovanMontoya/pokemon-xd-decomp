#ifndef XD_RUNTIME_TYPES_H
#define XD_RUNTIME_TYPES_H
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef int BOOL;
typedef unsigned long size_t;
typedef unsigned int uint;
#define TRUE 1
#define FALSE 0
#define ATTRIBUTE_ALIGN(n) __attribute__((aligned(n)))
#define __REGISTER register
#ifndef NULL
#define NULL 0
#endif
#endif
