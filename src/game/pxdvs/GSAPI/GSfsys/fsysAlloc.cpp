#include <game/pxdvs/GSAPI/GSfsys/fsysAlloc.hpp>
#include <game/pxdvs/GSAPI/GSfsys/fsysCache.hpp>
#include <game/pxdvs/GSAPI/GSres/GSres.hpp>
#include <game/pxdvs/GSAPI/GSmemman/GSmemman.hpp>
#include <dolphin/os.h>
#include <libc/string.h>
static s32 _fsysLocalHeap;
#pragma dont_inline on
extern "C" {
static u8 _fsysFreeCache(GSfsysCache*);
static u8 _fsysFreeCacheAddr(void*);
static s32 _fsysFreeFreshCache(u32, u32);
static u8 _fsysFreeFreshCacheGroup(u32);
static void* _fsysAllocCache(GSfsysRequest*, u32, u32, u32);
void* _fsysGetResource(u32 size, u32 group, u32 identifier) { return GSresAllocResourceAlign(size, 32, group, identifier, 0); }
u8 _fsysMemFreeCacheGroup(u32 group) {
    GSfsysCache* cache = _fsysGetCacheManageGroup(group);
    if (!cache) return 0;
    return _fsysFreeCache(cache);
}
void _fsysMemFreeCache(void* address) { _fsysFreeCacheAddr(address); }
void* _fsysMemAllocCache(GSfsysRequest* request, u32 identifier, u32 size, u32 freshness) {
    u32 length = (size + 31) & ~31;
    _fsysFreeFreshCache(request->group, length);
    for (;;) {
        void* result = _fsysAllocCache(request, identifier, length, freshness);
        if (result) return result;
        if (!_fsysFreeFreshCacheGroup(request->group)) return 0;
    }
}
static u8 _fsysFreeFreshCacheGroup(u32 group) {
    u32 freshness;
    u8 freed = 0;
    for (;;) {
        GSfsysCache* cache = _fsysGetFreshCacheManage(group, 1);
        if (!cache) return freed;
        if (freed != 1 || freshness == cache->freshness) {
            freshness = cache->freshness;
            freed = 1;
            if (!_fsysFreeCache(cache)) return 0;
        } else return freed;
    }
}
static s32 _fsysFreeFreshCache(u32 group, u32 size) {
    for (;;) {
        if (size < (u32)(_fsysGetFreeCacheHeapSize() - 0x80000)) return 1;
        GSfsysCache* cache = _fsysGetFreshCacheManage(group, 0);
        if (!cache) return 0;
        if (!_fsysFreeCache(cache)) return 0;
    }
}
static u8 _fsysFreeCacheAddr(void* address) {
    GSfsysCache* cache = _fsysGetCacheManageAddr(address);
    if (!cache) return 0;
    return _fsysFreeCache(cache);
}
static u8 _fsysFreeCache(GSfsysCache* cache) {
    void* data = cache->data;
    u32 length = cache->length;
    _fsysDelCacheManage(cache);
    _fsysFreeCacheFromHeap(data, length);
    return 1;
}
static void* _fsysAllocCache(GSfsysRequest* request, u32 identifier, u32 size, u32 freshness) {
    GSfsysCache* cache = _fsysGetCacheManage(request->group, identifier);
    if (!cache) {
        u8 persistent = request->persistent;
        GSfsysHeader* header = _fsysGetHeader(request);
        if (header && (header->flags & 0x40000000)) persistent = 1;
        cache = _fsysGetNewCacheManage(request->group, identifier, persistent, 1, freshness);
        if (!cache) return 0;
        cache->length = size;
        cache->data = _fsysAllocCacheFromHeap(cache->length);
        if (!cache->data) { _fsysDelCacheManage(cache); return 0; }
    }
    return cache->data;
}
void _fsysMemFreeHeader(GSfsysRequest* request) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysHeader* header = request->header;
    request->header = 0;
    request->headerLoaded = 0;
    OSRestoreInterrupts(interrupts);
    _fsysFree(header);
}
s32 _fsysMemAllocHeader(GSfsysRequest* request) {
    if (request->header) return 0;
    request->headerLoaded = 0;
    request->header = (GSfsysHeader*)_fsysAlloc((request->directory->headerLength + 31) & ~31);
    if (!request->header) return 0;
    memset(request->header, 0, 0x60);
    memcpy(request->header, "INVA", 4);
    DCFlushRange(request->header, 0x60);
    return 1;
}
s32 GSfsysCreateLocalHeap() {
    void* start = OSGetArenaLo();
    void* end = (u8*)start + 0x50000;
    _fsysLocalHeap = GSmemCreateHeap(start, end);
    if (_fsysLocalHeap == -1) return 0;
    OSSetArenaLo(end);
    return 1;
}
s32 _fsysFree(void* data) { GSmemFreeHeap(_fsysLocalHeap, data); return 1; }
void* _fsysAlloc(u32 size) { return GSmemAllocHeap(_fsysLocalHeap, size); }
}
#pragma dont_inline reset
