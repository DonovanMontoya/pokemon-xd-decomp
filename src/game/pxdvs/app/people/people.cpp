#include <game/pxdvs/app/people/runtime.hpp>
#pragma dont_inline on
extern "C" {
f64 fmod(f64, f64);
f32 PSVECDistance(GSvec*, GSvec*);
tagPeopleWork* peopleBiosGetPeopleWork(u32, u32);
void peopleBiosGetRot(tagPeopleWork*, GSvec*);
void peopleBiosGetPos(tagPeopleWork*, GSvec*);
void peopleBiosSetRot(tagPeopleWork*, GSvec*);
void peopleBiosSetPos(tagPeopleWork*, GSvec*);
void peopleBiosSetPrevPos(tagPeopleWork*, GSvec*);
bool peopleBiosCheckFlag(tagPeopleWork*, u32);
void peopleBiosSetFlagOff(tagPeopleWork*, u32);
void peopleBiosSetFlagOn(tagPeopleWork*, u32);
void peopleBiosSetFlags(tagPeopleWork*, u32);
void peoplePartAnimationSpeakStop(tagPeopleWork*);
void peoplePartAnimationSpeakStart(tagPeopleWork*);
void peoplePartAnimationBlinkStop(tagPeopleWork*);
void peoplePartAnimationBlinkStart(tagPeopleWork*);
void peoplePartAnimationBlinkOnce(tagPeopleWork*);
void GSthreadSwitch();
void peopleWalkTo(u32, u32, u8, GSvec*);
f32 adjustPIPI__Ff(f32);
void peopleSetCollision(u32, u32, u8);
tagPeopleWork* peopleGet(u32 group, u32 resource) { return peopleBiosGetPeopleWork(group, resource); }
void peopleSpeakStop(u32 group, u32 resource) { peoplePartAnimationSpeakStop(peopleGet(group, resource)); }
void peopleSpeakStart(u32 group, u32 resource) { peoplePartAnimationSpeakStart(peopleGet(group, resource)); }
void peopleBlinkStop(u32 group, u32 resource) { peoplePartAnimationBlinkStop(peopleGet(group, resource)); }
void peopleBlinkStart(u32 group, u32 resource) { peoplePartAnimationBlinkStart(peopleGet(group, resource)); }
void peopleBlinkOnce(u32 group, u32 resource) { peoplePartAnimationBlinkOnce(peopleGet(group, resource)); }
f32 peopleGetSpeed(u32 group, u32 resource) {
    GSvec position;
    tagPeopleWork* work = peopleGet(group, resource);
    peopleBiosGetPos(work, &position);
    f32 distance = PSVECDistance(&position, &work->speedPosition);
    work->speedPosition.param1 = position.param1;
    work->speedPosition.param2 = position.param2;
    work->speedPosition.param3 = position.param3;
    return distance;
}
s32 peopleRunOrNot(u32 group, u32 resource) {
    GSvec position;
    tagPeopleWork* work = peopleGet(group, resource);
    peopleBiosGetPos(work, &position);
    f32 distance = PSVECDistance(&position, &work->speedPosition);
    work->speedPosition.param1 = position.param1;
    work->speedPosition.param2 = position.param2;
    work->speedPosition.param3 = position.param3;
    return distance > work->unknown20;
}
s32 peopleSpeedSlowDownOff(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    work->slowDown = 0; return 1;
}
s32 peopleSpeedSlowDownOn(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    work->slowDown = 1; return 1;
}
s32 peopleManualAnimation(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    work->manualAnimation = 1; return 1;
}
s32 peopleAutoAnimation(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    work->manualAnimation = 0; return 1;
}
void peopleTaskSwich() { GSthreadSwitch(); }
void peopleGetRot(u32 group, u32 resource, GSvec* value) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) peopleBiosGetRot(work, value);
}
void peopleGetPos(u32 group, u32 resource, GSvec* value) {
    if (value) {
        tagPeopleWork* work = peopleGet(group, resource);
        if (work) peopleBiosGetPos(work, value);
    }
}
void peopleSetRot(u32 group, u32 resource, GSvec* value) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        value->param1 = (f32)fmod(6.2831855f + value->param1, 6.2831854820251465);
        value->param2 = (f32)fmod(6.2831855f + value->param2, 6.2831854820251465);
        value->param3 = (f32)fmod(6.2831855f + value->param3, 6.2831854820251465);
        peopleBiosSetRot(work, value);
        work->targetRotation = value->param2;
    }
}
void peopleSetPos(u32 group, u32 resource, GSvec* value) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        peopleBiosSetPos(work, value);
        peopleBiosSetPrevPos(work, value);
        work->originPosition.param1 = value->param1;
        work->originPosition.param2 = value->param2;
        work->originPosition.param3 = value->param3;
    }
}
void peopleSetDisp(u32 group, u32 resource, u8 visible) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        peopleBiosSetDispFlag(work, visible);
        peopleSetCollision(group, resource, visible);
    }
}
bool peopleCheckFlag(u32 group, u32 resource, u32 flags) {
    tagPeopleWork* work = peopleGet(group, resource);
    bool result;
    if (!work) result = 0;
    else result = peopleBiosCheckFlag(work, flags);
    return result;
}
s32 peopleGetFlags(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    s32 result;
    if (!work) result = 0;
    else result = work->flags;
    return result;
}
void peopleSetFlagOff(u32 group, u32 resource, u32 flags) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) peopleBiosSetFlagOff(work, flags);
}
void peopleSetFlagOn(u32 group, u32 resource, u32 flags) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) peopleBiosSetFlagOn(work, flags);
}
void peopleSetFlags(u32 group, u32 resource, u32 flags) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) peopleBiosSetFlags(work, flags);
}
void peopleSetCollision(u32 group, u32 resource, u8 enabled) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        if (!work->visible) enabled = 0;
        peopleBiosSetCollision(work, enabled);
    }
}
void peopleWalkToXYZ(u32 group, u32 resource, u8 mode, f32 x, f32 y, f32 z) {
    GSvec position; position.param1 = x; position.param2 = y; position.param3 = z;
    peopleWalkTo(group, resource, mode, &position);
}
void peopleSetRotXYZ(u32 group, u32 resource, f32 x, f32 y, f32 z) {
    GSvec rotation; rotation.param1 = 0.017453292f * x; rotation.param2 = 0.017453292f * y; rotation.param3 = 0.017453292f * z;
    peopleSetRot(group, resource, &rotation);
}
void peopleSetPosXYZ(u32 group, u32 resource, f32 x, f32 y, f32 z) {
    GSvec position; position.param1 = x; position.param2 = y; position.param3 = z;
    peopleSetPos(group, resource, &position);
}
f32 peopleGetYDegreeRotation(u32 group, u32 resource) {
    GSvec rotation;
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0.0f;
    peopleBiosGetRot(work, &rotation);
    return 57.29578f * adjustPIPI__Ff(rotation.param2);
}

