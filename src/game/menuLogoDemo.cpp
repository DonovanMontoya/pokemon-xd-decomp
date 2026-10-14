#include <game/menuSubLayout.hpp>

struct OPDEMO_SE_SEQUENCE_dd_ {
    u16 frame;
    u16 reserved2;
    u16 reserved4;
};

struct LogoMatrixState {
    u32 flags;
    f32 matrix[3][4];
};

struct LogoMatrixSlot {
    u32 reserved;
    LogoMatrixState* state;
};

struct LogoLayer {
    u8 reserved0[0xD54];
    s32 fieldD54;
    f32 fieldD58;
    f32 fieldD5C;
    f32 fieldD60;
    f32 fieldD64;
    f32 fieldD68;
    f32 fieldD6C;
    u8 reservedD70[0x1684 - 0xD70];
    f32 field1684;
    f32 field1688;
    u8 reserved168C[0x16A6 - 0x168C];
    u8 field16A6;
    u8 field16A7;
    s32 field16A8;
    s32 field16AC;
    u8 reserved16B0[0x170C - 0x16B0];
    s32 field170C;
    u8 reserved1710[0x1760 - 0x1710];
    s32 field1760;
    s32 field1764;
    u8 reserved1768[0x17C4 - 0x1768];
    s32 field17C4;
    u8 reserved17C8[0x19A0 - 0x17C8];
    LogoMatrixSlot* field19A0;
};

struct GSvec2 {
    f32 x;
    f32 y;
};

