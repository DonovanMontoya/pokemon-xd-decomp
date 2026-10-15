#include <global.h>
struct FsysStreamHandle { u8 reserved00[0x10]; s32 state; };
struct FsysStreamHeader { u8 reserved00[0xc]; u32 count; };
struct FsysStreamResource { u8 reserved00[0xc]; u32 flags; u8 reserved10[4]; u32 size; u8 reserved18[0x14]; void* cache; u8 reserved30[0x14]; u32 remaining; u32 reserved48, blocks; };
struct FsysStreamArq { u8 reserved00[0x30]; FsysStreamHandle* handle; FsysStreamResource* resource; void (*callback)(u32,u32,u32); u32 param1,param2; };
extern "C" {
extern u32 _fsysBlockByteSize;
s32 OSDisableInterrupts(); void OSRestoreInterrupts(s32);
FsysStreamResource* _fsysGetResHeader(FsysStreamHandle*,u32);
u32 _fsysID2Index(FsysStreamHandle*,u32);
u8 _fsysReadCacheEX(FsysStreamHandle*,FsysStreamResource*,void*,u32,u32,void(*)(void*),u32,u32,u32);
void _fsysMemSet(void*,u8,u32);
FsysStreamArq* _fsysArq2ArqTrans(void*);
FsysStreamHeader* _fsysGetHeader(FsysStreamHandle*);
void _fsysMemFreeCache(void*);
#pragma dont_inline on
u32 _fsysStreamGetReadBlockFlag(u32 offset) { return 1 << (offset / _fsysBlockByteSize); }
#pragma dont_inline reset
static void _fsysStreamGetDataCallback(void*);
u8 _fsysStreamGetData(FsysStreamHandle* handle,u32 id,void* out,u32 size,u32 offset,u32 a,u32 b,u32 c) {
    s32 interrupts=OSDisableInterrupts();
    FsysStreamResource* resource;
    if (id == 0) resource=_fsysGetResHeader(handle,1);
    else resource=_fsysGetResHeader(handle,_fsysID2Index(handle,id));
    if (resource && (resource->blocks & _fsysStreamGetReadBlockFlag(offset))) {
        resource->flags &= ~0x08000000;
        if (_fsysReadCacheEX(handle,resource,out,size,offset,_fsysStreamGetDataCallback,a,b,c)==1) {
            if(resource->flags & 0x00800000) resource->remaining=resource->size;
            else {
                resource->remaining-=size;
                resource->blocks &= ~_fsysStreamGetReadBlockFlag(offset);
            }
            OSRestoreInterrupts(interrupts);
            return 1;
        }
    }
    OSRestoreInterrupts(interrupts);
    _fsysMemSet(out,0,size);
    return 0;
}
static void _fsysStreamGetDataCallback(void* request) {
    FsysStreamArq* trans=_fsysArq2ArqTrans(request);
    if (!trans) { if (!trans) return; return; }
    FsysStreamResource* resource=trans->resource;
    FsysStreamHandle* handle=trans->handle;
    resource->flags |= 0x08000000;
    if(trans->callback) trans->callback(handle->state,trans->param1,trans->param2);
    trans->callback=0;
}
void _fsysStreamFreeCacheAll(FsysStreamHandle* handle) {
    if(handle && handle->state==4) {
        s32 interrupts=OSDisableInterrupts();
        FsysStreamHeader* header=_fsysGetHeader(handle);
        if(header) {
            u32 i=0;
            u32 index;
            for(;(index=i)<header->count;) {
                FsysStreamResource* resource=_fsysGetResHeader(handle,index);
                if(resource && resource->cache) { _fsysMemFreeCache(resource->cache); resource->cache=0; }
                ++i;
            }
        }
        OSRestoreInterrupts(interrupts);
    }
}
u32 _fsysStreamGetMinimumCacheSize() { return _fsysBlockByteSize; }
u32 _fsysStreamGetNormalCacheSize() { return _fsysBlockByteSize*4; }
u32 _fsysStreamGetCacheSize() { return _fsysBlockByteSize*8; }
}
