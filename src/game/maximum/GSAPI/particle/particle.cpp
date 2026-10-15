#include "game/maximum/GSAPI/particle/particle.h"
#define NULL ((void*)0)
s16 g_ps_token;
u16 numPeakPSAppSRT,numPeakGenerators,numPeakParticles,numActivePSAppSRT,numActiveGenerators,numActiveParticles;
PSJObj* psPointJObj[8];
s32 psNumCmdList[64];
s32 psNumTexGroup[64];
PSCmd** psCmdListArray[64];
PSTex** psTexGroupArray[64];
void* psFormGroupArray[64];
void* ptclref[64];
void psSetToken(s16 arg0) {
    g_ps_token = arg0;
}

void psSetParticleVisibility(PSGenerator *arg0, u8 arg1) {
    PSGenerator *var_r5;
    PSParticle *var_r3;

    var_r3 = _psListGetFirst((s32) arg0->link);
while (var_r3 != NULL) {
        if ((u16) var_r3->id == (u16) arg0->id) {
            if (arg1 != 0) {
                var_r3->kind &= 0xDFFFFFFF;
            } else {
                var_r3->kind |= 0x20000000;
            }
        }
        var_r3 = var_r3->next;
}
    var_r5 = activeGenerator;
while (var_r5 != NULL) {
        if ((u16) var_r5->id == (u16) arg0->id) {
            if (arg1 != 0) {
                var_r5->kind &= 0xDFFFFFFF;
            } else {
                var_r5->kind |= 0x20000000;
            }
        }
        var_r5 = var_r5->next;
}
}

void psSetGeneratorAngleRadiusScale(PSGenerator *arg0, PSVec *arg1, u8 arg2) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f3;
    u16 temp_r6;
    u32 temp_r7;
    u8 temp_r0;

    temp_f3 = arg1->x;
    temp_r7 = arg0->type & 0xF;
    temp_r0 = arg0->bank;
    temp_r6 = arg0->commandID;
    temp_f0 = (arg1->z + (temp_f3 + arg1->y)) / 3.0f;
    switch (temp_r7) {
    case 0:
    case 3:
    case 4:
        arg0->param1 = temp_f0 * psCmdListArray[temp_r0][temp_r6]->param1;
        arg0->param2 = temp_f0 * psCmdListArray[temp_r0][temp_r6]->param2;
        break;
    case 1:
        arg0->param1 = temp_f3 * psCmdListArray[temp_r0][temp_r6]->param1;
        arg0->param2 = arg1->y * psCmdListArray[temp_r0][temp_r6]->param2;
        arg0->param3 = arg1->z * psCmdListArray[temp_r0][temp_r6]->param3;
        break;
    case 6:
    case 7:
        arg0->param1 = temp_f0 * psCmdListArray[temp_r0][temp_r6]->param1;
        arg0->param2 = temp_f0 * psCmdListArray[temp_r0][temp_r6]->param2;
        arg0->param3 = temp_f0 * psCmdListArray[temp_r0][temp_r6]->param3;
        break;
    case 5:
        temp_f1 = temp_f3 * psCmdListArray[temp_r0][temp_r6]->param1;
        arg0->param1 = temp_f1;
        arg0->axisXX = temp_f1;
        temp_f1_2 = arg1->y * psCmdListArray[temp_r0][temp_r6]->param2;
        arg0->param2 = temp_f1_2;
        arg0->axisYY = temp_f1_2;
        temp_f1_3 = arg1->z * psCmdListArray[temp_r0][temp_r6]->param3;
        arg0->param3 = temp_f1_3;
        arg0->axisZZ = temp_f1_3;
        break;
    case 8:
        arg0->param3 = temp_f0 * psCmdListArray[temp_r0][temp_r6]->param1;
        arg0->axisXY = temp_f0 * psCmdListArray[temp_r0][temp_r6]->param2;
        break;
    }
    arg0->radius = temp_f0 * psCmdListArray[temp_r0][temp_r6]->radius;
    if (arg2 == 1) {
        arg0->gravity *= temp_f0;
        arg0->friction *= temp_f0;
        arg0->transformFlags |= 0x1000;
    }
    arg0->nodeScale.x = arg1->x;
    arg0->nodeScale.y = arg1->y;
    arg0->nodeScale.z = arg1->z;
}

