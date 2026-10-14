#include <game/menuSubLayout.hpp>

#define FLASH ((void*)0x1FE03000)

struct MenuTitleKeyInfo {
    u8 reserved0[4];
    u16 trigger;
};

struct MenuTitleWork {
    f32 pos[16];
    s16 select[6];
};

class WorldMapModel {
public:
    u32 offscreen;
    WorldMapModel() : offscreen(0) {}

    void SetModel(unsigned long, unsigned long, bool);
    void UnloadModel(unsigned long, unsigned long);
    void releaseOffscreenData();
};

void* operator new(unsigned long);
void operator delete(void*);

extern "C" {
u32 FlashSystemGetFrameFromLabel(void*, const char*);
u32 FlashSystemGetNowFrame(void*);
void FlashSystemPlayAndWait(void*, const char*, const char*);
void FlashSystemSetLoopFlag(void*, s32);
void FlashSystemSetNowFrameLabel(void*, const char*);
void FlashSystemSetPlayFrameLabel(void*, const char*, const char*);
s32 GSfloorGetCurrentFloorGroupID(void);
u8 GSfloorIsPop(void);
void GSfsysFree(s32);
void GSfsysPreReadWait(void);
void GSfsysReadWait(s32);
void GSfsysWait(s32);
void GSmodelGetAnimFrameCount(u32, s16);
void GSmodelSet60fpsAnimFlag(u32, s32);
void GSmodelSetAnimFrame(u32, f32);
void GSmodelSetAnimIndex(u32, s16);
void GSmodelSetAnimRate(u32, f32);
void GSmodelSetAnimType(u32, s32);
void GSmodelSetBoundCheck(u32, s32);
void GSmodelSetForceUseFractionalFramesFlag(u32, s32);
void GSmodelSetVisibility(u32, s32);
void GSmodelStartAnimation(u32);
void GSresFreeGroup(s32);
u32 GSresGetResourceAllGroup(u32);
u8 GSsndIsPlayingStream(s32);
void GSsndPlay(u32, s32, s32);
u32 GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
void GSthreadSwitch(void);
void GSthreadTerminate(u32);
void cameraPlayAnime(s32, u32, s32, f32);
void cameraSetType(s32);
void dbgMenuSetEnable(s32);
s8 fadeCheck(s32);
s32 fightEncountDataBiosGetPtr(s32);
void fightEncountDataBiosSetDiskId(s32, s32);
void fightEncountDataBiosSetFightTrainerDataId(s32, s32, s32);
void fightRegWzxLoadAll(s32);
void floorDataBiosGetFileGroupID(void*);
void* floorDataBiosGetPtr(s32);
s32 floorGetCurrentGroupID(void);
void floorLink(s32, s32);
u32 gamedatasaveGetStatus(s32, s32);
s32 memcardTaskCall(s32, s32, s32);
void menuCloseCustom(s32, s32, s32);
void* menuDataBiosGetPtr(s32);
u8 menuIsCheck(s32);
s32 menuOpenCustom(s32, s32, ...);
void menuToolInit(void*, f32, f32, f32, f32, f32, f32);
s32 menuTop(void);
u8 menuTopGetBattleMode(void);
void menuTopSetInitCursor(s32);
s32 pokecoloGetRomVersion(void);
void savedataCreate(s32, s32);
double sin(double);
u32 soundGetBGMID(void);
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayFadeOutIn(s32, s32, s32, s32);
f32 timeGetLastFrameSec(void);
void winMsgClose(s32);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
s32 windowGetActiveID(void);
MenuTitleKeyInfo* windowGetKeyInfo(void);
tagWINDOW_WORK* windowSearchID(s32);

void menuTitleCursorAnimeMain(void);
void menuTitlePlayBGM(void);
u8 menuTitlePlayBGMWait(u8);
void menuTitleReadWazaSelectMenu(void);
void menuTitleSetStartStatus(s32);
void menuTitleCloseSelectAnime(void);
void menuTitleBattlePreReadCheck(void);
void menuTitleCursorAnime(tagWINDOW_WORK*, tagSPRITE_WORK*);
void fn_800A39E4(void);
void fn_800A3BD4(u32, u32);
void fn_800A392C(void);
void fn_800A39A8(void);
void fn_800A3B34(u32, u32, bool);
void fn_800A3A48(u32, long, u8, f32);
}

