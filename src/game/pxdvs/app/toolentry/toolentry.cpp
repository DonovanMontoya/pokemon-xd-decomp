#include <game/pxdvs/app/toolentry/toolentryPrivate.hpp>

static void* _toolentryAlloc(unsigned long);
static void _toolentryFree(void*);
static ToolentryCBWork* _toolentryGetCBWork();
static Hero* _toolentryTaisenGetHeroPtr(long);
static Hero* _toolentryTaisenGetEntryHeroPtr(long);
static Pokemon* _toolentryTaisenGetPokemonPtr(long, long);
static Pokemon* _toolentryTaisenGetEntryPokemonPtr(long, long);
static u8 _toolentryTaisenGetPokemonFlag(long, long);
static Pokemon* _toolentryDebugGetPokemonPtr(long);
static long _toolentryTrainerFaceIDGet(unsigned long);

static void* _toolentryTaisen;
static void* _toolentryDebugPokemon;
static s32 _toolentryDebugPokemonNum = 0x18;

static void* _toolentryAlloc(unsigned long size) {
    return GSmemAllocAlign((size + 0x1F) & ~0x1F, 0x20);
}

static void _toolentryFree(void* p) {
    GSmemFree(p);
}

static ToolentryCBWork* _toolentryGetCBWork() {
    return menuCBBios_WorkContext();
}

static Hero* _toolentryTaisenGetHeroPtr(long idx) {
    return (Hero*)((u8*)menuCBBios_GetTrainerImmediately(idx) + 0x9A4);
}

static Hero* _toolentryTaisenGetEntryHeroPtr(long idx) {
    return (Hero*)((u8*)menuCBBios_GetTrainerImmediately(idx) + 0x2C);
}

static Pokemon* _toolentryTaisenGetPokemonPtr(long idx, long slot) {
    return heroBiosGetPokemonPtr((Hero*)((u8*)menuCBBios_GetTrainerImmediately(idx) + 0x9A4), slot);
}

static Pokemon* _toolentryTaisenGetEntryPokemonPtr(long idx, long slot) {
    return heroBiosGetPokemonPtr((Hero*)((u8*)menuCBBios_GetTrainerImmediately(idx) + 0x2C), slot);
}

static u8 _toolentryTaisenGetPokemonFlag(long idx, long slot) {
    u8 valid = pokemonCheckValid(heroBiosGetPokemonPtr((Hero*)((u8*)menuCBBios_GetTrainerImmediately(idx) + 0x9A4), slot));
    return valid != 0;
}

