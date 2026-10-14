#include <dolphin/types.h>

struct FightOutPokemon;

extern "C" {
u32 fightFloor_GetFightType(void *);
void *fightActionBiosGetActorFightTargetPtr(void *);
void fightSeqSpecificationActionCounterInit(void *);
u8 fightTargetIsHostSide(void *, u32);
u8 fightFloorSetFightResultId(void *, s32);
void fightFloor_SetEscapePokemonPtr(void *, void *);
void fightSeqPokemonSoubiItemCheckAppear(FightOutPokemon *);
void fightSeqFightOutPokemonTokuseiCheckAppear(FightOutPokemon *);
u32 fightGetFightEncountDataId(void);
void *fightEncountDataBiosGetPtr(void);
void *fightFloorGetStatus(u32, u32, u32, u32);
void fightFloorCreate(void *, u32);
void fightFloorInitFightStart(void *);
u32 fightEncountDataBiosGetFightFloorDataId(void *);
void *fightTargetGetPtr(u32, u32, u32);
u32 fightFloorDB_GetFightSideDataId(u32, u32);
void fightSideCreate(void *, u32);
}

extern "C" s32 fightActionFlowHeijou(void) {
    return 1;
}

static s32 _fightActionFlowKaisiPostSubFightOutPokemonSoubiItemCheckAppear(void *p, u16, void *) {
    fightSeqPokemonSoubiItemCheckAppear((FightOutPokemon *)p);
    return 1;
}

static s32 _fightActionFlowKaisiPostSubFightOutPokemonTokuseiCheckAppear(void *p, u16, void *) {
    fightSeqFightOutPokemonTokuseiCheckAppear((FightOutPokemon *)p);
    return 1;
}

extern "C" s32 fightActionFlowFightNigeru(void *actor) {
    void *target;
    u8 type = fightFloor_GetFightType(0);
    target = fightActionBiosGetActorFightTargetPtr(actor);
    fightSeqSpecificationActionCounterInit(target);
    u8 res;
    if (fightTargetIsHostSide(target, type) == 1) {
        res = fightFloorSetFightResultId(0, 4);
    } else {
        res = fightFloorSetFightResultId(0, 5);
    }
    if (res == 1) {
        fightFloor_SetEscapePokemonPtr(0, target);
    }
    return 1;
}

extern "C" s32 fightActionFlowKaijou(void) {
    void *data;
    u32 floorData;
    void *t;
    u8 type;
    u32 id = fightGetFightEncountDataId();
    data = fightEncountDataBiosGetPtr();
    fightFloorCreate(fightFloorGetStatus(0, 0, 0, 0), id);
    fightFloorInitFightStart(0);
    type = fightFloor_GetFightType(0);
    floorData = fightEncountDataBiosGetFightFloorDataId(data);
    t = fightTargetGetPtr(4, 0, type);
    u32 side = fightFloorDB_GetFightSideDataId(floorData, 0);
    fightSideCreate(t, side);
    t = fightTargetGetPtr(5, 0, type);
    fightSideCreate(t, fightFloorDB_GetFightSideDataId(floorData, 1));
    return 1;
}

extern "C" s32 fightActionFlowNullFunc(void) {
    return 1;
}
