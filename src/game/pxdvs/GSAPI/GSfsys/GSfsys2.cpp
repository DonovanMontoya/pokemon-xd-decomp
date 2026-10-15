#pragma pool_strings off
extern "C" {
#include <libc/stdio.h>
#include <libc/string.h>
}
#include <game/pxdvs/GSAPI/GSfsys/fsysRuntime.hpp>
#include <game/pxdvs/GSAPI/GSfsys/fsysCache.hpp>
#include <game/pxdvs/GSAPI/GSdvd/GSdvd.hpp>
#include <game/pxdvs/GSAPI/GSres/GSres.hpp>
#include <dolphin/os.h>
#pragma dont_inline on
extern "C" {
void* GSmemAllocAlign(u32, u16);
u32 GSgappCreate(u32, u32, u32, void (*)());
void GSgappSetName(u32, const char*);
void GSfsysDaemonForeground();
void GSfsysDaemonBackground();
u8 _fsysInitTOC();
u32 _fsysStreamGetCacheSize();
s32 GSmovieStreamPreFunc(u32, u32, u32);
void GSmovieStreamPostFunc(u32, u32);
s32 GSsndStreamPreFunc(u32, u32, u32);
void GSsndStreamPostFunc(u32, u32);
void GSthreadSwitch();
s32 _fsysRequest(s32, u32, u32, u8, u32, u32, u32, s32);
void _fsysQueExec();
u8 _fsysQueExecSub(FsysQueue*);
s32 _fsysExec(u32, u32, s32, u8, u32, u32, u32);
s32 _fsysReadStreamingExec(u32, u32, u32);
s32 _fsysWait(u32, u8);
u32 GSfsysRead(u32);
u32 GSfsysReadID(u32, u32);
u32 GSfsysReadIDEX(u32, u32, u32, u32, u32);
u32 GSfsysPreRead(u32);
u8 GSfsysCancel(u32);
s32 GSfsysGetStatus(u32);
FsysWork* _fsysGetWork(u32, u8);
u32 _fsysID2Index(FsysWork*, u32);
void _fsysFreeStatus(u32);
void _fsysMemSet(void*, s32, u32);
void _fsysStreamFreeCacheAll(GSfsysRequest*);
void _fsysBackgroundTaskNormalType(FsysBackgroundWork*, u8);
void _fsysBackgroundTaskCompressType(FsysBackgroundWork*);
extern u32 _fsysBlockByteSize;
void _fsysReadDataExec(GSfsysRequest*, GSfsysResource*);
u32 _fsysStreamGetNormalCacheSize();
u32 _fsysStreamGetMinimumCacheSize();
u8 _fsysCheckExpandComplete(FsysWork*, u32);
void _fsysForegroundTask(FsysWork*);
void _fsysReadRequest(GSfsysRequest*);
void _fsysHeaderSizeReadDvdCallback(s32, GSdvdWork*);
s32 _fsysStreamGetData(FsysWork*, u32, void*, u32, u32, u32, u32, u32);

static u8 _initFlag;
struct TocHeader { u32 magic, version, groupCount, reserved0C, tableOffset; };
struct TocGroup { u32 group; const char* name; u32 headerLength, flags; };
static TocHeader* _fsysTOC;
static FsysWork* _fsysWork;
static FsysBackgroundWork* _fsysBGWork;
static FsysBackgroundWork* _fsysBGWorkRoot;
static FsysQueue* _fsysQueManage;
static FsysQueue* _fsysQueManageExec;
static u32 _fsysDaemonForegroundHDL, _fsysDaemonBackgroundHDL;
static u32 _fsysQueManageMax, _fsysBGWorkIndex, _fsysBGWorkMax, _fsysWorkIndex, _fsysWorkMax;
static FsysQueue* _fsysQueManageRoot[3];
static u32 headerTop[8];
static u32* _headerTop;

// Stripped from the DOL; its strings still occupy .rodata.
void _fsysPrintStatus(FsysWork* work, s32 phase) {
    const char* modeNames[3] = { "READ", "PREREAD", "STREAMING" };
    const char* name = modeNames[work->mode];
    switch (phase) {
    case 0: OSReport("[%d]HEADERSIZE_READ", work->group); break;
    case 1: OSReport("[%d]HEADERSIZE_READ_WAIT", work->group); break;
    case 2: OSReport("[%d]START", work->group); break;
    case 3: OSReport("[%d]%s:---", work->group, name); break;
    case 4: OSReport("[%d]%s:[%d]ERROR_READDATAEXEC", work->group, name, phase); break;
    case 5: OSReport("[%d]%s:[%d]ERROR_EXPANDFILE", work->group, name, phase); break;
    case 6: OSReport("[%d]%s:[%d]ERROR_STREAMING", work->group, name, phase); break;
    case 7: OSReport("[%d]%s:[%d]STREAMING_COMPLETE", work->group, name, phase); break;
    case 8: OSReport("[%d]%s:[%d]READY", work->group, name, phase); break;
    case 9: OSReport("[%d]%s:[%d]NONE", work->group, name, phase); break;
    default: OSReport("[%d]%s:[%d]default", work->group, name, phase); break;
    }
    switch (work->status) {
    case 0: OSReport("[%d]SEEK", work->group); break;
    case 1: OSReport("[%d]READ_COMPLETE", work->group); break;
    case 2: OSReport("[%d]ERROR", work->group); break;
    case 3: OSReport("[%d]ERROR_READ", work->group); break;
    case 4: OSReport("[%d]ERROR_PREREAD", work->group); break;
    case 5: OSReport("[%d]ERROR_SEEK", work->group); break;
    case 6: OSReport("[%d]ERROR_FILEOPEN", work->group); break;
    case 7: OSReport("[%d]ERROR_FILECLOSE", work->group); break;
    case 8: OSReport("[%d]COMPLETE", work->group); break;
    case 9: OSReport("[%d]ERROR_WAIT", work->group); break;
    case 10: OSReport("[%d]COMPLETE_WAIT", work->group); break;
    case 11: OSReport("[%d]READY", work->group); break;
    case 12: OSReport("[%d]READY_WAIT", work->group); break;
    case 13: OSReport("[%d]NONE", work->group); break;
    default: OSReport("[%d]default", work->group); break;
    }
}
void* _fsysDoMalloc(u32 bytes) { return GSmemAllocAlign(bytes, 32); }
u8 GSfsysInit2(u32 blocks, u32 cacheBytes, u32 cacheEntries) {
    u32 i;
    if (_initFlag == 1) return 0;
    _fsysQueManageRoot[0] = 0;
    _fsysWorkIndex = 0;
    _fsysBGWorkIndex = 0;
    _fsysQueManageRoot[1] = 0;
    _fsysQueManageRoot[2] = 0;
    _fsysQueManageExec = 0;
    if ((u8)_fsysInitBlock(blocks) == 0) return 0;
    if ((u8)_fsysInitCache(cacheBytes, cacheEntries) == 0) return 0;
    _fsysWorkMax = 4;
    _fsysBGWorkMax = 16;
    _fsysQueManageMax = 24;
    _fsysWork = (FsysWork*)_fsysDoMalloc(_fsysWorkMax * sizeof(FsysWork));
    if (!_fsysWork) return 0;
    _fsysBGWork = (FsysBackgroundWork*)_fsysDoMalloc(_fsysBGWorkMax * sizeof(FsysBackgroundWork));
    if (!_fsysBGWork) return 0;
    _fsysQueManage = (FsysQueue*)_fsysDoMalloc(_fsysQueManageMax * sizeof(FsysQueue));
    if (!_fsysQueManage) return 0;
    for (i = 0; i < _fsysWorkMax; ++i) {
        _fsysWork[i].status = 0;
        _fsysWork[i].pendingStatus = 0xffff;
        _fsysWork[i].header = 0;
        _fsysWork[i].headerLoaded = 0;
    }
    for (i = 0; i < _fsysBGWorkMax; ++i) _fsysBGWork[i].inUse = 0;
    for (i = 0; i < _fsysQueManageMax; ++i) _fsysQueManage[i].group = 0;
    if (_fsysInitTOC() == 0) return 0;
    _fsysDaemonForegroundHDL = GSgappCreate(1, 0x14, 0, GSfsysDaemonForeground);
    GSgappSetName(_fsysDaemonForegroundHDL, "GSfsysDaemonForeground");
    _fsysDaemonBackgroundHDL = GSgappCreate(1, 0x13, 0, GSfsysDaemonBackground);
    GSgappSetName(_fsysDaemonBackgroundHDL, "GSfsysDaemonBackground");
    _initFlag = 1;
    return 1;
}
u8 GSfsysInit(u32 dvdEntries) { GSdvdInit(dvdEntries); return GSfsysInit2(0, 0, 0); }
u32 GSfsysGetInvalidID() { return 0xffff; }
u32 GSfsysStreamGetCacheSize() { return _fsysStreamGetCacheSize(); }
s32 GSfsysGetDriveStatus() { if (!_initFlag) { return -1; } else { return GSdvdGetDriveStatus(); } }
s32 GSfsysStreamHeaderPostFunc(u32, u32) { if (!_initFlag) return 0; return 0; }
s32 GSfsysStreamMovieHeaderPostFunc(u32, u32) { if (!_initFlag) return 0; return 0; }
s32 GSfsysStreamHeaderPreFunc(u32 group, u32 resource, u32 bytes) {
    if (!_initFlag) return 0;
    return GSsndStreamPreFunc(group, resource, bytes);
}
s32 GSfsysStreamMovieHeaderPreFunc(u32 group, u32 resource, u32 bytes) {
    if (!_initFlag) return 0;
    return GSmovieStreamPreFunc(group, resource, bytes);
}
s32 GSfsysStreamPreFunc(u32 group, u32 resource) {
    if (!_initFlag) return 0;
    FsysWork* work = _fsysGetWork(group, 0);
    if (!work) return 0;
    GSsndStreamPostFunc(group, work->secondaryResourceID);
    return 0;
}
s32 GSfsysStreamMoviePreFunc(u32 group, u32 resource) {
    if (!_initFlag) return 0;
    FsysWork* work = _fsysGetWork(group, 0);
    if (!work) return 0;
    GSmovieStreamPostFunc(group, work->secondaryResourceID);
    return 0;
}
void GSfsysFreeCache(u32 group) {
    if (_initFlag) while (_fsysMemFreeCacheGroup(group) != 0) {}
}
u32 GSfsysRead(u32 group) { return _fsysRequest(1, group, 0xffff, 0, 0, 0, 0, 1); }
u32 GSfsysReadID(u32 group, u32 resource) { return _fsysRequest(1, group, resource, 0, 0, 0, 0, 1); }
u32 GSfsysReadIDEX(u32 group, u32 resource, u32 pre, u32 post, u32 secondary) { return _fsysRequest(1, group, resource, 0, pre, post, secondary, 1); }
u32 _fsysPreReadExec(u32, u8, u32, u32, u32, s32);
u32 GSfsysPreRead(u32 group) { return _fsysPreReadExec(group, 0, 0, 0, 0, 1); }
u32 GSfsysPreReadKeepCache(u32 group) { return _fsysPreReadExec(group, 1, 0, 0, 0, 1); }
u32 _fsysPreReadExec(u32 group, u8 keep, u32 pre, u32 post, u32 secondary, s32 priority) { return _fsysRequest(2, group, 0xffff, keep, pre, post, secondary, priority); }
u32 GSfsysReadStreaming(u32 group) { return _fsysReadStreamingExec(group, 0xffff, 0); }
u32 GSfsysReadStreamingEX(u32 group, u32 resource, u32 secondary) { return _fsysReadStreamingExec(group, resource, secondary); }
s32 GSfsysWait(u32 group) { return _fsysWait(group, 1); }
s32 GSfsysReadIDWait(u32 group, u32 resource) {
    if (!_initFlag) return 0;
    for (;;) {
        if ((u8)GSfsysReadID(group, resource) == 1) break;
        GSthreadSwitch();
    }
    return _fsysWait(group, 0);
}
s32 GSfsysReadIDEXWait(u32 group, u32 resource, u32 pre, u32 post, u32 secondary) {
    if (!_initFlag) return 0;
    for (;;) {
        if ((u8)GSfsysReadIDEX(group, resource, pre, post, secondary) == 1) break;
        GSthreadSwitch();
    }
    return _fsysWait(group, 0);
}
s32 GSfsysPreReadWait(u32 group) {
    if (!_initFlag) return 0;
    for (;;) {
        if ((u8)GSfsysPreRead(group) == 1) break;
        GSthreadSwitch();
    }
    return _fsysWait(group, 0);
}
void GSfsysStreamSetLoopPoint(u32 group, u32 id, u32 start, u32 end) {
    if (!_initFlag) return;
    FsysWork* work = _fsysGetWork(group, 0);
    if (!work) return;
    GSfsysResource* resource;
    if (id == 0) {
        resource = _fsysGetResHeader((GSfsysRequest*)work, 1);
    } else {
        resource = _fsysGetResHeader((GSfsysRequest*)work, _fsysID2Index(work, id));
    }
    if (resource) { resource->loopStart = start; resource->loopEnd = end; }
}
void GSfsysStreamSetLoopFlag(u32 group, u32 id, u8 loop) {
    if (!_initFlag) return;
    FsysWork* work = _fsysGetWork(group, 0);
    if (!work) return;
    GSfsysResource* resource;
    if (id == 0) {
        resource = _fsysGetResHeader((GSfsysRequest*)work, 1);
    } else {
        resource = _fsysGetResHeader((GSfsysRequest*)work, _fsysID2Index(work, id));
    }
    if (resource) {
        if (loop == 0) { resource->flags |= 0x800; return; }
        resource->flags &= ~0x800;
    }
}

TocGroup* _fsysGetGROUP(u32 id) {
    u32 count = _fsysTOC->groupCount;
    TocGroup* group = (TocGroup*)((u8*)_fsysTOC + _fsysTOC->tableOffset);
    for (u32 i = 0; i < count; ++i, ++group) {
        if (group->group == id) return group;
    }
    return 0;
}
void _fsysOffTOCFlag(u32 groupId, u32 bits) {
    TocGroup* group = _fsysGetGROUP(groupId);
    if (group) group->flags &= ~bits;
}
void _fsysOnTOCFlag(u32 groupId, u32 bits) {
    TocGroup* group = _fsysGetGROUP(groupId);
    if (group) group->flags |= bits;
}
s32 _fsysGetFilename(FsysWork* work, char* output) {
    TocGroup* group = _fsysGetGROUP(work->group);
    if (!group) return 0;
    sprintf(output, "%s.fsys", group->name);
    return 1;
}
FsysWork* _fsysGetWork(u32 group, u8 activeOnly) {
    FsysWork* work = _fsysWork;
    for (u32 i = 0; i < _fsysWorkMax; ++i, ++work) {
        s32 status = work->status;
        if (activeOnly == 1) {
            if (status == 0 || status == -999 || status == 12) continue;
        } else if (status == 0) {
            continue;
        }
        if (group == work->group) return _fsysWork + i;
    }
    return 0;
}
u32 _fsysID2Index(FsysWork* work, u32 id) {
    if (id == 0xffff) return 0xffff;
    GSfsysHeader* header = _fsysGetHeader((GSfsysRequest*)work);
    if (header) for (u32 i = 0; i < header->fileCount; ++i) {
        GSfsysResource* resource = _fsysGetResHeader((GSfsysRequest*)work, i);
        if (resource && resource->identifier == id) return i;
    }
    return 0xffff;
}
void _fsysWorkSetTaskStatus(FsysWork* work, s32 status) {
    BOOL interrupts = OSDisableInterrupts();
    work->pendingStatus = status;
    OSRestoreInterrupts(interrupts);
}
void _fsysResHeaderSetTaskStatus(GSfsysResource* resource, s32 status) {
    BOOL interrupts = OSDisableInterrupts();
    resource->token = status;
    OSRestoreInterrupts(interrupts);
}
void _fsysFreeStatus(u32 group) {
    _fsysOffTOCFlag(group, 1);
    FsysWork* work = _fsysGetWork(group, 0);
    if (work) work->status = 1;
}
s32 _fsysWait(u32 group, u8 allowPreread) {
    if (!_initFlag) return 0;
    for (;;) {
        s32 status = GSfsysGetStatus(group);
        if (status == 0) return 1;
        if (status == -1) { if (allowPreread == 1) return 1; }
        else if (status <= -2) return 0;
        GSthreadSwitch();
    }
}
s32 _fsysGetActiveTask(s32 mode) {
    s32 count = 0;
    FsysWork* work = _fsysWork;
    for (u32 i = 0; i < _fsysWorkMax; ++i, ++work) {
        s32 status = work->status;
        if ((status < 0 && status != -999) || (status >= 2 && status != 12)) {
            if (mode == work->mode) ++count;
        }
    }
    return count;
}

s32 GSfsysGetStatus(u32 groupId) {
    if (!_initFlag) return -2;
    TocGroup* group = _fsysGetGROUP(groupId);
    if (!group) return -1;
    if (group->flags & 1) return 0;
    FsysWork* work = _fsysGetWork(groupId, 0);
    if (!work) return -1;
    switch (work->status) {
    case 12: return 0;
    case 1: return -1;
    case -999: return -2;
    default: return 1;
    }
}
u8 GSfsysCancel(u32 group) {
    if (!_initFlag) return 0;
    if (GSfsysGetStatus(group) <= 0) return 0;
    FsysWork* work = _fsysGetWork(group, 1);
    if (!work) return 0;
    work->cancelled = 1;
    return 1;
}
s32 GSfsysCancelWait(u32 group) {
    if (GSfsysCancel(group) == 0) return 0;
    return _fsysWait(group, 0);
}
s32 GSfsysReadWait(u32 group) {
    if (!_initFlag) return 0;
    FsysWork* work = _fsysGetWork(group, 1);
    if (work && work->mode == 2) GSfsysCancelWait(group);
    for (;;) {
        if ((u8)GSfsysRead(group) == 1) break;
        GSthreadSwitch();
    }
    return _fsysWait(group, 0);
}

FsysQueue* _fsysGetNewQueManage(s32 mode, u32 group, u32 resource, u8 keep, u32 pre, u32 post, u32 secondary) {
    FsysQueue* queue = _fsysQueManage;
    for (u32 i = 0; i < _fsysQueManageMax; ++i, ++queue) {
        if (queue->group == 0) {
            FsysQueue* result = _fsysQueManage + i;
            result->previous = 0;
            result->next = 0;
            result->mode = mode;
            result->group = group;
            result->resourceID = resource;
            result->preCallback = pre;
            result->postCallback = post;
            result->secondaryResourceID = secondary;
            result->keepCache = keep;
            result->processed = 0;
            return result;
        }
    }
    return 0;
}
u8 _fsysAddQueManage(FsysQueue* queue, s32 priority) {
    FsysQueue* current = _fsysQueManageRoot[priority];
    if (!current) { _fsysQueManageRoot[priority] = queue; return 1; }
    while (current->next) current = current->next;
    current->next = queue;
    queue->previous = current;
    return 0;
}
void _fsysDelQueManage(FsysQueue* queue) {
    if (queue->previous) queue->previous->next = queue->next;
    if (queue->next) queue->next->previous = queue->previous;
    for (s32 i = 0; i < 3; ++i) {
        if (queue == _fsysQueManageRoot[i]) { _fsysQueManageRoot[i] = queue->next; break; }
    }
    queue->group = 0;
}
FsysQueue* _fsysGetQueManage(u32 group, u32 resource) {
    for (s32 i = 0; i < 3; ++i) {
        FsysQueue* queue = _fsysQueManageRoot[i];
        while (queue) {
            if (queue->group == group) {
                if (resource != 0xffff && queue->resourceID == resource) return queue;
                return queue;
            }
            queue = queue->next;
        }
    }
    return 0;
}
s32 _fsysRequest(s32 mode, u32 group, u32 resource, u8 keep, u32 pre, u32 post, u32 secondary, s32 priority) {
    if (!_initFlag) return 0;
    if (mode < 0 || priority >= 6) return 0;
    if (priority < 0 || priority >= 3) return 0;
    FsysQueue* queue = _fsysGetQueManage(group, resource);
    if (queue && queue->processed == 0 && (mode == 2 || mode == 3)) _fsysDelQueManage(queue);
    queue = _fsysGetNewQueManage(mode, group, resource, keep, pre, post, secondary);
    if (!queue) return 0;
    if (_fsysAddQueManage(queue, priority) == 1) _fsysQueExec();
    return 1;
}
u8 _fsysQueExecSub(FsysQueue* queue) {
    if (queue->processed == 0) {
        queue->processed = 1;
        switch (queue->mode) {
        case 5:
            GSfsysCancel(queue->group);
            return 0;
        case 1: case 2: case 3: case 4:
            _fsysExec(queue->group, queue->resourceID, queue->mode, queue->keepCache, queue->preCallback, queue->postCallback, queue->secondaryResourceID);
            return 0;
        default:
            _fsysDelQueManage(queue);
            return 1;
        }
    }
    if (GSfsysGetStatus(queue->group) <= 0) { _fsysDelQueManage(queue); return 1; }
    return 0;
}
void _fsysQueExec() {
    FsysQueue* queue;
    FsysQueue* next;
    s32 i;
    if (_fsysQueManageExec) {
        if (_fsysQueExecSub(_fsysQueManageExec) == 0) return;
        _fsysQueManageExec = 0;
    }
    for (i = 0; i < 3; ++i) {
        queue = _fsysQueManageRoot[i];
        while (queue) {
            next = queue->next;
            if (_fsysQueExecSub(queue) == 0) { _fsysQueManageExec = queue; return; }
            queue = next;
        }
    }
}

FsysWork* _fsysGetNewWork_Sub(s32 preserveFinished) {
    FsysWork* result = 0;
    u32 index = _fsysWorkIndex;
    while (!result) {
        FsysWork* work = _fsysWork + index;
        s32 status = work->status;
        if (status == -999 || status == 0 || status == 1 || (status == 12 && preserveFinished != 1)) {
            result = work;
            if (work->header) _fsysMemFreeHeader((GSfsysRequest*)work);
        }
        ++index;
        if (index >= _fsysWorkMax) index = 0;
        if (index == _fsysWorkIndex) break;
    }
    _fsysWorkIndex = index;
    return result;
}
FsysWork* _fsysGetNewWork() {
    FsysWork* work = _fsysGetNewWork_Sub(1);
    if (work) return work;
    work = _fsysGetNewWork_Sub(0);
    if (work) return work;
    return 0;
}
s32 _fsysOpenFile(FsysWork* work) {
    char filename[128];
    _fsysGetFilename(work, filename);
    work->dvd = GSdvdOpen(filename);
    if (!work->dvd) { _fsysWorkSetTaskStatus(work, -998); return 0; }
    if (work->directory->headerLength == 0) {
        _fsysWorkSetTaskStatus(work, 3);
    } else {
        _fsysWorkSetTaskStatus(work, 5);
    }
    return 1;
}
s32 _fsysExec(u32 group, u32 resource, s32 mode, u8 keep, u32 pre, u32 post, u32 secondary) {
    BOOL interrupts = OSDisableInterrupts();
    _fsysFreeStatus(group);
    FsysWork* work = _fsysGetWork(group, 0);
    if (!work) {
        work = _fsysGetNewWork();
        if (!work) {
            s32 previous = OSRestoreInterrupts(interrupts);
            if (work) return 0;
            return previous;
        }
        work->header = 0;
        work->cacheGroup = _fsysIncCacheUniqueGroupID();
    }
    work->group = group;
    work->resourceID = resource;
    work->dvd = 0;
    work->mode = mode;
    work->status = 2;
    work->pendingStatus = 0xffff;
    work->readIndex = 0;
    work->expandIndex = 0;
    work->cancelled = 0;
    work->keepCache = keep;
    work->preCallback = pre;
    work->postCallback = post;
    work->secondaryResourceID = secondary;
    work->directory = (GSfsysDirectory*)_fsysGetGROUP(group);
    _fsysOpenFile(work);
    OSRestoreInterrupts(interrupts);
    return 1;
}
s32 _fsysReadStreamingExec(u32 group, u32 resource, u32 secondary) {
    if (!_initFlag) return 0;
    if (GSfsysGetStatus(group) <= 0) return _fsysExec(group, resource, 4, 0, 0, 0, secondary);
    GSfsysCancelWait(group);
    return _fsysExec(group, resource, 4, 0, 0, 0, secondary);
}
void GSfsysFree(u32 group) {
    if (_initFlag) {
        BOOL interrupts = OSDisableInterrupts();
        _fsysFreeStatus(group);
        FsysWork* work = _fsysGetWork(group, 0);
        if (work) {
            GSfsysHeader* header = _fsysGetHeader((GSfsysRequest*)work);
            if (header) for (u32 i = 0; i < header->fileCount; ++i) {
                GSfsysResource* resource = _fsysGetResHeader((GSfsysRequest*)work, i);
                if (resource) resource->flags &= ~8;
            }
        }
        OSRestoreInterrupts(interrupts);
    }
}
void _fsysDelTAG(FsysBackgroundWork* entry, FsysBackgroundWork** root) {
    BOOL interrupts = OSDisableInterrupts();
    if (entry->previous) entry->previous->next = entry->next;
    if (entry->next) entry->next->previous = entry->previous;
    if (entry == *root) *root = entry->next;
    entry->inUse = 0;
    entry->previous = 0;
    entry->next = 0;
    OSRestoreInterrupts(interrupts);
}
void _fsysAddTAG(FsysBackgroundWork* entry, FsysBackgroundWork** root) {
    BOOL interrupts = OSDisableInterrupts();
    if (*root == 0) {
        *root = entry;
    } else {
        FsysBackgroundWork* tail = *root;
        while (tail->next) tail = tail->next;
        tail->next = entry;
        entry->previous = tail;
    }
    OSRestoreInterrupts(interrupts);
}
void _fsysDelBGWork(FsysBackgroundWork* entry) { _fsysDelTAG(entry, &_fsysBGWorkRoot); }
void _fsysAddBGWork(FsysBackgroundWork* entry) { _fsysAddTAG(entry, &_fsysBGWorkRoot); }
FsysBackgroundWork* _fsysGetNewBGWork() {
    FsysBackgroundWork* result = 0;
    BOOL interrupts = OSDisableInterrupts();
    FsysBackgroundWork* entry;
    u32 index = _fsysBGWorkIndex;
    while (!result) {
        entry = _fsysBGWork + index;
        if (entry->inUse == 0) {
            entry->previous = 0;
            entry->next = 0;
            entry->inUse = 1;
            entry->loaded = 0;
            entry->compressed = 0;
            entry->resourceAllocated = 0;
            entry->work = 0;
            entry->resource = 0;
            entry->flags[0] = 0;
            entry->flags[1] = 0;
            entry->flags[2] = 0;
            entry->flags[3] = 0;
            entry->expandedBytes = 0;
            entry->compressedBytes = 0;
            entry->payloadBytes = 0;
            entry->dictionary = 0;
            entry->matchPosition = 0;
            entry->dictionaryPosition = 0;
            entry->tokenFlags = 0;
            entry->tokenCount = 0;
            entry->consumedBytes = 0;
            entry->writtenBytes = 0;
            entry->decodeState = 0;
            result = entry;
        }
        ++index;
        if (index >= _fsysBGWorkMax) index = 0;
        if (index == _fsysBGWorkIndex) break;
    }
    _fsysBGWorkIndex = index;
    OSRestoreInterrupts(interrupts);
    return result;
}
void _fsysMemSet(void* data, s32 value, u32 bytes) {
    if (data) { memset(data, value, bytes); DCFlushRange(data, bytes); }
}
u8 _fsysBGTaskCancel(FsysBackgroundWork* entry) {
    if (entry->work->cancelled == 1) {
        _fsysFreeBlockAll(&entry->resource->readBlocks);
        _fsysFreeBlockAll(&entry->resource->expandBlocks);
        entry->loaded = 1;
        return 1;
    } else {
        return 0;
    }
}
s32 GSfsysStreamGetData(u32 group, u32 resource, void* data, u32 bytes, u32 a, u32 b, u32 c, u32 d) {
    if (!_initFlag) return 0;
    FsysWork* work = _fsysGetWork(group, 0);
    if (!work) { _fsysMemSet(data, 0, bytes); return 0; }
    return _fsysStreamGetData(work, resource, data, bytes, a, b, c, d);
}
u8 _fsysCloseFile(FsysWork* work, u8 cancelled) {
    if (cancelled == 0 && work->preCallback && work->mode != 4)
        ((void (*)(s32, u32, u32))work->preCallback)(work->mode, work->postCallback, work->secondaryResourceID);
    BOOL interrupts = OSDisableInterrupts();
    _fsysSetLockCacheFlagGroup(work->group, 0);
    _fsysStreamFreeCacheAll((GSfsysRequest*)work);
    OSRestoreInterrupts(interrupts);
    void* dvd = work->dvd;
    work->dvd = 0;
    return GSdvdClose((GSdvdWork*)dvd);
}
FsysWork* _fsysInfo2Work(void* dvd) {
    FsysWork* work;
    u32 i;
    u32 j;
    for (i = 0; i < _fsysWorkMax; ++i) {
        work = _fsysWork + i;
        switch (work->status) { case -999: case 0: case 1: case 12: continue; }
        if (work->dvd == dvd) return work;
        GSfsysHeader* header = _fsysGetHeader((GSfsysRequest*)work);
        if (header && (header->flags & 1)) {
            for (j = 0; j < header->fileCount; ++j) {
                GSfsysResource* resource = _fsysGetResHeader((GSfsysRequest*)work, j);
                if (resource && resource->dvd == dvd) return work;
            }
        }
    }
    return 0;
}
void GSfsysOSUnLink(u32 group, u32 identifier, u32) {
    if (_initFlag) {
        OSModuleHeader* module = (OSModuleHeader*)GSresGetResource(group, identifier);
        if (module) {
            if (module->epilog) ((void (*)())module->epilog)();
            OSUnlink(&module->info);
        }
    }
}
u8 _fsysOSUnLink(void*, unsigned long group, unsigned long identifier) {
    if (!_initFlag) return 0;
    GSfsysOSUnLink(group, identifier, 0);
    return 1;
}
void* GSfsysOSLinkPreFunc(u32 group, u32 identifier, u32 bytes) {
    void* resource = GSresAllocResourceAlign(bytes, 32, group, identifier, _fsysOSUnLink);
    if (!resource) { return 0; } else { return resource; }
}
void* GSfsysOSLinkPostFunc(u32 group, u32 identifier) {
    OSModuleHeader* module = (OSModuleHeader*)GSresGetResource(group, identifier);
    if (!module) return 0;
    if (module->info.version < 3) return 0;
    OSModuleHeader* end = module + module->fixSize;
    void* bss = (void*)(((u32)end + 31) & ~31);
    OSLinkFixed(&module->info, bss);
    if (module->prolog) ((void (*)())module->prolog)();
    return module;
}
void GSfsysDaemonBackground() {
    FsysBackgroundWork* entry = _fsysBGWorkRoot;
    while (entry) {
        if (entry->resourceAllocated == 0) {
            entry->resourceAllocated = 1;
            GSfsysDataType* type = _fsysGetDataType(entry->resource->dataType);
            void* data;
            if (type->begin) {
                data = type->begin(entry->work->group, entry->resource->identifier, entry->resource->expandedLength);
            } else {
                data = _fsysGetResource((entry->resource->expandedLength + 31) & ~31, entry->work->group, entry->resource->identifier);
            }
            entry->resource->expandedData = data;
        }
        if (!entry->resource->expandedData) {
            _fsysBackgroundTaskNormalType(entry, 0);
        } else if (entry->compressed == 1) {
            _fsysBackgroundTaskCompressType(entry);
        } else {
            _fsysBackgroundTaskNormalType(entry, 1);
        }
        entry = entry->next;
    }
}
void _fsysBackgroundTaskNormalType(FsysBackgroundWork* entry, u8 copy) {
    if (entry->loaded != 1) {
        do {
            if (_fsysBGTaskCancel(entry) == 1) return;
            GSfsysResource* resource = entry->resource;
            GSfsysBlock* block = resource->expandBlocks;
            if (!block) return;
            if (copy == 1) {
                void* destination = (u8*)resource->expandedData + entry->consumedBytes;
                memcpy(destination, block->data, _fsysGetTransLength(resource->length, entry->consumedBytes));
            }
            _fsysFreeBlock(&entry->resource->expandBlocks, 1);
            entry->consumedBytes += _fsysBlockByteSize;
        } while (entry->consumedBytes < entry->resource->length);
        DCFlushRange(entry->resource->expandedData, entry->resource->length);
        entry->loaded = 1;
    }
}
u8 _fsysCheckExpandCompleteAll(FsysWork* work) {
    u32 i;
    GSfsysHeader* header = _fsysGetHeader((GSfsysRequest*)work);
    if (!header) return 0;
    u8 complete = 1;
    if (_fsysID2Index(work, work->resourceID) != 0xffff) {
        if (work->mode == 4) {
            if (_fsysCheckExpandComplete(work, _fsysID2Index(work, work->resourceID)) == 0) complete = 0;
            if (_fsysCheckExpandComplete(work, _fsysID2Index(work, work->secondaryResourceID)) == 0) complete = 0;
        } else {
            return _fsysCheckExpandComplete(work, _fsysID2Index(work, work->resourceID));
        }
    } else {
        for (u32 i = 0; i < header->fileCount; ++i)
            if (_fsysCheckExpandComplete(work, i) == 0) complete = 0;
    }
    return complete;
}
u8 _fsysCheckExpandComplete(FsysWork* work, u32 index) {
    GSfsysResource* resource = _fsysGetResHeader((GSfsysRequest*)work, index);
    if (!resource) return 0;
    BOOL interrupts = OSDisableInterrupts();
    if (resource->token != 0xffff) { resource->reserved3C = resource->token; resource->token = 0xffff; }
    OSRestoreInterrupts(interrupts);
    u8 complete;
    if (!(resource->flags & 8)) {
        switch ((s32)resource->reserved3C) {
        case 3:
            _fsysReadDataExec((GSfsysRequest*)work, resource);
            break;
        case 4:
            if (_fsysExpandFileExec((GSfsysRequest*)work, resource) == 1)
                _fsysReadDataExec((GSfsysRequest*)work, resource);
            break;
        case 5:
            if (work->cancelled == 1) {
                _fsysWorkSetTaskStatus(work, 10);
                _fsysResHeaderSetTaskStatus(resource, 1);
            } else {
                s32 active = _fsysGetActiveTask(2);
                if (_fsysGetActiveTask(1) + active == 0) {
                    if (resource->streamBytes <= _fsysStreamGetNormalCacheSize())
                        _fsysReadDataExec((GSfsysRequest*)work, resource);
                } else if (resource->streamBytes <= _fsysStreamGetMinimumCacheSize()) {
                    _fsysReadDataExec((GSfsysRequest*)work, resource);
                }
            }
            break;
        case 2:
            if (work->cancelled == 1) {
                _fsysWorkSetTaskStatus(work, 10);
                _fsysResHeaderSetTaskStatus(resource, 1);
            }
            break;
        }
        complete = 0;
    } else {
        complete = 1;
    }
    interrupts = OSDisableInterrupts();
    if (resource->token != 0xffff) { resource->reserved3C = resource->token; resource->token = 0xffff; }
    OSRestoreInterrupts(interrupts);
    return complete;
}
void _fsysHeaderSizeReadDvdCallback(s32 result, GSdvdWork* dvd) {
    FsysWork* work = _fsysInfo2Work(dvd);
    if (!work) {
        _headerTop = 0;
        _fsysWorkSetTaskStatus(work, 3);
    } else if (result < 0) {
        _headerTop = 0;
        _fsysWorkSetTaskStatus(work, 3);
    } else {
        work->directory->headerLength = _headerTop[7];
        _headerTop = 0;
        _fsysWorkSetTaskStatus(work, 5);
    }
}
void GSfsysDaemonForeground() {
    FsysBackgroundWork* entry = _fsysBGWorkRoot;
    while (entry) {
        FsysBackgroundWork* next = entry->next;
        if (entry->loaded == 1) {
            GSfsysResource* resource = entry->resource;
            FsysWork* work = entry->work;
            u32 index = _fsysID2Index(work, resource->identifier);
            GSfsysResource* previous = index != 0 ? _fsysGetResHeader((GSfsysRequest*)work, index - 1) : 0;
            if (_fsysID2Index(work, work->resourceID) != 0xffff || !previous || (previous->flags & 8)) {
                GSfsysDataType* type = _fsysGetDataType(resource->dataType);
                if (work->cancelled == 0 && type->finish) {
                    if (resource->flags & 0x80000000) type->finish(work->group, resource->identifier, resource->expandedLength);
                    else type->finish(work->group, resource->identifier, resource->length);
                }
                if (entry->dictionary) { _fsysFree((void*)entry->dictionary); entry->dictionary = 0; }
                _fsysDelBGWork(entry);
                resource->flags |= 8;
                _fsysSetLockCacheFlag(work->group, _fsysID2Index(work, resource->identifier), 0);
            } else if (previous && !(previous->flags & 8)) {
                OSReport("<1>-----fsysBGwork:Wait Prev ResFinish Index=%d:%d\n", work->group, _fsysID2Index(work, resource->identifier));
            } else {
                OSReport("<2>-----fsysBGwork:Wait Prev ResFinish Index=%d:%d\n", work->group, _fsysID2Index(work, resource->identifier));
            }
        }
        entry = next;
    }
    for (u32 i = 0; i < _fsysWorkMax; ++i) _fsysForegroundTask(_fsysWork + i);
    _fsysQueExec();
}
void _fsysForegroundTask(FsysWork* work) {
    BOOL interrupts = OSDisableInterrupts();
    if (work->pendingStatus != 0xffff) { work->status = work->pendingStatus; work->pendingStatus = 0xffff; }
    OSRestoreInterrupts(interrupts);
    switch (work->status) {
    case 3:
        if (!_headerTop) {
            _headerTop = headerTop;
            _fsysWorkSetTaskStatus(work, 4);
            if (GSdvdReadAsync((GSdvdWork*)work->dvd, _headerTop, 32, 0, _fsysHeaderSizeReadDvdCallback) == 0) {
                _headerTop = 0;
                _fsysWorkSetTaskStatus(work, 3);
            }
        }
        break;
    case 5:
        switch (work->mode) {
        case 1: _fsysWorkSetTaskStatus(work, 6); _fsysReadRequest((GSfsysRequest*)work); break;
        case 4: _fsysWorkSetTaskStatus(work, 9); _fsysReadRequest((GSfsysRequest*)work); break;
        case 2: _fsysWorkSetTaskStatus(work, 7); _fsysReadRequest((GSfsysRequest*)work); break;
        case 3: _fsysWorkSetTaskStatus(work, 8); _fsysSeekRequest((GSfsysRequest*)work); break;
        default: _fsysWorkSetTaskStatus(work, -1000); break;
        }
        break;
    case 6: case 7: case 9: _fsysCheckExpandCompleteAll(work); break;
    case 10:
        switch (work->mode) {
        case 1: if (!_fsysCheckExpandCompleteAll(work)) break;
        case 2: case 4: _fsysWorkSetTaskStatus(work, 11); break;
        default: _fsysWorkSetTaskStatus(work, -1000); break;
        }
        break;
    case -1000: case -996: case -995: case -994:
        OSReport("_fsysForegroundTask:ERROR...:%d\n", work->group);
        if (_fsysCloseFile(work, 1) == 0) { _fsysWorkSetTaskStatus(work, -997); break; }
    case -998:
        OSReport("_fsysForegroundTask:ERROR_FILEOPEN:%d\n", work->group);
        _fsysOpenFile(work);
        break;
    case -997:
        OSReport("_fsysForegroundTask:ERROR_FILECLOSE:%d\n", work->group);
        _fsysWorkSetTaskStatus(work, -999);
        break;
    case 11:
        if (_fsysCloseFile(work, 0) == 0) _fsysWorkSetTaskStatus(work, -997);
        else {
            if (work->mode >= 5 || work->mode < 3) _fsysOnTOCFlag(work->group, 1);
            _fsysWorkSetTaskStatus(work, 12);
        }
        break;
    case 12:
    case -999:
        break;
    }
    interrupts = OSDisableInterrupts();
    if (work->pendingStatus != 0xffff) { work->status = work->pendingStatus; work->pendingStatus = 0xffff; }
    OSRestoreInterrupts(interrupts);
}
u8 _fsysInitTOC() {
    u32 length;
    GSdvdWork* dvd = GSdvdOpen("gsfsys.toc");
    if (!dvd) return 0;
    length = (GSdvdGetLength(dvd) + 31) & ~31;
    _fsysTOC = (TocHeader*)_fsysDoMalloc(length);
    if (!_fsysTOC) return 0;
    if (GSdvdRead(dvd, _fsysTOC, length, 0) < 0) { GSdvdClose(dvd); return 0; }
    GSdvdClose(dvd);
    TocGroup* group = (TocGroup*)((u8*)_fsysTOC + _fsysTOC->tableOffset);
    for (u32 i = 0; i < _fsysTOC->groupCount; ++i, ++group) {
        group->name = (const char*)((u32)group->name + (u32)_fsysTOC);
        group->flags = 0;
    }
    return 1;
}
void _fsysBackgroundTaskCompressType(FsysBackgroundWork* entry) {
    if (entry->loaded == 1 || _fsysBGTaskCancel(entry) == 1) return;
    GSfsysBlock* block = entry->resource->expandBlocks;
    if (!block) return;
    u32 position;
    if (entry->dictionary == 0) {
        entry->dictionary = (u8*)_fsysAlloc(0x1011);
        if (!entry->dictionary) return;
        memset((void*)entry->dictionary, 0, 0xfee);
        memcpy(entry->flags, block->data, 16);
        entry->dictionaryPosition = 0xfee;
        position = 16;
        entry->tokenFlags = 0;
        entry->payloadBytes = entry->compressedBytes - 16;
        entry->decodeState = 0;
    } else position = 0;
    s32 tokens = entry->tokenCount;
    u32 flags = entry->tokenFlags;
    s32 ringPosition = entry->dictionaryPosition;
    s32 matchPosition = entry->matchPosition;
    u32 consumed = entry->consumedBytes;
    s32 written = entry->writtenBytes;
    u8* output = (u8*)entry->resource->expandedData;
    u32 inputLength = entry->payloadBytes;
    u32 blockBytes = _fsysBlockByteSize;
    u8* ring = (u8*)entry->dictionary;
    s32 state = entry->decodeState;
    u8 value;
    u8* input;
    s32 count;
nextBlock:
    input = (u8*)block->data;
    switch (state) {
    case 1: goto readFlags;
    case 2: goto literal;
    case 3: goto matchLow;
    case 4: goto matchHigh;
    }
nextToken:
    flags >>= 1;
    if (flags & 0x100) goto chooseToken;
readFlags:
    ++consumed;
    value = input[position++];
    if (consumed > inputLength) goto finishBlock;
    if (position > blockBytes) { state = 1; --consumed; goto finishBlock; }
    flags = value | 0xff00;
chooseToken:
    if (!(flags & 1)) goto matchLow;
literal:
    ++consumed;
    value = input[position++];
    if (consumed > inputLength) goto finishBlock;
    if (position > blockBytes) { state = 2; --consumed; goto finishBlock; }
    output[written++] = value;
    ring[ringPosition] = value;
    ringPosition = (ringPosition + 1) & 0xfff;
    goto tokenDone;
matchLow:
    ++consumed;
    matchPosition = input[position++];
    if (consumed > inputLength) goto finishBlock;
    if (position > blockBytes) { state = 3; --consumed; goto finishBlock; }
matchHigh:
    ++consumed;
    value = input[position++];
    if (consumed > inputLength) goto finishBlock;
    if (position > blockBytes) { state = 4; --consumed; goto finishBlock; }
    count = (value & 15) + 2;
    matchPosition |= (value << 4) & 0xf00;
    for (s32 i = 0; i <= count; ++i) {
        value = ring[(matchPosition + i) & 0xfff];
        output[written++] = value;
        ring[ringPosition] = value;
        ringPosition = (ringPosition + 1) & 0xfff;
    }
tokenDone:
    ++tokens;
    goto nextToken;
finishBlock:
    _fsysFreeBlock(&entry->resource->expandBlocks, 1);
    if (consumed > inputLength) {
        DCFlushRange(entry->resource->expandedData, entry->expandedBytes);
        entry->loaded = 1;
        return;
    }
    if (_fsysBGTaskCancel(entry) == 1) return;
    block = entry->resource->expandBlocks;
    if (block) { position = 0; goto nextBlock; }
    entry->tokenCount = tokens;
    entry->tokenFlags = flags;
    entry->matchPosition = matchPosition;
    entry->dictionaryPosition = ringPosition;
    entry->consumedBytes = consumed;
    entry->writtenBytes = written;
    entry->decodeState = state;
}

}
