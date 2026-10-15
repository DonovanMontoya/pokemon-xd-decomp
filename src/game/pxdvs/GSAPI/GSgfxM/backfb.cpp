#include <game/pxdvs/GSAPI/GSgfxM/backfbPrivate.hpp>
extern "C" {
s32 GStextureGetFormat(GStexture *);
void GStextureUnlockImage(GStexture *);
void GStextureSetWrap(GStexture *, s32, s32);
void GStextureSetFilter(GStexture *, s32, s32, u8);
void *GStextureLockImage(GStexture *, u32);
void GetFifoSize__10GSgfxLayerFPUlPUl(GSgfxLayer *, u32 *, u32 *);
void textureCopy__10GSgfxLayerF14GSgfxLayerPassP9GStexturebPUcbbb(GSgfxLayer *, s32, GStexture *, u8, u8 *, u8, u8, u8);
static BackFBCapture gfxBackFBList[4];
static u8 _backFBIsCapturing;

static inline BackFBCapture *findCapture(GStexture *texture) {
    BackFBCapture *capture = gfxBackFBList;
    for (u32 i = 0; i < 4; ++i, ++capture) {
        if (capture->active == 1 && capture->texture == texture) return capture;
    }
    return 0;
}
s32 GSgfxEndBackFBCapture(GStexture *texture) {
    BackFBCapture *capture = findCapture(texture);
    if (capture == 0) return 0;
    GStextureUnlockImage(capture->texture);
    capture->active = 0;
    _backFBIsCapturing = 0;
    BackFBCapture *other = gfxBackFBList;
    for (u32 i = 0; i < 4; ++i, ++other) {
        if (other->active == 1) { _backFBIsCapturing = 1; break; }
    }
    return 1;
}
static inline BackFBCapture *findFreeCapture() {
    BackFBCapture *capture = gfxBackFBList;
    for (u32 i = 0; i < 4; ++i, ++capture) {
        if (capture->active == 0) return capture;
    }
    return 0;
}
s32 GSgfxBeginBackFBCapture(GStexture *texture, BackFBCaptureCallback callback, void *argument) {
    switch (GStextureGetFormat(texture)) {
    case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x90: break;
    default: return 0;
    }
    if (findCapture(texture) != 0) return 0;
    BackFBCapture *capture = findFreeCapture();
    if (capture == 0) return 0;
    capture->active = 1;
    capture->texture = texture;
    capture->callback = callback;
    capture->argument = argument;
    capture->frame = 0;
    GStextureSetWrap(capture->texture, 0, 0);
    GStextureSetFilter(capture->texture, 2, 2, 0);
    GStextureLockImage(capture->texture, 0);
    _backFBIsCapturing = 1;
    return 1;
}
void GSgfxBackFBDoFrame__FP10GSgfxLayer(GSgfxLayer *layer) {
    u32 opaque, translucent;
    s32 pass;
    u32 i;
    BackFBCapture *capture;
    if (_backFBIsCapturing != 0) {
        GetFifoSize__10GSgfxLayerFPUlPUl(layer, &opaque, &translucent);
        capture = gfxBackFBList;
        i = 0;
        pass = (translucent != 0) ? 1 : 0;
        for (; i < 4; ++i, ++capture) {
            if (capture->active == 1) {
                textureCopy__10GSgfxLayerF14GSgfxLayerPassP9GStexturebPUcbbb(layer, pass, capture->texture, 1, 0, 0, 0, 0);
                if (capture->callback && capture->callback(capture->texture, capture->frame, capture->argument) == 0)
                    GSgfxEndBackFBCapture(capture->texture);
                ++capture->frame;
            }
        }
    }
}
void GSgfxBackFBInit__Fv(void) {
    gfxBackFBList[0].active = 0;
    _backFBIsCapturing = 0;
    gfxBackFBList[1].active = 0;
    gfxBackFBList[2].active = 0;
    gfxBackFBList[3].active = 0;
}
}
