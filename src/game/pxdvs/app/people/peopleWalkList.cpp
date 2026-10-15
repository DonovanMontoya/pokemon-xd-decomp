#include <game/pxdvs/app/people/runtime.hpp>
extern "C" {void*GSmemAllocClr(u32);void GSmemFree(void*);void _peopleSetMoveAnimation(tagPeopleWork*);tagPeopleWork*peopleGet(u32,u32);void peopleSetFlagOn(u32,u32,u32);s32 peopleFreeWalkList(u32,u32);}
extern "C" s32 peopleFreeWalkList(u32 group,u32 resource){tagPeopleWork*p=peopleGet(group,resource);if(!p)return 0;if(p->walkPoints){if(p->walkPoints){GSmemFree(p->walkPoints);p->walkPoints=0;}p->walkActive=0;p->walkPointCount=0;p->walkPointIndex=0;p->walkPhase=0;}return 1;}

extern "C" s32 peopleStartWalkList(u32 arg0, u32 arg1, u32 arg2) {
    tagPeopleWork *temp_r3;

    temp_r3 = peopleGet(arg0,arg1);
    if (temp_r3 == NULL) {
        return 0;
    }
    peopleSetFlagOn(arg0, arg1, 8);
    temp_r3->walkPhase = 0;
    temp_r3->walkPointIndex = 0;
    temp_r3->unknown28 = (f32) temp_r3->unknown20;
    temp_r3->walkPhase = 1;
    if (arg2 != 0U) {
        temp_r3->walkActive = 3;
    } else {
        temp_r3->walkActive = 2;
    }
    temp_r3->unknown7C[0] = 0;
    _peopleSetMoveAnimation(temp_r3);
    return 1;
}

extern "C" s32 peopleStartWalkListStrict(u32 arg0, u32 arg1, u32 arg2) {
    tagPeopleWork *temp_r3;

    temp_r3 = peopleGet(arg0,arg1);
    if (temp_r3 == NULL) {
        return 0;
    }
    peopleSetFlagOn(arg0, arg1, 8);
    temp_r3->walkPhase = 0;
    temp_r3->walkPointIndex = 0;
    temp_r3->unknown28 = (f32) temp_r3->unknown20;
    temp_r3->walkPhase = 1;
    if (arg2 != 0U) {
        temp_r3->walkActive = 3;
    } else {
        temp_r3->walkActive = 2;
    }
    temp_r3->unknown7C[0] = 1;
    _peopleSetMoveAnimation(temp_r3);
    return 1;
}

extern "C" s32 peopleAddWalkList(u32 group,u32 resource,f32 farg0, f32 farg1, f32 farg2) {
    u16 temp_r4;
    GSvec *temp_r5;
    tagPeopleWork *temp_r3;
    GSvec *temp_r4_2;

    temp_r3 = peopleGet(group,resource);
    if (temp_r3 == NULL) {
        return 0;
    }
    temp_r5 = temp_r3->walkPoints;
    if (temp_r5 == 0) {
        return 0;
    }
    temp_r4 = temp_r3->walkPointIndex;
    if (temp_r4 >= (u16) temp_r3->walkPointCount) {
        return 0;
    }
    temp_r4_2 = temp_r5+temp_r4;
    temp_r4_2->param1 = farg0;
    temp_r4_2->param2 = farg1;
    temp_r4_2->param3 = farg2;
    temp_r3->walkPointIndex = (u16) (temp_r3->walkPointIndex + 1);
    return 1;
}

extern "C" s32 peopleInitWalkList(u32 arg0, u32 arg1, u16 arg2) {
    tagPeopleWork *temp_r3;

    temp_r3 = peopleGet(arg0,arg1);
    if (temp_r3 == NULL) {
        return 0;
    }
    peopleFreeWalkList(arg0, arg1);
    temp_r3->walkPoints = (GSvec*)GSmemAllocClr(arg2 * 0xC);
    if ((u32) temp_r3->walkPoints == 0) {
        return 0;
    }
    temp_r3->walkPointCount = arg2;
    temp_r3->walkPointIndex = 0;
    temp_r3->walkPhase = 0;
    return 1;
}
