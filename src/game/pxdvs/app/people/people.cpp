#include <game/pxdvs/app/people/runtime.hpp>
#pragma dont_inline on
namespace GSscript { struct Tiga { int getNameToFuncId(const char*); }; }
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
    if (work == 0) {
        return 0;
    } else {
        return peopleBiosCheckFlag(work, flags);
    }
}
s32 peopleGetFlags(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work == 0) {
        return 0;
    } else {
        return work->flags;
    }
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
void _peopleAdjustPositionSub__FP13tagPeopleWorkP5GSvecP5GSvec(tagPeopleWork*, GSvec*, GSvec*);
u32 GSinputButtonsPressed(u32);
void* GSresGetResource(u32, u32);
u32 _peopleAdjustPosition__FP13tagPeopleWorkP5GSvecP5GSvec(tagPeopleWork* work, GSvec* position, GSvec* previous) {
    u8* debug = (u8*)GSresGetResource(0, 2);
    if (debug && debug[1] && (GSinputButtonsPressed(1) & 0x200)) {
        peopleBiosSetPos(work, position);
        return 1;
    }
    _peopleAdjustPositionSub__FP13tagPeopleWorkP5GSvecP5GSvec(work, position, previous);
    peopleBiosSetPos(work, position);
    return work->unknown17E ? 0 : 1;
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
s32 peopleWaitSyncMotionBlend(u32 group, u32 resource, u8 wait) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    GSmodel* model = peopleBiosGetModelPtr(work);
    if (!model) return 0;
    for (;;) {
        if (1.0f == work->motionBlend) return 0;
        if (wait) {
            if (*(s32*)((u8*)model + 0x74) == 1) return 0;
            GSthreadSwitch();
        } else {
            return 1;
        }
    }
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
            s8 neck = peopleInfoBiosGetNeckIndex(info);
            peopleGetPartsPos(group, resource, neck, result);
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
f64 sin(f64);
f64 cos(f64);
void peopleMoveNeckAngleWorld(u32 group, u32 resource, f32 yaw, f32 pitch, f32 rate) {
    PeopleNeckInfo info;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        if (_getNeck__FP13tagPeopleWorkP14PeopleNeckInfo(work, &info)) {
            GSvec* rotation = peopleBiosGetRotPtr(work);
            yaw = 0.017453292f * yaw;
            pitch = 0.017453292f * pitch;
            f32 diff = adjustPIPI__Ff(yaw - rotation->param2);
            if (diff < info.left) diff = info.left;
            if (diff > info.right) diff = info.right;
            yaw = adjust2PI__Ff(diff + rotation->param2);
            f32 x = 1000000.0f * (f32)sin(yaw) + info.position.param1;
            f32 z = 1000000.0f * (f32)cos(yaw) + info.position.param3;
            f32 y = info.position.param2 - 1000000.0f * (f32)sin(pitch);
            work->neckTargetPosition.param1 = x;
            work->neckTargetPosition.param2 = y;
            work->neckTargetPosition.param3 = z;
            work->neckEnabled = 3;
            f32 first = _peopleGetNearAngle__Ff(pitch - info.rotation.param1);
            f32 second = _peopleGetNearAngle__Ff(yaw - info.rotation.param2);
            if (first * first + second * second > 0.0f) {
            }
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
            _peopleUpdateNeck__FP13tagPeopleWorkf(work, 75.0f);
        }
    }
}
void peopleMoveNeckAngle(u32 group, u32 resource, f32 yaw, f32 pitch, f32 rate) {
    PeopleNeckInfo info;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        if (_getNeck__FP13tagPeopleWorkP14PeopleNeckInfo(work, &info)) {
            yaw = 0.017453292f * yaw;
            pitch = 0.017453292f * pitch;
            f32 x = 1000000.0f * (f32)sin(yaw) + info.position.param1;
            f32 z = 1000000.0f * (f32)cos(yaw) + info.position.param3;
            f32 y = info.position.param2 - 1000000.0f * (f32)sin(pitch);
            work->neckTargetPosition.param1 = x;
            work->neckTargetPosition.param2 = y;
            work->neckTargetPosition.param3 = z;
            work->neckEnabled = 3;
            f32 first = _peopleGetNearAngle__Ff(pitch);
            f32 second = _peopleGetNearAngle__Ff(yaw);
            if (first * first + second * second > 0.0f) {
            }
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
            _peopleUpdateNeck__FP13tagPeopleWorkf(work, 75.0f);
        }
    }
}
void fn_8029CD20(u32 group, u32 resource, u32 targetGroup, u32 targetResource, f32 rate) {
    PeopleNeckInfo info;
    tagPeopleWork* work = peopleGet(group, resource);
    tagPeopleWork* target = peopleGet(targetGroup, targetResource);
    if (work == 0 || target == 0) return;
    {
        if (_getNeck__FP13tagPeopleWorkP14PeopleNeckInfo(target, &info)) {
            work->neckTargetPosition.param1 = info.position.param1;
            work->neckTargetPosition.param2 = info.position.param2;
            work->neckTargetPosition.param3 = info.position.param3;
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
}
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
f32 HSD_Randf();
void _peopleMoveTypeRandomRot__FP13tagPeopleWork(tagPeopleWork* work) {
    switch (work->walkPhase) {
    case 0:
        if (work->motionFrame > 0.0f) {
            work->motionFrame = work->motionFrame - _getLastFrameSec__Fv();
            if (work->motionFrame < 0.0f) work->motionFrame = 0.0f;
            break;
        }
        work->walkPhase = 1;
    case 1: {
        f32 offset = 2.0f * HSD_Randf() - 1.0f;
        f32 angle = (f32)fmod(6.2831855f + (1.5707964f * offset + (3.1415927f + work->targetRotation)), 6.2831854820251465);
        f32 rate = 1.0f;
        if (work->moveSpeed > 0.1f + work->unknown20) rate = 2.0f;
        peopleRotateToAngle(work->group, work->resource, angle, rate);
        work->walkPhase = 2;
    }
    case 2:
        work->motionFrame = work->randomRange * (2.0f * HSD_Randf() - 1.0f) + work->randomCentre;
        work->walkPhase = 0;
        break;
    }
}
u8 gimmickBoxIsBox(tagPeopleWork*);
f32 GSmodelGetAnimFrame(GSmodel*);
void _peopleUpdateNoBlendAnimation__FP13tagPeopleWorkf(tagPeopleWork* work, f32 delta) {
    s32 firstIndex, secondIndex;
    f32 firstFrames, secondFrames;
    GSmodel* model = peopleBiosGetModelPtr(work);
    if (model) {
        GSmodelGetAnimIndex(model, &firstIndex, &secondIndex);
        GSmodelGetFrameCount(model, &firstFrames, &secondFrames);
        if (!gimmickBoxIsBox(work)) {
            if (firstIndex == work->motions.walkStart || firstIndex == work->motions.runStart) return;
        }
        f32 frame = GSmodelGetAnimFrame(model);
        f32 firstRatio = firstFrames > 0.0f ? frame / firstFrames : 0.0f;
        f32 secondRatio = secondFrames > 0.0f ? frame / secondFrames : 0.0f;
        if (work->unknown160 < 0.00001f && work->unknown160 > -0.00001f) {
            if (firstIndex == work->motions.idle && secondIndex == -1) return;
            setAnimIndex__13tagPeopleWorkFi(work, work->motions.idle);
            f32 newFirst, newSecond;
            GSmodelGetFrameCount(model, &newFirst, &newSecond);
            f32 ratio = secondIndex == -1 ? secondRatio : firstRatio;
            setAnimFrame__13tagPeopleWorkFf(work, newFirst * ratio);
            setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 1);
            setAnimRate__13tagPeopleWorkFfb(work, 0.5f, 1);
        } else {
            _peopleSetMoveAnimation(work);
        }
    }
}
u8 isAlwayBlendChara__13tagPeopleWorkCFv(tagPeopleWork*);
void GSmodelStartAnimation(GSmodel*);
s32 peopleStartWalkRandom(u32 group, u32 resource, f32 range) {
    s32 firstIndex, secondIndex;
    f32 firstFrames, secondFrames;
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    work->walkActive = 4;
    work->walkPhase = 0;
    peopleSetFlagOn(group, resource, 8);
    peopleBiosGetPos(work, &work->originPosition);
    *(f32*)work->unknown8C = range;
    work->motionFrame = 0.0f;
    work->randomCentre = 5.0f;
    work->randomRange = 3.0f;
    work->unknown28 = work->unknown20;
    if (isAlwayBlendChara__13tagPeopleWorkCFv(work)) {
        GSmodel* model = work->model;
        GSmodelGetAnimIndex(model, &firstIndex, &secondIndex);
        GSmodelGetFrameCount(model, &firstFrames, &secondFrames);
        f32 frame = GSmodelGetAnimFrame(model);
        f32 firstRatio = firstFrames > 0.0f ? frame / firstFrames : 0.0f;
        f32 secondRatio = secondFrames > 0.0f ? frame / secondFrames : 0.0f;
        if (!(firstIndex == work->motions.idle && secondIndex == -1)) {
            setAnimIndex__13tagPeopleWorkFi(work, work->motions.idle);
            f32 newFirst, newSecond;
            GSmodelGetFrameCount(model, &newFirst, &newSecond);
            f32 ratio = secondIndex == -1 ? secondRatio : firstRatio;
            setAnimFrame__13tagPeopleWorkFf(work, newFirst * ratio);
            setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 1);
            setAnimRate__13tagPeopleWorkFfb(work, 0.5f, 1);
            GSmodelStartAnimation(work->model);
        }
    }
    return 1;
}
s32 peopleViewerDisplayRandWalk(tagPeopleWork*);
s32 _peopleMoveSub__FP13tagPeopleWork(tagPeopleWork*);
void _peopleSetMoveAnimation(tagPeopleWork*);
f32 _distanceXZ__FP5GSvecP5GSvec(GSvec*, GSvec*);
extern f32 END_NEED_DISTANCE;
f64 atan2(f64, f64);
u8 GSmodelHasAnimationEnded(GSmodel*);
void _peopleMoveTypeRandomWalk__FP13tagPeopleWork(tagPeopleWork* work) {
    f32 rate = 1.0f;
    switch (work->walkPhase) {
    case 0:
        peopleViewerDisplayRandWalk(work);
        if (work->motionFrame > 0.0f) {
            work->motionFrame = work->motionFrame - _getLastFrameSec__Fv();
            if (!(work->motionFrame <= 0.0f)) break;
            work->motionFrame = 0.0f;
        }
        if (!GSmodelHasAnimationEnded(work->model)) break;
        work->walkPhase = 1;
    case 1: {
        peopleBiosGetPos(work, &work->walkStartPosition);
        peopleBiosGetPos(work, &work->walkTarget);
        for (s32 i = 0; i < 10; i++) {
            f32 angle = 6.2831855f * HSD_Randf();
            work->walkTarget.param1 = (*(f32*)work->unknown8C) * (f32)sin(angle) + work->originPosition.param1;
            work->walkTarget.param3 = (*(f32*)work->unknown8C) * (f32)cos(angle) + work->originPosition.param3;
            work->walkTarget.param2 = GScolsys2HumanGetWalkHeight(&work->walkTarget);
            if (_distanceXZ__FP5GSvecP5GSvec(&work->walkTarget, &work->walkStartPosition) > 6.0f * END_NEED_DISTANCE) break;
        }
        f32 angle = (f32)atan2(work->walkTarget.param1 - peopleBiosGetPosPtr(work)->param1, work->walkTarget.param3 - peopleBiosGetPosPtr(work)->param3);
        if (work->moveSpeed > 0.1f + work->unknown20) rate = 2.0f;
        peopleRotateToAngle(work->group, work->resource, angle, rate);
        _peopleSetMoveAnimation(work);
        work->walkPhase = 2;
    }
    case 2:
        if (_peopleMoveSub__FP13tagPeopleWork(work) != 0) {
            if (work->unknown17E & 1) {
                if (work->moveSpeed > 0.1f + work->unknown20) rate = 2.0f;
                peopleRotateToAngle(work->group, work->resource, 3.1415927f + work->targetRotation, rate);
            }
            work->motionFrame = work->randomRange * (2.0f * HSD_Randf() - 1.0f) + work->randomCentre;
            work->walkPhase = 0;
        }
        break;
    }
}
static u8 m_bMoveByHero;
u8 gimmickBoxIsGimmickMoving();
void GSmodelDisableAnimBlend(GSmodel*);
void _peopleUpdateBlendAnimation__FP13tagPeopleWorkf(tagPeopleWork*, f32);
void _peopleUpdateNoBlendAnimation__FP13tagPeopleWorkf(tagPeopleWork*, f32);
extern void* g_pMana;
void peopleUpdateAnimation(tagPeopleWork* work, u8 moveByHero) {
    m_bMoveByHero = moveByHero ? 0 : 1;
    if (work->walkActive != 6 && !work->waitAnimation) {
        PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
        if (info && !((info->flags >> 1) & 1) && !work->manualAnimation && !gimmickBoxIsGimmickMoving()) {
            f32 speed = work->unknown28;
            if ((void*)work != g_pMana && (peopleBiosCheckFlag(work, 8) || work->resource == 0x64)) {
                f32 distance = PSVECDistance(peopleBiosGetPosPtr(work), &work->walkTarget);
                peopleViewerGetPlaySpeedRate(work);
                if (!isAlwayBlendChara__13tagPeopleWorkCFv(work)) {
                    f32 limit = work->running ? 2.0f * END_NEED_DISTANCE : END_NEED_DISTANCE;
                    if (distance < limit && (!(distance < 0.00001f) || !(distance > -0.00001f))) {
                        if (!work->animationBlend) {
                            GSmodelEnableAnimBlend(work->model);
                            work->animationBlend = 1;
                        }
                    } else if (work->unknown13E[1] && work->animationBlend) {
                        s32 index;
                        GSmodelGetAnimIndex(work->model, &index, 0);
                        GSmodelDisableAnimBlend(work->model);
                        setAnimIndex__13tagPeopleWorkFi(work, index);
                        work->animationBlend = 0;
                    }
                }
            }
            if (work->attachIndex >= 0) speed = 0.0f;
            if (speed > work->unknown24) speed = work->unknown24;
            if (speed < 0.0f) speed = 0.0f;
            if (work->animationBlend) _peopleUpdateBlendAnimation__FP13tagPeopleWorkf(work, speed);
            else _peopleUpdateNoBlendAnimation__FP13tagPeopleWorkf(work, speed);
        }
    }
}
u8 GSgfxVideoGetVsyncRate();
s32 peopleMoveAlongAngle(u32, u32, f32, f32);
void _peopleMoveTypeList__FP13tagPeopleWorkb(tagPeopleWork* work, u8 loop) {
    f32 angle;
    f32 speed;
    f32 rotationSpeed = 2.0f;
    f32 direction;
    u8 started = 0;
    u8 arrived;
    GSvec* point;
    if (work->running) speed = work->unknown24;
    else speed = work->unknown20;
    switch (work->walkPhase) {
    case 0:
    case 1:
        if (work->walkPoints == 0) break;
        started = 1;
        point = &work->walkPoints[work->walkPointIndex];
        work->walkTarget.param1 = point->param1;
        work->walkTarget.param2 = point->param2;
        work->walkTarget.param3 = point->param3;
        work->walkPhase = 2;
    case 2:
        arrived = 0;
        if ((work->walkPointIndex >= work->walkPointCount - 1 && work->walkActive == 2) || work->unknown7C[0] != 0) {
            f32 step;
            f32 distance;
            f32 rate;
            distance = PSVECDistance(peopleBiosGetPosPtr(work), &work->walkTarget);
            rate = (f32)GSgfxVideoGetVsyncRate();
            step = speed * (30.0f * (f32)timeGetLastFrameTime() / rate);
            if (distance < peopleViewerGetPlaySpeedRate(work) * step) arrived = 1;
        } else if (PSVECDistance(peopleBiosGetPosPtr(work), &work->walkTarget) < 5.0f) {
            arrived = 1;
        }
        if (arrived) {
            work->walkPointIndex++;
            if (work->walkPointIndex >= work->walkPointCount) {
                if (loop) {
                    work->walkPointIndex = 0;
                } else {
                    peopleSetPos(work->group, work->resource, &work->walkTarget);
                    work->walkActive = 0;
                    break;
                }
            }
            point = &work->walkPoints[work->walkPointIndex];
            work->walkTarget.param1 = point->param1;
            work->walkTarget.param2 = point->param2;
            work->walkTarget.param3 = point->param3;
        }
        {
            f32 dz = work->walkTarget.param3 - peopleBiosGetPosPtr(work)->param3;
            angle = (f32)atan2(work->walkTarget.param1 - peopleBiosGetPosPtr(work)->param1, dz);
        }
        if (work->unknown7C[0] != 0 || work->walkPointCount <= 2 || started) {
            direction = angle;
            if (started) peopleBiosGetRotPtr(work)->param2 = angle;
        } else {
            if (work->walkPointIndex != 0) {
                static f32 max_rot_speed = 5.0f;
                f32 first = PSVECDistance(peopleBiosGetPosPtr(work), &work->walkPoints[work->walkPointIndex]);
                f32 second = PSVECDistance(&work->walkPoints[work->walkPointIndex - 1], &work->walkPoints[work->walkPointIndex]);
                if (first < second) {
                    f32 factor = peopleGetBlendFactor(first, 0.0f, second);
                    f32 value = 2.0f * factor + max_rot_speed * (1.0f - factor);
                    if (!(2.0f >= value)) rotationSpeed = value;
                }
                first = PSVECDistance(&work->walkPoints[work->walkPointIndex - 1], peopleBiosGetPosPtr(work));
                second = PSVECDistance(&work->walkPoints[work->walkPointIndex - 1], &work->walkPoints[work->walkPointIndex]);
                if (first < second) {
                    f32 factor = peopleGetBlendFactor(first, 0.0f, second);
                    f32 value = 2.0f * factor + max_rot_speed * (1.0f - factor);
                    if (!(rotationSpeed >= value)) rotationSpeed = value;
                }
            }
            GSvec rotation;
            peopleBiosGetRot(work, &rotation);
            direction = adjustPIPI__Ff(rotation.param2);
            if ((f32)fabs(57.29578f * adjustPIPI__Ff(direction - angle)) > 90.0f) direction = angle;
        }
        peopleRotateToAngle(work->group, work->resource, angle, rotationSpeed);
        peopleMoveAlongAngle(work->group, work->resource, speed, direction);
        break;
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
s32 peopleMoveForward(u32, u32, f32);
f32 _distanceXZ__FP5GSvecP5GSvec(GSvec*, GSvec*);
u8 isHero__13tagPeopleWorkCFv(tagPeopleWork*);
u8 isAnimBlend__13tagPeopleWorkCFv(tagPeopleWork*);
s32 _peopleMoveSub__FP13tagPeopleWork(tagPeopleWork* work) {
    GSvec difference;
    f32 speed;
    PSVECSubtract(&work->walkTarget, peopleBiosGetPosPtr(work), &difference);
    difference.param2 = 0.0f;
    if (!(PSVECMag(&difference) < 0.00001f) || !(PSVECMag(&difference) > -0.00001f)) {
        work->targetRotation = (f32)atan2(difference.param1, difference.param3);
    }
    switch (work->followerMotion) {
    case 1:
    case 2:
    case 4:
        speed = 0.53333336f;
        break;
    case 3:
        speed = work->unknown2C;
        break;
    default:
        if (work->running == 0) speed = work->unknown20;
        else speed = work->unknown24;
        break;
    }
    if (!(u8)peopleMoveForward(work->group, work->resource, speed)) return 2;
    f32 distance = _distanceXZ__FP5GSvecP5GSvec(&work->walkTarget, peopleBiosGetPosPtr(work));
    if (distance < 0.00001f && distance > -0.00001f) {
        if (isHero__13tagPeopleWorkCFv(work)) {
            peopleBiosSetFlagOff(work, 8);
        } else if (peopleBiosCheckFlag(work, 8) && !isAlwayBlendChara__13tagPeopleWorkCFv(work) && isAnimBlend__13tagPeopleWorkCFv(work) && work->unknown13E[1] == 0) {
            return 0;
        }
        work->unknown160 = 0.0f;
        return 1;
    }
    return 0;
}
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
struct PeopleCollisionParams {
    u32 group;
    u32 resource;
    f32 radius;
    f32 height;
};
struct PeopleQuat {
    f32 x, y, z, w;
};
extern GSvec yAxisVector;
u32 peopleInfoBiosGetColType(PeopleInfo*);
f32 gimmickBoxGetBoxHeight();
s32 GScolsys2HumanAddCurrentFloor(s32*, PeopleCollisionParams*);
void C_QUATRotAxisRad(PeopleQuat*, GSvec*, f32);
void GSvecTransformQuat(GSvec*, PeopleQuat*, GSvec*);
void peopleAddCollision(u32 group, u32 resource) {
    s32 handle;
    PeopleCollisionParams params;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
        if (info) {
            if (work->collisionHandle < 0) {
                switch ((u8)peopleInfoBiosGetColType(info)) {
                case 1:
                    params.group = group;
                    params.resource = resource;
                    params.radius = peopleInfoBiosGetColBallSize(info);
                    params.height = 12.0f;
                    if (GScolsys2HumanAddCurrentFloor(&handle, &params) == 0) work->collisionHandle = handle;
                    else work->collisionHandle = -1;
                    break;
                case 2:
                    params.group = group;
                    params.resource = resource;
                    params.radius = peopleInfoBiosGetColBallSize(info);
                    params.height = gimmickBoxGetBoxHeight();
                    if (GScolsys2HumanAddCurrentFloor(&handle, &params) == 0) work->collisionHandle = handle;
                    else work->collisionHandle = -1;
                    break;
                }
            }
        }
    }
}
s32 peopleInsideCheck(GSvec* from, GSvec* to, GSvec* out, f32 size) {
    GSvec centre, local;
    PeopleQuat rotation;
    PSVECAdd(from, to, &centre);
    PSVECScale(&centre, &centre, 0.5f);
    C_QUATRotAxisRad(&rotation, &yAxisVector, peopleVecCalcRotY(from, to, 0.0f));
    PSVECSubtract(out, &centre, out);
    GSvecTransformQuat(&local, &rotation, out);
    f32 distance = PSVECDistance(&centre, to);
    if (size >= (f32)fabs(local.param1) && distance >= (f32)fabs(local.param3)) return 1;
    return 0;
}
u8 peopleCheckTresure(u32 group, u32 resource) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work == 0) {
        return 0;
    } else {
        return (work->resource & 0x7FFF0000) == 0x7FFF0000;
    }
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