void GSmodelAllPauseAnimation();
void GSmodelAllUnpauseAnimation();
void peopleTalkLeaveFloor();
void floorBlockScriptThread(u16);
u32 timeGetLastFrameTime();
f32 timeGetLastFrameSec();
s32 peopleGetAnywaySaveSize();
s32 peopleBiosGetPushDataSize();
void peopleRestoreAnywaySaveData(void*, u32);
void peopleMakeAnywaySaveData(void*, u32);
void peopleBiosPopData(void*, u32);
void peopleBiosPushData(void*, u32);
void _peopleCloseSub__FP13tagPeopleWorkbb(tagPeopleWork*, u8, u8);
static u8 m_peopleBlock;
u8 peopleIsBlock() { return m_peopleBlock; }
void peopleUnblock() {
    if (m_peopleBlock) { m_peopleBlock = 0; GSmodelAllUnpauseAnimation(); }
}
void peopleBlock() {
    if (!m_peopleBlock) { m_peopleBlock = 1; GSmodelAllPauseAnimation(); }
}
void _peopleExitFloor__FUi14FloorEnterMode(u32 floor, s32 mode) {
    peopleTalkLeaveFloor();
    if (mode != 1) {
        s32 index = peopleBiosGetMaxNum();
        while (index-- > 0) {
            tagPeopleWork* work = peopleBiosGetWorkPtr(index);
            if (work->used) work->walkActive = 0;
        }
    }
}
const char* _peopleGetModuleName__Fv() { return "people"; }
s32 _peopleGetMagicNumber__Fv() { return 0x13; }
s32 _peopleGetStateSize__F14FloorStateMode(s32 mode) {
    if (mode == 3) return peopleGetAnywaySaveSize();
    if (mode == 1) return peopleBiosGetPushDataSize();
    return 0;
}
void _peopleRestoreStateData__F14FloorStateModePvUl(s32 mode, void* buffer, u32 size) {
    if (mode == 3) peopleRestoreAnywaySaveData(buffer, size);
    else if (mode == 1) peopleBiosPopData(buffer, size);
}
void _peopleMakeStateData__F14FloorStateModePvUl(s32 mode, void* buffer, u32 size) {
    if (mode == 3) peopleMakeAnywaySaveData(buffer, size);
    else if (mode == 1) peopleBiosPushData(buffer, size);
}
s32 _peopleBlockMoveScript__FP13tagPeopleWork(tagPeopleWork* work) {
    if (!work) return 0;
    work->state = 0;
    floorBlockScriptThread(work->moveScriptThread);
    return 1;
}
void peopleAllBlockMoveScript() {
    for (s32 index = 0; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->used) _peopleBlockMoveScript__FP13tagPeopleWork(work);
    }
}
void peopleAllClose(u8 freeResource) {
    for (s32 index = 0; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->used) _peopleCloseSub__FP13tagPeopleWorkbb(work, freeResource, 0);
    }
}
void peopleClose(u32 group, u32 resource, u8 freeResource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) _peopleCloseSub__FP13tagPeopleWorkbb(work, 1, freeResource);
}
s32 peopleRotateCheck(u32 group, u32 resource, u8 wait) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    for (;;) {
        if (!work->unknown0E) return 0;
        if (wait) GSthreadSwitch();
        else return 1;
    }
}
f32 _getLastFrameSec__Fv() { return timeGetLastFrameSec(); }
u32 _getLastFrameTime__Fv() { return timeGetLastFrameTime(); }

void GSmodelGetAnimIndex(GSmodel*, s32*, s32*);
u8 GSmodelHasAnimationEnded(GSmodel*);
u8 GSmodelIsAnimating(GSmodel*);
void GSmodelStopAnimation(GSmodel*);
void GSmodelSetTexAnimIndex(GSmodel*, s32);
void GSmodelSetTexAnimFrame(GSmodel*, f32);
void GSmodelSetTexAnimRate(GSmodel*, f32);
void GSmodelEnableAnimBlend(GSmodel*);
void GSmodelSetAnimRate(GSmodel*, f32);
void GSmodelSetBlendFactor(GSmodel*, f32);
void GSmodelGetFrameCount(GSmodel*, f32*, f32*);
void GSmodelSetBlendAnimFrameForce(GSmodel*, f32, f32);
void setAnimIndex__13tagPeopleWorkFi(tagPeopleWork*, s32);
void setAnimFrame__13tagPeopleWorkFf(tagPeopleWork*, f32);
void setAnimRate__13tagPeopleWorkFfb(tagPeopleWork*, f32, u8);
void setAnimType__13tagPeopleWorkF15GSmodelAnimType(tagPeopleWork*, s32);
void setAnimBlend__13tagPeopleWorkFii(tagPeopleWork*, s32, s32);
f32 peopleViewerGetPlaySpeedRate(tagPeopleWork*);
u8 isAnimLast__13tagPeopleWorkCFv(tagPeopleWork*);
void GSlogWrite(const char*, ...);
void peopleSetMotionType(tagPeopleWork*, s32);
void _peopleSetMotionSub__FP13tagPeopleWorkP8_GSmodelllb(tagPeopleWork*, GSmodel*, s32, s32, bool);