MenuTitleWork _menuTitleWork;
static s32 _menuTitleWorkPat = 3;
static s32 _menuTitleStartStatus;
static s32 _menuTitleDiskCoverOpen;
static s32 _menuTitleStatus;
static f32 _menuTitleTimer;
static f32 _menuTitleFrameSec;
static f32 _menuTitleSeFrame;
static s32 _menuTitleSeCount;
static s32 _menuTitleType;
static f32 _menuTitleFrameCount;
static f32 _menuTitleAutoDemoCount;
extern "C" s32 _menuTitleSkipFlag;
s32 _menuTitleSkipFlag;
static u32 _gsthread_ptr_fight_reg_wzx;
static s16 _titleCursorTimer;

static s32 _selectMenu(void);
static void _menuTitleSetSE(unsigned long);
static void _menuTitleClose2(long, unsigned long);
static void _menuTitleNormalButton(tagWINDOW_WORK*);
static void _cursorSpriteOnOff(tagWINDOW_WORK*, tagSPRITE_WORK*);
static void _CreateThread(void);
static void _menuTitlePreReadFightRegWzxData(void);

extern "C" {

void menuTitleOpenMenu(void) {
    fn_800A39E4();
    menuOpenCustom(0x11, windowGetActiveID(), 0, 0, 0, 0);
}

s16 menuTitleGetSelect(s32 index) {
    return _menuTitleWork.select[index];
}

void menuTitleSetSelect(s32 index, s16 value) {
    _menuTitleWork.select[index] = value;
}

void menuTitleFunc(void) {
    menuTitleCursorAnimeMain();
    _menuTitleFrameSec = timeGetLastFrameSec();
    f32 c = 0.5f;
    _menuTitleFrameCount = (f32)_menuTitleFrameSec * c + _menuTitleFrameCount;
    if (_menuTitleFrameCount >= 1.0f) {
        _menuTitleFrameCount = 0.0f;
    }
    if (_menuTitleStatus >= 0x1E) {
        if (_menuTitleStatus == 0x29) {
            _menuTitleFrameCount = 0.0f;
        } else if (_menuTitleStatus != 0xC8) {
            if (pokecoloGetRomVersion() != 1) {
                _menuTitleAutoDemoCount = _menuTitleAutoDemoCount + _menuTitleFrameSec;
                if (_menuTitleAutoDemoCount >= 60.5f) {
                    _menuTitleAutoDemoCount = 0.0f;
                    if (_menuTitleStatus != 0x3E8 && (_menuTitleStatus >= 0x3E8 || _menuTitleStatus != 0x1F)) {
                        _menuTitleStatus = 0x28;
                        menuTitleSetStartStatus(0);
                    }
                }
            }
        }
    }
}

void menuTitleButton(tagWINDOW_WORK* win) {
    u32 end;
    if (fadeCheck(0) == 0) {
        dbgMenuSetEnable(1);
        end = FlashSystemGetFrameFromLabel(FLASH, "end");
        if (FlashSystemGetNowFrame(FLASH) >= end) {
            _menuTitleNormalButton(win);
        }
    }
}

}

static void _menuTitleNormalButton(tagWINDOW_WORK* win) {
    if (_menuTitleStatus < 0x29 && win != 0) {
        menuDataBiosGetPtr(win->menu);
        if ((windowGetKeyInfo()->trigger & 0x810) != 0) {
            if (win->finished == 0) {
                _menuTitleSetSE(0x11);
            }
            win->finished = 1;
        }
    }
}

extern "C" {

void menuTitleCursorAnime(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s32 t;
    if ((u32)win == (u32)windowSearchID(windowGetActiveID())) {
        t = _titleCursorTimer % 60;
        sprite->color.value = -1;
        if (t < 0x1E) {
            sprite->color.channels.alpha -= (u8)(128.0f * (f32)sin(3.14f * ((f32)t / 30.0f)));
        }
    } else {
        sprite->color.channels.alpha = 0xFF;
    }
}

void menuTitleCursorAnimeMain(void) {
    _titleCursorTimer = (s32)(60.0f * timeGetLastFrameSec() + (f32)_titleCursorTimer) % 1000;
}

void menuTitleHook(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s16 id = sprite->id;
    if (id < 0x42) {
        if (id < 0x40) {
            if (id < 0x3D) {
                return;
            }
            goto run;
        }
    } else if (id < 0x44) {
run:
        menuTitleCursorAnime(win, sprite);
        _cursorSpriteOnOff(win, sprite);
    }
}

}

