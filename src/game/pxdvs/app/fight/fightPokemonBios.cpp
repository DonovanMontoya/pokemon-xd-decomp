#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>

#include <libc/stddef.h>
#pragma dont_inline on
struct FightEnemyBiosLayout {
    FightOutPokemon* target;
    u16 oumuWazaDataId, initHp, damage, reserved0A;
};
typedef char EnemyBiosSize[sizeof(FightEnemyBiosLayout) == sizeof(FightOutPokemonEnemy) ? 1 : -1];
typedef char HensinMotoOffset[offsetof(FightOutPokemon, hensinMotoPkxId) == 0x7b8 ? 1 : -1];

extern "C" {
FightOutPokemon* __as__15FightOutPokemonFRC15FightOutPokemon(FightOutPokemon*, const FightOutPokemon*);
void fightOutPokemonBiosCopy(FightOutPokemon* target, const FightOutPokemon* source) {
    if (target && source) __as__15FightOutPokemonFRC15FightOutPokemon(target, source);
}


void fightOutPokemonBiosSetOumuWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->oumuWazaDataId = value;
}

void fightOutPokemonBiosSetGamanDamageTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->gamanDamageTargetId = value;
}

void fightOutPokemonBiosSetGamanDamageValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->gamanDamageValue = value;
}

void fightOutPokemonBiosSetHitWazaZokuseiDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->hitWazaZokuseiDataId = value;
}

void fightOutPokemonBiosSetHitWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->hitWazaDataId = value;
}

void fightOutPokemonBiosSetLastReceiveWazaTargetDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->lastReceiveWazaTargetDataId = value;
}

void fightOutPokemonBiosSetLastUseWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->lastUseWazaDataId = value;
}

void fightOutPokemonBiosSetLastSelectWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->lastSelectWazaDataId = value;
}

void fightOutPokemonBiosSetSketchWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->sketchWazaDataId = value;
}

FightWaza* fightOutPokemonBiosGetKeepFightWazaPtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return nullptr; } else { return &poke->keepFightWaza; }
}

u16 fightOutPokemonBiosGetOumuWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->oumuWazaDataId; }
}

u16 fightOutPokemonBiosGetGamanDamageTargetId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->gamanDamageTargetId; }
}

int fightOutPokemonBiosGetGamanDamageValue(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->gamanDamageValue; }
}

u16 fightOutPokemonBiosGetHitWazaZokuseiDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 9; } else { return poke->hitWazaZokuseiDataId; }
}

u16 fightOutPokemonBiosGetHitWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->hitWazaDataId; }
}

u16 fightOutPokemonBiosGetLastReceiveWazaTargetDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->lastReceiveWazaTargetDataId; }
}

u16 fightOutPokemonBiosGetLastUseWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->lastUseWazaDataId; }
}

u16 fightOutPokemonBiosGetLastSelectWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->lastSelectWazaDataId; }
}

u16 fightOutPokemonBiosGetSketchWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->sketchWazaDataId; }
}

FightOutPokemonEnemy* fightOutPokemonBiosGetFightOutPokemonEnemyPtr(FightOutPokemon* poke,u16 index) {
    if (poke == nullptr) return nullptr;
    if (index >= 4) return nullptr;
    return &poke->enemy[index];
}

void fightOutPokemonBiosSetIrekaeTargetEntryId(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->irekaeTargetEntryId = value;
}

int fightOutPokemonBiosGetIrekaeTargetEntryId(FightOutPokemon* poke) {
    if (poke == nullptr) { return -1; } else { return poke->irekaeTargetEntryId; }
}

void fightOutPokemonBiosSetKizetuFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->kizetuFlag = value;
}

u8 fightOutPokemonBiosGetKizetuFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->kizetuFlag; }
}

void fightOutPokemonBiosSetMyselfDamageSpeTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->myselfDamageSpeTargetId = value;
}

void fightOutPokemonBiosSetMyselfDamageSpeValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->myselfDamageSpeValue = value;
}

