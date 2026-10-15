#include "game/pxdvs/app/fade/fade_effect.hpp"
#include <libc/stddef.h>

#include "game/pxdvs/GSAPI/GSmath/GSvec.hpp"
#include "game/pxdvs/GSAPI/GStexture/GStexture.hpp"
#include "game/pxdvs/GSAPI/GSres/GSres.hpp"
#include "game/pxdvs/GSAPI/GSmemman/GSmemman.hpp"
extern "C" void* memcpy(void*, const void*, unsigned long);


typedef f32 FadeMtx[3][4];
extern "C" {
void PSMTXTrans(FadeMtx, f32, f32, f32);
void PSMTXScale(FadeMtx, f32, f32, f32);
void PSMTXRotRad(FadeMtx, char, f32);
void PSMTXConcat(const FadeMtx, const FadeMtx, FadeMtx);
void PSMTXTransApply(const FadeMtx, FadeMtx, f32, f32, f32);
void PSMTXMultVec(const FadeMtx, const GSvec*, GSvec*);
void GSlerpGetLinearInterpolationVector(GSvec*, const GSvec*, const GSvec*, f32);
}

// The graphics module is still unrecovered. These declarations model only the
// storage and member interfaces used by fade effects; no virtual dispatch exists.
enum GSgfxLayerID { GS_SHAPE_LAYER_DEFAULT = 2, GS_SHAPE_LAYER_ALTERNATE = 4 };
struct GSmtx;
enum GSgfxTgenFunc { FadeTgenFuncDummy };
enum GSgfxTgenSrc { FadeTgenSrcDummy };
struct GSgfxVF { u8 storage[0x440]; };
struct FadeMatrixState { u32 flags; f32 matrix[3][4]; };
struct FadeMatrixSlot { u32 reserved; FadeMatrixState* state; };
struct FadeLayerConfigView { u8 prefix[0x1818]; u8 configs[2][0xbc]; };
struct GSgfxLayer {
    u8 reserved0[0xD54];
    s32 fieldD54;
    f32 fieldD58;
    f32 fieldD5C;
    f32 fieldD60;
    f32 fieldD64;
    f32 fieldD68;
    f32 fieldD6C;
    u8 reservedD70[0x1C];
    s32 fieldD8C;
    u8 reservedD90[0x8B4];
    s32 field1644;
    s32 field1648;
    s32 field164C;
    s32 field1650;
    u8 reserved1654[0x2];
    u8 field1656;
    u8 field1657;
    u8 field1658;
    u8 reserved1659[0x3];
    u8 field165C;
    u8 reserved165D[0x3];
    s32 field1660;
    s32 field1664;
    s32 field1668;
    s32 field166C;
    u8 field1670;
    u8 field1671;
    u8 field1672;
    u8 reserved1673[0x11];
    f32 field1684;
    f32 field1688;
    u8 reserved168C[0x1A];
    u8 field16A6;
    u8 field16A7;
    s32 field16A8;
    s32 field16AC;
    u8 reserved16B0[0x8];
    s32 field16B8;
    u8 reserved16BC[0x50];
    s32 field170C;
    u8 reserved1710[0x2C];
    s32 field173C;
    GStexture* field1740;
    u8 reserved1744[0x1C];
    s32 field1760;
    s32 field1764;
    u8 reserved1768[0x8];
    s32 field1770;
    u8 reserved1774[0x50];
    s32 field17C4;
    u8 reserved17C8[0x2C];
    s32 field17F4;
    GStexture* field17F8;
    u8 reserved17FC[0x194];
    void* field1990;
    s32 field1994;
    s32 field1998;
    u8 reserved199C[0x4];
    FadeMatrixSlot* field19A0;
    void tgenFunc(u8, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx*, bool, GSmtx*);
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

extern "C" {
void GSmemFree(void*);
void fadeEffectDokuStop();
s32 HSD_Rand();
f32 HSD_Randf();
void GSgfxVideoSetLockFrameRate(bool);
void GSgfxVFInit(GSgfxVF*);
void GSgfxVFCreate(GSgfxVF*);
void GSgfxVFFree(GSgfxVF*);
u8 GSgfxVFIsUsed(GSgfxVF*);
void GSgfxVFSetElement(GSgfxVF*, s32, s32, s32, u8);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, u8, u8, s32, s32, s32, s32, s32);
GSgfxLayer* GSgfxLayerFindByID(GSgfxLayerID);
void GSmtx44Ortho(f32 (*)[4], f32, f32, f32, f32, f32, f32);
extern f32 mtxIdent[3][4];
void GSgfxBeginBackFBCapture(GStexture*, s32 (*)(GStexture*, unsigned long, void*), void*);
void GSgfxEndBackFBCapture(GStexture*);
void fadeFluidInit(s32, s32, f32, f32, f32, f32);
void fadeFluidSetShock(GSvec*, f32);
void fadeFluidSetShockSecond(GSvec*, f32);
void fadeFluidQuit();
void fadeFluidEvaluate();
void fadeFluidDisp(GStexture*, f32, f32);
unsigned long timeGetLastFrameTime();
}

struct FADE_EFFECT_WORK {
    GStexture* ballTexture; GStexture* secondTexture;
    u16 frame; u16 counter; u16 direction; u16 state;
    f32 rotationStep; f32 rotation; f32 distanceStep;
};
struct FADE_EFFECT_BALL {
    GSvec position; f32 rotation; s32 alpha;
    FADE_EFFECT_BALL() {}
};
struct FADE_EFFECT_BOUND { s16 x, y, rotation, speed, state; };
struct FadeGridPoint { s16 x, y; };
struct FadeUV { f32 u, v; };
struct FADE_DISTORTION_WORK {
    s32 columns, rows, width, height;
    FadeGridPoint* points; FadeUV* uv;
};
typedef char FadeWorkSize[sizeof(FADE_EFFECT_WORK) == 0x1c ? 1 : -1];
typedef char FadeBallSize[sizeof(FADE_EFFECT_BALL) == 0x14 ? 1 : -1];
typedef char FadeBoundSize[sizeof(FADE_EFFECT_BOUND) == 0xa ? 1 : -1];
typedef char FadeGridSize[sizeof(FADE_DISTORTION_WORK) == 0x18 ? 1 : -1];
typedef char FadeVFSize[sizeof(GSgfxVF) == 0x440 ? 1 : -1];

// These offsets are the graphics prefix used by the original fade renderer.
typedef char FadeLayerOffsetD54[offsetof(GSgfxLayer, fieldD54) == 0xd54 ? 1 : -1];
typedef char FadeLayerOffsetD58[offsetof(GSgfxLayer, fieldD58) == 0xd58 ? 1 : -1];
typedef char FadeLayerOffset1644[offsetof(GSgfxLayer, field1644) == 0x1644 ? 1 : -1];
typedef char FadeLayerOffset1656[offsetof(GSgfxLayer, field1656) == 0x1656 ? 1 : -1];
typedef char FadeLayerOffset1660[offsetof(GSgfxLayer, field1660) == 0x1660 ? 1 : -1];
typedef char FadeLayerOffset1684[offsetof(GSgfxLayer, field1684) == 0x1684 ? 1 : -1];
typedef char FadeLayerOffset16A8[offsetof(GSgfxLayer, field16A8) == 0x16a8 ? 1 : -1];
typedef char FadeLayerOffset170C[offsetof(GSgfxLayer, field170C) == 0x170c ? 1 : -1];
typedef char FadeLayerOffset1740[offsetof(GSgfxLayer, field1740) == 0x1740 ? 1 : -1];
typedef char FadeLayerOffset17C4[offsetof(GSgfxLayer, field17C4) == 0x17c4 ? 1 : -1];
typedef char FadeLayerOffset17F8[offsetof(GSgfxLayer, field17F8) == 0x17f8 ? 1 : -1];
typedef char FadeLayerOffset1990[offsetof(GSgfxLayer, field1990) == 0x1990 ? 1 : -1];
typedef char FadeLayerOffset1994[offsetof(GSgfxLayer, field1994) == 0x1994 ? 1 : -1];
typedef char FadeLayerOffset19A0[offsetof(GSgfxLayer, field19A0) == 0x19a0 ? 1 : -1];
typedef char FadeFADEEFFECTWORKOffset10[offsetof(FADE_EFFECT_WORK, rotationStep) == 0x10 ? 1 : -1];
typedef char FadeFADEEFFECTBALLOffset10[offsetof(FADE_EFFECT_BALL, alpha) == 0x10 ? 1 : -1];
typedef char FadeFADEEFFECTBOUNDOffset6[offsetof(FADE_EFFECT_BOUND, speed) == 0x6 ? 1 : -1];
typedef char FadeFADEDISTORTIONWORKOffset10[offsetof(FADE_DISTORTION_WORK, points) == 0x10 ? 1 : -1];
typedef char FadeFadeMatrixSlotOffset4[offsetof(FadeMatrixSlot, state) == 0x4 ? 1 : -1];
typedef char FadeFadeLayerConfigViewOffset1818[offsetof(FadeLayerConfigView, configs) == 0x1818 ? 1 : -1];

typedef bool (*FadeEffectCallback)(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern "C" void fadeSetFunctionOnly(FadeEffectCallback);
extern bool fadeEffectHookFunction_virtual_hexa_decay(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_trainer_second(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_slide_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_four_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_distortion_strip_yoko(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_distortion_strip_tate(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_distortion_yoko(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_distortion_zoom_out(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_distortion_zoom_in(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_blur_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_tear_off(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_ball_second(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_bound_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_dist_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_boss_second(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_distortion(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_Doku(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_trainer(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_carde(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
extern bool fadeEffectHookFunction_ball(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_tate(GSgfxLayerID, bool, f32, f32, f32, f32, void*);
static bool fadeEffectHookFunction_yoko(GSgfxLayerID, bool, f32, f32, f32, f32, void*);

#define FADE_RANDOM(range) (((unsigned long)(HSD_Rand() << 16) | HSD_Rand()) % (range))
#pragma force_active on
static FADE_EFFECT_WORK _fadeEffectWork;
static FADE_EFFECT_BALL _fadeEffectBall[2][12];
static GSgfxVF _fadeEffectTrainer_vf;
static u8 _fadeEffectPulse[0xc0];
static u8 _fadeEffectBlock[0x40];
static u8 _fadeEffectLines[0x80];
static FADE_EFFECT_BOUND _fadeEffectBound[16];
static FADE_DISTORTION_WORK _fadeDistortionWork;
static void* _fadeHexaLine[2] = { 0, 0 };
static u8 _fadeEffectFirstFlag;
static void* _fadeHexaRibbon;
static s32 _fadeHexaRibbonNum;
static GStexture* _fadeHexaTexture;
static GSgfxVF* _fadeHexaNoiseVF;
static f32 _fadeHexaDecayTime;
struct FadeTearOff { s16 x, y; };
static FadeTearOff _fadeTearOffWork;

static void _fadeEffect_AdjustParms();
static unsigned long _fadeEffectGetRandom(unsigned long);
static s32 _myBackFB(GStexture*, unsigned long, void*);
static void _fadeEffectEnd(GSgfxLayer*);
static void _fadeEffectStartSprites(GSgfxLayer*);
static void _fadeEffectStartTexture(GSgfxLayer*, GStexture*);
static void _fadeEffectMaskFunction(GSgfxLayer*, f32);

extern "C" void fadeEffectHookFunction_virtual_end_Init();
extern "C" void fadeEffectHookFunction_trainer_second_Init();
extern "C" void fadeEffectHookFunction_slide_ball_Init();
extern "C" void fadeEffectHookFunction_four_ball_Init();
extern "C" void fadeEffectHookFunction_distortion_strip_yoko_Init();
extern "C" void fadeEffectHookFunction_distortion_strip_tate_Init();
extern "C" void fadeEffectHookFunction_dist_yoko_Init();
extern "C" void fadeEffectHookFunction_dist_zoom_out_Init();
extern "C" void fadeEffectHookFunction_dist_zoom_in_Init();
extern "C" void fadeEffectHookFunction_blur_ball_Init();
extern "C" void fadeEffectHookFunction_tear_off_Init();
extern "C" void fadeEffectHookFunction_ball_second_Init();
extern "C" void fadeEffectHookFunction_bound_ball_Init();
extern "C" void fadeEffectHookFunction_dist_ball_Init();
extern "C" void fadeEffectHookFunction_boss_second_Init();
extern "C" void fadeEffectHookFunction_distortion_Init();
extern "C" void fadeEffectHookFunction_Doku_Init();
extern "C" void fadeEffectHookFunction_trainer_Init();
extern "C" void fadeEffectHookFunction_fadein_Init();
extern "C" void fadeEffectHookFunction_fadeout_in_Init();
extern "C" void fadeEffectHookFunction_carde_Init();
extern "C" void fadeEffectHookFunction_boss_Init();
extern "C" void fadeEffectHookFunction_yoko_or_tate_or_ball_Init();
extern "C" void fadeEffectHookFunction_ball_Init();
extern "C" void fadeEffectHookFunction_yoko_or_tate_Init();
extern "C" void fadeEffectHookFunction_tate_Init();
extern "C" void fadeEffectHookFunction_yoko_Init();
static void _fadeVirtualHexaDecayQuit();
static void _fadeDistortionStripQuit();
static void _fadeDistortionStripInit(int columns, int rows);
static void _fadeEffectFunction_trainer_second_FirstInit();
static void _fadeDistortionQuit();
static void _fadeDistortionDo(unsigned long range);
static void _fadeDistortionDoAverage(unsigned long range);
static void _fadeDistortionDoSecond(unsigned long range, bool inward);
static void _fadeDistortionInit();
static void _fadeEffectFourBallInit();
static void _disp_four_ball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha);
static void _fadeBlurBallQuit();
static void _fadeBlurBallInit();
static void _fadeDistBallQuit();
static void _fadeDistBallInit();
static void _fadeEffectSlideBallInit();
static void _fadeEffectBoundBallInit();
static void _disp_bound_ball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha);
static void _disp_dist_ball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha);
static void _disp_blur_ball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha);
static void _fadeTearOffDraw(GSgfxLayer* layer, u8 alpha, int shift);
static void _fadeEffectFunction_trainer_FirstInit(GStexture* arg0);
static bool fadeEffectHookFunction_fadein(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void*);
static bool fadeEffectHookFunction_fadeout_in(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque);
static void _fadeEffectFunction_boss_FirstInit_second();
static bool fadeEffectHookFunction_boss(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void* opaque);
static void _fadeEffectFunction_boss_FirstInit();
static void _fadeEffectBallSecondQuit();
static void _fadeEffectBallSecondInit();
static void _dispball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha);
static void _fadeEffectFunction_ball_FirstInit();
static void _fadeEffectFunction_UDLR_FirstInit(GStexture* arg0, u16 arg1);
static void _fadeEffectSnapshotFadeFunction(GSgfxLayer* layer, GStexture* texture, GSvec* center, f32 scale, f32 angle, f32 progress, f32 opacity);
static void _fadeEffectMaskFunction(GSgfxLayer* layer, f32 amount);
static void _fadeEffectSnapshotRotate(GSgfxLayer* layer, GStexture* texture, GSvec* center, f32 scale, GSvec* pivot, f32 angle, f32 progress, f32 opacity);
static void _fadeEffectSnapshotTex(GSgfxLayer* layer, GStexture* texture, GSvec* center, f32 u0, f32 v0, f32 u1, f32 v1, f32 scaleY, f32 angle, f32 progress, f32 opacity);
static void _fadeEffectStartSprites(GSgfxLayer* arg0);
static void _fadeEffectStartTexture(GSgfxLayer* arg0, GStexture* arg1);
static unsigned long _fadeEffectGetRandom(unsigned long range);
extern "C" void fadeEffectInit();
static bool _fadeEffectFunction_UDLR_Main(GSgfxLayer* layer, bool active, f32 elapsed, f32 duration, f32, f32, GStexture* texture);
static bool fadeEffectHookFunction_tate(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque);
static bool fadeEffectHookFunction_yoko(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque);

extern "C" void fadeEffectHookFunction_virtual_end_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_virtual_hexa_decay); }

extern "C" void fadeEffectHookFunction_trainer_second_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_trainer_second); }

extern "C" void fadeEffectHookFunction_slide_ball_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_slide_ball); }

extern "C" void fadeEffectHookFunction_four_ball_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_four_ball); }

extern "C" void fadeEffectHookFunction_distortion_strip_yoko_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_distortion_strip_yoko); }

extern "C" void fadeEffectHookFunction_distortion_strip_tate_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_distortion_strip_tate); }

extern "C" void fadeEffectHookFunction_dist_yoko_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_distortion_yoko); }

extern "C" void fadeEffectHookFunction_dist_zoom_out_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_distortion_zoom_out); }

extern "C" void fadeEffectHookFunction_dist_zoom_in_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_distortion_zoom_in); }

extern "C" void fadeEffectHookFunction_blur_ball_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_blur_ball); }

extern "C" void fadeEffectHookFunction_tear_off_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_tear_off); }

extern "C" void fadeEffectHookFunction_ball_second_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_ball_second); }

extern "C" void fadeEffectHookFunction_bound_ball_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_bound_ball); }

extern "C" void fadeEffectHookFunction_dist_ball_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_dist_ball); }

extern "C" void fadeEffectHookFunction_boss_second_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_boss_second); }

extern "C" void fadeEffectHookFunction_distortion_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_distortion); }

extern "C" void fadeEffectHookFunction_Doku_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_Doku); }

extern "C" void fadeEffectHookFunction_trainer_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_trainer); }

extern "C" void fadeEffectHookFunction_fadein_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_fadein); }

extern "C" void fadeEffectHookFunction_fadeout_in_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_fadeout_in); }

extern "C" void fadeEffectHookFunction_carde_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_carde); }

extern "C" void fadeEffectHookFunction_boss_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_boss); }

