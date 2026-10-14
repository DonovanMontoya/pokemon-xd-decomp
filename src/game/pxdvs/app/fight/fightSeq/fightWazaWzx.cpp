#include <dolphin/types.h>

struct FightOutPokemon;
struct FightWaza;
struct Pokemon;
struct FightPokemon;
struct FightTargetData;

extern "C" {
extern u8* UserWork;
u8 fight_seq_oiuchiflag;

u8 fightFloorGetNowTenkouDataId(void*, u8);
u32 fightFloor_GetFightType(void*);
s16 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon*, u16);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
u16 fightWaza_GetIryoku(FightWaza*);
u16 fightWaza_GetTargetDataId(FightWaza*);
s32 fightWaza_GetDamage(FightWaza*);
u8 figthOutPokemonGetLevel(FightOutPokemon*);
FightOutPokemon* fightTargetGetPtr(u8, FightOutPokemon*, u8);
FightOutPokemon* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16, u8);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonLoadWazaEffect(FightOutPokemon*, u16, u8, u32);
u16 wazaDB_GetWazawzxdataId(u16);
void* fightOutPokemon_GetSequencePtr(FightOutPokemon*);
void* fightOutPokemonCreateSequence(FightOutPokemon*, u32, s32);
void fightOutPokemonBiosCopy(void*, FightOutPokemon*);
void fightOutPokemon_SetSequencePtr(void*, void*);
void battleGridReplacePokemon(void*, void*);
void battleGridUpdate();
void Sequence_Free(void*);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
s8 pokemonCheckRare(Pokemon*);
void fightSeqFightOutPokemonEffect(u8, FightOutPokemon*, u8, u8);
void* fightTargetDataBiosGetPtr(u8);
void* fightTargetDataBiosGetBuff(void*);
void fightOutPokemonWazaEffect(FightOutPokemon*, u16, s32, bool, void*);
}

static void _fightWazaWxzfightOutPokemonWazaEffectSpe(FightOutPokemon*, u16, bool);
static void _fightWazaWxzfightOutPokemonWazaEffectDef(FightOutPokemon*, u16, bool);
static void _fightWazaWxzfightOutPokemonWazaEffectAtk(FightOutPokemon*, u16, bool);

