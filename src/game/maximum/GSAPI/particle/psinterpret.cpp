#include "game/maximum/GSAPI/particle/psinterpret.h"
#define NULL ((void*)0)
#define fabs __fabs
static PSByteFloat BYTEF32;

static u8 *getFloat(u8 *arg0,f32 *arg1);
static u8 *getTime(u8 *arg0, u16 *arg1);
static void modifyDirGenBase(PSParticle *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
static void modifyDir(PSParticle *arg0, f32 farg0);
static void setVelToJObj(PSParticle *arg0, PSJObj *arg1);
static s32 applyForceJObj(PSParticle *arg0, PSJObj *arg1, f32 farg0, f32 farg1);
static void psApplyVelocityLocalRotation(PSParticle *arg0);
static void psApplyOffsetLocalRotation(PSParticle *arg0, PSVec *arg1);
static void psCopyGeneratorData(PSGenerator *arg0, PSGenerator *arg1);
__declspec(weak) PSParticle *_psListGetNext(PSParticle *arg0);
static void HSD_MTXSRT(f32 (*arg0)[4], PSVec *arg1, PSVec *arg2, PSVec *arg3, s32 arg4);
__declspec(weak) s32 U8ClampAdd(u8 arg0, f32 farg0);
static void HSD_JObjSetupMatrix(PSJObj *arg0);
static void HSD_JObjAddTx(PSJObj *arg0, f32 farg0);
static void HSD_JObjAddTy(PSJObj *arg0, f32 farg0);
static void HSD_JObjAddTz(PSJObj *arg0, f32 farg0);
PSParticle *psInterpretParticle0(PSParticle *arg0, PSParticle *arg1);
void psInterpretParticles(u32 arg0);

static u8 *getFloat(u8 *arg0,f32 *arg1) {
    BYTEF32.bytes[0] = *arg0++;
    BYTEF32.bytes[1] = *arg0++;
    BYTEF32.bytes[2] = *arg0++;
    BYTEF32.bytes[3] = *arg0++;
    *arg1 = BYTEF32.value;
    return arg0;
}

static u8 *getTime(u8 *arg0, u16 *arg1) {
    *arg1 = *arg0++;
    if (*arg1 & 0x80) { *arg1 = ((*arg1 << 8) & 0x7F00) + *arg0++; }
    return arg0;
}

static void modifyDirGenBase(PSParticle *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 sp8;
    PSGenerator *temp_r4;
    f32 temp_f0;
    f32 temp_f1_4;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f25_2;
    f32 temp_f25_3;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f30;
    f32 temp_f3;
    f32 temp_f6;
    f32 var_f24;
    f32 var_f24_2;
    f32 var_f31;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    s32 temp_r3;
    s32 var_r0;

    temp_r4 = arg0->generator;
    temp_f28 = temp_r4->velocity.z + farg3;
    temp_f25 = temp_r4->velocity.x + farg1;
    temp_f27 = temp_r4->velocity.y + farg2;
    if (fabs(temp_f28) < __float_min[0]) {

        if (temp_f27 >= 0.0f) {
            var_f24 = 1.5707964f;
        } else {
            var_f24 = -1.5707964f;
        }
    } else {
        var_f24 = (f32) atan2((f64) temp_f27, (f64) temp_f28);
    }
    temp_f30 = (f32) sin((f64) var_f24);
    temp_f29 = (f32) cos((f64) var_f24);
    temp_f2 = (temp_f27 * temp_f30) + (temp_f28 * temp_f29);
    if (fabs(temp_f2) < __float_min[0]) {

        if (temp_f25 >= 0.0f) {
            var_f24_2 = 1.5707964f;
        } else {
            var_f24_2 = -1.5707964f;
        }
    } else {
        var_f24_2 = (f32) atan2((f64) temp_f25, (f64) temp_f2);
    }
    temp_f28_2 = (f32) sin((f64) var_f24_2);
    temp_f2_2 = arg0->velocity.x;
    temp_f27_2 = (f32) cos((f64) var_f24_2);
    temp_f0 = arg0->velocity.y;
    temp_f3 = arg0->velocity.z;
    var_f31 = (temp_f3 * temp_f3) + ((temp_f2_2 * temp_f2_2) + (temp_f0 * temp_f0));
    if (var_f31 > 0.0f) {
        temp_f1 = __frsqrte(var_f31);
        temp_f1_2 = 0.5 * temp_f1 * -(((f64) var_f31 * (temp_f1 * temp_f1)) - 3.0);
        temp_f1_3 = 0.5 * temp_f1_2 * -(((f64) var_f31 * (temp_f1_2 * temp_f1_2)) - 3.0);
        var_f31 = (f32) ((f64) var_f31 * (0.5 * temp_f1_3 * -(((f64) var_f31 * (temp_f1_3 * temp_f1_3)) - 3.0)));
    } else if (var_f31 < 0.0) {
        var_f31 = __float_nan[0];
    } else {
        sp8 = var_f31;
        temp_r3 = *(s32*)&sp8 & 0x7F800000;
        switch (temp_r3) {                          /* irregular */
        case 0x7F800000:
            if (*(s32*)&sp8 & 0x7FFFFF) {
                var_r0 = 1;
            } else {
                var_r0 = 2;
            }
            break;
        case 0x0:
            if (*(s32*)&sp8 & 0x7FFFFF) {
                var_r0 = 5;
            } else {
                var_r0 = 3;
            }
            break;
        default:
            var_r0 = 4;
            break;
        }
        if (var_r0 == 1) {
            var_f31 = __float_nan[0];
        }
    }
    temp_f25_2 = (f32) (2.0 * (3.141592653589793 * HSD_Randf()));
    temp_f24 = var_f31 * (f32) sin((f64) farg0);
    temp_f25_3 = temp_f24 * (f32) cos((f64) temp_f25_2);
    temp_f26 = temp_f24 * (f32) sin((f64) temp_f25_2);
    temp_f1_4 = -temp_f25_3;
    temp_f6 = var_f31 * (f32) cos((f64) farg0);
    arg0->velocity.x = (temp_f25_3 * temp_f27_2) + (temp_f6 * temp_f28_2);
    arg0->velocity.y = (temp_f27_2 * (temp_f6 * temp_f30)) + ((temp_f28_2 * (temp_f1_4 * temp_f30)) + (temp_f26 * temp_f29));
    arg0->velocity.z = (temp_f27_2 * (temp_f6 * temp_f29)) + ((temp_f28_2 * (temp_f1_4 * temp_f29)) - (temp_f26 * temp_f30));
}

static void modifyDir(PSParticle *arg0, f32 farg0) {
    f32 sp8;
    f32 temp_f1_4;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f26_3;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f6;
    f32 var_f24;
    f32 var_f24_2;
    f32 var_f27;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    s32 temp_r3;
    s32 var_r0;

    temp_f26 = arg0->velocity.z;
    temp_f27 = arg0->velocity.x;
    temp_f28 = arg0->velocity.y;
    if (fabs(temp_f26) < __float_min[0]) {

        if (temp_f28 >= 0.0f) {
            var_f24 = 1.5707964f;
        } else {
            var_f24 = -1.5707964f;
        }
    } else {
        var_f24 = (f32) atan2((f64) temp_f28, (f64) temp_f26);
    }
    temp_f31 = (f32) sin((f64) var_f24);
    temp_f30 = (f32) cos((f64) var_f24);
    temp_f2 = (temp_f28 * temp_f31) + (temp_f26 * temp_f30);
    if (fabs(temp_f2) < __float_min[0]) {

        if (temp_f27 >= 0.0f) {
            var_f24_2 = 1.5707964f;
        } else {
            var_f24_2 = -1.5707964f;
        }
    } else {
        var_f24_2 = (f32) atan2((f64) temp_f27, (f64) temp_f2);
    }
    temp_f29 = (f32) sin((f64) var_f24_2);
    temp_f28_2 = (f32) cos((f64) var_f24_2);
    var_f27 = (temp_f26 * temp_f26) + ((temp_f27 * temp_f27) + (temp_f28 * temp_f28));
    if (var_f27 > 0.0f) {
        temp_f1 = __frsqrte(var_f27);
        temp_f1_2 = 0.5 * temp_f1 * -(((f64) var_f27 * (temp_f1 * temp_f1)) - 3.0);
        temp_f1_3 = 0.5 * temp_f1_2 * -(((f64) var_f27 * (temp_f1_2 * temp_f1_2)) - 3.0);
        var_f27 = (f32) ((f64) var_f27 * (0.5 * temp_f1_3 * -(((f64) var_f27 * (temp_f1_3 * temp_f1_3)) - 3.0)));
    } else if (var_f27 < 0.0) {
        var_f27 = __float_nan[0];
    } else {
        sp8 = var_f27;
        temp_r3 = *(s32*)&sp8 & 0x7F800000;
        switch (temp_r3) {                          /* irregular */
        case 0x7F800000:
            if (*(s32*)&sp8 & 0x7FFFFF) {
                var_r0 = 1;
            } else {
                var_r0 = 2;
            }
            break;
        case 0x0:
            if (*(s32*)&sp8 & 0x7FFFFF) {
                var_r0 = 5;
            } else {
                var_r0 = 3;
            }
            break;
        default:
            var_r0 = 4;
            break;
        }
        if (var_r0 == 1) {
            var_f27 = __float_nan[0];
        }
    }
    temp_f26_2 = (f32) (2.0 * (3.141592653589793 * HSD_Randf()));
    temp_f24 = var_f27 * (f32) sin((f64) farg0);
    temp_f26_3 = temp_f24 * (f32) cos((f64) temp_f26_2);
    temp_f25 = temp_f24 * (f32) sin((f64) temp_f26_2);
    temp_f1_4 = -temp_f26_3;
    temp_f6 = var_f27 * (f32) cos((f64) farg0);
    arg0->velocity.x = (temp_f26_3 * temp_f28_2) + (temp_f6 * temp_f29);
    arg0->velocity.y = (temp_f28_2 * (temp_f6 * temp_f31)) + ((temp_f29 * (temp_f1_4 * temp_f31)) + (temp_f25 * temp_f30));
    arg0->velocity.z = (temp_f28_2 * (temp_f6 * temp_f30)) + ((temp_f29 * (temp_f1_4 * temp_f30)) - (temp_f25 * temp_f31));
}

static void setVelToJObj(PSParticle *arg0, PSJObj *arg1) {
    f32 spC;
    f32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f3;
    f32 temp_f8;
    f32 var_f0;
    f32 var_f4;
    f64 temp_f5;
    f64 temp_f5_2;
    f64 temp_f5_3;
    f64 temp_f5_4;
    f64 temp_f5_5;
    f64 temp_f5_6;
    s32 temp_cr0_eq;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r3;
    u32 temp_r4;

    if (arg1 != NULL) {
        if (arg1 != NULL) {
            if (arg1 == NULL) {
                __assert("jobj.h", 0x25D, "jobj");
            }
            temp_r4 = arg1->flags;
            var_r3 = 0;
            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 != 0) {
                HSD_JObjSetupMatrixSub(arg1);
            }
        }
        temp_f1 = arg0->velocity.x;
        temp_f0 = arg0->velocity.y;
        temp_f2 = arg0->velocity.z;
        temp_f1_2 = arg1->matrix[0][3] - arg0->position.x;
        var_f0 = (temp_f2 * temp_f2) + ((temp_f1 * temp_f1) + (temp_f0 * temp_f0));
        temp_f2_2 = arg1->matrix[1][3] - arg0->position.y;
        temp_f3 = arg1->matrix[2][3] - arg0->position.z;
        if (var_f0 > 0.0f) {
            temp_f5 = __frsqrte(var_f0);
            temp_f5_2 = 0.5 * temp_f5 * -(((f64) var_f0 * (temp_f5 * temp_f5)) - 3.0);
            temp_f5_3 = 0.5 * temp_f5_2 * -(((f64) var_f0 * (temp_f5_2 * temp_f5_2)) - 3.0);
            var_f0 = (f32) ((f64) var_f0 * (0.5 * temp_f5_3 * -(((f64) var_f0 * (temp_f5_3 * temp_f5_3)) - 3.0)));
        } else if (var_f0 < 0.0) {
            var_f0 = __float_nan[0];
        } else {
            spC = var_f0;
            temp_r3 = *(s32*)&spC & 0x7F800000;
            switch (temp_r3) {                      /* switch 1; irregular */
            case 0x7F800000:                        /* switch 1 */
                if (*(s32*)&spC & 0x7FFFFF) {
                    var_r0 = 1;
                } else {
                    var_r0 = 2;
                }
                break;
            case 0x0:                               /* switch 1 */
                if (*(s32*)&spC & 0x7FFFFF) {
                    var_r0 = 5;
                } else {
                    var_r0 = 3;
                }
                break;
            default:                                /* switch 1 */
                var_r0 = 4;
                break;
            }
            if (var_r0 == 1) {
                var_f0 = __float_nan[0];
            }
        }
        temp_f8 = (temp_f3 * temp_f3) + ((temp_f1_2 * temp_f1_2) + (temp_f2_2 * temp_f2_2));
        if (temp_f8 != 0.0f) {
            if (temp_f8 > 0.0f) {
                temp_f5_4 = __frsqrte(temp_f8);
                temp_f5_5 = 0.5 * temp_f5_4 * -(((f64) temp_f8 * (temp_f5_4 * temp_f5_4)) - 3.0);
                temp_f5_6 = 0.5 * temp_f5_5 * -(((f64) temp_f8 * (temp_f5_5 * temp_f5_5)) - 3.0);
                var_f4 = (f32) ((f64) temp_f8 * (0.5 * temp_f5_6 * -(((f64) temp_f8 * (temp_f5_6 * temp_f5_6)) - 3.0)));
            } else if (temp_f8 < 0.0) {
                var_f4 = __float_nan[0];
            } else {
                sp8 = temp_f8;
                temp_r3_2 = *(s32*)&sp8 & 0x7F800000;
                switch (temp_r3_2) {                /* switch 2; irregular */
                case 0x7F800000:                    /* switch 2 */
                    if (*(s32*)&sp8 & 0x7FFFFF) {
                        var_r0_2 = 1;
                    } else {
                        var_r0_2 = 2;
                    }
                    break;
                case 0x0:                           /* switch 2 */
                    if (*(s32*)&sp8 & 0x7FFFFF) {
                        var_r0_2 = 5;
                    } else {
                        var_r0_2 = 3;
                    }
                    break;
                default:                            /* switch 2 */
                    var_r0_2 = 4;
                    break;
                }
                if (var_r0_2 == 1) {
                    var_f4 = __float_nan[0];
                } else {
                    var_f4 = temp_f8;
                }
            }
            temp_f0_2 = var_f0 / var_f4;
            arg0->velocity.x = temp_f1_2 * temp_f0_2;
            arg0->velocity.y = temp_f2_2 * temp_f0_2;
            arg0->velocity.z = temp_f3 * temp_f0_2;
        }
    }
}

