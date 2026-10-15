#include <game/pxdvs/GSAPI/GSgfxM/resetPrivate.hpp>
extern "C" {
void GSmtx44Ortho(Mtx44,f32,f32,f32,f32,f32,f32);
void* GSgfxVFGetPredef(u32);
void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(GSgfxLayer*,void*);
void beginSurface__10GSgfxLayerFUs(GSgfxLayer*,u16);
void endSurface__10GSgfxLayerFv(GSgfxLayer*);
f32 GSgfxVideoGetLastRealRenderTime();
u8 GSgfxVideoGetVsyncRate();
}
#include <global.h>
static s32 _resetState;
static u8 _resetEnable;
static s32 _resetType;
static u8 (*_resetRenderCBFunc)(void*);
static void* _resetRenderCBArg;
static void (*_resetShutdownCBFunc)();
static s32 _resetFadeAlpha;
static u8 _resetDoFade(void*);
extern "C" {
s32 OSGetResetButtonState(); s32 DBIsDebuggerPresent(); void PADRecalibrate(u32);
void OSSetIdleFunction(void(*)(),u32,void*,u32); void OSResetSystem(s32,u32,s32);

}
extern void GSgfxShutdown();
void GSgfxResetUpdate() {
    switch(_resetState) {
    case 0: if(_resetEnable && OSGetResetButtonState()==1) _resetState=1; break;
    case 1: if(_resetEnable && OSGetResetButtonState()==0) { _resetState=2; _resetType=0; } break;
    case 2: if(_resetRenderCBFunc(_resetRenderCBArg)==1) _resetState=3; break;
    case 3:
        if(DBIsDebuggerPresent()==1) _resetState=0;
        else {
            if(_resetShutdownCBFunc) _resetShutdownCBFunc();
            PADRecalibrate(0xf0000000);
            OSSetIdleFunction(0,0,0,0);
            GSgfxShutdown();
            switch(_resetType) {
            case 0: OSResetSystem(0,0,0); break;
            case 1: OSResetSystem(1,0,0); break;
            case 2: OSResetSystem(1,0,1); break;
            }
        }
        break;
    }
}
extern "C" {
void GSgfxReset(s32 type) { if(_resetState==0) { _resetType=type; _resetState=2; } }
u8 GSgfxResetGetStatus() { return _resetEnable; }
u8 GSgfxResetRestore(u8 enabled) { u8 old=_resetEnable; _resetEnable=enabled; return old; }
u8 GSgfxResetDisable() { u8 old=_resetEnable; _resetEnable=0; return old; }
u8 GSgfxResetEnable() { u8 old=_resetEnable; _resetEnable=1; return old; }
void GSgfxResetSetShutdownCallback(void(*callback)()) { if(_resetState==0) _resetShutdownCBFunc=callback; }
}
void GSgfxResetInit() { _resetEnable=0; _resetState=0; _resetRenderCBFunc=_resetDoFade; _resetRenderCBArg=0; _resetShutdownCBFunc=0; }
static u8 _resetDoFade(void*) {
    Mtx44 projection;
    f32 temp_f31;
    SpriteMatrixFrame* temp_r3_2;
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r7;
    SpriteMatrixStack* temp_r30;
    GSgfxLayer* temp_r3;

    temp_r3 = GSgfxLayerFindByID(7);
    if (temp_r3 == NULL) {
        return 1;
    }
    temp_r3->unk1656 = 1;
    temp_r3->unk1657 = 0;
    temp_r3->unk1658 = 0;
    temp_r3->unk170C = (s32) (temp_r3->unk170C | 4);
    temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 0x40);
    temp_r3->unk17C4 = (s32) (temp_r3->unk17C4 | 4);
    temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 0x40);
    GSmtx44Ortho(projection, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    temp_r3->unkD54 = 1;
    temp_r3->unkD58 = projection[0][0];
    temp_r3->unkD5C = projection[0][3];
    temp_r3->unkD60 = projection[1][1];
    temp_r3->unkD64 = projection[1][3];
    temp_r3->unkD68 = projection[2][2];
    temp_r3->unkD6C = projection[2][3];
    temp_r30 = temp_r3->unk19A0;
    memcpy(temp_r30->frame->matrix, mtxIdent, 0x30);
    temp_r3_2 = temp_r30->frame;
    temp_r3_2->flags |= 1;
    temp_r3->unk1684 = 0.0f;
    temp_r3->unk1688 = 30000.0f;
    if ((u8) temp_r3->unk16A7 != 0) {
        if ((u8) temp_r3->unk16A6 != 0) {
            temp_r3->unk170C = (s32) (temp_r3->unk170C | 0x100);
            temp_r3->unk17C4 = (s32) (temp_r3->unk17C4 | 0x100);
        }
        temp_r3->unk170C = (s32) (temp_r3->unk170C | 0x40);
        temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 0x40);
        temp_r3->unk17C4 = (s32) (temp_r3->unk17C4 | 0x40);
        temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 0x40);
    }
    temp_r3->unk16AC = (s32) (temp_r3->unk16AC | 0x20);
    temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 1);
    temp_r3->unk1764 = (s32) (temp_r3->unk1764 | 0x20);
    temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 1);
    if ((s32) temp_r3->unk1994 != 1) {
        temp_r3->unk1994 = 1;
        temp_r3->unk1990 = temp_r3->shaders[temp_r3->unk1994];
    }
    temp_r3->unk1644 = 1;
    temp_r3->unk1648 = 4;
    temp_r3->unk164C = 5;
    temp_r3->unk1650 = 5;
    temp_r3->unk170C = (s32) (temp_r3->unk170C | 1);
    temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 0x40);
    temp_r3->unk17C4 = (s32) (temp_r3->unk17C4 | 1);
    temp_r7 = temp_r3->unk1760 | 0x40;
    temp_r3->unk1760 = temp_r7;
    temp_r3->unk165C = 0;
    temp_r3->unk1660 = 3;
    temp_r3->unk170C = (s32) (temp_r3->unk170C | 8);
    temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 0x40);
    temp_r3->unk17C4 = (s32) (temp_r3->unk17C4 | 8);
    temp_r5 = temp_r3->unk1760 | 0x40;
    temp_r3->unk1760 = temp_r5;
    temp_r3->unk1664 = 7;
    temp_r3->unk1670 = 0;
    temp_r3->unk1668 = 0;
    temp_r3->unk166C = 7;
    temp_r3->unk1671 = 0;
    temp_r3->unk1672 = 1;
    temp_r3->unk170C = (s32) (temp_r3->unk170C | 0x10);
    temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 0x40);
    temp_r3->unk17C4 = (s32) (temp_r3->unk17C4 | 0x10);
    temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 0x40);
    temp_r3->unkD8C = 0;
    temp_r3->unk16B8 = (s32) (temp_r3->unk16B8 | 2);
    temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 2);
    temp_r3->unk1770 = (s32) (temp_r3->unk1770 | 2);
    temp_r4 = temp_r3->unk1760 | 2;
    temp_r3->unk1760 = temp_r4;
    temp_r3->unkD90 = 1;
    temp_r3->unk16B8 = (s32) (temp_r3->unk16B8 | 4);
    temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 2);
    temp_r3->unk1770 = (s32) (temp_r3->unk1770 | 4);
    temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 2);
    setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(temp_r3, GSgfxVFGetPredef(0));
    temp_r3->unk1998 = 0x98;
    beginSurface__10GSgfxLayerFUs(temp_r3, 4);
    f32 zero=0.0f, width=640.0f, height=480.0f;
    s32 alpha;
    *(volatile f32*)0xcc008000 = zero;
    *(volatile f32*)0xcc008000 = zero;
    *(volatile f32*)0xcc008000 = zero;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = 0;
    alpha=_resetFadeAlpha;
    *(volatile u8*)0xcc008000 = alpha;
    *(volatile f32*)0xcc008000 = width;
    *(volatile f32*)0xcc008000 = zero;
    *(volatile f32*)0xcc008000 = zero;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = alpha;
    *(volatile f32*)0xcc008000 = zero;
    *(volatile f32*)0xcc008000 = height;
    *(volatile f32*)0xcc008000 = zero;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = alpha;
    *(volatile f32*)0xcc008000 = width;
    *(volatile f32*)0xcc008000 = height;
    *(volatile f32*)0xcc008000 = zero;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = 0;
    *(volatile u8*)0xcc008000 = alpha;
    endSurface__10GSgfxLayerFv(temp_r3);
    if ((s32) _resetFadeAlpha == 0xFF) {
        _resetFadeAlpha = 0;
        return 1;
    }
    temp_f31 = GSgfxVideoGetLastRealRenderTime();
    f32 rate=(f32)(0x100/(s32)GSgfxVideoGetVsyncRate());
    f32 opacity=(f32)_resetFadeAlpha;
    temp_r0=(s32)(rate*temp_f31+opacity);
    _resetFadeAlpha = temp_r0;
    if (temp_r0 > 0xFF) {
        _resetFadeAlpha = 0xFF;
    }
    return 0;
}
