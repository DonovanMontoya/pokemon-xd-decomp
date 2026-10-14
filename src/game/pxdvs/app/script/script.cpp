#include <game/pxdvs/app/script/scriptPrivate.hpp>

extern "C" u8 scriptPeopleInsideCheck(GSvec*, GSvec*, GSvec*, f32);
static s32 _fnDistanceSortFunc(const void*, const void*);
static u8 _checkCrossPeople(GSvec*, GSvec*, GSvec*, GSvec*);
static u32 _searchPeopleColiInfo(GSvec*, f32, PeopleRangeInfo_t*, int, GSvec*);
static u8 _peopleMoveCheckTime(u32, u32, f32);
static void _scriptEventWaitMotion(_GSmodel*);
static void _scriptEventSetMotion(_GSmodel*, s16, f32);

extern "C" {
static glowEffect* m_glow;
static s32 _scriptEventColID = -1;
static GSvec _vHizukiWalkkPos[3];
static s32 _vHizukiWalkPosCount;

u32 scriptSoundOpenPlayME(u32 me, u32 time, u32 flag) {
    FloorBgmMask* mask = floorSound_getBgmMaskObj();
    f32 wait = (f32)time / 1000.0f;
    u32 bgm = soundGetBGMID();
    u32 env = soundGetEnvID();
    u32 volume = soundGetVolume();
    GSflagSet(0x8FA, 1);
    if (mask) mask->startMECallback();
    if (bgm != 0xFFFFFFFF) {
        GSsndPause(bgm, time, 0);
        soundSetVolumeID(env, time, 0);
        scriptWaitTime(wait);
    }
    flag = soundPlayME(me, time, flag);
    if (me != 0xFFFFFFFF) {
        GSsndContinue(bgm, time, 0);
        soundSetVolumeID(env, time, volume);
        scriptWaitTime(wait);
    }
    if (mask) mask->endMECallback();
    GSflagSet(0x8FA, 0);
    return flag;
}

u8 pcBoxAllSearchPokemon(s32 id) {
    s8 box;
    s8 slot;
    for (box = 0; box < 8; ++box) {
        for (slot = 0; slot < 30; ++slot) {
            if (id == pokemonBiosGetPokemonDataId(PCBOX::getPointer()->getPokemon(box, slot))) return 1;
        }
    }
    return 0;
}

void scriptSetLensFlare(u32 id, u8 visible, f32 x, f32 y, f32 z) {
    if (id != 0) {
        void* lens = GSresGetResource(floorGetCurrentGroupID(), id);
        if (lens != 0) {
            GSlensFlareSetVisible(lens, 0);
            GSvec pos;
            pos.param1 = x;
            pos.param2 = y;
            pos.param3 = z;
            GSlensFlareSetSunPosition(lens, &pos);
            GSlensFlareSetVisible(lens, visible);
        }
    }
}

void scriptGlowEnd() {
    if (m_glow != 0) {
        delete m_glow;
        m_glow = 0;
    }
}

void scriptGlowStart(u8 r, u8 g, u8 b, u8 flag, u8 blend, f32 scale) {
    if (m_glow == 0) m_glow = new glowEffect;
    m_glow->scale = scale;
    m_glow->r = r;
    m_glow->g = g;
    m_glow->b = b;
    if (flag) m_glow->flag = 0;
    else m_glow->flag = 1;
    m_glow->blend = blend;
    m_glow->Start();
}

s32 scriptPokemonTeachWazaIndex(s32 waza) {
    switch (waza) {
    case 0x22: return 0;
    case 0x26: return 1;
    case 0x45: return 2;
    case 0x66: return 3;
    case 0x8A: return 4;
    case 0x56: return 5;
    case 0xA4: return 6;
    case 0xC4: return 7;
    case 0xCF: return 8;
    case 0x8F: return 9;
    case 0x78: return 10;
    case 0xAB: return 11;
    }
    return -1;
}

u8 scriptPokemonRememberWaza(Pokemon* pokemon, s32 waza) {
    u8 found = 0;
    s32 i;
    for (i = 0; i < 4; ++i) {
        if (waza == pokemonBiosGetPokemonWazaDataId(pokemon, i)) found = 1;
    }
    return found;
}

u8 scriptSetEndedMotion(u32 group, u32 resource, s32 motion, u8 loop) {
    tagPeopleWork* work = peopleGet(group, resource);
    if (work == 0) return 0;
    _GSmodel* model = peopleBiosGetModelPtr(work);
    if (model == 0) return 0;
    work->setAnimType(GS_ANIM_ONCE);
    for (;;) {
        if (GSmodelHasAnimationEnded(model)) break;
        GSthreadSwitch();
    }
    work->motion = motion;
    work->motionBlend = 0.0f;
    work->setAnimIndex(motion);
    work->setAnimFrame(0.0f);
    work->setAnimRate(0.5f, true);
    GSmodelSetTexAnimIndex(model, motion);
    GSmodelSetTexAnimFrame(model, 0.0f);
    GSmodelSetTexAnimRate(model, 0.5f * peopleViewerGetPlaySpeedRate(work));
    if (loop) work->setAnimType(GS_ANIM_LOOP);
    else work->setAnimType(GS_ANIM_ONCE);
    work->flags |= 0x4000;
    return 1;
}

u8 scriptHizukiAway(u32 group, u32 resource) {
    PeopleRangeInfo_t infos[8];
    GSvec neckPos;
    GSvec followerPos;
    GSvec heroPos;
    GSvec personPos;
    u32 heroGroup;
    u32 heroResource;
    u32 followerGroup;
    u32 followerResource;
    int i;
    PeopleRangeInfo_t* found;
    s32 j;
    followerPos.param1 = 0.0f;
    followerPos.param2 = 0.0f;
    followerPos.param3 = 0.0f;
    Hero* hero = Hero::getHeroPtr();
    if (!heroMoveGetResID(&followerGroup, &followerResource, hero->getFollowerID())) return 0;
    peopleGetPos(followerGroup, followerResource, &followerPos);
    if (!heroMoveGetResID(&heroGroup, &heroResource, 0)) return 0;
    peopleGetPos(heroGroup, heroResource, &heroPos);
    tagPeopleWork* work = peopleGet(group, resource);
    if (work == 0) return 0;
    peopleGetPos(group, resource, &personPos);
    PeopleInfo* info = peopleInfoBiosGetPtr(work->resource);
    if (info == 0) return 0;
    f32 radius = peopleInfoBiosGetColBallSize(info);
    radius += 1.0f;
    radius = 1.0f + radius;
    if (!scriptPeopleInsideCheck(&heroPos, &personPos, &followerPos, radius)) return 0;
    _searchPeopleColiInfo(&heroPos, 8.0f, infos, 8, &followerPos);
    qsort(infos, 8, sizeof(PeopleRangeInfo_t), _fnDistanceSortFunc);
    for (i = 0; i < 8; ++i) {
        if (infos[i].hit == 1) continue;
        if (!scriptPeopleInsideCheck(&heroPos, &personPos, &infos[i].position, 4.0f) &&
            !scriptPeopleInsideCheck(&followerPos, &infos[i].position, &heroPos, 4.0f) &&
            !_checkCrossPeople(&heroPos, &personPos, &followerPos, &infos[i].position)) {
            u8 reached;
            peopleInitEvent(followerGroup, followerResource);
            peopleWalkTo(followerGroup, followerResource, 1, &infos[i].position);
            reached = _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
            if (!reached) {
                s32 kind = infos[i].index;
                if (kind & 1) {
                    s32 target = -1;
                    if (kind == 3 || kind == 5) target = 4;
                    if (kind == 1 || kind == 7) target = 0;
                    found = infos;
                    for (j = 0; j < 8; ++j, ++found) {
                        if (found->index == target) break;
                    }
                    if (found->hit == 0 && !scriptPeopleInsideCheck(&heroPos, &personPos, &found->position, 4.0f)) {
                        peopleWalkTo(followerGroup, followerResource, 1, &found->position);
                        reached = _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
                    }
                }
            }
            if (!reached) {
                peopleGetNeckPos(followerGroup, followerResource, &neckPos);
                peopleRotateToXYZ(followerGroup, followerResource, neckPos.param1, neckPos.param2, neckPos.param3, 1.0f);
                _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
            }
            peopleTermEvent(followerGroup, followerResource);
            return 0;
        }
    }
    _searchPeopleColiInfo(&followerPos, 8.0f, infos, 8, &followerPos);
    qsort(infos, 8, sizeof(PeopleRangeInfo_t), _fnDistanceSortFunc);
    for (i = 0; i < 8; ++i) {
        if (infos[i].hit == 1) continue;
        if (!scriptPeopleInsideCheck(&followerPos, &infos[i].position, &heroPos, 4.0f) &&
            !_checkCrossPeople(&heroPos, &personPos, &followerPos, &infos[i].position) &&
            !scriptPeopleInsideCheck(&heroPos, &personPos, &infos[i].position, 4.0f)) {
            peopleInitEvent(followerGroup, followerResource);
            peopleWalkTo(followerGroup, followerResource, 1, &infos[i].position);
            if (!_peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f)) {
                peopleGetNeckPos(followerGroup, followerResource, &neckPos);
                peopleRotateToXYZ(followerGroup, followerResource, neckPos.param1, neckPos.param2, neckPos.param3, 1.0f);
                _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
            }
            peopleTermEvent(followerGroup, followerResource);
            return 0;
        }
    }
    return 0;
}

