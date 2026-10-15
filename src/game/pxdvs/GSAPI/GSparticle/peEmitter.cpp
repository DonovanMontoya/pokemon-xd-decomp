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
