#include <game/pxdvs/GSAPI/GSparticle/peDistortionPrivate.hpp>
#include <dolphin/os.h>
#include <libc/math.h>
static inline f32 spline(ShapeSpline *s,f32 t) {
 if(!s || !(s->flags&3))return 1.0f;
 f32 d=s->time-t;if(d<0)d=-d;
 return d<=0.00001f?s->value:peSplineGetValue(s,t);
}
static inline u32 &layerWord(u32 offset) {return *(u32*)((u8*)g_current_layer+offset);}
static inline u8 &layerByte(u32 offset) {return *((u8*)g_current_layer+offset);}
static inline void invalidate(peDistortionNode *node,GSgfxDL *list) {
 u16 *indices=(list->flags&1)?(u16*)(list->data+(((node->index*4)&0xfffc)*list->stride)+3):0;
 u16 vertices=4;while(vertices--) {indices[0]=0xffff;indices[1]=0xffff;indices[2]=0xffff;indices+=3;}list->flags|=2;
}
void peDistortionContainer::Stop() {
 if(active) {
  PreUpdate();active=0;peDistortionNode *node=(peDistortionNode*)nodes;u32 flags=owner->emitter->flags;
  if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)1,false);
  if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)3,false);
  if(flags&0x2000000)SetLayerVisibility((GSgfxLayerID)5,false);
  while(node) {invalidate(node,&displayLists[swapIndex]);node=(peDistortionNode*)node->next;}
  RemoveAll();ResetSwap();
 }
}
static inline u8 visible(peDistortionContainer *c) {
 if(!c->active)return 0;u32 flags=c->definition->flags;
 if(!c->count||g_render_pass!=1)return 0;
 switch(layerWord(0x28)) {case 1:if(!(flags&0x2000))return 0;break;case 3:if(flags&0x10)return 0;break;case 5:if(!(flags&0x10))return 0;break;default:return 0;}return 1;
}
void peDistortionContainer::Render() {
 if(active&&visible(this)) {
  ResolveMultipleSwap();u32 flags=definition->flags;
  layerWord(0xd8c)=(flags&0x100)?2:0;
  layerWord(0x16b8)|=2;layerWord(0x16a8)|=2;layerWord(0x1770)|=2;layerWord(0x1760)|=2;
  layerWord(0x165c)=0;layerWord(0x1660)=3;layerWord(0x170c)|=8;layerWord(0x16a8)|=0x40;layerWord(0x17c4)|=8;layerWord(0x1760)|=0x40;
  layerByte(0x1656)=1;layerByte(0x1657)=0;layerByte(0x1658)=0;layerWord(0x170c)|=4;layerWord(0x16a8)|=0x40;layerWord(0x17c4)|=4;layerWord(0x1760)|=0x40;
  layerWord(0x1664)=7;layerByte(0x1670)=0;layerWord(0x1668)=0;layerWord(0x166c)=7;layerByte(0x1671)=0;layerByte(0x1672)=1;
  layerWord(0x170c)|=0x10;layerWord(0x16a8)|=0x40;layerWord(0x17c4)|=0x10;layerWord(0x1760)|=0x40;
  particleEngineSetupBlendMode(0);particleEngineSetupTevStages(0,0,0);
  particleEngineSetupTexture(0,definition->texture,flags&3,(flags>>2)&3,(flags&0x20)?2:0,(flags&0x40)?2:0);
  GSgfxDL *list=&displayLists[swapIndex];GSgfxVF *format=(list->flags&1)?(GSgfxVF*)list->reserved:0;u8 *data=renderData[swapIndex];
  GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x30,4,renderBytes);GSgfxVFSetArray(format,13,3,uv,4,0x20);
  dlDraw__10GSgfxLayerFP7GSgfxDL(g_current_layer,list);MarkForSwap();
 }
}
void peDistortionContainer::Update(f32 dt) {
 if(active) {
  peDistortionNode *node=(peDistortionNode*)nodes;
  while(node) {
   peDistortionNode *next=(peDistortionNode*)node->next;_peDistortion *d=definition;u8 *data=renderData[swapIndex];
   peEmitterNode *emitter=owner;u8 alive;
   if(!data || (displayLists[swapIndex].flags&1)!=1 || !node->peNode::Update(emitter,dt))alive=0;
   else {f32 progress=1.0f-node->time/node->life;if(d->flags&0x200)node->angle=d->angle*spline(d->angleSpline,progress);node->angle+=node->angularSpeed*dt;node->UpdateRenderData(emitter,d,(char*)data,progress);alive=1;}
   if(!alive){invalidate(node,&displayLists[swapIndex]);RemoveNode(node);}node=next;
  }
 }
}
u16 peDistortionContainer::Emit(u16 requested) {
 if(!active)return 0;
 u16 remaining=CreateNodes(requested),created=remaining;_EmitParams *params=g_emitParams;peDistortionNode *node=(peDistortionNode*)nodes;
 while(remaining) {
  _peDistortion *d=definition;peDistortionNode *next=(peDistortionNode*)node->next;GSgfxDL *list=&displayLists[swapIndex];u32 flags=d->flags;
  if((list->flags&1)==1) {
   node->peNode::Start(owner,params);f32 random=HSD_Randf();node->width=d->widthRange*random;node->height=d->heightRange*random;node->width+=d->width;node->height+=d->height;
   node->rotation=(flags&0x80)?6.2831855f*HSD_Randf():0.0f;
   if((flags&0x1000)&&HSD_Randf()<0.5f)node->flags|=1;
   node->angle=d->angle;node->angularSpeed=d->angularRange*HSD_Randf()+d->angularMin;
   u16 base=node->index*13;u16 *indices=(list->flags&1)?(u16*)(list->data+(((node->index*4)&0xfffc)*list->stride)+3):0;
   indices[0]=base;indices[1]=base;indices[2]=0;indices[3]=base+3;indices[4]=base;indices[5]=2;indices[6]=base+6;indices[7]=base;indices[8]=4;indices[9]=base+9;indices[10]=base;indices[11]=6;list->flags|=2;
  }
  node=next;--remaining;++params;
 }return created;
}
void peDistortionContainer::Start() {
 if(!active) {active=1;u32 flags=owner->emitter->flags;InitSwap();
  if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)1,true);if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)3,true);if(flags&0x2000000)SetLayerVisibility((GSgfxLayerID)5,true);
 }
}
peDistortionContainer::~peDistortionContainer() {g_particle_debug_stats.node-=0x78;g_particle_debug_stats.total-=0x78;}
peDistortionContainer::peDistortionContainer(peEmitterNode *emitter,_peDistortion *d,u16 maximum):peRenderContainer(emitter,0x48,maximum,&g_vertex_format,(GSgfxPrimType)0x80,4,0x34,(d->flags>>14)&1) {
 definition=d;_peDistortion *textureDefinition=definition;uv[0]=textureDefinition->u1;uv[1]=textureDefinition->v1;uv[2]=textureDefinition->u0;uv[3]=textureDefinition->v1;uv[4]=textureDefinition->u0;uv[5]=textureDefinition->v0;uv[6]=textureDefinition->u1;uv[7]=textureDefinition->v0;DCFlushRange(uv,0x20);
 peDistortionNode *node=(peDistortionNode*)freeNodes;s16 index=0;while(node){node->index=index++;node=(peDistortionNode*)node->next;}g_particle_debug_stats.node+=0x78;g_particle_debug_stats.total+=0x78;
}
static inline void rotate(Vec *v,Quaternion *q) {Mtx matrix;PSMTXQuat(matrix,q);PSMTXMultVecSR(matrix,v,v);}
static inline void scaleBasis(Vec *v,ShapeTransform *transform) {
 Quaternion inverse;Vec local;PSQUATInverse(&transform->rotation,&inverse);Mtx matrix;PSMTXQuat(matrix,&inverse);PSMTXMultVecSR(matrix,v,&local);
 local.x*=transform->scale.x;local.y*=transform->scale.y;local.z*=transform->scale.z;rotate(&local,&transform->rotation);PSVECScale(v,v,PSVECDotProduct(v,&local));
}
static inline u8 alphaByte(f32 value) {if(value<0)return 0;if(value>255)return 255;return (u8)value;}
void peDistortionNode::UpdateRenderData(peEmitterNode *emitter,_peDistortion *d,char *data,f32 progress) {
 ShapeTransform *parent=(ShapeTransform*)transform;Vec world,side,up,normal,offset,temp;
 world.x=position.x*parent->scale.x;world.y=position.y*parent->scale.y;world.z=position.z*parent->scale.z;rotate(&world,&parent->rotation);PSVECAdd(&world,&parent->position,&world);u32 flags=d->flags;
 if(flags&0x100) {
  if(flags&0x400) {Vec toward;PSVECSubtract(&g_CameraPosition,&world,&toward);PSVECNormalize(&toward,&toward);PSVECCrossProduct(&toward,&g_CameraUpDir,&side);PSVECNormalize(&side,&side);PSVECCrossProduct(&toward,&side,&temp);}
  else {up=g_CameraUpDir;side=g_CameraSideDir;}
 } else {
  side=xAxisVector;up=yAxisVector;
  if(emitter->emitter->flags&0x400) {Vec euler;Quaternion q;euler.x=atan2(-velocity.y,sqrtf(velocity.x*velocity.x+velocity.z*velocity.z));euler.y=atan2(velocity.x,velocity.z);euler.z=0;EulerToQuat(&euler,&q);rotate(&side,&q);rotate(&up,&q);}
  rotate(&side,&parent->rotation);rotate(&up,&parent->rotation);
 }
 PSVECCrossProduct(&up,&side,&normal);f32 spin=(this->flags&1)?0.0f-(rotation+angle):0.0f+(rotation+angle);
 if((flags&0x8000)&&fabsf(spin)>0.00001f){Quaternion q;C_QUATRotAxisRad(&q,&normal,spin);rotate(&up,&q);rotate(&side,&q);}
 scaleBasis(&side,parent);scaleBasis(&up,parent);PSVECScale(&side,&side,width*spline(d->widthSpline,progress));PSVECScale(&up,&up,height*spline(d->heightSpline,progress));
 if(!(flags&0x8000)&&fabsf(spin)>0.00001f){Quaternion q;C_QUATRotAxisRad(&q,&normal,spin);rotate(&up,&q);rotate(&side,&q);}
 if(flags&0x800){Vec other;PSVECScale(&side,&offset,d->offsetX);PSVECScale(&up,&other,d->offsetY);offset.x*=other.x;offset.y*=other.y;offset.z*=other.z;}
 Vec *out=(Vec*)(data+index*0x34);
 temp.x=-side.x;temp.y=-side.y;temp.z=-side.z;PSVECSubtract(&temp,&up,&temp);
 if(flags&0x800)PSVECAdd(&temp,&offset,&temp);PSVECAdd(&temp,&world,&temp);out[0]=temp;if(g_currentBound)GSboundAddPoint(g_currentBound,temp.x,temp.y,temp.z);
 PSVECSubtract(&side,&up,&temp);if(flags&0x800)PSVECAdd(&temp,&offset,&temp);PSVECAdd(&temp,&world,&temp);out[1]=temp;if(g_currentBound)GSboundAddPoint(g_currentBound,temp.x,temp.y,temp.z);
 PSVECAdd(&side,&up,&temp);if(flags&0x800)PSVECAdd(&temp,&offset,&temp);PSVECAdd(&temp,&world,&temp);out[2]=temp;if(g_currentBound)GSboundAddPoint(g_currentBound,temp.x,temp.y,temp.z);
 PSVECSubtract(&up,&side,&temp);if(flags&0x800)PSVECAdd(&temp,&offset,&temp);PSVECAdd(&temp,&world,&temp);out[3]=temp;if(g_currentBound)GSboundAddPoint(g_currentBound,temp.x,temp.y,temp.z);
 *(u32*)(out+4)=0xffffff00|alphaByte((255.0f*emitter->color[3])*spline(d->alphaSpline,progress));
}