extern "C" void fadeEffectHookFunction_yoko_or_tate_or_ball_Init() {
    switch ((s32)_fadeEffectGetRandom(3)) {
    case 0: fadeSetFunctionOnly(fadeEffectHookFunction_yoko); break;
    case 1: fadeSetFunctionOnly(fadeEffectHookFunction_tate); break;
    case 2:
    default: fadeSetFunctionOnly(fadeEffectHookFunction_ball); break;
    }
}

extern "C" void fadeEffectHookFunction_ball_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_ball); }

extern "C" void fadeEffectHookFunction_yoko_or_tate_Init() {
    switch ((s32)_fadeEffectGetRandom(2)) {
    case 0: fadeSetFunctionOnly(fadeEffectHookFunction_yoko); break;
    case 1:
    default: fadeSetFunctionOnly(fadeEffectHookFunction_tate); break;
    }
}

extern "C" void fadeEffectHookFunction_tate_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_tate); }

extern "C" void fadeEffectHookFunction_yoko_Init() { fadeSetFunctionOnly(fadeEffectHookFunction_yoko); }

static void _fadeVirtualHexaDecayQuit() {
    GSmemFree(_fadeHexaLine[0]); _fadeHexaLine[0] = 0;
    GSmemFree(_fadeHexaLine[1]); _fadeHexaLine[1] = 0;
    if (_fadeHexaRibbon) { GSmemFree(_fadeHexaRibbon); _fadeHexaRibbon = 0; }
    _fadeHexaRibbonNum = 0;
    if (_fadeHexaTexture) { GStextureFree(_fadeHexaTexture); _fadeHexaTexture = 0; }
    if (_fadeHexaNoiseVF) { GSmemFree(_fadeHexaNoiseVF); _fadeHexaNoiseVF = 0; }
}

static void _fadeDistortionStripQuit() {
    if ((u32) _fadeDistortionWork.points != 0U) {
        GSmemFree(_fadeDistortionWork.points);
        _fadeDistortionWork.points = 0U;
    }
    if ((u32) _fadeDistortionWork.uv != 0U) {
        GSmemFree(_fadeDistortionWork.uv);
        _fadeDistortionWork.uv = 0U;
    }
}

static void _fadeDistortionStripInit(int columns, int rows) {
    s32 count = columns * rows;
    _fadeDistortionWork.columns = columns;
    _fadeDistortionWork.rows = rows;
    _fadeDistortionWork.width = 640;
    _fadeDistortionWork.height = 480;
    _fadeDistortionWork.points = (FadeGridPoint*)GSmemAllocAlign(count * 4, 32);
    FadeUV* uv = (FadeUV*)GSmemAllocAlign(count * 8, 32);
    _fadeDistortionWork.uv = uv;
    f32 dx = 640.0f / (columns - 1);
    f32 dy = 480.0f / (rows - 1);
    f32 du = 1.0f / (columns - 1);
    f32 dv = 1.0f / (rows - 1);
    if (_fadeDistortionWork.points && uv) {
        FadeGridPoint* points = _fadeDistortionWork.points;
        for (s32 y = 0; y < rows; ++y) {
            FadeGridPoint* point = points;
            FadeUV* coord = uv;
            for (s32 x = 0; x < columns; ++x) {
                point->x = (s16)(dx * x);
                point->y = (s16)(dy * y);
                if (x == columns - 1 && rows > 2) ++point->x;
                else if (y == rows - 1 && columns > 2) ++point->y;
                coord->u = du * x;
                coord->v = dv * y;
                ++point; ++points; ++uv; ++coord;
            }
        }
        u16 direction = ((HSD_Rand() << 16) | HSD_Rand()) & 3;
        _fadeEffectWork.state = 0;
        _fadeEffectWork.direction = direction;
        _fadeEffectWork.frame = 0;
    }
}

static void _fadeEffectFunction_trainer_second_FirstInit() {
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f3;

    _fadeEffectWork.ballTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.state = 0;
    if ((u32) (((HSD_Rand() << 0x10) | HSD_Rand()) & 1) != 0) {
        var_f3 = 1.0f;
    } else {
        var_f3 = -1.0f;
    }
    temp_f2 = 0.1f * var_f3;
    temp_f1 = 24.0f * var_f3;
    _fadeEffectWork.rotationStep = temp_f2;
    _fadeEffectWork.distanceStep = temp_f1;
    _fadeEffectWork.rotation = 0.0f;
    GSgfxVFInit(&_fadeEffectTrainer_vf);
    GSgfxVFCreate(&_fadeEffectTrainer_vf);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 9, 1, 4, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 0xB, 1, 5, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 0xD, 1, 4, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 0xE, 1, 4, 0);
}

static void _fadeDistortionQuit() {
    if ((u32) _fadeDistortionWork.points != 0U) {
        GSmemFree(_fadeDistortionWork.points);
        _fadeDistortionWork.points = 0U;
    }
    if ((u32) _fadeDistortionWork.uv != 0U) {
        GSmemFree(_fadeDistortionWork.uv);
        _fadeDistortionWork.uv = 0U;
    }
}

static void _fadeDistortionInit() {
    _fadeDistortionWork.columns = 40;
    _fadeDistortionWork.rows = 30;
    _fadeDistortionWork.width = 640;
    _fadeDistortionWork.height = 480;
    _fadeDistortionWork.points = (FadeGridPoint*)GSmemAllocAlign(1200 * 4, 32);
    FadeUV* uv = (FadeUV*)GSmemAllocAlign(1200 * 8, 32);
    _fadeDistortionWork.uv = uv;
    if (_fadeDistortionWork.points) {
        if (!uv) return;
        FadeGridPoint* points = _fadeDistortionWork.points;
        s32 y = 0;
        do {
            FadeGridPoint* point = points;
            FadeUV* coord = uv;
            s32 x = 0;
            for (s32 j = 0; j < 40; ++j) {
                point->x = (s16)((640.0f / 39.0f) * x);
                point->y = (s16)((480.0f / 29.0f) * y);
                if (y == 29) ++point->y;
                coord->u = (1.0f / 39.0f) * x;
                coord->v = (1.0f / 29.0f) * y;
                ++points; ++uv; ++point; ++coord; ++x;
            }
            ++y;
        } while (y < 30);
        _fadeEffectWork.direction = 0;
        _fadeEffectWork.frame = 0;
    }
}

static void _fadeEffectFourBallInit() {
    GSvec positions[2];
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.ballTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBD1200);
    FADE_EFFECT_BALL* group = &_fadeEffectBall[0][0];
    GSvec* position = positions;
    s32 i = 0;
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.state = 0;
    _fadeEffectWork.rotationStep = 4.0f;
    _fadeEffectWork.rotation = 0.0f;
    _fadeEffectWork.distanceStep = 64.0f;
    positions[0].param1 = -65.0f;
    positions[0].param2 = 65.0f;
    positions[0].param3 = 0.0f;
    positions[1].param1 = 705.0f;
    positions[1].param2 = 181.66666f;
    positions[1].param3 = 0.0f;
    do {
        FADE_EFFECT_BALL* ball = group;
        s32 fade = 0;
        for (s32 j = 0; j < 3; ++j) {
            f32 x = position->param1;
            f32 y = position->param2;
            ball->position.param1 = x;
            f32 z = position->param3;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 130 - fade;
            ++ball;
            fade += 10;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 130 - fade;
            ++ball;
            fade += 10;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 130 - fade;
            ++ball;
            fade += 10;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 130 - fade;
            ++ball;
            fade += 10;
        }
        ++position;
        group->alpha = 255;
        group += 12;
        ++i;
    } while (i < 2);
    _fadeEffect_AdjustParms();
}

static void _disp_four_ball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha) {
    FadeMtx transform, rotation;
    GSvec point, output;
    point.param1 = scale;
    point.param2 = scale;
    point.param3 = scale;
    f64 dv = scale;
    PSMTXScale(transform, dv, dv, dv);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, transform, transform);
    PSMTXTransApply(transform, transform, center->param1, center->param2, center->param3);
    layer->beginSurface(4);
    point.param1 = -65.0f;
    point.param2 = -65.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 65.0f;
    point.param2 = -65.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = -65.0f;
    point.param2 = 65.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 65.0f;
    point.param2 = 65.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    layer->endSurface();
}

static void _fadeBlurBallQuit() {

}

static void _fadeBlurBallInit() {
    s32 var_r0;
    s32 var_r0_2;

    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.ballTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    if ((u32) (((HSD_Rand() << 0x10) | HSD_Rand()) & 1) != 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    _fadeEffectWork.direction = var_r0;
    if ((u32) (((HSD_Rand() << 0x10) | HSD_Rand()) & 1) != 0) {
        var_r0_2 = 1;
    } else {
        var_r0_2 = 0;
    }
    _fadeEffectWork.state = var_r0_2;
    _fadeEffectWork.rotationStep = 0.1f;
    _fadeEffectWork.distanceStep = 16.0f;
    _fadeEffectWork.rotation = 0.0f;
    _fadeEffect_AdjustParms();
}

static void _fadeDistBallQuit() {
    GSgfxVFFree(&_fadeEffectTrainer_vf);
}

static void _fadeDistBallInit() {
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.ballTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.frame = 1;
    FADE_EFFECT_BOUND* ball = _fadeEffectBound;
    s32 i = 0;
    do {
        ball->x = FADE_RANDOM(640UL);
        ball->y = FADE_RANDOM(240UL);
        ball->rotation = 0;
        ball->speed = (FADE_RANDOM(4UL) * 4) + 4;
        s32 sign = (i % 2 == 0) ? 1 : -1;
        ball->speed *= sign;
        ball->state = 0;
        ++ball; ++i;
    } while (i < 12);
    GSgfxVFInit(&_fadeEffectTrainer_vf);
    GSgfxVFCreate(&_fadeEffectTrainer_vf);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 9, 1, 4, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 11, 1, 5, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 13, 1, 4, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 14, 1, 4, 0);
    _fadeEffect_AdjustParms();
}

static void _fadeEffectSlideBallInit() {
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.ballTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.frame = 0;
    u8 left = FADE_RANDOM(2UL) == 0 ? 1 : 0;
    FADE_EFFECT_BOUND* ball = _fadeEffectBound;
    s16 y = 26;
    s32 i = 0;
    do {
        if (left == 1) {
            ball->x = -FADE_RANDOM(160UL);
            ball->y = y;
            ball->rotation = (360.0f * ball->x) / 166.50441f;
            if (i % 2 == 0) ball->speed = (FADE_RANDOM(5UL) * 2) + 4;
            else ball->speed = (FADE_RANDOM(4UL) * 2) + 8;
        } else {
            ball->x = FADE_RANDOM(160UL) + 640;
            ball->y = y;
            ball->rotation = (360.0f * ball->x) / 166.50441f;
            if (i % 2 == 0) ball->speed = -((FADE_RANDOM(5UL) * 2) + 4);
            else ball->speed = -((FADE_RANDOM(4UL) * 2) + 8);
        }
        ++ball; y += 53; ++i;
    } while (i < 12);
}

static void _disp_slide_ball(GSgfxLayer* layer, f32 x, f32 y, f32 x2, f32 angle, int alpha) {
    FadeMtx transform, rotation;
    GSvec point, output;
    f32 bottom, left, top, right;
    f32 half = 0.5f;
    f32 zero = 0.0f;
    f32 size = 26.0f;
    f32 one = 1.0f;
    top = y - size;
    bottom = size + y;
    left = x - size;
    right = size + x;
    GXPosition2f32(x, top);
    GXColor4u8(255, 255, 255, (u8)(alpha / 5));
    GXTexCoord2f32(half, zero);
    GXPosition2f32(x, bottom);
    GXColor4u8(255, 255, 255, (u8)(alpha / 5));
    GXTexCoord2f32(half, one);
    GXPosition2f32(x2, bottom);
    GXColor4u8(255, 255, 255, 0);
    GXTexCoord2f32(half, one);
    GXPosition2f32(x2, top);
    GXColor4u8(255, 255, 255, 0);
    GXTexCoord2f32(half, zero);
    point.param1 = -x;
    point.param2 = -y;
    point.param3 = 0.0f;
    PSMTXTrans(transform, -x, -y, 0.0f);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, transform, transform);
    point.param1 = x;
    point.param2 = y;
    point.param3 = 0.0f;
    PSMTXTransApply(transform, transform, x, y, 0.0f);
    point.param1 = left;
    point.param2 = top;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    GXPosition2f32(output.param1, output.param2);
    GXColor4u8(255, 255, 255, (u8)alpha);
    GXTexCoord2f32(0.0f, 0.0f);
    point.param1 = right;
    point.param2 = top;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    GXPosition2f32(output.param1, output.param2);
    GXColor4u8(255, 255, 255, (u8)alpha);
    GXTexCoord2f32(1.0f, 0.0f);
    point.param1 = right;
    point.param2 = bottom;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    GXPosition2f32(output.param1, output.param2);
    GXColor4u8(255, 255, 255, (u8)alpha);
    GXTexCoord2f32(1.0f, 1.0f);
    point.param1 = left;
    point.param2 = bottom;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    GXPosition2f32(output.param1, output.param2);
    GXColor4u8(255, 255, 255, (u8)alpha);
    GXTexCoord2f32(0.0f, 1.0f);
}

static void _fadeEffectBoundBallInit() {
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.ballTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.frame = 1;
    FADE_EFFECT_BOUND* ball = _fadeEffectBound;
    s32 i = 0;
    do {
        switch (i % 4) {
        case 0: ball->x = FADE_RANDOM(320UL); ball->y = FADE_RANDOM(240UL); break;
        case 1: ball->x = FADE_RANDOM(320UL) + 320; ball->y = FADE_RANDOM(240UL) + 240; break;
        case 2: ball->x = FADE_RANDOM(320UL) + 320; ball->y = FADE_RANDOM(240UL); break;
        case 3: ball->x = FADE_RANDOM(320UL); ball->y = FADE_RANDOM(240UL) + 240; break;
        }
        ball->rotation = 0;
        ball->speed = (FADE_RANDOM(4UL) * 3) + 3;
        s32 sign = (i % 2 == 0) ? 1 : -1;
        ball->speed *= sign;
        ball->state = (FADE_RANDOM(4UL) * 3) + 3;
        ball->state *= sign;
        ++i; ++ball;
    } while (i < 16);
    _fadeEffect_AdjustParms();
}

static void _disp_bound_ball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha) {
    FadeMtx transform, rotation;
    GSvec point, output;
    point.param1 = scale;
    point.param2 = scale;
    point.param3 = scale;
    f64 dv = scale;
    PSMTXScale(transform, dv, dv, dv);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, transform, transform);
    PSMTXTransApply(transform, transform, center->param1, center->param2, center->param3);
    layer->beginSurface(4);
    point.param1 = -32.0f;
    point.param2 = -32.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 32.0f;
    point.param2 = -32.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = -32.0f;
    point.param2 = 32.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 32.0f;
    point.param2 = 32.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    layer->endSurface();
}

static void _fadeEffectFunction_trainer_FirstInit(GStexture* arg0) {
    GSgfxVideoSetLockFrameRate(0);
    _fadeEffectWork.ballTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.state = 0;
    _fadeEffectWork.rotationStep = 0.1f;
    _fadeEffectWork.distanceStep = 16.0f;
    _fadeEffectWork.rotation = 0.0f;
    GSgfxBeginBackFBCapture(arg0, _myBackFB, 0);
    GSgfxVFInit(&_fadeEffectTrainer_vf);
    GSgfxVFCreate(&_fadeEffectTrainer_vf);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 9, 1, 4, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 0xB, 1, 5, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 0xD, 1, 4, 0);
    GSgfxVFSetElement(&_fadeEffectTrainer_vf, 0xE, 1, 4, 0);
    _fadeEffect_AdjustParms();
}

#define FL(T, off) (*(T*)((u8*)layer + (off)))
#define FL_SET(a, b, v) \
    FL(s32, a) |= (v); FL(s32, 0x16A8) |= 8; FL(s32, b) |= (v); FL(s32, 0x1760) |= 8

#define FADE_LAYER_SETUP \
    f32 matrix[4][4]; \
    u32* flags; \
    FadeMatrixSlot* slot; \
    GSmtx44Ortho(matrix, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f); \
    layer->fieldD54 = 1; \
    layer->fieldD58 = matrix[0][0]; \
    layer->fieldD5C = matrix[0][3]; \
    layer->fieldD60 = matrix[1][1]; \
    layer->fieldD64 = matrix[1][3]; \
    layer->fieldD68 = matrix[2][2]; \
    layer->fieldD6C = matrix[2][3]; \
    slot = layer->field19A0; \
    memcpy(slot->state->matrix, mtxIdent, 0x30); \
    flags = &slot->state->flags; \
    *flags |= 1; \
    layer->field1684 = 0.0f; \
    layer->field1688 = 30000.0f; \
    if ((u8) layer->field16A7 != 0) { \
        if ((u8) layer->field16A6 != 0) { \
            layer->field170C = (s32) (layer->field170C | 0x100); \
            layer->field17C4 = (s32) (layer->field17C4 | 0x100); \
        } \
        layer->field170C = (s32) (layer->field170C | 0x40); \
        layer->field16A8 = (s32) (layer->field16A8 | 0x40); \
        layer->field17C4 = (s32) (layer->field17C4 | 0x40); \
        layer->field1760 = (s32) (layer->field1760 | 0x40); \
    } \
    layer->field16AC = (s32) (layer->field16AC | 0x20); \
    layer->field16A8 = (s32) (layer->field16A8 | 1); \
    layer->field1764 = (s32) (layer->field1764 | 0x20); \
    layer->field1760 = (s32) (layer->field1760 | 1); \
    if ((s32) layer->field1994 != 1) { \
        layer->field1994 = 1; \
        layer->field1990 = (void*) ((FadeLayerConfigView*)layer)->configs[layer->field1994]; \
    } \
    layer->field1644 = 1; \
    layer->field1648 = 4; \
    layer->field164C = 5; \
    layer->field1650 = 5; \
    layer->field170C = (s32) (layer->field170C | 1); \
    layer->field16A8 = (s32) (layer->field16A8 | 0x40); \
    layer->field17C4 = (s32) (layer->field17C4 | 1); \
    layer->field1760 = (s32) (layer->field1760 | 0x40); \
    layer->field1656 = 1; \
    layer->field1657 = 1; \
    layer->field1658 = 0; \
    layer->field170C = (s32) (layer->field170C | 4); \
    layer->field16A8 = (s32) (layer->field16A8 | 0x40); \
    layer->field17C4 = (s32) (layer->field17C4 | 4); \
    layer->field1760 = (s32) (layer->field1760 | 0x40); \
    layer->field165C = 0; \
    layer->field1660 = 1; \
    layer->field170C = (s32) (layer->field170C | 8); \
    layer->field16A8 = (s32) (layer->field16A8 | 0x40); \
    layer->field17C4 = (s32) (layer->field17C4 | 8); \
    layer->field1760 = (s32) (layer->field1760 | 0x40); \
    layer->field1664 = 7; \
    layer->field1670 = 0; \
    layer->field1668 = 0; \
    layer->field166C = 7; \
    layer->field1671 = 0; \
    layer->field1672 = 1; \
    layer->field170C = (s32) (layer->field170C | 0x10); \
    layer->field16A8 = (s32) (layer->field16A8 | 0x40); \
    layer->field17C4 = (s32) (layer->field17C4 | 0x10); \
    layer->field1760 = (s32) (layer->field1760 | 0x40); \
    layer->fieldD8C = 0; \
    layer->field16B8 = (s32) (layer->field16B8 | 2); \
    layer->field16A8 = (s32) (layer->field16A8 | 2); \
    layer->field1770 = (s32) (layer->field1770 | 2); \
    layer->field1760 = (s32) (layer->field1760 | 2);

