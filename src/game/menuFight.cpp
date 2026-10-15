#include <game/menuFightLayout.hpp>

extern "C" {
void *memcpy(void *, const void *, u32);
u8 fightKind_CheckFightKind(s32);
u8 fightFloorIsNowEncountTuusinTaisen(s32);
u8 fightFloorIsUseFightTimerCommand(s32);
u8 fightTimerCommandIsOver(void);
u16 fightGetFightResultId(void);
s32 fightMenuGetFightTrainerPtrToStatusMenuId(void);
void gbaCommandRequestAction(s32, s32, s32, s32);
u8 menuIsCheck(s32);
s32 menuOpen(s32, s32);
s32 menuOpenCustom(s32, s32, s32 *, s32, bool, s32, ...);
void menuCloseCustom(s32, s32, s32);
void menuButtonNormal(tagWINDOW_WORK *);
void winSeqSetMenu(s32, s32);
u8 winSeqCheckMove(s32);
s32 windowGetParam(tagWINDOW_WORK *, s32);
void *windowGetAllocPtr(tagWINDOW_WORK *);
struct FightWazaWork {
    u8 mode;
    u8 reserved1;
    s8 saved;
};
FightWazaWork *windowGetFreeWork(tagWINDOW_WORK *);
void *windowAllocMemory(tagWINDOW_WORK *, s32);
MenuFightKey *windowGetKeyInfo(void);
u8 menuItemBiosGetSelectFlag(s32, s16);
s32 menuGetCursorItemID(s32);
FIGHT_TRAINER *fightFloorGetGcHeroFightTrainerPtr(s32);
void *fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER *, u16);
s32 pokemonGetStatus(void *, s32, s32, u16);
u8 pokemonCheckValid(Pokemon *);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
void GSthreadSwitch(void);
f32 timeGetLastFrameSec(void);
MenuCursor windowGetCursor(s32);
Pokemon *fightOutPokemonGetPokemonPtr(s32);
u8 fightOutPokemonCheckCanOutOkWazaBanme(s32, u16, s32, u16 *);
void *wazaGetStatus(s32, u16, s32, s32);
u32 GSmsgGetGSchar(void *);
void fightFloorSetStatus(s32, s32, s32, s32, s32);
s32 fightOutPokemonGetSoubiItemDataId(s32);
u8 pokemonWazaCheckValid(void *, u8);
void windowDrawSprite(s32, s32, tagWINDOW_WORK *, s32, s32, s32);
s32 zokuseiBiosGetSpriteID(u16);
void winMsgOpen(s32, u32, s32, s32);
void winMsgClose(s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
f64 atan2(f64, f64);
s32 menuSetDisp(s32, s32);
void menuClose(s32);
void GSsndPlayNow(s32);
void windowCreateCursorSprite(tagWINDOW_WORK *);
s32 menuGetSelectItemNum(s32);
void pokemonWazaReplace(void *, s32, s32);
void pokemonToMenuWazaStatus(void *, MENU_WAZA_STATUS *);
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(s32, s32 *, s32 **);
s32 fightOutPokemonGetNicknamePtr(s32 *);
u16 fightOutPokemonGetTokuseiDataId(s32 *);
u32 fightPokemonGetNicknamePtr(u32);
u8 fightTrainerCheckCanIrekaeFightPokemon(FIGHT_TRAINER *, u32);
void GSlogWrite(const char *, ...);
s32 fightFloorGetStatus(s32, s32, s32, s32);
void msgctrlSetValue(s32, u32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
void GSmsgPrintRight(s32, s32, s32, s32, s32, u32, u32);
u32 GSmsgGetRect(u32);
void menuSubDrawCursorBack(s32, s32, s32, s32, s32, s32, s32);
s32 menuSubCalcColor(tagWINDOW_WORK *, tagSPRITE_WORK *);
void windowSetParam(tagWINDOW_WORK *, s32, s32);
tagWINDOW_WORK *windowSearchID(s32);
void GSsndPlayNow(s32);
s32 heroGetStatus(s32, s32, s32);
u16 fightFloor_GetTurnCount(s32);
u32 fightFloor_GetFightTypeFightoutPokemonNum(s32);
u8 fightFloor_GetFightKindGetOkaneFlag(s32);
u8 fightFloor_GetFightKindOkanePoolFlag(s32);
u32 fightTrainer_GetHeroPtr(void);
u8 fightTrainer_GetOkaneBai(FIGHT_TRAINER *);
FIGHT_TRAINER *fightTargetGetPtrAsNowFightType(s32, FIGHT_TRAINER *);
void fightTrainer_GetFightTrainerDataId(void);
u32 fightTrainerDB_GetKindDataId(void);
void fightTrainerKindDataBiosGetPtr(u8);
u16 fightTrainerKindDataBiosGetSyoukinBairitu(void);
void *fightTrainer_GetFightPokemonPtr(FIGHT_TRAINER *, u16);
u8 fightPokemonCheckValid(void);
u8 figthPokemonGetLevel(void *);
u8 fightPokemon_GetCatchEntryFlag(void *);
f32 menuGetTotalTime(void);
f32 fightTimerAllGetNokoriTime(void);
f32 fightTimerCommandGetNokoriTime(void);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
}

static s32 menuFightStatus;
static u16 oldKeyInfo[2] = { 0, 0 };
static u8 _menuFightCheckTimeOut(void);
static u8 isImasugu(void);
static Pokemon *_menuFightGetPokemonPtr(FIGHT_TRAINER *, u32);
static void _menuFightKeyWait(GSinputDevice);
static u16 _menuFightGetLeftKeyInfo(long);
static u16 _menuFightGetRightStickInfo(long, bool);


static s32 getKane(void) {
    u16 bairitu;
    u8 okaneBai;
    FIGHT_TRAINER *hero;
    u8 maxLevel;
    u8 fightOutNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    void *p;
    FIGHT_TRAINER *target;
    int i;
    int j;
    void *p2;
    s32 mult;
    if (fightFloor_GetFightKindGetOkaneFlag(0) == 0) {
        return -1;
    }
    hero = fightFloorGetGcHeroFightTrainerPtr(0);
    if (hero == 0) {
        return -1;
    }
    if (fightTrainer_GetHeroPtr() == 0) {
        return -1;
    }
    okaneBai = fightTrainer_GetOkaneBai(hero);
    target = fightTargetGetPtrAsNowFightType(9, hero);
    fightTrainer_GetFightTrainerDataId();
    fightTrainerKindDataBiosGetPtr(fightTrainerDB_GetKindDataId());
    bairitu = fightTrainerKindDataBiosGetSyoukinBairitu();
    maxLevel = 0;
    {
        for (i = 0; i < 6; i++) {
            p = fightTrainer_GetFightPokemonPtr(target, i);
            if (fightPokemonCheckValid()) {
                u8 level = figthPokemonGetLevel(p);
                if (maxLevel < level) {
                    maxLevel = level;
                }
            }
        }
    }
    {
        for (j = 0; j < 6; j++) {
            p2 = fightTrainer_GetFightPokemonPtr(hero, j);
            if (fightPokemonCheckValid() && fightPokemon_GetCatchEntryFlag(p2) == 1) {
                u8 level = figthPokemonGetLevel(p2);
                if (maxLevel < level) {
                    maxLevel = level;
                }
            }
        }
    }
    if (fightFloor_GetFightKindOkanePoolFlag(0) == 0) {
        if (fightOutNum <= 1) {
            mult = 1;
        } else {
            mult = 2;
        }
    } else {
        mult = 4;
    }
    return (u16)mult * (bairitu * (maxLevel * okaneBai));
}


#define WZ(T, w, i, off) (*(T *)((u8 *)(w) + (i) + (off)))
#define WZ_SLOT(w) (*(s32 *)((u8 *)(w) + 0x40))

static void menuFightDrawIwaitStatusWaza(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, Pokemon *pokemon, u8 index, u32 color) {
    if (pokemon != 0 && pokemonWazaCheckValid(pokemon, index)) {
        void *waza = wazaGetStatus(0, pokemonGetStatus(pokemon, 0, 0x7F, index), 1, 0);
        if (waza != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(waza));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4279);
        }
    }
}

