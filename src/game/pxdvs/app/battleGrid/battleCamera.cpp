#include <game/pxdvs/app/battleGrid/battleCameraPrivate.hpp>
#include <game/maximum/GSAPI/baselib/math_support.h>

extern GSvec zeroVector;
extern GSvec unitScaleVector;

WazaSequence *gActiveWazaSequenceCamera;
static f32 gLoopCameraWaitTime = 3.0f;
static s32 gLastSelectedIndex = -1;
static u8 gBattleGridSimpleCamera;
static u8 g_mode;
static u8 g_enable_battle_camera;

static inline ModelSequence *asModel(NullSequence *sequence) {
    if (sequence->type == 1) return static_cast<ModelSequence *>(sequence);
    return 0;
}

static void _battleCameraStartRandom(ModelSequence *sequence);
static void _battleCameraUpdateWaza();

// Clears the offsets left behind by the previous shot and fixes up the camera mode.
static inline void battleCameraResetOffsets() {
    battleGridResetModelVisibilityFlags();
    cameraMoveStop();
    cameraSetOffsetPosition(&zeroVector);
    cameraSetOffsetRotation(&zeroVector);
    cameraSetOffsetScale(&unitScaleVector);
    cameraSetMirrorFlag(0);
}

extern "C" {

void battleCameraDisable() {
    g_enable_battle_camera = 0;
}

u8 battleCameraIsSimple() {
    return gBattleGridSimpleCamera;
}

void battleCameraDoFull() {
    gBattleGridSimpleCamera = 0;
}

void battleCameraDoSimple() {
    gBattleGridSimpleCamera = 1;
}

void battleCameraInit(u32 enable) {
    u8 enabled = 0;
    g_mode = 0;
    gActiveWazaSequenceCamera = 0;
    gLastSelectedIndex = -1;
    gLoopCameraWaitTime = 3.0f;
    gBattleGridSimpleCamera = 0;
    if (enable != 0 && floorDataBiosGetFloorKind() == 2) {
        enabled = 1;
    }
    g_enable_battle_camera = enabled;
}

void battleCameraUpdate() {
    switch (g_mode) {
    case 2:
        _battleCameraUpdateWaza();
        break;
    case 1:
        if (cameraMoveEndCheckSpecial(0) == 0) {
            battleCameraResetOffsets();
            switch (g_mode) {
            case 2:
                if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) != 0 && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) != 0) {
                    cameraStopAnime();
                }
                gActiveWazaSequenceCamera = 0;
                g_mode = 0;
                break;
            case 1:
                g_mode = 3;
                break;
            case 3:
                g_mode = 0;
                break;
            }
        }
        break;
    case 3:
        battleCameraStartRandom(gBattleGridSimpleCamera);
        break;
    }
}

void battleCameraStop() {
    battleCameraResetOffsets();
    switch (g_mode) {
    case 2:
        if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) != 0 && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) != 0) {
            cameraStopAnime();
        }
        gActiveWazaSequenceCamera = 0;
        g_mode = 0;
        break;
    case 1:
        g_mode = 3;
        break;
    case 3:
        g_mode = 0;
        break;
    }
}

void battleCameraStartRandom(u8 simple) {
    s32 i;
    s32 j;
    s32 pick;
    s32 seen;
    BattleCameraGridEntry *entry;
    int count = gBattleGrid.pokemonCount;
    if (g_enable_battle_camera != 0 && g_mode != 1) {
        if (count == 0) {
            _battleCameraStartRandom(0);
            return;
        }
        if (count == 1) {
            pick = 0;
        } else {
            pick = (u16)HSD_Rand() % count;
            while (pick == gLastSelectedIndex) {
                pick = (u16)HSD_Rand() % count;
            }
        }
        gLastSelectedIndex = pick;
        seen = 0;
        entry = gBattleGrid.entry;
        for (i = 0; i < 4; i++, entry++) {
            if (entry->trainer != 0) {
                for (j = 0; j < 2; j++) {
                    if (entry->pokemon[j] != 0) {
                        if (seen == pick) {
                            _battleCameraStartRandom(entry->pokemon[j]);
                            gLoopCameraWaitTime = 3.0f;
                            return;
                        }
                        seen++;
                    }
                }
            }
        }
    }
}

}  // extern "C"

