/* Debug menu entries for the fight (battle) debug menu. */
#include <global.h>

typedef struct DbgFightWindow {
    u8 unk0[4];
    s32 menu;
    u8 unk8[0x80];
    s32 result;
    u8 unk88[0x18];
    u8 unkA4;
    u8 unkA5;
} DbgFightWindow;

extern void GScharCat(s16*, s16*, s16*);
extern void GScharMakeFromSJIS(s16*, const char*);
extern s32 GSfloorGetCurrentFloorGroupID(void);
extern s32 GSinputButtonsChanged(s32);
extern s32 GSinputButtonsPressed(s32);
extern u16 GSmsgGetGSchar(u32);
extern u32 GSthreadCreate(s32, s32, s32, s32, s32, void*);
extern void GSthreadSetArgs(u32, s32, ...);
extern void GSthreadSetName(u32, const char*);
extern void GSthreadSwitch(void);
extern void Sequence_Free(u16);
extern void Sequence_SetVisibility(s32, s32);
extern void battleGridReplacePokemon(u16, s32);
extern void battleGridUpdate(void);
extern void dbgMenuClose(void);
extern s32 dbgMenuFightTrainerAiAddsubDataComboEditSub(void);
extern s32 dbgMenuFightTrainerAiAddsubDataIrekaeDasuEditSub(void);
extern s32 dbgMenuFightTrainerAiAddsubDataIrekaeModosuEditSub(void);
extern s32 dbgMenuFightTrainerAiAddsubDataItemEditSub(void);
extern s32 dbgMenuFightTrainerAiAddsubDataWazaDefpokemonEditSub(void);
extern s32 dbgMenuFightTrainerAiAddsubDataWazaUsewazaEditSub(void);
extern s32 dbgMenuFightTrainerAiDataEditSub(u16);
extern void dbgMenuFightTrainerDataStatusInputDigit(u16, s32, s32, s32, s32);
extern s32 dbgMenuFightTrainerPokemonPartDataEditSub(u16);
extern s32 dbgMenuFightWazaEditSub(u16);
extern s32 dbgMenuPokemonEditSub(u32, s32, s8*, s8*, s8*, s8*);
extern u32 fightFloorGetFightPokemonPtrToFightTrainerPtr(s32, u32);
extern u32 fightFloorGetStatus(s32, u16, s32, s32);
extern void fightFloorSetTimeOutAllFightResult(s32);
extern u8 fightIsFight(void);
extern u16 fightKindDataBiosGetName(u32);
extern u32 fightKindDataBiosGetPtr(u16);
extern void fightMenuFightOutPokemonRenewStatusMenu(u32, u16, s32);
extern void fightMenuFightTrainerRenewStatusMenu(u32, u16);
extern void fightOutPokemonGetTokuseiDataId(u32);
extern void fightOutPokemonGetZokuseiDataId(u32, s32);
extern void fightOutPokemonInitJoutaiDataId(u32, s32);
extern u8 fightOutPokemonIsUseHensinBuff(void);
extern void fightOutPokemonSetTokuseiDataId(u32, s32);
extern void fightOutPokemonSetZokuseiDataId(u32, u8, u16);
extern u32 fightPokemonGetPokemonPtr(u32);
extern u8 fightSeqCheckYubiwohuruWazaDataId(u16);
extern u8 fightSeqGetEffectAminFlag(void);
extern void fightSeqSetEffectAminFlag(u8);
extern void fightSetFightResultId(s32);
extern u32 fightSideGetValidFightTrainerPtr(u32, s32);
extern u32 fightTargetGetPtrAsNowFightType(s32, s32);
extern u8 fightTrainerCheckCanIrekaeFightPokemon(u32, u32);
extern u32 fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(u32, u32);
extern u32 fightTrainerGetStatus(u32, u16, s32, u8);
extern u32 fightTrainerGetValidFightPokemonPtr(u32, s32);
extern u8 figthPokemonGetLevel(u32);
extern s16* getDeckMsgID(u16, s32, s32);
extern void menuCloseCustom(s32, s32, s32);
extern void menuFaceGetID(u32);
extern void menuFaceLoad(u32, s32, s32);
extern s8 menuFaceSearchEnable(void);
extern s32 menuGetCursorItemID(s32);
extern s32 menuOpen(s32, s32);
extern s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
extern void menuSubCloseNumberInput(void);
extern u8 menuSubOpenNumberInput(u8, s32*, s32, s32, s32, s32);
extern u8 menuSubOpenNumberInputID(u16, u32*, void (*)());
extern s8 menuSubOpenYesNo(s32, s32, s32, s32);
extern void msgctrlSetValue(s32, u16);
extern s32 pokemonCreateSequence(u32);
extern u16 pokemonGetStatus(u32, u16, s32, u16);
extern s32 pokemonGetTokuseiDataId(u32);
extern void pokemonSetSequenceStatus(u32, u16);
extern void pokemonSetStatus(u32, s32, s32, s32, s32);
extern u32 wazaGetStatus(s32, u16, s32, s32);
extern u32 wazaGetWazaTypeIdName(u8);
extern u8 winMsgCloseCheckFight(void);
extern void winMsgCloseFight(s32);
extern void winMsgOpenFight(s32, s32);
extern u32 zokuseiBiosGetName(u16);
extern u32 deckGetTrainerSize(void);

