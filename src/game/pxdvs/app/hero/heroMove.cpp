#include <game/pxdvs/app/hero/heroMovePrivate.hpp>

struct HeroMoveSlot {
    u32 fn;
    s32 arg;
};

static HeroMoveWork HeroMove;

static void _heroMoveSlowStopFactor(float, bool);
static bool getResID(unsigned long*, unsigned long*, HEROMOVE_MEMBER);
static void* getModel(HEROMOVE_MEMBER);

static void _heroMoveInitialize(unsigned int, FloorEnterMode mode) {
    HeroMove.raw[0x3AD] = 0;
    HeroMove.raw[0x3AC] = 0;
    HeroMove.raw[0x3AE] = 0;
    if (mode == 3) {
        heroMoveSetLockFrame(4);
    }
}

static void _closeHeroThread() {
    _heroMoveSlowStopFactor(4.0f, true);
}

static const char* _heroMoveGetModuleName() {
    return "hero";
}

extern "C" {

u8 heroMoveIsSmoothFloorLink() {
    return HeroMove.raw[0x3AC];
}

void heroMoveSetSmoothFloorLink(u8 v) {
    HeroMove.raw[0x3AC] = v;
}

}

void AnalogStickEmu::init() {
    b0 = 0;
    b1 = 0;
    b2 = 0;
    b3 = 0;
    b4 = 0x14;
    b5 = 10;
}

static void* _heroGetPeople(HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    return peopleGet(group, res);
}

static u8 isStoryMode() {
    return GSflagGet(0x30D) == 0;
}

static void _setStickData(s8 a, s8 b, s8 c, s8 d) {
    HeroMove.raw[0x3AE] = 1;
    HeroMove.raw[0x3AF] = a;
    HeroMove.raw[0x3B0] = b;
    HeroMove.raw[0x3B1] = c;
    HeroMove.raw[0x3B2] = d;
}

static s8 abs(s8 v) {
    return (s8)__abs((int)v);
}

static u32 getEquipItemEffect(u16 item) {
    u32 data = itemDataBiosGetPtr(item);
    if (data == 0) {
        return 0;
    }
    return itemDataBiosGetItemSoubiDataId(data);
}

extern "C" {

void heroMoveSlowStop() {
    _heroMoveSlowStopFactor(1.0f, false);
}

void heroMoveSetLockFrame(s32 frames) {
    if (frames >= 0) {
        *(s32*)&HeroMove.raw[0x3A8] = frames;
        ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    }
}

void heroMoveAddAutoEvent(s32 a, s32 b, s32 c, s32 d, s32 e) {
    *(s32*)&HeroMove.raw[0x3B4] = a;
    *(s32*)&HeroMove.raw[0x3B8] = b;
    *(s32*)&HeroMove.raw[0x3BC] = c;
    *(s32*)&HeroMove.raw[0x3C0] = d;
    *(s32*)&HeroMove.raw[0x3C4] = e;
}

}

static void initFootWork(FOOTWORK* w) {
    w->a = 0.0f;
    w->b = 0.0f;
    w->c = 0.0f;
    w->d = 0.0f;
}

static void setRot(HEROMOVE_MEMBER member, GSvec* rot) {
    GSmodelSetRotation(getModel(member), rot);
}

static void getRot(GSvec* rot, HEROMOVE_MEMBER member) {
    GSmodelGetRotation(getModel(member), rot);
}

extern "C" {

s32 heroMoveGetLeader();

void heroMoveGetHeroRot(GSvec* rot) {
    getRot(rot, (HEROMOVE_MEMBER)heroMoveGetLeader());
}

}

static void getPos(GSvec*, HEROMOVE_MEMBER);

extern "C" {

void heroMoveGetHeroPos(GSvec* pos) {
    getPos(pos, (HEROMOVE_MEMBER)heroMoveGetLeader());
}

}

static void* getModel(HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    return GSresGetResource(group, res);
}

static bool getResID(unsigned long* group, unsigned long* res, HEROMOVE_MEMBER member) {
    unsigned long ids[4] = {0x64, 0x65, 0x68, 0x69};
    if (member < 0 || member >= 4) {
        return false;
    }
    *group = 0;
    *res = ids[member];
    return true;
}

static void getPos(GSvec* pos, HEROMOVE_MEMBER member) {
    void* model = getModel(member);
    if (model != 0) {
        GSmodelGetPosition(model, pos);
    }
}

