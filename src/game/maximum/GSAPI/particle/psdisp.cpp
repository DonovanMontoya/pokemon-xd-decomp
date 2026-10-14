#include "game/maximum/GSAPI/particle/psdisp.h"
#define NULL ((void*)0)
#define fabs __fabs
static f32 vmtx[3][4], rvmtx[3][4], prj[7], pvmtx[3][4], rvmtxRot[3][4];
u8 psFrameNum = 123;
static void* particleFog;
static s32 currentMtx;
static GXColor prevColorMat,prevColorEnv,prevColorPrim,prevChanAmb,prevChanMat;
static s32 prevChanCtrl,prevBlendMode;
static f32 rz1,rz0,ry1,ry0,rx1,rx0;
static s32 prevLineWidth,prevPointSize;
static u8 billboard_tex0_u8[32] __attribute__((aligned(32))) = {0,1,0,0,1,0,1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1,0,1,0,1,1,0,1,0,0};
static const f32 identityMtx[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
s32 psDispHasRenderData(s32 arg0);

void psDispBeginFrame(void);
s32 psDispHasRenderData(s32 mask);
__declspec(weak) void setupChanReg(PSParticle *arg0);
__declspec(weak) void setupTevReg(PSParticle *arg0);
__declspec(weak) void psDispSubAPPSRTPoint(PSParticle *arg0);
__declspec(weak) PSParticle *psDispSubPointTrail(PSParticle *arg0);
__declspec(weak) void psDispSubAppSRT(PSParticle *arg0, u32 *arg1);
__declspec(weak) void psDispSubMakePolygon(PSParticle *arg0, u32 *arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 arg_sp8, f32 arg_spC, f32 arg_sp10, f32 arg_sp14);
__declspec(weak) void psDispSub(PSParticle *arg0, u32 *arg1);
static void _psDispParticlesSub(u32 arg0, s32 arg1, PSGenerator *arg2, u32 arg3);
void psDispSetProjection(f32 *arg0);
void psDispParticles(u32 arg0, s32 arg1, u32 arg2);

void psDispBeginFrame(void) {
    u8 var_r0;

    var_r0 = 1;
    if ((u8) psFrameNum < 0xFFU) {
        var_r0 = psFrameNum + 1;
    }
    psFrameNum = var_r0;
}

s32 psDispHasRenderData(s32 mask) {
    PSParticle *opaque, *translucent;
    s32 link;
    for (link = 0; link < 16; link++) {
        if (mask & (1 << link)) {
            particleSort(link, &opaque, &translucent);
            if (opaque != NULL || translucent != NULL) return 1;
        }
    }
    return 0;
}

__declspec(weak) void setupChanReg(PSParticle *arg0) {
    union { f64 alignment; u8 bytes[35]; } stack;
    s32 temp_r0;
    s32 temp_r10;
    s32 temp_r5_2;
    u16 temp_r5;
    u16 temp_r5_3;
    u8 temp_r0_2;
    u8 temp_r11;
    u8 temp_r12;
    u8 temp_r6;
    u8 temp_r6_2;
    u8 temp_r6_3;
    u8 temp_r7;
    void *temp_r3;

    if (arg0->kind & 0x80000000) {
        temp_r5 = arg0->ambCount;
        if (temp_r5 != 0) {
            temp_r6 = arg0->ambRGBTarget;
            temp_r5_2 = (s32) (arg0->ambRemain << 0x10) / (s32) temp_r5;
            temp_r0 = (s32) ((temp_r6 << 0x10) + (temp_r5_2 * (arg0->ambRGB - temp_r6))) >> 0x10;
            (*(u8*)(stack.bytes+0x16)) = (u8) temp_r0;
            (*(u8*)(stack.bytes+0x15)) = (u8) temp_r0;
            (*(u8*)(stack.bytes+0x14)) = (u8) temp_r0;
            temp_r6_2 = arg0->ambAlphaTarget;
            (*(u8*)(stack.bytes+0x17)) = (u8) ((s32) ((temp_r6_2 << 0x10) + (temp_r5_2 * (arg0->ambAlpha - temp_r6_2))) >> 0x10);
        } else {
            temp_r0_2 = arg0->ambRGB;
            (*(u8*)(stack.bytes+0x16)) = temp_r0_2;
            (*(u8*)(stack.bytes+0x15)) = temp_r0_2;
            (*(u8*)(stack.bytes+0x14)) = temp_r0_2;
            (*(u8*)(stack.bytes+0x17)) = arg0->ambAlpha;
        }
        if (arg0->kind & 0x80) {
            (*(u8*)(stack.bytes+0x1A)) = 0xFF;
            (*(u8*)(stack.bytes+0x19)) = 0xFF;
            (*(s8*)(stack.bytes+0x18)) = 0xFF;
        } else {
            temp_r5_3 = arg0->primCount;
            if (temp_r5_3 != 0) {
                temp_r6_3 = arg0->primTarget[0];
                temp_r10 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r5_3;
                temp_r7 = arg0->primTarget[1];
                temp_r11 = arg0->primTarget[2];
                temp_r12 = arg0->primTarget[3];
                (*(s8*)(stack.bytes+0x18)) = (s8) ((s32) ((temp_r6_3 << 0x10) + (temp_r10 * (arg0->primColor[0] - temp_r6_3))) >> 0x10);
                (*(u8*)(stack.bytes+0x19)) = (u8) ((s32) ((temp_r7 << 0x10) + (temp_r10 * (arg0->primColor[1] - temp_r7))) >> 0x10);
                (*(u8*)(stack.bytes+0x1A)) = (u8) ((s32) ((temp_r11 << 0x10) + (temp_r10 * (arg0->primColor[2] - temp_r11))) >> 0x10);
                (*(s8*)(stack.bytes+0x1B)) = (s8) ((s32) ((temp_r12 << 0x10) + (temp_r10 * (arg0->primColor[3] - temp_r12))) >> 0x10);
            } else {
                *(u32*)&(*(s8*)(stack.bytes+0x18)) = (s32) *(u32*)arg0->primColor;
            }
            (*(u8*)(stack.bytes+0x14)) = (u8) ((s32) ((*(u8*)(stack.bytes+0x14)) * (u8) (*(s8*)(stack.bytes+0x18))) >> 8);
            (*(u8*)(stack.bytes+0x15)) = (u8) ((s32) ((*(u8*)(stack.bytes+0x15)) * (*(u8*)(stack.bytes+0x19))) >> 8);
            (*(u8*)(stack.bytes+0x16)) = (u8) ((s32) ((*(u8*)(stack.bytes+0x16)) * (*(u8*)(stack.bytes+0x1A))) >> 8);
        }
        if (((u8) (*(s8*)(stack.bytes+0x18)) != (u8) prevChanMat.r) || ((*(u8*)(stack.bytes+0x19)) != (u8) prevChanMat.g) || ((*(u8*)(stack.bytes+0x1A)) != (u8) prevChanMat.b)) {
            *(u32*)&prevChanMat = *(u32*)&(*(s8*)(stack.bytes+0x18));
            (*(s32*)(stack.bytes+0x10)) = *(u32*)&(*(s8*)(stack.bytes+0x18));
            GXSetChanMatColor(GX_COLOR0, *(GXColor*)&(*(s32*)(stack.bytes+0x10)));
        }
        temp_r3 = HSD_LObjGetActiveByID(0x100U);
        if (temp_r3 != NULL) {
            HSD_MulColor((GXColor *) &(*(u8*)(stack.bytes+0x14)), (GXColor*)((u8*)temp_r3 + 0x10), (GXColor *) &(*(u8*)(stack.bytes+0x14)));
        } else {
            (*(u8*)(stack.bytes+0x16)) = 0;
            (*(u8*)(stack.bytes+0x15)) = 0;
            (*(u8*)(stack.bytes+0x14)) = 0;
        }
        if (((*(u8*)(stack.bytes+0x14)) != (u8) prevChanAmb.r) || ((*(u8*)(stack.bytes+0x15)) != (u8) prevChanAmb.g) || ((*(u8*)(stack.bytes+0x16)) != (u8) prevChanAmb.b)) {
            (*(s32*)(stack.bytes+0x8)) = *(s32*)&(*(u8*)(stack.bytes+0x14));
            *(u32*)&prevChanAmb = *(s32*)&(*(u8*)(stack.bytes+0x14));
            (*(s32*)(stack.bytes+0xC)) = *(s32*)&(*(u8*)(stack.bytes+0x14));
            GXSetChanAmbColor(GX_COLOR0, *(GXColor*)&(*(s32*)(stack.bytes+0xC)));
        }
    }
}

__declspec(weak) void setupTevReg(PSParticle *arg0) {
    union { f64 alignment; u8 bytes[55]; } stack;
    s32 temp_r0;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r4_4;
    s32 temp_r6_3;
    u16 temp_r4;
    u16 temp_r4_2;
    u16 temp_r4_3;
    u32 temp_r3;
    u32 temp_r8;
    u8 temp_r11;
    u8 temp_r11_2;
    u8 temp_r12;
    u8 temp_r12_2;
    u8 temp_r3_2;
    u8 temp_r5;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 temp_r6;
    u8 temp_r6_2;
    u8 temp_r7;

    temp_r4 = arg0->primCount;
    if (temp_r4 != 0) {
        temp_r5 = arg0->primTarget[0];
        temp_r6 = arg0->primTarget[1];
        temp_r10 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r4;
        temp_r11 = arg0->primTarget[2];
        temp_r12 = arg0->primTarget[3];
        (*(s8*)(stack.bytes+0x2C)) = (s8) ((s32) ((temp_r5 << 0x10) + (temp_r10 * (arg0->primColor[0] - temp_r5))) >> 0x10);
        (*(u8*)(stack.bytes+0x2D)) = (u8) ((s32) ((temp_r6 << 0x10) + (temp_r10 * (arg0->primColor[1] - temp_r6))) >> 0x10);
        (*(u8*)(stack.bytes+0x2E)) = (u8) ((s32) ((temp_r11 << 0x10) + (temp_r10 * (arg0->primColor[2] - temp_r11))) >> 0x10);
        (*(u8*)(stack.bytes+0x2F)) = (u8) ((s32) ((temp_r12 << 0x10) + (temp_r10 * (arg0->primColor[3] - temp_r12))) >> 0x10);
    } else {
        *(u32*)&(*(s8*)(stack.bytes+0x2C)) = (s32) *(u32*)arg0->primColor;
    }
    temp_r4_2 = arg0->envCount;
    if (temp_r4_2 != 0) {
        temp_r5_2 = arg0->envTarget[0];
        temp_r6_2 = arg0->envTarget[1];
        temp_r10_2 = (s32) (arg0->envRemain << 0x10) / (s32) temp_r4_2;
        temp_r11_2 = arg0->envTarget[2];
        temp_r12_2 = arg0->envTarget[3];
        (*(s8*)(stack.bytes+0x28)) = (s8) ((s32) ((temp_r5_2 << 0x10) + (temp_r10_2 * (arg0->envColor[0] - temp_r5_2))) >> 0x10);
        (*(u8*)(stack.bytes+0x29)) = (u8) ((s32) ((temp_r6_2 << 0x10) + (temp_r10_2 * (arg0->envColor[1] - temp_r6_2))) >> 0x10);
        (*(u8*)(stack.bytes+0x2A)) = (u8) ((s32) ((temp_r11_2 << 0x10) + (temp_r10_2 * (arg0->envColor[2] - temp_r11_2))) >> 0x10);
        (*(u8*)(stack.bytes+0x2B)) = (u8) ((s32) ((temp_r12_2 << 0x10) + (temp_r10_2 * (arg0->envColor[3] - temp_r12_2))) >> 0x10);
    } else {
        *(u32*)&(*(s8*)(stack.bytes+0x28)) = (s32) *(u32*)arg0->envColor;
    }
    temp_r3 = arg0->kind;
    if ((temp_r3 & 0x80) || (!(temp_r3 & 0x80000000) && !(temp_r3 & 0x100000))) {
        if (((u8) prevColorPrim.r != (u8) (*(s8*)(stack.bytes+0x2C))) || ((u8) prevColorPrim.g != (*(u8*)(stack.bytes+0x2D))) || ((u8) prevColorPrim.b != (*(u8*)(stack.bytes+0x2E))) || ((u8) prevColorPrim.a != (*(u8*)(stack.bytes+0x2F)))) {
            *(u32*)&prevColorPrim = *(u32*)&(*(s8*)(stack.bytes+0x2C));
            (*(s32*)(stack.bytes+0x20)) = *(u32*)&(*(s8*)(stack.bytes+0x2C));
            GXSetTevColor(GX_TEVREG0, *(GXColor*)&(*(s32*)(stack.bytes+0x20)));
        }
        if (arg0->kind & 0x80) {
            if (((u8) prevColorEnv.r != (u8) (*(s8*)(stack.bytes+0x28))) || ((u8) prevColorEnv.g != (*(u8*)(stack.bytes+0x29))) || ((u8) prevColorEnv.b != (*(u8*)(stack.bytes+0x2A))) || ((u8) prevColorEnv.a != (*(u8*)(stack.bytes+0x2B)))) {
                *(u32*)&prevColorEnv = *(u32*)&(*(s8*)(stack.bytes+0x28));
                (*(s32*)(stack.bytes+0x1C)) = *(u32*)&(*(s8*)(stack.bytes+0x28));
                GXSetTevColor(GX_TEVREG1, *(GXColor*)&(*(s32*)(stack.bytes+0x1C)));
            }
        } else if (((u8) prevColorEnv.r != 0) || ((u8) prevColorEnv.g != 0) || ((u8) prevColorEnv.b != 0) || ((u8) prevColorEnv.a != 0)) {
            prevColorEnv.a = 0;
            prevColorEnv.b = 0;
            prevColorEnv.g = 0;
            prevColorEnv.r = 0;
            *(u32*)&(*(s32*)(stack.bytes+0x18)) = (s32) *(u32*)&prevColorEnv;
            GXSetTevColor(GX_TEVREG1, *(GXColor*)&(*(s32*)(stack.bytes+0x18)));
        }
    }
    temp_r8 = arg0->kind;
    if (temp_r8 & 0x80000000) {
        temp_r4_3 = arg0->matCount;
        if (temp_r4_3 != 0) {
            temp_r5_3 = arg0->matRGBTarget;
            temp_r6_3 = (s32) (arg0->matRemain << 0x10) / (s32) temp_r4_3;
            temp_r7 = arg0->matAlphaTarget;
            temp_r4_4 = (s32) ((temp_r5_3 << 0x10) + (temp_r6_3 * (arg0->matRGB - temp_r5_3))) >> 0x10;
            (*(u8*)(stack.bytes+0x26)) = (u8) temp_r4_4;
            (*(u8*)(stack.bytes+0x25)) = (u8) temp_r4_4;
            (*(u8*)(stack.bytes+0x24)) = (u8) temp_r4_4;
            (*(u8*)(stack.bytes+0x27)) = (u8) ((s32) ((temp_r7 << 0x10) + (temp_r6_3 * (arg0->matAlpha - temp_r7))) >> 0x10);
        } else {
            temp_r3_2 = arg0->matRGB;
            (*(u8*)(stack.bytes+0x26)) = temp_r3_2;
            (*(u8*)(stack.bytes+0x25)) = temp_r3_2;
            (*(u8*)(stack.bytes+0x24)) = temp_r3_2;
            (*(u8*)(stack.bytes+0x27)) = arg0->matAlpha;
        }
        if (temp_r8 & 0x80) {
            if (((u8) prevColorMat.r != (*(u8*)(stack.bytes+0x24))) || ((u8) prevColorMat.g != (*(u8*)(stack.bytes+0x25))) || ((u8) prevColorMat.b != (*(u8*)(stack.bytes+0x26))) || ((u8) prevColorMat.a != (*(u8*)(stack.bytes+0x27)))) {
                (*(s32*)(stack.bytes+0xC)) = *(s32*)&(*(u8*)(stack.bytes+0x24));
                *(u32*)&prevColorMat = *(s32*)&(*(u8*)(stack.bytes+0x24));
                (*(s32*)(stack.bytes+0x14)) = *(s32*)&(*(u8*)(stack.bytes+0x24));
                GXSetTevColor(GX_TEVREG2, *(GXColor*)&(*(s32*)(stack.bytes+0x14)));
            }
        } else {
            temp_r0 = (s32) ((*(u8*)(stack.bytes+0x27)) * (*(u8*)(stack.bytes+0x2F))) >> 8;
            (*(u8*)(stack.bytes+0x27)) = (u8) temp_r0;
            if (((u8) prevColorMat.r != (*(u8*)(stack.bytes+0x24))) || ((u8) prevColorMat.g != (*(u8*)(stack.bytes+0x25))) || ((u8) prevColorMat.b != (*(u8*)(stack.bytes+0x26))) || ((u8) prevColorMat.a != (u8) temp_r0)) {
                (*(s32*)(stack.bytes+0x8)) = *(s32*)&(*(u8*)(stack.bytes+0x24));
                *(u32*)&prevColorMat = *(s32*)&(*(u8*)(stack.bytes+0x24));
                (*(s32*)(stack.bytes+0x10)) = *(s32*)&(*(u8*)(stack.bytes+0x24));
                GXSetTevColor(GX_TEVREG2, *(GXColor*)&(*(s32*)(stack.bytes+0x10)));
            }
        }
    }
}

__declspec(weak) void psDispSubAPPSRTPoint(PSParticle *arg0) {
    union { f64 alignment; u8 bytes[172]; } stack;
    PSAppSRT *temp_r3;
    PSAppSRT *temp_r3_2;
    PSAppSRT *temp_r3_3;
    PSAppSRT *temp_r6;
    PSAppSRT *temp_r6_2;
    PSAppSRT *temp_r6_3;
    PSGenerator *temp_r30;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f25;
    f32 temp_f25_2;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    f32 temp_f5;
    f32 temp_f9;
    f32 var_f0;
    f32 var_f1;
    f32 var_f22;
    f32 var_f22_2;
    f32 var_f23;
    f32 var_f23_2;
    f32 var_f24;
    f32 var_f24_2;
    f32 var_f29;
    s32 temp_r11;
    s32 temp_r3_4;
    s32 temp_r4;
    s32 temp_r7_2;
    u16 temp_r5;
    u32 temp_r0;
    u8 temp_r12;
    u8 temp_r30_2;
    u8 temp_r6_4;
    u8 temp_r7;

    if ((s32) currentMtx != 0) {
        currentMtx = 0;
        GXSetCurrentMtx(0U);
    }
    temp_r6 = arg0->appsrt;
    if ((u8) temp_r6->frame != (u8) psFrameNum) {
        if ((u8) temp_r6->status != 2) {
            HSD_MtxSRT((f32 (*)[4]) temp_r6->matrix[0], &temp_r6->scale, &temp_r6->rotation, &temp_r6->translate, 0);
        }
        temp_r3 = arg0->appsrt;
        if ((u8) temp_r3->status == 1) {
            temp_r3->status = 2;
        }
    }
    arg0->appsrt->frame = psFrameNum;
    PSMTXCopy((f32 (*)[4]) arg0->appsrt->matrix[0], (f32 (*)[4]) &((f32*)(stack.bytes+0x78))[0]);
    temp_r6_2 = arg0->appsrt;
    ((f32*)(stack.bytes+0x78))[3] -= temp_r6_2->translate.x;
    (*(f32*)(stack.bytes+0x94)) -= temp_r6_2->translate.y;
    (*(f32*)(stack.bytes+0xA4)) -= temp_r6_2->translate.z;
    (*(f32*)(stack.bytes+0x3C)) = arg0->velocity.x;
    (*(f32*)(stack.bytes+0x40)) = arg0->velocity.y;
    (*(f32*)(stack.bytes+0x44)) = arg0->velocity.z;
    PSMTXMultVec((f32 (*)[4]) &((f32*)(stack.bytes+0x78))[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
    if ((u8) arg0->appsrt->generatorOwned != 0) {
        PSMTXMultVec(rvmtxRot, (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
    }
    temp_f25 = (*(f32*)(stack.bytes+0x3C));
    temp_f26 = (*(f32*)(stack.bytes+0x40));
    (*(f32*)(stack.bytes+0x3C)) = arg0->position.x;
    temp_f27 = (*(f32*)(stack.bytes+0x44));
    (*(f32*)(stack.bytes+0x40)) = arg0->position.y;
    (*(f32*)(stack.bytes+0x44)) = arg0->position.z;
    temp_r3_2 = arg0->appsrt;
    if ((u8) temp_r3_2->generatorOwned != 0) {
        PSMTXMultVec((f32 (*)[4]) &((f32*)(stack.bytes+0x78))[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
        PSMTXMultVec(rvmtxRot, (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
        temp_r3_3 = arg0->appsrt;
        (*(f32*)(stack.bytes+0x3C)) += temp_r3_3->translate.x;
        (*(f32*)(stack.bytes+0x40)) += temp_r3_3->translate.y;
        (*(f32*)(stack.bytes+0x44)) += temp_r3_3->translate.z;
    } else {
        PSMTXMultVec((f32 (*)[4]) temp_r3_2->matrix[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
    }
    if (arg0->kind & 4) {
        temp_r30 = arg0->generator;
        if (temp_r30 == NULL) {
            var_f24 = arg0->position.x;
            var_f23 = arg0->position.y;
            var_f22 = arg0->position.z;
        } else {
            temp_f28 = (f32) sin((f64) arg0->gravity);
            temp_f27_2 = (f32) sin((f64) arg0->friction);
            temp_f26_2 = (f32) cos((f64) arg0->gravity);
            temp_f25_2 = (f32) cos((f64) arg0->friction);
            temp_f31 = arg0->velocity.z - temp_r30->param1;
            var_f29 = temp_r30->radius;
            temp_f30 = arg0->velocity.x - temp_r30->gravity;
            if (var_f29 < 0.0f) {
                var_f29 = -var_f29;
            }
            var_f1 = temp_r30->angle;
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            temp_f29 = ((temp_f31 * (f32) tan((f64) var_f1)) + var_f29) * arg0->velocity.y;
            temp_f30_2 = temp_f29 * (f32) cos((f64) temp_f30);
            temp_f9 = -temp_f30_2;
            temp_f5 = temp_f29 * (f32) sin((f64) temp_f30);
            var_f24 = temp_r30->position.x + ((temp_f30_2 * temp_f25_2) + (temp_f31 * temp_f27_2));
            var_f23 = temp_r30->position.y + ((temp_f25_2 * (temp_f31 * temp_f28)) + ((temp_f27_2 * (temp_f9 * temp_f28)) + (temp_f5 * temp_f26_2)));
            var_f22 = temp_r30->position.z + ((temp_f25_2 * (temp_f31 * temp_f26_2)) + ((temp_f27_2 * (temp_f9 * temp_f26_2)) - (temp_f5 * temp_f28)));
        }
        temp_r6_3 = arg0->appsrt;
        HSD_MtxSRT((f32 (*)[4]) &((f32*)(stack.bytes+0x48))[0], &temp_r6_3->scale, &temp_r6_3->rotation, &temp_r6_3->translate, 0);
        (*(f32*)(stack.bytes+0x30)) = var_f24;
        (*(f32*)(stack.bytes+0x34)) = var_f23;
        (*(f32*)(stack.bytes+0x38)) = var_f22;
        PSMTXMultVec((f32 (*)[4]) &((f32*)(stack.bytes+0x48))[0], (PSVec *) &(*(f32*)(stack.bytes+0x30)), (PSVec *) &(*(f32*)(stack.bytes+0x30)));
        var_f24_2 = (*(f32*)(stack.bytes+0x30));
        var_f23_2 = (*(f32*)(stack.bytes+0x34));
        var_f22_2 = (*(f32*)(stack.bytes+0x38));
    } else {
        var_f24_2 = (*(f32*)(stack.bytes+0x3C)) - temp_f25;
        var_f23_2 = (*(f32*)(stack.bytes+0x40)) - temp_f26;
        var_f22_2 = (*(f32*)(stack.bytes+0x44)) - temp_f27;
    }
    temp_f1 = arg0->size;
    if (temp_f1 > 42.5) {
        var_f0 = 255.0f;
    } else {
        var_f0 = 6.0f * temp_f1;
    }
    temp_r3_4 = (s32) var_f0;
    if (arg0->kind & 0x100000) {
        if ((s32) prevLineWidth != (s32) (u8) temp_r3_4) {
            prevLineWidth = (s32) (u8) temp_r3_4;
            GXSetLineWidth((u8) temp_r3_4, GX_TO_ONE);
        }
        temp_r0 = arg0->kind;
        temp_r4 = temp_r0 & 0x80000080;
        switch (temp_r4) {                          /* irregular */
        default:
        case 0x0:
            temp_r5 = arg0->primCount;
            if (temp_r5 != 0) {
                temp_r6_4 = arg0->primTarget[0];
                temp_r7 = arg0->primTarget[1];
                temp_r11 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r5;
                temp_r12 = arg0->primTarget[2];
                temp_r30_2 = arg0->primTarget[3];
                (*(s8*)(stack.bytes+0x2C)) = (s8) ((s32) ((temp_r6_4 << 0x10) + (temp_r11 * (arg0->primColor[0] - temp_r6_4))) >> 0x10);
                (*(u8*)(stack.bytes+0x2D)) = (u8) ((s32) ((temp_r7 << 0x10) + (temp_r11 * (arg0->primColor[1] - temp_r7))) >> 0x10);
                (*(u8*)(stack.bytes+0x2E)) = (u8) ((s32) ((temp_r12 << 0x10) + (temp_r11 * (arg0->primColor[2] - temp_r12))) >> 0x10);
                (*(u8*)(stack.bytes+0x2F)) = (u8) ((s32) ((temp_r30_2 << 0x10) + (temp_r11 * (arg0->primColor[3] - temp_r30_2))) >> 0x10);
            } else {
                *(u32*)&(*(s8*)(stack.bytes+0x2C)) = (s32) *(u32*)arg0->primColor;
            }
            break;
        case 0x80:
        case 0x80000080:
            (*(u8*)(stack.bytes+0x2F)) = 0xFF;
            (*(u8*)(stack.bytes+0x2E)) = 0xFF;
            (*(u8*)(stack.bytes+0x2D)) = 0xFF;
            (*(s8*)(stack.bytes+0x2C)) = 0xFF;
            break;
        }
        if (temp_r0 & 0x400) {
            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
            GXBegin(GX_LINES, GX_VTXFMT2, 2U);
        } else {
            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            GXBegin(GX_LINES, GX_VTXFMT3, 2U);
        }
        (*(f32*)(stack.bytes+0x28)) = var_f22_2;


        (*(f32*)(stack.bytes+0x24)) = var_f23_2;
        (*(f32*)(stack.bytes+0x20)) = var_f24_2;
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x20)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x24)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x28)));
        temp_r7_2 = (((((*(u8*)(stack.bytes+0x2D)) * 0x10) & 0xF00 & ~0xF000) | (((u8) (*(s8*)(stack.bytes+0x2C)) << 8) & 0xF000)) & ~0xF0) | ((*(u8*)(stack.bytes+0x2E)) & 0xF0);
        temp_f0 = (f32) (*(u8*)(stack.bytes+0x2F)) * arg0->textureScale;
        *(volatile s16 *)0xCC008000 = (temp_r7_2 & ~0xF) | (((u32) (s32) temp_f0 >> 4U) & 0xF);
        if (arg0->kind & 0x400) {
            *(volatile u8 *)0xCC008000 = 0;
        }
        (*(f32*)(stack.bytes+0x1C)) = (*(f32*)(stack.bytes+0x44));

        (*(f32*)(stack.bytes+0x18)) = (*(f32*)(stack.bytes+0x40));
        (*(f32*)(stack.bytes+0x14)) = (*(f32*)(stack.bytes+0x3C));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x14)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x18)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x1C)));
        *(volatile s16 *)0xCC008000 = (s16) ((((*(u8*)(stack.bytes+0x2F)) >> 4U) & 0xF) | temp_r7_2);
        if (arg0->kind & 0x400) {
            *(volatile u8 *)0xCC008000 = 1;
        }
    } else {
        if ((s32) prevPointSize != (s32) (u8) temp_r3_4) {
            prevPointSize = (s32) (u8) temp_r3_4;
            GXSetPointSize((u8) temp_r3_4, GX_TO_ONE);
        }
        if (arg0->kind & 0x400) {
            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
            GXBegin(GX_POINTS, GX_VTXFMT0, 1U);
        } else {
            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXBegin(GX_POINTS, GX_VTXFMT1, 1U);
        }
        (*(f32*)(stack.bytes+0x10)) = (*(f32*)(stack.bytes+0x44));


        (*(f32*)(stack.bytes+0xC)) = (*(f32*)(stack.bytes+0x40));
        (*(f32*)(stack.bytes+0x8)) = (*(f32*)(stack.bytes+0x3C));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x8)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0xC)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x10)));
        if (arg0->kind & 0x400) {
            *(volatile u8 *)0xCC008000 = 1;
        }
    }
}

