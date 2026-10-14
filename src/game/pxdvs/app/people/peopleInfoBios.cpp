#include <game/pxdvs/app/people/runtime.hpp>
extern "C" {
void gimmickBoxGetMotion(s32*, bool*);
bool peopleInfoBiosGetBoundCheck(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return (bool)(u8)((arg0->flags >> 4U) & 1);
    }
    return 0;
}

s32 peopleInfoBiosGetTalkSe(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return (arg0->flags >> 5U) & 7;
    }
    return 0;
}

void peopleInfoBiosGetMotion(PeopleInfo *arg0, u8 arg1, s32 *arg2, bool *arg3) {
    if (arg0 != NULL) {
        gimmickBoxGetMotion(arg2, arg3);
        switch (arg1) {
        case 1:
            *arg2 = 3;
            *arg3 = 1;
            return;
        case 2:
            *arg2 = 5;
            *arg3 = 1;
            return;
        case 3:
            *arg2 = 8;
            *arg3 = 1;
            return;
        case 4:
            *arg2 = 0xB;
            *arg3 = 0;
            return;
        case 5:
            *arg2 = 0xC;
            *arg3 = 1;
            return;
        case 6:
            *arg2 = 0xD;
            *arg3 = 0;
            return;
        case 7:
            *arg2 = 0x27;
            *arg3 = 1;
            return;
        case 8:
            *arg2 = 0x28;
            *arg3 = 0;
            break;
        }
    }
}

f32 peopleInfoBiosGetRunLength(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return arg0->runLength;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetWalkLength(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return arg0->walkLength;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetColBallSize(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return arg0->collisionRadius;
    }
    return 0.0f;
}

s32 peopleInfoBiosGetColType(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return (arg0->flags >> 2U) & 3;
    }
    return 0;
}

f32 peopleInfoBiosGetTalkDistance(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return arg0->talkDistance;
    }
    return 3.0f;
}

f32 peopleInfoBiosGetNeckDownLimit(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return 0.017453292f * arg0->neckDown;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetNeckUpLimit(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return 0.017453292f * arg0->neckUp;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetNeckRightLimit(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return 0.017453292f * arg0->neckRight;
    }
    return 0.0f;
}

f32 peopleInfoBiosGetNeckLeftLimit(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return 0.017453292f * arg0->neckLeft;
    }
    return 0.0f;
}

s8 peopleInfoBiosGetNeckIndex(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return (s8) arg0->neckIndex;
    }
    return -1;
}

s8 peopleInfoBiosGetChestIndex(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return (s8) arg0->chestIndex;
    }
    return -1;
}

s32 peopleInfoBiosGetModelResID(PeopleInfo *arg0) {
    if (arg0 != NULL) {
        return arg0->modelResource;
    }
    return 0;
}

PeopleInfo *peopleInfoBiosGetPtrFromIndex(u32 arg0) {
    if (arg0 >= (u32) *peopleInfoData_number) {
        return 0;
    }
    return peopleInfoData + arg0;
}

PeopleInfo* peopleInfoBiosGetPtr(u32 resource) {
    PeopleInfo* info = peopleInfoData;
    u32 count = *peopleInfoData_number;
    for (; count != 0; --count, ++info) {
        if (info->modelResource == resource) return info;
    }
    return 0;
}
}
