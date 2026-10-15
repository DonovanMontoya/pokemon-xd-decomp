#include <game/pxdvs/GSAPI/GSbound/GSbound.hpp>
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <libc/string.h>
extern "C" {
void* GSmemAlloc(u32);
void GSmemFree(void*);
void GSmodelGetRootPosition(GSmodel*, Vec*);
void GSmodelGetRootRotation(GSmodel*, Vec*);
void GSmodelGetRootScale(GSmodel*, Vec*);
}
static inline void boundEulerToQuat(Vec* vector, Quaternion* quaternion) {
    EulerToQuat((HSD_Vec3*)vector, (HSD_Quaternion*)quaternion);
}
extern "C" {
void GSboundGetLocalPosition(GSbound* bound, Vec* position) {
    Vec minimum, maximum;
    GSboundGetMinMax(bound, &minimum, &maximum, 0, 0, 0, 0);
    PSVECAdd(&minimum, &maximum, position);
    PSVECScale(position, position, 0.5f);
}
void GSboundGetWorldPosition(GSbound* bound, Vec* position) {
    Vec minimum, maximum;
    GSboundGetMinMax(bound, &minimum, &maximum, 1, 1, 1, 0);
    PSVECAdd(&minimum, &maximum, position);
    PSVECScale(position, position, 0.5f);
}
#pragma dont_inline on
void GSboundGetMinMax(GSbound* bound, Vec* minimum, Vec* maximum, u8 scale, u8 rotate, u8 translate, u8 skipRoot) {
    Mtx matrix, rootRotation, modelRotation, firstRotation, secondRotation;
    Vec vector;
    Quaternion quaternion, matrixQuaternion;
    if (bound->flags & 8) {
        GSboundAnimation* animation = bound->bounds.animated.animations[bound->bounds.animated.index];
        animation = (GSboundAnimation*)((u8*)animation + (s32)bound->bounds.animated.frame * sizeof(GSboundFrame));
        *minimum = animation->frames[0].minimum;
        *maximum = animation->frames[0].maximum;
    } else {
        *minimum = bound->bounds.box.minimum;
        *maximum = bound->bounds.box.maximum;
    }
    switch (bound->transformType) {
    case 1:
        if (skipRoot || !GSmodelIsRootNullAdded(bound->transform.model)) PSMTXIdentity(matrix);
        else {
            GSmodelGetRootScale(bound->transform.model, &vector);
            PSMTXScale(matrix, vector.x, vector.y, vector.z);
            GSmodelGetRootRotation(bound->transform.model, &vector);
            boundEulerToQuat(&vector, &quaternion);
            PSMTXQuat(rootRotation, &quaternion);
            PSMTXConcat(rootRotation, matrix, matrix);
            GSmodelGetRootPosition(bound->transform.model, &vector);
            PSMTXTransApply(matrix, matrix, vector.x, vector.y, vector.z);
        }
        if (scale) {
            GSmodelGetScale(bound->transform.model, (GSvec*)&vector);
            PSMTXScaleApply(matrix, matrix, vector.x, vector.y, vector.z);
        }
        if (rotate) {
            GSmodelGetRotation(bound->transform.model, (GSvec*)&vector);
            boundEulerToQuat(&vector, &quaternion);
            PSMTXQuat(modelRotation, &quaternion);
            PSMTXConcat(modelRotation, matrix, matrix);
        }
        if (translate) {
            GSmodelGetPosition(bound->transform.model, (GSvec*)&vector);
            PSMTXTransApply(matrix, matrix, vector.x, vector.y, vector.z);
        }
        PSMTXMultVec(matrix, minimum, minimum);
        PSMTXMultVec(matrix, maximum, maximum);
        return;
    case 2:
        if (scale && rotate && translate) {
            PSMTXMultVec(bound->transform.matrix, minimum, minimum);
            PSMTXMultVec(bound->transform.matrix, maximum, maximum);
            return;
        }
        if (scale && rotate) {
            PSMTXMultVecSR(bound->transform.matrix, minimum, minimum);
            PSMTXMultVecSR(bound->transform.matrix, maximum, maximum);
            return;
        }
        if (scale) {
            MtxPtr source = bound->transform.matrix;
            f32 x = PSVECMag((Vec*)source[0]);
            f32 y = PSVECMag((Vec*)source[1]);
            PSMTXScale(matrix, x, y, PSVECMag((Vec*)source[2]));
        } else if (rotate) {
            C_QUATMtx(&matrixQuaternion, bound->transform.matrix);
            PSMTXQuat(matrix, &matrixQuaternion);
        }
        if (translate) {
            MtxPtr source = bound->transform.matrix;
            PSMTXTransApply(matrix, matrix, source[0][3], source[1][3], source[2][3]);
        }
        PSMTXMultVec(matrix, minimum, minimum);
        PSMTXMultVec(matrix, maximum, maximum);
        return;
    case 3:
        if (scale) {
            GSboundTransform* transform = bound->transform.transform;
            minimum->x *= transform->scale.x;
            minimum->y *= transform->scale.y;
            minimum->z *= transform->scale.z;
            transform = bound->transform.transform;
            maximum->x *= transform->scale.x;
            maximum->y *= transform->scale.y;
            maximum->z *= transform->scale.z;
        }
        if (rotate) {
            PSMTXQuat(firstRotation, &bound->transform.transform->rotation);
            PSMTXMultVecSR(firstRotation, minimum, minimum);
            PSMTXQuat(secondRotation, &bound->transform.transform->rotation);
            PSMTXMultVecSR(secondRotation, maximum, maximum);
        }
        if (translate) {
            PSVECAdd(minimum, &bound->transform.transform->position, minimum);
            PSVECAdd(maximum, &bound->transform.transform->position, maximum);
        }
        return;
    }
}
#pragma dont_inline reset
static inline f32 absDot(Vec* first, Vec* second) {
    f32 result;
    if (PSVECDotProduct(first, second) > 0.0f) result = PSVECDotProduct(first, second);
    else result = -PSVECDotProduct(first, second);
    return result;
}
void GSboundGetShadowSize(Vec* result, GSbound* bound, Vec* from, Vec* to, Vec* direction) {
    Vec minimum, maximum, right, up, extent;
    Quaternion quaternion;
    Vec normal, toFrom, firstCross, secondCross, sizeDifference;
    Vec corners[4];
    Mtx rotation;
    Mtx scaleMatrix;
    PSVECNormalize(direction, &normal);
    right = normal;
    PSVECSubtract(to, from, &toFrom);
    extent = toFrom;
    PSVECNormalize(&extent, &extent);
    PSVECCrossProduct(&right, &extent, &firstCross);
    up = firstCross;
    PSVECNormalize(&up, &up);
    PSVECCrossProduct(&extent, &up, &secondCross);
    right = secondCross;
    GSboundGetMinMax(bound, &minimum, &maximum, 1, 0, 0, 0);
    switch (bound->transformType) {
    case 1:
        GSmodelGetRotation(bound->transform.model, (GSvec*)&extent);
        boundEulerToQuat(&extent, &quaternion);
        PSMTXQuat(rotation, &quaternion);
        break;
    case 2: {
        PSMTXCopy(bound->transform.matrix, rotation);
        rotation[0][3] = 0.0f; rotation[1][3] = 0.0f; rotation[2][3] = 0.0f;
        MtxPtr source = bound->transform.matrix;
        f32 x = PSVECMag((Vec*)source[0]);
        f32 y = PSVECMag((Vec*)source[1]);
        PSMTXScale(scaleMatrix, x, y, PSVECMag((Vec*)source[2]));
        PSMTXInverse(scaleMatrix, scaleMatrix);
        PSMTXConcat(scaleMatrix, rotation, rotation);
        break;
    }
    case 3: PSMTXQuat(rotation, &bound->transform.transform->rotation); break;
    default: PSMTXIdentity(rotation); break;
    }
    PSVECSubtract(&maximum, &minimum, &sizeDifference);
    extent = sizeDifference;
    if (extent.x < 0.0f) extent.x = -extent.x;
    if (extent.y < 0.0f) extent.y = -extent.y;
    if (extent.z < 0.0f) extent.z = -extent.z;
    f32 a;
    f32 maxA = 0.0f, maxB = 0.0f;
    Vec* corner = corners;
    corners[0] = extent;
    corners[1] = extent; corners[1].y *= -1.0f;
    corners[2] = extent; corners[2].x *= -1.0f;
    corners[3] = extent; corners[3].x *= -1.0f; corners[3].y *= -1.0f;
    for (s32 i = 0; i < 4; ++i, ++corner) {
        f32 b;
        PSMTXMultVec(rotation, corner, corner);
        a = absDot(corner, &up);
        b = absDot(corner, &right);
        if (a > maxA) maxA = a;
        if (b > maxB) maxB = b;
    }
    result->x = maxA;
    result->y = 0.0f;
    result->z = maxB;
}
void GSboundSetAnimFrame(GSbound* bound, f32 frame) {
    if (bound->flags & 8) {
        u16 count = bound->bounds.animated.animations[bound->bounds.animated.index]->frameCount;
        if (frame >= count) frame = count - 1;
        bound->bounds.animated.frame = frame;
    }
}
void GSboundSetAnimIndex(GSbound* bound, s32 index) {
    if (bound->flags & 8) { bound->bounds.animated.index = index; bound->bounds.animated.frame = 0.0f; }
}
s32 GSboundHasAnimData(GSbound* bound) { return (bound->flags >> 3) & 1; }
void GSboundAlwaysInView(GSbound* bound, u8 enabled) {
    if (enabled) bound->flags |= 4;
    else bound->flags &= ~4;
}
void GSboundAddPoint(GSbound* bound, f32 x, f32 y, f32 z) {
    u16 flags = bound->flags;
    if (!(flags & 8)) {
        if (flags & 1) {
            bound->bounds.box.minimum.x = x; bound->bounds.box.minimum.y = y; bound->bounds.box.minimum.z = z;
            bound->bounds.box.maximum.x = x; bound->bounds.box.maximum.y = y; bound->bounds.box.maximum.z = z;
            bound->flags &= ~1;
            return;
        }
        if (x < bound->bounds.box.minimum.x) bound->bounds.box.minimum.x = x;
        if (y < bound->bounds.box.minimum.y) bound->bounds.box.minimum.y = y;
        if (z < bound->bounds.box.minimum.z) bound->bounds.box.minimum.z = z;
        if (x > bound->bounds.box.maximum.x) bound->bounds.box.maximum.x = x;
        if (y > bound->bounds.box.maximum.y) bound->bounds.box.maximum.y = y;
        if (z > bound->bounds.box.maximum.z) bound->bounds.box.maximum.z = z;
    }
}
void GSboundReset(GSbound* bound) { if (!(bound->flags & 8)) bound->flags |= 1; }
void GSboundSetDataPtr(GSbound* bound, s32 type, void* data) {
    if (!data) { bound->transformType = 0; return; }
    bound->transformType = type;
    switch (type) {
    case 1: case 2: case 3: bound->transform.pointer = data; break;
    default: bound->transformType = 0; bound->transform.pointer = 0; break;
    }
}
void GSboundFree(GSbound* bound) {
    bound->transformType = 0;
    if (bound->flags & 8) { GSmemFree(bound->bounds.animated.animations); bound->bounds.animated.animations = 0; }
}
void GSboundCreate(GSbound* bound, GSboundData* data) {
    memset(bound, 0, sizeof(GSbound));
    if (!data) { bound->flags |= 1; return; }
    bound->bounds.animated.data = data;
    bound->bounds.animated.index = 0;
    bound->bounds.animated.frame = 0.0f;
    bound->bounds.animated.animations = (GSboundAnimation**)GSmemAlloc(bound->bounds.animated.data->animationCount * 4);
    GSboundAnimation* animation = (GSboundAnimation*)(bound->bounds.animated.data + 1);
    for (s32 i = 0; i < bound->bounds.animated.data->animationCount; ++i) {
        bound->bounds.animated.animations[i] = animation;
        animation = (GSboundAnimation*)((u8*)animation + animation->frameCount * sizeof(GSboundFrame));
        animation = (GSboundAnimation*)((u8*)animation + 4);
    }
    bound->flags |= 8;
}
}

