#include <game/menuSubLayout.hpp>

class Pokemon {
public:
    u16 getPokemonDataId() const;
};

struct Hero {
    u8 getHeroStyle() const;
};

struct ItemCraneMemo {
    u16 item;
    u16 index;
    u32 msg;
};

struct MenuPocketWorkEntry {
    u16 item;
    u16 unk2;
    u32 unk4;
};

struct MenuPocketWork {
    MenuPocketWorkEntry entry[8];
    s32 count;
};

struct MENU_LVUP_STATUS {
    s8 flag;
    s8 padding1;
    s16 hp;
    s16 attack;
    s16 defense;
    s16 spAttack;
    s16 spDefense;
    s16 speed;
    s16 reservedE;
};

struct LogEntry {
    s32 key;
    s16 a;
    s16 b;
};

struct ITEMUSE2POKEMON_LOG1 {
    LogEntry e[32];
};

struct ItemParam {
    s32 v[2];
};

extern "C" {
u32 GSflagGet(s32);
f32 GSgfxVideoGetLastRenderTime(void);
s32 GSmsgGetGSchar(u32);
void GSsndPlayNow(u32);
void GSthreadSwitch(void);
void fadeCheck(s32);
void fadeSet(s32, f32);
void* getPlaceMsg__14underTakerBiosFv(void*);
void itemParamConvertOrigFormat(void*, void*);
s32 itemParamGetRecoverType(void*);
void menuOffScreenSetPriority(s32);
void menuPocket2AddItemScript(u32, s32);
void getLogMsgBattleDummy(void);
void menuPocket2ClosePokemonMenu(s32);
s32 menuPocket2OpenPokemonMenu(u32, s32);
void fightEncountDataBiosDummy(void);
void menuPocket2GetTemochiPokemon(s32, Pokemon**, u32*);
s32 menuPocket2GetCurrentTemochiPokemonSlotID(void);
void menuOffScreenSetDisp(s32);
void GSsndPlayVolume(s32, s32, s32, s32);
void GSinputMotorStart(s32, s32, s32, s32, s32);
s32 GSsndGetStatus(u16);
s32 gamedatasaveGetStatus(s32, s32);
void pokemonInitJoutaiDataId(Pokemon*, s32);
f32 pokemonGetDp(Pokemon*);
void pokemonAddDpFormPokemonDpFilterId(Pokemon*, u16, s32);
void reliveHallInfomationPokemonDP0(Pokemon*);
void soundOpenPlayME(s32, s32, s32);
u8 pokemonBiosGetLevel(Pokemon*);
void winMsgOpenLevelUpFiledStatus(MENU_LVUP_STATUS*, s32);
void winMsgCloseLevelUpStatus(s32);
u16 pokemonGetOboeWazaDataId(Pokemon*, u8, u8*);
s8 pokemonSearchWazaDataId(Pokemon*, u16);
u32 fightFloor_GetStockPokemonNum(s32);
s8 pcboxGetNbPokemonBox(void);
s8 pcboxGetPokemonBoxNbEmptySlot(s32, s8);
void menuPocket2GetHero(Hero**, s32*);
void fightFloorGetNowPtr(void);
u32 fightFloor_GetFightKind(void);
u8 fightTrainerIsSelectedItemBall(s32);
void GSmsgMakeGScharStr(unsigned short*, s32, s32);
s32 pokemonGetStatus(Pokemon*, s32, s32, s32);
void itemDataBiosGetItemEffectParam(void);
void* itemParamGetPtr(void);
u8 itemParamGetPPSelectFlag(void);
s32 menuPokemonOpenWazaLight(s8);
void menuPokemonCloseWazaLight(void);
u8 pokemonCheckValid(Pokemon*);
u16 itemDataBiosGetWazaIDByWazaMachineNo(u8);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon*, u16);
u8 pokemonDataBiosGetWazaMcn(u32, u16);
s32 evolutionWazaLearn(Pokemon*, u16, u8*, s32, s8 (*)(Pokemon*, u16, long), void*);
s32 itemDataBiosGetPtr(u16);
u32 itemDataBiosGetWazaMachineNo(void);
u8 itemDataBiosGetHidenMachineNo(s32);
s16 itemUse2Pokemon(ITEMUSE2POKEMON_LOG1*, Pokemon*, u32, u16, u8);
void menuPokemonUpdate(void);
void pokemonEvolutionAll(Pokemon*, u16, u16, void*, s32, s32, s32, s32);
u16 pokemonEvolutionCheck(Pokemon*, s32, u16, u16*, void*);
u8 pokemonIsDarkPokemon(Pokemon*);
u8 pokemonIsJoutaiDataId(Pokemon*, s32);
s32 pokemonBiosGetNicknamePtr(Pokemon*);
s32 menuPokemonStatusOpenWazaMachine(Pokemon*, u16);
void menuScriptUsohachi2(void);
s32 menuSubOpenYesNo(s32, s32, s32, s32);
void msgctrlSetValue(s32, s32);
void pokemonBiosGetPokemonDataId(Pokemon*);
u32 pokemonDataBiosGetPtr(void);
u32 pokemonDataBiosGetVoice(void);
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon*, s32, s32);
s32 pokemonGetSoubiItemSoubiDataId(Pokemon*);
void pokemonWazaCreate(Pokemon*, u32, u16);
s8 winMsgCheck(void);
void winMsgClose(s32);
void winMsgOpen(s32, s32, s32, s32);
tagWINDOW_WORK* windowSearchID(s32);
}

