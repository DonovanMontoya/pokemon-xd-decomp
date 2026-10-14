#ifndef HERO_MOVE_PRIVATE_H
#define HERO_MOVE_PRIVATE_H

#include <global.h>

struct GSvec {
    f32 x;
    f32 y;
    f32 z;
};

enum HEROMOVE_MEMBER {
    HEROMOVE_MEMBER_0,
    HEROMOVE_MEMBER_1,
    HEROMOVE_MEMBER_2,
    HEROMOVE_MEMBER_3
};

enum FloorEnterMode { FloorEnterModeNone };

struct AnalogStickEmu {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;

    void init();
};

struct HeroMoveMember {
    s32 x0;
    u16 flags;
    u8 pad06[2];
    f32 dist;
    s32 neckMode;
    u8 pad10[0x10];
};

struct HeroMoveWork {
    union {
        u8 raw[0x660];
        HeroMoveMember members[4];
        struct {
            u8 pad00[0x8C];
            GSvec log[60];
        } leaderLog;
    };
};

struct FOOTWORK {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
};

struct Pokemon;

enum FootStepCounter { FOOTSTEP_COUNTER_0, FOOTSTEP_COUNTER_1, FOOTSTEP_COUNTER_2, FOOTSTEP_COUNTER_3 };

class Hero {
public:
    static Hero* getHeroPtr();
    void setFollowerID(u8);
    void addFootStep(unsigned long);
    void setFollowerResID(unsigned long);
    void setFollowerGrpID(unsigned long);
    unsigned long getFollowerGrpID();
    unsigned long getFollowerResID();
};

struct FloorModuleInterface {
    void (*create)(unsigned int, FloorEnterMode);
    void (*pre)(unsigned int, FloorEnterMode);
    void (*normal)(unsigned int, FloorEnterMode);
    int (*thread)(void*);
    void (*post)(unsigned int, FloorEnterMode);
    void (*free)(unsigned int, FloorEnterMode);
    const char* (*getName)();
    void (*saveState)(int, void*, unsigned long);
    void (*loadState)(int, void*, unsigned long);
    unsigned long (*getStateSize)(int);
    unsigned long (*getStateID)();
};

class FloorBgmMask {
public:
    void stopMask();
};

extern u32 pokecoloFrameCounter;

extern "C" {
u8 cameraGetType();
u8 dbgMenuIsOpen();
u8 menuIsCheck(u32);
s32 floorGetFloorState();
void floorExecScriptInteger(s32, s32, s32, s32);
s32 floorEventExecScript(u32, s32);
u8 gimmickBoxIsGimmickMoving();
FloorBgmMask* floorSound_getBgmMaskObj();
void menuFieldMain(u32);
u8 peopleCheckFlag(u32, u32, u32);
void PSVECSubtract(GSvec*, GSvec*, GSvec*);
f32 PSVECMag(GSvec*);
u32 timeGetLastFrameTime(u8);
u8 GSgfxVideoGetVsyncRate();
u32 GSinputButtonsChanged(u32);
u32 GSinputButtonsPressed(u32);
void FloorModuleInterface_clear(FloorModuleInterface*);
u32 floorRegisterModule(u8, u32, FloorModuleInterface*);
void* floorDataBiosGetPtr();
u8 floorDataBiosGetFloorKind(void*);
void floorCreateThread(u32, u32, u32, void (*)());
u8 pokemonCheckValid(void*);
void heroMoveSetLockFrame(s32);
bool heroMoveAppointLeader(s32);
s32 heroMoveAddStepCallback(void (*)(long, FootStepCounter, long), s32);
void peopleRemoveNeckTarget(u32, u32, f32);
void peopleSetNeckTargetHero(u32, u32);
void peopleSetCollision(u32, u32, u32);
void peopleSetFlagOn(u32, u32, u32);
void peopleSetFlagOff(u32, u32, u32);
void* memcpy(void*, const void*, unsigned long);
}

extern "C" {
s32 heroGetStatus(void*, u16, u16);
s32 heroMoveJoinMember(s32);
s32 heroMoveDismissMember(s32);
s32 heroMoveSetNeckMode(s32, s32);
s32 heroMoveGetNeckMode(s32);
s32 heroMoveGetLeader();
bool heroMoveIsMember(s32);
f32 PSVECDistance(GSvec*, GSvec*);
u32 peopleGetHumanID(u32, u32);
void* peopleSearchID(u32);
void peopleUpdateAnimation(void*, u32);
u16 pokemonBiosGetItemDataId(Pokemon*);
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon*, u32, u16);
s32 GSflagGet(u32);
void* GSresGetResource(u32, u32);
void GSmodelSetRotation(void*, GSvec*);
void GSmodelGetRotation(void*, GSvec*);
void GSmodelGetPosition(void*, GSvec*);
void peopleSetPos(u32, u32, GSvec*);
void peopleSetDisp(u32, u32, bool);
void* peopleGet(u32, u32);
u32 itemDataBiosGetPtr(u16);
u32 itemDataBiosGetItemSoubiDataId(u32);
}

#endif
