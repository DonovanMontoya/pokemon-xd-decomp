#include <global.h>

extern "C" {
extern u8 fight_target_data[];
extern u32 fight_target_data_number;

u8 fightTargetDataBiosGetRelativeFlag(void* data) {
    if (data == 0) return 0;
    return *((u8*)data + 1);
}

u32 fightTargetDataBiosGetBuff(void* data) {
    if (data == 0) return 0;
    return *(u32*)((u8*)data + 4);
}

u8 fightTargetDataBiosGetStatusKid(u8* data) {
    if (data == 0) return 0;
    return *data;
}

void* fightTargetDataBiosGetPtr(u16 id) {
    if (id >= fight_target_data_number) return 0;
    return fight_target_data + id * 8;
}

void *fightTargetGetPtr(u16,void*,u16);
u8 fightFloor_GetFightType(void*);
s32 fightTargetIsHostSide(void *target,u16 type) {
 void *host=fightTargetGetPtr(4,0,type); if(!host)return 0;
 void *side=fightTargetGetPtr(2,target,type); if(!side)return 0; return side==host;
}
void *fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16 id,u16 type) {
 void *host=fightTargetGetPtr(4,0,type); if(!host)return 0;
 void *result=fightTargetGetPtr(id,host,type); if(!result)result=0; return result;
}
u16 fightTargetGetTragetPtrToRelativeFightTargetId(void *base,void *target,u16 type) {
 for(u16 i=0;i<fight_target_data_number;i++) {
  if(i!=0) {void *data=fightTargetDataBiosGetPtr(i); if(data && fightTargetDataBiosGetRelativeFlag(data)!=0 && fightTargetGetPtr(i,base,type)==target) return i;}
 }return 0;
}
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void *target,u16 type) {
 void *host=fightTargetGetPtr(4,0,type);if(!host)return 0;
 return fightTargetGetTragetPtrToRelativeFightTargetId(host,target,type);
}
void *fightTargetGetPtrAsNowFightType(u16 id,void *base) {return fightTargetGetPtr(id,base,fightFloor_GetFightType(0));}
}
