#include <game/pxdvs/app/battleGrid/wazaSequenceCameraPrivate.hpp>
#include <game/maximum/GSAPI/baselib/math_support.h>

CameraFovKey gFOVlist[2];
f32 gCurrentFOV = 30.0f;
s32 gLastMotionType = 5;
f32 gCurrentFOVTime;

// Size multiplier applied to the shot distance.
static inline f32 cameraSizeScale(s8 size) {
    switch (size) {
    case -2:
    case -1:
        return 0.875f;
    case 1:
        return 1.4f;
    case 2:
        return 1.8f;
    case 3:
        return 3.0f;
    default:
        return 1.0f;
    }
}

void _wazaSequenceCameraDoPosition(ModelSequence *sequence, wazaSequenceCameraParams *params, f32 speed, bool flip) {
    TemplateExpFileHeader *record = (TemplateExpFileHeader *)&sequence->records[sequence->wazaIndex];
    cameraLockYTarget((record->flags >> 4) & 1);
    switch (params->motion) {
    case 0:
        _wazaSequenceCameraDoDollyPosition(record, params, speed, flip);
        break;
    case 1: {
        f32 distance;
        f32 height;
        f32 side;
        f32 duration;
        duration = record->time[record->index] * speed;
        side = 10.0f * HSD_Randf() + 25.0f;
        height = 9.0f * HSD_Randf() + 1.0f;
        distance = 30.0f * HSD_Randf() + 20.0f;
        cameraSetDistance(distance);
        cameraSetHeight(height);
        cameraSetRotY(0.0f);
        cameraUpdate();
        GSvec position;
        cameraGetPosition(&position);
        if (flip) {
            position.param1 = position.param1 + 10.0f;
        } else {
            position.param1 = position.param1 - 10.0f;
        }
        cameraSetPosition(&position);
        if (flip) {
            position.param1 = position.param1 + side;
        } else {
            position.param1 = position.param1 - side;
        }
        cameraMovePosition(7, &position, duration);
        cameraMovePositionAcc(duration * (0.1f / (f32)GSgfxVideoGetVsyncRate()));
        f32 planar = side * side + height * height;
        params->fovDistance[0] = hsdSqrt(planar);
        params->fovDistance[2] = hsdSqrt(distance * distance + planar);
        params->fovDistance[1] = 0.5f * (params->fovDistance[0] + params->fovDistance[2]);
        break;
    }
    case 2: {
        f32 duration = record->time[record->index] * speed;
        f32 distance = (params->distanceMax - params->distanceMin) * HSD_Randf() + params->distanceMin;
        f32 height = (params->heightMax - params->heightMin) * HSD_Randf() + params->heightMin;
        f32 rotationStart;
        f32 rotationEnd;
        if (flip) {
            rotationStart = (params->baseRotation - params->rotationA) - (params->rotationB - params->rotationA) * HSD_Randf();
            rotationEnd = (params->baseRotation - params->rotationA) - (params->rotationB - params->rotationA) * HSD_Randf();
        } else {
            rotationStart = (params->rotationB - params->rotationA) * HSD_Randf() + (params->baseRotation + params->rotationA);
            rotationEnd = (params->rotationB - params->rotationA) * HSD_Randf() + (params->baseRotation + params->rotationA);
        }
        if (rotationStart > rotationEnd) {
            f32 swap = rotationStart;
            rotationStart = rotationEnd;
            rotationEnd = swap;
        }
        cameraSetDistance(1.25f * distance);
        cameraSetHeight(height);
        cameraSetRotY(rotationStart);
        cameraUpdate();
        cameraMoveRotationXYZ(7, 0.0f, rotationEnd, 0.0f, duration);
        cameraMoveRotationAcc(duration * (0.1f / (f32)GSgfxVideoGetVsyncRate()));
        f32 reach = hsdSqrt(distance * distance + height * height);
        params->fovDistance[2] = reach;
        params->fovDistance[1] = reach;
        params->fovDistance[0] = reach;
        break;
    }
    case 3: {
        f32 duration = record->time[record->index] * speed;
        f32 distance = (params->distanceMax - params->distanceMin) * HSD_Randf() + params->distanceMin;
        f32 height = (params->heightMax - params->heightMin) * HSD_Randf() + params->heightMin;
        f32 rotation;
        if (flip) {
            rotation = (params->baseRotation - params->rotationA) - (params->rotationB - params->rotationA) * HSD_Randf();
        } else {
            rotation = (params->rotationB - params->rotationA) * HSD_Randf() + (params->baseRotation + params->rotationA);
        }
        cameraSetDistance(1.25f * distance);
        cameraSetHeight(height);
        cameraSetRotY(rotation);
        cameraUpdate();
        GSvec position;
        cameraGetPosition(&position);
        cameraMovePosition(7, &position, duration);
        f32 reach = hsdSqrt(distance * distance + height * height);
        params->fovDistance[2] = reach;
        params->fovDistance[1] = reach;
        params->fovDistance[0] = reach;
        break;
    }
    case 4: {
        f32 duration = record->time[record->index];
        f32 rotation;
        if (flip) {
            rotation = params->baseRotation - 0.47123894f;
        } else {
            rotation = 0.47123894f + params->baseRotation;
        }
        cameraSetDistance(110.0f);
        cameraSetHeight(25.0f);
        cameraSetRotY(rotation);
        cameraUpdate();
        GSvec position;
        cameraGetPosition(&position);
        cameraMovePosition(7, &position, duration);
        f64 value = 12725.0;
        f64 guess = __frsqrte(value);
        guess = 0.5 * guess * (3.0 - guess * guess * value);
        guess = 0.5 * guess * (3.0 - guess * guess * value);
        guess = 0.5 * guess * (3.0 - guess * guess * value);
        f32 reach = (f32)(value * guess);
        params->fovDistance[2] = reach;
        params->fovDistance[1] = reach;
        params->fovDistance[0] = reach;
        break;
    }
    case 5: {
        f32 duration = record->time[record->index] * speed;
        f32 distance = 50.0f * cameraSizeScale(sequence->modelSize);
        f32 height = (params->heightMax - params->heightMin) * HSD_Randf() + params->heightMin;
        f32 rotation;
        if (flip) {
            rotation = params->baseRotation - 0.7853982f;
        } else {
            rotation = 0.7853982f + params->baseRotation;
        }
        cameraSetDistance(1.25f * distance);
        cameraSetHeight(height);
        cameraSetRotY(rotation);
        cameraUpdate();
        GSvec position;
        cameraGetPosition(&position);
        cameraMovePosition(7, &position, duration);
        f32 reach = hsdSqrt(distance * distance + height * height);
        params->fovDistance[2] = reach;
        params->fovDistance[1] = reach;
        params->fovDistance[0] = reach;
        break;
    }
    }
}

