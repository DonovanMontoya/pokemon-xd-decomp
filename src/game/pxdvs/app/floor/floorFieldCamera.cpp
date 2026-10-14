#include <game/pxdvs/app/floor/floorFieldCameraPrivate.hpp>

namespace std {
inline float powf(float x, float y);
inline float pow(float x, float y);
inline float cosf(float x);
inline float sinf(float x);
inline float atan2f(float y, float x);
inline float sqrtf(float x);
}

extern "C" {
inline void GSvecAdd(GSvec* dst, GSvec* a, GSvec* b);
inline void GSvecTransform(GSvec* dst, GSmtx* m, GSvec* v);
inline f32 GSvecSquareDistance(GSvec* a, GSvec* b);
inline f32 GSvec2Length(GSvec2* v);
inline void GSvec2Rot(GSvec2* dst, GSvec2* src, f32 angle);
inline void GSvec2Sub(GSvec2* dst, GSvec2* a, GSvec2* b);
inline void GSvec2Set(GSvec2* v, f32 x, f32 y);
inline void GSmtxMakeYRotation(GSmtx* m, f32 angle);
}

static FloorModuleInterface _fieldCameraModule;
static f32 gCameraInitFOV = 30.0f;
static f32 gCameraFOV = 30.0f;
static f32 g_BlendingMaxTime = 1.0f;
static u32 _fieldCamera_hModule;
static u32 gNumFieldCameras;
static FieldCameraEntry* gFieldCameraList;
static bool gFieldCameraEnabled;
static u8 gFieldCameraPause;
static bool gCameraVarsInitialised;
static u8 g_updateMode;
static bool g_Blending;
static u16 g_currentIndex;
static f32 gCameraInitHeight;
static f32 gCameraHeight;
static f32 gCameraInitDistance;
static f32 gCameraDistance;
static f32 gCameraInitRotY;
static f32 gCameraRotY;
static f32 gPowValue;
static f32 g_BlendingTime;

static void _fieldCameraExitFloor(unsigned int, FloorEnterMode);
static void _fieldCameraEnterFloor(unsigned int, FloorEnterMode);
static const char* _fieldCameraGetModuleName();
static unsigned long _fieldCameraGetMagicNumber();
static unsigned long _fieldCameraGetStateSize(FloorStateMode);
static void _fieldCameraRestoreStateData(FloorStateMode, void*, unsigned long);
static void _fieldCameraMakeStateData(FloorStateMode, void*, unsigned long);
void floorReleaseFieldCamera();
void floorInitFieldCamera(GSfloor_dd_*);
static u8 _floorFieldCameraCalculateBlendParams(GSvec*, float*, float*, float*, float*);
static u8 _floorFieldCameraCalculatePathParams(GSvec*, float*, float*, float*, float*);
static void _floorFieldCameraSetParams(float, float, float, float);
static void _floorFieldCameraGetTargetPos(GSvec*);
static void _floorFieldCameraDetectMode();

extern "C" {

void floorUpdateFieldCamera();
void floorFieldCameraUnpause();

void floorFieldCameraInit() {
    FloorModuleInterface_clear(&_fieldCameraModule);
    _fieldCameraModule.saveState = _fieldCameraMakeStateData;
    _fieldCameraModule.loadState = _fieldCameraRestoreStateData;
    _fieldCameraModule.getStateSize = _fieldCameraGetStateSize;
    _fieldCameraModule.getStateID = _fieldCameraGetMagicNumber;
    _fieldCameraModule.getName = _fieldCameraGetModuleName;
    _fieldCameraModule.pre = _fieldCameraEnterFloor;
    _fieldCameraModule.post = _fieldCameraExitFloor;
    _fieldCamera_hModule = floorRegisterModule(0xA, 0, &_fieldCameraModule);
}

}

static void _fieldCameraExitFloor(unsigned int, FloorEnterMode mode) {
    if (mode != 1) {
        floorReleaseFieldCamera();
    }
}

static void _fieldCameraEnterFloor(unsigned int, FloorEnterMode mode) {
    GSfloor_dd_* floor = floorDataBiosGetPtr();
    if (floor != 0) {
        if (mode != 0 && mode != 1) {
        } else {
            floorInitFieldCamera(floor);
        }
    }
}

static const char* _fieldCameraGetModuleName() {
    return "field camera";
}

static unsigned long _fieldCameraGetMagicNumber() {
    return 0x15;
}

