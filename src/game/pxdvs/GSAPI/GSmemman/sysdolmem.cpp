#include "game/pxdvs/GSAPI/GSmemman/poolAlloc.hpp"

extern "C" void HSD_SetInitParameter(int parameter, ...);

GSmemPoolAllocator* _Sysdol8Allocator;
GSmemPoolAllocator* _Sysdol12Allocator;
GSmemPoolAllocator* _Sysdol20Allocator;
GSmemPoolAllocator* _Sysdol28Allocator;
GSmemPoolAllocator* _Sysdol48Allocator;


static void* _memAllocCallback(unsigned long, unsigned long, unsigned long);
static void _memFreeCallback(void*);
static unsigned long _memGetRemainCallback();
static void _memClearCallback();
static int _memCheckOwnCallback(void*);

void GSmemInitSysdolAllocator() {
    _Sysdol8Allocator = GSmemCreatePool(4000, 8);
    _Sysdol12Allocator = GSmemCreatePool(8000, 12);
    _Sysdol20Allocator = GSmemCreatePool(3000, 20);
    _Sysdol28Allocator = GSmemCreatePool(5000, 28);
    _Sysdol48Allocator = GSmemCreatePool(5000, 48);
    HSD_SetInitParameter(2, _memAllocCallback, _memFreeCallback, _memGetRemainCallback,
                         _memClearCallback, _memCheckOwnCallback, 0);
}

GSmemPoolAllocator* GSmemGetSysdolAllocator(unsigned long size) {
    register GSmemPoolAllocator* allocator = 0;
    switch (size) {
    case 8: allocator = _Sysdol8Allocator; break;
    case 12: allocator = _Sysdol12Allocator; break;
    case 20: allocator = _Sysdol20Allocator; break;
    case 28: allocator = _Sysdol28Allocator; break;
    case 48: allocator = _Sysdol48Allocator; break;
    }
    return allocator;
}

static void* _memAllocCallback(register unsigned long size, unsigned long, unsigned long) {
    register void* pointer;
    if (size == 0) {
        pointer = 0;
        return pointer;
    }
    if (size < 64) {
        register GSmemPoolAllocator* allocator = GSmemGetSysdolAllocator(size);
        if (allocator) {
            pointer = allocator->allocCell();
            if (pointer) return pointer;
        }
    }
    return GSmemAlloc(size);
}

static void _memFreeCallback(register void* pointer) {
    if (pointer) {
        if (_Sysdol12Allocator->isRegistration(pointer)) _Sysdol12Allocator->freeCell(pointer);
        else if (_Sysdol20Allocator->isRegistration(pointer)) _Sysdol20Allocator->freeCell(pointer);
        else if (_Sysdol28Allocator->isRegistration(pointer)) _Sysdol28Allocator->freeCell(pointer);
        else if (_Sysdol48Allocator->isRegistration(pointer)) _Sysdol48Allocator->freeCell(pointer);
        else GSmemFree(pointer);
    }
}

static unsigned long _memGetRemainCallback() { return GSmemGetLargestFree(); }
static void _memClearCallback() {}
static int _memCheckOwnCallback(void*) { return 1; }
