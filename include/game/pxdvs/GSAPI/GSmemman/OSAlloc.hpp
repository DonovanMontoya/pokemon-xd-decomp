#ifndef GSAPI_OSALLOC_HPP
#define GSAPI_OSALLOC_HPP
// External heaps store 20-byte descriptors separately from their allocation area.
struct GSmemHeapDesc;
struct GSmemCell {
    GSmemCell* prev;
    GSmemCell* next;
    int size;
    unsigned char* area;
    unsigned short layer;
    void clear();
    void init(int size);
    void* get_area(GSmemHeapDesc* heap);
    inline int getSize() { return size; }
    inline unsigned char* getArea() { return area; }
    inline unsigned char* getEnd() { return area + size; }
    inline void setArea(unsigned char* address) { area = address; }
    inline GSmemCell* getNext() { return next; }
};
struct GSmemHeapDesc {
    int size;
    GSmemCell* free;
    GSmemCell* allocated;
    int type;
    int method;
    int externalMode;
    GSmemCell* cells;
    int cellCount;
    GSmemCell* spare;
    int reserved[2]; // The original allocator leaves these fields untouched.
    bool failedAllocation;
    int getHeaderSize();
    GSmemCell* createNewCell();
    void addfreeCellList(GSmemCell* cell);
    GSmemCell* searchAllocCell(void* pointer);
};
typedef char GSmemCellSizeCheck[sizeof(GSmemCell) == 20 ? 1 : -1];
typedef char GSmemHeapDescSizeCheck[sizeof(GSmemHeapDesc) == 48 ? 1 : -1];
#endif