void psSetRandomVelocityScaling(PSGenerator *arg0, u8 arg1) {
    if (arg1 != 0) {
        arg0->transformFlags |= 0x200;
        return;
    }
    arg0->transformFlags &= 0xFFFFFDFF;
}

void psSetNodeScaling(PSGenerator *arg0, u8 arg1) {
    if (arg1 != 0) {
        arg0->transformFlags |= 0x100;
        return;
    }
    arg0->transformFlags &= 0xFFFFFEFF;
}

void psSetTornadoScaling(PSGenerator *arg0, u8 arg1, u8 arg2) {
    if (arg1 != 0) {
        arg0->transformFlags |= 0x40;
    } else {
        arg0->transformFlags &= 0xFFFFFFBF;
    }
    if (arg2 != 0) {
        arg0->transformFlags |= 0x80;
        return;
    }
    arg0->transformFlags &= 0xFFFFFF7F;
}

void psSetParticleTexScaling(PSGenerator *arg0, u8 arg1) {
    if (arg1 != 0) {
        arg0->transformFlags |= 0x20;
        return;
    }
    arg0->transformFlags &= 0xFFFFFFDF;
}

void psSetOffsetRotationInLocal(PSGenerator *arg0, u8 arg1, u8 arg2) {
    if (arg1 != 0) {
        arg0->transformFlags |= 8;
        if (arg2 != 0) {
            arg0->transformFlags |= 0x10;
            return;
        }
        arg0->transformFlags &= 0xFFFFFFEF;
        return;
    }
    arg0->transformFlags &= 0xFFFFFFF7;
    arg0->transformFlags &= 0xFFFFFFEF;
}

void psSetVelocityRotationInLocal(PSGenerator *arg0, u8 arg1) {
    if (arg1 != 0) {
        arg0->transformFlags |= 4;
        return;
    }
    arg0->transformFlags &= 0xFFFFFFFB;
}

void psUnlinkChildGensFromJObj(PSGenerator *arg0) {
    arg0->transformFlags &= 0xFFFE;
}

void psLinkChildGensToJObj(PSGenerator *arg0, PSJObj *arg1) {
    arg0->transformFlags |= 1;
    arg0->jobj = arg1;
}

s32 psGetParticleChildCount(PSGenerator *arg0) {
    PSGenerator *var_r6;
    s32 var_r5;

    var_r6 = activeGenerator;
    var_r5 = 0;
while (var_r6 != NULL) {
        if ((u16) var_r6->id == (u16) arg0->id) {
            var_r5 += var_r6->children;
        }
        var_r6 = var_r6->next;
}
    return var_r5;
}

u16 psGetGeneratorChildMaxLife(PSGenerator *arg0) {
    PSGenerator *var_r6;
    u16 temp_r0;
    u16 var_r5;

    var_r5 = arg0->life;
    var_r6 = activeGenerator;
while (var_r6 != NULL) {
        if ((u16) var_r6->id == (u16) arg0->id) {
            temp_r0 = var_r6->life;
            if (temp_r0 > var_r5) {
                var_r5 = temp_r0;
            }
        }
        var_r6 = var_r6->next;
}
    return var_r5;
}

