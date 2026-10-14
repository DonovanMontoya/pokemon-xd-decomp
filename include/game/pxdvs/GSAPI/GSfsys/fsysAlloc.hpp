#ifndef FSYS_ALLOC_HPP
#define FSYS_ALLOC_HPP
#include <global.h>
struct GSfsysDirectory { u8 reserved00[8]; u32 headerLength; };
struct GSfsysHeader {
    u32 magic, reserved04, reserved08, fileCount, flags;
    u8 reserved14[0x2c];
    u32 fileTableOffset;
};
struct GSfsysRequest {
    u32 group, identifier;
    u32 resourceID;
    void* dvd;
    s32 state;
    u8 reserved14[8];
    GSfsysDirectory* directory;
    GSfsysHeader* header;
    u32 readIndex, expandIndex;
    u8 cancelled;
    u8 persistent, headerLoaded, reserved2F;
};
typedef char GSfsysRequestHeaderCheck[sizeof(GSfsysRequest) == 0x30 ? 1 : -1];
extern "C" {
void* _fsysGetResource(u32, u32, u32);
u8 _fsysMemFreeCacheGroup(u32);
void _fsysMemFreeCache(void*);
void* _fsysMemAllocCache(GSfsysRequest*, u32, u32, u32);
void _fsysMemFreeHeader(GSfsysRequest*);
s32 _fsysMemAllocHeader(GSfsysRequest*);
s32 GSfsysCreateLocalHeap();
s32 _fsysFree(void*);
void* _fsysAlloc(u32);
GSfsysHeader* _fsysGetHeader(GSfsysRequest*);
}
#endif
