#include <game/pxdvs/GSAPI/GSparticle/peParticlePrivate.hpp>
void peParticleContainer::Stop() {
    if(active) {
        PreUpdate();active=0;u32 flags=particle->flags;
        if(flags&0x20000000)SetLayerVisibility((GSgfxLayerID)1,false);
        if(flags&0x40000000)SetLayerVisibility((GSgfxLayerID)3,false);
        if(flags&0x80000000)SetLayerVisibility((GSgfxLayerID)5,false);
        peParticleNode* node=(peParticleNode*)nodes;
        while(node) {
            s16* indices=0;node->live=0;GSgfxDL* list=&displayLists[swapIndex];
            if(list->flags&1)indices=(s16*)(list->data+(((node->sortIndex*4)&0xfffc)*list->stride)+3);
            u16 vertices=4;
            while(vertices--) {indices[0]=-1;indices[1]=-1;indices[2]=-1;indices+=3;if((particle->flags>>25)&1)*indices++=-1;}
            list->flags|=2;node=(peParticleNode*)node->next;
        }
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