static s32 applyForceJObj(PSParticle *arg0, PSJObj *arg1, f32 farg0, f32 farg1) {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f5;
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;

    if ((arg1 == NULL) || (farg1 < 0.0f)) {
        return 0;
    }
    if (arg1 != NULL) {
        if (arg1 == NULL) {
            __assert("jobj.h", 0x25D, "jobj");
        }
        temp_r4 = arg1->flags;
        var_r3 = 0;
        if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
            var_r3 = 1;
        }
        if (var_r3 != 0) {
            HSD_JObjSetupMatrixSub(arg1);
        }
    }
    temp_f4 = arg1->matrix[0][3] - arg0->position.x;
    temp_f5 = arg1->matrix[1][3] - arg0->position.y;
    temp_f2 = arg1->matrix[2][3] - arg0->position.z;
    temp_f1 = (temp_f2 * temp_f2) + ((temp_f4 * temp_f4) + (temp_f5 * temp_f5));

    if (temp_f1 <= (farg1 * farg1)) {
        return 1;
    }
    if (temp_f1 == 0.0f) {
        return 0;
    }
    temp_f1_2 = farg0 / temp_f1;
    arg0->velocity.x += temp_f1_2 * temp_f4;
    arg0->velocity.y += temp_f1_2 * temp_f5;
    arg0->velocity.z += temp_f1_2 * temp_f2;
    return 0;
}

static void psApplyVelocityLocalRotation(PSParticle *arg0) {
    PSVec vec8;
    f32 sp74[12], sp44[12], sp14[12];
    PSGenerator *temp_r5;

    temp_r5 = arg0->generator;
    if (temp_r5 != NULL) {
        if (!(temp_r5->transformFlags & 4)) {
            return;
        }
        vec8.x = arg0->velocity.x;
        vec8.y = arg0->velocity.y;
        vec8.z = arg0->velocity.z;
        PSMTXRotRad((f32 (*)[4]) &sp74[0], 0x58, temp_r5->rotation.x);
        PSMTXRotRad((f32 (*)[4]) &sp44[0], 0x59, arg0->generator->rotation.y);
        PSMTXRotRad((f32 (*)[4]) &sp14[0], 0x5A, arg0->generator->rotation.z);
        PSMTXConcat((f32 (*)[4]) &sp44[0], (f32 (*)[4]) &sp74[0], (f32 (*)[4]) &sp74[0]);
        PSMTXConcat((f32 (*)[4]) &sp14[0], (f32 (*)[4]) &sp74[0], (f32 (*)[4]) &sp74[0]);
        PSMTXMultVec((f32 (*)[4]) &sp74[0], (PSVec *) &vec8.x, (PSVec *) &vec8.x);
        arg0->velocity.x = vec8.x;
        arg0->velocity.y = vec8.y;
        arg0->velocity.z = vec8.z;
    }
}

static void psApplyOffsetLocalRotation(PSParticle *arg0, PSVec *arg1) {
    f32 sp98[12], sp68[12], sp38[12], sp8[12];
    PSGenerator *temp_r4;
    u16 temp_r3;

    temp_r4 = arg0->generator;
    if (temp_r4 != NULL) {
        temp_r3 = temp_r4->transformFlags;
        if (!(temp_r3 & 8)) {
            return;
        }
        if (temp_r3 & 0x10) {
            PSMTXIdentity((f32 (*)[4]) &sp8[0]);
        } else {
            PSMTXScale((f32 (*)[4]) &sp8[0], temp_r4->scale.x, temp_r4->scale.y, temp_r4->scale.z);
        }
        PSMTXRotRad((f32 (*)[4]) &sp98[0], 0x58, arg0->generator->rotation.x);
        PSMTXRotRad((f32 (*)[4]) &sp68[0], 0x59, arg0->generator->rotation.y);
        PSMTXRotRad((f32 (*)[4]) &sp38[0], 0x5A, arg0->generator->rotation.z);
        PSMTXConcat((f32 (*)[4]) &sp68[0], (f32 (*)[4]) &sp98[0], (f32 (*)[4]) &sp98[0]);
        PSMTXConcat((f32 (*)[4]) &sp38[0], (f32 (*)[4]) &sp98[0], (f32 (*)[4]) &sp98[0]);
        PSMTXConcat((f32 (*)[4]) &sp8[0], (f32 (*)[4]) &sp98[0], (f32 (*)[4]) &sp98[0]);
        PSMTXMultVec((f32 (*)[4]) &sp98[0], arg1, arg1);
    }
}

static void psCopyGeneratorData(PSGenerator *arg0, PSGenerator *arg1) {
    if (arg1 != NULL) {
        if (arg0 == NULL) {
            return;
        }
        if (arg1->kind & 0x20000000) {
            arg0->kind |= 0x20000000;
        }
        arg0->rotation.x = arg1->rotation.x;
        arg0->rotation.y = arg1->rotation.y;
        arg0->rotation.z = arg1->rotation.z;
        arg0->scale.x = arg1->scale.x;
        arg0->scale.y = arg1->scale.y;
        arg0->scale.z = arg1->scale.z;
        arg0->transformFlags = arg1->transformFlags;
        arg0->transformFlags &= 0xFFFFFFFD;
        arg0->jobj = arg1->jobj;
        if (arg1->transformFlags & 0x1000) {
            psSetGeneratorAngleRadiusScale(arg0, &arg1->nodeScale, 1U);
            return;
        }
        psSetGeneratorAngleRadiusScale(arg0, &arg1->nodeScale, 0U);
    }
}

__declspec(weak) PSParticle *_psListGetNext(PSParticle *arg0) {
    return arg0->next;
}

static void HSD_MTXSRT(f32 (*arg0)[4], PSVec *arg1, PSVec *arg2, PSVec *arg3, s32 arg4) {
    HSD_MtxSRT(arg0, arg1, arg2, arg3, arg4);
}

__declspec(weak) s32 U8ClampAdd(u8 arg0, f32 farg0) {
    f32 var_f1;

    var_f1 = (f32) arg0 + farg0;
    if (var_f1 < 0.0f) {
        var_f1 = 0.0f;
    }
    if (var_f1 > 255.0f) {
        var_f1 = 255.0f;
    }
    return (s32) var_f1;
}

static void HSD_JObjSetupMatrix(PSJObj *arg0) {
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;

    if (arg0 != NULL) {
        if (arg0 == NULL) {
            __assert("jobj.h", 0x25D, "jobj");
        }
        temp_r4 = arg0->flags;
        var_r3 = 0;
        if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
            var_r3 = 1;
        }
        if (var_r3 == 0) {
            return;
        }
        HSD_JObjSetupMatrixSub(arg0);
    }
}

static void HSD_JObjAddTx(PSJObj *arg0, f32 farg0) {
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;

    if (arg0 == NULL) {
        __assert("jobj.h", 0x455, "jobj");
    }
    (*(f32*)((u8*)arg0+0x38)) += farg0;
    if (!(arg0->flags & 0x02000000)) {
            if (arg0 != NULL) {
            if (arg0 == NULL) {
                __assert("jobj.h", 0x25D, "jobj");
            }
            temp_r4 = arg0->flags;
            var_r3 = 0;
            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(arg0);
            }
        }
    }
}

static void HSD_JObjAddTy(PSJObj *arg0, f32 farg0) {
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;

    if (arg0 == NULL) {
        __assert("jobj.h", 0x460, "jobj");
    }
    (*(f32*)((u8*)arg0+0x3C)) += farg0;
    if (!(arg0->flags & 0x02000000)) {
            if (arg0 != NULL) {
            if (arg0 == NULL) {
                __assert("jobj.h", 0x25D, "jobj");
            }
            temp_r4 = arg0->flags;
            var_r3 = 0;
            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(arg0);
            }
        }
    }
}

static void HSD_JObjAddTz(PSJObj *arg0, f32 farg0) {
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;

    if (arg0 == NULL) {
        __assert("jobj.h", 0x46B, "jobj");
    }
    (*(f32*)((u8*)arg0+0x40)) += farg0;
    if (!(arg0->flags & 0x02000000)) {
            if (arg0 != NULL) {
            if (arg0 == NULL) {
                __assert("jobj.h", 0x25D, "jobj");
            }
            temp_r4 = arg0->flags;
            var_r3 = 0;
            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(arg0);
            }
        }
    }
}

