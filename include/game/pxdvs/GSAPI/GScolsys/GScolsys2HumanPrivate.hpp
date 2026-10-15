#ifndef GSCOLSYS2_HUMAN_PRIVATE_HPP
#define GSCOLSYS2_HUMAN_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct GSvec { f32 x,y,z; };
struct GSCOLSYS2_HUMAN { s32 group; u32 resource; f32 radius,height; u16 flags,padding; };
struct HumanFloor { u8 objects[0xa00]; GSCOLSYS2_HUMAN humans[48]; };
struct HumanHeight { f32 height; u16 upper,lower; s8 layer,floor; u16 padding; };
struct tagPeopleWork { u8 isHero() const; u8 isFollower() const; };
typedef char HumanRecordSize[sizeof(GSCOLSYS2_HUMAN)==20?1:-1];
typedef char HumanArrayOffset[offsetof(HumanFloor,humans)==0xa00?1:-1];
typedef char HumanFloorSize[sizeof(HumanFloor)==0xdc0?1:-1];
extern "C" {
HumanFloor *GScolsys2GetCurFloor();
s32 GScolsys2WalkGetHeight(GSvec *,HumanHeight *);
u32 peopleGetHumanID(s32,u32);
tagPeopleWork *peopleSearchID(u32);
GSvec *peopleBiosGetPosPtr(tagPeopleWork *);
void peopleGetPos(s32,u32,GSvec *);
f32 peopleGetTalkDistance(s32,u32);
u8 gimmickBoxFixDistanceForPushBox(f32 *,tagPeopleWork *,f32,f32);
u8 gimmickBoxIsBox(tagPeopleWork *);
void heroMoveGetHeroPos(GSvec *);
tagPeopleWork *heroGetFollower();
void GSgfxLayerSetActive(s32);
void GScameraLoadActiveCameraMatrix(s32);
void GSgfxCullMode(s32);
void *GSgfxVFBuildTemp(s32,s32,u8,s32,u8,s32,u8,s32,s32);
void GSgfxSetupRenderAndSelect();
void GSgfxBlendMode(s32,s32,s32);
void GSgfxPixelMode(s32,s32,s32);
void GSgfxSetLineWidth(f32);
void GSgfxSetPrimitiveType(s32);
void GSgfxBeginSurface(s32);
void GSgfxVertex3f(f32,f32,f32);
void GSgfxColor4u8(u8,u8,u8,u8);
void GSgfxEndSurface();
f64 sin(f64); f64 cos(f64);
extern f32 __float_nan[];
}
#endif
