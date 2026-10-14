#include <game/pxdvs/app/fight/fightWazaBiosLayout.hpp>
#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>
#pragma dont_inline on
extern "C" {
extern FightWazaHitKakurituBiosRecord fight_waza_hit_kakuritu_data[];
extern u32 fight_waza_hit_kakuritu_data_number;
extern FightWazaCriticalBiosRecord fight_waza_critical_data[];
extern u32 fight_waza_critical_data_number;

u8 fightWazaHitKakurituDataBiosGetWaru(FightWazaHitKakurituBiosRecord* p){if(p==0){return 1;}else{return p->waru;}}
u8 fightWazaHitKakurituDataBiosGetKake(FightWazaHitKakurituBiosRecord* p){if(p==0){return 1;}else{return p->kake;}}
FightWazaHitKakurituBiosRecord* fightWazaHitKakurituDataBiosGetPtr(u16 id){if(id>=fight_waza_hit_kakuritu_data_number)return 0;return &fight_waza_hit_kakuritu_data[id];}
u8 fightWazaCriticalDataBiosGetBunbo(FightWazaCriticalBiosRecord* p){if(p==0){return 0;}else{return p->bunbo;}}
FightWazaCriticalBiosRecord* fightWazaCriticalDataBiosGetPtr(u16 id){if(id>=fight_waza_critical_data_number)return 0;return &fight_waza_critical_data[id];}
void fightWazaBiosSetAutoMakeFlag(FightWazaRecord* p,u8 v){if(p)p->autoMakeFlag=v;}
void fightWazaBiosSetKaisuu(FightWazaRecord* p,u8 v){if(p)p->kaisuu=v;}
void fightWazaBiosSetZokusei(FightWazaRecord* p,u16 v){if(p)p->zokusei=v;}
void fightWazaBiosSetIryoku(FightWazaRecord* p,u16 v){if(p)p->iryoku=v;}
void fightWazaBiosSetHitDamage(FightWazaRecord* p,u32 v){if(p)p->hitDamage=v;}
void fightWazaBiosSetDamage(FightWazaRecord* p,u32 v){if(p)p->damage=v;}
void fightWazaBiosSetDamageValue(FightWazaRecord* p,u8 v){if(p)p->damageValue=v;}
void fightWazaBiosSetCritical(FightWazaRecord* p,u8 v){if(p)p->critical=v;}
void fightWazaBiosSetTargetDataId(FightWazaRecord* p,u16 v){if(p)p->targetDataId=v;}
void fightWazaBiosSetUseWazaDataId(FightWazaRecord* p,u16 v){if(p)p->useWazaDataId=v;}
void fightWazaBiosSetMotoWazaDataId(FightWazaRecord* p,u16 v){if(p)p->motoWazaDataId=v;}
void fightWazaBiosSetWazaBanme(FightWazaRecord* p,s8 v){if(p)p->wazaBanme=v;}
u8 fightWazaBiosGetAutoMakeFlag(FightWazaRecord* p){if(p==0){return 0;}else{return p->autoMakeFlag;}}
u8 fightWazaBiosGetKaisuu(FightWazaRecord* p){if(p==0){return 0;}else{return p->kaisuu;}}
u16 fightWazaBiosGetZokusei(FightWazaRecord* p){if(p==0){return 0;}else{return p->zokusei;}}
u16 fightWazaBiosGetIryoku(FightWazaRecord* p){if(p==0){return 0;}else{return p->iryoku;}}
u32 fightWazaBiosGetHitDamage(FightWazaRecord* p){if(p==0){return 0;}else{return p->hitDamage;}}
u32 fightWazaBiosGetDamage(FightWazaRecord* p){if(p==0){return 0;}else{return p->damage;}}
u8 fightWazaBiosGetDamageValue(FightWazaRecord* p){if(p==0){return 0;}else{return p->damageValue;}}
u8 fightWazaBiosGetCritical(FightWazaRecord* p){if(p==0){return 0;}else{return p->critical;}}
FightJoutai* fightWazaBiosGetJoutaiPtr(FightWazaRecord* p,u16 index){if(p==0)return 0;if(index>=9)return 0;return (FightJoutai*)((u8*)p+8+index*0x10);}
u16 fightWazaBiosGetTargetDataId(FightWazaRecord* p){if(p==0){return 0;}else{return p->targetDataId;}}
u16 fightWazaBiosGetUseWazaDataId(FightWazaRecord* p){if(p==0){return 0;}else{return p->useWazaDataId;}}
u16 fightWazaBiosGetMotoWazaDataId(FightWazaRecord* p){if(p==0){return 0;}else{return p->motoWazaDataId;}}
u8 fightWazaBiosGetWazaBanme(FightWazaRecord* p){if(p==0){return 0;}else{return p->wazaBanme;}}
void fightWazaBiosCopy(FightWazaRecord* dst,const FightWazaRecord* src){if(dst==0)return;if(src==0)return;dst->wazaBanme=src->wazaBanme;dst->motoWazaDataId=src->motoWazaDataId;dst->useWazaDataId=src->useWazaDataId;dst->targetDataId=src->targetDataId;const u32* s=(const u32*)src+1;u32* d=(u32*)dst+1;for(u32 i=0;i<0x12;++i){d[1]=s[1];++d;++s;d[1]=s[1];++d;++s;}dst->critical=src->critical;dst->damageValue=src->damageValue;dst->damage=src->damage;dst->hitDamage=src->hitDamage;dst->iryoku=src->iryoku;dst->zokusei=src->zokusei;dst->kaisuu=src->kaisuu;dst->autoMakeFlag=src->autoMakeFlag;}
}