#define FADE_LAYER_BIND_TEXTURE(tex) \
    if (((void *) layer->field1740 != (tex)) || ((void *) layer->field17F8 != (tex)) || ((u8) (tex)->dirty != 0)) { \
        layer->field1740 = (tex); \
        layer->field173C = (s32) (layer->field173C | 1); \
        layer->field17F8 = (tex); \
        layer->field17F4 = (s32) (layer->field17F4 | 1); \
    }

bool fadeEffectHookFunction_slide_ball(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (!opaque) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectSlideBallInit();
    }
    if (_fadeEffectFirstFlag == 0 && !active) return active;
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) _fadeEffectWork.frame++;
    _fadeEffectMaskFunction(layer, progress);
    GSvec center;
    center.param1 = 320.0f; center.param2 = 240.0f; center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, (GStexture*)opaque, &center, 1.0f, 0.0f, progress, 0.0f);
    int alpha = (int)(255.0f * (1.0f - progress));
    FADE_LAYER_SETUP
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 4, 0, 0, 1, 5, 1, 1, 4));
    FADE_LAYER_BIND_TEXTURE((GStexture*)opaque)
    layer->field1998 = 0x80;
    layer->beginSurface(0x30);
    FADE_EFFECT_BOUND* ball = _fadeEffectBound;
    FADE_EFFECT_BOUND* base = _fadeEffectBound;
    s32 n = 12;
    do {
        f32 left, right, v0, v1;
        if ((f32)ball->speed > 0.0f) {
            left = ball->x;
            if (left < -1.0f) left = -1.0f;
            right = 641.0f;
            v0 = 0.0f;
            v1 = (641.0f - left) / 640.0f;
        } else {
            left = -1.0f;
            right = ball->x;
            if (right > 641.0f) right = 641.0f;
            v1 = 1.0f;
            v0 = (640.0f - right) / 640.0f;
        }
        f32 top = ball->y - 26;
        f32 vt = top / 480.0f;
        ++ball;
        GXPosition2f32(left, top);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(v0, vt);
        f32 bottom = 53.0f + top;
        f32 vb = bottom / 480.0f;
        GXPosition2f32(right, top);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(v1, vt);
        GXPosition2f32(right, bottom);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(v1, vb);
        GXPosition2f32(left, bottom);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(v0, vb);
    } while (--n != 0);
    layer->endSurface();
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 4, 0, 0, 1, 5, 1, 1, 4));
    FADE_LAYER_BIND_TEXTURE(_fadeEffectWork.ballTexture)
    layer->field1998 = 0x80;
    layer->beginSurface(0x60);
    s32 i = 0;
    do {
        f32 x2;
        if (base->speed > 0) {
            x2 = base->x - 320.0f;
            if (x2 < 0.0f) x2 = 0.0f;
        } else {
            x2 = 320.0f + base->x;
            if (x2 > 641.0f) x2 = 641.0f;
        }
        _disp_slide_ball(layer, base->x, base->y, x2, base->rotation, (u8)alpha);
        if (timeGetLastFrameTime() != 0) {
            base->x = base->x + base->speed;
            base->rotation = (s16)((360.0f * base->x) / 166.50441f);
            if (base->speed > 0) {
                base->x = base->x + (base->x / 80);
            } else {
                s16 cx = base->x;
                base->x = cx - ((640 - cx) / 80);
            }
        }
        ++base; ++i;
    } while (i < 12);
    layer->endSurface();
    return active;
}

bool fadeEffectHookFunction_bound_ball(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GSgfxLayer* layer;
    GStexture* texture;
    GSvec center;
    GSvec ballCenter;
    layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectBoundBallInit();
    }
    if (_fadeEffectFirstFlag == 0 && !active) return active;
    f32 progress = elapsed / duration;
    f32 progressSecond = elapsedSecond / durationSecond;
    if (timeGetLastFrameTime() != 0) _fadeEffectWork.frame++;
    _fadeEffectMaskFunction(layer, progress);
    center.param1 = 320.0f; center.param2 = 240.0f; center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.0f);
    center.param1 = 320.0f + _fadeEffectWork.frame;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.5f);
    center.param1 = 320.0f - _fadeEffectWork.frame;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.5f);
    _fadeEffectStartTexture(layer, _fadeEffectWork.ballTexture);
    FADE_EFFECT_BOUND* ball = _fadeEffectBound;
    s32 i = 0;
    do {
        f32 rot = ball->rotation;
        if (timeGetLastFrameTime() != 0) {
            if (ball->speed > 0) rot += 18.0f;
            else rot -= 18.0f;
            if (rot <= 0.0f) rot += 360.0f;
            else if (rot >= 360.0f) rot -= 360.0f;
        }
        ball->rotation = (s16)rot;
        f32 px = ball->x;
        if (timeGetLastFrameTime() != 0) {
            px += ball->speed;
            if (px < 32.0f) {
                px = 32.0f;
                ball->speed = -ball->speed;
            } else if (px > 608.0f) {
                px = 608.0f;
                ball->speed = -ball->speed;
            }
        }
        ball->x = (s16)px;
        f32 py = ball->y;
        if (timeGetLastFrameTime() != 0) {
            py += ball->state;
            if (py < 32.0f) {
                py = 32.0f;
                ball->state = -ball->state;
            } else if (py > 448.0f) {
                ball->state = -ball->state;
                py = 448.0f;
                if (ball->state < 0.5f) ball->state = -13;
            } else if (ball->state >= 0) {
                ball->state = ball->state + 0.5f;
            } else {
                ball->state = ball->state - 0.5f;
            }
        }
        ball->y = (s16)py;
        ballCenter.param3 = 0.0f;
        ballCenter.param2 = ball->y;
        ballCenter.param1 = ball->x;
        _disp_bound_ball(layer, &ballCenter, 1.0f, rot, (s32)(255.0f * (1.0f - progress) * (1.0f - progressSecond)));
        ++ball; ++i;
    } while (i < 16);
    _fadeEffectEnd(layer);
    return active;
}

bool fadeEffectHookFunction_distortion(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GStexture* texture;
    GSgfxLayer* layer;
    layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeDistortionInit();
        _fadeEffectWork.state = ((HSD_Rand() << 16) | HSD_Rand()) & 1;
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !active) {
        _fadeDistortionQuit();
        GSgfxEndBackFBCapture(texture);
        return active;
    }
    f32 progress = elapsed / duration;
    f32 progressSecond = elapsedSecond / durationSecond;
    if (timeGetLastFrameTime() != 0) {
        _fadeDistortionDo((unsigned long)-((6.0f * progress) - (10.0f - (3.0f * progressSecond))));
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(texture);
    }
    FADE_LAYER_SETUP
    layer->field1998 = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    FADE_LAYER_BIND_TEXTURE(texture)
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    FadeGridPoint* points = _fadeDistortionWork.points;
    FadeUV* uv = _fadeDistortionWork.uv;
    if (!points || !uv) return false;
    int count = columns * 2;
    s32 alpha = (s32)(255.0f * -((progress * (progress * progress)) - 1.0f));
    for (int x = 1; x < rows; ++x) {
        layer->beginSurface(count);
        for (int y = 0; y < columns; ++y) {
            int index = x * columns + y;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(uv[index].u, uv[index].v);
            index = (x - 1) * columns + y;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(uv[index].u, uv[index].v);
        }
        layer->endSurface();
    }
    return active;
}


struct FadeColor { u8 r, g, b, a; };

bool fadeEffectHookFunction_Doku(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void*) {
    FadeColor color = { 0x1F, 0x08, 0x08, 0xFF };
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    f32 progress = elapsedSecond / durationSecond;
    GSvec blend, high, low;
    f32 k;
    if (progress <= 0.5f) {
        k = 4.0f * progress;
        low.param1 = 1.0f; low.param2 = 1.0f; low.param3 = 1.0f;
        high.param1 = 0.0f; high.param2 = 0.0f; high.param3 = 0.0f;
        if (k >= 1.0f) k = 1.0f;
    } else {
        k = 2.0f * (progress - 0.5f);
        high.param1 = 1.0f; high.param2 = 1.0f; high.param3 = 1.0f;
        low.param1 = 0.0f; low.param2 = 0.0f; low.param3 = 0.0f;
        if (k >= 1.0f) k = 1.0f;
    }
    GSlerpGetLinearInterpolationVector(&blend, &high, &low, k);
    f32 base = (u8)(s32)(255.0f * blend.param1);
    s32 alpha = (s32)(base * (1.0f - (elapsed / duration)));
    FADE_LAYER_SETUP
    layer->field1998 = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
    layer->beginSurface(4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor4u8(color.r, color.g, color.b, (u8)alpha);
    GXPosition3f32(640.0f, 0.0f, 0.0f);
    GXColor4u8(color.r, color.g, color.b, (u8)alpha);
    GXPosition3f32(0.0f, 480.0f, 0.0f);
    GXColor4u8(color.r, color.g, color.b, (u8)alpha);
    GXPosition3f32(640.0f, 480.0f, 0.0f);
    GXColor4u8(color.r, color.g, color.b, (u8)alpha);
    layer->endSurface();
    if (progress >= 1.0f) {
        fadeEffectDokuStop();
        return false;
    }
    return active;
}


static void _fadeTearOffDraw(GSgfxLayer* layer, u8 alpha, int shift) {
    s16 w = _fadeTearOffWork.x;
    u8 half = (u32)alpha >> 1;
    s16 h = _fadeTearOffWork.y;
    f32 u = (f32)w / 640.0f;
    f32 v = (f32)h / 480.0f;
    layer->beginSurface(4);
    f32 zero = 0.0f;
    f32 one = 1.0f;
    GXPosition3s16(0, 0, 0);
    GXColor4u8(255, 255, 255, alpha);
    GXTexCoord2f32(zero, zero);
    GXPosition3s16(640, 0, 0);
    GXColor4u8(255, 255, 255, alpha);
    GXTexCoord2f32(one, zero);
    GXPosition3s16(0, 480, 0);
    GXColor4u8(255, 255, 255, alpha);
    GXTexCoord2f32(zero, one);
    GXPosition3s16(640, 480, 0);
    GXColor4u8(255, 255, 255, alpha);
    GXTexCoord2f32(one, one);
    layer->endSurface();
    layer->beginSurface(3);
    GXPosition3s16(w, 0, 0);
    GXColor4u8(255, 255, 255, alpha);
    GXTexCoord2f32(u, zero);
    GXPosition3s16(w, h, 0);
    GXColor4u8(255, 255, 255, alpha);
    GXTexCoord2f32(one, zero);
    GXPosition3s16(640, h, 0);
    GXColor4u8(255, 255, 255, alpha);
    GXTexCoord2f32(one, v);
    layer->endSurface();
    layer->beginSurface(3);
    GXPosition3s16(w + shift, shift, 0);
    GXColor4u8(255, 255, 255, half);
    GXTexCoord2f32(u, zero);
    GXPosition3s16(shift + 640, shift, 0);
    GXColor4u8(255, 255, 255, half);
    GXTexCoord2f32(one, zero);
    GXPosition3s16(shift + 640, h + shift, 0);
    GXColor4u8(255, 255, 255, half);
    GXTexCoord2f32(one, v);
    layer->endSurface();
    int shift2 = shift * 2;
    layer->beginSurface(3);
    GXPosition3s16(w + shift2, shift2, 0);
    GXColor4u8(255, 255, 255, half);
    GXTexCoord2f32(u, zero);
    GXPosition3s16(shift2 + 640, shift2, 0);
    GXColor4u8(255, 255, 255, half);
    GXTexCoord2f32(one, zero);
    GXPosition3s16(shift2 + 640, h + shift2, 0);
    GXColor4u8(255, 255, 255, half);
    GXTexCoord2f32(one, v);
    layer->endSurface();
}

bool fadeEffectHookFunction_tear_off(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void* opaque) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (!opaque) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        GSgfxVideoSetLockFrameRate(1);
        _fadeTearOffWork.x = 640;
        _fadeTearOffWork.y = 0;
        _fadeEffectWork.frame = 0;
    }
    if (_fadeEffectFirstFlag == 0 && !active) return active;
    if (timeGetLastFrameTime() != 0) _fadeEffectWork.frame++;
    FADE_LAYER_SETUP
    layer->field1998 = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    FADE_LAYER_BIND_TEXTURE((GStexture*)opaque)
    f32 progress = elapsed / duration;
    s32 alpha = (s32)(255.0f * (1.0f - progress));
    if (timeGetLastFrameTime() != 0) {
        _fadeTearOffWork.x -= 10;
        _fadeTearOffWork.y += 10;
    }
    _fadeTearOffDraw(layer, alpha, _fadeEffectWork.frame);
    return active;
}


