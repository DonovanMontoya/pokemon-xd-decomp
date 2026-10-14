#include "game/pxdvs/GSAPI/GSmemman/GSmemman.hpp"

static int _currentHeap = -1;
static bool _memInitialized;
static unsigned short _currentLayer;

bool GSmemIsInitialized() { return _memInitialized; }
void* GSmemInit(void* start, void* end, int heaps) {
    register void* arena;
    _currentHeap = -1;
    _currentLayer = 0;
    arena = OSInitAlloc(start, end, heaps);
    _memInitialized = true;
    GSmemInitPool();
    return arena;
}
int GSmemCreateHeap(void* start, void* end) {
    if (!GSmemIsInitialized()) return -1;
    return OSCreateHeap(start, end);
}
int GSmemCreateExternalHeap(void* start, void* end, void* cells, int count) {
    if (!GSmemIsInitialized()) return -1;
    return OSCreateExternalHeap(start, end, cells, count);
}
int GSmemGetCurrentHeap() { return _currentHeap; }
int GSmemSetCurrentHeap(int heap) {
    register int previous = GSmemGetCurrentHeap();
    _currentHeap = heap;
    return previous;
}
unsigned short GSmemGetCurrentLayer() { return _currentLayer; }
int GSmemSetAllocMethodHeap(int heap, int method) { return OSSetAllocMethodHeap(heap, method); }
void* GSmemAllocHeap(int heap, unsigned long size) {
    register void* pointer = OSAllocFromHeap(heap, size);
    return pointer;
}
void* GSmemAllocFillHeap(register int heap, register unsigned long size, unsigned char fill) {
    register void* pointer = GSmemAllocHeap(heap, size);
    if (!pointer) return 0;
    if (OSGetHeapType(heap) == 0) memset(pointer, fill, size);
    return pointer;
}
void* GSmemAllocClrHeap(int heap, unsigned long size) { return GSmemAllocFillHeap(heap, size, 0); }
void* GSmemAllocAlignHeap(int heap, unsigned long size, unsigned short align) {
    if (align <= 32) return GSmemAllocHeap(heap, size);
    return 0;
}
void GSmemShrinkHeap(int heap, void* pointer, unsigned long size) { OSShrinkHeap(heap, pointer, size); }
void GSmemFreeHeap(int heap, void* pointer) { OSFreeToHeap(heap, pointer); }
unsigned long GSmemGetHeapFreeSize(int heap, unsigned long* total, unsigned long* largest) {
    return OSGetHeapFreeSize(heap, total, largest);
}
static void _dumpHeapVisitor(void*, unsigned long, void*, void*);
void GSmemDumpHeap(register int heap) {
    unsigned long largest, totalFree, used, allocations = 0;
    GSmemVisitHeapAllocated(heap, _dumpHeapVisitor, 0, &allocations);
    OSGetHeapFreeSize(heap, &totalFree, &largest);
    register unsigned long size = OSGetHeapSize(heap);
    used = size - totalFree;
}
static void _dumpHeapVisitor(void*, unsigned long, void*, void*) {}
void* GSmemAlloc(unsigned long size) { return GSmemAllocHeap(GSmemGetCurrentHeap(), size); }
void* GSmemAllocClr(unsigned long size) { return GSmemAllocClrHeap(GSmemGetCurrentHeap(), size); }
void* GSmemAllocAlign(unsigned long size, unsigned short align) {
    return GSmemAllocAlignHeap(GSmemGetCurrentHeap(), size, align);
}
void* GSmemAllocAlignFromEnd(unsigned long size, unsigned short align) {
    return GSmemAllocAlignHeap(GSmemGetCurrentHeap(), size, align);
}
void* GSmemAllocAlignClr(register unsigned long size, unsigned short align) {
    register void* pointer = GSmemAllocAlignHeap(GSmemGetCurrentHeap(), size, align);
    if (pointer) memset(pointer, 0, size);
    return pointer;
}
void GSmemShrink(void* pointer, unsigned long size) { GSmemShrinkHeap(GSmemGetCurrentHeap(), pointer, size); }
void GSmemFree(register void* pointer) { if (pointer) GSmemFreeHeap(GSmemGetCurrentHeap(), pointer); }
unsigned long GSmemGetSize(register void* pointer) {
    if (!pointer) return 0;
    return OSReferentSize(pointer);
}
unsigned long GSmemGetLargestFree() {
    unsigned long largest;
    OSGetHeapFreeSize(GSmemGetCurrentHeap(), 0, &largest);
    return largest;
}
bool GSmemCheckHeap(int heap) { return OSCheckHeap(heap) >= 0; }
