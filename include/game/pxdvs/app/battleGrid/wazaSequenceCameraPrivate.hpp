#ifndef WAZA_SEQUENCE_CAMERA_PRIVATE_HPP
#define WAZA_SEQUENCE_CAMERA_PRIVATE_HPP
#include <game/pxdvs/app/wazaSequence/modelSequence.hpp>

struct GSbound;

// Camera shot description filled in by _wazaSequenceCameraCalculateParams.
struct wazaSequenceCameraParams {
    s32 motion;         // 0x00
    f32 width;          // 0x04
    f32 depth;          // 0x08
    f32 rotationA;      // 0x0c
    f32 rotationB;      // 0x10
    f32 baseRotation;   // 0x14
    f32 heightMin;      // 0x18
    f32 heightMax;      // 0x1c
    f32 distanceMin;    // 0x20
    f32 distanceMax;    // 0x24
    f32 fovDistance[3]; // 0x28
};

// Per-waza camera timing record (the 0xd0-byte entries of ModelSequence::records).
struct TemplateExpFileHeader {
    s32 index;          // 0x00
    s32 reserved;       // 0x04
    union {
        u32 flags;      // 0x08
        f32 time[1];    // 0x08 + index * 4
    };
};

// One camera keyframe description inside a pattern.
struct CameraPatternEntry {
    f32 chance[3];      // 0x00
    f32 reserved0C;     // 0x0c
    u8 kind;            // 0x10
    u8 durationMode;    // 0x11
    u8 startMask;       // 0x12
    u8 endMask;         // 0x13
    u8 order;           // 0x14
    u8 reserved15[3];
};

// Pattern returned by wazaSequenceCameraGetPattern.
struct CameraPattern {
    u32 header;                 // 0x00
    CameraPatternEntry entry[2]; // 0x04
};

extern "C" {
f32 HSD_Randf();
f64 atan2(f64, f64);
f64 __frsqrte(f64);
u8 GSgfxVideoGetVsyncRate();
void PSVECAdd(GSvec *, GSvec *, GSvec *);
void PSVECScale(GSvec *, GSvec *, f32);
void PSVECSubtract(GSvec *, GSvec *, GSvec *);
f32 PSVECMag(GSvec *);
void GSboundGetMinMax(GSbound *, GSvec *, GSvec *, u8, u8, u8, u8);
GSbound *GSmodelGetBound(_GSmodel *);
void cameraLockYTarget(u8);
void cameraSetDistance(f32);
void cameraSetHeight(f32);
void cameraSetRotY(f32);
void cameraSetFov(f32);
void cameraUpdate();
void cameraGetPosition(GSvec *);
void cameraSetPosition(GSvec *);
void cameraGetTargetPos(GSvec *);
void cameraMovePosition(u32, GSvec *, f32);
void cameraMovePositionAcc(f32);
void cameraMoveRotationAcc(f32);
void cameraMoveRotationXYZ(u32, f32, f32, f32, f32);
}
CameraPattern *wazaSequenceCameraGetPattern(bool, int);

struct CameraFovKey {
    f32 startFov, endFov, startTime, endTime;
};
extern CameraFovKey gFOVlist[2];
extern f32 gCurrentFOV;
extern s32 gLastMotionType;
extern f32 gCurrentFOVTime;

void _wazaSequenceCameraDoPosition(ModelSequence *, wazaSequenceCameraParams *, f32, bool);
void _wazaSequenceCameraDoDollyPosition(TemplateExpFileHeader *, wazaSequenceCameraParams *, f32, bool);
void _wazaSequenceCameraDoFOV(ModelSequence *, wazaSequenceCameraParams *, int, f32);
void _wazaSequenceCameraGetFOVRange(wazaSequenceCameraParams *, f32 *, f32 *, f32);
f32 _wazaSequenceCameraSelectDuration(u8, f32 *, f32);
void _wazaSequenceCameraSelectMotion(ModelSequence *, WazaSequence *, wazaSequenceCameraParams *);
void _wazaSequenceCameraCalculateParams(ModelSequence *, int, wazaSequenceCameraParams *);
#endif