extern bool fadeEffectHookFunction_trainer(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void* opaque) {
    GStexture* texture;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_trainer_FirstInit(texture);
    }
    if (_fadeEffectFirstFlag == 0 && !active) GSgfxVFFree(&_fadeEffectTrainer_vf);
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) {
        f32 step = _fadeEffectWork.rotationStep;
        f32 pos = _fadeEffectWork.rotation + step;
        _fadeEffectWork.frame++;
        _fadeEffectWork.rotation = pos;
        if (step >= 0.0f) {
            _fadeEffectWork.rotationStep = 0.5f * progress + step;
            if (pos >= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
        } else {
            _fadeEffectWork.rotationStep = -(0.5f * progress - step);
            if (pos <= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
        }
    }
    GSvec center;
    center.param1 = 320.0f; center.param2 = 240.0f; center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.0f);
    center.param2 = 240.0f; center.param3 = 0.0f;
    center.param1 = 320.0f + _fadeEffectWork.rotation;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.5f);
    center.param3 = 0.0f;
    center.param1 = 320.0f - _fadeEffectWork.rotation;
    center.param2 = 240.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.5f);
    if (GSgfxVFIsUsed(&_fadeEffectTrainer_vf)) {
        layer->setRenderStateAndSelect(&_fadeEffectTrainer_vf);
        f32 matrix[4][4];
        FadeMatrixSlot* slot;
        u32* flags;
        GSmtx44Ortho(matrix, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
        layer->fieldD54 = 1;
        layer->fieldD58 = matrix[0][0];
        layer->fieldD5C = matrix[0][3];
        layer->fieldD60 = matrix[1][1];
        layer->fieldD64 = matrix[1][3];
        layer->fieldD68 = matrix[2][2];
        layer->fieldD6C = matrix[2][3];
        slot = layer->field19A0;
        memcpy(slot->state->matrix, mtxIdent, 0x30);
        flags = &slot->state->flags;
        *flags |= 1;
        layer->field1684 = 0.0f;
        layer->field1688 = 30000.0f;
        if ((u8) layer->field16A7 != 0) {
            if ((u8) layer->field16A6 != 0) {
                layer->field170C = (s32) (layer->field170C | 0x100);
                layer->field17C4 = (s32) (layer->field17C4 | 0x100);
            }
            layer->field170C = (s32) (layer->field170C | 0x40);
            layer->field16A8 = (s32) (layer->field16A8 | 0x40);
            layer->field17C4 = (s32) (layer->field17C4 | 0x40);
            layer->field1760 = (s32) (layer->field1760 | 0x40);
        }
        layer->field16AC = (s32) (layer->field16AC | 0x20);
        layer->field16A8 = (s32) (layer->field16A8 | 1);
        layer->field1764 = (s32) (layer->field1764 | 0x20);
        layer->field1760 = (s32) (layer->field1760 | 1);
        if ((s32) layer->field1994 != 1) {
            layer->field1994 = 1;
            layer->field1990 = (void*) ((FadeLayerConfigView*)layer)->configs[layer->field1994];
        }
        layer->field1644 = 1;
        layer->field1648 = 4;
        layer->field164C = 5;
        layer->field1650 = 5;
        layer->field170C = (s32) (layer->field170C | 1);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 1);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
        layer->field1656 = 1;
        layer->field1657 = 1;
        layer->field1658 = 0;
        layer->field170C = (s32) (layer->field170C | 4);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 4);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
        layer->field165C = 0;
        layer->field1660 = 1;
        layer->field170C = (s32) (layer->field170C | 8);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 8);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
        layer->field1664 = 7;
        layer->field1670 = 0;
        layer->field1668 = 0;
        layer->field166C = 7;
        layer->field1671 = 0;
        layer->field1672 = 1;
        layer->field170C = (s32) (layer->field170C | 0x10);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 0x10);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
        layer->fieldD8C = 0;
        layer->field16B8 = (s32) (layer->field16B8 | 2);
        layer->field16A8 = (s32) (layer->field16A8 | 2);
        layer->field1770 = (s32) (layer->field1770 | 2);
        layer->field1760 = (s32) (layer->field1760 | 2);
        layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
        layer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)5, 0, false, 0);
        FL(s32, 0xEAC) = 2;
        FL_SET(0x16CC, 0x1784, 1);
        GStexture* tex0 = _fadeEffectWork.secondTexture;
        if (layer->field1740 != tex0 || layer->field17F8 != tex0 || tex0->dirty != 0) {
            layer->field1740 = tex0;
            layer->field173C = (s32) (layer->field173C | 1);
            layer->field17F8 = tex0;
            layer->field17F4 = (s32) (layer->field17F4 | 1);
        }
        FL(s32, 0xEB0) = 0; FL(s32, 0xEB4) = 0; FL(s32, 0xEB8) = 4;
        FL_SET(0x16D0, 0x1788, 1);
        FL(s32, 0x1170) = 8; FL(s32, 0x1174) = 0; FL(s32, 0x1178) = 0; FL(s32, 0x117C) = 0; FL(s32, 0x1180) = 1;
        FL_SET(0x16DC, 0x1794, 1);
        FL(s32, 0xF70) = 9; FL(s32, 0xF74) = 0xD; FL(s32, 0xF78) = 0xC; FL(s32, 0xF7C) = 0xF;
        FL_SET(0x16D4, 0x178C, 1);
        FL(s32, 0x12B0) = 0; FL(s32, 0x12B4) = 0; FL(s32, 0x12B8) = 0; FL(s32, 0x12BC) = 0; FL(s32, 0x12C0) = 1;
        FL_SET(0x16E0, 0x1798, 1);
        FL(s32, 0x1070) = 7; FL(s32, 0x1074) = 4; FL(s32, 0x1078) = 5; FL(s32, 0x107C) = 7;
        FL_SET(0x16D8, 0x1790, 1);
        if (FL(GStexture*, 0x1744) != texture || FL(GStexture*, 0x17FC) != texture || texture->dirty != 0) {
            FL(GStexture*, 0x1744) = texture;
            FL(s32, 0x173C) |= 2;
            FL(GStexture*, 0x17FC) = texture;
            FL(s32, 0x17F4) |= 2;
        }
        FL(s32, 0xEBC) = 1; FL(s32, 0xEC0) = 1; FL(s32, 0xEC4) = 4;
        FL_SET(0x16D0, 0x1788, 2);
        FL(s32, 0x1184) = 0; FL(s32, 0x1188) = 0; FL(s32, 0x118C) = 0; FL(s32, 0x1190) = 0; FL(s32, 0x1194) = 0;
        FL_SET(0x16DC, 0x1794, 2);
        FL(s32, 0xF80) = 0xF; FL(s32, 0xF84) = 8; FL(s32, 0xF88) = 2; FL(s32, 0xF8C) = 0xF;
        FL_SET(0x16D4, 0x178C, 2);
        FL(s32, 0x12C4) = 0; FL(s32, 0x12C8) = 0; FL(s32, 0x12CC) = 0; FL(s32, 0x12D0) = 0; FL(s32, 0x12D4) = 0;
        FL_SET(0x16E0, 0x1798, 2);
        FL(s32, 0x1080) = 7; FL(s32, 0x1084) = 7; FL(s32, 0x1088) = 7; FL(s32, 0x108C) = 1;
        FL_SET(0x16D8, 0x1790, 2);
        FL(GSgfxVF*, 0x199C) = &_fadeEffectTrainer_vf;
        layer->field1998 = 0x98;

        FadeMtx transform, rotation;
        GSvec point, output;
        s32 alpha = (s32)(255.0f * (1.0f - progress));
        center.param1 = 320.0f; center.param3 = 0.0f; center.param2 = 240.0f;
        f32 scale = 1.0f + (f32)_fadeEffectWork.frame / 150.0f;
        PSMTXScale(transform, scale, scale, scale);
        PSMTXRotRad(rotation, 'Z', 0.0f);
        PSMTXConcat(rotation, transform, transform);
        PSMTXTransApply(transform, transform, center.param1, center.param2, center.param3);
        point.param1 = 128.0f; point.param2 = 128.0f; point.param3 = 0.0f;
        PSMTXMultVec(transform, &point, &output);
        output.param1 -= 320.0f;
        output.param2 -= 240.0f;
        f32 u0 = (320.0f - output.param1) / 640.0f;
        f32 u1 = (320.0f + output.param1) / 640.0f;
        f32 v0 = (240.0f - output.param2) / 480.0f;
        f32 v1 = (240.0f + output.param2) / 480.0f;
        layer->beginSurface(4);
        point.param1 = -128.0f; point.param2 = -128.0f; point.param3 = 0.0f;
        PSMTXMultVec(transform, &point, &output);
        { f32 u = 0.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
        GXTexCoord2f32(u0, v0); }
        point.param1 = 128.0f; point.param2 = -128.0f; point.param3 = 0.0f;
        PSMTXMultVec(transform, &point, &output);
        { f32 u = 1.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
        GXTexCoord2f32(u1, v0); }
        point.param1 = -128.0f; point.param2 = 128.0f; point.param3 = 0.0f;
        PSMTXMultVec(transform, &point, &output);
        { f32 u = 0.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
        GXTexCoord2f32(u0, v1); }
        point.param1 = 128.0f; point.param2 = 128.0f; point.param3 = 0.0f;
        PSMTXMultVec(transform, &point, &output);
        { f32 u = 1.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
        GXTexCoord2f32(u1, v1); }
        layer->endSurface();
    }
    if (timeGetLastFrameTime() != 0) GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    else GSgfxEndBackFBCapture(texture);
    if (_fadeEffectFirstFlag == 0 && !active) GSgfxEndBackFBCapture(texture);
    return active;
}

bool fadeEffectHookFunction_dist_ball(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void* opaque) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    GStexture* texture;
    if (!layer) return active;
    texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeDistBallInit();
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !active) {
        _fadeDistBallQuit();
        GSgfxEndBackFBCapture(texture);
        return active;
    }
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) {
        ++_fadeEffectWork.frame;
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(texture);
    }
    GSvec center;
    center.param1 = 320.0f; center.param2 = 240.0f; center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.0f);
    center.param1 = 321.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.5f);
    center.param1 = 319.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.5f);
    {
        layer->setRenderStateAndSelect(&_fadeEffectTrainer_vf);
        f32 matrix[4][4];
        FadeMatrixSlot* slot;
        u32* flags;
        GSmtx44Ortho(matrix, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
        layer->fieldD54 = 1;
        layer->fieldD58 = matrix[0][0];
        layer->fieldD5C = matrix[0][3];
        layer->fieldD60 = matrix[1][1];
        layer->fieldD64 = matrix[1][3];
        layer->fieldD68 = matrix[2][2];
        layer->fieldD6C = matrix[2][3];
        slot = layer->field19A0;
        memcpy(slot->state->matrix, mtxIdent, 0x30);
        flags = &slot->state->flags;
        *flags |= 1;
        layer->field1684 = 0.0f;
        layer->field1688 = 30000.0f;
        if ((u8) layer->field16A7 != 0) {
            if ((u8) layer->field16A6 != 0) {
                layer->field170C = (s32) (layer->field170C | 0x100);
                layer->field17C4 = (s32) (layer->field17C4 | 0x100);
            }
            layer->field170C = (s32) (layer->field170C | 0x40);
            layer->field16A8 = (s32) (layer->field16A8 | 0x40);
            layer->field17C4 = (s32) (layer->field17C4 | 0x40);
            layer->field1760 = (s32) (layer->field1760 | 0x40);
        }
        layer->field16AC = (s32) (layer->field16AC | 0x20);
        layer->field16A8 = (s32) (layer->field16A8 | 1);
        layer->field1764 = (s32) (layer->field1764 | 0x20);
        layer->field1760 = (s32) (layer->field1760 | 1);
        if ((s32) layer->field1994 != 1) {
            layer->field1994 = 1;
            layer->field1990 = (void*) ((FadeLayerConfigView*)layer)->configs[layer->field1994];
        }
        layer->field1644 = 1;
        layer->field1648 = 4;
        layer->field164C = 5;
        layer->field1650 = 5;
        layer->field170C = (s32) (layer->field170C | 1);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 1);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
        layer->field1656 = 1;
        layer->field1657 = 1;
        layer->field1658 = 0;
        layer->field170C = (s32) (layer->field170C | 4);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 4);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
        layer->field165C = 0;
        layer->field1660 = 1;
        layer->field170C = (s32) (layer->field170C | 8);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 8);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
        layer->field1664 = 7;
        layer->field1670 = 0;
        layer->field1668 = 0;
        layer->field166C = 7;
        layer->field1671 = 0;
        layer->field1672 = 1;
        layer->field170C = (s32) (layer->field170C | 0x10);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 0x10);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
        layer->fieldD8C = 0;
        layer->field16B8 = (s32) (layer->field16B8 | 2);
        layer->field16A8 = (s32) (layer->field16A8 | 2);
        layer->field1770 = (s32) (layer->field1770 | 2);
        layer->field1760 = (s32) (layer->field1760 | 2);
        layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
        layer->tgenFunc(1, (GSgfxTgenFunc)1, (GSgfxTgenSrc)5, 0, false, 0);
        FL(s32, 0xEAC) = 3;
        FL_SET(0x16CC, 0x1784, 1);
        GStexture* tex0 = _fadeEffectWork.secondTexture;
        if (layer->field1740 != tex0 || layer->field17F8 != tex0 || tex0->dirty != 0) {
            layer->field1740 = tex0;
            layer->field173C = (s32) (layer->field173C | 1);
            layer->field17F8 = tex0;
            layer->field17F4 = (s32) (layer->field17F4 | 1);
        }
        FL(s32, 0xEB0) = 0; FL(s32, 0xEB4) = 0; FL(s32, 0xEB8) = 4;
        FL_SET(0x16D0, 0x1788, 1);
        FL(s32, 0x1170) = 8; FL(s32, 0x1174) = 0; FL(s32, 0x1178) = 0; FL(s32, 0x117C) = 0; FL(s32, 0x1180) = 1;
        FL_SET(0x16DC, 0x1794, 1);
        FL(s32, 0xF70) = 9; FL(s32, 0xF74) = 0xD; FL(s32, 0xF78) = 0xC; FL(s32, 0xF7C) = 0xF;
        FL_SET(0x16D4, 0x178C, 1);
        FL(s32, 0x12B0) = 0; FL(s32, 0x12B4) = 0; FL(s32, 0x12B8) = 0; FL(s32, 0x12BC) = 0; FL(s32, 0x12C0) = 1;
        FL_SET(0x16E0, 0x1798, 1);
        FL(s32, 0x1070) = 7; FL(s32, 0x1074) = 4; FL(s32, 0x1078) = 5; FL(s32, 0x107C) = 7;
        FL_SET(0x16D8, 0x1790, 1);
        if (FL(GStexture*, 0x1744) != texture || FL(GStexture*, 0x17FC) != texture || texture->dirty != 0) {
            FL(GStexture*, 0x1744) = texture;
            FL(s32, 0x173C) |= 2;
            FL(GStexture*, 0x17FC) = texture;
            FL(s32, 0x17F4) |= 2;
        }
        FL(s32, 0xEBC) = 1; FL(s32, 0xEC0) = 1; FL(s32, 0xEC4) = 4;
        FL_SET(0x16D0, 0x1788, 2);
        FL(s32, 0x1184) = 0; FL(s32, 0x1188) = 0; FL(s32, 0x118C) = 0; FL(s32, 0x1190) = 0; FL(s32, 0x1194) = 0;
        FL_SET(0x16DC, 0x1794, 2);
        FL(s32, 0xF80) = 0xF; FL(s32, 0xF84) = 8; FL(s32, 0xF88) = 2; FL(s32, 0xF8C) = 0xF;
        FL_SET(0x16D4, 0x178C, 2);
        FL(s32, 0x12C4) = 0; FL(s32, 0x12C8) = 0; FL(s32, 0x12CC) = 0; FL(s32, 0x12D0) = 0; FL(s32, 0x12D4) = 0;
        FL_SET(0x16E0, 0x1798, 2);
        FL(s32, 0x1080) = 7; FL(s32, 0x1084) = 7; FL(s32, 0x1088) = 7; FL(s32, 0x108C) = 1;
        FL_SET(0x16D8, 0x1790, 2);
        {
        GStexture* tex2 = _fadeEffectWork.ballTexture;
        if (FL(GStexture*, 0x1748) != tex2 || FL(GStexture*, 0x1800) != tex2 || tex2->dirty != 0) {
            FL(GStexture*, 0x1748) = tex2;
            FL(s32, 0x173C) |= 4;
            FL(GStexture*, 0x1800) = tex2;
            FL(s32, 0x17F4) |= 4;
        }
        }
        FL(s32, 0xEC8) = 0; FL(s32, 0xECC) = 2; FL(s32, 0xED0) = 4;
        FL_SET(0x16D0, 0x1788, 4);
        FL(s32, 0x1198) = 0; FL(s32, 0x119C) = 0; FL(s32, 0x11A0) = 0; FL(s32, 0x11A4) = 0; FL(s32, 0x11A8) = 0;
        FL_SET(0x16DC, 0x1794, 4);
        FL(s32, 0xF90) = 8; FL(s32, 0xF94) = 0xF; FL(s32, 0xF98) = 0xF; FL(s32, 0xF9C) = 0;
        FL_SET(0x16D4, 0x178C, 4);
        FL(s32, 0x12D8) = 0; FL(s32, 0x12DC) = 0; FL(s32, 0x12E0) = 0; FL(s32, 0x12E4) = 0; FL(s32, 0x12E8) = 0;
        FL_SET(0x16E0, 0x1798, 4);
        FL(s32, 0x1090) = 7; FL(s32, 0x1094) = 4; FL(s32, 0x1098) = 5; FL(s32, 0x109C) = 4;
        FL_SET(0x16D8, 0x1790, 4);
        FL(GSgfxVF*, 0x199C) = &_fadeEffectTrainer_vf;
        layer->field1998 = 0x98;
    }
    FADE_EFFECT_BOUND* ball = _fadeEffectBound;
    s32 i = 0;
    do {
        f32 angle = (f32)ball->rotation;
        if (timeGetLastFrameTime() != 0) {
            if ((f32)ball->speed < 0.0f) angle += 18.0f;
            else angle -= 18.0f;
            if (angle <= 0.0f) angle += 360.0f;
            else if (angle >= 360.0f) angle -= 360.0f;
        }
        ball->rotation = (s16)angle;
        if (timeGetLastFrameTime() != 0) {
            f32 nx = (f32)ball->x + (f32)ball->speed;
            if (nx < 32.0f) { nx = 32.0f; ball->speed = -ball->speed; }
            else if (nx > 608.0f) { nx = 608.0f; ball->speed = -ball->speed; }
            ball->x = (s16)nx;
        }
        if (timeGetLastFrameTime() != 0) {
            s16 vy = ball->state;
            f32 ny = (f32)ball->y + (f32)vy;
            if (ny < 32.0f) { ny = 32.0f; ball->state = -vy; }
            else if (ny > 448.0f) {
                ny = 448.0f;
                ball->state = (vy * -8) / 10;
                s16 t = ball->state;
                if ((f32)t > -1.0f && (f32)t < 1.0f) ball->state = -7;
            } else {
                if ((f32)vy >= 0.0f) ball->state = (s16)((f32)vy + 1.0f);
                else ball->state = (s16)((f32)vy + 1.0f);
            }
            ball->y = (s16)ny;
        }
        GSvec pos;
        pos.param2 = (f32)ball->y;
        pos.param3 = 0.0f;
        pos.param1 = (f32)ball->x;
        _disp_dist_ball(layer, &pos, 1.0f, angle, (s32)(0.2f * (255.0f * (1.0f - progress))));
        ++ball; ++i;
    } while (i < 12);
    return active;
}

static bool fadeEffectHookFunction_fadein(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void*) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    _fadeEffectMaskFunction(layer, elapsed / duration);
    return active;
}

static bool fadeEffectHookFunction_fadeout_in(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    f32 progress = elapsed / duration;
    f32 secondProgress = elapsedSecond / durationSecond;
    _fadeEffectMaskFunction(layer, progress);
    GStexture* texture = (GStexture*)opaque;
    if (!texture) return active;
    GSvec center;
    center.param1 = 320.0f; center.param2 = 240.0f; center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, secondProgress);
    return active;
}

static void _fadeEffectFunction_boss_FirstInit_second() {
    GSvec shock;

    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.ballTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.state = 0;
    fadeFluidInit(0x23, 0x19, 1.0f, 1.0f, 0.5f, 0.01f);
    shock.param1 = 17.5f;
    shock.param2 = 12.5f;
    shock.param3 = 0.0f;
    fadeFluidSetShockSecond(&shock, 50.0f);
    shock.param1 = 1.0f;
    shock.param2 = 1.0f;
    shock.param3 = 0.0f;
    fadeFluidSetShockSecond(&shock, 0.1f);
    shock.param1 = 34.0f;
    shock.param2 = 1.0f;
    shock.param3 = 0.0f;
    fadeFluidSetShockSecond(&shock, 0.1f);
    shock.param1 = 1.0f;
    shock.param2 = 24.0f;
    shock.param3 = 0.0f;
    fadeFluidSetShockSecond(&shock, 0.1f);
    shock.param1 = 34.0f;
    shock.param2 = 24.0f;
    shock.param3 = 0.0f;
    fadeFluidSetShockSecond(&shock, 0.1f);
    _fadeEffect_AdjustParms();
}

