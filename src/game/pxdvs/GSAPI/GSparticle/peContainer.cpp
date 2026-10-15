#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>
void peRenderContainer::ResetSwap() {}
void peRenderContainer::InitSwap() {
    if((displayLists[0].flags&1)==1) {tokens[0]=0;displayLists[0].flags|=2;if((displayLists[1].flags&1)==1){tokens[1]=0;displayLists[1].flags|=2;}}
}
void peRenderContainer::ResolveMultipleSwap() {
    if((displayLists[0].flags&1)==1 && (displayLists[1].flags&1)==1 && swapped) {swapIndex^=1;swapped=0;}
}
void peRenderContainer::MarkForSwap() {
    if((displayLists[0].flags&1)==1) {
        u16 token=g_current_layer->tokenMark();g_bank_token=token;tokens[swapIndex]=token;
        if((displayLists[1].flags&1)==1){swapIndex^=1;swapped=1;}
    }
}
void peRenderContainer::PreUpdate() {
    if(active && (displayLists[0].flags&1)==1) {
        if(tokens[swapIndex]) {GSgfxTokenWaitForClear(tokens[swapIndex]);tokens[swapIndex]=0;}
        if((displayLists[1].flags&1)==1 && swapped) {
            swapped=0;
            if(dirty) {
                u8 current=swapIndex;
                memcpy(displayLists[current].data,displayLists[!current].data,displayLists[0].size);
                u32 flagsOffset=swapIndex*16+40;u16* flags=(u16*)((u32)this+flagsOffset);*flags|=2;dirty=0;
            }
        }
    }
}
void peContainer::MoveNode(peNode* node,peNode* after) {
    peNode* next=node->next;peNode* previous=node->previous;
    if(next)next->previous=previous;if(previous)previous->next=next;else nodes=next;
    peNode* before=after->previous;after->previous=node;node->next=after;node->previous=before;
    if(before){before->next=node;return;}nodes=node;
}
void peContainer::RemoveAll() {
    peNode* node=nodes;if(!node)return;
    while(node->next)node=node->next;
    peNode* free=freeNodes;node->next=free;if(free)free->previous=node;
    freeNodes=nodes;nodes=0;count=0;dirty=1;
}
void peContainer::RemoveNode(peNode* node) {
    peNode* next=node->next;peNode* previous=node->previous;
    if(next)next->previous=previous;if(previous)previous->next=next;else nodes=next;
    node->previous=0;peNode* free=freeNodes;node->next=free;if(free)free->previous=node;
    freeNodes=node;--count;dirty=1;
}
u16 peContainer::CreateNodes(u16 requested) {
    peNode* next;
    peNode* first=freeNodes;if(!first)return 0;
    peNode* last=first;u16 created=1;
    while((next=last->next)!=0 && created<requested){last=next;++created;}
    if(next)next->previous=0;
    freeNodes=last->next;peNode* old=nodes;last->next=old;if(old)old->previous=last;
    first->previous=0;nodes=first;count+=created;dirty=1;return created;
}
void peContainer::SetLayerVisibility(GSgfxLayerID id,bool visible) {GSgfxLayer* layer=GSgfxLayerFindByID(id);if(layer)layer->SetLayerVisibility(visible);}
void peContainer::PreUpdate() {}
void peContainer::Start(){if(!active)active=1;}
peContainer::~peContainer() {
    if(memory){u32 size=GSmemGetSize(memory);g_particle_debug_stats.node-=size;g_particle_debug_stats.total-=size;GSmemFree(memory);memory=0;}
}
peContainer::peContainer(peEmitterNode* emitter,u32 nodeBytes,u16 maximum):owner(emitter),next(0),memory(0),freeNodes(0),nodes(0),count(0),capacity(maximum),dirty(0),active(0) {
    u32 totalNodes=maximum;
    u32 bytes=totalNodes*nodeBytes;
    u32 localTransform=(owner->emitter->flags>>6)&1;
    if(localTransform)bytes+=totalNodes*0x28;
    memory=(u8*)GSmemAllocClr(bytes);if(!memory)return;
    u32 size=GSmemGetSize(memory);g_particle_debug_stats.node+=size;g_particle_debug_stats.total+=size;
    freeNodes=(peNode*)memory;peNode* node;u8* cursor=(u8*)freeNodes;peNode* previous=0;
    for(u32 i=0;i<totalNodes;++i) {
        node=(peNode*)cursor;cursor+=nodeBytes;
        if(localTransform){node->transform=cursor;cursor+=0x28;}else node->transform=emitter->world;
        node->previous=previous;if(previous)previous->next=node;previous=node;
    }
    dirty=1;
}
peRenderContainer::~peRenderContainer() {
    if((displayLists[0].flags&1)==1) {
        g_particle_debug_stats.displayList-=displayLists[0].size;g_particle_debug_stats.total-=displayLists[0].size;GSgfxDLFree(&displayLists[0]);
        if((displayLists[1].flags&1)==1){g_particle_debug_stats.displayList-=displayLists[1].size;g_particle_debug_stats.total-=displayLists[1].size;GSgfxDLFree(&displayLists[1]);}
        if(renderData[0]) {
            renderData[0]-=0x40000000;u32 size=GSmemGetSize(renderData[0]);u32 total=g_particle_debug_stats.total;u32 data=g_particle_debug_stats.renderData;g_particle_debug_stats.total=total-size;g_particle_debug_stats.renderData=data-size;
            if(renderData[0]){GSmemFree(renderData[0]);renderData[0]=0;}
        }
    }
}
peRenderContainer::peRenderContainer(peEmitterNode* emitter,u32 nodeBytes,u16 maximum,GSgfxVF* format,GSgfxPrimType primitive,u8 vertices,u8 stride,bool doubleBuffer):peContainer(emitter,nodeBytes,maximum),swapped(0),swapIndex(0),renderBytes(0) {
    u32 aligned=maximum*stride;
    u32 bytes=aligned;memset(&displayLists[0],0,0x10);memset(&displayLists[1],0,0x10);renderData[0]=0;renderData[1]=0;tokens[0]=0;tokens[1]=0;
    aligned=(bytes+31)&~31;u32 allocate=aligned;if(doubleBuffer)allocate=aligned*2;
    u8* data=(u8*)GSmemAllocAlignClr(allocate,32);if(!data)return;
    u32 indices=maximum*vertices;GSgfxDLCreate(&displayLists[0],primitive,format,(u16)indices);
    if((displayLists[0].flags&1)!=1){if(data)GSmemFree(data);return;}
    if(doubleBuffer)GSgfxDLCreate(&displayLists[1],primitive,format,(u16)indices);
    u32 size=GSmemGetSize(data);
    u32 display0=displayLists[0].size,display1=displayLists[1].size;
    u32 oldDisplay=g_particle_debug_stats.displayList,oldData=g_particle_debug_stats.renderData,oldTotal=g_particle_debug_stats.total;
    g_particle_debug_stats.displayList=display0+(display1+oldDisplay);
    g_particle_debug_stats.renderData=oldData+size;
    g_particle_debug_stats.total=size+(display0+display1+oldTotal);
    if((displayLists[1].flags&1)==1){DCFlushRange(data,aligned*2);renderData[0]=data+0x40000000;renderData[1]=renderData[0]+aligned;}
    else {DCFlushRange(data,bytes);renderData[0]=data+0x40000000;}
    renderBytes=bytes;
    memset((displayLists[0].flags&1)?displayLists[0].data+3:0,255,maximum*(vertices*((displayLists[0].flags&1)?displayLists[0].stride:0)));displayLists[0].flags|=2;
    if((displayLists[1].flags&1)==1){memset((displayLists[1].flags&1)?displayLists[1].data+3:0,255,maximum*(vertices*((displayLists[1].flags&1)?displayLists[1].stride:0)));displayLists[1].flags|=2;}
}
