#include <game/menuColosseumBattleLayout.hpp>

class CReliveStage {
public:
    Pokemon* getDancerPointer(long);
};

class CReliveHall {
public:
    static CReliveHall* getPointer();
    CReliveStage* getStage(long);
};

extern "C" {
u8 FlashSystemIsLastFrame(u32);
void FlashSystemSetNowFrameLabel(u32, const char*);
void FlashSystemSetPlayFrameLabel(u32, const char*, const char*);
void GSthreadSwitch(void);
void heroInit(Hero*);
u8 memcardIsMemCardValid(void);
s32 memcardTaskCall(s32, s32, s32);
void menuCBBios_CurrentlyWorkingToolBattleSet(s32);
void menuCBBios_RuleEditSaveON(s32);
void menuCloseCustom(s32, s32, s32);
u8 menuIsCheck(s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
s32 pokecoloGetCountryCode(void);
void winMsgClose(s32);
void winMsgOpen(s32, s32, s32, s32);
void* windowSearchID(s32);
void* memset(void*, int, u32);
void fadeCheck(s32);
u8 menuCBBios_ContextIsLocked(void);
void GSflagSet(u32, u32);
u32 GSflagGet(u32);
void toolentryDebugPokemonDelete(void);
void toolentryDebugPokemonCreate(void);
u8 fightReadResourceID(s32, s32);
void fightFreeResourceID(s32, s32);
void* GSfloorGetCurrent(void);
void* memcardMemFreeForSavedata(void*);
void* memcardMemAllocForSavedata(void);
void GSfsysFree(s32);
void GSresFreeGroup(s32);
void GSfsysReadWait(s32);
void menuCBBios_RuleConstRuleSet(void);
void menuCBBios_InitContext(_MENUCBWORK*);
void menuCBBios_UnlockContext(void);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void GSfloorPush(s32);
void menuCB_FlashEnd(u8);
void menuCB_SE_Play(s32);
void menuOpen(s32, s32);
void menuCB_GBADisconnectedErrorJob(void);
s32 menuCB_MenuRollback(s32);
void menuCB_InitBattle(_MENUCBWORK*);
void menuCBTrainerBios_SetControlerID(_MENUCBTRAINER*, s32);
void menuCBBios_InitVersusTrainer(_MENUCBTRAINER*, Hero*);
s32 openMenuGBA(s32, s32, Hero**);
void heroBiosSetHomePlace(Hero*, s32);
void menuCBRule_Copy(CBRule*, CBRule*);
CBRule* menuCBRule_ConstantRule2(s32);
u8 menuCBRule_IsEquals(CBRule*, CBRule*);
s32 menuCB_GCEntry_SubWindow_Disp(void);
void menuCBGCEntryPokemon(void);
void menuCBReliveHallCursolInit(void);
void menuCB_GCEntry_PokemonStatusDisp(void);
void menuCB_GCEntry_ItemGiveJob(void);
void menuCB_GCEntry_ItemKeepJob(void);
void heroBiosCopy(Hero*, Hero*);
Pokemon* heroBiosGetPokemonPtr(Hero*, u16);
void menuCB_GCPokemonHPandWAZA_MAX(void);
void systemFree__4CAntFv(void);
void fn_80044314(void);
void fn_8004429C(void);
u16 HSD_Rand(void);
s32 menuOpenCustom(s32, s32, ...);
s32 windowGetActiveID(void);
void menuCBPokemonEntryLoadTex(void);
void menuCBpokemonFaceReadWait(void);
void toolentryTaisenSetEtnryPokemonOrder(s32, s32);
void toolentryTaisenEntryPokemon(s32);
void* menuCBBios_GetTrainerImmediately(s32);
void soundStop(s32, s32);
void menuCBBios_LockContext(void);
void menuTopOpenFlashBack(void);
void menuCB_FlashStart(u8);
void soundOpenPlay(s32, s32, s32);
void fn_80151F6C(void);
void GSfloorPop(void);
void menuTopSetBattleSelectMode(s32);
void menuColosseumBattleExit(void);
s32 menuCB_CurrentMenuID(void);
void menuGBACSetRomVer(s32, s32);
u8 GSinputIsConnected(s32);
u8 gbaCommandIsConnected(s32);
s32 menuCB_MenuPop(void);
void menuCB_MenuPush(s32);
void menuCB_WaitGCControler1(void);
void fadeSet(s32, f32);
void systemInit__4CAntFv(void);
void menuCB2DPokemonALLClear(void);
void cursorBiosInit(void);
void menuCB_TUNAIDE01_Rule_SELECT(void);
void menuCB_RuleNameChengeBeforeJob(s32);
void menuCB_RuleNameChengeAfterJob(s32);
u16* menuCB_RuleTitleNameGet(s32);
s32 menuNameEntryOpen(s32, u16*);
void menuCBTrainerBios_SetHomePlace(_MENUCBTRAINER*, s32);
void* gamedatasaveGetStatus(s32, s32);
void GSmemFree(void*);
void* GSmemAllocAlign(u32, u32);
void pokemonInit(Pokemon*);
void pokemonBiosCopy(Pokemon*, Pokemon*);
void* savedataGetStatus(void*, s32);
void* memcpy(void*, const void*, u32);
}

struct TunaideSelect {
    s32 mode;
    s32 field;
    s32 home;
    s8 ids[4];
};

static const TunaideSelect tunaide_select[4] = {
    {0, 0, 0, {1, 2, 0, 0}},
    {0, 0, 1, {2, 3, 0, 0}},
    {2, 2, 0, {1, 2, 3, 4}},
    {2, 2, 1, {1, 2, 3, 4}},
};
static const s32 tunaide_select_field[6] = {0, 1, 2, 3, 4, 5};

_MENUCBWORK _CB;
static u8 _flashBackFlag = 1;
struct CBTemp {
    u8 reserved0[0x1320];
    Hero heroes[4];
    u8 reserved3900[0x90];
    CBRule ruleOrg;             // 0x3990
    CBRule ruleEdit;            // 0x3A20
};
static CBTemp* _menuCB_Temp;
extern struct FlagEtc { u8 reserved0[0x428]; u32 unk428; }* flag_etc;
static s32 _menuCB_RuleData_SaveJob_flag;
void* pGCB;
void* toolBattleTempSaveData;

static s32 _YesNo(long);
static void _menuCB_RuleData_SaveJob(long);
static u8 menuCB_SubWinDisp_GCENTRY(void);
static void _imasuguBattleMenuMain(void);
static void menuCB_RuleCustomJobDisp(long);
static s32 _gbac_connect_job(long);
static s32 _colosseumbattlemenu_duel(long);
static s32 _colosseumbattlemenu_teamselect(long);
static s32 _colosseumbattlemenu_playerdecide(long);
static s32 _menuCB_SaveRule(void);

_MENUCBTRAINER::_MENUCBTRAINER() {}

extern "C" {

void fn_8004429C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 4; j++) {
            if (_CB.dancers[i][j] != 0) {
                GSmemFree(_CB.dancers[i][j]);
                _CB.dancers[i][j] = 0;
            }
        }
    }
}

