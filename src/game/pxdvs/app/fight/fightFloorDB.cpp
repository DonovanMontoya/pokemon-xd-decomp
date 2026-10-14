#include <game/pxdvs/app/fight/fightFloorDBLayout.hpp>
#pragma dont_inline on
extern "C" {
struct AbilityData;
AbilityData* pokemonTokuseiDataBiosGetPtr(u32);
u32 pokemonTokuseiDataBiosGetName(AbilityData*);
u32 itemDB_GetName(u32);
void* GSmsgGetGSchar(u32);
void fightMsgctrlSetValue(u32, u32);
u8 fightOutPokemonCheckValid(FightOutPokemon*);
u32 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
u32 fightOutPokemonGetSoubiItemDataId(FightOutPokemon*);
void fightFloorBiosSetAppointTokuseiDataId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointItemDataId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetItemPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u32);
void pokemonBiosCopy(Pokemon*, const Pokemon*);
void* memcpy(void*, const void*, unsigned long);
void fightFloorBiosSetAppointPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetTuikakoukaPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetDefensePokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);
void fightFloorBiosSetAttackPokemonPtr(FIGHT_FLOOR*, FightOutPokemon*);

void fightFloorBiosSetFirstAttackRnd(FIGHT_FLOOR*, u32);
void fightFloorBiosSetFightOutPokemonPtrAryPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetFightPokemonEntryCnt(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointWazaDataId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointPokemonDataId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetWazakoukaMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetCriticalMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAttackMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetEncountFloorId(u32);
void fightFloorBiosSetTokuseiPokemonPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetKizetuPokemonPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetIrekaePokemonPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetEscapePokemonPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetEncountDataId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetTurnCount(FIGHT_FLOOR*, u32);
u32 fightFloorBiosGetEncountFloorId(FIGHT_FLOOR*);
u32 fightFloorIsJoutaiDataId(FIGHT_FLOOR*, u16);
FightOutPokemon* fightFloorBiosGetAttackPokemonPtr(FIGHT_FLOOR*);
void fightOutPokemon_SetWazaTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaJoutaiDataId(FightOutPokemon*, u16);

FightEncountData* fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetFightFloorDataId(FightEncountData*);
u32 fightEncountDataBiosGetTrainer(FightEncountData*);
u8 fightEncountDataBiosGetFightType(FightEncountData*);
u8 fightEncountDataBiosGetFightKind(FightEncountData*);
FightKindData* fightKindDataBiosGetPtr(u16);
FightTypeData* fightTypeDataBiosGetPtr(u16);
u8 fightFloor_GetFightKind(FIGHT_FLOOR*);
u8 fightFloor_GetFightType(FIGHT_FLOOR*);
u16 fightFloor_GetFightFloorDataId(FIGHT_FLOOR*);
u32 fightKindDataBiosGetRegulationFlag(FightKindData*);
u32 fightKindDataBiosGetHostEnemyMsgFlag(FightKindData*);
u32 fightKindDataBiosGetPokemonStatusMenuSubbarFlag(FightKindData*);
u32 fightKindDataBiosGetDarkpokemonHypermodeFlag(FightKindData*);
u32 fightKindDataBiosGetMonohiroiFlag(FightKindData*);
u32 fightKindDataBiosGetDorobouFlag(FightKindData*);
u32 fightKindDataBiosGetBossFlag(FightKindData*);
u32 fightKindDataBiosGetKeikentihueruFlag(FightKindData*);
u32 fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(FightKindData*);
u32 fightKindDataBiosGetDoHizukiMiyaburiFlag(FightKindData*);
u32 fightKindDataBiosGetDoCriticalAttackFlag(FightKindData*);
u32 fightKindDataBiosGetGetInfectPokerusFlag(FightKindData*);
u32 fightKindDataBiosGetGetFriendFlag(FightKindData*);
u32 fightKindDataBiosGetGetNekoniKobanFlag(FightKindData*);
u32 fightKindDataBiosGetGetOkaneFlag(FightKindData*);
u32 fightKindDataBiosGetOkanePoolFlag(FightKindData*);
u32 fightKindDataBiosGetGetExpFlag(FightKindData*);
u32 fightKindDataBiosGetDrawFlag(FightKindData*);
u32 fightKindDataBiosGetNigeruFlag(FightKindData*);
u32 fightKindDataBiosGetUseItemFlag(FightKindData*);
u32 fightKindDataBiosGetDoZukanTukamaetaFlag(FightKindData*);
u32 fightKindDataBiosGetDoZukanMitaFlag(FightKindData*);
u32 fightKindDataBiosGetDoBadgeCheckFlag(FightKindData*);
u32 fightKindDataBiosGetBackSaveDataFlag(FightKindData*);
u32 fightTypeDataBiosGetFightoutPokemonNum(FightTypeData*);
u32 fightTypeDataBiosGetEntryPokemonNum(FightTypeData*);
u32 fightTypeDataBiosGetTrainerNum(FightTypeData*);
u32 fightTypeGetFightSideFightOutPokemonMax(u16);
u32 fightEncountGetEnvSndDataId(u16);
u32 fightFloorGetBgmSndDataId(FIGHT_FLOOR*);

FIGHT_FLOOR* fightFloorBiosGetFightFloorPtr();
FloorData* fightFloorDataBiosGetPtr(u16);
u8 fightFloor_GetStockPokemonNum(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->stockPokemonNum;
}

u16 fightFloor_GetFirstAttackRnd(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->firstAttackRnd;
}

s16 fightFloor_GetFightPokemonEntryCnt(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->fightPokemonEntryCnt;
}

s32 fightFloor_GetAppointMsgId(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->appointMsgId;
}

void* fightFloor_GetAppointItemPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->appointItemPtr;
}