s32 peopleWalkPauseTalkMode(u32 group, u32 resource, u8 pause) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    if (pause) {
        work->savedWalkMode = work->walkActive;
        switch (work->walkActive) {
        case 4: case 5: work->walkActive = 0; break;
        }
    } else {
        switch (work->savedWalkMode) {
        case 4: case 5:
            work->walkActive = work->savedWalkMode;
            work->walkPhase = 0;
            work->motionFrame = 1.0f;
            break;
        }
    }
    return 1;
}
s32 peopleWalkPause(u32 group, u32 resource, u8 pause) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    if (!work->walkActive) return 1;
    if (pause) {
        if (!work->walkPaused) {
            work->walkPaused = 1;
            peopleSetMotionType(work, 1);
        }
        return 1;
    }
    if (work->walkPaused) work->walkPaused = 0;
    return 0;
}
void peopleStopMotion(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        GSmodel* model = peopleBiosGetModelPtr(work);
        if (model) GSmodelStopAnimation(model);
    }
}
void peopleSetMotionForce(u32 group, u32 resource, s32 index, s32 frame, bool loop) {
    if (index >= 0) {
        tagPeopleWork* work = peopleGet(group, resource);
        if (work) {
            GSmodel* model = peopleBiosGetModelPtr(work);
            if (model) _peopleSetMotionSub__FP13tagPeopleWorkP8_GSmodelllb(work, model, index, frame, loop);
        }
    }
}
void _peopleSetMotionSub__FP13tagPeopleWorkP8_GSmodelllb(tagPeopleWork* work, GSmodel* model, s32 index, s32 frame, bool loop) {
    work->requestedMotion = index;
    work->motionBlendStep = 0.0f;
    setAnimIndex__13tagPeopleWorkFi(work, index);
    setAnimFrame__13tagPeopleWorkFf(work, (f32)frame);
    setAnimRate__13tagPeopleWorkFfb(work, 0.5f, 1);
    GSmodelSetTexAnimIndex(model, index);
    GSmodelSetTexAnimFrame(model, (f32)frame);
    GSmodelSetTexAnimRate(model, 0.5f * peopleViewerGetPlaySpeedRate(work));
    if (loop) setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 1);
    else setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 0);
    work->flags |= 0x4000;
}
u8 _peopleSetMotionMain(u32 group, u32 resource, s32 index, s32 frame, bool loop) {
    GSmodel* model;
    u8 changed;
    tagPeopleWork* work;
    changed = 0;
    if (index < 0) return 0;
    work = peopleGet(group, resource);
    if (!work) return 0;
    model = peopleBiosGetModelPtr(work);
    if (!model) return 0;
    if (GSmodelHasAnimationEnded(model)) changed = 1;
    else if (!GSmodelIsAnimating(model)) changed = 1;
    else {
        s32 first, second;
        GSmodelGetAnimIndex(model, &first, &second);
        if (first != index || second != -1) changed = 1;
    }
    if (changed) _peopleSetMotionSub__FP13tagPeopleWorkP8_GSmodelllb(work, model, index, frame, loop);
    if (loop) setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 1);
    else setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 0);
    return changed;
}
s32 peopleSetMotion(u32 group, u32 resource, s32 index, s32 frame, bool loop) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    u8 manual = work->manualAnimation;
    u8 changed = _peopleSetMotionMain(group, resource, index, frame, loop);
    return changed ? manual : 0;
}
s32 peopleSetAnimBlend(u32 group, u32 resource, s32 first, s32 second, u32 frames) {
    GSmodel* model;
    tagPeopleWork* work;
    if (first < 0 || second < 0) return 0;
    if (frames < 1) return 0;
    work = peopleGet(group, resource);
    if (!work) return 0;
    model = peopleBiosGetModelPtr(work);
    if (!model) return 0;
    work->requestedMotion = second;
    work->motionBlendStep = 1.0f / (f32)frames;
    work->motionBlend = 0.0f;
    GSmodelEnableAnimBlend(work->model);
    work->animationBlend = 1;
    setAnimBlend__13tagPeopleWorkFii(work, first, second);
    setAnimFrame__13tagPeopleWorkFf(work, 0.0f);
    GSmodelSetAnimRate(model, 0.0f);
    GSmodelSetBlendFactor(model, work->motionBlend);
    setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 0);
    f32 count;
    GSmodelGetFrameCount(model, &count, 0);
    GSmodelSetBlendAnimFrameForce(model, count - 1.5f, 0.0f);
    return 1;
}
s32 peopleWaitSyncMotion(u32 group, u32 resource, u8 wait) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    GSlogWrite("[%s] people[%d,%d]\n", __FUNCTION__, group, resource);
    for (;;) {
        if (isAnimLast__13tagPeopleWorkCFv(work)) {
            GSlogWrite("anm endl people[%d,%d]  %08xh\n", group, resource, work->flags);
            break;
        } else if (wait) GSthreadSwitch();
        else break;
    }
    return 1;
}

