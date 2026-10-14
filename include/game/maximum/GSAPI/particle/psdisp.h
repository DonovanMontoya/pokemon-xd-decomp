#ifndef GS_PSDISP_H
#define GS_PSDISP_H
/* GSmathInit configures GQR6 with signed 16-bit storage and scale 6. */
#define PS_FIXED6(value) ((s16)(((value) * 64.0f) >= 32767.0f ? 32767 : (((value) * 64.0f) <= -32768.0f ? -32768 : (s32)((value) * 64.0f))))
#include "particle.h"
#include <dolphin/gx.h>
typedef f32 PSMtx[3][4];

void* memcpy(void*,const void*,u32); void OSReport(const char*,...);
void psDispParticles(u32,s32,u32); void psDispSetProjection(f32*);

void psDispSub(PSParticle*,u32*); void psDispSubAppSRT(PSParticle*,u32*);
void psDispSubAPPSRTPoint(PSParticle*); PSParticle* psDispSubPointTrail(PSParticle*);
void psDispSubMakePolygon(PSParticle*,u32*,f32,f32,f32,f32,f32,f32,f32,f32,f32,f32,f32,f32);
void setupChanReg(PSParticle*); void setupTevReg(PSParticle*);
void psSetupTev(PSParticle*); void psSetupTevCommon(void); void psSetupTevInvalidState(void);
PSCamera* HSD_CObjGetCurrent(void); f32 (*HSD_CObjGetViewingMtx(PSCamera*))[4];
void HSD_FogSet(void*); u32 HSD_LObjGetLightMaskAttnFunc(void); u32 HSD_LObjGetLightMaskDiffuse(void); void* HSD_LObjGetActiveByID(u32);
void HSD_MulColor(GXColor*,GXColor*,GXColor*); void HSD_StateInvalidate(u32);
void HSD_MtxGetRotationMtx(PSMtx,PSMtx,s32,s32); void PSMTXRotAxisRad(PSMtx,PSVec*,f32);
f64 tan(f64); f64 fabs(f64);
extern f32 __float_min[],__float_nan[],__float_epsilon[];
void PSMTXScale(PSMtx,f32,f32,f32); void PSMTXCopy(PSMtx,PSMtx); s32 PSMTXInverse(PSMtx,PSMtx);
s32 psDispHasRenderData(s32);
void psDispBeginFrame(void);
extern u8 psFrameNum;
#endif
