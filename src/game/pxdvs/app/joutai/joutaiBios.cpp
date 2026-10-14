#include <game/pxdvs/app/joutai/joutaiDataLayout.hpp>
#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>
#pragma dont_inline on
extern "C" {
u8 joutaiDataBiosGetKaisuuDataId(u16 identifier) { JoutaiDataRecord* data = joutaiDataBiosGetDataPtr(identifier); if (data == 0) { return 0; } else { return data->kaisuuDataId; } }

u8 joutaiDataBiosGetMaxCount(u16 identifier) { JoutaiDataRecord* data = joutaiDataBiosGetDataPtr(identifier); if (data == 0) { return 0; } else { return data->maxCount; } }

u16 joutaiDataBiosGetSameJoutai(u16 identifier) { JoutaiDataRecord* data = joutaiDataBiosGetDataPtr(identifier); if (data == 0) { return 0; } else { return data->sameJoutai; } }

u8 joutaiDataBiosGetWriteMode(u16 identifier) { JoutaiDataRecord* data = joutaiDataBiosGetDataPtr(identifier); if (data == 0) { return 0; } else { return data->writeMode; } }

u8 joutaiDataBiosGetUseBanme(u16 identifier) { JoutaiDataRecord* data = joutaiDataBiosGetDataPtr(identifier); if (data == 0) { return 0; } else { return data->useBanme; } }

u16 joutaiDataBiosGetStatus(u16 identifier) { JoutaiDataRecord* data = joutaiDataBiosGetDataPtr(identifier); if (data == 0) { return 0; } else { return data->status; } }

u8 joutaiDataBiosGetStatusKind(u16 identifier) { JoutaiDataRecord* data = joutaiDataBiosGetDataPtr(identifier); if (data == 0) { return 0; } else { return data->statusKind; } }

u32 joutaiDataBiosGetName(u16 identifier) { JoutaiDataRecord* data = joutaiDataBiosGetDataPtr(identifier); if (data == 0) { return 0; } else { return data->name; } }

JoutaiDataRecord* joutaiDataBiosGetDataPtr(u16 identifier) { if (identifier >= joutai_data_number) return 0; return &joutai_data[identifier]; }

void joutaiBiosSetIdBuff(FightJoutai* data, u16 value) { if (data) data->idBuff = value; }

void joutaiBiosSetBuff(FightJoutai* data, u32 value) { if (data) data->buff = value; }

void joutaiBiosSetNowKaisuu(FightJoutai* data, u8 value) { if (data) data->nowKaisuu = value; }

u16 joutaiBiosGetIdBuff(FightJoutai* data) { if (data == 0) { return 0; } else { return data->idBuff; } }

u32 joutaiBiosGetBuff(FightJoutai* data) { if (data == 0) { return 0; } else { return data->buff; } }

u8 joutaiBiosGetCount(FightJoutai* data) { if (data == 0) { return 0; } else { return data->count; } }

u8 joutaiBiosGetNowKaisuu(FightJoutai* data) { if (data == 0) { return 0; } else { return data->nowKaisuu; } }

u8 joutaiBiosGetKaisuu(FightJoutai* data) { if (data == 0) { return 0; } else { return data->kaisuu; } }

u16 joutaiBiosGetUserFightTargetId(FightJoutai* data) { if (data == 0) { return 0; } else { return data->userFightTargetId; } }

u16 joutaiBiosGetJoutaiDataId(FightJoutai* data) { if (data == 0) { return 0; } else { return data->dataId; } }
}