u32 GSmodelGetMaxAnimIndex(GSmodel*);
f32 GSmodelGetAnimFrameCount(GSmodel*, u32);
u8 GSmodelIsNullAnimation(GSmodel*, u32);
f32 peopleInfoBiosGetWalkLength(PeopleInfo*);
f32 peopleInfoBiosGetRunLength(PeopleInfo*);
s32 _peopleSetAutoMotionFrameCount__FP13tagPeopleWork(tagPeopleWork*);
void _peopleValidMotionTable__FP8_GSmodelP18_peopleMotionTable(GSmodel* model, PeopleMotionTable* table) {
    if (model) {
        if (GSmodelIsNullAnimation(model, table->walkStart)) table->walkStart = -1;
        if (GSmodelIsNullAnimation(model, table->walk)) table->walk = -1;
        if (GSmodelIsNullAnimation(model, table->runStart)) table->runStart = -1;
        if (GSmodelIsNullAnimation(model, table->run)) table->run = -1;
    }
}
s32 peopleSetDefaultMotionTable(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    work->motions.idle = 3;
    work->motions.walk = 5;
    work->motions.run = 8;
    work->motions.walkStart = 4;
    work->motions.runStart = 7;
    _peopleValidMotionTable__FP8_GSmodelP18_peopleMotionTable(work->model, &work->motions);
    _peopleSetAutoMotionFrameCount__FP13tagPeopleWork(work);
    return 1;
}
s32 peopleSetMotionTable(u32 group, u32 resource, PeopleMotionTable* table) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    work->motions.idle = table->idle;
    work->motions.walk = table->walk;
    work->motions.run = table->run;
    work->motions.walkStart = table->walkStart;
    work->motions.runStart = table->runStart;
    _peopleValidMotionTable__FP8_GSmodelP18_peopleMotionTable(work->model, &work->motions);
    _peopleSetAutoMotionFrameCount__FP13tagPeopleWork(work);
    return 1;
}
s32 _peopleSetAutoMotionFrameCount__FP13tagPeopleWork(tagPeopleWork* work) {
    s32 maxIndex;
    u8 running;
    PeopleInfo* info;
    f32 walkLength = 1.0f;
    running = 0;
    f32 runLength = 1.0f;
    if (work->unknown28 > (0.3f + work->unknown20)) running = 1;
    maxIndex = GSmodelGetMaxAnimIndex(work->model);
    info = peopleInfoBiosGetPtr(work->object);
    if (info) {
        walkLength = peopleInfoBiosGetWalkLength(info);
        runLength = peopleInfoBiosGetRunLength(info);
    }
    if (maxIndex >= work->motions.walkStart && maxIndex >= work->motions.walk &&
        maxIndex >= work->motions.runStart && maxIndex >= work->motions.run &&
        (!info || !((info->flags >> 1) & 1))) {
        if (work->motions.walkStart >= 0) work->walkStartFrames = GSmodelGetAnimFrameCount(work->model, work->motions.walkStart);
        if (work->motions.walk >= 0) work->walkFrames = GSmodelGetAnimFrameCount(work->model, work->motions.walk);
        if (work->motions.runStart >= 0) work->runStartFrames = GSmodelGetAnimFrameCount(work->model, work->motions.runStart);
        if (work->motions.run >= 0) work->runFrames = GSmodelGetAnimFrameCount(work->model, work->motions.run);
        if (!info) return 0;
        work->unknown20 = walkLength / (work->walkFrames > 0.0f ? work->walkFrames : 30.0f);
        work->unknown24 = runLength / (work->runFrames > 0.0f ? work->runFrames : 17.0f);
        if (GSmodelIsNullAnimation(work->model, work->motions.walk)) work->unknown20 = 0.35f;
        if (GSmodelIsNullAnimation(work->model, work->motions.run)) work->unknown24 = 1.53f;
        if (!running) work->unknown28 = work->unknown20;
        else work->unknown28 = work->unknown24;
        return 1;
    }
    if (info) {
        work->unknown20 = walkLength / 30.0f;
        work->unknown24 = runLength / 17.0f;
    } else {
        work->unknown20 = 0.35f;
        work->unknown24 = 1.53f;
    }
    work->unknown28 = work->unknown20;
    return 0;
}
void peopleUnsetWaitAnimation(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    work->waitAnimation = 0;
}
void peopleSetWaitAnimation(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    _peopleSetMotionMain(group, resource, work->motions.idle, 0, 1);
    work->waitAnimation = 1;
}
f32 peopleGetBlendFactor(f32 value, f32 start, f32 end) {
    f32 difference = start - end;
    if (difference < 0.00001f && difference > -0.00001f) return 0.0f;
    f32 factor = (value - start) / (end - start);
    if (factor > 1.0f) return 1.0f;
    if (factor < 0.0f) return 0.0f;
    return factor;
}
void peopleSetWalkSpeed(u32 group, u32 resource, u32 mode, f32 speed) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        if (!work->model) return;
        if (mode == 1) { work->unknown20 = speed / work->walkFrames; return; }
        work->unknown24 = speed / work->runFrames;
    }
}

f64 fabs(f64);
#define fabs __fabs
struct GSpart;
GSpart* GSmodelGetPart(GSmodel*, u32);
void GSpartGetTransform(GSpart*, GSvec*, GSvec*, GSvec*);
void GSpartFree(GSpart*);
GSvec* peopleBiosGetPosPtr(tagPeopleWork*);
GSvec* peopleBiosGetRotPtr(tagPeopleWork*);
s8 peopleInfoBiosGetNeckIndex(PeopleInfo*);
f32 peopleInfoBiosGetNeckLeftLimit(PeopleInfo*);
f32 peopleInfoBiosGetNeckRightLimit(PeopleInfo*);
f32 peopleInfoBiosGetNeckUpLimit(PeopleInfo*);
f32 peopleInfoBiosGetNeckDownLimit(PeopleInfo*);
tagPeopleWork* peopleBiosGetTresureIDToPeopleWork(u16);
u8 floorIsRunningThread(u16);
s32 floorIsCurentScriptMode();
void floorUnblockScriptThread(u16);
u16 floorExecScriptResThread(u32, u32, u32);
void _peopleUpdateNeck__FP13tagPeopleWorkf(tagPeopleWork*, f32);

