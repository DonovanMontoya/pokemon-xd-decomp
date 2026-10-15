#include <game/pxdvs/GSAPI/GSparticle/peParticlePrivate.hpp>
static inline void invalidateParticle(peParticleNode* node,u32 flags,GSgfxDL* list) {
    u16* indices;
    u32 extended=(flags>>25)&1;
    indices=0;
    node->live=0;
    u16 vertex=node->sortIndex*4;
    if(list->flags&1)indices=(u16*)(list->data+(vertex*list->stride)+3);
    u16 vertices=4;
    while(vertices--) {indices[0]=0xffff;indices[1]=0xffff;indices[2]=0xffff;indices+=3;if(extended)*indices++=0xffff;}
    list->flags|=2;
}
void peParticleContainer::Stop() {
    if(active) {
        PreUpdate();active=0;u32 flags=particle->flags;
        if(flags&0x20000000)SetLayerVisibility((GSgfxLayerID)1,false);
        if(flags&0x40000000)SetLayerVisibility((GSgfxLayerID)3,false);
        if(flags&0x80000000)SetLayerVisibility((GSgfxLayerID)5,false);
        peParticleNode* node=(peParticleNode*)nodes;
        while(node){invalidateParticle(node,particle->flags,&displayLists[swapIndex]);node=(peParticleNode*)node->next;}
        RemoveAll();ResetSwap();
    }
}
extern "C" {
extern s32 g_render_pass;
void GSgfxVFSetArray(GSgfxVF*,s32,s32,void*,u8,u32);
void particleEngineSetupTevStages(u32,u32,s32);
void particleEngineSetupBlendMode(u32);
void particleEngineSetupTexture(u8,void*,s32,s32,s32,s32);
void dlDraw__10GSgfxLayerFP7GSgfxDL(GSgfxLayer*,GSgfxDL*);
}
static inline u32 &layerWord(u32 offset) {return *(u32*)((u8*)g_current_layer+offset);}
static inline u8 visible(peParticleContainer* c) {
    if(!c->active)return 0;
    if(!c->count)return 0;
    if(g_render_pass!=1)return 0;
    u32 flags=c->particle->flags;
    switch(layerWord(0x28)){
    case 0:if(flags&0x8000000)return 1;break;
    case 2:if(flags&0x10000000)return 1;if(!(flags&0xf8000800))return 1;break;
    case 4:if(flags&0x800)return 1;break;
    case 1:if(flags&0x20000000)return 1;break;
    case 3:if(flags&0x40000000)return 1;break;
    case 5:if(flags&0x80000000)return 1;break;
    default:return 0;}
    return 0;
}
void peParticleContainer::Render() {
    if(active&&visible(this)) {
        ResolveMultipleSwap();u32 flags=particle->flags;u32 extended=(flags>>25)&1;
        if(flags&0x200) {
            u8* layer=(u8*)g_current_layer;
            *(u32*)(layer+0xd8c)=2;*(u32*)(layer+0x16b8)|=2;*(u32*)(layer+0x16a8)|=2;*(u32*)(layer+0x1770)|=2;*(u32*)(layer+0x1760)|=2;
        } else {
            u8* layer=(u8*)g_current_layer;
            *(u32*)(layer+0xd8c)=0;*(u32*)(layer+0x16b8)|=2;*(u32*)(layer+0x16a8)|=2;*(u32*)(layer+0x1770)|=2;*(u32*)(layer+0x1760)|=2;
        }
        particleEngineSetupBlendMode(flags&7);
        GSgfxDL *list=&displayLists[swapIndex];u8 *data=(u8*)renderData[swapIndex];GSgfxVF *format=(list->flags&1)?(GSgfxVF*)list->reserved:0;
        if(extended) {
            GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x30,4,renderBytes);GSgfxVFSetArray(format,12,3,data+0x34,4,renderBytes);GSgfxVFSetArray(format,13,3,uv,4,0x20);
        } else {
            GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x30,4,renderBytes);GSgfxVFSetArray(format,13,3,uv,4,0x20);
        }
        if(flags&0x100000) {
            particleEngineSetupTevStages(0,extended,0xc00000==(flags&0xc00000));
            layerWord(0x1998)=0x80;layerWord(0x199c)=(u32)format;
            peParticleNode* node=(peParticleNode*)nodes;
            while(node){node->Render(particle,&displayLists[swapIndex],(char*)renderData[swapIndex]);node=(peParticleNode*)node->next;}
        } else {
            particleEngineSetupTevStages(0,extended,0);
            s32 wrapT=0;if(flags&0x100)wrapT=2;
            _peParticle* definition=particle;
            s32 wrapS=0;if(flags&0x80)wrapS=2;
            particleEngineSetupTexture(0,definition->texture,(flags>>12)&3,(flags>>14)&3,wrapS,wrapT);
            dlDraw__10GSgfxLayerFP7GSgfxDL(g_current_layer,&displayLists[swapIndex]);
        }
        MarkForSwap();
    }
}
u16 peParticleContainer::Emit(u16 requested) {
    if(!active)return 0;
    u16 remaining=CreateNodes(requested);_EmitParams* params=g_emitParams;peNode* node=nodes;peNode* next;u16 result=remaining;
    while(remaining){next=node->next;((peParticleNode*)node)->Start(owner,particle,&displayLists[swapIndex],params);node=next;--remaining;++params;}
    return result;
}
void peParticleContainer::Start() {
    if(!active){active=1;u32 flags=particle->flags;InitSwap();
        if(flags&0x20000000)SetLayerVisibility((GSgfxLayerID)1,true);
        if(flags&0x40000000)SetLayerVisibility((GSgfxLayerID)3,true);
        if(flags&0x80000000)SetLayerVisibility((GSgfxLayerID)5,true);
    }
}
peParticleContainer::~peParticleContainer(){if(sorted)delete[] sorted;g_particle_debug_stats.node-=0x7c;g_particle_debug_stats.total-=0x7c;}
void peParticleContainer::DepthSort() {
    if(active && (particle->flags&0x80000) && count>=2 && sorted) {
        u8 changed=0;
        for(s32 i=1;i<(s32)capacity;++i) {
            peParticleNode* node=sorted[i];
            if(node->live) {
                s32 position=i;
                for(;;) {
                    s32 previous=position;
                    if(!sorted)previous=-1;
                    else {
                        peParticleNode** cursor=&sorted[position];
                        for(;;) {
                            if(previous<=0){previous=-1;break;}
                            peParticleNode* before=cursor[-1];--cursor;--previous;
                            if(before->live)break;
                        }
                    }
                    if(previous>=0) {
                        peParticleNode* before=sorted[previous];
                        u8 move;
                        if(before->depth==node->depth)move=0;
                        else if(before->sortIndex<node->sortIndex)move=before->depth<node->depth;
                        else move=before->depth>node->depth;
                        if(move){sorted[position]=before;position=previous;changed=1;continue;}
                    }
                    sorted[position]=node;break;
                }
            }
        }
        if(changed) {
            u32 extended=(particle->flags>>25)&1;
            GSgfxDL* list=&displayLists[swapIndex];
            for(s32 i=0;i<(s32)capacity;++i) {
                peParticleNode* node=sorted[i];
                if(node->live && node->sortIndex!=(u16)i) {
                    node->sortIndex=i;
                    u16 vertex=node->index*(u16)((extended!=0)+13);
                    u16* indices=(list->flags&1)?(u16*)(list->data+(((i*4)&0xfffc)*list->stride)+3):0;
                    u16 j=0;
                    if(extended) {
                        for(;j<4;++j){s16 uv=j*2;indices[0]=vertex+j*3;indices[1]=vertex;indices[2]=vertex;indices[3]=uv;indices+=4;}
                    } else {
                        for(;j<4;++j){s16 uv=j*2;indices[0]=vertex+j*3;indices[1]=vertex;indices[2]=uv;indices+=3;}
                    }
                }
            }
            list->flags|=2;dirty=1;
        }
    }
}