struct GSgfxColAu8 {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

struct GStexture;

struct LogoDemoKeyInfo {
    u8 reserved0[4];
    u16 trigger;
};

extern "C" {
u8 GSflagTest(s32);
void GSfloorChange(s32);
s32 GSfsysGetDriveStatus(void);
u8 GSmoviePlayCheck(s32);
void GSmoviePlay(s32, s32, s32, s32);
void GSmovieStop(s32);
void GSthreadSwitch(void);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
void* memset(void*, int, u32);
void fadeCheck(s32);
void fadeSet(s32, f32);
void floorLink(s32, s32);
void floorSetFadeScript(s32, s32);
u32 floorGetPrevFloorID(void);
void menuTitleSetStartStatus(s32);
void soundInitBGM(void);
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayFadeOutIn(s32, s32, s32, s32);
LogoDemoKeyInfo* windowGetKeyInfo(void);
s32 GSfsysGetStatus(s32);
void GSfsysFree(s32);
void GSfsysInit(s32, s32, s32, s32);
void GSfsysReadWait(s32);
LogoLayer* GSgfxLayerFindByID(s32);
void GSmtx44Ortho(f32*, f32, f32, f32, f32, f32, f32);
void GSprimSetBlendMode(s32);
void GSprimSetQuadVertexOrder(s32);
u32 GSresGetResourceAllGroup(u32);
double sin(double);
void* memcpy(void*, const void*, u32);
extern f32 mtxIdent[3][4];
u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
void GSgfxVideoSetFilter(void*);
void GSgfxVideoSetMode(s32, s32, s32, s32, s32);
void GSinputReadEnd(void);
void GSinputReadStart(void);
s32 GSinputRead(s32);
void GSlogWrite(const char*, ...);
void GSprimSetup2DRender__FP10GSgfxLayer(void*);
void soundOpenWave(u32);
void GSsndInit(s32, s32, s32, s32, s32);
u32 OSGetProgressiveMode(void);
s32 OSGetResetCode(void);
void OSSetProgressiveMode(s32);
u32 VIGetDTVStatus(void);
void VIWaitForRetrace(void);
void floorLayerConfig(s32, s32);
void fn_8005C8CC(void);
void menuClose(s32);
void menuCloseSync(s32, s32);
s32 menuOpen(s32, s32);
s32 pokecoloGetRomVersion(void);
void soundInit(void);
void OSCreateThread(void*, int (*)(void*), void*, void*, u32, s32, u16);
void OSResumeThread(void*);
void menuNintendoWarning(void);
void fn_80087254(void);

void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
void winSeqSetMenu(s32, s32);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
u8 winSeqCheckMove(s32);
f32 timeGetLastFrameSec(void);
s32 menuOpenCustom(s32, s32, ...);
void menuSetPosition(s32, s16, s16);
void menuCloseCustom(s32, s32, s32);
u8 windowCheckCursor(s32, s32);
s32 windowGetActiveID(void);
s32 windowGetValue(s32);
tagWINDOW_WORK* windowSearchID(s32);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
void GSprimDraw2DTexQuad4V(GSvec2*, GSvec2*, GStexture*, GSgfxColAu8*);
void menuGSfsysInit__Fv(void);
void menuGSfsysInitWait__Fv(void);
}

static unsigned long _PlaySE(OPDEMO_SE_SEQUENCE_dd_* seq, unsigned long count, unsigned long index);
static unsigned long _menuOpeningDemo_SE(unsigned long index);
static unsigned long _menuAutoDemo_SE(unsigned long index);
static void _menuSetScreenFilter(bool on);
static void _menuSoundReadWave(unsigned long, unsigned long, unsigned long, unsigned long);
static void _menuSoundReadWaveWait(void);
static void _NintendoInit(void);
static void _NintendoMain(void);
static void _NintendoExit(void);
static void _setTexture(GStexture*, GSvec2*, GSvec2*, GSgfxColAu8);
static void _setTextureWindow(tagWINDOW_WORK*, tagSPRITE_WORK*, GStexture*);
static void _menuNintendoWarningButtonNormal(tagWINDOW_WORK*);
static void _NintendoWarningInit(void);
static void _NintendoWarningMain(void);
static void _NintendoWarningExit(void);
static void _ProgressiveModeMain(void);
static void _ProgressiveModeChange(void);
static void _ProgressiveModeSeq(void);
static s8 _ProgressiveModeYesNo(short, short, long);
static void _NormalModeSeq(void);
static void _menuWait(float);
static void _menuGSfsysInit(void);
static void _menuGSfsysInitWait(void);
static int _menuGSfsysInitThread(void*);
static int _menuSoundReadWaveThread(void*);


static OPDEMO_SE_SEQUENCE_dd_ _se_sequence[0x21] = {
    {0x03DF, 0x0424, 0x03B9},
    {0x0412, 0x0428, 0x0000},
    {0x0433, 0x0429, 0x0000},
    {0x043B, 0x03A3, 0x0000},
    {0x046C, 0x03A1, 0x0000},
    {0x049D, 0x0424, 0x03B9},
    {0x04D0, 0x03AD, 0x0000},
    {0x057C, 0x013F, 0x0000},
    {0x05BE, 0x0155, 0x0000},
    {0x05C8, 0x0156, 0x0000},
    {0x05E8, 0x0170, 0x0000},
    {0x0605, 0x00CE, 0x0000},
    {0x0667, 0x03C3, 0x0000},
    {0x0669, 0x03B9, 0x0000},
    {0x06CF, 0x0193, 0x0000},
    {0x070B, 0x0180, 0x0000},
    {0x0764, 0x01C3, 0x03B9},
    {0x078D, 0x01BF, 0x0000},
    {0x07DB, 0x03FA, 0x0000},
    {0x080D, 0x03FB, 0x0000},
    {0x0823, 0x03FC, 0x0000},
    {0x0842, 0x03A3, 0x0000},
    {0x086B, 0x0371, 0x0000},
    {0x0883, 0x0373, 0x0000},
    {0x08FB, 0x01D2, 0x0000},
    {0x0918, 0x03B9, 0x0000},
    {0x098F, 0x01D9, 0x0000},
    {0x09B6, 0x041B, 0x0000},
    {0x09C2, 0x03EB, 0x0000},
    {0x09D0, 0x01DA, 0x0000},
    {0x0A08, 0x03B1, 0x0000},
    {0x0A3B, 0x03B8, 0x0000},
    {0x0BB8, 0x0000, 0x0000},
};
static OPDEMO_SE_SEQUENCE_dd_ _opening_se_sequence[3] = {
    {0x013D, 0x016A, 0x0000},
    {0x05C3, 0x016A, 0x0000},
    {0x0BB8, 0x0000, 0x0000},
};
static u8 _rw_stack[0x1000];
static u8 _rw_thread[0x318];
static u32 _rw_arg[4];
static u8 _fs_stack[0x1000];
static u8 _fs_thread[0x318];
static u8 _menuMainExec;
static s32 _sound_wave_complete;
static s32 _gsfsysinit_complete;
static s32 _warningSeq;
static f32 _warningSeqTimer;
static f32 _warningTimer;
static s32 _progressive_mode_change = -1;

extern "C" {

void fn_80085E3C(tagWINDOW_WORK* win) {
    if (win != 0 && (windowGetKeyInfo()->trigger & 0x10)) {
        win->finished = 1;
    }
}

void menuOpeningDemoExit(void) {
    fadeSet(3, 0.0f);
    fadeCheck(1);
}

void menuOpeningDemoMain(void) {
    unsigned long index = 0;
    while (GSmoviePlayCheck(0x7DB) == 1) {
        index = _menuOpeningDemo_SE(index);
        GSthreadSwitch();
    }
    soundOpenPlay(8, 0, 0x7F);
    floorLink(0x8D, 0);
    floorSetFadeScript(0, 0x05960008);
}

void menuOpeningDemoInit(void) {
    fadeSet(2, 0.0f);
    fadeCheck(1);
    GSmoviePlay(0x7DB, 0, 0, 0);
    soundOpenPlay(8, 0, 0x7F);
}

}

static unsigned long _menuOpeningDemo_SE(unsigned long index) {
    return _PlaySE(_opening_se_sequence, 3, index);
}

extern "C" {

void fn_8008617C(void) {
}

void menuStaffRollExit(void) {
    fadeSet(3, 0.0f);
    fadeCheck(1);
}

void menuStaffRollInit(void) {
    fadeSet(2, 0.0f);
    fadeCheck(1);
}

void menuEndingDemoExit(void) {
    fadeSet(3, 0.0f);
    fadeCheck(1);
    _menuSetScreenFilter(true);
}

void menuEndingDemoMain(void) {
    u32 prev = floorGetPrevFloorID();
    while (GSmoviePlayCheck(0x8EB) == 1) {
        GSfsysGetDriveStatus();
        GSthreadSwitch();
    }
    soundOpenPlayFadeOutIn(8, 0x3E8, 0, 0x7F);
    if (prev == 0x4A) {
        if (GSflagTest(0x8EA) != 0) {
            floorLink(0x8C, 0);
            floorSetFadeScript(0, 0);
            return;
        }
        GSfloorChange(0x39F);
        floorSetFadeScript(0, 0x05960008);
        return;
    }
    GSfloorChange(0x384);
    floorSetFadeScript(0, 0x05960008);
}

void menuEndingDemoInit(void) {
    fadeSet(2, 0.0f);
    fadeCheck(1);
    _menuSetScreenFilter(false);
    GSmoviePlay(0x8EB, 0, 0, 0);
    soundOpenPlay(8, 0, 0x7F);
}

void menuAutoDemoExit(void) {
    fadeSet(3, 0.0f);
    fadeCheck(1);
    _menuSetScreenFilter(true);
}

void menuAutoDemoMain(void) {
    u32 index = 0;
    s32 status;
    while (GSmoviePlayCheck(0x7DC) == 1) {
        status = GSfsysGetDriveStatus();
        if (status == 0xB || status == 5) {
            GSthreadSwitch();
            continue;
        }
        if ((GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x1300) != 0) {
            GSmovieStop(0x7DC);
            menuTitleSetStartStatus(1);
            break;
        }
        index = _menuAutoDemo_SE(index);
        GSthreadSwitch();
    }
    soundOpenPlayFadeOutIn(8, 0x3E8, 0, 0x7F);
    GSfloorChange(0x384);
    floorSetFadeScript(0, 0x05960008);
}

void menuAutoDemoInit(void) {
    fadeSet(2, 0.0f);
    fadeCheck(1);
    _menuSetScreenFilter(false);
    GSmoviePlay(0x7DC, 0, 0, 0);
    soundOpenPlay(8, 0, 0x7F);
}

}

static unsigned long _menuAutoDemo_SE(unsigned long index) {
    return _PlaySE(_se_sequence, 0x21, index);
}

static unsigned long _PlaySE(OPDEMO_SE_SEQUENCE_dd_* seq, unsigned long count, unsigned long index) {
    if (index >= count) {
        return index;
    }
    if ((s32)seq[index].frame <= 0) {
        index++;
    }
    return index;
}

extern "C" {

void menuBattleDemoExit(void) {
}

void menuBattleDemoMain(void) {
}

void menuBattleDemoInit(void) {
}

void menuGeniusExit(void) {
    fadeSet(3, 0.0f);
    fadeCheck(1);
}

void menuGeniusMain(void) {
    if (_menuMainExec != 1) {
        while (GSmoviePlayCheck(0x7DA) == 1) {
            GSthreadSwitch();
        }
    }
    GSfloorChange(0x384);
    floorSetFadeScript(0, 0x05960008);
    _menuMainExec = 1;
}

void menuGeniusInit(void) {
    _menuMainExec = 0;
    _menuSoundReadWave(2, 0, 0, 0);
    _menuSoundReadWaveWait();
    fadeSet(2, 0.0f);
    fadeCheck(1);
    GSmoviePlay(0x7DA, 1, 0, 0);
    soundOpenPlay(8, 0, 0x7F);
    memset((void*)0x80001805, 0, 0x17FB);
}

void menuTpcExit(void) {
    fadeSet(3, 0.0f);
    fadeCheck(1);
}

void menuTpcMain(void) {
    if (_menuMainExec != 1) {
        while (GSmoviePlayCheck(0x7D9) == 1) {
            GSthreadSwitch();
        }
    }
    GSfloorChange(0x39A);
    floorSetFadeScript(0, 0);
    _menuMainExec = 1;
}

void menuTpcInit(void) {
    _menuMainExec = 0;
    fadeSet(2, 0.0f);
    fadeCheck(1);
    soundInitBGM();
    GSmoviePlay(0x7D9, 1, 0, 0);
    soundOpenPlay(8, 0, 0x7F);
    memset((void*)0x80001803, 0, 0x17FD);
}

void menuNintendoExit(void) {
}

void menuNintendoMain(void) {
}

void menuNintendoInit(void) {
}

void menuNintendo(void) {
    _NintendoInit();
    _NintendoMain();
    _NintendoExit();
}

}

extern "C" {

void fn_80085E88(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s32 cursor;
    u32 msg;
    u32 color;
    msg = 0;
    color = *((u8*)win + 0x93) | ~0xFF;
    cursor = *(s32*)&win->pos;
    switch (sprite->id) {
    case 0xA2:
        msg = 0x4A43;
        break;
    case 0xA3:
        msg = 0x4A44;
        break;
    case 0x9E:
        if (((s16*)&cursor)[1] == 0) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x9F:
        if (((s16*)&cursor)[1] == 1) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0xA4:
        msg = 0x4A45;
        break;
    case 0xA5:
        msg = 0x4A46;
        break;
    default:
        msg = 0;
        break;
    }
    if (msg != 0) {
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, -2, sprite->width, sprite->height, color, msg);
    }
}

void menuNintendoWarningCtrl(tagWINDOW_WORK* win) {
    f32 seqTimer;
    f32 dt = timeGetLastFrameSec();
    switch (win->phase) {
    case 0:
        _warningSeq = 0;
        _warningSeqTimer = 0.0f;
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x1CC);
            win->step = 1;
            menuGSfsysInit__Fv();
        }
        break;
    case 2:
        switch (_warningSeq) {
        case 0:
            if (winSeqCheckMove(win->menu) == 0) {
                _warningSeq = 1;
                return;
            }
            break;
        case 1:
            _warningSeqTimer = _warningSeqTimer + dt;
            if (_warningSeqTimer >= 1.5f) {
                _warningSeq = 2;
                _warningTimer = 0.0f;
                return;
            }
            break;
        case 2: {
            seqTimer = _warningSeqTimer + dt;
            _warningSeqTimer = seqTimer;
            _warningTimer += dt;
            if (seqTimer >= 60.0f) {
                _warningSeq = 3;
                return;
            }
            break;
        }
        case 3:
            _warningTimer += dt;
            return;
        }
        break;
    case 3:
        _warningTimer += dt;
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x1D0);
            win->step = 1;
        }
        break;
    }
}