void fn_80044314(void) {
    s32 i;
    s32 j;
    CReliveStage* stage;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 4; j++) {
            _CB.dancers[i][j] = (Pokemon*)GSmemAllocAlign(0xC4, 0x20);
            pokemonInit(_CB.dancers[i][j]);
        }
    }
    for (i = 0; i < 9; i++) {
        stage = CReliveHall::getPointer()->getStage(i);
        for (j = 0; j < 4; j++) {
            pokemonBiosCopy(_CB.dancers[i][j], stage->getDancerPointer(j));
        }
    }
}

}

static void _menuCB_RuleData_CBtoSAVEDATA(void) {
    memcpy(savedataGetStatus(0, 0xE), _CB.rules, 0x360);
}

static void _menuCB_Rule_Page_Chenge_Init2(void) {
    CBW(0xB124) = CBW(0xB118);
    CBW(0xB128) = 0xFF;
    CBW(0xB12C) = 0xF;
}

static void _menuCB_RuleEdit_Cursol_Init(long v) {
    CBW(0xB0AC) = v;
    CBW(0xB0A8) = v;
    CBW(0xB0A4) = v;
    CBW(0xB0A0) = v;
    CBW(0xB09C) = v;
    CBW(0xB098) = v;
    CBW(0xB094) = v;
    CBW(0xB02C) = v;
    CBW(0xB028) = v;
    CBW(0xB024) = v;
    CBW(0xB020) = v;
    CBW(0xB01C) = v;
    CBW(0xB018) = v;
    CBW(0xB014) = v;
}