u8 scriptPeopleInsideCheck(GSvec* from, GSvec* to, GSvec* point, f32 radius) {
    GSvec target;
    GSvec middle;
    target.param1 = point->param1;
    target.param2 = point->param2;
    target.param3 = point->param3;
    if (PSVECDistance(from, to) < 20.0f) return peopleInsideCheck(from, to, &target, radius);
    PSVECAdd(from, to, &middle);
    PSVECScale(&middle, &middle, 0.5f);
    if (peopleInsideCheck(from, &middle, &target, radius)) return 1;
    return peopleInsideCheck(&middle, to, &target, radius);
}
}

static s32 _fnDistanceSortFunc(const void* a, const void* b) {
    const PeopleRangeInfo_t* pa = (const PeopleRangeInfo_t*)a;
    const PeopleRangeInfo_t* pb = (const PeopleRangeInfo_t*)b;
    if (pa->distance == pb->distance) return 0;
    else if (pa->distance > pb->distance) return 1;
    else return -1;
}

static u8 _checkCrossPeople(GSvec* a, GSvec* b, GSvec* c, GSvec* d) {
    GSvec p2;
    GSvec p1;
    GSvec p0;
    GSvec v2;
    GSvec v1;
    GSvec out;
    GSvec v3;
    f32 t;
    p0.param1 = a->param1;
    p0.param2 = a->param2;
    p0.param3 = a->param3;
    p1.param1 = b->param1;
    p1.param2 = b->param2;
    p1.param3 = b->param3;
    p2.param1 = b->param1;
    p2.param2 = b->param2;
    p2.param3 = b->param3;
    p2.param2 = 1.0f;
    PSVECSubtract(&p0, &p1, &v1);
    PSVECNormalize(&v1, &v1);
    GSvec* pv2 = &v2;
    GSvec* pp2 = &p2;
    PSVECSubtract(&p0, pp2, pv2);
    PSVECNormalize(pv2, pv2);
    PSVECCrossProduct(&v1, pv2, &v3);
    if (GScolsys2UtilGetCpPlaneLine(&out, &t, &v3, &p0, c, d) == 0) return 0;
    if (t < 0.0f || t > 1.0f) return 0;
    return 1;
}