f32 _peopleGetNearAngle__Ff(f32 angle) {
    if ((f32)fabs(angle) >= 3.1415927f) {
        if (angle < 0.0f) return 6.2831855f + angle;
        return angle - 6.2831855f;
    }
    return angle;
}
f32 adjustPIPI__Ff(f32 angle) {
    f32 result = (f32)fmod(6.2831855f + angle, 6.2831854820251465);
    if (result > 3.1415927f) result -= 6.2831855f;
    return result;
}
f32 adjust2PI__Ff(f32 angle) { return (f32)fmod(6.2831855f + angle, 6.2831854820251465); }
f32 _peopleGetDiffAngle__Fff(f32 first, f32 second) {
    f32 wrapped = adjustPIPI__Ff(first);
    return _peopleGetNearAngle__Ff(wrapped - adjustPIPI__Ff(second));
}
f32 _peopleGetDiffAngleFix__Fff(f32 first, f32 second) { return _peopleGetDiffAngle__Fff(first, second); }
f32 _peopleGetDiffAngleFixForNeck__FffP13tagPeopleWork(f32 first, f32 second, tagPeopleWork* work) { return _peopleGetDiffAngle__Fff(first, second); }
void peopleGetPartsPos(u32 group, u32 resource, s32 index, GSvec* result) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        if (index >= 0) {
            GSpart* part = GSmodelGetPart(work->model, index);
            if (part) { GSpartGetTransform(part, result, 0, 0); GSpartFree(part); }
        } else {
            GSvec* position = peopleBiosGetPosPtr(work);
            result->param1 = position->param1;
            result->param2 = position->param2;
            result->param3 = position->param3;
        }
    }
}
void peopleGetNeckPos(u32 group, u32 resource, GSvec* result) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
        if (info) {
            peopleGetPartsPos(group, resource, peopleInfoBiosGetNeckIndex(info), result);
            result->param2 = peopleBiosGetPosPtr(work)->param2;
        }
    }
}
struct PeopleNeckInfo {
    s8 index;
    u8 reserved[3];
    f32 left, right, up, down;
    GSvec position, rotation;
};
u8 _getNeck__FP13tagPeopleWorkP14PeopleNeckInfo(tagPeopleWork* work, PeopleNeckInfo* neck) {
    if (!neck) return 0;
    peopleBiosGetRot(work, &neck->rotation);
    PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
    if (!info) return 0;
    neck->index = peopleInfoBiosGetNeckIndex(info);
    if (neck->index < 0) return 0;
    neck->left = peopleInfoBiosGetNeckLeftLimit(info);
    neck->right = peopleInfoBiosGetNeckRightLimit(info);
    neck->up = peopleInfoBiosGetNeckUpLimit(info);
    neck->down = peopleInfoBiosGetNeckDownLimit(info);
    GSpart* part = GSmodelGetPart(work->model, neck->index);
    if (!part) return 0;
    GSpartGetTransform(part, &neck->position, 0, 0);
    GSpartFree(part);
    return 1;
}
bool _peopleIsMoving__FP13tagPeopleWork(tagPeopleWork* work) {
    if (work->state) return 1;
    return floorIsRunningThread(work->moveScriptThread) == 0;
}
void _peopleDoNeckUpdate(tagPeopleWork* work) { _peopleUpdateNeck__FP13tagPeopleWorkf(work, 75.0f); }
f32 _peopleGetNeckRotationCB__FP6GSpart13GSpartMixTypePvP5GSvec(GSpart* part, s32 type, void* context, GSvec* result) {
    tagPeopleWork* work = (tagPeopleWork*)context;
    if (_peopleIsMoving__FP13tagPeopleWork(work) && !work->walkPaused) _peopleDoNeckUpdate(work);
    result->param1 = work->neckRotation.param1;
    result->param2 = work->neckRotation.param2;
    result->param3 = work->neckRotation.param3;
    return 1.0f;
}
f32 _peopleGetChestRotationCB__FP6GSpart13GSpartMixTypePvP5GSvec(GSpart* part, s32 type, tagPeopleWork* work, GSvec* result) {
    result->param1 = work->chestRotation.param1;
    result->param2 = work->chestRotation.param2;
    result->param3 = work->chestRotation.param3;
    return 1.0f;
}
void peopleSetNeckTargetXYZ(u32 group, u32 resource, s32 x, s32 y, s32 z) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        work->neckTargetPosition.param1 = (f32)x;
        work->neckTargetPosition.param2 = (f32)y;
        work->neckTargetPosition.param3 = (f32)z;
        work->neckEnabled = 2;
        work->neckMaxStep = 3.1415927f;
        work->neckMinStep = 3.1415927f;
        work->neckUnknownC3 = 0;
        work->neckInstant = 1;
    }
}
void peopleSetNeckTarget(u32 group, u32 resource, u32 targetGroup, u32 targetResource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        work->neckEnabled = 1;
        work->neckTargetGroup = targetGroup;
        work->neckTargetResource = targetResource;
        work->neckMaxStep = 3.1415927f;
        work->neckMinStep = 3.1415927f;
        work->neckUnknownC3 = 0;
        work->neckInstant = 1;
    }
}
void peopleSetNeckTargetHero(u32 group, u32 resource) { peopleSetNeckTarget(group, resource, 0, 100); }
void peopleMoveNeckTarget(u32 group, u32 resource, u32 targetGroup, u32 targetResource, f32 rate) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        work->neckEnabled = 1;
        work->neckTargetGroup = targetGroup;
        work->neckTargetResource = targetResource;
        work->neckUpdating = 1;
        work->neckUnknownC3 = 0;
        work->neckInstant = 0;
        if (rate > 0.0f) {
            f32 step = 0.07853982f * rate;
            work->neckMaxStep = step;
            work->neckMinStep = step / 2.0f;
            return;
        }
        work->neckMaxStep = 3.1415927f;
        work->neckMinStep = 3.1415927f;
    }
}
void peopleMoveNeckTargetHero(u32 group, u32 resource, f32 rate) { peopleMoveNeckTarget(group, resource, 0, 100, rate); }
void peopleMoveNeckTargetXYZ(u32 group, u32 resource, s32 x, s32 y, s32 z, f32 rate) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        work->neckTargetPosition.param1 = (f32)x;
        work->neckTargetPosition.param2 = (f32)y;
        work->neckTargetPosition.param3 = (f32)z;
        work->neckEnabled = 2;
        work->neckUpdating = 1;
        work->neckUnknownC3 = 0;
        work->neckInstant = 0;
        if (rate > 0.0f) {
            f32 step = 0.07853982f * rate;
            work->neckMaxStep = step;
            work->neckMinStep = step / 2.0f;
        } else {
            work->neckMaxStep = 3.1415927f;
            work->neckMinStep = 3.1415927f;
        }
    }
}
void peopleRemoveNeckTarget(u32 group, u32 resource, f32 rate) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        work->neckEnabled = 0;
        work->neckTargetRotation.param1 = 0.0f;
        work->neckTargetRotation.param2 = 0.0f;
        work->neckTargetRotation.param3 = 0.0f;
        work->neckUpdating = 1;
        work->neckUnknownC3 = 0;
        if (rate > 0.0f) {
            f32 step = 0.07853982f * rate;
            work->neckMaxStep = step;
            work->neckMinStep = step / 2.0f;
            work->neckInstant = 0;
            return;
        }
        work->neckInstant = 1;
        work->neckMaxStep = 3.1415927f;
        work->neckMinStep = 3.1415927f;
        work->neckRotation.param1 = 0.0f;
        work->neckRotation.param2 = 0.0f;
        work->neckRotation.param3 = 0.0f;
    }
}
void peopleSetMotionType(tagPeopleWork* work, s32 type) {
    s32 motion;
    bool loop;
    work->motionType = type;
    PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
    if (info) {
        peopleInfoBiosGetMotion(info, (u8)work->motionType, &motion, &loop);
        if (motion != -1) peopleSetMotion(work->group, work->resource, motion, 0, loop);
    }
}
void peopleSetTresureSearchDistance(u16 treasure, f32 distance) {
    tagPeopleWork* work = peopleBiosGetTresureIDToPeopleWork(treasure);
    if (work) work->treasureSearchDistance = distance;
}
tagPeopleWork* peopleSearchID(u32 identifier) {
    for (s32 index = 0; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->used && (u32)work->self == identifier) return work;
    }
    return 0;
}
u32 peopleGetHumanID(u32 group, u32 resource) {
    for (s32 index = 0; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->used && work->group == group && work->resource == resource) return (u32)work->self;
    }
    for (s32 index = 0; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->used && work->resource == resource) return (u32)work->self;
    }
    return 0;
}
s32 peopleUnblockMoveScript(u32 identifier) {
    tagPeopleWork* work = peopleSearchID(identifier);
    if (!work) return 0;
    work->state = 1;
    if (floorIsCurentScriptMode()) floorUnblockScriptThread(work->moveScriptThread);
    return 1;
}
void peopleBlockMoveScript(u32 identifier) { _peopleBlockMoveScript__FP13tagPeopleWork(peopleSearchID(identifier)); }
s32 peopleExecMoveScript(u32 group, u32 resource, u32 script) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    if (!script) return 0;
    work->moveScriptThread = floorExecScriptResThread(script, group, resource);
    return 1;
}
void _peopleClearTargetIfFollower__FUlUl(u32 group, u32 resource) {
    if (!group && (resource == 101 || resource == 104 || resource == 105)) {
        tagPeopleWork* work = peopleGet(group, resource);
        if (work) {
            work->walkTarget.param1 = peopleBiosGetPosPtr(work)->param1;
            work->walkTarget.param2 = peopleBiosGetPosPtr(work)->param2;
            work->walkTarget.param3 = peopleBiosGetPosPtr(work)->param3;
            work->walkActive = 0;
        }
    }
}
void peopleTermEvent(u32 group, u32 resource) {
    _peopleClearTargetIfFollower__FUlUl(group, resource);
    peopleSetFlagOn(group, resource, 0x100);
    peopleSetFlagOn(group, resource, 0x400);
    peopleSetFlagOff(group, resource, 0x80000000);
}
void peopleInitEvent(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work && work->followerMotion == 0) _peopleClearTargetIfFollower__FUlUl(group, resource);
    peopleSetFlagOff(group, resource, 0x100);
    peopleSetFlagOff(group, resource, 0x400);
    peopleSetFlagOn(group, resource, 0x80000000);
}