static void setPos(HEROMOVE_MEMBER member, GSvec* pos) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    peopleSetPos(group, res, pos);
}

static void setDisp(HEROMOVE_MEMBER member, bool disp) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    peopleSetDisp(group, res, disp);
}

extern "C" {

bool heroMoveGetResID(unsigned long* group, unsigned long* res, HEROMOVE_MEMBER member) {
    return getResID(group, res, member);
}

bool heroMoveIsMember(s32 member) {
    if (member < 0 || member >= 4) {
        return false;
    }
    return HeroMove.members[member].flags & 1;
}

s32 heroMoveGetLeader() {
    return *(s32*)&HeroMove.raw[0];
}

s32 heroMoveGetNeckMode(s32 member) {
    if (heroMoveIsMember(member)) {
        return HeroMove.members[member].neckMode;
    }
    return 2;
}

}

static void initLeaderLog() {
    *(s32*)&HeroMove.raw[0x84] = 0;
    *(s32*)&HeroMove.raw[0x88] = 0;
}

extern "C" void fn_80151F6C() {
    *(s32*)&HeroMove.raw[0x644] = 0;
    *(s32*)&HeroMove.raw[0x648] = 0;
    *(s32*)&HeroMove.raw[0x64C] = 0;
    *(s32*)&HeroMove.raw[0x650] = 0;
}

static void remakeFormation();
static void moveParty(HEROMOVE_MEMBER);
static void initLeaderLog();
static void cbPoison(long, FootStepCounter, long);
static void cbTsureFriend(long, FootStepCounter, long);
static void _heroMoveFinalize(unsigned int, FloorEnterMode);
static FloorModuleInterface _floorModuleHero;

static f32 GSvecDistanceXZ(GSvec* a, GSvec* b) {
    GSvec va;
    GSvec vb;
    va.x = a->x;
    va.y = a->y;
    va.z = a->z;
    vb.x = b->x;
    vb.y = b->y;
    vb.z = b->z;
    va.y = 0.0f;
    vb.y = 0.0f;
    return PSVECDistance(&va, &vb);
}

static void* getHumanPeople(HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    return peopleSearchID(peopleGetHumanID(group, res));
}

static s32 getObjID(HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    void* people;
    if (!getResID(&group, &res, member)) {
        return -1;
    }
    people = peopleSearchID(peopleGetHumanID(group, res));
    if (people == 0) {
        return -1;
    }
    return *(s32*)((u8*)people + 0x1C);
}

static void updateAnimation(f32 rate, HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    void* people;
    getResID(&group, &res, member);
    people = peopleSearchID(peopleGetHumanID(group, res));
    if (people != 0) {
        *(f32*)((u8*)people + 0x28) = rate;
        peopleUpdateAnimation(people, 0);
    }
}

static void updateMotion(HEROMOVE_MEMBER member, f32 rate) {
    getModel(member);
    updateAnimation(rate, member);
}

static void actionFriendSet(Pokemon* pokemon, u16 level) {
    pokemonGetFriendFormPokemonFriendFilterId(pokemon, getEquipItemEffect(pokemonBiosGetItemDataId(pokemon)), level);
}

static bool getLeaderLog(GSvec* out, int index) {
    if (index >= *(s32*)&HeroMove.raw[0x88]) {
        return false;
    }
    if (index >= 0x3C) {
        return false;
    }
    out->x = HeroMove.leaderLog.log[index].x;
    out->y = HeroMove.leaderLog.log[index].y;
    out->z = HeroMove.leaderLog.log[index].z;
    return true;
}

static void initHeroMove() {
    HeroMove.members[0].flags = 0;
    HeroMove.members[1].flags = 0;
    HeroMove.members[2].flags = 0;
    HeroMove.members[3].flags = 0;
    *(s32*)&HeroMove.raw[0] = 0;
    *(s32*)&HeroMove.raw[0x3A8] = 0;
    HeroMove.raw[0x3AE] = 0;
    ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
}

