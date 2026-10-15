#ifndef PE_EMITTER_PRIVATE_HPP
#define PE_EMITTER_PRIVATE_HPP
#include <global.h>
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct peEmitterNode;
struct _EmitParams { f32 time, fraction; u8 reserved[0x40]; _EmitParams() { time = 0.0f; fraction = 0.0f; } };
struct _peEmitter { u32 flags, flags2; u8 reserved08[0x10]; f32 startTime, endTime; u8 reserved20[8]; f32 duration; u8 reserved2c[0x10c]; struct Resource* resources; };
struct Resource { u32 reserved00, kind; void* data; Resource* next; };
struct peContainer;

struct peContainer {
    peEmitterNode* owner; peContainer* next; u32 reserved08; peEmitterNode* freeNodes; peEmitterNode* nodes;
    u16 count; u8 reserved16[3]; u8 active; u8 reserved1a[2];
    virtual ~peContainer();
    virtual void Start(); virtual void PreUpdate(); virtual u16 Emit(u16); virtual void Update(f32); virtual void Render(); virtual void Stop();
};
struct EmitterTransforms { Vec position; Quaternion rotation; Vec scale; };
struct peEmitterNode {
    u32 reserved00; f32 life; Vec basePosition; u8 reserved14[0xc]; void* transformParent; u32 reserved24; peEmitterNode* next; peEmitterNode* previous;
    f32 lastLoop; u8 reserved34[0x14]; u16 flags, count; u8 reserved4c[0xc]; Vec scale; Quaternion localRotation; Vec offset; Quaternion orientation; u8 reserved90[0x18]; EmitterTransforms world, previousWorld; f32 depth;
    _peEmitter* emitter; peContainer* containers;
    void Stop(_peEmitter*); void Render(_peEmitter*); void Release(); void SetLastLoop(); void CreateWorldParams();
    bool Update(peEmitterNode*, _peEmitter*, f32); void Start(peEmitterNode*, _peEmitter*, _EmitParams*);
};
struct peEmitterContainer : peContainer {
    _peEmitter* emitter;
    virtual ~peEmitterContainer();
    void Stop(); void Render(); bool DoRender(); void Update(f32); u16 Emit(u16); void PreUpdate();
};
struct ParticleLayer { u8 reserved00[0x28]; s32 kind; };
extern "C" {
extern ParticleLayer* g_current_layer;
extern s32 g_render_pass;
extern _EmitParams* g_emitParams;
void RemoveAll__11peContainerFv(peContainer*);
u16 CreateNodes__11peContainerFUs(peContainer*,u16);
void RemoveNode__11peContainerFP6peNode(peContainer*, peEmitterNode*);
void MoveNode__11peContainerFP6peNodeP6peNode(peContainer*, peEmitterNode*, peEmitterNode*);
}
typedef char EmitterNodeSizeCheck[sizeof(peEmitterNode) == 0x104 ? 1 : -1];
typedef char EmitterNodeWorldOffsetCheck[offsetof(peEmitterNode, world) == 0xa8 ? 1 : -1];
typedef char EmitterContainerSizeCheck[sizeof(peEmitterContainer) == 0x24 ? 1 : -1];
#endif