extern "C" {
extern MenuPocketWork menuPocketWork;
extern s32* undertakerdata;
}

extern "C" ItemCraneMemo item_crane_memo[5];
static ItemParam origRamSeedParam_field = {{0, 0}};
static ItemParam origRamSeedParam_battle = {{0, 0}};
extern "C" u32 item_crane_memo_number;

static void getLogMsgField(unsigned short*, int, ITEMUSE2POKEMON_LOG1*, short, Pokemon*);
static void getPokemonLvupStatus(MENU_LVUP_STATUS*, Pokemon*);
static void getDifLvupStatus(MENU_LVUP_STATUS*, MENU_LVUP_STATUS*, MENU_LVUP_STATUS*);
static u32 getPokemonData(Pokemon* pokemon);
static u16 playPokemonVoice(Pokemon* pokemon);
static void waitTime(float seconds);
static s32 dispMsgYesNo(unsigned long msg);
static void dispMsg(unsigned long msg);
static s8 cbForgetWazaSelect(Pokemon* pokemon, unsigned short move, long slot);
static void playRecoverSE(unsigned long item);
static void wazaLean(Pokemon* pokemon, unsigned short move, unsigned char level);
static s32 wazaMachineProc(Pokemon* pokemon, int machine);
static void getLogMsgBattle(unsigned short*, int, ITEMUSE2POKEMON_LOG1*, short, Pokemon*);

extern "C" {
s32 menuUseItemDummy(u32 item, s32* out);
s32 menuUseItemPPRecovery(u32 item, s32* out);
s32 menuUseItemRecovery(u32 item, s32* out);
s32 menuUseItemStatusUp(u32 item, s32* out);
s32 menuUseItemAlldeathRcv(u32 item, s32* out);
s32 menuUseItemListLVUp(u32 item, s32* out);
s32 menuUseItemScriptCologn(u32 item, s32 slot);
s32 menuUseItemWPointUp(u32 item, s32* out);
}

static u32 getPokemonData(Pokemon* pokemon) {
    if (pokemon == 0) {
        return 0;
    }
    if (!pokemonCheckValid(pokemon)) {
        return 0;
    }
    pokemonBiosGetPokemonDataId(pokemon);
    return pokemonDataBiosGetPtr();
}

static u16 playPokemonVoice(Pokemon* pokemon) {
    u16 voice;
    if (getPokemonData(pokemon) == 0) {
        return 0;
    }
    voice = pokemonDataBiosGetVoice();
    GSsndPlayNow(voice);
    return voice;
}

static void waitTime(float seconds) {
    s32 limit = (s32)(60.0f * seconds);
    s32 elapsed = 0;
    while (elapsed < limit) {
        GSthreadSwitch();
        elapsed = (s32)((f32)elapsed + GSgfxVideoGetLastRenderTime());
    }
}

static s32 dispMsgYesNo(unsigned long msg) {
    s8 answer;
    winMsgOpen(2, msg, 1, 0);
    answer = menuSubOpenYesNo(0, -1, -1, 0);
    winMsgClose(1);
    switch (answer) {
    case 0:
        return 0;
    case 1:
        return 1;
    default:
        return 2;
    }
}

static void dispMsg(unsigned long msg) {
    switch (msg) {
    case 0xC368:
    case 0xC369:
    case 0xC371:
    case 0xC372:
        GSsndPlayNow(0x13);
        break;
    }
    if (windowSearchID(0x4C) == 0) {
        winMsgOpen(2, msg, 1, 0);
    } else {
        winMsgOpen(2, msg, 0, 0);
        do {
            menuOffScreenSetPriority(0);
            GSthreadSwitch();
        } while (winMsgCheck() != 0);
    }
    winMsgClose(1);
}

static void playRecoverSE(unsigned long item) {
    s32 index;
    u16 local[5] = {0x27,0x28,0x29,0x2A,0x2B};
    for(index=0;index<5;index++){if(item==local[index])break;}
    GSsndPlayNow(index<5?0x20:0x1F);
}

