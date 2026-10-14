#include <game/pxdvs/GSAPI/GSfsys/fsysCache.hpp>
#include <game/pxdvs/GSAPI/GSfsys/fsysAlloc.hpp>
#include <game/pxdvs/GSAPI/GSmemman/GSmemman.hpp>
#include <game/pxdvs/GSAPI/GSmemman/OSAlloc.hpp>
#include <dolphin/os.h>
#include <dolphin/arq.h>
struct GSfsysARQTransfer {
    GSfsysARQTransfer *previous, *next;
    u8 inUse, reserved[3];
    ARQRequest request;
    ARQCallback callback;
    void* context;
    u32 identifier, extra[3];
    void* destination;
    u32 length;
};
typedef char GSfsysARQSizeCheck[sizeof(GSfsysARQTransfer) == 0x4c ? 1 : -1];
static GSmemCell _fsysAmemCell[512];
static GSfsysCache *_fsysCACHEManage, *_fsysCACHEManageRoot;
static GSfsysARQTransfer *_fsysARQTrans, *_fsysARQTransRoot;
static u32 _fsysAmemTopAddr;
static s32 _fsysAmemHeap;
static u32 _fsysARQTransIndex, _fsysARQTransSize, _fsysCACHEFreeBytes;
static u32 _fsysCACHEuniqueID, _fsysCACHEuniqueGroupID, _fsysCACHEManageIndex, _fsysCACHEManageSize, _fsysCACHESize;
extern "C" {
void* _fsysDoMalloc(u32);
void _fsysDelTAG(void*, void*);
void _fsysAddTAG(void*, void*);
}
#pragma dont_inline on
extern "C" {
static void _fsysAddCacheManage(GSfsysCache*);
static GSfsysARQTransfer* _fsysGetNewArq();
static void _fsysAddArq(GSfsysARQTransfer*);
static void _fsysDelARQTrans(GSfsysARQTransfer*);
GSfsysARQTransfer* _fsysArq2ArqTrans(u32);
static void _fsysARQCallbackWrite(u32);
static void _fsysARQCallbackRead(u32);
}
extern "C" {
u8 _fsysCheckCache(u32 group, u32 identifier) { return _fsysGetCacheManage(group, identifier) != 0; }
void _fsysIncCacheUniqueGroupID() { ++_fsysCACHEuniqueGroupID; }
s32 _fsysInitCache(u32 cacheSize, u32 entryCount) {
    _fsysCACHEManageRoot = 0;
    _fsysCACHEManageIndex = 0;
    _fsysCACHEuniqueGroupID = 0;
    _fsysCACHEuniqueID = 0;
    _fsysCACHEFreeBytes = 0;
    _fsysARQTransRoot = 0;
    _fsysARQTransIndex = 0;
    _fsysCACHESize = cacheSize;
    if (!cacheSize) _fsysCACHESize = 0xa00000;
    _fsysCACHEManageSize = entryCount;
    _fsysCACHESize = (_fsysCACHESize + 31) & ~31;
    if (!entryCount) _fsysCACHEManageSize = 512;
    _fsysARQTransSize = 8;
    if (!_fsysInitCacheHeap(_fsysCACHESize)) return 0;
    _fsysCACHEManage = (GSfsysCache*)_fsysDoMalloc(_fsysCACHEManageSize * sizeof(GSfsysCache));
    if (!_fsysCACHEManage) return 0;
    _fsysARQTrans = (GSfsysARQTransfer*)_fsysDoMalloc(_fsysARQTransSize * sizeof(GSfsysARQTransfer));
    if (!_fsysARQTrans) return 0;
    for (u32 i = 0; i < _fsysCACHEManageSize; ++i) {
        _fsysCACHEManage[i].inUse = 0;
        _fsysCACHEManage[i].persistent = 0;
        _fsysCACHEManage[i].locked = 0;
    }
    for (u32 i = 0; i < _fsysARQTransSize; ++i) _fsysARQTrans[i].inUse = 0;
    return 1;
}
s32 _fsysGetFreeCacheHeapSize() { return 0xa00000 - _fsysCACHEFreeBytes; }
void _fsysFreeCacheFromHeap(void* data, u32 size) { GSmemFreeHeap(_fsysAmemHeap, data); _fsysCACHEFreeBytes -= size; }
void* _fsysAllocCacheFromHeap(u32 size) {
    void* result = GSmemAllocHeap(_fsysAmemHeap, size);
    if (result) _fsysCACHEFreeBytes += size;
    return result;
}
u8 _fsysInitCacheHeap(u32 size) { return size <= 0xa00000; }
u32 GSfsysCreateCacheHeap() {
    _fsysAmemTopAddr = 0x600000;
    _fsysAmemHeap = GSmemCreateExternalHeap((void*)0x600000, (void*)0x1000000, _fsysAmemCell, 512);
    return _fsysAmemHeap != -1;
}
void _fsysSetLockCacheFlagGroup(u32 group, u8 locked) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysCache* entry = _fsysCACHEManageRoot;
    while (entry) {
        if (entry->group == group) entry->locked = locked;
        entry = entry->next;
    }
    OSRestoreInterrupts(interrupts);
}
void _fsysSetLockCacheFlag(u32 group, u32 identifier, u8 locked) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysCache* entry = _fsysGetCacheManage(group, identifier);
    if (entry) entry->locked = locked;
    OSRestoreInterrupts(interrupts);
}
GSfsysCache* _fsysGetFreshCacheManage(u32 group, u8 wholeGroup) {
    GSfsysCache* entry = _fsysCACHEManageRoot;
    GSfsysCache* result = 0;
    while (entry) {
        if (entry->persistent != 1 && entry->locked != 1 && entry->group != group) {
            if (!result) result = entry;
            else if (result->freshness >= entry->freshness) {
                if (!wholeGroup) { if (result->sequence < entry->sequence) result = entry; }
                else result = entry;
            }
        }
        entry = entry->next;
    }
    return result;
}
GSfsysCache* _fsysGetCacheManageAddr(void* address) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysCache* entry = _fsysCACHEManageRoot;
    while (entry) { if (entry->data == address) break; entry = entry->next; }
    OSRestoreInterrupts(interrupts);
    return entry;
}
GSfsysCache* _fsysGetCacheManageGroup(u32 group) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysCache* entry = _fsysCACHEManageRoot;
    while (entry) { if (entry->group == group) break; entry = entry->next; }
    OSRestoreInterrupts(interrupts);
    return entry;
}
GSfsysCache* _fsysGetCacheManage(u32 group, u32 identifier) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysCache* entry = _fsysCACHEManageRoot;
    while (entry) { if (entry->group == group && entry->identifier == identifier) break; entry = entry->next; }
    OSRestoreInterrupts(interrupts);
    return entry;
}
void _fsysDelCacheManage(GSfsysCache* entry) { _fsysDelTAG(entry, &_fsysCACHEManageRoot); }
}
extern "C" static void _fsysAddCacheManage(GSfsysCache* entry) { _fsysAddTAG(entry, &_fsysCACHEManageRoot); }
#pragma dont_inline reset