static bool fadeEffectHookFunction_boss(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void* opaque) {
    if (!GSgfxLayerFindByID(id)) return active;
    GStexture* texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_boss_FirstInit();
    }
    if (_fadeEffectFirstFlag == 0 && active == 0) fadeFluidQuit();
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) ++_fadeEffectWork.frame;
    if (active == 1) {
        if (timeGetLastFrameTime() != 0) fadeFluidEvaluate();
        fadeFluidDisp(texture, progress, 0.0f);
    }
    return active;
}

static void _fadeEffectFunction_boss_FirstInit() {
    GSvec shock;

    GSgfxVideoSetLockFrameRate(0);
    _fadeEffectWork.ballTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.state = 0;
    fadeFluidInit(0x23, 0x19, 1.0f, 1.0f, 0.4f, 0.01f);
    shock.param1 = 17.5f;
    shock.param2 = 12.499999f;
    shock.param3 = 0.0f;
    fadeFluidSetShock(&shock, 16.0f);
    shock.param1 = 5.4687495f;
    shock.param2 = 5.208333f;
    shock.param3 = 0.0f;
    fadeFluidSetShock(&shock, 8.0f);
    shock.param1 = 29.531248f;
    shock.param2 = 19.791666f;
    shock.param3 = 0.0f;
    fadeFluidSetShock(&shock, 8.0f);
    shock.param1 = 29.531248f;
    shock.param2 = 5.208333f;
    shock.param3 = 0.0f;
    fadeFluidSetShock(&shock, 8.0f);
    shock.param1 = 5.4687495f;
    shock.param2 = 19.791666f;
    shock.param3 = 0.0f;
    fadeFluidSetShock(&shock, 8.0f);
    _fadeEffect_AdjustParms();
}

static void _fadeEffectBallSecondQuit() {

}

static void _fadeEffectBallSecondInit() {
    GSvec positions[2];
    GSgfxVideoSetLockFrameRate(1);
    _fadeEffectWork.ballTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBD1200);
    FADE_EFFECT_BALL* group = &_fadeEffectBall[0][0];
    GSvec* position = positions;
    s32 i = 0;
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.state = 0;
    _fadeEffectWork.rotationStep = 4.0f;
    _fadeEffectWork.rotation = 0.0f;
    _fadeEffectWork.distanceStep = 48.0f;
    positions[0].param1 = -75.0f;
    positions[0].param2 = 165.0f;
    positions[0].param3 = 0.0f;
    positions[1].param1 = 715.0f;
    positions[1].param2 = 315.0f;
    positions[1].param3 = 0.0f;
    do {
        FADE_EFFECT_BALL* ball = group;
        s32 fade = 0;
        for (s32 j = 0; j < 3; ++j) {
            f32 x = position->param1;
            f32 y = position->param2;
            ball->position.param1 = x;
            f32 z = position->param3;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 255 - fade;
            ++ball;
            fade += 21;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 255 - fade;
            ++ball;
            fade += 21;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 255 - fade;
            ++ball;
            fade += 21;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 255 - fade;
            ++ball;
            fade += 21;
        }
        group += 12;
        ++position;
        ++i;
    } while (i < 2);
    _fadeEffect_AdjustParms();
}

static void _dispball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha) {
    FadeMtx transform, rotation;
    GSvec point, output;
    point.param1 = scale;
    point.param2 = scale;
    point.param3 = scale;
    f64 dv = scale;
    PSMTXScale(transform, dv, dv, dv);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, transform, transform);
    PSMTXTransApply(transform, transform, center->param1, center->param2, center->param3);
    layer->beginSurface(4);
    point.param1 = -128.0f;
    point.param2 = -128.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 128.0f;
    point.param2 = -128.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = -128.0f;
    point.param2 = 128.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 128.0f;
    point.param2 = 128.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    layer->endSurface();
}

static void _fadeEffectFunction_ball_FirstInit() {
    GSvec positions[2];
    GSgfxVideoSetLockFrameRate(0);
    _fadeEffectWork.ballTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*)GSresGetResourceAllGroup(0x0EBD1200);
    FADE_EFFECT_BALL* group = &_fadeEffectBall[0][0];
    GSvec* position = positions;
    s32 i = 0;
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    _fadeEffectWork.direction = 0;
    _fadeEffectWork.state = 0;
    _fadeEffectWork.rotationStep = 4.0f;
    _fadeEffectWork.rotation = 0.0f;
    _fadeEffectWork.distanceStep = 48.0f;
    positions[0].param1 = -128.0f;
    positions[0].param2 = 364.0f;
    positions[0].param3 = 0.0f;
    positions[1].param1 = 768.0f;
    positions[1].param2 = 116.0f;
    positions[1].param3 = 0.0f;
    do {
        FADE_EFFECT_BALL* ball = group;
        s32 fade = 0;
        for (s32 j = 0; j < 3; ++j) {
            f32 x = position->param1;
            f32 y = position->param2;
            ball->position.param1 = x;
            f32 z = position->param3;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 255 - fade;
            ++ball;
            fade += 21;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 255 - fade;
            ++ball;
            fade += 21;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 255 - fade;
            ++ball;
            fade += 21;
            ball->position.param1 = x;
            ball->position.param2 = y;
            ball->position.param3 = z;
            ball->rotation = 0.0f;
            ball->alpha = 255 - fade;
            ++ball;
            fade += 21;
        }
        group += 12;
        ++position;
        ++i;
    } while (i < 2);
    _fadeEffect_AdjustParms();
}

static bool fadeEffectHookFunction_tate(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GStexture* texture = (GStexture*)opaque;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_UDLR_FirstInit(texture, 8);
    }
    return _fadeEffectFunction_UDLR_Main(layer, active, elapsed, duration, elapsedSecond, durationSecond, texture);
}

static bool fadeEffectHookFunction_yoko(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GStexture* texture;
    GSgfxLayer* layer;
    texture = (GStexture*)opaque;
    layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_UDLR_FirstInit(texture, 2);
    }
    return _fadeEffectFunction_UDLR_Main(layer, active, elapsed, duration, elapsedSecond, durationSecond, texture);
}

static bool _fadeEffectFunction_UDLR_Main(GSgfxLayer* layer, bool active, f32 elapsed, f32 duration, f32, f32, GStexture* texture) {
    GSvec center;
    f32 progress = elapsed / duration;
    if (timeGetLastFrameTime() != 0) {
        ++_fadeEffectWork.frame;
        _fadeEffectWork.rotation += _fadeEffectWork.rotationStep;
        if (_fadeEffectWork.rotationStep >= 0.0f) {
            _fadeEffectWork.rotationStep = (0.5f * progress) + _fadeEffectWork.rotationStep;
            if (_fadeEffectWork.rotation >= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
        } else {
            _fadeEffectWork.rotationStep = -((0.5f * progress) - _fadeEffectWork.rotationStep);
            if (_fadeEffectWork.rotation <= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
        }
    }
    center.param1 = 320.0f; center.param2 = 240.0f; center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.0f);
    switch (_fadeEffectWork.direction) {
    case 1:
    case 2: {
        center.param1 = 320.0f + _fadeEffectWork.rotation;
        center.param2 = 240.0f;
        break;
    }
    case 4:
    case 8: center.param1 = 320.0f; center.param2 = 240.0f + _fadeEffectWork.rotation; break;
    }
    center.param3 = 0.0f;
    f32 angle = (f32)_fadeEffectWork.frame / ((45.0f * (1.0f - progress)) + 1.0f);
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, angle, progress, 0.4f);
    switch (_fadeEffectWork.direction) {
    case 1:
    case 2: center.param1 = (1.5f * _fadeEffectWork.rotation) + 320.0f; break;
    case 4:
    case 8: center.param2 = (1.5f * _fadeEffectWork.rotation) + 240.0f; break;
    }
    f32 reverseAngle = angle;
    reverseAngle *= -1.5f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, reverseAngle, progress, 0.4f);
    if (timeGetLastFrameTime() != 0) GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    else GSgfxEndBackFBCapture(texture);
    if (_fadeEffectFirstFlag == 0 && active == 0) GSgfxEndBackFBCapture(texture);
    return active;
}

static void _fadeEffectFunction_UDLR_FirstInit(GStexture* arg0, u16 arg1) {
    GSgfxVideoSetLockFrameRate(0);
    _fadeEffectWork.ballTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBC1200);
    _fadeEffectWork.secondTexture = (GStexture*) GSresGetResourceAllGroup(0x0EBD1200);
    _fadeEffectWork.frame = 0;
    _fadeEffectWork.counter = 0;
    _fadeEffectWork.direction = arg1;
    _fadeEffectWork.state = 0;
    _fadeEffectWork.rotationStep = 0.3f;
    _fadeEffectWork.distanceStep = 128.0f;
    _fadeEffectWork.rotation = 0.0f;
    if (_fadeEffectGetRandom(2U) == 0U) {
        f32 rotationStep = _fadeEffectWork.rotationStep;
        f32 negative = -1.0f;
        _fadeEffectWork.rotationStep = rotationStep * negative;
        _fadeEffectWork.distanceStep = _fadeEffectWork.distanceStep * negative;
        switch ((s32) arg1) {                       /* irregular */
        case 1:
            _fadeEffectWork.direction = 2U;
            break;
        case 2:
            _fadeEffectWork.direction = 1U;
            break;
        case 4:
            _fadeEffectWork.direction = 8U;
            break;
        case 8:
            _fadeEffectWork.direction = 4U;
            break;
        }
    }
    _fadeEffect_AdjustParms();
    GSgfxBeginBackFBCapture(arg0, _myBackFB, 0);
}

static s32 _myBackFB(GStexture*, unsigned long, void*) { return 1; }

static void _fadeEffectSnapshotFadeFunction(GSgfxLayer* layer, GStexture* texture, GSvec* center, f32 scale, f32 angle, f32 progress, f32 opacity) {
    FadeMtx transform, rotation;
    GSvec blend, point, output;
    _fadeEffectStartTexture(layer, texture);
    point.param1 = 1.0f; point.param2 = 1.0f; point.param3 = 1.0f;
    output.param1 = 0.0f; output.param2 = 0.0f; output.param3 = 0.0f;
    GSlerpGetLinearInterpolationVector(&blend, &point, &output, opacity);
    point.param1 = scale; point.param2 = scale; point.param3 = scale;
    f32 baseAlpha = (s32)(255.0f * blend.param1);
    s32 alpha = (s32)(baseAlpha * (1.0f - progress));
    f64 dv = scale;
    PSMTXScale(transform, dv, dv, dv);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, transform, transform);
    PSMTXTransApply(transform, transform, center->param1, center->param2, center->param3);
    layer->beginSurface(4);
    point.param1 = -320.0f; point.param2 = -240.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 320.1f; point.param2 = -240.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = -320.0f; point.param2 = 240.1f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 320.1f; point.param2 = 240.1f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    layer->endSurface();
    _fadeEffectEnd(layer);
}

static void _fadeEffectSnapshotTex(GSgfxLayer* layer, GStexture* texture, GSvec* center, f32 u0, f32 v0, f32 u1, f32 v1, f32 scaleY, f32 angle, f32 progress, f32 opacity) {
    FadeMtx transform, texMtx, rotation;
    GSvec point, output, blend;
    _fadeEffectStartTexture(layer, texture);
    point.param1 = 1.0f; point.param2 = 1.0f; point.param3 = 1.0f;
    output.param1 = 0.0f; output.param2 = 0.0f; output.param3 = 0.0f;
    GSlerpGetLinearInterpolationVector(&blend, &point, &output, opacity);
    point.param1 = 1.0f; point.param2 = scaleY; point.param3 = 1.0f;
    f32 baseAlpha = (s32)(255.0f * blend.param1);
    s32 alpha = (s32)(baseAlpha * (1.0f - progress));
    f64 dv = scaleY;
    PSMTXScale(transform, 1.0f, dv, 1.0f);
    PSMTXTransApply(transform, transform, center->param1, center->param2, center->param3);
    PSMTXTrans(texMtx, -0.5f, -0.5f, 0.0f);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, texMtx, texMtx);
    PSMTXTransApply(texMtx, texMtx, 0.5f, 0.5f, 0.0f);
    layer->beginSurface(4);
    point.param1 = -320.0f; point.param2 = -240.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    GXPosition3f32(output.param1, output.param2, output.param3);
    GXColor4u8(255, 255, 255, (u8)alpha);
    point.param1 = u0; point.param2 = v0; point.param3 = 0.0f;
    PSMTXMultVec(texMtx, &point, &output);
    GXTexCoord2f32(output.param1, output.param2);
    point.param1 = 321.0f; point.param2 = -240.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    GXPosition3f32(output.param1, output.param2, output.param3);
    GXColor4u8(255, 255, 255, (u8)alpha);
    point.param1 = u1; point.param2 = v0; point.param3 = 0.0f;
    PSMTXMultVec(texMtx, &point, &output);
    GXTexCoord2f32(output.param1, output.param2);
    point.param1 = -320.0f; point.param2 = 241.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    GXPosition3f32(output.param1, output.param2, output.param3);
    GXColor4u8(255, 255, 255, (u8)alpha);
    point.param1 = u0; point.param2 = v1; point.param3 = 0.0f;
    PSMTXMultVec(texMtx, &point, &output);
    GXTexCoord2f32(output.param1, output.param2);
    point.param1 = 321.0f; point.param2 = 241.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    GXPosition3f32(output.param1, output.param2, output.param3);
    GXColor4u8(255, 255, 255, (u8)alpha);
    point.param1 = u1; point.param2 = v1; point.param3 = 0.0f;
    PSMTXMultVec(texMtx, &point, &output);
    GXTexCoord2f32(output.param1, output.param2);
    layer->endSurface();
    _fadeEffectEnd(layer);
}

static void _fadeEffectSnapshotRotate(GSgfxLayer* layer, GStexture* texture, GSvec* center, f32 scale, GSvec* pivot, f32 angle, f32 progress, f32 opacity) {
    FadeMtx transform, rotation;
    GSvec blend, point, output;
    _fadeEffectStartTexture(layer, texture);
    point.param1 = 1.0f; point.param2 = 1.0f; point.param3 = 1.0f;
    output.param1 = 0.0f; output.param2 = 0.0f; output.param3 = 0.0f;
    GSlerpGetLinearInterpolationVector(&blend, &point, &output, opacity);
    point.param1 = scale; point.param2 = scale; point.param3 = scale;
    f32 baseAlpha = (s32)(255.0f * blend.param1);
    s32 alpha = (s32)(baseAlpha * (1.0f - progress));
    f64 dv = scale;
    PSMTXScale(transform, dv, dv, dv);
    PSMTXTransApply(transform, transform, -pivot->param1, -pivot->param2, 0.0f);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, transform, transform);
    PSMTXTransApply(transform, transform, center->param1, center->param2, center->param3);
    layer->beginSurface(4);
    point.param1 = -320.0f; point.param2 = -240.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 321.0f; point.param2 = -240.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = -320.0f; point.param2 = 241.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 321.0f; point.param2 = 241.0f; point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    layer->endSurface();
    _fadeEffectEnd(layer);
}

static void _fadeEffectMaskFunction(GSgfxLayer* layer, f32 amount) {
    _fadeEffectStartSprites(layer);
    s32 alpha = 255 - (s32)(255.0f * amount);
    layer->beginSurface(4);
    f32 zero = 0.0f;
    f32 width = 640.0f;
    f32 height = 480.0f;
    GXPosition3f32(zero, zero, zero);
    GXColor4u8(0, 0, 0, (u8)alpha);
    GXPosition3f32(width, zero, zero);
    GXColor4u8(0, 0, 0, (u8)alpha);
    GXPosition3f32(zero, height, zero);
    GXColor4u8(0, 0, 0, (u8)alpha);
    GXPosition3f32(width, height, zero);
    GXColor4u8(0, 0, 0, (u8)alpha);
    layer->endSurface();
    _fadeEffectEnd(layer);
}

static void _fadeEffectEnd(GSgfxLayer*) {}