void fightOutPokemonBiosSetMyselfDamageAtkTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->myselfDamageAtkTargetId = value;
}

void fightOutPokemonBiosSetMyselfDamageAtkValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->myselfDamageAtkValue = value;
}

void fightOutPokemonBiosSetKaigaraDamageValue(FightOutPokemon* poke, s32 value) {
    if (poke != nullptr) poke->kaigaraDamageValue = value;
}

void fightOutPokemonBiosSetItemKoraetaFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->itemKoraetaFlag = value;
}

void fightOutPokemonBiosSetIrekaetaFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->irekaetaFlag = value;
}

void fightOutPokemonBiosSetNoPressureFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->noPressureFlag = value;
}

void fightOutPokemonBiosSetDoTraceFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->doTraceFlag = value;
}

void fightOutPokemonBiosSetDoIkakuFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->doIkakuFlag = value;
}

void fightOutPokemonBiosSetVanishoffFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->vanishoffFlag = value;
}

void fightOutPokemonBiosSetReceivesWazaHiraishinFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->receivesWazaHiraishinFlag = value;
}

void fightOutPokemonBiosSetDoClearbodyFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->doClearbodyFlag = value;
}

void fightOutPokemonBiosSetFightActionFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->fightActionFlag = value;
}

void fightOutPokemonBiosSetPassPpdecFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->passPpdecFlag = value;
}

void fightOutPokemonBiosSetHirumuNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->hirumuNoAttackFlag = value;
}

void fightOutPokemonBiosSetIchamonNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->ichamonNoAttackFlag = value;
}

void fightOutPokemonBiosSetChouhatsuNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->chouhatsuNoAttackFlag = value;
}

void fightOutPokemonBiosSetKanashibariNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->kanashibariNoAttackFlag = value;
}

void fightOutPokemonBiosSetMeroMeroNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->meroMeroNoAttackFlag = value;
}

void fightOutPokemonBiosSetHuuinNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->huuinNoAttackFlag = value;
}

void fightOutPokemonBiosSetItemNigeruFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->itemNigeruFlag = value;
}

void fightOutPokemonBiosSetTameWazaFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->tameWazaFlag = value;
}

void fightOutPokemonBiosSetOutWazaKoukanaiFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->outWazaKoukanaiFlag = value;
}

void fightOutPokemonBiosSetKonranMyselfAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->konranMyselfAttackFlag = value;
}

void fightOutPokemonBiosSetMahiNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->mahiNoAttackFlag = value;
}

int fightOutPokemonBiosGetMyselfDamageSpeValue(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->myselfDamageSpeValue; }
}

int fightOutPokemonBiosGetMyselfDamageAtkValue(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->myselfDamageAtkValue; }
}

s32 fightOutPokemonBiosGetKaigaraDamageValue(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->kaigaraDamageValue; }
}

u8 fightOutPokemonBiosGetItemKoraetaFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->itemKoraetaFlag; }
}

u8 fightOutPokemonBiosGetIrekaetaFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->irekaetaFlag; }
}

u8 fightOutPokemonBiosGetNoPressureFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->noPressureFlag; }
}

u8 fightOutPokemonBiosGetDoTraceFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->doTraceFlag; }
}

u8 fightOutPokemonBiosGetDoIkakuFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->doIkakuFlag; }
}

u8 fightOutPokemonBiosGetVanishoffFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->vanishoffFlag; }
}

u8 fightOutPokemonBiosGetReceivesWazaHiraishinFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->receivesWazaHiraishinFlag; }
}

u8 fightOutPokemonBiosGetDoClearbodyFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->doClearbodyFlag; }
}

u8 fightOutPokemonBiosGetFightActionFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->fightActionFlag; }
}

u8 fightOutPokemonBiosGetPassPpdecFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->passPpdecFlag; }
}

u8 fightOutPokemonBiosGetTameWazaFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->tameWazaFlag; }
}

u8 fightOutPokemonBiosGetKonranMyselfAttackFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->konranMyselfAttackFlag; }
}