#pragma dont_inline on
extern "C" {
GSfsysCache* _fsysGetNewCacheManage(u32 group, u32 identifier, u8 persistent, u8 locked, u32 freshness) {
    GSfsysCache* result = 0;
    BOOL interrupts = OSDisableInterrupts();
    GSfsysCache* entry;
    u32 index = _fsysCACHEManageIndex;
    while (!result) {
        entry = &_fsysCACHEManage[index];
        if (!entry->inUse) {
            entry->previous = 0;
            result = entry;
            entry->next = 0;
            entry->inUse = 1;
            entry->persistent = persistent;
            entry->locked = locked;
            entry->group = group;
            entry->identifier = identifier;
            entry->data = 0;
            entry->length = 0;
            entry->freshness = freshness;
            entry->sequence = _fsysCACHEuniqueID;
            ++_fsysCACHEuniqueID;
        }
        ++index;
        if (index >= _fsysCACHEManageSize) index = 0;
        if (index == _fsysCACHEManageIndex) {
            // The original exhausted-pool path returns the saved interrupt state.
            return (GSfsysCache*)interrupts;
        }
    }
    _fsysCACHEManageIndex = index;
    _fsysAddCacheManage(result);
    OSRestoreInterrupts(interrupts);
    return result;
}
GSfsysARQTransfer* _fsysArq2ArqTrans(u32 request) {
    GSfsysARQTransfer* transfer = _fsysARQTransRoot;
    while (transfer) {
        if ((u32)&transfer->request == request) return transfer;
        transfer = transfer->next;
    }
    return 0;
}
static void _fsysDelARQTrans(GSfsysARQTransfer* transfer) { _fsysDelTAG(transfer, &_fsysARQTransRoot); }
static GSfsysARQTransfer* _fsysGetNewArq() {
    GSfsysARQTransfer* result = 0;
    GSfsysARQTransfer* transfer;
    u32 index = _fsysARQTransIndex;
    BOOL interrupts = OSDisableInterrupts();
    while (!result) {
        transfer = &_fsysARQTrans[index];
        if (!transfer->inUse) {
            transfer->previous = 0;
            result = transfer;
            transfer->next = 0;
            transfer->inUse = 1;
            transfer->callback = 0;
            transfer->context = 0;
            transfer->identifier = 0;
            transfer->extra[0] = 0;
            transfer->extra[1] = 0;
            transfer->extra[2] = 0;
            transfer->destination = 0;
            transfer->length = 0;
        }
        ++index;
        if (index >= _fsysARQTransSize) index = 0;
        if (index == _fsysARQTransIndex) break;
    }
    _fsysARQTransIndex = index;
    _fsysAddArq(result);
    OSRestoreInterrupts(interrupts);
    return result;
}
static void _fsysAddArq(GSfsysARQTransfer* transfer) { _fsysAddTAG(transfer, &_fsysARQTransRoot); }
static void _fsysARQCallbackWrite(u32 request) {
    GSfsysARQTransfer* transfer = _fsysArq2ArqTrans(request);
    if (transfer) {
        if (transfer->callback) transfer->callback(request);
        _fsysDelARQTrans(transfer);
    }
}
static void _fsysARQCallbackRead(u32 request) {
    GSfsysARQTransfer* transfer = _fsysArq2ArqTrans(request);
    if (transfer) {
        DCInvalidateRange(transfer->destination, transfer->length);
        if (transfer->callback) transfer->callback(request);
        _fsysDelARQTrans(transfer);
    }
}
}
typedef GSfsysRequest GSfsysCacheRequest;
extern "C" {
void _fsysWriteCache(GSfsysCacheRequest* request, u32 identifier, void* source, u32 destination, u32 length, u32 offset, ARQCallback callback) {
    GSfsysARQTransfer* transfer = _fsysGetNewArq();
    if (!transfer) return;
    transfer->context = request;
    transfer->identifier = identifier;
    transfer->callback = callback;
    s32 priority = request->state == 4;
    DCFlushRange(source, length);
    ARQPostRequest(&transfer->request, request->group, 0, priority, (u32)source, destination + offset, length, _fsysARQCallbackWrite);
}
static u8 _fsysReadCacheExec(GSfsysCacheRequest* request, u32 identifier, void* destination, u32 length, u32 offset, ARQCallback callback, u32 first, u32 second, u32 third) {
    GSfsysCache* entry = _fsysGetCacheManage(request->group, request->identifier);
    if (!entry) return 0;
    GSfsysARQTransfer* transfer = _fsysGetNewArq();
    if (!transfer) return 0;
    transfer->context = request;
    transfer->identifier = identifier;
    transfer->callback = callback;
    transfer->extra[0] = first;
    transfer->extra[1] = second;
    transfer->extra[2] = third;
    s32 priority = request->state == 4;
    if (offset + length > entry->length) length = entry->length - offset;
    if (!((u32)destination & 31) && !(length & 31)) {
        DCInvalidateRange(destination, length);
        transfer->destination = destination;
        transfer->length = length;
        ARQPostRequest(&transfer->request, request->group, 1, priority, (u32)entry->data + offset, (u32)destination, length, _fsysARQCallbackRead);
        return 1;
    }
    return (u8)(u32)transfer;
}
u8 _fsysReadCacheEX(GSfsysCacheRequest* request, u32 identifier, void* destination, u32 length, u32 offset, ARQCallback callback, u32 first, u32 second, u32 third) {
    return _fsysReadCacheExec(request, identifier, destination, length, offset, callback, first, second, third);
}
u8 _fsysReadCache(GSfsysCacheRequest* request, u32 identifier, void* destination, u32 length, u32 offset, ARQCallback callback) {
    return _fsysReadCacheExec(request, identifier, destination, length, offset, callback, 0, 0, 0);
}
}
#pragma dont_inline reset