static s32 chkWazaNew(MENU_WAZA_STATUS *status, u8 index) {
    Pokemon *pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
    if (index == 0) {
        return -1;
    }
    if (pokemon != 0 && pokemon->isDarkPokemon()) {
        DarkPokemon *dark = pokemon->getDarkPokemon();
        if (dark != 0) {
            s32 waza = (u16)pokemonGetStatus(pokemon, 0, 0x7F, index);
            if (waza < 0x164) {
                if (waza == 0) {
                    goto fail;
                }
            } else if (waza < 0x177) {
                goto fail;
            }
            return dark->isWazaNew(index - 1);
        }
    }
fail:
    return -1;
}

static u16 _menuFightIsUse(MENU_WAZA_STATUS *status, u16 index) {
    u16 sp8;
    s32 slot = WZ_SLOT(status);
    Pokemon *pokemon = fightOutPokemonGetPokemonPtr(slot);
    u8 result = fightOutPokemonCheckCanOutOkWazaBanme(slot, index, 1, &sp8);
    u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, index);
    u16 msg;
    if (result != 0) {
        msgctrlSetValue(0x11, slot);
        msgctrlSetValue(0x28, GSmsgGetGSchar(wazaGetStatus(0, waza, 1, 0)));
        fightFloorSetStatus(0, 0, 0x56, 0, fightOutPokemonGetSoubiItemDataId(slot));
    }
    switch (result) {
    case 6:
        msg = 0x4F42;
        break;
    case 5:
        msgctrlSetValue(0x28, GSmsgGetGSchar(wazaGetStatus(0, sp8, 1, 0)));
        msg = 0x4F9A;
        break;
    case 4:
        msg = 0x4EE9;
        break;
    case 3:
        msg = 0x4EE8;
        break;
    case 2:
        msg = 0x4EE7;
        break;
    case 1:
        msg = 0x4EE6;
        break;
    }
    if (result != 0) {
        return msg;
    }
    return 0;
}

