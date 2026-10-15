#include <game/menuPcBoxPokemonLayout.hpp>
extern "C" {u32 GSflagGet(u32);u32 GSmsgGetRect(u32);void GSmsgPrint2(s32,s16,s16,u32,u32);f32 timeGetLastFrameSec();f32 menuGetLastTime();double sin(double);void winAnimeCursor(tagWINDOW_WORK*,tagSPRITE_WORK*);void winSetSequence(void*,s32);void winSpriteSetDisp(tagSPRITE_WORK*,s32);void winSeqSetMenu(s32,s32);s32 pokecoloGetRomVersion();}
f32 _fieldMenuTimer;f32 _menuFieldCursorAngle;u8 _openFieldMenu;u32 _soundEnvID;s32 _soundEnvVol;
static f32 _menuFiledAlpha[5];static s32 barcolor=0xC0C0D000;static f32 _cursorSec=0.8f;static f32 _max_alpha=255.0f;static f32 _min_alpha=200.0f;
static void _menuFieldMenuCursor(tagWINDOW_WORK*,tagSPRITE_WORK*,long);static void _menuFieldFlashCursor(tagWINDOW_WORK*,tagSPRITE_WORK*,long);static void _menuFieldCursorCheck(tagWINDOW_WORK*,tagSPRITE_WORK*,long);static void _menuFieldDrawItemSub(tagWINDOW_WORK*,tagSPRITE_WORK*,long);static void _animAlpha(long);static s32 _menuFieldCheckCursor(long);static u8 _menuFieldCheckPDA();
extern "C" void menuFieldDrawItem2(tagWINDOW_WORK *arg0,tagSPRITE_WORK *arg1) {
    s16 temp_r0;

    temp_r0 = arg1->id;
    switch (temp_r0) {                              /* irregular */
    case 0x15:
        _menuFieldDrawItemSub(arg0,arg1,0);
        return;
    case 0x16:
        _menuFieldDrawItemSub(arg0,arg1,1);
        return;
    case 0x17:
        _menuFieldDrawItemSub(arg0,arg1,2);
        return;
    case 0x18:
        _menuFieldDrawItemSub(arg0,arg1,3);
        return;
    case 0x19:
        _menuFieldDrawItemSub(arg0,arg1,4);
        return;
    case 0x1A:
        _menuFieldFlashCursor(arg0,arg1,0);
        return;
    case 0x1B:
        _menuFieldFlashCursor(arg0,arg1,1);
        return;
    case 0x1C:
        _menuFieldFlashCursor(arg0,arg1,2);
        return;
    case 0x1D:
        _menuFieldFlashCursor(arg0,arg1,3);
        return;
    case 0x1E:
        _menuFieldFlashCursor(arg0,arg1,4);
        return;
    case 0x66B:
        _menuFieldMenuCursor(arg0,arg1,0);
        return;
    case 0x66C:
        _menuFieldMenuCursor(arg0,arg1,1);
        return;
    case 0x66D:
        _menuFieldMenuCursor(arg0,arg1,2);
        return;
    case 0x66E:
        _menuFieldMenuCursor(arg0,arg1,3);
        return;
    case 0x66F:
        _menuFieldMenuCursor(arg0,arg1,4);
        return;
    case 0x1F:
        _menuFieldCursorCheck(arg0,arg1,0);
        return;
    case 0x20:
        _menuFieldCursorCheck(arg0,arg1,1);
        return;
    case 0x21:
        _menuFieldCursorCheck(arg0,arg1,2);
        return;
    case 0x22:
        _menuFieldCursorCheck(arg0,arg1,3);
        return;
    case 0x23:
        _menuFieldCursorCheck(arg0,arg1,4);
        return;
    case 0x2C3:
        _menuFieldDrawItemSub(arg0,arg1,0);
        return;
    case 0x2C4:
        _menuFieldDrawItemSub(arg0,arg1,1);
        return;
    case 0x2C5:
        _menuFieldDrawItemSub(arg0,arg1,2);
        return;
    case 0x2C6:
        _menuFieldDrawItemSub(arg0,arg1,3);
        return;
    case 0x2C7:
        _menuFieldFlashCursor(arg0,arg1,0);
        return;
    case 0x2C8:
        _menuFieldFlashCursor(arg0,arg1,1);
        return;
    case 0x2C9:
        _menuFieldFlashCursor(arg0,arg1,2);
        return;
    case 0x2CA:
        _menuFieldFlashCursor(arg0,arg1,3);
        return;
    case 0x670:
        _menuFieldMenuCursor(arg0,arg1,0);
        return;
    case 0x671:
        _menuFieldMenuCursor(arg0,arg1,1);
        return;
    case 0x672:
        _menuFieldMenuCursor(arg0,arg1,2);
        return;
    case 0x673:
        _menuFieldMenuCursor(arg0,arg1,3);
        return;
    case 0x2CB:
        _menuFieldCursorCheck(arg0,arg1,0);
        return;
    case 0x2CC:
        _menuFieldCursorCheck(arg0,arg1,1);
        return;
    case 0x2CD:
        _menuFieldCursorCheck(arg0,arg1,2);
        return;
    case 0x2CE:
        _menuFieldCursorCheck(arg0,arg1,3);
        return;
    }
}