void menuNintendoWarningHook(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    f32 matrix[4][4];
    LogoMatrixSlot* slot;
    LogoLayer* layer = GSgfxLayerFindByID(7);
    GSmtx44Ortho(&matrix[0][0], -23.0f, 448.0f, 0.0f, 608.0f, 0.0f, -30000.0f);
    layer->fieldD54 = 1;
    layer->fieldD58 = matrix[0][0];
    layer->fieldD5C = matrix[0][3];
    layer->fieldD60 = matrix[1][1];
    layer->fieldD64 = matrix[1][3];
    layer->fieldD68 = matrix[2][2];
    layer->fieldD6C = matrix[2][3];
    slot = layer->field19A0;
    memcpy(slot->state->matrix, mtxIdent, 0x30);
    slot->state->flags |= 1;
    layer->field1684 = 0.0f;
    layer->field1688 = 30000.0f;
    if (layer->field16A7 != 0) {
        if (layer->field16A6 != 0) {
            layer->field170C = layer->field170C | 0x100;
            layer->field17C4 = layer->field17C4 | 0x100;
        }
        layer->field170C = layer->field170C | 0x40;
        layer->field16A8 = layer->field16A8 | 0x40;
        layer->field17C4 = layer->field17C4 | 0x40;
        layer->field1760 = layer->field1760 | 0x40;
    }
    layer->field16AC = layer->field16AC | 0x20;
    layer->field16A8 = layer->field16A8 | 1;
    layer->field1764 = layer->field1764 | 0x20;
    layer->field1760 = layer->field1760 | 1;
    GSprimSetup2DRender__FP10GSgfxLayer(layer);
    GSprimSetBlendMode(1);
    GSprimSetQuadVertexOrder(1);
    switch (sprite->id) {
    case 49:
        if (_warningSeq >= 2) {
            if (_warningTimer > 1.0f) {
                _warningTimer = 0.0f;
            }
            sprite->color.channels.alpha = (u8)(255.0f * (f32)sin(3.1415927f * _warningTimer));
            winSpriteSetDisp(sprite, 1);
            {
                GStexture* tex = (GStexture*)GSresGetResourceAllGroup(0x215A1200);
                _setTextureWindow(win, sprite, tex);
            }
            return;
        }
        winSpriteSetDisp(sprite, 0);
        return;
    case 48:
        _setTextureWindow(win, sprite, (GStexture*)GSresGetResourceAllGroup(0x21591200));
        return;
    }
}