struct floorCharacter_dd_;
floorCharacter_dd_* floorCharacterBiosFindByResID(u32, u32);
u32 floorCharacterBiosGetMoveSctID(floorCharacter_dd_*);
u32 floorCharacterBiosGetTalkSctID(floorCharacter_dd_*);
GSscript::Tiga* floorGetCurentScript__Fv();
u32 peopleGetMoveSctID(u32 group, u32 resource) {
    return floorCharacterBiosGetMoveSctID(floorCharacterBiosFindByResID(group, resource));
}
u32 peopleGetTalkSctID(u32 group, u32 resource) {
    if (resource == 101 || resource == 104 || resource == 105) return floorGetCurentScript__Fv()->getNameToFuncId("talk_follower");
    floorCharacter_dd_* character = floorCharacterBiosFindByResID(group, resource);
    if (character) return floorCharacterBiosGetTalkSctID(character);
    return 0;
}
void* g_pMana;
void peopleSetFollowerPtr(void* mana) { g_pMana = mana; }
void _peopleRegisterAnimMix() {}
void GSmodelDetachFromGSpart(GSmodel*, s32);
void GSmodelAttachToGSpart(GSmodel*, GSpart*, s32, s32, u8);
static u8 m_b_bikkuri;
void peopleDetach(u32 group, u32 resource, s32 flag) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        GSmodel* model = (GSmodel*)GSresGetResource(group, resource);
        if (model && work->attachIndex >= 0) {
            work->attachGroup = -1;
            work->attachResource = -1;
            work->attachIndex = -1;
            GSmodelDetachFromGSpart(model, flag);
            _peopleClearTargetIfFollower__FUlUl(group, resource);
        }
    }
}
void peopleDoAttach(GSmodel* model, s32 group, s32 resource, s32 index, u8 mode) {
    GSmodel* target = (GSmodel*)GSresGetResource(group, resource);
    if (target) {
        s32 type = 7;
        if (mode == 1) type = 8;
        GSpart* part = GSmodelGetPart(target, index);
        if (part) {
            GSmodelAttachToGSpart(model, part, type, 0, m_b_bikkuri);
            GSpartFree(part);
        }
    }
}
void peopleAttachWithMode(u32 group, u32 resource, s32 targetGroup, s32 targetResource, s32 index, u8 mode) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        GSmodel* model = (GSmodel*)GSresGetResource(group, resource);
        if (model) {
            GSvec rotation;
            peopleDetach(group, resource, 1);
            work->attachGroup = targetGroup;
            work->attachResource = targetResource;
            work->attachIndex = index;
            peopleDoAttach(model, targetGroup, targetResource, index, mode);
            work->unknown0E = 0;
            peopleBiosGetRot(work, &rotation);
            work->targetRotation = rotation.param2;
        }
    }
}
void peopleAttach(u32 group, u32 resource, s32 targetGroup, s32 targetResource, s32 index) {
    peopleAttachWithMode(group, resource, targetGroup, targetResource, index, 0);
}
bool peopleSetNeckLimitHold(u32 group, u32 resource, u8 hold) {
    bool previous;
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    previous = peopleBiosCheckFlag(work, 2);
    if (hold) peopleBiosSetFlagOn(work, 2);
    else peopleBiosSetFlagOff(work, 2);
    return previous;
}