static void _battleCameraStartRandom(ModelSequence *sequence) {
    static u8 old_pos_pattern[2] = {12, 12};
    f32 fovLowB, fovHighB;
    f32 fovLowA, fovHighA;
    wazaSequenceCameraParams params;
    GSvec cameraPosition;
    GSvec posA;
    GSvec posB;
    GSvec target;
    u8 nonTrainerActive;
    u8 *history;
    u32 pattern;
    u8 retry;
    bool isTrainer;
    s32 fovMask;
    isTrainer = fightFloor_GetTrainer(0) != 0;
    nonTrainerActive = fightPokemonGetNonTrainerPokemonIsActiveFlag();
    fovMask = 0;
    if (g_enable_battle_camera == 0) return;
    if (!(wazaSequenceSysIsValidSequence(sequence) && sequence->visible != 0)) {
        sequence = 0;
    }
    battleCameraResetOffsets();
    switch (g_mode) {
    case 1:
    case 3:
        break;
    case 2:
        if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) != 0 && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) != 0) {
            cameraStopAnime();
        }
        gActiveWazaSequenceCamera = 0;
        break;
    }
    g_mode = 1;
    retry = 1;
    history = old_pos_pattern;
    while (retry) {
        bool useTrainerSet = (sequence == 0 || sequence->isPokemon == 0);
        pattern = 12;
        if (useTrainerSet) pattern = 10;
        pattern = (u8)((u16)HSD_Rand() % (s32)pattern);
        if (pattern != old_pos_pattern[0] && pattern != history[1]) {
            retry = 0;
        }
        if (isTrainer == 0 && pattern == 3) {
            retry = 1;
        }
    }
    history[1] = old_pos_pattern[0];
    old_pos_pattern[0] = pattern;
    if (sequence != 0 && sequence->isPokemon == 0) {
        switch (battleGridGetNumPokemonsForTrainer(sequence)) {
        case 1:
            fovMask = 7;
            break;
        case 2:
            fovMask = 1;
            break;
        }
    }
    if (sequence != 0) {
        _wazaSequenceCameraCalculateParams(sequence, fovMask, &params);
    }
    f32 distanceFar;
    f32 distanceNear;
    f32 height;
    f32 rotationStart;
    f32 rotationEnd;
    switch (pattern) {
    case 0: {
        target.param1 = 0.0f;
        target.param2 = 0.0f;
        target.param3 = 0.0f;
        posA.param1 = -20.0f;
        posA.param2 = 27.5f;
        posA.param3 = 110.0f;
        posB.param1 = 20.0f;
        posB.param2 = 27.5f;
        posB.param3 = 110.0f;
        f32 ratio = battleGridGetUnscaledDistance(1);
        ratio = battleGridGetDistance(1) / ratio;
        PSVECScale(&posA, &posA, ratio);
        PSVECScale(&posB, &posB, ratio);
        if (HSD_Randf() < 0.5f) {
            cameraSetType(2);
            cameraSetPosition(&posA);
            cameraMovePosition(2, &posB, 4.0f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        } else {
            cameraSetType(2);
            cameraSetPosition(&posB);
            cameraMovePosition(2, &posA, 4.0f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        }
        return;
    }
    case 1: {
        target.param1 = 0.0f;
        target.param2 = 0.0f;
        target.param3 = 0.0f;
        posA.param1 = 110.0f;
        posA.param2 = 27.5f;
        posA.param3 = 0.0f;
        posB.param1 = 110.0f;
        posB.param2 = 27.5f;
        posB.param3 = 20.0f;
        f32 ratio = battleGridGetUnscaledDistance(1);
        ratio = battleGridGetDistance(1) / ratio;
        PSVECScale(&posA, &posA, ratio);
        PSVECScale(&posB, &posB, ratio);
        if (HSD_Randf() < 0.5f) {
            cameraSetType(2);
            cameraSetPosition(&posA);
            cameraMovePosition(2, &posB, 2.5f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        } else {
            cameraSetType(2);
            cameraSetPosition(&posB);
            cameraMovePosition(2, &posA, 2.5f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        }
        return;
    }
    case 2: {
        target.param1 = 0.0f;
        target.param2 = 0.0f;
        target.param3 = 0.0f;
        posA.param1 = -110.0f;
        posA.param2 = 27.5f;
        posA.param3 = 20.0f;
        posB.param1 = -110.0f;
        posB.param2 = 27.5f;
        posB.param3 = 0.0f;
        f32 ratio = battleGridGetUnscaledDistance(1);
        ratio = battleGridGetDistance(1) / ratio;
        PSVECScale(&posA, &posA, ratio);
        PSVECScale(&posB, &posB, ratio);
        if (HSD_Randf() < 0.5f) {
            cameraSetType(2);
            cameraSetPosition(&posA);
            cameraMovePosition(2, &posB, 2.5f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        } else {
            cameraSetType(2);
            cameraSetPosition(&posB);
            cameraMovePosition(2, &posA, 2.5f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        }
        return;
    }
    case 3: {
        target.param1 = 0.0f;
        target.param2 = 0.0f;
        target.param3 = 0.0f;
        posA.param1 = -65.0f;
        posA.param2 = 27.5f;
        posA.param3 = 100.0f;
        posB.param1 = -100.0f;
        posB.param2 = 27.5f;
        posB.param3 = 65.0f;
        f32 ratio = battleGridGetUnscaledDistance(1);
        ratio = battleGridGetDistance(1) / ratio;
        PSVECScale(&posA, &posA, ratio);
        PSVECScale(&posB, &posB, ratio);
        if (HSD_Randf() < 0.5f) {
            cameraSetType(2);
            cameraSetPosition(&posA);
            cameraMovePosition(2, &posB, 4.0f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        } else {
            cameraSetType(2);
            cameraSetPosition(&posB);
            cameraMovePosition(2, &posA, 4.0f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        }
        return;
    }
    case 4: {
        target.param1 = 0.0f;
        target.param2 = 0.0f;
        target.param3 = 0.0f;
        posA.param1 = 100.0f;
        posA.param2 = 27.5f;
        posA.param3 = 65.0f;
        posB.param1 = 65.0f;
        posB.param2 = 27.5f;
        posB.param3 = 100.0f;
        f32 ratio = battleGridGetUnscaledDistance(1);
        ratio = battleGridGetDistance(1) / ratio;
        PSVECScale(&posA, &posA, ratio);
        PSVECScale(&posB, &posB, ratio);
        if (HSD_Randf() < 0.5f) {
            cameraSetType(2);
            cameraSetPosition(&posA);
            cameraMovePosition(2, &posB, 4.0f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        } else {
            cameraSetType(2);
            cameraSetPosition(&posB);
            cameraMovePosition(2, &posA, 4.0f);
            cameraSetFov(60.0f);
            cameraSetTargetPos(&target);
            cameraSetTargetOfs(&zeroVector);
        }
        return;
    }
    case 5: {
        f32 side;
        if ((isTrainer != 0 || nonTrainerActive != 0) && HSD_Randf() < 0.5f) {
            side = -1.0f;
        } else {
            side = 1.0f;
        }
        f32 distance = battleGridGetDistance(1);
        target.param1 = -distance * side;
        target.param2 = 4.0f;
        target.param3 = 0.0f;
        posA.param1 = distance * side;
        posA.param2 = 4.0f;
        posA.param3 = distance;
        posB.param1 = 0.2f * distance * side;
        posB.param2 = 4.0f;
        posB.param3 = distance;
        f32 extra = HSD_Randf();
        cameraSetType(2);
        cameraSetPosition(&posA);
        cameraMovePosition(2, &posB, 3.0f + extra);
        cameraSetFov(40.0f);
        cameraSetTargetPos(&target);
        cameraSetTargetOfs(&zeroVector);
        return;
    }
    case 6: {
        f32 side;
        if (HSD_Randf() < 0.5f) {
            side = -1.0f;
        } else {
            side = 1.0f;
        }
        f32 near = battleGridGetDistance(1);
        f32 far = battleGridGetDistance(0);
        target.param1 = -far * side;
        target.param2 = 0.0f;
        target.param3 = 0.0f;
        posA.param1 = side * (near + far);
        posA.param2 = 4.0f;
        posA.param3 = 0.7f * near;
        posB.param1 = side * (near + far);
        posB.param2 = 4.0f;
        posB.param3 = 0.7f * -near;
        f32 extra = HSD_Randf();
        cameraSetType(2);
        cameraSetPosition(&posA);
        cameraMovePosition(2, &posB, 3.0f + extra);
        cameraSetFov(30.0f);
        cameraSetTargetPos(&target);
        cameraSetTargetOfs(&zeroVector);
        return;
    }
    case 7: {
        f32 side;
        if ((isTrainer != 0 || nonTrainerActive != 0) && HSD_Randf() < 0.5f) {
            side = -1.0f;
        } else {
            side = 1.0f;
        }
        f32 near = battleGridGetDistance(1);
        f32 far = battleGridGetDistance(0);
        target.param1 = -far * side;
        target.param2 = 4.0f;
        target.param3 = 0.0f;
        posA.param1 = 0.0f;
        posA.param2 = 4.0f;
        posA.param3 = 0.7f * near;
        posB.param1 = 0.0f;
        posB.param2 = 4.0f;
        posB.param3 = 0.7f * -near;
        f32 extra = HSD_Randf();
        cameraSetType(2);
        cameraSetPosition(&posA);
        cameraMovePosition(2, &posB, 3.0f + extra);
        cameraSetFov(60.0f);
        cameraSetTargetPos(&target);
        cameraSetTargetOfs(&zeroVector);
        return;
    }
    case 8: {
        f32 heightA = 2.0f * HSD_Randf() + 4.0f;
        f32 heightB = 2.0f * HSD_Randf() + 4.0f;
        f32 flip = HSD_Randf();
        if (flip < 0.5f) heightA = heightA * -1.0f;
        if (!(flip < 0.5f)) heightB = heightB * -1.0f;
        f32 side;
        if (HSD_Randf() < 0.5f) {
            side = -1.0f;
        } else {
            side = 1.0f;
        }
        f32 near = battleGridGetDistance(1);
        f32 far = battleGridGetDistance(0);
        target.param1 = -near * side;
        target.param2 = 0.0f;
        target.param3 = 0.0f;
        posA.param1 = side * (near + far);
        posA.param2 = 4.0f;
        posA.param3 = heightA;
        posB.param1 = side * (near + far);
        posB.param2 = 20.0f;
        posB.param3 = heightB;
        f32 extra = HSD_Randf();
        cameraSetType(2);
        cameraSetPosition(&posA);
        cameraMovePosition(2, &posB, 3.0f + extra);
        cameraSetFov(20.0f);
        cameraSetTargetPos(&target);
        cameraSetTargetOfs(&zeroVector);
        return;
    }
    case 9: {
        f32 side;
        if (HSD_Randf() < 0.5f) {
            side = -1.0f;
        } else {
            side = 1.0f;
        }
        f32 near = battleGridGetDistance(1);
        f32 far = battleGridGetDistance(0);
        target.param1 = -far * side;
        target.param2 = 4.0f;
        target.param3 = 0.0f;
        posA.param1 = side * (near + far);
        posA.param2 = 2.0f;
        posA.param3 = 0.25f * near;
        posB.param1 = side * (near + far);
        posB.param2 = 2.0f;
        posB.param3 = 0.25f * -near;
        f32 extra = HSD_Randf();
        cameraSetType(2);
        cameraSetPosition(&posA);
        cameraMovePosition(2, &posB, 3.0f + extra);
        cameraSetFov(15.0f);
        cameraSetTargetPos(&target);
        cameraSetTargetOfs(&zeroVector);
        return;
    }
    case 10:
        distanceFar = (params.distanceMax - params.distanceMin) * HSD_Randf() + params.distanceMin;
        distanceNear = (params.distanceMax - params.distanceMin) * HSD_Randf() + params.distanceMin;
        if (distanceFar < distanceNear) {
            f32 swap = distanceNear;
            distanceNear = distanceFar;
            distanceFar = swap;
        }
        height = (params.heightMax - params.heightMin) * HSD_Randf() + params.heightMin;
        if (sequence->flipped != 0) {
            rotationEnd = (params.baseRotation - params.rotationA) - (params.rotationB - params.rotationA) * HSD_Randf();
            rotationStart = rotationEnd;
        } else {
            rotationEnd = (params.rotationB - params.rotationA) * HSD_Randf() + (params.baseRotation + params.rotationA);
            rotationStart = rotationEnd;
        }
        break;
    case 11:
        distanceNear = (params.distanceMax - params.distanceMin) * HSD_Randf() + params.distanceMin;
        distanceFar = distanceNear;
        height = (params.heightMax - params.heightMin) * HSD_Randf() + params.heightMin;
        if (sequence->flipped != 0) {
            rotationStart = (params.baseRotation - params.rotationA) - (params.rotationB - params.rotationA) * HSD_Randf();
            rotationEnd = (params.baseRotation - params.rotationA) - (params.rotationB - params.rotationA) * HSD_Randf();
        } else {
            rotationStart = (params.rotationB - params.rotationA) * HSD_Randf() + (params.baseRotation + params.rotationA);
            rotationEnd = (params.rotationB - params.rotationA) * HSD_Randf() + (params.baseRotation + params.rotationA);
        }
        break;
    default:
        distanceNear = (params.distanceMax - params.distanceMin) * HSD_Randf() + params.distanceMin;
        distanceFar = distanceNear;
        height = (params.heightMax - params.heightMin) * HSD_Randf() + params.heightMin;
        if (sequence->flipped != 0) {
            rotationEnd = (params.baseRotation - params.rotationA) - (params.rotationB - params.rotationA) * HSD_Randf();
            rotationStart = rotationEnd;
        } else {
            rotationEnd = (params.rotationB - params.rotationA) * HSD_Randf() + (params.baseRotation + params.rotationA);
            rotationStart = rotationEnd;
        }
        break;
    }
    f32 heightSquared = height * height;
    _wazaSequenceCameraGetFOVRange(&params, &fovLowA, &fovHighA, hsdSqrt(distanceFar * distanceFar + heightSquared));
    _wazaSequenceCameraGetFOVRange(&params, &fovLowB, &fovHighB, hsdSqrt(distanceNear * distanceNear + heightSquared));
    f32 fovStart;
    f32 fovEnd;
    switch ((u8)(HSD_Rand() % 3)) {
    case 0:
        fovStart = (fovHighA - fovLowA) * HSD_Randf() + fovLowA;
        fovEnd = (fovHighB - fovLowB) * HSD_Randf() + fovLowB;
        if (fovStart < fovEnd) {
            f32 swap = fovEnd;
            fovEnd = fovStart;
            fovStart = swap;
        }
        break;
    case 1:
        fovStart = (fovHighA - fovLowA) * HSD_Randf() + fovLowA;
        fovEnd = (fovHighB - fovLowB) * HSD_Randf() + fovLowB;
        if (fovStart > fovEnd) {
            f32 swap = fovEnd;
            fovEnd = fovStart;
            fovStart = swap;
        }
        break;
    default:
        fovEnd = (fovHighA - fovLowA) * HSD_Randf() + fovLowA;
        fovStart = fovEnd;
        break;
    }
    f32 duration = 3.0f + HSD_Randf();
    cameraMoveStop();
    cameraSetType(7);
    fn_80196A14(1);
    u16 joint = 0;
    _GSmodel *model = sequence->model;
    u32 targetId = sequence->field3C;
    if (model != 0) {
        joint = GSmodelCenterNull(model);
    }
    cameraSetTargetExt(20000, targetId, joint);
    cameraRefreshTargetPos();
    cameraSetTargetExt(0, 0, -1);
    cameraSetDistance(distanceFar);
    cameraSetHeight(height);
    cameraSetRotY(rotationStart);
    cameraSetFov(fovStart);
    cameraUpdate();
    cameraGetPosition(&cameraPosition);
    cameraGetTargetPos(&target);
    PSVECSubtract(&cameraPosition, &target, &cameraPosition);
    cameraPosition.param2 = 0.0f;
    PSVECScale(&cameraPosition, &cameraPosition, distanceNear / distanceFar);
    cameraPosition.param2 = height;
    PSVECAdd(&cameraPosition, &target, &cameraPosition);
    cameraMovePosition(7, &cameraPosition, duration);
    cameraMoveRotationXYZ(7, 0.0f, rotationEnd, 0.0f, duration);
    cameraMoveFov(7, fovEnd, duration);
    cameraMovePositionAcc(duration * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
    cameraMoveRotationAcc(duration * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
    cameraMoveFovAcc(duration * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
}

extern "C" void battleCameraStartWaza(WazaSequence *waza) {
    ModelSequence *sequence;
    _GSmodel *model;
    f32 speed = 1.0f;
    bool flip = false;
    s32 fovMask = 0;
    wazaSequenceCameraParams params;
    GSvec rootPosition;
    GSvec offsetPosition;
    GSvec offsetRotation;
    GSvec offsetScale;
    GSvec boundMiddle;
    GSvec boundMin;
    GSvec boundMax;
    GSvec probe;
    GSvec probeTrainer;
    GSvec boundSum;
    battleCameraResetOffsets();
    switch (g_mode) {
    case 2:
        if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) != 0 && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) != 0) {
            cameraStopAnime();
        }
        gActiveWazaSequenceCamera = 0;
        g_mode = 0;
        break;
    case 1:
        g_mode = 3;
        break;
    case 3:
        g_mode = 0;
        break;
    }
    if (wazaSequenceSysIsValidWaza(waza) != 0) {
    sequence = asModel(waza->owner);
    if (sequence != 0 && (model = sequence->model) != 0) {
    if (GSmodelIsRootNullAdded(model) != 0) {
        GSmodelGetRootPosition(model, &rootPosition);
    } else {
        rootPosition.param1 = 0.0f;
        rootPosition.param2 = 0.0f;
        rootPosition.param3 = 0.0f;
    }
    gActiveWazaSequenceCamera = waza;
    g_mode = 2;
    if (sequence->flipped != 0 && !(wazaSequenceFlags(waza) & 0x80)) {
        flip = true;
    }
    if (wazaSequenceCameraAnim(waza) != 0 && GSresGetResource(20000, wazaSequenceCameraAnim(waza)) != 0) {
        s32 mirror = 0;
        if (flip != 0) mirror = 4;
        cameraPlayOffsetAnime(20000, wazaSequenceCameraAnim(waza), 0, 0);
        u32 flags = wazaSequenceFlags(waza);
        if (flags & 4) {
            offsetPosition.param1 = 0.0f;
            offsetPosition.param2 = 0.0f;
            offsetPosition.param3 = 0.0f;
            offsetRotation.param1 = 0.0f;
            offsetRotation.param2 = 0.0f;
            offsetRotation.param3 = 0.0f;
            if (sequence->flipped != 0 && (flags & 0x02000000)) {
                offsetRotation.param2 = 3.1415927f;
            }
            if (wazaSequenceFlags(waza) & 0x800000) {
                battleGridGetNormalisedScale(&offsetScale);
                if (wazaSequenceFlags(waza) & 0x01000000) {
                    offsetScale.param2 = 1.0f;
                }
            } else {
                offsetScale.param1 = 1.0f;
                offsetScale.param2 = 1.0f;
                offsetScale.param3 = 1.0f;
            }
        } else {
            sequence->GetPosition(&offsetPosition);
            sequence->GetRotation(&offsetRotation);
            if (wazaSequenceFlags(waza) & 0x20000000) {
                offsetScale.param3 = 1.0f;
                offsetScale.param2 = 1.0f;
                offsetScale.param1 = 1.0f;
            } else {
                f32 scale = sequence->GetModelScale(true);
                offsetScale.param3 = scale;
                offsetScale.param2 = scale;
                offsetScale.param1 = scale;
            }
            if (wazaSequenceFlags(waza) & 0x4000) {
                GSboundGetMinMax(GSmodelGetBound(model), &boundMin, &boundMax, 1, 1, 0, 0);
                PSVECAdd(&boundMin, &boundMax, &boundSum);
                boundMiddle.param1 = boundSum.param1;
                boundMiddle.param2 = boundSum.param2;
                boundMiddle.param3 = boundSum.param3;
                PSVECScale(&boundMiddle, &boundMiddle, 0.5f);
                PSVECAdd(&offsetPosition, &boundMiddle, &offsetPosition);
            }
            if (waza->category == 2 && (sequence->flags & 1) == 1) {
                offsetPosition.param2 += rootPosition.param2;
            }
        }
        cameraSetMirrorFlag(mirror);
        cameraMoveStop();
        cameraSetOffsetPosition(&offsetPosition);
        cameraSetOffsetRotation(&offsetRotation);
        cameraSetOffsetScale(&offsetScale);
        cameraUpdate();
        return;
    }
    if (sequence->isPokemon != 0) {
        u32 flags = wazaSequenceFlags(waza);
        if (flags & 0x200000) {
            fovMask = 3;
        } else if (flags & 0x200) {
            fovMask = 4;
        } else if (flags & 0x400000) {
            sequence->GetPosition(&probe);
            if (probe.param3 < 0.0f) {
                fovMask = 4;
            } else {
                fovMask = 5;
            }
        }
    } else {
        switch (battleGridGetNumPokemonsForTrainer(sequence)) {
        case 1:
            if (wazaSequenceFlags(waza) & 0x400000) {
                fovMask = 7;
            } else {
                fovMask = 6;
            }
            break;
        case 2:
            if (wazaSequenceFlags(waza) & 0x200000) {
                fovMask = 1;
            } else {
                fovMask = 2;
            }
        default: {
            u32 flags = wazaSequenceFlags(waza);
            if (flags & 0x200000) {
                fovMask = 3;
            } else if (flags & 0x200) {
                fovMask = 4;
            } else if (flags & 0x400000) {
                sequence->GetPosition(&probeTrainer);
                if (probeTrainer.param3 < 0.0f) {
                    fovMask = 4;
                } else {
                    fovMask = 5;
                }
            }
            break;
        }
        }
        speed = 2.0f;
    }
    u32 flagsAfter = wazaSequenceFlags(waza);
    if (flagsAfter & 0x400) {
        fovMask |= 0x80;
    } else if (flagsAfter & 0x800) {
        fovMask |= 0x100;
    } else if (flagsAfter & 0x1000) {
        fovMask |= 0x200;
    }
    cameraMoveStop();
    cameraSetType(7);
    u32 targetId = sequence->field3C;
    s32 joint;
    WazaSequence *active = gActiveWazaSequenceCamera;
    if (sequence->model == 0) {
        joint = 0;
    } else if (active != 0) {
        ModelRecord *record = &sequence->records[sequence->wazaIndex];
        if ((((TemplateExpFileHeader *)record)->flags & 0x20) || wazaSequenceJointIndex(active) == 0x10) {
            joint = GSmodelCenterNull(sequence->model);
        } else {
            joint = record->joints[wazaSequenceJointIndex(active)];
        }
    } else {
        joint = GSmodelCenterNull(sequence->model);
    }
    cameraSetTargetExt(20000, targetId, joint);
    cameraRefreshTargetPos();
    cameraSetTargetExt(0, 0, -1);
    _wazaSequenceCameraCalculateParams(sequence, fovMask, &params);
    _wazaSequenceCameraSelectMotion(sequence, waza, &params);
    _wazaSequenceCameraDoPosition(sequence, &params, speed, flip);
    _wazaSequenceCameraDoFOV(sequence, &params, fovMask, speed);
    cameraUpdate();
    }
    }
}

static void _battleCameraUpdateWaza() {
    CameraFovKey *key = gFOVlist;
    if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) != 0 && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) == 0) {
        ModelSequence *sequence = asModel(gActiveWazaSequenceCamera->owner);
        u16 frames = (u16)(0.5f + GSgfxVideoGetLastRenderTime());
        _GSmodel *model = sequence->model;
        s32 joint;
        if (model == 0) {
            joint = 0;
        } else if (gActiveWazaSequenceCamera != 0) {
            ModelRecord *record = &sequence->records[sequence->wazaIndex];
            if ((((TemplateExpFileHeader *)record)->flags & 0x20) || wazaSequenceJointIndex(gActiveWazaSequenceCamera) == 0x10) {
                joint = GSmodelCenterNull(model);
            } else {
                joint = record->joints[wazaSequenceJointIndex(gActiveWazaSequenceCamera)];
            }
        } else {
            joint = GSmodelCenterNull(model);
        }
        if (!(wazaSequenceFlags(gActiveWazaSequenceCamera) & 0x40000000)) {
            void *part = GSmodelGetPart(sequence->model, joint);
            if (part != 0) {
                GSvec partPosition;
                GSvec sequencePosition;
                GSpartGetTransform(part, &partPosition, 0, 0);
                sequence->NullSequence::GetPosition(&sequencePosition);
                PSVECSubtract(&partPosition, &sequencePosition, &partPosition);
                cameraMoveTargetOfs(7, &partPosition, 0.25f);
                GSpartFree(part);
            }
        }
        gCurrentFOVTime = gCurrentFOVTime + (f32)frames / (f32)GSgfxVideoGetVsyncRate();
        for (s32 i = 0; i < 2; i++, key++) {
            if (gCurrentFOVTime <= key->startTime) {
                gCurrentFOV = key->startFov;
                break;
            }
            if (gCurrentFOVTime <= key->endTime) {
                gCurrentFOV = GSlerpGetLinearInterpolationFloat(key->startFov, key->endFov, (gCurrentFOVTime - key->startTime) / (key->endTime - key->startTime));
                break;
            }
            gCurrentFOV = key->endFov;
        }
        cameraSetFov(gCurrentFOV);
    }
}
