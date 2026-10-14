#ifndef GSAPI_POOL_ALLOC_HPP
#define GSAPI_POOL_ALLOC_HPP

class GSmemPoolAllocator {
public:
    unsigned long used;
    unsigned long peak;
    unsigned long capacity;
    unsigned long cellSize;
    unsigned char* start;
    unsigned char* end;
    struct Cell { Cell* next; };
    Cell* free;

    void init(unsigned long count, unsigned long size);
    void* allocCell();
    void freeCell(void* pointer);
    unsigned long getFreeCell() const;
    bool isRegistration(void* pointer);
    void dump();
};

extern "C" {
void* GSmemAlloc(unsigned long size);
void* GSmemAllocClr(unsigned long size);
void GSmemFree(void* pointer);
unsigned long GSmemGetLargestFree();
void* memset(void*, int, unsigned long);
void GSmemInitPool();
GSmemPoolAllocator* GSmemCreatePool(unsigned long count, unsigned long size);
void* GSmemAllocPool(GSmemPoolAllocator* pool);
void GSmemFreePool(GSmemPoolAllocator* pool, void* pointer);
bool GSmemIsRegistrationPool(GSmemPoolAllocator* pool, void* pointer);
void GSmemDumpPool(GSmemPoolAllocator* pool);
unsigned long GSmemGetFreePool(GSmemPoolAllocator* pool);
GSmemPoolAllocator* GSmemGetSysdolAllocator(unsigned long size);
void GSmemInitSysdolAllocator();
}

#endif
