/* Debug menu entries for testing menus, PDA, memo, esaba and Shadow Pokemon state. */
#include <global.h>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

struct tagWINDOW_WORK;

typedef struct DbgMenuKeyInfo {
    u8 unk0[6];
    u16 trigger;
} DbgMenuKeyInfo;

typedef struct DbgMenuWindow {
    u8 unk0[4];
    s32 id;
    u8 unk8[0x60];
    void* data;
    u8 unk6C[0x32];
    s16 cursor;
} DbgMenuWindow;

typedef struct DbgWorldMapData {
    u16 select;
    s16 mode;
    u16 count;
} DbgWorldMapData;

typedef struct WorldMapXDData {
    u16 unk0;
    u16 unk2;
    u32 flag;
    u8 unk8[0x1C];
} WorldMapXDData;

typedef struct DbgMenuPair {
    s32 menu;
    s32 value;
} DbgMenuPair;

enum D2PRESENT_MODE { D2PRESENT_MODE_0 };

extern "C" {
s32 GSflagGet(s32);
void GSflagOff(s32);
void GSflagOn(s32);
void GSflagSet(s32, s32);
u8 GSflagTest(s32);
s32 GSfloorGetCurrentFloorGroupID(void);
void GSfloorPush(s32);
s32 GSthreadCreate(s32, s32, s32, s32, s32, void (*)(void));
void GSthreadSetArgs(s32, s32, ...);
void d2presentOpen(D2PRESENT_MODE);
void darkPokemonBiosSetFightFlag(u16, s32);
u16 darkpokemonBiosGetScenarioNum(void);
void esabaGet(s32);
s32 esabaGetPokemonMax(u16);
void esabaPut(s32);
void esabaSet(s32);
void esabaSetPokemon(u16, u16);
void esabaSetPokemonRnd(s32, s32);
void evolutionOpen(Pokemon*, Pokemon*, s32, s16*, s32, void*);
void fadeCheck(s32);
void fadeSet(s32, f32);
s32 gamedataGetStatus(s32, s32);
Pokemon* heroBiosGetPokemonPtr(u32*, s32);
void heroCatchPokemon(s32, Pokemon*, s32, s32, s32);
s32 heroGetStatus(s32, s32, s32);
s32 memoDataGetPokemonRndFromID(s32, u16);
s32 memoDataGetPokemonTrainerRndFromID(s32, u16);
void memoDataSetMemoFlag(s32);
void memoDataSetPokemonID(s32, u16);
void memoInitDebug(s32);
void menuBattleDiskOpen(void);
void menuBattleDiskOpenFight(void);
void menuClose(s32);
void menuCloseSync(s32, s32);
void menuIntUnderTakerOpenIcon(void);
u8 menuIsCheck(s32);
void menuMoveDemo(s32);
void menuNameEntryOpen(s32, s32);
void menuNintendoWarning(void);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
void menuOrreColosseum(u16);
void menuOrreColosseumGetResult(void);
void menuPokemonChange(void);
void menuPokemonOpen(s32, s32, s32);
void menuPokemonStatusOpenWazaLearn(Pokemon*, s32);
void menuScriptEevee(void);
void menuScriptInfoEsa(void);
void menuScriptInfoRelive(s32, s32);
void menuScriptOpenWorldMap(u16);
void menuScriptPdaAddFunc(u32);
void menuScriptReadMail(u32);
void menuScriptReciveMail(void);
void menuScriptTutorial(void);
void menuScriptUsohachi(void);
void menuScriptUsohachi2(void);
void menuScriptWazaBasan(void*);
void menuScriptWazaMeijin(s32);
void menuShopOpen(s32);
void menuSubCloseNumberInput(void);
void menuSubCloseNumberInputWait(void);
u8 menuSubOpenNumberInput(s32, u32*, s32, s32, s32, s32);
s32 menuSubOpenSelect2(s32, s32*, s32, s32, s32, s32, s32, s32);
void menuWorldMapMXDebug(void);
void mewWazaSequence(void);
void msgctrlSetValue(s32, s32);
void pcboxDebugPokemonSetup(void);
void pcboxDebugPokemonSetupFull(void);
void pokemonBiosSetCatchTrainerRnd(Pokemon*, s32);
void pokemonBiosSetRnd(Pokemon*, s32);
u8 pokemonCheckValid(Pokemon*);
void pokemonCreate(Pokemon*, u16, s32, s32);
s32 pokemonCreateRndFit(Pokemon*, s32, s32, s32, s32);
void pokemonSetDarkPokemonStatus(Pokemon*, u16);
void reliveHallDebugPokemonSetup(s32);
u32* savedataGetStatus(s32, s32);
u32 undertakerGetPlace(u32*);
s32 undertakerGetStartFlagID(void);
void undertakerSetPlace(u32);
s32 windowGetActiveID(void);
DbgMenuKeyInfo* windowGetKeyInfo(void);

extern WorldMapXDData* worldmapXD_data;
extern u32* worldmapXD_data_number;
u16 _testEncount[28] = {
    0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64,
    0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72,
};
}

