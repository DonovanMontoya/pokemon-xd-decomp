#include <game/pxdvs/app/people/runtime.hpp>
#include <libc/stddef.h>
struct _GSmodel;
struct GSpart;
enum GSmodelAnimType { PEOPLE_PART_ANIM_ONCE, PEOPLE_PART_ANIM_LOOP };
static s32 _peoplePartAnimationStartAnimation(_GSmodel*,s8,int,f32,GSmodelAnimType);
typedef char SpeechAnimationsOffset[offsetof(tagPeopleWork,speechAnimations)==0x190?1:-1];
typedef char SpeechTimerOffset[offsetof(tagPeopleWork,speechTimer)==0x1ac?1:-1];
typedef char BlinkTimerOffset[offsetof(tagPeopleWork,blinkTimer)==0x148?1:-1];
extern "C" {
u8 peopleBiosCheckFlag(tagPeopleWork*,u32);
GSpart* GSmodelGetPart(_GSmodel*,s32);
void GSpartStopAnimIndex(GSpart*,s32);
void GSpartFree(GSpart*);
s32 GSpartSetAnimIndex(GSpart*,s32,f32,GSmodelAnimType);
void GSmodelSetKeepPartAnimFlag(_GSmodel*,u32);
void GSmodelLinkTexAnimToAnim(_GSmodel*,u32);
void GSmodelSetTexAnimIndex(_GSmodel*,u32);
void GSmodelSetTexAnimType(_GSmodel*,u32);
void GSmodelStartTexAnimation(_GSmodel*);
s32 HSD_Rand();
f32 timeGetLastFrameSec();
void peoplePartAnimationBlinkOnce(tagPeopleWork*);
#pragma dont_inline on
void peoplePartAnimationSpeakStop(tagPeopleWork* work){
    if(work && work->flag14D){
        _GSmodel* model=(_GSmodel*)work->model;
        PeopleInfo* info=peopleInfoBiosGetPtr(work->object);
        for(s32 i=0;i<7;i++){
            if(work->speechAnimations[i]>=0){
                GSpart* part=GSmodelGetPart(model,(s8)info->unknown28[i]);
                if(part){GSpartStopAnimIndex(part,work->speechAnimations[i]);GSpartFree(part);}
                work->speechAnimations[i]=-1;
            }
        }
        work->flag14D=0;
    }
}
void peoplePartAnimationSpeakStart(tagPeopleWork* work){
    u8 started=0;
    if(work){
        _GSmodel* model=(_GSmodel*)work->model;
        PeopleInfo* info=peopleInfoBiosGetPtr(work->object);
        if(!peopleBiosCheckFlag(work,0x20000) && !work->flag14D){
            for(s32 i=0;i<7;i++){
                work->speechAnimations[i]=_peoplePartAnimationStartAnimation(model,(s8)info->unknown28[i],2,0.0f,PEOPLE_PART_ANIM_LOOP);
                if(work->speechAnimations[i]>=0)started=1;
            }
            if(started){work->flag14D=1;GSmodelSetKeepPartAnimFlag(model,0);work->speechTimer=1.5f;}
        }
    }
}
void peoplePartAnimationBlinkStop(tagPeopleWork* work){
    if(work){work->flag14C=0;_GSmodel* model=(_GSmodel*)work->model;if(model)GSmodelSetKeepPartAnimFlag(model,0);}
}
void peoplePartAnimationBlinkStart(tagPeopleWork* work){
    if(work && !peopleBiosCheckFlag(work,0x10000)){
        work->flag14C=1;work->blinkTimer=(f32)(HSD_Rand()&0x7fff)/65536.0f;
    }
}
void peoplePartAnimationBlink(tagPeopleWork* work){
    if(work){
        if(work->flag14D){work->speechTimer-=timeGetLastFrameSec();if(work->speechTimer<0.0f)peoplePartAnimationSpeakStop(work);}
        if(work->flag14C){
            work->blinkTimer-=timeGetLastFrameSec();
            if(!(work->blinkTimer>0.0f)){f32 randomWait=(f32)(HSD_Rand()&0x7fff)/32768.0f;work->blinkTimer=randomWait+2.0f;peoplePartAnimationBlinkOnce(work);}
        }
    }
}
void peoplePartAnimationBlinkOnce(tagPeopleWork* work){
    if(work){
        _GSmodel* model=(_GSmodel*)work->model;
        PeopleInfo* info=peopleInfoBiosGetPtr(work->object);
        for(s32 i=0;i<4;i++)_peoplePartAnimationStartAnimation(model,(s8)info->unknown28[7+i],1,0.0f,PEOPLE_PART_ANIM_ONCE);
        GSmodelLinkTexAnimToAnim(model,0);GSmodelSetTexAnimIndex(model,1);GSmodelSetTexAnimType(model,0);GSmodelStartTexAnimation(model);
    }
}
}
static s32 _peoplePartAnimationStartAnimation(_GSmodel* model,s8 partIndex,int animation,f32 frame,GSmodelAnimType type){
    s32 index=-1;
    if(partIndex>=0){
        GSpart* part=GSmodelGetPart(model,partIndex);
        if(!part)return -1;
        index=GSpartSetAnimIndex(part,animation,frame,type);
        GSpartFree(part);
    }
    return index;
}
