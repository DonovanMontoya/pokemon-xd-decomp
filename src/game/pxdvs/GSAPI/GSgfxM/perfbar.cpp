#include <dolphin/types.h>
#include <libc/string.h>
#include <dolphin/gx.h>
#include <game/pxdvs/GSAPI/GSgfxM/resetPrivate.hpp>

static u8 _perfLastFrame[0x2228];
static u8 _perfCurFrame[0x2228];
static f32 _perfPERFMtx[4][4];
static s32 _perfRenderMode = 1;
static s32 _perfBkgnd = 0x202020C0;
static u8 _perfFrameCount;
static f32 _perfPixelSkip;
static f32 _perfPeakCPU;
static f32 _perfPeakGPU;
static s32 _perfPeakCPUTimer;
static s32 _perfPeakGPUTimer;
static s32 _perfUpdateCount;
static f32 _perfUpdateTime;
static f32 _perfUpdateFPS;
static u32 _perfDisplayList;
static u32 _perfDListSize;
static u8 _perfFullStarted;
static s16 _perfDListToken;
static GXColor _perfDrawColor;

extern "C" {
void GSprimSetRenderLayer__FP10GSgfxLayer(GSgfxLayer *);
void GSprimSetQuadVertexOrder(s32);
void GSprimSetLineWidth(f32);
void GSprimSetTextSize(f32, f32);
void GSprimSetTextWidth(f32);
void GSmtx44Ortho(f32 *, f32, f32, f32, f32, f32, f32);
void GSprimDraw2DQuadWH(f32, f32, f32, f32, const GXColor *);
void GSprimDraw2DHLine(f32, f32, f32, const GXColor *);
void GSprimDraw2DVLine(f32, f32, f32, const GXColor *);
void GSprimWriteStr(f32, f32, const char *, ...);
s32 GSgfxVideoGetLockFrameRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);
extern s32 __float_epsilon[];
void GSgfxGPUGetBPTick__FPlPl(s32 *, s32 *);
void FlushState__10GSgfxLayerFv(GSgfxLayer *);
void InvalidateState__10GSgfxLayerFv(GSgfxLayer *);
s16 tokenMark__10GSgfxLayerFv(GSgfxLayer *);
void PERFPreDraw(void);
void PERFPostDraw(void);
void GXCallDisplayList(void *, u32);
}

