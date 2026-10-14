#include <game/pxdvs/GSAPI/GSdvd/GSdvd.hpp>
#include <game/pxdvs/GSAPI/GSmemman/GSmemman.hpp>
#include <dolphin/os.h>
static u8 _initFlag;
static u16 _DvdServerPort;
extern "C" u8 _DvdServerON;
u8 _DvdServerON;
static u16 _ReportServerPort;
extern "C" u8 _ReportServerON, _GCClientON;
u8 _ReportServerON, _GCClientON;
static u32 _errorState;
static s32 _GappHandle;
static GSdvdWork* _dvdWork;
static u32 _maxDvdWork;
static u32 _DvdServerAddr = 0, _ReportServerAddr = 0, _GCClientAddr = 0, _Netmask = 0, _Gateway = 0;
static u32 _errorMsg_CoverOpen = 1, _errorMsg_NoDisc = 1, _errorMsg_WrongDisc = 1, _errorMsg_Retry = 1, _errorMsg_FatalError = 1;
static const char* _diskid_gameName = "GXXJ";
static const char* _diskid_company = "01";
extern "C" {
void winMsgOpenError(u32, u32, u32);
void winMsgCloseError(u32);
void GSgfxResetDisable();
void GSlogWrite(const char*, ...);
void GSlogSetIP(u32*, u16);
void GSnetworkSetIP(u32*, u32*, u32*);
s32 pokecoloGetRomVersion();
s32 pokecoloGetCountryCode();
s32 GSgappCreate(u32, u32, u32, void (*)());
void GSgappSetName(s32, const char*);
#pragma dont_inline on
static GSdvdWork* _getNewDvdWork();
static void _freeDvdWork(GSdvdWork*);
static GSdvdWork* _info2work(DVDFileInfo*);
static void _AsyncCallback(s32, DVDFileInfo*);
static void _AsyncReadCallback(s32, DVDFileInfo*);
s32 GSdvdFstRefresh() { return 0; }
static void _gsdvdError_MsgOpen(u32 message) { if (message != 1) winMsgOpenError(message, 1, 1); }
static void _errorTask_State_None(s32 drive) {
    switch (drive) {
    case -1: _errorState = 9; break;
    case 5: _errorState = 1; break;
    case 4: _errorState = 3; break;
    case 6: _errorState = 5; break;
    case 11: _errorState = 7; break;
    }
}
static void _gsdvdErrorTask() {
    s32 drive = GSdvdGetDriveStatus();
    switch (_errorState) {
    case 0: _errorTask_State_None(drive); break;
    case 1: _gsdvdError_MsgOpen(_errorMsg_CoverOpen); _errorState = 2; break;
    case 2:
        GSlogWrite("[GSDVD_ERROR_STATE_COVEROPEN_WAIT]  status = %d\n", drive);
        if (drive != 5 && drive != 2) { winMsgCloseError(1); _errorState = 0; }
        break;
    case 3: _gsdvdError_MsgOpen(_errorMsg_NoDisc); _errorState = 4; break;
    case 4: if (drive != 4) { winMsgCloseError(1); _errorState = 0; } break;
    case 5: _gsdvdError_MsgOpen(_errorMsg_WrongDisc); _errorState = 6; break;
    case 6: if (drive != 6) { winMsgCloseError(1); _errorState = 0; } break;
    case 7: _gsdvdError_MsgOpen(_errorMsg_Retry); _errorState = 8; break;
    case 8: if (drive != 11) { winMsgCloseError(1); _errorState = 0; } break;
    case 9: GSgfxResetDisable(); _gsdvdError_MsgOpen(_errorMsg_FatalError); _errorState = 10; break;
    case 10: break;
    }
}
void GSdvdSetErrorMsg(u32 cover, u32 noDisc, u32 wrong, u32 retry, u32 fatal) {
    _errorMsg_CoverOpen = cover; _errorMsg_NoDisc = noDisc; _errorMsg_WrongDisc = wrong; _errorMsg_Retry = retry; _errorMsg_FatalError = fatal;
}
u8 GSdvdSeekAsync(GSdvdWork* work, s32 offset, GSdvdCallback callback) {
    if (!_initFlag) return 0;
    if (!work) return 0;
    work->callback = callback;
    return DVDSeekAsyncPrio(&work->info, offset, _AsyncCallback, 2);
}
s32 GSdvdGetFileInfoStatus(GSdvdWork* work) {
    if (!_initFlag) return -1;
    if (!work) return -1;
    return DVDGetCommandBlockStatus(&work->info.cb);
}
s32 GSdvdGetDriveStatus() { if (!_initFlag) return -1; return DVDGetDriveStatus(); }
s32 GSdvdWrite() { return -1; }
s32 GSdvdRemove() { return 0 & ~-((_initFlag == 0) & 1); }
s32 GSdvdCreate() { return 0; }
u32 GSdvdGetLength(GSdvdWork* work) { if (!_initFlag) return 0; if (!work) return 0; return work->info.length; }
s32 GSdvdClose(GSdvdWork* work) { if (!_initFlag) return 0; if (!work) return 0; _freeDvdWork(work); return DVDClose(&work->info); }
u8 GSdvdReadAsync(GSdvdWork* work, void* buffer, s32 length, s32 offset, GSdvdCallback callback) {
    if (!_initFlag) return 0;
    if (!work) return 0;
    work->callback = callback;
    if ((u32)buffer & 31) return 0;
    if (length & 31) return 0;
    if (offset & 3) return 0;
    work->buffer = buffer; work->length = length;
    return DVDReadAsyncPrio(&work->info, buffer, length, offset, _AsyncReadCallback, 2);
}
s32 GSdvdRead(GSdvdWork* work, void* buffer, s32 length, s32 offset) {
    if (!_initFlag) return -1;
    if (!work) return -1;
    if ((u32)buffer & 31) return -1;
    if (length & 31) return -1;
    if (offset & 3) return -1;
    return DVDReadPrio(&work->info, buffer, length, offset, 2);
}
u32 GSdvdOpenTest(const char* path) { if (!_initFlag) return 0; return DVDConvertPathToEntrynum(path) != -1; }
GSdvdWork* GSdvdOpen(const char* path) {
    if (!_initFlag) return 0;
    GSdvdWork* work = _getNewDvdWork();
    if (!work) return 0;
    if (!DVDOpen(path, &work->info)) { _freeDvdWork(work); return 0; }
    return work;
}
// Network address conversion is disabled in the original release.
static s32 _SOInetAtoN(const char*, u32*) { return 0; }
void GSdvdSetGCClient(const char* address, const char* mask, const char* gateway, u8 apply) {
    _SOInetAtoN(address, &_GCClientAddr); _SOInetAtoN(mask, &_Netmask); _SOInetAtoN(gateway, &_Gateway);
    _GCClientON = 1;
    if (apply == 1) GSnetworkSetIP(&_GCClientAddr, &_Netmask, &_Gateway);
}
void GSdvdSetReportServer(const char* address, u16 port, u8 apply) {
    _SOInetAtoN(address, &_ReportServerAddr); _ReportServerPort = port; _ReportServerON = 1;
    if (apply == 1) GSlogSetIP(&_ReportServerAddr, port);
}
void GSdvdSetDVDServer(const char* address, u16 port) { _SOInetAtoN(address, &_DvdServerAddr); _DvdServerPort = port; _DvdServerON = 1; }
static void _initDvdWork() { for (u32 i = 0; i < _maxDvdWork; ++i) _dvdWork[i].inUse = 0; }
static void* _dvdDoMalloc(u32 size) { return GSmemAllocAlign(size, 32); }
s32 GSdvdInit(u32 count) {
    if (_initFlag == 1) return 0;
    _maxDvdWork = count; _dvdWork = (GSdvdWork*)_dvdDoMalloc(count * sizeof(GSdvdWork));
    if (!_dvdWork) return 0;
    _initDvdWork(); DVDInit();
    if (pokecoloGetRomVersion() != 4) {
        switch (pokecoloGetCountryCode()) { case 0: _diskid_gameName = "GXXJ"; break; case 1: _diskid_gameName = "GXXE"; break; case 2: _diskid_gameName = "GXXP"; break; }
        DVDDiskID* id = DVDGetCurrentDiskID();
        id->gameName[0] = _diskid_gameName[0]; id->gameName[1] = _diskid_gameName[1]; id->gameName[2] = _diskid_gameName[2]; id->gameName[3] = _diskid_gameName[3];
        id->company[0] = _diskid_company[0]; id->company[1] = _diskid_company[1]; id->diskNumber = 0; id->gameVersion = 0;
    }
    DVDSetAutoFatalMessaging(1);
    _GappHandle = GSgappCreate(1, 19, 0, _gsdvdErrorTask); GSgappSetName(_GappHandle, "GSdvdErrorTask");
    _initFlag = 1; return 1;
}
static void _AsyncCallback(s32 result, DVDFileInfo* info) {
    GSdvdWork* work = _info2work(info);
    if (work && work->callback) work->callback(result, work);
}
static void _AsyncReadCallback(s32 result, DVDFileInfo* info) {
    GSdvdWork* work = _info2work(info);
    if (work && work->callback) { DCInvalidateRange(work->buffer, work->length); work->callback(result, work); }
}
static GSdvdWork* _info2work(DVDFileInfo* info) {
    s32 index = 0; GSdvdWork* work = _dvdWork;
    for (u32 count = _maxDvdWork; count > 0; --count, ++work, ++index) {
        if (work->inUse && &work->info == info) return &_dvdWork[index];
    }
    return 0;
}
static void _freeDvdWork(GSdvdWork* work) { BOOL interrupts = OSDisableInterrupts(); work->inUse = 0; OSRestoreInterrupts(interrupts); }
static GSdvdWork* _getNewDvdWork() {
    BOOL interrupts = OSDisableInterrupts();
    GSdvdWork* result = 0; s32 index = 0; GSdvdWork* work = _dvdWork;
    for (u32 count = _maxDvdWork; count > 0; --count, ++work, ++index) {
        if (work->inUse != 1) { _dvdWork[index].inUse = 1; result = &_dvdWork[index]; break; }
    }
    OSRestoreInterrupts(interrupts); return result;
}
#pragma dont_inline reset
}
