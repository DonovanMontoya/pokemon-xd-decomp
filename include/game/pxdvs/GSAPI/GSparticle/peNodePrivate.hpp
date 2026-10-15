#ifndef PE_NODE_PRIVATE_HPP
#define PE_NODE_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct NodeTransform { Vec position; Quaternion rotation; Vec scale; };
struct _peEmitter { u32 flags; u8 reserved04[0x9c]; f32 friction,bounce,attraction; };
struct peEmitterNode { u8 reserved00[0x9c]; Vec force; u8 reserveda8[0x54]; _peEmitter *emitter; };
struct _EmitParams { f32 life,forceFactor; Vec position,velocity; NodeTransform transform; };
struct peNode {
 f32 life,time; Vec position,velocity; NodeTransform *transform; f32 forceFactor; peNode *next,*previous;
 void Start(peEmitterNode*,_EmitParams*); u8 Update(peEmitterNode*,f32);
};
typedef char NodeTransformSize[sizeof(NodeTransform)==0x28?1:-1];
typedef char NodeBaseSize[sizeof(peNode)==0x30?1:-1];
typedef char NodeForceOffset[offsetof(peEmitterNode,force)==0x9c?1:-1];
typedef char NodeEmitterOffset[offsetof(peEmitterNode,emitter)==0xfc?1:-1];
typedef char NodeParamsSize[sizeof(_EmitParams)==0x48?1:-1];
typedef char NodeEmitterAttraction[offsetof(_peEmitter,attraction)==0xa8?1:-1];
extern "C" { Mtx *GSgfxMatrixGetPtr(s32); }
#endif
