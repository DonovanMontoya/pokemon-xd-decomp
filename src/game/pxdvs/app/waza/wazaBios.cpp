#include <game/pxdvs/app/waza/wazaLayout.hpp>
#pragma dont_inline on
extern "C" {
void wazaDataBiosSetFightWazaWzxVariationFuncPtr(WazaDataRecord* data, void* callback) { if (!data) return; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (functions) functions->fightWazaWzxVariation = callback; }

void wazaDataBiosSetFightWazaWzxTypeFuncPtr(WazaDataRecord* data, void* callback) { if (!data) return; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (functions) functions->fightWazaWzxType = callback; }

void* wazaDataBiosGetFightWazaWzxVariationFuncPtr(WazaDataRecord* data) { if (!data) return 0; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (!functions) return 0; return functions->fightWazaWzxVariation; }

void* wazaDataBiosGetFightWazaWzxTypeFuncPtr(WazaDataRecord* data) { if (!data) return 0; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (!functions) return 0; return functions->fightWazaWzxType; }

void wazaDataBiosSetFightTrainerAiWazaDamageFuncPtr(WazaDataRecord* data, void* callback) { if (!data) return; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (functions) functions->fightTrainerAiWazaDamage = callback; }

void wazaDataBiosSetFightTrainerAiWazaHitFuncPtr(WazaDataRecord* data, void* callback) { if (!data) return; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (functions) functions->fightTrainerAiWazaHit = callback; }

void wazaDataBiosSetFightTrainerAiWazaValueFuncPtr(WazaDataRecord* data, void* callback) { if (!data) return; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (functions) functions->fightTrainerAiWazaValue = callback; }

void wazaDataBiosSetRiskFlag(WazaDataRecord* data, u8 value) { if (data) data->riskFlag = value; }

void wazaDataBiosSetTypeId(WazaDataRecord* data, u16 index, u8 value) { if (!data) return; if (index >= 3) return; data->typeId[index] = value; }

void* wazaDataBiosGetFightTrainerAiWazaDamageFuncPtr(WazaDataRecord* data) { if (!data) return 0; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (!functions) return 0; return functions->fightTrainerAiWazaDamage; }

void* wazaDataBiosGetFightTrainerAiWazaHitFuncPtr(WazaDataRecord* data) { if (!data) return 0; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (!functions) return 0; return functions->fightTrainerAiWazaHit; }

void* wazaDataBiosGetFightTrainerAiWazaValueFuncPtr(WazaDataRecord* data) { if (!data) return 0; u16 identifier; if (data == 0) { identifier = 0; } else { identifier = data->wazaFuncDataId; } WazaFunctionRecord* functions; if (identifier >= waza_func_data_number) functions = 0; else functions = &waza_func_data[identifier]; if (!functions) return 0; return functions->fightTrainerAiWazaValue; }

u16 wazaDataBiosGetWazaFuncDataId(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->wazaFuncDataId; } }

u8 wazaDataBiosGetRiskFlag(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->riskFlag; } }

u8 wazaDataBiosGetTypeId(WazaDataRecord* data, u16 index) { if (!data) return 0; if (index >= 3) return 0; return data->typeId[index]; }

void wazaDataBiosSetHidenFlag(WazaDataRecord* data, u8 value) { if (data) data->hidenFlag = value; }

u8 wazaDataBiosGetHidenFlag(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->hidenFlag; } }

void wazaDataBiosSetDoc(WazaDataRecord* data, u32 value) { if (data) data->doc = value; }

void wazaDataBiosSetWazawzxdataId(WazaDataRecord* data, u32 value) { if (data) data->wazawzxdataId = value; }

void wazaDataBiosSetPressure(WazaDataRecord* data, u8 value) { if (data) data->pressure = value; }

void wazaDataBiosSetBouon(WazaDataRecord* data, u8 value) { if (data) data->bouon = value; }

void wazaDataBiosSetNegoto(WazaDataRecord* data, u8 value) { if (data) data->negoto = value; }

void wazaDataBiosSetNekonote(WazaDataRecord* data, u8 value) { if (data) data->nekonote = value; }

void wazaDataBiosSetMonomane(WazaDataRecord* data, u8 value) { if (data) data->monomane = value; }

void wazaDataBiosSetYubiwohuru(WazaDataRecord* data, u8 value) { if (data) data->yubiwohuru = value; }

void wazaDataBiosSetOujanosirusi(WazaDataRecord* data, u8 value) { if (data) data->oujanosirusi = value; }