void fn_800860E8(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x1D4);
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x1D8);
            win->step = 1;
        }
        break;
    }
}

void menuNintendoWarningButton(tagWINDOW_WORK* win) {
    if (_warningSeq == 2) {
        _menuNintendoWarningButtonNormal(win);
    } else if (_warningSeq == 3) {
        win->finished = 1;
    }
}

}

static void _menuNintendoWarningButtonNormal(tagWINDOW_WORK* win) {
    if (win != 0 && (windowGetKeyInfo()->trigger & 0xFF0) != 0) {
        win->finished = 1;
    }
}

static void _setTexture(GStexture* texture, GSvec2* pos, GSvec2* uv, GSgfxColAu8 color) {
    GSgfxColAu8 copy = color;
    GSprimDraw2DTexQuad4V(pos, uv, texture, &copy);
}

static void _setTextureWindow(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, GStexture* texture) {
    GSvec2 pos[4];
    GSvec2 uv[4];
    GSgfxColAu8 color;
    s16 x;
    s16 y;
    s32 x1;
    s32 y1;
    u16 alpha;

    x = sprite->x;
    pos[0].x = x;
    y = sprite->y;
    pos[0].y = y;
    x1 = x + sprite->width;
    pos[1].y = y;
    pos[1].x = x1;
    pos[2].x = x1;
    y1 = y + sprite->height;
    pos[3].x = x;
    uv[0].x = 0.0f;
    uv[0].y = 0.0f;
    pos[2].y = y1;
    pos[3].y = y1;
    uv[1].x = 1.0f;
    uv[1].y = 0.0f;
    uv[2].x = 1.0f;
    uv[2].y = 1.0f;
    uv[3].x = 0.0f;
    uv[3].y = 1.0f;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    alpha = (*((u8*)win + 0x93) * sprite->color.channels.alpha) / 255;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    color.a = alpha;
    _setTexture(texture, &pos[0], &uv[0], color);
}