static void _menuFieldMenuCursor(tagWINDOW_WORK *arg0,tagSPRITE_WORK *arg1,long arg2) {
    s16 temp_r0;

    temp_r0 = arg0->selected;
    s16 previous=*(s16*)((u8*)arg0+0xA2);
    if (temp_r0 == arg2) {
        if (previous != temp_r0) {
            winAnimeCursor(arg0,arg1);
            _fieldMenuTimer = 0.0f;
        }
        winSpriteSetDisp(arg1, 1);
    } else {
        winSpriteSetDisp(arg1, 0);
    }
    if ((s8) arg0->phase == 3) {
        winSetSequence(arg1->sequence, 0);
    }
}

static void _menuFieldFlashCursor(tagWINDOW_WORK *arg0,tagSPRITE_WORK *arg1,long arg2) {
    if ((s16) arg0->selected == arg2) {
        *(f32*)((u8*)arg1+0x70) = (f32) _menuFieldCursorAngle;
        winSpriteSetDisp(arg1, 1);
        return;
    }
    winSpriteSetDisp(arg1, 0);
}

static void _menuFieldCursorCheck(tagWINDOW_WORK *w,tagSPRITE_WORK *s,long index){s16 x;u32 color;s32 selected=w->selected;winSpriteSetDisp(s,0);if(s->message){if(selected==index)color=0xF0F0F0FF;else color=0xF0F0F080;x=(s->width-(s16)(GSmsgGetRect(s->message)>>16))/2;u16 height=GSmsgGetRect(s->message);s16 y=(s->height-(s16)height)/2-2;GSmsgPrint2(w->layer,x,y,color,s->message);}}

static void _menuFieldDrawItemSub(tagWINDOW_WORK *arg0,tagSPRITE_WORK *arg1,long arg2) {
    f32 temp_f0;
    f32 temp_f2;
    s16 temp_r31;

    temp_r31 = arg0->selected;
    temp_f2 = (255.0f * timeGetLastFrameSec()) / 0.4f;
    if (temp_r31 == arg2) {
        winSpriteSetDisp(arg1, 1);
        _animAlpha(arg2);
    } else {
        temp_f0 = _menuFiledAlpha[arg2];
        if (temp_f0 > 0.0f) {
            _menuFiledAlpha[arg2] = temp_f0 - temp_f2;
            if (_menuFiledAlpha[arg2] < 0.0f) {
                _menuFiledAlpha[arg2] = 0.0f;
            }
        }
    }
    arg1->color.value = (s32) (barcolor | (u8) (s32) _menuFiledAlpha[arg2]);
}

static void _animAlpha(long arg0) {
    f32 temp_f1;
    f32 temp_f31;
    f32 var_f1;

    temp_f1 = _fieldMenuTimer + ((3.1415927f * (2.0f * menuGetLastTime())) / _cursorSec);
    _fieldMenuTimer = temp_f1;
    if (temp_f1 >= 6.2831855f) {
        _fieldMenuTimer = temp_f1 - 6.2831855f;
    }
    temp_f31 = _max_alpha - _min_alpha;
    f32 wave=(1.0f+(f32)sin(_fieldMenuTimer))/2.0f;
    f32 scaled=temp_f31*wave;
    var_f1=scaled+_min_alpha;
    if (var_f1 > 255.0f) {
        var_f1 = 255.0f;
    }
    _menuFiledAlpha[arg0] = var_f1;
}