extern "C" {
s64 OSGetTime(void);
void PERFStartFrame(void);
void PERFStartAutoSampling(f32);
u32 PERFInit(u32, u32, u32, void *(*)(u32), void (*)(void *), void (*)(void));
void PERFSetDrawBWBarKey(BOOL);
void PERFSetDrawSyncCallback(void (*)(u16));
void GSgfxTokenSetDrawSyncCBFunc__FPFPFUs_v_v(void (*)(void (*)(u16)));
void *GSmemAlloc(u32);
void GSmemFree(void *);
f32 __cvt_sll_flt(s64);
void GSgfxTokenWaitForClearAndReset(u16 *);
void *GSmemAllocAlign(u32, u32);
void DCFlushRange(void *, u32);
void GXBeginDisplayList(void *, u32);
void GXResetWriteGatherPipe(void);
void PERFDumpScreen(void);
void GXFlush(void);
u32 GXEndDisplayList(void);
void PERFEndFrame(void);
void PERFStopAutoSampling(void);


s32 GSgfxPerfbarGetRenderMode(void)
{
    return _perfRenderMode;
}

void GSgfxPerfbarSetRenderMode(s32 mode)
{
    _perfRenderMode = mode;
}

static void _perfRestoreGPU__Fv(void)
{
}

void GSgfxPerfbarGPUStart__Fv(void)
{
    s64 time = OSGetTime();
    *(s64 *)(_perfCurFrame + 0x2010) = time;
    *(u32 *)(_perfCurFrame + 0x201C) = 0;
}

void GSgfxPerfbarCPUStart__Fv(void)
{
    s64 time = OSGetTime();
    *(s64 *)_perfCurFrame = time;
    *(u32 *)(_perfCurFrame + 0xC) = 0;
    if (_perfRenderMode == 2) {
        PERFStartFrame();
        PERFStartAutoSampling(1.0f);
        _perfFullStarted = 1;
    }
}

s32 GSgfxPerfbarGPUEntry__FUl(u32 color)
{
    if (*(u32 *)(_perfCurFrame + 0x201C) >= 0x40) return 0;
    u32 previous;
    if (*(u32 *)(_perfCurFrame + 0x201C) == 0) previous = 0xFFFF;
    else previous = *(u32 *)(_perfCurFrame + 0x211C + *(u32 *)(_perfCurFrame + 0x201C) * 4);
    s64 now = OSGetTime();
    *(f32 *)(_perfCurFrame + 0x2020 + *(u32 *)(_perfCurFrame + 0x201C) * 4) =
        (f32)(__cvt_sll_flt(now - *(s64 *)(_perfCurFrame + 0x2010)) /
              (f32)(*(volatile u32 *)0x800000F8 / 240));
    *(u32 *)(_perfCurFrame + 0x2120 + *(u32 *)(_perfCurFrame + 0x201C) * 4) = color;
    *(u32 *)(_perfCurFrame + 0x201C) += 1;
    return previous;
}

s32 GSgfxPerfbarCPUEntry(s32 color)
{
    if (*(u32 *)(_perfCurFrame + 0xC) >= 0x400) return 0;
    u32 previous;
    if (*(u32 *)(_perfCurFrame + 0xC) == 0) previous = 0xFFFFFF;
    else previous = *(u32 *)(_perfCurFrame + 0x1010 + *(u32 *)(_perfCurFrame + 0xC) * 4);
    s64 now = OSGetTime();
    *(f32 *)(_perfCurFrame + 0x10 + *(u32 *)(_perfCurFrame + 0xC) * 4) =
        __cvt_sll_flt(now - *(s64 *)_perfCurFrame) /
        (f32)(*(volatile u32 *)0x800000F8 / 240);
    *(u32 *)(_perfCurFrame + 0x1010 + *(u32 *)(_perfCurFrame + 0xC) * 4) = color;
    *(u32 *)(_perfCurFrame + 0xC) += 1;
    return previous;
}

void GSgfxPerfbarGPUEnd__Fv(void)
{
    if (*(u32 *)(_perfCurFrame + 0x201C) < 0x40) {
        s64 now = OSGetTime();
        f32 elapsed = __cvt_sll_flt(now - *(s64 *)(_perfCurFrame + 0x2010));
        *(f32 *)(_perfCurFrame + 0x2020 + *(u32 *)(_perfCurFrame + 0x201C) * 4) =
            elapsed / (f32)(*(volatile u32 *)0x800000F8 / 240);
        *(u32 *)(_perfCurFrame + 0x2120 + *(u32 *)(_perfCurFrame + 0x201C) * 4) = 0;
        *(u32 *)(_perfCurFrame + 0x201C) += 1;
    }
    s64 now = OSGetTime();
    f32 elapsed = __cvt_sll_flt(now - *(s64 *)(_perfCurFrame + 0x2010));
    *(f32 *)(_perfCurFrame + 0x2018) = elapsed / (f32)(*(volatile u32 *)0x800000F8 / 240);
    memcpy(_perfLastFrame + 0x2010, _perfCurFrame + 0x2010, 0x210);
    memset(_perfCurFrame + 0x2010, 0, 0x210);
}

void GSgfxPerfbarCPUEnd__Fv(void)
{
    if (*(u32 *)(_perfCurFrame + 0xC) < 0x400) {
        s64 now = OSGetTime();
        f32 elapsed = __cvt_sll_flt(now - *(s64 *)_perfCurFrame);
        *(f32 *)(_perfCurFrame + 0x10 + *(u32 *)(_perfCurFrame + 0xC) * 4) =
            elapsed / (f32)(*(volatile u32 *)0x800000F8 / 240);
        *(u32 *)(_perfCurFrame + 0x1010 + *(u32 *)(_perfCurFrame + 0xC) * 4) = 0;
        *(u32 *)(_perfCurFrame + 0xC) += 1;
    }
    s64 now = OSGetTime();
    f32 elapsed = __cvt_sll_flt(now - *(s64 *)_perfCurFrame);
    *(f32 *)(_perfCurFrame + 8) = elapsed / (f32)(*(volatile u32 *)0x800000F8 / 240);
    memcpy(_perfLastFrame, _perfCurFrame, 0x2010);
    memset(_perfCurFrame, 0, 0x2010);
    _perfDListSize = 0;
    if (_perfFullStarted == 1) {
        PERFEndFrame();
        PERFStopAutoSampling();
        _perfFullStarted = 0;
        if (_perfRenderMode == 2) {
            GSgfxTokenWaitForClearAndReset((u16 *)&_perfDListToken);
            if (_perfDisplayList == 0) {
                _perfDisplayList = (u32)GSmemAllocAlign(0x8000, 0x20);
                DCFlushRange((void *)_perfDisplayList, 0x8000);
            }
            GXBeginDisplayList((void *)_perfDisplayList, 0x8000);
            GXResetWriteGatherPipe();
            PERFDumpScreen();
            GXFlush();
            _perfDListSize = GXEndDisplayList();
        }
    }
}

void GSgfxPerfbarInit__FUc(u8 frameCount)
{
    _perfFrameCount = frameCount;
    if (_perfFrameCount == 0) _perfFrameCount = 1;
    _perfPixelSkip = 600.0f / _perfFrameCount;
    memset(_perfLastFrame, 0, sizeof(_perfLastFrame));
    memset(_perfCurFrame, 0, sizeof(_perfCurFrame));
    _perfPeakCPU = 0.0f;
    _perfPeakCPUTimer = 0;
    _perfPeakGPUTimer = 0;
    _perfUpdateTime = 0.0f;
    _perfUpdateFPS = 0.0f;
    _perfUpdateCount = 0;
    PERFInit(60, 1, 1, GSmemAlloc, GSmemFree, _perfRestoreGPU__Fv);
    PERFSetDrawBWBarKey(1);
    GSgfxTokenSetDrawSyncCBFunc__FPFPFUs_v_v(PERFSetDrawSyncCallback);
    _perfPERFMtx[0][0] = 0.0f;
    _perfPERFMtx[0][1] = 0.0f;
    _perfPERFMtx[0][2] = 0.0f;
    _perfPERFMtx[0][3] = 0.0f;
    _perfPERFMtx[1][0] = 0.0f;
    _perfPERFMtx[1][1] = 0.0f;
    _perfPERFMtx[1][2] = 0.0f;
    _perfPERFMtx[1][3] = 0.0f;
    _perfPERFMtx[2][0] = 0.0f;
    _perfPERFMtx[2][1] = 0.0f;
    _perfPERFMtx[2][2] = 0.0f;
    _perfPERFMtx[2][3] = 0.0f;
    _perfPERFMtx[3][0] = 0.0f;
    _perfPERFMtx[3][1] = 0.0f;
    _perfPERFMtx[3][2] = 0.0f;
    _perfPERFMtx[3][3] = 0.0f;
    _perfPERFMtx[0][0] = 0.003125f;
    _perfPERFMtx[1][1] = 0.00416667f;
    _perfPERFMtx[2][2] = 1.0f;
    _perfPERFMtx[3][3] = 1.0f;
    _perfPERFMtx[0][3] = -0.95f;
    _perfPERFMtx[1][3] = -0.6250007f;
    _perfDisplayList = 0;
    _perfDListSize = 0;
    _perfFullStarted = 0;
    _perfDListToken = 0;
    s64 time = OSGetTime();
    *(s64 *)_perfCurFrame = time;
    *(u32 *)(_perfCurFrame + 0xC) = 0;
    if (_perfRenderMode == 2) {
        PERFStartFrame();
        PERFStartAutoSampling(1.0f);
        _perfFullStarted = 1;
    }
    GSgfxPerfbarGPUStart__Fv();
}
void GSgfxPerfbarRender__FP10GSgfxLayer(GSgfxLayer *layer)
{
    if (_perfRenderMode == 0) return;
    s64 startTime = OSGetTime();
    u32 *last = (u32 *)_perfLastFrame;
    f32 cpu = *(f32 *)(_perfLastFrame + 8) + *(f32 *)(_perfLastFrame + 0x2220);
    *(f32 *)(_perfLastFrame + 8) = cpu;
    if (cpu > _perfPeakCPU || --_perfPeakCPUTimer < 0) {
        _perfPeakCPU = cpu;
        _perfPeakCPUTimer = 60;
    }
    f32 gpu = *(f32 *)(_perfLastFrame + 0x2018);
    if (gpu > _perfPeakGPU || --_perfPeakGPUTimer < 0) {
        _perfPeakGPU = gpu;
        _perfPeakGPUTimer = 60;
    }
    if (--_perfUpdateCount < 0) {
        f64 updateTime = GSgfxVideoGetLastRenderTime();
        _perfUpdateTime = (f32)updateTime;
        if (_perfUpdateTime > *(f32 *)__float_epsilon) {
            _perfUpdateFPS = 0.1f + (f32)GSgfxVideoGetVsyncRate() / _perfUpdateTime;
            if (_perfUpdateFPS > 60.0f) _perfUpdateFPS = 60.0f;
        } else {
            _perfUpdateFPS = 0.0f;
        }
        _perfUpdateCount = 6;
    }

    GSprimSetRenderLayer__FP10GSgfxLayer(layer);
    GSprimSetQuadVertexOrder(0);
    GSprimSetLineWidth(1.0f);
    GSprimSetTextSize(10.0f, 10.0f);
    GSprimSetTextWidth(1.0f);
    layer->unk1644 = 1;
    layer->unk1648 = 4;
    layer->unk164C = 5;
    layer->unk1650 = 5;
    layer->unk170C |= 1;
    layer->unk16A8 |= 0x40;
    layer->unk17C4 |= 1;
    layer->unk1760 |= 0x40;
    f32 projection[16];
    GSmtx44Ortho(projection, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    layer->unkD54 = 1;
    layer->unkD58 = projection[0];
    layer->unkD5C = projection[3];
    layer->unkD60 = projection[5];
    layer->unkD64 = projection[7];
    layer->unkD68 = projection[10];
    layer->unkD6C = projection[11];
    SpriteMatrixStack *stack = (SpriteMatrixStack *)layer->unk19A0;
    memcpy((u8 *)stack->frame + 4, mtxIdent, 0x30);
    stack->frame->flags |= 1;
    layer->unk1684 = 0.0f;
    layer->unk1688 = 30000.0f;
    if (layer->unk16A7 != 0) {
        if (layer->unk16A6 != 0) {
            layer->unk170C |= 0x100;
            layer->unk17C4 |= 0x100;
        }
        layer->unk170C |= 0x40;
        layer->unk16A8 |= 0x40;
        layer->unk17C4 |= 0x40;
        layer->unk1760 |= 0x40;
    }
    layer->unk16AC |= 0x20;
    layer->unk16A8 |= 1;
    layer->unk1764 |= 0x20;
    layer->unk1760 |= 1;
    layer->unk1656 = 1;
    layer->unk1657 = 0;
    layer->unk1658 = 0;
    layer->unk170C |= 4;
    layer->unk16A8 |= 0x40;
    layer->unk17C4 |= 4;
    layer->unk1760 |= 0x40;
    layer->unk165C = 0;
    layer->unk1660 = 3;
    layer->unk170C |= 8;
    layer->unk16A8 |= 0x40;
    layer->unk17C4 |= 8;
    layer->unk1760 |= 0x40;
    layer->unk1664 = 7;
    layer->unk1670 = 0;
    layer->unk1668 = 0;
    layer->unk166C = 7;
    layer->unk1671 = 0;
    layer->unk1672 = 1;
    layer->unk170C |= 0x10;
    layer->unk16A8 |= 0x40;
    layer->unk17C4 |= 0x10;
    layer->unk1760 |= 0x40;
    layer->unkD8C = 0;
    layer->unk16B8 |= 2;
    layer->unk16A8 |= 2;
    layer->unk1770 |= 2;
    layer->unk1760 |= 2;
    layer->unkD90 = 1;
    layer->unk16B8 |= 4;
    layer->unk16A8 |= 2;
    layer->unk1770 |= 4;
    layer->unk1760 |= 2;
    GXColor background = {0x20, 0x20, 0x20, 0xC0};
    GSprimDraw2DQuadWH(10.0f, 420.0f, 620.0f, 40.0f, &background);

    f32 x = 20.0f;
    for (s32 i = 0; i < _perfFrameCount; ++i) {
        u32 rgb;
        if ((u32)i < (u32)(GSgfxVideoGetLockFrameRate() + 1)) rgb = 0x00FF00;
        else if (i >= 3) rgb = 0xFF0000;
        else rgb = 0xFFFF00;
        _perfDrawColor.r = (u8)(rgb >> 16);
        _perfDrawColor.g = (u8)(rgb >> 8);
        _perfDrawColor.b = (u8)rgb;
        _perfDrawColor.a = 0xFF;
        f32 nextX = x + _perfPixelSkip;
        GSprimDraw2DHLine(x, nextX, 455.0f, &_perfDrawColor);
        GSprimDraw2DVLine(x, 450.0f, 455.0f, &_perfDrawColor);
        GSprimDraw2DVLine(nextX, 450.0f, 455.0f, &_perfDrawColor);
        x = nextX;
    }

    f32 peak = *(f32 *)(_perfLastFrame + 8);
    if (gpu > peak) peak = gpu;
    _perfDrawColor.r = 0; _perfDrawColor.g = 0x80; _perfDrawColor.b = 0x80; _perfDrawColor.a = 0xFF;
    GSprimDraw2DQuadWH(446.0f, _perfPixelSkip * (f32)(s32)(0.9999f + peak), 5.0f, _perfPixelSkip, &_perfDrawColor);
    _perfDrawColor.r = 0; _perfDrawColor.g = 0xFF; _perfDrawColor.b = 0xFF; _perfDrawColor.a = 0xFF;
    GSprimDraw2DQuadWH(420.0f, 446.0f, _perfPixelSkip * gpu, 5.0f, &_perfDrawColor);

    f32 prior = _perfPixelSkip * *(f32 *)(_perfLastFrame + 0x2020);
    u32 count = last[0x201C / 4];
    for (u32 i = 1; i < count && i < 0x40; ++i) {
        f32 at = _perfPixelSkip * *(f32 *)(_perfLastFrame + 0x2020 + i * 4);
        if ((s32)(at - prior) >= 1) {
            u32 color = *(u32 *)(_perfLastFrame + 0x2120 + i * 4);
            _perfDrawColor.r = (u8)(color >> 16);
            _perfDrawColor.g = (u8)(color >> 8);
            _perfDrawColor.b = (u8)color;
            _perfDrawColor.a = 0xFF;
            GSprimDraw2DQuadWH(20.0f + prior, 446.0f, at - prior, 5.0f, &_perfDrawColor);
        }
        prior = at;
        if (at > 640.0f) break;
    }

    _perfDrawColor.r = 0xFF; _perfDrawColor.g = 0xFF; _perfDrawColor.b = 0xFF; _perfDrawColor.a = 0xFF;
    GSprimDraw2DQuadWH(420.0f, 440.0f, _perfPixelSkip * *(f32 *)(_perfLastFrame + 8), 5.0f, &_perfDrawColor);
    prior = _perfPixelSkip * *(f32 *)(_perfLastFrame + 16);
    count = last[3];
    for (u32 i = 1; i < count && i < 0x400; ++i) {
        f32 at = _perfPixelSkip * *(f32 *)(_perfLastFrame + 16 + i * 4);
        if ((s32)(at - prior) >= 1) {
            u32 color = *(u32 *)(_perfLastFrame + 0x1010 + i * 4);
            _perfDrawColor.r = (u8)(color >> 16);
            _perfDrawColor.g = (u8)(color >> 8);
            _perfDrawColor.b = (u8)color;
            _perfDrawColor.a = 0xFF;
            GSprimDraw2DQuadWH(20.0f + prior, 444.0f, at - prior, 5.0f, &_perfDrawColor);
        }
        prior = at;
        if (at > 640.0f) break;
    }

    s32 bp, cp;
    GSgfxGPUGetBPTick__FPlPl(&bp, &cp);
    if (bp == -1 && cp == -1) {
        GSprimWriteStr(30.0f, 425.0f,
            "|00ff00CUR: |ffffff%2.3f |00ffff%2.3f  |00ff00PK: |ffffff%2.3f |00ffff%2.3f  |00ff00VUPD: |ffffff%1.3f  |ffff00%2.1f FPS",
            *(f32 *)(_perfLastFrame + 8), gpu, _perfPeakCPU, _perfPeakGPU, _perfUpdateTime, _perfUpdateFPS);
    } else {
        u32 ticks = *(volatile u32 *)0x800000F8 / 500000;
        GSprimWriteStr(30.0f, 425.0f, "|ffffff%d    |ffff00%d", (u32)(bp * 8) / ticks, (u32)(cp * 8) / ticks);
    }
    if (_perfRenderMode == 2 && _perfDListSize != 0) {
        FlushState__10GSgfxLayerFv(layer);
        PERFPreDraw();
        GXSetProjection(_perfPERFMtx, GX_ORTHOGRAPHIC);
        GXCallDisplayList((void *)_perfDisplayList, _perfDListSize);
        PERFPostDraw();
        InvalidateState__10GSgfxLayerFv(layer);
        _perfDListToken = tokenMark__10GSgfxLayerFv(layer);
    }
    s64 endTime = OSGetTime();
    f32 drawTime = __cvt_sll_flt(endTime - startTime) / (f32)(*(volatile u32 *)0x800000F8 / 240);
    *(f32 *)(_perfLastFrame + 0x2220) = drawTime;
    *(f32 *)(_perfCurFrame + 0x2220) = drawTime;
}

}
