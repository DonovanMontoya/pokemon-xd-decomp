#ifndef FSYS_READ_HPP
#define FSYS_READ_HPP
#include <game/pxdvs/GSAPI/GSfsys/fsysAlloc.hpp>
#include <game/pxdvs/GSAPI/GSfsys/fsysBlock.hpp>
struct GSfsysResource {
    u32 identifier, offset, expandedLength, flags;
    u32 reserved10, length;
    void* expandedData;
    u32 nameOffset, dataType, reserved24;
    u32 readPosition;
    void* cache;
    GSfsysBlock *readBlocks, *expandBlocks;
    void* dvd;
    u32 reserved3C, token, streamBytes, streamPosition, streamFlags, loopStart, loopEnd;
};
typedef char GSfsysResourceSizeCheck[sizeof(GSfsysResource) == 0x58 ? 1 : -1];
struct GSfsysDataType { const char* name; u32 identifier; void* (*begin)(u32, u32, u32); void (*finish)(u32, u32, u32); };
struct GSfsysBGWork {
    GSfsysBGWork *previous, *next;
    u8 inUse, reserved09, compressed, reserved0B;
    GSfsysRequest* request;
    GSfsysResource* resource;
};
extern "C" {
void _fsysSeekRequest(GSfsysRequest*);
GSfsysResource* _fsysGetResHeader(GSfsysRequest*, u32);
u32 _fsysGetTransLength(u32, u32);
u8 _fsysExpandFileExec(GSfsysRequest*, GSfsysResource*);
GSfsysDataType* _fsysGetDataType(u32);
}
#endif