void psKillGeneratorChild(PSGenerator *arg0) {
    PSGenerator *temp_r4;
    PSJObj *temp_r3;
    PSParticle *temp_r29;
    PSParticle *var_r27;
    PSParticle *var_r28;
    s32 temp_r30;
    u16 temp_r26;
    u32 temp_r4_2;

    var_r28 = NULL;
    temp_r26 = arg0->id;
    var_r27 = _psListGetFirst((s32) arg0->link);
while (var_r27 != NULL) {
        temp_r29 = var_r27->next;
        if (((u16) var_r27->id == temp_r26) && (temp_r4 = var_r27->generator, ((temp_r4 == NULL) == 0)) && (temp_r4 == arg0)) {
            if (temp_r4 != NULL) {
                temp_r4->children -= 1;
            }
            if ((PSAppSRT *) var_r27->appsrt != NULL) {
                psRemoveParticleAppSRT(var_r27);
            }
            temp_r4_2 = var_r27->kind;
            if (temp_r4_2 & 0x8000) {
                temp_r30 = (temp_r4_2 >> 0xAU) & 0x1C;
                temp_r3 = *(PSJObj**)((u8*)psPointJObj + temp_r30);
                if (temp_r3 != NULL) {
                    HSD_JObjUnref(temp_r3);
                    *(PSJObj**)((u8*)psPointJObj + temp_r30) = 0;
                }
            }
            _psListDelete(var_r27, var_r28);
        } else {
            var_r28 = var_r27;
        }
        var_r27 = temp_r29;
}
}

void psKillFamily(u16 arg0, s32 arg1) {
    PSGenerator *temp_r4;
    PSJObj *temp_r3;
    PSParticle *temp_r27;
    PSParticle *var_r25;
    PSParticle *var_r26;
    s32 temp_r29;
    u32 temp_r4_2;

    var_r26 = NULL;
    var_r25 = _psListGetFirst((s32) arg1);
while (var_r25 != NULL) {
        temp_r27 = var_r25->next;
        if ((u16) var_r25->id == arg0) {
            temp_r4 = var_r25->generator;
            if (temp_r4 != NULL) {
                temp_r4->children -= 1;
            }
            if ((PSAppSRT *) var_r25->appsrt != NULL) {
                psRemoveParticleAppSRT(var_r25);
            }
            temp_r4_2 = var_r25->kind;
            if (temp_r4_2 & 0x8000) {
                temp_r29 = (temp_r4_2 >> 0xAU) & 0x1C;
                temp_r3 = *(PSJObj**)((u8*)psPointJObj + temp_r29);
                if (temp_r3 != NULL) {
                    HSD_JObjUnref(temp_r3);
                    *(PSJObj**)((u8*)psPointJObj + temp_r29) = 0;
                }
            }
            _psListDelete(var_r25, var_r26);
        } else {
            var_r26 = var_r25;
        }
        var_r25 = temp_r27;
}
    psKillGeneratorID(arg0);
}

void psDeletePntJObjwithParticle(PSParticle *arg0) {
    PSJObj *temp_r3;
    s32 temp_r30;
    u32 temp_r4;

    temp_r4 = arg0->kind;
    if (temp_r4 & 0x8000) {
        temp_r30 = (temp_r4 >> 0xAU) & 0x1C;
        temp_r3 = *(PSJObj**)((u8*)psPointJObj + temp_r30);
        if (temp_r3 != NULL) {
            HSD_JObjUnref(temp_r3);
            *(PSJObj**)((u8*)psPointJObj + temp_r30) = 0;
        }
    }
}

