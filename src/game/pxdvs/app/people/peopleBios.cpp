#include <game/pxdvs/app/people/runtime.hpp>
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
extern "C" {
#include <libc/string.h>
void* GSmemAlloc(u32);
void* GSmemAllocClr(u32);
void GScolsys2HumanEnable(s32, u8);
void peopleFreeWalkList(u32, u32);
void* getHeroPtr__4HeroFv();
u32 getFollowerGrpID__4HeroFv();
u32 getFollowerResID__4HeroFv(void*);
static s32 _people_num;
static tagPeopleWork* _pPeopleWorkTop;

s32 peopleBiosGetPushDataSize() {
    s32 index = 0;
    s32 size = 8;
    for (; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->used) {
            u16 count = work->walkPointCount;
            size += 0x220;
            if (count && work->walkPoints) size += count * sizeof(GSvec);
        }
    }
    return size;
}

void peopleBiosPushData(void* buffer, u32 size) {
    tagPeopleWork* work;
    u8* end;
    u8* cursor;
    GSmodel* model;
    s32 index;
    u32 count;
    count = 0;
    cursor = (u8*)buffer + 8;
    index = 0;
    end = (u8*)buffer + size;
    for (; index < peopleBiosGetMaxNum(); ++index) {
        work = peopleBiosGetWorkPtr(index);
        if (work->used) {
            model = work->model;
            ++count;
            memcpy(cursor, (u8*)work + 0xC, 0x184);
            memcpy(cursor + 0x184, GSmodelGetPositionPtr(model), sizeof(GSvec));
            memcpy(cursor + 0x190, GSmodelGetRotationPtr(model), sizeof(GSvec));
            memcpy(cursor + 0x19C, (u8*)model + 0x5B4, sizeof(GSvec));
            memcpy(cursor + 0x1A8, (u8*)model + 0x5C0, sizeof(GSvec));
            GSmodelPushState(model, (GSmodelState*)(cursor + 0x1B4));
            if (work->walkPointCount && work->walkPoints) {
                u8* points = cursor + 0x220;
                memcpy(points, work->walkPoints, work->walkPointCount * sizeof(GSvec));
                points += work->walkPointCount * sizeof(GSvec);
                peopleFreeWalkList(work->group, work->resource);
                cursor = points;
            } else {
                cursor += 0x220;
            }
            // Preserve the original early exit before writing the save header.
            if (cursor > end) return;
        }
    }
    ((u32*)buffer)[0] = size;
    ((u32*)buffer)[1] = count;
}

void peopleOpenSub(tagPeopleWork*, u32, u32, u32);
void peopleSetMotionType(tagPeopleWork*, s32);
void peopleDoAttach(GSmodel*, s32, s32, s32, u8);
void _peopleRegisterAnimMix(tagPeopleWork*);
void _peopleDoNeckUpdate(tagPeopleWork*);
void gimmickBoxPop();
void peopleBiosPopData(void* buffer, u32 size) {
    tagPeopleWork* restored[64];
    u32 count;
    s32 index;
    tagPeopleWork* work;
    u8* cursor;
    u32 remaining;
    memset(_pPeopleWorkTop, 0, _people_num * sizeof(tagPeopleWork));
    if (((u32*)buffer)[0] == size) {
        count = ((u32*)buffer)[1];
        if (count <= 64) {
            remaining = count;
            cursor = (u8*)buffer + 8;
            index = 0;
            while (remaining--) {
                work = peopleBiosGetNewWork();
                u32* saved = (u32*)cursor;
                peopleOpenSub(work, saved[2], saved[3], saved[4]);
                memcpy((u8*)work + 0xC, cursor, 0x184);
                if (work->model) GSmodelPopState(work->model, (GSmodelState*)(cursor + 0x1B4));
                restored[index++] = work;
                if (work->walkPointCount && work->walkPoints) {
                    u8* next = cursor + 0x220;
                    next += work->walkPointCount * sizeof(GSvec);
                    cursor = next;
                }
                else cursor += 0x220;
            }
            u8* secondCursor = (u8*)buffer + 8;
            index = 0;
            while (count--) {
                tagPeopleWork* secondWork = restored[index++];
                GSmodel* model = secondWork->model;
                peopleBiosSetDispFlag(secondWork, secondWork->visible);
                peopleBiosSetCollision(secondWork, secondWork->collisionEnabled);
                peopleSetMotionType(secondWork, secondWork->motionType);
                GSmodelPopState(model, (GSmodelState*)(secondCursor + 0x1B4));
                if (secondWork->attachGroup != -1 && secondWork->attachResource != -1) {
                    peopleDoAttach(model, secondWork->attachGroup, secondWork->attachResource, secondWork->attachIndex, 0);
                    GSvec* pos = GSmodelGetPositionPtr(model);
                    GSvec* saved = (GSvec*)(secondCursor + 0x184);
                    pos->param1 = saved->param1;
                    pos->param2 = saved->param2;
                    pos->param3 = saved->param3;
                    GSvec* rot = GSmodelGetRotationPtr(model);
                    saved = (GSvec*)(secondCursor + 0x190);
                    rot->param1 = saved->param1;
                    rot->param2 = saved->param2;
                    rot->param3 = saved->param3;
                    GSmodelSetPosition(model, (GSvec*)(secondCursor + 0x19C));
                    GSmodelSetRotation(model, (GSvec*)(secondCursor + 0x1A8));
                }
                secondWork->animationMixRegistered = 0;
                secondWork->secondaryMixRegistered = 0;
                _peopleRegisterAnimMix(secondWork);
                if (secondWork->animationBlend) GSmodelEnableAnimBlend(secondWork->model);
                if (secondWork->neckEnabled) {
                    for (s32 step = 0; step < 60; ++step) _peopleDoNeckUpdate(secondWork);
                }
                if (secondWork->walkPointCount && secondWork->walkPoints) {
                    u8* points = secondCursor + 0x220;
                    secondWork->walkPoints = (GSvec*)GSmemAlloc(secondWork->walkPointCount * sizeof(GSvec));
                    if (secondWork->walkPoints) memcpy(secondWork->walkPoints, points, secondWork->walkPointCount * sizeof(GSvec));
                    else { secondWork->walkPointCount = 0; secondWork->walkPointIndex = 0; }
                    points += secondWork->walkPointCount * sizeof(GSvec);
                    secondCursor = points;
                } else secondCursor += 0x220;
            }
            gimmickBoxPop();
        }
    }
}

