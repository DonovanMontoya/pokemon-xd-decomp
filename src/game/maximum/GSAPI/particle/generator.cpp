#include "game/maximum/GSAPI/particle/generator.h"
#define NULL ((void*)0)
#include "game/maximum/GSAPI/baselib/math_support.h"
f64 __fabs(f64);
PSGenerator *activeGenerator,*freeGenerator,*lastGP;
void* standbyGenerator;
PSCamera* psCamera;
void (*psExtExecGenFunc)(PSGenerator*,f32 (*)[4]);
void (*psExtCreateGenFunc)(PSGenerator*);
static u16 psIDNum = 0x100;
s32 psGeneratorGetCamera(PSGenerator *arg0) {
    return arg0->camera;
}

void psGeneratorSetCamera(PSGenerator *arg0, s32 arg1) {
    arg0->camera = arg1;
}

static inline int psRefDec(PSCamera *o) {
    int ret;
    if ((ret = (o->references == 0xFFFF))) {
        return ret;
    }
    return o->references-- == 0;
}

static inline void psCameraUnref(PSCamera *cam) {
    if (cam != NULL) {
        if (cam != NULL && psRefDec(cam)) {
            if (cam != NULL) {
                cam->methods->release((PSObject *) cam, cam->methods);
                cam->methods->destroy((PSObject *) cam, cam->methods);
            }
        }
    }
}

static inline void psKillGenNode(PSGenerator *arg0) {
    PSAppSRT *temp_r3;
    PSGenerator *var_r30;

    var_r30 = lastGP;
    if (arg0->type & 0x80) {
        psKillGeneratorChild(arg0);
    }
    if ((u32) arg0->children != 0) {
        var_r30 = arg0;
        arg0->random = 0.0f;
        arg0->life = 1;
    } else if ((arg0->type & 0x3800) && (temp_r3 = arg0->appsrt, temp_r3 != NULL) && ((PSGenerator *) temp_r3->generator == arg0) && ((u16) temp_r3->references != 1)) {
        var_r30 = arg0;
        arg0->random = 0.0f;
        arg0->life = 1;
    } else {
        if (var_r30 == NULL) {
            activeGenerator = arg0->next;
        } else {
            var_r30->next = arg0->next;
        }
        if ((PSAppSRT *) arg0->appsrt != NULL) {
            psRemoveGeneratorAppSRT(arg0);
        }
        arg0->next = freeGenerator;
        freeGenerator = arg0;
        numActiveGenerators -= 1;
    }
    lastGP = var_r30;
}

static inline void psKillGeneratorSub(PSGenerator *arg0) {
    PSGenerator *temp_r0;
    PSGenerator *var_r4;

    var_r4 = activeGenerator;
    lastGP = NULL;
    while (var_r4 != NULL) {
        if (var_r4 == arg0) {
            psKillGenNode(arg0);
            if (lastGP != NULL) {
                while ((temp_r0 = lastGP->next) != NULL) {
                    lastGP = temp_r0;
                }
            } else if ((temp_r0 = activeGenerator) != NULL) {
                lastGP = temp_r0;
                while ((temp_r0 = lastGP->next) != NULL) {
                    lastGP = temp_r0;
                }
            }
            return;
        }
        lastGP = var_r4;
        var_r4 = var_r4->next;
    }
}

void psKillAllGenerator(void) {
    PSGenerator *cur;
    PSGenerator *next;

    cur = activeGenerator;
    while (cur != NULL) {
        next = cur->next;
        psKillGeneratorSub(cur);
        cur = next;
    }
    while ((void *) standbyGenerator != NULL) {
        standbyGenerator = HSD_SListRemove(standbyGenerator);
    }
}

void psKillGeneratorID(u16 arg0) {
    PSAppSRT *temp_r3;
    PSGenerator *var_r30;
    PSGenerator *var_r29;
    PSGenerator *temp_r28;

    var_r29 = activeGenerator;
    lastGP = NULL;
while (var_r29 != NULL) {
        temp_r28 = var_r29->next;
        if ((u16) var_r29->id == arg0) {
            var_r30 = lastGP;
            if (var_r29->type & 0x80) {
                psKillGeneratorChild(var_r29);
            }
            if ((u32) var_r29->children != 0) {
                var_r30 = var_r29;
                var_r29->random = 0.0f;
                var_r29->life = 1;
            } else if ((var_r29->type & 0x3800) && (temp_r3 = var_r29->appsrt, ((temp_r3 == NULL) == 0)) && ((PSGenerator *) temp_r3->generator == var_r29) && ((u16) temp_r3->references != 1)) {
                var_r30 = var_r29;
                var_r29->random = 0.0f;
                var_r29->life = 1;
            } else {
                if (var_r30 == NULL) {
                    activeGenerator = var_r29->next;
                } else {
                    var_r30->next = var_r29->next;
                }
                if ((PSAppSRT *) var_r29->appsrt != NULL) {
                    psRemoveGeneratorAppSRT(var_r29);
                }
                var_r29->next = freeGenerator;
                freeGenerator = var_r29;
                numActiveGenerators -= 1;
            }
            lastGP = var_r30;
        } else {
            lastGP = var_r29;
        }
        var_r29 = temp_r28;
}
}

void psKillGenerator(PSGenerator *arg0) {
    PSGenerator *temp_r0;
    PSGenerator *var_r4;

    var_r4 = activeGenerator;
    lastGP = NULL;
    while (var_r4 != NULL) {
        if (var_r4 == arg0) {
            psKillGenNode(arg0);
            if (lastGP != NULL) {
                while ((temp_r0 = lastGP->next) != NULL) {
                    lastGP = temp_r0;
                }
            } else if ((temp_r0 = activeGenerator) != NULL) {
                lastGP = temp_r0;
                while ((temp_r0 = lastGP->next) != NULL) {
                    lastGP = temp_r0;
                }
            }
            return;
        }
        lastGP = var_r4;
        var_r4 = var_r4->next;
    }
}

void psInitGenerator(s32 count) {
    PSGenerator* gp; s32 i;
    activeGenerator = NULL; freeGenerator = NULL;
    for (i = count - 1; i >= 0; i--) {
        gp = HSD_Alloc(0xB8); memset(gp, 0, 0xB8);
        if (gp == NULL) return;
        gp->next = freeGenerator; freeGenerator = gp;
    }
    numActiveGenerators = 0; numPeakGenerators = 0;
    standbyGenerator = NULL; psCamera = NULL; psExtExecGenFunc = NULL; psExtCreateGenFunc = NULL; lastGP = NULL;
}

