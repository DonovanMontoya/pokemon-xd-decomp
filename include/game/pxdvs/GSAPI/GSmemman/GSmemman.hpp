#ifndef GSAPI_GSMEMMAN_HPP
#define GSAPI_GSMEMMAN_HPP
#include "game/pxdvs/GSAPI/GSmemman/poolAlloc.hpp"
extern "C" {
bool GSmemIsInitialized();
void* GSmemInit(void* start, void* end, int heaps);
int GSmemCreateHeap(void* start, void* end);
int GSmemCreateExternalHeap(void* start, void* end, void* cells, int count);
int GSmemGetCurrentHeap();
int GSmemSetCurrentHeap(int heap);
unsigned short GSmemGetCurrentLayer();
int GSmemSetAllocMethodHeap(int heap, int method);
void* GSmemAllocHeap(int heap, unsigned long size);
void* GSmemAllocFillHeap(int heap, unsigned long size, unsigned char fill);
void* GSmemAllocClrHeap(int heap, unsigned long size);
void* GSmemAllocAlignHeap(int heap, unsigned long size, unsigned short align);
void GSmemShrinkHeap(int heap, void* pointer, unsigned long size);
void GSmemFreeHeap(int heap, void* pointer);
unsigned long GSmemGetHeapFreeSize(int heap, unsigned long* total, unsigned long* largest);
void GSmemDumpHeap(int heap);
void* GSmemAllocAlign(unsigned long size, unsigned short align);
void* GSmemAllocAlignFromEnd(unsigned long size, unsigned short align);
void* GSmemAllocAlignClr(unsigned long size, unsigned short align);
void GSmemShrink(void* pointer, unsigned long size);
unsigned long GSmemGetSize(void* pointer);
bool GSmemCheckHeap(int heap);

void* OSInitAlloc(void* start, void* end, int heaps);
int OSCreateHeap(void* start, void* end);
int OSCreateExternalHeap(void* start, void* end, void* cells, int count);
int OSSetAllocMethodHeap(int heap, int method);
void* OSAllocFromHeap(int heap, unsigned long size);
void OSShrinkHeap(int heap, void* pointer, unsigned long size);
void OSFreeToHeap(int heap, void* pointer);
int OSGetHeapType(int heap);
unsigned long OSGetHeapSize(int heap);
unsigned long OSGetHeapFreeSize(int heap, unsigned long* total, unsigned long* largest);
long OSCheckHeap(int heap);
unsigned long OSReferentSize(void* pointer);
void GSmemVisitHeapAllocated(int heap, void (*visitor)(void*, unsigned long, void*, void*), void*, void*);
}
#endif
