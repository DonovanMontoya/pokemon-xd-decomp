#ifndef BATTLE_CAMERA_PRIVATE_HPP
#define BATTLE_CAMERA_PRIVATE_HPP
#include <game/pxdvs/app/battleGrid/wazaSequenceCameraPrivate.hpp>


// Layout of BattleGrid (see battleGrid.cpp): four trainers plus the live counters.
struct BattleCameraGridEntry {
    ModelSequence *trainer;
    ModelSequence *pokemon[2];
    u16 count;
    u8 side;
    s8 lane;
};
struct BattleCameraGrid {
    BattleCameraGridEntry entry[4];
    u16 trainerCount;
    u16 pokemonCount;
};
extern BattleCameraGrid gBattleGrid;

// Raw access to the parts of WazaSequence the camera code looks at.
static inline u32 wazaSequenceFlags(WazaSequence *waza) { return *(u32 *)((u8 *)waza + 8); }
static inline u32 wazaSequenceCameraAnim(WazaSequence *waza) { return *(u32 *)((u8 *)waza + 0x1c); }
static inline u8 wazaSequenceJointIndex(WazaSequence *waza) { return *(u8 *)((u8 *)waza + 0x16); }

extern "C" {
u8 wazaSequenceSysIsValidWaza(WazaSequence *);
u8 wazaSequenceSysIsValidSequence(NullSequence *);
u8 fightFloor_GetTrainer(int);
u8 fightPokemonGetNonTrainerPokemonIsActiveFlag();
u8 floorDataBiosGetFloorKind();
u8 cameraMoveEndCheckSpecial(u8);
void cameraMoveStop();
void cameraMoveTargetOfs(u32, GSvec *, f32);
void cameraMoveFov(u32, f32, f32);
void cameraMoveFovAcc(f32);
void cameraPlayOffsetAnime(u32, u32, s32, u8);
void cameraRefreshTargetPos();
void cameraSetMirrorFlag(s32);
void cameraSetOffsetPosition(GSvec *);
void cameraSetOffsetRotation(GSvec *);
void cameraSetOffsetScale(GSvec *);
void cameraSetTargetExt(u32, u32, s32);
void cameraSetTargetPos(GSvec *);
void cameraSetTargetOfs(GSvec *);
void cameraSetType(u8);
void cameraStopAnime();
void fn_80196A14(u8);
void battleGridResetModelVisibilityFlags();
void battleGridGetNormalisedScale(GSvec *);
f32 battleGridGetDistance(u8);
f32 battleGridGetUnscaledDistance(u8);
u16 battleGridGetNumPokemonsForTrainer(NullSequence *);
s32 HSD_Rand();
f32 GSgfxVideoGetLastRenderTime();
f32 GSlerpGetLinearInterpolationFloat(f32, f32, f32);
u16 GSmodelCenterNull(_GSmodel *);
u8 GSmodelIsRootNullAdded(_GSmodel *);
void GSmodelGetRootPosition(_GSmodel *, GSvec *);
void *GSresGetResource(u32, u32);
void GSpartGetTransform(void *, GSvec *, void *, void *);
void battleCameraDisable();
u8 battleCameraIsSimple();
void battleCameraDoFull();
void battleCameraDoSimple();
void battleCameraInit(u32);
void battleCameraUpdate();
void battleCameraStop();
void battleCameraStartRandom(u8);
void battleCameraStartWaza(WazaSequence *);
}
#endif
