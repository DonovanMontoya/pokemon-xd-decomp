#ifndef PEOPLE_SAVE_PRIVATE_HPP
#define PEOPLE_SAVE_PRIVATE_HPP
#include <game/pxdvs/app/people/runtime.hpp>
#include <game/pxdvs/GSAPI/GSScript/tiga.hpp>

struct PeopleSavedState {
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
typedef char PeopleSavedStateSize[sizeof(PeopleSavedState)==0x1A4 ? 1 : -1];

// Five-byte packed state used by the retail version 0x0103/type 4 record.
struct PeopleSaveFlags {
    unsigned char state:1, visible:1, unknown0E:1, running:1;
    unsigned char collision:1, paused:1, reserved0:2;
    unsigned char active:3, mode:3, phase:2;
    unsigned char neck:2, reserved1:6;
    u8 reserved2[2];
};
typedef char PeopleSaveFlagsSize[sizeof(PeopleSaveFlags)==5 ? 1 : -1];
extern "C" {
void* GSmemAllocClr(unsigned long);
GSvec* GSmodelGetPositionPtr(GSmodel*);
GSvec* GSmodelGetRotationPtr(GSmodel*);
void GSmodelSetPosition(GSmodel*,GSvec*);
void GSmodelSetRotation(GSmodel*,GSvec*);
void peopleClose(u32,u32,u8);
void peopleOpen(u32,u32,u32);
void peopleAddCollision(u32,u32);
tagPeopleWork* peopleGet(u32,u32);
void peopleSetDisp(u32,u32,u8);
void heroMoveTermEvent();
void gimmickBoxPop();
void GSlogWrite(const char*,...);
}
#endif