u32* fightOutPokemonBiosGetWazaMenuCurPtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return nullptr; } else { return &poke->wazaMenuCur; }
}

void fightOutPokemonBiosSetTokuseiDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->tokuseiDataId = value;
}

u16 fightOutPokemonBiosGetTokuseiDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->tokuseiDataId; }
}

void fightOutPokemonBiosSetZokuseiDataId(FightOutPokemon* poke,u8 index,u16 value) {
    if (poke == nullptr) return;
    if (index >= 2) return;
    poke->zokuseiDataId[index] = value;
}

u16 fightOutPokemonBiosGetZokuseiDataId(FightOutPokemon* poke,u8 index) {
    if (poke == nullptr) return 0;
    if (index >= 2) return 0;
    return poke->zokuseiDataId[index];
}

FightActionBuff* fightOutPokemonBiosGetFightActionBuffPtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return nullptr; } else { return &poke->fightActionBuff; }
}

void fightOutPokemonBiosSetMeetEnemyFightPokemonEntryId(FightOutPokemon* poke,u8 index,s16 value) {
    if (poke == nullptr) return;
    if (index >= 12) return;
    poke->meetEnemyFightPokemonEntryId[index] = value;
}

int fightOutPokemonBiosGetMeetEnemyFightPokemonEntryId(FightOutPokemon* poke,u8 index) {
    if (poke == nullptr) return -1;
    if (index >= 12) return -1;
    return poke->meetEnemyFightPokemonEntryId[index];
}

void fightOutPokemonBiosSetDamageSpeTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->damageSpeTargetId = value;
}

void fightOutPokemonBiosSetDamageSpeValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->damageSpeValue = value;
}

void fightOutPokemonBiosSetDamageAtkTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->damageAtkTargetId = value;
}

void fightOutPokemonBiosSetDamageAtkValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->damageAtkValue = value;
}

void fightOutPokemonBiosSetSuccessCnt(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->successCnt = value;
}

void fightOutPokemonBiosSetStockItemDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->stockItemDataId = value;
}

void fightOutPokemonBiosSetUsedItemDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->usedItemDataId = value;
}

void fightOutPokemonBiosSetNamakeFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->namakeFlag = value;
}

u16 fightOutPokemonBiosGetDamageSpeTargetId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->damageSpeTargetId; }
}

int fightOutPokemonBiosGetDamageSpeValue(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->damageSpeValue; }
}

u16 fightOutPokemonBiosGetDamageAtkTargetId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->damageAtkTargetId; }
}

int fightOutPokemonBiosGetDamageAtkValue(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->damageAtkValue; }
}

u8 fightOutPokemonBiosGetSuccessCnt(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->successCnt; }
}

u16 fightOutPokemonBiosGetStockItemDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->stockItemDataId; }
}

u16 fightOutPokemonBiosGetUsedItemDataId(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->usedItemDataId; }
}

u8 fightOutPokemonBiosGetNamakeFlag(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->namakeFlag; }
}

void fightOutPokemonBiosSetSequencePtr(FightOutPokemon* poke, void* value) {
    if (poke != nullptr) poke->sequence = value;
}

void* fightOutPokemonBiosGetSequencePtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->sequence; }
}

void fightOutPokemonBiosSetFightoutTurnCount(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->fightoutTurnCount = value;
}

void fightOutPokemonBiosSetAbicntAverage(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->abicntAverage = value;
}

void fightOutPokemonBiosSetFightPokemonPtr(FightOutPokemon* poke, FightPokemon* value) {
    if (poke != nullptr) poke->fightPokemon = value;
}

void fightOutPokemonBiosSetMotoFightPokemonPtr(FightOutPokemon* poke, FightPokemon* value) {
    if (poke != nullptr) poke->motoFightPokemon = value;
}

void fightPokemonBiosSetHokakuFlag(FightPokemon* poke, u8 value) {
    if (poke != nullptr) poke->state.hokakuFlag = value;
}

