#include <global.h>
struct FadeWork { u8 unk0,busy; u16 unk2; f32 unk4,unk8; s32 unkC; u32 unk10; f32 unk14,unk18; };
static FadeWork _fadeWork;
static u8 _complete;
extern "C" {
void GSthreadSwitch(); void GSsndPlayNow(s32); void fadeEffectHookFunction_Doku_Init(); void fadeEffectInit(); u32 menuOffScreenGetPtr(); u8 menuOffScreenIsDoing(); void GStextureFree(u32); s32 GSmemGetCurrentHeap(); s32 GSmemSetAllocMethodHeap(s32,s32); u32 GStextureCreate(s32,s32,s32,s32,s32); void GSgfxBeginBackFBCapture(u32,s32(*)(),s32);
void fadeSet(u16,f32); s32 fadeSetEX(u16,void(*)(),u8,f32,f32); static s32 fadeSetFunction__FPFv_vbUsf(void(*)(),u8,u16,f32); static void _fadeSnapshot__Fv(); static s32 myBackFB__FP9GStextureUlPv();
void fadeEffectDokuStop(void) {
    if ((u8) _fadeWork.unk0 == 4) {
        _fadeWork.busy = 0;
        _fadeWork.unk0 = 0;
    }
}

void fadeEffectDokuStart(void) {
    if ((u8) _fadeWork.unk0 == 0) {
        fadeSetEX(9U, fadeEffectHookFunction_Doku_Init, 0U, 1.0f, 0.5f);
        GSsndPlayNow(0x18);
    }
}

u16 fadeGetType(void) {
    return _fadeWork.unk2;
}

s8 fadeCheck(u8 arg0) {
    if (arg0 == 0) {
        return (s8) _fadeWork.busy;
    }
while (_fadeWork.busy == 1) GSthreadSwitch();
    GSthreadSwitch();
    return (s8) _fadeWork.busy;
}

s32 fadeSetEX(u16 arg0, void (*arg1)(), u8 arg2, f32 farg0, f32 farg1) {
    s32 temp_r31;

    temp_r31 = fadeSetFunction__FPFv_vbUsf(arg1, arg2, arg0, farg1);
    fadeSet(arg0, farg0);
    return temp_r31;
}

void fadeSetToBlackInIfBlack(f32 time) {
    if ((u8) _fadeWork.unk0 == 2) {
        fadeSet(2U,time);
    }
}

void fadeSetToBlackOutIfNotBlack(f32 time) {
    if ((u8) _fadeWork.unk0 != 2) {
        fadeSet(3U,time);
    }
}

void fadeSet(u16 arg0, f32 farg0) {
    _fadeWork.busy = 1;
    _fadeWork.unk2 = arg0;
    _fadeWork.unk4 = farg0;
    _fadeWork.unk8 = 0.0f;
    if ((s32) (arg0 & 8) != 0) {
        if ((s32) (arg0 & 1) != 0) {
            _fadeWork.unk0 = 4;
            return;
        }
        _fadeWork.unk0 = 3;
        return;
    }
    if ((s32) (arg0 & 1) != 0) {
        _fadeWork.unk0 = 2;
        return;
    }
    _fadeWork.unk0 = 1;
}

s32 fadeSetFunction__FPFv_vbUsf(void (*arg0)(), u8 arg1, u16 arg2, f32 farg0) {
    s32 temp_r31;

    if (arg0 == NULL) {
        return _fadeWork.unkC;
    }
    _fadeWork.busy = 1;
    _fadeWork.unk2 = arg2;
    _fadeWork.unk14 = farg0;
    _fadeWork.unk18 = 0.0f;
    _fadeWork.unk0 = 0;
    temp_r31 = _fadeWork.unkC;
    _fadeWork.unkC = 0;
    if (arg1 == 1) {
        _fadeSnapshot__Fv();
    } else if ((u32) _fadeWork.unk10 != 0U) {
        if ((u32) _fadeWork.unk10 != menuOffScreenGetPtr()) {
            GStextureFree(_fadeWork.unk10);
        }
        _fadeWork.unk10 = 0U;
    }
    fadeEffectInit();
    arg0();
    return temp_r31;
}

void fadeSetFunctionOnly(s32 arg0) {
    _fadeWork.unkC = arg0;
}

void _fadeSnapshot__Fv(void) {
    s32 temp_r30;
    u32 var_r31;

    var_r31 = _fadeWork.unk10;
    _fadeWork.unk10 = 0U;
    if (menuOffScreenIsDoing() == 0) {
        var_r31 = menuOffScreenGetPtr();
    }
    if (var_r31 == 0U) {
        temp_r30 = GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(),3);
        var_r31 = GStextureCreate(0, 0, 0x44, 0, 0);
        GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(),temp_r30);
    }
    if (var_r31 != 0U) {
        _complete = 0;
        GSgfxBeginBackFBCapture(var_r31, myBackFB__FP9GStextureUlPv, 0);
while (_complete == 0) GSthreadSwitch();
        _fadeWork.unk10 = var_r31;
    }
}

s32 myBackFB__FP9GStextureUlPv(void) {
    _complete = 1;
    return 0;
}

void fadeInit(void) {
    _fadeWork.unk0 = 0;
    _fadeWork.busy = 0;
    _fadeWork.unk2 = 0;
    _fadeWork.unk4 = 0.0f;
    _fadeWork.unk8 = 0.0f;
    _fadeWork.unkC = 0;
    _fadeWork.unk10 = 0;
    _fadeWork.unk14 = 0.0f;
    _fadeWork.unk18 = 0.0f;
}

}
