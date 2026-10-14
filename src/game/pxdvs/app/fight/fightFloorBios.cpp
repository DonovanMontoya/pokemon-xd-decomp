#include <game/pxdvs/app/fight/fightFloorDBLayout.hpp>
#pragma dont_inline on
extern "C" {
extern u32 encount_floor_id;
extern FIGHT_FLOOR fight_floor;
extern FloorData* fight_floor_data;
extern u32* fight_floor_data_number;

void fightFloorBiosSetEncountFloorId(u32 value) { encount_floor_id = value; }

u32 fightFloorBiosGetEncountFloorId() { return encount_floor_id; }

void fightFloorBiosSetItemPokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->itemPokemonPtr = value;
}

void* fightFloorBiosGetItemPokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->itemPokemonPtr; }
}

void fightFloorBiosSetTokuseiPokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->tokuseiPokemonPtr = value;
}

void* fightFloorBiosGetTokuseiPokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->tokuseiPokemonPtr; }
}

void fightFloorBiosSetTuikakoukaPokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->tuikakoukaPokemonPtr = value;
}

void* fightFloorBiosGetTuikakoukaPokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->tuikakoukaPokemonPtr; }
}

void fightFloorBiosSetKizetuPokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->kizetuPokemonPtr = value;
}

void* fightFloorBiosGetKizetuPokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->kizetuPokemonPtr; }
}

void fightFloorBiosSetFirstAttackRnd(FIGHT_FLOOR* object, u16 value) {
    if (object) object->firstAttackRnd = value;
}

u16 fightFloorBiosGetFirstAttackRnd(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->firstAttackRnd; }
}

void fightFloorBiosSetFightOutPokemonPtrAryPtr(FIGHT_FLOOR* floor, void** pokemon) {
    if (floor) for (u16 i = 0; i < 8; ++i) floor->fightOutPokemon[i] = pokemon[i];
}

void** fightFloorBiosGetFightOutPokemonPtrAryPtr(FIGHT_FLOOR* floor) { if (floor == 0) { return 0; } else { return floor->fightOutPokemon; } }

void fightFloorBiosSetFightOutPokemonPtrAry(FIGHT_FLOOR* floor, u16 index, void* pokemon) { if (floor && index < 8) floor->fightOutPokemon[index] = pokemon; }

void* fightFloorBiosGetFightOutPokemonPtrAry(FIGHT_FLOOR* floor, u16 index) {
    if (!floor) return 0;
    if (index >= 8) return 0;
    return floor->fightOutPokemon[index];
}

void fightFloorBiosSetFightPokemonEntryCnt(FIGHT_FLOOR* object, s16 value) {
    if (object) object->fightPokemonEntryCnt = value;
}

s16 fightFloorBiosGetFightPokemonEntryCnt(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->fightPokemonEntryCnt; }
}

void fightFloorDataBiosSetName(FloorData* object, u32 value) {
    if (object) object->name = value;
}

u32 fightFloorDataBiosGetName(FloorData* object) {
    if (object == 0) { return 0; } else { return object->name; }
}

void fightFloorDataBiosSetEnvSndId(FloorData* object, u32 value) {
    if (object) object->environmentSound = value;
}

void fightFloorDataBiosSetBgmSndId(FloorData* object, u32 value) {
    if (object) object->bgm = value;
}

void fightFloorDataBiosSetSyoukaiWzxDataId(FloorData* object, u32 value) {
    if (object) object->introSequence = value;
}

void fightFloorDataBiosSetTikeiDataId(FloorData* data, u8 value) { if (data) data->terrain = value; }

void fightFloorDataBiosSetFightSideDataId(FloorData* data, u8 side, u16 value) { if (data && side < 2) data->sides[side] = value; }

void fightFloorDataBiosSetFloorDataId(FloorData* object, u16 value) {
    if (object) object->floor = value;
}

u32 fightFloorDataBiosGetEnvSndId(FloorData* object) {
    if (object == 0) { return 0; } else { return object->environmentSound; }
}

u32 fightFloorDataBiosGetBgmSndId(FloorData* object) {
    if (object == 0) { return 0; } else { return object->bgm; }
}

u32 fightFloorDataBiosGetSyoukaiWzxDataId(FloorData* object) {
    if (object == 0) { return 0; } else { return object->introSequence; }
}

u8 fightFloorDataBiosGetTikeiDataId(FloorData* data) { if (data == 0) { return 0; } else { return data->terrain; } }

u16 fightFloorDataBiosGetFightSideDataId(FloorData* data, u8 side) {
    if (!data) return 0;
    if (side >= 2) return 0;
    return data->sides[side];
}

u16 fightFloorDataBiosGetFloorDataId(FloorData* object) {
    if (object == 0) { return 0; } else { return object->floor; }
}