__declspec(weak) PSParticle *psDispSubPointTrail(PSParticle *arg0) {
    union { f64 alignment; u8 bytes[43]; } stack;
    PSGenerator *temp_r30;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    f32 temp_f5;
    f32 temp_f9;
    f32 var_f0;
    f32 var_f19;
    f32 var_f1;
    f32 var_f20;
    f32 var_f21;
    f32 var_f29;
    s32 temp_r11;
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r7_2;
    u16 temp_r5;
    u32 temp_r0;
    u8 temp_r12;
    u8 temp_r30_2;
    u8 temp_r6;
    u8 temp_r7;

    if ((s32) currentMtx != 0) {
        currentMtx = 0;
        GXSetCurrentMtx(0U);
    }
    temp_f1 = arg0->size;
    if (temp_f1 > 42.5) {
        var_f0 = 255.0f;
    } else {
        var_f0 = 6.0f * temp_f1;
    }
    temp_r3 = (s32) var_f0;
    if ((s32) prevLineWidth != (s32) (u8) temp_r3) {
        prevLineWidth = (s32) (u8) temp_r3;
        GXSetLineWidth((u8) temp_r3, GX_TO_ONE);
    }
    if (arg0->kind & 4) {
        temp_r30 = arg0->generator;
        if (temp_r30 == NULL) {
            var_f21 = arg0->position.x;
            var_f20 = arg0->position.y;
            var_f19 = arg0->position.z;
        } else {
            temp_f25 = (f32) sin((f64) arg0->gravity);
            temp_f24 = (f32) sin((f64) arg0->friction);
            temp_f23 = (f32) cos((f64) arg0->gravity);
            temp_f22 = (f32) cos((f64) arg0->friction);
            temp_f31 = arg0->velocity.z - temp_r30->param1;
            var_f29 = temp_r30->radius;
            temp_f30 = arg0->velocity.x - temp_r30->gravity;
            if (var_f29 < 0.0f) {
                var_f29 = -var_f29;
            }
            var_f1 = temp_r30->angle;
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            temp_f29 = ((temp_f31 * (f32) tan((f64) var_f1)) + var_f29) * arg0->velocity.y;
            temp_f30_2 = temp_f29 * (f32) cos((f64) temp_f30);
            temp_f9 = -temp_f30_2;
            temp_f5 = temp_f29 * (f32) sin((f64) temp_f30);
            var_f21 = temp_r30->position.x + ((temp_f30_2 * temp_f22) + (temp_f31 * temp_f24));
            var_f20 = temp_r30->position.y + ((temp_f22 * (temp_f31 * temp_f25)) + ((temp_f24 * (temp_f9 * temp_f25)) + (temp_f5 * temp_f23)));
            var_f19 = temp_r30->position.z + ((temp_f22 * (temp_f31 * temp_f23)) + ((temp_f24 * (temp_f9 * temp_f23)) - (temp_f5 * temp_f25)));
        }
    } else {
        var_f21 = arg0->position.x - arg0->velocity.x;
        var_f20 = arg0->position.y - arg0->velocity.y;
        var_f19 = arg0->position.z - arg0->velocity.z;
    }
    temp_r0 = arg0->kind;
    temp_r4 = temp_r0 & 0x80000080;
    switch (temp_r4) {                              /* irregular */
    default:
    case 0x0:
        temp_r5 = arg0->primCount;
        if (temp_r5 != 0) {
            temp_r6 = arg0->primTarget[0];
            temp_r7 = arg0->primTarget[1];
            temp_r11 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r5;
            temp_r12 = arg0->primTarget[2];
            temp_r30_2 = arg0->primTarget[3];
            (*(s8*)(stack.bytes+0x20)) = (s8) ((s32) ((temp_r6 << 0x10) + (temp_r11 * (arg0->primColor[0] - temp_r6))) >> 0x10);
            (*(u8*)(stack.bytes+0x21)) = (u8) ((s32) ((temp_r7 << 0x10) + (temp_r11 * (arg0->primColor[1] - temp_r7))) >> 0x10);
            (*(u8*)(stack.bytes+0x22)) = (u8) ((s32) ((temp_r12 << 0x10) + (temp_r11 * (arg0->primColor[2] - temp_r12))) >> 0x10);
            (*(u8*)(stack.bytes+0x23)) = (u8) ((s32) ((temp_r30_2 << 0x10) + (temp_r11 * (arg0->primColor[3] - temp_r30_2))) >> 0x10);
        } else {
            *(u32*)&(*(s8*)(stack.bytes+0x20)) = (s32) *(u32*)arg0->primColor;
        }
        break;
    case 0x80:
    case 0x80000080:
        (*(u8*)(stack.bytes+0x23)) = 0xFF;
        (*(u8*)(stack.bytes+0x22)) = 0xFF;
        (*(u8*)(stack.bytes+0x21)) = 0xFF;
        (*(s8*)(stack.bytes+0x20)) = 0xFF;
        break;
    }
    if (temp_r0 & 0x400) {
        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        GXBegin(GX_LINES, GX_VTXFMT2, 2U);
    } else {
        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXBegin(GX_LINES, GX_VTXFMT3, 2U);
    }
    (*(f32*)(stack.bytes+0x1C)) = var_f19;


    (*(f32*)(stack.bytes+0x18)) = var_f20;
    (*(f32*)(stack.bytes+0x14)) = var_f21;
    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x14)));
    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x18)));
    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x1C)));
    temp_r7_2 = (((((*(u8*)(stack.bytes+0x21)) * 0x10) & 0xF00 & ~0xF000) | (((u8) (*(s8*)(stack.bytes+0x20)) << 8) & 0xF000)) & ~0xF0) | ((*(u8*)(stack.bytes+0x22)) & 0xF0);
    temp_f0 = (f32) (*(u8*)(stack.bytes+0x23)) * arg0->textureScale;
    *(volatile s16 *)0xCC008000 = (temp_r7_2 & ~0xF) | (((u32) (s32) temp_f0 >> 4U) & 0xF);
    if (arg0->kind & 0x400) {
        *(volatile u8 *)0xCC008000 = 0;
    }
    (*(f32*)(stack.bytes+0x10)) = arg0->position.z;

    (*(f32*)(stack.bytes+0xC)) = arg0->position.y;
    (*(f32*)(stack.bytes+0x8)) = arg0->position.x;
    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x8)));
    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0xC)));
    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x10)));
    *(volatile s16 *)0xCC008000 = (s16) ((((*(u8*)(stack.bytes+0x23)) >> 4U) & 0xF) | temp_r7_2);
    if (arg0->kind & 0x400) {
        *(volatile u8 *)0xCC008000 = 1;
    }
    return arg0;
}