void genPosUpdate(PSGenerator *arg0) {
    PSJObj *temp_r31;
    s32 temp_cr0_eq;
    s32 var_r3;
    u16 temp_r3;
    u32 temp_r4;

    if (arg0 != NULL) {
        temp_r3 = arg0->transformFlags;
        if (!(temp_r3 & 2) && (temp_r3 & 1)) {
            temp_r31 = arg0->jobj;

            if (temp_r31 != NULL) {
                if (temp_r31 != NULL) {
                    if (temp_r31 == NULL) {
                        __assert("jobj.h", 0x25D, "jobj");
                    }
                    temp_r4 = temp_r31->flags;
                    var_r3 = 0;
                    if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                        var_r3 = 1;
                    }
                    if (var_r3 != 0) {
                        HSD_JObjSetupMatrixSub(temp_r31);
                    }
                }
                arg0->position.x = arg0->jobj->matrix[0][3];
                arg0->position.y = arg0->jobj->matrix[1][3];
                arg0->position.z = arg0->jobj->matrix[2][3];
            }
        }
    }
}

u16 psGetNewIDNum(void) {
    if (++psIDNum < 0x100) psIDNum = 0x100;
    return psIDNum;
}


void psSetBillboardCamera(PSCamera *arg0) {
    if (arg0 != psCamera) {
        psCameraUnref(psCamera);
        if (arg0 != NULL) {
            if (arg0 != NULL) {
                arg0->references++;
                if (arg0->references == 0xFFFF) {
                    __assert("object.h", 0x5D, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
                }
            }
        }
        psCamera = arg0;
    }
}

void psExecGenerator(s32 arg0) {
    PSGenerator *var_r31;
    PSJObj *temp_r29;
    f32 temp_f1;
    s32 temp_cr0_eq;
    s32 var_r3;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 temp_r3_3;
    u32 temp_r4;

while ((void *) standbyGenerator != NULL) {
        standbyGenerator = HSD_SListRemove(standbyGenerator);

}
    var_r31 = activeGenerator;
    lastGP = NULL;
while (var_r31 != NULL) {
        if (arg0 & (1 << (var_r31->link + 0x10))) {
            lastGP = var_r31;
            var_r31 = var_r31->next;
        } else if (var_r31->kind & 0x800) {
            lastGP = var_r31;
            var_r31 = var_r31->next;
        } else {
            if (var_r31 != NULL) {
                temp_r3 = var_r31->transformFlags;
                if (!(temp_r3 & 2) && (temp_r3 & 1)) {
                    temp_r29 = var_r31->jobj;
                    /* null checks below retain the original nested guards */
                    if (temp_r29 != NULL) {
                        if (temp_r29 != NULL) {
                            if (temp_r29 == NULL) {
                                __assert("jobj.h", 0x25D, "jobj");
                            }
                            temp_r4 = temp_r29->flags;
                            var_r3 = 0;
                            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                                var_r3 = 1;
                            }
                            if (var_r3 != 0) {
                                HSD_JObjSetupMatrixSub(temp_r29);
                            }
                        }
                        var_r31->position.x = var_r31->jobj->matrix[0][3];
                        var_r31->position.y = var_r31->jobj->matrix[1][3];
                        var_r31->position.z = var_r31->jobj->matrix[2][3];
                    }
                }
            }
            temp_f1 = var_r31->random;
            if (temp_f1 < 0.0f) {
                var_r31->count -= temp_f1;
            } else {
                var_r31->count += var_r31->random * HSD_Randf();
            }
            if (var_r31->count >= 1.0f) {
                var_r31->count = generateParticle(var_r31);
            }
            if (var_r31->life != 0 && --var_r31->life == 0) {
                if ((u8) var_r31->state == 0) {
                    psKillGenNode(var_r31);
                } else {
                    var_r31->kind |= 0x800;
                }
                if ((PSGenerator *) lastGP != NULL) {
                    var_r31 = lastGP->next;
                } else {
                    var_r31 = activeGenerator;
                }
            } else {
                lastGP = var_r31;
                var_r31 = var_r31->next;
            }
        }
}
}

void psRemoveGenerator(void) {
    PSGenerator *next;
    PSGenerator *cur;
    PSGenerator *free_cur;

    psKillAllParticle();
    cur = activeGenerator;
    while (cur != NULL) {
        next = cur->next;
        psKillGeneratorSub(cur);
        cur = next;
    }
    while ((void *) standbyGenerator != NULL) {
        standbyGenerator = HSD_SListRemove(standbyGenerator);
    }
    free_cur = freeGenerator;
    while (free_cur != NULL) {
        next = free_cur->next;
        HSD_Free(free_cur);
        free_cur = next;
    }
    freeGenerator = NULL;
    if (psCamera != NULL) {
        psCameraUnref(psCamera);
        psCamera = NULL;
    }
}

static inline PSGenerator *psAllocGenerator(void) {
    PSGenerator *gen;
    PSGenerator *temp_r3;
    PSGenerator *temp_r3_3;

    if (freeGenerator == NULL) {
        temp_r3 = (PSGenerator *) HSD_Alloc(0xB8U);
        freeGenerator = temp_r3;
        memset(temp_r3, 0, 0xB8U);
    }
    gen = freeGenerator;
    if (gen == NULL) {
        gen = NULL;
    } else {
        numActiveGenerators++;
        if (numActiveGenerators > numPeakGenerators) {
            numPeakGenerators = numActiveGenerators;
        }
        freeGenerator = gen->next;
        if ((lastGP == NULL) || (temp_r3_3 = lastGP->next, temp_r3_3 == NULL)) {
            if (activeGenerator == NULL) {
                gen->next = NULL;
                activeGenerator = gen;
            } else {
                gen->next = activeGenerator->next;
                activeGenerator->next = gen;
            }
        } else {
            gen->next = temp_r3_3->next;
            lastGP->next->next = gen;
        }
        if (++psIDNum < 0x100U) {
            psIDNum = 0x100;
        }
        gen->id = psIDNum;
        gen->appsrt = NULL;
        gen->state = 0;
    }
    return gen;
}

