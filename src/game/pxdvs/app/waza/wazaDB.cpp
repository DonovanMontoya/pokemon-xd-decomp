#include <game/pxdvs/app/waza/wazaLayout.hpp>
#pragma dont_inline on
extern "C" {
void fightWaza_SetAutoMakeFlag(FightWazaRecord* data, u8 value) { if (data) data->autoMakeFlag = value; }

void fightWaza_SetKaisuu(FightWazaRecord* data, u8 value) { if (data) data->kaisuu = value; }

void fightWaza_SetZokusei(FightWazaRecord* data, u16 value) { if (data) data->zokusei = value; }

void fightWaza_SetIryoku(FightWazaRecord* data, u16 value) { if (data) data->iryoku = value; }

void fightWaza_SetHitDamage(FightWazaRecord* data, u32 value) { if (data) data->hitDamage = value; }

void fightWaza_SetDamage(FightWazaRecord* data, u32 value) { if (data) data->damage = value; }

void fightWaza_SetDamageValue(FightWazaRecord* data, u8 value) { if (data) data->damageValue = value; }

void fightWaza_SetCritical(FightWazaRecord* data, u8 value) { if (data) data->critical = value; }

void fightWaza_SetTargetDataId(FightWazaRecord* data, u16 value) { if (data) data->targetDataId = value; }

void fightWaza_SetUseWazaDataId(FightWazaRecord* data, u16 value) { if (data) data->useWazaDataId = value; }

void fightWaza_SetMotoWazaDataId(FightWazaRecord* data, u16 value) { if (data) data->motoWazaDataId = value; }

void fightWaza_SetWazaBanme(FightWazaRecord* data, u8 value) { if (data) data->wazaBanme = value; }

u8 fightWaza_GetAutoMakeFlag(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->autoMakeFlag; } }

u8 fightWaza_GetKaisuu(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->kaisuu; } }

u16 fightWaza_GetZokusei(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->zokusei; } }

u16 fightWaza_GetIryoku(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->iryoku; } }

u32 fightWaza_GetHitDamage(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->hitDamage; } }

u32 fightWaza_GetDamage(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->damage; } }

u8 fightWaza_GetDamageValue(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->damageValue; } }

u8 fightWaza_GetCritical(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->critical; } }

WazaStatusRecord* fightWaza_GetJoutaiPtr(FightWazaRecord* data, u16 index) { if (!data) return 0; if (index >= 9) return 0; return &data->statuses[index]; }

u16 fightWaza_GetTargetDataId(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->targetDataId; } }

u16 fightWaza_GetUseWazaDataId(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->useWazaDataId; } }

u16 fightWaza_GetMotoWazaDataId(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->motoWazaDataId; } }

u8 fightWaza_GetWazaBanme(FightWazaRecord* data) { if (data == 0) { return 0; } else { return data->wazaBanme; } }

void* wazaDB_GetFightWazaWzxVariationFuncPtr(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { WazaFunctionRecord* functions = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data)); if (functions == 0) { return 0; } else { return functions->fightWazaWzxVariation; } } }

void* wazaDB_GetFightWazaWzxTypeFuncPtr(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { WazaFunctionRecord* functions = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data)); if (functions == 0) { return 0; } else { return functions->fightWazaWzxType; } } }

void* wazaDB_GetFightTrainerAiWazaDamageFightPokemonFuncPtr(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { WazaFunctionRecord* functions = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data)); if (functions == 0) { return 0; } else { return functions->fightTrainerAiWazaDamageFightPokemon; } } }

void* wazaDB_GetFightTrainerAiWazaDamageFuncPtr(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { WazaFunctionRecord* functions = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data)); if (functions == 0) { return 0; } else { return functions->fightTrainerAiWazaDamage; } } }

void* wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { WazaFunctionRecord* functions = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data)); if (functions == 0) { return 0; } else { return functions->fightTrainerAiWazaHit; } } }

void* wazaDB_GetFightTrainerAiWazaValueFuncPtr(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { WazaFunctionRecord* functions = wazaFuncDataBiosGetPtr(wazaDataBiosGetWazaFuncDataId(data)); if (functions == 0) { return 0; } else { return functions->fightTrainerAiWazaValue; } } }

u8 wazaDB_GetCompatible(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->compatible; } }

u32 wazaDB_GetWazawzxdataId(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->wazawzxdataId; } }

u8 wazaDB_GetRiskFlag(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->riskFlag; } }

u8 wazaDB_GetTypeId(u16 identifier, u16 index) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (!data) return 0; if (index >= 3) return 0; return data->typeId[index]; }

u8 wazaDB_GetHidenFlag(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->hidenFlag; } }

u8 wazaDB_GetBouon(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->bouon; } }

u8 wazaDB_GetOujanosirusi(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->oujanosirusi; } }

u8 wazaDB_GetOumugaesi(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->oumugaesi; } }

u8 wazaDB_GetYokodori(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->yokodori; } }

u8 wazaDB_GetMajikku(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->majikku; } }

u8 wazaDB_GetMamoru(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->mamoru; } }

u8 wazaDB_GetDageki(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->dageki; } }

u8 wazaDB_GetAddFightKoukaAvg(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->addFightKoukaAvg; } }

u16 wazaDB_GetSeqId(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->seqId; } }

s16 wazaDB_GetIryoku(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->iryoku; } }

u8 wazaDB_GetAvg(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->avg; } }

u8 wazaDB_GetRangeId(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->rangeId; } }

s8 wazaDB_GetPri(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->pri; } }

u8 waza_GetZokuseiKindData(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (!data) return 0; if (wazaCheckDarkWaza(identifier) == 1) { WazaDataRecord* dark = wazaDataBiosGetPtr(identifier); if (dark == 0) { return 0; } else { return dark->darkKind; } } return zokuseiBiosGetWazaKind(data->zokuseiDataId); }

u8 wazaDB_GetZokuseiDataId(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->zokuseiDataId; } }

u8 wazaDB_GetPp(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->pp; } }

u32 wazaDB_GetName(u16 identifier) { WazaDataRecord* data = wazaDataBiosGetPtr(identifier); if (data == 0) { return 0; } else { return data->name; } }
}