extern void fightEncount(void);
extern u32* fight_floor_data_number;
extern u32* fight_kind_data_number;
extern u32* fight_trainer_ai_value_addsub_data_number;
extern u32* fight_trainer_pokemon_part_data_number;
extern u32* zokusei_data_number;
extern u32 deck_group_data[];
extern u32 deck_group_data_number;

static s16 strbuf[0x40];
static u8 _msg_speed = 5;
static u16 _dbgmenu_fight_waza_edit_waza_data_id = 1;
static u16 _dbgmenu_fight_deck_data_id = 1;
static u16 _dbgmenu_fight_sample_encount_data_id = 1;
static u16 _dbgmenu_fight_story_encount_data_id = 1;
static u16 _dbgmenu_fight_hundred_encount_data_id = 1;
static u16 _dbgmenu_fight_imasugu_encount_data_id = 1;
static u16 _dbgmenu_fight_virtual_encount_data_id = 1;
static u16 _dbgmenu_fight_bingo_encount_data_id = 1;
static u16 _dbgmenu_fight_colosseum_encount_data_id = 1;
static u8 _fight_trainer_ai_last_value_revise_flag = 1;
static u8 _fight_pokemon_status_menu_open_flag = 1;
static u16 _dbgmenu_fight_trainer_pokemon_part_data_id = 1;

static u8 _msg_key_wait_flag;
static u8 _all_fight_trainer_operate_flag;
static u8 _fight_debug_menu_open_flag;
static u8 _fight_trainer_ai_flow_disp_flag;
static u8 _tuikakouka_flag;
static u32 _target_fight_side_ptr;
static u32 _target_fight_trainer_ptr;
static u32 _target_fight_pokemon_ptr;
static u8 _soubikakouka_flag;
static u16 _yubiwohuru_waza_data_id;
static u16 _dbgmenu_fight_trainer_data_id;
static u16 _dbgmenu_fight_trainer_ai_addsub_data_id;
static u16 _readEncountDataCnt;
static s32 _readEncountDataID;
static s32 _readEncountDataName;

s32 dbgMenuFightGetFightTrainerDataId(u32 id);
s32 dbgMenuFightGetFightTrainerPokemonPartDataId(u32 id);
s32 dbgMenuFightGetFightTrainerAiAddsubValueDataId(u32 id, u8 close);
s32 dbgMenuFightGetWazaDataId(u32 id);
u8 dbgMenuFightGetMsgSpeed(void);
void dbgMenuFightSetMsgSpeed(u8 speed);
u8 dbgMenuFightGetTuikakoukaFlag(void);
void dbgMenuFightSetTuikakoukaFlag(u8 flag);
u8 dbgMenuFightGetMsgKeyWaitFlag(void);
void dbgMenuFightSetMsgKeyWaitFlag(u8 flag);
u8 dbgMenuFightGetAllFightTrainerOperateFlag(void);
void dbgMenuFightSetAllFightTrainerOperateFlag(u8 flag);
u8 dbgMenuFightGetFightDebugMenuOpenFlag(void);
void dbgMenuFightSetFightDebugMenuOpenFlag(u8 flag);
u8 dbgMenuFightGetFightTrainerAiFlowDispFlag(void);
void dbgMenuFightSetFightTrainerAiFlowDispFlag(u8 flag);
u8 dbgMenuFightGetSoubikoukaFlag(void);
void dbgMenuFightSetSoubikoukaFlag(u8 flag);
u16 dbgMenuFightGetYubiwohuruWazaDataId(void);
void dbgMenuFightSetYubiwohuruWazaDataId(u16 id);
u8 dbgMenuFightGetFightTrainerAiLastValueReviseFlag(void);
void dbgMenuFightSetFightTrainerAiLastValueReviseFlag(u8 flag);
u8 dbgMenuFightGetFightPokeStMenuOpenFlag(void);
void dbgMenuFightSetFightPokeStMenuOpenFlag(u8 flag);
u32 dbgMenuGetGsinputMsgId(s32 id);

static void _dbgMenuFightStopSub(s32 result);
static s32 _dbgMenuFightFightPokemonSelectSub(u32 pokemon);
static s32 _dbgMenuFightFightTrainerSerihuTestSub(u16 id, u32 kind);
static void _dbgMenuFightGetFightTrainerAiAddsubValueDataIdSub(u32 id);
static void _dbgMenuFightGetFightTrainerPokemonPartDataIdSub(u32 id);
static void _dbgMenuFightGetWazaDataIdSub(u32 id);
static void _dbgMenuFightGetWazaTypeIdSub(u32 id);
static void _dbgMenuFightGetZokuseiDataIdSub(u32 id);
static void _dbgMenuFightGetGsinputDevIdSub(s32 id);
static void _dbgMenuFightGetFightTrainerDataIdSub(u32 id);
static void _dbgMenuFightGetPokemonEntrySub(u32 id);
static void _dbgMenuFightGetPokemonFightTypeSub(u32 id);
static void _dbgMenuFightGetFightTypeDataIdSub(u32 id);
static void _dbgMenuFightGetFightKindDataIdSub(u32 id);
static void _dbgMenuFightGetFightFloorDataIdSub(u32 id);
static void _dbgMenuFightGetFightDeckDataIdSub(u32 id);
static void _dbgMenuFightGetFightEncountDataIdSub(u32 id);