void* fightFloor_GetAppointSidePtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->appointSidePtr;
}

void* fightFloor_GetAppointWazaPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->appointWazaPtr;
}

void* fightFloor_GetAppointTrainerPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->appointTrainerPtr;
}

void* fightFloor_GetAppointPokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->appointPokemonPtr;
}

void* fightFloor_GetItemPokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->itemPokemonPtr;
}

void* fightFloor_GetTokuseiPokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->tokuseiPokemonPtr;
}

void* fightFloor_GetTuikakoukaPokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->tuikakoukaPokemonPtr;
}

void* fightFloor_GetKizetuPokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->kizetuPokemonPtr;
}

void* fightFloor_GetIrekaePokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->irekaePokemonPtr;
}

void* fightFloor_GetEscapePokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->escapePokemonPtr;
}

void* fightFloor_GetDefensePokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->defensePokemonPtr;
}

void* fightFloor_GetAttackPokemonPtr(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->attackPokemonPtr;
}

u16 fightFloor_GetEncountDataId(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    return floor->encountDataId;
}

u16 fightFloor_GetTurnCount(FIGHT_FLOOR* floor) {
    if (!floor) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (!floor) return 0;
    }
    if (!floor) return 0;
    return floor->turnCount;
}

u32 fightFloorDB_GetEnvSndId(u16 dataId) {
    FloorData* data = fightFloorDataBiosGetPtr(dataId);
    if (data == 0) {
        return 0;
    } else {
        return data->environmentSound;
    }
}

u32 fightFloorDB_GetBgmSndId(u16 dataId) {
    FloorData* data = fightFloorDataBiosGetPtr(dataId);
    if (data == 0) {
        return 0;
    } else {
        return data->bgm;
    }
}

u32 fightFloorDB_GetSyoukaiWzxDataId(u16 dataId) {
    FloorData* data = fightFloorDataBiosGetPtr(dataId);
    if (data == 0) {
        return 0;
    } else {
        return data->introSequence;
    }
}

u8 fightFloorDB_GetTikeiDataId(u16 dataId) {
    FloorData* data = fightFloorDataBiosGetPtr(dataId);
    if (data == 0) {
        return 0;
    } else {
        return data->terrain;
    }
}

u16 fightFloorDB_GetFloorDataId(u16 dataId) {
    FloorData* data = fightFloorDataBiosGetPtr(dataId);
    if (data == 0) {
        return 0;
    } else {
        return data->floor;
    }
}