extern "C" {

void menuNintendoWarning(void) {
    _NintendoWarningInit();
    _NintendoWarningMain();
    _NintendoWarningExit();
}

}

static void _NintendoExit(void) {
    _menuSoundReadWave(3, 0, 0, 0);
    fadeSet(3, 0.5f);
    fadeCheck(1);
    menuClose(0x17);
    _menuSoundReadWaveWait();
}

static void _ProgressiveModeChange(void) {
    if (_progressive_mode_change != -1) {
        GSgfxVideoGetVsyncRate();
        OSSetProgressiveMode(_progressive_mode_change);
        if ((u32)_progressive_mode_change == 1) {
            GSgfxVideoSetMode(0, 1, 0, 1, 1);
            return;
        }
        GSgfxVideoSetMode(0, 1, 0, 1, 0);
    }
}

static void _NintendoMain(void) {
    s32 status;
    for (;;) {
        status = GSfsysGetStatus(0xA);
        if (status < 0) {
            GSlogWrite("読み出しエラー\n");
        }
        if (status == 0) {
            break;
        }
        GSthreadSwitch();
    }
    GSsndInit(2, 1, 0x20, 1, 0x10);
    soundInit();
    _menuSoundReadWave(1, 0, 0, 0);
    _menuSoundReadWaveWait();
}

