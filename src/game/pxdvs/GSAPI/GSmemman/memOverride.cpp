#include "game/pxdvs/GSAPI/GSmemman/GSmemman.hpp"

void* operator new(register unsigned long size) {
    if (GSmemIsInitialized()) {
        // The original small-allocation diagnostic leaves a local marker.
        if (size < 0x40) { int smallAllocation = 0; }
        return GSmemAlloc(size);
    }
    return 0;
}
void* operator new[](unsigned long size) {
    if (GSmemIsInitialized()) return GSmemAlloc(size);
    return 0;
}
void operator delete(void* pointer) { GSmemFree(pointer); }
void operator delete[](void* pointer) { GSmemFree(pointer); }