static u16 _menuFightGetLeftKeyInfo(long player) {
    u16 key = 0;
    int idx;
    u32 pressed;
    if (player != 0) {
        idx = 1;
    } else {
        idx = 0;
    }
    if (idx != 0) {
        pressed = GSinputButtonsPressed(2);
    } else {
        pressed = GSinputButtonsPressed(1);
    }
    if (pressed & 8) {
        key |= 1;
    }
    if (pressed & 4) {
        key |= 2;
    }
    if (pressed & 1) {
        key |= 4;
    }
    if (pressed & 2) {
        key |= 8;
    }
    if (key == oldKeyInfo[idx]) {
        key = 0;
    } else {
        oldKeyInfo[idx] = key;
    }
    return key;
}

#define ABSI(v) ((v) < 0 ? -(v) : (v))
#define FABSF(v) ((v) > 0.0f ? (v) : -(v))

static u16 _menuFightGetRightStickInfo(long player, bool edge) {
    u16 key = 0;
    s8 y;
    s8 x;
    f32 ang;
    int idx;
    if (player != 0) {
        idx = 1;
    } else {
        idx = 0;
    }
    if (idx == 0) {
        y = GSinputGetRightStickYData(1, 0);
        x = GSinputGetRightStickXData(1, 0);
    } else {
        y = GSinputGetRightStickYData(2, 0);
        x = GSinputGetRightStickXData(2, 0);
    }
    if (ABSI(x) > 0x20 || ABSI(y) > 0x20) {
        ang = (f32)atan2((f64)x, (f64)y);
        if (FABSF(ang) < 0.7853982f) {
            key |= 2;
        } else if (FABSF(ang) > 2.3561945f) {
            key |= 1;
        }
        if (FABSF(ang) > 0.7853982f && FABSF(ang) < 2.3561945f) {
            if (ang < 0.0f) {
                key |= 4;
            } else {
                key |= 8;
            }
        }
        if (edge) {
            if (key == oldKeyInfo[idx]) {
                key = 0;
            } else {
                oldKeyInfo[idx] = key;
            }
        }
    } else {
        oldKeyInfo[idx] = 0;
    }
    return key;
}