static void _fadeEffectStartSprites(GSgfxLayer* arg0) {
    f32 matrix[4][4];
    u32* flags;
    FadeMatrixSlot* slot;
    GSmtx44Ortho(matrix, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    arg0->fieldD54 = 1;
    arg0->fieldD58 = matrix[0][0];
    arg0->fieldD5C = matrix[0][3];
    arg0->fieldD60 = matrix[1][1];
    arg0->fieldD64 = matrix[1][3];
    arg0->fieldD68 = matrix[2][2];
    arg0->fieldD6C = matrix[2][3];
    slot = arg0->field19A0;
    memcpy(slot->state->matrix, mtxIdent, 0x30);
    flags = &slot->state->flags;
    *flags |= 1;
    arg0->field1684 = 0.0f;
    arg0->field1688 = 30000.0f;
    if ((u8) arg0->field16A7 != 0) {
        if ((u8) arg0->field16A6 != 0) {
            arg0->field170C = (s32) (arg0->field170C | 0x100);
            arg0->field17C4 = (s32) (arg0->field17C4 | 0x100);
        }
        arg0->field170C = (s32) (arg0->field170C | 0x40);
        arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
        arg0->field17C4 = (s32) (arg0->field17C4 | 0x40);
        arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    }
    arg0->field16AC = (s32) (arg0->field16AC | 0x20);
    arg0->field16A8 = (s32) (arg0->field16A8 | 1);
    arg0->field1764 = (s32) (arg0->field1764 | 0x20);
    arg0->field1760 = (s32) (arg0->field1760 | 1);
    if ((s32) arg0->field1994 != 1) {
        arg0->field1994 = 1;
        arg0->field1990 = (void*) ((FadeLayerConfigView*)arg0)->configs[arg0->field1994];
    }
    arg0->field1644 = 1;
    arg0->field1648 = 4;
    arg0->field164C = 5;
    arg0->field1650 = 5;
    arg0->field170C = (s32) (arg0->field170C | 1);
    arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
    arg0->field17C4 = (s32) (arg0->field17C4 | 1);
    arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    arg0->field1656 = 1;
    arg0->field1657 = 1;
    arg0->field1658 = 0;
    arg0->field170C = (s32) (arg0->field170C | 4);
    arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
    arg0->field17C4 = (s32) (arg0->field17C4 | 4);
    arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    arg0->field165C = 0;
    arg0->field1660 = 1;
    arg0->field170C = (s32) (arg0->field170C | 8);
    arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
    arg0->field17C4 = (s32) (arg0->field17C4 | 8);
    arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    arg0->field1664 = 7;
    arg0->field1670 = 0;
    arg0->field1668 = 0;
    arg0->field166C = 7;
    arg0->field1671 = 0;
    arg0->field1672 = 1;
    arg0->field170C = (s32) (arg0->field170C | 0x10);
    arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
    arg0->field17C4 = (s32) (arg0->field17C4 | 0x10);
    arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    arg0->fieldD8C = 0;
    arg0->field16B8 = (s32) (arg0->field16B8 | 2);
    arg0->field16A8 = (s32) (arg0->field16A8 | 2);
    arg0->field1770 = (s32) (arg0->field1770 | 2);
    arg0->field1760 = (s32) (arg0->field1760 | 2);
    arg0->field1998 = 0x98;
    arg0->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
}

static void _fadeEffectStartTexture(GSgfxLayer* arg0, GStexture* arg1) {
    f32 matrix[4][4];
    u32* flags;
    FadeMatrixSlot* slot;
    GSmtx44Ortho(matrix, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    arg0->fieldD54 = 1;
    arg0->fieldD58 = matrix[0][0];
    arg0->fieldD5C = matrix[0][3];
    arg0->fieldD60 = matrix[1][1];
    arg0->fieldD64 = matrix[1][3];
    arg0->fieldD68 = matrix[2][2];
    arg0->fieldD6C = matrix[2][3];
    slot = arg0->field19A0;
    memcpy(slot->state->matrix, mtxIdent, 0x30);
    flags = &slot->state->flags;
    *flags |= 1;
    arg0->field1684 = 0.0f;
    arg0->field1688 = 30000.0f;
    if ((u8) arg0->field16A7 != 0) {
        if ((u8) arg0->field16A6 != 0) {
            arg0->field170C = (s32) (arg0->field170C | 0x100);
            arg0->field17C4 = (s32) (arg0->field17C4 | 0x100);
        }
        arg0->field170C = (s32) (arg0->field170C | 0x40);
        arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
        arg0->field17C4 = (s32) (arg0->field17C4 | 0x40);
        arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    }
    arg0->field16AC = (s32) (arg0->field16AC | 0x20);
    arg0->field16A8 = (s32) (arg0->field16A8 | 1);
    arg0->field1764 = (s32) (arg0->field1764 | 0x20);
    arg0->field1760 = (s32) (arg0->field1760 | 1);
    if ((s32) arg0->field1994 != 1) {
        arg0->field1994 = 1;
        arg0->field1990 = (void*) ((FadeLayerConfigView*)arg0)->configs[arg0->field1994];
    }
    arg0->field1644 = 1;
    arg0->field1648 = 4;
    arg0->field164C = 5;
    arg0->field1650 = 5;
    arg0->field170C = (s32) (arg0->field170C | 1);
    arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
    arg0->field17C4 = (s32) (arg0->field17C4 | 1);
    arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    arg0->field1656 = 1;
    arg0->field1657 = 1;
    arg0->field1658 = 0;
    arg0->field170C = (s32) (arg0->field170C | 4);
    arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
    arg0->field17C4 = (s32) (arg0->field17C4 | 4);
    arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    arg0->field165C = 0;
    arg0->field1660 = 1;
    arg0->field170C = (s32) (arg0->field170C | 8);
    arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
    arg0->field17C4 = (s32) (arg0->field17C4 | 8);
    arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    arg0->field1664 = 7;
    arg0->field1670 = 0;
    arg0->field1668 = 0;
    arg0->field166C = 7;
    arg0->field1671 = 0;
    arg0->field1672 = 1;
    arg0->field170C = (s32) (arg0->field170C | 0x10);
    arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
    arg0->field17C4 = (s32) (arg0->field17C4 | 0x10);
    arg0->field1760 = (s32) (arg0->field1760 | 0x40);
    arg0->fieldD8C = 0;
    arg0->field16B8 = (s32) (arg0->field16B8 | 2);
    arg0->field16A8 = (s32) (arg0->field16A8 | 2);
    arg0->field1770 = (s32) (arg0->field1770 | 2);
    arg0->field1760 = (s32) (arg0->field1760 | 2);
    arg0->field1998 = 0x98;
    arg0->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 1, 1, 4));
    if (((void *) arg0->field1740 != arg1) || ((void *) arg0->field17F8 != arg1) || ((u8) arg1->dirty != 0)) {
        arg0->field1740 = arg1;
        arg0->field173C = (s32) (arg0->field173C | 1);
        arg0->field17F8 = arg1;
        arg0->field17F4 = (s32) (arg0->field17F4 | 1);
    }
}

static void _fadeEffect_AdjustParms() {
    _fadeEffectWork.rotationStep = (f32) (_fadeEffectWork.rotationStep / 3.0f);
    _fadeEffectWork.rotation = (f32) (_fadeEffectWork.rotation / 3.0f);
    _fadeEffectWork.distanceStep = (f32) (_fadeEffectWork.distanceStep / 3.0f);
}

static unsigned long _fadeEffectGetRandom(unsigned long range) {
    return ((HSD_Rand() << 16) | HSD_Rand()) % range;
}

extern "C" void fadeEffectInit() { _fadeEffectFirstFlag = 1; }

extern "C" s32 __float_nan[];
// Three Newton steps are the SDK square-root expansion used by these fades.
static inline f32 fadeSqrt(f32 value) {
    if (value > 0.0f) {
        f64 estimate = __frsqrte((f64)value);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * value);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * value);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * value);
        return (f32)(value * estimate);
    } else if (value < 0.0) return *(f32*)__float_nan;
    else {
        union { f32 f; u32 u; } representation;
        representation.f = value;
        s32 bits = representation.u;
        int classification;
        switch (bits & 0x7f800000) {
        case 0x7f800000: classification = (bits & 0x7fffff) ? 1 : 2; break;
        case 0: classification = (bits & 0x7fffff) ? 5 : 3; break;
        default: classification = 4; break;
        }
        if (classification == 1) return *(f32*)__float_nan;
        return value;
    }
}

// The random pair is evaluated low word first in the original update paths.
#define FADE_UPDATE_RANDOM(range) (((unsigned long)(HSD_Rand() << 16) | HSD_Rand()) % (range))

static void _fadeDistortionDoAverage(unsigned long range) {
    FadeUV* coord;
    FadeUV* uv;
    int columns, rows, x, y;
    columns = _fadeDistortionWork.columns;
    rows = _fadeDistortionWork.rows;
    f32 du = 1.0f / (columns - 1);
    f32 dv = 1.0f / (rows - 1);
    if (_fadeDistortionWork.uv) {
        uv = _fadeDistortionWork.uv;
        for (y = 0; y < rows; ++y) {
            coord = uv;
            for (x = 0; x < columns; ++x) {
                f32 su = FADE_UPDATE_RANDOM(2) == 0 ? 1.0f : -1.0f;
                f32 sv = FADE_UPDATE_RANDOM(2) == 0 ? 1.0f : -1.0f;
                f32 ru = su * (f32)FADE_UPDATE_RANDOM(range);
                coord->u = ru / 1000.0f + du * x;
                coord->v = dv * y + (sv * (f32)FADE_UPDATE_RANDOM(range)) / 1000.0f;
                ++uv; ++coord;
            }
        }
    }
}

static void _fadeDistortionDo(unsigned long range) {
    FadeUV* coord;
    FadeUV* uv;
    int cx, cy, columns, rows, x, y, radius;
    columns = _fadeDistortionWork.columns;
    rows = _fadeDistortionWork.rows;
    f32 du = 1.0f / (columns - 1);
    f32 dv = 1.0f / (rows - 1);
    if (_fadeDistortionWork.uv) {
        uv = _fadeDistortionWork.uv;
        radius = rows * rows / 16;
        cx = columns / 2;
        cy = rows / 2;
        for (y = 0; y < rows; ++y) {
            coord = uv;
            for (x = 0; x < columns; ++x) {
                f32 su, sv;
                if ((x-cx)*(x-cx)+(y-cy)*(y-cy) < radius) {
                    if (FADE_UPDATE_RANDOM(2) == 0) su = 1.0f; else su = -1.0f;
                    if (FADE_UPDATE_RANDOM(2) == 0) sv = 1.0f; else sv = -1.0f;
                } else {
                    if (x < cx) su = FADE_UPDATE_RANDOM(4) == 0 ? -1.0f : 1.0f;
                    else su = FADE_UPDATE_RANDOM(4) == 0 ? 1.0f : -1.0f;
                    if (y < cy) sv = FADE_UPDATE_RANDOM(4) == 0 ? -1.0f : 1.0f;
                    else sv = FADE_UPDATE_RANDOM(4) == 0 ? 1.0f : -1.0f;
                }
                f32 ru = su * (f32)FADE_UPDATE_RANDOM(range);
                coord->u = ru / 1000.0f + du * x;
                coord->v = dv * y + (sv * (f32)FADE_UPDATE_RANDOM(range)) / 1000.0f;
                ++uv; ++coord;
            }
        }
    }
}

static void _fadeDistortionDoSecond(unsigned long range, bool inward) {
    FadeUV* coord;
    FadeUV* uv;
    int cx, cy, columns, rows, x, y, radius;
    columns = _fadeDistortionWork.columns;
    rows = _fadeDistortionWork.rows;
    f32 du = 1.0f / (columns - 1);
    f32 dv = 1.0f / (rows - 1);
    if (_fadeDistortionWork.uv) {
        uv = _fadeDistortionWork.uv;
        radius = rows * rows / 16;
        cx = columns / 2;
        cy = rows / 2;
        for (y = 0; y < rows; ++y) {
            coord = uv;
            for (x = 0; x < columns; ++x) {
                f32 su, sv;
                if ((x-cx)*(x-cx)+(y-cy)*(y-cy) < radius) {
                    if (FADE_UPDATE_RANDOM(2) == 0) su = 1.0f; else su = -1.0f;
                    if (FADE_UPDATE_RANDOM(2) == 0) sv = 1.0f; else sv = -1.0f;
                } else if (inward) {
                    if (x < cx) su = FADE_UPDATE_RANDOM(3) == 0 ? -1.0f : 1.0f;
                    else su = FADE_UPDATE_RANDOM(3) == 0 ? 1.0f : -1.0f;
                    if (y < cy) sv = FADE_UPDATE_RANDOM(3) == 0 ? -1.0f : 1.0f;
                    else sv = FADE_UPDATE_RANDOM(3) == 0 ? 1.0f : -1.0f;
                } else {
                    if (x < cx) su = FADE_UPDATE_RANDOM(3) != 0 ? -1.0f : 1.0f;
                    else su = FADE_UPDATE_RANDOM(3) != 0 ? 1.0f : -1.0f;
                    if (y < cy) sv = FADE_UPDATE_RANDOM(3) != 0 ? -1.0f : 1.0f;
                    else sv = FADE_UPDATE_RANDOM(3) != 0 ? 1.0f : -1.0f;
                }
                f32 ru = su * (f32)FADE_UPDATE_RANDOM(range);
                coord->u = ru / 1000.0f + du * x;
                coord->v = dv * y + (sv * (f32)FADE_UPDATE_RANDOM(range)) / 1000.0f;
                ++uv; ++coord;
            }
        }
    }
}

static void _fadeDistortionStripDoYoko() {
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    if (!_fadeDistortionWork.points) return;
    if (!_fadeDistortionWork.uv) return;
    bool forward = _fadeEffectWork.direction < 2;
    s16 step = _fadeEffectWork.direction % 2 == 0 ? 5 : -5;
    FadeGridPoint* points = _fadeDistortionWork.points;
    FadeUV* uv = _fadeDistortionWork.uv;
    f32 width = _fadeDistortionWork.width;
    f32 height = _fadeDistortionWork.height;
    f32 jitter = 0.5f / height;
    for (int y = 0; y < rows; ++y) {
        FadeGridPoint* point = points;
        FadeUV* coord = uv;
        for (int x = 0; x < columns; ++x) {
            if (forward) {
                if (y % 2 == 0) { if (point->y < _fadeEffectWork.frame * 18) point->x += step; }
                else if (point->y < _fadeEffectWork.frame * 27) point->x += step;
            } else {
                if (y % 2 == 0) { if (point->y > 480 - _fadeEffectWork.frame * 18) point->x += step; }
                else if (point->y > 480 - _fadeEffectWork.frame * 27) point->x += step;
            }
            coord->u = point->x / width;
            int sign = FADE_UPDATE_RANDOM(2) != 0 ? -1 : 1;
            coord->v = jitter * sign + point->y / height;
            ++point; ++coord; ++points; ++uv;
        }
    }
}

static void _fadeDistortionStripDoTate() {
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    if (!_fadeDistortionWork.points) return;
    if (!_fadeDistortionWork.uv) return;
    bool forward = _fadeEffectWork.direction % 2 == 0;
    s16 step = _fadeEffectWork.direction < 2 ? 5 : -5;
    FadeGridPoint* points = _fadeDistortionWork.points;
    FadeUV* uv = _fadeDistortionWork.uv;
    f32 width = _fadeDistortionWork.width;
    f32 height = _fadeDistortionWork.height;
    f32 jitter = 0.5f / width;
    for (int y = 0; y < rows; ++y) {
        FadeGridPoint* point = points;
        FadeUV* coord = uv;
        for (int x = 0; x < columns; ++x) {
            if (forward) {
                if (x % 2 == 0) { if (point->x < _fadeEffectWork.frame * 16) point->y += step; }
                else if (point->x < _fadeEffectWork.frame * 24) point->y += step;
            } else {
                if (x % 2 == 0) { if (point->x > 640 - _fadeEffectWork.frame * 16) point->y += step; }
                else if (point->x > 640 - _fadeEffectWork.frame * 24) point->y += step;
            }
            int sign = FADE_UPDATE_RANDOM(2) != 0 ? -1 : 1;
            coord->u = jitter * sign + point->x / width;
            coord->v = point->y / height;
            ++point; ++coord; ++points; ++uv;
        }
    }
}

struct FadeHexaRibbon { s16 x, y, width, height; };
struct FadeHexaLine {
    f32 speed;
    FadeUV points[34];
    s16 count, distance;
    u8 direction, active;
    u8 padding[2];
};
typedef char FadeHexaRibbonSize[sizeof(FadeHexaRibbon) == 8 ? 1 : -1];
typedef char FadeHexaLineSize[sizeof(FadeHexaLine) == 0x11c ? 1 : -1];
typedef char FadeHexaLineDistanceOffset[offsetof(FadeHexaLine, distance) == 0x116 ? 1 : -1];
typedef char FadeHexaLineDirectionOffset[offsetof(FadeHexaLine, direction) == 0x118 ? 1 : -1];
typedef char FadeHexaLineActiveOffset[offsetof(FadeHexaLine, active) == 0x119 ? 1 : -1];
typedef char FadeHexaLineCountOffset[offsetof(FadeHexaLine, count) == 0x114 ? 1 : -1];

static void _fadeVirtualHexaDecayRibbonUpdate() {
    for (int i = 0; i < _fadeHexaRibbonNum; ++i) {
        FadeHexaRibbon* ribbon = (FadeHexaRibbon*)_fadeHexaRibbon + i;
        ++ribbon->y;
        ribbon->width += 2;
    }
    if (_fadeHexaRibbonNum < 16 && _fadeEffectWork.frame % 5 == 0) {
        FadeHexaRibbon* ribbon = (FadeHexaRibbon*)((u8*)_fadeHexaRibbon + (_fadeHexaRibbonNum * 8));
        ribbon->x = 0;
        ribbon->y = FADE_UPDATE_RANDOM(421) + 30;
        ribbon->width = 640;
        ribbon->height = 10;
        ++_fadeHexaRibbonNum;
    }
}