__declspec(weak) void psDispSubAppSRT(PSParticle *arg0, u32 *arg1) {
    union { f64 alignment; u8 bytes[236]; } stack;
    PSAppSRT *temp_r3;
    PSAppSRT *temp_r3_10;
    PSAppSRT *temp_r3_2;
    PSAppSRT *temp_r3_3;
    PSAppSRT *temp_r3_5;
    PSAppSRT *temp_r3_6;
    PSAppSRT *temp_r3_9;
    PSAppSRT *temp_r4;
    PSAppSRT *temp_r6;
    PSAppSRT *temp_r6_2;
    PSAppSRT *temp_r7;
    PSGenerator *temp_r28;
    f32 (*temp_r3_11)[4];
    f32 (*temp_r3_12)[4];
    f32 (*temp_r3_8)[4];
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f15;
    f32 temp_f15_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f17;
    f32 temp_f17_2;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f19;
    f32 temp_f19_2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f3_4;
    f32 temp_f3_5;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f4_4;
    f32 temp_f5;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f6_3;
    f32 temp_f6_4;
    f32 temp_f6_5;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f9;
    f32 temp_f9_2;
    f32 temp_f9_3;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f18;
    f32 var_f19;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f1_6;
    f32 var_f1_7;
    f32 var_f26;
    f32 var_f27;
    f32 var_f28;
    f32 var_f29;
    f32 var_f2;
    f32 var_f30;
    f32 var_f31;
    f32 var_f5;
    f32 var_f5_2;
    f32 var_f5_3;
    f32 var_f6;
    u32 temp_r3_4;
    void *temp_r3_7;
    void *temp_r6_3;

    temp_r6 = arg0->appsrt;
    if ((u8) temp_r6->frame != (u8) psFrameNum) {
        if ((u8) temp_r6->status != 2) {
            HSD_MtxSRT((f32 (*)[4]) temp_r6->matrix[0], &temp_r6->scale, &temp_r6->rotation, &temp_r6->translate, 0);
        }
        temp_r3 = arg0->appsrt;
        if ((u8) temp_r3->status == 1) {
            temp_r3->status = 2;
        }
    }
    arg0->appsrt->frame = psFrameNum;
    PSMTXCopy((f32 (*)[4]) arg0->appsrt->matrix[0], (f32 (*)[4]) &((f32*)(stack.bytes+0xA8))[0]);
    temp_r6_2 = arg0->appsrt;
    ((f32*)(stack.bytes+0xA8))[3] -= temp_r6_2->translate.x;
    (*(f32*)(stack.bytes+0xC4)) -= temp_r6_2->translate.y;
    (*(f32*)(stack.bytes+0xD4)) -= temp_r6_2->translate.z;
    (*(f32*)(stack.bytes+0x3C)) = arg0->velocity.x;
    (*(f32*)(stack.bytes+0x40)) = arg0->velocity.y;
    (*(f32*)(stack.bytes+0x44)) = arg0->velocity.z;
    PSMTXMultVec((f32 (*)[4]) &((f32*)(stack.bytes+0xA8))[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
    if (((u8) arg0->appsrt->generatorOwned != 0) && !(arg0->kind & 4)) {
        PSMTXMultVec(rvmtxRot, (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
    }
    temp_f22 = (*(f32*)(stack.bytes+0x3C));
    temp_f21 = (*(f32*)(stack.bytes+0x40));
    (*(f32*)(stack.bytes+0x3C)) = arg0->position.x;
    temp_f20 = (*(f32*)(stack.bytes+0x44));
    (*(f32*)(stack.bytes+0x40)) = arg0->position.y;
    (*(f32*)(stack.bytes+0x44)) = arg0->position.z;
    temp_r3_2 = arg0->appsrt;
    if ((u8) temp_r3_2->generatorOwned != 0) {
        PSMTXMultVec((f32 (*)[4]) &((f32*)(stack.bytes+0xA8))[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
        PSMTXMultVec(rvmtxRot, (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
        temp_r3_3 = arg0->appsrt;
        (*(f32*)(stack.bytes+0x3C)) += temp_r3_3->translate.x;
        (*(f32*)(stack.bytes+0x40)) += temp_r3_3->translate.y;
        (*(f32*)(stack.bytes+0x44)) += temp_r3_3->translate.z;
    } else {
        PSMTXMultVec((f32 (*)[4]) temp_r3_2->matrix[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
    }
    temp_f25 = (*(f32*)(stack.bytes+0x3C));
    temp_f24 = (*(f32*)(stack.bytes+0x40));
    temp_f23 = (*(f32*)(stack.bytes+0x44));
    if (arg1 != NULL) {
        temp_r4 = arg0->appsrt;
        PSMTXScale((f32 (*)[4]) &((f32*)(stack.bytes+0x78))[0], temp_r4->scale.x, temp_r4->scale.y, 1.0f);
        PSMTXConcat(rvmtx, (f32 (*)[4]) &((f32*)(stack.bytes+0x78))[0], (f32 (*)[4]) &((f32*)(stack.bytes+0x78))[0]);
        temp_f6 = arg0->size;
        var_f31 = ((f32*)(stack.bytes+0x78))[0] * temp_f6;
        var_f30 = -((f32*)(stack.bytes+0x78))[1] * temp_f6;
        var_f29 = (*(f32*)(stack.bytes+0x88)) * temp_f6;
        var_f28 = -(*(f32*)(stack.bytes+0x8C)) * temp_f6;
        var_f27 = (*(f32*)(stack.bytes+0x98)) * temp_f6;
        var_f26 = -(*(f32*)(stack.bytes+0x9C)) * temp_f6;
    } else {
        temp_r7 = arg0->appsrt;
        temp_r6_3 = vmtx;
        temp_f3 = (*(f32*)((u8*)temp_r6_3+0x1C));
        temp_f2 = temp_r7->scale.x + (*(f32*)((u8*)temp_r6_3+0xC));
        temp_f4 = (*(f32*)((u8*)temp_r6_3+0x2C));
        (*(f32*)(stack.bytes+0x30)) = temp_f2;
        temp_f1 = temp_r7->scale.y;
        (*(f32*)(stack.bytes+0x38)) = temp_f4;
        (*(f32*)(stack.bytes+0x24)) = temp_f2;
        (*(f32*)(stack.bytes+0x34)) = temp_f1 + temp_f3;
        (*(f32*)(stack.bytes+0x28)) = -temp_f1 + temp_f3;
        (*(f32*)(stack.bytes+0x2C)) = temp_f4;
        PSMTXMultVec(rvmtx, (PSVec *) &(*(f32*)(stack.bytes+0x30)), (PSVec *) &(*(f32*)(stack.bytes+0x30)));
        temp_f3_2 = arg0->size;
        var_f31 = (*(f32*)(stack.bytes+0x30)) * temp_f3_2;
        var_f29 = (*(f32*)(stack.bytes+0x34)) * temp_f3_2;
        var_f27 = (*(f32*)(stack.bytes+0x38)) * temp_f3_2;
        PSMTXMultVec(rvmtx, (PSVec *) &(*(f32*)(stack.bytes+0x24)), (PSVec *) &(*(f32*)(stack.bytes+0x24)));
        temp_f3_3 = arg0->size;
        var_f30 = (*(f32*)(stack.bytes+0x24)) * temp_f3_3;
        var_f28 = (*(f32*)(stack.bytes+0x28)) * temp_f3_3;
        var_f26 = (*(f32*)(stack.bytes+0x2C)) * temp_f3_3;
    }
    temp_r28 = arg0->generator;
    if ((temp_r28 != NULL) && (temp_r28->transformFlags & 0x20)) {
        temp_f0 = temp_r28->scale.x;
        temp_f1_2 = temp_r28->scale.y;
        temp_f2_2 = temp_r28->scale.z;
        var_f31 *= temp_f0;
        var_f30 *= temp_f0;
        var_f29 *= temp_f1_2;
        var_f28 *= temp_f1_2;
        var_f27 *= temp_f2_2;
        var_f26 *= temp_f2_2;
    }
    temp_r3_4 = arg0->kind;
    if ((temp_r3_4 & 0x100000) || (temp_r3_4 & 0x200000)) {
        if (prj[0] == 0.0f) {
            if (temp_r3_4 & 4) {
                if (temp_r28 == NULL) {
                    var_f5 = arg0->position.x;
                    var_f1 = arg0->position.y;
                    var_f0 = arg0->position.z;
                } else {
                    temp_f17 = (f32) sin((f64) arg0->gravity);
                    temp_f16 = (f32) sin((f64) arg0->friction);
                    temp_f15 = (f32) cos((f64) arg0->gravity);
                    temp_f14 = (f32) cos((f64) arg0->friction);
                    temp_f19 = arg0->velocity.z - temp_r28->param1;
                    var_f18 = temp_r28->radius;
                    (*(f32*)(stack.bytes+0xE4)) = arg0->velocity.x - temp_r28->gravity;
                    if (var_f18 < 0.0f) {
                        var_f18 = -var_f18;
                    }
                    var_f1_2 = temp_r28->angle;
                    if (var_f1_2 < 0.0f) {
                        var_f1_2 = -var_f1_2;
                    }
                    temp_f18 = ((temp_f19 * (f32) tan((f64) var_f1_2)) + var_f18) * arg0->velocity.y;
                    (*(f32*)(stack.bytes+0xE0)) = temp_f18 * (f32) cos((f64) (*(f32*)(stack.bytes+0xE4)));
                    temp_f9 = -(*(f32*)(stack.bytes+0xE0));
                    temp_f6_2 = temp_f18 * (f32) sin((f64) (*(f32*)(stack.bytes+0xE4)));
                    var_f5 = temp_r28->position.x + (((*(f32*)(stack.bytes+0xE0)) * temp_f14) + (temp_f19 * temp_f16));
                    var_f1 = temp_r28->position.y + ((temp_f14 * (temp_f19 * temp_f17)) + ((temp_f16 * (temp_f9 * temp_f17)) + (temp_f6_2 * temp_f15)));
                    var_f0 = temp_r28->position.z + ((temp_f14 * (temp_f19 * temp_f15)) + ((temp_f16 * (temp_f9 * temp_f15)) - (temp_f6_2 * temp_f17)));
                }
                (*(f32*)(stack.bytes+0x3C)) = var_f5;
                (*(f32*)(stack.bytes+0x40)) = var_f1;
                (*(f32*)(stack.bytes+0x44)) = var_f0;
                temp_r3_5 = arg0->appsrt;
                if ((u8) temp_r3_5->generatorOwned != 0) {
                    PSMTXMultVec((f32 (*)[4]) &((f32*)(stack.bytes+0xA8))[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
                    PSMTXMultVec(rvmtxRot, (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
                    temp_r3_6 = arg0->appsrt;
                    (*(f32*)(stack.bytes+0x3C)) += temp_r3_6->translate.x;
                    (*(f32*)(stack.bytes+0x40)) += temp_r3_6->translate.y;
                    (*(f32*)(stack.bytes+0x44)) += temp_r3_6->translate.z;
                } else {
                    PSMTXMultVec((f32 (*)[4]) temp_r3_5->matrix[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
                }
                var_f5_2 = (*(f32*)(stack.bytes+0x3C));
                var_f1_3 = (*(f32*)(stack.bytes+0x40));
                var_f6 = (*(f32*)(stack.bytes+0x44));
            } else {
                var_f5_2 = temp_f25 - temp_f22;
                var_f1_3 = temp_f24 - temp_f21;
                var_f6 = temp_f23 - temp_f20;
            }
            temp_r3_7 = vmtx;
            temp_f4_2 = (*(f32*)((u8*)temp_r3_7+0x24));
            temp_f7 = (*(f32*)((u8*)temp_r3_7+0x20));
            temp_f9_2 = (*(f32*)((u8*)temp_r3_7+0x28));
            temp_f10 = (*(f32*)((u8*)temp_r3_7+0x2C));
            temp_f8 = temp_f10 + ((temp_f9_2 * temp_f23) + ((temp_f7 * temp_f25) + (temp_f4_2 * temp_f24)));
            if (temp_f8 != 0.0f) {
                temp_f8_2 = -1.0f / temp_f8;
                temp_f0_2 = temp_f10 + ((temp_f9_2 * var_f6) + ((temp_f7 * var_f5_2) + (temp_f4_2 * var_f1_3)));
                if (temp_f0_2 != 0.0f) {
                    temp_f7_2 = -1.0f / temp_f0_2;
                    temp_r3_8 = pvmtx;
                    temp_f10_2 = temp_r3_8[0][1];
                    temp_f14_2 = temp_r3_8[1][1];
                    temp_f2_3 = temp_r3_8[1][0];
                    temp_f0_3 = temp_r3_8[0][2];
                    temp_f3_4 = temp_r3_8[1][2];
                    temp_f1_3 = temp_r3_8[0][3];
                    temp_f4_3 = temp_r3_8[1][3];
                    var_f1_4 = (temp_f8_2 * (temp_f1_3 + ((temp_f0_3 * temp_f23) + ((pvmtx[0][0] * temp_f25) + (temp_f10_2 * temp_f24))))) - (temp_f7_2 * (temp_f1_3 + ((temp_f0_3 * var_f6) + ((pvmtx[0][0] * var_f5_2) + (temp_f10_2 * var_f1_3)))));
                    var_f2 = (temp_f8_2 * (temp_f4_3 + ((temp_f3_4 * temp_f23) + ((temp_f2_3 * temp_f25) + (temp_f14_2 * temp_f24))))) - (temp_f7_2 * (temp_f4_3 + ((temp_f3_4 * var_f6) + ((temp_f2_3 * var_f5_2) + (temp_f14_2 * var_f1_3)))));
                    goto block_49;
                }
            }
            goto block_56;
        }
        if (temp_r3_4 & 4) {
            if (temp_r28 == NULL) {
                var_f5_3 = arg0->position.x;
                var_f1_5 = arg0->position.y;
                var_f0_2 = arg0->position.z;
            } else {
                temp_f14_3 = (f32) sin((f64) arg0->gravity);
                temp_f15_2 = (f32) sin((f64) arg0->friction);
                temp_f16_2 = (f32) cos((f64) arg0->gravity);
                temp_f17_2 = (f32) cos((f64) arg0->friction);
                temp_f18_2 = arg0->velocity.z - temp_r28->param1;
                var_f19 = temp_r28->radius;
                (*(f32*)(stack.bytes+0xDC)) = arg0->velocity.x - temp_r28->gravity;
                if (var_f19 < 0.0f) {
                    var_f19 = -var_f19;
                }
                var_f1_6 = temp_r28->angle;
                if (var_f1_6 < 0.0f) {
                    var_f1_6 = -var_f1_6;
                }
                temp_f19_2 = ((temp_f18_2 * (f32) tan((f64) var_f1_6)) + var_f19) * arg0->velocity.y;
                (*(f32*)(stack.bytes+0xD8)) = temp_f19_2 * (f32) cos((f64) (*(f32*)(stack.bytes+0xDC)));
                temp_f9_3 = -(*(f32*)(stack.bytes+0xD8));
                temp_f6_3 = temp_f19_2 * (f32) sin((f64) (*(f32*)(stack.bytes+0xDC)));
                var_f5_3 = temp_r28->position.x + (((*(f32*)(stack.bytes+0xD8)) * temp_f17_2) + (temp_f18_2 * temp_f15_2));
                var_f1_5 = temp_r28->position.y + ((temp_f17_2 * (temp_f18_2 * temp_f14_3)) + ((temp_f15_2 * (temp_f9_3 * temp_f14_3)) + (temp_f6_3 * temp_f16_2)));
                var_f0_2 = temp_r28->position.z + ((temp_f17_2 * (temp_f18_2 * temp_f16_2)) + ((temp_f15_2 * (temp_f9_3 * temp_f16_2)) - (temp_f6_3 * temp_f14_3)));
            }
            (*(f32*)(stack.bytes+0x3C)) = var_f5_3;
            (*(f32*)(stack.bytes+0x40)) = var_f1_5;
            (*(f32*)(stack.bytes+0x44)) = var_f0_2;
            temp_r3_9 = arg0->appsrt;
            if ((u8) temp_r3_9->generatorOwned != 0) {
                PSMTXMultVec((f32 (*)[4]) &((f32*)(stack.bytes+0xA8))[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
                PSMTXMultVec(rvmtxRot, (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
                temp_r3_10 = arg0->appsrt;
                (*(f32*)(stack.bytes+0x3C)) += temp_r3_10->translate.x;
                (*(f32*)(stack.bytes+0x40)) += temp_r3_10->translate.y;
                (*(f32*)(stack.bytes+0x44)) += temp_r3_10->translate.z;
            } else {
                PSMTXMultVec((f32 (*)[4]) temp_r3_9->matrix[0], (PSVec *) &(*(f32*)(stack.bytes+0x3C)), (PSVec *) &(*(f32*)(stack.bytes+0x3C)));
            }
            temp_r3_11 = pvmtx;
            temp_f6_4 = temp_f24 - (*(f32*)(stack.bytes+0x40));
            temp_f5 = temp_f25 - (*(f32*)(stack.bytes+0x3C));
            temp_f6_5 = temp_f23 - (*(f32*)(stack.bytes+0x44));
            var_f1_4 = (temp_r3_11[0][2] * temp_f6_5) + ((pvmtx[0][0] * temp_f5) + (temp_r3_11[0][1] * temp_f6_4));
            var_f2 = (temp_r3_11[1][2] * temp_f6_5) + ((temp_r3_11[1][0] * temp_f5) + (temp_r3_11[1][1] * temp_f6_4));
        } else {
            temp_r3_12 = pvmtx;
            var_f1_4 = (temp_r3_12[0][2] * temp_f20) + ((pvmtx[0][0] * temp_f22) + (temp_r3_12[0][1] * temp_f21));
            var_f2 = (temp_r3_12[1][2] * temp_f20) + ((temp_r3_12[1][0] * temp_f22) + (temp_r3_12[1][1] * temp_f21));
        }
block_49:
        if (fabs(var_f2) < __float_min[0]) {

            if (var_f1_4 >= 0.0f) {
                var_f1_7 = 1.5707964f;
            } else {
                var_f1_7 = -1.5707964f;
            }
        } else {
            var_f1_7 = (f32) atan2((f64) var_f1_4, (f64) var_f2);
        }
        if (arg0->kind & 0x200000) {
            var_f1_7 += arg0->rotate;
        }
    } else {
block_56:
        var_f1_7 = arg0->rotate;
    }
    if (fabs(var_f1_7) > 0.01) {
        (*(f32*)(stack.bytes+0x18)) = (var_f29 * var_f26) - (var_f27 * var_f28);
        (*(f32*)(stack.bytes+0x1C)) = (var_f27 * var_f30) - (var_f31 * var_f26);
        (*(f32*)(stack.bytes+0x20)) = (var_f31 * var_f28) - (var_f29 * var_f30);
        PSMTXRotAxisRad((f32 (*)[4]) &((f32*)(stack.bytes+0x48))[0], (PSVec *) &(*(f32*)(stack.bytes+0x18)), var_f1_7);
        temp_f4_4 = ((*(f32*)(stack.bytes+0x58)) * var_f31) + ((*(f32*)(stack.bytes+0x5C)) * var_f29);
        temp_f1_4 = ((*(f32*)(stack.bytes+0x58)) * var_f30) + ((*(f32*)(stack.bytes+0x5C)) * var_f28);
        temp_f3_5 = ((*(f32*)(stack.bytes+0x68)) * var_f31) + ((*(f32*)(stack.bytes+0x6C)) * var_f29);
        temp_f0_4 = ((*(f32*)(stack.bytes+0x68)) * var_f30) + ((*(f32*)(stack.bytes+0x6C)) * var_f28);
        var_f31 = (((f32*)(stack.bytes+0x48))[2] * var_f27) + ((((f32*)(stack.bytes+0x48))[0] * var_f31) + (((f32*)(stack.bytes+0x48))[1] * var_f29));
        var_f29 = ((*(f32*)(stack.bytes+0x60)) * var_f27) + temp_f4_4;
        var_f27 = ((*(f32*)(stack.bytes+0x70)) * var_f27) + temp_f3_5;
        var_f30 = (((f32*)(stack.bytes+0x48))[2] * var_f26) + ((((f32*)(stack.bytes+0x48))[0] * var_f30) + (((f32*)(stack.bytes+0x48))[1] * var_f28));
        var_f28 = ((*(f32*)(stack.bytes+0x60)) * var_f26) + temp_f1_4;
        var_f26 = ((*(f32*)(stack.bytes+0x70)) * var_f26) + temp_f0_4;
    }
    (*(f32*)(stack.bytes+0x8)) = var_f27;
    (*(f32*)(stack.bytes+0xC)) = var_f30;
    (*(f32*)(stack.bytes+0x10)) = var_f28;
    (*(f32*)(stack.bytes+0x14)) = var_f26;
    psDispSubMakePolygon(arg0, arg1, temp_f25, temp_f24, temp_f23, temp_f22, temp_f21, temp_f20, var_f31, var_f29, (*(f32*)(stack.bytes+0x8)), (*(f32*)(stack.bytes+0xC)), (*(f32*)(stack.bytes+0x10)), (*(f32*)(stack.bytes+0x14)));
}

__declspec(weak) void psDispSubMakePolygon(PSParticle *arg0, u32 *arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 arg_sp8, f32 arg_spC, f32 arg_sp10, f32 arg_sp14) {
    union { f64 alignment; u8 bytes[316]; } stack;
    f64 saved390;
    PSAppSRT *temp_r6;
    PSGenerator *temp_r27;
    PSGenerator *temp_r27_2;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_13;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_16;
    f32 temp_f0_17;
    f32 temp_f0_18;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f15;
    f32 temp_f15_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f17;
    f32 temp_f17_2;
    f32 temp_f17_3;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f2_4;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 var_f0;
    f32 var_f14;
    f32 var_f14_2;
    f32 var_f15;
    f32 var_f15_2;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f21;
    f32 var_f22;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f5;
    f64 temp_f2;
    f64 temp_f2_2;
    f64 temp_f2_3;
    f64 temp_f2_5;
    f64 temp_f2_6;
    f64 temp_f2_7;
    s16 temp_r8;
    s32 temp_r0_2;
    s32 temp_r11;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r5;
    u16 temp_r5;
    u32 *var_r29;
    u32 *var_r29_2;
    u32 temp_r0;
    u32 temp_r3;
    u32 temp_r3_2;
    u32 temp_r3_5;
    u32 temp_r3_6;
    u32 temp_r3_7;
    u32 temp_r3_8;
    u32 temp_r3_9;
    u32 temp_r4_2;
    u32 temp_r5_2;
    u32 temp_r6_3;
    u32 temp_r6_4;
    u32 var_r25;
    u32 var_r30;
    u8 temp_r12;
    u8 temp_r25;
    u8 temp_r26;
    u8 temp_r26_2;
    u8 temp_r27_3;
    u8 temp_r27_4;
    u8 temp_r6_2;
    u8 temp_r7;
    u8 var_ctr;
    u8 var_ctr_2;

    (*(f32*)(stack.bytes+0x8)) = farg3;
    (*(f32*)(stack.bytes+0xC)) = farg4;
    (*(f32*)(stack.bytes+0x10)) = farg5;
    if ((s32) currentMtx != 0) {
        currentMtx = 0;
        GXSetCurrentMtx(0U);
    }
    temp_r3 = arg0->kind;
    if (temp_r3 & 0x100000) {
        if (temp_r3 & 4) {
            if ((PSAppSRT *) arg0->appsrt != NULL) {
                temp_r27 = arg0->generator;
                if (temp_r27 == NULL) {
                    var_f15 = arg0->position.x;
                    var_f14 = arg0->position.y;
                    var_f16 = arg0->position.z;
                } else {
                    temp_f17 = (f32) sin((f64) arg0->gravity);
                    temp_f16 = (f32) sin((f64) arg0->friction);
                    temp_f15 = (f32) cos((f64) arg0->gravity);
                    temp_f14 = (f32) cos((f64) arg0->friction);
                    temp_f21 = arg0->velocity.z - temp_r27->param1;
                    var_f22 = temp_r27->radius;
                    (*(f32*)(stack.bytes+0x12C)) = arg0->velocity.x - temp_r27->gravity;
                    if (var_f22 < 0.0f) {
                        var_f22 = -var_f22;
                    }
                    var_f1 = temp_r27->angle;
                    if (var_f1 < 0.0f) {
                        var_f1 = -var_f1;
                    }
                    temp_f22 = ((temp_f21 * (f32) tan((f64) var_f1)) + var_f22) * arg0->velocity.y;
                    temp_f0 = temp_f22 * (f32) cos((f64) (*(f32*)(stack.bytes+0x12C)));
                    (*(f32*)(stack.bytes+0x128)) = temp_f0;
                    temp_f5 = -temp_f0;
                    temp_f8 = temp_f22 * (f32) sin((f64) (*(f32*)(stack.bytes+0x12C)));
                    var_f15 = temp_r27->position.x + (((*(f32*)(stack.bytes+0x128)) * temp_f14) + (temp_f21 * temp_f16));
                    var_f14 = temp_r27->position.y + ((temp_f14 * (temp_f21 * temp_f17)) + ((temp_f16 * (temp_f5 * temp_f17)) + (temp_f8 * temp_f15)));
                    var_f16 = temp_r27->position.z + ((temp_f14 * (temp_f21 * temp_f15)) + ((temp_f16 * (temp_f5 * temp_f15)) - (temp_f8 * temp_f17)));
                }
                temp_r6 = arg0->appsrt;
                HSD_MtxSRT((f32 (*)[4]) &((f32*)(stack.bytes+0xA4))[0], &temp_r6->scale, &temp_r6->rotation, &temp_r6->translate, 0);
                (*(f32*)(stack.bytes+0x98)) = var_f15;
                (*(f32*)(stack.bytes+0x9C)) = var_f14;
                (*(f32*)(stack.bytes+0xA0)) = var_f16;
                PSMTXMultVec((f32 (*)[4]) &((f32*)(stack.bytes+0xA4))[0], (PSVec *) &(*(f32*)(stack.bytes+0x98)), (PSVec *) &(*(f32*)(stack.bytes+0x98)));
                var_f14_2 = (*(f32*)(stack.bytes+0x98));
                var_f15_2 = (*(f32*)(stack.bytes+0x9C));
                var_f16_2 = (*(f32*)(stack.bytes+0xA0));
            } else {
                temp_r27_2 = arg0->generator;
                if (temp_r27_2 == NULL) {
                    var_f14_2 = arg0->position.x;
                    var_f15_2 = arg0->position.y;
                    var_f16_2 = arg0->position.z;
                } else {
                    temp_f14_2 = (f32) sin((f64) arg0->gravity);
                    temp_f15_2 = (f32) sin((f64) arg0->friction);
                    temp_f16_2 = (f32) cos((f64) arg0->gravity);
                    temp_f17_2 = (f32) cos((f64) arg0->friction);
                    temp_f22_2 = arg0->velocity.z - temp_r27_2->param1;
                    var_f21 = temp_r27_2->radius;
                    (*(f32*)(stack.bytes+0x134)) = arg0->velocity.x - temp_r27_2->gravity;
                    if (var_f21 < 0.0f) {
                        var_f21 = -var_f21;
                    }
                    var_f1_2 = temp_r27_2->angle;
                    if (var_f1_2 < 0.0f) {
                        var_f1_2 = -var_f1_2;
                    }
                    temp_f21_2 = ((temp_f22_2 * (f32) tan((f64) var_f1_2)) + var_f21) * arg0->velocity.y;
                    temp_f0_2 = temp_f21_2 * (f32) cos((f64) (*(f32*)(stack.bytes+0x134)));
                    (*(f32*)(stack.bytes+0x130)) = temp_f0_2;
                    temp_f5_2 = -temp_f0_2;
                    temp_f8_2 = temp_f21_2 * (f32) sin((f64) (*(f32*)(stack.bytes+0x134)));
                    var_f14_2 = temp_r27_2->position.x + (((*(f32*)(stack.bytes+0x130)) * temp_f17_2) + (temp_f22_2 * temp_f15_2));
                    var_f15_2 = temp_r27_2->position.y + ((temp_f17_2 * (temp_f22_2 * temp_f14_2)) + ((temp_f15_2 * (temp_f5_2 * temp_f14_2)) + (temp_f8_2 * temp_f16_2)));
                    var_f16_2 = temp_r27_2->position.z + ((temp_f17_2 * (temp_f22_2 * temp_f16_2)) + ((temp_f15_2 * (temp_f5_2 * temp_f16_2)) - (temp_f8_2 * temp_f14_2)));
                }
            }
        } else {
            var_f14_2 = farg0 - (*(f32*)(stack.bytes+0x8));
            var_f15_2 = farg1 - (*(f32*)(stack.bytes+0xC));
            var_f16_2 = farg2 - (*(f32*)(stack.bytes+0x10));
        }
        temp_r0 = arg0->kind;
        temp_r4 = temp_r0 & 0x80000080;
        switch (temp_r4) {                          /* switch 1; irregular */
        default:                                    /* switch 1 */
        case 0x0:                                   /* switch 1 */
            temp_r5 = arg0->primCount;
            if (temp_r5 != 0) {
                temp_r6_2 = arg0->primTarget[0];
                temp_r7 = arg0->primTarget[1];
                temp_r11 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r5;
                temp_r12 = arg0->primTarget[2];
                temp_r27_3 = arg0->primTarget[3];
                (*(s8*)(stack.bytes+0x94)) = (s8) ((s32) ((temp_r6_2 << 0x10) + (temp_r11 * (arg0->primColor[0] - temp_r6_2))) >> 0x10);
                (*(u8*)(stack.bytes+0x95)) = (u8) ((s32) ((temp_r7 << 0x10) + (temp_r11 * (arg0->primColor[1] - temp_r7))) >> 0x10);
                (*(u8*)(stack.bytes+0x96)) = (u8) ((s32) ((temp_r12 << 0x10) + (temp_r11 * (arg0->primColor[2] - temp_r12))) >> 0x10);
                (*(u8*)(stack.bytes+0x97)) = (u8) ((s32) ((temp_r27_3 << 0x10) + (temp_r11 * (arg0->primColor[3] - temp_r27_3))) >> 0x10);
            } else {
                *(u32*)&(*(s8*)(stack.bytes+0x94)) = (s32) *(u32*)arg0->primColor;
            }
            break;
        case 0x80:                                  /* switch 1 */
        case 0x80000080:                            /* switch 1 */
            (*(u8*)(stack.bytes+0x97)) = 0xFF;
            (*(u8*)(stack.bytes+0x96)) = 0xFF;
            (*(u8*)(stack.bytes+0x95)) = 0xFF;
            (*(s8*)(stack.bytes+0x94)) = 0xFF;
            break;
        }
        if (arg1 == NULL) {
            if (temp_r0 & 0x400) {
                GXClearVtxDesc();
                GXInvalidateVtxCache();
                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
                GXBegin(GX_QUADS, GX_VTXFMT2, 4U);
            } else {
                GXClearVtxDesc();
                GXInvalidateVtxCache();
                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
                GXBegin(GX_QUADS, GX_VTXFMT3, 4U);
            }
            temp_f0_3 = var_f16_2 - arg_sp8;
            (*(f32*)(stack.bytes+0x124)) = temp_f0_3;
            temp_f0_4 = (f32) temp_f0_3;
            (*(f32*)(stack.bytes+0x88)) = temp_f0_4;
            saved390 = (f64) (var_f15_2 - farg7);

            (*(f32*)(stack.bytes+0x120)) = (f32) saved390;
            temp_f0_5 = (f32) saved390;
            (*(f32*)(stack.bytes+0x84)) = temp_f0_5;
            saved390 = (f64) (var_f14_2 - farg6);
            (*(f32*)(stack.bytes+0x11C)) = (f32) saved390;
            temp_f0_6 = (f32) saved390;
            (*(f32*)(stack.bytes+0x80)) = temp_f0_6;
            saved390 = (f64) temp_f0_6;
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_6);
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_5);
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_4);
            temp_r0_2 = (((((*(u8*)(stack.bytes+0x95)) * 0x10) & 0xF00 & ~0xF000) | (((u8) (*(s8*)(stack.bytes+0x94)) << 8) & 0xF000)) & ~0xF0) | ((*(u8*)(stack.bytes+0x96)) & 0xF0);
            *(volatile s16 *)0xCC008000 = (temp_r0_2 & ~0xF) | (((u32) (s32) ((f32) (*(u8*)(stack.bytes+0x97)) * arg0->textureScale) >> 4U) & 0xF);
            temp_r5_2 = arg0->kind;
            if (temp_r5_2 & 0x400) {
                *(volatile u8 *)0xCC008000 = (s8) ((temp_r5_2 >> 0x10U) & 0xC);
            }
            temp_f0_7 = farg2 - arg_sp14;
            (*(f32*)(stack.bytes+0x118)) = temp_f0_7;
            temp_f0_8 = (f32) temp_f0_7;
            (*(f32*)(stack.bytes+0x7C)) = temp_f0_8;
            saved390 = (f64) (farg1 - arg_sp10);
            (*(f32*)(stack.bytes+0x114)) = (f32) saved390;
            temp_f0_9 = (f32) saved390;
            (*(f32*)(stack.bytes+0x78)) = temp_f0_9;
            saved390 = (f64) (farg0 - arg_spC);
            (*(f32*)(stack.bytes+0x110)) = (f32) saved390;
            temp_f0_10 = (f32) saved390;
            (*(f32*)(stack.bytes+0x74)) = temp_f0_10;
            temp_r8 = (((*(u8*)(stack.bytes+0x97)) >> 4U) & 0xF) | temp_r0_2;
            saved390 = (f64) temp_f0_10;
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_10);
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_9);
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_8);
            *(volatile s16 *)0xCC008000 = temp_r8;
            temp_r6_3 = arg0->kind;
            if (temp_r6_3 & 0x400) {
                *(volatile u8 *)0xCC008000 = (s8) (((temp_r6_3 >> 0x10U) & 0xC) + 1);
            }
            temp_f0_11 = farg2 + arg_sp8;
            (*(f32*)(stack.bytes+0x10C)) = temp_f0_11;
            temp_f0_12 = (f32) temp_f0_11;
            (*(f32*)(stack.bytes+0x70)) = temp_f0_12;
            saved390 = (f64) (farg1 + farg7);
            (*(f32*)(stack.bytes+0x108)) = (f32) saved390;
            temp_f0_13 = (f32) saved390;
            (*(f32*)(stack.bytes+0x6C)) = temp_f0_13;
            saved390 = (f64) (farg0 + farg6);
            (*(f32*)(stack.bytes+0x104)) = (f32) saved390;
            temp_f0_14 = (f32) saved390;
            (*(f32*)(stack.bytes+0x68)) = temp_f0_14;
            saved390 = (f64) temp_f0_14;
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_14);
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_13);
            *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_12);
            *(volatile s16 *)0xCC008000 = temp_r8;
            temp_r6_4 = arg0->kind;
            if (temp_r6_4 & 0x400) {
                *(volatile u8 *)0xCC008000 = (s8) (((temp_r6_4 >> 0x10U) & 0xC) + 2);
            }
            (*(f32*)(stack.bytes+0x64)) = var_f16_2 + arg_sp14;
            (*(f32*)(stack.bytes+0x60)) = var_f15_2 + arg_sp10;
            (*(f32*)(stack.bytes+0x5C)) = var_f14_2 + arg_spC;
            *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x5C)));
            *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x60)));
            *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x64)));
            *(volatile s16 *)0xCC008000 = (s16) ((((u32) (s32) ((f32) (*(u8*)(stack.bytes+0x97)) * arg0->textureScale) >> 4U) & 0xF) | temp_r0_2);
            temp_r3_2 = arg0->kind;
            if (temp_r3_2 & 0x400) {
                *(volatile u8 *)0xCC008000 = (s8) (((temp_r3_2 >> 0x10U) & 0xC) + 3);
            }
        } else {
            var_f0 = (arg_sp14 * arg_sp14) + ((arg_spC * arg_spC) + (arg_sp10 * arg_sp10));
            temp_f17_3 = 255.0f * (1.0f - arg0->textureScale);
            if (var_f0 > 0.0f) {
                temp_f2 = __frsqrte(var_f0);
                temp_f2_2 = 0.5 * temp_f2 * -(((f64) var_f0 * (temp_f2 * temp_f2)) - 3.0);
                temp_f2_3 = 0.5 * temp_f2_2 * -(((f64) var_f0 * (temp_f2_2 * temp_f2_2)) - 3.0);
                var_f0 = (f32) ((f64) var_f0 * (0.5 * temp_f2_3 * -(((f64) var_f0 * (temp_f2_3 * temp_f2_3)) - 3.0)));
            } else if (var_f0 < 0.0) {
                var_f0 = __float_nan[0];
            } else {
                (*(f32*)(stack.bytes+0x90)) = var_f0;
                temp_r3_3 = *(s32*)&(*(f32*)(stack.bytes+0x90)) & 0x7F800000;
                switch (temp_r3_3) {                /* switch 2; irregular */
                case 0x7F800000:                    /* switch 2 */
                    if (*(s32*)&(*(f32*)(stack.bytes+0x90)) & 0x7FFFFF) {
                        var_r0 = 1;
                    } else {
                        var_r0 = 2;
                    }
                    break;
                case 0x0:                           /* switch 2 */
                    if (*(s32*)&(*(f32*)(stack.bytes+0x90)) & 0x7FFFFF) {
                        var_r0 = 5;
                    } else {
                        var_r0 = 3;
                    }
                    break;
                default:                            /* switch 2 */
                    var_r0 = 4;
                    break;
                }
                if (var_r0 == 1) {
                    var_f0 = __float_nan[0];
                }
            }
            if (!(fabs(var_f0) < __float_min[0])) {
                temp_f3 = farg0 - var_f14_2;
                temp_f2_4 = farg1 - var_f15_2;
                temp_f4 = farg2 - var_f16_2;
                var_f5 = (temp_f4 * temp_f4) + ((temp_f3 * temp_f3) + (temp_f2_4 * temp_f2_4));
                if (var_f5 > 0.0f) {
                    temp_f2_5 = __frsqrte(var_f5);
                    temp_f2_6 = 0.5 * temp_f2_5 * -(((f64) var_f5 * (temp_f2_5 * temp_f2_5)) - 3.0);
                    temp_f2_7 = 0.5 * temp_f2_6 * -(((f64) var_f5 * (temp_f2_6 * temp_f2_6)) - 3.0);
                    var_f5 = (f32) ((f64) var_f5 * (0.5 * temp_f2_7 * -(((f64) var_f5 * (temp_f2_7 * temp_f2_7)) - 3.0)));
                } else if (var_f5 < 0.0) {
                    var_f5 = __float_nan[0];
                } else {
                    (*(f32*)(stack.bytes+0x8C)) = var_f5;
                    temp_r3_4 = *(s32*)&(*(f32*)(stack.bytes+0x8C)) & 0x7F800000;
                    switch (temp_r3_4) {            /* switch 3; irregular */
                    case 0x7F800000:                /* switch 3 */
                        if (*(s32*)&(*(f32*)(stack.bytes+0x8C)) & 0x7FFFFF) {
                            var_r0_2 = 1;
                        } else {
                            var_r0_2 = 2;
                        }
                        break;
                    case 0x0:                       /* switch 3 */
                        if (*(s32*)&(*(f32*)(stack.bytes+0x8C)) & 0x7FFFFF) {
                            var_r0_2 = 5;
                        } else {
                            var_r0_2 = 3;
                        }
                        break;
                    default:                        /* switch 3 */
                        var_r0_2 = 4;
                        break;
                    }
                    if (var_r0_2 == 1) {
                        var_f5 = __float_nan[0];
                    }
                }
                var_f1_3 = var_f5 / var_f0;
                if (var_f1_3 < 1.0f) {
                    var_f1_3 = 1.0f;
                }
                var_r30 = *arg1;
                var_r29 = (u32*)((u8*)arg1 + 4);
loop_99:
                if (var_r30 != 0) {
                    temp_r26 = ((u8*)var_r29)[0x0];
                    temp_r25 = ((u8*)var_r29)[0x1];
                    var_r29 = (u32*)((u8*)var_r29 + 4);
                    if (arg0->kind & 0x400) {
                        GXClearVtxDesc();
                        GXInvalidateVtxCache();
                        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
                        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
                        GXBegin((enum _GXPrimitive) temp_r26, GX_VTXFMT5, (u16) temp_r25);
                    } else {
                        GXClearVtxDesc();
                        GXInvalidateVtxCache();
                        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
                        GXBegin((enum _GXPrimitive) temp_r26, GX_VTXFMT3, (u16) temp_r25);
                    }
                    var_ctr = temp_r25;
                    if ((s32) temp_r25 > 0) {
                        do {
                            var_f1_4 = *(f32*)var_r29;
                            temp_r3_5 = arg0->kind;
                            temp_f3_2 = 2.0f * (var_f1_4 - 0.5f);
                            if (temp_r3_5 & 0x40000) {
                                var_f1_4 = 1.0f - var_f1_4;
                            }
                            var_f2 = *(f32*)((u8*)var_r29+4);
                            var_r29 = (u32*)((u8*)var_r29 + 8);
                            var_r5 = (s32) -((var_f2 * temp_f17_3) - 255.0f);
                            if (var_r5 < 0) {
                                var_r5 = 0;
                            }
                            if (var_r5 > 0xFF) {
                                var_r5 = 0xFF;
                            }
                            temp_f4_2 = 2.0f * (var_f2 - 0.5f);
                            if (temp_r3_5 & 0x80000) {
                                var_f2 = 1.0f - var_f2;
                            }
                            (*(f32*)(stack.bytes+0x58)) = (arg_sp14 * var_f1_3 * temp_f4_2) + ((arg_sp8 * temp_f3_2) + farg2);
                            saved390 = (f64) ((farg7 * temp_f3_2) + farg1);

                            (*(f32*)(stack.bytes+0x54)) = (arg_sp10 * var_f1_3 * temp_f4_2) + (f32) saved390;
                            saved390 = (f64) ((farg6 * temp_f3_2) + farg0);
                            (*(f32*)(stack.bytes+0x50)) = (arg_spC * var_f1_3 * temp_f4_2) + (f32) saved390;
                            *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x50)));
                            *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x54)));
                            *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x58)));
                            *(volatile s16 *)0xCC008000 = (s16) ((((u32) var_r5 >> 4U) & 0xF) | ((((((*(u8*)(stack.bytes+0x95)) * 0x10) & 0xF00 & ~0xF000) | (((u8) (*(s8*)(stack.bytes+0x94)) << 8) & 0xF000)) & ~0xF0) | ((*(u8*)(stack.bytes+0x96)) & 0xF0)));
                            if (arg0->kind & 0x400) {
                                *(volatile f32 *)0xCC008000 = var_f1_4;
                                *(volatile f32 *)0xCC008000 = var_f2;
                            }
                            var_ctr -= 1;
                        } while (var_ctr != 0);
                    }
                    var_r30 -= 1;
                    goto loop_99;
                }
            }
        }
    } else if (arg1 == NULL) {
        if (temp_r3 & 0x400) {
            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
        } else {
            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXBegin(GX_QUADS, GX_VTXFMT1, 4U);
        }
        temp_f0_15 = farg2 - arg_sp8;
        (*(f32*)(stack.bytes+0x100)) = temp_f0_15;
        temp_f0_16 = (f32) temp_f0_15;
        (*(f32*)(stack.bytes+0x4C)) = temp_f0_16;
        saved390 = (f64) (farg1 - farg7);

        (*(f32*)(stack.bytes+0xFC)) = (f32) saved390;
        temp_f0_17 = (f32) saved390;
        (*(f32*)(stack.bytes+0x48)) = temp_f0_17;
        saved390 = (f64) (farg0 - farg6);
        (*(f32*)(stack.bytes+0xF8)) = (f32) saved390;
        temp_f0_18 = (f32) saved390;
        (*(f32*)(stack.bytes+0x44)) = temp_f0_18;
        saved390 = (f64) temp_f0_18;
        *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_18);
        *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_17);
        *(volatile s16 *)0xCC008000 = PS_FIXED6(temp_f0_16);
        temp_r4_2 = arg0->kind;
        if (temp_r4_2 & 0x400) {
            *(volatile u8 *)0xCC008000 = (s8) ((temp_r4_2 >> 0x10U) & 0xC);
        }
        (*(f32*)(stack.bytes+0x40)) = farg2 - arg_sp14;
        (*(f32*)(stack.bytes+0x3C)) = farg1 - arg_sp10;
        (*(f32*)(stack.bytes+0x38)) = farg0 - arg_spC;
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x38)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x3C)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x40)));
        temp_r3_6 = arg0->kind;
        if (temp_r3_6 & 0x400) {
            *(volatile u8 *)0xCC008000 = (s8) (((temp_r3_6 >> 0x10U) & 0xC) + 1);
        }
        (*(f32*)(stack.bytes+0x34)) = farg2 + arg_sp8;
        (*(f32*)(stack.bytes+0x30)) = farg1 + farg7;
        (*(f32*)(stack.bytes+0x2C)) = farg0 + farg6;
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x2C)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x30)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x34)));
        temp_r3_7 = arg0->kind;
        if (temp_r3_7 & 0x400) {
            *(volatile u8 *)0xCC008000 = (s8) (((temp_r3_7 >> 0x10U) & 0xC) + 2);
        }
        (*(f32*)(stack.bytes+0x28)) = farg2 + arg_sp14;
        (*(f32*)(stack.bytes+0x24)) = farg1 + arg_sp10;
        (*(f32*)(stack.bytes+0x20)) = farg0 + arg_spC;
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x20)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x24)));
        *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x28)));
        temp_r3_8 = arg0->kind;
        if (temp_r3_8 & 0x400) {
            *(volatile u8 *)0xCC008000 = (s8) (((temp_r3_8 >> 0x10U) & 0xC) + 3);
        }
    } else {
        var_r25 = *arg1;
        var_r29_2 = (u32*)((u8*)arg1 + 4);
loop_126:
        if (var_r25 != 0) {
            temp_r26_2 = ((u8*)var_r29_2)[0x0];
            temp_r27_4 = ((u8*)var_r29_2)[0x1];
            var_r29_2 = (u32*)((u8*)var_r29_2 + 4);
            if (arg0->kind & 0x400) {
                GXClearVtxDesc();
                GXInvalidateVtxCache();
                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
                GXBegin((enum _GXPrimitive) temp_r26_2, GX_VTXFMT4, (u16) temp_r27_4);
            } else {
                GXClearVtxDesc();
                GXInvalidateVtxCache();
                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                GXBegin((enum _GXPrimitive) temp_r26_2, GX_VTXFMT1, (u16) temp_r27_4);
            }
            var_ctr_2 = temp_r27_4;
            if ((s32) temp_r27_4 > 0) {
                do {
                    var_f1_5 = *(f32*)var_r29_2;
                    temp_r3_9 = arg0->kind;
                    temp_f3_3 = 2.0f * (var_f1_5 - 0.5f);
                    if (temp_r3_9 & 0x40000) {
                        var_f1_5 = 1.0f - var_f1_5;
                    }
                    var_f2_2 = *(f32*)((u8*)var_r29_2+4);
                    var_r29_2 = (u32*)((u8*)var_r29_2 + 8);
                    temp_f4_3 = 2.0f * (var_f2_2 - 0.5f);
                    if (temp_r3_9 & 0x80000) {
                        var_f2_2 = 1.0f - var_f2_2;
                    }
                    (*(f32*)(stack.bytes+0x1C)) = (arg_sp14 * temp_f4_3) + ((arg_sp8 * temp_f3_3) + farg2);
                    saved390 = (f64) ((farg7 * temp_f3_3) + farg1);

                    (*(f32*)(stack.bytes+0x18)) = (arg_sp10 * temp_f4_3) + (f32) saved390;
                    saved390 = (f64) ((farg6 * temp_f3_3) + farg0);
                    (*(f32*)(stack.bytes+0x14)) = (arg_spC * temp_f4_3) + (f32) saved390;
                    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x14)));
                    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x18)));
                    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x1C)));
                    if (arg0->kind & 0x400) {
                        *(volatile f32 *)0xCC008000 = var_f1_5;
                        *(volatile f32 *)0xCC008000 = var_f2_2;
                    }
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
            var_r25 -= 1;
            goto loop_126;
        }
    }
}

