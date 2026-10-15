#ifndef PE_CONTAINER_PRIVATE_HPP
#define PE_CONTAINER_PRIVATE_HPP
#include <global.h>
#include <dolphin/mtx.h>
#include <libc/string.h>
struct _peEmitter {u32 flags;};
struct peEmitterNode {u8 reserved00[0xa8];u8 world[0x28];u8 previousWorld[0x28];f32 depth;_peEmitter* emitter;void* containers;};
struct peNode {u8 reserved00[0x20];void* transform;u32 reserved24;peNode* next;peNode* previous;};
struct GSgfxVF;
enum GSgfxPrimType { PARTICLE_PRIMITIVE_DEFAULT };
enum GSgfxLayerID { PARTICLE_LAYER_DEFAULT };
struct GSgfxLayer {u16 tokenMark();void SetLayerVisibility(bool);};
struct GSgfxDL {u16 flags,stride;u8* data;u32 size,reserved;};
struct ParticleDebugStats {u32 bank,node,displayList,renderData,reserved10,total,reserved18[3];};
struct peContainer {
    peEmitterNode* owner;peContainer* next;u8* memory;peNode* freeNodes;peNode* nodes;u16 count,capacity;u8 dirty,active;u8 reserved1a[2];
    peContainer(peEmitterNode*,u32,u16);virtual ~peContainer();virtual void Start();virtual void PreUpdate();virtual u16 Emit(u16)=0;virtual void Update(f32)=0;virtual void Render()=0;virtual void Stop()=0;
    void MoveNode(peNode*,peNode*);void RemoveAll();void RemoveNode(peNode*);u16 CreateNodes(u16);static void SetLayerVisibility(GSgfxLayerID,bool);
};
struct peRenderContainer:peContainer {
    u8 swapped,swapIndex;u8 reserved22[2];u32 renderBytes;GSgfxDL displayLists[2];u8* renderData[2];u16 tokens[2];
    peRenderContainer(peEmitterNode*,u32,u16,GSgfxVF*,GSgfxPrimType,u8,u8,bool);virtual ~peRenderContainer();virtual void Start()=0;virtual void PreUpdate();
    void ResetSwap();void InitSwap();void ResolveMultipleSwap();void MarkForSwap();
};
extern "C" {
extern GSgfxLayer* g_current_layer;extern u16 g_bank_token;extern ParticleDebugStats g_particle_debug_stats;
GSgfxLayer* GSgfxLayerFindByID(GSgfxLayerID);void GSgfxTokenWaitForClear(u16);
void* GSmemAllocClr(u32);void* GSmemAllocAlignClr(u32,u32);void GSmemFree(void*);u32 GSmemGetSize(void*);
void GSgfxDLCreate(GSgfxDL*,GSgfxPrimType,GSgfxVF*,u16);void GSgfxDLFree(GSgfxDL*);void DCFlushRange(void*,u32);
}
#endif