void dbgMenuFightFightTrainerSerihuTestHaiboku2(void) {
    _dbgMenuFightFightTrainerSerihuTestSub(_dbgmenu_fight_trainer_data_id, 3);
}

void dbgMenuFightFightTrainerSerihuTestHaiboku(void) {
    _dbgMenuFightFightTrainerSerihuTestSub(_dbgmenu_fight_trainer_data_id, 2);
}

void dbgMenuFightFightTrainerSerihuTestSyouri(void) {
    _dbgMenuFightFightTrainerSerihuTestSub(_dbgmenu_fight_trainer_data_id, 1);
}

void dbgMenuFightFightTrainerSerihuTestToujou(void) {
    _dbgMenuFightFightTrainerSerihuTestSub(_dbgmenu_fight_trainer_data_id, 0);
}

static s32 _dbgMenuFightFightTrainerSerihuTestSub(u16 id, u32 kind) {
    if (fightTrainerGetStatus(0, id, 8, kind) == 0) {
        return -1;
    }
    winMsgOpenFight(1, 1);
    winMsgCloseFight(1);
    return 1;
}

s32 dbgMenuFightFightTrainerSerihuTest(void) {
    s32 id = dbgMenuFightGetFightTrainerDataId(_dbgmenu_fight_trainer_data_id);

    if (id < 0) {
        return -1;
    }
    _dbgmenu_fight_trainer_data_id = id;
    return 1;
}

u32 dbgMenuGetGsinputMsgId(s32 id) {
    if (id == 0) {
        return 0xED04;
    }
    if (id == 1) {
        return 0xED05;
    }
    if (id == 2) {
        return 0xED06;
    }
    if (id == 3) {
        return 0xED07;
    }
    if (id == 4) {
        return 0xED08;
    }
    return 0xED04;
}

void dbmMenuFightButtonNormal(DbgFightWindow* window) {
    u32 changed;

    if (window != 0) {
        changed = GSinputButtonsChanged(1);
        if (GSinputButtonsPressed(1) & changed & 0x100) {
            window->unkA4 = 1;
            window->result = menuGetCursorItemID(window->menu);
        }
        changed = GSinputButtonsChanged(1);
        if (GSinputButtonsPressed(1) & changed & 0x1000) {
            window->unkA4 = 1;
            window->result = -2;
        }
        changed = GSinputButtonsChanged(1);
        if (GSinputButtonsPressed(1) & changed & 0x200) {
            window->unkA4 = 1;
            window->unkA5 = 1;
            window->result = -1;
        }
    }
}

s32 dbgMenuFightStopTimeOut(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    fightFloorSetTimeOutAllFightResult(0);
    dbgMenuClose();
    return 0;
}

s32 dbgMenuFightStopHostLose(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _dbgMenuFightStopSub(3);
    return 0;
}

s32 dbgMenuFightStopHostWin(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    _dbgMenuFightStopSub(2);
    return 0;
}

static void _dbgMenuFightStopSub(s32 result) {
    fightSetFightResultId(result);
    dbgMenuClose();
}

#define DBG_FIGHT_POKEMON_SELECT(n)                                                         \
    s32 dbgMenuFightFightPokemonSelect##n(void) {                                           \
        u32 pokemon;                                                                        \
        if (fightIsFight() == 0) {                                                          \
            return -1;                                                                      \
        }                                                                                   \
        pokemon = fightTrainerGetValidFightPokemonPtr(_target_fight_trainer_ptr, n);        \
        _target_fight_pokemon_ptr = pokemon;                                                \
        if (pokemon == 0) {                                                                 \
            return -1;                                                                      \
        }                                                                                   \
        return _dbgMenuFightFightPokemonSelectSub(pokemon);                                 \
    }

DBG_FIGHT_POKEMON_SELECT(5)
DBG_FIGHT_POKEMON_SELECT(4)
DBG_FIGHT_POKEMON_SELECT(3)
DBG_FIGHT_POKEMON_SELECT(2)
DBG_FIGHT_POKEMON_SELECT(1)
DBG_FIGHT_POKEMON_SELECT(0)