static void wazaLean(Pokemon* pokemon, unsigned short move, unsigned char slot) {
    s32 soubi;
    pokemonWazaCreate(pokemon, slot, move);
    soubi = pokemonGetSoubiItemSoubiDataId(pokemon);
    pokemonGetFriendFormPokemonFriendFilterId(pokemon, soubi, 4);
}

static s8 cbForgetWazaSelect(Pokemon* pokemon, unsigned short move, long slot) {
    s32 result;
    fadeSet(3, 0.5f);
    fadeCheck(1);
    result = menuPokemonStatusOpenWazaMachine(pokemon, move);
    if (result >= 4) {
        result = -1;
    }
    fadeSet(2, 0.5f);
    fadeCheck(1);
    return result;
}

static s32 wazaMachineProc(Pokemon* pokemon, int machine) {
    u8 slot;
    u16 moveCopy;
    s32 i;
    s32 learned;
    u16 move;
    menuOffScreenSetPriority(0);
    if (pokemonIsDarkPokemon(pokemon)) {
        dispMsg(0xC371);
        return 0;
    }
    move = itemDataBiosGetWazaIDByWazaMachineNo(machine);
    moveCopy = move;
    i = 0;
    for (;;) {
        if (moveCopy == pokemonBiosGetPokemonWazaDataId(pokemon, i)) {
            break;
        }
        i++;
        if (i >= 4) {
            break;
        }
    }
    if (i < 4) {
        s32 nick = pokemonBiosGetNicknamePtr(pokemon);
        msgctrlSetValue(0x32, nick);
        msgctrlSetValue(0x39, (u16)move);
        dispMsg(0xC368);
        return 0;
    }
    pokemonBiosGetPokemonDataId(pokemon);
    if (pokemonDataBiosGetWazaMcn(pokemonDataBiosGetPtr(), machine) == 0) {
        msgctrlSetValue(0x32, pokemonBiosGetNicknamePtr(pokemon));
        msgctrlSetValue(0x39, (u16)move);
        dispMsg(0xC369);
        return 0;
    }
    learned = evolutionWazaLearn(pokemon, move, &slot, 1, cbForgetWazaSelect, 0);
    if (learned != 0) {
        wazaLean(pokemon, move, slot);
    }
    return learned;
}

static void getLogMsgBattle(unsigned short* buf, int len, ITEMUSE2POKEMON_LOG1* log, short count, Pokemon* pokemon) {
    s32 table[14] = {7, 0xC362, 5, 0xC363, 6, 0xC364, 3, 0xC365, 4, 0xC366, 1, 0xC370, 2, 0xC36F};
    s16 a;
    s16 b;
    s32 msg;
    LogEntry* lp;
    s32* tp;
    s32 j;
    s32 i;
    s32 key;
    if (count <= 0) {
        GSmsgMakeGScharStr(buf, len + 1, 0xC374);
        return;
    }
    for (i = 0, tp = table; i < 7; tp += 2, i++) {
        key = tp[0];
        lp = log->e;
        for (j = 0; j < count; lp++, j++) {
            if (key == lp->key) {
                break;
            }
        }
        if (j < count) {
            break;
        }
    }
    if (i >= 7) {
        GSmsgMakeGScharStr(buf, len + 1, 0xC374);
        return;
    }
    lp = &log->e[j];
    msg = table[i * 2 + 1];
    a = lp->a;
    b = lp->b;
    {
        s32 nick = pokemonBiosGetNicknamePtr(pokemon);
        msgctrlSetValue(0x32, nick);
    }
    msgctrlSetValue(0x2F, a);
    msgctrlSetValue(0x30, b);
    GSmsgMakeGScharStr(buf, len + 1, msg);
}