extern "C" {
void fightWazaWzxTypeFuncNormal(u16, FightOutPokemon*, FightOutPokemon*, u16, u32);

u32 fightWazaWzxVariationFuncOiuchi(u16, FightOutPokemon*) {
    return fight_seq_oiuchiflag == 1;
}

u32 fightWazaWzxVariationFuncWeatherBall(u16, FightOutPokemon*) {
    switch (fightFloorGetNowTenkouDataId(0, 1)) {
    case 0: return 0;
    case 2: return 1;
    case 4: return 2;
    case 1: return 3;
    case 3: return 4;
    case 5: return 5;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncIceball(u16, FightOutPokemon* poke) {
    switch (fightOutPokemonGetCountAsJoutaiDataId(poke, 0x2f)) {
    case 1: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case -1: return 4;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncKawarawari(u16, FightOutPokemon*) {
    switch (UserWork[0x16002]) {
    case 0: return 3;
    case 1: return 2;
    case 2: return 1;
    case 3: return 0;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncNomikomu(u16, FightOutPokemon*) {
    switch (UserWork[0x16002]) {
    case 1:
    case 2: return 0;
    case 3: return 1;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncHakidasu(u16, FightOutPokemon*) {
    switch (UserWork[0x16002]) {
    case 1:
    case 2: return 0;
    case 3: return 1;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncWeatherHP(u16, FightOutPokemon*) {
    switch (fightFloorGetNowTenkouDataId(0, 1)) {
    case 1: return 0;
    case 0: return 1;
    case 2:
    case 3:
    case 4:
    case 5: return 2;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncMagnitude(u16, FightOutPokemon* poke) {
    switch (fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(poke))) {
    case 10:
    case 30: return 0;
    case 50:
    case 70:
    case 90: return 1;
    case 110:
    case 150: return 2;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncYatuatari(u16, FightOutPokemon* poke) {
    u16 power = fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(poke));
    if (power > 0x59) return 3;
    if (power >= 0x3e) return 2;
    return power >= 0x16;
}

u32 fightWazaWzxVariationFuncPresent(u16, FightOutPokemon* poke) {
    switch (fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(poke))) {
    case 40:
    case 80:
    case 120: return 0;
    }
    return 1;
}

u32 fightWazaWzxVariationFuncOngaesi(u16, FightOutPokemon* poke) {
    u16 power = fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(poke));
    if (power <= 0x18) return 0;
    if (power <= 0x24) return 1;
    return (power <= 0x50) ? 2 : 3;
}

u32 fightWazaWzxVariationFuncRenzokugiri(u16, FightOutPokemon* poke) {
    switch (fightOutPokemonGetCountAsJoutaiDataId(poke, 0x2e)) {
    case 1: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case 5: return 4;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncKorogaru(u16, FightOutPokemon* poke) {
    switch (fightOutPokemonGetCountAsJoutaiDataId(poke, 0x2f)) {
    case 1: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case -1: return 4;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncTripleKick(u16, FightOutPokemon* poke) {
    switch (fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(poke))) {
    case 10: return 0;
    case 20: return 1;
    case 30: return 2;
    }
    return 0;
}

u32 fightWazaWzxVariationFuncTikyuunage(u16, FightOutPokemon* poke) {
    u8 level = figthOutPokemonGetLevel(poke);
    if (level < 0x21) return 0;
    return (level < 0x42) ? 1 : 2;
}

u32 fightWazaWzxVariationFuncKetaguri(u16, FightOutPokemon* poke) {
    switch (fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(poke))) {
    case 20: return 0;
    case 40: return 1;
    case 60: return 2;
    case 80: return 3;
    case 100: return 4;
    case 120: return 5;
    }
    return 0;
}

void fightWazaWzxTypeFuncHuuin(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    u32 v = var;
    u8 type = fightFloor_GetFightType(0);
    FightOutPokemon* a = fightTargetGetPtr(0xf, atk, type);
    FightOutPokemon* b = fightTargetGetPtr(0x10, atk, type);
    fightOutPokemonLoadWazaEffect(atk, waza, 1, v);
    fightOutPokemonLoadWazaEffect(a, waza, 2, v);
    fightOutPokemonLoadWazaEffect(b, waza, 2, v);
    if (fightOutPokemonCheckFightOut(a) == 1 && fightOutPokemonCheckFightOut(b) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(a, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(b, waza, false);
    } else if (fightOutPokemonCheckFightOut(b) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(b, waza, false);
    } else if (fightOutPokemonCheckFightOut(a) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(a, waza, false);
    } else {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
    }
}

void fightWazaWzxTypeFuncMigawari(u16 waza, FightOutPokemon* poke, FightOutPokemon* def, u16 mode, u32 var) {
    void* oldSeq;
    u32 weather = fightFloorGetNowTenkouDataId(0, 1);
    u8 copy[0x898];
    wazaDB_GetWazawzxdataId(waza);
    oldSeq = fightOutPokemon_GetSequencePtr(poke);
    void* newSeq = fightOutPokemonCreateSequence(poke, weather, -1);
    fightOutPokemonBiosCopy(copy, poke);
    fightOutPokemon_SetSequencePtr(copy, newSeq);
    fightOutPokemonLoadWazaEffect(poke, waza, 1, 0);
    fightOutPokemonLoadWazaEffect((FightOutPokemon*)copy, waza, 3, 0);
    _fightWazaWxzfightOutPokemonWazaEffectAtk(poke, waza, true);
    battleGridReplacePokemon(oldSeq, newSeq);
    battleGridUpdate();
    fightOutPokemon_SetSequencePtr(poke, newSeq);
    _fightWazaWxzfightOutPokemonWazaEffectSpe(poke, waza, false);
    Sequence_Free(oldSeq);
}

void fightWazaWzxTypeFuncHensin(u16 waza, FightOutPokemon* poke, FightOutPokemon* def, u16 mode, u32 var) {
    void* oldSeq;
    u32 weather = fightFloorGetNowTenkouDataId(0, 1);
    u8 copy[0x898];
    wazaDB_GetWazawzxdataId(waza);
    oldSeq = fightOutPokemon_GetSequencePtr(poke);
    s8 rare = pokemonCheckRare(fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(poke)));
    void* newSeq = fightOutPokemonCreateSequence(poke, weather, rare);
    fightOutPokemonBiosCopy(copy, poke);
    fightOutPokemon_SetSequencePtr(copy, newSeq);
    fightOutPokemonLoadWazaEffect(poke, waza, 3, 0);
    fightOutPokemonLoadWazaEffect((FightOutPokemon*)copy, waza, 3, 1);
    _fightWazaWxzfightOutPokemonWazaEffectSpe(poke, waza, true);
    battleGridReplacePokemon(oldSeq, newSeq);
    battleGridUpdate();
    fightOutPokemon_SetSequencePtr(poke, newSeq);
    _fightWazaWxzfightOutPokemonWazaEffectSpe(poke, waza, false);
    Sequence_Free(oldSeq);
}

void fightWazaWzxTypeFuncKawarawari(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    fightOutPokemonLoadWazaEffect(atk, waza, 1, 0);
    fightOutPokemonLoadWazaEffect(def, waza, 2, var);
    _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
    _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
}

void fightWazaWzxTypeFuncMagiccort(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
    if (fightOutPokemonIsJoutaiDataId(def, 0x37) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, false);
    }
}

void fightWazaWzxTypeFuncNegaigoto(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
    _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, false);
}

void fightWazaWzxTypeFuncTedasuke(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    u8 type = fightFloor_GetFightType(0);
    fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightWaza_GetTargetDataId(fightOutPokemon_GetFightWazaPtr(atk)), type);
    FightOutPokemon* target = fightTargetGetPtr(0xe, atk, type);
    fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
    fightOutPokemonLoadWazaEffect(target, waza, 3, var);
    _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
    if (fightOutPokemonCheckFightOut(target) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectSpe(target, waza, false);
    }
}

void fightWazaWzxTypeFuncAtt(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
    if (mode == 0) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, false);
    }
}

void fightWazaWzxTypeFuncItamiwake(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, false);
    } else {
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    }
}

void fightWazaWzxTypeFuncAttDef(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, false);
    } else {
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    }
}

void fightWazaWzxTypeFuncAllAlly(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    u8 type = fightFloor_GetFightType(0);
    FightOutPokemon* ally = fightTargetGetPtr(0xe, atk, type);
    fightOutPokemonLoadWazaEffect(atk, waza, 3, var);
    fightOutPokemonLoadWazaEffect(ally, waza, 3, var);
    if (fightOutPokemonCheckFightOut(ally) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectSpe(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectSpe(ally, waza, false);
    } else {
        _fightWazaWxzfightOutPokemonWazaEffectSpe(atk, waza, false);
    }
}

void fightWazaWzxTypeFuncAllEnemy(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    u8 type = fightFloor_GetFightType(0);
    FightOutPokemon* other = fightTargetGetPtr(0x10, atk, type);
    fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
    fightOutPokemonLoadWazaEffect(def, waza, 2, var);
    fightOutPokemonLoadWazaEffect(other, waza, 2, var);
    if (fightOutPokemonCheckFightOut(other) == 1) {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(other, waza, false);
    } else {
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    }
}

void fightWazaWzxTypeFuncAttDefSpc(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        fightOutPokemonLoadWazaEffect(atk, waza, 3, var);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    } else if (mode == 1) {
        fightOutPokemonLoadWazaEffect(atk, waza, 3, var);
        _fightWazaWxzfightOutPokemonWazaEffectSpe(atk, waza, false);
    }
}

void fightWazaWzxTypeFuncVampire(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    s32 damage = fightWaza_GetDamage(fightOutPokemon_GetFightWazaPtr(atk));
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        fightOutPokemonLoadWazaEffect(atk, waza, 3, var);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    } else if (mode == 1) {
        fightOutPokemonLoadWazaEffect(atk, waza, 3, var);
        if (damage > 0) {
            fightSeqFightOutPokemonEffect(0x32, atk, 0, 1);
        } else {
            _fightWazaWxzfightOutPokemonWazaEffectSpe(atk, waza, false);
        }
    }
}

void fightWazaWzxTypeFuncSpc(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    fightOutPokemonLoadWazaEffect(atk, waza, 3, var);
    _fightWazaWxzfightOutPokemonWazaEffectSpe(atk, waza, false);
}

void fightWazaWzxTypeFuncTame(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    if (UserWork[0x16002] != 1) {
        fightOutPokemonLoadWazaEffect(atk, waza, 3, var);
        _fightWazaWxzfightOutPokemonWazaEffectSpe(atk, waza, false);
    } else {
        fightWazaWzxTypeFuncNormal(waza, atk, def, mode, var);
    }
}

void fightWazaWzxTypeFuncNormal2(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(atk, waza, 1, 0);
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    } else {
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    }
}

void fightWazaWzxTypeFuncNormal(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var) {
    if (mode == 0) {
        fightOutPokemonLoadWazaEffect(atk, waza, 1, var);
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        _fightWazaWxzfightOutPokemonWazaEffectAtk(atk, waza, true);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    } else {
        fightOutPokemonLoadWazaEffect(def, waza, 2, var);
        _fightWazaWxzfightOutPokemonWazaEffectDef(def, waza, false);
    }
}

u32 fightWazaWzxVariationFuncNormal(u16, FightOutPokemon*) {
    return 0;
}

void fightWazaWzxTypeFuncNull(u16, FightOutPokemon*, FightOutPokemon*, u16, u8) {
}

u32 fightWazaWzxVariationFuncNull(u16, FightOutPokemon*) {
    return 0;
}
}

static void _fightWazaWxzfightOutPokemonWazaEffectSpe(FightOutPokemon* poke, u16 waza, bool wait) {
    fightOutPokemonWazaEffect(poke, waza, 3, wait, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
}

static void _fightWazaWxzfightOutPokemonWazaEffectDef(FightOutPokemon* poke, u16 waza, bool wait) {
    fightOutPokemonWazaEffect(poke, waza, 2, wait, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
}

static void _fightWazaWxzfightOutPokemonWazaEffectAtk(FightOutPokemon* poke, u16 waza, bool wait) {
    fightOutPokemonWazaEffect(poke, waza, 1, wait, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
}