f64 atan2(f64, f64);
void PSVECSubtract(GSvec*, GSvec*, GSvec*);
f32 PSVECMag(GSvec*);
GSvec* GSmodelGetPositionPtr(GSmodel*);
void* GSresGetResource(u32, u32);
f32 GScolsys2HumanGetWalkHeight(GSvec*);
void _peopleSetMoveAnimation(tagPeopleWork*);
void peopleRotateToAngle(u32 group, u32 resource, f32 angle, f32 rate) {
    GSvec rotation;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        f32 target = adjustPIPI__Ff(angle);
        work->unknown0E = 1;
        work->targetRotation = target;
        peopleBiosGetRot(work, &rotation);
        work->initialRotation = rotation.param2;
        work->rotationProgress = 0.0f;
        work->rotationRate = rate;
    }
}
void peopleRotateStop(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        work->unknown0E = 0;
        work->targetRotation = peopleBiosGetRotPtr(work)->param2;
    }
}
void peopleRotateTo(u32 group, u32 resource, f32 angle) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        f32 rate = 1.0f;
        if (work->moveSpeed > (0.1f + work->unknown20)) rate = 2.0f;
        peopleBiosSetFlagOn(work, 8);
        peopleRotateToAngle(group, resource, 0.017453292f * angle, rate);
    }
}
f32 peopleVecCalcRotY(GSvec* from, GSvec* to, f32 current) {
    GSvec difference;
    PSVECSubtract(to, from, &difference);
    f32 angle = atan2(difference.param1, difference.param3);
    f32 result = (f32)fmod(6.2831855f + (angle - current), 6.2831854820251465);
    if (result > 3.1415927f) return result - 6.2831855f;
    if (result < -3.1415927f) result = 6.2831855f + result;
    return result;
}
void peopleRotateToXYZ(u32 group, u32 resource, f32 x, f32 y, f32 z, f32 rate) {
    GSvec difference, target, rotation;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        target.param1 = x;
        target.param2 = y;
        target.param3 = z;
        PSVECSubtract(&target, peopleBiosGetPosPtr(work), &difference);
        difference.param2 = 0.0f;
        f32 angle;
        if (!(PSVECMag(&difference) < 0.00001f) || !(PSVECMag(&difference) > -0.00001f))
            angle = atan2(difference.param1, difference.param3);
        else { peopleBiosGetRot(work, &rotation); angle = rotation.param2; }
        peopleRotateToAngle(group, resource, angle, rate);
    }
}
void peopleRotateToTarget(u32 group, u32 resource, u32 targetGroup, u32 targetResource, f32 rate) {
    GSvec difference, target, rotation;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        GSmodel* model = (GSmodel*)GSresGetResource(targetGroup, targetResource);
        if (model) {
            GSvec* position = GSmodelGetPositionPtr(model);
            target.param1 = position->param1;
            target.param2 = position->param2;
            target.param3 = position->param3;
            PSVECSubtract(&target, peopleBiosGetPosPtr(work), &difference);
            difference.param2 = 0.0f;
            f32 angle;
            if (!(PSVECMag(&difference) < 0.00001f) || !(PSVECMag(&difference) > -0.00001f))
                angle = atan2(difference.param1, difference.param3);
            else { peopleBiosGetRot(work, &rotation); angle = rotation.param2; }
            if (rate < 0.00001f && rate > -0.00001f) {
                peopleSetRotXYZ(group, resource, 0.0f, 57.29578f * angle, 0.0f);
                return;
            }
            peopleRotateToAngle(group, resource, angle, rate);
        }
    }
}
void peopleWalkTo(u32 group, u32 resource, u8 rotate, GSvec* target) {
    GSvec difference, rotation;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        work->walkActive = 1;
        work->walkTarget.param1 = target->param1;
        work->walkTarget.param2 = target->param2;
        work->walkTarget.param3 = target->param3;
        PSVECSubtract(&work->walkTarget, peopleBiosGetPosPtr(work), &difference);
        difference.param2 = 0.0f;
        f32 angle;
        if (!(PSVECMag(&difference) < 0.00001f) || !(PSVECMag(&difference) > -0.00001f))
            angle = atan2(difference.param1, difference.param3);
        else { peopleBiosGetRot(work, &rotation); angle = rotation.param2; }
        work->walkTarget.param2 = GScolsys2HumanGetWalkHeight(&work->walkTarget);
        _peopleSetMoveAnimation(work);
        f32 rate = 1.0f;
        if (work->moveSpeed > (0.1f + work->unknown20)) rate = 2.0f;
        peopleRotateToAngle(group, resource, angle, rate);
        if (!rotate) work->unknown0E = 0;
        peopleBiosGetPos(work, &work->walkStartPosition);
    }
}

