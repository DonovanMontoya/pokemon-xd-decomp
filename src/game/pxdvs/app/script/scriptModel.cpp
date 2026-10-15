#include <global.h>
extern "C" {
static u8 script_model_num;
u32 floorGetCurrentGroupID();
void* GSresGetResource(u32,u32);
u32 peopleGetHumanID(u32,u32);
u32 peopleOpen(u32,u32,u32);
void* peopleSearchID(u32);
void* peopleBiosGetModelPtr(void*);
void peopleClose(u32,u32,u32);
void peopleSetDisp(u32,u32,u8);
void peopleSetMotionForce(u32,u32,u32,s32,u8);
void peopleStopMotion(u32,u32);
u8 peopleWaitSyncMotion(u32,u32,u8);
void peopleDetach(u32,u32,u32);
void peopleAttach(u32,u32,u32,u32,u32);
void GSmodelSetForceUseFractionalFramesFlag(void*,u32);
void* GSmodelGetPart(void*,u32);
void* GSparticleCreateGenerator(void*,u32,u32);
void GSparticleAttachGeneratorToGSpart(void*,void*,u32,u32,u32,u32);
void GSparticleDestroyAllGenerators(void*,u32);
void GSpartFree(void*);
void GSmodelLinkToGSparticleBank(void*,void*);
void GSmodelSetGSparticleLinkAttachMode(void*,u32);
void GSmodelDetachFromGSpart(void*,u32);
void GSmodelAttachToGSpart(void*,void*,u32,u32,u32);
u8 GSmodelHasAnimationEnded(void*);
void GSthreadSwitch();
void GSmodelStopAnimation(void*);
void GSmodelSetAnimIndex(void*,u32);
void GSmodelSetTexAnimIndex(void*,u32);
void GSmodelSetAnimFrame(void*,f32);
void GSmodelSetTexAnimFrame(void*,f32);
void GSmodelSetAnimRate(void*,f32);
void GSmodelSetTexAnimRate(void*,f32);
void GSmodelSetAnimType(void*,u32);
void GSmodelStartAnimation(void*);
void GSmodelSetVisibility(void*,u8);
void GSmodelSetBoundCheck(void*,u32);
#pragma dont_inline on
void scriptModelSetFractionalFramesFlag(u32 id,u32 flag){GSmodelSetForceUseFractionalFramesFlag(GSresGetResource(floorGetCurrentGroupID(),id),flag);}
void scriptModelPartPaticle(u32 model,u32 particle,u32 part){
    void* joint=GSmodelGetPart(GSresGetResource(floorGetCurrentGroupID(),model),part);
    void* generator=GSparticleCreateGenerator(GSresGetResource(floorGetCurrentGroupID(),particle),0,0);
    GSparticleAttachGeneratorToGSpart(generator,joint,7,0,1,0);
    GSpartFree(joint);
}
void scriptModelDeleteParticle(u32 id,u32 mode){GSparticleDestroyAllGenerators(GSresGetResource(floorGetCurrentGroupID(),id),mode);}
void scriptModelSetParticle(u32 id,u32 particle){
    void* model=GSresGetResource(floorGetCurrentGroupID(),id);
    GSmodelLinkToGSparticleBank(model,GSresGetResource(floorGetCurrentGroupID(),particle));
    GSmodelSetGSparticleLinkAttachMode(model,4);
}
s32 scriptModelDetach(u32 id){
    u32 group=floorGetCurrentGroupID();
    if(peopleGetHumanID(group,id))peopleDetach(group,id,0);
    else {
        void* model=GSresGetResource(group,id);
        if(!model)return 0;
        GSmodelDetachFromGSpart(model,1);
    }
    return 1;
}
s32 scriptModelAttach(u32 id,u32 parent,u32 part){
    u32 group=floorGetCurrentGroupID();
    if(peopleGetHumanID(group,id))peopleAttach(group,id,group,parent,part);
    else{
        void* model=GSresGetResource(group,id);
        if(!model)return 0;
        void* parentModel=GSresGetResource(group,parent);
        if(!parentModel)return 0;
        void* joint=GSmodelGetPart(parentModel,part);
        GSmodelAttachToGSpart(model,joint,7,0,1);
        GSpartFree(joint);
    }
    return 1;
}
u8 scriptModelWaitMotion(u32 id,u32 wait){
    u32 group=floorGetCurrentGroupID();
    if(peopleGetHumanID(group,id))return peopleWaitSyncMotion(group,id,wait!=0);
    void* model=GSresGetResource(group,id);
    if(!model)return 0;
    for(;;){
        if(GSmodelHasAnimationEnded(model))return 0;
        if(wait)GSthreadSwitch();else break;
    }
    return 1;
}
void scriptModelStopMotion(u32 id){
    u32 group=floorGetCurrentGroupID();
    if(peopleGetHumanID(group,id))peopleStopMotion(group,id);
    else{void* model=GSresGetResource(group,id);if(model)GSmodelStopAnimation(model);}
}
s32 scriptModelSetEndedMotion(u32 id,u32 index,u8 loop){
    void* model=GSresGetResource(floorGetCurrentGroupID(),id);
    if(!model)return 0;
    while(!GSmodelHasAnimationEnded(model))GSthreadSwitch();
    GSmodelSetAnimIndex(model,index);GSmodelSetAnimFrame(model,0.0f);GSmodelSetAnimRate(model,0.5f);
    GSmodelSetTexAnimIndex(model,index);GSmodelSetTexAnimFrame(model,0.0f);GSmodelSetTexAnimRate(model,0.5f);
    if(loop)GSmodelSetAnimType(model,1);else GSmodelSetAnimType(model,0);
    GSmodelStartAnimation(model);return 1;
}
void scriptModelSetMotionRate(u32 id,u32 index,s32 frame,f32 rate,u32 loop){
    u32 group=floorGetCurrentGroupID();
    if(peopleGetHumanID(group,id))peopleSetMotionForce(group,id,index,frame,loop!=0);
    else{
        void* model=GSresGetResource(group,id);
        if(model){
            GSmodelSetAnimIndex(model,index);GSmodelSetAnimFrame(model,(f32)frame);GSmodelSetAnimRate(model,rate);
            GSmodelSetTexAnimIndex(model,index);GSmodelSetTexAnimFrame(model,(f32)frame);GSmodelSetTexAnimRate(model,rate);
            if(loop)GSmodelSetAnimType(model,1);else GSmodelSetAnimType(model,0);
            GSmodelStartAnimation(model);
        }
    }
}
void scriptModelSetMotion(u32 id,u32 index,s32 frame,u32 loop){
    u32 group=floorGetCurrentGroupID();
    if(peopleGetHumanID(group,id))peopleSetMotionForce(group,id,index,frame,loop!=0);
    else{
        void* model=GSresGetResource(group,id);
        if(model){
            GSmodelSetAnimIndex(model,index);GSmodelSetAnimFrame(model,(f32)frame);GSmodelSetAnimRate(model,0.5f);
            GSmodelSetTexAnimIndex(model,index);GSmodelSetTexAnimFrame(model,(f32)frame);GSmodelSetTexAnimRate(model,0.5f);
            if(loop)GSmodelSetAnimType(model,1);else GSmodelSetAnimType(model,0);
            GSmodelStartAnimation(model);
        }
    }
}
void scriptModelSetDisp(u32 id,u32 show){
    u32 group=floorGetCurrentGroupID();
    if(peopleGetHumanID(group,id))peopleSetDisp(group,id,show!=0);
    else {void* model=GSresGetResource(group,id);if(model)GSmodelSetVisibility(model,show!=0);}
}
void scriptModelClose(u32 id){peopleClose(floorGetCurrentGroupID(),id,0);}
u32 scriptModelOpen(u32 object){
    u32 id=(s8)script_model_num|0x7ffe0000;
    ++script_model_num;
    u32 person=peopleOpen(floorGetCurrentGroupID(),id,object);
    if(!person)return 0;
    GSmodelSetBoundCheck(peopleBiosGetModelPtr(peopleSearchID(person)),0);
    return id;
}
void scriptModelInit(){script_model_num=0;}
}