__declspec(weak) void psDispSub(PSParticle *arg0, u32 *arg1) {
    union { f64 alignment; u8 bytes[84]; } stack;
    PSGenerator *temp_r28;
    f32 (*temp_r3_4)[4];
    f32 (*temp_r3_5)[4];
    f32 (*temp_r3_6)[4];
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f17;
    f32 temp_f17_2;
    f32 temp_f17_3;
    f32 temp_f17_4;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f19;
    f32 temp_f19_2;
    f32 temp_f19_3;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f30;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f3_4;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f4_4;
    f32 temp_f4_5;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f5_3;
    f32 temp_f5_4;
    f32 temp_f5_5;
    f32 temp_f5_6;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f6_3;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f7_3;
    f32 temp_f9;
    f32 temp_f9_2;
    f32 temp_f9_3;
    f32 var_f16;
    f32 var_f18;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f23;
    f32 var_f24;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f32 var_f28;
    f32 var_f2;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f5;
    f32 var_f8;
    f32 var_f9;
    u32 temp_r3_2;
    void *temp_r3;
    void *temp_r3_3;

    temp_f0 = arg0->position.x;
    var_f1 = arg0->position.y;
    temp_f2 = arg0->position.z;
    temp_f30 = var_f1;
    if (arg1 != NULL) {
        temp_r3 = rvmtx;
        temp_f9 = arg0->size;
        var_f28 = rvmtx[0][0] * temp_f9;
        var_f27 = -(*(f32*)((u8*)temp_r3+0x4)) * temp_f9;
        var_f26 = (*(f32*)((u8*)temp_r3+0x10)) * temp_f9;
        var_f25 = -(*(f32*)((u8*)temp_r3+0x14)) * temp_f9;
        var_f24 = (*(f32*)((u8*)temp_r3+0x20)) * temp_f9;
        var_f23 = -(*(f32*)((u8*)temp_r3+0x24)) * temp_f9;
    } else {
        temp_f6 = arg0->size;
        var_f28 = rx0 * temp_f6;
        var_f27 = rx1 * temp_f6;
        var_f26 = ry0 * temp_f6;
        var_f25 = ry1 * temp_f6;
        var_f24 = rz0 * temp_f6;
        var_f23 = rz1 * temp_f6;
    }
    temp_r28 = arg0->generator;
    if ((temp_r28 != NULL) && (temp_r28->transformFlags & 0x20)) {
        temp_f3 = temp_r28->scale.x;
        temp_f4 = temp_r28->scale.y;
        temp_f5 = temp_r28->scale.z;
        var_f28 *= temp_f3;
        var_f27 *= temp_f3;
        var_f26 *= temp_f4;
        var_f25 *= temp_f4;
        var_f24 *= temp_f5;
        var_f23 *= temp_f5;
    }
    temp_r3_2 = arg0->kind;
    if ((temp_r3_2 & 0x100000) || (temp_r3_2 & 0x200000)) {
        if (prj[0] == 0.0f) {
            if (temp_r3_2 & 4) {
                if (temp_r28 == NULL) {
                    var_f8 = temp_f0;
                    var_f4 = var_f1;
                    var_f9 = temp_f2;
                } else {
                    temp_f22 = (f32) sin((f64) arg0->gravity);
                    temp_f21 = (f32) sin((f64) arg0->friction);
                    temp_f20 = (f32) cos((f64) arg0->gravity);
                    temp_f19 = (f32) cos((f64) arg0->friction);
                    temp_f18 = arg0->velocity.z - temp_r28->param1;
                    var_f16 = temp_r28->radius;
                    temp_f17 = arg0->velocity.x - temp_r28->gravity;
                    if (var_f16 < 0.0f) {
                        var_f16 = -var_f16;
                    }
                    var_f1_2 = temp_r28->angle;
                    if (var_f1_2 < 0.0f) {
                        var_f1_2 = -var_f1_2;
                    }
                    temp_f16 = ((temp_f18 * (f32) tan((f64) var_f1_2)) + var_f16) * arg0->velocity.y;
                    temp_f17_2 = temp_f16 * (f32) cos((f64) temp_f17);
                    temp_f9_2 = -temp_f17_2;
                    temp_f5_2 = temp_f16 * (f32) sin((f64) temp_f17);
                    var_f8 = temp_r28->position.x + ((temp_f17_2 * temp_f19) + (temp_f18 * temp_f21));
                    var_f4 = temp_r28->position.y + ((temp_f19 * (temp_f18 * temp_f22)) + ((temp_f21 * (temp_f9_2 * temp_f22)) + (temp_f5_2 * temp_f20)));
                    var_f9 = temp_r28->position.z + ((temp_f19 * (temp_f18 * temp_f20)) + ((temp_f21 * (temp_f9_2 * temp_f20)) - (temp_f5_2 * temp_f22)));
                }
            } else {
                var_f8 = temp_f0 - arg0->velocity.x;
                var_f4 = var_f1 - arg0->velocity.y;
                var_f9 = temp_f2 - arg0->velocity.z;
            }
            temp_r3_3 = vmtx;
            temp_f0_2 = arg0->position.y;
            temp_f7 = (*(f32*)((u8*)temp_r3_3+0x24));
            temp_f10 = (*(f32*)((u8*)temp_r3_3+0x20));
            temp_f1 = arg0->position.x;
            temp_f12 = (*(f32*)((u8*)temp_r3_3+0x28));
            temp_f2_2 = arg0->position.z;
            temp_f13 = (*(f32*)((u8*)temp_r3_3+0x2C));
            temp_f11 = temp_f13 + ((temp_f12 * temp_f2_2) + ((temp_f10 * temp_f1) + (temp_f7 * temp_f0_2)));
            if (temp_f11 != 0.0f) {
                temp_f11_2 = -1.0f / temp_f11;
                temp_f3_2 = temp_f13 + ((temp_f12 * var_f9) + ((temp_f10 * var_f8) + (temp_f7 * var_f4)));
                if (temp_f3_2 != 0.0f) {
                    temp_f10_2 = -1.0f / temp_f3_2;
                    temp_r3_4 = pvmtx;
                    temp_f13_2 = temp_r3_4[0][1];
                    temp_f19_2 = temp_r3_4[1][1];
                    temp_f5_3 = temp_r3_4[1][0];
                    temp_f3_3 = temp_r3_4[0][2];
                    temp_f6_2 = temp_r3_4[1][2];
                    temp_f4_2 = temp_r3_4[0][3];
                    temp_f7_2 = temp_r3_4[1][3];
                    var_f1_3 = (temp_f11_2 * (temp_f4_2 + ((temp_f3_3 * temp_f2_2) + ((pvmtx[0][0] * temp_f1) + (temp_f13_2 * temp_f0_2))))) - (temp_f10_2 * (temp_f4_2 + ((temp_f3_3 * var_f9) + ((pvmtx[0][0] * var_f8) + (temp_f13_2 * var_f4)))));
                    var_f2 = (temp_f11_2 * (temp_f7_2 + ((temp_f6_2 * temp_f2_2) + ((temp_f5_3 * temp_f1) + (temp_f19_2 * temp_f0_2))))) - (temp_f10_2 * (temp_f7_2 + ((temp_f6_2 * var_f9) + ((temp_f5_3 * var_f8) + (temp_f19_2 * var_f4)))));
                    goto block_31;
                }
            }
            goto block_38;
        }
        if (temp_r3_2 & 4) {
            if (temp_r28 == NULL) {
                var_f4_2 = temp_f0;
                var_f5 = temp_f2;
            } else {
                temp_f19_3 = (f32) sin((f64) arg0->gravity);
                temp_f20_2 = (f32) sin((f64) arg0->friction);
                temp_f21_2 = (f32) cos((f64) arg0->gravity);
                temp_f22_2 = (f32) cos((f64) arg0->friction);
                temp_f16_2 = arg0->velocity.z - temp_r28->param1;
                var_f18 = temp_r28->radius;
                temp_f17_3 = arg0->velocity.x - temp_r28->gravity;
                if (var_f18 < 0.0f) {
                    var_f18 = -var_f18;
                }
                var_f1_4 = temp_r28->angle;
                if (var_f1_4 < 0.0f) {
                    var_f1_4 = -var_f1_4;
                }
                temp_f18_2 = ((temp_f16_2 * (f32) tan((f64) var_f1_4)) + var_f18) * arg0->velocity.y;
                temp_f17_4 = temp_f18_2 * (f32) cos((f64) temp_f17_3);
                temp_f9_3 = -temp_f17_4;
                temp_f5_4 = temp_f18_2 * (f32) sin((f64) temp_f17_3);
                var_f4_2 = temp_r28->position.x + ((temp_f17_4 * temp_f22_2) + (temp_f16_2 * temp_f20_2));
                var_f1 = temp_r28->position.y + ((temp_f22_2 * (temp_f16_2 * temp_f19_3)) + ((temp_f20_2 * (temp_f9_3 * temp_f19_3)) + (temp_f5_4 * temp_f21_2)));
                var_f5 = temp_r28->position.z + ((temp_f22_2 * (temp_f16_2 * temp_f21_2)) + ((temp_f20_2 * (temp_f9_3 * temp_f21_2)) - (temp_f5_4 * temp_f19_3)));
            }
            temp_r3_5 = pvmtx;
            temp_f7_3 = arg0->position.y - var_f1;
            temp_f6_3 = arg0->position.x - var_f4_2;
            temp_f5_5 = arg0->position.z - var_f5;
            var_f1_3 = (temp_r3_5[0][2] * temp_f5_5) + ((pvmtx[0][0] * temp_f6_3) + (temp_r3_5[0][1] * temp_f7_3));
            var_f2 = (temp_r3_5[1][2] * temp_f5_5) + ((temp_r3_5[1][0] * temp_f6_3) + (temp_r3_5[1][1] * temp_f7_3));
        } else {
            temp_r3_6 = pvmtx;
            temp_f4_3 = arg0->velocity.y;
            temp_f5_6 = arg0->velocity.x;
            temp_f4_4 = arg0->velocity.z;
            var_f1_3 = (temp_r3_6[0][2] * temp_f4_4) + ((pvmtx[0][0] * temp_f5_6) + (temp_r3_6[0][1] * temp_f4_3));
            var_f2 = (temp_r3_6[1][2] * temp_f4_4) + ((temp_r3_6[1][0] * temp_f5_6) + (temp_r3_6[1][1] * temp_f4_3));
        }
block_31:
        if (fabs(var_f2) < __float_min[0]) {

            if (var_f1_3 >= 0.0f) {
                var_f1_5 = 1.5707964f;
            } else {
                var_f1_5 = -1.5707964f;
            }
        } else {
            var_f1_5 = (f32) atan2((f64) var_f1_3, (f64) var_f2);
        }
        if (arg0->kind & 0x200000) {
            var_f1_5 += arg0->rotate;
        }
    } else {
block_38:
        var_f1_5 = arg0->rotate;
    }
    if (fabs(var_f1_5) > 0.01) {
        (*(f32*)(stack.bytes+0x18)) = (var_f26 * var_f23) - (var_f24 * var_f25);
        (*(f32*)(stack.bytes+0x1C)) = (var_f24 * var_f27) - (var_f28 * var_f23);
        (*(f32*)(stack.bytes+0x20)) = (var_f28 * var_f25) - (var_f26 * var_f27);
        PSMTXRotAxisRad((f32 (*)[4]) &((f32*)(stack.bytes+0x24))[0], (PSVec *) &(*(f32*)(stack.bytes+0x18)), var_f1_5);
        temp_f4_5 = ((*(f32*)(stack.bytes+0x34)) * var_f28) + ((*(f32*)(stack.bytes+0x38)) * var_f26);
        temp_f1_2 = ((*(f32*)(stack.bytes+0x34)) * var_f27) + ((*(f32*)(stack.bytes+0x38)) * var_f25);
        temp_f3_4 = ((*(f32*)(stack.bytes+0x44)) * var_f28) + ((*(f32*)(stack.bytes+0x48)) * var_f26);
        temp_f0_3 = ((*(f32*)(stack.bytes+0x44)) * var_f27) + ((*(f32*)(stack.bytes+0x48)) * var_f25);
        var_f28 = (((f32*)(stack.bytes+0x24))[2] * var_f24) + ((((f32*)(stack.bytes+0x24))[0] * var_f28) + (((f32*)(stack.bytes+0x24))[1] * var_f26));
        var_f26 = ((*(f32*)(stack.bytes+0x3C)) * var_f24) + temp_f4_5;
        var_f24 = ((*(f32*)(stack.bytes+0x4C)) * var_f24) + temp_f3_4;
        var_f27 = (((f32*)(stack.bytes+0x24))[2] * var_f23) + ((((f32*)(stack.bytes+0x24))[0] * var_f27) + (((f32*)(stack.bytes+0x24))[1] * var_f25));
        var_f25 = ((*(f32*)(stack.bytes+0x3C)) * var_f23) + temp_f1_2;
        var_f23 = ((*(f32*)(stack.bytes+0x4C)) * var_f23) + temp_f0_3;
    }
    (*(f32*)(stack.bytes+0x8)) = var_f24;
    (*(f32*)(stack.bytes+0xC)) = var_f27;
    (*(f32*)(stack.bytes+0x10)) = var_f25;
    (*(f32*)(stack.bytes+0x14)) = var_f23;
    psDispSubMakePolygon(arg0, arg1, temp_f0, temp_f30, temp_f2, arg0->velocity.x, arg0->velocity.y, arg0->velocity.z, var_f28, var_f26, (*(f32*)(stack.bytes+0x8)), (*(f32*)(stack.bytes+0xC)), (*(f32*)(stack.bytes+0x10)), (*(f32*)(stack.bytes+0x14)));
}

