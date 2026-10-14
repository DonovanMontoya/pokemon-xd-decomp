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
void *windowGetParam(tagWINDOW_WORK *, s32);
void *windowGetAllocPtr(tagWINDOW_WORK *);
void *windowGetFreeWork(void);
void *windowAllocMemory(tagWINDOW_WORK *, s32);
MenuFightKey *windowGetKeyInfo(void);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
u8 menuItemBiosGetSelectFlag(s32, s16);
s32 menuGetCursorItemID(s32);
FIGHT_TRAINER *fightFloorGetGcHeroFightTrainerPtr(s32);
void *fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER *, u16);
Pokemon *pokemonGetStatus(void *, s32, s32, s32);
u8 pokemonCheckValid(Pokemon *);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
void GSthreadSwitch(void);
f32 timeGetLastFrameSec(void);
}

static s32 menuFightStatus;
static u8 _menuFightCheckTimeOut(void);
static u8 isImasugu(void);
static Pokemon *_menuFightGetPokemonPtr(FIGHT_TRAINER *, u32);
static void _menuFightKeyWait(GSinputDevice);

extern "C" {
void menuFightButtonTimeOutCheck(tagWINDOW_WORK *);
void menuFightButtonSecretKousan(tagWINDOW_WORK *window) {
    menuButtonNormal(window);
    menuFightButtonTimeOutCheck(window);
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
    if (window->unk1 == 0 && (dst = windowAllocMemory(window, 0x18)) != 0) {
        memcpy(dst, window->unk68, 0x18);
    }
    return 0;
}

s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK *window) {
    void *dst;
    if (window->unk1 == 0 && (dst = windowAllocMemory(window, 0x48)) != 0) {
        memcpy(dst, window->unk68, 0x48);
    }
    windowGetAllocPtr(window);
    return 0;
}

s32 menuFightCtrlBall(tagWINDOW_WORK *window) {
    void *work = windowGetFreeWork();
    if (window->unk1 == 0) {
        memcpy(work, windowGetParam(window, 0), 6);
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
        window->unkA4 = 1;
        window->unkA5 = 1;
        window->unk88 = -1;
    }
    if (sel >= 0) {
        window->unkA4 = 1;
        window->unk88 = sel;
    }
    menuFightButtonTimeOutCheck(window);
}

void menuFightDrawSecretSelect(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    s32 show = 1;
    if (window->unk4 == 0x92) {
        u8 has = windowGetParam(window, 2) != 0;
        if (has == 0) {
            show = 0;
        }
    }
    switch (sprite->unk6) {
    case 33:
    case 35:
        winSpriteSetDisp(sprite, show);
    case 34:
        return;
    }
}

void menuFightDrawTargetCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    if (menuItemBiosGetSelectFlag(window->unk4, sprite->unk6)) {
        if (sprite->unk6 == menuGetCursorItemID(window->unk4)) {
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
    pokemon = pokemonGetStatus(valid, 0, 0xCC, 0);
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
        window->unkA4 = 1;
        window->unkA5 = 1;
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