extern "C" {

bool heroMoveAppointLeader(s32 member) {
    if (!heroMoveIsMember(member)) {
        return false;
    }
    *(s32*)&HeroMove.raw[0] = member;
    if (heroMoveGetNeckMode(member) == 1) {
        heroMoveSetNeckMode(member, 0);
    }
    remakeFormation();
    initLeaderLog();
    return true;
}

void heroMoveSyncWithHero() {
    u8 join = 0;
    if (isStoryMode()) {
        if (heroGetStatus(0, 0x18, 0) != 0) {
            join = 1;
        }
    }
    if (join) {
        heroMoveJoinMember(1);
    } else {
        heroMoveDismissMember(1);
    }
}

void heroMoveMoveParty() {
    s32 i = 0;
    do {
        if (heroMoveIsMember(i)) {
            if (i != heroMoveGetLeader()) {
                moveParty((HEROMOVE_MEMBER)i);
            }
        }
        i++;
    } while (i < 4);
}

}

extern "C" void heroMoveCallStepCallback(s32 a, s32 b);

extern "C" {

s32 heroMoveDismissMember(s32 member) {
    if (member < 0 || member >= 4) {
        return 0;
    }
    if (member == heroMoveGetLeader()) {
        return 0;
    }
    HeroMoveMember* m = (HeroMoveMember*)((u8*)&HeroMove + (member << 5));
    m->flags = m->flags & 0xFFFE;
    remakeFormation();
    return 1;
}

s32 heroMoveSetNeckMode(s32 member, s32 mode) {
    unsigned long group;
    unsigned long res;
    HeroMoveMember* m;
    if (mode < 0 || mode >= 2) {
        return 0;
    }
    if (!heroMoveIsMember(member)) {
        return 0;
    }
    getResID(&group, &res, (HEROMOVE_MEMBER)member);
    m = (HeroMoveMember*)((u8*)&HeroMove + (member << 5));
    if (m->neckMode != 1) {
    } else {
        peopleRemoveNeckTarget(group, res, 1.0f);
    }
    if (mode != 1) {
    } else {
        peopleSetNeckTargetHero(group, res);
    }
    m->neckMode = mode;
    return 1;
}

void heroMoveSetColision(u8 enable) {
    unsigned long group;
    unsigned long res;
    s32 i = 0;
    do {
        if (heroMoveIsMember(i)) {
            getResID(&group, &res, (HEROMOVE_MEMBER)i);
            if (enable != 0) {
                peopleSetCollision(group, res, 1);
                peopleSetFlagOn(group, res, 0x700);
            } else {
                peopleSetFlagOff(group, res, 0x100);
                peopleSetFlagOff(group, res, 0x400);
                peopleSetCollision(group, res, 0);
            }
        }
        i++;
    } while (i < 4);
}

void heroMoveTermEvent() {
    unsigned long group;
    unsigned long res;
    s32 i = 0;
    do {
        if (heroMoveIsMember(i)) {
            getResID(&group, &res, (HEROMOVE_MEMBER)i);
            peopleSetCollision(group, res, 1);
            peopleSetFlagOn(group, res, 0x700);
            peopleSetFlagOff(group, res, 0x80000008);
        }
        i++;
    } while (i < 4);
    ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    peopleRemoveNeckTarget(0, 0x64, 1.0f);
}

void heroMoveInitEvent() {
    unsigned long group;
    unsigned long res;
    s32 i = 0;
    do {
        if (heroMoveIsMember(i)) {
            getResID(&group, &res, (HEROMOVE_MEMBER)i);
            getModel((HEROMOVE_MEMBER)i);
            updateAnimation(0.0f, (HEROMOVE_MEMBER)i);
            peopleSetFlagOn(group, res, 0x80000008);
            peopleSetFlagOff(group, res, 0x100);
            peopleSetFlagOff(group, res, 0x400);
            peopleSetCollision(group, res, 0);
        }
        i++;
    } while (i < 4);
}

void heroMoveSetEventList(u8 kind, s32 list, s32 owner) {
    switch (kind) {
    case 1:
        memcpy(&HeroMove.raw[0x498], (void*)list, 0xD0);
        *(s32*)&HeroMove.raw[0x63C] = owner;
        break;
    case 2:
        memcpy(&HeroMove.raw[0x568], (void*)list, 0xD0);
        *(s32*)&HeroMove.raw[0x640] = owner;
        break;
    case 3:
        memcpy(&HeroMove.raw[0x3C8], (void*)list, 0xD0);
        *(s32*)&HeroMove.raw[0x638] = owner;
        break;
    }
}

void heroMovePoolCounter(s32 kind, s32 amount) {
    switch (kind) {
    case 0:
        *(s32*)&HeroMove.raw[0x644] += amount;
        break;
    case 1:
        *(s32*)&HeroMove.raw[0x648] += amount;
        break;
    case 2:
        *(s32*)&HeroMove.raw[0x64C] += amount;
        break;
    case 3:
        *(s32*)&HeroMove.raw[0x650] += amount;
        break;
    }
}

}