extern "C" s32 menuFieldMainCtrl(tagWINDOW_WORK *arg0) {
    f32 *temp_r3;
    f32 *temp_r3_2;
    s32 i;
    s32 temp_r4;
    u8 temp_r0;

    temp_r0 = arg0->phase;
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        if ((s8) arg0->step == 0) {
            winSeqSetMenu(arg0->menu, 1);
            temp_r4 = arg0->selected;
            _fieldMenuTimer = 0.0f;
            for(i=0;i<5;i++){if(temp_r4==i)_menuFiledAlpha[i]=255.0f;else _menuFiledAlpha[i]=0.0f;}
            arg0->step = 1U;
        }
        break;
    case 3:
        if ((s8) arg0->step == 0) {
            winSeqSetMenu(arg0->menu, 7);
            arg0->step = 1U;
        }
        break;
    }
    return 0;
}

class GSvec {public:f32 x,y,z;GSvec(){}};
struct FieldEvent {GSvec points[3];u8 pad24[12];u16 script;u8 pad32[2];};
extern "C" {u8 GSgfxVideoGetVsyncRate();void GSgfxVideoSetLockFrameRate(s32);void GSmodelAllPauseAnimation();void GSmodelAllUnpauseAnimation();void GSsndPopVolumeALL(s32,s32,s32);void GSsndPushVolumeALL(s32,s32,s32,s32);void GSthreadSwitch();s8 fadeCheck(s32);void floorEventExecScript(s32,u16);void floorFieldCameraPause();void floorFieldCameraUnpause();void fn_80233AB4();void heroMoveAddAutoEvent(u32,u16,s32,s32,s32);s32 heroMoveCheckEvent(FieldEvent*);void heroMoveInitEvent();void heroMoveTermEvent();void mailMainReceiveTerminate();void menuClose(s32);void menuCloseCustom(s32,s32,s32);void menuCloseSync(s32,s32);void menuCreateOffScreen(u8,f32,f32);u8 menuGetOffScreenFlag();void menuIntUnderTakerDispIconOff2();void menuIntUnderTakerDispIconRestore2();void menuOffScreenRelease();s32 menuOpen(s32,s32);void menuPdaOpen();u32 menuPocket2GetItemScript(u32);u16 menuPocket2Open(s32,s32*,s32);void menuPokemonOpen(s32,s32,s32);void menuReleaseOffScreen(u8,f32);void menuReport();s32 scriptContinueSave();u32 soundGetEnvID();s32 soundGetVolume();void soundSetVolumeID(u32,s32,s32);}
extern "C" s32 menuFieldMain(u8 arg0) {
    FieldEvent events[4];
    s32 sp8;u32 script;
    FieldEvent *var_r28;
    s32 var_r27_2;
    s32 temp_r29;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 var_r27;
    u16 var_r31;
    u32 temp_r3_2;
    u8 temp_r3;
    u8 temp_r3_5;

    if (fadeCheck(0) != 0) {
        return 0;
    }
    temp_r29 = heroMoveCheckEvent(events);
    var_r28 = events;
    var_r27 = 0;
loop_4:
    if (var_r27 < temp_r29) {
        floorEventExecScript(4, var_r28->script);
        var_r28++;
        var_r27 += 1;
        goto loop_4;
    }
    menuIntUnderTakerDispIconOff2();
    heroMoveInitEvent();
    mailMainReceiveTerminate();
    GSthreadSwitch();
    floorFieldCameraPause();
    GSmodelAllPauseAnimation();
    _openFieldMenu = 1;
    GSthreadSwitch();
    temp_r3 = GSgfxVideoGetVsyncRate();
    menuCreateOffScreen(temp_r3, 20.0f / (f32) temp_r3, 50.0f);
loop_7:
    if (menuGetOffScreenFlag() == 0) {
        GSthreadSwitch();
        goto loop_7;
    }
    temp_r3_2 = soundGetEnvID();
    _soundEnvID = temp_r3_2;
    if (temp_r3_2 != 0U) {
        _soundEnvVol = soundGetVolume();
    }
    GSsndPushVolumeALL(0x55, 0x1F4, 1, 1);
    GSgfxVideoSetLockFrameRate(0);
    if (GSflagGet(0x30D) == 0U) {
        if (_menuFieldCheckPDA() != 0) {
            var_r27_2 = 0x57;
        } else {
            var_r27_2 = 0x58;
        }
    } else {
        var_r27_2 = 0x70;
    }
    fn_80233AB4();
    switch ((s32) arg0) {                           /* irregular */
    case 0:
        if (GSflagGet(0x30D) == 0U) {
loop_22:
            GSgfxVideoSetLockFrameRate(0);
            _menuFiledAlpha[0] = 255.0f;
            _menuFiledAlpha[1] = 255.0f;
            _menuFiledAlpha[2] = 255.0f;
            _menuFiledAlpha[3] = 255.0f;
            _menuFiledAlpha[4] = 255.0f;
            temp_r3_3 = _menuFieldCheckCursor(menuOpen(var_r27_2,1));
            if (temp_r3_3 == 0) {
                menuCloseCustom(var_r27_2, 0, 1);
                menuPokemonOpen(1, 0, 0);
                GSmodelAllPauseAnimation();
block_32:
                GSthreadSwitch();
                goto loop_22;
            }
            if (temp_r3_3 == 1) {
                menuCloseCustom(var_r27_2, 0, 1);
                menuPdaOpen();
                GSmodelAllPauseAnimation();
                goto block_32;
            }
            if (temp_r3_3 == 2) {
                menuCloseCustom(var_r27_2, 0, 1);
                var_r31 = menuPocket2Open(0, &sp8, 0);
                GSmodelAllPauseAnimation();
                if (var_r31 != 0) {
                    if ((u32) ((script=menuPocket2GetItemScript(var_r31)) + 0x10000) != 0xFFFFU) {
                        heroMoveAddAutoEvent(script,var_r31,sp8,0,0);
                    }
                } else {
                    goto loop_22;
                }
            } else if (temp_r3_3 == 3) {
                menuCloseCustom(var_r27_2, 0, 1);
                menuReport();
                goto block_32;
            }
        } else {
loop_34:
            GSgfxVideoSetLockFrameRate(0);
            temp_r3_4 = menuOpen(var_r27_2, 1);
            if (temp_r3_4 == 0) {
                menuClose(var_r27_2);
                menuPokemonOpen(1, 0, 0);
                goto loop_34;
            }
            if (temp_r3_4 == 1) {
                if (scriptContinueSave() == 1) {
                    menuOffScreenRelease();
                    _openFieldMenu = 0;
                    GSthreadSwitch();
                }
                goto loop_34;
            }
        }
        break;
    case 1:
        var_r31 = menuPocket2Open(0, &sp8, 0);
        if ((var_r31 != 0) && ((u32) ((script=menuPocket2GetItemScript(var_r31)) + 0x10000) != 0xFFFFU)) {
            heroMoveAddAutoEvent(script,var_r31,sp8,0,0);
        }
        break;
    }
    menuPocket2GetItemScript(var_r31);
    GSsndPopVolumeALL(0x1F4, 1, 1);
    if ((u32) _soundEnvID == soundGetEnvID()) {
        soundSetVolumeID(_soundEnvID, 0x1F4, _soundEnvVol);
    }
    GSthreadSwitch();
    menuClose(var_r27_2);
    temp_r3_5 = GSgfxVideoGetVsyncRate();
    menuReleaseOffScreen(temp_r3_5, 20.0f / (f32) temp_r3_5);
    menuCloseSync(var_r27_2, 1);
    GSgfxVideoSetLockFrameRate(1);
    heroMoveTermEvent();
    GSmodelAllUnpauseAnimation();
    floorFieldCameraUnpause();
    _openFieldMenu = 0;
    menuIntUnderTakerDispIconRestore2();
    return 0;
}

extern "C" u8 menuFieldIsOpen(void) {
    return _openFieldMenu;
}

static s32 _menuFieldCheckCursor(long arg0) {
    s32 var_r3;

    if (_menuFieldCheckPDA() != 0) {
        return arg0;
    }
    var_r3 = arg0;
    if (arg0 >= 1) {
        var_r3 = arg0 + 1;
    }
    return var_r3;
}

static u8 _menuFieldCheckPDA(void) {
    if (pokecoloGetRomVersion() == 1) {
        return 1U;
    }
    return GSflagGet(0x3F1) != 0U;
}
