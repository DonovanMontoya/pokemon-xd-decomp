#include <dolphin/types.h>
enum GSmodelAnimType { AnimTypeDummy };
struct PeopleInfo {u8 flags;};
struct tagPeopleWork {
 u8 pad0[8];void *model;u32 padC;u32 flags;u8 pad14[8];u32 info;u8 pad20[0x34];u8 moveType;u8 pad55[0x10F];s32 startMotion,walkMotion,runMotion,startMotion2,startMotion3;
 u8 getMoveType();s32 getRunMotion();s32 getWalkMotion();void setAnimType(GSmodelAnimType);void setAnimFrame(f32);void setAnimBlend(int,int);void setAnimIndex(int);void setAnimRate(f32,bool);u8 isAnimLast() const;u32 getFlags() const;u8 checkFlags(unsigned long) const;u8 isWalkStartMotion() const;u8 isAlwayBlendChara() const;
};
extern "C" {
u8 GSmodelIsNullAnimation(void *,s32);
void GSmodelSetAnimType(void *,GSmodelAnimType);
void GSmodelSetAnimFrame(void *,f32);
void GSmodelSetAnimBlend(void *,s32,s32);
void GSmodelSetAnimIndex(void *,s32);
void GSmodelSetAnimRate(void *,f32);
u8 GSmodelHasAnimationEnded(void *);
u8 peopleBiosCheckFlag(const tagPeopleWork *,unsigned long);
f32 peopleViewerGetPlaySpeedRate(tagPeopleWork *);
PeopleInfo *peopleInfoBiosGetPtr(u32);
void GSmodelGetAnimIndex(void *,s32 *,s32 *);
}
u8 tagPeopleWork::getMoveType(){return moveType;}
s32 tagPeopleWork::getRunMotion(){if(runMotion>=0){s32 a=runMotion;if(!GSmodelIsNullAnimation(model,a))return a;}s32 b=walkMotion;if(b>=0 && !GSmodelIsNullAnimation(model,b))return b;return 3;}
s32 tagPeopleWork::getWalkMotion(){if(walkMotion>=0){s32 a=walkMotion;if(!GSmodelIsNullAnimation(model,a))return a;}s32 b=runMotion;if(b>=0 && !GSmodelIsNullAnimation(model,b))return b;return 3;}
void tagPeopleWork::setAnimType(GSmodelAnimType type){if(model)GSmodelSetAnimType(model,type);}
void tagPeopleWork::setAnimFrame(f32 frame){if(model){if(frame<0.0f)frame=0.0f;GSmodelSetAnimFrame(model,frame);}}
void tagPeopleWork::setAnimBlend(int a,int b){if(model && !GSmodelIsNullAnimation(model,a)){if(GSmodelIsNullAnimation(model,b))setAnimIndex(a);else GSmodelSetAnimBlend(model,a,b);}}
void tagPeopleWork::setAnimIndex(int i){if(model)GSmodelSetAnimIndex(model,i);}
void tagPeopleWork::setAnimRate(f32 rate,bool viewer){if(model && !checkFlags(0x8000)){if(viewer)rate*=peopleViewerGetPlaySpeedRate(this);GSmodelSetAnimRate(model,rate);}}
u8 tagPeopleWork::isAnimLast() const {if(!model)return 0;return GSmodelHasAnimationEnded(model);}
u32 tagPeopleWork::getFlags() const {return flags;}
u8 tagPeopleWork::checkFlags(unsigned long mask) const {return peopleBiosCheckFlag(this,mask);}
u8 tagPeopleWork::isWalkStartMotion() const {
 PeopleInfo *p=peopleInfoBiosGetPtr(info);if(!p)return 0;if((p->flags>>1)&1)return 0;
 s32 a,b;GSmodelGetAnimIndex(model,&a,&b);if(b!=-1)return 0;
 if(a==startMotion || a==startMotion2 || a==startMotion3)return 1;return 0;
}
u8 tagPeopleWork::isAlwayBlendChara() const {
 if(info==0x16C90400 || info==0x169E0400 || info==0x169F0400 || info==0x16A00400 || info==0x20250400 || info==0x1EE20400 || info==0x16C70400 || info==0x195B0400 || info==0x1A7C0400 || info==0x19540400)return 1;return 0;
}