static u32 _searchPeopleColiInfo(GSvec* center, f32 radius, PeopleRangeInfo_t* info, int count, GSvec* ref) {
    s32 i;
    u32 mask = 0;
    for (i = 0; i < count; ++i, ++info) {
        GSvec offset;
        f32 angle;
        info->index = i;
        angle = (f32)i * (6.2831855f / (f32)count);
        offset.param1 = radius * (f32)cos(angle);
        offset.param2 = 0.0f;
        offset.param3 = radius * (f32)sin(angle);
        PSVECAdd(&offset, center, &info->position);
        if (GScolsys2HitCollision(center, &info->position, 0, 4.0f)) {
            info->hit = 1;
            mask |= 1 << i;
        } else {
            info->hit = 0;
        }
        info->distance = PSVECDistance(&info->position, ref);
    }
    return mask;
}

extern "C" {
void scriptOpenItemMenu() {
    s32 cursor = menuGetCursorFromItemID(0x2C, 0x9B);
    if (cursor < 0) cursor = 0;
    CursorPos tmp;
    tmp.x = 0;
    tmp.y = (s8)cursor;
    CursorPos pos = tmp;
    cursorBiosSetPos(2, &pos);
    menuFieldMain(1);
}
}

extern "C" {
s32 floorEventCtrlElevatorFollower(u32 floorID, u32 index, u16 control, u32 mode) {
    GSvec position;
    GSvec pos3;
    GSvec pos2;
    f32 frame = 0.0f;
    s32 sound;
    ScriptDoor* door;
    _GSmodel* model;
    s16 motion = -1;
    u8 reached = 0;
    GSpart* part;
    s32 i;
    Hero* hero = Hero::getHeroPtr();
    if (index >= *floor_door_list_number) return -1;
    door = &floor_door_list[index];
    if (door->resourceID == 0) return -1;
    model = floorGetResource(floorID, door->resourceID);
    if (model == 0) return -1;
    GSmodelUseRootJointAnimation(model, 1);
    u32 modelGroup = floorDataBiosGetGroupID(floorDataBiosGetPtr(floorID));
    if (mode >= 2 && mode <= 5) {
        peopleAttach(0, 0x64, modelGroup, door->resourceID, door->partIndex);
        peopleAttach(0, hero->getFollowerResID(), modelGroup, door->resourceID, door->partIndex);
        switch (mode) {
        case 2:
            peopleSetPosXYZ(0, 0x64, 0.0f, 0.0f, 5.0f);
            peopleSetPosXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, -5.0f);
            break;
        case 3:
            peopleSetPosXYZ(0, 0x64, 0.0f, 0.0f, -5.0f);
            peopleSetPosXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, 5.0f);
            break;
        case 4:
            peopleSetPosXYZ(0, 0x64, 5.0f, 0.0f, 0.0f);
            peopleSetPosXYZ(0, hero->getFollowerResID(), -5.0f, 0.0f, 0.0f);
            break;
        case 5:
            peopleSetPosXYZ(0, 0x64, -5.0f, 0.0f, 0.0f);
            peopleSetPosXYZ(0, hero->getFollowerResID(), 5.0f, 0.0f, 0.0f);
            break;
        }
        peopleRemoveNeckTarget(0, hero->getFollowerResID(), 1.0f);
        _scriptEventSetMotion(model, control, 0.0f);
        return 0;
    }
    switch (control) {
    case 1: case 2: case 0x81: case 0x82: {
        _scriptEventSetMotion(model, door->openMotion, frame);
        sound = control & 0x80;
        if (sound != 0) GSsndPlayNow(0x27);
        _scriptEventWaitMotion(model);
        part = GSmodelGetPart(model, door->partIndex);
        GSpartGetTransform(part, &position, 0, 0);
        GSpartFree(part);
        if ((control & 1) != 0) {
            peopleRemoveNeckTarget(0, hero->getFollowerResID(), 1.0f);
            peopleSetSpeedRate(0, 0x64, 2.0f);
            peopleSetSpeedRate(0, hero->getFollowerResID(), 2.0f);
            position.param3 -= 5.0f;
            peopleWalkTo(0, 0x64, 1, &position);
            pos2.param1 = position.param1;
            pos2.param2 = position.param2;
            pos2.param3 = 10.0f + position.param3;
            scriptWaitTime(0.2f);
            if (_vHizukiWalkPosCount != 0) {
                for (i = 0; i < _vHizukiWalkPosCount; ++i) {
                    peopleWalkTo(0, hero->getFollowerResID(), 1, &_vHizukiWalkkPos[i]);
                    reached = _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
                    if (reached) break;
                }
            }
            if (!reached) peopleWalkTo(0, hero->getFollowerResID(), 1, &pos2);
            peopleMoveCheck(0, 0x64, 1);
            if (!reached) reached = _peopleMoveCheckTime(0, hero->getFollowerResID(), 3.0f);
            peopleRotateToAngle(0, 0x64, 0.0f, 2.0f);
            if (!reached) peopleRotateToAngle(0, hero->getFollowerResID(), 0.0f, 2.0f);
        } else {
            peopleDetach(0, 0x64, 0);
            peopleDetach(0, hero->getFollowerResID(), 0);
            peopleSetNeckTargetHero(0, hero->getFollowerResID());
            part = GSmodelGetPart(model, door->partIndex);
            GSpartGetTransform(part, &position, 0, 0);
            GSpartFree(part);
            pos3.param1 = position.param1;
            pos3.param2 = position.param2;
            pos3.param3 = 5.0f + position.param3;
            peopleSetPos(0, 0x64, &pos3);
            pos2.param1 = position.param1;
            pos2.param2 = position.param2;
            pos2.param3 = position.param3 - 5.0f;
            peopleSetPos(0, hero->getFollowerResID(), &pos2);
            pos3.param3 += 25.0f;
            pos2.param3 += 25.0f;
            peopleSetSpeedRate(0, 0x64, 2.0f);
            peopleSetSpeedRate(0, hero->getFollowerResID(), 2.0f);
            peopleSetFlagOff(0, 0x64, 0x2000);
            peopleSetFlagOff(0, hero->getFollowerResID(), 0x2000);
            peopleWalkTo(0, 0x64, 1, &pos3);
            scriptWaitTime(0.2f);
            peopleWalkTo(0, hero->getFollowerResID(), 1, &pos2);
            scriptWaitTime(0.5f);
        }
        _scriptEventSetMotion(model, door->closeMotion, frame);
        if (sound != 0) GSsndPlayNow(0x27);
        _scriptEventWaitMotion(model);
        peopleMoveCheck(0, 0x64, 1);
        peopleMoveCheck(0, hero->getFollowerResID(), 1);
        peopleSetSpeedRate(0, 0x64, 1.0f);
        peopleSetSpeedRate(0, hero->getFollowerResID(), 1.0f);
        break;
    }
    case 0xC0:
        _scriptEventWaitMotion(model);
        if ((control & 0x80) != 0) {
            GSsndStopNow(0x29);
            GSsndPlayNow(0x2A);
        }
        break;
    case 0x100:
        break;
    default:
        if ((control & 4) != 0) motion = door->ascendMotion;
        else if ((control & 8) != 0) motion = door->descendMotion;
        if (motion < 0) return -1;
        if (GSmodelCanAnimate(model) == 0) return -1;
        peopleSetFlagOn(0, 0x64, 0x2000);
        peopleSetFlagOn(0, hero->getFollowerResID(), 0x2000);
        if ((control & 0x20) != 0) {
            peopleAttach(0, 0x64, modelGroup, door->resourceID, door->partIndex);
            peopleAttach(0, hero->getFollowerResID(), modelGroup, door->resourceID, door->partIndex);
            if (mode != 0) {
                peopleSetPosXYZ(0, 0x64, 0.0f, 0.0f, 5.0f);
                peopleSetRotXYZ(0, 0x64, 0.0f, 0.0f, 0.0f);
                peopleSetPosXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, -5.0f);
                peopleSetRotXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, 0.0f);
            } else {
                peopleSetPosXYZ(0, 0x64, 0.0f, 0.0f, -5.0f);
                peopleSetRotXYZ(0, 0x64, 0.0f, 0.0f, 0.0f);
                peopleSetPosXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, 5.0f);
                peopleSetRotXYZ(0, hero->getFollowerResID(), 0.0f, 0.0f, 0.0f);
            }
            peopleRemoveNeckTarget(0, hero->getFollowerResID(), 1.0f);
        }
        if ((control & 0x10) != 0) {
            GSmodelSetAnimIndex(model, motion);
            GSmodelGetFrameCount(model, &frame, 0);
            frame -= 1.0f;
        }
        _scriptEventSetMotion(model, motion, frame);
        if ((control & 0x40) != 0) {
            floorEventCtrlElevatorHero(floorID, index, 0xC0, mode);
            peopleSetFlagOff(0, 0x64, 0x2000);
            peopleSetFlagOff(0, hero->getFollowerResID(), 0x2000);
        } else if ((control & 0x80) != 0) {
            GSsndPlayNow(0x29);
        }
        break;
    }
    GSmodelGetFrameCount(model, &frame, 0);
    return (s32)(100.0f * ((2.0f * frame) / (f32)GSgfxVideoGetVsyncRate()));
}