extern "C" {
void GSboundGetSize(GSbound* bound, Vec* size, u8 scale, u8 rotate) {
    Mtx matrix, inverseScale;
    Vec minimum, maximum, corner;
    Quaternion quaternion;
    Vec difference;
    f32 extentX, extentY, extentZ;
    GSboundGetMinMax(bound, &minimum, &maximum, scale, 0, 0, 0);
    PSVECSubtract(&maximum, &minimum, &difference);
    f32 dx = difference.x, dy = difference.y, dz = difference.z;
    size->x = dx; size->y = dy; size->z = dz;
    if (size->x < 0.0f) size->x = -size->x;
    if (size->y < 0.0f) size->y = -size->y;
    if (size->z < 0.0f) size->z = -size->z;
    if (rotate) {
        switch (bound->transformType) {
        case 1:
            GSmodelGetRotation(bound->transform.model, (GSvec*)&corner);
            boundEulerToQuat(&corner, &quaternion);
            PSMTXQuat(matrix, &quaternion);
            break;
        case 2: {
            PSMTXCopy(bound->transform.matrix, matrix);
            matrix[0][3] = 0.0f; matrix[1][3] = 0.0f; matrix[2][3] = 0.0f;
            MtxPtr source = bound->transform.matrix;
            f32 x = PSVECMag((Vec*)source[0]);
            f32 y = PSVECMag((Vec*)source[1]);
            PSMTXScale(inverseScale, x, y, PSVECMag((Vec*)source[2]));
            PSMTXInverse(inverseScale, inverseScale);
            PSMTXConcat(inverseScale, matrix, matrix);
            break;
        }
        case 3: PSMTXQuat(matrix, &bound->transform.transform->rotation); break;
        default: return;
        }
        extentX = size->x; extentY = size->y; extentZ = size->z;
        PSMTXMultVec(matrix, size, size);
        f32* component = &corner.x;
        for (s32 i = 0; i < 3; ++i, ++component) {
            corner.x = extentX; corner.y = extentY; corner.z = extentZ;
            *component *= -1.0f;
            PSMTXMultVec(matrix, &corner, &corner);
            if (corner.x < 0.0f) corner.x = -corner.x;
            if (corner.y < 0.0f) corner.y = -corner.y;
            if (corner.z < 0.0f) corner.z = -corner.z;
            if (corner.x > size->x) size->x = corner.x;
            if (corner.y > size->y) size->y = corner.y;
            if (corner.z > size->z) size->z = corner.z;
        }
    }
}
s32 GSgfxProjectFastList(Vec*, Vec*, s32);
s32 GSboundIsInViewFast(GSbound* bound) {
    Vec corners[8], projected[8], maximum, minimum;
    if (bound->flags & 4) return 2;
    GSboundGetMinMax(bound, &minimum, &maximum, 1, 1, 1, 0);
    corners[0].x = minimum.x; corners[0].y = minimum.y; corners[0].z = minimum.z;
    corners[1].x = minimum.x; corners[1].y = minimum.y; corners[1].z = maximum.z;
    corners[2].x = minimum.x; corners[2].y = maximum.y; corners[2].z = minimum.z;
    corners[3].x = minimum.x; corners[3].y = maximum.y; corners[3].z = maximum.z;
    corners[4].x = maximum.x; corners[4].y = minimum.y; corners[4].z = minimum.z;
    corners[5].x = maximum.x; corners[5].y = minimum.y; corners[5].z = maximum.z;
    corners[6].x = maximum.x; corners[6].y = maximum.y; corners[6].z = minimum.z;
    corners[7].x = maximum.x; corners[7].y = maximum.y; corners[7].z = maximum.z;
    if (GSgfxProjectFastList(corners, projected, 8) != 2) return 2;
    u8 outsideAny = 0, outsideAll = 0x1f;
    Vec* point = projected;
    for (s32 i = 0; i < 8; ++i, ++point) {
        u8 outside;
        if (point->x < 0.0f) outside = 1;
        else if (point->x > 640.0f) outside = 2;
        else outside = 0;
        if (point->y < 0.0f) outside |= 4;
        else if (point->y > 480.0f) outside |= 8;
        if (point->z == -1.0f) outside |= 16;
        outsideAny |= outside;
        outsideAll &= outside;
    }
    if (!outsideAny) return 2;
    if (outsideAll) return 0;
    else return 1;
}
}