void makePocketDeubugMakeDarkPokemonReset(void);

static u32 _undertakerFloorID[8];
static DbgWorldMapData _debugWorldMapData;
static u32 _undertakerFloorCount;
static s32 _esabaPlace;
static u16 _esabaSelectPokemon;

static s32 _getWorldMapFlagData(long index);
static void _setWorldMapFlagData(long index, long value);
static void _pokemonCreate(Pokemon* pokemon, u16 id, u32 trainerRnd);
static void _esabaSetPokemon(long place, long id);
static void _dbgMenuMenuTestPdaFlagSet(u32 flag);
static void _debugPokemonCreate(Pokemon* pokemon, u16 id);
static u16 _getDPPokemonID(long index);
static void _setDPStatus(long index, darkPokemonStatus status);
static s32 _getDPStatus(long index);

extern "C" {

s32 dbgMenuMenuReliveHallDisp(void) {
    if (menuIsCheck(0x108)) {
        menuClose(0x108);
    } else {
        menuOpenCustom(0x108, 0, 0, 0, 1, 0);
    }
    return 0;
}

}

static s32 _getWorldMapFlagData(long index) {
    if (worldmapXD_data[index].flag == 0) {
        return -1;
    }
    return GSflagGet(worldmapXD_data[index].flag);
}

static void _setWorldMapFlagData(long index, long value) {
    if (worldmapXD_data[index].flag != 0) {
        GSflagSet(worldmapXD_data[index].flag, value);
    }
}