s32 floorEventCtrlElevatorHero(u32 floorID, u32 index, u16 control, u32 mode) {
    GSvec position;
    GSvec pos2;
    f32 frame = 0.0f;
    s32 sound;
    ScriptDoor* door;
    _GSmodel* model;
    s16 motion = -1;
    GSpart* part;
    Hero::getHeroPtr();
    if (index >= *floor_door_list_number) return -1;
    door = &floor_door_list[index];
    if (door->resourceID == 0) return -1;
    model = floorGetResource(floorID, door->resourceID);
    if (model == 0) return -1;
    GSmodelUseRootJointAnimation(model, 1);
    u32 modelGroup = floorDataBiosGetGroupID(floorDataBiosGetPtr(floorID));
    if (mode >= 2 && mode <= 5) {
        peopleAttach(0, 0x64, modelGroup, door->resourceID, door->partIndex);
        peopleSetPosXYZ(0, 0x64, 0.0f, 0.0f, 0.0f);
        _scriptEventSetMotion(model, control, 0.0f);
        return 0;
    }
    switch (control) {
    case 1: case 2: case 0x81: case 0x82: {
        _scriptEventSetMotion(model, door->openMotion, frame);
        sound = control & 0x80;
        if (sound != 0) GSsndPlayNow(0x27);
        _scriptEventWaitMotion(model);
        part = GSmodelGetPart(model, door->partIndex);
        GSpartGetTransform(part, &position, 0, 0);
        GSpartFree(part);
        if ((control & 1) != 0) {
            peopleSetSpeedRate(0, 0x64, 2.0f);
            peopleWalkTo(0, 0x64, 1, &position);
            peopleMoveCheck(0, 0x64, 1);
            peopleRotateToAngle(0, 0x64, 0.0f, 2.0f);
        } else {
            peopleDetach(0, 0x64, 0);
            part = GSmodelGetPart(model, door->partIndex);
            GSpartGetTransform(part, &position, 0, 0);
            GSpartFree(part);
            pos2 = position;
            peopleSetPos(0, 0x64, &pos2);
            peopleSetSpeedRate(0, 0x64, 2.0f);
            pos2.param3 += 25.0f;
            peopleWalkTo(0, 0x64, 1, &pos2);
            scriptWaitTime(0.5f);
        }
        _scriptEventSetMotion(model, door->closeMotion, frame);
        if (sound != 0) GSsndPlayNow(0x27);
        _scriptEventWaitMotion(model);
        peopleMoveCheck(0, 0x64, 1);
        peopleSetSpeedRate(0, 0x64, 1.0f);
        break;
    }
    case 0xC0:
        _scriptEventWaitMotion(model);
        if ((control & 0x80) != 0) {
            GSsndStopNow(0x29);
            GSsndPlayNow(0x2A);
        }
        break;
    case 0x100:
        break;
    default:
        if ((control & 4) != 0) motion = door->ascendMotion;
        else if ((control & 8) != 0) motion = door->descendMotion;
        if (motion < 0) return -1;
        if (GSmodelCanAnimate(model) == 0) return -1;
        if ((control & 0x20) != 0) {
            peopleAttach(0, 0x64, modelGroup, door->resourceID, door->partIndex);
            if (mode != 0) {
                peopleSetPosXYZ(0, 0x64, 0.0f, 0.0f, 0.0f);
                peopleSetRotXYZ(0, 0x64, 0.0f, 0.0f, 0.0f);
            } else {
                peopleSetPosXYZ(0, 0x64, 0.0f, 0.0f, 0.0f);
                peopleSetRotXYZ(0, 0x64, 0.0f, 0.0f, 0.0f);
            }
        }
        if ((control & 0x10) != 0) {
            GSmodelSetAnimIndex(model, motion);
            GSmodelGetFrameCount(model, &frame, 0);
            frame -= 1.0f;
        }
        _scriptEventSetMotion(model, motion, frame);
        if ((control & 0x40) != 0) floorEventCtrlElevatorHero(floorID, index, 0xC0, mode);
        else if ((control & 0x80) != 0) GSsndPlayNow(0x29);
        break;
    }
    GSmodelGetFrameCount(model, &frame, 0);
    return (s32)(100.0f * ((2.0f * frame) / (f32)GSgfxVideoGetVsyncRate()));
}
}