void _wazaSequenceCameraDoDollyPosition(TemplateExpFileHeader *record, wazaSequenceCameraParams *params, f32 speed, bool flip) {
    f32 zoomOutChance = 0.5f;
    f32 zoomInChance = 0.75f;
    f32 duration = record->time[record->index] * speed;
    bool inward;
    if (HSD_Randf() <= 0.7f) {
        zoomOutChance = 0.3f;
        inward = true;
        zoomInChance = 0.65f;
    } else {
        inward = false;
    }
    f32 moveEnd;
    f32 moveStart;
    f32 roll = HSD_Randf();
    if (roll < zoomOutChance) {
        moveEnd = duration;
        moveStart = 0.0f;
    } else if (roll < zoomInChance) {
        moveStart = 0.0f;
        moveEnd = duration * HSD_Randf();
        f32 half = 0.5f * duration;
        if (moveEnd < half) moveEnd = half;
    } else {
        moveStart = duration * HSD_Randf();
        f32 half = 0.5f * duration;
        if (moveStart > half) moveStart = half;
        moveEnd = duration;
    }
    f32 distanceA = (params->distanceMax - params->distanceMin) * HSD_Randf() + params->distanceMin;
    f32 distanceFar = distanceA;
    f32 distanceNear = (params->distanceMax - params->distanceMin) * HSD_Randf() + params->distanceMin;
    f32 height;
    if (inward) {
        if (distanceA < distanceNear) {
            distanceNear = distanceA;
            distanceFar = distanceNear;
        }
        height = (params->heightMax - params->heightMin) * HSD_Randf() + params->heightMin;
    } else {
        if (distanceA > distanceNear) {
            distanceNear = distanceA;
            distanceFar = distanceNear;
        }
        height = (params->heightMax - params->heightMin) * HSD_Randf() + params->heightMin;
    }
    f32 rotation;
    if (flip) {
        rotation = (params->baseRotation - params->rotationA) - (params->rotationB - params->rotationA) * HSD_Randf();
    } else {
        rotation = (params->rotationB - params->rotationA) * HSD_Randf() + (params->baseRotation + params->rotationA);
    }
    cameraSetDistance(1.25f * distanceFar);
    cameraSetHeight(height);
    cameraSetRotY(rotation);
    cameraUpdate();
    GSvec position;
    GSvec target;
    cameraGetPosition(&position);
    cameraGetTargetPos(&target);
    PSVECSubtract(&position, &target, &position);
    position.param2 = 0.0f;
    PSVECScale(&position, &position, distanceNear / distanceFar);
    position.param2 = height;
    PSVECAdd(&position, &target, &position);
    f32 travel = moveEnd - moveStart;
    cameraMovePosition(7, &position, travel);
    cameraMovePositionAcc(travel * (0.1f / (f32)GSgfxVideoGetVsyncRate()));
    f32 heightSquared = height * height;
    params->fovDistance[0] = hsdSqrt(distanceFar * distanceFar + heightSquared);
    f32 middle = 0.5f * (distanceFar + distanceNear);
    params->fovDistance[1] = hsdSqrt(middle * middle + heightSquared);
    params->fovDistance[2] = hsdSqrt(distanceNear * distanceNear + heightSquared);
}