// Batch 2.
class Hero {
public:
    static Hero* getHeroPtr();
    u32 getFollowerGrpID();
    u32 getFollowerResID();
};
struct FloorModuleInterface {
    void (*create)(u32, s32);
    void (*pre)(u32, s32);
    void (*normal)(u32, s32);
    s32 (*thread)(void*);
    void (*post)(u32, s32);
    void (*free)(u32, s32);
    const char* (*getName)();
    void (*saveState)(s32, void*, u32);
    void (*loadState)(s32, void*, u32);
    s32 (*getStateSize)(s32);
    s32 (*getStateID)();
};
struct _GSmodelAnimCBData {
    u32 unknown0;
    s32 index;
    void* user;
};
void heroMoveDismissMember(s32);
void heroMoveJoinMember(s32);
void* GSlightCreate();
void GSlightSetType(void*, s32);
void GSlightSetActive(void*, u8);
void FloorModuleInterface_clear(FloorModuleInterface*);
u32 floorRegisterModule(u8, u32, FloorModuleInterface*);
void* floorOpenObject(u32);
void GSresRegisterResource(void*, u32, u32, void*);
void* floorCreateThread(u32, u32, u32, void (*)());
u32 GSthreadGetCurrentThread();
void peopleBiosAllocWork();
void GSmodelSetVisibility(GSmodel*, u8);
void GSmodelGetPosition(GSmodel*, GSvec*);
void GSmodelGetRotation(GSmodel*, GSvec*);
void GSmodelSetPosition(GSmodel*, GSvec*);
void GSmodelSetRotation(GSmodel*, GSvec*);
void* floorReadResourceID(u32, u32);
u8 peopleChangeModel(tagPeopleWork*, u32, u32, u32);
u8 peopleSetInfo(tagPeopleWork*, u32, u32, u32);
s32 peopleMoveAlongAngle(u32, u32, f32, f32);
void _peopleEnterFloor__FUi14FloorEnterMode(u32, s32);
void _peopleAnimEndCallback__FP8_GSmodelP18_GSmodelAnimCBData(GSmodel*, _GSmodelAnimCBData*);
void _peopleLoadThread__Fv();
u32 peopleGetHumanID(u32, u32);
tagPeopleWork* peopleSearchID(u32);
u8 peopleReadObject(u32, u32, u32);
static u32 m_change_people_objID;
static u32 _hModulePeople;
static FloorModuleInterface _floorModulePeople;
static void* shadowLight[2];

