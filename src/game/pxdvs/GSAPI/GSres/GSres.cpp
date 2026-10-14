#include <game/pxdvs/GSAPI/GSres/GSres.hpp>
#include <game/pxdvs/GSAPI/GSmemman/GSmemman.hpp>
extern "C" void GSlogWrite(const char*, ...);
struct _resEntry {
    u8 allocated, locked, unique, reserved;
    void* resource;
    unsigned long group, identifier;
    GSresFreeCallback freeCallback;
    _resEntry *next, *previous;
};
typedef char GSresEntrySizeCheck[sizeof(_resEntry) == 0x1c ? 1 : -1];
static _resEntry* _resStructList;
static GSmemPoolAllocator* _resEntryAllocator;
#pragma dont_inline on
static _resEntry* resFindResource(unsigned long, unsigned long);
static _resEntry* resFreeResource(_resEntry*, bool);
extern "C" {
void GSresIsUniqueID(unsigned long group, unsigned long identifier, u8 unique) {
    _resEntry* entry = resFindResource(group, identifier);
    if (entry) entry->unique = unique;
}
void GSresUnlockResource(unsigned long group, unsigned long identifier) {
    _resEntry* entry = resFindResource(group, identifier);
    if (entry) entry->locked = 0;
}
void GSresLockResource(unsigned long group, unsigned long identifier) {
    _resEntry* entry = resFindResource(group, identifier);
    if (entry) entry->locked = 1;
}
void GSresDumpGroup(unsigned long group) {
    _resEntry* entry = _resStructList;
    GSmemDumpPool(_resEntryAllocator);
    GSlogWrite("alloc registMem   grpID resID      freeFunc\n");
    GSlogWrite("-----------------------------------------------\n");
    while (entry) {
        if (entry->group == group || group == ~0UL) {
            s8 mark = ' ';
            if (entry->allocated) mark = 'o';
            GSlogWrite("  %c   0x%08x  %04d  0x%08x 0x%08x\n", mark, entry->resource, entry->group, entry->identifier, entry->freeCallback);
        }
        entry = entry->next;
    }
}
void GSresDumpAll() { GSresDumpGroup(~0UL); }
void GSresFreeGroup(unsigned long group) {
    _resEntry* entry = _resStructList;
    while (entry) {
        _resEntry* next;
        if (entry->group == group) next = resFreeResource(entry, true);
        else next = entry->next;
        entry = next;
    }
}
void GSresFreeResource(unsigned long group, unsigned long identifier) {
    _resEntry* entry = resFindResource(group, identifier);
    if (entry) resFreeResource(entry, true);
}
void GSresFreeResourceAllGroup(unsigned long identifier) {
    _resEntry* entry = _resStructList;
    while (entry) {
        if (entry->unique && entry->identifier == identifier) { resFreeResource(entry, true); return; }
        entry = entry->next;
    }
}
void* GSresGetResourceAllGroup(unsigned long identifier) {
    _resEntry* entry = _resStructList;
    while (entry) {
        if (entry->unique && entry->identifier == identifier && !entry->locked) return entry->resource;
        entry = entry->next;
    }
    return 0;
}
void* GSresGetResource(unsigned long group, unsigned long identifier) {
    _resEntry* entry = resFindResource(group, identifier);
    if (!entry || entry->locked) return 0;
    return entry->resource;
}
void GSresChangeResourceAdress(void* resource, unsigned long group, unsigned long identifier, GSresFreeCallback callback) {
    _resEntry* entry = resFindResource(group, identifier);
    if (!entry) { if (resource) GSresRegisterResource(resource, group, identifier, callback); }
    else {
        if (!resource) { resFreeResource(entry, true); return; }
        resFreeResource(entry, false);
        entry->allocated = 0;
        entry->resource = resource;
        entry->freeCallback = callback;
    }
}
void GSresRegisterResource(void* resource, unsigned long group, unsigned long identifier, GSresFreeCallback callback) {
    _resEntry* entry = resFindResource(group, identifier);
    if (!resource) { if (entry) resFreeResource(entry, true); }
    else if (entry) {
        if (!entry->allocated) {
            if (entry->resource != resource) {
                if (entry->freeCallback) entry->freeCallback(entry->resource, group, identifier);
                entry->resource = resource;
            }
            entry->freeCallback = callback;
        }
    } else {
        entry = (_resEntry*)_resEntryAllocator->allocCell();
        if (!entry) { GSlogWrite("GSres: error -- no free pool\n"); return; }
        if (_resStructList) _resStructList->previous = entry;
        entry->next = _resStructList;
        entry->previous = 0;
        _resStructList = entry;
        entry->allocated = 0;
        entry->locked = 0;
        entry->unique = 1;
        entry->resource = resource;
        entry->group = group;
        entry->identifier = identifier;
        entry->freeCallback = callback;
    }
}
void* GSresAllocResourceAlign(unsigned long size, unsigned short alignment, unsigned long group, unsigned long identifier, GSresFreeCallback callback) {
    if (resFindResource(group, identifier)) return 0;
    _resEntry* entry = (_resEntry*)_resEntryAllocator->allocCell();
    if (!entry) { GSlogWrite("GSres: error -- no free pool\n"); return 0; }
    entry->resource = GSmemAllocAlign(size, alignment);
    if (!entry->resource) { _resEntryAllocator->freeCell(entry); return 0; }
    if (_resStructList) _resStructList->previous = entry;
    entry->next = _resStructList;
    entry->previous = 0;
    _resStructList = entry;
    entry->allocated = 1;
    entry->locked = 0;
    entry->unique = 1;
    entry->group = group;
    entry->identifier = identifier;
    entry->freeCallback = callback;
    return entry->resource;
}
void* GSresAllocResource(unsigned long size, unsigned long group, unsigned long identifier, GSresFreeCallback callback) {
    if (resFindResource(group, identifier)) return 0;
    _resEntry* entry = (_resEntry*)_resEntryAllocator->allocCell();
    if (!entry) { GSlogWrite("GSres: error -- no free pool\n"); return 0; }
    entry->resource = GSmemAlloc(size);
    if (!entry->resource) { _resEntryAllocator->freeCell(entry); return 0; }
    if (_resStructList) _resStructList->previous = entry;
    entry->next = _resStructList;
    entry->previous = 0;
    _resStructList = entry;
    entry->allocated = 1;
    entry->locked = 0;
    entry->unique = 1;
    entry->group = group;
    entry->identifier = identifier;
    entry->freeCallback = callback;
    return entry->resource;
}
void GSresInit(unsigned long count) { _resEntryAllocator = GSmemCreatePool(count, sizeof(_resEntry)); }
}
static _resEntry* resFreeResource(_resEntry* entry, bool releaseEntry) {
    if (entry->freeCallback && !entry->freeCallback(entry->resource, entry->group, entry->identifier)) return entry->next;
    if (entry->allocated) {
        if (entry->resource) { GSmemFree(entry->resource); entry->resource = 0; }
        entry->allocated = 0;
    }
    entry->resource = 0;
    _resEntry* next = entry->next;
    if (releaseEntry) {
        if (entry->previous) entry->previous->next = next;
        else _resStructList = next;
        if (next) next->previous = entry->previous;
        _resEntryAllocator->freeCell(entry);
    }
    return next;
}
static _resEntry* resFindResource(unsigned long group, unsigned long identifier) {
    _resEntry* entry = _resStructList;
    while (entry) {
        if (entry->group == group && entry->identifier == identifier) return entry;
        entry = entry->next;
    }
    return 0;
}
#pragma dont_inline reset