static void menuCB_RuleCustomJobDisp(long mode) {
    long cursor;
    if (mode == 0) {
        cursor = 0;
    }
    if (mode == 1) {
        cursor = -1;
    }
    _CB.unk9C78 = &_CB.rules[CBW(0xB004)];
    menuCBRule_Copy(&_menuCB_Temp->ruleOrg, menuCBRule_ConstantRule2(CBW(0xB004)));
    menuCBRule_Copy(&_menuCB_Temp->ruleEdit, _CB.unk9C78);
    _menuCB_RuleEdit_Cursol_Init(cursor);
    CBW(0xB118) = 0;
    CBW(0xB11C) = 0;
    CBW(0xB090) = 0;
    CBW(0xB010) = 0;
    CBW(0xB0B4) = 1;
    CBW(0xB0B0) = 1;
    CBW(0xB034) = 1;
    CBW(0xB030) = 1;
    CBW(0xB124) = -1;
    CBW(0xB130) = 0;
    CBW(0xB134) = 0x1F4;
    menuCB_SE_Play(0x14);
    menuOpen(0xF5, 0);
    menuOpen(0xEF, 0);
    menuOpen(0xF0, 0);
    menuOpen(0xF1, 0);
    menuOpen(0xF2, 0);
    menuOpen(0xF3, 0);
    menuOpen(0xF4, 0);
    do {
        if (CBW(0xB0B0) == 0) {
            winMsgOpen(2, 0x4411, 1, 1);
            if (_YesNo(0) == 0) {
                menuCBRule_Copy(_CB.unk9C78, &_menuCB_Temp->ruleOrg);
                _menuCB_RuleEdit_Cursol_Init(0);
                winMsgClose(0);
                _menuCB_Rule_Page_Chenge_Init2();
                CBW(0xB118) = 0;
            } else {
                winMsgClose(0);
            }
            CBW(0xB0B0) = 1;
            CBW(0xB030) = 1;
        }
        if (CBW(0xB0B4) == 0) {
            winMsgOpen(2, 0x4412, 1, 1);
            if (_YesNo(0) == 0) {
                menuCBRule_Copy(_CB.unk9C78, &_menuCB_Temp->ruleEdit);
                _menuCB_RuleEdit_Cursol_Init(0);
                winMsgClose(0);
                _menuCB_Rule_Page_Chenge_Init2();
                CBW(0xB118) = 0;
            } else {
                winMsgClose(0);
            }
            CBW(0xB0B4) = 1;
            CBW(0xB034) = 1;
        }
        if (CBW(0xB010) == 2) {
            if (CBW(0xB014) == -1) {
                CBW(0xB010) = 0;
            }
            CBW(0xB090) = 2;
        }
        if (CBW(0xB010) == 1) {
            if (menuCBRule_IsEquals(&_menuCB_Temp->ruleEdit, _CB.unk9C78) == 0) {
                _menuCB_RuleData_SaveJob(0);
                if (_menuCB_RuleData_SaveJob_flag == 0) {
                    CBW(0xB090) = 1;
                } else {
                    CBW(0xB11C) = 0;
                }
            } else {
                CBW(0xB090) = 1;
            }
            CBW(0xB010) = 0;
        }
        GSthreadSwitch();
    } while (CBW(0xB090) == 0);
    if (CBW(0xB010) == 2 && menuCBRule_IsEquals(&_menuCB_Temp->ruleEdit, _CB.unk9C78) == 0) {
        _menuCB_RuleData_SaveJob(0);
        if (_menuCB_RuleData_SaveJob_flag == 0 && memcardIsMemCardValid() != 0) {
            CBW(0xB090) = 1;
        } else {
            CBW(0xB090) = 2;
        }
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xF4, 0, 0);
    menuCloseCustom(0xF3, 0, 0);
    menuCloseCustom(0xF2, 0, 0);
    menuCloseCustom(0xF1, 0, 0);
    menuCloseCustom(0xF0, 0, 0);
    menuCloseCustom(0xEF, 0, 0);
    menuCloseCustom(0xF5, 0, 1);
    if (CBW(0xB090) == 2) {
        menuCBRule_Copy(_CB.unk9C78, &_menuCB_Temp->ruleEdit);
        _menuCB_RuleData_CBtoSAVEDATA();
    }
    if (memcardIsMemCardValid() == 0) {
        _menuCB_RuleData_CBtoSAVEDATA();
        menuCBBios_RuleEditSaveON(1);
    }
}

static void _menuCB_RuleData_SaveJob(long flag) {
    _menuCB_RuleData_SaveJob_flag = flag;
    for (;;) {
        if (memcardIsMemCardValid() == 0) break;
        winMsgOpen(2, 0xCB, 1, 1);
        _menuCB_RuleData_SaveJob_flag = _YesNo(0);
        if (_menuCB_RuleData_SaveJob_flag != 0) break;
        _menuCB_RuleData_CBtoSAVEDATA();
        if (_menuCB_SaveRule() >= 0) break;
    }
    winMsgClose(1);
}

extern "C" {

void menuCB_FlashEnd(u8 flag) {
    if (flag != 0 && menuIsCheck(0x119) == 1) {
        menuCloseCustom(0x119, 0, 0);
    }
}

void menuCB_FlashStart(u8 flag) {
    u8* win;
    if (flag != 0) {
        if (_CB.mode == 1) {
            FlashSystemSetPlayFrameLabel(0x200A3000, "1_start", "1_end");
            FlashSystemSetNowFrameLabel(0x200A3000, "1_start");
        } else {
            FlashSystemSetPlayFrameLabel(0x200A3000, "2_start", "2_end");
            FlashSystemSetNowFrameLabel(0x200A3000, "2_start");
        }
    } else if (_CB.mode == 1) {
        FlashSystemSetPlayFrameLabel(0x200A3000, "1_end", "1_end");
        FlashSystemSetNowFrameLabel(0x200A3000, "1_end");
    } else {
        FlashSystemSetPlayFrameLabel(0x200A3000, "2_end", "2_end");
        FlashSystemSetNowFrameLabel(0x200A3000, "2_end");
    }
    win = (u8*)windowSearchID(0x119);
    if (win != 0) {
        win[9] = 0;
    }
    CBW(0xB13C) = 1;
    do {
        GSthreadSwitch();
    } while (FlashSystemIsLastFrame(0x200A3000) == 0);
}

}