static u8 _peopleMoveCheckTime(u32 group, u32 resource, f32 time) {
    while (time > 0.0f) {
        if (!peopleMoveCheck(group, resource, 0)) return 0;
        GSthreadSwitch();
        time -= GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
    }
    return 1;
}

static void _scriptEventWaitMotion(_GSmodel* model) {
    if (model == 0) return;
    while (!GSmodelHasAnimationEnded(model)) GSthreadSwitch();
}

static void _scriptEventSetMotion(_GSmodel* model, s16 motion, f32 frame) {
    if (model != 0 && motion >= 0) {
        GSmodelSetAnimIndex(model, motion);
        GSmodelSetAnimFrame(model, frame);
        GSmodelSetAnimRate(model, 0.5f);
        GSmodelSetAnimType(model, 0);
        GSmodelStartAnimation(model);
    }
}

extern "C" {
s32 scriptHeroCtrlElevator(u32 a, u32 b, u16 c, u32 mode) {
    Hero* hero = Hero::getHeroPtr();
    if (mode >= 2 && mode <= 5) return floorEventCtrlElevatorHero(a, b, c, mode);
    if (!hero->getFollowerID()) return floorEventCtrlElevatorHero(a, b, c, mode);
    return floorEventCtrlElevatorFollower(a, b, c, mode);
}

void scriptCheckHizukiFollow() {
    u32 group;
    u32 resource;
    Hero* hero = Hero::getHeroPtr();
    if (heroMoveGetResID(&group, &resource, hero->getFollowerID())) heroMoveChkHinderClear(hero->getFollowerID());
}

s32 scriptLighgtWaitMotion(u32 id, s32 wait) {
    void* light = GSresGetResourceAllGroup(id);
    if (light == 0) {
        GSlogWrite("\x83\x89\x83\x43\x83\x67[%d]\x82\xCC\x8E\xE6\x93\xBE\x82\xC9\x82\xB5\x82\xC1\x82\xCF\x82\xA2\n", id);
        return 0;
    }
    while (1) {
        if (GSlightHasAnimationEnded(light)) return 0;
        if (wait != 0) GSthreadSwitch();
        else return 0;
    }
    return 0;
}

void scriptLightStopMotion(u32 id) {
    void* light = GSresGetResourceAllGroup(id);
    if (light == 0) {
        GSlogWrite("\x83\x89\x83\x43\x83\x67[%d]\x82\xCC\x8E\xE6\x93\xBE\x82\xC9\x82\xB5\x82\xC1\x82\xCF\x82\xA2\n", id);
    } else {
        GSlightStopAnimation(light);
    }
}

void scriptLightSetMotion(u32 id, s32 anim, s32 frame, s32 loop) {
    void* light = GSresGetResourceAllGroup(id);
    if (light == 0) {
        GSlogWrite("\x83\x89\x83\x43\x83\x67[%d]\x82\xCC\x8E\xE6\x93\xBE\x82\xC9\x82\xB5\x82\xC1\x82\xCF\x82\xA2\n", id);
    } else {
        GSlightSetAnimIndex(light, anim);
        GSlightSetAnimRate(light, 0.5f);
        GSlightSetAnimFrame(light, (f32)frame);
        if (loop != 0) GSlightSetAnimType(light, 1);
        else GSlightSetAnimType(light, 0);
        GSlightStartAnimation(light);
    }
}

void scriptLightSetDisp(u32 id, s32 disp) {
    void* light = GSresGetResourceAllGroup(id);
    if (light == 0) {
        GSlogWrite("\x83\x89\x83\x43\x83\x67[%d]\x82\xCC\x8E\xE6\x93\xBE\x82\xC9\x82\xB5\x82\xC1\x82\xCF\x82\xA2\n", id);
    } else {
        GSlightSetActive(light, disp != 0);
    }
}

void scriptSetMemoFlag() {
    memoDataSetMemoFlag(0);
}

void scriptPartyChange(u8 join) {
    Hero::getHeroPtr();
    if (join) {
        heroSetStatus(0, 0x18, 1);
        heroMoveJoinMember(1);
    } else {
        heroSetStatus(0, 0x18, 0);
        heroMoveDismissMember(1);
    }
}

s32 controlTV() {
    heroMoveInitEvent();
    controlTVScreen();
    scriptWaitTime(3.0f);
    winMsgOpenFieldWithSE(1, 1, 0, 5);
    winMsgCloseField(1);
    heroMoveTermEvent();
    return 1;
}

s32 controlTVScreen() {
    floorSetOffscreenIndex(-1);
    floorOffscreenPlayWait();
    return 1;
}

u32 scriptGetRandom(u32 range) {
    u32 low = HSD_Rand();
    u32 high = HSD_Rand();
    u32 value = (high << 16) | low;
    return value % range;
}

void scriptWaitTime(f32 time) {
    f32 elapsed = 0.0f;
    while (elapsed < time) {
        GSthreadSwitch();
        elapsed += GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
    }
}

u16 scriptEncount(u32 encounter, u8 fade, s32 skip) {
    u32 result;
    u8 defeated = 0;
    GSflagOff(0x323);
    void* data = fightEncountDataBiosGetPtr(encounter);
    if (GSflagGet(0x30D)) {
        GSflagOff(0x323);
        if (GSflagGet(0x30D)) {
            floorExecSoundScript();
        } else {
            scriptBattleMountainEnd(0);
            floorSetFadeScript(0, 0x5960008);
        }
    } else {
        if (fade != 0 || skip != 0) GSflagOn(0x323);
        result = fightEncount(encounter);
        if (fightEncountDataBiosGetZenmetuFlag(data)) {
            if (!fightFloorIsGcHeroWin(0, fightGetFightResultId())) {
                GSthreadSwitch();
                GSthreadSwitch();
                GSthreadSwitch();
                defeated = 1;
            }
        }
        if (skip == 0 && !defeated && fade != 0) fadeSet(2, 0.5f);
    }
    GSflagOff(0x323);
    return result;
}

s32 scriptAddPoint(s32 amount) {
    scriptGetPoint();
    if (amount >= 0) heroAddPokecoupon(0, amount);
    else heroDecPokecoupon(0, -amount);
    return scriptGetPoint();
}

void scriptSetPoint(s32 value) {
    heroSetStatus(0, 0xD, value);
}

s32 scriptGetPoint() {
    return heroGetStatus(0, 0xD, 0);
}

s32 scriptAddPremium(s32 amount) {
    s32 value = GSflagGet(0x319);
    value += amount;
    GSflagSet(0x319, value);
    return value;
}

void scriptSetPremium(s32 value) {
    GSflagSet(0x319, value);
}

s32 scriptGetPremium() {
    return GSflagGet(0x319);
}

s32 scriptAddPokedoru(s32 amount) {
    if (amount >= 0) heroAddPokedoru(0, amount);
    else heroDecPokedoru(0, -amount);
    return scriptGetPokedoru();
}

s32 scriptGetPokedoru() {
    return heroGetStatus(0, 0xC, 0);
}

void scriptSetEventCol(s32 value) {
    scriptSetCol(scriptGetEventColID(), value);
}

s32 scriptGetEventColID() {
    return _scriptEventColID;
}

s32 scriptSetEventColID(s32 id) {
    s32 old = _scriptEventColID;
    _scriptEventColID = id;
    return old;
}

void scriptSetCol(s32 id, s32 value) {
    if (id >= 0) GScolsys2SetObjEnable(id, value);
}

u8 scriptHaveItem(u32 item) {
    return heroItemCheckHaveItemDataId(0, item);
}

s32 scriptAddItem(u32 item, s32 count) {
    s32 result;
    if (count > 0) result = heroItemAddItemDataId(0, item, count, -1);
    else if (count < 0) {
        count = -count;
        result = heroItemDecItemDataId(0, item, count, -1);
    }
    return result;
}

s32 scriptGetItem(s32 item, s32 count) {
    return floorEventGetTresure(4, item, count);
}

struct TemochiFlag { u32 low, high; };

u8 scriptCheckTemochiPokemon(u32 hero) {
    TemochiFlag table[6];
    table[0].low = 0x908;
    table[1].low = 0x909;
    table[2].low = 0x90A;
    table[3].low = 0x90B;
    table[4].low = 0x90C;
    table[5].low = 0x90D;
    table[0].high = 0x90E;
    table[1].high = 0x90F;
    table[2].high = 0x910;
    table[3].high = 0x911;
    table[4].high = 0x912;
    table[5].high = 0x913;
    u8 used[6];
    s32 i;
    s32 j;
    for (i = 0; i < 6; ++i) used[i] = 0;
    for (i = 0; i < 6; ++i) {
        if (GSflagGet(table[i].high)) {
            for (j = 0; j < 6; ++j) {
                if (used[j] == 0) {
                    Pokemon* pokemon = (Pokemon*)heroGetStatus(hero, 3, j);
                    if (pokemon != 0 && pokemonCheckValid(pokemon)) {
                        pokemonGetStatus(pokemon, 0, 0x6E, 0);
                        u32 value = pokemonGetStatus(pokemon, 0, 0x6F, 0);
                        if (value == GSflagGet(table[i].low)) break;
                    }
                }
            }
            if (j >= 6) return 1;
            used[j] = 1;
        }
    }
    for (i = 0; i < 6; ++i) {
        if (used[i] == 0) {
            Pokemon* pokemon = (Pokemon*)heroGetStatus(hero, 3, i);
            if (pokemon != 0 && pokemonCheckValid(pokemon)) return 1;
        }
    }
    return 0;
}

void scriptStoreTemochiPokemon(u32 hero) {
    TemochiFlag table[6];
    table[0].low = 0x908;
    table[1].low = 0x909;
    table[2].low = 0x90A;
    table[3].low = 0x90B;
    table[4].low = 0x90C;
    table[5].low = 0x90D;
    table[0].high = 0x90E;
    table[1].high = 0x90F;
    table[2].high = 0x910;
    table[3].high = 0x911;
    table[4].high = 0x912;
    table[5].high = 0x913;
    s32 i;
    for (i = 0; i < 6; ++i) {
        Pokemon* pokemon = (Pokemon*)heroGetStatus(hero, 3, i);
        if (pokemon != 0 && pokemonCheckValid(pokemon)) {
            u16 high = pokemonGetStatus(pokemon, 0, 0x6E, 0);
            u32 low = pokemonGetStatus(pokemon, 0, 0x6F, 0);
            GSflagSet(table[i].high, high);
            GSflagSet(table[i].low, low);
        }
    }
}

u16 scriptGetEarthRibbon() {
    u32 hero;
    Pokemon* pokemon;
    u16 i;
    u32 count = 0;
    hero = savedataGetStatus(0, 2);
    for (i = 0; i < 6; ++i) {
        pokemon = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(pokemon)) {
            exribbonSetEarthRibbon(pokemon);
            ++count;
        }
    }
    return count;
}