extern "C" void heroMoveCallStepCallback(s32 a, s32 b) {
    HeroMoveSlot* p = (HeroMoveSlot*)&HeroMove;
    s32 i = 0;
    do {
        HeroMoveSlot* e = &p[0x6C];
        if (e != 0) {
            u32 fn = e->fn;
            if (fn != 0) {
                ((void (*)(s32, s32, s32))fn)(e->arg, a, b);
            }
        }
        i++;
        p++;
    } while (i < 8);
}

extern "C" u8 heroMoveCallStepCallbackAll() {
    u8 called = 0;
    s32 count;
    count = *(s32*)&HeroMove.raw[0x644];
    if (count != 0) {
        heroMoveCallStepCallback(0, count);
        called = 1;
        *(s32*)&HeroMove.raw[0x644] = 0;
    }
    count = *(s32*)&HeroMove.raw[0x648];
    if (count != 0) {
        heroMoveCallStepCallback(1, count);
        called = 1;
        *(s32*)&HeroMove.raw[0x648] = 0;
    }
    count = *(s32*)&HeroMove.raw[0x64C];
    if (count != 0) {
        heroMoveCallStepCallback(2, count);
        called = 1;
        *(s32*)&HeroMove.raw[0x64C] = 0;
    }
    count = *(s32*)&HeroMove.raw[0x650];
    if (count != 0) {
        heroMoveCallStepCallback(3, count);
        called = 1;
        *(s32*)&HeroMove.raw[0x650] = 0;
    }
    return called;
}

static void cbTsureFriend(long, FootStepCounter counter, long amount) {
    if (counter != 1) {
        *(s32*)&HeroMove.raw[0x3A4] += amount;
        while (*(s32*)&HeroMove.raw[0x3A4] > 0x100) {
            s32 i = 0;
            for (; i < 6; i++) {
                Pokemon* p = (Pokemon*)heroGetStatus(0, 3, i);
                if (p != 0 && pokemonCheckValid(p)) {
                    actionFriendSet(p, 5);
                }
            }
            *(s32*)&HeroMove.raw[0x3A4] -= 0x100;
        }
    }
}

static void remakeFormation() {
    f32 d = 12.0f;
    s32 i;
    HeroMove.members[HeroMove.members[0].x0].dist = 0.0f;
    for (i = 0; i < 4; i++) {
        if ((HeroMove.members[i].flags & 1) && HeroMove.members[0].x0 != i) {
            HeroMove.members[i].dist = d;
            d += 12.0f;
        }
    }
}

extern "C" {

s32 heroMoveJoinMember(s32 member) {
    Hero* hero;
    HeroMoveMember* m;
    if (member < 0 || member >= 4) {
        return 0;
    }
    if (heroMoveIsMember(member)) {
        return 1;
    }
    hero = Hero::getHeroPtr();
    hero->setFollowerGrpID(0);
    switch (member) {
    case 1:
        hero->setFollowerResID(0x65);
        hero->setFollowerID(1);
        break;
    case 2:
        hero->setFollowerResID(0x68);
        hero->setFollowerID(2);
        break;
    case 3:
        hero->setFollowerResID(0x69);
        hero->setFollowerID(3);
        break;
    }
    m = &HeroMove.members[member];
    m->flags = m->flags | 1;
    heroMoveSetNeckMode(member, 1);
    remakeFormation();
    setDisp((HEROMOVE_MEMBER)member, true);
    return 1;
}

}

static void _heroMoveFinalize(unsigned int, FloorEnterMode) {
    u8 smooth = HeroMove.raw[0x3AC];
    HeroMove.raw[0x3AD] = 0;
    if (smooth != 0) {
        if (floorDataBiosGetFloorKind(floorDataBiosGetPtr()) == 1) {
            floorCreateThread(0x80, 0, 1, _closeHeroThread);
        }
    }
}