void psKillAllParticle(void) {
    PSGenerator *temp_r4;
    PSJObj *temp_r3;
    PSParticle *temp_r27;
    PSParticle *var_r28;
    PSParticle *var_r29;
    PSParticle *var_r30;
    s32 temp_r30;
    s32 var_r26;
    u32 temp_r4_2;

    var_r26 = 0;
    do {
        var_r30 = _psListGetFirst(var_r26);
while (var_r30 != NULL) {
            temp_r27 = var_r30->next;
            var_r28 = NULL;
            var_r29 = _psListGetFirst((s32) var_r30->link);
while (var_r29 != NULL) {
                if (var_r29 == var_r30) {
                    temp_r4 = var_r30->generator;
                    if (temp_r4 != NULL) {
                        temp_r4->children -= 1;
                    }
                    if ((PSAppSRT *) var_r30->appsrt != NULL) {
                        psRemoveParticleAppSRT(var_r30);
                    }
                    temp_r4_2 = var_r29->kind;
                    if (temp_r4_2 & 0x8000) {
                        temp_r30 = (temp_r4_2 >> 0xAU) & 0x1C;
                        temp_r3 = *(PSJObj**)((u8*)psPointJObj + temp_r30);
                        if (temp_r3 != NULL) {
                            HSD_JObjUnref(temp_r3);
                            *(PSJObj**)((u8*)psPointJObj + temp_r30) = 0;
                        }
                    }
                    _psListDelete(var_r29, var_r28);
                } else {
                    var_r28 = var_r29;
                    var_r29 = var_r29->next;
                    continue;
                }

    break;
}
            var_r30 = temp_r27;
}
        var_r26 += 1;
    } while (var_r26 < 0x10);
}


PSParticle* psGenerateParticle0(PSParticle* arg0,s32 arg1,s32 arg2,s32 reserved0,s32 reserved1,u32 arg5,s32 arg6,u8* arg7,f32 farg0,f32 farg1,f32 farg2,f32 farg3,f32 farg4,f32 farg5,f32 farg6,f32 farg7,s32 life,f32 friction,s32 arg_sp10,PSGenerator* arg_sp14,s32 arg_sp18) {
    PSAppSRT *temp_r4;
    PSParticle *temp_r3;

    temp_r3 = _psListNew(arg0, (s32) arg1);
    if (temp_r3 == NULL) {
        return NULL;
    }
    if (arg_sp14 != NULL) {
        temp_r3->id = arg_sp14->id;
    } else {
        temp_r3->id = psGetNewIDNum();
    }
    temp_r3->appsrt = NULL;
    if (arg_sp14 != NULL) {
        temp_r4 = arg_sp14->appsrt;
        if (temp_r4 != NULL) {
            psAttachParticleAppSRT(temp_r3, temp_r4);
        }
    }
    temp_r3->bank = (u8) arg2;
    temp_r3->link = (u8) arg1;
    temp_r3->kind = arg5;
    temp_r3->texGroup = (u8) arg6;
    temp_r3->position.x = farg0;
    temp_r3->position.y = farg1;
    temp_r3->position.z = farg2;
    temp_r3->velocity.x = farg3;
    temp_r3->velocity.y = farg4;
    temp_r3->velocity.z = farg5;
    temp_r3->size = farg6;
    temp_r3->gravity = farg7;
    temp_r3->friction = friction;
    temp_r3->life = (u16) (life + 1);
    temp_r3->commands = arg7;
    temp_r3->markPtr = 0;
    temp_r3->commandPtr = 0;
    if (arg_sp10 != 0) {
        temp_r3->kind |= 0x10;
    }
    temp_r3->wait = arg7 != NULL;
    temp_r3->pose = 0;
    temp_r3->palette = 0xFF;
    temp_r3->primColor[3] = 0xFF;
    temp_r3->primColor[2] = 0xFF;
    temp_r3->primColor[1] = 0xFF;
    temp_r3->primColor[0] = 0xFF;
    temp_r3->envColor[3] = 0;
    temp_r3->envColor[2] = 0;
    temp_r3->envColor[1] = 0;
    temp_r3->envColor[0] = 0;
    temp_r3->envCount = 0;
    temp_r3->primCount = 0;
    temp_r3->sizeCount = 0;
    temp_r3->envRemain = 0;
    temp_r3->primRemain = 0;
    temp_r3->alphaMode = 0x33;
    if ((u32) (((u32) temp_r3->kind >> 0x16U) & 3) >= 2U) {
        temp_r3->alpha1 = 0;
    } else {
        temp_r3->alpha1 = 1;
    }
    temp_r3->alpha2 = 0xFF;
    temp_r3->alphaRemain = 0;
    temp_r3->alphaCount = 0;
    temp_r3->rotateCount = 0;
    temp_r3->trail = 0.0f;
    temp_r3->rotateTarget = 0.0f;
    temp_r3->rotate = 0.0f;
    temp_r3->generator = arg_sp14;
    if (arg_sp14 != NULL) {
        arg_sp14->children += 1;
    }
    temp_r3->pointOffset = 0;
    temp_r3->matRemain = 0;
    temp_r3->matCount = 0;
    temp_r3->matRGB = 0xFF;
    temp_r3->matAlpha = 0xFF;
    temp_r3->ambRemain = 0;
    temp_r3->ambCount = 0;
    temp_r3->ambRGB = 0xFF;
    temp_r3->ambAlpha = 0xFF;
    temp_r3->textureScale = 1.0f;
    if (arg_sp18 != 0) {
        psInterpretParticle0(temp_r3, 0);
    }
    return temp_r3;
}