static void _fadeVirtualHexaDecayInit() {
    _fadeHexaLine[0] = GSmemAllocAlign(0x1514, 32);
    _fadeHexaLine[1] = GSmemAllocAlign(0x1514, 32);
    for (int side = 0; side < 2; ++side) {
        s16 y = side == 0 ? 0 : 490;
        f32 offset = side == 0 ? 0.0f : 17.320507f;
        for (int i = 0; i < 19; ++i) {
            FadeHexaLine* line = (FadeHexaLine*)_fadeHexaLine[side] + i;
            line->speed = 4.4f * HSD_Randf() + 0.1f;
            line->count = 2;
            line->points[0].u = 34.641014f * i + offset;
            line->points[0].v = y;
            line->points[1].u = line->points[0].u;
            line->points[1].v = line->points[0].v;
            line->direction = FADE_UPDATE_RANDOM(2) + 1;
            line->distance = 0;
            line->active = 1;
        }
    }
    _fadeHexaRibbon = GSmemAllocAlign(128, 32);
    _fadeHexaRibbonNum = 0;
    _fadeHexaDecayTime = 0.0f;
    _fadeHexaTexture = GStextureCreate(8, 8, 0x40, 0, 0);
    _fadeHexaNoiseVF = (GSgfxVF*)GSmemAllocAlign(0x440, 32);
    if (_fadeHexaTexture) {
        GStextureSetWrap(_fadeHexaTexture, 1, 1);
        GStextureSetFilter(_fadeHexaTexture, 1, 1, 1);
        u16* image = (u16*)GStextureLockImage(_fadeHexaTexture, 0);
        for (int i = 0; i < 16; ++i) *image++ = (i / 2) % 2 == 0 ? 0xffff : 0x2222;
        GStextureUnlockImage(_fadeHexaTexture);
    }
    if (_fadeHexaNoiseVF) {
        GSgfxVFInit(_fadeHexaNoiseVF);
        GSgfxVFCreate(_fadeHexaNoiseVF);
        GSgfxVFSetElement(_fadeHexaNoiseVF, 9, 1, 4, 0);
        GSgfxVFSetElement(_fadeHexaNoiseVF, 11, 1, 5, 0);
        GSgfxVFSetElement(_fadeHexaNoiseVF, 13, 1, 4, 0);
        GSgfxVFSetElement(_fadeHexaNoiseVF, 14, 1, 4, 0);
    }
}
bool fadeEffectHookFunction_distortion_yoko(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GSgfxLayer* layer;
    GStexture* texture;
    layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeDistortionInit();
        _fadeEffectWork.rotation = 0.0f;
        s32 rand0 = HSD_Rand();
        s32 hi0 = HSD_Rand();
        if ((u32)(((hi0 << 0x10) | rand0) & 1) == 0) {
            _fadeEffectWork.rotationStep = 0.4f;
            _fadeEffectWork.distanceStep = 128.0f;
        } else {
            _fadeEffectWork.rotationStep = -0.4f;
            _fadeEffectWork.distanceStep = -128.0f;
        }
        s32 rand1 = HSD_Rand();
        s32 hi1 = HSD_Rand();
        s32 dir;
        if ((u32)(((hi1 << 0x10) | rand1) & 1) != 0) {
            dir = 2;
        } else {
            dir = 1;
        }
        _fadeEffectWork.direction = (u16)dir;
        s32 rand2 = HSD_Rand();
        s32 hi2 = HSD_Rand();
        s32 st;
        if ((u32)(((hi2 << 0x10) | rand2) & 1) != 0) {
            st = 1;
        } else {
            st = 0;
        }
        _fadeEffectWork.state = (u16)st;
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !active) {
        _fadeDistortionQuit();
        GSgfxEndBackFBCapture(texture);
        return active;
    }
    f32 progress = elapsed / duration;
    f32 progressSecond = elapsedSecond / durationSecond;
    if (timeGetLastFrameTime() != 0) {
        f32 pos = _fadeEffectWork.rotation + _fadeEffectWork.rotationStep;
        f32 step = _fadeEffectWork.rotationStep;
        ++_fadeEffectWork.frame;
        _fadeEffectWork.rotation = pos;
        if (step >= 0.0f) {
            _fadeEffectWork.rotationStep = 0.5f * progress + step;
            if (pos >= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
        } else {
            _fadeEffectWork.rotationStep = -(0.5f * progress - step);
            if (pos <= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
        }
        _fadeDistortionDoAverage(10);
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(texture);
    }
    _fadeEffectMaskFunction(layer, progress);
    FADE_LAYER_SETUP
    layer->field1998 = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 1, 1, 4));
    FADE_LAYER_BIND_TEXTURE(texture)
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    FadeGridPoint* points = _fadeDistortionWork.points;
    FadeUV* uv = _fadeDistortionWork.uv;
    if (!points || !uv) return false;
    int count = columns * 2;
    s32 alpha = (s32)(255.0f * (1.0f - fadeSqrt(progress)));
    for (int x = 1; x < rows; ++x) {
        layer->beginSurface(count);
        for (int y = 0; y < columns; ++y) {
            int index = x * columns + y;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(uv[index].u, uv[index].v);
            index = (x - 1) * columns + y;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(uv[index].u, uv[index].v);
        }
        layer->endSurface();
    }
    GSvec center;
    switch (_fadeEffectWork.direction) {
    case 1:
    case 2:
        center.param2 = 240.0f;
        center.param1 = 320.0f + _fadeEffectWork.rotation;
        break;
    case 3:
        break;
    case 4:
    case 8:
        center.param1 = 320.0f;
        center.param2 = 240.0f + _fadeEffectWork.rotation;
        break;
    }
    center.param3 = 0.0f;
    f32 sign = _fadeEffectWork.state != 0 ? 3.0f : -3.0f;
    f32 remaining = 1.0f - progress;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, sign * (remaining * (1.0f - progressSecond)), progress, 0.5f);
    return active;
}

bool fadeEffectHookFunction_distortion_strip_yoko(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void* opaque) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (!opaque) return active;
    GStexture* texture = (GStexture*)opaque;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        GSgfxVideoSetLockFrameRate(true);
        _fadeDistortionStripInit(2, 240);
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !active) {
        _fadeDistortionStripQuit();
        GSgfxEndBackFBCapture(texture);
        return active;
    }
    f32 progress = elapsed / duration;
    _fadeEffectMaskFunction(layer, progress);
    if (timeGetLastFrameTime() != 0) {
        if (progress < 0.00001f) _fadeDistortionStripDoYoko();
        ++_fadeEffectWork.frame;
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    } else GSgfxEndBackFBCapture(texture);

    f32 matrix[4][4];
    u32* flags;
    FadeMatrixSlot* slot;
    GSmtx44Ortho(matrix, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    layer->fieldD54 = 1;
    layer->fieldD58 = matrix[0][0];
    layer->fieldD5C = matrix[0][3];
    layer->fieldD60 = matrix[1][1];
    layer->fieldD64 = matrix[1][3];
    layer->fieldD68 = matrix[2][2];
    layer->fieldD6C = matrix[2][3];
    slot = layer->field19A0;
    memcpy(slot->state->matrix, mtxIdent, 0x30);
    flags = &slot->state->flags;
    *flags |= 1;
    layer->field1684 = 0.0f;
    layer->field1688 = 30000.0f;
    if ((u8) layer->field16A7 != 0) {
        if ((u8) layer->field16A6 != 0) {
            layer->field170C = (s32) (layer->field170C | 0x100);
            layer->field17C4 = (s32) (layer->field17C4 | 0x100);
        }
        layer->field170C = (s32) (layer->field170C | 0x40);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 0x40);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
    }
    layer->field16AC = (s32) (layer->field16AC | 0x20);
    layer->field16A8 = (s32) (layer->field16A8 | 1);
    layer->field1764 = (s32) (layer->field1764 | 0x20);
    layer->field1760 = (s32) (layer->field1760 | 1);
    if ((s32) layer->field1994 != 1) {
        layer->field1994 = 1;
        layer->field1990 = (void*) ((FadeLayerConfigView*)layer)->configs[layer->field1994];
    }
    layer->field1644 = 1;
    layer->field1648 = 4;
    layer->field164C = 5;
    layer->field1650 = 5;
    layer->field170C = (s32) (layer->field170C | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 1);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    layer->field1656 = 1;
    layer->field1657 = 1;
    layer->field1658 = 0;
    layer->field170C = (s32) (layer->field170C | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 4);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    layer->field165C = 0;
    layer->field1660 = 1;
    layer->field170C = (s32) (layer->field170C | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 8);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    layer->field1664 = 7;
    layer->field1670 = 0;
    layer->field1668 = 0;
    layer->field166C = 7;
    layer->field1671 = 0;
    layer->field1672 = 1;
    layer->field170C = (s32) (layer->field170C | 0x10);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 0x10);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    layer->fieldD8C = 0;
    layer->field16B8 = (s32) (layer->field16B8 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 2);
    layer->field1770 = (s32) (layer->field1770 | 2);
    layer->field1760 = (s32) (layer->field1760 | 2);
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    layer->field1998 = 0x98;
    if (((void *) layer->field1740 != texture) || ((void *) layer->field17F8 != texture) || ((u8) texture->dirty != 0)) {
        layer->field1740 = texture;
        layer->field173C = (s32) (layer->field173C | 1);
        layer->field17F8 = texture;
        layer->field17F4 = (s32) (layer->field17F4 | 1);
    }

    FadeGridPoint* points = _fadeDistortionWork.points;
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    FadeUV* uv = _fadeDistortionWork.uv;
    if (!points || !uv) return false;
    f32 opacity = progress < 0.00001f ? 1.0f - progress : 1.0f - fadeSqrt(progress);
    f32 alpha = 255.0f * opacity;
    bool forward = _fadeEffectWork.direction % 2 == 0;
    u8 alphaFirst, alphaSecond;
    if (forward) { alphaFirst = (u8)alpha; alphaSecond = (u8)(alpha * 1.0f); }
    else { alphaSecond = (u8)alpha; alphaFirst = (u8)(alpha * 1.0f); }
    u16 count = rows * 2;
    for (int x = 1; x < columns; ++x) {
        layer->beginSurface(count);
        for (int y = 0; y < rows; ++y) {
            int index = x + y * columns;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alphaFirst);
            GXTexCoord2f32(forward ? uv[index].u : 1.0f, uv[index].v);
            --index;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alphaSecond);
            GXTexCoord2f32(forward ? 0.0f : uv[index].u, uv[index].v);
        }
        layer->endSurface();
    }
    return active;
}

bool fadeEffectHookFunction_distortion_strip_tate(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32, f32, void* opaque) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (!opaque) return active;
    GStexture* texture = (GStexture*)opaque;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        GSgfxVideoSetLockFrameRate(true);
        _fadeDistortionStripInit(320, 2);
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !active) {
        _fadeDistortionStripQuit();
        GSgfxEndBackFBCapture(texture);
        return active;
    }
    f32 progress = elapsed / duration;
    _fadeEffectMaskFunction(layer, progress);
    if (timeGetLastFrameTime() != 0) {
        if (progress < 0.00001f) _fadeDistortionStripDoTate();
        ++_fadeEffectWork.frame;
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    } else GSgfxEndBackFBCapture(texture);

    f32 matrix[4][4];
    u32* flags;
    FadeMatrixSlot* slot;
    GSmtx44Ortho(matrix, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    layer->fieldD54 = 1;
    layer->fieldD58 = matrix[0][0];
    layer->fieldD5C = matrix[0][3];
    layer->fieldD60 = matrix[1][1];
    layer->fieldD64 = matrix[1][3];
    layer->fieldD68 = matrix[2][2];
    layer->fieldD6C = matrix[2][3];
    slot = layer->field19A0;
    memcpy(slot->state->matrix, mtxIdent, 0x30);
    flags = &slot->state->flags;
    *flags |= 1;
    layer->field1684 = 0.0f;
    layer->field1688 = 30000.0f;
    if ((u8) layer->field16A7 != 0) {
        if ((u8) layer->field16A6 != 0) {
            layer->field170C = (s32) (layer->field170C | 0x100);
            layer->field17C4 = (s32) (layer->field17C4 | 0x100);
        }
        layer->field170C = (s32) (layer->field170C | 0x40);
        layer->field16A8 = (s32) (layer->field16A8 | 0x40);
        layer->field17C4 = (s32) (layer->field17C4 | 0x40);
        layer->field1760 = (s32) (layer->field1760 | 0x40);
    }
    layer->field16AC = (s32) (layer->field16AC | 0x20);
    layer->field16A8 = (s32) (layer->field16A8 | 1);
    layer->field1764 = (s32) (layer->field1764 | 0x20);
    layer->field1760 = (s32) (layer->field1760 | 1);
    if ((s32) layer->field1994 != 1) {
        layer->field1994 = 1;
        layer->field1990 = (void*) ((FadeLayerConfigView*)layer)->configs[layer->field1994];
    }
    layer->field1644 = 1;
    layer->field1648 = 4;
    layer->field164C = 5;
    layer->field1650 = 5;
    layer->field170C = (s32) (layer->field170C | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 1);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    layer->field1656 = 1;
    layer->field1657 = 1;
    layer->field1658 = 0;
    layer->field170C = (s32) (layer->field170C | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 4);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    layer->field165C = 0;
    layer->field1660 = 1;
    layer->field170C = (s32) (layer->field170C | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 8);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    layer->field1664 = 7;
    layer->field1670 = 0;
    layer->field1668 = 0;
    layer->field166C = 7;
    layer->field1671 = 0;
    layer->field1672 = 1;
    layer->field170C = (s32) (layer->field170C | 0x10);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 0x10);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    layer->fieldD8C = 0;
    layer->field16B8 = (s32) (layer->field16B8 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 2);
    layer->field1770 = (s32) (layer->field1770 | 2);
    layer->field1760 = (s32) (layer->field1760 | 2);
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    layer->field1998 = 0x98;
    if (((void *) layer->field1740 != texture) || ((void *) layer->field17F8 != texture) || ((u8) texture->dirty != 0)) {
        layer->field1740 = texture;
        layer->field173C = (s32) (layer->field173C | 1);
        layer->field17F8 = texture;
        layer->field17F4 = (s32) (layer->field17F4 | 1);
    }

    FadeGridPoint* points = _fadeDistortionWork.points;
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    FadeUV* uv = _fadeDistortionWork.uv;
    if (!points || !uv) return false;
    f32 opacity = progress < 0.00001f ? 1.0f - progress : 1.0f - fadeSqrt(progress);
    f32 alpha = 255.0f * opacity;
    bool forward = _fadeEffectWork.direction < 2;
    u8 alphaFirst, alphaSecond;
    if (forward) { alphaFirst = (u8)alpha; alphaSecond = (u8)(alpha * 1.0f); }
    else { alphaSecond = (u8)alpha; alphaFirst = (u8)(alpha * 1.0f); }
    u16 count = columns * 2;
    int row = columns;
    for (int y = 1; y < rows; ++y) {
        layer->beginSurface(count);
        for (int x = 0; x < columns; ++x) {
            int index = row + x;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alphaFirst);
            GXTexCoord2f32(uv[index].u, forward ? uv[index].v : 1.0f);
            index = (y - 1) * columns + x;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alphaSecond);
            GXTexCoord2f32(uv[index].u, forward ? 0.0f : uv[index].v);
        }
        layer->endSurface();
        row += columns;
    }
    return active;
}

static void _fadeVirtualHexaDecayLineUpdate() {
    for (int side = 0; side < 2; ++side) {
        int sign = side == 0 ? 1 : -1;
        f32 diagonal = 0.5f * sign;
        for (int i = 0; i < 19; ++i) {
            FadeHexaLine* line = (FadeHexaLine*)_fadeHexaLine[side] + i;
            if (line->count < 34) {
                line->distance = (s16)(line->distance + line->speed);
                s16 amount = line->distance < 20 ? line->distance : 20;
                FadeUV* previous = &line->points[line->count - 2];
                FadeUV* current = &line->points[line->count - 1];
                f32 distance = amount;
                switch (line->direction) {
                case 0: current->v = sign * distance + previous->v; break;
                case 1:
                    current->u = distance * 0.8660254f + previous->u;
                    current->v = distance * diagonal + previous->v; break;
                case 2:
                    current->u = -(distance * 0.8660254f - previous->u);
                    current->v = distance * diagonal + previous->v; break;
                }
            }
            while (line->distance > 20 && line->count < 34) {
                ++line->count;
                line->distance -= 20;
                line->direction = line->direction == 0 ? FADE_UPDATE_RANDOM(2) + 1 : 0;
                FadeUV* previous = &line->points[line->count - 2];
                FadeUV* current = &line->points[line->count - 1];
                f32 distance = line->distance;
                switch (line->direction) {
                case 0:
                    current->u = previous->u;
                    current->v = sign * distance + previous->v; break;
                case 1:
                    current->u = distance * 0.8660254f + previous->u;
                    current->v = distance * diagonal + previous->v; break;
                case 2:
                    current->u = -(distance * 0.8660254f - previous->u);
                    current->v = distance * diagonal + previous->v; break;
                }
            }
            if (line->speed < 9.0f) line->speed += 0.2f;
        }
    }
}

bool fadeEffectHookFunction_ball_second(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GSgfxLayer* layer;
    s32 alpha;
    GStexture* texture;
    layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectBallSecondInit();
    }
    if (_fadeEffectFirstFlag == 0 && !active) {
        _fadeEffectBallSecondQuit();
        return active;
    }
    f32 progress = elapsed / duration;
    f32 progressSecond = elapsedSecond / durationSecond;
    if (timeGetLastFrameTime() != 0) {
        f32 distance = _fadeEffectWork.rotation + _fadeEffectWork.rotationStep;
        f32 limit = _fadeEffectWork.distanceStep;
        ++_fadeEffectWork.frame;
        _fadeEffectWork.rotation = distance;
        if (distance >= limit) _fadeEffectWork.rotation = limit;
    }
    _fadeEffectMaskFunction(layer, progress);
    GSvec center;
    center.param1 = 320.0f;
    center.param2 = 240.0f;
    center.param3 = 0.0f;
    progressSecond = progressSecond * progressSecond;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, progressSecond);
    _fadeEffectStartTexture(layer, _fadeEffectWork.ballTexture);
    f32 movement[2], rotation[2];
    movement[0] = _fadeEffectWork.rotation;
    rotation[0] = 360.0f * (_fadeEffectWork.rotation / 471.23892f);
    movement[1] = -_fadeEffectWork.rotation;
    rotation[1] = -rotation[0];
    f32 x;
    for (int side = 0; side < 2; ++side) {
        FADE_EFFECT_BALL* balls = _fadeEffectBall[side];
        for (int i = 11; i > 0; --i) {
            FADE_EFFECT_BALL* ball = balls + i;
            if (timeGetLastFrameTime() != 0 && (_fadeEffectWork.frame & 3) == 0) {
                ball->position.param1 = ball[-1].position.param1;
                ball->position.param2 = ball[-1].position.param2;
                ball->position.param3 = ball[-1].position.param3;
                ball->rotation = ball[-1].rotation;
            }
            if (!(x > 790.0f) && !(x < -150.0f)) {
                alpha = (s32)((1.0f - progress) * ball->alpha);
                _dispball(layer, &ball->position, 0.5f, ball->rotation, alpha);
            }
        }
        f32 angle = balls->rotation + rotation[side];
        if (angle <= 0.0f) angle += 360.0f;
        else if (angle >= 360.0f) angle -= 360.0f;
        if (timeGetLastFrameTime() != 0) balls->rotation = angle;
        x = balls->position.param1 + movement[side];
        if (timeGetLastFrameTime() != 0) balls->position.param1 = x;
        if (!(x > 790.0f) && !(x < -150.0f)) {
            f32 y = balls->position.param2 - movement[side];
            if (y > 405.0f) y = 405.0f;
            else if (y < 75.0f) y = 75.0f;
            balls->position.param2 = y;
            _dispball(layer, &balls->position, 0.5f, balls->rotation, alpha);
        }
    }
    _fadeEffectEnd(layer);
    return active;
}