static u8 menuCB_SubWinDisp_GCENTRY(void) {
    s32 result;
    if (CBW(0xB0F4) == 1) {
        if (CBW(0xB070) == 1) {
            return 0;
        }
        if (CBW(0xAFF0) == 1) {
            switch (menuCB_GCEntry_SubWindow_Disp()) {
            case 0:
                return 0;
            case 1:
                CBW(0xB0F4) = 0;
                CBW(0xAFF0) = 0;
                return 1;
            }
        }
        return 0;
    }
    result = menuCB_GCEntry_SubWindow_Disp();
    GSthreadSwitch();
    switch (result) {
    case 0:
    case 1:
        menuCBGCEntryPokemon();
        if (CBW(0xB0FC) >= 2) {
            return 1;
        }
        CBW(0xB0FC) = 0;
        switch (pokecoloGetCountryCode()) {
        case 0:
            if (CBW(0xB0F0) == 2) {
                menuCBReliveHallCursolInit();
            }
            break;
        case 1:
        case 2:
            break;
        }
        return 1;
    case 2:
        menuCB_GCEntry_PokemonStatusDisp();
        break;
    case 4:
        menuCB_GCEntry_ItemGiveJob();
        break;
    case 5:
        menuCB_GCEntry_ItemKeepJob();
        break;
    case 6:
        break;
    }
    CBW(0xB0FC) = 0;
    return 1;
}

static void menuCB_SAVEDATA_recover(void) {
    memcpy(savedataGetStatus(toolBattleTempSaveData, 0xE), savedataGetStatus(0, 0xE), 0x360);
    memcpy(savedataGetStatus(0, 0), toolBattleTempSaveData, 0x27FD0);
}

static void menuCB_GCEntry_Job(void) {
    Hero* hero;
    Hero* save;
    u32 i;
    save = (Hero*)savedataGetStatus(0, 2);
    hero = &_CB.gcHero;
    heroBiosCopy(hero, save);
    for (i = 0; i < 6; i++) {
        pokemonInit(heroBiosGetPokemonPtr(hero, i));
    }
    menuCB_GCPokemonHPandWAZA_MAX();
    switch (pokecoloGetCountryCode()) {
    case 0:
        break;
    case 1:
    case 2:
        fn_80044314();
        break;
    }
    CBW(0xB100) = 0;
    CBW(0xB0FC) = 0;
    CBW(0xB0F8) = 0;
    CBW(0xB0F0) = 0;
    CBW(0xB0EC) = 0;
    CBW(0xB0E8) = 0;
    CBW(0xB070) = 0;
    CBW(0xAFF0) = 0;
    CBW(0xB0D8) = 0;
    CBW(0xB150) = 0;
    menuCB_SE_Play(0x14);
    menuOpen(0xBB, 0);
    menuOpen(0xBD, 0);
    menuOpen(0xBE, 0);
    menuOpen(0xBF, 0);
    menuOpen(0x10D, 0);
    menuOpen(0x10F, 0);
    menuOpen(0x10E, 0);
    menuOpen(0xC2, 0);
    do {
        CBW(0xB0F4) = 0;
        CBW(0xB0FC) = 0;
        do {
            menuOpen(0xBC, 1);
        } while (menuCB_SubWinDisp_GCENTRY() != 0);
    } while (CBW(0xAFF0) == 0);
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xBC, 0, 0);
    menuCloseCustom(0xC2, 0, 0);
    menuCloseCustom(0x10E, 0, 0);
    menuCloseCustom(0x10F, 0, 0);
    menuCloseCustom(0x10D, 0, 0);
    menuCloseCustom(0xBF, 0, 0);
    menuCloseCustom(0xBE, 0, 0);
    menuCloseCustom(0xBD, 0, 0);
    menuCloseCustom(0xBB, 0, 1);
    heroBiosCopy(save, hero);
    systemFree__4CAntFv();
    switch (pokecoloGetCountryCode()) {
    case 0:
        break;
    case 1:
    case 2:
        fn_8004429C();
        break;
    }
}