extern "C" {

s32 dbgMenuMenuTestUsohachi2(void) {
    menuScriptUsohachi2();
    return 0;
}

s32 dbgMenuMenuTestUsohachi(void) {
    menuScriptUsohachi();
    return 0;
}

s32 dbgMenuMenuTestWorlMapShow(void) {
    s32 result;

    _debugWorldMapData.select = 0;
    _debugWorldMapData.mode = 0;
    _debugWorldMapData.count = *worldmapXD_data_number;
    result = menuOpenCustom(0xD7, windowGetActiveID(), 0, 0, 1, 1, &_debugWorldMapData);
    menuClose(0xD7);
    menuCloseSync(0xD7, 1);
    if (result >= 0) {
        menuScriptOpenWorldMap(_debugWorldMapData.select);
    }
    return 0;
}

s32 dbgMenuMenuWorldMapCursor(DbgMenuWindow* window) {
    DbgMenuKeyInfo* key = windowGetKeyInfo();
    DbgWorldMapData* data = (DbgWorldMapData*)window->data;
    s32 flag;

    if (window->id != 0xD7) {
        if (key->trigger & 1) {
            if (--window->cursor < 0) {
                window->cursor = 0;
            }
        } else if (key->trigger & 2) {
            if (++window->cursor > 1) {
                window->cursor = 1;
            }
        }
    }
    switch (window->cursor) {
    case 0:
        if (key->trigger & 8) {
            if (data->select < (u16)(data->count - 1)) {
                data->select++;
            }
        } else if (key->trigger & 4) {
            if (data->select != 0) {
                data->select--;
            }
        }
        break;
    case 1:
        flag = _getWorldMapFlagData(data->select);
        if (flag >= 0) {
            if (key->trigger & 8) {
                if (flag < 2) {
                    flag++;
                }
            } else if ((key->trigger & 4) && flag != 0) {
                flag--;
            }
            _setWorldMapFlagData(data->select, flag);
        }
        break;
    }
    return 0;
}

s32 dbgMenuMenuTestWorlMapFlagSet(void) {
    _debugWorldMapData.select = 0;
    _debugWorldMapData.mode = 0;
    _debugWorldMapData.count = *worldmapXD_data_number;
    while (menuOpenCustom(0xC4, windowGetActiveID(), 0, 0, 1, 1, &_debugWorldMapData) != -1) {
    }
    menuClose(0xC4);
    menuCloseSync(0xC4, 1);
    return 0;
}

s32 dbgMenuEsabaDebugCursor(DbgMenuWindow* window) {
    DbgMenuKeyInfo* key = windowGetKeyInfo();
    s32 max = esabaGetPokemonMax(_esabaPlace);

    if (key->trigger & 5) {
        if (--window->cursor < 0) {
            window->cursor = 0;
        }
    } else if (key->trigger & 0xA) {
        u16 count = max + 3;
        if (++window->cursor >= count) {
            window->cursor = count - 1;
        }
    }
    return 0;
}

s32 dbgMenuUnderTakerebugCursor(DbgMenuWindow* window) {
    DbgMenuKeyInfo* key = windowGetKeyInfo();
    u32 count;

    _undertakerFloorCount = count = undertakerGetPlace(_undertakerFloorID);
    if (count != 0) {
        if (key->trigger & 5) {
            if (--window->cursor < 0) {
                window->cursor = 0;
            }
        } else if (key->trigger & 0xA) {
            if (++window->cursor >= count) {
                window->cursor = _undertakerFloorCount - 1;
            }
        }
    }
    return 0;
}

s32 dbgMenuMenuTestNintendoWarning(void) {
    menuNintendoWarning();
    return 0;
}

u32 dbgMenuMenuUnderTakerIconAppear(void) {
    s32 result = menuOpenCustom(0x111, windowGetActiveID(), 0, 0, 1, 0);

    if (result >= 0 && _undertakerFloorID[result] != 0) {
        undertakerSetPlace(_undertakerFloorID[result]);
    }
    menuClose(0x111);
    menuCloseSync(0x111, 1);
    return (u32)result >> 31;
}

s32 dbgMenuMenuUnderTakerIconFlagOnOff(void) {
    if (GSflagTest(0x5AD)) {
        GSflagOff(0x5AD);
    } else {
        GSflagOn(0x5AD);
    }
    return 0;
}

s32 dbgMenuMenuUnderTakerIconOnOff(void) {
    menuIntUnderTakerOpenIcon();
    return 0;
}

s32 dbgMenuMenuUnderTakerDisp(void) {
    if (menuIsCheck(0xC0)) {
        menuClose(0xC0);
    } else {
        menuOpenCustom(0xC0, 0, 0, 0, 1, 0);
    }
    return 0;
}

s32 dbgMenuMenuUnderTakerOnOff(void) {
    s32 flag = undertakerGetStartFlagID();

    if (GSflagTest(flag)) {
        GSflagOff(flag);
    } else {
        GSflagOn(flag);
    }
    return 0;
}

s32 dbgMenuMenuTestInfoRelive(void) {
    menuScriptInfoRelive(0, 1);
    return 0;
}

s32 dbgMenuMenuTestInfoEsa(void) {
    menuScriptInfoEsa();
    return 0;
}

s32 dbgMenuMenuEsabaDisp(void) {
    if (menuIsCheck(0xB7)) {
        menuClose(0xB7);
    } else {
        menuOpenCustom(0xB7, 0, 0, 0, 1, 0);
    }
    return 0;
}

u32 dbgMenuMenuTestEsabaPokemon(void) {
    s32 select[2] = { 0xF86F, 0xF146 };
    Pokemon pokemon;
    s32 trainerRnd;
    s32 result;
    s32 rnd;

    _esabaSelectPokemon = 0;
    trainerRnd = heroGetStatus(0, 2, 0);
    result = menuOpenCustom(0x10A, windowGetActiveID(), 0, 0, 1, 0);
    if (result > 0) {
        if (_esabaSelectPokemon == 0x19D || _esabaSelectPokemon == 0x19E) {
            _esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
        } else {
            switch (menuSubOpenSelect2(0, select, 2, 0x96, 0x96, 0, 2, 1)) {
            case 0:
                _esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
                _pokemonCreate(&pokemon, _esabaSelectPokemon, trainerRnd);
                rnd = pokemonCreateRndFit(&pokemon, -1, -1, 0, trainerRnd);
                esabaSetPokemonRnd(_esabaPlace, rnd);
                break;
            case 1:
                _esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
                esabaSetPokemonRnd(_esabaPlace, trainerRnd);
                break;
            }
        }
    } else if (result == 0) {
        _esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
    }
    menuClose(0x10A);
    menuCloseSync(0x10A, 1);
    return (u32)result >> 31;
}

}