static unsigned long _fieldCameraGetStateSize(FloorStateMode mode) {
    if (mode == 3 || mode == 1) {
        GSBinWriteSizeStream stream;
        stream.writeU16(0x3C7);
        stream.writeU8(0);
        stream.writeBool(gFieldCameraEnabled);
        stream.writeBool(gCameraVarsInitialised);
        stream.writeBool(g_Blending);
        stream.writeU16(g_currentIndex);
        stream.writeFloat(gCameraInitHeight);
        stream.writeFloat(gCameraHeight);
        stream.writeFloat(gCameraInitDistance);
        stream.writeFloat(gCameraDistance);
        stream.writeFloat(gCameraInitRotY);
        stream.writeFloat(gCameraRotY);
        stream.writeFloat(gCameraInitFOV);
        stream.writeFloat(gCameraFOV);
        stream.writeFloat(gPowValue);
        stream.writeFloat(g_BlendingTime);
        stream.writeFloat(g_BlendingMaxTime);
        return stream.getWriteSize();
    }
    return 0;
}

static void _fieldCameraRestoreStateData(FloorStateMode mode, void* data, unsigned long size) {
    if (mode == 3 || mode == 1) {
        GSBinReadStream stream(data, size);
        if (stream.readU16() == 0x3C7 && stream.readU8() == 0 && floorDataBiosGetCurrentPtr() != 0) {
            FieldCameraList* list = (FieldCameraList*)floorDataBiosGetFieldCameraListPtr();
            if (list != 0) {
                gNumFieldCameras = *list->count;
                gFieldCameraList = list->entries;
                gFieldCameraEnabled = stream.readBool();
                gCameraVarsInitialised = stream.readBool();
                g_Blending = stream.readBool();
                g_currentIndex = stream.readU16();
                gCameraInitHeight = stream.readFloat();
                gCameraHeight = stream.readFloat();
                gCameraInitDistance = stream.readFloat();
                gCameraDistance = stream.readFloat();
                gCameraInitRotY = stream.readFloat();
                gCameraRotY = stream.readFloat();
                gCameraInitFOV = stream.readFloat();
                gCameraFOV = stream.readFloat();
                gPowValue = stream.readFloat();
                g_BlendingTime = stream.readFloat();
                g_BlendingMaxTime = stream.readFloat();
                _floorFieldCameraDetectMode();
                floorUpdateFieldCamera();
            }
        }
    }
}

static void _fieldCameraMakeStateData(FloorStateMode mode, void* data, unsigned long size) {
    if (mode == 3 || mode == 1) {
        GSBinWriteStream stream(data, size);
        stream.writeU16(0x3C7);
        stream.writeU8(0);
        stream.writeBool(gFieldCameraEnabled);
        stream.writeBool(gCameraVarsInitialised);
        stream.writeBool(g_Blending);
        stream.writeU16(g_currentIndex);
        stream.writeFloat(gCameraInitHeight);
        stream.writeFloat(gCameraHeight);
        stream.writeFloat(gCameraInitDistance);
        stream.writeFloat(gCameraDistance);
        stream.writeFloat(gCameraInitRotY);
        stream.writeFloat(gCameraRotY);
        stream.writeFloat(gCameraInitFOV);
        stream.writeFloat(gCameraFOV);
        stream.writeFloat(gPowValue);
        stream.writeFloat(g_BlendingTime);
        stream.writeFloat(g_BlendingMaxTime);
    }
}

extern "C" u8 floorFieldCameraGetMode() {
    return g_updateMode;
}

void floorReleaseFieldCamera() {
    gNumFieldCameras = 0;
    gFieldCameraList = 0;
}

void floorInitFieldCamera(GSfloor_dd_*) {
    FieldCameraList* list = (FieldCameraList*)floorDataBiosGetFieldCameraListPtr();
    gNumFieldCameras = 0;
    gFieldCameraList = 0;
    gCameraVarsInitialised = 0;
    gFieldCameraEnabled = 1;
    gCameraHeight = 0.0f;
    gCameraDistance = 0.0f;
    gCameraRotY = 0.0f;
    gCameraFOV = 30.0f;
    gPowValue = 0.0f;
    if (list != 0) {
        gNumFieldCameras = *list->count;
        gFieldCameraList = list->entries;
        _floorFieldCameraDetectMode();
        g_currentIndex = 0;
        gCameraInitHeight = gCameraHeight = gFieldCameraList->height;
        gCameraInitDistance = gCameraDistance = gFieldCameraList->distance;
        gCameraInitRotY = gCameraRotY = gFieldCameraList->rotY;
        gCameraInitFOV = gCameraFOV = gFieldCameraList->fov;
        gPowValue = gFieldCameraList->pow;
        g_Blending = 0;
        g_BlendingTime = 0.0f;
        floorUpdateFieldCamera();
    }
}

