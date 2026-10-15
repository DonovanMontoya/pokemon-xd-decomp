#include <game/pxdvs/GSAPI/GSparticle/peShapePrivate.hpp>
void peShapeContainer::Stop() {
    if(active) {
        PreUpdate();active=0;
        if(shape->flags&0x800000)SetLayerVisibility((GSgfxLayerID)1,false);
        if(shape->flags&0x1000000)SetLayerVisibility((GSgfxLayerID)3,false);
        if(shape->flags&0x2000000)SetLayerVisibility((GSgfxLayerID)5,false);
        RemoveAll();
    }
}
void peShapeContainer::Update(f32 time) {
    if(active) {
        peShapeNode* node=(peShapeNode*)nodes;
        while(node) {peShapeNode* next=(peShapeNode*)node->next;if(!node->Update(owner,shape,time))RemoveNode(node);node=next;}
        if(g_currentBound && nodes)GSboundAlwaysInView(g_currentBound,1);
        if(active && (shape->flags&0x80) && count>=2) {
            peShapeNode* sorting=(peShapeNode*)nodes->next;
            while(sorting) {
                peShapeNode* before=sorting;f32 depth=sorting->depth;peShapeNode* previous=(peShapeNode*)sorting->previous;
                while(previous && previous->depth<depth) {before=previous;previous=(peShapeNode*)previous->previous;}
                node=(peShapeNode*)sorting->next;
                if(before!=sorting)MoveNode(sorting,before);
                sorting=node;
            }
        }
    }
}
u16 peShapeContainer::Emit(u16 requested) {
    if(!active)return 0;
    u16 remaining=CreateNodes(requested);_EmitParams* params=g_emitParams;peNode* node=nodes;peNode* next;u16 result=remaining;
    while(remaining){next=node->next;((peShapeNode*)node)->Start(owner,shape,params);node=next;--remaining;++params;}
    return result;
}
void peShapeContainer::Start() {
    if(!active) {
        active=1;
        if(shape->flags&0x800000)SetLayerVisibility((GSgfxLayerID)1,true);
        if(shape->flags&0x1000000)SetLayerVisibility((GSgfxLayerID)3,true);
        if(shape->flags&0x2000000)SetLayerVisibility((GSgfxLayerID)5,true);
    }
}
peShapeContainer::~peShapeContainer(){g_particle_debug_stats.node-=0x24;g_particle_debug_stats.total-=0x24;}
peShapeContainer::peShapeContainer(peEmitterNode* emitter,_peShape* data,u16 maximum):peContainer(emitter,0x9c,maximum){shape=data;g_particle_debug_stats.node+=0x24;g_particle_debug_stats.total+=0x24;}

