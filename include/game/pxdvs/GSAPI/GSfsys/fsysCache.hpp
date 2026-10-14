#ifndef FSYS_CACHE_HPP
#define FSYS_CACHE_HPP
#include <global.h>
struct GSfsysCache {
    GSfsysCache *previous, *next;
    u8 inUse, persistent, locked, reserved;
    void* data;
    u32 length, freshness, sequence, group, identifier;
};
typedef char GSfsysCacheSizeCheck[sizeof(GSfsysCache) == 0x24 ? 1 : -1];
extern "C" {
u8 _fsysCheckCache(u32, u32);
void _fsysIncCacheUniqueGroupID();
s32 _fsysInitCache(u32, u32);
s32 _fsysGetFreeCacheHeapSize();
void _fsysFreeCacheFromHeap(void*, u32);
void* _fsysAllocCacheFromHeap(u32);
u8 _fsysInitCacheHeap(u32);
u32 GSfsysCreateCacheHeap();
void _fsysSetLockCacheFlagGroup(u32, u8);
void _fsysSetLockCacheFlag(u32, u32, u8);
GSfsysCache* _fsysGetFreshCacheManage(u32, u8);
GSfsysCache* _fsysGetCacheManageAddr(void*);
GSfsysCache* _fsysGetCacheManageGroup(u32);
GSfsysCache* _fsysGetCacheManage(u32, u32);
void _fsysDelCacheManage(GSfsysCache*);
GSfsysCache* _fsysGetNewCacheManage(u32, u32, u8, u8, u32);
}
#endif