static void _NormalModeSeq(void) {
    GSthreadSwitch();
    fadeCheck(1);
    _menuWait(2.0f);
}

static void _NintendoInit(void) {
    floorLayerConfig(0, 5);
    if (pokecoloGetRomVersion() != 1) {
        _ProgressiveModeMain();
    } else {
        fn_80087254();
    }
    _ProgressiveModeChange();
    GSprimSetup2DRender__FP10GSgfxLayer(GSgfxLayerFindByID(7));
    if (pokecoloGetRomVersion() != 1) {
        menuNintendoWarning();
    } else {
        menuGSfsysInit__Fv();
    }
    menuGSfsysInitWait__Fv();
    GSfsysReadWait(0xD);
    menuOpen(0x17, 0);
    fadeSet(2, 0.5f);
    fn_8005C8CC();
    memset((void*)0x80001801, 0, 0x17FF);
    GSfsysFree(0xD);
}

static void _NintendoWarningExit(void) {
    GSgfxLayerFindByID(7);
    menuClose(0x112);
    menuCloseSync(0x112, 1);
}

static void _NintendoWarningMain(void) {
}

static void _NintendoWarningInit(void) {
    GSprimSetup2DRender__FP10GSgfxLayer(GSgfxLayerFindByID(7));
    _warningSeq = 0;
    _warningSeqTimer = 0.0f;
    menuOpen(0x112, 1);
}

void menuGSfsysInitWait(void) {
    _menuGSfsysInitWait();
}

void menuGSfsysInit(void) {
    _menuGSfsysInit();
}

static void _menuGSfsysInitWait(void) {
    while (_gsfsysinit_complete == 0) {
        GSthreadSwitch();
    }
}

static void _menuGSfsysInit(void) {
    if (_gsfsysinit_complete != 1) {
        OSCreateThread(_fs_thread, _menuGSfsysInitThread, 0, _fs_stack + 0xFFC, 0x1000, 0x10, 1);
        OSResumeThread(_fs_thread);
    }
}

static int _menuGSfsysInitThread(void*) {
    GSfsysInit(0x40, 0, 0, 0);
    _gsfsysinit_complete = 1;
    return 0;
}

static void _menuSetScreenFilter(bool on) {
    static u8 filt_off[7] = {0x00, 0x00, 0x15, 0x16, 0x15, 0x00, 0x00};
    static u8 filt_on[7] = {0x0C, 0x0A, 0x08, 0x08, 0x08, 0x0A, 0x0C};
    if (on) {
        GSgfxVideoSetFilter(filt_on);
        return;
    }
    GSgfxVideoSetFilter(filt_off);
}

static void _menuSoundReadWaveWait(void) {
    while (_sound_wave_complete != 0) {
        GSthreadSwitch();
    }
}

static void _menuSoundReadWave(unsigned long a, unsigned long b, unsigned long c, unsigned long d) {
    _sound_wave_complete++;
    _rw_arg[0] = a;
    _rw_arg[1] = b;
    _rw_arg[2] = c;
    _rw_arg[3] = d;
    OSCreateThread(_rw_thread, _menuSoundReadWaveThread, _rw_arg, _rw_stack + 0xFFC, 0x1000, 0x10, 1);
    OSResumeThread(_rw_thread);
}

static int _menuSoundReadWaveThread(void* arg) {
    u32* args = (u32*)arg;
    if (args[0] != 0) {
        soundOpenWave(args[0]);
    }
    if (args[1] != 0) {
        soundOpenWave(args[1]);
    }
    if (args[2] != 0) {
        soundOpenWave(args[2]);
    }
    if (args[3] != 0) {
        soundOpenWave(args[3]);
    }
    _sound_wave_complete--;
    return 0;
}