s32 peopleBiosGetUseObjIDSize(u32 object) {
    s32 index = 0;
    s32 count = 0;
    for (; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->used && work->object == object) ++count;
    }
    return count;
}

tagPeopleWork* peopleBiosGetTresureIDToPeopleWork(u16 treasure) {
    for (s32 index = 0; index < peopleBiosGetMaxNum(); ++index) {
        tagPeopleWork* work = peopleBiosGetWorkPtr(index);
        if (work->used && work->treasure == treasure) return work;
    }
    return 0;
}
void peopleBiosSetTresureID(tagPeopleWork* work, u16 treasure) { work->treasure = treasure; }
void peopleBiosSetCollision(tagPeopleWork* work, u8 enabled) {
    work->collisionEnabled = enabled;
    if (work->collisionHandle >= 0) GScolsys2HumanEnable(work->collisionHandle, enabled);
}
void peopleBiosSetDispFlag(tagPeopleWork* work, u8 visible) {
    GSmodel* model = peopleBiosGetModelPtr(work);
    if (model) { work->visible = visible; GSmodelSetVisibility(model, visible); }
}
bool peopleBiosCheckFlag(tagPeopleWork* work, u32 flags) { return (work->flags & flags) != 0; }
void peopleBiosSetFlagOff(tagPeopleWork* work, u32 flags) { work->flags &= ~flags; }
void peopleBiosSetFlagOn(tagPeopleWork* work, u32 flags) { work->flags |= flags; }
void peopleBiosSetFlags(tagPeopleWork* work, u32 flags) { work->flags = flags; }
GSmodel* peopleBiosGetModelPtr(tagPeopleWork* work) { return work->model; }
void peopleBiosSetPrevPos(tagPeopleWork* work, GSvec* value) {
    work->previousPosition.param1 = value->param1;
    work->previousPosition.param2 = value->param2;
    work->previousPosition.param3 = value->param3;
}
GSvec* peopleBiosGetPrevPosPtr(tagPeopleWork* work) { return &work->previousPosition; }
void peopleBiosSetRot(tagPeopleWork* work, GSvec* value) { GSmodelSetRotation(work->model, value); }
void peopleBiosGetRot(tagPeopleWork* work, GSvec* value) { GSmodelGetRotation(work->model, value); }
GSvec* peopleBiosGetRotPtr(tagPeopleWork* work) { return GSmodelGetRotationPtr(work->model); }
void peopleBiosSetPos(tagPeopleWork* work, GSvec* value) { GSmodelSetPosition(work->model, value); }
void peopleBiosGetPos(tagPeopleWork* work, GSvec* value) { GSmodelGetPosition(work->model, value); }
GSvec* peopleBiosGetPosPtr(tagPeopleWork* work) { return GSmodelGetPositionPtr(work->model); }
s32 peopleBiosGetState(tagPeopleWork* work) {
    if (!work) return 0;
    if (!work->used) return 0;
    s32 state = 1;
    if (GSmodelGetVisibility(work->model)) state |= 2;
    if (work->treasure) state |= 4;
    return state;
}
tagPeopleWork* peopleBiosGetNewWork() {
    tagPeopleWork* work;
    s32 index;
    for (index = 0; index < peopleBiosGetMaxNum(); ++index) {
        work = peopleBiosGetWorkPtr(index);
        if (!work->used) {
            memset(work, 0, sizeof(*work));
            work->used = 1;
            work->self = work;
            work->collisionHandle = -1;
            work->unknown28 = work->unknown20;
            return work;
        }
    }
    return 0;
}
tagPeopleWork* peopleBiosGetPeopleWork(u32 group, u32 resource) {
    tagPeopleWork* work = _pPeopleWorkTop;
    tagPeopleWork* end = work + _people_num;
    for (; work != end; ++work) {
        if (work->used && work->resource == resource && work->group == group) return work;
    }
    return 0;
}
tagPeopleWork* peopleBiosGetWorkPtr(s32 index) {
    if (index < 0 || _people_num <= index) return 0;
    return _pPeopleWorkTop + index;
}
s32 peopleBiosGetMaxNum() { return _people_num; }
s32 peopleBiosFreeWork(tagPeopleWork* work) { work->used = 0; work->state = 0; return 1; }
void peopleBiosAllocWork(s32 count) {
    _pPeopleWorkTop = (tagPeopleWork*)GSmemAllocClr(count * sizeof(tagPeopleWork));
    _people_num = count;
}
u8 isAnimBlend__13tagPeopleWorkCFv(tagPeopleWork* work) { return work->animationBlend; }
bool isFollower__13tagPeopleWorkCFv(tagPeopleWork* work) {
    void* hero = getHeroPtr__4HeroFv();
    if (work->group == getFollowerGrpID__4HeroFv() && work->resource == getFollowerResID__4HeroFv(hero)) return true;
    return false;
}
bool isHero__13tagPeopleWorkCFv(tagPeopleWork* work) { return work->resource == 100; }
}