static s32 _dbgMenuFightFightPokemonSelectSub(u32 pokemon) {
    s8 a = 0;
    s8 b = 0;
    s8 c = 0;
    s8 d = 0;
    u16 floorStatus;
    u32 pokemonPtr;
    u32 trainer;
    u8 level;
    s32 result;
    u32 out;
    u16 i;
    u16 oldSeq;
    u16 prevType;
    s32 newSeq;

    floorStatus = fightFloorGetStatus(0, 0, 0x14, 0);
    pokemonPtr = fightPokemonGetPokemonPtr(pokemon);
    if (pokemonPtr == 0) {
        return -1;
    }
    trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(0, pokemon);
    if (trainer == 0) {
        return -1;
    }
    level = figthPokemonGetLevel(pokemon);
    if (fightTrainerCheckCanIrekaeFightPokemon(trainer, pokemon) == 2) {
        out = fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(trainer, pokemon);
        if (fightOutPokemonIsUseHensinBuff() == 1) {
            return -1;
        }
        if (out != 0) {
            fightOutPokemonGetTokuseiDataId(out);
            for (i = 0; i < 2; i++) {
                fightOutPokemonGetZokuseiDataId(out, 0);
            }
        }
        result = dbgMenuPokemonEditSub(pokemonPtr, 1, &a, &b, &c, &d);
        if (result == 1) {
            prevType = pokemonGetStatus(pokemonPtr, 0, 0x6E, 0);
            if (out != 0) {
                oldSeq = pokemonGetStatus(out, 0, 0xEE, 0);
                if (oldSeq != 0) {
                    menuFaceLoad(pokemonPtr, 0, 0);
                    for (;;) {
                        menuFaceGetID(pokemonPtr);
                        if (menuFaceSearchEnable() != 0) {
                            break;
                        }
                        GSthreadSwitch();
                    }
                    newSeq = pokemonCreateSequence(pokemon);
                    battleGridReplacePokemon(oldSeq, newSeq);
                    battleGridUpdate();
                    pokemonSetStatus(out, 0, 0xEE, 0, newSeq);
                    Sequence_Free(oldSeq);
                    Sequence_SetVisibility(newSeq, 1);
                    fightOutPokemonInitJoutaiDataId(out, 0x14);
                }
                fightMenuFightOutPokemonRenewStatusMenu(out, fightFloorGetStatus(0, 0, 0x14, 0), 1);
                pokemonSetSequenceStatus(pokemonPtr, pokemonGetStatus(out, 0, 0xEE, 0));
                fightOutPokemonSetTokuseiDataId(out, pokemonGetTokuseiDataId(pokemonPtr));
                for (i = 0; i < 2; i++) {
                    fightOutPokemonSetZokuseiDataId(out, i, pokemonGetStatus(0, prevType, 0x16, i));
                }
            }
        }
    } else {
        result = dbgMenuPokemonEditSub(pokemonPtr, 1, 0, 0, 0, 0);
    }
    if (figthPokemonGetLevel(pokemon) > level) {
        pokemonSetStatus(pokemon, 0, 0xD0, 0, 1);
    }
    fightMenuFightTrainerRenewStatusMenu(trainer, floorStatus);
    return result;
}

s32 dbgMenuFightFightTrainerPokemonPartDataEdit(void) {
    s32 id;

    if (fightIsFight() == 0) {
        return -1;
    }
    for (;;) {
        id = dbgMenuFightGetFightTrainerPokemonPartDataId(_dbgmenu_fight_trainer_pokemon_part_data_id);
        if (id >= 0) {
            _dbgmenu_fight_trainer_pokemon_part_data_id = id;
            dbgMenuFightTrainerPokemonPartDataEditSub(id);
        } else {
            break;
        }
    }
    return 1;
}

s32 dbgMenuFightFightTrainerAiDataEdit(void) {
    u16 id = fightTrainerGetStatus(0, fightTrainerGetStatus(_target_fight_trainer_ptr, 0, 0x43, 0), 2, 0);

    if (fightIsFight() == 0) {
        return -1;
    }
    return dbgMenuFightTrainerAiDataEditSub(id);
}

void dbgMenuFightFightTrainerAiAddsubCombo(void) {
    dbgMenuFightTrainerAiAddsubDataComboEditSub();
}

void dbgMenuFightFightTrainerAiAddsubItem(void) {
    dbgMenuFightTrainerAiAddsubDataItemEditSub();
}

void dbgMenuFightFightTrainerAiAddsubWazaUsewaza(void) {
    dbgMenuFightTrainerAiAddsubDataWazaUsewazaEditSub();
}

void dbgMenuFightFightTrainerAiAddsubWazaDefpokemon(void) {
    dbgMenuFightTrainerAiAddsubDataWazaDefpokemonEditSub();
}

s32 dbgMenuFightFightTrainerAiAddsubWaza(void) {
    return 1;
}

void dbgMenuFightFightTrainerAiAddsubIrekaeDasu(void) {
    dbgMenuFightTrainerAiAddsubDataIrekaeDasuEditSub();
}

void dbgMenuFightFightTrainerAiAddsubIrekaeModosu(void) {
    dbgMenuFightTrainerAiAddsubDataIrekaeModosuEditSub();
}

s32 dbgMenuFightFightTrainerAiAddsubIrekae(void) {
    return 1;
}

s32 dbgMenuFightFightTrainerAiAddsubDataEdit(void) {
    s32 id;

    for (;;) {
        id = dbgMenuFightGetFightTrainerAiAddsubValueDataId(_dbgmenu_fight_trainer_ai_addsub_data_id, 1);
        if (id >= 0) {
            _dbgmenu_fight_trainer_ai_addsub_data_id = id;
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3E, 0, 0xC8, -0xC8);
        } else {
            break;
        }
    }
    return 1;
}

