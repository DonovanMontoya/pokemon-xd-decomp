#include "game/pxdvs/GSAPI/GSmemman/OSAlloc.hpp"

extern "C" void OSReport(const char*, ...);
extern "C" void* memset(void*, int, unsigned long);
extern "C" unsigned short GSmemGetCurrentLayer();
extern "C" { volatile int __OSCurrHeap = -1; }
static GSmemHeapDesc* HeapArray;
static int NumHeaps;
static void* ArenaStart;
static void* ArenaEnd;
static bool _allocFillMode;
static bool _freeFillMode;


// SDK heap dump formats retained in the release object.
#pragma force_active on
static const char dumpFormat0[] = "\nOSDumpHeap(%d):\n";
static const char dumpFormat1[] = "--------Inactive\n";
static const char dumpFormat2[] = "addr\tend\tsize\tprev\tnext\n";
static const char dumpFormat3[] = "--------Allocated\n";
static const char dumpFormat4[] = "%08xh\t%08xh\t%x\t%08xh\t%08xh\n";
static const char dumpFormat5[] = "--------Free\n";
#pragma force_active reset

static GSmemCell* DLAddFront(GSmemCell*, GSmemCell*);
static GSmemCell* DLExtract(GSmemCell*, GSmemCell*);
static GSmemCell* DLInsert(GSmemCell*, GSmemCell*, GSmemHeapDesc*);