void peParticleContainer::Update(f32 time) {
    if(active) {
        peParticleNode* node=(peParticleNode*)nodes;
        while(node) {
            peParticleNode* next=(peParticleNode*)node->next;
            peEmitterNode* emitter;
            _peParticle* definition=particle;
            emitter=owner;
            char* data=(char*)renderData[swapIndex];
            u8 alive;
            if(!data)alive=0;
            else if(!node->peNode::Update(emitter,time))alive=0;
            else {
                f32 progress=1.0f-(node->time/node->life);
                if(definition->flags&0x10000) {
                    ParticleSpline* spline=definition->angleSpline;
                    f32 value;
                    if(!spline || !(spline->flags&3))value=1.0f;
                    else {
                        f32 difference=spline->time-progress;if(difference<0.0f)difference=-difference;
                        if(difference<=0.00001f)value=spline->value;else value=peSplineGetValue(spline,progress);
                    }
                    node->angle=definition->angle*value;
                }
                node->angle=node->angularSpeed*time+node->angle;
                node->UpdateRenderData(emitter,definition,data,progress);
                alive=1;
            }
            if(!alive){invalidateParticle(node,particle->flags,&displayLists[swapIndex]);RemoveNode(node);}
            node=next;
        }
        DepthSort();
    }
}
