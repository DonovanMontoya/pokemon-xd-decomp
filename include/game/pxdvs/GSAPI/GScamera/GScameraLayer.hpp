#ifndef GSCAMERA_LAYER_HPP
#define GSCAMERA_LAYER_HPP
#include <dolphin/mtx.h>
struct GSgfxCameraMatrixEntry { u32 dirty; Mtx matrix; };
struct GSgfxCameraMatrixStack { void* previous; GSgfxCameraMatrixEntry* top; };
struct GSgfxCameraRenderState {
    u32 dirty, projection;
    u8 reserved0[8];
    u32 clipping;
    u8 reserved1[0x50];
    u32 lighting;
    u8 reserved2[0x50];
};
struct GSgfxLayer {
    u8 reserved0[0x28];
    s32 id;
    u8 reservedID[0xd54 - 0x2c];
    s32 projectionType;
    f32 projection[6];
    u16 scissor[4];
    f32 viewport[4];
    u8 reserved1[0x1684 - 0xd88];
    f32 nearPlane, farPlane;
    u8 reserved2[0x16a6 - 0x168c];
    u8 lightingEnabled, fogEnabled;
    GSgfxCameraRenderState renderState[2];
    u8 reserved3[0x19a0 - 0x1818];
    GSgfxCameraMatrixStack* matrixStack;
};
#endif
