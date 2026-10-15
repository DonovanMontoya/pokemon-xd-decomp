#include "game/pxdvs/app/fade/fade_effect.hpp"
#include <libc/stddef.h>

#include "game/pxdvs/GSAPI/GSmath/GSvec.hpp"
#include "game/pxdvs/GSAPI/GStexture/GStexture.hpp"
#include "game/pxdvs/GSAPI/GSres/GSres.hpp"
#include "game/pxdvs/GSAPI/GSmemman/GSmemman.hpp"
extern "C" void* memcpy(void*, const void*, unsigned long);


typedef f32 FadeMtx[3][4];
extern "C" {
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
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

extern "C" {
void GSmemFree(void*);
s32 HSD_Rand();
f32 HSD_Randf();
void GSgfxVideoSetLockFrameRate(bool);
void GSgfxVFInit(GSgfxVF*);
void GSgfxVFCreate(GSgfxVF*);
void GSgfxVFFree(GSgfxVF*);
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
static void* _fadeTearOffWork;

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
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
    if (!layer) return active;
    if (!opaque) return active;
    if (_fadeEffectFirstFlag == 1) {
        _fadeEffectFirstFlag = 0;
        _fadeEffectFunction_UDLR_FirstInit((GStexture*)opaque, 8);
    }
    return _fadeEffectFunction_UDLR_Main(layer, active, elapsed, duration, elapsedSecond, durationSecond, (GStexture*)opaque);
}

static bool fadeEffectHookFunction_yoko(GSgfxLayerID id, bool active, f32 elapsed, f32 duration, f32 elapsedSecond, f32 durationSecond, void* opaque) {
    GStexture* texture = (GStexture*)opaque;
    GSgfxLayer* layer = GSgfxLayerFindByID(id);
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
        f32 rotation = _fadeEffectWork.rotationStep + _fadeEffectWork.rotation;
        ++_fadeEffectWork.frame;
        _fadeEffectWork.rotation = rotation;
        if (_fadeEffectWork.rotationStep >= 0.0f) {
            _fadeEffectWork.rotationStep = (0.5f * progress) + _fadeEffectWork.rotationStep;
            if (rotation >= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
        } else {
            _fadeEffectWork.rotationStep = -((0.5f * progress) - _fadeEffectWork.rotationStep);
            if (rotation <= _fadeEffectWork.distanceStep) _fadeEffectWork.rotation = _fadeEffectWork.distanceStep;
        }
    }
    center.param1 = 320.0f; center.param2 = 240.0f; center.param3 = 0.0f;
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, 0.0f, progress, 0.0f);
    switch (_fadeEffectWork.direction) {
    case 1:
    case 2: center.param2 = 240.0f; center.param1 = 320.0f + _fadeEffectWork.rotation; break;
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
    _fadeEffectSnapshotFadeFunction(layer, texture, &center, 1.0f, -1.5f * angle, progress, 0.4f);
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

extern "C" f32 __float_nan;
// Three Newton steps are the SDK square-root expansion used by these fades.
static inline f32 fadeSqrt(f32 value) {
    if (value > 0.0f) {
        f64 estimate = __frsqrte((f64)value);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * value);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * value);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * value);
        return (f32)(value * estimate);
    } else if (value < 0.0) return __float_nan;
    else {
        u32 bits = *(u32*)&value;
        int classification;
        switch (bits & 0x7f800000) {
        case 0x7f800000: classification = (bits & 0x7fffff) ? 1 : 2; break;
        case 0: classification = (bits & 0x7fffff) ? 5 : 3; break;
        default: classification = 4; break;
        }
        if (classification == 1) return __float_nan;
        return value;
    }
}

// The random pair is evaluated low word first in the original update paths.
#define FADE_UPDATE_RANDOM(range) (((unsigned long)(HSD_Rand() << 16) | HSD_Rand()) % (range))

