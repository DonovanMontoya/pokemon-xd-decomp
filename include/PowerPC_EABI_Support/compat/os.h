#ifndef XD_RUNTIME_OS_H
#define XD_RUNTIME_OS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif
extern int __OSCurrHeap;
void OSReport(const char*, ...);
void* OSGetArenaLo(void);
void* OSGetArenaHi(void);
void* OSInitAlloc(void*, void*, int);
void OSSetArenaLo(void*);
int OSSetCurrentHeap(int);
int OSCreateHeap(void*, void*);
void OSFreeToHeap(int, void*);
u32 OSGetConsoleType(void);
#define OSRoundUp32B(x) (((u32)(x) + 31) & ~31)
#define OSRoundDown32B(x) ((u32)(x) & ~31)
#ifdef __cplusplus
}
#endif
#endif