void wazaDataBiosSetOumugaesi(WazaDataRecord* data, u8 value) { if (data) data->oumugaesi = value; }

void wazaDataBiosSetYokodori(WazaDataRecord* data, u8 value) { if (data) data->yokodori = value; }

void wazaDataBiosSetMajikku(WazaDataRecord* data, u8 value) { if (data) data->majikku = value; }

void wazaDataBiosSetMamoru(WazaDataRecord* data, u8 value) { if (data) data->mamoru = value; }

void wazaDataBiosSetDageki(WazaDataRecord* data, u8 value) { if (data) data->dageki = value; }

void wazaDataBiosSetAddFightKoukaAvg(WazaDataRecord* data, u8 value) { if (data) data->addFightKoukaAvg = value; }

void wazaDataBiosSetFightAttackMsgId(WazaDataRecord* data, u32 value) { if (data) data->fightAttackMsgId = value; }

void wazaDataBiosSetFightAttackTunagiMsgId(WazaDataRecord* data, u32 value) { if (data) data->fightAttackTunagiMsgId = value; }

void wazaDataBiosSetSeqId(WazaDataRecord* data, u16 value) { if (data) data->seqId = value; }

void wazaDataBiosSetFightKoukaDataId(WazaDataRecord* data, u16 value) { if (data) data->fightKoukaDataId = value; }

void wazaDataBiosSetIryoku(WazaDataRecord* data, s16 value) { if (data) data->iryoku = value; }

void wazaDataBiosSetAvg(WazaDataRecord* data, u8 value) { if (data) data->avg = value; }

void wazaDataBiosSetRangeId(WazaDataRecord* data, u8 value) { if (data) data->rangeId = value; }

void wazaDataBiosSetPri(WazaDataRecord* data, s8 value) { if (data) data->pri = value; }

void wazaDataBiosSetZokuseiDataId(WazaDataRecord* data, u8 value) { if (data) data->zokuseiDataId = value; }

void wazaDataBiosSetPp(WazaDataRecord* data, u8 value) { if (data) data->pp = value; }

void wazaDataBiosSetName(WazaDataRecord* data, u32 value) { if (data) data->name = value; }

u32 wazaDataBiosGetDoc(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->doc; } }

u32 wazaDataBiosGetWazawzxdataId(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->wazawzxdataId; } }

u8 wazaDataBiosGetPressure(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->pressure; } }

u8 wazaDataBiosGetBouon(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->bouon; } }

u8 wazaDataBiosGetNegoto(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->negoto; } }

u8 wazaDataBiosGetNekonote(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->nekonote; } }

u8 wazaDataBiosGetMonomane(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->monomane; } }

u8 wazaDataBiosGetYubiwohuru(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->yubiwohuru; } }

u8 wazaDataBiosGetOujanosirusi(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->oujanosirusi; } }

u8 wazaDataBiosGetOumugaesi(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->oumugaesi; } }

u8 wazaDataBiosGetYokodori(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->yokodori; } }

u8 wazaDataBiosGetMajikku(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->majikku; } }

u8 wazaDataBiosGetMamoru(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->mamoru; } }

u8 wazaDataBiosGetDageki(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->dageki; } }

u8 wazaDataBiosGetAddFightKoukaAvg(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->addFightKoukaAvg; } }

u32 wazaDataBiosGetFightAttackMsgId(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->fightAttackMsgId; } }

u32 wazaDataBiosGetFightAttackTunagiMsgId(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->fightAttackTunagiMsgId; } }

u16 wazaDataBiosGetSeqId(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->seqId; } }

u16 wazaDataBiosGetFightKoukaDataId(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->fightKoukaDataId; } }

s16 wazaDataBiosGetIryoku(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->iryoku; } }

u8 wazaDataBiosGetAvg(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->avg; } }

u8 wazaDataBiosGetRangeId(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->rangeId; } }

s8 wazaDataBiosGetPri(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->pri; } }

u8 wazaDataBiosGetZokuseiDataId(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->zokuseiDataId; } }

u8 wazaDataBiosGetPp(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->pp; } }

u32 wazaDataBiosGetName(WazaDataRecord* data) { if (data == 0) { return 0; } else { return data->name; } }

WazaDataRecord* wazaDataBiosGetPtr(u32 identifier) { u16 index = identifier; if (index >= *waza_data_number) return waza_data; return &waza_data[index]; }

WazaFunctionRecord* wazaFuncDataBiosGetPtr(u16 identifier) { if (identifier >= waza_func_data_number) return 0; return &waza_func_data[identifier]; }
}
