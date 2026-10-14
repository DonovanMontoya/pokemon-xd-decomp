#ifndef EVOLUTION_PRIVATE_H
#define EVOLUTION_PRIVATE_H

#include <global.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

struct CAM_STORE {
    f32 pos[3];         // 0x0
    f32 rot[3];         // 0xC
    f32 targetPos[3];   // 0x18
    f32 targetOfs[3];   // 0x24
    f32 fov;            // 0x30
};

struct WORK {
    u32 seqBefore;      // 0x0
    u32 seqAfter;       // 0x4
    s32 step;           // 0x8
    u32 bgmId;          // 0xC
    u32 envId;          // 0x10
    s32 bgmVolume;      // 0x14
    s32 envVolume;      // 0x18
    u32 bgmPush;        // 0x1C
    u32 envPush;        // 0x20
};

struct EvolutionParameter {
    Pokemon* before;    // 0x0
    Pokemon* after;     // 0x4
    s32 canCancel;      // 0x8
    s32 wazaCount;      // 0xC
    u16* wazaIds;       // 0x10
    u8* wazaSlots;      // 0x14
    s32 result;         // 0x18
};

enum EVOLUTION_WINDOW_TYPE {
    EVOLUTION_WINDOW_FIELD = 0,
    EVOLUTION_WINDOW_NORMAL = 1
};

enum STEP {
    STEP_0,
    STEP_1,
    STEP_2,
    STEP_3,
    STEP_4
};

enum FADE_CTRL {
    FADE_CTRL_NONE = 0
};

extern "C" {
void cameraSetType(s32);
void cameraSetPosition(f32*);
void cameraSetRotation(f32*);
void cameraSetTargetPos(f32*);
void cameraSetTargetOfs(f32*);
void cameraSetFov(f32);
void cameraGetPosition(f32*);
void cameraGetRotation(f32*);
void cameraGetTargetPos(f32*);
void cameraGetTargetOfs(f32*);
void* GScameraGetActiveCamera();
void GScameraGetPerspective(void*, f32*, f32*, f32*, f32*);
void soundOpenPlay(u32, u32, u32);
void soundOpenPlayEnv(u32, u32, u32);
void soundOpenPlayME(u32, u32, u32);
void soundStop(u32, u32);
void soundStopEnv(u32);
s32 soundGetBGMID();
s32 soundGetEnvID();
s32 soundGetVolume(s32);
void GSsndSetPushVolumeID(u32, void*);
void GSsndGetPushVolumeID(u32, void*);
s32 GSsndGetStatus(u32);
void GSsndPlayNow(u16);
u8 pokemonCheckValid(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
u32 pokemonDataBiosGetPtr(u16);
u32 pokemonDataBiosGetVoice(u32);
void GSthreadSwitch();
u32 timeGetLastFrameTime();
void winMsgOpenField(u32, u32, u32);
void winMsgOpen(u32, u32, u32, u32);
void winMsgClose(u32);
void winMsgCloseField(u32);
s32 menuSubOpenYesNoField();
s32 menuSubOpenYesNo(u32, s32, s32, u32);
s32 menuPokemonStatusOpenWazaLearn(Pokemon*, u16);
u32 pokemonBiosGetRnd(Pokemon*);
u32 Sequence_LoadPokemon(u16, u32, u32);
u32 Sequence_LoadWaza(u32, u16, u32, u32);
u32 Sequence_GetWaza(u32, u16, u32);
void* Sequence_GetGSmodel(u32);
void Sequence_SetVisibility(u32, s32);
void WazaSequence_Start(u32, u32);
u8 WazaSequence_IsActive(u32);
void WazaSequence_Free(u32);
void* GSresGetResourceAllGroup(u32, u32);
void GSmodelSetForceUseFractionalFramesFlag(void*, u32);
void GSmodelSetSkipFractionalFramesFlag(void*, u32);
void GSmodelSetAnimType(void*, u32);
void fadeSet(u32, f32);
s8 fadeCheck(u32);
void msgctrlSetValue(u32, u32);
char* pokemonBiosGetNicknamePtr(Pokemon*);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon*, u16);
void pokemonBiosCopy(Pokemon*, Pokemon*);
void pokemonWazaCreate(Pokemon*, u8, u16);
s32 GSinputButtonsChanged(u32);
s32 GSinputButtonsPressed(u32);
void wazaSequenceSysEnableLayerChange();
void GSfloorPush(u32);
void GSfloorPop();
void floorSetFadeScript(u32, u32);
void floorWaitForChange();
}

#endif