FloorData* fightFloorDataBiosGetPtr(u16 index) {
    if (index >= *fight_floor_data_number) return 0;
    return fight_floor_data + index;
}

void fightFloorBiosSetAppointTokuseiDataId(FIGHT_FLOOR* object, u16 value) {
    if (object) object->appointTokuseiDataId = value;
}

void fightFloorBiosSetAppointItemDataId(FIGHT_FLOOR* object, u16 value) {
    if (object) object->appointItemDataId = value;
}

void fightFloorBiosSetAppointWazaDataId(FIGHT_FLOOR* object, u16 value) {
    if (object) object->appointWazaDataId = value;
}

void fightFloorBiosSetAppointPokemonDataId(FIGHT_FLOOR* object, u16 value) {
    if (object) object->appointPokemonDataId = value;
}

void fightFloorBiosSetWazakoukaMsgId(FIGHT_FLOOR* object, u32 value) {
    if (object) object->wazaEffectMsgId = value;
}

void fightFloorBiosSetCriticalMsgId(FIGHT_FLOOR* object, u32 value) {
    if (object) object->criticalMsgId = value;
}

void fightFloorBiosSetAttackMsgId(FIGHT_FLOOR* object, u32 value) {
    if (object) object->attackMsgId = value;
}

void fightFloorBiosSetAppointMsgId(FIGHT_FLOOR* object, s32 value) {
    if (object) object->appointMsgId = value;
}

void fightFloorBiosSetAppointItemPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->appointItemPtr = value;
}

void fightFloorBiosSetAppointSidePtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->appointSidePtr = value;
}

void fightFloorBiosSetAppointWazaPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->appointWazaPtr = value;
}

void fightFloorBiosSetAppointTrainerPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->appointTrainerPtr = value;
}

void fightFloorBiosSetAppointPokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->appointPokemonPtr = value;
}

void fightFloorBiosSetIrekaePokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->irekaePokemonPtr = value;
}

void fightFloorBiosSetEscapePokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->escapePokemonPtr = value;
}

void fightFloorBiosSetDefensePokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->defensePokemonPtr = value;
}

void fightFloorBiosSetAttackPokemonPtr(FIGHT_FLOOR* object, void* value) {
    if (object) object->attackPokemonPtr = value;
}

void fightFloorBiosSetEncountDataId(FIGHT_FLOOR* object, u16 value) {
    if (object) object->encountDataId = value;
}

void fightFloorBiosSetTurnCount(FIGHT_FLOOR* object, u16 value) {
    if (object) object->turnCount = value;
}

u16 fightFloorBiosGetAppointTokuseiDataId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointTokuseiDataId; }
}

u16 fightFloorBiosGetAppointItemDataId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointItemDataId; }
}

u16 fightFloorBiosGetAppointWazaDataId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointWazaDataId; }
}

u16 fightFloorBiosGetAppointPokemonDataId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointPokemonDataId; }
}

u32 fightFloorBiosGetWazakoukaMsgId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->wazaEffectMsgId; }
}

u32 fightFloorBiosGetCriticalMsgId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->criticalMsgId; }
}

u32 fightFloorBiosGetAttackMsgId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->attackMsgId; }
}

s32 fightFloorBiosGetAppointMsgId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointMsgId; }
}

void* fightFloorBiosGetAppointItemPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointItemPtr; }
}

void* fightFloorBiosGetAppointSidePtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointSidePtr; }
}

void* fightFloorBiosGetAppointWazaPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointWazaPtr; }
}

void* fightFloorBiosGetAppointTrainerPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointTrainerPtr; }
}

void* fightFloorBiosGetAppointPokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->appointPokemonPtr; }
}

void* fightFloorBiosGetIrekaePokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->irekaePokemonPtr; }
}

void* fightFloorBiosGetEscapePokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->escapePokemonPtr; }
}

void* fightFloorBiosGetDefensePokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->defensePokemonPtr; }
}

void* fightFloorBiosGetAttackPokemonPtr(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->attackPokemonPtr; }
}

FightSide* fightFloorBiosGetFightSidePtr(FIGHT_FLOOR* floor, u16 side) {
    if (!floor) return 0;
    if (side >= 2) return 0;
    return (FightSide*)((u8*)floor + 0x14 + side * 0x6ef0);
}

u16 fightFloorBiosGetEncountDataId(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->encountDataId; }
}

u16 fightFloorBiosGetTurnCount(FIGHT_FLOOR* object) {
    if (object == 0) { return 0; } else { return object->turnCount; }
}

void* fightFloorBiosGetJoutaiPtr(FIGHT_FLOOR* floor, u16 condition) {
    if (!floor) return 0;
    if (condition >= 1) return 0;
    return (u8*)floor + condition * 0x10;
}

FIGHT_FLOOR* fightFloorBiosGetFightFloorPtr() { return &fight_floor; }
}