extern "C" {

void floorUpdateFieldCamera() {
    GSvec target;
    f32 distance;
    f32 height;
    f32 rotY;
    f32 fov;
    if (gFieldCameraEnabled != 0 && gFieldCameraPause == 0 && cameraGetType() == 0 && gNumFieldCameras != 0) {
        if (gNumFieldCameras == 1) {
            _floorFieldCameraSetParams(gFieldCameraList->height, gFieldCameraList->distance, gFieldCameraList->rotY, gFieldCameraList->fov);
            return;
        }
        cameraGetTargetPos(&target);
        height = gCameraHeight;
        distance = gCameraDistance;
        rotY = gCameraRotY;
        fov = gCameraFOV;
        switch ((int)g_updateMode) {
        case 1:
            if (_floorFieldCameraCalculatePathParams(&target, &height, &distance, &rotY, &fov) != 0) {
                if (gCameraVarsInitialised != 0 && g_Blending != 0 && g_BlendingMaxTime > 0.0f) {
                    u8 rate = GSgfxVideoGetVsyncRate();
                    g_BlendingTime = g_BlendingTime + GSgfxVideoGetLastRenderTime(rate) / rate;
                    if (g_BlendingTime >= g_BlendingMaxTime) {
                        g_Blending = 0;
                        gCameraHeight = height;
                        gCameraDistance = distance;
                        gCameraRotY = rotY;
                        gCameraFOV = fov;
                    } else {
                        f32 t = g_BlendingTime / g_BlendingMaxTime;
                        if (gPowValue < -0.00001f) {
                            gCameraHeight = t * (height - gCameraInitHeight) + gCameraInitHeight;
                            gCameraDistance = t * (distance - gCameraInitDistance) + gCameraInitDistance;
                            gCameraRotY = t * (rotY - gCameraInitRotY) + gCameraInitRotY;
                            gCameraFOV = t * (fov - gCameraInitFOV) + gCameraInitFOV;
                        } else if (gPowValue < 0.19999f) {
                            f32 t2 = t * t;
                            gCameraHeight += t2 * (height - gCameraHeight);
                            gCameraDistance += t2 * (distance - gCameraDistance);
                            gCameraRotY += t2 * (rotY - gCameraRotY);
                            gCameraFOV += t2 * (fov - gCameraFOV);
                        } else {
                            u8 flip = 0;
                            f32 x = t * 2.0f;
                            f32 y;
                            if (x > 1.0f) {
                                flip = 1;
                                x = 2.0f - x;
                            }
                            y = std::pow(1.0f - std::cosf(1.5707964f * x), gPowValue);
                            if (flip != 0) {
                                y = 2.0f - y;
                            }
                            y = y * 0.5f;
                            gCameraHeight = y * (height - gCameraInitHeight) + gCameraInitHeight;
                            gCameraDistance = y * (distance - gCameraInitDistance) + gCameraInitDistance;
                            gCameraRotY = y * (rotY - gCameraInitRotY) + gCameraInitRotY;
                            gCameraFOV = y * (fov - gCameraInitFOV) + gCameraInitFOV;
                        }
                    }
                } else {
                    g_Blending = 0;
                    gCameraInitHeight = gCameraHeight = height;
                    gCameraInitDistance = gCameraDistance = distance;
                    gCameraInitRotY = gCameraRotY = rotY;
                    gCameraInitFOV = gCameraFOV = fov;
                    gCameraVarsInitialised = 1;
                }
                goto setParams;
            }
            break;
        case 0:
        default:
            if (_floorFieldCameraCalculateBlendParams(&target, &height, &distance, &rotY, &fov) != 0) {
                if (gCameraVarsInitialised != 0) {
                    gCameraHeight = 0.5f * gCameraHeight + 0.5f * height;
                    gCameraDistance = 0.5f * gCameraDistance + 0.5f * distance;
                    gCameraRotY = 0.5f * gCameraRotY + 0.5f * rotY;
                    gCameraFOV = 0.5f * gCameraFOV + 0.5f * fov;
                } else {
                    gCameraHeight = height;
                    gCameraDistance = distance;
                    gCameraRotY = rotY;
                    gCameraFOV = fov;
                    gCameraVarsInitialised = 1;
                }
setParams:
                _floorFieldCameraSetParams(gCameraHeight, gCameraDistance, gCameraRotY, gCameraFOV);
            }
        }
    }
}

void floorFieldCameraBlend(f32 dt) {
    GSvec target;
    GSvec ofs;
    GSvec pos;
    GSvec rot;
    GSvec off;
    GSmtx mtx;
    f32 distance;
    f32 height;
    f32 rotY;
    f32 fov;
    if (gFieldCameraEnabled != 0 && gFieldCameraPause == 0 && cameraGetType() == 0 && gNumFieldCameras != 0) {
        _floorFieldCameraGetTargetPos(&target);
        cameraGetTargetOfs(&ofs);
        if (gNumFieldCameras == 1) {
            height = gFieldCameraList->height;
            distance = gFieldCameraList->distance;
            rotY = gFieldCameraList->rotY;
            fov = gFieldCameraList->fov;
            goto apply;
        }
        height = cameraGetHeight();
        distance = cameraGetDistance();
        rotY = cameraGetRotY();
        fov = cameraGetFov();
        switch ((int)g_updateMode) {
        case 1:
            if (_floorFieldCameraCalculatePathParams(&target, &height, &distance, &rotY, &fov) == 0) {
                break;
            }
            goto apply;
        case 0:
            if (_floorFieldCameraCalculateBlendParams(&target, &height, &distance, &rotY, &fov) == 0) {
                return;
            }
apply:
            GSvecSet(&off, 0.0f, height, distance);
            GSmtxMakeYRotation(&mtx, rotY);
            GSvecTransform(&off, &mtx, &off);
            GSvecAdd(&pos, &target, &ofs);
            GSvecAdd(&pos, &pos, &off);
            rot.z = rotY;
            rot.x = -std::atan2f(height, distance);
            rot.y = 0.0f;
            cameraMoveTargetOfs(0, &ofs, dt, rot.x);
            cameraMoveTargetOfsAcc(0.08f);
            cameraMoveTargetPos(0, &target, dt);
            cameraMoveTargetPosAcc(0.08f);
            cameraMovePosition(0, &pos, dt);
            cameraMovePositionAcc(0.08f);
            cameraMoveRotation(0, &rot, dt);
            cameraMoveRotationAcc(0.08f);
            cameraSetFov(fov);
        }
    }
}

s32 floorFieldCameraDataExist() {
    s32 result = 0;
    if (gNumFieldCameras != 0 && gFieldCameraList != 0) {
        result = 1;
    }
    return result;
}

u8 floorFieldCameraGetEnabled() {
    return gFieldCameraEnabled;
}

void floorFieldCameraUnpause() {
    gFieldCameraPause = 0;
}

void floorFieldCameraPause() {
    gFieldCameraPause = 1;
}

void floorFieldCameraDisable() {
    gFieldCameraEnabled = 0;
}

void floorFieldCameraEnable() {
    gFieldCameraEnabled = 1;
    gCameraVarsInitialised = 0;
    floorFieldCameraUnpause();
}

}

