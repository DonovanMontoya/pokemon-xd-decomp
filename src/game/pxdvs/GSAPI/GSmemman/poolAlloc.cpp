#include "game/pxdvs/GSAPI/GSmemman/poolAlloc.hpp"

static unsigned long _getDabr() { return 0; }
static void _setDabr(unsigned long) {}

GSmemPoolAllocator _poolArea[32];

void GSmemPoolAllocator::init(register unsigned long count, register unsigned long size) {
    size = (size + 7) & ~3UL;
    capacity = count;
    cellSize = size;
    start = (unsigned char*)GSmemAllocClr((count + 1) * size);
    end = start + count * size;
    free = (Cell*)start;
    register Cell* cell = (Cell*)start;
    register unsigned long i;
    register Cell* previous = 0;
    for (i = 0; i < count; i++) {
        register Cell* next = (Cell*)((unsigned char*)cell + size);
        previous = cell;
        cell->next = next;
        cell = next;
    }
    previous->next = 0;
}

void* GSmemPoolAllocator::allocCell() {
    register Cell* cell = free;
    register unsigned long dabr = _getDabr();
    _setDabr(0);
    if (cell) {
        free = cell->next;
    } else {
        _setDabr(dabr);
        return 0;
    }
    _setDabr(dabr);
    memset(cell, 0, cellSize);
    ++used;
    if (used > peak) peak = used;
    return cell + 1;
}

void GSmemPoolAllocator::freeCell(register void* pointer) {
    if (pointer) {
        pointer = (unsigned char*)pointer - sizeof(Cell);
        register Cell* cell = (Cell*)pointer;
        cell->next = free;
        --used;
        register unsigned long dabr = _getDabr();
        _setDabr(0);
        free = cell;
        _setDabr(dabr);
    }
}

unsigned long GSmemPoolAllocator::getFreeCell() const { return capacity - used; }

bool GSmemPoolAllocator::isRegistration(register void* pointer) {
    if (!pointer) return false;
    if ((unsigned char*)pointer >= start && (unsigned char*)pointer < end) return true;
    return false;
}

void GSmemPoolAllocator::dump() {}

void GSmemInitPool() { memset(_poolArea, 0, sizeof(_poolArea)); }

GSmemPoolAllocator* GSmemCreatePool(unsigned long count, unsigned long size) {
    register int i;
    for (i = 0; i < 32; i++) {
        if (!_poolArea[i].capacity) break;
    }
    if (_poolArea[i].capacity) return 0;
    _poolArea[i].init(count, size);
    return &_poolArea[i];
}

void* GSmemAllocPool(GSmemPoolAllocator* pool) {
    register void* pointer = pool->allocCell();
    return pointer;
}
void GSmemFreePool(GSmemPoolAllocator* pool, register void* pointer) {
    if (pointer) pool->freeCell(pointer);
}
bool GSmemIsRegistrationPool(GSmemPoolAllocator* pool, void* pointer) {
    return pool->isRegistration(pointer);
}
void GSmemDumpPool(register GSmemPoolAllocator* pool) {
    if (pool) {
        pool->dump();
    } else {
        for (register int i = 0; i < 32; i++) {
            if (_poolArea[i].capacity) _poolArea[i].dump();
        }
    }
}
unsigned long GSmemGetFreePool(register GSmemPoolAllocator* pool) {
    if (pool) return pool->getFreeCell();
    return 0;
}