static void _menuWait(float seconds) {
    float elapsed = 0.0f;
    while (elapsed < seconds) {
        GSthreadSwitch();
        elapsed += GSgfxVideoGetLastRenderTime() / (float)GSgfxVideoGetVsyncRate();
    }
}

extern "C" {

void fn_80087314(u8 flag) {
    _progressive_mode_change = (flag == 1) ? 1 : 0;
    fadeCheck(1);
    _menuWait(2.0f);
}

void fn_80087254(void) {
    s32 input;
    _progressive_mode_change = -1;
    VIWaitForRetrace();
    VIWaitForRetrace();
    if (((OSGetResetCode() & 0x80000000) != 0 ? 1 : 0) == 0) {
        do {
            GSthreadSwitch();
            GSinputReadStart();
            input = GSinputRead(1);
            GSinputReadEnd();
        } while (input != 0);
        GSinputReadStart();
        if ((GSinputButtonsPressed(1) & 0x200) != 0) {
            fn_80087314(0);
        } else if (VIGetDTVStatus() == 1) {
            fn_80087314(1);
        } else {
            fn_80087314(0);
        }
        GSinputReadEnd();
    }
}

}

static void _ProgressiveModeMain(void) {
    _progressive_mode_change = -1;
    VIWaitForRetrace();
    VIWaitForRetrace();
    if (((OSGetResetCode() & 0x80000000) != 0 ? 1 : 0) == 0) {
        if (VIGetDTVStatus() == 1) {
            if (OSGetProgressiveMode() == 1) {
                _ProgressiveModeSeq();
                return;
            }
            GSthreadSwitch();
            GSinputReadStart();
            if ((GSinputButtonsPressed(1) & 0x200) != 0) {
                _ProgressiveModeSeq();
            } else {
                _NormalModeSeq();
            }
            GSinputReadEnd();
            return;
        }
        _NormalModeSeq();
        OSSetProgressiveMode(0);
        return;
    }
    _NormalModeSeq();
}

static void _ProgressiveModeSeq(void) {
    GSthreadSwitch();
    winMsgOpen(1, 0x4A39, 1, 1);
    if (_ProgressiveModeYesNo(0x2D, 0xBE, 0) == 0) {
        if (((OSGetResetCode() & 0x80000000) != 0 ? 1 : 0) == 1) {
            if (OSGetProgressiveMode() == 0) {
                _progressive_mode_change = 1;
            }
        } else {
            _progressive_mode_change = 1;
        }
        winMsgOpen(1, 0x4A3A, 1, 1);
        _menuWait(2.0f);
    } else {
        if (((OSGetResetCode() & 0x80000000) != 0 ? 1 : 0) == 1) {
            if (OSGetProgressiveMode() == 1) {
                _progressive_mode_change = 0;
            }
        } else {
            _progressive_mode_change = 0;
        }
        winMsgOpen(1, 0x4A3B, 1, 1);
        _menuWait(2.0f);
    }
    winMsgClose(1);
}

static s8 _ProgressiveModeYesNo(short x, short y, long initial) {
    f32 vsync;
    f32 timer;
    s8 prev;
    s8 result;
    s16 selected;
    if (initial != 0) {
        initial = 1;
    }
    menuOpenCustom(0x35, windowGetActiveID(), &initial, 8, 0, 0);
    if (x >= 0 && y >= 0) {
        menuSetPosition(0x35, x, y);
    }
    timer = 0.0f;
    prev = -1;
    while (timer < 10.0f) {
        if (windowCheckCursor(0x35, 0) == 0) {
            result = windowGetValue(0x35);
            break;
        }
        selected = windowSearchID(0x35)->pos.selected;
        if (prev != selected) {
            timer = 0.0f;
            prev = (s8)selected;
        }
        GSthreadSwitch();
        vsync = (f32)GSgfxVideoGetVsyncRate();
        timer += GSgfxVideoGetLastRenderTime() / vsync;
    }
    if (timer >= 10.0f) {
        result = (s8)windowSearchID(0x35)->pos.selected;
    }
    menuCloseCustom(0x35, 0, 1);
    return result;
}