static u8 _floorFieldCameraCalculateBlendParams(GSvec* target, float* height, float* distance, float* rotY, float* fov) {
    GSvec pos;
    f32 weightSum = 0.0f;
    u32 i = 0;
    f32 sumDistance = 0.0f;
    f32 sumHeight = 0.0f;
    f32 sumRotY = 0.0f;
    f32 sumFov = 0.0f;
    for (; i < gNumFieldCameras; i++) {
        FieldCameraEntry* e = &gFieldCameraList[i];
        f32 d;
        GSvecSet(&pos, e->x, target->y, e->z);
        d = GSvecSquareDistance(&pos, target);
        if (d > 1.0f) {
            f32 w = 0.001f / d;
            weightSum += w;
            sumDistance += e->distance * w;
            sumHeight += e->height * w;
            sumRotY += e->rotY * w;
            sumFov += e->fov * w;
        } else {
            weightSum = 1.0f;
            sumHeight = e->height;
            sumDistance = e->distance;
            sumRotY = e->rotY;
            sumFov = e->fov;
            break;
        }
    }
    if (weightSum == 0.0f) {
        GSlogWrite("floorUpdateFieldCamera: error updating field camera - divide by zero!");
        return 0;
    }
    {
        f32 inv = 1.0f / weightSum;
        *height = sumHeight * inv;
        *distance = sumDistance * inv;
        *rotY = sumRotY * inv;
        *fov = sumFov * inv;
    }
    return 1;
}