static void _imasuguBattleMenuMain(void) {
    s32 i;
    u32* trainer;
    menuCB_SE_Play(0x14);
    for (;;) {
        if (CBW(0xB17C) == 0) {
            menuOpen(0xA4, 1);
            if (CBW(0xB054) == 1) {
                menuCB_SE_Play(0x15);
                menuCloseCustom(0xA4, 0, 0);
                menuCBBios_UnlockContext();
                fn_80151F6C();
                menuCloseCustom(0xA4, 0, 1);
                _flashBackFlag = 0;
                GSfloorPop();
                menuTopSetBattleSelectMode(0);
                floorSetFadeScript(0, 0);
                return;
            }
        } else {
            menuOpen(0xA4, 0);
        }
        _CB.unkB4A1 = -1;
        menuOpenCustom(0x106, windowGetActiveID(), &CBW(0xAFD8), 0, 1, 0);
        if (CBW(0xAFD8) == 4 || CBW(0xB058) == 1) {
            menuCloseCustom(0x106, 0, 1);
            CBW(0xB058) = 0;
            CBW(0xAFD8) = 0;
            CBW(0xB17C) = 0;
            continue;
        }
        CBW(0xB17C) = 1;
        _CB.unk8 = 1;
        _CB.unkC = 0;
        _CB.unk10 = HSD_Rand() % 3;
        switch (CBW(0xAFD4)) {
        case 0:
            _CB.unk14 = 3;
            break;
        case 1:
            _CB.unk14 = 4;
            break;
        }
        menuCB_InitBattle(&_CB);
        menuCBPokemonEntryLoadTex();
        menuCloseCustom(0x106, 2, 0);
        menuCloseCustom(0xA4, 2, 1);
        menuCBpokemonFaceReadWait();
        menuOpenCustom(0xA5, windowGetActiveID(), &CBW(0xAFDC), 0, 1, 0);
        menuCloseCustom(0xA5, 0, 1);
        if (CBW(0xAFDC) == 1 || CBW(0xB05C) == 1) {
            CBW(0xB05C) = 0;
            CBW(0xAFDC) = 0;
            menuCB_SE_Play(0x14);
            continue;
        }
        for (i = 0; i < 2; i++) {
            toolentryTaisenSetEtnryPokemonOrder(0, i);
            toolentryTaisenSetEtnryPokemonOrder(1, i);
        }
        trainer = (u32*)menuCBBios_GetTrainerImmediately(0);
        trainer[4] = 0xF;
        trainer[5] = 0xF;
        trainer[6] = 0xF;
        trainer[7] = 0xF;
        trainer = (u32*)menuCBBios_GetTrainerImmediately(1);
        trainer[4] = 0xF;
        trainer[5] = 0xF;
        trainer[6] = 0xF;
        trainer[7] = 0xF;
        toolentryTaisenEntryPokemon(0);
        toolentryTaisenEntryPokemon(1);
        soundStop(0x568, 0x1F4);
        menuCBBios_LockContext();
        menuColosseumBattleExit();
        _flashBackFlag = 1;
        GSfloorPush(0x397);
        floorWaitForChange();
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        soundOpenPlay(0x568, 0, 0xFF);
    }
}

static s32 _YesNo(long a) {
    switch (pokecoloGetCountryCode()) {
    case 0:
        return menuSubOpenYesNo(0, 0x3C, 0xD2, a);
    case 1:
    case 2:
        return menuSubOpenYesNo(0, 0x3C, 0xC8, a);
    }
    return 0;
}

static void _tempHeroInitAll(void) {
    u32 i;
    i = 0;
    for (; i < 4; i++) {
        memset(&_menuCB_Temp->heroes[i], 0, 0x978);
        heroInit(&_menuCB_Temp->heroes[i]);
    }
}

static s32 _menuCB_SaveRule(void) {
    s32 result;
    menuCBBios_RuleEditSaveON(1);
    menuCBBios_CurrentlyWorkingToolBattleSet(0);
    result = memcardTaskCall(0xD, 2, 0);
    menuCBBios_CurrentlyWorkingToolBattleSet(1);
    if (result != 4) {
        menuCBBios_RuleEditSaveON(0);
    }
    if (result == 4) {
        return 0;
    }
    return -1;
}

static s32 _colosseumbattlemenu_teamselect(long) {
    s32 result;
    s32 sel;
    _CB.w[0x71] = 0;
    _CB.w[0x26] = 0;
    _CB.w[0x6] = 0;
    menuCB_SE_Play(0x14);
    menuOpen(0xAC, 1);
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xAC, 0, 1);
    sel = _CB.w[0x6];
    if (_CB.w[0x71] != 0 || _CB.w[0x26] == 1) {
        menuCB_GBADisconnectedErrorJob();
        return menuCB_MenuRollback(0xA9);
    }
    result = 0xB1;
    switch (sel) {
    case 0:
    case 1:
    case 2: {
        static const s8 sta[3][4] = {{0, 1, 2, 3}, {0, 2, 1, 3}, {0, 3, 1, 2}};
        _CB.orgTrainers[0].unk28 = sta[sel][0];
        _CB.orgTrainers[1].unk28 = sta[sel][1];
        _CB.orgTrainers[2].unk28 = sta[sel][2];
        _CB.orgTrainers[3].unk28 = sta[sel][3];
        menuCB_InitBattle(&_CB);
        break;
    }
    case 3:
    default:
        menuCB_GBADisconnectedErrorJob();
        result = menuCB_MenuRollback(0xA9);
        break;
    }
    return result;
}

static s32 _colosseumbattlemenu_playerdecide(long) {
    _CB.w[0x25] = 0;
    _CB.w[0x40] = 0;
    _CB.w[0x70] = 0;
    menuCB_SE_Play(0x14);
    menuOpen(0xAB, 1);
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xAB, 0, 1);
    if (_CB.w[0x70] != 0 || _CB.w[0x25] == 1) {
        menuCB_GBADisconnectedErrorJob();
        return menuCB_MenuRollback(0xA9);
    }
    if (_CB.unk8 != 2) {
        menuCB_InitBattle(&_CB);
        return 0xB1;
    }
    return 0xAC;
}

