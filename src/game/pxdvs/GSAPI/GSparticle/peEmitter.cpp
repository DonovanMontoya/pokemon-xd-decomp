#include <game/pxdvs/GSAPI/GSparticle/peEmitterPrivate.hpp>
void peEmitterNode::Stop(_peEmitter*) {
    peContainer* container = containers;
    while (container) { container->Stop(); container = container->next; }
}
void peEmitterNode::Render(_peEmitter*) {
    peContainer* container = containers;
    if (count == 0) return;
    while (container) { container->Render(); container = container->next; }
}
void peEmitterNode::Release() {
    peContainer* next;
    peContainer* container = containers;
    while (container) {
        next = container->next;
        container->Stop();
        delete container;
        container = next;
    }
    containers = 0;
}
void peEmitterNode::SetLastLoop() {
    if (flags & 0x40) return;
    if (!(emitter->flags & 1)) return;
    flags |= 0x40;
    f32 loop = emitter->startTime + emitter->endTime;
    if (life < emitter->duration - loop) { life = emitter->duration - loop; lastLoop = loop; }
}
void peEmitterContainer::PreUpdate() {
    Resource* resource = emitter->resources;
    while (resource) resource = resource->next;
}
void peEmitterContainer::Stop() {
    if (active) {
        PreUpdate();
        active = 0;
        peEmitterNode* node = nodes;
        while (node) {
            peEmitterNode* next = node->next;
            node->Stop(0);
            node = next;
        }
        RemoveAll__11peContainerFv(this);
    }
}
void peEmitterContainer::Render() {
    if (active && DoRender()) {
        peEmitterNode* node = nodes;
        while (node) { node->Render(0); node = node->next; }
    }
}
u16 peEmitterContainer::Emit(u16 count) {
    if (!active) return 0;
    u16 remaining = CreateNodes__11peContainerFUs(this, count);
    _EmitParams* params = g_emitParams;
    peEmitterNode* node = nodes;
    peEmitterNode* next;
    u16 result = remaining;
    while (remaining) {
        next = node->next;
        node->Start(owner, emitter, params);
        node = next; --remaining; ++params;
    }
    return result;
}
bool peEmitterContainer::DoRender() {
    if (!active) return false;
    u32 flags = emitter->flags;
    if (!count) return false;
    if (flags & 0x80000000) return false;
    switch (g_render_pass) {
    case 0: if (!(flags & 0x800)) return false; break;
    case 1: if (!(flags & 0x1000)) return false; break;
    default: return false;
    }
    switch (g_current_layer->kind) {
    case 0: if (flags & 0x2000) return true; break;
    case 2:
        if (flags & 0x4000) return true;
        if (!(flags & 0x0380e000)) return true;
        break;
    case 4: if (flags & 0x8000) return true; break;
    case 1: if (flags & 0x800000) return true; break;
    case 3: if (flags & 0x1000000) return true; break;
    case 5: if (flags & 0x2000000) return true; break;
    default: return false;
    }
    return false;
}

void peEmitterContainer::Update(f32 delta) {
    if (active) {
        peEmitterNode* node = nodes;
        peEmitterNode* next;
        while (node) {
            next = node->next;
            if (!node->Update(owner, emitter, delta)) {
                node->Stop(0);
                RemoveNode__11peContainerFP6peNode(this, node);
            }
            node = next;
        }
        if (active && (emitter->flags & 0x40000) && count >= 2) {
            peEmitterNode* node = nodes->next;
            while (node) {
                f32 depth = node->depth;
                peEmitterNode* before = node;
                peEmitterNode* previous = node->previous;
                while (previous && previous->depth < depth) {
                    before = previous;
                    previous = previous->previous;
                }
                next = node->next;
                if (before != node) MoveNode__11peContainerFP6peNodeP6peNode(this, node, before);
                node = next;
            }
        }
    }
}

extern "C" u32 g_particle_debug_stats[6];
peEmitterContainer::~peEmitterContainer() {
    peEmitterNode* node = freeNodes;
    while (node) {
        peEmitterNode* next = node->next;
        node->Release();
        node = next;
    }
    g_particle_debug_stats[1] -= 0x24;
    g_particle_debug_stats[5] -= 0x24;
}