PSGenerator *psCreateGeneratorID(s32 arg0, s32 arg1, s32 arg2) {
    f32 spC;
    f32 sp8;
    PSAppSRT *temp_r3_10;
    PSCmd *temp_r3_6;
    PSCmd *temp_r3_7;
    PSGenerator *temp_r3;
    PSGenerator *temp_r3_3;
    PSGenerator *var_r29;
    PSTex *temp_r3_5;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f1;
    f32 temp_f1_5;
    f32 temp_f1_9;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f3;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f4;
    f64 temp_f1_2;
    f64 temp_f1_3;
    f64 temp_f1_4;
    f64 temp_f1_6;
    f64 temp_f1_7;
    f64 temp_f1_8;
    s32 temp_r3_8;
    s32 temp_r3_9;
    s32 var_r0;
    s32 var_r0_2;
    u16 temp_r3_2;
    u16 temp_r3_4;
    u32 temp_r0;

    if (arg1 >= 0x40) {
        return NULL;
    }
    if (arg0 >= 8) {
        return NULL;
    }
    if (arg2 >= (s32) psNumCmdList[arg1]) {
        return NULL;
    }
    if ((PSCmd *) psCmdListArray[arg1][arg2] == NULL) {
        return NULL;
    }
    var_r29 = psAllocGenerator();
    if (var_r29 != NULL) {
        var_r29->type = psCmdListArray[arg1][arg2]->type;
        var_r29->bank = (u8) arg1;
        var_r29->link = (u8) arg0;
        var_r29->commandID = (u16) arg2;
        var_r29->camera = 0;
        var_r29->kind = psCmdListArray[arg1][arg2]->kind;
        var_r29->texGroup = (u8) psCmdListArray[arg1][arg2]->texGroup;
        var_r29->particleLife = psCmdListArray[arg1][arg2]->life;
        var_r29->life = psCmdListArray[arg1][arg2]->genLife;
        var_r29->position.z = 0.0f;
        var_r29->position.y = 0.0f;
        var_r29->position.x = 0.0f;
        var_r29->velocity.x = psCmdListArray[arg1][arg2]->velocity.x;
        var_r29->velocity.y = psCmdListArray[arg1][arg2]->velocity.y;
        var_r29->velocity.z = psCmdListArray[arg1][arg2]->velocity.z;
        var_r29->gravity = psCmdListArray[arg1][arg2]->gravity;
        var_r29->friction = psCmdListArray[arg1][arg2]->friction;
        var_r29->size = psCmdListArray[arg1][arg2]->size;
        var_r29->commands = psCmdListArray[arg1][arg2]->commands;
        var_r29->radius = psCmdListArray[arg1][arg2]->radius;
        var_r29->angle = psCmdListArray[arg1][arg2]->angle;
        var_r29->random = psCmdListArray[arg1][arg2]->random;
        if (var_r29->kind & 0x100) {
            temp_f0 = var_r29->random;
            if (temp_f0 < 0.0f) {
                var_f2 = (1.0f + temp_f0) > __float_epsilon[0] ? 1.0f : 0.0f;
                var_r29->count = var_f2;
            } else {
                var_r29->count = 1.0f - __float_epsilon[0];
            }
        } else if (var_r29->random < 0.0f) {
            var_r29->count = 0.0f;
        } else {
            var_r29->count = HSD_Randf();
        }
        temp_r3_5 = psTexGroupArray[arg1][var_r29->texGroup];
        if ((temp_r3_5 != NULL) && ((u16) temp_r3_5->paletteFlags != 0)) {
            var_r29->kind |= 0x10;
        }
        var_r29->children = 0;
        temp_r0 = var_r29->type & 0xF;
        switch (temp_r0) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
        case 3:                                     /* switch 1 */
        case 4:                                     /* switch 1 */
            temp_r3_6 = psCmdListArray[arg1][arg2];
            temp_f2 = temp_r3_6->param1;
            if ((temp_f2 == 0.0f) && (temp_r3_6->param2 == 0.0f)) {
                var_r29->param1 = 0.0f;
                var_r29->param2 = 6.2831855f;
            } else {
                var_r29->param1 = temp_f2;
                var_r29->param2 = psCmdListArray[arg1][arg2]->param2;
            }
            break;
        case 1:                                     /* switch 1 */
            var_r29->param1 = psCmdListArray[arg1][arg2]->param1;
            var_r29->param2 = psCmdListArray[arg1][arg2]->param2;
            var_r29->param3 = psCmdListArray[arg1][arg2]->param3;
            break;
        case 6:                                     /* switch 1 */
        case 7:                                     /* switch 1 */
            temp_r3_7 = psCmdListArray[arg1][arg2];
            temp_f2_2 = temp_r3_7->param1;
            if ((temp_f2_2 == 0.0f) && (temp_r3_7->param2 == 0.0f)) {
                var_r29->param1 = 0.0f;
                var_r29->param2 = 6.2831855f;
            } else {
                var_r29->param1 = temp_f2_2;
                var_r29->param2 = psCmdListArray[arg1][arg2]->param2;
            }
            var_r29->param3 = psCmdListArray[arg1][arg2]->param3;
            break;
        case 5:                                     /* switch 1 */
            temp_f0_2 = psCmdListArray[arg1][arg2]->param1;
            var_r29->param1 = temp_f0_2;
            var_r29->axisXX = temp_f0_2;
            temp_f0_3 = psCmdListArray[arg1][arg2]->param2;
            var_r29->param2 = temp_f0_3;
            var_r29->axisYY = temp_f0_3;
            temp_f0_4 = psCmdListArray[arg1][arg2]->param3;
            var_r29->param3 = temp_f0_4;
            var_r29->axisZZ = temp_f0_4;
            var_r29->axisZY = 0.0f;
            var_r29->axisZX = 0.0f;
            var_r29->axisYZ = 0.0f;
            var_r29->axisYX = 0.0f;
            var_r29->axisXZ = 0.0f;
            var_r29->axisXY = 0.0f;
            var_r29->edgeFlags = 0;
            if (psCmdListArray[arg1][arg2]->param1 < 0.0f) {
                var_r29->edgeFlags |= 1;
            }
            if (psCmdListArray[arg1][arg2]->param2 < 0.0f) {
                var_r29->edgeFlags |= 2;
            }
            if (psCmdListArray[arg1][arg2]->param3 < 0.0f) {
                var_r29->edgeFlags |= 4;
            }
            break;
        case 8:                                     /* switch 1 */
            var_f4 = hsdSqrt(var_r29->velocity.x * var_r29->velocity.x + var_r29->velocity.y * var_r29->velocity.y + var_r29->velocity.z * var_r29->velocity.z);
            var_r29->param1 = var_f4;
            var_f2_2 = hsdSqrt(var_r29->velocity.x * var_r29->velocity.x + var_r29->velocity.z * var_r29->velocity.z);
            if (var_f2_2 < __float_min[0]) {
                if (var_r29->velocity.y >= 0.0f) {
                    var_r29->param2 = 1.5707964f;
                } else {
                    var_r29->param2 = -1.5707964f;
                }
            } else {
                var_r29->param2 = (f32) atan2((f64) var_r29->velocity.y, (f64) var_f2_2);
            }
            temp_f2_4 = var_r29->velocity.x;
            if (__fabs(temp_f2_4) < __float_min[0]) {
                if (var_r29->velocity.z >= 0.0f) {
                    var_r29->axisXX = 1.5707964f;
                } else {
                    var_r29->axisXX = -1.5707964f;
                }
            } else {
                var_r29->axisXX = (f32) atan2((f64) var_r29->velocity.z, (f64) temp_f2_4);
            }
            var_r29->param3 = psCmdListArray[arg1][arg2]->param1;
            temp_f1_9 = var_r29->param3;
            if (temp_f1_9 < 0.0f) {
                var_r29->param3 = -temp_f1_9;
                var_r29->param1 = -var_r29->param1;
            }
            var_r29->axisXY = psCmdListArray[arg1][arg2]->param2;
            break;
        case 2:
            break;
        default:                                    /* switch 1 */
            if (((void (*)(PSGenerator *)) psExtCreateGenFunc) != NULL) {
                psExtCreateGenFunc(var_r29);
            }
            break;
        }
        if (var_r29->kind & 0x20000) {
            var_r29->type |= 0x800;
            psAddGeneratorAppSRT(var_r29, 0);
            temp_r3_10 = var_r29->appsrt;
            if (temp_r3_10 != NULL) {
                temp_r3_10->generatorOwned = 1;
                var_r29->appsrt->generator = var_r29;
            }
        }
        var_r29->transformFlags = 2;
        var_r29->jobj = NULL;
        var_r29->rotation.z = 0.0f;
        var_r29->rotation.y = 0.0f;
        var_r29->rotation.x = 0.0f;
        var_r29->scale.z = 1.0f;
        var_r29->scale.y = 1.0f;
        var_r29->scale.x = 1.0f;
        var_r29->nodeScale.z = 1.0f;
        var_r29->nodeScale.y = 1.0f;
        var_r29->nodeScale.x = 1.0f;
    }
    return var_r29;
}