static void getLogMsgField(unsigned short* buf, int len, ITEMUSE2POKEMON_LOG1* log, short count, Pokemon* pokemon) {
    struct FieldMsg {
        s32 key;
        s32 msg;
        s32 group;
    };
    FieldMsg table[21] = {
        {9, 0xC353, 0},
        {10, 0xC353, 0},
        {11, 0xC354, 1},
        {12, 0xC354, 1},
        {13, 0xC354, 1},
        {14, 0xC355, 2},
        {15, 0xC356, 3},
        {16, 0xC357, 4},
        {17, 0xC381, 5},
        {0, 0xC358, 6},
        {22, 0xC352, -1},
        {21, 0xC351, 7},
        {20, 0xC35A, -1},
        {19, 0xC35B, -1},
        {28, 0xC35C, -1},
        {27, 0xC35D, -1},
        {26, 0xC35E, -1},
        {25, 0xC35F, -1},
        {18, 0xC360, -1},
        {29, 0xC360, -1},
        {23, 0xC361, -1},
    };
    s16 a;
    s16 b;
    s32 msg;
    s32 group;
    FieldMsg* tp;
    LogEntry* lp;
    s32 i;
    s32 j;
    s32 key;
    s32 i2;
    s32 j2;
    FieldMsg* tp2;
    LogEntry* lp2;
    if (count <= 0) {
        GSmsgMakeGScharStr(buf, len + 1, 0xC374);
        return;
    }
    for (i = 0, tp = table; i < 21; tp++, i++) {
        key = tp->key;
        lp = log->e;
        for (j = 0; j < count; lp++, j++) {
            if (key == lp->key) {
                break;
            }
        }
        if (j < count) {
            break;
        }
    }
    if (i >= 21) {
        GSmsgMakeGScharStr(buf, len + 1, 0xC374);
        return;
    }
    group = table[i].group;
    lp = &log->e[j];
    msg = table[i].msg;
    a = lp->a;
    b = lp->b;
    if (group >= 0) {
        i2 = i + 1;
        tp2 = &table[i2];
        for (; i2 < 21; tp2++, i2++) {
            if (tp2->group >= 0 && group != tp2->group) {
                lp2 = log->e;
                for (j2 = 0; j2 < count; lp2++, j2++) {
                    if (tp2->key == lp2->key) {
                        break;
                    }
                }
                if (j2 < count) {
                    break;
                }
            }
        }
        if (i2 < 21) {
            msg = 0xC359;
        }
    }
    {
        s32 nick = pokemonBiosGetNicknamePtr(pokemon);
        msgctrlSetValue(0x32, nick);
    }
    msgctrlSetValue(0x2F, a);
    msgctrlSetValue(0x30, b);
    GSmsgMakeGScharStr(buf, len + 1, msg);
}

static void getPokemonLvupStatus(MENU_LVUP_STATUS* status, Pokemon* pokemon) {
    status->hp = pokemonGetStatus(pokemon, 0, 0x87, 0);
    status->attack = pokemonGetStatus(pokemon, 0, 0x88, 0);
    status->defense = pokemonGetStatus(pokemon, 0, 0x89, 0);
    status->spDefense = pokemonGetStatus(pokemon, 0, 0x8A, 0);
    status->speed = pokemonGetStatus(pokemon, 0, 0x8B, 0);
    status->spAttack = pokemonGetStatus(pokemon, 0, 0x8C, 0);
}

static void getDifLvupStatus(MENU_LVUP_STATUS* out, MENU_LVUP_STATUS* a, MENU_LVUP_STATUS* b) {
    out->hp = a->hp - b->hp;
    out->attack = a->attack - b->attack;
    out->defense = a->defense - b->defense;
    out->spDefense = a->spDefense - b->spDefense;
    out->speed = a->speed - b->speed;
    out->spAttack = a->spAttack - b->spAttack;
}