u16 fightFloorDB_GetFightSideDataId(u16 dataId, u8 side) {
    FloorData* data = fightFloorDataBiosGetPtr(dataId);
    if (!data) return 0;
    if (side >= 2) return 0;
    return data->sides[side];
}
void* fightFloor_GetFightOutPokemonPtrAry(FIGHT_FLOOR* floor, u16 index) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    if (index >= 8) return 0;
    return floor->fightOutPokemon[index];
}
void** fightFloor_GetFightOutPokemonPtrAryPtr(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return floor->fightOutPokemon;
}
void fightFloor_SetStockPokemonNum(FIGHT_FLOOR* floor, u8 count) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return; }
    floor->stockPokemonNum = count;
}
Pokemon* fightFloor_GetStockPokemonPtr(FIGHT_FLOOR* floor, u8 index) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    if (index >= 6) return 0;
    return (Pokemon*)floor->stockPokemon[index].pokemon;
}
u8 fightFloor_GetStockPokemonBallID(FIGHT_FLOOR* floor, u8 index) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    if (index >= 6) return 0;
    return floor->stockPokemon[index].ballId;
}
void fightFloor_SetStockPokemonBallID(FIGHT_FLOOR* floor, u8 index, u8 ballId) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return; }
    if (index < 6) floor->stockPokemon[index].ballId = ballId;
}
u32 fightFloor_GetFightKindRegulationFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetRegulationFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindHostEnemyMsgFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetHostEnemyMsgFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindPokemonStatusMenuSubbarFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetPokemonStatusMenuSubbarFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDarkpokemonHypermodeFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDarkpokemonHypermodeFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindMonohiroiFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetMonohiroiFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDorobouFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDorobouFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindBossFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetBossFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindKeikentihueruFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetKeikentihueruFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDoItemSoubiTokukoutokubouupFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDoHizukiMiyaburiFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDoHizukiMiyaburiFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDoCriticalAttackFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDoCriticalAttackFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindGetInfectPokerusFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetGetInfectPokerusFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindGetFriendFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetGetFriendFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindGetNekoniKobanFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetGetNekoniKobanFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindGetOkaneFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetGetOkaneFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindOkanePoolFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetOkanePoolFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindGetExpFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetGetExpFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDrawFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDrawFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindNigeruFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetNigeruFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindUseItemFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetUseItemFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDoZukanTukamaetaFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDoZukanTukamaetaFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDoZukanMitaFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDoZukanMitaFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindDoBadgeCheckFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetDoBadgeCheckFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u32 fightFloor_GetFightKindBackSaveDataFlag(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightKindDataBiosGetBackSaveDataFlag(fightKindDataBiosGetPtr(fightFloor_GetFightKind(floor)));
}

u16 fightFloor_GetFightFloorDataId(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
}

u32 fightFloor_GetTrainer(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightEncountDataBiosGetTrainer(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
}

u8 fightFloor_GetFightType(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightEncountDataBiosGetFightType(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
}

u8 fightFloor_GetFightKind(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor)));
}

u32 fightFloor_GetFightTypeFightoutPokemonNum(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(fightFloor_GetFightType(floor)));
}

u32 fightFloor_GetFightTypeEntryPokemonNum(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightTypeDataBiosGetEntryPokemonNum(fightTypeDataBiosGetPtr(fightFloor_GetFightType(floor)));
}

u32 fightFloor_GetFightTypeTrainerNum(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightTypeDataBiosGetTrainerNum(fightTypeDataBiosGetPtr(fightFloor_GetFightType(floor)));
}

u32 fightFloor_GetFightSideFightOutPokemonSideMax(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightTypeGetFightSideFightOutPokemonMax(fightFloor_GetFightType(floor));
}

u32 fightFloor_GetSyoukaiWzxDataId(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightFloorDB_GetSyoukaiWzxDataId(fightFloor_GetFightFloorDataId(floor));
}

u8 fightFloor_GetTikeiDataId(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightFloorDB_GetTikeiDataId(fightFloor_GetFightFloorDataId(floor));
}

u32 fightFloor_GetEnvSndId(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightEncountGetEnvSndDataId(fightFloor_GetEncountDataId(floor));
}

u32 fightFloor_GetBgmSndId(FIGHT_FLOOR* floor) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightFloorGetBgmSndDataId(floor);
}