static s32 _gbac_connect_job(long) {
    Hero* sp[4];
    s32 mode;
    _tempHeroInitAll();
    menuCBTrainerBios_SetControlerID(&_CB.trainers[0], 1);
    menuCBTrainerBios_SetControlerID(&_CB.trainers[1], 2);
    menuCBTrainerBios_SetControlerID(&_CB.trainers[2], 3);
    menuCBTrainerBios_SetControlerID(&_CB.trainers[3], 4);
    switch (_CB.unk8) {
    case 0:
    case 1:
        if (_CB.orgTrainers[0].unk4 == 0) {
            sp[2] = 0;
            mode = 0;
            sp[0] = &_menuCB_Temp->heroes[0];
            sp[1] = &_menuCB_Temp->heroes[1];
            sp[3] = 0;
        } else {
            sp[0] = 0;
            mode = 1;
            sp[1] = &_menuCB_Temp->heroes[0];
            sp[2] = &_menuCB_Temp->heroes[1];
            sp[3] = 0;
        }
        break;
    case 2:
    default:
        if (_CB.orgTrainers[0].unk4 == 0) {
            mode = 2;
        } else {
            mode = 3;
        }
        sp[0] = &_menuCB_Temp->heroes[0];
        sp[1] = &_menuCB_Temp->heroes[1];
        sp[2] = &_menuCB_Temp->heroes[2];
        sp[3] = &_menuCB_Temp->heroes[3];
        break;
    }
    if (_CB.orgTrainers[0].unk4 == 0) {
        menuCB_SAVEDATA_recover();
        menuCB_GCEntry_Job();
        if (CBW(0xB070) == 1) {
            menuCB_SAVEDATA_recover();
            return menuCB_MenuRollback(0xA9);
        }
    } else {
        systemFree__4CAntFv();
    }
    if (openMenuGBA(mode, 0x1A, sp) < 0) {
        return menuCB_MenuRollback(0xA9);
    }
    if (_CB.orgTrainers[0].unk4 == 0) {
        heroBiosSetHomePlace(&_menuCB_Temp->heroes[0], 0);
    }
    switch (_CB.unk8) {
    case 0:
    case 1: {
        _MENUCBTRAINER* t0;
        _MENUCBTRAINER* t1;
        t0 = &_CB.orgTrainers[0];
        menuCBBios_InitVersusTrainer(t0, &_menuCB_Temp->heroes[0]);
        t1 = &_CB.orgTrainers[1];
        menuCBBios_InitVersusTrainer(t1, &_menuCB_Temp->heroes[1]);
        if (_CB.orgTrainers[0].unk4 == 0) {
            menuCBTrainerBios_SetControlerID(t0, 1);
            menuCBTrainerBios_SetControlerID(t1, 2);
        } else {
            menuCBTrainerBios_SetControlerID(t0, 2);
            menuCBTrainerBios_SetControlerID(t1, 3);
        }
        menuCBTrainerBios_SetControlerID(&_CB.orgTrainers[2], 0);
        menuCBTrainerBios_SetControlerID(&_CB.orgTrainers[3], 0);
        break;
    }
    case 2:
    default: {
        _MENUCBTRAINER* t0;
        _MENUCBTRAINER* t1;
        _MENUCBTRAINER* t2;
        _MENUCBTRAINER* t3;
        t0 = &_CB.orgTrainers[0];
        menuCBBios_InitVersusTrainer(t0, &_menuCB_Temp->heroes[0]);
        t1 = &_CB.orgTrainers[1];
        menuCBBios_InitVersusTrainer(t1, &_menuCB_Temp->heroes[1]);
        t2 = &_CB.orgTrainers[2];
        menuCBBios_InitVersusTrainer(t2, &_menuCB_Temp->heroes[2]);
        t3 = &_CB.orgTrainers[3];
        menuCBBios_InitVersusTrainer(t3, &_menuCB_Temp->heroes[3]);
        menuCBTrainerBios_SetControlerID(t0, 1);
        menuCBTrainerBios_SetControlerID(t1, 2);
        menuCBTrainerBios_SetControlerID(t2, 3);
        menuCBTrainerBios_SetControlerID(t3, 4);
        break;
    }
    }
    return 0xAB;
}