static u8 _floorFieldCameraCalculatePathParams(GSvec* target, float* height, float* distance, float* rotY, float* fov) {
    GSvec2 delta;
    GSvec2 tpos;
    FieldCameraEntry* e;
    FieldCameraEntry* cur;
    u16 i;
    GSvec2Set(&tpos, target->x, target->z);
    cur = &gFieldCameraList[g_currentIndex];
    *height = cur->height;
    *distance = cur->distance;
    *rotY = cur->rotY;
    *fov = cur->fov;
    GSvec2Set(&delta, cur->x, cur->z);
    GSvec2Sub(&delta, &delta, &tpos);
    if (cur->isBox != 0) {
        f32 ax;
        f32 az;
        f32 r;
        GSvec2Rot(&delta, &delta, -cur->angle);
        ax = delta.x;
        if (ax < 0.0f) {
            ax = -ax;
        }
        r = cur->radius;
        if (ax < r) {
            az = delta.y;
            if (az < 0.0f) {
                az = -az;
            }
            if (az < r * cur->ratio) {
                return 1;
            }
        }
    } else {
        if (GSvec2Length(&delta) <= cur->radius) {
            return 1;
        }
    }
    e = gFieldCameraList;
    for (i = 0; i < gNumFieldCameras; i++, e++) {
        if (i != g_currentIndex) {
            u8 inside = 0;
            GSvec2Set(&delta, e->x, e->z);
            GSvec2Sub(&delta, &delta, &tpos);
            if (e->isBox != 0) {
                f32 ax;
                f32 az;
                f32 r;
                GSvec2Rot(&delta, &delta, -e->angle);
                ax = delta.x;
                if (ax < 0.0f) {
                    ax = -ax;
                }
                r = e->radius;
                if (ax < r) {
                    az = delta.y;
                    if (az < 0.0f) {
                        az = -az;
                    }
                    if (az < r * e->ratio) {
                        inside = 1;
                    }
                }
            } else {
                if (GSvec2Length(&delta) <= e->radius) {
                    inside = 1;
                }
            }
            if (inside != 0) {
                *height = e->height;
                *distance = e->distance;
                *rotY = e->rotY;
                *fov = e->fov;
                g_currentIndex = i;
                gCameraInitHeight = gCameraHeight;
                gCameraInitDistance = gCameraDistance;
                gCameraInitRotY = gCameraRotY;
                gCameraInitFOV = gCameraFOV;
                gPowValue = e->pow;
                g_Blending = 1;
                g_BlendingTime = 0.0f;
                g_BlendingMaxTime = e->blendTime;
                break;
            }
        }
    }
    return 1;
}

static void _floorFieldCameraSetParams(float height, float distance, float rotY, float fov) {
    cameraSetHeight(height);
    cameraSetDistance(distance);
    cameraSetRotY(rotY);
    cameraSetFov(fov);
}

static void _floorFieldCameraGetTargetPos(GSvec* out) {
    u32 model = GSresGetResource(0, 0x64);
    if (model != 0) {
        GSmodelGetPosition(model, out);
        return;
    }
    cameraGetTargetPos(out);
}

static void _floorFieldCameraDetectMode() {
    FieldCameraEntry* e = gFieldCameraList;
    u32 i;
    g_updateMode = 0;
    for (i = 0; i < gNumFieldCameras; i++, e++) {
        if (e->radius <= 0.001f || e->blendTime < 0.0f) {
            return;
        }
    }
    g_updateMode = 1;
}

u32 GSBinWriteStream::getWriteSize() const {
    return cur - start;
}

inline void GSBinWriteStream::writeFloat(f32 v) {
    union { f32 f; u32 u; } c;
    c.f = v;
    writeU32(c.u);
}

inline void GSBinWriteStream::writeU32(u32 v) {
    if (writing == 0) {
        cur += 4;
        return;
    }
    *cur++ = v >> 24;
    *cur++ = v >> 16;
    *cur++ = v >> 8;
    *cur++ = v;
}