void peopleChangeFollower(u32 objectId) {
    m_change_people_objID = objectId;
    if (GSthreadGetCurrentThread() == 0) floorCreateThread(0x20, 0, 1, _peopleLoadThread__Fv);
    else _peopleLoadThread__Fv();
}
void _peopleLoadThread__Fv() {
    Hero* hero = Hero::getHeroPtr();
    u32 group = hero->getFollowerGrpID();
    u32 resource = hero->getFollowerResID();
    if (peopleGet(group, resource)) {
        switch (resource) {
        case 0x65:
            heroMoveDismissMember(2);
            heroMoveDismissMember(3);
            heroMoveJoinMember(1);
            break;
        case 0x68:
            heroMoveDismissMember(1);
            heroMoveDismissMember(3);
            heroMoveJoinMember(2);
            break;
        case 0x69:
            heroMoveDismissMember(1);
            heroMoveDismissMember(2);
            heroMoveJoinMember(3);
            break;
        }
        peopleReadObject(group, resource, m_change_people_objID);
    }
}
void _peopleInitShadow__Fv() {
    for (s32 i = 0; i < 2; ++i) {
        shadowLight[i] = GSlightCreate();
        GSlightSetType(shadowLight[i], 2);
        GSlightSetActive(shadowLight[i], 0);
    }
}
void peopleInit() {
    peopleBiosAllocWork();
    _peopleInitShadow__Fv();
    FloorModuleInterface_clear(&_floorModulePeople);
    _floorModulePeople.saveState = _peopleMakeStateData__F14FloorStateModePvUl;
    _floorModulePeople.loadState = _peopleRestoreStateData__F14FloorStateModePvUl;
    _floorModulePeople.getStateSize = _peopleGetStateSize__F14FloorStateMode;
    _floorModulePeople.getStateID = _peopleGetMagicNumber__Fv;
    _floorModulePeople.getName = _peopleGetModuleName__Fv;
    _floorModulePeople.pre = _peopleEnterFloor__FUi14FloorEnterMode;
    _floorModulePeople.post = _peopleExitFloor__FUi14FloorEnterMode;
    _hModulePeople = floorRegisterModule(10, 0, &_floorModulePeople);
    m_peopleBlock = 0;
}
void _peopleMarkAnimEndCallback__FP8_GSmodelP18_GSmodelAnimCBData(GSmodel* model, _GSmodelAnimCBData* data) {
    u32* ids = (u32*)data->user;
    GSmodelSetVisibility(model, 0);
    peopleSetFlagOn(ids[0], ids[1], 0x40000);
}
u32 floorGetCurrentGroupID();
void GSmodelClearShadowFlags(GSmodel*, u32);
u32 scriptModelOpen(u32);
void GSmodelSetAnimEndedCallback(GSmodel*, void (*)(GSmodel*, _GSmodelAnimCBData*), void*);
void scriptModelSetMotion(u32, u32, u32, u32);
void GSsndPlayNow(u32);
void GSmodelSetRenderLayer(GSmodel*, s32, s32*);
void peopleDispMark(u32 group, u32 resource) {
    u32 floorGroup;
    u32 mark;
    s8 neck = 0;
    floorGroup = floorGetCurrentGroupID();
    mark = scriptModelOpen(0x0EBB0400);
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
        if (info) neck = peopleInfoBiosGetNeckIndex(info);
    }
    m_b_bikkuri = 1;
    if (neck >= 0) peopleAttach(floorGroup, mark, group, resource, neck);
    else peopleAttach(floorGroup, mark, group, resource, 0);
    m_b_bikkuri = 0;
    work = peopleGet(floorGroup, mark);
    if (work) peopleBiosSetFlagOn(work, 0x2000);
    GSmodel* model = (GSmodel*)GSresGetResource(floorGroup, mark);
    if (model) {
        s32 layer[1] = {4};
        GSmodelSetRenderLayer(model, 1, layer);
        GSmodelClearShadowFlags(model, 1);
    }
    static u32 markRes[2];
    markRes[0] = floorGroup;
    markRes[1] = mark;
    GSmodelSetAnimEndedCallback(model, _peopleMarkAnimEndCallback__FP8_GSmodelP18_GSmodelAnimCBData, markRes);
    scriptModelSetMotion(mark, 0, 0, 0);
    GSsndPlayNow(0x16);
}
void _peopleExecAnimEndCallBack__FP13tagPeopleWork(tagPeopleWork* work) {
    s32 first, second;
    _GSmodelAnimCBData data;
    GSmodelGetAnimIndex(work->model, &first, &second);
    data.index = first;
    if (second != -1) data.index = second;
    data.user = work;
    _peopleAnimEndCallback__FP8_GSmodelP18_GSmodelAnimCBData(work->model, &data);
}
s32 peopleMoveForward(u32 group, u32 resource, f32 distance) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work || !work->model) return 1;
    return peopleMoveAlongAngle(group, resource, distance, work->targetRotation);
}
u8 peopleOpenSub(tagPeopleWork* work, u32 group, u32 resource, u32 object) {
    void* model = floorOpenObject(object);
    if (!model) return 0;
    GSresRegisterResource(model, group, resource, 0);
    work->model = (GSmodel*)model;
    work->unknown13E[0] = 0;
    return peopleSetInfo(work, group, resource, object);
}
u8 _peopleOpenSubWithoutModel__FP13tagPeopleWorkUlUlUl(tagPeopleWork* work, u32 group, u32 resource, u32 object) {
    work->model = 0;
    work->unknown13E[0] = 0;
    return peopleSetInfo(work, group, resource, object);
}
u8 peopleReadObject(u32 group, u32 resource, u32 objectId) {
    GSvec position;
    GSvec rotation;
    GSmodel* model;
    u8 visible;
    tagPeopleWork* work;
    u32 previous;
    u32 human = peopleGetHumanID(group, resource);
    if (!human) return 0;
    work = peopleSearchID(human);
    if (!work) return 0;
    if (objectId == work->object) return 1;
    visible = work->visible;
    model = peopleBiosGetModelPtr(work);
    previous = work->object;
    if (!floorReadResourceID(0x9A, objectId)) return 0;
    if (model) {
        GSmodelSetVisibility(model, 0);
        GSmodelGetPosition(model, &position);
        GSmodelGetRotation(model, &rotation);
    }
    if (!peopleChangeModel(work, group, resource, objectId)) {
        work->object = 0;
        return 0;
    }
    work->object = objectId;
    model = peopleBiosGetModelPtr(work);
    if (model) {
        GSmodelSetVisibility(model, visible);
        GSmodelSetPosition(model, &position);
        GSmodelSetRotation(model, &rotation);
    }
    if (work->unknown13E[0]) floorFreeResource(0x9A, previous);
    work->unknown13E[0] = 1;
    if (!peopleSetInfo(work, group, resource, objectId)) return 0;
    peopleSetDisp(group, resource, visible);
    return 1;
}