s16 scriptCatchPokemon(u8 kind) {
    Hero* hero = (Hero*)savedataGetStatus(0, 2);
    switch (kind) {
    case 1: return heroPokemonGetBlacky(hero, 0x259);
    case 2: return heroPokemonGetEifie(hero, 0x259);
    case 3: return heroPokemonGetPrasle(hero, 0x259);
    case 4: return heroPokemonGetHouou(hero, 0xFF);
    case 5: return heroPokemonGetPikachu(hero, 0xFF);
    case 6: return heroPokemonGetCelebi(hero, 0xFF);
    }
    static u16 rnd_status_id[6] = {0x93, 0x94, 0x95, 0x96, 0x97, 0x98};
    u16 name[32];
    HeroPokemonGetParam param;
    s16 slot;
    memset(&param, 0, sizeof(HeroPokemonGetParam));
    param.pokemonDataID = 0;
    param.shadowPokemonDataID = 0;
    param.catchLevel = 5;
    param.friendLevel = 0x46;
    param.move1 = 1;
    param.trainerSexID = heroBiosGetSexDataId(hero);
    param.trainerRnd = heroBiosGetRnd(hero);
    param.trainerNamePtr = heroBiosGetNamePtr(hero);
    param.catchFloorID = floorGetCurrent();
    param.exp = 0;
    switch (kind) {
    case 7:
        param.pokemonDataID = 0xAF;
        param.shadowPokemonDataID = 0x51;
        param.catchLevel = 0x19;
        param.friendLevel = 0;
        param.move1 = 0x10A;
        param.move2 = 0xA1;
        param.move3 = 0xF6;
        param.move4 = 0x10E;
        break;
    case 8:
        param.pokemonDataID = 0xEF;
        param.catchLevel = 0x14;
        param.trainerSexID = 0;
        param.trainerRnd = 0x10000 - 0x5E48;
        param.trainerNamePtr = GSmsgGetGSchar(0x1828);
        param.move1 = 8;
        param.move2 = 7;
        param.move3 = 9;
        param.move4 = 0xEE;
        switch (pokecoloGetLanguage()) {
        case 2: GScharMakeFromSJIS(name, "ZAPRONG"); break;
        case 3: GScharMakeFromSJIS(name, "ZAPRONG"); break;
        case 4: GScharMakeFromSJIS(name, "ZAPRONG"); break;
        case 5: GScharMakeFromSJIS(name, "ZAPRONG"); break;
        case 6: GScharMakeFromSJIS(name, "ZAPRONG"); break;
        default: GScharMakeFromSJIS(name, "ZAPRONG"); break;
        }
        param.nicknamePtr = name;
        break;
    case 9:
        param.pokemonDataID = 0x164;
        param.catchLevel = 0x14;
        param.trainerSexID = 0;
        param.trainerRnd = 0x10000 - 0x6EE3;
        param.trainerNamePtr = GSmsgGetGSchar(0x17B9);
        param.move1 = 0xDF;
        param.move2 = 0x5D;
        param.move3 = 0xF7;
        param.move4 = 0xC5;
        break;
    case 10:
        param.pokemonDataID = 0xD5;
        param.catchLevel = 0x14;
        param.trainerSexID = 0;
        param.trainerRnd = 0x10000 - 0x6EE3;
        param.trainerNamePtr = GSmsgGetGSchar(0x17B9);
        param.move1 = 0x5C;
        param.move2 = 0xA4;
        param.move3 = 0xBC;
        param.move4 = 0xE3;
        break;
    case 11:
        param.pokemonDataID = 0xF6;
        param.catchLevel = 0x14;
        param.trainerSexID = 0;
        param.trainerRnd = 0x10000 - 0x6EE3;
        param.trainerNamePtr = GSmsgGetGSchar(0x17B9);
        param.move1 = 0xC9;
        param.move2 = 0x15D;
        param.move3 = 0x2C;
        param.move4 = 0xC8;
        break;
    case 12:
        param.pokemonDataID = 0x98;
        param.move1 = 0xF6;
        param.move2 = 0x21;
        param.move3 = 0x2D;
        param.move4 = 0x152;
        break;
    case 13:
        param.pokemonDataID = 0x9B;
        param.move1 = 0xB3;
        param.move2 = 0x21;
        param.move3 = 0x2B;
        param.move4 = 0x133;
        break;
    case 14:
        param.pokemonDataID = 0x9E;
        param.move1 = 0xF2;
        param.move2 = 0xA;
        param.move3 = 0x2B;
        param.move4 = 0x134;
        break;
    }
    void* growData = pokemonGrowDataBiosGetPtr(pokemonDB_GetGrowDataId(param.pokemonDataID));
    if (growData == 0) return 0;
    param.exp = pokemonGrowDataBiosGetExp(growData, param.catchLevel);
    if (param.pokemonDataID != 0) {
        param.trainerRnd = (param.trainerRnd & 0xFFFF) | (hero->getHeroRnd() & 0xFFFF0000);
        slot = hero->pokemonGet(&param, true);
        if (param.shadowPokemonDataID != 0) {
            bool created;
            Pokemon* pokemon = hero->getPokemon(slot, created);
            DarkPokemon* dark = pokemon->getDarkPokemon();
            if (dark != 0) {
                dark->setCatchBallID(4);
                dark->setCatchFloorId(param.catchFloorID);
                dark->setUpdate(true);
                u8 count = hero->getMeetDarkPokemonCount();
                hero->setMeetDarkPokemonCount(count + 1);
                dark->setSnatchIndex(count);
                dark->setRnd(pokemon->getRnd());
                s32 i;
                for (i = 0; i < 6; ++i) {
                    darkPokemonBiosSetStatusRnd(param.shadowPokemonDataID, i, pokemonGetStatus(pokemon, 0, rnd_status_id[i], 0));
                }
            }
        }
        return slot;
    }
    return -2;
}