static s32 _colosseumbattlemenu_duel(long) {
    u32 j;
    s32 i;
    s32 next;
    memcpy(&_CB.rules[0], savedataGetStatus(0, 0xE), 0x360);
    systemInit__4CAntFv();
    menuCB2DPokemonALLClear();
    cursorBiosInit();
    CBW(0xB10C) = 0;
    CBW(0xB064) = 0;
    CBW(0xAFE4) = 0;
    CBW(0xB144) = -1;
    menuGBACSetRomVer(0, 0xFFFF);
    menuCB_SE_Play(0x14);
    menuOpen(0xA9, 0);
    menuOpen(0xCE, 0);
    menuOpen(0xCB, 0);
    menuOpen(0xCC, 0);
    menuOpen(0xCD, 0);
    menuOpen(0xAA, 0);
    menuOpen(0xF7, 0);
    for (;;) {
        if (CBW(0xB10C) == 2) {
            CBW(0xAFE0) = 0;
            for (;;) {
                u16* title;
                s32 res;
                u16 buf[21];
                if (CBW(0xAFE0) >= 0x10) {
                    CBW(0xAFE0) -= 0x10;
                }
                menuCB_TUNAIDE01_Rule_SELECT();
                switch (CBW(0xAFE0)) {
                case 0:
                    break;
                case 1:
                    menuCB_RuleNameChengeBeforeJob(0);
                    menuCB_RuleCustomJobDisp(1);
                    menuCB_RuleNameChengeAfterJob(0);
                    continue;
                case 17:
                    menuCB_RuleNameChengeBeforeJob(0);
                    menuCB_RuleCustomJobDisp(0);
                    menuCB_RuleNameChengeAfterJob(0);
                    continue;
                case 18:
                    menuCB_RuleNameChengeBeforeJob(1);
                    title = menuCB_RuleTitleNameGet(CBW(0xB004));
                    for (i = 0; i < 21; i++) {
                        buf[i] = _CB.rules[CBW(0xB004)].name[i];
                    }
                    res = menuNameEntryOpen(6, title);
                    menuCB_RuleNameChengeAfterJob(1);
                    if (res != 0) {
                        if (memcardIsMemCardValid() == 0) {
                            _menuCB_RuleData_CBtoSAVEDATA();
                            menuCBBios_RuleEditSaveON(1);
                        } else {
                            _menuCB_RuleData_SaveJob(0);
                            if (_menuCB_RuleData_SaveJob_flag != 0) {
                                for (i = 0; i < 21; i++) {
                                    title[i] = buf[i];
                                }
                                _menuCB_RuleData_CBtoSAVEDATA();
                            }
                        }
                    }
                    continue;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 19:
                    break;
                }
                break;
            }
        }
        if (CBW(0xB064) == 2) {
            next = -1;
            menuGBACSetRomVer(0, 0xFFFF);
            _CB.unkC = 0;
            fn_80151F6C();
            break;
        } else if (CBW(0xB064) == 1) {
            if (CBW(0xAFF4) == 0 || CBW(0xAFF4) == 2) {
                if (memcardIsMemCardValid() == 0) {
                    winMsgOpen(2, 0x82, 1, 0);
                    winMsgClose(1);
                    CBW(0xB064) = 0;
                    continue;
                }
                if (gamedatasaveGetStatus(0, 4) == 0) {
                    winMsgOpen(2, 0x9C, 1, 0);
                    winMsgClose(1);
                    CBW(0xB064) = 0;
                    continue;
                }
            }
            winMsgOpen(2, 0x4419, 1, 1);
            if (_YesNo(0) != 0) {
                winMsgClose(0);
                CBW(0xB064) = 0;
                continue;
            }
            winMsgClose(0);
            _CB.unk8 = tunaide_select[CBW(0xAFF4)].mode;
            if (CBW(0xAFFC) == 6) {
                _CB.unk10 = 0;
            } else {
                _CB.unk10 = tunaide_select_field[CBW(0xAFFC)];
            }
            menuCBTrainerBios_SetHomePlace(&_CB.orgTrainers[0], tunaide_select[CBW(0xAFF4)].home);
            menuCBTrainerBios_SetControlerID(&_CB.orgTrainers[0], tunaide_select[CBW(0xAFF4)].ids[0]);
            for (j = 1; j < 4; j++) {
                menuCBTrainerBios_SetHomePlace(&_CB.orgTrainers[j], 1);
                menuCBTrainerBios_SetControlerID(&_CB.orgTrainers[j], tunaide_select[CBW(0xAFF4)].ids[j]);
            }
            if (CBW(0xAFF8) == 0) {
                _CB.unk8 = 0;
            } else {
                _CB.unk8 = 1;
            }
            if (CBW(0xAFF4) >= 2) {
                _CB.unk8 = 2;
            }
            next = 0xB0;
            break;
        } else {
            GSthreadSwitch();
        }
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xF7, 0, 0);
    menuCloseCustom(0xAA, 0, 0);
    menuCloseCustom(0xCD, 0, 0);
    menuCloseCustom(0xCC, 0, 0);
    menuCloseCustom(0xCB, 0, 0);
    menuCloseCustom(0xCE, 0, 0);
    menuCloseCustom(0xA9, 0, 1);
    if (CBW(0xB064) == 2) {
        systemFree__4CAntFv();
    }
    _CB.unkC = CBW(0xB004);
    return next;
}