extern "C" {
void menuFightDrawTurn(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    switch (sprite->id) {
    case 2:
        msgctrlSetValue(0x5F, fightFloor_GetTurnCount(0));
        if (fightFloor_GetTurnCount(0) > 9) {
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, -1, 0x4351);
        } else {
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 8, 0, -1, 0x4351);
        }
        break;
    case 0x27C:
    case 0x295:
    case 0x2D3:
        if (window->selected == 0) {
            menuSubDrawCursorBack(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, 0xFF, 1);
        }
        break;
    case 0x27D:
    case 0x296:
    case 0x2D4:
        if (window->selected == 1) {
            menuSubDrawCursorBack(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, 0xFF, 1);
        }
        break;
    }
}

void menuFightDrawKane(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    s32 kane = getKane();
    winSpriteSetDisp(sprite, 0);
    if (kane != -1) {
        if (sprite->id == 6) {
            s16 w;
            msgctrlSetValue(0x50, kane + heroGetStatus(0, 0xC, 0));
            w = GSmsgGetRect(0x434E) >> 16;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), sprite->width - w, 0, -1, 0x434E);
        }
        winSpriteSetDisp(sprite, 1);
    }
}

void menuFightDrawTimer(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    static u16 buff[8];
    static u16 half_digit_code[16] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                                       0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46 };
    s32 color;
    switch (sprite->id) {
    case 0xA7:
    case 0xA8:
    case 0xA9:
    case 0xAA:
        winSpriteSetDisp(sprite, 0);
        if (0.5f <= menuGetTotalTime()) {
            winSpriteSetDisp(sprite, 1);
        }
        break;
    case 0xAB:
        break;
    case 0xAC: {
        s32 t = windowGetParam(window, 0);
        s32 v = t / 60;
        buff[0] = half_digit_code[v / 10];
        buff[1] = half_digit_code[v % 10];
        buff[2] = 0;
        msgctrlSetValue(0x37, (u32)buff);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, menuSubCalcColor(window, sprite), 0x4276);
        break;
    }
    case 0xAD: {
        s32 t = windowGetParam(window, 0);
        s32 v = t - t / 60 * 60;
        buff[0] = half_digit_code[v / 10];
        buff[1] = half_digit_code[v % 10];
        buff[2] = 0;
        msgctrlSetValue(0x37, (u32)buff);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, menuSubCalcColor(window, sprite), 0x4276);
        break;
    }
    case 0xAF: {
        msgctrlSetValue(0x5F, windowGetParam(window, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, menuSubCalcColor(window, sprite), 0x4357);
        break;
    }
    }
}

s32 menuFightCtrlTimer(tagWINDOW_WORK *window) {
    static s32 oldTime = 0;
    if (window->phase == 0) {
        oldTime = 0;
        if (window->menu == 0x9C) {
            windowSetParam(window, 0, (s32)fightTimerAllGetNokoriTime());
        }
    }
    switch (window->menu) {
    case 0x9C:
        if (menuIsCheck(0x9D) == 0) {
            windowSetParam(window, 0, (s32)fightTimerAllGetNokoriTime());
        }
        break;
    case 0x9D: {
        s32 t = (s32)fightTimerCommandGetNokoriTime();
        windowSetParam(window, 0, t);
        if (oldTime != t) {
            if (t <= 5) {
                if (t != 0) {
                    GSsndPlayNow(0x441);
                } else if (oldTime == 1) {
                    GSsndPlayNow(0x13);
                }
            }
            oldTime = t;
            if (menuIsCheck(0x9C)) {
                s32 total = (s32)fightTimerAllGetNokoriTime();
                windowSetParam(windowSearchID(0x9C), 0, total);
            }
        }
        break;
    }
    }
    return 0;
}
}