// Batch 3.
void GSpartRegisterAnimMix(GSpart*, s32, u32, void*, void*);
void GSpartUnregisterAnimMix(GSpart*, s32);
s8 peopleInfoBiosGetChestIndex(PeopleInfo*);
void GSmodelClearShadowFlags(GSmodel*, u32);
void GSmodelSetShadowFlags(GSmodel*, u32);
void _peopleUpdateShadows__FP13tagPeopleWork(tagPeopleWork*);
void _peoplePostUpdateShadows__Fv();

u8 GScolsys2WalkGetLayer(GSvec*, u8*, u8*);
s32 floorDataBiosGetShadowReciveNum(void*);
u32 floorDataBiosGetShadowReciveID(void*);
u8 heroIsPlayerPeople(u32, u32);
u32 floorGetCurrentGroupID();
void* floorDataBiosGetCurrentPtr();
void gimmickBoxSetKenShadowOnBoxIfOnBoxFloor(tagPeopleWork*, void**, s32*);
void GSmodelSetShadowSurface(GSmodel*, s32, void**);
u8 GSmodelGetVisibility(GSmodel*);
void GSlightSetTarget(void*, GSvec*);
void GSlightSetPosition(void*, GSvec*);
void _peopleUpdateShadows__FP13tagPeopleWork(tagPeopleWork* work) {
    void* floorData = floorDataBiosGetCurrentPtr();
    if (floorData) {
        u32 group = floorGetCurrentGroupID();
        void* resources[2];
        GSvec position;
        s32 mode;
        u8 layer[2];
        peopleBiosGetPos(work, &position);
        if (!GScolsys2WalkGetLayer(&position, &layer[1], &layer[0])) {
            layer[1] = 0;
            layer[0] = 0;
        }
        s32 count = floorDataBiosGetShadowReciveNum(floorData);
        if (layer[1] >= count || layer[0] >= count) return;
        mode = 1;
        resources[0] = GSresGetResource(group, floorDataBiosGetShadowReciveID(floorData));
        if (layer[1] != layer[0]) {
            mode = 2;
            resources[1] = GSresGetResource(group, floorDataBiosGetShadowReciveID(floorData));
        }
        gimmickBoxSetKenShadowOnBoxIfOnBoxFloor(work, resources, &mode);
        GSmodelSetShadowSurface(work->model, mode, resources);
    }
}
void _peoplePostUpdateShadows__Fv() {
    if (peopleBiosGetMaxNum() == 0) return;
    for (s32 i = 0; i < 2; i++) {
        GSvec target;
        target.param1 = 0.0f;
        target.param2 = 0.0f;
        target.param3 = 0.0f;
        for (s32 index = 0; index < peopleBiosGetMaxNum(); index++) {
            tagPeopleWork* work = peopleBiosGetWorkPtr(index);
            if (work->used) {
                GSmodel* model = peopleBiosGetModelPtr(work);
                if (model && work->visible && GSmodelGetVisibility(model) && (i == (heroIsPlayerPeople(work->group, work->resource) != 1))) {
                    GSvec* position = peopleBiosGetPosPtr(work);
                    target.param1 = position->param1;
                    target.param2 = position->param2;
                    target.param3 = position->param3;
                    break;
                }
            }
        }
        target.param2 = 0.0f;
        GSlightSetTarget(shadowLight[i], &target);
        target.param2 = 2500.0f;
        GSlightSetPosition(shadowLight[i], &target);
    }
}