static void _pokemonCreate(Pokemon* pokemon, u16 id, u32 trainerRnd) {
    s32 rnd;

    pokemonCreate(pokemon, id, 10, gamedataGetStatus(0, 1));
    rnd = memoDataGetPokemonRndFromID(0, id);
    pokemonBiosSetRnd(pokemon, rnd);
    pokemonBiosSetCatchTrainerRnd(pokemon, trainerRnd);
}

static void _esabaSetPokemon(long place, long id) {
    esabaSetPokemon(_esabaPlace, _esabaSelectPokemon);
}

extern "C" {

s32 dbgMenuMenuTestEsabaGet(void) {
    esabaGet(_esabaPlace);
    return 0;
}

s32 dbgMenuMenuTestEsabaPut(void) {
    esabaPut(_esabaPlace);
    return 0;
}

s32 dbgMenuMenuTestEsabaSet(void) {
    esabaSet(_esabaPlace);
    return 0;
}

s32 dbgMenuMenuSetPlace(DbgMenuWindow* window, s32 place) {
    _esabaPlace = place;
    return 1;
}

s32 dbgMenuMenuMoveDemo(DbgMenuWindow* window, s32 demo) {
    menuMoveDemo(demo);
    return 0;
}

s32 dbgMenuMenuTestMewWazaMenu(void) {
    mewWazaSequence();
    return 0;
}

s32 dbgMenuMenuTestOrreColosseumMenu(void) {
    u32 index = 0;

    menuSubOpenNumberInput(0, &index, 1, 0x32, 0x32, 1);
    if (index >= 28) {
        index = 0;
    }
    menuOrreColosseum(_testEncount[index]);
    menuOrreColosseumGetResult();
    return 0;
}

s32 dbgMenuMenuTestWazaOshieBasanMenu(void) {
    u8 work[4];

    menuScriptWazaBasan(work);
    return 0;
}

s32 dbgMenuMenuTestWazaOshieMeijinMenu(DbgMenuWindow* window, s32 type) {
    menuScriptWazaMeijin(type);
    return 0;
}

s32 dbgMenuMenuTestTutorialMenu(void) {
    menuScriptTutorial();
    return 0;
}

s32 dbgMenuMenuTestEeveeMenu(void) {
    menuScriptEevee();
    return 0;
}

s32 dbgMenuMenuTestPdaAddFunc(void) {
    u32 value = 0;

    if (menuSubOpenNumberInput(0, &value, 1, 0x32, 0x32, 0)) {
        menuSubCloseNumberInput();
        menuSubCloseNumberInputWait();
        if (value > 1) {
            value = 0;
        }
        menuScriptPdaAddFunc(value);
    }
    menuSubCloseNumberInput();
    return 0;
}

s32 dbgMenuMenuTestMailRead(void) {
    u32 value = 0;

    if (menuSubOpenNumberInput(0, &value, 1, 0x32, 0x32, 0)) {
        menuSubCloseNumberInput();
        menuSubCloseNumberInputWait();
        menuScriptReadMail(value);
    }
    menuSubCloseNumberInput();
    return 0;
}

s32 dbgMenuMenuTestMailReceive(void) {
    menuScriptReciveMail();
    return 0;
}

s32 dbgMenuMenuTestPdaSyougou(void) {
    u32 value = GSflagGet(0x6C2);

    for (;;) {
        if (!menuSubOpenNumberInput(value, &value, 1, 0x32, 0x32, 0)) {
            break;
        }
        if (value <= 7) {
            GSflagSet(0x6C2, value);
        }
    }
    menuSubCloseNumberInput();
    return 0;
}

s32 dbgMenuMenuTestPdaMR(void) {
    _dbgMenuMenuTestPdaFlagSet(0x3F4);
    return 1;
}

s32 dbgMenuMenuTestPdaEsa(void) {
    _dbgMenuMenuTestPdaFlagSet(0x3F3);
    return 1;
}

s32 dbgMenuMenuTestPdaDPM(void) {
    _dbgMenuMenuTestPdaFlagSet(0x3F2);
    return 1;
}

s32 dbgMenuMenuTestPdaEnable(void) {
    _dbgMenuMenuTestPdaFlagSet(0x3F1);
    return 1;
}

}