extern "C" {
void menuFightButtonTimeOutCheck(tagWINDOW_WORK *);
void menuFightButtonSecretKousan(tagWINDOW_WORK *window) {
    menuButtonNormal(window);
    menuFightButtonTimeOutCheck(window);
}

void menuFightDrawPP(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    s32 color = menuSubCalcColor(window, sprite);
    s16 cursorIndex = windowGetCursor(window->menu).y;
    s16 x = sprite->width - (s16)(GSmsgGetRect(0x42C4) >> 16) * 5;
    GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x42C4);
    if (cursorIndex >= 0 && cursorIndex < 4) {
        s32 off = cursorIndex * 0xC;
        if (WZ(u32, status, off, 4) != 0) {
            s32 waza;
            Pokemon *pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
            if (pokemon != 0) {
                waza = (u16)pokemonGetStatus(pokemon, 0, 0x7F, window->selected);
            } else {
                waza = 0;
            }
            if (waza == 0 || (waza >= 0x164 && waza < 0x176)) {
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->height, color, 0x3AF5);
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x3AF5);
            } else if (waza != 0x176) {
                msgctrlSetValue(0x5F, WZ(u8, status, off, 0xF));
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->height, color, 0x4351);
                msgctrlSetValue(0x5F, WZ(u8, status, off, 0xE));
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4351);
            } else {
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->height, color, 0x3AD1);
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x3AD1);
            }
        }
    }
}

void menuFightDrawType(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    s16 cursorIndex = windowGetCursor(window->menu).y;
    if (cursorIndex >= 0 && cursorIndex < 4) {
        s32 off = cursorIndex * 0xC;
        if (WZ(u32, status, off, 4) != 0) {
            s32 waza;
            Pokemon *pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
            if (pokemon != 0) {
                waza = (u16)pokemonGetStatus(pokemon, 0, 0x7F, window->selected);
            } else {
                waza = 0;
            }
            if (waza < 0x164) {
                if (waza == 0) {
                    return;
                }
            } else if (waza < 0x177) {
                return;
            }
            {
                u16 type = WZ(u16, status, off, 0xC);
                windowDrawSprite(0, 2, window, zokuseiBiosGetSpriteID(type), 0, winSpriteGetLayerID(window, sprite));
            }
        }
    }
}

void menuFightDrawNew(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    u8 index;
    s32 r;
    winSpriteSetDisp(sprite, 0);
    index = 0;
    switch (sprite->id) {
    case 0x10B:
        break;
    case 0x10E:
        index = 1;
    case 0x10C:
        index += 1;
    case 0x10D:
        index += 1;
        break;
    }
    r = chkWazaNew(status, index);
    if (r != -1 && r == 0) {
        winSpriteSetDisp(sprite, 1);
    }
}

