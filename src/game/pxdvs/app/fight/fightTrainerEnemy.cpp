#include <game/pxdvs/app/fight/fightTrainerEnemy.hpp>

extern "C" {
s16 fightTrainerEnemyPokemonBiosGetFightEntryeId(FightTrainerEnemyPokemon*);
void fightTrainerEnemyPokemonBiosSetFightEntryeId(FightTrainerEnemyPokemon*, s16);
void fightTrainerEnemyPokemonBiosSetStoreWazaNum(FightTrainerEnemyPokemon*, u8);
void fightTrainerEnemyPokemonBiosSetExpectWazaNum(FightTrainerEnemyPokemon*, u8);
void fightTrainerEnemyPokemonBiosSetStoreWazaDataId(FightTrainerEnemyPokemon*, u8, u16);
void fightTrainerEnemyPokemonBiosSetExpectWazaDataId(FightTrainerEnemyPokemon*, u8, u16);
void fightTrainerEnemyPokemonBiosSetTokuseiFlag(FightTrainerEnemyPokemon*, u8);
void fightTrainerEnemyPokemonBiosSetStoreTokuseiData(FightTrainerEnemyPokemon*, u16);
void fightTrainerEnemyPokemonBiosSetNowhp1banhikuiFlag(FightTrainerEnemyPokemon*, u8);
void fightTrainerEnemyPokemonBiosSetLv1banhikuiFlag(FightTrainerEnemyPokemon*, u8);
void fightTrainerEnemyPokemonBiosSetDefense1banhikuiFlag(FightTrainerEnemyPokemon*, u8);
void fightTrainerEnemyPokemonBiosSetBadwazaHaveFlag(FightTrainerEnemyPokemon*, u8);
void fightTrainerEnemyPokemonBiosSetParam1bantakaiFlag(FightTrainerEnemyPokemon*, u8);

u8 fightTrainerEnemyPokemonEraseAry(FightTrainerEnemyPokemon* ary, u16 count, s16 entry) {
    if (!ary) return 0;
    if (entry < 0) return 0;
    FightTrainerEnemyPokemon* p = fightTrainerEnemyPokemonSearchAry(ary, count, entry);
    if (!p) return 0;
    fightTrainerEnemyPokemonInit(p);
    return 1;
}

u8 fightTrainerEnemyPokemonRegistAry(FightTrainerEnemyPokemon* ary, u16 count, s16 entry) {
    if (!ary) return 0;
    if (entry < 0) return 0;
    if (fightTrainerEnemyPokemonSearchAry(ary, count, entry)) return 0;
    FightTrainerEnemyPokemon* p = fightTrainerEnemyPokemonSearchAry(ary, count, -1);
    if (!p) return 0;
    fightTrainerEnemyPokemonCreate(p, entry);
    return 1;
}

FightTrainerEnemyPokemon* fightTrainerEnemyPokemonSearchAry(FightTrainerEnemyPokemon* ary, u16 count, s16 entry) {
    if (!ary) return 0;
    FightTrainerEnemyPokemon* p;
    for (u16 i = 0; i < count; ++i) {
        p = &ary[i];
        if (entry < 0) {
            if (!fightTrainerEnemyPokemonCheckValid(p)) return p;
        } else if (fightTrainerEnemyPokemonCheckValid(p)) {
            if (entry == fightTrainerEnemyPokemonBiosGetFightEntryeId(p)) return p;
        }
    }
    return 0;
}

bool fightTrainerEnemyPokemonCheckValid(FightTrainerEnemyPokemon* p) {
    if (!p) return 0;
    if (fightTrainerEnemyPokemonBiosGetFightEntryeId(p) < 0) return false;
    return true;
}

void fightTrainerEnemyPokemonCreate(FightTrainerEnemyPokemon* p, s16 entry) {
    if (p && entry >= 0) {
        fightTrainerEnemyPokemonInit(p);
        fightTrainerEnemyPokemonBiosSetFightEntryeId(p, entry);
    }
}

void fightTrainerEnemyPokemonInitAry(FightTrainerEnemyPokemon* ary, u16 count) {
    if (ary) for (u16 i = 0; i < count; ++i) fightTrainerEnemyPokemonInit(&ary[i]);
}

void fightTrainerEnemyPokemonInit(FightTrainerEnemyPokemon* p) {
    fightTrainerEnemyPokemonBiosSetFightEntryeId(p, -1);
    fightTrainerEnemyPokemonInitFightStatus(p);
    fightTrainerEnemyPokemonInitFightOutStatus(p);
    fightTrainerEnemyPokemonBiosSetStoreWazaNum(p, 0);
    fightTrainerEnemyPokemonBiosSetExpectWazaNum(p, 0);
    for (u8 i = 0; i < 4; ++i) fightTrainerEnemyPokemonBiosSetStoreWazaDataId(p, i, 0);
    for (u8 i = 0; i < 8; ++i) fightTrainerEnemyPokemonBiosSetExpectWazaDataId(p, i, 0);
    fightTrainerEnemyPokemonBiosSetTokuseiFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetStoreTokuseiData(p, 0);
}

void fightTrainerEnemyPokemonInitFightOutStatus(FightTrainerEnemyPokemon* p) {
    fightTrainerEnemyPokemonBiosSetNowhp1banhikuiFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetLv1banhikuiFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetDefense1banhikuiFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetBadwazaHaveFlag(p, 0);
    fightTrainerEnemyPokemonBiosSetParam1bantakaiFlag(p, 0);
}

void fightTrainerEnemyPokemonInitFightStatus(FightTrainerEnemyPokemon* p) {
    u8 i;
    for (i = 0; i < 4; ++i) p->storeWaza[i] = 0;
    for (i = 0; i < 8; ++i) p->expectWaza[i] = 0;
    p->storeWazaNum = 0;
    p->expectWazaNum = 0;
    p->tokuseiFlag = 0;
    p->storeTokusei = 0;
}
}