static void _dbgMenuMenuTestPdaFlagSet(u32 flag) {
    u32 value = GSflagTest(flag);

    for (;;) {
        if (!menuSubOpenNumberInput(value, &value, 1, 0x32, 0x32, 0)) {
            break;
        }
        if (value != 0) {
            GSflagOn(flag);
        } else {
            GSflagOff(flag);
        }
    }
    menuSubCloseNumberInput();
}

static void testD2Present(D2PRESENT_MODE mode) {
    d2presentOpen(mode);
}

extern "C" {

s32 dbgMenuMenuTestD2Present(s32 menu) {
    DbgMenuPair table[3] = { { 0x1DF, 0 }, { 0x1E0, 1 }, { 0x1E1, 2 } };
    s32 i;
    s32 value;

    for (i = 0; i < 3; i++) {
        if (menu == table[i].menu) {
            break;
        }
    }
    value = table[i].value;
    GSthreadSetArgs(GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (void (*)(void))testD2Present), 1,
                    value);
    return 0;
}

s32 dbgMenuMenuTestWorlMapSetAllFlag(void) {
    menuWorldMapMXDebug();
    return 0;
}

s32 dbgMenuEntrySnatchListRelive(void) {
    s32 i;

    for (i = 0; i <= darkpokemonBiosGetScenarioNum(); i++) {
        if (_getDPStatus(i) >= 1) {
            _setDPStatus(i, darkStatus4);
        }
    }
    return 1;
}

}

static void _debugPokemonCreate(Pokemon* pokemon, u16 id) {
    s32 rnd;
    s32 trainerRnd;

    pokemonCreate(pokemon, id, 10, gamedataGetStatus(0, 1));
    rnd = memoDataGetPokemonRndFromID(0, id);
    trainerRnd = memoDataGetPokemonTrainerRndFromID(0, id);
    pokemonBiosSetRnd(pokemon, rnd);
    pokemonBiosSetCatchTrainerRnd(pokemon, trainerRnd);
}

