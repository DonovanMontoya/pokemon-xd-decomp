#ifndef FLOOR_FIELD_CAMERA_PRIVATE_H
#define FLOOR_FIELD_CAMERA_PRIVATE_H

#include <global.h>

struct GSvec {
    f32 x;
    f32 y;
    f32 z;
    GSvec();
};

struct GSmtx {
    f32 m[3][4];
    GSmtx();
};

struct GSvec2 {
    f32 x;
    f32 y;
};

struct GSfloor_dd_;
struct GSthread;

enum FloorStateMode { FloorStateModeNone };
enum FloorEnterMode { FloorEnterModeNone };

struct FloorModuleInterface {
    void (*create)(unsigned int, FloorEnterMode);
    void (*pre)(unsigned int, FloorEnterMode);
    void (*normal)(unsigned int, FloorEnterMode);
    int (*thread)(GSthread*);
    void (*post)(unsigned int, FloorEnterMode);
    void (*free)(unsigned int, FloorEnterMode);
    const char* (*getName)();
    void (*saveState)(FloorStateMode, void*, unsigned long);
    void (*loadState)(FloorStateMode, void*, unsigned long);
    unsigned long (*getStateSize)(FloorStateMode);
    unsigned long (*getStateID)();
};


struct FieldCameraEntry {
    u8 isBox;           // 0x0
    u8 pad01[3];
    f32 x;              // 0x4
    f32 y;              // 0x8
    f32 z;              // 0xC
    f32 distance;       // 0x10
    f32 height;         // 0x14
    f32 rotY;           // 0x18
    f32 radius;         // 0x1C
    f32 ratio;          // 0x20
    f32 angle;          // 0x24
    f32 pow;            // 0x28
    f32 blendTime;      // 0x2C
    f32 fov;            // 0x30
};

struct FieldCameraList {
    u32* count;
    FieldCameraEntry* entries;
};

struct GSBinWriteStream {
    u8* start;          // 0x0
    u8* cur;            // 0x4
    u32 size;           // 0x8
    void* buffer;       // 0xC
    u8 writing;         // 0x10

    GSBinWriteStream();
    GSBinWriteStream(void*, u32);
    ~GSBinWriteStream();
    u32 getWriteSize() const;
    void writeU8(u8);
    void writeS8(s8);
    void writeU16(u16);
    void writeU32(u32);
    void writeBool(bool);
    void writeFloat(f32);
};

struct GSBinWriteSizeStream : public GSBinWriteStream {
    GSBinWriteSizeStream();
    ~GSBinWriteSizeStream();
};

struct GSBinReadStream {
    u8* start;          // 0x0
    u8* cur;            // 0x4
    u32 size;           // 0x8

    GSBinReadStream(void*, u32);
    u8 readU8();
    u16 readU16();
    u32 readU32();
    bool readBool();
    f32 readFloat();
};

extern "C" {
void FloorModuleInterface_clear(FloorModuleInterface*);
u32 floorRegisterModule(u8, u32, FloorModuleInterface*);
void GSmemFree(void*);
void GSlogWrite(const char*, ...);
void* floorDataBiosGetFieldCameraListPtr();
u32 floorDataBiosGetCurrentPtr();
GSfloor_dd_* floorDataBiosGetPtr();
u32 GSresGetResource(u32, u32);
void GSmodelGetPosition(u32, GSvec*);
void GSvecSet(GSvec*, f32, f32, f32);
f32 GSgfxVideoGetLastRenderTime(u8);
u8 GSgfxVideoGetVsyncRate();
void cameraGetTargetPos(GSvec*);
void cameraGetTargetOfs(GSvec*);
u8 cameraGetType();
f32 cameraGetHeight();
f32 cameraGetDistance();
f32 cameraGetRotY();
f32 cameraGetFov();
void cameraSetHeight(f32);
void cameraSetDistance(f32);
void cameraSetRotY(f32);
void cameraSetFov(f32);
void cameraMoveTargetOfs(u32, GSvec*, f32, f32);
void cameraMoveTargetOfsAcc(f32);
void cameraMoveTargetPos(u32, GSvec*, f32);
void cameraMoveTargetPosAcc(f32);
void cameraMovePosition(u32, GSvec*, f32);
void cameraMovePositionAcc(f32);
void cameraMoveRotation(u32, GSvec*, f32);
void cameraMoveRotationAcc(f32);
void PSMTXMultVec(GSmtx*, GSvec*, GSvec*);
void PSMTXRotRad(GSmtx*, u8, f32);
void PSVECAdd(GSvec*, GSvec*, GSvec*);
f32 PSVECSquareDistance(GSvec*, GSvec*);
f64 sin(f64);
f64 cos(f64);
f64 atan2(f64, f64);
f64 pow(f64, f64);
s32 __fpclassifyf(f32);
f64 __frsqrte(f64);
extern unsigned long __float_nan[];
}

#endif