extern "C" {

void menuColosseumBattleMain(void) {
    s32 next;
    u32 target;
    menuCB_CurrentMenuID();
    target = 0;
    menuCB_FlashStart(1);
    for (;;) {
        soundOpenPlay(0x568, 0, 0xFF);
        if (_CB.mode == 1) {
            menuGBACSetRomVer(0, 0xFFFF);
            _imasuguBattleMenuMain();
            return;
        }
        _CB.unkB4A1 = 0;
        while (menuCB_CurrentMenuID() > 0) {
            menuCB_CurrentMenuID();
            next = menuCB_CurrentMenuID();
            switch (menuCB_CurrentMenuID()) {
            case 0xA9:
                next = _colosseumbattlemenu_duel(next);
                break;
            case 0xB0:
                next = _gbac_connect_job(next);
                break;
            case 0xAB:
                next = _colosseumbattlemenu_playerdecide(next);
                break;
            case 0xAC:
                next = _colosseumbattlemenu_teamselect(next);
                break;
            case 0xB1:
                soundStop(0x568, 0x1F4);
                menuCBBios_LockContext();
                target = 0x397;
                break;
            }
            if (GSinputIsConnected(1) == 0 && gbaCommandIsConnected(1) == 0) {
                winMsgOpen(2, 0x4436, 0, 0);
                GSthreadSwitch();
                do {
                    GSthreadSwitch();
                } while (GSinputIsConnected(1) == 0);
                winMsgClose(1);
            }
            if (next < 0) {
                if (menuCB_MenuPop() < 0) {
                    break;
                }
            } else if (next != menuCB_CurrentMenuID()) {
                if (windowGetActiveID() == menuCB_CurrentMenuID()) {
                    menuCloseCustom(menuCB_CurrentMenuID(), 0, 0);
                }
                menuCB_MenuPush(next);
            }
            if (target != 0) {
                if (windowGetActiveID() == menuCB_CurrentMenuID()) {
                    menuCloseCustom(menuCB_CurrentMenuID(), 0, 0);
                }
                break;
            }
        }
        if (target == 0) {
            target = 0x384;
            menuCBBios_UnlockContext();
            menuCB_WaitGCControler1();
        } else {
            menuCBBios_LockContext();
        }
        if (target == 0x384) {
            _flashBackFlag = 0;
            GSfloorPop();
            menuTopSetBattleSelectMode(1);
            floorSetFadeScript(0, 0);
            return;
        }
        _flashBackFlag = 1;
        fadeSet(3, 0.5f);
        fadeCheck(1);
        menuColosseumBattleExit();
        GSfloorPush(target);
        floorSetFadeScript(0, 0x5960008);
        floorWaitForChange();
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        fadeSet(2, 0.5f);
        fadeCheck(1);
        menuCB_CurrentMenuID();
        target = 0;
    }
}

}

extern "C" {

void menuColosseumBattleExit(void) {
    fadeCheck(1);
    if (menuCBBios_ContextIsLocked() == 0) {
        GSflagSet(0x30D, 0);
    }
    toolentryDebugPokemonDelete();
    if (_CB.mode == 1) {
        if (fightReadResourceID(0x842, 0x184F3400) == 0) {
            fightFreeResourceID(0x842, 0x184F3400);
        }
    } else {
        if (fightReadResourceID(0x842, 0x195F3400) == 0) {
            fightFreeResourceID(0x842, 0x195F3400);
        }
    }
    GSfloorGetCurrent();
    menuCB_FlashEnd(_flashBackFlag);
    if (_menuCB_Temp != 0) {
        GSmemFree(_menuCB_Temp);
    }
    _menuCB_Temp = 0;
    menuCB_SAVEDATA_recover();
    toolBattleTempSaveData = memcardMemFreeForSavedata(toolBattleTempSaveData);
    menuCBBios_CurrentlyWorkingToolBattleSet(0);
    GSfsysFree(0x14);
    GSresFreeGroup(0x14);
    GSfsysFree(0x88C);
    GSresFreeGroup(0x88C);
}

void menuColosseumBattleInit(void) {
    if (toolBattleTempSaveData == 0) {
        _CB.unk9C80 = 0;
        menuCBBios_CurrentlyWorkingToolBattleSet(1);
        GSflagSet(0x30D, 0);
        if (GSflagGet(0x3C4) >= flag_etc->unk428) {
            _CB.unkB4A0 = 1;
        } else {
            _CB.unkB4A0 = 0;
        }
        if (_CB.mode == 1) {
            fightReadResourceID(0x842, 0x184F3400);
        } else {
            fightReadResourceID(0x842, 0x195F3400);
        }
        GSfsysReadWait(0x88C);
        GSfsysReadWait(0x14);
        _menuCB_Temp = (CBTemp*)GSmemAllocAlign(0xF0C0, 0x20);
        menuCBBios_RuleConstRuleSet();
        toolBattleTempSaveData = memcardMemAllocForSavedata();
        memcpy(toolBattleTempSaveData, savedataGetStatus(0, 0), 0x27FD0);
        toolentryDebugPokemonCreate();
        menuCBBios_InitContext(&_CB);
        menuCBBios_ContextIsLocked();
    }
}

}

extern "C" {

void menuColosseumBattle(s32 mode) {
    s32 i;
    menuCBBios_UnlockContext();
    _CB.mode = mode;
    for (i = 0; i < 0x20; i++) {
        _CB.w[0x20 + i] = 0;
        _CB.w[i] = 0;
    }
    for (i = 0; i < 0x30; i++) {
        _CB.w[0x40 + i] = 0;
    }
    for (i = 0; i < 0x10; i++) {
        _CB.w[0x70 + i] = 0;
    }
    _flashBackFlag = 1;
    GSfloorPush(0x395);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
}

}
