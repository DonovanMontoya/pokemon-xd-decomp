#include <game/pxdvs/app/gamedata/gamedatasaveBiosLayout.hpp>
#pragma dont_inline on
extern "C" {
void gamedataBiosSetZukanFLag(u16* flags,u16 index,u16 value){if(flags==0)return;if(index>0x10)return;u16 bit=(u16)(1u<<index);if(value==1){*flags|=bit;}else{*flags&=(u16)~bit;}}
u32 gamedataBiosGetZukanFlag(const u16* flags,u16 index){if(flags==0)return 0;if(index>0x10)return 0;u16 bit=(u16)(1u<<index);return ((*flags&bit)!=0);}
void* gamedatasaveBiosGetplaydata(GamedataSaveRecord* p){if(p==0)return 0;return (u8*)p+0x40;}
void gamedatasaveBiosSetSysHeadChecksum(GamedataSaveRecord* p,u32 value){if(p)p->payload.checksumWords.sysHeadChecksum=value;}
u32 gamedatasaveBiosGetSysHeadChecksum(GamedataSaveRecord* p){if(p)return p->payload.checksumWords.sysHeadChecksum;return 0;}
void fn_801577B4(GamedataSaveRecord* p,u8 value){if(p)p->payload.flags20.flagBytes.flag23=value;}
u8 fn_801577C4(GamedataSaveRecord* p){if(p)return p->payload.flags20.flagBytes.flag23;return 0;}
void gamedatasaveBiosSetParChecksum(GamedataSaveRecord* p,u32 value){if(p)p->payload.parChecksum=value;}
u32 gamedatasaveBiosGetParChecksum(GamedataSaveRecord* p){if(p)return p->payload.parChecksum;return 0;}
void gamedatasaveBiosSetOptionAudio(GamedataSaveRecord* p,u8 value){if(p)p->payload.flags20.flagBytes.audioOption=value;}
void gamedatasaveBiosSetOptionNoVibration(GamedataSaveRecord* p,u8 value){if(p)p->payload.flags20.flagBytes.noVibration=value;}
void gamedatasaveBiosSetFloorposindex(GamedataSaveRecord* p,u8 value){if(p)p->payload.flags20.flagBytes.floorPositionIndex=value;}
void gamedatasaveBiosSetPrevfloorid(GamedataSaveRecord* p,u32 value){if(p)p->payload.previousFloorId=value;}
void gamedatasaveBiosSetPlaytime(GamedataSaveRecord* p,f64 value){if(p)p->payload.playtime=value;}
void gamedatasaveBiosSetFloorid(GamedataSaveRecord* p,u32 value){if(p)p->payload.floorId=value;}
void gamedatasaveBiosSetSavecount(GamedataSaveRecord* p,u32 value){if(p)p->payload.saveCount=value;}
void gamedatasaveBiosSetMemcardID(GamedataSaveRecord* p,u64 value){if(p)p->memcardId=value;}
void gamedatasaveBiosSetSavernd(GamedataSaveRecord* p,u32 value){if(p)p->payload.saveRandom=value;}
u8 gamedatasaveBiosGetOptionAudio(GamedataSaveRecord* p){if(p)return p->payload.flags20.flagBytes.audioOption;return 0;}
u8 gamedatasaveBiosGetOptionNoVibration(GamedataSaveRecord* p){if(p)return p->payload.flags20.flagBytes.noVibration;return 0;}
u8 gamedatasaveBiosGetFloorposindex(GamedataSaveRecord* p){if(p)return p->payload.flags20.flagBytes.floorPositionIndex;return 0;}
u32 gamedatasaveBiosGetPrevfloorid(GamedataSaveRecord* p){if(p)return p->payload.previousFloorId;return 0;}
f64 gamedatasaveBiosGetPlaytime(GamedataSaveRecord* p){if(p)return p->payload.playtime;return 0.0;}
u32 gamedatasaveBiosGetFloorid(GamedataSaveRecord* p){if(p)return p->payload.floorId;return 0;}
u32 gamedatasaveBiosGetSavecount(GamedataSaveRecord* p){if(p)return p->payload.saveCount;return 0;}
u64 gamedatasaveBiosGetMemcardID(GamedataSaveRecord* p){if(p)return p->memcardId;return 0;}
u32 gamedatasaveBiosGetSavernd(GamedataSaveRecord* p){if(p)return p->payload.saveRandom;return 0;}
void gamedatasaveBiosSetPtr(GamedataSaveRecord* dst,const GamedataSavePayload* src){if(dst==0)return;if(src==0)return;dst->payload.saveCount=src->saveCount;dst->payload.saveRandom=src->saveRandom;dst->payload.parChecksum=src->parChecksum;dst->payload.floorId=src->floorId;dst->payload.copiedWord18=src->copiedWord18;dst->payload.previousFloorId=src->previousFloorId;dst->payload.flags20.copiedFloat20=src->flags20.copiedFloat20;dst->payload.flags20.copiedWords20[1]=src->flags20.copiedWords20[1];dst->payload.raw28.copiedByte28=src->raw28.copiedByte28;dst->payload.raw28.copiedBytes29to2b[0]=src->raw28.copiedBytes29to2b[0];dst->payload.raw28.copiedBytes29to2b[1]=src->raw28.copiedBytes29to2b[1];dst->payload.raw28.copiedBytes29to2b[2]=src->raw28.copiedBytes29to2b[2];dst->payload.copiedAggregateDouble30=src->copiedAggregateDouble30;dst->payload.copiedWord38=src->copiedWord38;}
GamedataSavePayload* gamedatasaveBiosGetPtr(GamedataSaveRecord* p){if(p==0)return 0;return &p->payload;}
void gamedatasaveInit(GamedataSaveRecord* p){if(p==0)return;p->payload.parChecksum=0;}
}