struct _peParticle { u8 reserved00[0x54]; s32 texture; };
struct _peParticleStrip { u8 reserved00[0x1c]; s32 texture; };
struct _peDistortion { u8 reserved00[0x60]; s32 texture; };
struct _peModel { u8 reserved00[0x4c]; s32 resource; };
struct _peShape { u8 reserved00[0x74]; s32 resource; };
struct peParticleContainer : peContainer { u8 reserved20[0x7c - 0x20]; peParticleContainer(peEmitterNode*, _peParticle*, u16); };
struct peParticleStripContainer : peContainer { u8 reserved20[0x60 - 0x20]; peParticleStripContainer(peEmitterNode*, _peParticleStrip*, u16); };
struct peDistortionContainer : peContainer { u8 reserved20[0x78 - 0x20]; peDistortionContainer(peEmitterNode*, _peDistortion*, u16); };
struct peModelContainer : peContainer { u8 reserved20[0x24 - 0x20]; peModelContainer(peEmitterNode*, _peModel*, u16); };
struct peShapeContainer : peContainer { u8 reserved20[0x24 - 0x20]; peShapeContainer(peEmitterNode*, _peShape*, u16); };
inline peEmitterContainer::peEmitterContainer(peEmitterNode* owner, _peEmitter* definition, u16 maximum) : peContainer(owner, 0x104, maximum) {
    emitter = definition;
    peEmitterNode* node = freeNodes;
    while (node) {
        peEmitterNode* next = node->next;
        node->Init(definition);
        node = next;
    }
    g_particle_debug_stats[1] += 0x24;
    g_particle_debug_stats[5] += 0x24;
}
void peEmitterNode::Init(_peEmitter* definition) {
    peContainer* container;
    peContainer* last;
    void* data;
    u16 maximum;
    Resource* resource;
    emitter = definition;
    maximum = definition->flags2;
    for (resource = definition->resources; resource; resource = resource->next) {
        data = resource->data;
        if (data) {
            container = 0;
            switch (resource->kind) {
            case 0: {
                _peEmitter* child = (_peEmitter*)data;
                if (child->resources) container = new peEmitterContainer(this, (_peEmitter*)data, maximum);
                break;
            }
            case 1:
                if (((_peParticle*)data)->texture) container = new peParticleContainer(this, (_peParticle*)data, maximum);
                break;
            case 6:
                if (((_peParticleStrip*)data)->texture) container = new peParticleStripContainer(this, (_peParticleStrip*)data, maximum);
                break;
            case 3:
                if (((_peDistortion*)data)->texture) container = new peDistortionContainer(this, (_peDistortion*)data, maximum);
                break;
            case 2:
                if (((_peModel*)data)->resource) container = new peModelContainer(this, (_peModel*)data, maximum);
                break;
            case 4:
                if (((_peShape*)data)->resource) container = new peShapeContainer(this, (_peShape*)data, maximum);
                break;
            }
            if (container) {
                if (!containers) containers = container;
                else {
                    last = containers;
                    while (last->next) last = last->next;
                    last->next = container;
                }
            }
        }
    }
}