PSParticle* psGenerateParticle(s32 link,s32 bank,s32 reserved,u32 kind,s32 tex,u8* commands,f32 x,f32 y,f32 z,f32 vx,f32 vy,f32 vz,f32 size,f32 gravity,s32 life,f32 friction,s32 palettes,PSGenerator* gp) {
    return psGenerateParticle0(NULL,link,bank,kind,reserved,kind,tex,commands,x,y,z,vx,vy,vz,size,gravity,life,friction,palettes,gp,1);
}
PSParticle* psGenerateParticleID0(PSParticle* parent,s32 link,s32 bank,s32 id,s32 interpret) {
    PSCmd* cmd; PSTex* tex; u16 flags;
    if (link >= 8) return NULL;
    if (bank >= 64) return NULL;
    if (id >= psNumCmdList[bank]) return NULL;
    cmd = psCmdListArray[bank][id];
    if (cmd == NULL) return NULL;
    tex = psTexGroupArray[bank][cmd->texGroup];
    flags = tex != NULL ? tex->paletteFlags : 0;
    return psGenerateParticle0(parent,link,bank,(s32)tex,0,cmd->kind,cmd->texGroup,cmd->commands,0,0,0,cmd->velocity.x,cmd->velocity.y,cmd->velocity.z,cmd->size,cmd->gravity,cmd->life,cmd->friction,flags,NULL,interpret);
}
void psRemoveParticle(void) {
    PSParticle *next;
    PSParticle *prev;
    PSParticle *node;
    int i;
    PSParticle *cur;

    for (i = 0; i < 16; i++) {
        cur = _psListGetFirst(i);
        while (cur != NULL) {
            next = cur->next;
            prev = NULL;
            node = _psListGetFirst(cur->link);
            while (node != NULL) {
                if (node == cur) {
                    if (cur->generator != NULL) {
                        cur->generator->children -= 1;
                    }
                    if (cur->appsrt != NULL) {
                        psRemoveParticleAppSRT(cur);
                    }
                    if (node->kind & 0x8000) {
                        s32 idx = (node->kind >> 10) & 0x1C;
                        PSJObj *jobj = *(PSJObj **) ((u8 *) psPointJObj + idx);
                        if (jobj != NULL) {
                            HSD_JObjUnref(jobj);
                            *(PSJObj **) ((u8 *) psPointJObj + idx) = NULL;
                        }
                    }
                    _psListDelete(node, prev);
                    break;
                }
                prev = node;
                node = node->next;
            }
            cur = next;
        }
    }
    psKillAllGenerator();
    _psListClear();
    for (i = 0; i < 64; i++) {
        psNumCmdList[i] = 0;
        psNumTexGroup[i] = 0;
        psCmdListArray[i] = NULL;
        psTexGroupArray[i] = NULL;
        psFormGroupArray[i] = NULL;
        ptclref[i] = NULL;
    }
    for (i = 0; i < 8; i++) {
        if (psPointJObj[i] != NULL) {
            HSD_JObjUnref(psPointJObj[i]);
            psPointJObj[i] = NULL;
        }
    }
}