void _wazaSequenceCameraDoFOV(ModelSequence *sequence, wazaSequenceCameraParams *params, int flags, f32 speed) {
    u8 index = sequence->wazaIndex;
    TemplateExpFileHeader *record = (TemplateExpFileHeader *)&sequence->records[index];
    s32 count = record->index;
    f32 low = 0.0f;
    f32 high = 1.0f;
    f32 fovMin;
    f32 fovMax;
    _wazaSequenceCameraGetFOVRange(params, &fovMin, &fovMax, params->fovDistance[0]);
    if (params->motion == 0 || (params->motion >= 4 && params->motion < 6)) {
        u8 mask;
        if (flags & 0x80) {
            mask = 1;
        } else if (flags & 0x200) {
            mask = 4;
        } else {
            mask = 2;
        }
        u8 seenLow;
        u8 seenMid;
        seenLow = 0;
        seenMid = seenLow;
        if ((mask & 1) == 1) {
            low = 0.0f;
            seenLow = 1;
            high = 0.2f;
        }
        if ((mask & 2) == 2) {
            if (seenLow == 0) low = 0.35f;
            high = 0.6f;
            seenMid = 1;
        }
        if ((mask & 4) == 4) {
            if (seenMid == 0) low = 0.75f;
            high = 1.0f;
        }
        f32 fov = ((high - low) * HSD_Randf() + low) * (fovMax - fovMin) + fovMin;
        gFOVlist[1].endFov = fov;
        gFOVlist[1].startFov = fov;
        gFOVlist[0].endFov = fov;
        gFOVlist[0].startFov = fov;
        gCurrentFOV = fov;
        f32 time = record->time[1] * speed;
        gFOVlist[1].endTime = time;
        gFOVlist[1].startTime = time;
        gFOVlist[0].endTime = time;
        gFOVlist[0].startTime = time;
        gCurrentFOVTime = time;
        cameraSetFov(fov);
        return;
    }
    CameraPattern *pattern = wazaSequenceCameraGetPattern(index != 8 && index != 9, flags);
    CameraPatternEntry *entry = pattern->entry;
    u8 mask = entry->startMask;
    u8 seenLow;
    u8 seenMid;
    seenLow = 0;
    seenMid = seenLow;
    if ((mask & 1) == 1) {
        low = 0.0f;
        seenLow = 1;
        high = 0.2f;
    }
    if ((mask & 2) == 2) {
        if (seenLow == 0) low = 0.35f;
        high = 0.6f;
        seenMid = 1;
    }
    if ((mask & 4) == 4) {
        if (seenMid == 0) low = 0.75f;
        high = 1.0f;
    }
    f32 fov = ((high - low) * HSD_Randf() + low) * (fovMax - fovMin) + fovMin;
    gFOVlist[1].endFov = fov;
    gFOVlist[1].startFov = fov;
    gFOVlist[0].endFov = fov;
    gFOVlist[0].startFov = fov;
    gCurrentFOV = fov;
    f32 time = record->time[1] * speed;
    gFOVlist[1].endTime = time;
    gFOVlist[1].startTime = time;
    gFOVlist[0].endTime = time;
    gFOVlist[0].startTime = time;
    gCurrentFOVTime = time;
    cameraSetFov(fov);
    if (count > 2) {
        f32 previousFov = fov;
        f32 startTime = record->time[1];
        CameraFovKey *key = gFOVlist;
        wazaSequenceCameraParams *stage = params;
        for (s32 i = 0; i < 2; i++) {
            f32 begin = startTime;
            startTime = record->time[2];
            if (begin == startTime) {
                f32 time = begin * speed;
                key->startTime = time;
                key->endTime = time;
                key->startFov = previousFov;
                key->endFov = previousFov;
            } else if (entry->kind >= 3 && entry->kind < 5) {
                f32 step = _wazaSequenceCameraSelectDuration(entry->durationMode, entry->chance, startTime - begin);
                f32 nextMin;
                f32 nextMax;
                _wazaSequenceCameraGetFOVRange(params, &nextMin, &nextMax, stage->fovDistance[1]);
                u8 nextMask = entry->endMask;
                u8 nextSeenLow;
                u8 nextSeenMid;
                nextSeenLow = 0;
                nextSeenMid = nextSeenLow;
                if ((nextMask & 1) == 1) {
                    low = 0.0f;
                    nextSeenLow = 1;
                    high = 0.2f;
                }
                if ((nextMask & 2) == 2) {
                    if (nextSeenLow == 0) low = 0.35f;
                    high = 0.6f;
                    nextSeenMid = 1;
                }
                if ((nextMask & 4) == 4) {
                    if (nextSeenMid == 0) low = 0.75f;
                    high = 1.0f;
                }
                f32 nextFov = ((high - low) * HSD_Randf() + low) * (nextMax - nextMin) + nextMin;
                f32 from;
                f32 to;
                if (entry->order == 2) {
                    to = startTime;
                    from = startTime - step;
                } else {
                    from = begin;
                    to = begin + step;
                }
                key->startTime = from * speed;
                key->endTime = to * speed;
                key->startFov = previousFov;
                previousFov = nextFov;
                key->endFov = nextFov;
            } else {
                key->startTime = begin * speed;
                key->endTime = startTime * speed;
                key->startFov = previousFov;
                key->endFov = previousFov;
            }
            key++;
            stage = (wazaSequenceCameraParams *)((u8 *)stage + 4);
            entry++;
            record = (TemplateExpFileHeader *)((u8 *)record + 4);
        }
    }
}