static void _psDispParticlesSub(u32 arg0, s32 arg1, PSGenerator *arg2, u32 arg3) {
    union { f64 alignment; u8 bytes[260]; } stack;
    PSParticle *var_r25;
    PSTex *temp_r3_8;
    enum _GXAttnFn var_r17;
    enum _GXAttnFn var_r17_2;
    enum _GXTexFilter temp_r4_5;
    enum _GXTexWrapMode var_r16_2;
    enum _GXTexWrapMode var_r17_3;
    f32 (*temp_r27)[4];
    f32 (*temp_r28)[4];
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f27;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f5;
    f32 temp_f7;
    f32 temp_f8;
    f32 var_f0;
    f32 var_f1;
    f32 var_f2;
    s32 temp_r3;
    s32 temp_r3_11;
    s32 temp_r3_2;
    s32 temp_r7;
    u16 temp_r4;
    u16 var_r0;
    u32 *var_r22;
    u32 temp_r0;
    u32 temp_r0_3;
    u32 temp_r3_10;
    u32 temp_r3_3;
    u32 temp_r3_4;
    u32 temp_r3_5;
    u32 temp_r3_7;
    u32 temp_r3_9;
    u32 temp_r4_2;
    u32* temp_r4_3;
    u32 var_r14;
    u32 var_r16 = 0;
    u32 var_r19;
    u32 var_r20;
    u32 var_r21;
    u32 var_r23;
    u8 temp_r0_2;
    u8 temp_r5;
    u8 temp_r6;
    u8 temp_r6_2;
    u8 var_r4;
    u8 var_r7;
    void **temp_r4_4;
    void **var_r4_2;
    void *temp_r26;
    void *temp_r29;
    u32** temp_r3_6;
    void *var_r18;
    void *var_r24;
    void *var_r4_3;

    (*(s32*)(stack.bytes+0xF0)) = 0;
    (*(u8*)(stack.bytes+0xED)) = 0;
    (*(u8*)(stack.bytes+0xEC)) = 0xFF;
    temp_r29 = vmtx;
    temp_r28 = (f32 (*)[4])prj;
    (*(s32*)(stack.bytes+0xE8)) = 1;
    temp_r27 = pvmtx;
    temp_r26 = rvmtx;
    (*(u32*)(stack.bytes+0x10)) = arg0;
    var_r23 = 0;
    (*(s32*)(stack.bytes+0x14)) = arg1;
    (*(u32*)(stack.bytes+0x18)) = arg3;
    (*(s32*)(stack.bytes+0xF8)) = 0;
    do {
        if ((*(u32*)(stack.bytes+0x10)) & (1 << (*(s32*)(stack.bytes+0xF8)))) {
            particleSort((*(s32*)(stack.bytes+0xF8)), &(*(PSParticle **)(stack.bytes+0x40)), &(*(PSParticle **)(stack.bytes+0x3C)));
            switch ((*(s32*)(stack.bytes+0x14))) {                         /* switch 1; irregular */
            case 1:                                 /* switch 1 */
                var_r25 = (*(PSParticle **)(stack.bytes+0x40));
block_8:
                (*(f32 **)(stack.bytes+0xFC)) = __float_epsilon;
loop_138:
                if (var_r25 != NULL) {
                    if (((u32) (*(s32*)(stack.bytes+0x14)) != 1U) || (var_r25->kind & 8)) {
                        if (!(var_r25->size < *(*(f32 **)(stack.bytes+0xFC))) && ((arg2 == NULL) || ((u16) var_r25->id == (u16) arg2->id)) && ((u32) var_r25->generator->camera == (*(u32*)(stack.bytes+0x18))) && !(var_r25->kind & 0x20000000)) {
                            if ((*(s32*)(stack.bytes+0xE8)) != 0) {
                                var_r24 = NULL;
                                prevPointSize = -1;
                                prevLineWidth = -1;
                                prevChanCtrl = -1;
                                psSetupTevInvalidState();
                                var_r16 &= 0xFEFFFFFF;
                                (*(u32*)(stack.bytes+0xF4)) = -1U;
                                var_r14 = -1U;
                                HSD_FogSet(NULL);
                                prevChanMat.g = 0xFF;
                                prevChanMat.b = 0xFF;
                                prevChanMat.a = 0xFF;
                                prevChanMat.r = 0xFF;
                                prevChanAmb.b = 0xFF;
                                prevChanAmb.g = 0xFF;
                                prevChanAmb.r = 0xFF;
                                prevChanAmb.a = 0xFF;
                                *(u32*)&(*(s32*)(stack.bytes+0x38)) = (s32) *(u32*)&prevChanMat;
                                GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&(*(s32*)(stack.bytes+0x38)));
                                *(u32*)&(*(s32*)(stack.bytes+0x34)) = (s32) *(u32*)&prevChanAmb;
                                GXSetChanAmbColor(GX_COLOR0A0, *(GXColor*)&(*(s32*)(stack.bytes+0x34)));
                                psSetupTevInvalidState();
                                psSetupTevCommon();
                                prevColorPrim.g = 0xFF;
                                prevColorPrim.b = 0xFF;
                                prevColorPrim.a = 0xFF;
                                prevColorEnv.g = 0;
                                prevColorPrim.r = 0xFF;
                                prevColorEnv.b = 0;
                                prevColorEnv.a = 0;
                                prevColorMat.g = 0xFF;
                                prevColorMat.b = 0xFF;
                                prevColorEnv.r = 0;
                                prevColorMat.r = 0xFF;
                                prevColorMat.a = 0xFF;
                                *(u32*)&(*(s32*)(stack.bytes+0x30)) = (s32) *(u32*)&prevColorPrim;
                                GXSetTevColor(GX_TEVREG0, *(GXColor*)&(*(s32*)(stack.bytes+0x30)));
                                *(u32*)&(*(s32*)(stack.bytes+0x2C)) = (s32) *(u32*)&prevColorEnv;
                                GXSetTevColor(GX_TEVREG1, *(GXColor*)&(*(s32*)(stack.bytes+0x2C)));
                                *(u32*)&(*(s32*)(stack.bytes+0x28)) = (s32) *(u32*)&prevColorMat;
                                GXSetTevColor(GX_TEVREG2, *(GXColor*)&(*(s32*)(stack.bytes+0x28)));
                                prevBlendMode = -1;
                                GXSetZCompLoc(0U);
                                HSD_CObjGetViewingMtx(HSD_CObjGetCurrent());
                                PSMTXInverse(vmtx, rvmtx);
                                if (prj[0] == 0.0f) {
                                    temp_f2 = temp_r28[0][2];
                                    temp_f0 = (*(f32*)((u8*)temp_r29+0x20));
                                    temp_f3 = (*(f32*)((u8*)temp_r29+0x24));
                                    temp_f7 = temp_r28[1][0];
                                    temp_f12 = (*(f32*)((u8*)temp_r29+0x28));
                                    temp_f10 = (*(f32*)((u8*)temp_r29+0x2C));
                                    temp_f27 = temp_r28[0][1];
                                    temp_f8 = temp_r28[0][3];
                                    pvmtx[0][0] = (f32) ((temp_f27 * vmtx[0][0]) + (temp_f2 * temp_f0));
                                    temp_r27[0][1] = (temp_f27 * (*(f32*)((u8*)temp_r29+0x4))) + (temp_f2 * temp_f3);
                                    temp_r27[0][2] = (temp_f27 * (*(f32*)((u8*)temp_r29+0x8))) + (temp_f2 * temp_f12);
                                    temp_r27[0][3] = (temp_f27 * (*(f32*)((u8*)temp_r29+0xC))) + (temp_f2 * temp_f10);
                                    temp_r27[1][0] = (temp_f8 * (*(f32*)((u8*)temp_r29+0x10))) + (temp_f7 * temp_f0);
                                    temp_r27[1][1] = (temp_f8 * (*(f32*)((u8*)temp_r29+0x14))) + (temp_f7 * temp_f3);
                                    temp_r27[1][2] = (temp_f8 * (*(f32*)((u8*)temp_r29+0x18))) + (temp_f7 * temp_f12);
                                    temp_r27[1][3] = (temp_f8 * (*(f32*)((u8*)temp_r29+0x1C))) + (temp_f7 * temp_f10);
                                } else {
                                    temp_f4 = temp_r28[0][1];
                                    temp_f3_2 = temp_r28[0][2];
                                    temp_f5 = temp_r28[0][3];
                                    temp_f4_2 = temp_r28[1][0];
                                    pvmtx[0][0] = (f32) ((temp_f4 * vmtx[0][0]) + temp_f3_2);
                                    temp_r27[0][1] = (temp_f4 * (*(f32*)((u8*)temp_r29+0x4))) + temp_f3_2;
                                    temp_r27[0][2] = (temp_f4 * (*(f32*)((u8*)temp_r29+0x8))) + temp_f3_2;
                                    temp_r27[0][3] = (temp_f4 * (*(f32*)((u8*)temp_r29+0xC))) + temp_f3_2;
                                    temp_r27[1][0] = (temp_f5 * (*(f32*)((u8*)temp_r29+0x10))) + temp_f4_2;
                                    temp_r27[1][1] = (temp_f5 * (*(f32*)((u8*)temp_r29+0x14))) + temp_f4_2;
                                    temp_r27[1][2] = (temp_f5 * (*(f32*)((u8*)temp_r29+0x18))) + temp_f4_2;
                                    temp_r27[1][3] = (temp_f5 * (*(f32*)((u8*)temp_r29+0x1C))) + temp_f4_2;
                                }
                                temp_f0_2 = (*(f32*)((u8*)temp_r26+0x4));
                                temp_f3_3 = (*(f32*)((u8*)temp_r26+0x10));
                                temp_f1 = (*(f32*)((u8*)temp_r26+0x14));
                                temp_f2_2 = (*(f32*)((u8*)temp_r26+0x20));
                                temp_f0_3 = (*(f32*)((u8*)temp_r26+0x24));
                                rx0 = rvmtx[0][0] + temp_f0_2;
                                rx1 = rvmtx[0][0] - temp_f0_2;
                                ry0 = temp_f3_3 + temp_f1;
                                ry1 = temp_f3_3 - temp_f1;
                                rz0 = temp_f2_2 + temp_f0_3;
                                rz1 = temp_f2_2 - temp_f0_3;
                                GXLoadPosMtxImm(vmtx, 0U);
                                (*(s32*)(stack.bytes+0xB0)) = ((const s32*)identityMtx)[0];
                                (*(s32*)(stack.bytes+0xB4)) = ((const s32*)identityMtx)[1];
                                (*(s32*)(stack.bytes+0xB8)) = ((const s32*)identityMtx)[2];
                                (*(s32*)(stack.bytes+0xBC)) = ((const s32*)identityMtx)[3];
                                (*(s32*)(stack.bytes+0xC0)) = ((const s32*)identityMtx)[4];
                                (*(s32*)(stack.bytes+0xC4)) = ((const s32*)identityMtx)[5];
                                (*(s32*)(stack.bytes+0xC8)) = ((const s32*)identityMtx)[6];
                                (*(s32*)(stack.bytes+0xCC)) = ((const s32*)identityMtx)[7];
                                (*(s32*)(stack.bytes+0xD0)) = ((const s32*)identityMtx)[8];
                                (*(s32*)(stack.bytes+0xD4)) = ((const s32*)identityMtx)[9];
                                (*(s32*)(stack.bytes+0xD8)) = ((const s32*)identityMtx)[10];
                                (*(s32*)(stack.bytes+0xDC)) = ((const s32*)identityMtx)[11];
                                GXLoadPosMtxImm((f32 (*)[4]) &(*(s32*)(stack.bytes+0xB0)), 3U);
                                currentMtx = 3;
                                if (3 != 0) {
                                    currentMtx = 0;
                                    GXSetCurrentMtx(0U);
                                }
                                GXEnableTexOffsets(GX_TEXCOORD0, 1U, 1U);
                                HSD_MtxGetRotationMtx(rvmtx, rvmtxRot, 0x7A, 0x78);
                                GXSetCullMode(GX_CULL_BACK);
                                GXSetArray(GX_VA_TEX0, billboard_tex0_u8, 2U);
                                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 6U);
                                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);
                                GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 6U);
                                GXSetVtxAttrFmt(GX_VTXFMT2, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 6U);
                                GXSetVtxAttrFmt(GX_VTXFMT2, GX_VA_CLR0, GX_TEX_ST, GX_RGBA4, 0U);
                                GXSetVtxAttrFmt(GX_VTXFMT2, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);
                                GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 6U);
                                GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_CLR0, GX_TEX_ST, GX_RGBA4, 0U);
                                GXSetVtxAttrFmt(GX_VTXFMT4, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 6U);
                                GXSetVtxAttrFmt(GX_VTXFMT4, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0U);
                                GXSetVtxAttrFmt(GX_VTXFMT5, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 6U);
                                GXSetVtxAttrFmt(GX_VTXFMT5, GX_VA_CLR0, GX_TEX_ST, GX_RGBA4, 0U);
                                GXSetVtxAttrFmt(GX_VTXFMT5, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0U);
                                (*(s32*)(stack.bytes+0xE8)) = 0;
                            }
                            temp_r3_2 = ((u32) var_r25->kind >> 0x16U) & 3;
                            if ((s32) prevBlendMode != temp_r3_2) {
                                prevBlendMode = temp_r3_2;
                                switch (temp_r3_2) { /* switch 2; irregular */
                                case 0:             /* switch 2 */
                                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                                    break;
                                case 1:             /* switch 2 */
                                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
                                    break;
                                case 2:             /* switch 2 */
                                    GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                                    break;
                                case 3:             /* switch 2 */
                                    GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTCLR, GX_BL_ZERO, GX_LO_CLEAR);
                                    break;
                                default:            /* switch 2 */
                                    OSReport("Particle:setBlendMode:Unknown mode\n");
                                    break;
                                }
                            }
                            temp_r4 = var_r25->alphaCount;
                            if (temp_r4 != 0) {
                                temp_r5 = var_r25->alpha1Target;
                                temp_r7 = (s32) (var_r25->alphaRemain << 0x10) / (s32) temp_r4;
                                temp_r6 = var_r25->alpha2Target;
                                var_r4 = (u8) ((s32) ((temp_r5 << 0x10) + (temp_r7 * (var_r25->alpha1 - temp_r5))) >> 0x10);
                                var_r7 = (u8) ((s32) ((temp_r6 << 0x10) + (temp_r7 * (var_r25->alpha2 - temp_r6))) >> 0x10);
                            } else {
                                var_r4 = var_r25->alpha1;
                                var_r7 = var_r25->alpha2;
                            }
                            temp_r6_2 = var_r25->alphaMode;
                            if (((*(s32*)(stack.bytes+0xF0)) != (s32) temp_r6_2) || ((*(u8*)(stack.bytes+0xED)) != var_r4) || ((*(u8*)(stack.bytes+0xEC)) != var_r7)) {
                                (*(s32*)(stack.bytes+0xF0)) = (s32) temp_r6_2;
                                (*(u8*)(stack.bytes+0xED)) = var_r4;
                                (*(u8*)(stack.bytes+0xEC)) = var_r7;
                                GXSetAlphaCompare((temp_r6_2 >> 3U) & 7, var_r4, (temp_r6_2 >> 6U) & 3, temp_r6_2 & 7, var_r7);
                            }
                            psSetupTev(var_r25);
                            temp_r3_3 = var_r25->kind & 0x80100000;
                            if (temp_r3_3 != (u32) prevChanCtrl) {
                                prevChanCtrl = (s32) temp_r3_3;
                                GXSetNumChans(1U);
                                if ((s32) prevChanCtrl != 0x80100000) {
                                    if ((s32) prevChanCtrl < 0x80100000) {
                                        if ((s32) prevChanCtrl < 0x80000001) {
                                            var_r17 = GX_AF_NONE;
                                            if (HSD_LObjGetLightMaskAttnFunc() != 0) {
                                                var_r17 = GX_AF_SPOT;
                                            }
                                            GXSetChanCtrl(GX_COLOR0, 1U, GX_SRC_REG, GX_SRC_REG, HSD_LObjGetLightMaskDiffuse(), GX_DF_NONE, var_r17);
                                            GXSetChanCtrl(GX_ALPHA0, 0U, GX_SRC_REG, GX_SRC_REG, 0U, GX_DF_NONE, GX_AF_NONE);
                                        } else {
                                            goto block_57;
                                        }
                                    } else if ((s32) prevChanCtrl != 0x100000) {
block_57:
                                        GXSetChanCtrl(GX_COLOR0A0, 0U, GX_SRC_REG, GX_SRC_REG, 0U, GX_DF_NONE, GX_AF_NONE);
                                    } else {
                                        GXSetChanCtrl(GX_COLOR0A0, 0U, GX_SRC_VTX, GX_SRC_VTX, 0U, GX_DF_NONE, GX_AF_NONE);
                                    }
                                } else {
                                    var_r17_2 = GX_AF_NONE;
                                    if (HSD_LObjGetLightMaskAttnFunc() != 0) {
                                        var_r17_2 = GX_AF_SPOT;
                                    }
                                    GXSetChanCtrl(GX_COLOR0, 1U, GX_SRC_REG, GX_SRC_REG, HSD_LObjGetLightMaskDiffuse(), GX_DF_NONE, var_r17_2);
                                    GXSetChanCtrl(GX_ALPHA0, 0U, GX_SRC_VTX, GX_SRC_VTX, 0U, GX_DF_NONE, GX_AF_NONE);
                                }
                            }
                            setupChanReg(var_r25);
                            setupTevReg(var_r25);
                            temp_r4_2 = var_r25->kind;
                            temp_r3_4 = temp_r4_2 & 0x10000008;
                            if (temp_r3_4 != (*(u32*)(stack.bytes+0xF4))) {
                                (*(u32*)(stack.bytes+0xF4)) = temp_r3_4;
                                if (temp_r3_4 & 8) {
                                    GXSetZMode(((temp_r4_2 >> 0x1CU) & 1) ^ 1, GX_LEQUAL, 1U);
                                } else {
                                    GXSetZMode(((temp_r4_2 >> 0x1CU) & 1) ^ 1, GX_LEQUAL, 0U);
                                }
                            }
                            temp_r3_5 = var_r25->kind;
                            if ((temp_r3_5 ^ var_r16) & 0x01000000) {
                                if (temp_r3_5 & 0x01000000) {
                                    HSD_FogSet(particleFog);
                                } else {
                                    HSD_FogSet(NULL);
                                }
                            }
                            temp_r3_6 = (u32**)psFormGroupArray[var_r25->bank];
                            if ((temp_r3_6 != NULL) && (temp_r4_3 = temp_r3_6[var_r25->texGroup], temp_r4_3 != NULL) && ((u8*)temp_r4_3 + 4 != NULL)) {
                                var_r22 = (u32*)temp_r4_3[var_r25->pose + 1];
                            } else {
                                var_r22 = NULL;
                            }
                            temp_r3_7 = var_r25->kind;
                            if (temp_r3_7 & 0x400) {
                                if (temp_r3_7 & 0x20) {
                                    var_f1 = 2.0f;
                                    var_r17_3 = GX_MIRROR;
                                } else {
                                    var_f1 = 1.0f;
                                    var_r17_3 = GX_CLAMP;
                                }
                                if (temp_r3_7 & 0x40) {
                                    var_f2 = 2.0f;
                                    var_r16_2 = GX_MIRROR;
                                } else {
                                    var_f2 = 1.0f;
                                    var_r16_2 = GX_CLAMP;
                                }
                                temp_r0 = temp_r3_7 & 0x60;
                                if (temp_r0 != var_r14) {
                                    var_r14 = temp_r0;
                                    var_r24 = NULL;
                                    PSMTXScale((f32 (*)[4]) &((f32*)(stack.bytes+0x80))[0], var_f1, var_f2, 1.0f);
                                    if (var_r25->kind & 0x40) {
                                        (*(f32*)(stack.bytes+0x9C)) = 1.0f;
                                    }
                                    GXLoadTexMtxImm((f32 (*)[4]) &((f32*)(stack.bytes+0x80))[0], 0x1EU, GX_MTX2x4);
                                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x1EU, 0U, 0x7DU);
                                }
                                temp_r3_8 = psTexGroupArray[var_r25->bank][var_r25->texGroup];
                                if (temp_r3_8 != NULL) {
                                    var_r21 = temp_r3_8->format;
                                    var_r4_2 = temp_r3_8->textures;
                                    var_r20 = temp_r3_8->width;
                                    var_r19 = temp_r3_8->height;
                                } else {
                                    var_r21 = 0;
                                    var_r19 = 0;
                                    var_r20 = 0;
                                    var_r4_2 = NULL;
                                }
                                if (var_r4_2 != NULL) {
                                    var_r18 = var_r4_2[var_r25->pose];
                                } else {
                                    var_r18 = NULL;
                                }
                                if ((((s32) var_r21 == 8) || ((s32) var_r21 == 9)) && (var_r4_2 != NULL)) {
                                    temp_r4_4 = &var_r4_2[temp_r3_8->count];
                                    if (temp_r4_4 != NULL) {
                                        temp_r0_2 = var_r25->palette;
                                        if (temp_r0_2 != 0xFF) {
                                            var_r4_3 = temp_r4_4[temp_r0_2 & 0xFF];
                                        } else if (!(var_r25->kind & 0x10)) {
                                            var_r4_3 = temp_r4_4[var_r25->pose];
                                        } else {
                                            var_r4_3 = *temp_r4_4;
                                        }
                                        if (var_r4_3 != NULL) {
                                            (*(u32*)(stack.bytes+0x58)) = 0;
                                            var_r0 = 0x100;
                                            (*(u32*)(stack.bytes+0x54)) = temp_r3_8->paletteFormat;
                                            if ((s32) var_r21 == 8) {
                                                var_r0 = 0x10;
                                            }
                                            (*(u16*)(stack.bytes+0x5C)) = var_r0;
                                            GXInitTlutObj(&(*(GXTlutObj*)(stack.bytes+0x44)), var_r4_3, (enum _GXTlutFmt) (*(u32*)(stack.bytes+0x54)), var_r0);
                                            GXLoadTlut(&(*(GXTlutObj*)(stack.bytes+0x44)), (*(u32*)(stack.bytes+0x58)));
                                        }
                                        var_r24 = NULL;
                                    }
                                }
                                if ((var_r24 != var_r18) && (var_r18 != NULL)) {
                                    var_r24 = var_r18;
                                    if ((s32) var_r21 < 0xA) {
                                        if ((s32) var_r21 != 7) {
                                            if ((s32) var_r21 < 7) {
                                                if ((s32) var_r21 < 0) {
                                                    goto block_113;
                                                }
                                                goto block_112;
                                            }
                                            (*(s32*)(stack.bytes+0x8)) = 0;
                                            GXInitTexObjCI(&(*(GXTexObj*)(stack.bytes+0x60)), var_r18, (u16) var_r20, (u16) var_r19, (enum _GXCITexFmt) var_r21, var_r17_3, var_r16_2, 0U, 0);
                                        } else {
                                            goto block_113;
                                        }
                                    } else if ((s32) var_r21 != 0xE) {
block_113:
                                        __assert("psdisp.c", 0x7AD, "0");
                                    } else {
block_112:
                                        GXInitTexObj(&(*(GXTexObj*)(stack.bytes+0x60)), var_r18, (u16) var_r20, (u16) var_r19, (enum _GXTexFmt) var_r21, var_r17_3, var_r16_2, 0U);
                                    }
                                    temp_r0_3 = var_r25->kind;
                                    var_r23 = temp_r0_3 & 0x200;
                                    GXInitTexObjLOD(&(*(GXTexObj*)(stack.bytes+0x60)), var_r23 == 0, ((temp_r0_3 >> 9U) & 1) ^ 1, 0.0f, 0.0f, 0.0f, 0U, 0U, GX_ANISO_1);
                                    GXLoadTexObj(&(*(GXTexObj*)(stack.bytes+0x60)), GX_TEXMAP0);
                                }
                                temp_r3_9 = var_r25->kind & 0x200;
                                if (var_r23 != temp_r3_9) {
                                    temp_r4_5 = temp_r3_9 == 0;
                                    var_r23 = temp_r3_9;
                                    GXInitTexObjLOD(&(*(GXTexObj*)(stack.bytes+0x60)), temp_r4_5, temp_r4_5, 0.0f, 0.0f, 0.0f, 0U, 0U, GX_ANISO_1);
                                    GXLoadTexObj(&(*(GXTexObj*)(stack.bytes+0x60)), GX_TEXMAP0);
                                }
                            }
                            temp_r3_10 = var_r25->kind;
                            if (temp_r3_10 & 0x40000000) {
                                if ((PSAppSRT *) var_r25->appsrt != NULL) {
                                    psDispSubAPPSRTPoint(var_r25);
                                } else if (temp_r3_10 & 0x100000) {
                                    var_r25 = psDispSubPointTrail(var_r25);
                                } else {
                                    if ((s32) currentMtx != 0) {
                                        currentMtx = 0;
                                        GXSetCurrentMtx(0U);
                                    }
                                    temp_f1_2 = var_r25->size;
                                    if (temp_f1_2 > 42.5) {
                                        var_f0 = 255.0f;
                                    } else {
                                        var_f0 = 6.0f * temp_f1_2;
                                    }
                                    temp_r3_11 = (s32) var_f0;
                                    if ((s32) prevPointSize != (s32) (u8) temp_r3_11) {
                                        prevPointSize = (s32) (u8) temp_r3_11;
                                        GXSetPointSize((u8) temp_r3_11, GX_TO_ONE);
                                    }
                                    if (var_r25->kind & 0x400) {
                                        GXClearVtxDesc();
                                        GXInvalidateVtxCache();
                                        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                                        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
                                        GXBegin(GX_POINTS, GX_VTXFMT0, 1U);
                                    } else {
                                        GXClearVtxDesc();
                                        GXInvalidateVtxCache();
                                        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                                        GXBegin(GX_POINTS, GX_VTXFMT1, 1U);
                                    }
                                    (*(f32*)(stack.bytes+0x24)) = var_r25->position.z;

                                    (*(f32*)(stack.bytes+0x20)) = var_r25->position.y;
                                    (*(f32*)(stack.bytes+0x1C)) = var_r25->position.x;
                                    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x1C)));
                                    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x20)));
                                    *(volatile s16 *)0xCC008000 = PS_FIXED6((*(f32*)(stack.bytes+0x24)));
                                    if (var_r25->kind & 0x400) {
                                        *(volatile u8 *)0xCC008000 = 1;
                                    }
                                }
                            } else if ((PSAppSRT *) var_r25->appsrt != NULL) {
                                psDispSubAppSRT(var_r25, var_r22);
                            } else {
                                psDispSub(var_r25, var_r22);
                            }
                        }
                        var_r16 = var_r25->kind;
                        var_r25 = var_r25->next;
                        goto loop_138;
                    }
                }
                break;
            case 2:                                 /* switch 1 */
                var_r25 = (*(PSParticle **)(stack.bytes+0x3C));
                goto block_8;
            }
        }
        temp_r3 = (*(s32*)(stack.bytes+0xF8)) + 1;
        (*(s32*)(stack.bytes+0xF8)) = temp_r3;
    } while (temp_r3 < 0x10);
    if ((*(s32*)(stack.bytes+0xE8)) == 0) {
        HSD_StateInvalidate(-1U);
    }
}

void psDispSetProjection(f32 *arg0) {
    memcpy(prj, arg0, 0x1CU);
}

void psDispParticles(u32 arg0, s32 arg1, u32 arg2) {
    _psDispParticlesSub(arg0, arg1, NULL, arg2);
}
