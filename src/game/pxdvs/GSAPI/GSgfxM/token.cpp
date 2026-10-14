#include "graphics_round1.h"
struct TokenRegistration { u16 start,end; void(*callback)(u16); };
ABI_SIZE(TokenRegistration,8); ABI_OFF(TokenRegistration,callback,4);
static TokenRegistration _tokenRegisterList[4];
static u16 _tokenCurrent,_tokenFrameEnd,_tokenFrameStart,_tokenLastGPU,_tokenMaximum;
static u8 _tokenRegisterCount;
extern "C" {
static void _tokenDrawSyncCallback__FUs(u16);
inline u8 validToken(u16 token) { if(token==0 || token>=_tokenMaximum) return 0;return 1; }
inline u8 outsideFrame(u16 token) {
    if(token==0 || token>=_tokenMaximum) return 0;
    if(_tokenFrameStart<=_tokenFrameEnd) { if(token>=_tokenFrameStart && token<=_tokenFrameEnd) return 0; }
    else if(token>=_tokenFrameStart || token<=_tokenFrameEnd) return 0;
    return 1;
}
inline u8 clearedBy(u16 token,u16 gpu) {
    if(_tokenFrameEnd>gpu) { if(token<=gpu || token>_tokenFrameEnd) return 1; }
    else if(token>_tokenFrameEnd && token<=gpu) return 1;
    return 0;
}
inline u8 completedToken(u16 token) {
    if(clearedBy(token,_tokenLastGPU)) return 1;
    u16 gpu=GXReadDrawSync();if(gpu>=_tokenMaximum) return 0;
    if(clearedBy(token,gpu)) return 1;
    return 0;
}
void GSgfxTokenWaitForClearAndReset(u16 *ptr) {
    u16 token; register u16 *saved=ptr; token=*saved; if(*saved!=0) { if(outsideFrame(token)) { GSgfxRenderWaitData data;GSgfxRenderWaitInit__FP19GSgfxRenderWaitData(&data);while(!completedToken(token)) GSgfxRenderWaitTick__FP19GSgfxRenderWaitData(&data);GSgfxRenderWaitExit__FP19GSgfxRenderWaitData(&data); }*saved=0; }
}
void GSgfxTokenIfClearedReset(u16 *ptr) {u16 token;register u16 *saved=ptr;token=*saved;if(*saved!=0) {u8 clear;if(!validToken(*saved)) clear=1;else clear=completedToken(token);if(clear==1) *saved=0;} }
void GSgfxTokenWaitForClear(u16 token) { if(outsideFrame(token)) { GSgfxRenderWaitData data;GSgfxRenderWaitInit__FP19GSgfxRenderWaitData(&data);while(!completedToken(token)) GSgfxRenderWaitTick__FP19GSgfxRenderWaitData(&data);GSgfxRenderWaitExit__FP19GSgfxRenderWaitData(&data); } }
u8 GSgfxTokenCleared(u16 token) {if(!validToken(token)) return 1; return completedToken(token);}

u16 GSgfxTokenMark_Sub__Fv() {
    u16 token=_tokenCurrent; if(token==_tokenFrameEnd) return _tokenFrameEnd;
    GXSetDrawSync(token);if(++_tokenCurrent>=_tokenMaximum) _tokenCurrent=1;return token;
}
void GSgfxTokenMarkFrame__Fv() { _tokenFrameStart=_tokenCurrent;_tokenFrameEnd=_tokenCurrent+0x1000;if(_tokenFrameEnd>=_tokenMaximum) _tokenFrameEnd-=_tokenMaximum; }

void GSgfxTokenSetDrawSyncCBFunc__FPFPFUs_v_v(void (*cb)(void(*)(u16))) { if(cb) cb(_tokenDrawSyncCallback__FUs); }

void GSgfxTokenAbortFrame__Fv(void) {
    _tokenLastGPU = _tokenFrameStart;
}

void GSgfxTokenInit__Fv(void) {
    _tokenLastGPU = 0;
    _tokenCurrent = 1;
    _tokenMaximum = 0xE000;
    _tokenFrameStart = 1;
    _tokenFrameEnd = 0x1001;
    _tokenRegisterList[0].callback = 0;
    _tokenRegisterList[1].callback = 0;
    _tokenRegisterList[2].callback = 0;
    _tokenRegisterList[3].callback = 0;
    _tokenRegisterCount = 0;
    GSgfxGPUSetDrawSyncCallback__FPFUs_v(_tokenDrawSyncCallback__FUs);
}

static void _tokenDrawSyncCallback__FUs(u16 token) {
    for(u8 i=0;i<_tokenRegisterCount;i++) { TokenRegistration *entry=&_tokenRegisterList[i];if(entry->start<=token && entry->end>=token) {entry->callback(token);return;} }
    _tokenLastGPU=token;
}
}