void _wazaSequenceCameraGetFOVRange(wazaSequenceCameraParams *params, f32 *minFov, f32 *maxFov, f32 distance) {
    f32 extent = 0.75f * params->width;
    if (params->depth > extent) extent = params->depth;
    f32 half = 2.0f * (f32)atan2(0.6f * extent, distance);
    *minFov = 57.29578f * half;
    *maxFov = 57.29578f * (2.0f * (f32)atan2(1.8f * extent, distance));
    if (*minFov < 15.0f) *minFov = 15.0f;
    if (*maxFov < 15.0f) *maxFov = 15.0f;
    if (*minFov > 85.0f) *minFov = 85.0f;
    if (*maxFov > 85.0f) *maxFov = 85.0f;
}

f32 _wazaSequenceCameraSelectDuration(u8 mode, f32 *chance, f32 length) {
    f32 result = length;
    f32 original = result;
    if (mode == 1) {
        if (original < 0.2f) return result;
        return 0.2f;
    } else if (mode == 2) {
        if (original < 0.333f) return result;
        return 0.333f;
    } else if (mode == 4) {
        if (original < 0.75f) return result;
        return 0.75f;
    } else if (mode == 8) {
        return result;
    } else if (mode == 3) {
        if (HSD_Randf() < chance[0]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        result = 0.333f;
        if (original < result) return original;
        return result;
    } else if (mode == 5) {
        if (HSD_Randf() < chance[0]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        result = 0.75f;
        if (original < result) return original;
        return result;
    } else if (mode == 9) {
        if (HSD_Randf() < chance[0]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        return original;
    } else if (mode == 6) {
        if (HSD_Randf() < chance[1]) {
            result = 0.333f;
            if (original < result) return original;
            return result;
        }
        result = 0.75f;
        if (original < result) return original;
        return result;
    } else if (mode == 10) {
        if (HSD_Randf() < chance[1]) {
            result = 0.333f;
            if (original < result) return original;
            return result;
        }
        return original;
    } else if (mode == 12) {
        if (HSD_Randf() < chance[2]) {
            result = 0.75f;
            if (original < result) return original;
            return result;
        }
        return original;
    } else if (mode == 7) {
        f32 roll = HSD_Randf();
        if (roll < chance[0]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        if (roll < chance[1]) {
            result = 0.333f;
            if (original < result) return original;
            return result;
        }
        result = 0.75f;
        if (original < result) return original;
        return result;
    } else if (mode == 11) {
        f32 roll = HSD_Randf();
        if (roll < chance[0]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        if (roll < chance[1]) {
            result = 0.333f;
            if (original < result) return original;
            return result;
        }
        return original;
    } else if (mode == 13) {
        f32 roll = HSD_Randf();
        if (roll < chance[0]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        if (roll < chance[2]) {
            result = 0.75f;
            if (original < result) return original;
            return result;
        }
        return original;
    } else if (mode == 14) {
        f32 roll = HSD_Randf();
        if (roll < chance[1]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        if (roll < chance[2]) {
            result = 0.333f;
            if (original < result) return original;
            return result;
        }
        return original;
    } else if (mode == 15) {
        f32 roll = HSD_Randf();
        if (roll < chance[0]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        if (roll < chance[1]) {
            result = 0.2f;
            if (original < result) return original;
            return result;
        }
        if (roll < chance[2]) {
            result = 0.333f;
            if (original < result) return original;
            return result;
        }
        return original;
    }
    return result;
}

void _wazaSequenceCameraSelectMotion(ModelSequence *sequence, WazaSequence *waza, wazaSequenceCameraParams *params) {
    u32 flags;
    u32 front, back, left, right;
    s32 count = 0;
    if (sequence->id == 0x13a) {
        params->motion = 4;
        return;
    }
    if (waza != 0) {
        flags = *(u32 *)((u8 *)waza + 8);
        if (flags & 1) {
            params->motion = 5;
            return;
        }
        front = (flags >> 3) & 1;
        if (front) count = 1;
        back = (flags >> 4) & 1;
        if (back) count++;
        left = (flags >> 5) & 1;
        if (left) count++;
        right = (flags >> 6) & 1;
        if (right) count++;
    }
    if (count == 0) {
        count = 4;
        front = 1;
        back = 1;
        left = 1;
        right = 1;
    } else if (count == 1) {
        if (front) params->motion = 3;
        if (back) params->motion = 0;
        if (left) params->motion = 1;
        if (right) params->motion = 2;
        gLastMotionType = params->motion;
        return;
    }
    f32 share = 1.0f / (f32)count;
    u8 useRight = right;
    u8 useLeft = left;
    u8 useBack = back;
    u8 useFront = front;
    for (;;) {
        f32 roll = HSD_Randf();
        f32 threshold = share;
        if (useFront) {
            if (threshold > roll) {
                params->motion = 3;
                if (gLastMotionType != params->motion) break;
            }
            threshold += share;
        }
        if (useBack) {
            if (threshold > roll) {
                params->motion = 0;
                if (gLastMotionType != params->motion) break;
            }
            threshold += share;
        }
        if (useLeft) {
            if (threshold > roll) {
                params->motion = 1;
                if (gLastMotionType != params->motion) break;
            }
            threshold += share;
        }
        if (useRight) {
            if (threshold > roll) {
                params->motion = 2;
                if (gLastMotionType != params->motion) break;
            }
        }
    }
    gLastMotionType = params->motion;
}

void _wazaSequenceCameraCalculateParams(ModelSequence *sequence, int flags, wazaSequenceCameraParams *params) {
    _GSmodel *model = sequence->model;
    GSbound *bound = GSmodelGetBound(model);
    s32 size = sequence->modelSize;
    GSvec size3;
    GSvec boundMin;
    GSvec boundMax;
    GSvec rotation;
    GSvec extent;
    GSmodelGetRotation(model, &rotation);
    params->baseRotation = rotation.param2;
    f32 rangeScale;
    f32 sizeScale;
    switch (size) {
    case -2:
        rangeScale = 2.4f;
        sizeScale = 0.875f;
        break;
    case -1:
        rangeScale = 1.5f;
        sizeScale = 0.875f;
        break;
    case 1:
        rangeScale = 1.25f;
        sizeScale = 1.4f;
        break;
    case 2:
        rangeScale = 1.3f;
        sizeScale = 1.8f;
        break;
    case 3:
        rangeScale = 1.5f;
        sizeScale = 3.0f;
        break;
    default:
        rangeScale = 1.2f;
        sizeScale = 1.0f;
        break;
    }
    switch (flags & 7) {
    case 1:
        params->rotationA = 0.0f;
        params->rotationB = 0.34906584f;
        break;
    case 2:
        params->rotationA = 0.17453292f;
        params->rotationB = 0.34906584f;
        break;
    case 3:
        params->rotationA = 0.20943952f;
        params->rotationB = 0.7330383f;
        break;
    case 4:
        if (size > 0) {
            params->rotationA = 0.31415927f;
            params->rotationB = 0.83775806f;
        } else {
            params->rotationA = 0.5235988f;
            params->rotationB = 1.0471976f;
        }
        break;
    case 5:
        if (size > 0) {
            params->rotationA = 0.62831855f;
            params->rotationB = 1.1519173f;
        } else {
            params->rotationA = 1.0471976f;
            params->rotationB = 1.3613569f;
        }
        break;
    case 6:
        params->rotationA = 1.2217305f;
        params->rotationB = 1.3962634f;
        break;
    case 7:
        params->rotationA = 1.2217305f;
        params->rotationB = 1.5707964f;
        break;
    default:
        if (size > 0) {
            params->rotationA = 0.20943952f;
            params->rotationB = 1.0471976f;
        } else {
            params->rotationA = 0.20943952f;
            params->rotationB = 1.2566371f;
        }
        break;
    }
    f32 heightLow;
    f32 heightHigh;
    if (flags & 0x80) {
        params->distanceMin = 25.0f;
        params->distanceMax = 35.0f;
        heightLow = 6.0f;
        heightHigh = 8.0f;
    } else if (flags & 0x100) {
        params->distanceMin = 35.0f;
        params->distanceMax = 50.0f;
        heightLow = 6.0f;
        heightHigh = 11.0f;
    } else if (flags & 0x200) {
        params->distanceMin = 50.0f;
        params->distanceMax = 60.0f;
        heightLow = 6.0f;
        heightHigh = 20.0f;
    } else {
        heightHigh = 20.0f;
        params->distanceMin = heightHigh;
        params->distanceMax = 60.0f;
        heightLow = 6.0f;
    }
    params->distanceMin = params->distanceMin * sizeScale;
    params->distanceMax = params->distanceMax * sizeScale;
    GSboundGetMinMax(bound, &boundMin, &boundMax, 0, 0, 0, 0);
    PSVECSubtract(&boundMax, &boundMin, &extent);
    size3.param1 = extent.param1;
    size3.param2 = extent.param2;
    size3.param3 = extent.param3;
    if (size3.param1 < 0.0f) size3.param1 = -size3.param1;
    if (size3.param2 < 0.0f) size3.param2 = -size3.param2;
    if (size3.param3 < 0.0f) size3.param3 = -size3.param3;
    params->width = 0.57735026f * PSVECMag(&size3);
    params->depth = size3.param2;
    params->heightMin = boundMin.param2;
    params->heightMax = boundMax.param2;
    if (params->heightMin < heightLow) {
        params->heightMin = heightLow;
        if (params->heightMax < heightLow) params->heightMax = 1.5f * heightLow;
    }
    if (params->heightMax > heightHigh) {
        params->heightMax = heightHigh;
        if (params->heightMin > heightHigh) params->heightMin = 0.8f * heightHigh;
    }
    params->width = params->width * rangeScale;
    params->depth = params->depth * rangeScale;
    if (params->distanceMin < 20.0f) params->distanceMin = 20.0f;
    if (params->distanceMax < 40.0f) params->distanceMax = 40.0f;
    if (params->distanceMin > 48.0f) params->distanceMin = 48.0f;
    if (params->distanceMax > 60.0f) params->distanceMax = 60.0f;
}