void _registerNeck__FP13tagPeopleWork(tagPeopleWork* work) {
    if (work->object != 0) {
        PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
        if (info) {
            s8 neck = peopleInfoBiosGetNeckIndex(info);
            if (neck >= 0 && work->animationMixRegistered == 0) {
                GSpart* part = GSmodelGetPart(work->model, neck);
                if (part) {
                    GSpartRegisterAnimMix(part, 2, 0x20202, (void*)_peopleGetNeckRotationCB__FP6GSpart13GSpartMixTypePvP5GSvec, work);
                    GSpartFree(part);
                    work->animationMixRegistered = 1;
                }
            }
        }
    }
}
void _peopleUnregisterChestPart__FP13tagPeopleWork(tagPeopleWork* work) {
    if (work && work->used && work->model && work->chestHidden == 0 && work->object) {
        PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
        if (info) {
            s8 chest = peopleInfoBiosGetChestIndex(info);
            if (chest >= 0) {
                work->chestBlend = 0.0f;
                if (work->secondaryMixRegistered == 1) {
                    GSpart* part = GSmodelGetPart(work->model, chest);
                    if (part) {
                        GSpartUnregisterAnimMix(part, 2);
                        GSpartFree(part);
                        work->secondaryMixRegistered = 0;
                    }
                }
                work->chestHidden = 1;
            }
        }
    }
}
void _peopleRegisterChestPart__FP13tagPeopleWork(tagPeopleWork* work) {
    if (work && work->used && work->model && work->chestHidden != 0 && work->object) {
        PeopleInfo* info = peopleInfoBiosGetPtr(work->object);
        if (info) {
            s8 chest = peopleInfoBiosGetChestIndex(info);
            if (chest >= 0) {
                work->chestBlend = 0.0f;
                if (work->secondaryMixRegistered == 0) {
                    GSpart* part = GSmodelGetPart(work->model, chest);
                    if (part) {
                        GSpartRegisterAnimMix(part, 2, 0x20202, (void*)_peopleGetChestRotationCB__FP6GSpart13GSpartMixTypePvP5GSvec, work);
                        GSpartFree(part);
                        work->secondaryMixRegistered = 1;
                    }
                }
                work->chestHidden = 0;
            }
        }
    }
}
void peopleUpdateShadow() {
    tagPeopleWork* work;
    s32 index = peopleBiosGetMaxNum();
    while (index-- > 0) {
        work = peopleBiosGetWorkPtr(index);
        if (work->used && work->model && work->visible) {
            if (peopleBiosCheckFlag(work, 0x2000)) GSmodelClearShadowFlags(work->model, 1);
            else GSmodelSetShadowFlags(work->model, 1);
            _peopleUpdateShadows__FP13tagPeopleWork(work);
        }
    }
    _peoplePostUpdateShadows__Fv();
}
s32 peopleCheckNeckRotate(u32 group, u32 resource, u8 wait) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    GSthreadSwitch();
    for (;;) {
        f32 dx = work->neckRotation.param1 - work->neckTargetRotation.param1;
        f32 dy = work->neckRotation.param2 - work->neckTargetRotation.param2;
        if (dx < 0.00001f && dx > -0.00001f && dy < 0.00001f && dy > -0.00001f) return 0;
        if (wait) GSthreadSwitch();
        else return 1;
    }
}
s32 peopleMoveCheck(u32 group, u32 resource, u8 wait) {
    s32 count = 0;
    s32 animation;
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    peopleBiosSetFlagOn(work, 8);
    for (;;) {
        GSmodelGetAnimIndex(work->model, &animation, 0);
        if (animation == 0) {
            if (++count > 180) {
                work->walkActive = 0;
                return 0;
            }
        }
        if (!work->walkActive && !work->unknown0E) return 0;
        if (!peopleBiosCheckFlag(work, 8)) return 0;
        if (!_peopleIsMoving__FP13tagPeopleWork(work) && !work->unknown0E) return 0;
        if (wait) GSthreadSwitch();
        else return 1;
    }
}