u8 fightPokemonBiosGetHokakuFlag(FightPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->state.hokakuFlag; }
}

void fightPokemonBiosSetDarkOutFlag(FightPokemon* poke, u8 value) {
    if (poke != nullptr) poke->state.darkOutFlag = value;
}

void fightPokemonBiosSetLevelUpFlag(FightPokemon* poke, u8 value) {
    if (poke != nullptr) poke->state.levelUpFlag = value;
}

void fightPokemonBiosSetCatchEntryFlag(FightPokemon* poke, u8 value) {
    if (poke != nullptr) poke->state.catchEntryFlag = value;
}

void fightPokemonBiosSetEntryId(FightPokemon* poke, s16 value) {
    if (poke != nullptr) poke->state.entryId = value;
}

void fightPokemonBiosSetMotoPokemonPtr(FightPokemon* poke, Pokemon* value) {
    if (poke != nullptr) poke->motoPokemon = value;
}

u16 fightOutPokemonBiosGetFightoutTurnCount(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->fightoutTurnCount; }
}

u8 fightOutPokemonBiosGetAbicntAvoid(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->abicntAvoid; }
}

u8 fightOutPokemonBiosGetAbicntAverage(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->abicntAverage; }
}

u8 fightOutPokemonBiosGetAbicntNimbleness(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->abicntNimbleness; }
}

u8 fightOutPokemonBiosGetAbicntSpeDef(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->abicntSpeDef; }
}

u8 fightOutPokemonBiosGetAbicntSpeAtk(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->abicntSpeAtk; }
}

u8 fightOutPokemonBiosGetAbicntPhyDef(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->abicntPhyDef; }
}

u8 fightOutPokemonBiosGetAbicntPhyAtk(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->abicntPhyAtk; }
}

FightItem* fightOutPokemonBiosGetFightItemPtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return nullptr; } else { return &poke->fightItem; }
}

FightWaza* fightOutPokemonBiosGetFightWazaPtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return nullptr; } else { return &poke->fightWaza; }
}

FightJoutai* fightOutPokemonBiosGetFightoutJoutaiPtr(FightOutPokemon* poke,u16 index) {
    if (poke == nullptr) return nullptr;
    if (index >= 52) return nullptr;
    return &poke->joutai[index];
}

FightPokemon* fightOutPokemonBiosGetFightPokemonHensinBuffPtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return nullptr; } else { return &poke->fightPokemonHensinBuff; }
}

FightPokemon* fightOutPokemonBiosGetFightPokemonPtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->fightPokemon; }
}

FightPokemon* fightOutPokemonBiosGetMotoFightPokemonPtr(FightOutPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->motoFightPokemon; }
}

u8 fightPokemonBiosGetDarkOutFlag(FightPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->state.darkOutFlag; }
}

u8 fightPokemonBiosGetLevelUpFlag(FightPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->state.levelUpFlag; }
}

u8 fightPokemonBiosGetCatchEntryFlag(FightPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->state.catchEntryFlag; }
}

int fightPokemonBiosGetEntryId(FightPokemon* poke) {
    if (poke == nullptr) { return -1; } else { return poke->state.entryId; }
}

FightJoutai* fightPokemonBiosGetFightJoutaiPtr(FightPokemon* poke,u16 index) {
    if (poke == nullptr) return nullptr;
    if (index >= 1) return nullptr;
    return &poke->state.joutai[index];
}

Pokemon* fightPokemonBiosGetPokemonBuffPtr(FightPokemon* poke) {
    if (poke == nullptr) { return nullptr; } else { return &poke->pokemonBuff; }
}

Pokemon* fightPokemonBiosGetMotoPokemonPtr(FightPokemon* poke) {
    if (poke == nullptr) { return 0; } else { return poke->motoPokemon; }
}


void fightOutPokemonEnemyBiosSetDamage(FightOutPokemonEnemy* enemy, u16 value) { if (enemy) ((FightEnemyBiosLayout*)enemy)->damage = value; }