extern "C" {

s32 menuUseItemEventUsohachiPhoto(u32 item, s32* out) {
    *out = 0;
    menuScriptUsohachi2();
    return 2;
}

s32 menuUseItemEventMirraboradar(u32 item, s32* out) {
    u32 msg;
    u16 stage;
    msg = 1;
    *out = 0;
    if (GSflagGet(0x8ED) != 0) {
        msg = 0x3C31;
    } else if (GSflagGet(0x8EE) != 0) {
        msg = 0x3C32;
    } else {
        stage = GSflagGet(undertakerdata[5]);
        if (stage <= 2) {
            dispMsg(0x3C1C);
        } else if (stage <= 5) {
            dispMsg(0x3C1D);
        } else if (stage <= 8) {
            dispMsg(0x3C1E);
        } else {
            u8 buf[4];
            msg = (u32)getPlaceMsg__14underTakerBiosFv(buf);
        }
    }
    if (msg != 1) {
        s32 chr = GSmsgGetGSchar(msg);
        msgctrlSetValue(0x4D, chr);
        dispMsg(0x3C1F);
    }
    return 2;
}

s32 menuUseItemEventCraneMemo(u32 item, s32* out) {
    ItemCraneMemo* memo;
    s32 i;
    *out = 0;
    for (i = 0, memo = item_crane_memo; i < item_crane_memo_number; memo++, i++) {
        if (memo->item == item) {
            dispMsg(memo->msg);
            return 2;
        }
    }
    dispMsg(0xC373);
    return 1;
}

s32 menuUseItemEventNotConsum(u32 item, s32* out) {
    MenuPocketWorkEntry* entry;
    s32 i;
    *out = 0;
    entry = menuPocketWork.entry;
    for (i = 0; i < menuPocketWork.count; i++, entry++) {
        if (item == entry->item) {
            return 2;
        }
    }
    dispMsg(0xC373);
    return 1;
}

s32 menuUseItemBattleNazonomi(u32 item, s32* out) {
    ItemParam param;
    itemParamConvertOrigFormat(&param, &origRamSeedParam_battle);
    switch (itemParamGetRecoverType(&param)) {
    case 0:
        return menuUseItemStatusUp(item, out);
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        return menuUseItemRecovery(item, out);
    case 21:
        return menuUseItemPPRecovery(item, out);
    default:
        return menuUseItemDummy(item, out);
    }
}

s32 menuUseItemFieldNazonomi(u32 item, s32* out) {
    ItemParam param;
    itemParamConvertOrigFormat(&param, &origRamSeedParam_field);
    switch (itemParamGetRecoverType(&param)) {
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
        return menuUseItemRecovery(item, out);
    case 1:
        return menuUseItemAlldeathRcv(item, out);
    case 2:
        return menuUseItemListLVUp(item, out);
    case 19:
    case 20:
        return menuUseItemWPointUp(item, out);
    case 21:
        return menuUseItemPPRecovery(item, out);
    default:
        return menuUseItemDummy(item, out);
    }
}

s32 menuUseItemStatusUp(u32 item, s32* out) {
    ITEMUSE2POKEMON_LOG1 log;
    u16 msg[0x42];
    Pokemon* pokemon;
    u32 slot;
    s16 count;
    menuPocket2GetTemochiPokemon(menuPocket2GetCurrentTemochiPokemonSlotID(), &pokemon, &slot);
    if (pokemonIsJoutaiDataId(pokemon, 0x3E)) {
        s32 nick = pokemonBiosGetNicknamePtr(pokemon);
        msgctrlSetValue(0x32, nick);
        dispMsg(0xC372);
        return 1;
    }
    count = itemUse2Pokemon(&log, pokemon, slot, item, 0);
    if (count > 0) {
        playRecoverSE(item);
        menuPokemonUpdate();
    }
    getLogMsgBattle(msg, 0x40, &log, count, pokemon);
    msgctrlSetValue(0x4D, (s32)msg);
    dispMsg(0x4289);
    if (count > 0) {
        *out = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemCologn(u32 item, s32* out) {
    Pokemon* pokemon;
    u32 slot;
    s32 menu = menuPocket2OpenPokemonMenu(item, 1);
    if (menu >= 0) {
        menuPocket2GetTemochiPokemon(menu, &pokemon, &slot);
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(menu);
    if (menu >= 0) {
        menuPocket2AddItemScript(item, 0x05960011);
        *out = 1;
        return 2;
    }
    return 1;
}

s32 menuUseItemEvolution(u32 item, s32* out) {
    ITEMUSE2POKEMON_LOG1 log;
    Pokemon* pokemon;
    u32 slot;
    u8 evolveWork[4];
    u16 evolveId;
    s16 count = -1;
    s32 menu = menuPocket2OpenPokemonMenu(item, 1);
    u16 target;
    if (menu >= 0) {
        menuPocket2GetTemochiPokemon(menu, &pokemon, &slot);
        if (pokemonIsDarkPokemon(pokemon) == 0) {
            count = itemUse2Pokemon(&log, pokemon, slot, item, 0);
            if (count <= 0) {
                dispMsg(0xC374);
            }
        } else {
            dispMsg(0xC371);
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(menu);
    if (menu >= 0 && count > 0) {
        target = pokemonEvolutionCheck(pokemon, 1, item, &evolveId, evolveWork);
        fadeSet(3, 0.5f);
        fadeCheck(1);
        menuOffScreenSetDisp(0);
        pokemonEvolutionAll(pokemon, target, evolveId, evolveWork, 0, 1, 0, 0);
        menuOffScreenSetDisp(1);
        fadeSet(2, 0.5f);
        fadeCheck(1);
        *out = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemSkill(u32 item, s32* out) {
    Pokemon* pokemon;
    u32 slot;
    s32 itemData;
    u32 move;
    u8 machine;
    u8 hiden;
    u32 msg;
    s32 menu;
    s32 answer;
    s32 learned;
    itemData = itemDataBiosGetPtr(item);
    machine = itemDataBiosGetWazaMachineNo();
    move = itemDataBiosGetWazaIDByWazaMachineNo(machine);
    GSsndPlayNow(0x23);
    hiden = itemDataBiosGetHidenMachineNo(itemData);
    if (hiden != 0xFF) {
        msg = 0xC376;
    } else {
        msg = 0xC375;
    }
    msgctrlSetValue(0x39, move);
    dispMsg(msg);
    answer = dispMsgYesNo(0xC377);
    if (answer == 1 || answer == 2) {
        return 1;
    }
    menu = menuPocket2OpenPokemonMenu(item, 1);
    if (menu >= 0) {
        menuPocket2GetTemochiPokemon(menu, &pokemon, &slot);
        learned = wazaMachineProc(pokemon, machine);
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(menu);
    if (menu >= 0 && learned != 0) {
        if (hiden != 0xFF) {
            *out = 0;
        } else {
            *out = 1;
        }
        return 0;
    }
    return 1;
}

s32 menuUseItemRecovery(u32 item, s32* out) {
    ITEMUSE2POKEMON_LOG1 log;
    u16 msg[0x42];
    Pokemon* pokemon;
    u32 slot;
    s32 menu;
    s16 count;
    menu = menuPocket2OpenPokemonMenu(item, 1);
    if (menu >= 0) {
        menuPocket2GetTemochiPokemon(menu, &pokemon, &slot);
        if (pokemonIsJoutaiDataId(pokemon, 0x3E) == 0) {
            count = itemUse2Pokemon(&log, pokemon, slot, item, 0);
            if (count > 0) {
                playRecoverSE(item);
                menuPokemonUpdate();
            }
            getLogMsgField(msg, 0x40, &log, count, pokemon);
            msgctrlSetValue(0x4D, (s32)msg);
            dispMsg(0x4289);
        } else {
            s32 nick = pokemonBiosGetNicknamePtr(pokemon);
            msgctrlSetValue(0x32, nick);
            dispMsg(0xC372);
            count = 0;
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(menu);
    if (menu >= 0 && count > 0) {
        switch ((s32)item) {
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
            *out = 0;
            break;
        default:
            *out = 1;
            break;
        }
        return 0;
    }
    return 1;
}

s32 menuUseItemAlldeathRcv(u32 item, s32* out) {
    ITEMUSE2POKEMON_LOG1 log;
    u16 msg[0x42];
    Pokemon* pokemon;
    u32 slot;
    s32 index;
    u16 total;
    s16 count;
    s32 result;
    total = 0;
    menuPocket2OpenPokemonMenu(item, 0);
    for (index = 0; index < 6; index++) {
        menuPocket2GetTemochiPokemon(index, &pokemon, &slot);
        if (pokemonCheckValid(pokemon) != 0 && pokemonGetStatus(pokemon, 0, 0x83, 0) <= 0 && pokemonIsJoutaiDataId(pokemon, 0x3E) == 0) {
            count = itemUse2Pokemon(&log, pokemon, slot, item, 0);
            if (count > 0) {
                playRecoverSE(item);
                menuPokemonUpdate();
                getLogMsgField(msg, 0x40, &log, count, pokemon);
                msgctrlSetValue(0x4D, (s32)msg);
                dispMsg(0x4289);
                total += count;
            }
        }
    }
    if (total == 0) {
        dispMsg(0xC374);
        result = -1;
    } else {
        result = 1;
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(-1);
    if (result < 0) {
        return 1;
    }
    *out = 1;
    return 0;
}

s32 menuUseItemPPRecovery(u32 item, s32* out) {
    ITEMUSE2POKEMON_LOG1 log;
    u16 msg[0x42];
    Pokemon* pokemon;
    u32 slot;
    s32 menu;
    s16 count;
    s32 selected;
    s32 joutai;
    joutai = 0;
    for (;;) {
        menu = menuPocket2OpenPokemonMenu(item, 1);
        if (menu >= 0) {
            menuPocket2GetTemochiPokemon(menu, &pokemon, &slot);
            if (pokemonIsJoutaiDataId(pokemon, 0x3E) != 0) {
                joutai = 1;
            } else {
                itemDataBiosGetPtr(item);
                itemDataBiosGetItemEffectParam();
                itemParamGetPtr();
                if (itemParamGetPPSelectFlag() != 0) {
                    selected = menuPokemonOpenWazaLight(menu);
                    menuPokemonCloseWazaLight();
                } else {
                    selected = 0;
                }
                if (selected < 0) {
                    continue;
                }
            }
        }
        break;
    }
    if (menu >= 0) {
        if (joutai != 0) {
            s32 nick = pokemonBiosGetNicknamePtr(pokemon);
            msgctrlSetValue(0x32, nick);
            dispMsg(0xC372);
            count = 0;
        } else {
            count = itemUse2Pokemon(&log, pokemon, slot, item, selected);
            if (count > 0) {
                playRecoverSE(item);
                menuPokemonUpdate();
            }
            getLogMsgField(msg, 0x40, &log, count, pokemon);
            msgctrlSetValue(0x4D, (s32)msg);
            dispMsg(0x4289);
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(menu);
    if (menu >= 0 && count > 0) {
        *out = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemBattleBall(u32 item, s32* out) {
    s32 total;
    u8 stock;
    s32 i;
    Hero* hero;
    s32 ball;
    Pokemon* pokemon;
    u32 slot;
    s32 box;
    s8 boxes;
    u8 kind;
    total = 0;
    stock = fightFloor_GetStockPokemonNum(0);
    i = 0;
    do {
        menuPocket2GetTemochiPokemon(i, &pokemon, &slot);
        if (pokemonCheckValid(pokemon) == 0) {
            total++;
        }
        i++;
    } while (i < 6);
    boxes = pcboxGetNbPokemonBox();
    box = 0;
    while (box < boxes) {
        s8 empty = pcboxGetPokemonBoxNbEmptySlot(0, box);
        box++;
        total += empty;
    }
    if (total < stock + 1) {
        dispMsg(0x4F8B);
        return 1;
    }
    menuPocket2GetHero(&hero, &ball);
    fightFloorGetNowPtr();
    kind = fightFloor_GetFightKind();
    if (hero->getHeroStyle() != 2 && kind != 0xC && kind != 0xD) {
        dispMsg(0x5000);
        return 1;
    }
    if (fightTrainerIsSelectedItemBall(ball) != 0) {
        dispMsg(0xC378);
        return 1;
    }
    *out = 0;
    return 0;
}

s32 menuUseItemListLVUp(u32 item, s32* out) {
    ITEMUSE2POKEMON_LOG1 log;
    MENU_LVUP_STATUS diff;
    MENU_LVUP_STATUS before;
    MENU_LVUP_STATUS after;
    Pokemon* pokemon;
    u32 slot;
    u8 evolveWork[4];
    u16 evolveId;
    u8 learnSlot;
    u8 oboeIndex;
    s32 menu;
    s16 count;
    u16 evolved;
    u8 level;
    u16 move;
    oboeIndex = 0;
    menu = menuPocket2OpenPokemonMenu(item, 1);
    if (menu >= 0) {
        menuPocket2GetTemochiPokemon(menu, &pokemon, &slot);
        if (pokemonIsDarkPokemon(pokemon) == 0) {
            getPokemonLvupStatus(&before, pokemon);
            count = itemUse2Pokemon(&log, pokemon, slot, item, 0);
            if (count > 0) {
                menuPokemonUpdate();
            } else {
                count = 0;
            }
        } else {
            count = -1;
        }
        switch (count) {
        case 0:
            dispMsg(0xC374);
            break;
        case -1:
            dispMsg(0xC371);
            break;
        default:
            menuOffScreenSetPriority(0);
            soundOpenPlayME(0x3C7, 0, 0xFF);
            {
                s32 nick = pokemonBiosGetNicknamePtr(pokemon);
                msgctrlSetValue(0x32, nick);
            }
            level=pokemonBiosGetLevel(pokemon);
            msgctrlSetValue(0x2F,(u8)level);
            dispMsg(0xC367);
            getPokemonLvupStatus(&after, pokemon);
            getDifLvupStatus(&diff, &after, &before);
            diff.flag = 1;
            winMsgOpenLevelUpFiledStatus(&diff, 1);
            after.flag = 0;
            winMsgOpenLevelUpFiledStatus(&after, 1);
            winMsgCloseLevelUpStatus(1);
            level = pokemonBiosGetLevel(pokemon);
            oboeIndex = 0;
            while ((u16)(move = pokemonGetOboeWazaDataId(pokemon, level, &oboeIndex)) != 0) {
                if (pokemonSearchWazaDataId(pokemon, move) == -1 && evolutionWazaLearn(pokemon, move, &learnSlot, 1, cbForgetWazaSelect, 0) != 0) {
                    pokemonWazaCreate(pokemon, learnSlot, move);
                }
                oboeIndex++;
            }
            evolved = pokemonEvolutionCheck(pokemon, 0, 0, &evolveId, evolveWork);
            break;
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(menu);
    if (menu >= 0 && count > 0) {
        if (evolved != 0) {
            fadeSet(3, 0.5f);
            fadeCheck(1);
            menuOffScreenSetDisp(0);
            pokemonEvolutionAll(pokemon, evolved, evolveId, evolveWork, 0, 1, 1, 0);
            menuOffScreenSetDisp(1);
            fadeSet(2, 0.5f);
            fadeCheck(1);
        }
        *out = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemWPointUp(u32 item, s32* out) {
    ITEMUSE2POKEMON_LOG1 log;
    u16 msg[0x42];
    Pokemon* pokemon;
    u32 slot;
    s32 menu;
    s16 count;
    s32 selected;
    u32 flag;
    flag = 0;
    for (;;) {
        menu = menuPocket2OpenPokemonMenu(item, 1);
        if (menu >= 0) {
            menuPocket2GetTemochiPokemon(menu, &pokemon, &slot);
            if (pokemonIsJoutaiDataId(pokemon, 0x3E) != 0) {
                flag = 1;
            } else {
                selected = menuPokemonOpenWazaLight(menu);
                menuPokemonCloseWazaLight();
                if (selected < 0) {
                    continue;
                }
            }
        }
        break;
    }
    if (menu >= 0) {
        if (flag != 0) {
            s32 nick = pokemonBiosGetNicknamePtr(pokemon);
            msgctrlSetValue(0x32, nick);
            dispMsg(0xC372);
            count = 0;
        } else {
            flag = pokemonBiosGetPokemonWazaDataId(pokemon, selected);
            if ((u16)flag > 0x163 && (u16)flag < 0x176) {
                dispMsg(0xC374);
                count = 0;
            } else {
                count = itemUse2Pokemon(&log, pokemon, slot, item, selected);
                if (count > 0) {
                    playRecoverSE(item);
                    menuPokemonUpdate();
                }
                msgctrlSetValue(0x4D, (s32)msg);
                msgctrlSetValue(0x39, (u16)flag);
                getLogMsgField(msg, 0x40, &log, count, pokemon);
                dispMsg(0x4289);
            }
        }
    }
    menuOffScreenSetPriority(0);
    menuPocket2ClosePokemonMenu(menu);
    if (menu >= 0 && count > 0) {
        *out = 1;
        return 0;
    }
    return 1;
}

s32 menuUseItemScriptCologn(u32 item, s32 slot) {
    struct CologneMsg {
        u16 item;
        u16 reserved;
        s32 first;
        s32 second;
    };
    CologneMsg table[3] = {
        {0x201, 0, 0xC3B6, 0xC3B8},
        {0x202, 0, 0xC3BC, 0xC3B9},
        {0x203, 0, 0xC3BD, 0xC3BA},
    };
    Pokemon* pokemon;
    u32 slotOut;
    s32 index;
    s32 offset;
    s32 i;
    u16 voice;
    u16 id;
    f32 remaining;
    menuPocket2GetTemochiPokemon(slot, &pokemon, &slotOut);
    if (pokemonCheckValid(pokemon) == 0) {
        return 1;
    }
    for(index=0;index<3;index++){if((u16)item==table[index].item)break;}
    if (index >= 3) {
        return 1;
    }
    {
        s32 nick = pokemonBiosGetNicknamePtr(pokemon);
        msgctrlSetValue(0x32, nick);
    }
    msgctrlSetValue(0x2D, item);
    offset = index * 12;
    dispMsg(*(s32*)((u8*)&table[0].first + offset));
    GSsndPlayVolume(0x444, 0, 0xFF, 0);
    if (gamedatasaveGetStatus(0, 9) == 0) {
        i = 0;
        do {
            GSinputMotorStart(1, 0, 0xFF, 0x15, 0);
            waitTime(1.0f);
            i++;
        } while (i < 2);
        GSinputMotorStart(1, 0, 0xFF, 0x30, 0);
        waitTime(1.6f);
    }
    voice = playPokemonVoice(pokemon);
    while (GSsndGetStatus(voice) == 2) {
        GSthreadSwitch();
    }
    msgctrlSetValue(0x32, pokemonBiosGetNicknamePtr(pokemon));
    dispMsg(0xC3B7);
    if (pokemonIsJoutaiDataId(pokemon, 0x3E)) {
        pokemonInitJoutaiDataId(pokemon, 0x3E);
        dispMsg(0xC3BE);
    }
    if (pokemonGetDp(pokemon) > 0.0f && pokemon->getPokemonDataId() != 0xF9) {
        pokemonAddDpFormPokemonDpFilterId(pokemon, item, 4);
        msgctrlSetValue(0x32, pokemonBiosGetNicknamePtr(pokemon));
        dispMsg(*(s32*)((u8*)&table[0].second + offset));
        remaining=pokemonGetDp(pokemon);
        if (!remaining) {
            reliveHallInfomationPokemonDP0(pokemon);
        }
    }
    return 1;
}

s32 menuUseItemNoPokecolo(u32 item, s32* out) {
    dispMsg(0xC380);
    return 1;
}

s32 menuUseItemNoEffects(u32 item, s32* out) {
    dispMsg(0xC374);
    return 1;
}

s32 menuUseItemDummy(u32 item, s32* out) {
    dispMsg(0xC373);
    return 1;
}

}
