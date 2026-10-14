#ifndef GS_PSINTERPRET_H
#define GS_PSINTERPRET_H
#include "particle.h"
PSParticle* psInterpretParticle0(PSParticle*, PSParticle*);
typedef f32 PSMtx[3][4];
void HSD_JObjSetMtxDirtySub(PSJObj*); PSJObj* HSD_JObjAlloc(void);

void HSD_MtxSRT(PSMtx,PSVec*,PSVec*,PSVec*,s32);
s32 U8ClampAdd(u8,f32); PSParticle* _psListGetNext(PSParticle*);

void PSMTXScale(PSMtx,f32,f32,f32); void PSMTXCopy(PSMtx,PSMtx); s32 PSMTXInverse(PSMtx,PSMtx);
f32 sinf(f32); f32 cosf(f32); f32 tanf(f32); f32 sqrtf(f32);
extern PSJObj* psPointJObj[8]; extern f32 __float_min[],__float_nan[],__float_epsilon[];
f64 fabs(f64);
typedef union PSByteFloat { u8 bytes[4]; f32 value; } PSByteFloat;

void psInterpretParticles(u32);
#endif
