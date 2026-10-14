extern "C" int sprintf(char*, const char*, ...);
#include <game/maximum/app/gimmick/gimmickBox.hpp>

extern "C" {
long dbgMenuGetLayerID(void);
void GSprint(long, long, long, long, const char*, ...);
double fabs(double);
double fmod(double, double);
}

static f32 m_radius_fix = 1.0f;
static f32 m_radius_fix2 = 1.0f;
static u8 sound_flag;

extern "C" {
void peopleBiosGetPos(tagPeopleWork*, GSvec*);
GSvec* peopleBiosGetPosPtr(tagPeopleWork*);
GSvec* peopleBiosGetPrevPosPtr(tagPeopleWork*);
void peopleBiosGetRot(tagPeopleWork*, GSvec*);
void peopleBiosSetPos(tagPeopleWork*, GSvec*);
tagPeopleWork* peopleBiosGetWorkPtr(s32);
u8 peopleBiosCheckFlag(tagPeopleWork*, u32);
void peopleBiosSetFlags(tagPeopleWork*, u32);
s32 peopleBiosGetMaxNum(void);
u32 peopleBiosGetModelPtr(tagPeopleWork*);
void* peopleInfoBiosGetPtr(u32);
f32 peopleInfoBiosGetColBallSize(void*);
u32 peopleGetHumanID(s32, s32);
tagPeopleWork* peopleSearchID(u32);
void peopleGetPos(s32, s32, GSvec*);
void peopleSetPos(s32, s32, GSvec*);
void peopleGetRot(s32, s32, GSvec*);
void peopleSetRot(s32, s32, GSvec*);
void peopleSetMotion(s32, s32, s32, s32, u8);
void peopleSetMotionType(tagPeopleWork*, s32);
void peopleUpdateAnimation(tagPeopleWork*, s32);
f32 peopleVecCalcRotY(GSvec*, GSvec*, f32);
void peopleRotateToAngle(s32, s32, f32, f32);
void peopleSetFlagOn(s32, s32, u32);
void peopleSetFlagOff(s32, s32, u32);
f32 GScolsys2HumanGetWalkHighest(GSvec*);
u8 GScolsys2HitCollision(GSvec*, GSvec*, f32, GSvec*);
u8 GScolsys2HitNpcCollision(GSvec*, GSvec*, f32, s32);
u8 GSgfxVideoGetVsyncRate(void);
u32 timeGetLastFrameTime(void);
void soundOpenPlay(s32, s32, s32);
void GSthreadSwitch(void);
f32 GSmodelGetAnimFrame(u32);
void GSmodelSetAnimIndex(u32, s32);
void GSmodelGetFrameCount(u32, f32*, s32);
void GSmodelSetAnimFrame(u32, f32);
void GSmodelSetAnimRate(u32, f32);
void GSmodelSetTexAnimIndex(u32, s32);
void GSmodelSetTexAnimFrame(u32, f32);
void GSmodelSetTexAnimRate(u32, f32);
void GSmodelSetAnimType(u32, s32);
void GSmodelStartAnimation(u32);
void GSmodelGetAnimIndex(u32, s32*, s32*);
u8 GSmodelHasAnimationEnded(u32);
void GSvecCopy(GSvec*, GSvec*);
void GSlogWrite(const char*, ...);
s32 heroMoveGetLeader(void);
u32 heroMoveGetKenObjID(void);
s8 GSinputGetLeftStickXData(s32, s32);
s8 GSinputGetLeftStickYData(s32, s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
u32 GSinputButtonsPressed(s32);
u8 cameraGetType(void);
}
namespace std {
float sqrtf(float);
float sinf(float);
float cosf(float);
inline float fabsf(float x) { return (float)fabs(x); }
inline float fmodf(float x, float y) { return (float)fmod(x, y); }
}

static void _gimmickBoxSetJumpPosYs();
static void _gimmickBoxSetBoxDirection(f32, f32);
static void _gimmickBoxGetDirection(M_STICK_DIRECTION, f32*, f32*, f32*);
static M_STICK_DIRECTION _gimmickBoxCheckStickDirection();
static u8 _gimmickBoxCanBoxMove(GSvec*, GSvec*);
static f32 _gimmickBoxGetFixDistanceBoxAndPeople(f32, f32);
static s32 _gimmickBoxAllowAcrossPrevention(s32);
static void _gimmickBoxReadyAndMoveBox(tagPeopleWork*);
static void _gimmickBoxJump();
static u8 _gimmickBoxPushEndMotion();
static void _gimmickBoxPushBoxComplete();
static s32 _gimmickBoxWalkMotion();
static void _gimmickBoxRotateToAngle(f32, f32);
static void _gimmickBoxSetBoxAndKenToPushPosition(tagPeopleWork*, f32, f32);
static u8 _gimmickBoxRoatateKenToBoxPushRotationReady();
static u8 _gimmickBoxTranslateKenToBoxPushPosition();
static u8 _gimmickBoxRoatateKenToBoxPushRotation();
static u8 _gimmickBoxPushStartMotion();
static void _gimmickBoxMoveBox(tagPeopleWork*);
static u8 _gimmickBoxIsJumpOK(GSvec*);
static u8 _gimmickBoxIsOnBoxPos(GSvec*);
static u8 _gimmickBoxCanJump(f32, u8*);
static f32 adjust2PI(f32);
static f32 adjustNear8(f32);
static u8 _gimmickBoxJumpMotion();
static s32 _gimmickBoxGetPeopleNum();
static u8 _gimmickBoxInit();
static u8 _gimmickBoxIsOnBox(f32, f32, f32, f32, f32);
extern "C" void gimmickSetMotion(s32, s32, s32, s32, u8);
extern "C" f32 gimmickBoxGetFrameCount(tagPeopleWork*, s32);

static void gimmickBoxFloorInitDecl();
extern "C" {
u8 gimmickBoxIsPushBoxFloor(void);
void gimmickBoxFloorInit(void);

s32 gimmickBoxPop(void) {
    gimmickBoxFloorInit();
    return 1;
}

u8 gimmickBoxIsBox(tagPeopleWork* people) {
    if (!gimmickBoxIsPushBoxFloor()) {
        return 0;
    }
    if (people == 0) {
        return 0;
    }
    if (people->id == 0x11A40400) {
        return 1;
    }
    return 0;
}

void gimmickBoxDrawString(s32 x, s32 y, const char* str) {
    GSprint(dbgMenuGetLayerID(), x * 13 + 20, y * 13 + 20, -1, str);
}

void gimmickBoxDrawInt(s32 x, s32 y, s32 value) {
    char buf[1024];
    sprintf(buf, "%d", value);
    GSprint(dbgMenuGetLayerID(), x * 13 + 20, y * 13 + 20, -1, buf);
}

void gimmickBoxDrawFloat(s32 x, s32 y, f32 value) {
    char buf[1024];
    sprintf(buf, "%f", value);
    GSprint(dbgMenuGetLayerID(), x * 13 + 20, y * 13 + 20, -1, buf);
}

u8 gimmickBoxIsPushBoxFloor(void) {
    if (pd.state == 1) {
        return 1;
    }
    return 0;
}
}

static void _gimmickBoxSetJumpPosYs() {
    s32 i;
    s32 n;
    s32 k;
    f32 t;
    f32 y;
    f32 h;
    h = 10.0f / 3.0f;
    for (i = 0; i < pd.jumpFrames; i++) {
        if (i <= 3) {
            pd.jumpY[i] = 10.0f;
        } else if (i <= 12) {
            n = 9;
            k = i - 3;
            t = -0.5f + (1.5f * k) / (n - 1);
            y = (10.0f + h) - (10.0f * (t * t)) / 0.75f;
            pd.jumpY[i] = y;
        } else {
            t = 1.1363636f;
            y = (10.0f + h) - (10.0f * (t * t)) / 0.75f;
            pd.jumpY[i] = y;
        }
    }
}

static u8 _gimmickBoxBoxMoveStart(tagPeopleWork* people, f32 dx, f32 dz) {
    f32 vx;
    f32 vz;
    peopleBiosGetPos(people, &pd.boxPos);
    _gimmickBoxSetBoxDirection(dx, dz);
    _gimmickBoxGetDirection(pd.dir, &vx, &vz, 0);
    pd.target.x = pd.boxPos.x + vx * pd.moveDist;
    pd.target.z = pd.boxPos.z + vz * pd.moveDist;
    pd.progress = 0.0f;
    if (pd.dir == _gimmickBoxCheckStickDirection() && _gimmickBoxCanBoxMove(&pd.boxPos, &pd.target)) {
        pd.box = people;
        return 1;
    }
    return 0;
}

extern "C" {
s32 gimmickBoxFixDistanceForPushBox(f32 dx, f32 dz, f32* dist, tagPeopleWork* people) {
    u8 near;
    f32 ax;
    f32 az;
    if (people->id != 0x11A40400) {
        return 0;
    }
    ax = std::fabsf(dx);
    az = std::fabsf(dz);
    if (ax > pd.kenRadius && az > pd.kenRadius) {
        *dist = _gimmickBoxGetFixDistanceBoxAndPeople(dx, dz);
        return _gimmickBoxAllowAcrossPrevention(3);
    }
    near = 0;
    if (ax < az) {
        *dist = std::sqrtf(*dist * *dist + dx * dx);
        if (az < pd.kenRadius + pd.boxRadius) {
            near = 1;
        }
    } else {
        *dist = std::sqrtf(*dist * *dist + dz * dz);
        if (ax < pd.kenRadius + pd.boxRadius) {
            near = 1;
        }
    }
    if (pd.kenPos.y <= 2.0f && pd.box == 0 && *dist > std::sqrtf(dx * dx + dz * dz)) {
        _gimmickBoxBoxMoveStart(people, dx, dz);
    }
    return 1;
}
}

extern "C" {
void gimmickBoxPushBox(u32 ken) {
    s32 i;
    tagPeopleWork* people;
    if (pd.state == 1 && ken == (u32)pd.ken) {
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        if (pd.box != 0) {
            for (i = 0; i < pd.peopleNum; i++) {
                people = peopleBiosGetWorkPtr(i);
                if (people == 0) {
                    break;
                }
                if (peopleBiosCheckFlag(people, 0x100000) && people == pd.box) {
                    _gimmickBoxReadyAndMoveBox(people);
                    break;
                }
            }
        }
        _gimmickBoxJump();
    }
}
}

static u8 _gimmickBoxTranslateKenToBoxPushPosition() {
    f32 vx;
    f32 vz;
    u8 done;
    _gimmickBoxGetDirection(pd.dir, &vx, &vz, 0);
    done = 0;
    if (vx == 0.0f) {
        if (pd.kenPos.x < pd.boxPos.x - 0.5f) {
            pd.kenPos.x += 0.5f;
        } else if (pd.kenPos.x > pd.boxPos.x + 0.5f) {
            pd.kenPos.x -= 0.5f;
        } else {
            pd.kenPos.x = pd.boxPos.x;
            done = 1;
        }
        pd.kenPos.z = pd.boxPos.z - vz * pd.pushDist;
    } else {
        if (pd.kenPos.z < pd.boxPos.z - 0.5f) {
            pd.kenPos.z += 0.5f;
        } else if (pd.kenPos.z > pd.boxPos.z + 0.5f) {
            pd.kenPos.z -= 0.5f;
        } else {
            pd.kenPos.z = pd.boxPos.z;
            done = 1;
        }
        pd.kenPos.x = pd.boxPos.x - vx * pd.pushDist;
    }
    pd.flagWalk = 1;
    pd.flagPush = 0;
    pd.kenPos.y = GScolsys2HumanGetWalkHighest(&pd.kenPos);
    peopleBiosSetPos(pd.ken, &pd.kenPos);
    if (!done) {
        _gimmickBoxWalkMotion();
    }
    return done;
}

static u8 _gimmickBoxRoatateKenToBoxPushRotationReady() {
    switch (pd.dir) {
    case M_STICK_3:
        if (pd.kenPos.x < pd.boxPos.x - 0.5f) {
            _gimmickBoxRotateToAngle(1.5707964f, 0.1f);
        } else if (pd.kenPos.x > pd.boxPos.x + 0.5f) {
            _gimmickBoxRotateToAngle(-1.5707964f, 0.1f);
        } else {
            pd.walkCnt = GSmodelGetAnimFrame(peopleBiosGetModelPtr(pd.ken));
        }
        break;
    case M_STICK_4:
        if (pd.kenPos.x < pd.boxPos.x - 0.5f) {
            _gimmickBoxRotateToAngle(1.5707964f, 0.1f);
        } else if (pd.kenPos.x > pd.boxPos.x + 0.5f) {
            _gimmickBoxRotateToAngle(-1.5707964f, 0.1f);
        } else {
            pd.walkCnt = GSmodelGetAnimFrame(peopleBiosGetModelPtr(pd.ken));
        }
        break;
    case M_STICK_1:
        if (pd.kenPos.z < pd.boxPos.z - 0.5f) {
            _gimmickBoxRotateToAngle(0.0f, 0.1f);
        } else if (pd.kenPos.z > pd.boxPos.z + 0.5f) {
            _gimmickBoxRotateToAngle(3.1415927f, 0.1f);
        } else {
            pd.walkCnt = GSmodelGetAnimFrame(peopleBiosGetModelPtr(pd.ken));
        }
        break;
    case M_STICK_2:
        if (pd.kenPos.z < pd.boxPos.z - 0.5f) {
            _gimmickBoxRotateToAngle(0.0f, 0.1f);
        } else if (pd.kenPos.z > pd.boxPos.z + 0.5f) {
            _gimmickBoxRotateToAngle(3.1415927f, 0.1f);
        } else {
            pd.walkCnt = GSmodelGetAnimFrame(peopleBiosGetModelPtr(pd.ken));
        }
        break;
    }
    return 1;
}

static u8 _gimmickBoxRoatateKenToBoxPushRotation() {
    f32 angle;
    _gimmickBoxGetDirection(pd.dir, 0, 0, &angle);
    _gimmickBoxRotateToAngle(angle, 0.1f);
    if (std::fabsf(pd.ken->angle - angle) < 0.1f) {
        peopleGetRot(0, 100, &pd.kenRot);
        pd.kenRot.y = angle;
        peopleSetRot(0, 100, &pd.kenRot);
        return 1;
    }
    return 0;
}

static void _gimmickBoxPushBoxComplete() {
    pd.box = 0;
    pd.flagWalk = 0;
    pd.flagStart = 0;
    pd.flagPush = 0;
    pd.pushStartCnt = 0.0f;
    pd.pushCnt = 0.0f;
    pd.pushEndCnt = 0.0f;
    pd.walkCnt = 0.0f;
    sound_flag = 0;
    peopleSetMotionType(pd.ken, 1);
}

static void _gimmickBoxSetBoxAndKenToPushPosition(tagPeopleWork* people, f32 vx, f32 vz) {
    pd.kenPos.x = pd.boxPos.x - vx * pd.pushDist;
    pd.kenPos.z = pd.boxPos.z - vz * pd.pushDist;
    pd.kenPos.y = GScolsys2HumanGetWalkHighest(&pd.kenPos);
    peopleBiosSetPos(people, &pd.boxPos);
    peopleBiosSetPos(pd.ken, &pd.kenPos);
}

static void _gimmickBoxMoveBox(tagPeopleWork* people) {
    f32 vx;
    f32 vz;
    f32 step;
    _gimmickBoxGetDirection(pd.dir, &vx, &vz, 0);
    step = (30.0f * timeGetLastFrameTime()) / GSgfxVideoGetVsyncRate();
    pd.boxPos.x += step * (0.25f * vx);
    pd.boxPos.z += step * (0.25f * vz);
    pd.progress += 0.25f * step;
    if (sound_flag == 0) {
        soundOpenPlay(0x562, 0, 100);
        sound_flag = 1;
    }
    if (pd.progress >= pd.moveDist) {
        pd.boxPos.x = pd.target.x;
        pd.boxPos.z = pd.target.z;
        peopleBiosSetPos(people, &pd.boxPos);
        if (_gimmickBoxPushEndMotion()) {
            _gimmickBoxPushBoxComplete();
        }
    } else {
        gimmickSetMotion(0, 100, 0x20, (s32)pd.pushCnt, 1);
        pd.pushCnt += (30.0f * timeGetLastFrameTime()) / GSgfxVideoGetVsyncRate();
        pd.flagWalk = 0;
        pd.flagPush = 1;
    }
    _gimmickBoxSetBoxAndKenToPushPosition(people, vx, vz);
}

static void _gimmickBoxReadyAndMoveBox(tagPeopleWork* people) {
    if (people->model != 0) {
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        peopleBiosGetPos(people, &pd.boxPos);
        if (_gimmickBoxRoatateKenToBoxPushRotationReady()) {
            if (_gimmickBoxTranslateKenToBoxPushPosition() && _gimmickBoxRoatateKenToBoxPushRotation() &&
                _gimmickBoxPushStartMotion()) {
                _gimmickBoxMoveBox(people);
            }
            GSthreadSwitch();
        }
    }
}

static s32 _gimmickBoxWalkMotion() {
    peopleSetMotion(0, 100, 5, (s32)pd.walkCnt, 1);
    pd.walkCnt += (30.0f * timeGetLastFrameTime()) / GSgfxVideoGetVsyncRate();
    return 0;
}

static u8 _gimmickBoxPushStartMotion() {
    if (pd.pushStartCnt < pd.pushStartFrames) {
        gimmickSetMotion(0, 100, 0x1F, (s32)pd.pushStartCnt, 0);
        pd.pushStartCnt += (30.0f * timeGetLastFrameTime()) / GSgfxVideoGetVsyncRate();
        return 0;
    }
    return 1;
}

static u8 _gimmickBoxPushEndMotion() {
    if (pd.pushEndCnt < pd.pushEndFrames) {
        gimmickSetMotion(0, 100, 0x21, (s32)pd.pushEndCnt, 0);
        pd.pushEndCnt += (30.0f * timeGetLastFrameTime()) / GSgfxVideoGetVsyncRate();
        return 0;
    }
    return 1;
}

static void _gimmickBoxGetDirection(M_STICK_DIRECTION dir, f32* x, f32* z, f32* angle) {
    f32 vx = 0.0f;
    f32 vz = 0.0f;
    f32 a = 0.0f;
    switch (dir) {
    case M_STICK_3:
        vz = -1.0f;
        a = 3.1415927f;
        break;
    case M_STICK_4:
        vz = 1.0f;
        a = 0.0f;
        break;
    case M_STICK_2:
        vx = 1.0f;
        a = 1.5707964f;
        break;
    case M_STICK_1:
        vx = -1.0f;
        a = -1.5707964f;
        break;
    }
    if (x != 0) {
        *x = vx;
    }
    if (z != 0) {
        *z = vz;
    }
    if (angle != 0) {
        *angle = a;
    }
}

GimmickBoxPushData pd;

static u8 _gimmickBoxCanBoxMove(GSvec* from, GSvec* to) {
    s32 i;
    u8 ok;
    tagPeopleWork* people;
    if (GScolsys2HitNpcCollision(from, to, pd.kenRadius - 0.1f, 0)) {
        return 0;
    }
    if (GScolsys2HumanGetWalkHighest(to) >= 0.1f) {
        return 0;
    }
    ok = 1;
    for (i = 0; i < pd.peopleNum; i++) {
        people = peopleBiosGetWorkPtr(i);
        if (people->id == 0x11A40400 && people->model != 0 && to->x == peopleBiosGetPosPtr(people)->x &&
            to->z == peopleBiosGetPosPtr(people)->z) {
            ok = 0;
        }
    }
    return ok;
}

static f32 _gimmickBoxGetFixDistanceBoxAndPeople(f32 dx, f32 dz) {
    f32 ox;
    f32 oz;
    f32 ex;
    f32 ez;
    f32 len;
    f32 rx;
    f32 rz;
    f32 ax;
    f32 az;
    if (dx < 0.0f) {
        ox = -pd.kenRadius;
    } else {
        ox = pd.kenRadius;
    }
    if (dz < 0.0f) {
        oz = -pd.kenRadius;
    } else {
        oz = pd.kenRadius;
    }
    ex = dx - ox;
    ez = dz - oz;
    len = std::sqrtf(ex * ex + ez * ez);
    if (len == 0.0f) {
        len = 1.0f;
    }
    ax = (ex * pd.boxRadius) / len;
    az = (ez * pd.boxRadius) / len;
    rx = ox + ax;
    rz = oz + az;
    return std::sqrtf(rx * rx + rz * rz);
}

static void _gimmickBoxSetBoxDirection(f32 dx, f32 dz) {
    if (std::fabsf(dx) > std::fabsf(dz)) {
        if (dx > 0.0f) {
            pd.dir = M_STICK_1;
            return;
        }
        pd.dir = M_STICK_2;
        return;
    }
    if (dz > 0.0f) {
        pd.dir = M_STICK_3;
        return;
    }
    pd.dir = M_STICK_4;
}

extern "C" {
f32 gimmickBoxGetFrameCount(tagPeopleWork* people, s32 anim) {
    u32 model;
    f32 count;
    model = people->model;
    GSmodelSetAnimIndex(model, anim);
    GSmodelGetFrameCount(model, &count, 0);
    return count;
}
}

static s32 _gimmickBoxGetPeopleNum() {
    s32 i;
    tagPeopleWork* p;
    for (i = 0; i < peopleBiosGetMaxNum(); i++) {
        p = peopleBiosGetWorkPtr(i);
        if (p == 0) {
            return i;
        }
    }
    return peopleBiosGetMaxNum();
}

extern "C" {
s32 gimmickBoxIsGimmickMoving(void) {
    if (pd.state == 1 && (pd.flagPush || pd.flagWalk || pd.flagJump)) {
        return 1;
    }
    return 0;
}

f32 gimmickBoxGetBoxHeight(void) {
    return 10.0f;
}
}

static void _gimmickBoxRotateToAngle(f32 angle, f32 rate) {
    pd.ken->rotFlag = 1;
    pd.ken->angle = angle;
    pd.ken->rate = rate;
}

static f32 adjust2PI(f32 a) {
    return std::fmodf(6.2831855f + a, 6.2831855f);
}

extern "C" {
s32 gimmickBoxGetMotion(s32* motion, s8* flag) {
    if (pd.state == 1) {
        if (pd.flagStart) {
            *motion = 0x1F;
            *flag = 0;
            return 1;
        }
        if (pd.flagPush) {
            *motion = 0x20;
            *flag = 1;
            return 1;
        }
        if (pd.flagWalk) {
            *motion = 5;
            *flag = 0;
            return 1;
        }
    }
    return 0;
}
}

static u8 _gimmickBoxInit() {
    pd.ken = peopleSearchID(peopleGetHumanID(0, 100));
    if (pd.ken == 0) {
        return 0;
    }
    pd.kenInfo = peopleInfoBiosGetPtr(pd.ken->id);
    pd.box = 0;
    pd.progress = 0.0f;
    pd.boxPos.y = 0.0f;
    pd.kenPos.y = 0.0f;
    pd.flagPush = 0;
    pd.flagWalk = 0;
    pd.flagStart = 0;
    pd.flagJump = 0;
    pd.pushStartCnt = 0.0f;
    pd.pushCnt = 0.0f;
    pd.pushEndCnt = 0.0f;
    pd.jumpCnt = 0.0f;
    pd.walkCnt = 0.0f;
    pd.pushStartFrames = gimmickBoxGetFrameCount(pd.ken, 0x1F);
    pd.pushEndFrames = gimmickBoxGetFrameCount(pd.ken, 0x21);
    pd.jumpFrames = gimmickBoxGetFrameCount(pd.ken, 0x22);
    pd.walkFrames = gimmickBoxGetFrameCount(pd.ken, 5);
    pd.boxRadius = peopleInfoBiosGetColBallSize(pd.kenInfo);
    pd.kenRadius = peopleInfoBiosGetColBallSize(peopleInfoBiosGetPtr(0x11A40400));
    pd.moveDist = 2.0f * pd.kenRadius;
    pd.pushDist = 4.0f + pd.kenRadius;
    _gimmickBoxSetJumpPosYs();
    pd.peopleNum = _gimmickBoxGetPeopleNum();
    return 1;
}

static u8 _gimmickBoxIsJumpOK(GSvec* p) {
    if (GScolsys2HumanGetWalkHighest(p) <= 2.0f && !_gimmickBoxIsOnBoxPos(p)) {
        return 1;
    }
    return 0;
}

static u8 _gimmickBoxIsOnBox(f32 x, f32 z, f32 y, f32 bx, f32 bz) {
    f32 dx = x - bx;
    f32 dz = z - bz;
    f32 r;
    f32 d;
    f32 adx;
    f32 adz;
    f32 dist;
    adx = std::fabsf(dx);
    adz = std::fabsf(dz);
    if (adx > pd.kenRadius && adz > pd.kenRadius) {
        d = _gimmickBoxGetFixDistanceBoxAndPeople(dx, dz);
    } else {
        r = y + pd.kenRadius;
        if (adx < adz) {
            d = std::sqrtf(r * r + dx * dx);
        } else {
            d = std::sqrtf(r * r + dz * dz);
        }
    }
    dist = std::sqrtf(dx * dx + dz * dz);
    if (dist >= d) {
        return 0;
    }
    return 1;
}

extern "C" {
s32 gimmickBoxOnBox(u32 ken, GSvec* prev, GSvec* pos) {
    s32 i;
    tagPeopleWork* p;
    GSvec* bp;
    if (pd.state == 1 && ken == (u32)pd.ken && (prev->y - 10.0f) < 0.00001f && (prev->y - 10.0f) > -0.00001f) {
        for (i = 0; i < pd.peopleNum; i++) {
            p = peopleBiosGetWorkPtr(i);
            if (p != 0 && p->model != 0 && p->id == 0x11A40400) {
                bp = peopleBiosGetPosPtr(p);
                if (_gimmickBoxIsOnBox(pos->x, pos->z, 0.0f, peopleBiosGetPosPtr(p)->x, bp->z)) {
                    pos->y = 10.0f;
                    return 1;
                }
            }
        }
    }
    return 0;
}
}

static u8 _gimmickBoxIsOnBoxPos(GSvec* pos) {
    s32 i;
    tagPeopleWork* p;
    GSvec* bp;
    if (pos->y == 10.0f) {
        for (i = 0; i < pd.peopleNum; i++) {
            p = peopleBiosGetWorkPtr(i);
            if (p != 0 && p->model != 0 && p->id == 0x11A40400) {
                bp = peopleBiosGetPosPtr(p);
                if (_gimmickBoxIsOnBox(pos->x, pos->z, 0.0f, peopleBiosGetPosPtr(p)->x, bp->z)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

static s32 _gimmickBoxAllowAcrossPrevention(s32 n) {
    peopleBiosGetPos(pd.ken, &pd.kenPos);
    GSvec a = pd.kenPos;
    GSvec b = pd.kenPos;
    GSvec c = pd.kenPos;
    GSvec d = pd.kenPos;
    s32 count;
    a.x -= 4.0f;
    a.z += 4.0f;
    b.x += 4.0f;
    b.z += 4.0f;
    c.x -= 4.0f;
    c.z -= 4.0f;
    d.x += 4.0f;
    d.z -= 4.0f;
    count = 0;
    if (!_gimmickBoxIsJumpOK(&a)) {
        count++;
    }
    if (!_gimmickBoxIsJumpOK(&b)) {
        count++;
    }
    if (!_gimmickBoxIsJumpOK(&c)) {
        count++;
    }
    if (!_gimmickBoxIsJumpOK(&d)) {
        count++;
    }
    if (count >= n) {
        return 1;
    }
    return 0;
}

static f32 adjustNear8(f32 a) {
    a = adjust2PI(a);
    if (a < 0.3926991f || a > 5.8904862f) {
        return 0.0f;
    }
    if (a > 5.105088f) {
        return 5.497787f;
    }
    if (a > 4.3196898f) {
        return 4.712389f;
    }
    if (a > 3.5342917f) {
        return 3.9269907f;
    }
    if (a > 2.7488935f) {
        return 3.1415927f;
    }
    if (a > 1.9634954f) {
        return 2.3561945f;
    }
    if (a > 1.1780972f) {
        return 1.5707964f;
    }
    return 0.7853982f;
}

extern "C" {
void gimmickBoxFloorInit(void) {
    s32 i;
    tagPeopleWork* p;
    pd.state = 0;
    pd.peopleNum = peopleBiosGetMaxNum();
    for (i = 0; i < pd.peopleNum; i++) {
        p = peopleBiosGetWorkPtr(i);
        if (p == 0) {
            break;
        }
        if (p->active) {
            if (p->id == 0x11A40400) {
                peopleBiosSetFlags(p, 0x100000);
                if (_gimmickBoxInit()) {
                    pd.state = 1;
                }
            } else if (p->id == 0x1F380400) {
                pd.state = 2;
            }
        }
    }
}

void gimmickSetMotion(s32 a, s32 b, s32 anim, s32 frame, u8 loop) {
    tagPeopleWork* p;
    u32 model;
    if (frame == 0 && anim != 5 && anim >= 0) {
        p = peopleSearchID(peopleGetHumanID(a, b));
        if (p != 0) {
            model = peopleBiosGetModelPtr(p);
            if (model != 0) {
                p->motion = anim;
                p->f12C = 0.0f;
                GSmodelSetAnimIndex(model, anim);
                GSmodelSetAnimFrame(model, (f32)frame);
                GSmodelSetAnimRate(model, 0.5f);
                GSmodelSetTexAnimIndex(model, anim);
                GSmodelSetTexAnimFrame(model, (f32)frame);
                GSmodelSetTexAnimRate(model, 0.5f);
                if (loop) {
                    GSmodelSetAnimType(model, 1);
                } else {
                    GSmodelSetAnimType(model, 0);
                }
                if (frame == 0) {
                    GSmodelStartAnimation(model);
                }
            }
        }
    }
}
}

extern "C" {
s32 gimmickBoxSetKenShadowOnBoxIfOnBoxFloor(tagPeopleWork* ken, u32* list, s32* count) {
    f32 dx;
    f32 dz;
    s32 found;
    s32 i;
    u32 model;
    u8 near;
    u8 isNear;
    tagPeopleWork* p;
    if (pd.state == 0) {
        return 0;
    }
    if (ken->id != heroMoveGetKenObjID()) {
        return 0;
    }
    found = 0;
    for (i = 0; i < pd.peopleNum; i++) {
        p = peopleBiosGetWorkPtr(i);
        if (p != 0 && p->active && ken != 0 && ken->model != 0 && p != 0 && p->model != 0) {
            dx = std::fabsf(peopleBiosGetPosPtr(ken)->x - peopleBiosGetPosPtr(p)->x);
            dz = std::fabsf(peopleBiosGetPosPtr(ken)->z - peopleBiosGetPosPtr(p)->z);
            near = 0;
            if (dx < 20.0f && dz < 20.0f) {
                near = 1;
            }
            isNear = near;
            if (isNear && (p->id == 0x11A40400 || p->id == 0x1F380400)) {
                model = peopleBiosGetModelPtr(p);
                if (model != 0) {
                    if (*count < 7) {
                        (*count)++;
                    } else {
                        GSlogWrite("gimmickBox.cpp : receiveList over flow.\n");
                    }
                    list[*count - 1] = model;
                    found = 1;
                }
            }
        }
    }
    return found;
}
}

static u8 _gimmickBoxJumpMotion() {
    s32 animIndex;
    s32 animFlag;
    f32 step;
    f32 s;
    f32 c;
    f32 ang;
    f32 k;
    f32 h;
    f32 w;
    f32 oldY;
    GSvec* prev;
    peopleBiosGetPos(pd.ken, &pd.kenPos);
    oldY = pd.kenPos.y;
    prev = peopleBiosGetPrevPosPtr(pd.ken);
    GScolsys2HitCollision(peopleBiosGetPosPtr(pd.ken), prev, pd.boxRadius * m_radius_fix2, &pd.kenPos);
    pd.kenPos.y = oldY;
    if (pd.flagJump) {
        GSmodelGetAnimIndex(pd.ken->model, &animIndex, &animFlag);
        if (animIndex == 0x22 && animFlag == -1 && GSmodelHasAnimationEnded(pd.ken->model)) {
            pd.jumpCnt = pd.jumpFrames;
            return 1;
        }
        step = (30.0f * timeGetLastFrameTime()) / GSgfxVideoGetVsyncRate();
        ang = pd.jumpAngle;
        s = std::sinf(ang);
        c = std::cosf(ang);
        peopleGetPos(0, 100, &pd.kenPos);
        k = 0.8888889f;
        GSvec v(pd.kenPos);
        v.x += s;
        v.z += c;
        h = GScolsys2HumanGetWalkHighest(&v);
        if ((s32)pd.jumpCnt > 3 && (s32)pd.jumpCnt <= 12) {
            pd.kenPos.x += step * (s * k);
            pd.kenPos.z += step * (c * k);
        }
        pd.kenPos.y = (pd.jumpY[(s32)pd.jumpCnt] + pd.jumpBaseY) - 10.0f;
        if (pd.kenPos.y < h) {
            pd.kenPos.y = h;
        }
        w = GScolsys2HumanGetWalkHighest(&pd.kenPos);
        if (pd.kenPos.y < w) {
            pd.kenPos.y = w;
        }
        peopleSetPos(0, 100, &pd.kenPos);
        gimmickSetMotion(0, 100, 0x22, (s32)pd.jumpCnt, 0);
        pd.jumpCnt += step;
        return 0;
    }
    return 1;
}

static M_STICK_DIRECTION _gimmickBoxCheckStickDirection() {
    s32 leader;
    f32 ang;
    f32 mag;
    f32 a2;
    f32 mx;
    f32 my;
    f32 ratio;
    s8 lx;
    s8 ly;
    s8 lx2;
    s8 ly2;
    s32 ax;
    s32 ay;
    s32 ax2;
    s32 ay2;
    s32 bx;
    s32 by;
    leader = heroMoveGetLeader();
    mag = 0.0f;
    lx = GSinputGetLeftStickXData(1, 1);
    ly = GSinputGetLeftStickYData(1, 1);
    lx2 = GSinputGetLeftStickXData(1, 0);
    ly2 = GSinputGetLeftStickYData(1, 0);
    if (lx == 0 && ly == 0) {
        if (GSinputButtonsPressed(1) & 8) {
            ly = -0x38;
        }
        if (GSinputButtonsPressed(1) & 4) {
            ly = 0x38;
        }
        if (GSinputButtonsPressed(1) & 1) {
            lx = -0x38;
        }
        if (GSinputButtonsPressed(1) & 2) {
            lx = 0x38;
        }
        lx2 = lx;
        ly2 = ly;
    }
    if (cameraGetType() != 6 && cameraGetType() != 5 && lx == 0 && ly == 0 && lx2 == 0 && ly2 == 0) {
        lx = GSinputGetRightStickXData(1, 1);
        if (lx < 0) {
            ax = -lx;
        } else {
            ax = lx;
        }
        if (ax < 0x10) {
            lx = 0;
        }
        ly = GSinputGetRightStickYData(1, 1);
        if (ly < 0) {
            ay = -ly;
        } else {
            ay = ly;
        }
        if (ay < 0x10) {
            ly = 0;
        }
        lx2 = GSinputGetRightStickXData(1, 0);
        if (lx2 < 0) {
            ax2 = -lx2;
        } else {
            ax2 = lx2;
        }
        if (ax2 < 0x10) {
            lx2 = 0;
        }
        ly2 = GSinputGetRightStickYData(1, 0);
        if (ly2 < 0) {
            ay2 = -ly2;
        } else {
            ay2 = ly2;
        }
        if (ay2 < 0x10) {
            ly2 = 0;
        }
        lx = (lx * 0x38) / 44;
        ly = (ly * 0x38) / 44;
        lx2 = (lx2 * 0x38) / 44;
        ly2 = (ly2 * 0x38) / 44;
    }
    if (lx != 0 || ly != 0) {
        if (lx > 0x38) {
            lx = 0x38;
        } else if (lx < -0x38) {
            lx = -0x38;
        }
        if (ly > 0x38) {
            ly = 0x38;
        } else if (ly < -0x38) {
            ly = -0x38;
        }
        if (lx > 0) {
            bx = lx;
        } else {
            bx = -lx;
        }
        mx = (f32)bx / 28.0f;
        if (ly > 0) {
            by = ly;
        } else {
            by = -ly;
        }
        my = (f32)by / 28.0f;
        mag = std::sqrtf(mx * mx + my * my);
        if (mag > 2.0f) {
            mag = 2.0f;
        }
        if (lx2 <= -2 || lx2 >= 2 || ly2 <= -2 || ly2 >= 2) {
            if (my < 0.001f) {
                a2 = 1.5707964f;
            } else {
                ratio = mx / my;
                if (ratio > 5.0f) {
                    ratio = 5.0f;
                }
                a2 = 1.5707964f * std::sinf(ratio / 3.1830988f);
            }
            if (ly >= 0) {
                ang = a2;
            } else {
                ang = 3.1415927f - a2;
            }
            if (lx < 0) {
                if (ly >= 0) {
                    ang = 3.1415927f + (3.1415927f - a2);
                } else {
                    ang = 3.1415927f + a2;
                }
            }
        }
    }
    if (mag == 0.0f) {
        return M_STICK_NONE;
    }
    if (ang < 0.3926991f || ang > 5.8904862f) {
        return M_STICK_4;
    }
    if (ang > 1.1780972f && ang < 1.9634954f) {
        return M_STICK_2;
    }
    if (ang > 2.7488935f && ang < 3.5342917f) {
        return M_STICK_3;
    }
    if (ang > 4.3196898f && ang < 5.105088f) {
        return M_STICK_1;
    }
    return M_STICK_NONE;
}

#define GB_CANJUMP_CHECK(FLAG)                                                    \
    dst.y = pd.kenPos.y;                                                          \
    dst.y = GScolsys2HumanGetWalkHighest(&dst);                                   \
    near = std::fabsf((pd.kenPos.y - dst.y) - 10.0f) < 3.0f;                      \
    dst.y = 10.0f;                                                                \
    onBox = _gimmickBoxIsOnBoxPos(&dst);                                          \
    if (near && !onBox) {                                                         \
        *flags |= FLAG;                                                           \
    } else {                                                                      \
        ok = 0;                                                                   \
    }

static u8 _gimmickBoxCanJump(f32 ang, u8* flags) {
    GSvec dst;
    f32 step = (30.0f * timeGetLastFrameTime()) / GSgfxVideoGetVsyncRate();
    GSvec np;
    f32 s = std::sinf(ang);
    f32 c = std::cosf(ang);
    f32 oldY;
    f32 r;
    f32 r2;
    u8 ok;
    bool near;
    u8 onBox;
    np = pd.kenPos;
    np.x += step * (8.0f * s);
    np.z += step * (8.0f * c);
    peopleBiosGetPos(pd.ken, &pd.kenPos);
    GSvec cur(pd.kenPos);
    dst = np;
    cur.y += 6.0f;
    dst.y += 6.0f;
    oldY = pd.kenPos.y;
    if (GScolsys2HitCollision(&cur, &dst, pd.boxRadius * m_radius_fix2, &pd.kenPos)) {
        pd.kenPos.y = oldY;
        return 0;
    }
    pd.kenPos.y = oldY;
    ok = 1;
    *flags = 0;
    r = pd.boxRadius * m_radius_fix;
    r2 = 0.701f * r;
    dst = np;
    dst.x -= r;
    GB_CANJUMP_CHECK(4)
    dst = np;
    dst.x += r;
    GB_CANJUMP_CHECK(8)
    dst = np;
    dst.z -= r;
    GB_CANJUMP_CHECK(1)
    dst = np;
    dst.z += r;
    GB_CANJUMP_CHECK(2)
    dst = np;
    dst.x -= r2;
    dst.z -= r2;
    GB_CANJUMP_CHECK(0x10)
    dst = np;
    dst.x += r2;
    dst.z -= r2;
    GB_CANJUMP_CHECK(0x20)
    dst = np;
    dst.x -= r2;
    dst.z += r2;
    GB_CANJUMP_CHECK(0x40)
    dst = np;
    dst.x += r2;
    dst.z += r2;
    GB_CANJUMP_CHECK(0x80)
    if (*flags == 0xFF) {
        return 1;
    }
    return 0;
}

#define GB_JUMP_CHECK(FLAG)                                                       \
    p2.y = pd.kenPos.y;                                                           \
    p2.y = GScolsys2HumanGetWalkHighest(&p2);                                     \
    near = std::fabsf((pd.kenPos.y - p2.y) - 10.0f) < 3.0f;                       \
    p2.y = 10.0f;                                                                 \
    onBox = _gimmickBoxIsOnBoxPos(&p2);                                           \
    if (near && !onBox) {                                                         \
        blocked = 1;                                                              \
        flags |= FLAG;                                                            \
    }

#define GB_JUMP_CHECK2(FLAG)                                                       \
    p2.y = pd.kenPos.y;                                                           \
    p2.y = GScolsys2HumanGetWalkHighest(&p2);                                     \
    near = std::fabsf((pd.kenPos.y - p2.y) - 10.0f) < 3.0f;                       \
    p2.y = 10.0f;                                                                 \
    onBox = _gimmickBoxIsOnBoxPos(&p2);                                           \
    if (near && !onBox) {                                                         \
        blocked |= 1;                                                              \
        flags |= FLAG;                                                            \
    }


static void _gimmickBoxJump() {
    f32 ang;
    f32 r2;
    f32 stepFix;
    f32 oldY;
    f32 rad;
    f32 base;
    f32 s;
    f32 c;
    u8 flags;
    bool near;
    u8 onBox;
    bool blocked;
    void* info;
    u8 still;
    u8 stopped;
    s8 unused;
    u8 canFlags;
    static f32 angle;
    if (pd.flagJump == 0) {
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        if (pd.kenPos.y < 10.0f) {
            return;
        }
        GSvec rot;
        peopleBiosGetRot(pd.ken, &rot);
        unused = 0;
        still = 0;
        if (GSvecDistance(peopleBiosGetPrevPosPtr(pd.ken), peopleBiosGetPosPtr(pd.ken)) < 0.00001f) {
            if (GSvecDistance(peopleBiosGetPrevPosPtr(pd.ken), peopleBiosGetPosPtr(pd.ken)) > -0.00001f) {
                still = 1;
            }
        }
        stopped = still;
        if (stopped) {
            ang = rot.y;
        } else {
            ang = peopleVecCalcRotY(peopleBiosGetPrevPosPtr(pd.ken), peopleBiosGetPosPtr(pd.ken), 0.0f);
        }
        angle = ang;
        info = peopleInfoBiosGetPtr(pd.ken->id);
        if (info != 0) {
            rad = peopleInfoBiosGetColBallSize(info);
        } else {
            rad = 3.5f;
        }
        GSvec p1;
        GSvec p2;
        blocked = 0;
        flags = 0;
        f32 unusedStep = (30.0f * timeGetLastFrameTime()) / GSgfxVideoGetVsyncRate();
        GSvec np;
        s = std::sinf(ang);
        c = std::cosf(ang);
        peopleBiosGetPos(pd.ken, &pd.kenPos);
        np = pd.kenPos;
        np.x += s * pd.ken->speed;
        np.z += c * pd.ken->speed;
        GSvec prevCopy(*peopleBiosGetPrevPosPtr(pd.ken));
        p2 = np;
        prevCopy.y += 6.0f;
        p2.y += 6.0f;
        oldY = pd.kenPos.y;
        pd.kenPos.y = oldY;
        if (GScolsys2HitCollision(&prevCopy, &p2, pd.boxRadius * m_radius_fix2, &pd.kenPos)) {
            pd.kenPos.y = oldY;
            return;
        }
        pd.kenPos.y = oldY;
        static f32 fix_rr = rad * m_radius_fix;
        p2 = pd.kenPos;
        p2.x -= fix_rr;
        GB_JUMP_CHECK(4)
        p2 = pd.kenPos;
        p2.x += fix_rr;
        GB_JUMP_CHECK(8)
        p2 = pd.kenPos;
        p2.z -= fix_rr;
        GB_JUMP_CHECK(1)
        p2 = pd.kenPos;
        p2.z += fix_rr;
        GB_JUMP_CHECK2(2)
        r2 = 0.701f * fix_rr;
        p2 = pd.kenPos;
        p2.x -= r2;
        p2.z -= r2;
        GB_JUMP_CHECK(0x10)
        p2 = pd.kenPos;
        p2.x += r2;
        p2.z -= r2;
        GB_JUMP_CHECK(0x20)
        p2 = pd.kenPos;
        p2.x -= r2;
        p2.z += r2;
        GB_JUMP_CHECK(0x40)
        p2 = pd.kenPos;
        p2.x += r2;
        p2.z += r2;
        GB_JUMP_CHECK(0x80)
        if (near && !onBox) {
            blocked = 1;
        }
        if (!blocked) {
            return;
        }
        canFlags = 0;
        if (!_gimmickBoxCanJump(ang, &canFlags)) {
            ang = adjustNear8(ang);
            base = ang;
            if (!_gimmickBoxCanJump(ang, &canFlags)) {
                static f32 step_fix = 1.0f;
                stepFix = step_fix;
                while (stepFix <= 90.0f) {
                    ang = adjust2PI(base - 0.017453292f * stepFix);
                    if (_gimmickBoxCanJump(ang, &canFlags)) {
                        goto jumpOK;
                    }
                    ang = adjust2PI(base + 0.017453292f * stepFix);
                    if (_gimmickBoxCanJump(ang, &canFlags)) {
                        goto jumpOK;
                    }
                    stepFix += step_fix;
                }
                GSvecCopy(peopleBiosGetPosPtr(pd.ken), peopleBiosGetPrevPosPtr(pd.ken));
                pd.ken->f28 = 0.0f;
                peopleUpdateAnimation(pd.ken, 1);
                return;
            }
        }
    jumpOK:
        pd.jumpAngle = ang;
        pd.jumpCnt = 0.0f;
        pd.flagJump = 1;
        pd.jumpBaseY = pd.kenPos.y;
        peopleSetFlagOn(0, 100, 8);
        peopleRotateToAngle(0, 100, ang, 1.0f);
    }
    if (_gimmickBoxJumpMotion()) {
        pd.flagJump = 0;
        peopleSetFlagOff(0, 100, 8);
        peopleSetPos(0, 100, &pd.kenPos);
        peopleSetMotionType(pd.ken, 1);
    }
}