void fightFloor_SetFisstAttackRnd(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetFirstAttackRnd(floor, value);
}

void fightFloor_SetfightoutPokemonPtrAryPtr(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetFightOutPokemonPtrAryPtr(floor, value);
}

void fightFloor_SetfightPokemonEntryCnt(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetFightPokemonEntryCnt(floor, value);
}

void fightFloor_SetAppointPokemonWazaDataId(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetAppointWazaDataId(floor, value);
}

void fightFloor_SetAppointPokemonDataId(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetAppointPokemonDataId(floor, value);
}

void fightFloor_SetWazakoukaMsgId(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetWazakoukaMsgId(floor, value);
}

void fightFloor_SetCriticakMsgId(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetCriticalMsgId(floor, value);
}

void fightFloor_SetAttackMsgId(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetAttackMsgId(floor, value);
}

void fightFloor_SetAppointMsgPtr(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetAppointMsgId(floor, value);
}

void fightFloor_SetEncountFloorId(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetEncountFloorId(value);
}

void fightFloor_SetTokuseiPokemonPtr(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetTokuseiPokemonPtr(floor, value);
}

void fightFloor_SetKizetuPokemonPtr(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetKizetuPokemonPtr(floor, value);
}

void fightFloor_SetIrekaePokemonPtr(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetIrekaePokemonPtr(floor, value);
}

void fightFloor_SetEscapePokemonPtr(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetEscapePokemonPtr(floor, value);
}

void fightFloor_SetEncountDataId(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetEncountDataId(floor, value);
}

void fightFloor_SetTurnCount(FIGHT_FLOOR* floor, u32 value) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloorBiosSetTurnCount(floor, value);
}

u32 fightFloor_GetEncountFloorId(FIGHT_FLOOR* floor) { return fightFloorBiosGetEncountFloorId(floor); }
FightSide* fightFloor_GetFightSidePtr(FIGHT_FLOOR* floor, u16 side) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    if (side >= 2) return 0;
    return (FightSide*)((u8*)floor + 0x14 + side * 0x6ef0);
}
u32 fightFloor_GetIsJoutaiDataId(FIGHT_FLOOR* floor, u16 condition) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    return fightFloorIsJoutaiDataId(floor, condition);
}
void* fightFloor_GetJoutaiPtr(FIGHT_FLOOR* floor, u16 index) {
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return 0; }
    if (index >= 1) return 0;
    return (u8*)floor + index * 0x10;
}
void fightFloor_SetAttackPokemonFightWazaTargetId(FIGHT_FLOOR* floor, u16 target) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightOutPokemon_SetWazaTargetId(fightFloorBiosGetAttackPokemonPtr(floor), target);
}
void fightFloor_SetAttackPokemonFightWazaJoutaiDataId(FIGHT_FLOOR* floor, u16 condition) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightOutPokemon_SetWazaJoutaiDataId(fightFloorBiosGetAttackPokemonPtr(floor), condition);
}
void fightFloor_SetStockPokemonPtr(FIGHT_FLOOR* floor, u8 index, Pokemon* pokemon) {
    u8 copy[0xc4];
    if (!floor) { floor = fightFloorBiosGetFightFloorPtr(); if (!floor) return; }
    if (index < 6) {
        pokemonBiosCopy((Pokemon*)copy, pokemon);
        memcpy(floor->stockPokemon[index].pokemon, copy, 0xc4);
    }
}
void fightFloor_SetAppointTokuseiDataId(FIGHT_FLOOR* floor, u32 ability) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightMsgctrlSetValue(0x1c, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(ability))));
    fightFloorBiosSetAppointTokuseiDataId(floor, ability);
}
void fightFloor_SetAppointItemDataId(FIGHT_FLOOR* floor, u32 item) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightMsgctrlSetValue(0x29, (u32)GSmsgGetGSchar(itemDB_GetName(item)));
    fightFloorBiosSetAppointItemDataId(floor, item);
}
void fightFloor_SetItemPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    if (pokemon && fightOutPokemonCheckValid(pokemon) == 1) {
        fightFloor_SetAppointItemDataId(floor, fightOutPokemonGetSoubiItemDataId(pokemon));
    }
    fightFloorBiosSetItemPokemonPtr(floor, pokemon);
}
void fightFloor_SetAppointPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    if (pokemon) {
        if (fightOutPokemonCheckValid(pokemon) == 1) {
            fightMsgctrlSetValue(0x1e, (u32)pokemon);
            fightMsgctrlSetValue(0x1c, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(pokemon)))));
        } else {
            fightMsgctrlSetValue(0x1e, 0);
            fightMsgctrlSetValue(0x1c, 0);
        }
    } else {
            fightMsgctrlSetValue(0x1e, 0);
            fightMsgctrlSetValue(0x1c, 0);
    }
    fightFloorBiosSetAppointPokemonPtr(floor, pokemon);
}

