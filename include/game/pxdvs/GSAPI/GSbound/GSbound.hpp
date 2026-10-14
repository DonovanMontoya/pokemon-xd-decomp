#ifndef GSBOUND_HPP
#define GSBOUND_HPP
#include <dolphin/mtx.h>
struct GSmodel;
struct GSboundFrame { Vec minimum, maximum; };
struct GSboundAnimation { u16 reserved, frameCount; GSboundFrame frames[1]; };
struct GSboundData { u16 animationCount, reserved; };
struct GSboundTransform { Vec position; Quaternion rotation; Vec scale; };
struct GSbound {
    u16 flags, transformType;
    union { GSmodel* model; MtxPtr matrix; GSboundTransform* transform; void* pointer; } transform;
    union {
        struct { Vec minimum, maximum; } box;
        struct { s32 index; f32 frame; GSboundData* data; GSboundAnimation** animations; u8 reserved[8]; } animated;
    } bounds;
};
typedef char GSboundSizeCheck[sizeof(GSbound) == 0x20 ? 1 : -1];
extern "C" {
void GSboundGetMinMax(GSbound*, Vec*, Vec*, u8, u8, u8, u8);
void GSboundGetLocalPosition(GSbound*, Vec*);
void GSboundGetWorldPosition(GSbound*, Vec*);
void GSboundGetSize(GSbound*, Vec*, u8, u8);
void GSboundSetAnimFrame(GSbound*, f32);
void GSboundSetAnimIndex(GSbound*, s32);
s32 GSboundHasAnimData(GSbound*);
s32 GSboundIsInViewFast(GSbound*);
void GSboundAlwaysInView(GSbound*, u8);
void GSboundAddPoint(GSbound*, f32, f32, f32);
void GSboundReset(GSbound*);
void GSboundSetDataPtr(GSbound*, s32, void*);
void GSboundFree(GSbound*);
void GSboundCreate(GSbound*, GSboundData*);
}
#endif