extern "C" {

s32 heroMoveAddStepCallback(void (*fn)(long, FootStepCounter, long), s32 arg) {
    s32 i = 0;
    HeroMoveSlot* p = (HeroMoveSlot*)&HeroMove;
    for (; i < 8; i++, p++) {
        if (p[0x6C].fn == 0) {
            break;
        }
    }
    if (i >= 8) {
        return -1;
    }
    p = (HeroMoveSlot*)&HeroMove + i;
    p[0x6C].fn = (u32)fn;
    p[0x6C].arg = arg;
    return i;
}

void heroMoveAllInit() {
    initHeroMove();
    heroMoveJoinMember(0);
    heroMoveAppointLeader(0);
    *(f32*)&HeroMove.raw[0x35C] = 0.0f;
    *(s32*)&HeroMove.raw[0x3B4] = 0;
    *(s32*)&HeroMove.raw[0x360] = 0;
    *(s32*)&HeroMove.raw[0x368] = 0;
    *(s32*)&HeroMove.raw[0x370] = 0;
    *(s32*)&HeroMove.raw[0x378] = 0;
    *(s32*)&HeroMove.raw[0x380] = 0;
    *(s32*)&HeroMove.raw[0x388] = 0;
    *(s32*)&HeroMove.raw[0x390] = 0;
    *(s32*)&HeroMove.raw[0x398] = 0;
    *(s32*)&HeroMove.raw[0x3A0] = 0;
    heroMoveAddStepCallback(cbPoison, 0);
    *(s32*)&HeroMove.raw[0x3A4] = 0;
    heroMoveAddStepCallback(cbTsureFriend, 0);
    HeroMove.raw[0x3AE] = 0;
    *(s32*)&HeroMove.raw[0x644] = 0;
    *(s32*)&HeroMove.raw[0x648] = 0;
    *(s32*)&HeroMove.raw[0x64C] = 0;
    *(s32*)&HeroMove.raw[0x650] = 0;
    ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    FloorModuleInterface_clear(&_floorModuleHero);
    _floorModuleHero.pre = _heroMoveInitialize;
    _floorModuleHero.post = _heroMoveFinalize;
    _floorModuleHero.getName = _heroMoveGetModuleName;
    floorRegisterModule(0x80, 0, &_floorModuleHero);
}

}

extern "C" s32 heroGetFollower() {
    u8* people;
    unsigned long res;
    Hero* hero;
    hero = Hero::getHeroPtr();
    res = hero->getFollowerResID();
    people = (u8*)peopleGet(hero->getFollowerGrpID(), res);
    if (people == 0) {
        return 0;
    }
    if (people[0] == 0) {
        return 0;
    }
    if (people[0xD] == 0) {
        return 0;
    }
    if (*(u32*)(people + 0x1C) == 0) {
        return 0;
    }
    switch (hero->getFollowerResID()) {
    case 0x65:
        return HeroMove.members[1].flags & 1;
    case 0x68:
        return 2 & -(HeroMove.members[2].flags & 1);
    case 0x69:
        return 3 & -(HeroMove.members[3].flags & 1);
    default:
        return 0;
    }
}

static f32 moveLeaderPosition(HEROMOVE_MEMBER);
static void procStep(HEROMOVE_MEMBER);
static void updateLeaderMovement(HEROMOVE_MEMBER, float*);
static void updateLeaderLog();
static u8 updateChat(HEROMOVE_MEMBER);

static f32 moveLeader(HEROMOVE_MEMBER member) {
    u32 changed = GSinputButtonsChanged(1);
    if ((GSinputButtonsPressed(1) & changed & 0x100) && updateChat(member) != 0) {
        return 0.0f;
    }
    return moveLeaderPosition(member);
}

static void proc1Step(f32 dt) {
    Hero* hero = Hero::getHeroPtr();
    if (isStoryMode()) {
        unsigned long group;
        unsigned long res;
        heroMoveGetResID(&group, &res, (HEROMOVE_MEMBER)heroMoveGetLeader());
        if (peopleCheckFlag(group, res, 0x80000000) == 0) {
            f32* accum = (f32*)&HeroMove.raw[0x35C];
            *accum = *accum + dt;
            while (*accum >= 7.0f) {
                hero->addFootStep(1);
                heroMoveCallStepCallback(0, 1);
                *accum = *accum - 7.0f;
            }
        }
    }
}

