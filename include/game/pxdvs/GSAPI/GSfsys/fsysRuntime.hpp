#ifndef FSYS_RUNTIME_HPP
#define FSYS_RUNTIME_HPP
#include <game/pxdvs/GSAPI/GSfsys/fsysRead.hpp>
#include <libc/stddef.h>
struct FsysWork {
    u32 group, identifier, resourceID;
    void* dvd;
    s32 mode, status, pendingStatus;
    GSfsysDirectory* directory;
    GSfsysHeader* header;
    u32 readIndex, expandIndex;
    u8 cancelled, keepCache, headerLoaded, reserved2F;
    u32 preCallback, postCallback, secondaryResourceID, cacheGroup;
};
struct FsysQueue {
    FsysQueue* previous;
    FsysQueue* next;
    s32 mode;
    u32 group, resourceID, preCallback, postCallback, secondaryResourceID;
    u8 keepCache, processed, reserved[2];
};
struct FsysBackgroundWork {
    FsysBackgroundWork* previous;
    FsysBackgroundWork* next;
    u8 inUse, loaded, compressed, resourceAllocated;
    FsysWork* work;
    GSfsysResource* resource;
    u8 flags[4];
    u32 expandedBytes, compressedBytes, payloadBytes;
    u8* dictionary;
    s32 matchPosition, dictionaryPosition;
    u32 tokenFlags;
    s32 tokenCount;
    u32 consumedBytes;
    s32 writtenBytes, decodeState;
};
typedef char FsysWorkSize[sizeof(FsysWork) == 0x40 ? 1 : -1];
typedef char FsysQueueSize[sizeof(FsysQueue) == 0x24 ? 1 : -1];
typedef char FsysBackgroundSize[sizeof(FsysBackgroundWork) == 0x44 ? 1 : -1];
typedef char FsysPrefixGroup[offsetof(FsysWork, group) == offsetof(GSfsysRequest, group) ? 1 : -1];
typedef char FsysPrefixHeader[offsetof(FsysWork, header) == offsetof(GSfsysRequest, header) ? 1 : -1];
typedef char FsysPrefixResource[offsetof(FsysWork, resourceID) == offsetof(GSfsysRequest, resourceID) ? 1 : -1];
typedef char FsysWorkStatus[offsetof(FsysWork, status) == 0x14 ? 1 : -1];
typedef char FsysWorkPending[offsetof(FsysWork, pendingStatus) == 0x18 ? 1 : -1];
typedef char FsysWorkCacheGroup[offsetof(FsysWork, cacheGroup) == 0x3c ? 1 : -1];
typedef char FsysDictionaryOffset[offsetof(FsysBackgroundWork, dictionary) == 0x24 ? 1 : -1];
typedef char FsysDecodeStateOffset[offsetof(FsysBackgroundWork, decodeState) == 0x40 ? 1 : -1];
#endif