void PSVECScale(GSvec*, GSvec*, f32);
void PSVECAdd(GSvec*, GSvec*, GSvec*);
f32 peopleInfoBiosGetColBallSize(PeopleInfo*);
u8 GScolsys2HitNpcCollision(GSvec*, GSvec*, GSvec*, f32);
s32 _peopleMoveSub__FP13tagPeopleWork(tagPeopleWork*);
u8 _peopleBreakWithWalkList__FP13tagPeopleWork(tagPeopleWork* work) {
    u8 mode = work->walkActive;
    if (mode == 3) return 0;
    if (mode != 2 || work->walkPointIndex == 0 || work->walkPointIndex >= work->walkPointCount - 1) return 1;
    return 0;
}
void _peopleMoveTypeLinear__FP13tagPeopleWork(tagPeopleWork* work) {
    if (_peopleMoveSub__FP13tagPeopleWork(work) == 1) {
        if (_peopleBreakWithWalkList__FP13tagPeopleWork(work)) work->walkActive = 0;
        work->followerMotion = 0;
    }
}
u8 peopleCheckTresure(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    return (work->resource & 0x7FFF0000) == 0x7FFF0000;
}
void peopleWalkToTarget(u32 group, u32 resource, u32 targetGroup, u32 targetResource, u8 rotate, f32 distance) {
    GSvec difference, target, current;
    distance = 10.0f * distance;
    peopleGetPos(group, resource, &current);
    peopleGetPos(targetGroup, targetResource, &target);
    PSVECSubtract(&current, &target, &difference);
    f32 length = PSVECMag(&difference);
    f32 scale;
    if (length < 0.00001f && length > -0.00001f) scale = 1.0f;
    else scale = distance / length;
    if (scale >= 1.0f) {
        tagPeopleWork* work = peopleGet(group, resource);
        if (work) work->walkActive = 0;
    } else {
        PSVECScale(&difference, &difference, scale);
        PSVECAdd(&target, &difference, &target);
        peopleWalkTo(group, resource, rotate, &target);
    }
}
s32 peopleGazeCheck(u32 group, u32 resource, u32 targetGroup, u32 targetResource, f32 distance, f32 degrees) {
    GSvec position, target, rotation, difference;
    f32 radius = 4.0f;
    tagPeopleWork* targetWork = peopleGet(targetGroup, targetResource);
    if (!targetWork) return 0;
    GSvec* value = peopleBiosGetPosPtr(targetWork);
    target.param1 = value->param1;
    target.param2 = value->param2;
    target.param3 = value->param3;
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    value = peopleBiosGetPosPtr(work);
    position.param1 = value->param1;
    position.param2 = value->param2;
    position.param3 = value->param3;
    PSVECSubtract(&position, &target, &difference);
    distance = 10.0f * distance;
    if (PSVECMag(&difference) > distance) return 0;
    peopleBiosGetRot(work, &rotation);
    if ((f32)fabs(peopleVecCalcRotY(&position, &target, rotation.param2)) > 0.5f * (0.017453292f * degrees)) return 0;
    PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
    if (info) radius = peopleInfoBiosGetColBallSize(info);
    if (GScolsys2HitNpcCollision(&position, &target, 0, radius)) return 0;
    return 1;
}
s32 peopleGazeHeroCheck(u32 group, u32 resource) { return peopleGazeCheck(group, resource, 0, 100, 3.0f, 30.0f); }