extern "C" {

void toolentryTaisenInit() {
    s32 j;
    s32 i;
    for (i = 0; i < 4; i++) {
        heroInit(_toolentryTaisenGetHeroPtr(i));
        for (j = 0; j < 6; j++) {
            pokemonInit(_toolentryTaisenGetPokemonPtr(i, j));
        }
    }
    for (i = 0; i < 4; i++) {
        heroInit(_toolentryTaisenGetEntryHeroPtr(i));
        for (j = 0; j < 6; j++) {
            pokemonInit(_toolentryTaisenGetEntryPokemonPtr(i, j));
        }
    }
}

u8 toolentryTaisenSetPokemon(Pokemon* src, s32 idx, s32 slot) {
    Pokemon* dst = _toolentryTaisenGetPokemonPtr(idx, slot);
    if (dst) {
        memcpy(dst, src, sizeof(Pokemon));
        return 1;
    }
    return 0;
}

u8 toolentryTaisenSetHeroFromSaveData(s32 idx) {
    void* save = savedataGetStatus(0, 2);
    Hero* hero = _toolentryTaisenGetHeroPtr(idx);
    if (save) {
        memcpy(hero, save, sizeof(Hero));
        return 1;
    }
    return 0;
}

u8 toolentryTaisenGetPokemonFlag(s32 idx, s32 slot) {
    return _toolentryTaisenGetPokemonFlag(idx, slot);
}

s32 toolentryTaisenGetBattleType() {
    return _toolentryGetCBWork()->battleType;
}

s32 toolentryTaisenGetEntryPlayerNum() {
    s32 type = toolentryTaisenGetBattleType();
    s32 n = 2;
    switch (type) {
    case 0:
    case 1:
        n = 2;
        break;
    case 2:
        n = 4;
        break;
    }
    return n;
}

u32 toolentryTaisenGetBattlePlayerID(s32 idx) {
    return menuCBTrainerBios_GetPlayerID(menuCBBios_GetTrainerImmediately(idx));
}

u16 toolentryTaisenGetHomePlace(s32 idx) {
    return menuCBTrainerBios_GetHomePlace(menuCBBios_GetTrainerImmediately(idx));
}

s32 toolentryTaisenGetBattleVersus() {
    return _toolentryGetCBWork()->battleVersus;
}

s32 toolentryTaisenGetBattleMode() {
    return _toolentryGetCBWork()->battleMode;
}

Pokemon* toolentryTaisenGetPokemonPtr(s32 idx, s32 slot) {
    return _toolentryTaisenGetPokemonPtr(idx, slot);
}

Pokemon* toolentryTaisenGetEntryPokemonPtr(s32 idx, s32 slot) {
    return _toolentryTaisenGetEntryPokemonPtr(idx, slot);
}

Hero* toolentryTaisenGetHeroPtr(s32 idx) {
    return _toolentryTaisenGetHeroPtr(idx);
}

Hero* toolentryTaisenGetEntryHeroPtr(s32 idx) {
    return _toolentryTaisenGetEntryHeroPtr(idx);
}

u16 toolentryTaisenGetPokemonNum(s32 idx) {
    u16 n = 0;
    s32 i;
    for (i = 0; i < 6; i++) {
        if (toolentryTaisenGetPokemonFlag(idx, i)) {
            n++;
        }
    }
    return n;
}

u16 toolentryTaisenGetEntryPokemonNum(s32 idx) {
    u16 limit = menuCBBios_ParticipationPokemonMax();
    u16 num = toolentryTaisenGetPokemonNum(idx);
    return (num < limit) ? num : limit;
}

void toolentryCopyHero() {
    Hero* src;
    Hero* dst;
    s32 i;
    for (i = 0; i < 4; i++) {
        src = toolentryTaisenGetHeroPtr(i);
        dst = toolentryTaisenGetEntryHeroPtr(i);
        if (src && dst) {
            *dst = *src;
        }
    }
}

void toolentryTaisenInitPokemonOrder(s32 idx) {
    ToolentryCBTrainer* t = menuCBBios_GetTrainerImmediately(idx);
    s32 i;
    t->orderNum = 0;
    for (i = 0; i < 6; i++) {
        t->order[i] = -1;
    }
}

s32 toolentryTaisenSetEtnryPokemonOrder(s32 idx, s32 pokemon) {
    ToolentryCBTrainer* t = menuCBBios_GetTrainerImmediately(idx);
    s32 num = t->orderNum;
    s32 i;
    if (t->orderNum >= toolentryTaisenGetEntryPokemonNum(idx)) {
        return -1;
    }
    for (i = 0; i < num; i++) {
        if (t->order[i] == pokemon) {
            return -1;
        }
    }
    t->order[num] = pokemon;
    t->orderNum++;
    return num;
}

s32 toolentryTaisenSetEtnryPokemonOrderGBA(s32 idx, s32 count, s32* order) {
    ToolentryCBTrainer* t = menuCBBios_GetTrainerImmediately(idx);
    s32 n = 0;
    s32 i;
    for (i = 0; i < count; i++) {
        t->order[i] = order[i];
        n++;
    }
    t->orderNum = n;
    return n;
}

s32 toolentryTaisenDeleteEtnryPokemonOrder(s32 idx) {
    ToolentryCBTrainer* t = menuCBBios_GetTrainerImmediately(idx);
    s32 last = t->orderNum - 1;
    if (last < 0 || last > 6) {
        return 0;
    }
    t->order[last] = -1;
    t->orderNum--;
    return t->orderNum;
}

s32 toolentryTaisengetEtnryPokemonOrderNum(s32 idx) {
    return menuCBBios_GetTrainerImmediately(idx)->orderNum;
}

s32 toolentryTaisenGetEtnryPokemonOrder(s32 idx, s32 slot) {
    ToolentryCBTrainer* t = (ToolentryCBTrainer*)((u8*)menuCBBios_GetTrainerImmediately(idx) + slot * 4);
    return t->order[0];
}

void toolentryTaisenFreePokemonData();

void toolentryTaisenCreateBattlePokemonData() {
    toolentryTaisenFreePokemonData();
    _toolentryTaisen = _toolentryAlloc(0x70);
}

void toolentryTaisenFreePokemonData() {
    if (_toolentryTaisen) {
        _toolentryFree(_toolentryTaisen);
        _toolentryTaisen = 0;
    }
}

void toolentryTaisenEntryPokemon(s32 idx) {
    s32 num = toolentryTaisenGetEntryPokemonNum(idx);
    Hero* entryHero = _toolentryTaisenGetEntryHeroPtr(idx);
    Hero* hero = _toolentryTaisenGetHeroPtr(idx);
    *entryHero = *hero;
    for (s32 i = 0; i < 6; i++) {
        s32 order;
        pokemonInit(_toolentryTaisenGetEntryPokemonPtr(idx, i));
        order = toolentryTaisenGetEtnryPokemonOrder(idx, i);
        if (order == 0xF || order == -1) {
            if (num > i) {
                num = i;
            }
        } else {
            Pokemon* src = _toolentryTaisenGetPokemonPtr(idx, i);
            Pokemon* dst = _toolentryTaisenGetEntryPokemonPtr(idx, i);
            if (dst && src) {
                *dst = *src;
            }
        }
    }
    for (s32 k = 0; k < num; k++) {
        Pokemon* src = _toolentryTaisenGetPokemonPtr(idx, toolentryTaisenGetEtnryPokemonOrder(idx, k));
        Pokemon* dst = _toolentryTaisenGetEntryPokemonPtr(idx, k);
        if (dst && src) {
            *dst = *src;
        }
    }
}

u16 toolentryTaisenGetTrainerDataID(s32);

u32 toolentryGetTrainerBicFaceResID(s32 idx, s32 girl) {
    u32 res;
    u32 val;
    u16 id = toolentryTaisenGetTrainerDataID(idx);
    if (id == 0) {
        return 0;
    }
    ToolentryTrainerFace* face;
    long fid = _toolentryTrainerFaceIDGet((u16)fightTrainerDB_GetPkxDataId(id));
    face = trainer_face_data + fid;
    if (girl == 0) {
        val = face->bigFaceBoy;
        res = 0x21BF1200;
        if (val != 0) {
            res = val;
        }
    } else {
        val = face->bigFaceGirl;
        res = 0x21E81200;
        if (val != 0) {
            res = val;
        }
    }
    return res;
}

u32 toolentryGetTrainerSamllFaceResID(s32 idx, s32 girl) {
    u32 res;
    u32 val;
    u16 id = toolentryTaisenGetTrainerDataID(idx);
    if (id == 0) {
        return 0;
    }
    ToolentryTrainerFace* face;
    long fid = _toolentryTrainerFaceIDGet((u16)fightTrainerDB_GetPkxDataId(id));
    face = trainer_face_data + fid;
    if (girl == 0) {
        val = face->smallFaceBoy;
        res = 0x21D91200;
        if (val != 0) {
            res = val;
        }
    } else {
        val = face->smallFaceGirl;
        res = 0x21F31200;
        if (val != 0) {
            res = val;
        }
    }
    return res;
}

s32 toolentryTaisenGetControlerType(s32 idx) {
    return menuCBBios_GetTrainerImmediately(idx)->controllerType;
}

u16 toolentryTaisenGetTrainerDataID(s32 idx) {
    return menuCBBios_GetTrainerImmediately(idx)->trainerDataId;
}

}