void fightFloor_SetTuikakoukaPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    if (pokemon) {
        if (fightOutPokemonCheckValid(pokemon) == 1) {
            fightMsgctrlSetValue(0x12, (u32)pokemon);
            fightMsgctrlSetValue(0x1d, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(pokemon)))));
        } else {
            fightMsgctrlSetValue(0x12, 0);
            fightMsgctrlSetValue(0x1d, 0);
        }
    } else {
            fightMsgctrlSetValue(0x12, 0);
            fightMsgctrlSetValue(0x1d, 0);
    }
    fightFloorBiosSetTuikakoukaPokemonPtr(floor, pokemon);
}

void fightFloor_SetDefensePokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    if (pokemon) {
        if (fightOutPokemonCheckValid(pokemon) == 1) {
            fightMsgctrlSetValue(0x10, (u32)pokemon);
            fightMsgctrlSetValue(0x1b, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(pokemon)))));
            fightMsgctrlSetValue(0x42, (u32)pokemon);
            fightMsgctrlSetValue(0x44, (u32)pokemon);
            fightMsgctrlSetValue(0x43, (u32)pokemon);
        } else {
            fightMsgctrlSetValue(0x10, 0);
            fightMsgctrlSetValue(0x1b, 0);
            fightMsgctrlSetValue(0x42, 0);
            fightMsgctrlSetValue(0x44, 0);
            fightMsgctrlSetValue(0x43, 0);
        }
    } else {
            fightMsgctrlSetValue(0x10, 0);
            fightMsgctrlSetValue(0x1b, 0);
            fightMsgctrlSetValue(0x42, 0);
            fightMsgctrlSetValue(0x44, 0);
            fightMsgctrlSetValue(0x43, 0);
    }
    fightFloorBiosSetDefensePokemonPtr(floor, pokemon);
}

void fightFloor_SetAttackPokemonPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    if (pokemon) {
        if (fightOutPokemonCheckValid(pokemon) == 1) {
            fightMsgctrlSetValue(0xf, (u32)pokemon);
            fightMsgctrlSetValue(0x1a, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(pokemon)))));
            fightMsgctrlSetValue(0x1f, (u32)pokemon);
            fightMsgctrlSetValue(0x21, (u32)pokemon);
            fightMsgctrlSetValue(0x20, (u32)pokemon);
        } else {
            fightMsgctrlSetValue(0xf, 0);
            fightMsgctrlSetValue(0x1a, 0);
            fightMsgctrlSetValue(0x1f, 0);
            fightMsgctrlSetValue(0x21, 0);
            fightMsgctrlSetValue(0x20, 0);
        }
    } else {
            fightMsgctrlSetValue(0xf, 0);
            fightMsgctrlSetValue(0x1a, 0);
            fightMsgctrlSetValue(0x1f, 0);
            fightMsgctrlSetValue(0x21, 0);
            fightMsgctrlSetValue(0x20, 0);
    }
    fightFloorBiosSetAttackPokemonPtr(floor, pokemon);
}

void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    u32 type = (u8)fightFloor_GetFightType(floor);
    if (!floor) floor = fightFloorBiosGetFightFloorPtr();
    fightFloor_SetDefensePokemonPtr(floor, pokemon);
    fightFloor_SetAttackPokemonFightWazaTargetId(floor, fightTargetGetTragetPtrToRelativeHostSideFightTargetId(pokemon, type));
}
}