void scriptPlayPokemonNakigoe() {
    etctoolSetPokemonNakigoe();
}

u32 scriptGetPokemonNickName(s32 index) {
    if (index >= 6) return 0;
    Pokemon* pokemon = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), (u16)index);
    if (pokemon == 0) return 0;
    return pokemonGetStatus(pokemon, 0, 0x77, 0);
}

u16 scriptGetDarkPointZeroPokemonNum() {
    u32 hero;
    Pokemon* pokemon;
    u16 i;
    u32 count = 0;
    hero = savedataGetStatus(0, 2);
    for (i = 0; i < 6; ++i) {
        pokemon = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(pokemon) && pokemonBiosGetDarkFlag(pokemon) && pokemonGetDp(pokemon) == 0.0f) ++count;
    }
    return count;
}

u16 scriptGetDarkPokemonNum() {
    u32 hero;
    Pokemon* pokemon;
    u16 i;
    u32 count = 0;
    hero = savedataGetStatus(0, 2);
    for (i = 0; i < 6; ++i) {
        pokemon = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(pokemon) && pokemonBiosGetDarkFlag(pokemon)) ++count;
    }
    return count;
}

u16 scriptGetPokemonNum() {
    u32 hero;
    u16 i;
    u16 count = 0;
    hero = savedataGetStatus(0, 2);
    for (i = 0; i < 6; ++i) {
        if (pokemonCheckValid(heroBiosGetPokemonPtr(hero, i))) ++count;
    }
    return (u32)count;
}

