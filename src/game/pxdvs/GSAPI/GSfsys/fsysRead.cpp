#include <game/pxdvs/GSAPI/GSfsys/fsysRead.hpp>
#include <game/pxdvs/GSAPI/GSfsys/fsysCache.hpp>
#include <dolphin/os.h>
extern "C" {
u8 GSdvdSeekAsync(void*, s32, void (*)(s32, void*));
void _fsysWorkSetTaskStatus(GSfsysRequest*, s32);
GSfsysRequest* _fsysInfo2Work(void*);
GSfsysBGWork* _fsysGetNewBGWork();
void _fsysAddBGWork(GSfsysBGWork*);
void _fsysResHeaderSetTaskStatus(GSfsysResource*, s32);
extern u32 _fsysBlockByteSize;
extern GSfsysDataType fsys_datatype[];
extern u32 fsys_datatype_number;
}
#pragma dont_inline on
extern "C" {
static void _fsysSeekCallback(s32, void*);
static u8 _fsysReadData(GSfsysRequest*, GSfsysResource*, u8, u32, void*, u32, u32, void (*)(s32, void*), void (*)(u32));
static u8 _fsysAdjustReadFile(GSfsysRequest*);
static u8 _fsysExpandFile(GSfsysRequest*);
static void _fsysReadBlockHandling(GSfsysRequest*, GSfsysResource*);
void _fsysSeekRequest(GSfsysRequest* request) {
    if (!GSdvdSeekAsync(request->dvd, 0, _fsysSeekCallback)) _fsysWorkSetTaskStatus(request, -994);
}
u32 _fsysGetTransLength(u32 length, u32 position) {
    u32 remaining = length - position;
    if (remaining > _fsysBlockByteSize) remaining = _fsysBlockByteSize;
    return (remaining + 31) & ~31;
}
static void _fsysReadBlockHandling(GSfsysRequest* request, GSfsysResource* resource) {
    s32 state = request->state;
    if ((state == 1 || (state == 4 && (resource->flags & 0x40000))) && request->cancelled != 1) {
        _fsysMoveBlock(&resource->readBlocks, &resource->expandBlocks);
        return;
    }
    _fsysFreeBlock(&resource->readBlocks, 0);
}
GSfsysResource* _fsysGetResHeader(GSfsysRequest* request, u32 index) {
    GSfsysHeader* header = _fsysGetHeader(request);
    if (!header) return 0;
    if (index >= header->fileCount) return 0;
    u32* table = (u32*)((u8*)header + header->fileTableOffset);
    return (GSfsysResource*)((u8*)header + table[index]);
}
GSfsysHeader* _fsysGetHeader(GSfsysRequest* request) {
    GSfsysHeader* header = request->header;
    if (!header) return 0;
    else if (!request->headerLoaded) return 0;
    else return header;
}
static u8 _fsysAdjustReadFile(GSfsysRequest* request) {
    GSfsysHeader* header = _fsysGetHeader(request);
    u16 index = 0;
    while (index < header->fileCount) {
        if (!_fsysCheckCache(request->group, index)) break;
        ++index;
    }
    if (index >= header->fileCount) return 0;
    request->readIndex = index;
    return 1;
}
static u8 _fsysExpandFile(GSfsysRequest* request) {
    if (request->expandIndex >= _fsysGetHeader(request)->fileCount) return 0;
    GSfsysResource* resource = _fsysGetResHeader(request, request->expandIndex);
    if (!resource) return 0;
    ++request->expandIndex;
    return _fsysExpandFileExec(request, resource);
}
u8 _fsysExpandFileExec(GSfsysRequest* request, GSfsysResource* resource) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysBGWork* work = _fsysGetNewBGWork();
    if (!work) {
        _fsysResHeaderSetTaskStatus(resource, 4);
        OSRestoreInterrupts(interrupts);
        return 0;
    }
    _fsysResHeaderSetTaskStatus(resource, 1);
    work->resource = resource;
    work->request = request;
    if (resource->flags & 0x80000000) work->compressed = 1;
    else work->compressed = 0;
    _fsysAddBGWork(work);
    OSRestoreInterrupts(interrupts);
    return 1;
}
GSfsysDataType* _fsysGetDataType(u32 identifier) {
    GSfsysDataType* type = fsys_datatype;
    for (u32 i = 0; i < fsys_datatype_number; ++i, ++type) if (type->identifier == identifier) return type;
    return 0;
}
static void _fsysSeekCallback(s32 result, void* info) {
    GSfsysRequest* request = _fsysInfo2Work(info);
    if (request) {
        if (result < 0) { _fsysWorkSetTaskStatus(request, -994); return; }
        _fsysWorkSetTaskStatus(request, 11);
    }
}
}
#pragma dont_inline reset

extern "C" {
u8 GSdvdReadAsync(void*, void*, u32, u32, void (*)(s32, void*));
u8 _fsysReadCache(GSfsysRequest*, u32, void*, u32, u32, void (*)(u32));
#pragma dont_inline on
static u8 _fsysReadData(GSfsysRequest* request, GSfsysResource* resource, u8 cached, u32 identifier, void* destination, u32 length, u32 offset, void (*dvdCallback)(s32, void*), void (*cacheCallback)(u32)) {
    request->identifier = identifier;
    if (cached == 1) {
        if (!_fsysReadCache(request, (u32)resource, destination, length, offset, cacheCallback)) {
            _fsysWorkSetTaskStatus(request, -996);
            return 0;
        }
    } else if (resource && resource->dvd) {
        if (!GSdvdReadAsync(resource->dvd, destination, length, offset, dvdCallback)) {
            _fsysWorkSetTaskStatus(request, -996);
            return 0;
        }
    } else {
        if (resource) offset += resource->offset;
        if (!GSdvdReadAsync(request->dvd, destination, length, offset, dvdCallback)) {
            _fsysWorkSetTaskStatus(request, -996);
            return 0;
        }
    }
    return 1;
}
#pragma dont_inline reset
}
