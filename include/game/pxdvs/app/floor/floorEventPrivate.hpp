#ifndef FLOOR_EVENT_PRIVATE_HPP
#define FLOOR_EVENT_PRIVATE_HPP
#include <game/pxdvs/app/floor/floorBiosPrivate.hpp>
struct _GSmodel;
struct GSthread;
struct GSpart;
struct FloorEventTreasure {
    u8 displayType:3, rewardType:3, reservedFlags:2;
    union { u8 quantity; s8 signedQuantity; };
    u16 reserved2, floorID, flagID;
    u32 reserved8, rewardID;
    u8 reserved10[0xC];
};
struct FloorEventDoor {
    s8 openMotion, closeMotion, openedMotion, closedMotion, reserved4, ascendMotion, descendMotion;
    u8 soundType, partIndex, reserved9;
    s16 collisionID;
    u16 reservedC, openFlag, requiredFlag, reserved12;
    u32 resourceID;
};
struct FloorEventScript { u8 type; u8 reserved1; u16 floorID; u32 collisionID, scriptID; s32 parameters[4]; };
struct FloorEventME { u32 soundID; u8 playing; u8 reserved5[3]; };
typedef char FloorEventTreasureSize[sizeof(FloorEventTreasure) == 0x1C ? 1 : -1];
typedef char FloorEventDoorSize[sizeof(FloorEventDoor) == 0x18 ? 1 : -1];
typedef char FloorEventScriptSize[sizeof(FloorEventScript) == 0x1C ? 1 : -1];
typedef char FloorEventDoorResourceOffset[offsetof(FloorEventDoor, resourceID) == 0x14 ? 1 : -1];
typedef char FloorEventTreasureRewardOffset[offsetof(FloorEventTreasure, rewardID) == 0xC ? 1 : -1];
extern "C" {
extern FloorEventTreasure *floor_tresure_list;
extern u32 *floor_tresure_list_number;
extern FloorEventDoor *floor_door_list;
extern u32 *floor_door_list_number;
extern FloorEventScript *floor_event_list;
extern u32 *floor_event_list_number;
void GSlogWrite(const char *, ...);
u32 floorGetCurrentGroupID();
_GSmodel *floorGetResource(u32);
void peopleSetDisp(u32, u32, s32);
void peopleSetMotion(u32,u32,s32,s32,s32);
void peopleSetFlagOn(u32,u32,u32);
void peopleWaitSyncMotion(u32,u32,s32);
u8 GSflagTest(u16);
void GSflagOn(u16);
void GSflagOff(u16);
void GSsndPlayNow(u32);
void GSsndStopNow(u32);
s32 GSsndGetStatus(u32);
void GSthreadSwitch();
void soundPlayWait(u32);
void *floorCreateThread(s32,u32,s32,s32 (*)(GSthread *));
void msgctrlSetValue(u32,s32);
void winMsgOpen(u32,u32,u32,u32);
void winMsgClose(u32);
void heroAddPokedoru(u32,s32);
s32 heroItemAddItemDataId(u32,u16,u16,s32);
u16 pcboxAddItem(u32,u16,u16);
u8 GSmodelCanAnimate(_GSmodel *);
u8 GSmodelIsAnimating(_GSmodel *);
void GSmodelSetAnimIndex(_GSmodel *,s32);
void GSmodelSetAnimFrame(_GSmodel *,f32);
void GSmodelSetAnimRate(_GSmodel *,f32);
void GSmodelSetAnimType(_GSmodel *,s32);
void GSmodelStartAnimation(_GSmodel *);
void GSmodelGetFrameCount(_GSmodel *,f32 *,f32 *);
GSpart *GSmodelGetPart(_GSmodel *,u8);
void GSpartGetTransform(GSpart *,GSvec *,GSvec *,GSvec *);
void GSpartFree(GSpart *);
void __ct__5GSvecFv(GSvec *);
void peopleWalkTo(u32,u32,u8,GSvec *);
void peopleMoveCheck(u32,u32,s32);
void peopleRotateToAngle(u32,u32,f32,f32);
void peopleDetach(u32,u32,s32);
void peopleGetPos(u32,u32,GSvec *);
void peopleAttach(u32,u32,u32,u32,u8);
void peopleSetPosXYZ(u32,u32,f32,f32,f32);
u8 GSgfxVideoGetVsyncRate();
void scriptSetCol(s16,s32);
u32 peopleGetFlags(u32,u32);
void peopleSetFlags(u32,u32,u32);
void heroMoveInitEvent();
void heroMoveTermEvent();
void scriptSetEventColID(u32);
void floorExecScriptInteger(u32,s32,s32,s32,s32);
void scriptSoundOpenPlayME(u32,s32,u8);
}
void EvlogSet(s8,u32);
#endif