f32 generateParticle(PSGenerator *arg0) {
    f32 sp8;
    f32 bits10;
    f32 bits14;
    f32 bits18;
    PSVec direction;
    PSVec cameraRight;
    PSVec cameraUp;
    PSVec cameraForward;
    PSVec velocity;
    PSVec offset;
    PSVec position;
    PSVec baseVelocity;
    f32 directionMatrix[3][4];
    f32 rotationZ[3][4];
    f32 rotationY[3][4];
    f32 rotationX[3][4];
    f32 transform[3][4];
    PSGenerator *spC;
    PSWObj *temp_r5;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f19;
    f32 temp_f1;
    f32 temp_f1_11;
    f32 temp_f1_12;
    f32 temp_f1_13;
    f32 temp_f1_14;
    f32 temp_f1_15;
    f32 temp_f1_16;
    f32 temp_f1_17;
    f32 temp_f1_21;
    f32 temp_f1_22;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_7;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f20_4;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f21_3;
    f32 temp_f21_4;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f2_10;
    f32 temp_f2_11;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f2_8;
    f32 temp_f2_9;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f5_3;
    f32 temp_f5_4;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 var_f0;
    f32 var_f0_10;
    f32 var_f0_11;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f0_5;
    f32 var_f0_6;
    f32 var_f0_7;
    f32 var_f0_8;
    f32 var_f0_9;
    f32 var_f1;
    f32 var_f20;
    f32 var_f20_2;
    f32 var_f21;
    f32 var_f21_2;
    f32 var_f22;
    f32 var_f22_2;
    f32 var_f23;
    f32 var_f25;
    f32 var_f27;
    f32 var_f30;
    f32 var_f31;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f4_3;
    f64 temp_f1_10;
    f64 temp_f1_18;
    f64 temp_f1_19;
    f64 temp_f1_20;
    f64 temp_f1_4;
    f64 temp_f1_5;
    f64 temp_f1_6;
    f64 temp_f1_8;
    f64 temp_f1_9;
    s32 temp_r0;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    u16 temp_r0_6;
    u32 temp_r0_2;

    var_f25 = 0.0f;
    temp_f1_2 = arg0->count;
    var_f23 = 0.0f;
    if (temp_f1_2 < 1.0f) {
        return temp_f1_2;
    }
    temp_f2 = arg0->velocity.x;
    baseVelocity.x = temp_f2;
    temp_f1_3 = arg0->velocity.y;
    baseVelocity.y = temp_f1_3;
    temp_f0 = arg0->velocity.z;
    baseVelocity.z = temp_f0;
    temp_f26 = arg0->scale.x;
    temp_f29 = arg0->scale.y;
    temp_f28 = arg0->scale.z;
    if (((s32) (arg0->type & 0xF) == 2) && (arg0->transformFlags & 0x80)) {
        baseVelocity.x = temp_f2 * temp_f26;
        baseVelocity.y = temp_f1_3 * temp_f29;
        baseVelocity.z = temp_f0 * temp_f28;
    }
    var_f27 = (baseVelocity.z * baseVelocity.z) + ((baseVelocity.x * baseVelocity.x) + (baseVelocity.y * baseVelocity.y));
    if (var_f27 > 0.0f) {
        temp_f1_4 = __frsqrte(var_f27);
        temp_f1_5 = 0.5 * temp_f1_4 * -(((f64) var_f27 * (temp_f1_4 * temp_f1_4)) - 3.0);
        temp_f1_6 = 0.5 * temp_f1_5 * -(((f64) var_f27 * (temp_f1_5 * temp_f1_5)) - 3.0);
        var_f27 = (f32) ((f64) var_f27 * (0.5 * temp_f1_6 * -(((f64) var_f27 * (temp_f1_6 * temp_f1_6)) - 3.0)));
    } else if (var_f27 < 0.0) {
        var_f27 = __float_nan[0];
    } else {
        bits18 = var_f27;
        temp_r3 = *(s32*)&bits18 & 0x7F800000;
        switch (temp_r3) {                          /* switch 1; irregular */
        case 0x7F800000:                            /* switch 1 */
            if (*(s32*)&bits18 & 0x7FFFFF) {
                var_r0 = 1;
            } else {
                var_r0 = 2;
            }
            break;
        case 0x0:                                   /* switch 1 */
            if (*(s32*)&bits18 & 0x7FFFFF) {
                var_r0 = 5;
            } else {
                var_r0 = 3;
            }
            break;
        default:                                    /* switch 1 */
            var_r0 = 4;
            break;
        }
        if (var_r0 == 1) {
            var_f27 = __float_nan[0];
        }
    }
    PSMTXIdentity((f32 (*)[4]) &transform[0][0]);
    if (!(arg0->kind & 0x30000)) {
        PSMTXRotRad((f32 (*)[4]) &rotationX[0][0], 0x58, arg0->rotation.x);
        PSMTXRotRad((f32 (*)[4]) &rotationY[0][0], 0x59, arg0->rotation.y);
        PSMTXRotRad((f32 (*)[4]) &rotationZ[0][0], 0x5A, arg0->rotation.z);
        PSMTXConcat((f32 (*)[4]) &rotationY[0][0], (f32 (*)[4]) &rotationX[0][0], (f32 (*)[4]) &rotationX[0][0]);
        PSMTXConcat((f32 (*)[4]) &rotationZ[0][0], (f32 (*)[4]) &rotationX[0][0], (f32 (*)[4]) &rotationX[0][0]);
        velocity.x = rotationX[0][0];
        velocity.y = rotationX[1][0];
        velocity.z = rotationX[2][0];
        PSVECNormalize((PSVec *) &velocity.x, (PSVec *) &velocity.x);
        transform[0][0] = velocity.x;
        transform[1][0] = velocity.y;
        transform[2][0] = velocity.z;
        velocity.x = rotationX[0][1];
        velocity.y = rotationX[1][1];
        velocity.z = rotationX[2][1];
        PSVECNormalize((PSVec *) &velocity.x, (PSVec *) &velocity.x);
        transform[0][1] = velocity.x;
        transform[1][1] = velocity.y;
        transform[2][1] = velocity.z;
        velocity.x = rotationX[0][2];
        velocity.y = rotationX[1][2];
        velocity.z = rotationX[2][2];
        PSVECNormalize((PSVec *) &velocity.x, (PSVec *) &velocity.x);
        transform[0][2] = velocity.x;
        transform[1][2] = velocity.y;
        transform[2][2] = velocity.z;
        transform[2][3] = 0.0f;
        transform[1][3] = 0.0f;
        transform[0][3] = 0.0f;
    }
    if (arg0->kind & 0x10000) {
        if ((PSCamera *) psCamera == NULL) {
            __assert("generator.c", 0x272, "psCamera");
        }
        temp_r5 = psCamera->eye;
        cameraForward.x = temp_r5->position.x - arg0->position.x;
        cameraForward.y = temp_r5->position.y - arg0->position.y;
        cameraForward.z = temp_r5->position.z - arg0->position.z;
        PSVECNormalize((PSVec *) &cameraForward.x, (PSVec *) &cameraForward.x);
        HSD_CObjGetUpVector(psCamera, &cameraUp);
        PSVECNormalize(&cameraUp, &cameraUp);
        PSVECCrossProduct(&cameraUp, (PSVec *) &cameraForward.x, &cameraRight);
        PSVECCrossProduct((PSVec *) &cameraForward.x, &cameraRight, &cameraUp);
        transform[0][0] = cameraRight.x;
        transform[1][0] = cameraRight.y;
        transform[2][0] = cameraRight.z;
        transform[0][1] = cameraUp.x;
        transform[1][1] = cameraUp.y;
        transform[2][1] = cameraUp.z;
        transform[0][2] = cameraForward.x;
        transform[1][2] = cameraForward.y;
        transform[2][2] = cameraForward.z;
    }
    if (((s32) (arg0->type & 0xF) != 1) && (var_f27 > __float_epsilon[0])) {
        direction.x = arg0->velocity.x;
        direction.y = arg0->velocity.y;
        direction.z = arg0->velocity.z;
        PSVECNormalize((PSVec *) &direction.x, (PSVec *) &direction.x);
        if (__fabs(direction.z) < __float_min[0]) {
            if (direction.y >= 0.0f) {
                var_f20 = 1.5707964f;
            } else {
                var_f20 = -1.5707964f;
            }
        } else {
            var_f20 = (f32) atan2((f64) direction.y, (f64) direction.z);
        }
        temp_f22 = (f32) sin((f64) var_f20);
        temp_f24 = (f32) cos((f64) var_f20);
        temp_f2_2 = (direction.y * temp_f22) + (direction.z * temp_f24);
        if (__fabs(temp_f2_2) < __float_min[0]) {
            if (direction.x >= 0.0f) {
                var_f21 = 1.5707964f;
            } else {
                var_f21 = -1.5707964f;
            }
        } else {
            var_f21 = (f32) atan2((f64) direction.x, (f64) temp_f2_2);
        }
        temp_f20 = (f32) sin((f64) var_f21);
        temp_f5 = (f32) cos((f64) var_f21);
        temp_f6 = -temp_f22;
        directionMatrix[0][1] = 0.0f;
        directionMatrix[0][0] = temp_f5;
        directionMatrix[0][2] = temp_f20;
        directionMatrix[0][3] = 0.0f;
        directionMatrix[1][0] = temp_f6 * temp_f20;
        directionMatrix[1][1] = temp_f24;
        directionMatrix[1][2] = temp_f22 * temp_f5;
        directionMatrix[1][3] = 0.0f;
        directionMatrix[2][0] = -temp_f24 * temp_f20;
        directionMatrix[2][1] = temp_f6;
        directionMatrix[2][2] = temp_f24 * temp_f5;
        directionMatrix[2][3] = 0.0f;
        PSMTXConcat((f32 (*)[4]) &transform[0][0], (f32 (*)[4]) &directionMatrix[0][0], (f32 (*)[4]) &transform[0][0]);
    }
    if ((s32) (arg0->type & 0xF) == 2) {
        if (__fabs(transform[2][2]) < __float_min[0]) {
            if (transform[1][2] >= 0.0f) {
                var_f25 = 1.5707964f;
            } else {
                var_f25 = -1.5707964f;
            }
        } else {
            var_f25 = (f32) atan2((f64) transform[1][2], (f64) transform[2][2]);
        }
        temp_f20_2 = (f32) cos((f64) var_f25);
        temp_f2_3 = (transform[1][2] * (f32) sin((f64) var_f25)) + (transform[2][2] * temp_f20_2);
        if (__fabs(temp_f2_3) < __float_min[0]) {
            if (transform[0][2] >= 0.0f) {
                var_f23 = 1.5707964f;
            } else {
                var_f23 = -1.5707964f;
            }
        } else {
            var_f23 = (f32) atan2((f64) transform[0][2], (f64) temp_f2_3);
        }
    }
    if (arg0->angle < 0.0f) {
        temp_r0 = arg0->type & 0xF;
        if (temp_r0 != 5) {
            if (temp_r0 < 5) {
                if (temp_r0 != 0) {
                    if (temp_r0 >= 0) {
                        if (temp_r0 < 3) {
                            goto block_63;
                        }
                        goto block_61;
                    }
                    goto block_63;
                }
block_61:
                temp_f20_3 = arg0->param1;
                temp_f0_2 = (arg0->param2 - temp_f20_3) / (f32) (s32) arg0->count;
                var_f30 = temp_f0_2;
                var_f31 = (temp_f0_2 * HSD_Randf()) + temp_f20_3;
            } else if (temp_r0 < 8) {
                temp_f20_4 = arg0->param1;
                temp_f0_3 = (arg0->param2 - temp_f20_4) / (f32) (s32) arg0->count;
                var_f30 = temp_f0_3;
                var_f31 = (temp_f0_3 * HSD_Randf()) + temp_f20_4;
            } else {
                goto block_63;
            }
        } else {
block_63:
            var_f31 = (f32) (2.0 * (3.141592653589793 * HSD_Randf()));
            var_f30 = (f32) (6.283185307179586 / (f64) (s32) arg0->count);
        }
    }
loop_215:
    temp_f1 = arg0->count;
    if (temp_f1 >= 1.0f) {
        temp_r0_2 = arg0->type & 0xF;
        switch (temp_r0_2) {                        /* switch 2 */
        case 0:                                     /* switch 2 */
        case 3:                                     /* switch 2 */
        case 4:                                     /* switch 2 */
        case 6:                                     /* switch 2 */
        case 7:                                     /* switch 2 */
            temp_f1_7 = arg0->radius;
            if (temp_f1_7 < 0.0f) {
                var_f21_2 = -temp_f1_7;
                var_f20_2 = 1.0f;
            } else {
                var_f20_2 = HSD_Randf();
                temp_r0_3 = arg0->type & 0xF;
                if ((temp_r0_3 == 3) || (temp_r0_3 == 4)) {
                    if (var_f20_2 > 0.0f) {
                        temp_f1_8 = __frsqrte(var_f20_2);
                        temp_f1_9 = 0.5 * temp_f1_8 * -(((f64) var_f20_2 * (temp_f1_8 * temp_f1_8)) - 3.0);
                        temp_f1_10 = 0.5 * temp_f1_9 * -(((f64) var_f20_2 * (temp_f1_9 * temp_f1_9)) - 3.0);
                        var_f0 = (f32) ((f64) var_f20_2 * (0.5 * temp_f1_10 * -(((f64) var_f20_2 * (temp_f1_10 * temp_f1_10)) - 3.0)));
                    } else if (var_f20_2 < 0.0) {
                        var_f0 = __float_nan[0];
                    } else {
                        bits14 = var_f20_2;
                        temp_r3_2 = *(s32*)&bits14 & 0x7F800000;
                        switch (temp_r3_2) {        /* switch 3; irregular */
                        case 0x7F800000:            /* switch 3 */
                            if (*(s32*)&bits14 & 0x7FFFFF) {
                                var_r0_2 = 1;
                            } else {
                                var_r0_2 = 2;
                            }
                            break;
                        case 0x0:                   /* switch 3 */
                            if (*(s32*)&bits14 & 0x7FFFFF) {
                                var_r0_2 = 5;
                            } else {
                                var_r0_2 = 3;
                            }
                            break;
                        default:                    /* switch 3 */
                            var_r0_2 = 4;
                            break;
                        }
                        if (var_r0_2 == 1) {
                            var_f0 = __float_nan[0];
                        } else {
                            var_f0 = var_f20_2;
                        }
                    }
                    var_f20_2 = var_f0;
                }
                var_f21_2 = var_f20_2 * arg0->radius;
            }
            temp_r0_4 = arg0->type & 0xF;
            switch (temp_r0_4) {                    /* switch 4; irregular */
            case 6:                                 /* switch 4 */
                temp_f2_4 = arg0->angle;
                if (temp_f2_4 < 0.0f) {
                    var_f31 += var_f30;
                    if (__fabs(var_f21_2) < __float_min[0]) {
                        if (arg0->param3 >= 0.0f) {
                            var_f22 = -temp_f2_4;
                        } else {
                            var_f22 = (f32) (3.141592653589793 - (f64) temp_f2_4);
                        }
                    } else {
                        var_f22 = (f32) ((1.5707963267948966 - (f64) (f32) atan2((f64) arg0->param3, (f64) var_f21_2)) - (f64) arg0->angle);
                    }
                } else {
                    temp_f22_2 = arg0->param1;
                    var_f31 = ((arg0->param2 - temp_f22_2) * HSD_Randf()) + temp_f22_2;
                    if (__fabs(var_f21_2) < __float_min[0]) {
                        if (arg0->param3 >= 0.0f) {
                            var_f22 = arg0->angle;
                        } else {
                            var_f22 = (f32) (3.141592653589793 + (f64) arg0->angle);
                        }
                    } else {
                        var_f22 = (f32) ((f64) arg0->angle + (1.5707963267948966 - (f64) (f32) atan2((f64) arg0->param3, (f64) var_f21_2)));
                    }
                }
                break;
            case 7:                                 /* switch 4 */
                temp_f1_11 = arg0->angle;
                if (temp_f1_11 < 0.0f) {
                    var_f31 += var_f30;
                    var_f22 = (f32) (1.5707963267948966 - (f64) temp_f1_11);
                } else {
                    temp_f31 = arg0->param1;
                    var_f31 = ((arg0->param2 - temp_f31) * HSD_Randf()) + temp_f31;
                    var_f22 = (f32) (1.5707963267948966 + (f64) arg0->angle);
                }
                break;
            default:                                /* switch 4 */
                temp_f1_12 = arg0->angle;
                if (temp_f1_12 < 0.0f) {
                    var_f31 += var_f30;
                    var_f22 = var_f20_2 * -temp_f1_12;
                } else {
                    temp_f31_2 = arg0->param1;
                    var_f22 = var_f20_2 * arg0->angle;
                    var_f31 = ((arg0->param2 - temp_f31_2) * HSD_Randf()) + temp_f31_2;
                }
                break;
            }
            position.x = var_f21_2 * (f32) cos((f64) var_f31);
            position.y = var_f21_2 * (f32) sin((f64) var_f31);
            temp_r0_5 = arg0->type & 0xF;
            if ((temp_r0_5 == 6) || (temp_r0_5 == 7)) {
                temp_f1_13 = HSD_Randf();
                position.z = temp_f1_13;
                if ((s32) (arg0->type & 0xF) == 6) {
                    temp_f2_5 = 1.0f - (f32) temp_f1_13;
                    position.x *= temp_f2_5;
                    position.y *= temp_f2_5;
                }
                position.z *= arg0->param3;
            } else {
                position.z = 0.0f;
            }
            temp_f21 = var_f27 * (f32) sin((f64) var_f22);
            velocity.x = temp_f21 * (f32) cos((f64) var_f31);
            velocity.y = temp_f21 * (f32) sin((f64) var_f31);
            temp_f0_4 = var_f27 * (f32) cos((f64) var_f22);
            velocity.z = temp_f0_4;
            if ((s32) (arg0->type & 0xF) == 3) {
                velocity.z = temp_f0_4 * var_f20_2;
                velocity.x *= var_f20_2;
                velocity.y *= var_f20_2;
            }
            PSMTXMultVec((f32 (*)[4]) &transform[0][0], (PSVec *) &position.x, (PSVec *) &position.x);
            position.x += arg0->position.x;
            position.y += arg0->position.y;
            position.z += arg0->position.z;
            PSMTXMultVec((f32 (*)[4]) &transform[0][0], (PSVec *) &velocity.x, (PSVec *) &velocity.x);
            sp8 = arg0->friction;
            spC = arg0;
            psGenerateParticle((s32) arg0->link, (s32) arg0->bank, 0, arg0->kind, (s32) arg0->texGroup, arg0->commands, position.x, position.y, position.z, velocity.x * temp_f26, velocity.y * temp_f29, velocity.z * temp_f28, arg0->size, arg0->gravity, (s32) arg0->particleLife, sp8, 0, spC);
            break;
        case 1:                                     /* switch 2 */
            temp_f1_14 = HSD_Randf();
            position.x = temp_f1_14 * arg0->param1;
            position.y = temp_f1_14 * arg0->param2;
            position.z = temp_f1_14 * arg0->param3;
            PSMTXMultVec((f32 (*)[4]) &transform[0][0], (PSVec *) &position.x, (PSVec *) &position.x);
            position.x += arg0->position.x;
            position.y += arg0->position.y;
            position.z += arg0->position.z;
            PSMTXMultVec((f32 (*)[4]) &transform[0][0], (PSVec *) &baseVelocity.x, (PSVec *) &velocity.x);
            sp8 = arg0->friction;
            spC = arg0;
            psGenerateParticle((s32) arg0->link, (s32) arg0->bank, 0, arg0->kind, (s32) arg0->texGroup, arg0->commands, position.x, position.y, position.z, velocity.x * temp_f26, velocity.y * temp_f29, velocity.z * temp_f28, arg0->size, arg0->gravity, (s32) arg0->particleLife, sp8, 0, spC);
            break;
        case 2:                                     /* switch 2 */
            if (arg0->radius < 0.0f) {
                var_f1 = 1.0f;
            } else {
                var_f1 = HSD_Randf();
            }
            if (arg0->angle < 0.0f) {
                var_f4 = var_f31 + var_f30;
            } else {
                var_f4 = (f32) (2.0 * (3.141592653589793 * HSD_Randf()));
            }
            arg0->param1 = var_f27;
            var_f31 = var_f4;
            sp8 = var_f23;
            spC = arg0;
            psGenerateParticle((s32) arg0->link, (s32) arg0->bank, 0, arg0->kind | 4, (s32) arg0->texGroup, arg0->commands, 0.0f, 0.0f, 0.0f, var_f4, var_f1, 0.0f, arg0->size, var_f25, (s32) arg0->particleLife, sp8, 0, spC);
            break;
        case 5:                                     /* switch 2 */
            position.x = HSD_Randf();
            position.y = HSD_Randf();
            temp_f1_15 = HSD_Randf();
            position.z = temp_f1_15;
            temp_r0_6 = arg0->edgeFlags;
            switch (temp_r0_6) {                    /* switch 5 */
            case 1:                                 /* switch 5 */
                if (position.x > 0.5f) {
                    var_f0_2 = 1.0f;
                } else {
                    var_f0_2 = 0.0f;
                }
                position.x = var_f0_2;
                break;
            case 2:                                 /* switch 5 */
                if (position.y > 0.5f) {
                    var_f0_3 = 1.0f;
                } else {
                    var_f0_3 = 0.0f;
                }
                position.y = var_f0_3;
                break;
            case 3:                                 /* switch 5 */
                temp_f2_6 = arg0->param1;
                if (HSD_Randf() > (temp_f2_6 / (temp_f2_6 + arg0->param2))) {
                    if (position.y > 0.5f) {
                        var_f0_4 = 1.0f;
                    } else {
                        var_f0_4 = 0.0f;
                    }
                    position.y = var_f0_4;
                } else {
                    if (position.x > 0.5f) {
                        var_f0_5 = 1.0f;
                    } else {
                        var_f0_5 = 0.0f;
                    }
                    position.x = var_f0_5;
                }
                break;
            case 4:                                 /* switch 5 */
                if ((f32) temp_f1_15 > 0.5f) {
                    var_f0_6 = 1.0f;
                } else {
                    var_f0_6 = 0.0f;
                }
                position.z = var_f0_6;
                break;
            case 5:                                 /* switch 5 */
                temp_f2_7 = arg0->param1;
                if (HSD_Randf() > (temp_f2_7 / (temp_f2_7 + arg0->param3))) {
                    if (position.z > 0.5f) {
                        var_f0_7 = 1.0f;
                    } else {
                        var_f0_7 = 0.0f;
                    }
                    position.z = var_f0_7;
                } else {
                    if (position.x > 0.5f) {
                        var_f0_8 = 1.0f;
                    } else {
                        var_f0_8 = 0.0f;
                    }
                    position.x = var_f0_8;
                }
                break;
            case 6:                                 /* switch 5 */
                temp_f2_8 = arg0->param2;
                if (HSD_Randf() > (temp_f2_8 / (temp_f2_8 + arg0->param3))) {
                    if (position.z > 0.5f) {
                        var_f0_9 = 1.0f;
                    } else {
                        var_f0_9 = 0.0f;
                    }
                    position.z = var_f0_9;
                } else {
                    if (position.y > 0.5f) {
                        var_f0_10 = 1.0f;
                    } else {
                        var_f0_10 = 0.0f;
                    }
                    position.y = var_f0_10;
                }
                break;
            case 7:                                 /* switch 5 */
                temp_f1_16 = HSD_Randf();
                temp_f5_2 = arg0->param3;
                temp_f0_5 = arg0->param2;
                temp_f6_2 = arg0->param1;
                var_f4_2 = 1.0f;
                temp_f2_9 = 1.0f / ((temp_f6_2 * (temp_f0_5 + temp_f5_2)) + (temp_f0_5 * temp_f5_2));
                if (temp_f1_16 < (temp_f2_9 * (temp_f6_2 * temp_f0_5))) {
                    if (position.z > 0.5f) {

                    } else {
                        var_f4_2 = 0.0f;
                    }
                    position.z = var_f4_2;
                } else if (temp_f1_16 > -((temp_f2_9 * (temp_f6_2 * temp_f5_2)) - 1.0f)) {
                    if (position.y > 0.5f) {

                    } else {
                        var_f4_2 = 0.0f;
                    }
                    position.y = var_f4_2;
                } else {
                    if (position.x > 0.5f) {

                    } else {
                        var_f4_2 = 0.0f;
                    }
                    position.x = var_f4_2;
                }
                break;
            }
            temp_f5_3 = position.x - 0.5f;
            temp_f4 = position.y - 0.5f;
            temp_f3 = position.z - 0.5f;
            position.x = temp_f5_3;
            position.y = temp_f4;
            position.z = temp_f3;
            offset.x = (arg0->axisZX * temp_f3) + ((arg0->axisXX * temp_f5_3) + (arg0->axisYX * temp_f4));
            offset.y = (arg0->axisZY * temp_f3) + ((arg0->axisXY * temp_f5_3) + (arg0->axisYY * temp_f4));
            offset.z = (arg0->axisZZ * temp_f3) + ((arg0->axisXZ * temp_f5_3) + (arg0->axisYZ * temp_f4));
            PSMTXMultVec((f32 (*)[4]) &transform[0][0], (PSVec *) &offset.x, (PSVec *) &position.x);
            position.x += arg0->position.x;
            position.y += arg0->position.y;
            position.z += arg0->position.z;
            temp_f2_10 = arg0->axisZX;
            temp_f1_17 = arg0->axisZY;
            temp_f3_2 = arg0->axisZZ;
            var_f4_3 = (temp_f3_2 * temp_f3_2) + ((temp_f2_10 * temp_f2_10) + (temp_f1_17 * temp_f1_17));
            if (var_f4_3 > 0.0f) {
                temp_f1_18 = __frsqrte(var_f4_3);
                temp_f1_19 = 0.5 * temp_f1_18 * -(((f64) var_f4_3 * (temp_f1_18 * temp_f1_18)) - 3.0);
                temp_f1_20 = 0.5 * temp_f1_19 * -(((f64) var_f4_3 * (temp_f1_19 * temp_f1_19)) - 3.0);
                var_f4_3 = (f32) ((f64) var_f4_3 * (0.5 * temp_f1_20 * -(((f64) var_f4_3 * (temp_f1_20 * temp_f1_20)) - 3.0)));
            } else if (var_f4_3 < 0.0) {
                var_f4_3 = __float_nan[0];
            } else {
                bits10 = var_f4_3;
                temp_r3_3 = *(s32*)&bits10 & 0x7F800000;
                switch (temp_r3_3) {                /* switch 6; irregular */
                case 0x7F800000:                    /* switch 6 */
                    if (*(s32*)&bits10 & 0x7FFFFF) {
                        var_r0_3 = 1;
                    } else {
                        var_r0_3 = 2;
                    }
                    break;
                case 0x0:                           /* switch 6 */
                    if (*(s32*)&bits10 & 0x7FFFFF) {
                        var_r0_3 = 5;
                    } else {
                        var_r0_3 = 3;
                    }
                    break;
                default:                            /* switch 6 */
                    var_r0_3 = 4;
                    break;
                }
                if (var_r0_3 == 1) {
                    var_f4_3 = __float_nan[0];
                }
            }
            temp_f1_21 = var_f27 / var_f4_3;
            velocity.x = arg0->axisZX * temp_f1_21;
            velocity.y = arg0->axisZY * temp_f1_21;
            velocity.z = arg0->axisZZ * temp_f1_21;
            PSMTXMultVec((f32 (*)[4]) &transform[0][0], (PSVec *) &velocity.x, (PSVec *) &velocity.x);
            sp8 = arg0->friction;
            spC = arg0;
            psGenerateParticle((s32) arg0->link, (s32) arg0->bank, 0, arg0->kind, (s32) arg0->texGroup, arg0->commands, position.x, position.y, position.z, velocity.x * temp_f26, velocity.y * temp_f29, velocity.z * temp_f28, arg0->size, arg0->gravity, (s32) arg0->particleLife, sp8, 0, spC);
            break;
        case 8:                                     /* switch 2 */
            if (arg0->param3 == 0.0f) {
                var_f0_11 = (f32) (3.141592653589793 * HSD_Randf());
            } else {
                var_f0_11 = arg0->param3 * HSD_Randf();
            }
            temp_f21_2 = arg0->radius;
            temp_f19 = (f32) (2.0 * (3.141592653589793 * HSD_Randf()));
            if (temp_f21_2 < 0.0f) {
                var_f22_2 = -temp_f21_2;
            } else {
                var_f22_2 = temp_f21_2 * HSD_Randf();
            }
            temp_f21_3 = (f32) cos((f64) temp_f19);
            velocity.x = (f32) sin((f64) var_f0_11) * temp_f21_3;
            temp_f21_4 = (f32) sin((f64) temp_f19);
            velocity.y = (f32) sin((f64) var_f0_11) * temp_f21_4;
            velocity.z = (f32) cos((f64) var_f0_11);
            PSMTXMultVec((f32 (*)[4]) &transform[0][0], (PSVec *) &velocity.x, (PSVec *) &position.x);
            temp_f5_4 = arg0->param1;
            temp_f2_11 = position.x * temp_f5_4;
            temp_f4_2 = position.y * temp_f5_4;
            temp_f3_3 = position.z * temp_f5_4;
            velocity.x = temp_f2_11;
            velocity.y = temp_f4_2;
            velocity.z = temp_f3_3;
            temp_f1_22 = arg0->radius;
            if ((temp_f1_22 >= 0.0f) && (temp_f5_4 < 0.0f)) {
                temp_f0_6 = var_f22_2 / temp_f1_22;
                velocity.x = temp_f2_11 * temp_f0_6;
                velocity.y = temp_f4_2 * temp_f0_6;
                velocity.z = temp_f3_3 * temp_f0_6;
            }
            position.x = (var_f22_2 * position.x) + arg0->position.x;
            position.y = (var_f22_2 * position.y) + arg0->position.y;
            position.z = (var_f22_2 * position.z) + arg0->position.z;
            sp8 = arg0->friction;
            spC = arg0;
            psGenerateParticle((s32) arg0->link, (s32) arg0->bank, 0, arg0->kind, (s32) arg0->texGroup, arg0->commands, position.x, position.y, position.z, velocity.x * temp_f26, velocity.y * temp_f29, velocity.z * temp_f28, arg0->size, arg0->gravity, (s32) arg0->particleLife, sp8, 0, spC);
            break;
        default:                                    /* switch 2 */
            if (((void (*)(PSGenerator *, f32 (*)[4])) psExtExecGenFunc) != NULL) {
                psExtExecGenFunc(arg0, (f32 (*)[4]) &transform[0][0]);
            }
            break;
        }
        arg0->count -= 1.0f;
        goto loop_215;
    }
    return temp_f1;
}