inline void GSBinWriteStream::writeBool(bool v) {
    int b;
    if (v) {
        b = 1;
    } else {
        b = 0;
    }
    writeS8(b);
}

inline void GSBinWriteStream::writeS8(s8 v) {
    writeU8(v);
}

inline void GSBinWriteStream::writeU8(u8 v) {
    if (writing == 0) {
        cur++;
        return;
    }
    *cur++ = v;
}

inline void GSBinWriteStream::writeU16(u16 v) {
    if (writing == 0) {
        cur += 2;
        return;
    }
    *cur++ = (v >> 8) & 0xFF;
    *cur++ = v & 0xFF;
}

inline GSBinWriteSizeStream::~GSBinWriteSizeStream() {
}

inline GSBinWriteStream::~GSBinWriteStream() {
    if (buffer != 0) {
        GSmemFree(buffer);
    }
}

inline GSBinWriteSizeStream::GSBinWriteSizeStream() {
    cur = 0;
    buffer = 0;
    start = 0;
    size = 0x10000000;
    writing = 0;
}

inline GSBinWriteStream::GSBinWriteStream() {
    cur = 0;
    buffer = 0;
    start = 0;
    size = 0;
    writing = 0;
}

inline f32 GSBinReadStream::readFloat() {
    union { f32 f; u32 u; } c;
    c.u = readU32();
    return c.f;
}

inline u32 GSBinReadStream::readU32() {
    u32 v = (cur[0] << 24) | (cur[1] << 16) | (cur[2] << 8) | cur[3];
    cur += 4;
    return v;
}

inline bool GSBinReadStream::readBool() {
    return readU8() != 0;
}

inline u8 GSBinReadStream::readU8() {
    return *cur++;
}

inline u16 GSBinReadStream::readU16() {
    u16 v = (cur[0] << 8) | cur[1];
    cur += 2;
    return v;
}

inline GSBinReadStream::GSBinReadStream(void* data, u32 sz) {
    cur = (u8*)data;
    start = (u8*)data;
    size = sz;
}

inline GSBinWriteStream::GSBinWriteStream(void* data, u32 sz) {
    buffer = 0;
    cur = (u8*)data;
    start = (u8*)data;
    size = sz;
    writing = 1;
}

namespace std {
inline float pow(float x, float y) {
    return powf(x, y);
}
inline float powf(float x, float y) {
    return (float)::pow(x, y);
}
inline float cosf(float x) {
    return (float)::cos(x);
}
inline float atan2f(float y, float x) {
    return (float)::atan2(y, x);
}
inline float sinf(float x) {
    return (float)::sin(x);
}
inline float sqrtf(float x) {
    if (x > 0.0f) {
        double dmag = x;
        double t = __frsqrte(dmag);
        t = 0.5 * t * (3.0 - t * t * dmag);
        t = 0.5 * t * (3.0 - t * t * dmag);
        t = 0.5 * t * (3.0 - t * t * dmag);
        return (float)(dmag * t);
    } else if (x < 0.0) {
        return *(float*)__float_nan;
    } else if (__fpclassifyf(x) == 1) {
        return *(float*)__float_nan;
    }
    return x;
}
}

extern "C" {

inline void GSvecAdd(GSvec* dst, GSvec* a, GSvec* b) {
    PSVECAdd(a, b, dst);
}

inline void GSvecTransform(GSvec* dst, GSmtx* m, GSvec* v) {
    PSMTXMultVec(m, v, dst);
}

inline f32 GSvecSquareDistance(GSvec* a, GSvec* b) {
    return PSVECSquareDistance(a, b);
}

inline f32 GSvec2Length(GSvec2* v) {
    return std::sqrtf(v->x * v->x + v->y * v->y);
}

inline void GSvec2Rot(GSvec2* dst, GSvec2* src, f32 angle) {
    f32 c = std::cosf(angle);
    f32 s = std::sinf(angle);
    f32 sy = src->y;
    f32 sx = src->x;
    dst->x = sx * c + sy * s;
    dst->y = -sx * s + sy * c;
}

inline void GSvec2Sub(GSvec2* dst, GSvec2* a, GSvec2* b) {
    dst->x = a->x - b->x;
    dst->y = a->y - b->y;
}

inline void GSvec2Set(GSvec2* v, f32 x, f32 y) {
    v->x = x;
    v->y = y;
}

inline void GSmtxMakeYRotation(GSmtx* m, f32 angle) {
    PSMTXRotRad(m, 'Y', angle);
}

}