u8 isAlwayBlendChara__13tagPeopleWorkCFv(tagPeopleWork*);
void peopleFreeWalkList(u32, u32);
void GSresFreeResourceAllGroup(u32);
void GSresFreeResource(u32, u32);
void GSmodelFree(GSmodel*);
u32 peopleBiosGetUseObjIDSize(u32);
s32 peopleBiosFreeWork(tagPeopleWork*);
void floorFreeResource(u32, u32);
f32 _distanceXZ__FP5GSvecP5GSvec(GSvec* first, GSvec* second) {
    GSvec firstFlat, secondFlat;
    firstFlat.param1 = first->param1;
    firstFlat.param2 = first->param2;
    firstFlat.param3 = first->param3;
    secondFlat.param1 = second->param1;
    secondFlat.param2 = second->param2;
    secondFlat.param3 = second->param3;
    firstFlat.param2 = 0.0f;
    secondFlat.param2 = 0.0f;
    return PSVECDistance(&firstFlat, &secondFlat);
}
void _peopleSetMoveAnimation(tagPeopleWork* work) {
    bool loop = 0;
    if (work) {
        if (!work->model) return;
        if (!work->manualAnimation && (work->walkActive != 4 || work->walkPhase != 0) && !isAlwayBlendChara__13tagPeopleWorkCFv(work)) {
            s32 first, second;
            GSmodelGetAnimIndex(work->model, &first, &second);
            if (!work->running) {
                if (first != work->motions.walk || second != -1) {
                    s32 start = work->motions.walkStart;
                    if (start == -1) { start = work->motions.walk; loop = 1; }
                    peopleSetMotion(work->group, work->resource, start, 0, loop);
                }
            } else {
                if (first != work->motions.run || second != -1) {
                    s32 start = work->motions.runStart;
                    if (start == -1) { start = work->motions.run; loop = 1; }
                    peopleSetMotion(work->group, work->resource, start, 0, loop);
                }
            }
        }
    }
}
void _peopleCloseSub__FP13tagPeopleWorkbb(tagPeopleWork* work, u8 clearWalks, u8 freeResource) {
    if (work->visible) peopleSetDisp(work->group, work->resource, 0);
    if (clearWalks) peopleFreeWalkList(work->group, work->resource);
    GSresFreeResourceAllGroup(work->resource);
    if (work->model) {
        GSmodelFree(work->model);
        work->model = 0;
        if (freeResource && peopleBiosGetUseObjIDSize(work->object) == 1U) {
            GSresFreeResource(work->group, work->object);
            floorFreeResource(0x9A, work->object);
        }
    }
    peopleBiosFreeWork(work);
    for (s32 index = 0; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* other = peopleBiosGetWorkPtr(index);
        if (other->used && other->neckTargetGroup == work->group && other->neckTargetResource == work->resource) other->neckEnabled = 0;
    }
}
void peopleSetSpeedRate(u32 group, u32 resource, f32 rate) {
    s32 first, second;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        if (!work->model) return;
        GSmodelGetAnimIndex(work->model, &first, &second);
        if (rate < 0.00001f && rate > -0.00001f) {
            work->moveSpeed = 0.0f;
            if (!work->manualAnimation) peopleSetMotion(work->group, work->resource, work->motions.idle, 0, 1);
        } else if (rate < 1.5f) {
            work->moveSpeed = work->unknown20;
            if (work->running) {
                work->running = 0;
                if ((first == work->motions.walk || first == work->motions.run) && !isAlwayBlendChara__13tagPeopleWorkCFv(work) && !work->manualAnimation)
                    peopleSetMotion(work->group, work->resource, work->motions.walk, 0, 1);
            }
        } else {
            work->moveSpeed = work->unknown24;
            if (!work->running) {
                work->running = 1;
                if ((first == work->motions.walk || first == work->motions.run) && !isAlwayBlendChara__13tagPeopleWorkCFv(work) && !work->manualAnimation)
                    peopleSetMotion(work->group, work->resource, work->motions.run, 0, 1);
            }
        }
    }
}
}
