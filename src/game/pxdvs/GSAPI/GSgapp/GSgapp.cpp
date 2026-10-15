#include <global.h>
#include <libc/string.h>
struct GappJob {
    GappJob *previous,*next; s32 type,pauseLevel; u8 priority,blocked; u8 reserved12[2]; char name[32]; u32 data; void(*callback)(u32,u32);
};
static GappJob* _gappStructList;
static u32 _gappMaxJobs,_gappMaxBkgndJobs,_gappTotalJobs;
static u8 _gappPause;
static void* _gappBkgndStackPtr;
static GappJob *_gappCurrentGapp,*_gappListTop,*_gappCreateBGJobRequestListTop;
extern "C" {
s32 OSDisableInterrupts(); void OSRestoreInterrupts(s32);
void* GSmemAlloc(u32);
void OSSetIdleFunction(void(*)(),u32,void*,u32);
void GSgfxVideoSetVSyncCallback(void(*)());
void gappBackgroundCallback(); void gappVSyncCallback();
void GSgappSetName(u32 handle,const char* name) {
    if(name) { GappJob* job=&_gappStructList[handle-1]; memcpy(job->name,name,31); job->name[31]=0; }
}
void GSgappUnblock(u32 handle) { u32 index=handle-1; GappJob* job=&_gappStructList[index]; job->blocked=0; }
void GSgappSetPauseLevel(u32 handle,s32 level) { u32 index=handle-1; GappJob* job=&_gappStructList[index]; job->pauseLevel=level; }
void GSgappPauseOff() { _gappPause=0; }
void GSgappPauseOn() { _gappPause=1; }
void GSgappBlock(u32 handle) { u32 index=handle-1; GappJob* job=&_gappStructList[index]; job->blocked=1; }
void GSgappTerminate(u32 handle) {
    GappJob* job=&_gappStructList[handle-1];
    s32 interrupts=OSDisableInterrupts();
    if(job->previous) job->previous->next=job->next;
    if(job->next) job->next->previous=job->previous;
    if(_gappListTop==job) _gappListTop=job->next;
    job->previous=0; job->next=0;
    OSRestoreInterrupts(interrupts);
    job->type=0;
}
void GSgappUpdate() {
    GappJob* next;
    GappJob* job=_gappListTop;
    while(job) {
        next=job->next;
        if(job->type==1 && !job->blocked && (!_gappPause || job->pauseLevel==0)) {
            _gappCurrentGapp=job;
            job->callback(((u32)job-(u32)_gappStructList)/sizeof(GappJob)+1,job->data);
        }
        job=next;
    }
    _gappCurrentGapp=0;
}
}
static inline void insertJob(GappJob* job) {
    GappJob* next;
    GappJob* current=_gappListTop;
    while ((next=current->next)!=0 && current->priority<job->priority) current=next;
    if(!next && current->priority<job->priority) {
        job->previous=current; job->next=0; current->next=job;
    } else {
        if(current->previous) current->previous->next=job;
        job->previous=current->previous; job->next=current; current->previous=job;
        if(_gappListTop==current) _gappListTop=job;
    }
}
static inline GappJob* findJob(s32 type) {
    GappJob* job;
    u32 count;
    if(type==2) { job=&_gappStructList[_gappMaxJobs]; count=_gappMaxBkgndJobs; }
    else { job=_gappStructList; count=_gappMaxJobs; }
    while(count--) { if(job->type==0) return job; ++job; }
    return 0;
}
extern "C" {
u32 GSgappCreate(s32 type,u8 priority,u32 data,void(*callback)(u32,u32)) {
    GappJob* job=findJob(type);
    if(!job) return 0;
    job->previous=0; job->next=0; job->type=type; job->priority=priority; job->blocked=0; job->data=data; job->callback=callback; job->pauseLevel=0; job->name[0]=0;
    if(!_gappListTop) _gappListTop=job;
    else {
        s32 interrupts=OSDisableInterrupts();
        if(job->type==2) { job->next=_gappCreateBGJobRequestListTop; _gappCreateBGJobRequestListTop=job; }
        else insertJob(job);
        OSRestoreInterrupts(interrupts);
    }
    return ((u32)job-(u32)_gappStructList)/sizeof(GappJob)+1;
}
void GSgappInit(u32 jobs,u32 backgroundJobs) {
    _gappMaxJobs=jobs; _gappMaxBkgndJobs=backgroundJobs; _gappTotalJobs=jobs+backgroundJobs; _gappCurrentGapp=0;
    _gappStructList=(GappJob*)GSmemAlloc(_gappTotalJobs*sizeof(GappJob));
    if(_gappStructList) {
        for(u32 i=0;i<_gappTotalJobs;++i) _gappStructList[i].type=0;
        _gappBkgndStackPtr=GSmemAlloc(0x2000);
        OSSetIdleFunction(gappBackgroundCallback,0,(u8*)_gappBkgndStackPtr+0x1ffc,0x1ffc);
        GSgfxVideoSetVSyncCallback(gappVSyncCallback);
    }
}
void gappBackgroundCallback() {
    GappJob* next;
    for(;;) {
        GappJob* job=_gappListTop;
        while(job) {
            next=job->next;
            if(job->type==2 && !job->blocked && (!_gappPause || job->pauseLevel==0)) {
                _gappCurrentGapp=job;
                job->callback(((u32)job-(u32)_gappStructList)/sizeof(GappJob)+1,job->data);
            }
            job=next;
        }
        _gappCurrentGapp=0;
        s32 interrupts=OSDisableInterrupts();
        job=_gappCreateBGJobRequestListTop;
        while(job) {
            GappJob* next=job->next;
            insertJob(job);
            job=next;
        }
        _gappCreateBGJobRequestListTop=0;
        OSRestoreInterrupts(interrupts);
    }
}
void gappVSyncCallback() {
    GappJob* next;
    GappJob* job=_gappListTop;
    while(job) {
        next=job->next;
        if(job->type==3 && !job->blocked && (!_gappPause || job->pauseLevel==0)) {
            _gappCurrentGapp=job;
            job->callback(((u32)job-(u32)_gappStructList)/sizeof(GappJob)+1,job->data);
        }
        job=next;
    }
    _gappCurrentGapp=0;
}
}