void psInitParticle(s32 count) {
    int i;
    _psLinkInit(count);
    numActiveParticles = 0; numPeakParticles = 0;
    for (i = 0; i < 64; i++) {
        psNumCmdList[i] = 0; psNumTexGroup[i] = 0; psCmdListArray[i] = NULL;
        psTexGroupArray[i] = NULL; psFormGroupArray[i] = NULL; ptclref[i] = NULL;
    }
    for (i = 0; i < 8; i++) psPointJObj[i] = NULL;
}

void psInitDataBankLocate(s32 *cmdBank, s32 *texBank, s32 *formBank);

void psInitDataBank(s32 bank, s32 *cmdBank, s32 *texBank, void *ref, s32 *formBank) {
    u16 version;

    if (bank >= 64) {
        return;
    }
    psInitDataBankLocate(cmdBank, texBank, formBank);
    if (formBank != NULL && *formBank != *texBank) {
        OSPanic("particle.c", 98, "illigal form data (strange number of group)\n");
    }
    ptclref[bank] = ref;
    psNumTexGroup[bank] = *texBank;
    psTexGroupArray[bank] = (PSTex **) (texBank + 1);
    if (formBank != NULL) {
        psFormGroupArray[bank] = formBank + 1;
    } else {
        psFormGroupArray[bank] = NULL;
    }
    version = *(u16 *) cmdBank;
    switch (version) {
    case 0:
        psNumCmdList[bank] = cmdBank[1];
        psCmdListArray[bank] = (PSCmd **) (cmdBank + 2);
        break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43: {
        s32 count = cmdBank[1];
        psNumCmdList[bank] = cmdBank[2] + count;
        psCmdListArray[bank] = (PSCmd **) (cmdBank + 3 - count);
        break;
    }
    default:
        OSPanic("particle.c", 128, "psInitDataBanks: unknown version\n");
    }
}