s32 scriptFloorCharSetPos(f32 x, f32 y, f32 z) {
    GSvec pos;
    pos.param1 = x;
    pos.param2 = y;
    pos.param3 = z;
    floorCharacterBiosSetPos(floorCharacterBiosGetCurrentPtr(), &pos);
    return 1;
}

s32 scriptFloorCharSetDisp(u32 id, s32 disp) {
    floorCharacterBiosSetVisibility(floorCharacterBiosGetCurrentPtr(), disp != 0);
    return 1;
}

u8 scriptIsTrigerPush() {
    u8 pushed = 0;
    if (GSinputButtonsPressed(1) & 0x1F70) pushed = 1;
    return pushed;
}

u8 scriptIsMoveButtonPush();

u8 scriptIsButtonPush() {
    u8 pushed = scriptIsMoveButtonPush();
    if (GSinputButtonsPressed(1) & 0x1F70) pushed = 1;
    return pushed;
}

#define ABS_S8(x) ((x) > 0 ? (x) : -(x))
u8 scriptIsMoveButtonPush() {
    u8 pushed = 0;
    if (GSinputButtonsPressed(1) & 0xF) pushed = 1;
    if (ABS_S8(GSinputGetLeftStickXData(1, 0)) > 2) pushed = 1;
    if (ABS_S8(GSinputGetLeftStickYData(1, 0)) > 2) pushed = 1;
    return pushed;
}
}