inline void GSgfxLayer::tunitKRegSel(u8 arg1,GSgfxTunitKReg arg2) {
    u32 temp_r6;
    u32 temp_r6_2;
    u32 temp_r6_3;
    u32 temp_r6_4;
    ParticleLayerState *temp_r5;
    ParticleLayerState *temp_r5_2;
    ParticleLayerState *temp_r5_3;
    ParticleLayerState *temp_r5_4;

    switch (arg2) {                                 /* irregular */
    case 0:
        temp_r5 = (ParticleLayerState*)((u8*)this + ((arg1 * 4) & 0x3FC));
        temp_r5->unk1504 = 0xC;
        temp_r6 = 1 << arg1;
        ((ParticleLayerState*)this)->unk16FC = (s32) (((ParticleLayerState*)this)->unk16FC | temp_r6);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B4 = (s32) (((ParticleLayerState*)this)->unk17B4 | temp_r6);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        temp_r5->unk1544 = 0x1C;
        ((ParticleLayerState*)this)->unk1700 = (s32) (((ParticleLayerState*)this)->unk1700 | temp_r6);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B8 = (s32) (((ParticleLayerState*)this)->unk17B8 | temp_r6);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        return;
    case 1:
        temp_r5_2 = (ParticleLayerState*)((u8*)this + ((arg1 * 4) & 0x3FC));
        temp_r5_2->unk1504 = 0xD;
        temp_r6_2 = 1 << arg1;
        ((ParticleLayerState*)this)->unk16FC = (s32) (((ParticleLayerState*)this)->unk16FC | temp_r6_2);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B4 = (s32) (((ParticleLayerState*)this)->unk17B4 | temp_r6_2);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        temp_r5_2->unk1544 = 0x1D;
        ((ParticleLayerState*)this)->unk1700 = (s32) (((ParticleLayerState*)this)->unk1700 | temp_r6_2);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B8 = (s32) (((ParticleLayerState*)this)->unk17B8 | temp_r6_2);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        return;
    case 2:
        temp_r5_3 = (ParticleLayerState*)((u8*)this + ((arg1 * 4) & 0x3FC));
        temp_r5_3->unk1504 = 0xE;
        temp_r6_3 = 1 << arg1;
        ((ParticleLayerState*)this)->unk16FC = (s32) (((ParticleLayerState*)this)->unk16FC | temp_r6_3);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B4 = (s32) (((ParticleLayerState*)this)->unk17B4 | temp_r6_3);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        temp_r5_3->unk1544 = 0x1E;
        ((ParticleLayerState*)this)->unk1700 = (s32) (((ParticleLayerState*)this)->unk1700 | temp_r6_3);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B8 = (s32) (((ParticleLayerState*)this)->unk17B8 | temp_r6_3);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        return;
    case 3:
        temp_r5_4 = (ParticleLayerState*)((u8*)this + ((arg1 * 4) & 0x3FC));
        temp_r5_4->unk1504 = 0xF;
        temp_r6_4 = 1 << arg1;
        ((ParticleLayerState*)this)->unk16FC = (s32) (((ParticleLayerState*)this)->unk16FC | temp_r6_4);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B4 = (s32) (((ParticleLayerState*)this)->unk17B4 | temp_r6_4);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        temp_r5_4->unk1544 = 0x1F;
        ((ParticleLayerState*)this)->unk1700 = (s32) (((ParticleLayerState*)this)->unk1700 | temp_r6_4);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B8 = (s32) (((ParticleLayerState*)this)->unk17B8 | temp_r6_4);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        return;
    }
}