static void _cursorSpriteOnOff(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    static const s32 ids[5] = {0x3D, 0x3E, 0x3F, 0x42, 0x43};
    s32 index = 0;
    s16 id = sprite->id;
    if (id != ids[0]) {
        index = 1;
        if (id != ids[1]) {
            index = 2;
            if (id != ids[2]) {
                index = 3;
                if (id != ids[3]) {
                    index = 4;
                    if (id != ids[4]) {
                        index = 5;
                    }
                }
            }
        }
    }
    if (index == win->pos.selected) {
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}

extern "C" {

void menuTitle(void) {
    s32 running;
    s32 result;
    running = 1;
    _menuTitleStatus = 0;
    _menuTitleTimer = 0.0f;
    _menuTitleSeFrame = 0.0f;
    _menuTitleSeCount = 0;
    _menuTitleSkipFlag = 0;
    menuTitlePlayBGM();
    menuTitlePlayBGMWait(1);
    if (_menuTitleStartStatus == 1) {
        _menuTitleStatus = 1;
        _menuTitleStartStatus = 0;
        _menuTitleType = 1;
    } else {
        _menuTitleType = 0;
    }
    fn_800A39E4();
    do {
        switch (_menuTitleStatus) {
        case 0:
            FlashSystemSetLoopFlag(FLASH, 0);
            FlashSystemSetPlayFrameLabel(FLASH, "start", "end");
            FlashSystemSetNowFrameLabel(FLASH, "start");
            _menuTitleStatus = 0x1E;
            break;
        case 1:
            FlashSystemSetLoopFlag(FLASH, 0);
            FlashSystemSetPlayFrameLabel(FLASH, "back", "end");
            FlashSystemSetNowFrameLabel(FLASH, "back");
            _menuTitleStatus = 0x1E;
            break;
        case 0x28:
            _menuTitleStatus = 0x3E8;
            break;
        case 0x1E:
            _menuTitleStatus = 0x20;
            break;
        case 0x20:
            if (menuOpenCustom(0x11, windowGetActiveID(), 0, 0, 1, 0) >= 0) {
                FlashSystemSetLoopFlag(FLASH, 0);
                FlashSystemSetPlayFrameLabel(FLASH, "end", "window");
                _menuTitleStatus = 0x1F;
                _menuTitleTimer = 0.0f;
            }
            break;
        case 0x1F:
            while (_menuTitleTimer < 1.0f) {
                _menuTitleTimer += timeGetLastFrameSec();
                GSthreadSwitch();
            }
            FlashSystemSetPlayFrameLabel(FLASH, "window", "window");
            FlashSystemSetNowFrameLabel(FLASH, "window");
            _menuTitleStatus = 0xC8;
            break;
        case 0xC8:
            if (pokecoloGetRomVersion() == 1) {
                result = 5;
            } else {
                result = memcardTaskCall(1, 2, 0);
            }
            if (result == -1) {
                _menuTitleStatus = 0x20;
                FlashSystemSetPlayFrameLabel(FLASH, "back", "end");
                FlashSystemSetNowFrameLabel(FLASH, "back");
            } else {
                if (result != 3) {
                    savedataCreate(0, 0);
                }
                if (gamedatasaveGetStatus(0, 4) != 0) {
                    menuTopSetInitCursor(1);
                } else {
                    menuTopSetInitCursor(0);
                }
                _menuTitleStatus = 0x29;
            }
            break;
        case 0x29:
            result = _selectMenu();
            if (result < 0 || result == 4) {
                menuTitleCloseSelectAnime();
                _menuTitleStatus = 1;
                _menuTitleAutoDemoCount = 0.0f;
            }
            break;
        case 0xC9:
            break;
        case 0x3E8:
            running = 0;
            break;
        }
    } while (running != 0);
}

void fn_800A392C(void) {
    fn_800A3A48(0x22141000, 0, 1, 0.0f);
    fn_800A3A48(0x22141001, 0, 1, 0.0f);
    fn_800A3A48(0x22141002, 0, 1, 0.0f);
    fn_800A3A48(0x22141003, 0, 1, 0.0f);
}

void fn_800A39A8(void) {
    cameraSetType(4);
    cameraPlayAnime(floorGetCurrentGroupID(), 0x22161800, 1, 0.0f);
}

void fn_800A39E4(void) {
    fn_800A3B34(floorGetCurrentGroupID(), 0x22140400, 1);
    fn_800A392C();
    fn_800A39A8();
}

void fn_800A3A1C(void) {
    fn_800A3BD4(floorGetCurrentGroupID(), 0x22140400);
}

void fn_800A3A48(u32 res, long anim, u8 loop, f32 frame) {
    u32 model = GSresGetResourceAllGroup(res);
    if (model != 0) {
        GSmodelSetAnimIndex(model, anim);
        GSmodelSetAnimFrame(model, frame);
        GSmodelSetAnimRate(model, 0.5f);
        GSmodelGetAnimFrameCount(model, anim);
        if (loop != 0) {
            GSmodelSetAnimType(model, 1);
        } else {
            GSmodelSetAnimType(model, 0);
        }
        GSmodelStartAnimation(model);
        GSmodelSetForceUseFractionalFramesFlag(model, 1);
        GSmodelSet60fpsAnimFlag(model, 1);
        GSmodelSetVisibility(model, 1);
        GSmodelSetBoundCheck(model, 0);
    }
}

void fn_800A3B34(u32 a, u32 b, bool c) {
    WorldMapModel* model = new WorldMapModel;
    model->SetModel(a, b, c);
    if (model != 0) {
        if (model != 0) {
            if (model->offscreen != 0) {
                model->releaseOffscreenData();
            }
            delete model;
        }
    }
}

void fn_800A3BD4(u32 a, u32 b) {
    WorldMapModel* model = new WorldMapModel;
    model->UnloadModel(a, b);
    if (model != 0) {
        if (model != 0) {
            if (model->offscreen != 0) {
                model->releaseOffscreenData();
            }
            delete model;
        }
    }
}

u8 menuTitlePlayBGMWait(u8 wait) {
    f32 elapsed;
    if (wait == 0) {
        return GSsndIsPlayingStream(0x5E2);
    }
    elapsed = 0.0f;
    for (;;) {
        if (GSsndIsPlayingStream(0x5E2) == 1) {
            break;
        }
        elapsed += timeGetLastFrameSec();
        if (elapsed >= 2.0f) {
            break;
        }
        GSthreadSwitch();
    }
    return 1;
}

void menuTitlePlayBGM(void) {
    if (soundGetBGMID() != 0x5E2) {
        soundOpenPlay(0x5E2, 0, 0xFF);
    }
    _menuTitleAutoDemoCount = 0.0f;
}

}

static s32 _selectMenu(void) {
    u32 end;
    u32 now;
    FlashSystemSetPlayFrameLabel(FLASH, "menu_play", "menu_end");
    FlashSystemSetLoopFlag(FLASH, 0);
    FlashSystemSetNowFrameLabel(FLASH, "menu_play");
    end = FlashSystemGetFrameFromLabel(FLASH, "menu_end");
    do {
        now = FlashSystemGetNowFrame(FLASH);
        GSthreadSwitch();
    } while (now < end);
    return menuTop();
}

extern "C" {

void menuTitleCloseSelectAnime(void) {
    FlashSystemPlayAndWait(FLASH, "back_play", "back_end");
}

void menuTitleOpenSelectAnime2(void) {
    FlashSystemPlayAndWait(FLASH, "menu_end", "menu_end");
}

void menuTitleOpenSelectAnime(void) {
    FlashSystemPlayAndWait(FLASH, "menu_play", "menu_end");
}

}

static void _menuTitleSetSE(unsigned long id) {
    GSsndPlay(id, 0, 0);
}

extern "C" {

void menuTitleExit(void) {
    GSfsysWait(0xA8C);
    if (menuTopGetBattleMode() == 0) {
        GSfsysFree(0xA8C);
        GSresFreeGroup(0xA8C);
    }
    _menuTitleClose2(0x11, 2);
    _menuTitleClose2(0x116, 2);
    _menuTitleClose2(0x118, 2);
    winMsgClose(1);
    menuTitleBattlePreReadCheck();
}

void menuTitleBattleSelectFree(void) {
    GSfsysWait(0xA8C);
    GSfsysFree(0xA8C);
    GSresFreeGroup(0xA8C);
}

void menuTitleBattlePreReadCheck(void) {
    if (_gsthread_ptr_fight_reg_wzx != 0) {
        GSthreadTerminate(_gsthread_ptr_fight_reg_wzx);
        _gsthread_ptr_fight_reg_wzx = 0;
    }
}

void menuTitlePreReadWait(void) {
    while (_gsthread_ptr_fight_reg_wzx != 0) {
        GSthreadSwitch();
    }
}

void menuTitleMain(void) {
    s32 done = 0x3E8;
    for (;;) {
        if (_menuTitleStatus == 0x28) {
            soundOpenPlayFadeOutIn(0x5E2, 0x3E8, 0, 0x7F);
            floorLink(0x39C, 0);
            _menuTitleStatus = done;
            continue;
        }
        GSthreadSwitch();
    }
}

void menuTitleInit(void) {
    s32 encount;
    _menuTitleDiskCoverOpen = 0;
    _menuTitleAutoDemoCount = 0.0f;
    _menuTitleFrameSec = 0.0f;
    menuTitleReadWazaSelectMenu();
    encount = fightEncountDataBiosGetPtr(0xE);
    fightEncountDataBiosSetDiskId(encount, 0);
    fightEncountDataBiosSetFightTrainerDataId(encount, 1, 2);
    _CreateThread();
    if (GSfloorIsPop() == 0) {
        _menuTitleStatus = 0;
        _menuTitleWorkPat++;
        if (_menuTitleWorkPat >= 4) {
            _menuTitleWorkPat = 0;
        }
        _menuTitleWork.pos[4] = 300.0f;
        _menuTitleWork.pos[7] = -300.0f;
        _menuTitleWork.pos[10] = 0.0f;
        _menuTitleWork.pos[13] = 0.0f;
        _menuTitleWork.pos[5] = 400.0f;
        _menuTitleWork.pos[8] = -400.0f;
        _menuTitleWork.pos[11] = 0.0f;
        _menuTitleWork.pos[14] = 0.0f;
        _menuTitleWork.pos[6] = 500.0f;
        _menuTitleWork.pos[9] = -500.0f;
        _menuTitleWork.pos[12] = 0.0f;
        _menuTitleWork.pos[15] = 0.0f;
        _menuTitleWork.select[0] = -1;
        _menuTitleWork.select[1] = -1;
        _menuTitleWork.select[2] = -1;
        _menuTitleWork.select[3] = -1;
        _menuTitleWork.select[4] = -1;
        menuToolInit(&_menuTitleWork, 500.0f, -400.0f, 400.0f, 0.0f, -300.0f, 300.0f);
    }
}

}

static void _CreateThread(void) {
    _gsthread_ptr_fight_reg_wzx = GSthreadCreate(0x14, GSfloorGetCurrentFloorGroupID(), 0x2000, 1, 1, (void (*)(void))_menuTitlePreReadFightRegWzxData);
}

static void _menuTitlePreReadFightRegWzxData(void) {
    for (;;) {
        if (soundGetBGMID() == 0x5E2) {
            break;
        }
        GSthreadSwitch();
    }
    menuTitlePlayBGMWait(1);
    floorDataBiosGetFileGroupID(floorDataBiosGetPtr(0x397));
    GSfsysPreReadWait();
    fightRegWzxLoadAll(-1);
    _gsthread_ptr_fight_reg_wzx = 0;
}

extern "C" {

void menuTitleReadWazaSelectMenu(void) {
    if (GSresGetResourceAllGroup(0x200A3000) == 0) {
        GSfsysReadWait(0xA8C);
    }
}

void menuTitleSetStartStatus(s32 status) {
    _menuTitleStartStatus = status;
}

}

static void _menuTitleClose2(long menu, unsigned long mode) {
    if (menuIsCheck(menu) == 1) {
        menuCloseCustom(menu, mode, 1);
    }
}
