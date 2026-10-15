#include <global.h>
extern "C" {
u32 HSD_Rand();
u8 fightFloor_GetFightType(void*);
u16 fightJoukenDataBiosGetLink(u16);
u8 fightJoukenDataBiosGetForm(u16);
u8 fightJoukenDataBiosGetValueKind(u16,u16);
u16 fightJoukenDataBiosGetValueTarget(u16,u16);
u16 fightJoukenDataBiosGetValueBuff(u16,u16);
s16 fightJoukenDataBiosGetValueKake(u16,u16);
s16 fightJoukenDataBiosGetValueWaru(u16,u16);
u8 fightJoukenDataBiosGetValueHoseiFlag(u16,u16);
u8 fightJoukenLinkDataBiosGetJoint(u16);
u16 fightJoukenLinkDataBiosGetJoukenDataId(u16);
u16 fightJoukenLinkDataBiosGetNextLinkDataId(u16);
void* fightTargetGetPtr(u16,void*,u16);
void* fightTargetDataBiosGetPtr(u16);
u8 fightTargetDataBiosGetStatusKid(void*);
s32 statusGetStatus(u8,void*,u16,u16,u16);
}
static u8 _fightJoukenExecOne(u16,void*);
static s32 _fightJoukenGetValue(u16,u16,void*);
extern "C" u8 fightJoukenExec(u16 id,void* target) {
    u8 result=_fightJoukenExecOne(id,target);
    u16 condition;
    u16 link=fightJoukenDataBiosGetLink(id);
    if(!link)return result;
    do {
        condition=fightJoukenLinkDataBiosGetJoukenDataId(link);
        u8 next=_fightJoukenExecOne(condition,target);
        switch(fightJoukenLinkDataBiosGetJoint(condition)) {
        case 1: if(result||next)result=1;else result=0;break;
        case 2: if(result&&next)result=1;else result=0;break;
        }
        link=fightJoukenLinkDataBiosGetNextLinkDataId(link);
    }while(link);
    return result;
}
static u8 _fightJoukenExecOne(u16 id,void* target) {
    s32 values[2];
    for(u8 i=0;i<2;++i)values[i]=_fightJoukenGetValue(id,i,target);
    u8 result=0;
    switch(fightJoukenDataBiosGetForm(id)) {
    case 0: result=1;break;
    case 1: if(values[0]==values[1])result=1;break;
    case 2: if(values[0]!=values[1])result=1;break;
    case 3: if(values[0]>=values[1])result=1;break;
    case 4: if(values[0]<=values[1])result=1;break;
    case 5: if(values[0]<values[1])result=1;break;
    case 6: if(values[0]>values[1])result=1;break;
    }
    return result;
}
static s32 _fightJoukenGetValue(u16 id,u16 index,void* target) {
    u16 selected,buff;
    s16 multiplier,divisor;
    u8 kind,adjust;
    s32 value=0;
    kind=fightJoukenDataBiosGetValueKind(id,index);
    selected=fightJoukenDataBiosGetValueTarget(id,index);
    buff=fightJoukenDataBiosGetValueBuff(id,index);
    multiplier=fightJoukenDataBiosGetValueKake(id,index);
    divisor=fightJoukenDataBiosGetValueWaru(id,index);
    adjust=fightJoukenDataBiosGetValueHoseiFlag(id,index);
    switch(kind) {
    case 0: break;
    case 1: value=selected;break;
    case 2: {
        value=HSD_Rand();
        u32 high=HSD_Rand()<<16;
        u32 random=high|(u32)value;
        u32 lowerBound=selected;
        value=lowerBound+(random%(u32)(buff-lowerBound));
        break;
    }
    case 3: {
        value=(s32)fightTargetGetPtr(selected,target,fightFloor_GetFightType(0));
        if(!value)return 0;
        u8 status=fightTargetDataBiosGetStatusKid(fightTargetDataBiosGetPtr(selected));
        if(!adjust)value=statusGetStatus(status,(void*)value,(u16)multiplier,buff,(u16)divisor);
        else value=statusGetStatus(status,(void*)value,0,buff,0);
        break;
    }
    }
    if(adjust==1) {
        value*=(s16)multiplier;
        if((s16)divisor)value/=(s16)divisor;
    }
    return value;
}