extern "C" {

s32 dbgMenuEntrySnatchListSuccess(void) {
    Pokemon pokemon;
    s32 i;

    for (i = 0; i <= darkpokemonBiosGetScenarioNum(); i++) {
        if (_getDPStatus(i) >= 1) {
            u16 id = _getDPPokemonID(i);
            _debugPokemonCreate(&pokemon, id);
            pokemonSetDarkPokemonStatus(&pokemon, i);
            heroCatchPokemon(0, &pokemon, 0, 4, 1);
            _setDPStatus(i, darkStatus3);
        }
    }
    return 1;
}

s32 dbgMenuEntrySnatchListAll(void) {
    s32 i;

    for (i = 0; i <= darkpokemonBiosGetScenarioNum(); i++) {
        if (_getDPStatus(i) == 0) {
            _setDPStatus(i, darkStatus1);
        }
    }
    return 1;
}

s32 dbgMenuEntrySnatchList(void) {
    u32 value = 0;

    for (;;) {
        if (!menuSubOpenNumberInput(value, &value, 1, 0x32, 0x32, 0)) {
            break;
        }
        DarkPokemon* dark = darkPokemonGetDarkPokemon((u16)value);
        if (dark != NULL) {
            darkPokemonBiosSetFightFlag(value, 1);
            dark->setUpdate(true);
        }
    }
    menuSubCloseNumberInput();
    return 1;
}

}

static u16 _getDPPokemonID(long index) {
    return darkPokemonGetDarkPokemon((u16)index)->getPokemonID();
}

static void _setDPStatus(long index, darkPokemonStatus status) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon((u16)index);

    if (dark->getPokemonID() != 0) {
        dark->setStatus(status);
        dark->setUpdate(true);
    }
}

static s32 _getDPStatus(long index) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon((u16)index);

    if (dark->getPokemonID() != 0) {
        return dark->getStatus();
    }
    return 0;
}

extern "C" {

s32 dbgMenuMenuTestTeacherMemo(void) {
    memoDataSetMemoFlag(0);
    return 1;
}

s32 dbgMenuMenuTestCompleteMemo(void) {
    memoInitDebug(0);
    return 1;
}

s32 dbgMenuMenuTestAddPokemonMemo(void) {
    u32 value = 0;

    for (;;) {
        if (!menuSubOpenNumberInput(value, &value, 1, 0x32, 0x32, 0)) {
            break;
        }
        memoDataSetPokemonID(0, value);
    }
    menuSubCloseNumberInput();
    return 1;
}

s32 dbgMenuMenuTestEnableMemo(void) {
    return 1;
}

}

static void testEvolution(void) {
    Pokemon* before = (Pokemon*)heroGetStatus(0, 3, 0);
    Pokemon* after;
    struct {
        u8 result[0x14];
        s16 order[2];
        u8 unk18[0x28];
    } work;

    if (pokemonCheckValid(before)) {
        after = (Pokemon*)heroGetStatus(0, 3, 1);
        if (pokemonCheckValid(after)) {
            fadeSet(3, 0.5f);
            fadeCheck(1);
            work.order[0] = 1;
            work.order[1] = 2;
            evolutionOpen(before, after, 1, work.order, 2, work.result);
            fadeSet(2, 0.5f);
            fadeCheck(1);
        }
    }
}

extern "C" {

s32 dbgMenuMenuTestEvolution(void) {
    GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, testEvolution);
    return 0;
}

s32 dbgMenuMenuTestWazaMenu(void) {
    u32* hero = savedataGetStatus(0, 2);
    Pokemon* pokemon;

    if (hero == NULL) {
        return 0;
    }
    pokemon = heroBiosGetPokemonPtr(hero, 0);
    if (!pokemonCheckValid(pokemon)) {
        return 0;
    }
    menuPokemonStatusOpenWazaLearn(pokemon, 0x25);
    return 0;
}

s32 dbgMenuMenuTestPokemonChangeMenu(void) {
    msgctrlSetValue(0x59, 0x1772);
    menuPokemonChange();
    return 0;
}

