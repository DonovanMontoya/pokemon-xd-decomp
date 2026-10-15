#include <game/pxdvs/GSAPI/GSparticle/peModelPrivate.hpp>
#include <dolphin/gx.h>
#include <libc/math.h>
static u32 _primitive_instance_memory;
static inline void updatePrimitiveMemory() {
 g_particle_debug_stats.reserved10-=_primitive_instance_memory;
 g_particle_debug_stats.total-=_primitive_instance_memory;
 _primitive_instance_memory=shapeGetInstancedMemorySizeAll();
 g_particle_debug_stats.reserved10+=_primitive_instance_memory;
 g_particle_debug_stats.total+=_primitive_instance_memory;
}
static inline void freeModelInstance(peModelNode *node,_peModel *model) {
 if(model->flags&0x40) {shapeFreePrimitiveInstance(model->resource.primitive-1,node->instance);updatePrimitiveMemory();}
}
void peModelContainer::Stop() {
 if(active) {
  PreUpdate();active=0;
  if(model->flags&0x40) {
   peModelNode *node=(peModelNode*)nodes;
   while(node) {peModelNode *next=(peModelNode*)node->next;freeModelInstance(node,model);node=next;}
  }
  RemoveAll();
 }
}
static inline u8 modelVisible(peModelContainer *container) {
 if(!container->active)return 0;
 u32 flags=container->model->flags;
 if(!container->count || g_render_pass!=1)return 0;
 switch(((ParticleLayerState*)g_current_layer)->unk28) {
 case 2:if(flags&2)return 0;break;
 case 4:if(!(flags&2))return 0;break;
 case 3:default:return 0;
 }
 return 1;
}
static inline void setModelMatrix(ModelJObj *jobj,Mtx matrix) {
 if(!jobj)__assert("jobj.h",0x495,"jobj");
 if(!matrix)__assert("jobj.h",0x496,"mtx");
 PSMTXCopy(matrix,jobj->matrix);jobj->flags|=0x03800000;
 if(jobj) {
  if(!jobj)__assert("jobj.h",0x25d,"jobj");
  u32 flags=jobj->flags;u8 dirty=0;
  if(!(flags&0x800000)&&(flags&0x40))dirty=1;
  if(!dirty)HSD_JObjSetMtxDirtySub(jobj);
 }
}
void peModelContainer::Render() {
 Mtx transform,rotation;
 if(active&&modelVisible(this)) {
  if(!(model->flags&0x40)) {
   ModelCamera *camera=GScameraGetActiveCamera();
   if(!camera)return;
   GXSetClipMode(GX_CLIP_ENABLE);HSD_StateInvalidate(-1);
   HSD_CObjSetCurrent(camera->camera);GSlightSetupLights(camera->camera);
  }
  peModelNode *node=(peModelNode*)nodes;
  while(node) {
   _peModel *definition=model;
   PSMTXQuat(rotation,&node->worldRotation);
   PSMTXScale(transform,node->worldScale.x,node->worldScale.y,node->worldScale.z);
   PSMTXConcat(rotation,transform,transform);
   PSMTXTransApply(transform,transform,node->worldPosition.x,node->worldPosition.y,node->worldPosition.z);
   if(definition->flags&0x40) {
    u16 primitive=definition->resource.primitive-1;
    shapeUpdate(primitive,node->instance,node->life-node->time);
    pushMult__16GSgfxMatrixStackFP5GSmtx(((ParticleLayerState*)g_current_layer)->unk19A0,transform);
    shapeRender(primitive,node->instance,((ParticleLayerState*)g_current_layer)->unk28);
    pop__16GSgfxMatrixStackFv(((ParticleLayerState*)g_current_layer)->unk19A0);
   } else {
    ModelJObj *jobj=definition->resource.jobj;
    if(jobj) {
     u32 mask;
     switch(g_render_pass) {
     case 0:mask=1;break;
     case 1:mask=6;break;
     default:node=(peModelNode*)node->next;continue;
     }
     setModelMatrix(jobj,transform);
     if(definition->duration>0.00001f) {
      f32 rate=GSgfxVideoGetVsyncRate();
      HSD_JObjReqAnimAll(jobj,(f32)fmod((node->life-node->time)*rate,definition->duration));
      HSD_JObjAnimAll(jobj);HSD_JObjDispAll(jobj,0,mask,0);
     }
    }
   }
   node=(peModelNode*)node->next;
  }
  if(!(model->flags&0x40))InvalidateState__10GSgfxLayerFv(g_current_layer);
  particleEngineSetDefaultRenderState(1);
 }
}
void peModelContainer::Update(f32 time) {
 if(active) {
  peModelNode *node=(peModelNode*)nodes;
  while(node) {
   peModelNode *next=(peModelNode*)node->next;
   if(!node->Update(owner,model,time)){freeModelInstance(node,model);RemoveNode(node);}
   node=next;
  }
  if(active&&(model->flags&0x10000)&&count>=2) {
   peModelNode *sorting=(peModelNode*)nodes->next;
   while(sorting) {
    peModelNode *before=sorting,*previous=(peModelNode*)sorting->previous;
    while(previous&&previous->depth<sorting->depth){before=previous;previous=(peModelNode*)previous->previous;}
    peModelNode *next=(peModelNode*)sorting->next;
    if(before!=sorting)MoveNode(sorting,before);
    sorting=next;
   }
  }
  if(g_currentBound&&nodes)GSboundAlwaysInView(g_currentBound,1);
 }
}
u16 peModelContainer::Emit(u16 requested) {
 if(!active)return 0;
 u16 remaining=CreateNodes(requested);_EmitParams *params=g_emitParams;peNode *node=nodes;peNode *next;u16 result=remaining;
 while(remaining){next=node->next;((peModelNode*)node)->Start(owner,model,params);node=next;--remaining;++params;}
 return result;
}
peModelContainer::~peModelContainer(){g_particle_debug_stats.node-=0x24;g_particle_debug_stats.total-=0x24;}
peModelContainer::peModelContainer(peEmitterNode *emitter,_peModel *data,u16 maximum):peContainer(emitter,0x98,maximum) {model=data;g_particle_debug_stats.node+=0x24;g_particle_debug_stats.total+=0x24;}
static inline f32 modelSpline(ShapeSpline *spline,f32 progress) {
 if(!spline||!(spline->flags&3))return 1.0f;
 f32 difference=spline->time-progress;if(difference<0.0f)difference=-difference;
 if(difference<=0.00001f)return spline->value;
 return peSplineGetValue(spline,progress);
}
u8 peModelNode::Update(peEmitterNode *emitter,_peModel *model,f32 delta) {
 u32 flags=model->flags;
 if(!peNode::Update(emitter,delta))return 0;
 if((flags&8)&&(life-time>=model->duration))return 0;
 u32 emitterFlags=emitter->emitter->flags;
 f32 progress=1.0f-time/life;
 Vec angles;
 if(emitterFlags&0x400) {
  Vec direction=velocity;
  if(emitterFlags&0x40){Mtx matrix;PSMTXQuat(matrix,(Quaternion*)((u8*)transform+12));PSMTXMultVecSR(matrix,&direction,&direction);}
  f32 horizontal=sqrtf(direction.x*direction.x+direction.z*direction.z);
  angles.x=(f32)atan2(-direction.y,horizontal);angles.y=(f32)atan2(direction.x,direction.z);angles.z=0.0f;
  EulerToQuat(&angles,&localRotation);
 } else if(flags&0x20) {
  angles.x=model->rotation.x*modelSpline(model->rotationSpline[0],progress);
  angles.y=model->rotation.y*modelSpline(model->rotationSpline[1],progress);
  angles.z=model->rotation.z*modelSpline(model->rotationSpline[2],progress);
  EulerToQuat(&angles,&localRotation);
 } else {
  Vec rotation;Quaternion step;PSVECScale(&angularSpeed,&rotation,delta);angles=rotation;
  EulerToQuat(&angles,&step);PSQUATMultiply(&localRotation,&step,&localRotation);
 }
 Quaternion flipped;
 flipped.x=(flips&1)?-localRotation.x:localRotation.x;
 flipped.y=(flips&2)?-localRotation.y:localRotation.y;
 flipped.z=(flips&4)?-localRotation.z:localRotation.z;flipped.w=localRotation.w;
 angles.x=baseScale.x*modelSpline(model->scaleSpline[0],progress);
 angles.y=baseScale.y*modelSpline(model->scaleSpline[1],progress);
 angles.z=baseScale.z*modelSpline(model->scaleSpline[2],progress);
 ShapeTransform local;local.position=position;PSQUATMultiply(&randomRotation,&flipped,&local.rotation);local.scale=angles;
 peNodeTransformsConcat((ShapeTransform*)&worldPosition,transform,&local,0);
 Vec distance;PSVECSubtract(&worldPosition,&g_CameraPosition,&distance);Vec copy=distance;depth=PSVECDotProduct(&g_CameraLookDir,&copy);
 return 1;
}
void peModelNode::Start(peEmitterNode *emitter,_peModel *model,_EmitParams *params) {
 Vec randomAngles,scale;u32 flags=model->flags;
 peNode::Start(emitter,params);flips=0;
 PSVECScale(&model->scaleRange,&scale,HSD_Randf());
 baseScale.x=scale.x;baseScale.y=scale.y;baseScale.z=scale.z;PSVECAdd(&baseScale,&model->scale,&baseScale);
 randomRotation.x=0.0f;randomRotation.y=0.0f;randomRotation.z=0.0f;randomRotation.w=1.0f;
 worldPosition.x=0.0f;worldPosition.y=0.0f;worldPosition.z=0.0f;
 worldRotation.x=0.0f;worldRotation.y=0.0f;worldRotation.z=0.0f;worldRotation.w=1.0f;worldScale=unitScaleVector;
 if(!(emitter->emitter->flags&0x400)) {
  EulerToQuat(&model->rotation,&localRotation);
  if(flags&0xe380) {
   randomAngles.x=(flags&0x80)?6.2831855f*HSD_Randf():0.0f;
   randomAngles.y=(flags&0x100)?6.2831855f*HSD_Randf():0.0f;
   randomAngles.z=(flags&0x200)?6.2831855f*HSD_Randf():0.0f;
   if((flags&0x2000)&&HSD_Randf()<0.5f)flips|=1;
   if((flags&0x4000)&&HSD_Randf()<0.5f)flips|=2;
   if((flags&0x8000)&&HSD_Randf()<0.5f)flips|=4;
   EulerToQuat(&randomAngles,&randomRotation);
  }
 }
 angularSpeed=model->angularSpeed;
 if(flags&0x400)angularSpeed.x*=HSD_Randf();
 if(flags&0x800)angularSpeed.y*=HSD_Randf();
 if(flags&0x1000)angularSpeed.z*=HSD_Randf();
 if(model->flags&0x40){instance=shapeCreatePrimitiveInstance(model->resource.primitive-1);updatePrimitiveMemory();}
}