u8 menuPokemonCheckPokemonChange(s32 *outInfo, FIGHT_TRAINER *trainer, u32 index) {
    s32 *other;
    u8 result;
    u32 target;
    u8 check;
    result = fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, outInfo, &other);
    if (result == 1) {
        msgctrlSetValue(0xD, fightOutPokemonGetNicknamePtr(outInfo));
        winMsgOpen(1, 0x4FC8, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    }
    if (result == 2) {
        fightFloorSetStatus(0, 0, 0x57, 0, fightOutPokemonGetTokuseiDataId(other));
        msgctrlSetValue(0xD, fightOutPokemonGetNicknamePtr(other));
        msgctrlSetValue(0xE, fightOutPokemonGetNicknamePtr(outInfo));
        winMsgOpen(1, 0x4F08, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    }
    if (trainer == 0) {
        trainer = fightFloorGetGcHeroFightTrainerPtr(0);
    }
    if (trainer == 0) {
        return 0;
    }
    target = (u32)fightTrainerGetValidFightPokemonPtr(trainer, index);
    if (target == 0) {
        return 0;
    }
    check = fightTrainerCheckCanIrekaeFightPokemon(trainer, target);
    if (check == 1) {
        msgctrlSetValue(0xD, fightPokemonGetNicknamePtr(target));
        winMsgOpen(1, 0x4FCB, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    } else if (check == 2) {
        msgctrlSetValue(0xD, fightPokemonGetNicknamePtr(target));
        winMsgOpen(1, 0x4FC9, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    } else if (check == 3) {
        msgctrlSetValue(0xD, fightPokemonGetNicknamePtr(target));
        winMsgOpen(1, 0x4FCA, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    } else if (check == 0) {
        return 1;
    } else {
        GSlogWrite("%s: \x97\x5c\x92\xe8\x8a\x4f\x82\xcc\x8f\xf0\x8c\x8f\x82\xaa\x8b\x41\x82\xc1\x82\xc4\x82\xab\x82\xc4\x82\xa2\x82\xdc\x82\xb7\n", __FUNCTION__);
        return 0;
    }
}

s32 menuFightWazaButton(tagWINDOW_WORK *window) {
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    FightWazaWork *work = windowGetFreeWork(window);
    Pokemon *pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
    u16 key = windowGetKeyInfo()->unk4;
    switch ((s32)work->mode) {
    case 0:
        if (key & 0xC0) {
            if (pokemonGetStatus(pokemon, 0, 0xC2, 0) != 0 || fightKind_CheckFightKind(0xD) != 0) {
                GSsndPlayNow(0x13);
            } else if (fightFloorGetStatus(0, 0, 0x32, 0) != 0 || fightKind_CheckFightKind(0xF) != 0) {
                work->saved = window->selected;
                if (work->saved == 0) {
                    window->selected = 1;
                } else {
                    window->selected = 0;
                }
                if (menuGetSelectItemNum(window->menu) <= 1) {
                    window->selected = 0;
                }
                windowCreateCursorSprite(window);
                work->mode = 1;
            }
        } else if (pokemon != 0 && (u16)pokemonGetStatus(pokemon, 0, 0x7F, (u16)window->selected) == 0x176) {
            if (windowGetKeyInfo()->unk4 & 0x20) {
                window->finished = 1;
                window->cancelled = 1;
            }
        } else {
            menuButtonNormal(window);
        }
        break;
    case 1:
        if (key & 0xD0) {
            if (pokemon != 0) {
                s32 saved;
                s8 from = work->saved;
                pokemonWazaReplace(pokemon, from, (u16)window->selected);
                saved = WZ_SLOT(status);
                pokemonToMenuWazaStatus(pokemon, status);
                WZ_SLOT(status) = saved;
            }
            work->saved = -1;
            work->mode = 0;
        } else if (key & 0x20) {
            work->saved = -1;
            work->mode = 0;
        }
        break;
    }
    return 0;
}

void menuFightCtrlTarget(void) {
}

s32 menuFightGetStatus(void) {
    return menuFightStatus;
}

void menuFightSetStatus(s32 status) {
    menuFightStatus = status;
}

void menuFightCloseCheckCountDown(void) {
    menuIsCheck(0x9D);
}

void menuFightCloseCheckTotalTimer(void) {
    menuIsCheck(0x9C);
}

void menuFightOpenGBAIrekae(s32 a, s32 b, s32 c) {
    gbaCommandRequestAction(a, b, c, 1);
}

void menuFightOpenGBAMain(s32 a, s32 b, s32 c) {
    gbaCommandRequestAction(a, b, c, 0);
}

void menuFightOpenTimeup(void) {
    menuOpen(0x10B, 0);
}

void menuFightCloseCountDown(void) {
    menuCloseCustom(0x9D, 0, 0);
}

void menuFightCloseTotalTimer(void) {
    menuCloseCustom(0x9C, 0, 0);
}

void menuFightOpenCountDown(void) {
    menuOpenCustom(0x9D, -1, 0, 0, 0, 0);
}

void menuFightOpenTotalTimer(void) {
    menuOpenCustom(0x9C, -1, 0, 0, 0, 0);
}

s32 menuFightChkOpenBall(s32 id) {
    if ((id == 0x44 || id == 0x45) && fightKind_CheckFightKind(0xC)) {
        return 0;
    }
    return 1;
}

s32 menuFightCtrlSecretPokemonTop(tagWINDOW_WORK *window) {
    windowGetParam(window, 0);
    windowGetParam(window, 1);
    windowGetParam(window, 2);
    return 0;
}

void menuFightSetSeq(void) {
    winSeqSetMenu(0x37, 0x1A5);
    winSeqSetMenu(0x40, 0x1A5);
    winSeqSetMenu(0x38, 0x1A9);
    winSeqSetMenu(0x41, 0x1A9);
}

s32 menuFightCtrlSecretMain(tagWINDOW_WORK *window) {
    void *dst;
    if (window->phase == 0 && (dst = windowAllocMemory(window, 0x18)) != 0) {
        memcpy(dst, (void *)window->parameters[0], 0x18);
    }
    return 0;
}

s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK *window) {
    void *dst;
    if (window->phase == 0 && (dst = windowAllocMemory(window, 0x48)) != 0) {
        memcpy(dst, (void *)window->parameters[0], 0x48);
    }
    windowGetAllocPtr(window);
    return 0;
}

s32 menuFightCtrlBall(tagWINDOW_WORK *window) {
    FightWazaWork *work = windowGetFreeWork(window);
    if (window->phase == 0) {
        memcpy(work, (void *)windowGetParam(window, 0), 6);
    }
    return 0;
}

s32 menuFightChkSeq(void) {
    if (winSeqCheckMove(0x37)) {
        return 1;
    }
    if (winSeqCheckMove(0x40)) {
        return 1;
    }
    if (winSeqCheckMove(0x38)) {
        return 1;
    }
    return winSeqCheckMove(0x41) != 0;
}

s32 menuFightCloseTarget(s32 arg) {
    if (menuIsCheck(0x5C)) {
        menuCloseCustom(0x5C, 0, arg);
    }
    if (menuIsCheck(0x91)) {
        menuCloseCustom(0x91, 0, arg);
    }
    return 0;
}

s32 menuFightGetKeyWaitMenuId(void) {
    s32 id = 0x98;
    switch (fightMenuGetFightTrainerPtrToStatusMenuId()) {
    case 0x42:
        id = 0x98;
        break;
    case 0x43:
        id = 0x99;
        break;
    case 0x44:
        id = 0x9A;
        break;
    case 0x45:
        id = 0x9B;
        break;
    }
    return id;
}

s32 menuFightCloseTop(s32 arg) {
    if (menuIsCheck(0x3A)) {
        menuCloseCustom(0x3A, 0, arg);
    }
    if (menuIsCheck(0x8E)) {
        menuCloseCustom(0x8E, 0, arg);
    }
    return 0;
}

s32 menuFightCloseWaza(s32 arg) {
    if (menuIsCheck(0x39)) {
        menuCloseCustom(0x39, 0, arg);
    }
    if (menuIsCheck(0x94)) {
        menuCloseCustom(0x94, 0, arg);
    }
    if (menuIsCheck(0x93)) {
        menuCloseCustom(0x93, 0, arg);
    }
    if (menuIsCheck(0x90)) {
        menuCloseCustom(0x90, 0, arg);
    }
    return 0;
}

void menuFightCloseAll(void) {
    s32 ids[28] = { 0x37, 0x40, 0x38, 0x41, 0x69, 0x6A, 0x39, 0x3A, 0x42, 0x43, 0x44, 0x45, 0x98, 0x99,
                    0x9A, 0x9B, 0x9D, 0xB5, 0x9C, 0x10B, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0x11C, 0x11D };
    s32 id;
    u8 i;
    for (i = 0; i < 0x1C; i++) {
        id = ids[i];
        if (menuIsCheck(id) == 1) {
            menuCloseCustom(id, 0, 0);
        }
    }
}

void menuFightButtonSecretMain(tagWINDOW_WORK *window) {
    s32 sel;
    u16 key = windowGetKeyInfo()->unk4;
    sel = -1;
    if (key & 0x10) {
        sel = 0;
    } else if (key & 0x20) {
        sel = 2;
    } else if (key & 0x800) {
        sel = 3;
    } else if (key & 0x200) {
        window->finished = 1;
        window->cancelled = 1;
        window->value = -1;
    }
    if (sel >= 0) {
        window->finished = 1;
        window->value = sel;
    }
    menuFightButtonTimeOutCheck(window);
}

void menuFightDrawSecretSelect(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    s32 show = 1;
    if (window->menu == 0x92) {
        u8 has = windowGetParam(window, 2) != 0;
        if (has == 0) {
            show = 0;
        }
    }
    switch (sprite->id) {
    case 33:
    case 35:
        winSpriteSetDisp(sprite, show);
    case 34:
        return;
    }
}

void menuFightDrawTargetCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    if (menuItemBiosGetSelectFlag(window->menu, sprite->id)) {
        if (sprite->id == menuGetCursorItemID(window->menu)) {
            winSpriteSetDisp(sprite, 1);
            return;
        }
        winSpriteSetDisp(sprite, 0);
        return;
    }
    winSpriteSetDisp(sprite, 0);
}
}

static Pokemon *_menuFightGetPokemonPtr(FIGHT_TRAINER *trainer, u32 index) {
    Pokemon *pokemon;
    void *valid;
    if (index >= 6) {
        return 0;
    }
    if (trainer == 0) {
        trainer = fightFloorGetGcHeroFightTrainerPtr(0);
    }
    if (trainer == 0) {
        return 0;
    }
    valid = fightTrainerGetValidFightPokemonPtr(trainer, index);
    if (valid == 0) {
        return 0;
    }
    pokemon = (Pokemon *)pokemonGetStatus(valid, 0, 0xCC, 0);
    if (pokemonCheckValid(pokemon) == 0) {
        return 0;
    }
    return pokemon;
}

static void _menuFightKeyWait(GSinputDevice device) {
    f32 timer = 0.0f;
    u32 changed;
    if (isImasugu()) {
        while (timer < 2.5f) {
            timer += timeGetLastFrameSec();
            GSthreadSwitch();
        }
        return;
    }
    while (changed = GSinputButtonsChanged(device), (GSinputButtonsPressed(device) & changed & 0x300) == 0) {
        if (_menuFightCheckTimeOut()) {
            break;
        }
        GSthreadSwitch();
    }
}

extern "C" void menuFightButtonTimeOutCheck(tagWINDOW_WORK *window) {
    if (_menuFightCheckTimeOut()) {
        window->finished = 1;
        window->cancelled = 1;
    }
}

static u8 isImasugu(void) {
    if (fightKind_CheckFightKind(0xA)) {
        return 1;
    }
    return fightKind_CheckFightKind(0x11) != 0;
}

static u8 _menuFightCheckTimeOut(void) {
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
            return 1;
        }
        if (fightGetFightResultId() == 1) {
            return 1;
        }
    }
    return 0;
}

static void menuFightSetSeqOut(void) {
    winSeqSetMenu(0x37, 0x19D);
    winSeqSetMenu(0x40, 0x19D);
    winSeqSetMenu(0x38, 0x1A1);
    winSeqSetMenu(0x41, 0x1A1);
    menuFightSetStatus(1);
}
