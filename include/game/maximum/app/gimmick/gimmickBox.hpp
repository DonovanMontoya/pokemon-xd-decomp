#ifndef GAME_MAXIMUM_APP_GIMMICK_GIMMICKBOX_HPP
#define GAME_MAXIMUM_APP_GIMMICK_GIMMICKBOX_HPP
#include <dolphin/types.h>

struct GSvec {
    f32 x;
    f32 y;
    f32 z;
    GSvec();
    GSvec(f32 x_, f32 y_, f32 z_);
    GSvec(const GSvec& o) {
        x = o.x;
        y = o.y;
        z = o.z;
    }
    GSvec& operator=(const GSvec& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
};

struct tagPeopleWork {
    u8 active;
    u8 pad01[7];
    u32 model;
    u8 pad0C[2];
    u8 rotFlag;
    u8 pad0F[0x0D];
    u32 id;
    u8 pad20[8];
    f32 f28;
    u8 pad2C[0x14];
    f32 angle;
    f32 rate;
    s32 motion;
    u8 pad4C[0x58 - 0x4C];
    f32 speed;
    u8 pad5C[0x12C - 0x5C];
    f32 f12C;
};

extern "C" {
f32 C_VECDistance(const GSvec*, const GSvec*);

inline f32 GSvecDistance(const GSvec* a, const GSvec* b) {
    return C_VECDistance(a, b);
}
}

enum M_STICK_DIRECTION { M_STICK_NONE, M_STICK_1, M_STICK_2, M_STICK_3, M_STICK_4 };

struct GimmickBoxPushData {
    u8 field0;
    u8 pad1[7];
    GSvec boxPos;
    GSvec kenPos;
    GSvec kenRot;
    f32 pushStartCnt;
    f32 pushCnt;
    f32 pushEndCnt;
    f32 jumpCnt;
    f32 walkCnt;
    tagPeopleWork* ken;
    void* kenInfo;
    tagPeopleWork* box;
    M_STICK_DIRECTION dir;
    GSvec target;
    f32 progress;
    f32 pushStartFrames;
    f32 pushEndFrames;
    f32 jumpFrames;
    f32 walkFrames;
    f32 jumpY[50];
    f32 boxRadius;
    f32 kenRadius;
    f32 moveDist;
    f32 pushDist;
    s32 peopleNum;
    u8 flagPush;
    u8 flagWalk;
    u8 flagStart;
    u8 flagJump;
    s32 state;
    f32 jumpBaseY;
    f32 jumpAngle;
    GimmickBoxPushData() {
        field0 = 0;
        pushStartFrames = 10.0f;
        pushEndFrames = 10.0f;
        jumpFrames = 20.0f;
        walkFrames = 16.0f;
        boxRadius = 4.0f;
        kenRadius = 7.5f;
        moveDist = 2.0f * kenRadius;
        pushDist = 4.0f + kenRadius;
        peopleNum = 64;
        jumpAngle = 0.0f;
    }
};

extern GimmickBoxPushData pd;

#endif