extern "C" {
f32 HSD_Randf();
s32 EulerToQuat(Vec*, Quaternion*);
extern Vec unitScaleVector;
void Start__6peNodeFP13peEmitterNodeP11_EmitParams(peEmitterNode*, peEmitterNode*, _EmitParams*);
}
void peEmitterNode::Start(peEmitterNode* parent, _peEmitter* definition, _EmitParams* params) {
    Vec angles;
    u32 definitionFlags = definition->flags;
    Start__6peNodeFP13peEmitterNodeP11_EmitParams(this, parent, params);
    if (!parent && (definitionFlags & 1)) life = definition->startTime + definition->endTime;
    else life = definition->duration;
    time = definition->duration;
    lastLoop = 0.0f;
    field34 = 0.0f;
    field44 = 0.0f;
    count = 0;
    flags = 0x20;
    localRotation.x = 0.0f;
    localRotation.y = 0.0f;
    localRotation.z = 0.0f;
    localRotation.w = 1.0f;
    orientation.x = 0.0f;
    orientation.y = 0.0f;
    orientation.z = 0.0f;
    orientation.w = 1.0f;
    previousWorld.position.x = 0.0f;
    previousWorld.position.y = 0.0f;
    previousWorld.position.z = 0.0f;
    previousWorld.rotation.x = 0.0f;
    previousWorld.rotation.y = 0.0f;
    previousWorld.rotation.z = 0.0f;
    previousWorld.rotation.w = 1.0f;
    previousWorld.scale = unitScaleVector;
    world.position.x = 0.0f;
    world.position.y = 0.0f;
    world.position.z = 0.0f;
    world.rotation.x = 0.0f;
    world.rotation.y = 0.0f;
    world.rotation.z = 0.0f;
    world.rotation.w = 1.0f;
    world.scale = unitScaleVector;
    if (!(definitionFlags & 2) && (!parent || (parent->emitter->flags & 0x400) != 0x400)) {
        if ((definitionFlags & 0x80) != 0x80) EulerToQuat(&definition->euler, &localRotation);
        if (definitionFlags & 0x700038) {
            if (definitionFlags & 8) angles.x = 6.2831855f * HSD_Randf();
            else angles.x = 0.0f;
            if (definitionFlags & 0x10) angles.y = 6.2831855f * HSD_Randf();
            else angles.y = 0.0f;
            if (definitionFlags & 0x20) angles.z = 6.2831855f * HSD_Randf();
            else angles.z = 0.0f;
            if (definitionFlags & 0x100000) {
                if (HSD_Randf() < 0.5f) { flags |= 1; angles.x = -angles.x; }
            }
            if (definitionFlags & 0x200000) {
                if (HSD_Randf() < 0.5f) { flags |= 2; angles.y = -angles.y; }
            }
            if (definitionFlags & 0x400000) {
                if (HSD_Randf() < 0.5f) { flags |= 4; angles.z = -angles.z; }
            }
            EulerToQuat(&angles, &orientation);
        }
    }
    if ((definitionFlags & 0x80) != 0x80) {
        randomOffset.x = definition->position.x + definition->positionRange.x * HSD_Randf();
        randomOffset.y = definition->position.y + definition->positionRange.y * HSD_Randf();
        randomOffset.z = definition->position.z + definition->positionRange.z * HSD_Randf();
    }
    spin.x = definition->spin.x;
    spin.y = definition->spin.y;
    spin.z = definition->spin.z;
    peContainer* container = containers;
    while (container) { container->Start(); container = container->next; }
}

extern "C" {
extern Vec g_CameraPosition, g_CameraLookDir;
void peNodeTransformsConcat(EmitterTransforms*,void*,EmitterTransforms*,u32);
}
void peEmitterNode::CreateWorldParams() {
    EmitterTransforms transform;
    Vec direction;
    Vec difference;
    u32 emitterFlags = emitter->flags;
    previousWorld.position.x = world.position.x;
    previousWorld.position.y = world.position.y;
    previousWorld.position.z = world.position.z;
    previousWorld.rotation.x = world.rotation.x;
    previousWorld.rotation.y = world.rotation.y;
    previousWorld.rotation.z = world.rotation.z;
    previousWorld.rotation.w = world.rotation.w;
    previousWorld.scale.x = world.scale.x;
    previousWorld.scale.y = world.scale.y;
    previousWorld.scale.z = world.scale.z;
    if (flags & 1) world.rotation.x = -localRotation.x;
    else world.rotation.x = localRotation.x;
    if (flags & 2) world.rotation.y = -localRotation.y;
    else world.rotation.y = localRotation.y;
    if (flags & 4) world.rotation.z = -localRotation.z;
    else world.rotation.z = localRotation.z;
    world.rotation.w = localRotation.w;
    Vec position;
    PSVECAdd(&basePosition, &offset, &position);
    transform.position.x = position.x;
    transform.position.y = position.y;
    transform.position.z = position.z;
    Quaternion rotation;
    PSQUATMultiply(&orientation, &world.rotation, &rotation);
    transform.rotation.x = rotation.x;
    transform.rotation.y = rotation.y;
    transform.rotation.z = rotation.z;
    transform.rotation.w = rotation.w;
    transform.scale.x = scale.x;
    transform.scale.y = scale.y;
    transform.scale.z = scale.z;
    peNodeTransformsConcat(&world,transformParent,&transform,(emitterFlags >> 1) & 1);
    PSVECSubtract(&world.position,&g_CameraPosition,&difference);
    direction.x = difference.x;
    direction.y = difference.y;
    direction.z = difference.z;
    depth = PSVECDotProduct(&g_CameraLookDir,&direction);
    if (count == 0) {
        previousWorld.position.x = world.position.x;
        previousWorld.position.y = world.position.y;
        previousWorld.position.z = world.position.z;
        previousWorld.rotation.x = world.rotation.x;
        previousWorld.rotation.y = world.rotation.y;
        previousWorld.rotation.z = world.rotation.z;
        previousWorld.rotation.w = world.rotation.w;
        previousWorld.scale.x = world.scale.x;
        previousWorld.scale.y = world.scale.y;
        previousWorld.scale.z = world.scale.z;
    }
}
