#ifndef GAME_PXDVS_GSAPI_GSGFXM_BACKFB_PRIVATE_HPP
#define GAME_PXDVS_GSAPI_GSGFXM_BACKFB_PRIVATE_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct GStexture;
struct GSgfxLayer;
typedef u8 (*BackFBCaptureCallback)(GStexture *, u32, void *);
struct BackFBCapture {
    u8 active;
    u8 padding[3];
    GStexture *texture;
    BackFBCaptureCallback callback;
    void *argument;
    u32 frame;
};
typedef char BackFBCaptureSizeCheck[sizeof(BackFBCapture) == 0x14 ? 1 : -1];
#endif