s32 dbgMenuMenuTestPCBox(void) {
    GSfloorPush(0x391);
    return 0;
}

s32 dbgMenuMenuTestRelivehallTutorialMenu(void) {
    msgctrlSetValue(0x59, 0x1772);
    GSfloorPush(0x3A7);
    return 0;
}

s32 dbgMenuMenuTestPcBoxPokemonSetFull(void) {
    makePocketDeubugMakeDarkPokemonReset();
    pcboxDebugPokemonSetupFull();
    reliveHallDebugPokemonSetup(2);
    return 0;
}

s32 dbgMenuMenuTestReliveHallPokemonSetBest(void) {
    makePocketDeubugMakeDarkPokemonReset();
    pcboxDebugPokemonSetup();
    reliveHallDebugPokemonSetup(2);
    return 0;
}

s32 dbgMenuMenuTestReliveHallPokemonSet1(void) {
    makePocketDeubugMakeDarkPokemonReset();
    pcboxDebugPokemonSetup();
    reliveHallDebugPokemonSetup(0);
    return 0;
}

s32 dbgMenuMenuTestReliveHallPokemonSet0(void) {
    makePocketDeubugMakeDarkPokemonReset();
    pcboxDebugPokemonSetup();
    reliveHallDebugPokemonSetup(1);
    return 0;
}

s32 dbgMenuMenuTestHologramMenu(void) {
    GSfloorPush(0x3A6);
    return 0;
}

s32 dbgMenuMenuTestReliveHallMenu(void) {
    GSfloorPush(0x3A3);
    return 0;
}

s32 dbgMenuMenuTestBingoClear(void) {
    u32* status = savedataGetStatus(0, 0x1B);

    *status |= 0x3F0000 | 0xFFFF;
    return 0;
}

s32 dbgMenuMenuTestBingoSelect(void) {
    u32* status = savedataGetStatus(0, 0x1B);

    *status |= 0x2A0000 | 0xAAAA;
    return 0;
}

s32 dbgMenuMenuTestBingo(void) {
    GSfloorPush(0x388);
    return 0;
}

s32 dbgMenuMenuTestBattleDiskExec(void) {
    menuBattleDiskOpenFight();
    return 0;
}

s32 dbgMenuMenuTestBattleDisk(void) {
    menuBattleDiskOpen();
    return 0;
}

s32 dbgMenuMenuTestPokemonMenu(s32 menu) {
    switch (menu) {
    case 0x1D5:
        menuPokemonOpen(1, 0, 0);
        break;
    case 0x1D6:
        menuPokemonOpen(2, 0, 0);
        break;
    default:
        menuPokemonOpen(2, 0, 0);
        break;
    }
    return 0;
}

s32 dbgMenuMenuTestShopMenu(s32 menu) {
    DbgMenuPair table[13] = {
        { 0x1C8, 0 }, { 0x1C9, 16 }, { 0x1CA, 1 }, { 0x1CB, 2 }, { 0x1CC, 3 },
        { 0x1CD, 4 }, { 0x1CE, 5 }, { 0x1CF, 6 }, { 0x1D0, 7 }, { 0x1D1, 8 },
        { 0x1D2, 9 }, { 0x1D3, 10 }, { 0x1D4, 11 },
    };
    s32 i;

    for (i = 0; i < 13; i++) {
        if (menu == table[i].menu) {
            break;
        }
    }
    if (i >= 13) {
        return 0;
    }
    menuShopOpen(table[i].value);
    return 0;
}

s32 dbgMenuMenuTestNameEntryMenu(s32 menu) {
    DbgMenuPair table[4] = { { 0x1C4, 0 }, { 0x1C5, 1 }, { 0x1C6, 2 }, { 0x1C7, 3 } };
    s32 i;

    for (i = 0; i < 4; i++) {
        if (menu == table[i].menu) {
            break;
        }
    }
    if (i >= 4) {
        return 0;
    }
    menuNameEntryOpen(table[i].value, 0);
    return 0;
}

}