static void _fadeDistortionDoAverage(unsigned long range) {
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    f32 du = 1.0f / (columns - 1);
    f32 dv = 1.0f / (rows - 1);
    if (_fadeDistortionWork.uv) {
        FadeUV* uv = _fadeDistortionWork.uv;
        for (int y = 0; y < rows; ++y) {
            FadeUV* coord = uv;
            for (int x = 0; x < columns; ++x) {
                f32 su = FADE_UPDATE_RANDOM(2) == 0 ? 1.0f : -1.0f;
                f32 sv = FADE_UPDATE_RANDOM(2) == 0 ? 1.0f : -1.0f;
                coord->u = du * x + (su * (f32)FADE_UPDATE_RANDOM(range)) / 1000.0f;
                coord->v = dv * y + (sv * (f32)FADE_UPDATE_RANDOM(range)) / 1000.0f;
                ++uv; ++coord;
            }
        }
    }
}

static void _fadeDistortionDo(unsigned long range) {
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    f32 du = 1.0f / (columns - 1);
    f32 dv = 1.0f / (rows - 1);
    if (_fadeDistortionWork.uv) {
        FadeUV* uv = _fadeDistortionWork.uv;
        int radius = rows * rows / 16;
        int cx = columns / 2;
        int cy = rows / 2;
        for (int y = 0; y < rows; ++y) {
            FadeUV* coord = uv;
            for (int x = 0; x < columns; ++x) {
                f32 su, sv;
                if ((x-cx)*(x-cx)+(y-cy)*(y-cy) < radius) {
                    su = FADE_UPDATE_RANDOM(2) == 0 ? 1.0f : -1.0f;
                    sv = FADE_UPDATE_RANDOM(2) == 0 ? 1.0f : -1.0f;
                } else {
                    if (x < cx) su = FADE_UPDATE_RANDOM(4) == 0 ? -1.0f : 1.0f;
                    else su = FADE_UPDATE_RANDOM(4) == 0 ? 1.0f : -1.0f;
                    if (y < cy) sv = FADE_UPDATE_RANDOM(4) == 0 ? -1.0f : 1.0f;
                    else sv = FADE_UPDATE_RANDOM(4) == 0 ? 1.0f : -1.0f;
                }
                coord->u = du * x + (su * (f32)FADE_UPDATE_RANDOM(range)) / 1000.0f;
                coord->v = dv * y + (sv * (f32)FADE_UPDATE_RANDOM(range)) / 1000.0f;
                ++uv; ++coord;
            }
        }
    }
}

static void _fadeDistortionDoSecond(unsigned long range, bool inward) {
    int columns = _fadeDistortionWork.columns;
    int rows = _fadeDistortionWork.rows;
    f32 du = 1.0f / (columns - 1);
    f32 dv = 1.0f / (rows - 1);
    if (_fadeDistortionWork.uv) {
        FadeUV* uv = _fadeDistortionWork.uv;
        int radius = rows * rows / 16;
        int cx = columns / 2;
        int cy = rows / 2;
        for (int y = 0; y < rows; ++y) {
            FadeUV* coord = uv;
            for (int x = 0; x < columns; ++x) {
                f32 su, sv;
                if ((x-cx)*(x-cx)+(y-cy)*(y-cy) < radius) {
                    su = FADE_UPDATE_RANDOM(2) == 0 ? 1.0f : -1.0f;
                    sv = FADE_UPDATE_RANDOM(2) == 0 ? 1.0f : -1.0f;
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
                coord->u = du * x + (su * (f32)FADE_UPDATE_RANDOM(range)) / 1000.0f;
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
    u8 trailAlpha = alpha / 5;
    GXColor4u8(255, 255, 255, trailAlpha);
    GXTexCoord2f32(half, zero);
    GXPosition3f32(center->param1, ext + center->param2, center->param3);
    GXColor4u8(255, 255, 255, trailAlpha);
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