void psInitDataBankLocate(s32 *cmdBank, s32 *texBank, s32 *formBank) {
    s32 num;
    s32 *ptr;
    s32 *group;
    s32 j;
    s32 i;
    s32 num2;
    s32 *groups;
    s32 *base;
    s32 version;

    version = *(u16 *) cmdBank;
    switch (version) {
    case 0:
        num2 = cmdBank[1];
        base = cmdBank + 2;
        num = 0;
        for (i = 0; i < num2; i++) {
            cmdBank[i + 2] += (s32) cmdBank;
        }
        break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
        num = cmdBank[1];
        num2 = cmdBank[2] + num;
        base = cmdBank + 3 - num;
        ptr = cmdBank;
        j = 0;
        while (j < cmdBank[2]) {
            if (ptr[3] != 0) {
                ptr[3] += (s32) cmdBank;
            }
            ptr++;
            j++;
        }
        break;
    }

    ptr = base + num;
    for (i = num; i < num2; i++) {
        s32 *cmd = (s32 *) ptr[0];
        if (cmd != NULL) {
            cmd[2] = cmd[2] & 0xF1FFFFFF;
            cmd = (s32 *) ptr[0];
            cmd[2] = cmd[2] | 0x08000000;
        }
        ptr++;
    }

    {
        s32 num_groups = texBank[0];
        s32 k;

        group = groups = texBank + 1;
        for (k = 1; k <= num_groups; k++) {
            if (group[0] != 0) {
                group[0] += (s32) texBank;
            }
            group++;
        }

        group = groups;
        for (k = 0; k < num_groups; group++, k++) {
            PSTex *tg = (PSTex *) group[0];
            if (tg == NULL) {
                continue;
            }
            {
                s32 ti;
                for (ti = 0; (u32) ti < ((PSTex *) group[0])->count; ti++) {
                    if (((PSTex *) group[0])->textures[ti] != NULL) {
                        ((PSTex *) group[0])->textures[ti] = (void *) ((u32) ((PSTex *) group[0])->textures[ti] + (u32) texBank);
                    }
                }
                tg = (PSTex *) group[0];
            }
            {
                u32 fmt = tg->format;
                if (fmt != 8 && (fmt - 9) > 1) {
                    continue;
                }
            }
            if (tg->paletteFlags & 1) {
                i = tg->count;
                if (tg->textures[i] != NULL) {
                    tg->textures[i] = (void *) ((u32) tg->textures[i] + (u32) texBank);
                }
            } else if (tg->palettes != 0) {
                i = tg->count;
                for (; (u32) i < ((PSTex *) group[0])->count + ((PSTex *) group[0])->palettes; i++) {
                    PSTex *tg2 = (PSTex *) group[0];
                    void **entry = &tg2->textures[i];
                    if (*entry != NULL) {
                        *entry = (void *) ((u32) *entry + (u32) texBank);
                    }
                }
            } else {
                i = tg->count;
                for (; (u32) i < ((PSTex *) group[0])->count * 2; i++) {
                    PSTex *tg2 = (PSTex *) group[0];
                    void **entry = &tg2->textures[i];
                    if (*entry != NULL) {
                        *entry = (void *) ((u32) *entry + (u32) texBank);
                    }
                }
            }
        }

        if (formBank == NULL) {
            return;
        }
        for (i = 1; i <= num_groups; i++) {
            if (formBank[i] != 0) {
                s32 fi;
                u32 *fg;
                formBank[i] += (s32) formBank;
                fg = (u32 *) formBank[i];
                for (fi = 0; (u32) fi < fg[0]; fi++) {
                    if (fg[1 + fi] != 0) {
                        fg[1 + fi] += (u32) formBank;
                    }
                }
            }
        }
    }
}

void psSetPointJObjNodup(PSObject *arg0, s32 arg1) {
    PSJObj **p;
    s32 i;

    if (arg1 < 0 || arg1 > 8) {
        return;
    }
    for (i = 0; i < 8; i++) {
        if (psPointJObj[i] == (PSJObj *) arg0) {
            HSD_JObjUnref(psPointJObj[i]);
            psPointJObj[i] = NULL;
        }
    }
    if (arg1 != 0) {
        PSJObj *old;
        p = psPointJObj;
        p += arg1;
        old = *--p;
        if (old != NULL) {
            HSD_JObjUnref(old);
        }
        *p = (PSJObj *) arg0;
        if (arg0 != NULL) {
            arg0->references++;
            if (arg0->references == 0xFFFF) {
                __assert("object.h", 0x5D, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
            }
        }
    }
}

void psSetPointJObj(s32 arg0, PSObject *arg1) {
    if (arg0 < 0 || arg0 > 8) {
        return;
    }
    if (arg0 != 0) {
        PSJObj *old;
        PSJObj **p;
        p = psPointJObj;
        p += arg0;
        old = *--p;
        if (old != (PSJObj *) arg1) {
            if (old != NULL) {
                HSD_JObjUnref(old);
            }
            *p = (PSJObj *) arg1;
            if (arg1 != NULL) {
                arg1->references++;
                if (arg1->references == 0xFFFF) {
                    __assert("object.h", 0x5D, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
                }
            }
        }
    } else {
        s32 i;
        for (i = 0; i < 8; i++) {
            if (psPointJObj[i] == (PSJObj *) arg1) {
                HSD_JObjUnref(psPointJObj[i]);
                psPointJObj[i] = NULL;
            }
        }
    }
}