u16 fightOutPokemonEnemyBiosGetDamage(FightOutPokemonEnemy* enemy) { if (enemy == nullptr) { return 0; } else { return ((FightEnemyBiosLayout*)enemy)->damage; } }

void fightOutPokemonEnemyBiosSetInitHp(FightOutPokemonEnemy* enemy, u16 value) { if (enemy) ((FightEnemyBiosLayout*)enemy)->initHp = value; }

u16 fightOutPokemonEnemyBiosGetInitHp(FightOutPokemonEnemy* enemy) { if (enemy == nullptr) { return 0; } else { return ((FightEnemyBiosLayout*)enemy)->initHp; } }

void fightOutPokemonEnemyBiosSetOumuWazaDataId(FightOutPokemonEnemy* enemy, u16 value) { if (enemy) ((FightEnemyBiosLayout*)enemy)->oumuWazaDataId = value; }

u16 fightOutPokemonEnemyBiosGetOumuWazaDataId(FightOutPokemonEnemy* enemy) { if (enemy == nullptr) { return 0; } else { return ((FightEnemyBiosLayout*)enemy)->oumuWazaDataId; } }

void fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(FightOutPokemonEnemy* enemy, FightOutPokemon* value) { if (enemy) ((FightEnemyBiosLayout*)enemy)->target = value; }

FightOutPokemon* fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(FightOutPokemonEnemy* enemy) { if (enemy == nullptr) { return 0; } else { return ((FightEnemyBiosLayout*)enemy)->target; } }

u16 fightOutPokemonBiosGetMyselfDamageSpeTargetId(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->myselfDamageSpeTargetId; } }

u16 fightOutPokemonBiosGetMyselfDamageAtkTargetId(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->myselfDamageAtkTargetId; } }

u8 fightOutPokemonBiosGetHirumuNoAttackFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->hirumuNoAttackFlag; } }

u8 fightOutPokemonBiosGetIchamonNoAttackFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->ichamonNoAttackFlag; } }

u8 fightOutPokemonBiosGetChouhatsuNoAttackFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->chouhatsuNoAttackFlag; } }

u8 fightOutPokemonBiosGetKanashibariNoAttackFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->kanashibariNoAttackFlag; } }

u8 fightOutPokemonBiosGetMeroMeroNoAttackFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->meroMeroNoAttackFlag; } }

u8 fightOutPokemonBiosGetHuuinNoAttackFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->huuinNoAttackFlag; } }

u8 fightOutPokemonBiosGetItemNigeruFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->itemNigeruFlag; } }

u8 fightOutPokemonBiosGetOutWazaKoukanaiFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->outWazaKoukanaiFlag; } }

u8 fightOutPokemonBiosGetMahiNoAttackFlag(FightOutPokemon* poke) { if (poke == nullptr) { return 0; } else { return poke->mahiNoAttackFlag; } }

void fightOutPokemonBiosSetHensinMotoPkxId(FightOutPokemon* poke, u16 value) { if (poke) poke->hensinMotoPkxId = value; }

void fightOutPokemonBiosSetAbicntAvoid(FightOutPokemon* poke, u8 value) { if (poke) poke->abicntAvoid = value; }

void fightOutPokemonBiosSetAbicntNimbleness(FightOutPokemon* poke, u8 value) { if (poke) poke->abicntNimbleness = value; }

void fightOutPokemonBiosSetAbicntSpeDef(FightOutPokemon* poke, u8 value) { if (poke) poke->abicntSpeDef = value; }

void fightOutPokemonBiosSetAbicntSpeAtk(FightOutPokemon* poke, u8 value) { if (poke) poke->abicntSpeAtk = value; }

void fightOutPokemonBiosSetAbicntPhyDef(FightOutPokemon* poke, u8 value) { if (poke) poke->abicntPhyDef = value; }

void fightOutPokemonBiosSetAbicntPhyAtk(FightOutPokemon* poke, u8 value) { if (poke) poke->abicntPhyAtk = value; }
}
