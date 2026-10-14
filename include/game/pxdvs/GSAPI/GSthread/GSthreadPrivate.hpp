#ifndef GSTHREAD_PRIVATE_HPP
#define GSTHREAD_PRIVATE_HPP

#include <dolphin/types.h>

struct GSthread {
    GSthread* prev;         // 0x0
    GSthread* next;         // 0x4
    u8 used;                // 0x8
    u8 blocked;             // 0x9
    u8 groupBlocked;        // 0xA
    u8 priority;            // 0xB
    u32 groupId;            // 0xC
    s32 stackSize;          // 0x10
    u8 running;             // 0x14
    u8 terminate;           // 0x15
    u8 usesFPU;             // 0x16
    u8 autoTerminate;       // 0x17
    s32 result;             // 0x18
    s32 entry;              // 0x1C
    s32* stack;             // 0x20
    u8* regState;           // 0x24
    s32 heap;               // 0x28
    s32 lr;                 // 0x2C
    char name[0x20];        // 0x30
};

struct GSthreadRegState {
    u8 raw[0x84];
    void (*entry)();
};

extern "C" {
void* memcpy(void*, const void*, unsigned long);
void DCFlushRange(void*, unsigned long);
void GSlogWrite(const char*, ...);
void* GSmemAlloc(unsigned long);
int GSmemGetCurrentHeap();
void* GSmemAllocHeap(int, unsigned long);
void* GSmemAllocAlignHeap(int, unsigned long, unsigned short);
void GSmemFreeHeap(int, void*);
u8 GSscratchIsPtr(void*);
void GSscratchWaitForCompletion();
s32 GSscratchStore(void*, void*, u32);
void GSscratchFree(void*);
}

#endif