int GSmemHeapDesc::getHeaderSize() { if (type == 0) return 32; return 0; }
GSmemCell* GSmemHeapDesc::createNewCell() {
    register GSmemCell* cell = spare;
    register GSmemCell* head;
    register GSmemCell* current;
    register GSmemCell* next;
    if (cell) {
        head = spare;
        current = head;
        next = current->next;
        spare = next;
        if (spare) spare->prev = 0;
    }
    return cell;
}
void GSmemHeapDesc::addfreeCellList(register GSmemCell* cell) {
    if (cell && cell->size == 0) {
        cell->prev = 0; cell->next = 0;
        if (spare == 0) spare = cell;
        else spare = DLAddFront(spare, cell);
    }
}
GSmemCell* GSmemHeapDesc::searchAllocCell(void* pointer) {
    register GSmemCell* cell;
    for (cell = allocated; cell; cell = cell->getNext()) {
        if (cell->get_area(this) == pointer) return cell;
    }
    return 0;
}
void GSmemCell::clear() { prev = 0; next = 0; size = 0; }
void GSmemCell::init(int bytes) { clear(); size = bytes; }
void* GSmemCell::get_area(GSmemHeapDesc* heap) {
    register unsigned char* start = area;
    return start + heap->getHeaderSize();
}
static GSmemCell* DLAddFront(GSmemCell* list, GSmemCell* cell) {
    cell->next = list; cell->prev = 0;
    if (list) list->prev = cell;
    return cell;
}
static GSmemCell* DLExtract(GSmemCell* list, GSmemCell* cell) {
    if (cell->next) cell->next->prev = cell->prev;
    if (cell->prev == 0) return cell->next;
    cell->prev->next = cell->next;
    return list;
}
static GSmemCell* DLInsert(register GSmemCell* list, register GSmemCell* cell, register GSmemHeapDesc* heap) {
    register GSmemCell* prev;
    register GSmemCell* next;
    register GSmemCell* discarded;
    for (next = list, prev = 0; next; prev = next, next = next->next) {
        if (cell->getArea() <= next->getArea()) break;
    }
    cell->next = next; cell->prev = prev;
    if (next) {
        next->prev = cell;
        if (cell->getEnd() == next->getArea()) {
            cell->size += next->size;
            discarded = next;
            next = next->next;
            cell->next = next;
            if (next) next->prev = cell;
            discarded->size = 0;
            if (heap && heap->type == 1) heap->addfreeCellList(discarded);
        }
    }
    if (prev) {
        prev->next = cell;
        if (prev->getEnd() == cell->getArea()) {
            prev->size += cell->size;
            discarded = cell;
            prev->next = next;
            if (next) next->prev = prev;
            discarded->size = 0;
            if (heap && heap->type == 1) heap->addfreeCellList(discarded);
        }
        return list;
    }
    return cell;
}
extern "C" void* OSAllocFromHeap(int heap, register unsigned long size) {
    register GSmemHeapDesc* hd;
    register GSmemCell* cell;
    register GSmemCell* newCell;
    register GSmemCell* search;
    register int largest;
    register unsigned long leftover;
    hd = &HeapArray[heap];
    size += hd->getHeaderSize();
    size = (size + 31) & ~31UL;
    if (hd->method == 1) {
        search = hd->free; cell = 0;
        for (; search; search = search->next) {
            if ((int)size <= search->getSize()) {
                if ((int)size == search->getSize()) { cell = search; break; }
                if (cell) {
                    if (search->getSize() < cell->getSize()) cell = search;
                } else cell = search;
            }
        }
    } else if (hd->method == 3) {
        search = hd->free;
        largest = -1;
        cell = 0;
        for (; search; search = search->getNext()) {
            if (largest <= search->getSize()) { largest = search->size; cell = search; }
        }
        if ((int)size > largest) cell = 0;
    } else if (hd->method == 3) {
        // Preserve the duplicated method test in the original allocator.
        search = hd->free;
        cell = 0;
        for (; search; search = search->getNext()) {
            if ((int)size <= search->size && cell < search) cell = search;
        }
    } else {
        for (cell = hd->free; cell; cell = cell->next) {
            if ((int)size <= cell->size) break;
        }
    }
    if (!cell) { hd->failedAllocation = true; return 0; }
    leftover = cell->size - size;
    if (leftover < 64) hd->free = DLExtract(hd->free, cell);
    else {
        if (hd->method == 3 && hd->type == 0) {
            newCell = cell;
            cell = (GSmemCell*)((unsigned char*)cell + leftover);
            newCell->size = leftover;
            cell->init(size); cell->area = (unsigned char*)cell;
        } else {
            if (hd->type == 1) {
                newCell = hd->createNewCell();
                if (!newCell) {
                    OSReport("OSAllocFromHeap: Warning- not free cell\n");
                    hd->failedAllocation = true; return 0;
                }
                cell->size = size;
                newCell->init(leftover);
                newCell->setArea(cell->getEnd());
            } else {
                newCell = (GSmemCell*)((unsigned char*)cell + size);
                cell->size = size; newCell->init(leftover);
                newCell->area = (unsigned char*)newCell;
            }
            newCell->prev = cell->prev; newCell->next = cell->next;
            if (newCell->next) newCell->next->prev = newCell;
            if (newCell->prev) newCell->prev->next = newCell;
            else hd->free = newCell;
        }
    }
    hd->allocated = DLAddFront(hd->allocated, cell);
    cell->layer = GSmemGetCurrentLayer();
    hd->failedAllocation = false;
    return cell->get_area(hd);
}
extern "C" void OSFreeToHeap(int heap, register void* pointer) {
    register GSmemHeapDesc* hd = &HeapArray[heap];
    register GSmemCell* cell;
    if (hd->type == 0) {
        if (!pointer) return;
        cell = (GSmemCell*)((unsigned char*)pointer - 32);
    } else cell = hd->searchAllocCell(pointer);
    hd->allocated = DLExtract(hd->allocated, cell);
    hd->free = DLInsert(hd->free, cell, hd);
}
extern "C" int OSShrinkHeap(int heap, register void* pointer, register unsigned long size) {
    register GSmemHeapDesc* hd;
    register GSmemCell* cell;
    register GSmemCell* newCell;
    register unsigned long leftover;
    if (size == 0) return 0;
    hd = &HeapArray[heap];
    size += hd->getHeaderSize(); size = (size + 31) & ~31UL;
    if (hd->type == 0) {
        if (!pointer) return 0;
        cell = (GSmemCell*)((unsigned char*)pointer - 32);
    } else cell = hd->searchAllocCell(pointer);
    int originalSize;
    originalSize = cell->getSize();
    leftover = cell->getSize() - size;
    if (leftover < 64) return 1;
    if (hd->type == 1) {
        newCell = hd->createNewCell();
        if (!newCell) return 0;
        cell->size = size; newCell->area = (unsigned char*)newCell;
    } else {
        newCell = (GSmemCell*)(cell->getArea() + size);
        cell->size = size;
        register unsigned char* end = cell->getEnd();
        newCell->area = end;
    }
    newCell->init(leftover);
    hd->free = DLInsert(hd->free, newCell, hd);
    return 1;
}
extern "C" int OSSetCurrentHeap(int heap) {
    register int previous = __OSCurrHeap; __OSCurrHeap = heap; return previous;
}
extern "C" void* OSInitAlloc(register void* start, register void* end, register int maxHeaps) {
    register unsigned long arraySize;
    register int i;
    register GSmemHeapDesc* hd;
    OSReport("OSInitAlloc : arenaStart=%08xh, arenaEnd=%08xh, maxHeaps %d\n", start, end, maxHeaps);
    arraySize = maxHeaps * sizeof(GSmemHeapDesc);
    HeapArray = (GSmemHeapDesc*)start; NumHeaps = maxHeaps;
    for (i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i]; hd->size = -1;
        hd->free = hd->allocated = 0;
        hd->type = 0; hd->externalMode = 0; hd->method = 0;
        hd->cells = 0; hd->cellCount = 0; hd->failedAllocation = false;
    }
    __OSCurrHeap = -1;
    start = (unsigned char*)HeapArray + arraySize;
    start = (void*)(((unsigned long)start + 31) & ~31UL);
    ArenaStart = start; ArenaEnd = (void*)((unsigned long)end & ~31UL);
    _allocFillMode = false; _freeFillMode = false;
    return start;
}
extern "C" int OSCreateHeap(register void* start, register void* end) {
    register int heap;
    register GSmemHeapDesc* hd;
    register GSmemCell* cell;
    OSReport("OSCreateHeap : start=%08xh, end=%08xh\n", start, end);
    start = (void*)(((unsigned long)start + 31) & ~31UL);
    end = (void*)((unsigned long)end & ~31UL);
    for (heap = 0; heap < NumHeaps; heap++) {
        hd = &HeapArray[heap];
        if (hd->size < 0) {
            hd->size = (unsigned char*)end - (unsigned char*)start;
            cell = (GSmemCell*)start; cell->init(hd->size);
            cell->area = (unsigned char*)cell;
            hd->free = cell; hd->allocated = 0; hd->failedAllocation = false;
            return heap;
        }
    }
    return -1;
}
extern "C" int OSCreateExternalHeap(register void* start, register void* end, register GSmemCell* cells, register int count) {
    register int heap;
    register GSmemHeapDesc* hd;
    register GSmemCell* cell;
    start = (void*)(((unsigned long)start + 31) & ~31UL);
    end = (void*)((unsigned long)end & ~31UL);
    memset(cells, 0, count * sizeof(GSmemCell));
    for (heap = 0; heap < NumHeaps; heap++) {
        hd = &HeapArray[heap];
        if (hd->size < 0) {
            hd->size = (unsigned char*)end - (unsigned char*)start;
            hd->method = 0; hd->cells = cells; hd->cellCount = count;
            hd->type = 1; hd->externalMode = 1;
            cell = hd->cells; cell->init(hd->size); cell->area = (unsigned char*)start;
            hd->free = cell; hd->allocated = 0; hd->spare = 0;
            for (register int i = 0; i < count; i++) hd->addfreeCellList(&cells[i]);
            return heap;
        }
    }
    return -1;
}
extern "C" void OSDestroyHeap(int heap) {
    register GSmemHeapDesc* hd = &HeapArray[heap]; hd->size = -1;
}
#define NULL 0
#define ALIGNMENT 32
#define MINOBJSIZE 64UL
#define OFFSET(value, alignment) ((unsigned long)(value) & ((alignment) - 1))
#define InRange(cell, start, end) ((unsigned long)(start) <= (unsigned long)(cell) && (unsigned long)(cell) < (unsigned long)(end))
#define CHECK_CELLALIGN(hd, cell) ((hd)->type == 1 || ((hd)->type == 0 && OFFSET(cell, ALIGNMENT) == 0))
#define ASSERTREPORT(line, message, cond) if (!(cond)) { OSReport(message, line); return -1; }
extern "C" int OSCheckHeap(register int heap) {
    register GSmemHeapDesc* hd;
    register GSmemCell* cell;
    register int total = 0;
    register int free = 0;
    ASSERTREPORT(0x645, "OSCheckHeap: Failed HeapArray in %d", HeapArray);
    ASSERTREPORT(0x646, "OSCheckHeap: Failed 0 <= heap && heap < NumHeaps in %d", 0 <= heap && heap < NumHeaps);
    hd = &HeapArray[heap];
    ASSERTREPORT(0x649, "OSCheckHeap: Failed 0 <= hd->size in %d", 0 <= hd->size);
    ASSERTREPORT(0x64b, "OSCheckHeap: Failed hd->allocated == NULL || hd->allocated->prev == NULL in %d", hd->allocated == NULL || hd->allocated->prev == NULL);
    for (cell = hd->allocated; cell; cell = cell->next) {
        if (hd->type == 0) {
            ASSERTREPORT(0x64f, "OSCheckHeap: Failed InRange(cell, ArenaStart, ArenaEnd) in %d", InRange(cell, ArenaStart, ArenaEnd));
            ASSERTREPORT(0x650, "OSCheckHeap: Failed CHECK_CELLALIGN( hd, cell) in %d", CHECK_CELLALIGN( hd, cell));
        }
        ASSERTREPORT(0x652, "OSCheckHeap: Failed cell->next == NULL || cell->next->prev == cell in %d", cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(0x653, "OSCheckHeap: Failed MINOBJSIZE <= cell->size in %d", MINOBJSIZE <= cell->size);
        ASSERTREPORT(0x654, "OSCheckHeap: Failed OFFSET(cell->size, ALIGNMENT) == 0 in %d", OFFSET(cell->size, ALIGNMENT) == 0);
        total += cell->size;
        ASSERTREPORT(0x657, "OSCheckHeap: Failed 0 < total && total <= hd->size in %d", 0 < total && total <= hd->size);
    }
    ASSERTREPORT(0x65f, "OSCheckHeap: Failed hd->free == NULL || hd->free->prev == NULL in %d", hd->free == NULL || hd->free->prev == NULL);
    for (cell = hd->free; cell; cell = cell->next) {
        if (hd->type == 0) {
            ASSERTREPORT(0x663, "OSCheckHeap: Failed InRange(cell, ArenaStart, ArenaEnd) in %d", InRange(cell, ArenaStart, ArenaEnd));
            ASSERTREPORT(0x664, "OSCheckHeap: Failed CHECK_CELLALIGN(hd, cell ) in %d", CHECK_CELLALIGN(hd, cell ));
            ASSERTREPORT(0x665, "OSCheckHeap: Failed cell->next == NULL || (char*) cell + cell->size < (char*) cell->next in %d", cell->next == NULL || (char*) cell + cell->size < (char*) cell->next);
        }
        ASSERTREPORT(0x667, "OSCheckHeap: Failed cell->next == NULL || cell->next->prev == cell in %d", cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(0x668, "OSCheckHeap: Failed MINOBJSIZE <= cell->size in %d", MINOBJSIZE <= cell->size);
        ASSERTREPORT(0x669, "OSCheckHeap: Failed OFFSET(cell->size, ALIGNMENT) == 0 in %d", OFFSET(cell->size, ALIGNMENT) == 0);
        total += cell->size;
        free += cell->size - hd->getHeaderSize();
        ASSERTREPORT(0x66d, "OSCheckHeap: Failed 0 < total && total <= hd->size in %d", 0 < total && total <= hd->size);
    }
    ASSERTREPORT(0x674, "OSCheckHeap: Failed total == hd->size in %d", total == hd->size);
    return free;
}
extern "C" unsigned long OSReferentSize(void* pointer) {
    register GSmemCell* cell = (GSmemCell*)((unsigned char*)pointer - 32);
    return cell->size - 32;
}
extern "C" int GSmemVisitHeapAllocated(register int heap, register void (*visitor)(void*, unsigned long, void*, void*), void* user1, void* user2) {
    register GSmemCell* cell;
    register int count = 0;
    if (HeapArray[heap].size <= 0 || !visitor) return 0;
    if (HeapArray[heap].size >= 0) {
        for (cell = HeapArray[heap].allocated; cell; cell = cell->next) {
            if (visitor) visitor(cell->get_area(&HeapArray[heap]), cell->size, user1, user2);
            count++;
        }
    }
    return count;
}
extern "C" unsigned long OSGetHeapSize(int heap) {
    register GSmemHeapDesc* hd;
    if (heap < 0 || heap >= NumHeaps) return 0;
    hd = &HeapArray[heap]; return hd->size;
}
extern "C" int OSGetHeapFreeSize(int heap, unsigned long* total, unsigned long* largest) {
    register GSmemCell* cell;
    register int sum = 0;
    register int max = 0;
    register GSmemHeapDesc* hd;
    if (heap < 0 || heap >= NumHeaps) {
        if (total) *total = 0;
        if (largest) *largest = 0;
        return 0;
    }
    hd = &HeapArray[heap];
    for (cell = hd->free; cell; cell = cell->next) {
        sum += cell->size;
        if (cell->size > max) max = cell->size;
    }
    if (total) *total = sum;
    if (largest) *largest = max;
    return 1;
}
extern "C" int OSGetHeapType(int heap) {
    register GSmemHeapDesc* hd = &HeapArray[heap]; return hd->type;
}
extern "C" int OSSetAllocMethodHeap(int heap, int method) {
    register GSmemHeapDesc* hd = &HeapArray[heap];
    register int previous = hd->method; hd->method = method; return previous;
}
extern "C" void GSmemDumpHeapInfo() {}