s32 dbgMenuFightFightTrainerSelect1(void) {
    u32 trainer;

    if (fightIsFight() == 0) {
        return -1;
    }
    trainer = fightSideGetValidFightTrainerPtr(_target_fight_side_ptr, 1);
    _target_fight_trainer_ptr = trainer;
    if (trainer == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightTrainerSelect0(void) {
    u32 trainer;

    if (fightIsFight() == 0) {
        return -1;
    }
    trainer = fightSideGetValidFightTrainerPtr(_target_fight_side_ptr, 0);
    _target_fight_trainer_ptr = trainer;
    if (trainer == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightSideSelectHostEnemy(void) {
    u32 side;

    if (fightIsFight() == 0) {
        return -1;
    }
    side = fightTargetGetPtrAsNowFightType(5, 0);
    _target_fight_side_ptr = side;
    if (side == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightSideSelectHost(void) {
    u32 side;

    if (fightIsFight() == 0) {
        return -1;
    }
    side = fightTargetGetPtrAsNowFightType(4, 0);
    _target_fight_side_ptr = side;
    if (side == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightFloorEditTenkou(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightWazaEdit(void) {
    s32 id;

    if (fightIsFight() == 0) {
        return -1;
    }
loop:
    id = dbgMenuFightGetWazaDataId(_dbgmenu_fight_waza_edit_waza_data_id);
    if (id >= 0) {
        _dbgmenu_fight_waza_edit_waza_data_id = id;
        dbgMenuFightWazaEditSub(id);
        goto loop;
    }
    return 1;
}

#define DBG_FIGHT_FLAG_TOGGLE(getter, setter, cur) \
    {                                              \
        s8 answer = menuSubOpenYesNo(0x7F, -1, -1, cur == 0); \
        if (answer == 0) {                         \
            setter(1);                             \
        } else if (answer == 1) {                  \
            setter(0);                             \
        }                                          \
    }

s32 dbgMenuFightFlagEdit(void) {
    s32 value;
    s32 result;
    u8 msgSpeed = dbgMenuFightGetMsgSpeed();
    u8 tuikakouka = dbgMenuFightGetTuikakoukaFlag();
    u8 keyWait = dbgMenuFightGetMsgKeyWaitFlag();
    u8 allOperate = dbgMenuFightGetAllFightTrainerOperateFlag();
    u8 debugOpen = dbgMenuFightGetFightDebugMenuOpenFlag();
    u8 effectAnim = fightSeqGetEffectAminFlag();
    u8 aiFlowDisp = dbgMenuFightGetFightTrainerAiFlowDispFlag();
    u8 soubikouka = dbgMenuFightGetSoubikoukaFlag();
    u16 yubiwohuru = dbgMenuFightGetYubiwohuruWazaDataId();
    u8 lastValueRevise = dbgMenuFightGetFightTrainerAiLastValueReviseFlag();
    u16 waza;

    dbgMenuFightGetFightPokeStMenuOpenFlag();
    for (;;) {
        result = menuOpenCustom(0xE, 0, 0, 0, 1, 0, 0);
        switch (result) {
        case -1:
            menuCloseCustom(0xE, 0, 1);
            dbgMenuFightSetMsgSpeed(msgSpeed);
            dbgMenuFightSetTuikakoukaFlag(tuikakouka);
            dbgMenuFightSetMsgKeyWaitFlag(keyWait);
            dbgMenuFightSetAllFightTrainerOperateFlag(allOperate);
            dbgMenuFightSetFightDebugMenuOpenFlag(debugOpen);
            fightSeqSetEffectAminFlag(effectAnim);
            dbgMenuFightSetFightTrainerAiFlowDispFlag(aiFlowDisp);
            dbgMenuFightSetSoubikoukaFlag(soubikouka);
            dbgMenuFightSetYubiwohuruWazaDataId(yubiwohuru);
            dbgMenuFightSetFightTrainerAiLastValueReviseFlag(lastValueRevise);
            return -1;
        case -2:
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            menuCloseCustom(0xE, 0, 1);
            return 1;
        case 114:
            DBG_FIGHT_FLAG_TOGGLE(0, dbgMenuFightSetTuikakoukaFlag, dbgMenuFightGetTuikakoukaFlag())
            break;
        case 118:
            if (menuSubOpenNumberInput(dbgMenuFightGetMsgSpeed(), &value, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
            } else {
                dbgMenuFightSetMsgSpeed(value);
                menuSubCloseNumberInput();
            }
            break;
        case 120:
            DBG_FIGHT_FLAG_TOGGLE(0, dbgMenuFightSetMsgKeyWaitFlag, dbgMenuFightGetMsgKeyWaitFlag())
            break;
        case 122:
            DBG_FIGHT_FLAG_TOGGLE(0, fightSeqSetEffectAminFlag, fightSeqGetEffectAminFlag())
            break;
        case 124:
            DBG_FIGHT_FLAG_TOGGLE(0, dbgMenuFightSetAllFightTrainerOperateFlag, dbgMenuFightGetAllFightTrainerOperateFlag())
            break;
        case 126:
            DBG_FIGHT_FLAG_TOGGLE(0, dbgMenuFightSetFightDebugMenuOpenFlag, dbgMenuFightGetFightDebugMenuOpenFlag())
            break;
        case 128:
            DBG_FIGHT_FLAG_TOGGLE(0, dbgMenuFightSetFightTrainerAiFlowDispFlag, dbgMenuFightGetFightTrainerAiFlowDispFlag())
            break;
        case 116:
            DBG_FIGHT_FLAG_TOGGLE(0, dbgMenuFightSetSoubikoukaFlag, dbgMenuFightGetSoubikoukaFlag())
            break;
        case 130:
            if (fightIsFight() != 0) {
                waza = dbgMenuFightGetYubiwohuruWazaDataId();
                for (;;) {
                    waza = dbgMenuFightGetWazaDataId(waza);
                    if ((s32)waza < 0) {
                        break;
                    }
                    if (fightSeqCheckYubiwohuruWazaDataId(waza) == 1) {
                        dbgMenuFightSetYubiwohuruWazaDataId(waza);
                        break;
                    }
                }
            }
            break;
        case 132:
            DBG_FIGHT_FLAG_TOGGLE(0, dbgMenuFightSetFightTrainerAiLastValueReviseFlag, dbgMenuFightGetFightTrainerAiLastValueReviseFlag())
            break;
        case 134:
            DBG_FIGHT_FLAG_TOGGLE(0, dbgMenuFightSetFightPokeStMenuOpenFlag, dbgMenuFightGetFightPokeStMenuOpenFlag())
            break;
        }
    }
}

s32 dbgMenuFightStop(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightFightFloorEdit(void) {
    if (fightIsFight() == 0) {
        return -1;
    }
    return 1;
}

s32 dbgMenuFightEncount(u16 id) {
    u32 thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (void*)fightEncount);

    if (thread != 0) {
        GSthreadSetArgs(thread, 1, id);
        GSthreadSetName(thread, "fightEnc(Debug)");
    }
    return 0;
}

s32 dbgMenuFightMain(void) {
    return 1;
}

void dbgMenuFightSetYubiwohuruWazaDataId(u16 id) {
    _yubiwohuru_waza_data_id = id;
}

void dbgMenuFightSetSoubikoukaFlag(u8 flag) {
    _soubikakouka_flag = flag;
}

u16 dbgMenuFightGetYubiwohuruWazaDataId(void) {
    return _yubiwohuru_waza_data_id;
}

u8 dbgMenuFightGetSoubikoukaFlag(void) {
    return _soubikakouka_flag;
}

void dbgMenuFightSetFightPokeStMenuOpenFlag(u8 flag) {
    _fight_pokemon_status_menu_open_flag = flag;
}

u8 dbgMenuFightGetFightPokeStMenuOpenFlag(void) {
    return _fight_pokemon_status_menu_open_flag;
}

void dbgMenuFightSetFightTrainerAiLastValueReviseFlag(u8 flag) {
    _fight_trainer_ai_last_value_revise_flag = flag;
}

u8 dbgMenuFightGetFightTrainerAiLastValueReviseFlag(void) {
    return _fight_trainer_ai_last_value_revise_flag;
}

void dbgMenuFightSetFightTrainerAiFlowDispFlag(u8 flag) {
    _fight_trainer_ai_flow_disp_flag = flag;
}

u8 dbgMenuFightGetFightTrainerAiFlowDispFlag(void) {
    return _fight_trainer_ai_flow_disp_flag;
}

void dbgMenuFightSetFightDebugMenuOpenFlag(u8 flag) {
    _fight_debug_menu_open_flag = flag;
}

u8 dbgMenuFightGetFightDebugMenuOpenFlag(void) {
    return _fight_debug_menu_open_flag;
}

void dbgMenuFightSetAllFightTrainerOperateFlag(u8 flag) {
    _all_fight_trainer_operate_flag = flag;
}

u8 dbgMenuFightGetAllFightTrainerOperateFlag(void) {
    return _all_fight_trainer_operate_flag;
}

void dbgMenuFightSetMsgKeyWaitFlag(u8 flag) {
    _msg_key_wait_flag = flag;
}

u8 dbgMenuFightGetMsgKeyWaitFlag(void) {
    return _msg_key_wait_flag;
}

void dbgMenuFightSetTuikakoukaFlag(u8 flag) {
    _tuikakouka_flag = flag;
}

u8 dbgMenuFightGetTuikakoukaFlag(void) {
    return _tuikakouka_flag;
}

void dbgMenuFightSetMsgSpeed(u8 speed) {
    u8 value = speed;

    if (value < 1) {
        value = 1;
    }
    if (value > 9) {
        value = 9;
    }
    _msg_speed = value;
}

u8 dbgMenuFightGetMsgSpeed(void) {
    return _msg_speed;
}

s32 dbgMenuFightGetMsgSpeedToFrame(u32 frames) {
    u8 table[10] = { 0x00, 0x0A, 0x19, 0x32, 0x4B, 0x64, 0x7D, 0x96, 0xAF, 0xC8 };
    u8 speed = dbgMenuFightGetMsgSpeed();
    s32 changed;

    if (winMsgCloseCheckFight() == 1) {
        frames = frames * table[speed] / 100;
        if (dbgMenuFightGetMsgKeyWaitFlag() == 1) {
            frames = 0;
            for (;;) {
                changed = GSinputButtonsChanged(1);
                if (GSinputButtonsPressed(1) & changed & 0x100) {
                    break;
                }
                GSthreadSwitch();
            }
        }
    }
    return frames;
}

s32 dbgMenuFightGetFightTrainerAiAddsubValueDataId(u32 id, u8 close) {
    u32 value;
    u32 max;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetFightTrainerAiAddsubValueDataIdSub) == 0) {
        return -1;
    }
    max = *fight_trainer_ai_value_addsub_data_number;
    if (value > max) {
        value = max - 1;
    }
    if (close == 1) {
        menuSubCloseNumberInput();
    }
    return value;
}

static void _dbgMenuFightGetFightTrainerAiAddsubValueDataIdSub(u32 id) {
    u16 a;
    u16 b;
    u16 c;
    u16 d;

    if (id >= *fight_trainer_ai_value_addsub_data_number) {
        d = 0;
        a = 0xEB63;
        b = 0xEB63;
        c = 0xEB63;
    } else {
        a = fightTrainerGetStatus(0, id, 0x40, 0);
        b = fightTrainerGetStatus(0, id, 0x41, 0);
        c = fightTrainerGetStatus(0, id, 0x3F, 0);
        d = fightTrainerGetStatus(0, id, 0x3E, 0);
    }
    if (c == 0) {
        c = 0xEB63;
    }
    if (a == 0) {
        a = 0xEB63;
    }
    if (b == 0) {
        b = 0xEB63;
    }
    msgctrlSetValue(0xD, GSmsgGetGSchar(a));
    msgctrlSetValue(0xE, GSmsgGetGSchar(b));
    msgctrlSetValue(0x4D, GSmsgGetGSchar(c));
    msgctrlSetValue(0x2F, d);
    GSmsgGetGSchar(0xF159);
}

s32 dbgMenuFightGetFightTrainerPokemonPartDataId(u32 id) {
    u32 value;
    u32 max;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetFightTrainerPokemonPartDataIdSub) == 0) {
        return -1;
    }
    max = *fight_trainer_pokemon_part_data_number;
    if (value >= max) {
        value = max - 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetFightTrainerPokemonPartDataIdSub(u32 id) {
    if (id == 0) {
        GSmsgGetGSchar(0xEB63);
        return;
    }
    if (id >= *fight_trainer_pokemon_part_data_number) {
        GSmsgGetGSchar(0xEB63);
        return;
    }
    GSmsgGetGSchar(fightTrainerGetStatus(0, id, 0xB, 0));
}

s32 dbgMenuFightGetWazaDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetWazaDataIdSub) == 0) {
        return -1;
    }
    if (value >= 0x163) {
        value = 0x162;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetWazaDataIdSub(u32 id) {
    if (id == 0) {
        GSmsgGetGSchar(0xEB63);
        return;
    }
    if (id >= 0x163) {
        GSmsgGetGSchar(0xEB63);
        return;
    }
    GSmsgGetGSchar(wazaGetStatus(0, id, 1, 0));
}

u32 dbgMenuFightGetWazaTypeId(u8 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetWazaTypeIdSub) == 0) {
        return -1;
    }
    if (value > 0xD) {
        value = 0xD;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetWazaTypeIdSub(u32 id) {
    if (id == 0) {
        GSmsgGetGSchar(0xEB63);
        return;
    }
    if (id > 0xD) {
        GSmsgGetGSchar(0xEB63);
        return;
    }
    GSmsgGetGSchar(wazaGetWazaTypeIdName(id));
}

u32 dbgMenuFightGetZokuseiDataId(u32 id) {
    u32 value;
    u32 max;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetZokuseiDataIdSub) == 0) {
        return -1;
    }
    max = *zokusei_data_number;
    if (value >= max) {
        value = max - 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetZokuseiDataIdSub(u32 id) {
    if (id == 9) {
        GSmsgGetGSchar(0xEB63);
        return;
    }
    if (id >= *zokusei_data_number) {
        GSmsgGetGSchar(0xEB63);
        return;
    }
    GSmsgGetGSchar(zokuseiBiosGetName(id));
}

u32 dbgMenuFightGetGsinputDevId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetGsinputDevIdSub) == 0) {
        return -1;
    }
    if (value >= 5) {
        value = 4;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetGsinputDevIdSub(s32 id) {
    u32 msg;

    if (id >= 5) {
        msg = 0xEB63;
    } else {
        msg = dbgMenuGetGsinputMsgId(id);
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    GSmsgGetGSchar(msg);
}

s32 dbgMenuFightGetFightTrainerDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetFightTrainerDataIdSub) == 0) {
        return -1;
    }
    if (value > _readEncountDataCnt && value < 0x1388) {
        value = _readEncountDataCnt;
    }
    if (value > 0x138E) {
        value = 0x138E;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetFightTrainerDataIdSub(u32 id) {
    u32 msg;

    if (id >= deckGetTrainerSize()) {
        msg = 0xEB63;
    } else {
        msg = fightTrainerGetStatus(0, id, 3, 0);
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    switch (id) {
    case 0x1388:
        msg = 0xED00;
        break;
    case 0x1389:
        msg = 0xF60A;
        break;
    case 0x138A:
        msg = 0xF60B;
        break;
    case 0x138B:
        msg = 0xF60C;
        break;
    case 0x138C:
        msg = 0xF60D;
        break;
    case 0x138D:
        msg = 0xF60E;
        break;
    case 0x138E:
        msg = 0xF60F;
        break;
    }
    GSmsgGetGSchar(msg);
}

u32 dbgMenuFightGetPokemonEntry(u8 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetPokemonEntrySub) == 0) {
        return -1;
    }
    if (value > 6) {
        value = 6;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetPokemonEntrySub(u32 id) {
    u32 msg = id;

    if (msg > 6) {
        msg = 0xEB63;
    } else {
        switch (msg) {
        case 1:
            msg = 0xF604;
            break;
        case 2:
            msg = 0xF605;
            break;
        case 3:
            msg = 0xF606;
            break;
        case 4:
            msg = 0xF607;
            break;
        case 5:
            msg = 0xF608;
            break;
        case 6:
            msg = 0xF609;
            break;
        }
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    GSmsgGetGSchar(msg);
}

u32 dbgMenuFightGetPokemonFightType(u8 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetPokemonFightTypeSub) == 0) {
        return -1;
    }
    if (value > 2) {
        value = 2;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetPokemonFightTypeSub(u32 id) {
    u32 msg = id;

    if (msg > 2) {
        msg = 0xEB63;
    } else {
        switch (msg) {
        case 1:
            msg = 0xF602;
            break;
        case 2:
            msg = 0xF603;
            break;
        }
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    GSmsgGetGSchar(msg);
}

u32 dbgMenuFightGetFightTypeDataId(u8 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetFightTypeDataIdSub) == 0) {
        return -1;
    }
    if (value > 2) {
        value = 2;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetFightTypeDataIdSub(u32 id) {
    u32 msg = id;

    if (msg > 2) {
        msg = 0xEB63;
    } else {
        switch (msg) {
        case 0:
            msg = 0xF5FF;
            break;
        case 1:
            msg = 0xF600;
            break;
        case 2:
            msg = 0xF601;
            break;
        }
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    GSmsgGetGSchar(msg);
}

u32 dbgMenuFightGetFightKindDataId(u8 id) {
    u32 value;
    u32 max;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetFightKindDataIdSub) == 0) {
        return -1;
    }
    max = *fight_kind_data_number;
    if (value >= max) {
        value = max - 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetFightKindDataIdSub(u32 id) {
    u32 msg;

    if (id >= *fight_kind_data_number) {
        msg = 0xEB63;
    } else {
        msg = fightKindDataBiosGetName(fightKindDataBiosGetPtr(id));
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    GSmsgGetGSchar(msg);
}

u32 dbgMenuFightGetFightFloorDataId(u32 id) {
    u32 value;
    u32 max;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetFightFloorDataIdSub) == 0) {
        return -1;
    }
    max = *fight_floor_data_number;
    if (value >= max) {
        value = max - 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetFightFloorDataIdSub(u32 id) {
    u32 msg;

    if (id >= *fight_floor_data_number) {
        msg = 0xEB63;
    } else {
        msg = fightFloorGetStatus(0, id, 1, 0);
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    GSmsgGetGSchar(msg);
}

u32 dbgMenuFightGetFightDeckDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetFightDeckDataIdSub) == 0) {
        return -1;
    }
    if (value >= deck_group_data_number) {
        value = deck_group_data_number - 1;
    }
    if (value == 0) {
        value = 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetFightDeckDataIdSub(u32 id) {
    u32 msg;

    if (id == 0) {
        msg = 0xEB63;
    } else if (id >= deck_group_data_number) {
        msg = 0xEB63;
    } else {
        msg = deck_group_data[id];
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    GSmsgGetGSchar(msg);
}

u32 dbgMenuFightGetFightEncountDataId(u32 id) {
    u32 value;

    if (menuSubOpenNumberInputID(id, &value, _dbgMenuFightGetFightEncountDataIdSub) == 0) {
        return -1;
    }
    if (value > _readEncountDataCnt) {
        value = _readEncountDataCnt;
    }
    if (value == 0) {
        value = 1;
    }
    menuSubCloseNumberInput();
    return value;
}

static void _dbgMenuFightGetFightEncountDataIdSub(u32 id) {
    s16 close[2];
    s16* msgId;
    u32 msg;

    if (id >= 1 && id <= _readEncountDataCnt) {
        msg = ((u32*)_readEncountDataName)[id - 1];
    } else {
        msg = 0xEB63;
    }
    if (msg == 0) {
        msg = 0xEB63;
    }
    if (id <= _readEncountDataCnt) {
        msgId = getDeckMsgID(((u16*)_readEncountDataID)[id - 1], 1, _readEncountDataID);
        GScharMakeFromSJIS(strbuf, "[");
        GScharMakeFromSJIS(&strbuf[1], (const char*)msgId);
        GScharMakeFromSJIS(close, "]");
        GScharCat(strbuf, close, 0);
    } else {
        strbuf[0] = 0;
    }
    GScharCat(strbuf, (s16*)GSmsgGetGSchar(msg), strbuf);
}