PSParticle *psInterpretParticle0(PSParticle *arg0, PSParticle *arg1) {
    PSVec vec18;
    PSVec vec24;
    PSVec vec30;
    PSVec vec3C;
    PSVec vec48;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    PSAppSRT *temp_r0_5;
    PSAppSRT *temp_r0_6;
    PSAppSRT *temp_r0_7;
    PSAppSRT *temp_r3_18;
    PSAppSRT *temp_r3_19;
    PSAppSRT *temp_r3_22;
    PSAppSRT *temp_r3_23;
    PSAppSRT *temp_r3_27;
    PSAppSRT *temp_r3_28;
    PSAppSRT *temp_r3_33;
    PSAppSRT *temp_r4_10;
    PSAppSRT *temp_r4_13;
    PSAppSRT *temp_r4_14;
    PSAppSRT *temp_r4_19;
    PSAppSRT *temp_r4_21;
    PSAppSRT *temp_r4_4;
    PSAppSRT *temp_r4_5;
    PSAppSRT *temp_r4_6;
    PSAppSRT *temp_r4_7;
    PSAppSRT *temp_r4_9;
    PSAppSRT *temp_r5_2;
    PSAppSRT *temp_r5_4;
    PSAppSRT *temp_r5_5;
    PSAppSRT *temp_r6_2;
    PSGenerator *temp_r26_11;
    PSGenerator *temp_r3_11;
    PSGenerator *temp_r3_14;
    PSGenerator *temp_r3_16;
    PSGenerator *temp_r3_17;
    PSGenerator *temp_r3_20;
    PSGenerator *temp_r3_21;
    PSGenerator *temp_r3_25;
    PSGenerator *temp_r3_26;
    PSGenerator *temp_r3_29;
    PSGenerator *temp_r3_32;
    PSGenerator *temp_r3_36;
    PSGenerator *temp_r3_39;
    PSGenerator *temp_r3_7;
    PSGenerator *temp_r3_8;
    PSGenerator *temp_r3_9;
    PSGenerator *temp_r4_12;
    PSGenerator *temp_r4_17;
    PSGenerator *temp_r4_18;
    PSGenerator *temp_r4_20;
    PSGenerator *temp_r4_25;
    PSGenerator *temp_r4_2;
    PSGenerator *temp_r4_39;
    PSGenerator *temp_r4_3;
    PSGenerator *temp_r5_6;
    PSJObj *temp_r3_56;
    PSJObj *temp_r3_57;
    PSJObj *temp_r3_58;
    PSJObj *temp_r3_59;
    PSJObj *temp_r3_60;
    PSParticle *temp_r3_10;
    PSParticle *temp_r3_13;
    PSParticle *temp_r3_31;
    PSParticle *temp_r3_35;
    PSParticle *temp_r3_38;
    PSParticle *var_r26;
    PSTex *temp_r4;
    PSTex *temp_r4_24;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f1_10;
    f32 temp_f1_12;
    f32 temp_f1_13;
    f32 temp_f1_14;
    f32 temp_f1_15;
    f32 temp_f1_16;
    f32 temp_f1_17;
    f32 temp_f1_18;
    f32 temp_f1_19;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f1_9;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f3_4;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f8;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f27;
    f64 temp_f1_11;
    s32 temp_r0_13;
    s32 temp_r0_15;
    s32 temp_r0_18;
    s32 temp_r0_24;
    s32 temp_r0_2;
    s32 temp_r0_30;
    s32 temp_r0_31;
    s32 temp_r0_32;
    s32 temp_r0_33;
    s32 temp_r0_36;
    s32 temp_r0_38;
    s32 temp_r26_2;
    s32 temp_r26_6;
    s32 temp_r26_7;
    s32 temp_r27_3;
    s32 temp_r27_4;
    s32 temp_r27_6;
    s32 temp_r3_45;
    s32 temp_r3_46;
    s32 temp_r3_47;
    s32 temp_r3_48;
    s32 temp_r5_3;
    s32 temp_r6;
    s32 temp_r6_3;
    s32 temp_r6_4;
    s32 temp_r6_5;
    s32 temp_r6_6;
    s32 var_r26_2;
    s32 var_r5;
    s32 var_r6;
    s32 var_r6_2;
    u16 temp_r0_12;
    u16 temp_r0_14;
    u16 temp_r0_16;
    u16 temp_r0_23;
    u16 temp_r0_29;
    u16 temp_r0_41;
    u16 temp_r0_44;
    u16 temp_r0_9;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 temp_r3_3;
    u16 temp_r3_4;
    u16 temp_r3_54;
    u16 temp_r3_5;
    u16 temp_r3_6;
    u16 temp_r4_11;
    u16 temp_r4_15;
    u16 temp_r4_22;
    u16 temp_r4_23;
    u16 temp_r4_27;
    u16 temp_r4_28;
    u16 temp_r4_29;
    u16 temp_r4_30;
    u16 temp_r4_31;
    u16 temp_r4_32;
    u16 temp_r4_33;
    u16 temp_r4_36;
    u16 var_r29;
    u32* temp_r3_12;
    u32* temp_r3_24;
    u32* temp_r3_30;
    u32* temp_r3_37;
    u32 temp_r3_55;
    u32 temp_r4_40;
    u8 *temp_r26_4;
    u8 *temp_r26_5;
    u8 *temp_r3_34;
    u8 *temp_r3_42;
    u8 *temp_r3_43;
    u8 *temp_r3_50;
    u8 *temp_r3_51;
    u8 *temp_r3_52;
    u8 *var_r30;
    u8 temp_r0;
    u8 temp_r0_10;
    u8 temp_r0_11;
    u8 temp_r0_17;
    u8 temp_r0_19;
    u8 temp_r0_20;
    u8 temp_r0_21;
    u8 temp_r0_22;
    u8 temp_r0_25;
    u8 temp_r0_26;
    u8 temp_r0_27;
    u8 temp_r0_28;
    u8 temp_r0_34;
    u8 temp_r0_35;
    u8 temp_r0_37;
    u8 temp_r0_39;
    u8 temp_r0_3;
    u8 temp_r0_40;
    u8 temp_r0_42;
    u8 temp_r0_43;
    u8 temp_r0_45;
    u8 temp_r0_4;
    u8 temp_r0_8;
    u8 temp_r26;
    u8 temp_r26_10;
    u8 temp_r26_3;
    u8 temp_r26_8;
    u8 temp_r26_9;
    u8 temp_r27;
    u8 temp_r27_2;
    u8 temp_r27_5;
    u8 temp_r3_15;
    u8 temp_r3_40;
    u8 temp_r3_41;
    u8 temp_r3_44;
    u8 temp_r3_49;
    u8 temp_r3_53;
    u8 temp_r4_16;
    u8 temp_r4_26;
    u8 temp_r4_34;
    u8 temp_r4_35;
    u8 temp_r4_37;
    u8 temp_r4_38;
    u8 temp_r4_8;
    u8 temp_r5;
    u8 temp_r5_10;
    u8 temp_r5_11;
    u8 temp_r5_12;
    u8 temp_r5_13;
    u8 temp_r5_14;
    u8 temp_r5_15;
    u8 temp_r5_16;
    u8 temp_r5_17;
    u8 temp_r5_18;
    u8 temp_r5_19;
    u8 temp_r5_20;
    u8 temp_r5_21;
    u8 temp_r5_22;
    u8 temp_r5_23;
    u8 temp_r5_24;
    u8 temp_r5_25;
    u8 temp_r5_26;
    u8 temp_r5_27;
    u8 temp_r5_28;
    u8 temp_r5_29;
    u8 temp_r5_30;
    u8 temp_r5_31;
    u8 temp_r5_32;
    u8 temp_r5_33;
    u8 temp_r5_34;
    u8 temp_r5_35;
    u8 temp_r5_36;
    u8 temp_r5_37;
    u8 temp_r5_38;
    u8 temp_r5_39;
    u8 temp_r5_40;
    u8 temp_r5_41;
    u8 temp_r5_42;
    u8 temp_r5_43;
    u8 temp_r5_44;
    u8 temp_r5_7;
    u8 temp_r5_8;
    u8 temp_r5_9;
    u8 var_r0;

    if (arg0->kind & 0x800) {
        return _psListGetNext(arg0);
    }
    temp_r3 = arg0->sizeCount;
    if (temp_r3 != 0) {
        temp_f3 = arg0->size;
        arg0->size = temp_f3 + ((arg0->sizeTarget - temp_f3) / (f32) temp_r3);
        arg0->sizeCount -= 1;
    }
    if ((u16) arg0->primCount != 0) {
        arg0->primRemain -= 1;
        if ((u16) arg0->primRemain == 0) {
            arg0->primCount = 0;
            arg0->primColor[0] = arg0->primTarget[0];
            arg0->primColor[1] = arg0->primTarget[1];
            arg0->primColor[2] = arg0->primTarget[2];
            arg0->primColor[3] = arg0->primTarget[3];
        }
    }
    if ((u16) arg0->envCount != 0) {
        arg0->envRemain -= 1;
        if ((u16) arg0->envRemain == 0) {
            arg0->envCount = 0;
            arg0->envColor[0] = arg0->envTarget[0];
            arg0->envColor[1] = arg0->envTarget[1];
            arg0->envColor[2] = arg0->envTarget[2];
            arg0->envColor[3] = arg0->envTarget[3];
        }
    }
    if ((u16) arg0->matCount != 0) {
        arg0->matRemain -= 1;
        if ((u16) arg0->matRemain == 0) {
            arg0->matCount = 0;
            arg0->matRGB = arg0->matRGBTarget;
            arg0->matAlpha = arg0->matAlphaTarget;
        }
    }
    if ((u16) arg0->ambCount != 0) {
        arg0->ambRemain -= 1;
        if ((u16) arg0->ambRemain == 0) {
            arg0->ambCount = 0;
            arg0->ambRGB = arg0->ambRGBTarget;
            arg0->ambAlpha = arg0->ambAlphaTarget;
        }
    }
    if ((u16) arg0->alphaCount != 0) {
        arg0->alphaRemain -= 1;
        if ((u16) arg0->alphaRemain == 0) {
            arg0->alphaCount = 0;
            arg0->alpha1 = arg0->alpha1Target;
            arg0->alpha2 = arg0->alpha2Target;
        }
    }
    temp_r3_2 = arg0->rotateCount;
    if (temp_r3_2 != 0) {
        if (arg0->trail != 0.0f) {
            arg0->rotate += arg0->rotateTarget;
            temp_f1 = arg0->rotateTarget;

            if (temp_f1 >= 0.0f) {
                arg0->rotateTarget = temp_f1 + arg0->trail;
            } else {
                arg0->rotateTarget = temp_f1 - arg0->trail;
            }
            temp_r3_3 = arg0->rotateCount - 1;
            arg0->rotateCount = temp_r3_3;
            if (temp_r3_3 == 0) {
                arg0->trail = 0.0f;
                arg0->rotateTarget = 0.0f;
            }
        } else {
            temp_f3_2 = arg0->rotate;
            arg0->rotate = temp_f3_2 + ((arg0->rotateTarget - temp_f3_2) / (f32) temp_r3_2);
            arg0->rotateCount -= 1;
        }
    }
    temp_r3_4 = arg0->wait;
    if (temp_r3_4 != 0) {
        temp_r3_5 = temp_r3_4 - 1;
        arg0->wait = temp_r3_5;
        if (temp_r3_5 == 0) {
            var_r30 = &arg0->commands[arg0->commandPtr];
loop_30:
            temp_r26 = *var_r30;
            var_r30 += 1;
            if (temp_r26 < 0x80U) {
                temp_r3_6 = temp_r26 & 0x1F;
                var_r29 = temp_r3_6;
                if (temp_r26 & 0x20) {
                    temp_r0 = var_r30[0x0];
                    var_r30 += 1;
                    var_r29 = ((temp_r3_6 << 8) & 0xFFFF00) + temp_r0;
                }
                temp_r0_2 = temp_r26 & 0xC0;
                switch (temp_r0_2) {                /* switch 1; irregular */
                case 0x0:                           /* switch 1 */
                    break;
                case 0x40:                          /* switch 1 */
                    temp_r0_3 = *var_r30;
                    var_r30 += 1;
                    arg0->pose = temp_r0_3;
                    temp_r4 = psTexGroupArray[arg0->bank][arg0->texGroup];
                    if ((temp_r4 != NULL) && (temp_r4->textures != NULL) && ((void *) temp_r4->textures[arg0->pose] != NULL)) {
                        arg0->kind |= 0x400;
                    }
                    break;
                }
                goto block_427;
            }
            var_r0 = temp_r26 & 0xF8;
            var_r29 = 0;
            if (var_r0 > 0x98U) {
                var_r0 = temp_r26 & 0xF0;
                if ((var_r0 != 0xC0) && (var_r0 != 0xD0)) {
                    var_r0 = temp_r26;
                }
            }
            switch (var_r0) {                       /* switch 2 */
            case 0x80:                              /* switch 2 */
                if (temp_r26 & 1) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec48.x = sp14;
                } else {
                    vec48.x = 0.0f;
                }
                if (temp_r26 & 2) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec48.y = sp14;
                } else {
                    vec48.y = 0.0f;
                }
                if (temp_r26 & 4) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec48.z = sp14;
                } else {
                    vec48.z = 0.0f;
                }
                psApplyOffsetLocalRotation(arg0, (PSVec *) &vec48.x);
                arg0->position.x = vec48.x;
                arg0->position.y = vec48.y;
                arg0->position.z = vec48.z;
            default:                                /* switch 2 */
block_427:
                if (var_r29 == 0) {
                    goto loop_30;
                }
                break;
            case 0x88:                              /* switch 2 */
                if (temp_r26 & 1) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec3C.x = sp14;
                } else {
                    vec3C.x = 0.0f;
                }
                if (temp_r26 & 2) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec3C.y = sp14;
                } else {
                    vec3C.y = 0.0f;
                }
                if (temp_r26 & 4) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec3C.z = sp14;
                } else {
                    vec3C.z = 0.0f;
                }
                psApplyOffsetLocalRotation(arg0, (PSVec *) &vec3C.x);
                arg0->position.x += vec3C.x;
                arg0->position.y += vec3C.y;
                arg0->position.z += vec3C.z;
                goto block_427;
            case 0x90:                              /* switch 2 */
                if (temp_r26 & 1) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec30.x = sp14;
                } else {
                    vec30.x = 0.0f;
                }
                if (temp_r26 & 2) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec30.y = sp14;
                } else {
                    vec30.y = 0.0f;
                }
                if (temp_r26 & 4) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec30.z = sp14;
                } else {
                    vec30.z = 0.0f;
                }
                psApplyOffsetLocalRotation(arg0, (PSVec *) &vec30.x);
                arg0->velocity.x = vec30.x;
                arg0->velocity.y = vec30.y;
                arg0->velocity.z = vec30.z;
                goto block_427;
            case 0x98:                              /* switch 2 */
                if (temp_r26 & 1) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec24.x = sp14;
                } else {
                    vec24.x = 0.0f;
                }
                if (temp_r26 & 2) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec24.y = sp14;
                } else {
                    vec24.y = 0.0f;
                }
                if (temp_r26 & 4) {
                    var_r30 = getFloat(var_r30, &sp14);
                    vec24.z = sp14;
                } else {
                    vec24.z = 0.0f;
                }
                if (!(arg0->kind & 4)) {
                    psApplyOffsetLocalRotation(arg0, (PSVec *) &vec24.x);
                } else {
                    temp_r3_7 = arg0->generator;
                    if ((temp_r3_7 != NULL) && (temp_r3_7->transformFlags & 0x40)) {
                        temp_f3_3 = (temp_r3_7->scale.z + (temp_r3_7->scale.x + temp_r3_7->scale.y)) / 3.0f;
                        vec24.x *= temp_f3_3;
                        vec24.y *= temp_f3_3;
                        vec24.z *= temp_f3_3;
                    }
                }
                arg0->velocity.x += vec24.x;
                arg0->velocity.y += vec24.y;
                arg0->velocity.z += vec24.z;
                goto block_427;
            case 0xA0:                              /* switch 2 */
                var_r30 = getFloat(getTime(var_r30, &arg0->sizeCount), &arg0->sizeTarget);
                if ((u16) arg0->sizeCount == 0) {
                    arg0->size = arg0->sizeTarget;
                }
                goto block_427;
            case 0xA1:                              /* switch 2 */
                arg0->kind &= 0xFFFFFBFF;
                goto block_427;
            case 0xA2:                              /* switch 2 */
                var_r30 = getFloat(var_r30, &arg0->gravity);
                if (arg0->gravity == 0.0f) {
                    arg0->kind &= 0xFFFFFFFE;
                } else {
                    arg0->kind |= 1;
                }
                temp_r3_8 = arg0->generator;
                if ((temp_r3_8 != NULL) && (temp_r3_8->transformFlags & 0x1000)) {
                    arg0->gravity *= (temp_r3_8->scale.z + (temp_r3_8->scale.x + temp_r3_8->scale.y)) / 3.0f;
                }
                goto block_427;
            case 0xA3:                              /* switch 2 */
                var_r30 = getFloat(var_r30, &arg0->friction);
                if (arg0->friction == 1.0f) {
                    arg0->kind &= 0xFFFFFFFD;
                } else {
                    arg0->kind |= 2;
                }
                temp_r3_9 = arg0->generator;
                if ((temp_r3_9 != NULL) && (temp_r3_9->transformFlags & 0x1000)) {
                    arg0->friction *= (temp_r3_9->scale.z + (temp_r3_9->scale.x + temp_r3_9->scale.y)) / 3.0f;
                }
                goto block_427;
            case 0xA4:                              /* switch 2 */
                temp_r6 = ((var_r30[0x0] << 8) & 0xFF00) + var_r30[0x1];
                var_r30 += 2;
                temp_r3_10 = psGenerateParticleID0(arg0, (s32) arg0->link, (s32) arg0->bank, temp_r6, 0);
                if (temp_r3_10 != NULL) {
                    temp_r3_10->id = arg0->id;
                    temp_r3_10->generator = arg0->generator;
                    temp_r4_2 = arg0->generator;
                    if (temp_r4_2 != NULL) {
                        temp_r4_2->children += 1;
                    }
                    if (arg0->generator->kind & 0x20000000) {
                        temp_r3_10->kind |= 0x20000000;
                    }
                    psApplyVelocityLocalRotation(temp_r3_10);
                    temp_r3_11 = arg0->generator;
                    if ((temp_r3_11 != NULL) && (temp_r3_11->type & 0x2000)) {
                        psChangeParticleAppSRT(temp_r3_10, arg0->appsrt);
                    } else {
                        psAttachParticleAppSRT(temp_r3_10, arg0->appsrt);
                    }
                    temp_r3_10->position.x = arg0->position.x;
                    temp_r3_10->position.y = arg0->position.y;
                    temp_r3_10->position.z = arg0->position.z;
                    psInterpretParticle0(temp_r3_10, arg0);
                }
                goto block_427;
            case 0xF1:                              /* switch 2 */
                temp_r5 = arg0->bank;
                temp_r3_12 = (u32*)ptclref[temp_r5 & 0xFF];
                var_r6 = ((var_r30[0x0] << 8) & 0xFF00) + var_r30[0x1];
                var_r30 += 2;
                if (temp_r3_12 != 0U) {
                    var_r6 = temp_r3_12[var_r6];
                }
                temp_r3_13 = psGenerateParticleID0(arg0, (s32) arg0->link, (s32) temp_r5, var_r6, 0);
                if (temp_r3_13 != NULL) {
                    temp_r3_13->id = arg0->id;
                    temp_r3_13->generator = arg0->generator;
                    temp_r4_3 = arg0->generator;
                    if (temp_r4_3 != NULL) {
                        temp_r4_3->children += 1;
                    }
                    if (arg0->generator->kind & 0x20000000) {
                        temp_r3_13->kind |= 0x20000000;
                    }
                    psApplyVelocityLocalRotation(temp_r3_13);
                    temp_r3_14 = arg0->generator;
                    if ((temp_r3_14 != NULL) && (temp_r3_14->type & 0x2000)) {
                        psChangeParticleAppSRT(temp_r3_13, arg0->appsrt);
                    } else {
                        psAttachParticleAppSRT(temp_r3_13, arg0->appsrt);
                    }
                    temp_r3_13->position.x = arg0->position.x;
                    temp_r3_13->position.y = arg0->position.y;
                    temp_r3_13->position.z = arg0->position.z;
                    psInterpretParticle0(temp_r3_13, arg0);
                }
                goto block_427;
            case 0xA5:                              /* switch 2 */
                temp_r3_15 = var_r30[0x0];
                temp_r0_4 = var_r30[0x1];
                var_r30 += 2;
                temp_r3_16 = psCreateGeneratorID((s32) arg0->link, (s32) arg0->bank, ((temp_r3_15 << 8) & 0xFF00) + temp_r0_4);
                if (temp_r3_16 != NULL) {
                    temp_r3_16->id = arg0->id;
                    psCopyGeneratorData(temp_r3_16, arg0->generator);
                    temp_r4_4 = arg0->appsrt;
                    if (temp_r4_4 != NULL) {
                        temp_r3_17 = arg0->generator;
                        if ((temp_r3_17 != NULL) && (temp_r3_17->type & 0x2000)) {
                            psChangeGeneratorAppSRT(temp_r3_16, temp_r4_4);
                        } else {
                            psAttachGeneratorAppSRT(temp_r3_16, temp_r4_4);
                        }
                    }
                    if ((PSAppSRT *) arg0->appsrt != NULL) {
                        if ((PSAppSRT *) temp_r3_16->appsrt != NULL) {
                            temp_r3_16->position.x = arg0->position.x;
                            temp_r3_16->position.y = arg0->position.y;
                            temp_r3_16->position.z = arg0->position.z;
                            temp_r5_2 = temp_r3_16->appsrt;
                            temp_r4_5 = arg0->appsrt;
                            if (temp_r5_2 != temp_r4_5) {
                                M2C_STRUCT_COPY(temp_r5_2, temp_r4_5, 0xC);
                            }
                        }
                    } else {
                        temp_r3_18 = temp_r3_16->appsrt;
                        if (temp_r3_18 != NULL) {
                            temp_r3_18->translate.x = arg0->position.x;
                            temp_r3_16->appsrt->translate.y = arg0->position.y;
                            temp_r3_16->appsrt->translate.z = arg0->position.z;
                            temp_r3_16->position.x = arg0->position.x;
                            temp_r3_16->position.y = arg0->position.y;
                            temp_r3_16->position.z = arg0->position.z;
                        } else {
                            temp_r3_16->position.x = arg0->position.x;
                            temp_r3_16->position.y = arg0->position.y;
                            temp_r3_16->position.z = arg0->position.z;
                        }
                    }
                    temp_r0_5 = temp_r3_16->appsrt;
                    temp_r3_19 = arg0->appsrt;
                    if (temp_r0_5 != temp_r3_19) {
                        if (temp_r3_19 == NULL) {
                            if (temp_r0_5 != NULL) {
                                genPosUpdate(temp_r3_16);
                                temp_r3_16->position.x -= temp_r3_16->appsrt->translate.x;
                                temp_r3_16->position.y -= temp_r3_16->appsrt->translate.y;
                                temp_r3_16->position.z -= temp_r3_16->appsrt->translate.z;
                            }
                        } else {
                            genPosUpdate(temp_r3_19->generator);
                            if ((PSAppSRT *) temp_r3_16->appsrt != NULL) {
                                genPosUpdate(temp_r3_16);
                                temp_r3_16->position.x += arg0->appsrt->translate.x - temp_r3_16->appsrt->translate.x;
                                temp_r3_16->position.y += arg0->appsrt->translate.y - temp_r3_16->appsrt->translate.y;
                                temp_r3_16->position.z += arg0->appsrt->translate.z - temp_r3_16->appsrt->translate.z;
                            } else {
                                temp_r3_16->position.x += arg0->appsrt->translate.x;
                                temp_r3_16->position.y += arg0->appsrt->translate.y;
                                temp_r3_16->position.z += arg0->appsrt->translate.z;
                            }
                        }
                    }
                }
                goto block_427;
            case 0xEF:                              /* switch 2 */
                temp_r27 = var_r30[0x2];
                temp_r5_3 = ((var_r30[0x0] << 8) & 0xFF00) + var_r30[0x1];
                var_r30 += 3;
                temp_r3_20 = psCreateGeneratorID((s32) arg0->link, (s32) arg0->bank, temp_r5_3);
                if (temp_r3_20 != NULL) {
                    temp_r3_20->id = arg0->id;
                    psCopyGeneratorData(temp_r3_20, arg0->generator);
                    temp_r4_6 = arg0->appsrt;
                    if (temp_r4_6 != NULL) {
                        temp_r3_21 = arg0->generator;
                        if ((temp_r3_21 != NULL) && (temp_r3_21->type & 0x2000)) {
                            psChangeGeneratorAppSRT(temp_r3_20, temp_r4_6);
                        } else {
                            psAttachGeneratorAppSRT(temp_r3_20, temp_r4_6);
                        }
                    }
                    temp_r3_20->kind &= 0xF1FFFFFF;
                    temp_r3_20->kind |= (temp_r27 << 0x19) & 0x0E000000;
                    if ((PSAppSRT *) arg0->appsrt != NULL) {
                        if ((PSAppSRT *) temp_r3_20->appsrt != NULL) {
                            temp_r3_20->position.x = arg0->position.x;
                            temp_r3_20->position.y = arg0->position.y;
                            temp_r3_20->position.z = arg0->position.z;
                            temp_r5_4 = temp_r3_20->appsrt;
                            temp_r4_7 = arg0->appsrt;
                            if (temp_r5_4 != temp_r4_7) {
                                M2C_STRUCT_COPY(temp_r5_4, temp_r4_7, 0xC);
                            }
                        }
                    } else {
                        temp_r3_22 = temp_r3_20->appsrt;
                        if (temp_r3_22 != NULL) {
                            temp_r3_22->translate.x = arg0->position.x;
                            temp_r3_20->appsrt->translate.y = arg0->position.y;
                            temp_r3_20->appsrt->translate.z = arg0->position.z;
                            temp_r3_20->position.x = arg0->position.x;
                            temp_r3_20->position.y = arg0->position.y;
                            temp_r3_20->position.z = arg0->position.z;
                        } else {
                            temp_r3_20->position.x = arg0->position.x;
                            temp_r3_20->position.y = arg0->position.y;
                            temp_r3_20->position.z = arg0->position.z;
                        }
                    }
                    temp_r0_6 = temp_r3_20->appsrt;
                    temp_r3_23 = arg0->appsrt;
                    if (temp_r0_6 != temp_r3_23) {
                        if (temp_r3_23 == NULL) {
                            if (temp_r0_6 != NULL) {
                                genPosUpdate(temp_r3_20);
                                temp_r3_20->position.x -= temp_r3_20->appsrt->translate.x;
                                temp_r3_20->position.y -= temp_r3_20->appsrt->translate.y;
                                temp_r3_20->position.z -= temp_r3_20->appsrt->translate.z;
                            }
                        } else {
                            genPosUpdate(temp_r3_23->generator);
                            if ((PSAppSRT *) temp_r3_20->appsrt != NULL) {
                                genPosUpdate(temp_r3_20);
                                temp_r3_20->position.x += arg0->appsrt->translate.x - temp_r3_20->appsrt->translate.x;
                                temp_r3_20->position.y += arg0->appsrt->translate.y - temp_r3_20->appsrt->translate.y;
                                temp_r3_20->position.z += arg0->appsrt->translate.z - temp_r3_20->appsrt->translate.z;
                            } else {
                                temp_r3_20->position.x += arg0->appsrt->translate.x;
                                temp_r3_20->position.y += arg0->appsrt->translate.y;
                                temp_r3_20->position.z += arg0->appsrt->translate.z;
                            }
                        }
                    }
                }
                goto block_427;
            case 0xF0:                              /* switch 2 */
                temp_r4_8 = arg0->bank;
                temp_r3_24 = (u32*)ptclref[temp_r4_8 & 0xFF];
                temp_r27_2 = var_r30[0x2];
                var_r5 = ((var_r30[0x0] << 8) & 0xFF00) + var_r30[0x1];
                var_r30 += 3;
                if (temp_r3_24 != 0U) {
                    var_r5 = temp_r3_24[var_r5];
                }
                temp_r3_25 = psCreateGeneratorID((s32) arg0->link, (s32) temp_r4_8, var_r5);
                if (temp_r3_25 != NULL) {
                    temp_r3_25->id = arg0->id;
                    psCopyGeneratorData(temp_r3_25, arg0->generator);
                    temp_r4_9 = arg0->appsrt;
                    if (temp_r4_9 != NULL) {
                        temp_r3_26 = arg0->generator;
                        if ((temp_r3_26 != NULL) && (temp_r3_26->type & 0x2000)) {
                            psChangeGeneratorAppSRT(temp_r3_25, temp_r4_9);
                        } else {
                            psAttachGeneratorAppSRT(temp_r3_25, temp_r4_9);
                        }
                    }
                    temp_r3_25->kind &= 0xF1FFFFFF;
                    temp_r3_25->kind |= (temp_r27_2 << 0x19) & 0x0E000000;
                    if ((PSAppSRT *) arg0->appsrt != NULL) {
                        if ((PSAppSRT *) temp_r3_25->appsrt != NULL) {
                            temp_r3_25->position.x = arg0->position.x;
                            temp_r3_25->position.y = arg0->position.y;
                            temp_r3_25->position.z = arg0->position.z;
                            temp_r5_5 = temp_r3_25->appsrt;
                            temp_r4_10 = arg0->appsrt;
                            if (temp_r5_5 != temp_r4_10) {
                                M2C_STRUCT_COPY(temp_r5_5, temp_r4_10, 0xC);
                            }
                        }
                    } else {
                        temp_r3_27 = temp_r3_25->appsrt;
                        if (temp_r3_27 != NULL) {
                            temp_r3_27->translate.x = arg0->position.x;
                            temp_r3_25->appsrt->translate.y = arg0->position.y;
                            temp_r3_25->appsrt->translate.z = arg0->position.z;
                            temp_r3_25->position.x = arg0->position.x;
                            temp_r3_25->position.y = arg0->position.y;
                            temp_r3_25->position.z = arg0->position.z;
                        } else {
                            temp_r3_25->position.x = arg0->position.x;
                            temp_r3_25->position.y = arg0->position.y;
                            temp_r3_25->position.z = arg0->position.z;
                        }
                    }
                    temp_r0_7 = temp_r3_25->appsrt;
                    temp_r3_28 = arg0->appsrt;
                    if (temp_r0_7 != temp_r3_28) {
                        if (temp_r3_28 == NULL) {
                            if (temp_r0_7 != NULL) {
                                genPosUpdate(temp_r3_25);
                                temp_r3_25->position.x -= temp_r3_25->appsrt->translate.x;
                                temp_r3_25->position.y -= temp_r3_25->appsrt->translate.y;
                                temp_r3_25->position.z -= temp_r3_25->appsrt->translate.z;
                            }
                        } else {
                            genPosUpdate(temp_r3_28->generator);
                            if ((PSAppSRT *) temp_r3_25->appsrt != NULL) {
                                genPosUpdate(temp_r3_25);
                                temp_r3_25->position.x += arg0->appsrt->translate.x - temp_r3_25->appsrt->translate.x;
                                temp_r3_25->position.y += arg0->appsrt->translate.y - temp_r3_25->appsrt->translate.y;
                                temp_r3_25->position.z += arg0->appsrt->translate.z - temp_r3_25->appsrt->translate.z;
                            } else {
                                temp_r3_25->position.x += arg0->appsrt->translate.x;
                                temp_r3_25->position.y += arg0->appsrt->translate.y;
                                temp_r3_25->position.z += arg0->appsrt->translate.z;
                            }
                        }
                    }
                }
                goto block_427;
            case 0xA6:                              /* switch 2 */
                temp_r0_8 = var_r30[0x3];
                temp_r27_3 = (var_r30[0x2] << 8) & 0xFF00;
                temp_r26_2 = ((var_r30[0x0] << 8) & 0xFF00) + var_r30[0x1];
                var_r30 += 4;
                arg0->life = temp_r26_2 + (s32) ((f32) (temp_r27_3 + temp_r0_8) * HSD_Randf());
                goto block_427;
            case 0xA7:                              /* switch 2 */
                temp_r26_3 = var_r30[0x0];
                var_r30 += 1;
                if ((s32) temp_r26_3 >= (s32) (100.0f * HSD_Randf())) {
                    arg0->life = 1;
                } else {
                    goto block_427;
                }
                break;
            case 0xA8:                              /* switch 2 */
                temp_r26_4 = getFloat(var_r30, &sp14);
                vec18.x = (2.0f * sp14 * HSD_Randf()) - sp14;
                temp_r26_5 = getFloat(temp_r26_4, &sp14);
                vec18.y = (2.0f * sp14 * HSD_Randf()) - sp14;
                var_r30 = getFloat(temp_r26_5, &sp14);
                vec18.z = (2.0f * sp14 * HSD_Randf()) - sp14;
                psApplyOffsetLocalRotation(arg0, (PSVec *) &vec18.x);
                arg0->position.x += vec18.x;
                arg0->position.y += vec18.y;
                arg0->position.z += vec18.z;
                goto block_427;
            case 0xA9:                              /* switch 2 */
                var_r30 = getFloat(var_r30, &sp14);
                modifyDir(arg0, sp14);
                goto block_427;
            case 0xF4:                              /* switch 2 */
                var_r30 = getFloat(getFloat(getFloat(getFloat(var_r30, &sp10), &spC), &sp8), &sp14);
                if ((PSGenerator *) arg0->generator != NULL) {
                    modifyDirGenBase(arg0, sp14, sp10, spC, sp8);
                }
                goto block_427;
            case 0xF5:                              /* switch 2 */
                temp_r5_6 = arg0->generator;
                if ((temp_r5_6 != NULL) && ((PSAppSRT *) temp_r5_6->appsrt != NULL)) {
                    temp_r4_11 = temp_r5_6->type;
                    temp_r5_6->type = temp_r4_11 | 0x2000;
                    arg0->generator->appsrt->generatorOwned = 0;
                    if (!(temp_r4_11 & 0x2000)) {
                        genPosUpdate(arg0->generator);
                    }
                }
                goto block_427;
            case 0xF6:                              /* switch 2 */
                temp_r3_29 = arg0->generator;
                if ((temp_r3_29 != NULL) && ((PSAppSRT *) temp_r3_29->appsrt != NULL)) {
                    temp_r0_9 = temp_r3_29->type;
                    temp_r3_29->type = temp_r0_9 | 0x1000;
                    if (!(temp_r0_9 & 0x1000)) {
                        genPosUpdate(arg0->generator);
                    }
                }
                goto block_427;
            case 0xF7:                              /* switch 2 */
                arg0->kind |= 0x10000000;
                goto block_427;
            case 0xAA:                              /* switch 2 */
                temp_r0_10 = var_r30[0x3];
                temp_r27_4 = (var_r30[0x2] << 8) & 0xFF00;
                temp_r26_6 = ((var_r30[0x0] << 8) & 0xFF00) + var_r30[0x1];
                var_r30 += 4;
                temp_r5_7 = arg0->bank;
                temp_r3_30 = (u32*)ptclref[temp_r5_7 & 0xFF];
                var_r26_2 = temp_r26_6 + (s32) ((f32) (temp_r27_4 + temp_r0_10) * HSD_Randf());
                if (temp_r3_30 != 0U) {
                    var_r26_2 = temp_r3_30[var_r26_2];
                }
                temp_r3_31 = psGenerateParticleID0(arg0, (s32) arg0->link, (s32) temp_r5_7, var_r26_2, 0);
                if (temp_r3_31 != NULL) {
                    temp_r3_31->position.x = arg0->position.x;
                    temp_r3_31->position.y = arg0->position.y;
                    temp_r3_31->position.z = arg0->position.z;
                    temp_r3_31->id = arg0->id;
                    temp_r3_31->generator = arg0->generator;
                    temp_r4_12 = arg0->generator;
                    if (temp_r4_12 != NULL) {
                        temp_r4_12->children += 1;
                    }
                    if (arg0->generator->kind & 0x20000000) {
                        temp_r3_31->kind |= 0x20000000;
                    }
                    psApplyVelocityLocalRotation(temp_r3_31);
                    temp_r4_13 = arg0->appsrt;
                    if (temp_r4_13 != NULL) {
                        temp_r3_32 = arg0->generator;
                        if ((temp_r3_32 != NULL) && (temp_r3_32->type & 0x2000)) {
                            psChangeParticleAppSRT(temp_r3_31, temp_r4_13);
                        } else {
                            psAttachParticleAppSRT(temp_r3_31, temp_r4_13);
                        }
                    }
                    psInterpretParticle0(temp_r3_31, arg0);
                }
                goto block_427;
            case 0xAB:                              /* switch 2 */
                var_r30 = getFloat(var_r30, &sp14);
                arg0->velocity.x *= sp14;
                arg0->velocity.y *= sp14;
                arg0->velocity.z *= sp14;
                goto block_427;
            case 0xAC:                              /* switch 2 */
                var_r30 = getFloat(getFloat(getTime(var_r30, &arg0->sizeCount), &arg0->sizeTarget), &sp14);
                arg0->sizeTarget += sp14 * HSD_Randf();
                if ((u16) arg0->sizeCount == 0) {
                    arg0->size = arg0->sizeTarget;
                }
                goto block_427;
            case 0xAD:                              /* switch 2 */
                arg0->kind |= 0x80;
                goto block_427;
            case 0xAE:                              /* switch 2 */
                arg0->kind &= 0xFFFFFF9F;
                goto block_427;
            case 0xAF:                              /* switch 2 */
                arg0->kind &= 0xFFFFFFBF;
                arg0->kind |= 0x20;
                goto block_427;
            case 0xB0:                              /* switch 2 */
                arg0->kind &= 0xFFFFFFDF;
                arg0->kind |= 0x40;
                goto block_427;
            case 0xB1:                              /* switch 2 */
                arg0->kind |= 0x60;
                goto block_427;
            case 0xB2:                              /* switch 2 */
                temp_r3_33 = arg0->appsrt;
                if ((temp_r3_33 != NULL) && ((u8) temp_r3_33->generatorOwned == 0)) {
                    genPosUpdate(temp_r3_33->generator);
                    temp_r6_2 = arg0->appsrt;
                    HSD_MTXSRT((f32 (*)[4]) temp_r6_2->matrix[0], &temp_r6_2->scale, &temp_r6_2->rotation, &temp_r6_2->translate, 0);
                    temp_r4_14 = arg0->appsrt;
                    temp_f3_4 = arg0->position.y;
                    temp_f6 = arg0->position.x;
                    temp_f7 = arg0->position.z;
                    arg0->position.x = temp_r4_14->matrix[0][3] + ((temp_r4_14->matrix[0][2] * temp_f7) + ((temp_r4_14->matrix[0][0] * temp_f6) + (temp_r4_14->matrix[0][1] * temp_f3_4)));
                    arg0->position.y = temp_r4_14->matrix[1][3] + ((temp_r4_14->matrix[1][2] * temp_f7) + ((temp_r4_14->matrix[1][0] * temp_f6) + (temp_r4_14->matrix[1][1] * temp_f3_4)));
                    arg0->position.z = temp_r4_14->matrix[2][3] + ((temp_r4_14->matrix[2][2] * temp_f7) + ((temp_r4_14->matrix[2][0] * temp_f6) + (temp_r4_14->matrix[2][1] * temp_f3_4)));
                    psRemoveParticleAppSRT(arg0);
                }
                goto block_427;
            case 0xB3:                              /* switch 2 */
                temp_r4_15 = arg0->alphaCount;
                if (temp_r4_15 != 0) {
                    temp_r5_8 = arg0->alpha1Target;
                    temp_r6_3 = (s32) (arg0->alphaRemain << 0x10) / (s32) temp_r4_15;
                    arg0->alpha1 = (u8) ((s32) ((temp_r5_8 << 0x10) + (temp_r6_3 * (arg0->alpha1 - temp_r5_8))) >> 0x10);
                    temp_r4_16 = arg0->alpha2Target;
                    arg0->alpha2 = (u8) ((s32) ((temp_r4_16 << 0x10) + (temp_r6_3 * (arg0->alpha2 - temp_r4_16))) >> 0x10);
                }
                temp_r3_34 = getTime(var_r30, &arg0->alphaCount);
                temp_r0_11 = temp_r3_34[0x0];
                var_r30 = temp_r3_34 + 3;
                arg0->alphaMode = temp_r0_11;
                arg0->alpha1Target = temp_r3_34[0x1];
                arg0->alpha2Target = temp_r3_34[0x2];
                temp_r0_12 = arg0->alphaCount;
                if (temp_r0_12 == 0) {
                    arg0->alpha1 = arg0->alpha1Target;
                    arg0->alpha2 = arg0->alpha2Target;
                    arg0->alphaRemain = 0;
                    arg0->alphaCount = 0;
                } else {
                    arg0->alphaRemain = temp_r0_12;
                }
                goto block_427;
            case 0xB4:                              /* switch 2 */
                arg0->kind |= 0x200;
                goto block_427;
            case 0xB5:                              /* switch 2 */
                arg0->kind &= 0xFFFFFDFF;
                goto block_427;
            case 0xB6:                              /* switch 2 */
                var_r30 = getFloat(getTime(var_r30, &arg0->rotateCount), &sp14);
                arg0->rotateTarget += sp14;
                if ((u16) arg0->rotateCount == 0) {
                    arg0->rotate = arg0->rotateTarget;
                }
                goto block_427;
            case 0xB7:                              /* switch 2 */
                temp_r5_9 = var_r30[0x0];
                var_r30 += 1;
                setVelToJObj(arg0, psPointJObj[temp_r5_9 + arg0->pointOffset]);
                goto block_427;
            case 0xB8:                              /* switch 2 */
                temp_r26_7 = var_r30[0x0] + arg0->pointOffset;
                temp_r4_17 = arg0->generator;
                var_r30 = getFloat(getFloat(var_r30 + 1, &sp14), &sp10);
                if ((temp_r4_17 != NULL) && (temp_r4_17->transformFlags & 0x100)) {
                    temp_f2 = (temp_r4_17->scale.z + (temp_r4_17->scale.x + temp_r4_17->scale.y)) / 3.0f;
                    sp14 *= temp_f2;
                    sp10 *= temp_f2;
                }
                if (applyForceJObj(arg0, psPointJObj[temp_r26_7], sp14, sp10) != 0) {
                    arg0->life = 1;
                } else {
                    goto block_427;
                }
                break;
            case 0xB9:                              /* switch 2 */
                temp_r6_4 = ((var_r30[0x0] << 8) & 0xFF00) + var_r30[0x1];
                var_r30 += 2;
                temp_r3_35 = psGenerateParticleID0(arg0, (s32) arg0->link, (s32) arg0->bank, temp_r6_4, 0);
                if (temp_r3_35 != NULL) {
                    temp_r3_35->position.x = arg0->position.x;
                    temp_r3_35->position.y = arg0->position.y;
                    temp_r3_35->position.z = arg0->position.z;
                    temp_r3_35->velocity.x = arg0->velocity.x;
                    temp_r3_35->velocity.y = arg0->velocity.y;
                    temp_r3_35->velocity.z = arg0->velocity.z;
                    temp_r3_35->id = arg0->id;
                    temp_r3_35->generator = arg0->generator;
                    temp_r4_18 = arg0->generator;
                    if (temp_r4_18 != NULL) {
                        temp_r4_18->children += 1;
                    }
                    if (arg0->generator->kind & 0x20000000) {
                        temp_r3_35->kind |= 0x20000000;
                    }
                    psApplyVelocityLocalRotation(temp_r3_35);
                    temp_r4_19 = arg0->appsrt;
                    if (temp_r4_19 != NULL) {
                        temp_r3_36 = arg0->generator;
                        if ((temp_r3_36 != NULL) && (temp_r3_36->type & 0x2000)) {
                            psChangeParticleAppSRT(temp_r3_35, temp_r4_19);
                        } else {
                            psAttachParticleAppSRT(temp_r3_35, temp_r4_19);
                        }
                    }
                    psInterpretParticle0(temp_r3_35, arg0);
                }
                goto block_427;
            case 0xF2:                              /* switch 2 */
                temp_r5_10 = arg0->bank;
                temp_r3_37 = (u32*)ptclref[temp_r5_10 & 0xFF];
                var_r6_2 = ((var_r30[0x0] << 8) & 0xFF00) + var_r30[0x1];
                var_r30 += 2;
                if (temp_r3_37 != 0U) {
                    var_r6_2 = temp_r3_37[var_r6_2];
                }
                temp_r3_38 = psGenerateParticleID0(arg0, (s32) arg0->link, (s32) temp_r5_10, var_r6_2, 0);
                if (temp_r3_38 != NULL) {
                    temp_r3_38->position.x = arg0->position.x;
                    temp_r3_38->position.y = arg0->position.y;
                    temp_r3_38->position.z = arg0->position.z;
                    temp_r3_38->velocity.x = arg0->velocity.x;
                    temp_r3_38->velocity.y = arg0->velocity.y;
                    temp_r3_38->velocity.z = arg0->velocity.z;
                    temp_r3_38->id = arg0->id;
                    temp_r3_38->generator = arg0->generator;
                    temp_r4_20 = arg0->generator;
                    if (temp_r4_20 != NULL) {
                        temp_r4_20->children += 1;
                    }
                    if (arg0->generator->kind & 0x20000000) {
                        temp_r3_38->kind |= 0x20000000;
                    }
                    psApplyVelocityLocalRotation(temp_r3_38);
                    temp_r4_21 = arg0->appsrt;
                    if (temp_r4_21 != NULL) {
                        temp_r3_39 = arg0->generator;
                        if ((temp_r3_39 != NULL) && (temp_r3_39->type & 0x2000)) {
                            psChangeParticleAppSRT(temp_r3_38, temp_r4_21);
                        } else {
                            psAttachParticleAppSRT(temp_r3_38, temp_r4_21);
                        }
                    }
                    psInterpretParticle0(temp_r3_38, arg0);
                }
                goto block_427;
            case 0xBA:                              /* switch 2 */
                temp_r4_22 = arg0->primCount;
                if (temp_r4_22 != 0) {
                    temp_r5_11 = arg0->primTarget[0];
                    temp_r0_13 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r4_22;
                    arg0->primColor[0] = (u8) ((s32) ((temp_r5_11 << 0x10) + (temp_r0_13 * (arg0->primColor[0] - temp_r5_11))) >> 0x10);
                    temp_r5_12 = arg0->primTarget[1];
                    arg0->primColor[1] = (u8) ((s32) ((temp_r5_12 << 0x10) + (temp_r0_13 * (arg0->primColor[1] - temp_r5_12))) >> 0x10);
                    temp_r5_13 = arg0->primTarget[2];
                    arg0->primColor[2] = (u8) ((s32) ((temp_r5_13 << 0x10) + (temp_r0_13 * (arg0->primColor[2] - temp_r5_13))) >> 0x10);
                    temp_r5_14 = arg0->primTarget[3];
                    arg0->primColor[3] = (u8) ((s32) ((temp_r5_14 << 0x10) + (temp_r0_13 * (arg0->primColor[3] - temp_r5_14))) >> 0x10);
                }
                temp_f1_2 = (f32) ((s8) var_r30[0x0] * 2) * HSD_Randf();
                sp14 = temp_f1_2;
                arg0->primTarget[0] = U8ClampAdd(arg0->primTarget[0], temp_f1_2);
                temp_f1_3 = (f32) ((s8) var_r30[0x1] * 2) * HSD_Randf();
                sp14 = temp_f1_3;
                arg0->primTarget[1] = U8ClampAdd(arg0->primTarget[1], temp_f1_3);
                temp_f1_4 = (f32) ((s8) var_r30[0x2] * 2) * HSD_Randf();
                sp14 = temp_f1_4;
                arg0->primTarget[2] = U8ClampAdd(arg0->primTarget[2], temp_f1_4);
                temp_r3_40 = var_r30[0x3];
                var_r30 += 4;
                temp_f1_5 = (f32) ((s8) temp_r3_40 * 2) * HSD_Randf();
                sp14 = temp_f1_5;
                arg0->primTarget[3] = U8ClampAdd(arg0->primTarget[3], temp_f1_5);
                temp_r0_14 = arg0->primCount;
                if (temp_r0_14 == 0) {
                    *(u32*)arg0->primColor = (s32) *(u32*)arg0->primTarget;
                } else {
                    arg0->primRemain = temp_r0_14;
                }
                goto block_427;
            case 0xBB:                              /* switch 2 */
                temp_r4_23 = arg0->envCount;
                if (temp_r4_23 != 0) {
                    temp_r5_15 = arg0->envTarget[0];
                    temp_r0_15 = (s32) (arg0->envRemain << 0x10) / (s32) temp_r4_23;
                    arg0->envColor[0] = (u8) ((s32) ((temp_r5_15 << 0x10) + (temp_r0_15 * (arg0->envColor[0] - temp_r5_15))) >> 0x10);
                    temp_r5_16 = arg0->envTarget[1];
                    arg0->envColor[1] = (u8) ((s32) ((temp_r5_16 << 0x10) + (temp_r0_15 * (arg0->envColor[1] - temp_r5_16))) >> 0x10);
                    temp_r5_17 = arg0->envTarget[2];
                    arg0->envColor[2] = (u8) ((s32) ((temp_r5_17 << 0x10) + (temp_r0_15 * (arg0->envColor[2] - temp_r5_17))) >> 0x10);
                    temp_r5_18 = arg0->envTarget[3];
                    arg0->envColor[3] = (u8) ((s32) ((temp_r5_18 << 0x10) + (temp_r0_15 * (arg0->envColor[3] - temp_r5_18))) >> 0x10);
                }
                temp_f1_6 = (f32) ((s8) var_r30[0x0] * 2) * HSD_Randf();
                sp14 = temp_f1_6;
                arg0->envTarget[0] = U8ClampAdd(arg0->envTarget[0], temp_f1_6);
                temp_f1_7 = (f32) ((s8) var_r30[0x1] * 2) * HSD_Randf();
                sp14 = temp_f1_7;
                arg0->envTarget[1] = U8ClampAdd(arg0->envTarget[1], temp_f1_7);
                temp_f1_8 = (f32) ((s8) var_r30[0x2] * 2) * HSD_Randf();
                sp14 = temp_f1_8;
                arg0->envTarget[2] = U8ClampAdd(arg0->envTarget[2], temp_f1_8);
                temp_r3_41 = var_r30[0x3];
                var_r30 += 4;
                temp_f1_9 = (f32) ((s8) temp_r3_41 * 2) * HSD_Randf();
                sp14 = temp_f1_9;
                arg0->envTarget[3] = U8ClampAdd(arg0->envTarget[3], temp_f1_9);
                temp_r0_16 = arg0->envCount;
                if (temp_r0_16 == 0) {
                    *(u32*)arg0->envColor = (s32) *(u32*)arg0->envTarget;
                } else {
                    arg0->envRemain = temp_r0_16;
                }
                goto block_427;
            case 0xBC:                              /* switch 2 */
                arg0->pose = var_r30[0x0];
                temp_r0_17 = var_r30[0x1];
                var_r30 += 2;
                sp14 = (f32) temp_r0_17;
                arg0->pose = (u8) (s32) ((sp14 * HSD_Randf()) + (f32) arg0->pose);
                temp_r4_24 = psTexGroupArray[arg0->bank][arg0->texGroup];
                if ((temp_r4_24 != NULL) && (temp_r4_24->textures != NULL) && ((void *) temp_r4_24->textures[arg0->pose] != NULL)) {
                    arg0->kind |= 0x400;
                }
                goto block_427;
            case 0xBD:                              /* switch 2 */
                temp_r4_25 = arg0->generator;
                var_r30 = getFloat(getFloat(var_r30, &sp14), &sp10);
                if ((temp_r4_25 != NULL) && (temp_r4_25->transformFlags & 0x200)) {
                    temp_f2_2 = (temp_r4_25->scale.z + (temp_r4_25->scale.x + temp_r4_25->scale.y)) / 3.0f;
                    sp14 *= temp_f2_2;
                    sp10 *= temp_f2_2;
                }
                sp14 += sp10 * HSD_Randf();
                temp_f1_10 = arg0->velocity.x;
                temp_f0 = arg0->velocity.y;
                temp_f2_3 = arg0->velocity.z;
                temp_f1_11 = sqrtf((temp_f2_3 * temp_f2_3) + ((temp_f1_10 * temp_f1_10) + (temp_f0 * temp_f0)));
                temp_f2_4 = (f32) temp_f1_11;
                sp10 = (f32) temp_f1_11;
                if (temp_f2_4 > 1e-10f) {
                    temp_f1_12 = sp14 / temp_f2_4;
                    sp14 = temp_f1_12;
                    arg0->velocity.x *= temp_f1_12;
                    arg0->velocity.y *= sp14;
                    arg0->velocity.z *= sp14;
                }
                goto block_427;
            case 0xBE:                              /* switch 2 */
                temp_r3_42 = getFloat(var_r30, &sp14);
                arg0->velocity.x *= sp14;
                temp_r3_43 = getFloat(temp_r3_42, &sp14);
                arg0->velocity.y *= sp14;
                var_r30 = getFloat(temp_r3_43, &sp14);
                arg0->velocity.z *= sp14;
                goto block_427;
            case 0xBF:                              /* switch 2 */
                temp_r4_26 = var_r30[0x0];
                var_r30 += 1;
                arg0->kind |= (((temp_r4_26 + arg0->pointOffset) << 0xC) & 0x7000) | 0x8000;
                goto block_427;
            case 0xC0:                              /* switch 2 */
                temp_r4_27 = arg0->primCount;
                if (temp_r4_27 != 0) {
                    temp_r5_19 = arg0->primTarget[0];
                    temp_r0_18 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r4_27;
                    arg0->primColor[0] = (u8) ((s32) ((temp_r5_19 << 0x10) + (temp_r0_18 * (arg0->primColor[0] - temp_r5_19))) >> 0x10);
                    temp_r5_20 = arg0->primTarget[1];
                    arg0->primColor[1] = (u8) ((s32) ((temp_r5_20 << 0x10) + (temp_r0_18 * (arg0->primColor[1] - temp_r5_20))) >> 0x10);
                    temp_r5_21 = arg0->primTarget[2];
                    arg0->primColor[2] = (u8) ((s32) ((temp_r5_21 << 0x10) + (temp_r0_18 * (arg0->primColor[2] - temp_r5_21))) >> 0x10);
                    temp_r5_22 = arg0->primTarget[3];
                    arg0->primColor[3] = (u8) ((s32) ((temp_r5_22 << 0x10) + (temp_r0_18 * (arg0->primColor[3] - temp_r5_22))) >> 0x10);
                }
                var_r30 = getTime(var_r30, &arg0->primCount);
                *(u32*)arg0->primTarget = (s32) *(u32*)arg0->primColor;
                if (temp_r26 & 1) {
                    temp_r0_19 = *var_r30;
                    var_r30 += 1;
                    arg0->primTarget[0] = temp_r0_19;
                }
                if (temp_r26 & 2) {
                    temp_r0_20 = *var_r30;
                    var_r30 += 1;
                    arg0->primTarget[1] = temp_r0_20;
                }
                if (temp_r26 & 4) {
                    temp_r0_21 = *var_r30;
                    var_r30 += 1;
                    arg0->primTarget[2] = temp_r0_21;
                }
                if (temp_r26 & 8) {
                    temp_r0_22 = *var_r30;
                    var_r30 += 1;
                    arg0->primTarget[3] = temp_r0_22;
                }
                temp_r0_23 = arg0->primCount;
                if (temp_r0_23 == 0) {
                    *(u32*)arg0->primColor = (s32) *(u32*)arg0->primTarget;
                    arg0->primRemain = 0;
                } else {
                    arg0->primRemain = temp_r0_23;
                }
                goto block_427;
            case 0xD0:                              /* switch 2 */
                temp_r4_28 = arg0->envCount;
                if (temp_r4_28 != 0) {
                    temp_r5_23 = arg0->envTarget[0];
                    temp_r0_24 = (s32) (arg0->envRemain << 0x10) / (s32) temp_r4_28;
                    arg0->envColor[0] = (u8) ((s32) ((temp_r5_23 << 0x10) + (temp_r0_24 * (arg0->envColor[0] - temp_r5_23))) >> 0x10);
                    temp_r5_24 = arg0->envTarget[1];
                    arg0->envColor[1] = (u8) ((s32) ((temp_r5_24 << 0x10) + (temp_r0_24 * (arg0->envColor[1] - temp_r5_24))) >> 0x10);
                    temp_r5_25 = arg0->envTarget[2];
                    arg0->envColor[2] = (u8) ((s32) ((temp_r5_25 << 0x10) + (temp_r0_24 * (arg0->envColor[2] - temp_r5_25))) >> 0x10);
                    temp_r5_26 = arg0->envTarget[3];
                    arg0->envColor[3] = (u8) ((s32) ((temp_r5_26 << 0x10) + (temp_r0_24 * (arg0->envColor[3] - temp_r5_26))) >> 0x10);
                }
                var_r30 = getTime(var_r30, &arg0->envCount);
                *(u32*)arg0->envTarget = (s32) *(u32*)arg0->envColor;
                if (temp_r26 & 1) {
                    temp_r0_25 = *var_r30;
                    var_r30 += 1;
                    arg0->envTarget[0] = temp_r0_25;
                }
                if (temp_r26 & 2) {
                    temp_r0_26 = *var_r30;
                    var_r30 += 1;
                    arg0->envTarget[1] = temp_r0_26;
                }
                if (temp_r26 & 4) {
                    temp_r0_27 = *var_r30;
                    var_r30 += 1;
                    arg0->envTarget[2] = temp_r0_27;
                }
                if (temp_r26 & 8) {
                    temp_r0_28 = *var_r30;
                    var_r30 += 1;
                    arg0->envTarget[3] = temp_r0_28;
                }
                temp_r0_29 = arg0->envCount;
                if (temp_r0_29 == 0) {
                    *(u32*)arg0->envColor = (s32) *(u32*)arg0->envTarget;
                    arg0->envRemain = 0;
                } else {
                    arg0->envRemain = temp_r0_29;
                }
                goto block_427;
            case 0xE0:                              /* switch 2 */
                temp_r4_29 = arg0->primCount;
                if (temp_r4_29 != 0) {
                    temp_r5_27 = arg0->primTarget[0];
                    temp_r0_30 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r4_29;
                    arg0->primColor[0] = (u8) ((s32) ((temp_r5_27 << 0x10) + (temp_r0_30 * (arg0->primColor[0] - temp_r5_27))) >> 0x10);
                    temp_r5_28 = arg0->primTarget[1];
                    arg0->primColor[1] = (u8) ((s32) ((temp_r5_28 << 0x10) + (temp_r0_30 * (arg0->primColor[1] - temp_r5_28))) >> 0x10);
                    temp_r5_29 = arg0->primTarget[2];
                    arg0->primColor[2] = (u8) ((s32) ((temp_r5_29 << 0x10) + (temp_r0_30 * (arg0->primColor[2] - temp_r5_29))) >> 0x10);
                    temp_r5_30 = arg0->primTarget[3];
                    arg0->primColor[3] = (u8) ((s32) ((temp_r5_30 << 0x10) + (temp_r0_30 * (arg0->primColor[3] - temp_r5_30))) >> 0x10);
                }
                temp_r4_30 = arg0->envCount;
                if (temp_r4_30 != 0) {
                    temp_r5_31 = arg0->envTarget[0];
                    temp_r0_31 = (s32) (arg0->envRemain << 0x10) / (s32) temp_r4_30;
                    arg0->envColor[0] = (u8) ((s32) ((temp_r5_31 << 0x10) + (temp_r0_31 * (arg0->envColor[0] - temp_r5_31))) >> 0x10);
                    temp_r5_32 = arg0->envTarget[1];
                    arg0->envColor[1] = (u8) ((s32) ((temp_r5_32 << 0x10) + (temp_r0_31 * (arg0->envColor[1] - temp_r5_32))) >> 0x10);
                    temp_r5_33 = arg0->envTarget[2];
                    arg0->envColor[2] = (u8) ((s32) ((temp_r5_33 << 0x10) + (temp_r0_31 * (arg0->envColor[2] - temp_r5_33))) >> 0x10);
                    temp_r5_34 = arg0->envTarget[3];
                    arg0->envColor[3] = (u8) ((s32) ((temp_r5_34 << 0x10) + (temp_r0_31 * (arg0->envColor[3] - temp_r5_34))) >> 0x10);
                }
                temp_f1_13 = (f32) ((s8) var_r30[0x0] * 2) * HSD_Randf();
                sp14 = temp_f1_13;
                arg0->primTarget[0] = U8ClampAdd(arg0->primTarget[0], temp_f1_13);
                arg0->envTarget[0] = U8ClampAdd(arg0->envTarget[0], temp_f1_13);
                temp_f1_14 = (f32) ((s8) var_r30[0x1] * 2) * HSD_Randf();
                sp14 = temp_f1_14;
                arg0->primTarget[1] = U8ClampAdd(arg0->primTarget[1], temp_f1_14);
                arg0->envTarget[1] = U8ClampAdd(arg0->envTarget[1], temp_f1_14);
                temp_f1_15 = (f32) ((s8) var_r30[0x2] * 2) * HSD_Randf();
                sp14 = temp_f1_15;
                arg0->primTarget[2] = U8ClampAdd(arg0->primTarget[2], temp_f1_15);
                arg0->envTarget[2] = U8ClampAdd(arg0->envTarget[2], temp_f1_15);
                temp_r3_44 = var_r30[0x3];
                var_r30 += 4;
                temp_f1_16 = (f32) ((s8) temp_r3_44 * 2) * HSD_Randf();
                sp14 = temp_f1_16;
                arg0->primTarget[3] = U8ClampAdd(arg0->primTarget[3], temp_f1_16);
                arg0->envTarget[3] = U8ClampAdd(arg0->envTarget[3], temp_f1_16);
                if ((u16) arg0->primCount == 0) {
                    *(u32*)arg0->primColor = (s32) *(u32*)arg0->primTarget;
                }
                arg0->primRemain = arg0->primCount;
                if ((u16) arg0->envCount == 0) {
                    *(u32*)arg0->envColor = (s32) *(u32*)arg0->envTarget;
                }
                arg0->envRemain = arg0->envCount;
                goto block_427;
            case 0xE9:                              /* switch 2 */
                temp_r4_31 = arg0->primCount;
                if (temp_r4_31 != 0) {
                    temp_r5_35 = arg0->primTarget[0];
                    temp_r0_32 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r4_31;
                    arg0->primColor[0] = (u8) ((s32) ((temp_r5_35 << 0x10) + (temp_r0_32 * (arg0->primColor[0] - temp_r5_35))) >> 0x10);
                    temp_r5_36 = arg0->primTarget[1];
                    arg0->primColor[1] = (u8) ((s32) ((temp_r5_36 << 0x10) + (temp_r0_32 * (arg0->primColor[1] - temp_r5_36))) >> 0x10);
                    temp_r5_37 = arg0->primTarget[2];
                    arg0->primColor[2] = (u8) ((s32) ((temp_r5_37 << 0x10) + (temp_r0_32 * (arg0->primColor[2] - temp_r5_37))) >> 0x10);
                    temp_r5_38 = arg0->primTarget[3];
                    arg0->primColor[3] = (u8) ((s32) ((temp_r5_38 << 0x10) + (temp_r0_32 * (arg0->primColor[3] - temp_r5_38))) >> 0x10);
                }
                temp_r4_32 = arg0->envCount;
                if (temp_r4_32 != 0) {
                    temp_r5_39 = arg0->envTarget[0];
                    temp_r0_33 = (s32) (arg0->envRemain << 0x10) / (s32) temp_r4_32;
                    arg0->envColor[0] = (u8) ((s32) ((temp_r5_39 << 0x10) + (temp_r0_33 * (arg0->envColor[0] - temp_r5_39))) >> 0x10);
                    temp_r5_40 = arg0->envTarget[1];
                    arg0->envColor[1] = (u8) ((s32) ((temp_r5_40 << 0x10) + (temp_r0_33 * (arg0->envColor[1] - temp_r5_40))) >> 0x10);
                    temp_r5_41 = arg0->envTarget[2];
                    arg0->envColor[2] = (u8) ((s32) ((temp_r5_41 << 0x10) + (temp_r0_33 * (arg0->envColor[2] - temp_r5_41))) >> 0x10);
                    temp_r5_42 = arg0->envTarget[3];
                    arg0->envColor[3] = (u8) ((s32) ((temp_r5_42 << 0x10) + (temp_r0_33 * (arg0->envColor[3] - temp_r5_42))) >> 0x10);
                }
                temp_r27_5 = var_r30[0x1];
                temp_r26_8 = var_r30[0x0];
                var_r30 += 2;
                if ((s32) temp_r27_5 != 0) {
                    var_f1 = (f32) (s32) ((f32) (temp_r27_5 + 1) * HSD_Randf()) / (f32) temp_r27_5;
                } else {
                    var_f1 = HSD_Randf();
                }
                sp14 = var_f1;
                if (temp_r26_8 & 1) {
                    temp_r3_45 = (s8) *var_r30 * 2;
                    var_r30 += 1;
                    temp_f1_17 = (f32) var_f1 * (f32) temp_r3_45;
                    sp10 = temp_f1_17;
                    if (temp_r26_8 & 0x10) {
                        arg0->primTarget[0] = U8ClampAdd(arg0->primTarget[0], temp_f1_17);
                    }
                    if (temp_r26_8 & 0x20) {
                        arg0->envTarget[0] = U8ClampAdd(arg0->envTarget[0], sp10);
                    }
                }
                if (temp_r26_8 & 2) {
                    temp_r3_46 = (s8) *var_r30 * 2;
                    var_r30 += 1;
                    temp_f1_18 = sp14 * (f32) temp_r3_46;
                    sp10 = temp_f1_18;
                    if (temp_r26_8 & 0x10) {
                        arg0->primTarget[1] = U8ClampAdd(arg0->primTarget[1], temp_f1_18);
                    }
                    if (temp_r26_8 & 0x20) {
                        arg0->envTarget[1] = U8ClampAdd(arg0->envTarget[1], sp10);
                    }
                }
                if (temp_r26_8 & 4) {
                    temp_r3_47 = (s8) *var_r30 * 2;
                    var_r30 += 1;
                    temp_f1_19 = sp14 * (f32) temp_r3_47;
                    sp10 = temp_f1_19;
                    if (temp_r26_8 & 0x10) {
                        arg0->primTarget[2] = U8ClampAdd(arg0->primTarget[2], temp_f1_19);
                    }
                    if (temp_r26_8 & 0x20) {
                        arg0->envTarget[2] = U8ClampAdd(arg0->envTarget[2], sp10);
                    }
                }
                if (temp_r26_8 & 8) {
                    if ((s32) temp_r27_5 != 0) {
                        temp_r3_48 = (s8) *var_r30 * 2;
                        var_r30 += 1;
                        var_f0 = ((f32) temp_r3_48 * (f32) (s32) ((f32) (temp_r27_5 + 1) * HSD_Randf())) / (f32) temp_r27_5;
                    } else {
                        temp_r3_49 = *var_r30;
                        var_r30 += 1;
                        var_f0 = (f32) ((s8) temp_r3_49 * 2) * HSD_Randf();
                    }
                    sp14 = var_f0;
                    if (temp_r26_8 & 0x10) {
                        arg0->primTarget[3] = U8ClampAdd(arg0->primTarget[3], (f32) var_f0);
                    }
                    if (temp_r26_8 & 0x20) {
                        arg0->envTarget[3] = U8ClampAdd(arg0->envTarget[3], sp14);
                    }
                }
                if ((u16) arg0->primCount == 0) {
                    *(u32*)arg0->primColor = (s32) *(u32*)arg0->primTarget;
                }
                arg0->primRemain = arg0->primCount;
                if ((u16) arg0->envCount == 0) {
                    *(u32*)arg0->envColor = (s32) *(u32*)arg0->envTarget;
                }
                arg0->envRemain = arg0->envCount;
                goto block_427;
            case 0xE2:                              /* switch 2 */
                arg0->kind |= 8;
                goto block_427;
            case 0xE3:                              /* switch 2 */
                temp_r0_34 = var_r30[0x0];
                var_r30 += 1;
                arg0->palette = temp_r0_34;
                goto block_427;
            case 0xE4:                              /* switch 2 */
                temp_r0_35 = var_r30[0x0];
                var_r30 += 1;
                temp_r0_36 = temp_r0_35 & 3;
                switch (temp_r0_36) {               /* switch 3; irregular */
                case 0:                             /* switch 3 */
                    arg0->kind &= 0xFFFBFFFF;
                    break;
                case 1:                             /* switch 3 */
                    arg0->kind |= 0x40000;
                    break;
                case 2:                             /* switch 3 */
                    arg0->kind ^= 0x40000;
                    break;
                case 3:                             /* switch 3 */
                    if (HSD_Randf() < 0.5f) {
                        arg0->kind &= 0xFFFBFFFF;
                    } else {
                        arg0->kind |= 0x40000;
                    }
                    break;
                }
                goto block_427;
            case 0xE5:                              /* switch 2 */
                temp_r0_37 = var_r30[0x0];
                var_r30 += 1;
                temp_r0_38 = temp_r0_37 & 3;
                switch (temp_r0_38) {               /* switch 4; irregular */
                case 0:                             /* switch 4 */
                    arg0->kind &= 0xFFF7FFFF;
                    break;
                case 1:                             /* switch 4 */
                    arg0->kind |= 0x80000;
                    break;
                case 2:                             /* switch 4 */
                    arg0->kind ^= 0x80000;
                    break;
                case 3:                             /* switch 4 */
                    if (HSD_Randf() < 0.5f) {
                        arg0->kind &= 0xFFF7FFFF;
                    } else {
                        arg0->kind |= 0x80000;
                    }
                    break;
                }
                goto block_427;
            case 0xE6:                              /* switch 2 */
                arg0->kind |= 0x200000;
                goto block_427;
            case 0xE7:                              /* switch 2 */
                arg0->kind &= 0xFFDFFFFF;
                goto block_427;
            case 0xE8:                              /* switch 2 */
                var_r30 = getFloat(var_r30, &sp14);
                if (sp14 < 0.0f) {
                    arg0->kind &= 0xFFEFFFFF;
                } else {
                    arg0->kind |= 0x100000;
                    arg0->textureScale = sp14;
                }
                goto block_427;
            case 0xEA:                              /* switch 2 */
                temp_r4_33 = arg0->matCount;
                if (temp_r4_33 != 0) {
                    temp_r5_43 = arg0->matRGBTarget;
                    temp_r6_5 = (s32) (arg0->matRemain << 0x10) / (s32) temp_r4_33;
                    arg0->matRGB = (u8) ((s32) ((temp_r5_43 << 0x10) + (temp_r6_5 * (arg0->matRGB - temp_r5_43))) >> 0x10);
                    temp_r4_34 = arg0->matAlphaTarget;
                    arg0->matAlpha = (u8) ((s32) ((temp_r4_34 << 0x10) + (temp_r6_5 * (arg0->matAlpha - temp_r4_34))) >> 0x10);
                }
                temp_r3_50 = getTime(var_r30, &arg0->matCount);
                temp_r4_35 = *temp_r3_50;
                var_r30 = temp_r3_50 + 1;
                arg0->matRGBTarget = arg0->matRGB;
                if (temp_r4_35 & 1) {
                    temp_r0_39 = *var_r30;
                    var_r30 += 1;
                    arg0->matRGBTarget = temp_r0_39;
                }
                if (temp_r4_35 & 8) {
                    temp_r0_40 = *var_r30;
                    var_r30 += 1;
                    arg0->matAlphaTarget = temp_r0_40;
                }
                temp_r0_41 = arg0->matCount;
                if (temp_r0_41 == 0) {
                    arg0->matRGB = arg0->matRGBTarget;
                    arg0->matRemain = 0;
                } else {
                    arg0->matRemain = temp_r0_41;
                }
                goto block_427;
            case 0xEB:                              /* switch 2 */
                temp_r4_36 = arg0->ambCount;
                if (temp_r4_36 != 0) {
                    temp_r5_44 = arg0->ambRGBTarget;
                    temp_r6_6 = (s32) (arg0->ambRemain << 0x10) / (s32) temp_r4_36;
                    arg0->ambRGB = (u8) ((s32) ((temp_r5_44 << 0x10) + (temp_r6_6 * (arg0->ambRGB - temp_r5_44))) >> 0x10);
                    temp_r4_37 = arg0->ambAlphaTarget;
                    arg0->ambAlpha = (u8) ((s32) ((temp_r4_37 << 0x10) + (temp_r6_6 * (arg0->ambAlpha - temp_r4_37))) >> 0x10);
                }
                temp_r3_51 = getTime(var_r30, &arg0->ambCount);
                temp_r4_38 = *temp_r3_51;
                var_r30 = temp_r3_51 + 1;
                arg0->ambRGBTarget = arg0->ambRGB;
                if (temp_r4_38 & 1) {
                    temp_r0_42 = *var_r30;
                    var_r30 += 1;
                    arg0->ambRGBTarget = temp_r0_42;
                }
                if (temp_r4_38 & 8) {
                    temp_r0_43 = *var_r30;
                    var_r30 += 1;
                    arg0->ambAlphaTarget = temp_r0_43;
                }
                temp_r0_44 = arg0->ambCount;
                if (temp_r0_44 == 0) {
                    arg0->ambRGB = arg0->ambRGBTarget;
                    arg0->ambRemain = 0;
                } else {
                    arg0->ambRemain = temp_r0_44;
                }
                goto block_427;
            case 0xED:                              /* switch 2 */
                temp_r3_52 = getFloat(getFloat(var_r30, &sp14), &sp10);
                temp_r26_9 = *temp_r3_52;
                var_r30 = temp_r3_52 + 1;
                if ((s32) temp_r26_9 != 0) {
                    var_f0_2 = sp14 + ((sp10 * (f32) (s32) ((f32) (temp_r26_9 + 1) * HSD_Randf())) / (f32) temp_r26_9);
                } else {
                    var_f0_2 = (sp10 * HSD_Randf()) + sp14;
                }
                sp14 = var_f0_2;
                arg0->rotateTarget += (f32) var_f0_2;
                arg0->rotate += var_f0_2;
                goto block_427;
            case 0xF3:                              /* switch 2 */
                temp_r26_10 = var_r30[0x0];
                var_r30 = getTime(getFloat(getFloat(var_r30 + 1, &arg0->rotateTarget), &arg0->trail), &arg0->rotateCount);
                if ((u16) arg0->rotateCount != 0) {
                    if ((s32) temp_r26_10 == 0) {
                        arg0->rotateTarget = (f32) (((f64) arg0->trail * 0.5) + (f64) arg0->rotateTarget);
                    } else {
                        arg0->rotateTarget *= -1.0f;
                        arg0->rotateTarget = (f32) -(((f64) arg0->trail * 0.5) - (f64) arg0->rotateTarget);
                    }
                } else {
                    arg0->rotateTarget = 0.0f;
                    arg0->trail = 0.0f;
                }
                goto block_427;
            case 0xFA:                              /* switch 2 */
                temp_r0_45 = var_r30[0x0];
                var_r30 += 1;
                arg0->loopCount = temp_r0_45;
                arg0->loopPtr = var_r30 - arg0->commands;
                goto block_427;
            case 0xFB:                              /* switch 2 */
                temp_r3_53 = arg0->loopCount - 1;
                arg0->loopCount = temp_r3_53;
                if (temp_r3_53 != 0) {
                    var_r30 = &arg0->commands[arg0->loopPtr];
                }
                goto block_427;
            case 0xFC:                              /* switch 2 */
                arg0->markPtr = var_r30 - arg0->commands;
                goto block_427;
            case 0xFD:                              /* switch 2 */
                var_r30 = &arg0->commands[arg0->markPtr];
                goto block_427;
            case 0xFE:                              /* switch 2 */
            case 0xFF:                              /* switch 2 */
                arg0->life = 1;
                break;
            }
            arg0->commandPtr = var_r30 - arg0->commands;
            arg0->wait = var_r29;
        }
    }
    temp_r3_54 = arg0->life - 1;
    arg0->life = temp_r3_54;
    if (temp_r3_54 == 0) {
        temp_r4_39 = arg0->generator;
        if (temp_r4_39 != NULL) {
            temp_r4_39->children -= 1;
        }
        var_r26 = _psListGetNext(arg0);
        if (((PSAppSRT *) arg0->appsrt != NULL) && (psRemoveParticleAppSRT(arg0) == 0) && (arg1 == NULL) && (_psListGetFirst((s32) arg0->link) != var_r26)) {
            var_r26 = _psListGetFirst((s32) arg0->link);
        }
        psDeletePntJObjwithParticle(arg0);
        _psListDelete(arg0, arg1);
        return var_r26;
    }
    temp_r3_55 = arg0->kind;
    if (temp_r3_55 & 4) {
        temp_r26_11 = arg0->generator;
        temp_f28 = sinf(arg0->gravity);
        temp_f29 = sinf(arg0->friction);
        temp_f30 = cosf(arg0->gravity);
        temp_f31 = cosf(arg0->friction);
        arg0->velocity.z += temp_r26_11->param1;
        var_f27 = temp_r26_11->radius;
        if (var_f27 < 0.0) {
            var_f27 = -var_f27;
        }
        var_f1_2 = temp_r26_11->angle;
        if (var_f1_2 < 0.0) {
            var_f1_2 = -var_f1_2;
        }
        temp_f27 = (arg0->velocity.z * tanf(var_f1_2)) + var_f27;
        arg0->velocity.x += temp_r26_11->gravity;
        temp_f27_2 = temp_f27 * arg0->velocity.y;
        temp_f26 = temp_f27_2 * cosf(arg0->velocity.x);
        temp_f8 = arg0->velocity.z;
        temp_f7_2 = temp_f27_2 * sinf(arg0->velocity.x);
        temp_f6_2 = -temp_f26;
        temp_f2_5 = (temp_f29 * (temp_f6_2 * temp_f28)) + (temp_f7_2 * temp_f30);
        temp_f0_2 = temp_f7_2 * temp_f28;
        arg0->position.x = temp_r26_11->position.x + ((temp_f26 * temp_f31) + (temp_f8 * temp_f29));
        arg0->position.y = temp_r26_11->position.y + ((temp_f31 * (temp_f8 * temp_f28)) + temp_f2_5);
        arg0->position.z = temp_r26_11->position.z + ((temp_f31 * (temp_f8 * temp_f30)) + ((temp_f29 * (temp_f6_2 * temp_f30)) - temp_f0_2));
    } else {
        if (temp_r3_55 & 1) {
            arg0->velocity.y -= arg0->gravity;
        }
        if (arg0->kind & 2) {
            arg0->velocity.x *= arg0->friction;
            arg0->velocity.y *= arg0->friction;
            arg0->velocity.z *= arg0->friction;
        }
        arg0->position.x += arg0->velocity.x;
        arg0->position.y += arg0->velocity.y;
        arg0->position.z += arg0->velocity.z;
    }
    temp_r4_40 = arg0->kind;
    if (temp_r4_40 & 0x8000) {
        temp_r27_6 = (temp_r4_40 >> 0xAU) & 0x1C;
        if ((u32) psPointJObj[temp_r27_6 / 4] == 0U) {
            temp_r3_56 = HSD_JObjAlloc();
            if (temp_r3_56 != NULL) {
                psSetPointJObj(((temp_r4_40 >> 0xCU) & 7) + 1, (PSObject *) temp_r3_56);
                HSD_JObjUnref(temp_r3_56);
            }
        }
        temp_r3_57 = psPointJObj[temp_r27_6 / 4];
        if (temp_r3_57 != NULL) {
            HSD_JObjSetupMatrix(temp_r3_57);
            temp_r3_58 = psPointJObj[temp_r27_6 / 4];
            HSD_JObjAddTx(temp_r3_58, arg0->position.x - temp_r3_58->matrix[0][3]);
            temp_r3_59 = psPointJObj[temp_r27_6 / 4];
            HSD_JObjAddTy(temp_r3_59, arg0->position.y - temp_r3_59->matrix[1][3]);
            temp_r3_60 = psPointJObj[temp_r27_6 / 4];
            HSD_JObjAddTz(temp_r3_60, arg0->position.z - temp_r3_60->matrix[2][3]);
        }
    }
    return _psListGetNext(arg0);
}

void psInterpretParticles(u32 mask) {
    PSParticle *current, *last, *next, *result;
    s32 link;
    for (link = 0; link < 16; link++, mask >>= 1) {
        if (!(mask & 0x10000)) {
            last = NULL;
            current = _psListGetFirst(link);
            while (current != NULL) {
                next = current->next;
                result = psInterpretParticle0(current, last);
                if (next != NULL) {
                    if (current->next == next) {
                        last = current;
                    } else if (result != next) {
                        last = result;
                        while (last->next != next) {
                            if (last == NULL) __assert("psinterpret.c", 0x82E, "lastPP");
                            last = last->next;
                        }
                    }
                }
                current = next;
            }
        }
    }
}
