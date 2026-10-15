#include <game/menuInterruptPrivate.hpp>
extern "C" {
u8 GSflagTest(s32);u32 GSfloorGetCurrent();void *GSgfxLayerFindByID(s32);void GSinputMotorStart(s32,s32,s32,s32,s32);void GSsndPlayNow(u32);f64 cos(f64);u8 floorDataBiosGetFloorKind(void*);void *floorDataBiosGetPtr(u32);s32 gamedatasaveGetStatus(s32,s32);void menuButtonNormal(tagWINDOW_WORK*);void menuClose(s32);void menuCloseSync(s32,s32);u8 menuIsCheck(s32);void menuOpenCustom(s32,s32,s32,s32,s32,s32,...);f32 timeGetLastFrameSec();u8 winSeqCheckMove(s32);void winSeqSetMenu(s32,s32);s32 winSpriteGetLayerID(tagWINDOW_WORK*,tagSPRITE_WORK*);void winSpriteSetDisp(tagSPRITE_WORK*,s32);
}
static u8 _menuIntGetAlpha2();static u8 _menuIntGetAlpha();static void _menuIntVibSet();
static f32 _menuIntFrameCount,_menuIntFrameCount2;
static u8 _menuIntVibFlag=1,_underTakerIconFlag=1;
extern "C" {
void menuIntUnderTakerOpenIcon(void) {
    if (menuIsCheck(0xC1) != 0) {
        menuClose(0xC1);
        return;
    }
    menuOpenCustom(0xC1, 0, 0, 0, 1, 0);
}

void menuIntUnderTakerMenuClose(void) {
    if (menuIsCheck(0xC1) != 0) {
        menuClose(0xC1);
        menuCloseSync(0xC1, 1);
    }
}

void menuIntUnderTakerMenuOpen(void) {
    _menuIntVibFlag = 1;
    menuOpenCustom(0xC1, 0, 0, 0, 1, 0);
}

void menuIntUnderTakerDispIconRestore2(void) {
    _underTakerIconFlag = 1;
}

void menuIntUnderTakerDispIconOff2(void) {
    _underTakerIconFlag = 0;
}

void menuIntUnderTakerHook(tagWINDOW_WORK *arg0, tagSPRITE_WORK *arg1) {
    u8 temp_r31;

    s32 layer=winSpriteGetLayerID(arg0,arg1);
    GSgfxLayerFindByID(layer);
    void *floor=floorDataBiosGetPtr(GSfloorGetCurrent());
    temp_r31 = floorDataBiosGetFloorKind(floor);
    if (((u8) _underTakerIconFlag != 0) && (GSflagTest(undertakerdata->flag) != 0) && (temp_r31 == 1)) {
        winSpriteSetDisp(arg1, 1);
        if ((s16) arg1->id != 0x65C) {
            return;
        }
        if ((s8) arg0->mode != 0) {
            arg1->alpha = _menuIntGetAlpha2();
        }
    } else {
        winSpriteSetDisp(arg1, 0);
    }
}

static u8 _menuIntGetAlpha2(void) {
    s32 var_r31;

    f32 wave = 1.0f + (f32)cos((6.2831855f * _menuIntFrameCount2) / 1.5f);
    f32 alpha = wave * 0.5f;
    var_r31 = (s32)(300.0f * alpha);
    if ((u16) var_r31 > 0xFFU) {
        var_r31 = 0xFF;
    }
    if ((u16) var_r31 < 0x32U) {
        var_r31 = 0x32;
    }
    _menuIntFrameCount2 += timeGetLastFrameSec();
    return (u8) var_r31;
}

s32 menuIntUnderTakerMainCtrl(tagWINDOW_WORK *arg0) {
    u8 temp_r0;

    temp_r0 = arg0->mode;
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        GSsndPlayNow(0x5B4);
        if ((u8) _menuIntVibFlag != 0) {
            _menuIntVibSet();
        }
        if ((s8) arg0->sub == 0) {
            winSeqSetMenu(arg0->id, 0x171);
            arg0->sub = 1U;
        }
        _menuIntVibFlag = 1;
        break;
    case 3:
        if ((s8) arg0->sub == 0) {
            winSeqSetMenu(arg0->id, 0x177);
            arg0->sub = 1U;
        }
        break;
    }
    return 0;
}

void menuIntHook(tagWINDOW_WORK *arg0, tagSPRITE_WORK *arg1) {
    s16 temp_r0;
    s32 *temp_r3;

    temp_r0 = arg1->id;
    temp_r3 = arg0->data;
    switch (temp_r0) {                              /* irregular */
    case 0x4BE:
        if ((s32) *temp_r3 != 0) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        winSpriteSetDisp(arg1, 1);
        if ((s8) arg0->mode != 0) {
            arg1->alpha = _menuIntGetAlpha();
            return;
        }
        return;
    case 0x505:
        if ((s32) *temp_r3 != 1) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        winSpriteSetDisp(arg1, 1);
        if ((s8) arg0->mode != 0) {
            arg1->alpha = _menuIntGetAlpha();
            return;
        }
        break;
    case 0x506:
        if ((s32) *temp_r3 != 2) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        winSpriteSetDisp(arg1, 1);
        if ((s8) arg0->mode != 0) {
            arg1->alpha = _menuIntGetAlpha();
        }
        break;
    }
}

static u8 _menuIntGetAlpha(void) {
    s32 var_r31;

    f32 wave = 1.0f + (f32)cos((6.2831855f * _menuIntFrameCount) / 1.5f);
    f32 alpha = wave * 0.5f;
    var_r31 = (s32)(300.0f * alpha);
    if ((u16) var_r31 > 0xFFU) {
        var_r31 = 0xFF;
    }
    if ((u16) var_r31 < 0x32U) {
        var_r31 = 0x32;
    }
    _menuIntFrameCount += timeGetLastFrameSec();
    return (u8) var_r31;
}

void menuIntButton(tagWINDOW_WORK *arg0) {
    if (winSeqCheckMove(arg0->id) == 0) {
        menuButtonNormal(arg0);
    }
}

s32 menuIntMainCtrl(tagWINDOW_WORK *arg0) {
    s32 *temp_r31;
    s32 temp_r0_2;
    u32 var_r3;
    u8 temp_r0;

    temp_r0 = arg0->mode;
    temp_r31 = arg0->data;
    switch ((s8) temp_r0) {                         /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        _menuIntVibSet();
        temp_r0_2 = *temp_r31;
        var_r3 = 0U;
        switch (temp_r0_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            var_r3 = 0x566U;
            break;
        case 1:                                     /* switch 2 */
            var_r3 = 0x564U;
            break;
        case 2:                                     /* switch 2 */
            var_r3 = 0x565U;
            break;
        }
        if (var_r3 != 0U) {
            GSsndPlayNow(var_r3);
        }
        if ((s8) arg0->sub == 0) {
            winSeqSetMenu(arg0->id, 0x171);
            arg0->sub = 1U;
        }
        break;
    case 3:                                         /* switch 1 */
        if ((s8) arg0->sub == 0) {
            winSeqSetMenu(arg0->id, 0x177);
            arg0->sub = 1U;
        }
        break;
    }
    return 0;
}

static void _menuIntVibSet(void) {
    if (gamedatasaveGetStatus(0, 9) == 0) {
        GSinputMotorStart(1, 0, 0xFF, 0x1E, 0);
    }
}

}
