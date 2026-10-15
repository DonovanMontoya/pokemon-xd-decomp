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