// Batch 4.
f32 HSD_Randf();
u32 HSD_Rand();
void soundOpenPlay(u32, u32, u32);
s32 peopleStartRotRandom(u32 group, u32 resource, f32 centre, f32 range) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (!work) return 0;
    work->walkActive = 5;
    work->walkPhase = 0;
    peopleSetFlagOn(group, resource, 8);
    peopleBiosGetPos(work, &work->originPosition);
    f32 randomOffset = 2.0f * HSD_Randf() - 1.0f;
    work->motionFrame = work->randomRange * randomOffset + work->randomCentre;
    work->randomCentre = centre;
    work->randomRange = range;
    work->unknown28 = work->unknown20;
    return 1;
}
void peopleFallAppear(u32 group, u32 resource, f32 height) {
    GSvec position;
    s32 count = 0;
    s32 previous;
    tagPeopleWork* work = peopleGet(group, resource);
    if (work) {
        peopleGetPos(group, resource, &position);
        position.param2 = height;
        peopleSetDisp(group, resource, 1);
        soundOpenPlay(0x5A2, 0, 0x7F);
        peopleSetMotionType(work, 7);
        for (;;) {
            previous = count;
            count++;
            position.param2 = position.param2 - ((f32)count * (0.4f * (f32)count) / 2.0f - (f32)previous * (0.4f * (f32)previous) / 2.0f);
            peopleSetPos(group, resource, &position);
            if (position.param2 <= 0.0f) {
                position.param2 = 0.0f;
                peopleSetPos(group, resource, &position);
                break;
            }
            GSthreadSwitch();
        }
        soundOpenPlay(0x5A3, 0, 0x7F);
        peopleSetMotionType(work, 8);
        peopleWaitSyncMotion(group, resource, 1);
        peopleSetMotionType(work, 1);
    }
}

// Batch 5.
void* floorDataBiosGetCurrentPtr();
u8 floorDataBiosGetFloorKind(void*);
void peopleTalkEnterFloor();
s32 peopleViewerThread(void*);
void peopleViewerSetPlaySpeedRate(f32);
void gimmickBoxFloorInit();
static u8 m_hero_move = 1;
static u8 m_bPeopleOpenWithModel = 1;
static f32 m_hero_idling_time;
static f32 m_hero_next_special_idling_time;
static s32 m_before_special_effect;
enum PeopleEnterMode { PEOPLE_ENTER_0 = 0, PEOPLE_ENTER_1 = 1, PEOPLE_ENTER_3 = 3 };
void _peopleEnterFloor__FUi14FloorEnterMode(u32 floor, s32 modeValue) {
    PeopleEnterMode mode = (PeopleEnterMode)modeValue;
    if (floorDataBiosGetFloorKind(floorDataBiosGetCurrentPtr()) != 2) {
        if (mode == PEOPLE_ENTER_0 || mode == PEOPLE_ENTER_1 || mode == PEOPLE_ENTER_3) {
            s32 index;
            m_bPeopleOpenWithModel = 1;
            peopleTalkEnterFloor();
            if (floor == 0xFA1) floorCreateThread(0x40, 0, 1, (void (*)())peopleViewerThread);
            for (index = 0; index < peopleBiosGetMaxNum(); ++index) {
                tagPeopleWork* work = peopleBiosGetWorkPtr(index);
                if (work) work->idleTimer = 0.0f;
            }
            peopleViewerSetPlaySpeedRate(1.0f);
            m_hero_move = 1;
            gimmickBoxFloorInit();
            switch ((u16)HSD_Rand() % 3) {
            case 0: m_before_special_effect = 0x13; break;
            case 1: m_before_special_effect = 0x14; break;
            default: m_before_special_effect = 0x15; break;
            }
            m_hero_idling_time = 0.0f;
            m_hero_next_special_idling_time = 4.0f * HSD_Randf() + 8.0f;
            peopleSetMotion(0, 100, 3, 0, 1);
        }
    }
}

// Batch 6.
f32 peopleInfoBiosGetTalkDistance(PeopleInfo*);
void _peopleUpdateNeck__FP13tagPeopleWorkf(tagPeopleWork*, f32);
void* memset(void*, int, u32);
void* g_pHero;
u32 peopleOpen(u32 group, u32 resource, u32 object) {
    tagPeopleWork* work;
    PeopleInfo* info;
    Hero* hero;
    u32 followerGroup;
    u32 followerResource;
    if (peopleGetHumanID(group, resource) != 0) return 0;
    work = peopleBiosGetNewWork();
    if (!work) return 0;
    if (m_bPeopleOpenWithModel != 0) {
        if (!peopleOpenSub(work, group, resource, object)) {
            memset(work, 0, 0x1B0);
            return 0;
        }
    } else {
        if (!_peopleOpenSubWithoutModel__FP13tagPeopleWorkUlUlUl(work, group, resource, object)) {
            memset(work, 0, 0x1B0);
            return 0;
        }
    }
    work->slowDown = 1;
    if (work->group == 0 && work->resource == 0x64) g_pHero = work;
    hero = Hero::getHeroPtr();
    followerGroup = hero->getFollowerGrpID();
    followerResource = hero->getFollowerResID();
    if (work->group == followerGroup && work->resource == followerResource) g_pMana = work;
    info = peopleInfoBiosGetPtr(work->object);
    if (info == 0) work->treasureSearchDistance = 3.0f;
    else work->treasureSearchDistance = peopleInfoBiosGetTalkDistance(info);
    work->unknown7C[0] = 0;
    work->walkPoints = 0;
    work->walkPointCount = 0;
    work->unknown2C = 1.1764706f;
    work->motionFrame = 0.0f;
    work->randomCentre = 5.0f;
    work->randomRange = 3.0f;
    f32 randomOffset = 2.0f * HSD_Randf() - 1.0f;
    work->motionFrame = work->randomRange * randomOffset + work->randomCentre;
    work->secondaryMixRegistered = 0;
    work->rotationProgress = 0.0f;
    work->rotationRate = 1.0f;
    work->neckEnabled = 0;
    work->neckMinStep = 0.07853982f;
    work->neckTargetRotation.param1 = 0.0f;
    work->neckTargetRotation.param2 = 0.0f;
    work->neckTargetRotation.param3 = 0.0f;
    work->neckRotation.param1 = 0.0f;
    work->neckRotation.param2 = 0.0f;
    work->neckRotation.param3 = 0.0f;
    work->chestRotation.param1 = 0.0f;
    work->chestRotation.param2 = 0.0f;
    work->chestRotation.param3 = 0.0f;
    work->targetRotation = 0.0f;
    if (work->model) {
        _peopleRegisterChestPart__FP13tagPeopleWork(work);
        _peopleUpdateNeck__FP13tagPeopleWorkf(work, 75.0f);
    }
    return (u32)work->self;
}