bool fadeEffectHookFunction_ball(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_ball_FirstInit();
    }
    f32 progress = elapsed / duration;
    f32 progressSecond = elapsedSecond / durationSecond;
    if (timeGetLastFrameTime() != 0) {
        f32 distance = _fadeEffectWork.rotation + _fadeEffectWork.rotationStep;
        ++_fadeEffectWork.frame;
        _fadeEffectWork.rotation = distance;
        if (distance >= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
    }
    _fadeEffectMaskFunction(layer, progress);
    if (!opaque) return active;
    GSvec center;
    center.param1 = 320.0f;
    center.param2 = 240.0f;
    center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, (GStexture*)opaque, &center, 1.0f, 0.0f, progress, progressSecond);
    _fadeEffectStartTexture(layer, _fadeEffectWork.ballTexture);
    f32 opacity = 1.0f - progress;
    f32 movement[2], rotation[2];
    movement[0] = _fadeEffectWork.rotation;
    rotation[0] = 360.0f * (_fadeEffectWork.rotation / 804.24774f);
    movement[1] = -_fadeEffectWork.rotation;
    rotation[1] = -rotation[0];
    for (int side = 0; side < 2; ++side) {
        FADE_EFFECT_BALL* balls = _fadeEffectBall[side];
        for (int i = 11; i > 0; --i) {
            FADE_EFFECT_BALL* ball = balls + i;
            if (timeGetLastFrameTime() != 0 && (_fadeEffectWork.frame & 3) == 0) {
                ball->position.param1 = ball[-1].position.param1;
                ball->position.param2 = ball[-1].position.param2;
                ball->position.param3 = ball[-1].position.param3;
                ball->rotation = ball[-1].rotation;
            }
            _dispball(layer, &ball->position, 1.0f, ball->rotation, (int)(opacity * ball->alpha));
        }
        f32 angle = balls->rotation;
        if (timeGetLastFrameTime() != 0) {
            angle += rotation[side];
            if (angle <= 0.0f) angle += 360.0f;
            else if (angle >= 360.0f) angle -= 360.0f;
            balls->rotation = angle;
        }
        f32 x = balls->position.param1;
        if (timeGetLastFrameTime() != 0) {
            x += movement[side];
            if (x > 896.0f) x = 896.0f;
            else if (x < -256.0f) x = -256.0f;
            balls->position.param1 = x;
        }
        _dispball(layer, &balls->position, 1.0f, balls->rotation, (int)(opacity * balls->alpha));
    }
    _fadeEffectEnd(layer);
    return active;
}

bool fadeEffectHookFunction_four_ball(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GSgfxLayer* layer;
    GStexture* texture;
    GSvec center;
    layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFourBallInit();
    }
    if (_fadeEffectFirstFlag == 0 && !active) return active;
    f32 progress = elapsed / duration;
    f32 progressSecond = elapsedSecond / durationSecond;
    if (timeGetLastFrameTime() != 0) {
        f32 distance = _fadeEffectWork.rotation + _fadeEffectWork.rotationStep;
        f32 limit = _fadeEffectWork.distanceStep;
        ++_fadeEffectWork.frame;
        _fadeEffectWork.rotation = distance;
        if (distance >= limit) _fadeEffectWork.rotation = limit;
    }
    _fadeEffectMaskFunction(layer, progress);
    center.param1 = 320.0f;
    center.param2 = 240.0f;
    center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, progressSecond);
    _fadeEffectStartTexture(layer, _fadeEffectWork.ballTexture);
    f32 opacity = 1.0f - progress;
    f32 movement[2], rotation[2];
    movement[0] = _fadeEffectWork.rotation;
    rotation[0] = 360.0f * (_fadeEffectWork.rotation / 408.40704f);
    movement[1] = -_fadeEffectWork.rotation;
    rotation[1] = -rotation[0];
    for (int side = 0; side < 2; ++side) {
        FADE_EFFECT_BALL* balls = _fadeEffectBall[side];
        for (int i = 11; i > 0; --i) {
            FADE_EFFECT_BALL* ball = balls + i;
            if (timeGetLastFrameTime() != 0 && (_fadeEffectWork.frame % 3) == 0) {
                ball->position.param1 = ball[-1].position.param1;
                ball->position.param2 = ball[-1].position.param2;
                ball->position.param3 = ball[-1].position.param3;
                ball->rotation = ball[-1].rotation;
            }
            f32 x = ball->position.param1;
            if (!(x > 770.0f) && !(x < -130.0f)) {
                center.param1 = x;
                f32 a = ball->alpha;
                center.param2 = ball->position.param2;
                f32 scaled = opacity * a;
                center.param3 = ball->position.param3;
                s32 alpha = (s32)scaled;
                _disp_four_ball(layer, &center, 1.0f, ball->rotation, alpha);
                center.param2 += 235.0f;
                _disp_four_ball(layer, &center, 1.0f, ball->rotation, alpha);
            }
        }
        f32 angle = balls->rotation;
        if (timeGetLastFrameTime() != 0) {
            angle += rotation[side];
            if (angle <= 0.0f) angle += 360.0f;
            else if (angle >= 360.0f) angle -= 360.0f;
            balls->rotation = angle;
        }
        f32 x = balls->position.param1;
        if (timeGetLastFrameTime() != 0) {
            x += movement[side];
            balls->position.param1 = x;
        }
        if (!(x > 770.0f) && !(x < -130.0f)) {
            center.param1 = balls->position.param1;
            center.param2 = balls->position.param2;
            center.param3 = balls->position.param3;
            _disp_four_ball(layer, &center, 1.0f, balls->rotation, (s32)(255.0f * opacity));
            center.param2 += 235.0f;
            _disp_four_ball(layer, &center, 1.0f, balls->rotation, (s32)(255.0f * opacity));
        }
    }
    _fadeEffectEnd(layer);
    return active;
}

bool fadeEffectHookFunction_blur_ball(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (!opaque) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeBlurBallInit();
        GSgfxBeginBackFBCapture((GStexture*)opaque, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !active) {
        _fadeBlurBallQuit();
        GSgfxEndBackFBCapture((GStexture*)opaque);
        return active;
    }
    f32 tilt;
    f32 progress = elapsed / duration;
    f32 progressSecond = elapsedSecond / durationSecond;
    if (timeGetLastFrameTime() != 0) {
        tilt = 4.0f * progressSecond;
        ++_fadeEffectWork.frame;
        if (_fadeEffectWork.direction == 0) tilt *= -1.0f;
        GSgfxBeginBackFBCapture((GStexture*)opaque, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture((GStexture*)opaque);
    }
    GSvec center;
    center.param1 = 320.0f;
    center.param2 = 240.0f;
    center.param3 = 0.0f;
    _fadeEffectSnapshotTex(layer, (GStexture*)opaque, &center, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, tilt, progress, 0.0f);
    FADE_LAYER_SETUP
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 1, 1, 4));
    GStexture* ballTex = _fadeEffectWork.ballTexture;
    FADE_LAYER_BIND_TEXTURE(ballTex)
    s32 alpha = (s32)(0.5f * (255.0f * (1.0f - progress)));
    f32 dist = 1.4f * (640.0f * progressSecond);
    layer->field1998 = 0x98;
    f32 angle = (360.0f * dist) / 376.99112f;
    if (dist > 753.98224f) dist = 753.98224f;
    if (dist > 580.0f) dist = 580.0f;
    center.param1 = 640.0f - dist;
    center.param2 = _fadeEffectWork.direction == 0 ? 72.0f : 408.0f;
    f32 x2 = 320.0f + center.param1;
    if (x2 > 640.0f) x2 = 640.0f;
    _disp_blur_ball(layer, &center, x2, -angle, alpha);
    center.param1 = dist;
    center.param2 = _fadeEffectWork.direction != 0 ? 72.0f : 408.0f;
    f32 x3 = center.param1 - 320.0f;
    if (x3 < 0.0f) x3 = 0.0f;
    _disp_blur_ball(layer, &center, x3, angle, alpha);
    return true;
}

static void _disp_dist_ball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha) {
    FadeMtx transform, rotation;
    GSvec point, output;
    point.param1 = scale;
    point.param2 = scale;
    point.param3 = scale;
    f64 dv = scale;
    PSMTXScale(transform, dv, dv, dv);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, transform, transform);
    PSMTXTransApply(transform, transform, center->param1, center->param2, center->param3);
    layer->beginSurface(4);
    f32 left, top, right, bottom;
    left = (center->param1 - 32.0f) / 640.0f;
    right = (32.0f + center->param1) / 480.0f;
    top = (center->param2 - 32.0f) / 640.0f;
    bottom = (32.0f + center->param2) / 480.0f;
    point.param1 = -32.0f;
    point.param2 = -32.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32( u, v);
        GXTexCoord2f32(left, top);
    }
    point.param1 = 32.0f;
    point.param2 = -32.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32( u, v);
        GXTexCoord2f32(right, top);
    }
    point.param1 = -32.0f;
    point.param2 = 32.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32( u, v);
        GXTexCoord2f32(left, bottom);
    }
    point.param1 = 32.0f;
    point.param2 = 32.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32( u, v);
        GXTexCoord2f32(right, bottom);
    }
    layer->endSurface();
}

static void _disp_blur_ball(GSgfxLayer* layer, GSvec* center, f32 scale, f32 angle, int alpha) {
    FadeMtx transform, rotation;
    GSvec point, output;
    point.param1 = 1.0f;
    point.param2 = 1.0f;
    point.param3 = 1.0f;
    f32 value = 1.0f;
    PSMTXScale(transform, value, value, value);
    PSMTXRotRad(rotation, 'Z', 0.017453292f * angle);
    PSMTXConcat(rotation, transform, transform);
    PSMTXTransApply(transform, transform, center->param1, center->param2, center->param3);
    layer->beginSurface(4);
    f32 ext = 60.0f; f32 half = 0.5f; f32 zero = 0.0f; f32 one = 1.0f;
    GXPosition3f32(center->param1, center->param2 - ext, center->param3);
    GXColor4u8(255, 255, 255, (u8)(alpha / 5));
    GXTexCoord2f32(half, zero);
    GXPosition3f32(center->param1, ext + center->param2, center->param3);
    GXColor4u8(255, 255, 255, (u8)(alpha / 5));
    GXTexCoord2f32(half, one);
    GXPosition3f32(scale, center->param2 - ext, center->param3);
    GXColor4u8(255, 255, 255, 0);
    GXTexCoord2f32(half, zero);
    GXPosition3f32(scale, ext + center->param2, center->param3);
    GXColor4u8(255, 255, 255, 0);
    GXTexCoord2f32(half, one);
    layer->endSurface();
    layer->beginSurface(4);
    point.param1 = -60.0f;
    point.param2 = -60.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 60.0f;
    point.param2 = -60.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 0.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = -60.0f;
    point.param2 = 60.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 0.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    point.param1 = 60.0f;
    point.param2 = 60.0f;
    point.param3 = 0.0f;
    PSMTXMultVec(transform, &point, &output);
    {
        f32 u = 1.0f; f32 v = 1.0f;
        GXPosition3f32(output.param1, output.param2, output.param3);
        GXColor4u8(255, 255, 255, (u8)alpha);
        GXTexCoord2f32(u, v);
    }
    layer->endSurface();
}

bool fadeEffectHookFunction_distortion_zoom(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque, bool zoomOut) {
    GSgfxLayer* layer;
    GStexture* texture;
    layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    texture = (GStexture*)opaque;
    if (!texture) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeDistortionInit();
        s32 lo0 = HSD_Rand();
        s32 hi0 = HSD_Rand();
        _fadeEffectWork.direction = ((hi0 << 0x10) | lo0) & 1;
        s32 lo1 = HSD_Rand();
        s32 hi1 = HSD_Rand();
        _fadeEffectWork.state = ((hi1 << 0x10) | lo1) & 3;
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    }
    if (_fadeEffectFirstFlag == 0 && !active) {
        _fadeDistortionQuit();
        GSgfxEndBackFBCapture(texture);
        return active;
    }
    f32 progress = elapsed / duration;
    f32 progressSecond = elapsedSecond / durationSecond;
    if (timeGetLastFrameTime() != 0) {
        _fadeEffectWork.frame++;
        GSgfxBeginBackFBCapture(texture, _myBackFB, 0);
    } else {
        GSgfxEndBackFBCapture(texture);
    }
    _fadeEffectMaskFunction(layer, progress);
    if (timeGetLastFrameTime() != 0) _fadeDistortionDoSecond(10, true);
    FADE_LAYER_SETUP
    layer->field1998 = 0x98;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 3, 0, 0, 1, 5, 1, 1, 4));
    FADE_LAYER_BIND_TEXTURE(texture)
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    FadeGridPoint* points = _fadeDistortionWork.points;
    FadeUV* uv = _fadeDistortionWork.uv;
    if (!points || !uv) return false;
    int count = columns * 2;
    s8 alpha = (s32)(255.0f * (1.0f - progress));
    for (int x = 1; x < rows; ++x) {
        layer->beginSurface(count);
        for (int y = 0; y < columns; ++y) {
            int index = x * columns + y;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(uv[index].u, uv[index].v);
            index = (x - 1) * columns + y;
            GXPosition3s16(points[index].x, points[index].y, 0);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(uv[index].u, uv[index].v);
        }
        layer->endSurface();
    }
    f32 stepX = 320.0f / (f32)_fadeDistortionWork.columns;
    GSvec center;
    center.param1 = 320.0f;
    center.param2 = 240.0f;
    center.param3 = 0.0f;
    f32 stepY = 240.0f / (f32)_fadeDistortionWork.rows;
    if (zoomOut) {
        if (_fadeEffectWork.state % 2 == 0) stepX = -stepX;
        center.param1 += stepX;
        if (_fadeEffectWork.state <= 1) stepY = -stepY;
        center.param2 += stepY;
        f32 angle = _fadeEffectWork.direction != 0 ? 4.0f : -4.0f;
        if (progressSecond < 0.99999f) {
            _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f - 0.4f * (progressSecond * progressSecond), angle, progress, 0.4f * progressSecond + 0.6f);
        }
        if (progress > 0.00001f) {
            center.param1 = 320.0f;
            center.param2 = 240.0f;
            _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.01f, 0.0f, progress, 0.8f);
        }
    } else {
        if (_fadeEffectWork.state % 2 == 0) stepX = -stepX;
        center.param1 += stepX;
        if (_fadeEffectWork.state <= 1) stepY = -stepY;
        center.param2 += stepY;
        f32 angle = _fadeEffectWork.direction != 0 ? 3.0f : -3.0f;
        if (progressSecond < 0.99999f) {
            GSvec pivot;
            pivot.param1 = center.param1 - 320.0f;
            pivot.param3 = 0.0f;
            pivot.param2 = center.param2 - 240.0f;
            _fadeEffectSnapshotRotate(layer, texture, &center, 1.0f + 0.4f * (progressSecond * progressSecond), &pivot, angle, progress, 0.5f * progressSecond + 0.5f);
        }
        if (progress > 0.00001f) {
            center.param1 = 320.0f;
            center.param2 = 240.0f;
            _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.01f, 0.0f, progress, 0.8f);
        }
    }
    return active;
}

extern bool fadeEffectHookFunction_distortion_zoom(GSgfxLayerID, bool, f32, f32, f32, f32, void*, bool);
bool fadeEffectHookFunction_distortion_zoom_out(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    return fadeEffectHookFunction_distortion_zoom(id, active, elapsed, duration, elapsedSecond, durationSecond, opaque, true);
}
bool fadeEffectHookFunction_distortion_zoom_in(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    return fadeEffectHookFunction_distortion_zoom(id, active, elapsed, duration, elapsedSecond, durationSecond, opaque, false);
}
bool fadeEffectHookFunction_carde(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    return fadeEffectHookFunction_yoko(id, active, elapsed, duration, elapsedSecond, durationSecond, opaque);
}

extern "C" void fadeFluidDispSecond(s32,GStexture*,f32,f32);
extern "C" void fadeFluidEvaluateSecond();
bool fadeEffectHookFunction_boss_second(GSgfxLayerID id,bool active,f32 elapsed,f32 duration,f32 elapsedSecond,f32 durationSecond,void* opaque) {
    GStexture* texture;
    GSgfxLayer* layer=GSgfxLayerFindByID(id);
    if(!layer)return active;
    texture=(GStexture*)opaque;
    if(!texture)return active;
    if(_fadeEffectFirstFlag==1) {
        _fadeEffectFirstFlag=0;
        _fadeEffectFunction_boss_FirstInit_second();
        GSgfxBeginBackFBCapture(texture,_myBackFB,0);
    }
    if(_fadeEffectFirstFlag==0 && !active) {
        fadeFluidQuit();
        GSgfxEndBackFBCapture(texture);
        return active;
    }
    f32 progress=elapsed/duration;
    f32 second=elapsedSecond/durationSecond;
    if(timeGetLastFrameTime()) {
        ++_fadeEffectWork.frame;
        GSgfxBeginBackFBCapture(texture,_myBackFB,0);
    } else GSgfxEndBackFBCapture(texture);
    if(active==1) {
        GSvec center;
        center.param1=320.0f;center.param2=240.0f;center.param3=0.0f;
        _fadeEffectSnapshotFadeFunction(layer,texture,&center,1.0f,0.0f,fadeSqrt(progress),0.0f);
        if(timeGetLastFrameTime())fadeFluidEvaluateSecond();
        second*=second;
        progress=progress*(progress*(progress*progress));
        fadeFluidDispSecond(id,texture,progress,second);
    }
    return active;
}