static Pokemon* _toolentryDebugGetPokemonPtr(long idx) {
    return (Pokemon*)((u8*)_toolentryDebugPokemon + idx * 0xC4);
}

extern "C" {

void toolentryCreateDebugPokemon() {
    Pokemon* p;
    s32 i;
    _toolentryDebugPokemon = 0;
    _toolentryDebugPokemon = _toolentryAlloc(_toolentryDebugPokemonNum * 0xC4);
    p = (Pokemon*)_toolentryDebugPokemon;
    for (i = 0; i < _toolentryDebugPokemonNum; i++) {
        pokemonCreate(p, i + 1, 10, gamedataGetStatus(0, 1));
        s32 chr = GSmsgGetGSchar(i + 1);
        pokemonSetCatchStatus(p, 0, 8, 1, 0, 0, chr);
        pokemonAllKaihuku(p);
        p++;
    }
}

void toolentryFreeDebugPokemon() {
    if (_toolentryDebugPokemon) {
        _toolentryFree(_toolentryDebugPokemon);
        _toolentryDebugPokemon = 0;
    }
}

void toolentryDebugPokemonCreate() {
    s32 j;
    s32 i;
    s32 n;
    toolentryCreateDebugPokemon();
    toolentryTaisenCreateBattlePokemonData();
    toolentryTaisenInit();
    n = 0;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            toolentryTaisenSetHeroFromSaveData(i);
        } else {
            for (j = 0; j < 6; j++) {
                toolentryTaisenSetPokemon(_toolentryDebugGetPokemonPtr(n), i, j);
                n++;
            }
        }
    }
    toolentryFreeDebugPokemon();
}

void toolentryDebugPokemonDelete() {
    toolentryTaisenFreePokemonData();
}

}

static long _toolentryTrainerFaceIDGet(unsigned long id) {
    long i;
    for (i = 0; i < *trainer_face_data_number; i++) {
        if (trainer_face_data[i].trainerId == (u16)id) {
            return i;
        }
    }
    return 1;
}