static f32 moveLeaderPosition(HEROMOVE_MEMBER member) {
    GSvec prev;
    GSvec cur;
    GSvec delta;
    float move;
    unsigned long group;
    unsigned long res;
    u8 rate = GSgfxVideoGetVsyncRate();
    f32 frameTime = (f32)timeGetLastFrameTime(rate);
    f32 step = (30.0f * frameTime) / rate;
    f32 dist;
    getPos(&prev, member);
    updateLeaderMovement(member, &move);
    getPos(&cur, member);
    PSVECSubtract(&cur, &prev, &delta);
    getResID(&group, &res, member);
    dist = PSVECMag(&delta);
    if (step == 0.0f) {
        updateMotion(member, 0.0f);
    } else {
        updateMotion(member, dist / step);
    }
    updateLeaderLog();
    return dist;
}

extern "C" {

s32 heroMoveMain() {
    unsigned long group;
    unsigned long res;
    u32 total = 0;
    s32 i;
    u8* p1;
    u8* p2;
    u8* p3;
    f32 moved;
    if (HeroMove.raw[0x3AD] == 0) {
        HeroMove.raw[0x3AD] = 1;
    }
    if (dbgMenuIsOpen() != 0) {
        return 0;
    }
    if (menuIsCheck(0x23) != 0) {
        return 0;
    }
    if (floorGetFloorState() == 2 || floorGetFloorState() == 6) {
        return 0;
    }
    if (cameraGetType() == 6) {
        return 0;
    }
    if (menuIsCheck(0xA) != 0) {
        return 0;
    }
    if (*(s32*)&HeroMove.raw[0x3A8] > 0) {
        *(s32*)&HeroMove.raw[0x3A8] -= 1;
        return 0;
    }
    *(u32*)&HeroMove.raw[0x65C] = pokecoloFrameCounter;
    heroMoveGetResID(&group, &res, (HEROMOVE_MEMBER)heroMoveGetLeader());
    if (peopleCheckFlag(group, res, 0x80000000) != 0) {
        return 0;
    }
    if (*(u32*)&HeroMove.raw[0x3B4] != 0) {
        *(u32*)&HeroMove.raw[0x3B4] = 0;
        floorExecScriptInteger(*(s32*)&HeroMove.raw[0x3B8], *(s32*)&HeroMove.raw[0x3BC], *(s32*)&HeroMove.raw[0x3C0], *(s32*)&HeroMove.raw[0x3C4]);
        return 0;
    }
    if (heroMoveCallStepCallbackAll() != 0) {
        return 0;
    }
    p3 = (u8*)&HeroMove;
    i = 0;
    while (i < *(s32*)&HeroMove.raw[0x638]) {
        total += floorEventExecScript(3, *(u16*)(p3 + 0x3F8));
        p3 += 0x34;
        i++;
    }
    p2 = (u8*)&HeroMove;
    i = 0;
    while (i < *(s32*)&HeroMove.raw[0x640]) {
        total += floorEventExecScript(2, *(u16*)(p2 + 0x598));
        p2 += 0x34;
        i++;
    }
    p1 = (u8*)&HeroMove;
    i = 0;
    while (i < *(s32*)&HeroMove.raw[0x63C]) {
        total += floorEventExecScript(1, *(u16*)(p1 + 0x4C8));
        p1 += 0x34;
        i++;
    }
    *(s32*)&HeroMove.raw[0x63C] = 0;
    *(s32*)&HeroMove.raw[0x640] = 0;
    *(s32*)&HeroMove.raw[0x638] = 0;
    if (*(u32*)&HeroMove.raw[0x3B4] != 0) {
        return 0;
    }
    if (gimmickBoxIsGimmickMoving() == 0 && total == 0 && peopleCheckFlag(group, res, 0x80000000) == 0) {
        s32 changed = GSinputButtonsChanged(1);
        if (GSinputButtonsPressed(1) & changed & 0x1C00) {
            if (floorSound_getBgmMaskObj() != 0) {
                floorSound_getBgmMaskObj()->stopMask();
            }
            menuFieldMain(0);
            return 0;
        }
    }
    if (pokecoloFrameCounter - *(u32*)&HeroMove.raw[0x65C] > 5) {
        ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    }
    moved = moveLeader((HEROMOVE_MEMBER)heroMoveGetLeader());
    procStep((HEROMOVE_MEMBER)heroMoveGetLeader());
    proc1Step(moved);
    return 0;
}

}