// Batch 7.
struct PeopleCharacterFlags {
    u8 reserved : 5;
    u8 alwaysBlend : 1;
    u8 reserved2 : 2;
};
void GSresChangeResourceAdress(void*, u32, u32, u32);
u8 heroIsPlayerPeople(u32, u32);
u32 floorDataBiosGetShadowLightID(void*);
u32 floorGetCurrentGroupID();
void GSmodelSetShadowLight(GSmodel*, void*);
u8 peopleChangeModel(tagPeopleWork* work, u32 group, u32 resource, u32 object) {
    GSmodel* model;
    PeopleCharacterFlags* character;
    s32 shadow;
    u32 lightId;
    void* light;
    if (object == work->object) return 1;
    peoplePartAnimationBlinkStop(work);
    model = (GSmodel*)floorOpenObject(object);
    if (!model) return 0;
    GSmodelFree(work->model);
    GSresChangeResourceAdress(model, group, resource, 0);
    work->model = model;
    work->group = group;
    work->resource = resource;
    work->object = object;
    peopleSetMotionType(work, 1);
    work->attachGroup = -1;
    work->attachResource = -1;
    work->attachIndex = -1;
    work->neckEnabled = 0;
    character = (PeopleCharacterFlags*)floorCharacterBiosFindByResID(group, resource);
    if (character) {
        if (isAlwayBlendChara__13tagPeopleWorkCFv(work) || character->alwaysBlend == 1) {
            GSmodelEnableAnimBlend(work->model);
            work->animationBlend = 1;
        } else {
            work->animationBlend = 0;
        }
    }
    floorDataBiosGetCurrentPtr();
    shadow = heroIsPlayerPeople(group, resource) != 1;
    lightId = floorDataBiosGetShadowLightID(floorDataBiosGetCurrentPtr());
    if (lightId) light = GSresGetResource(floorGetCurrentGroupID(), lightId);
    else light = shadowLight[shadow];
    GSmodelSetShadowFlags(model, 1);
    if (shadow == 0) GSmodelSetShadowFlags(model, 4);
    GSmodelSetShadowLight(model, light);
    work->secondaryMixRegistered = 0;
    return 1;
}

// Batch 8.
struct PeopleCharacterInfo {
    u8 reserved : 5;
    u8 alwaysBlend : 1;
    u8 reserved2 : 2;
    u8 unknown1;
    u8 unknown2;
    u8 animation;
};
void peopleSetNeckTargetHero(u32, u32);
void GSmodelSetBoundCheck(GSmodel*, u8);
u8 peopleInfoBiosGetBoundCheck(PeopleInfo*);
u8 peopleViewerIsCheckNpc(tagPeopleWork*);
void GSmodelStartAnimation(GSmodel*);
void GSmodelRecalculateBound(GSmodel*);
u8 peopleSetInfo(tagPeopleWork* work, u32 group, u32 resource, u32 object) {
    s32 firstIndex, secondIndex;
    f32 firstFrames, secondFrames;
    f32 frames;
    PeopleCharacterInfo* character;
    s32 shadow;
    void* light;
    u32 lightId;
    work->group = group;
    work->resource = resource;
    work->object = object;
    work->state = 1;
    work->visible = 1;
    peopleSetMotionType(work, 1);
    if (resource == 0x64) peopleSetFlags(group, resource, peopleGetFlags(group, resource) | 0x40000000 | 0xF00);
    else if (resource == 0x65) peopleSetFlags(group, resource, peopleGetFlags(group, resource) | 0x701);
    else peopleSetFlags(group, resource, peopleGetFlags(group, resource) | 0x700);
    work->attachGroup = -1;
    work->attachResource = -1;
    work->attachIndex = -1;
    {
        Hero* hero = Hero::getHeroPtr();
        u32 followerGroup = hero->getFollowerGrpID();
        u32 followerResource = hero->getFollowerResID();
        if (group == followerGroup && resource == followerResource) peopleSetNeckTargetHero(group, resource);
        else work->neckEnabled = 0;
    }
    if (work->model) {
        PeopleInfo* info = peopleInfoBiosGetPtr(object);
        if (info) {
            GSmodelSetBoundCheck(work->model, peopleInfoBiosGetBoundCheck(info));
            peopleSetDefaultMotionTable(work->group, work->resource);
        }
    }
    character = (PeopleCharacterInfo*)floorCharacterBiosFindByResID(group, resource);
    if (work->model && character && (isAlwayBlendChara__13tagPeopleWorkCFv(work) || character->alwaysBlend == 1)) {
        GSmodelEnableAnimBlend(work->model);
        work->animationBlend = 1;
    } else {
        work->animationBlend = 0;
    }
    if (work->model) {
        floorDataBiosGetCurrentPtr();
        shadow = heroIsPlayerPeople(group, resource) != 1;
        lightId = floorDataBiosGetShadowLightID(floorDataBiosGetCurrentPtr());
        if (lightId) light = GSresGetResource(floorGetCurrentGroupID(), lightId);
        else light = shadowLight[shadow];
        GSmodelSetShadowFlags(work->model, 1);
        if (shadow == 0) GSmodelSetShadowFlags(work->model, 4);
        GSmodelSetShadowLight(work->model, light);
    }
    work->chestHidden = 1;
    work->waitAnimation = 0;
    if (work->model && isAlwayBlendChara__13tagPeopleWorkCFv(work)) {
        GSmodelEnableAnimBlend(work->model);
        work->animationBlend = 1;
    } else {
        work->animationBlend = 0;
    }
    work->moveSpeed = work->unknown20;
    work->unknown13E[1] = 0;
    work->flag14C = 0;
    work->flag14D = 0;
    work->followerMotion = 0;
    work->manualAnimation = 0;
    if (work->model) {
        setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 1);
        GSmodelSetTexAnimRate(work->model, 0.5f * peopleViewerGetPlaySpeedRate(work));
        if (peopleViewerIsCheckNpc(work)) {
            setAnimIndex__13tagPeopleWorkFi(work, 0);
            GSmodelStartAnimation(work->model);
        } else {
            character = (PeopleCharacterInfo*)floorCharacterBiosFindByResID(work->group, work->resource);
            if (character == 0 || work->group == 0) {
                if (isAlwayBlendChara__13tagPeopleWorkCFv(work)) setAnimBlend__13tagPeopleWorkFii(work, work->motions.idle, work->motions.walk);
                else setAnimIndex__13tagPeopleWorkFi(work, work->motions.idle);
            } else {
                setAnimIndex__13tagPeopleWorkFi(work, character->animation);
                if (character->animation != 3) work->manualAnimation = 1;
            }
            setAnimType__13tagPeopleWorkF15GSmodelAnimType(work, 1);
            GSmodelStartAnimation(work->model);
        }
        GSmodelGetAnimIndex(work->model, &firstIndex, &secondIndex);
        GSmodelGetFrameCount(work->model, &firstFrames, &secondFrames);
        if (secondIndex == -1) frames = firstFrames;
        else frames = secondFrames;
        setAnimFrame__13tagPeopleWorkFf(work, frames * HSD_Randf());
        GSmodelRecalculateBound(work->model);
    }
    work->neckMinStep = 0.07853982f;
    work->neckMaxStep = 0.07853982f;
    work->neckInstant = 0;
    work->animationMixRegistered = 0;
    work->neckRotation.param1 = 0.0f;
    work->neckRotation.param2 = 0.0f;
    work->neckRotation.param3 = 0.0f;
    work->neckTargetRotation.param1 = 0.0f;
    work->neckTargetRotation.param2 = 0.0f;
    work->neckTargetRotation.param3 = 0.0f;
    work->moveScriptThread = 0;
    work->value150 = 0.0f;
    work->chestRotation.param1 = 0.0f;
    work->chestRotation.param2 = 0.0f;
    work->chestRotation.param3 = 0.0f;
    work->unknownEC.param1 = 0.0f;
    work->unknownEC.param2 = 0.0f;
    work->unknownEC.param3 = 0.0f;
    work->secondaryMixRegistered = 0;
    work->running = 0;
    work->flag17F = 0;
    work->rotationProgress = 0.0f;
    work->rotationRate = 1.0f;
    _registerNeck__FP13tagPeopleWork(work);
    return 1;
}
}
