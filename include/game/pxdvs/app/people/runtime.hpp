#ifndef PEOPLE_RUNTIME_HPP
#define PEOPLE_RUNTIME_HPP

#include <global.h>
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>

struct PeopleInfo {
    u8 flags;
    s8 neckIndex;
    s8 chestIndex;
    u8 reserved;
    u32 modelResource;
    f32 walkLength;
    f32 runLength;
    f32 collisionRadius;
    f32 neckLeft;
    f32 neckRight;
    f32 neckUp;
    f32 neckDown;
    f32 talkDistance;
    u8 unknown28[12];
};

struct PeopleMotionTable { s32 idle, walk, run, walkStart, runStart; };
struct GSmodel;
struct tagPeopleWork {
    u8 used;
    u8 unknown01[3];
    tagPeopleWork* self;
    GSmodel* model;
    u8 state, visible, unknown0E, collisionEnabled;
    u32 flags, group, resource, object;
    f32 unknown20;
    f32 unknown24;
    f32 unknown28;
    f32 unknown2C;
    f32 walkStartFrames, walkFrames, runStartFrames, runFrames;
    f32 targetRotation;
    f32 rotationProgress;
    s32 requestedMotion;
    u16 moveScriptThread;
    u8 unknown4E[2];
    s32 collisionHandle;
    u8 walkActive;
    u8 walkPhase, walkPaused, savedWalkMode;
    f32 moveSpeed;
    GSvec walkStartPosition;
    GSvec walkTarget;
    u16 walkPointCount, walkPointIndex;
    GSvec* walkPoints;
    u8 unknown7C[4];
    GSvec originPosition;
    u8 unknown8C[4];
    f32 motionFrame;
    f32 randomCentre;
    f32 randomRange;
    s32 motionType;
    u8 unknownA0[8];
    GSvec previousPosition;
    GSvec speedPosition;
    u8 animationMixRegistered;
    u8 neckUpdating, neckInstant, neckUnknownC3;
    u8 neckEnabled;
    u8 unknownC5[3];
    GSvec neckTargetPosition, neckTargetRotation, neckRotation;
    GSvec unknownEC;
    u32 neckTargetGroup, neckTargetResource;
    f32 neckMinStep, neckMaxStep, neckDistance;
    u8 secondaryMixRegistered;
    u8 unknown10D[3];
    GSvec chestRotation;
    s32 attachGroup, attachResource, attachIndex;
    f32 motionBlend, motionBlendStep;
    f32 chestBlend;
    f32 initialRotation;
    f32 idleTimer;
    u8 chestHidden;
    u8 waitAnimation;
    u8 unknown13E[2];
    s32 followerMotion;
    u8 unknown144[4];
    f32 blinkTimer;
    u8 flag14C, flag14D;
    u8 unknown14E[2];
    f32 value150;
    u8 animationBlend;
    u8 manualAnimation;
    u8 unknown156[6];
    u8 running;
    u8 slowDown;
    u8 unknown15E[2];
    f32 unknown160;
    PeopleMotionTable motions;
    f32 treasureSearchDistance;
    u16 treasure;
    u8 unknown17E;
    u8 flag17F;
    f32 rotationRate;
    u8 unknown184[0x0c];
    s32 speechAnimations[7];
    f32 speechTimer;
};

extern "C" {
extern PeopleInfo* peopleInfoData;
extern u32* peopleInfoData_number;
PeopleInfo* peopleInfoBiosGetPtr(u32 resource);
PeopleInfo* peopleInfoBiosGetPtrFromIndex(u32 index);
void peopleInfoBiosGetMotion(PeopleInfo*, u8, s32*, bool*);
tagPeopleWork* peopleBiosGetWorkPtr(s32);
tagPeopleWork* peopleBiosGetNewWork();
s32 peopleBiosGetMaxNum();
GSmodel* peopleBiosGetModelPtr(tagPeopleWork*);
void peopleBiosSetDispFlag(tagPeopleWork*, u8);
void peopleBiosSetCollision(tagPeopleWork*, u8);
}

typedef char PeopleInfoSizeCheck[sizeof(PeopleInfo) == 0x34 ? 1 : -1];
typedef char PeopleWorkSizeCheck[sizeof(tagPeopleWork) == 0x1B0 ? 1 : -1];
#endif
