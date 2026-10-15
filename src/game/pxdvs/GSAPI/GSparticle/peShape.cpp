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
            peShapeNode* node=(peShapeNode*)nodes->next;
            while(node) {
                peShapeNode* before=node;peShapeNode* previous=(peShapeNode*)node->previous;
                while(previous && previous->depth<node->depth) {before=previous;previous=(peShapeNode*)previous->previous;}
                peShapeNode* next=(peShapeNode*)node->next;
                if(before!=node)MoveNode(node,before);
                node=next;
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