void peShapeContainer::Render() {
    peShapeContainer* arg0=this;
    Vec position, direction, transformed;
    ParticleLight* light0;
    ParticleLight* light1;
    struct LightList {ParticleLight* first;ParticleLight* second;};
    LightList lights;
    s32 var_r7,var_r8;
    f32 temp_f1,temp_f2;
    s32 temp_cr0_eq;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r31;
    s32 temp_r4;
    s32 temp_r9_2;
    u8 var_r0;
    u8 var_r30;
    u8 var_r7_2;
    ParticleLight *temp_r11;
    _peShape *temp_r5;
    ParticleLight *temp_r9;
    peShapeNode *var_r30_2;

    if (arg0->active) {
        if (!arg0->active) {
            var_r0 = 0;
        } else {
            temp_r4 = arg0->shape->flags;
            if ((u16) arg0->count == 0) {
                var_r0 = 0;
            } else if ((s32) g_render_pass != 1) {
                var_r0 = 0;
            } else {
                temp_r0 = ((ParticleLayerState*)g_current_layer)->unk28;
                switch (temp_r0) {                  /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    if (temp_r4 & 0x200000) {
                        var_r0 = 1;
                    } else {
block_31:
                        var_r0 = 0;
                    }
                    break;
                case 2:                             /* switch 1 */
                    if (temp_r4 & 0x400000) {
                        var_r0 = 1;
                    } else if (!(temp_r4 & 0x03E00008)) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 4:                             /* switch 1 */
                    if (temp_r4 & 8) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 1:                             /* switch 1 */
                    if (temp_r4 & 0x800000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 3:                             /* switch 1 */
                    if (temp_r4 & 0x01000000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                case 5:                             /* switch 1 */
                    if (temp_r4 & 0x02000000) {
                        var_r0 = 1;
                    } else {
                        goto block_31;
                    }
                    break;
                default:                            /* switch 1 */
                    var_r0 = 0;
                    break;
                }
            }
        }
        if (var_r0 != 0) {
            temp_r31 = arg0->shape->flags;
            if (temp_r31 & 0x800) {
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkD8C = 2;
                state->unk16B8 = (s32) (state->unk16B8 | 2);
                state->unk16A8 = (s32) (state->unk16A8 | 2);
                state->unk1770 = (s32) (state->unk1770 | 2);
                state->unk1760 = (s32) (state->unk1760 | 2);
                }
            } else {
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkD8C = 0;
                state->unk16B8 = (s32) (state->unk16B8 | 2);
                state->unk16A8 = (s32) (state->unk16A8 | 2);
                state->unk1770 = (s32) (state->unk1770 | 2);
                state->unk1760 = (s32) (state->unk1760 | 2);
                }
            }
            var_r8 = 0;
            if (temp_r31 & 0x40) {
                var_r8 = 2;
            }
            var_r7 = 0;
            if (temp_r31 & 0x20) {
                var_r7 = 2;
            }
            particleEngineSetupTexture(0, arg0->shape->texture, 0, 0, var_r7, var_r8);
            particleEngineSetupBlendMode(2);
            if (temp_r31 & 0x200) {
                temp_r9 = arg0->shape->light0;
                light0 = temp_r9;
                LightList empty={0,0};lights=empty;
                var_r30 = 1;

                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkEAC = 1;

                state->unk16CC = (s32) (state->unk16CC | 1);
                lights.first = temp_r9;
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1784 = (s32) (state->unk1784 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkDB8 = 1;
                state->unk16BC = (s32) (state->unk16BC | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 4);
                state->unk1774 = (s32) (state->unk1774 | 1);
                state->unk1760 = (s32) (state->unk1760 | 4);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unk1170 = 0;
                state->unk1174 = 0;
                state->unk1178 = 0;
                state->unk117C = 1;
                state->unk1180 = 0;
                state->unk16DC = (s32) (state->unk16DC | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1794 = (s32) (state->unk1794 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unk12B0 = 0;
                state->unk12B4 = 0;
                state->unk12B8 = 0;
                state->unk12BC = 1;
                state->unk12C0 = 0;
                state->unk16E0 = (s32) (state->unk16E0 | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1798 = (s32) (state->unk1798 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkF70 = 0xF;
                state->unkF74 = 0xA;
                state->unkF78 = 8;
                state->unkF7C = 0xF;
                state->unk16D4 = (s32) (state->unk16D4 | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk178C = (s32) (state->unk178C | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unk1544 = 0x1C;
                state->unk1700 = (s32) (state->unk1700 | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 0x10);
                state->unk17B8 = (s32) (state->unk17B8 | 1);
                state->unk1760 = (s32) (state->unk1760 | 0x10);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unk1070 = 7;
                state->unk1074 = 6;
                state->unk1078 = 4;
                state->unk107C = 7;
                state->unk16D8 = (s32) (state->unk16D8 | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1790 = (s32) (state->unk1790 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                PSMTXMultVec(g_CameraMatrix,&arg0->shape->position,&position);
                temp_r0_2 = light0->type;
                transformed.x = position.x;
                transformed.y = position.y;
                transformed.z = position.z;
                switch (temp_r0_2) {                /* switch 2; irregular */
                case 2:                             /* switch 2 */
                    light0->position.x = position.x;
                    light0->position.y = position.y;
                    light0->position.z = position.z;
                default:                            /* switch 2 */
block_48:
                    light0->flags = (u16) (light0->flags | 2);
                    break;
                case 1:                             /* switch 2 */
                    light0->position.x = position.x;
                    light0->position.y = position.y;
                    light0->position.z = position.z;
                    goto block_48;
                }

                cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(g_current_layer,0,0,0,0,1,&light0,2,2);
                if (temp_r31 & 0x400) {
                    temp_r11 = arg0->shape->light1;
                    light1 = temp_r11;
                    { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                    state->unkEAC = 2;
                    var_r30 = 2;
                    lights.second = temp_r11;
                    state->unk16CC = (s32) (state->unk16CC | 1);
                    state->unk16A8 = (s32) (state->unk16A8 | 8);
                    state->unk1784 = (s32) (state->unk1784 | 1);
                    state->unk1760 = (s32) (state->unk1760 | 8);
                    }
                    { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                    state->unkEBC = 0xFF;
                    state->unkEC0 = 0xFF;
                    state->unkEC4 = 5;
                    state->unk16D0 = (s32) (state->unk16D0 | 2);
                    state->unk16A8 = (s32) (state->unk16A8 | 8);
                    state->unk1788 = (s32) (state->unk1788 | 2);
                    state->unk1760 = (s32) (state->unk1760 | 8);
                    }
                    { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                    state->unk1184 = 0;
                    state->unk1188 = 0;
                    state->unk118C = 0;
                    state->unk1190 = 1;
                    state->unk1194 = 0;
                    state->unk16DC = (s32) (state->unk16DC | 2);
                    state->unk16A8 = (s32) (state->unk16A8 | 8);
                    state->unk1794 = (s32) (state->unk1794 | 2);
                    state->unk1760 = (s32) (state->unk1760 | 8);
                    }
                    { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                    state->unk12C4 = 0;
                    state->unk12C8 = 0;
                    state->unk12CC = 0;
                    state->unk12D0 = 0;
                    state->unk12D4 = 0;
                    state->unk16E0 = (s32) (state->unk16E0 | 2);
                    state->unk16A8 = (s32) (state->unk16A8 | 8);
                    state->unk1798 = (s32) (state->unk1798 | 2);
                    state->unk1760 = (s32) (state->unk1760 | 8);
                    }
                    { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                    state->unkF80 = 0xF;
                    state->unkF84 = 0xA;
                    state->unkF88 = 0xC;
                    state->unkF8C = 0;
                    state->unk16D4 = (s32) (state->unk16D4 | 2);
                    state->unk16A8 = (s32) (state->unk16A8 | 8);
                    state->unk178C = (s32) (state->unk178C | 2);
                    state->unk1760 = (s32) (state->unk1760 | 8);
                    }
                    { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                    state->unk1080 = 7;
                    state->unk1084 = 7;
                    state->unk1088 = 7;
                    state->unk108C = 0;
                    state->unk16D8 = (s32) (state->unk16D8 | 2);
                    state->unk16A8 = (s32) (state->unk16A8 | 8);
                    state->unk1790 = (s32) (state->unk1790 | 2);
                    state->unk1760 = (s32) (state->unk1760 | 8);
                    }
                    { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                    state->unkDB8 = 2;
                    state->unk16BC = (s32) (state->unk16BC | 1);
                    state->unk16A8 = (s32) (state->unk16A8 | 4);
                    state->unk1774 = (s32) (state->unk1774 | 1);
                    state->unk1760 = (s32) (state->unk1760 | 4);
                    }

                    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(g_current_layer,1,0,0,0,1,&light1,0,2);
                    if (PSVECSquareMag(&arg0->shape->position) < 0.00001f) {
                        direction.x = 0.0f;
                        direction.y = -1.0f;
                        direction.z = 0.0f;
                    } else {
                        temp_r5 = arg0->shape;
                        temp_f2 = -temp_r5->position.y;
                        temp_f1 = -temp_r5->position.z;
                        direction.y = temp_f2;
                        direction.x = -temp_r5->position.x;
                        direction.z = temp_f1;
                        PSVECNormalize(&direction,&direction);
                    }
                    PSMTXMultVecSR(g_CameraMatrix,&direction,&direction);
                    temp_r0_3 = light1->type;
                    if (temp_r0_3 < 2) {
                        if (temp_r0_3 < 0) {

                        } else {
                            light1->direction.x = direction.x;
                            light1->direction.y = direction.y;
                            light1->direction.z = direction.z;
                            light1->flags = (u16) (light1->flags | 4);
                        }
                    }
                }
                var_r7_2 = 0;
                ((ParticleLayerState*)g_current_layer)->unkD94 = var_r30;
loop_62:
                if (var_r7_2 < 8U) {
                    if (var_r7_2 < var_r30) {
                        temp_r9_2 = (var_r7_2 * 4) & 0x3FC;
                        ((ParticleLayerState*)g_current_layer)->lights[var_r7_2]=(&lights.first)[var_r7_2];
                    } else {
                        ((ParticleLayerState*)g_current_layer)->lights[var_r7_2]=0;
                    }
                    var_r7_2 += 1;
                    goto loop_62;
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unk16BC = (s32) (state->unk16BC | 0x10);
                state->unk16A8 = (s32) (state->unk16A8 | 4);
                state->unk1774 = (s32) (state->unk1774 | 0x10);
                state->unk1760 = (s32) (state->unk1760 | 4);
                }
            } else {
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkDB8 = 0;
                state->unk16BC = (s32) (state->unk16BC | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 4);
                state->unk1774 = (s32) (state->unk1774 | 1);
                state->unk1760 = (s32) (state->unk1760 | 4);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkEAC = 1;
                state->unk16CC = (s32) (state->unk16CC | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1784 = (s32) (state->unk1784 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkEB0 = 0;
                state->unkEB4 = 0;
                state->unkEB8 = 0xFF;
                state->unk16D0 = (s32) (state->unk16D0 | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1788 = (s32) (state->unk1788 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unk1170 = 0;
                state->unk1174 = 0;
                state->unk1178 = 0;
                state->unk117C = 1;
                state->unk1180 = 0;
                state->unk16DC = (s32) (state->unk16DC | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1794 = (s32) (state->unk1794 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unk12B0 = 0;
                state->unk12B4 = 0;
                state->unk12B8 = 0;
                state->unk12BC = 1;
                state->unk12C0 = 0;
                state->unk16E0 = (s32) (state->unk16E0 | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1798 = (s32) (state->unk1798 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                g_current_layer->tunitKRegSel(0,PARTICLE_KREG_DEFAULT);
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkF70 = 0xF;
                state->unkF74 = 0xE;
                state->unkF78 = 8;
                state->unkF7C = 0xF;
                state->unk16D4 = (s32) (state->unk16D4 | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk178C = (s32) (state->unk178C | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unk1070 = 7;
                state->unk1074 = 6;
                state->unk1078 = 4;
                state->unk107C = 7;
                state->unk16D8 = (s32) (state->unk16D8 | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1790 = (s32) (state->unk1790 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
            }
            ((ParticleLayerState*)g_current_layer)->unk199C = GSgfxVFGetPredef(4);
            var_r30_2=(peShapeNode*)arg0->nodes;
            while(var_r30_2 != NULL) {
                var_r30_2->Render(arg0->shape);
                var_r30_2=(peShapeNode*)var_r30_2->next;
            }
            particleEngineSetDefaultRenderState(1);
        }
    }
}


void peShapeNode::Start(peEmitterNode* emitter,_peShape* shape,_EmitParams* params) {
    Vec randomAngles;
    Vec scale;
    u32 flags=shape->flags;
    peNode::Start(emitter,params);
    flips=0;
    PSVECScale(&shape->scaleRange,&scale,HSD_Randf());
    baseScale.x=scale.x;baseScale.y=scale.y;baseScale.z=scale.z;
    PSVECAdd(&baseScale,&shape->scale,&baseScale);
    randomRotation.x=0.0f;randomRotation.y=0.0f;randomRotation.z=0.0f;randomRotation.w=1.0f;
    worldPosition.x=0.0f;worldPosition.y=0.0f;worldPosition.z=0.0f;
    worldRotation.x=0.0f;worldRotation.y=0.0f;worldRotation.z=0.0f;worldRotation.w=1.0f;
    worldScale=unitScaleVector;
    if(!(emitter->emitter->flags&0x400)) {
        EulerToQuat(&shape->rotation,&localRotation);
        if(flags&0x1c7000) {
            if(flags&0x1000)randomAngles.x=6.2831855f*HSD_Randf();else randomAngles.x=0.0f;
            if(flags&0x2000)randomAngles.y=6.2831855f*HSD_Randf();else randomAngles.y=0.0f;
            if(flags&0x4000)randomAngles.z=6.2831855f*HSD_Randf();else randomAngles.z=0.0f;
            if((flags&0x40000) && HSD_Randf()<0.5f)flips|=1;
            if((flags&0x80000) && HSD_Randf()<0.5f)flips|=2;
            if((flags&0x100000) && HSD_Randf()<0.5f)flips|=4;
            EulerToQuat(&randomAngles,&randomRotation);
        }
    }
    angularSpeed=shape->angularSpeed;
    if(flags&0x8000)angularSpeed.x*=HSD_Randf();
    if(flags&0x10000)angularSpeed.y*=HSD_Randf();
    if(flags&0x20000)angularSpeed.z*=HSD_Randf();
}

void peShapeNode::Render(_peShape* shape) {
    Mtx sp50;
    Mtx sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;
    u32 temp_r0;

    temp_r31 = shape->flags;
    temp_r4 = color;
    sp1C = 0;
    { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
    state->unk14F4 = temp_r4;
    sp18 = temp_r4;
    state->unk16F8 = (s32) (state->unk16F8 | 1);
    state->unk16A8 = (s32) (state->unk16A8 | 0x10);
    state->unk17B0 = (s32) (state->unk17B0 | 1);
    state->unk1760 = (s32) (state->unk1760 | 0x10);
    }
    if (temp_r31 & 0x200) {
        temp_r5 = color;
        temp_r4_2 = shape->ambient;
        sp10 = temp_r5;
        { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
        state->unkE9C = temp_r4_2;
        state->unkEA4 = temp_r5;
        sp14 = temp_r4_2;
        state->unk16C4 = (s32) (state->unk16C4 | 1);
        state->unk16C8 = (s32) (state->unk16C8 | 1);
        state->unk16A8 = (s32) (state->unk16A8 | 4);
        state->unk177C = (s32) (state->unk177C | 1);
        state->unk1780 = (s32) (state->unk1780 | 1);
        state->unk1760 = (s32) (state->unk1760 | 4);
        }
        if (temp_r31 & 0x400) {
            temp_r3 = color;
            sp8 = temp_r3;
            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unkEA0 = (s32) 0;
            state->unkEA8 = temp_r3;
            spC = 0;
            state->unk16C4 = (s32) (state->unk16C4 | 2);
            state->unk16C8 = (s32) (state->unk16C8 | 2);
            state->unk16A8 = (s32) (state->unk16A8 | 4);
            state->unk177C = (s32) (state->unk177C | 2);
            state->unk1780 = (s32) (state->unk1780 | 2);
            state->unk1760 = (s32) (state->unk1760 | 4);
            }
        }
    }
    PSMTXQuat(sp20, &worldRotation);
    PSMTXScale(sp50, worldScale.x, worldScale.y, worldScale.z);
    PSMTXConcat(sp20, sp50, sp50);
    PSMTXTransApply(sp50, sp50, worldPosition.x, worldPosition.y, worldPosition.z);
    pushMult__16GSgfxMatrixStackFP5GSmtx(((ParticleLayerState*)g_current_layer)->unk19A0, sp50);
    temp_r0 = temp_r31 & 7;
    switch (temp_r0) {
    case 0:
        drawCube__10GSgfxLayerFv(g_current_layer);
        break;
    case 1:
        drawCylinder__10GSgfxLayerFUc(g_current_layer, shape->segments1);
        break;
    case 2:
        drawDodecaedron__10GSgfxLayerFv(g_current_layer);
        break;
    case 3:
        drawIcosahedron__10GSgfxLayerFv(g_current_layer);
        break;
    case 4:
        drawOctahedron__10GSgfxLayerFv(g_current_layer);
        break;
    case 7:
        drawTorus__10GSgfxLayerFfUcUc(g_current_layer,shape->radius,shape->segments0,shape->segments1);
        break;
    case 6:
        drawSphere__10GSgfxLayerFUc(g_current_layer, shape->segments1);
        break;
    default:
        drawSphere__10GSgfxLayerFUcUc(g_current_layer, shape->segments0, shape->segments1);
        break;
    }
    pop__16GSgfxMatrixStackFv(((ParticleLayerState*)g_current_layer)->unk19A0);
}

#include <libc/math.h>
static inline f32 shapeSpline(ShapeSpline* spline,f32 progress) {
    if(!spline || !(spline->flags&3))return 1.0f;
    f32 difference=spline->time-progress;if(difference<0.0f)difference=-difference;
    if(difference<=0.00001f)return spline->value;
    return peSplineGetValue(spline,progress);
}
static inline u8 shapeColorByte(f32 value) {
    if(!(value>=0.0f))return 0;
    if(value>255.0f)return 255;
    return (u8)value;
}
bool peShapeNode::Update(peEmitterNode* emitter,_peShape* shape,f32 delta) {
    if(!peNode::Update(emitter,delta))return false;
    u32 emitterFlags=emitter->emitter->flags;
    f32 progress=1.0f-time/life;
    Vec angles;
    if(emitterFlags&0x400) {
        Vec direction=velocity;
        if(emitterFlags&0x40) {
            Mtx rotation;
            PSMTXQuat(rotation,(Quaternion*)((u8*)transform+12));
            PSMTXMultVecSR(rotation,&direction,&direction);
        }
        f32 horizontal=sqrtf(direction.x*direction.x+direction.z*direction.z);
        angles.x=(f32)atan2(-direction.y,horizontal);
        angles.y=(f32)atan2(direction.x,direction.z);angles.z=0.0f;
        EulerToQuat(&angles,&localRotation);
    } else if(shape->flags&0x100) {
        angles.x=shape->rotation.x*shapeSpline(shape->rotationSpline[0],progress);
        angles.y=shape->rotation.y*shapeSpline(shape->rotationSpline[1],progress);
        angles.z=shape->rotation.z*shapeSpline(shape->rotationSpline[2],progress);
        EulerToQuat(&angles,&localRotation);
    } else {
        Vec rotation;Quaternion step;
        PSVECScale(&angularSpeed,&rotation,delta);angles=rotation;
        EulerToQuat(&angles,&step);PSQUATMultiply(&localRotation,&step,&localRotation);
    }
    Vec scale;
    scale.x=baseScale.x*shapeSpline(shape->scaleSpline[0],progress);
    scale.y=baseScale.y*shapeSpline(shape->scaleSpline[1],progress);
    scale.z=baseScale.z*shapeSpline(shape->scaleSpline[2],progress);
    peColorSplineGetValue(&color,shape->colorSpline,progress);
    u8* rgba=(u8*)&color;
    rgba[0]=shapeColorByte((f32)rgba[0]*emitter->color[0]);
    rgba[1]=shapeColorByte((f32)rgba[1]*emitter->color[1]);
    rgba[2]=shapeColorByte((f32)rgba[2]*emitter->color[2]);
    rgba[3]=shapeColorByte((255.0f*emitter->color[3])*shapeSpline(shape->alphaSpline,progress));
    Quaternion flipped;
    flipped.x=(flips&1)?-localRotation.x:localRotation.x;
    flipped.y=(flips&2)?-localRotation.y:localRotation.y;
    flipped.z=(flips&4)?-localRotation.z:localRotation.z;
    flipped.w=localRotation.w;
    ShapeTransform local;
    local.position=position;PSQUATMultiply(&randomRotation,&flipped,&local.rotation);local.scale=scale;
    peNodeTransformsConcat((ShapeTransform*)&worldPosition,transform,&local,0);
    Vec distance;PSVECSubtract(&worldPosition,&g_CameraPosition,&distance);
    Vec copy=distance;depth=PSVECDotProduct(&g_CameraLookDir,&copy);
    return true;
}
