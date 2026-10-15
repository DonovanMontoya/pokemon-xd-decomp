#include <game/pxdvs/GSAPI/GSparticle/peParticleStripPrivate.hpp>
static inline f32 emitterFloat(peEmitterNode *owner,u32 offset) {return *(f32*)((u8*)owner->emitter+offset);}
static inline u32 &layerWord(u32 offset) {return *(u32*)((u8*)g_current_layer+offset);}
static inline u8 byte(f32 value) {if(value<0)return 0;if(value>255)return 255;return (u8)value;}
static inline s16 shortValue(f32 value) {if(value<-32768)return -32768;if(value>32767)return 32767;return (s16)value;}
static inline f32 spline(ShapeSpline *s,f32 t) {if(!s||!(s->flags&3))return 1;f32 d=s->time-t;if(d<0)d=-d;return d<=0.00001f?s->value:peSplineGetValue(s,t);}
void peParticleStripContainer::RearrangeIndices() {
 if(active) {
  s16 output=0,ordinal=0;u16 total=count;u32 flags=definition->flags;u32 extended=(flags>>18)&1;
  if(total>=2) {
   f32 step=(flags&0x10000)?1.0f/(f32)(s16)(total-1):emitterFloat(owner,8);
   u8 vertexStride=extended?12:11,indexStep=extended?8:6,dataStride=extended?0x30:0x2c;
   GSgfxDL *list=&displayLists[swapIndex];peParticleStripNode *node=(peParticleStripNode*)nodes;
   while(node) {
    node->sortIndex=output;u16 base=node->index*vertexStride;f32 *data=(f32*)(renderData[swapIndex]+node->index*dataStride);
    u16 *indices=(u16*)((list->flags&1)?list->data+3:0);indices+=((u16)output);
    if(extended) {for(u16 j=0;j<2;++j){indices[0]=base+j*3;indices[1]=base;indices[2]=base;indices[3]=base+j*2;indices+=4;}}
    else {for(u16 j=0;j<2;++j){indices[0]=base+j*3;indices[1]=base;indices[2]=base+j*2;indices+=3;}}
    f32 value=(flags&0x20000)?(f32)(s16)(count-ordinal-1):(f32)ordinal;
    if(flags&0x8000)data[9]=data[7]=-((value*step)-1.0f);else data[9]=data[7]=value*step;
    output+=indexStep;++ordinal;data[8]=definition->v0;data[10]=definition->v1;node=(peParticleStripNode*)node->next;
   }list->flags|=2;
  }
 }
}
static inline void invalidate(peParticleStripNode *node,GSgfxDL *list,u32 flags) {
 u16 *indices=(u16*)((list->flags&1)?list->data+3:0);indices+=node->sortIndex;u16 count=2;
 while(count--){indices[0]=0xffff;indices[1]=0xffff;indices[2]=0xffff;indices+=3;if(flags&0x40000)*indices++=0xffff;}list->flags|=2;
}
void peParticleStripContainer::Stop() {
 if(active){PreUpdate();active=0;u32 flags=definition->flags;
  if(flags&0x400000)SetLayerVisibility((GSgfxLayerID)1,false);if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)3,false);if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)5,false);
  peParticleStripNode *node=(peParticleStripNode*)nodes;while(node){invalidate(node,&displayLists[swapIndex],definition->flags);node=(peParticleStripNode*)node->next;}RemoveAll();ResetSwap();
 }
}
static inline u8 visible(peParticleStripContainer *c) {
 if(!c->active)return 0;u32 flags=c->definition->flags;if(c->count<2||g_render_pass!=1)return 0;
 switch(layerWord(0x28)){case 0:return (flags&0x100000)!=0;case 2:return (flags&0x200000)||!(flags&0x1f00040);case 4:return(flags&0x40)!=0;case 1:return(flags&0x400000)!=0;case 3:return(flags&0x800000)!=0;case 5:return(flags&0x1000000)!=0;default:return 0;}
}
void peParticleStripContainer::Render() {
 if(active&&visible(this)) {
  ResolveMultipleSwap();u32 flags=definition->flags;u32 extended=(flags>>18)&1;
  layerWord(0xd8c)=0;layerWord(0x16b8)|=2;layerWord(0x16a8)|=2;layerWord(0x1770)|=2;layerWord(0x1760)|=2;particleEngineSetupBlendMode(flags&7);
  GSgfxDL *list=&displayLists[swapIndex];u8 *data=renderData[swapIndex];GSgfxVF *format=(list->flags&1)?(GSgfxVF*)list->reserved:0;
  GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x18,4,renderBytes);if(extended)GSgfxVFSetArray(format,12,3,data+0x2c,4,renderBytes);GSgfxVFSetArray(format,13,3,data+0x1c,4,renderBytes);
  if(flags&0x400) {
   u16 current=frame;StripAnimation *animation=(StripAnimation*)definition->texture;
   if(flags&0x1000) {
    f32 span=(f32)(s16)animation->count;u32 blend=(flags>>13)&1;particleEngineSetupTevStages(0,extended,blend);if(blend)span-=1.0f;
    f32 duration=emitterFloat(owner,0x28),time;
    if(flags&0x4000000)time=span*(duration-remaining)/definition->frameRate;else time=definition->frameRate*(span*(1.0f-remaining/duration));
    f32 value=fmod(time+(f32)(s16)current,span);current=(u16)shortValue(value)%(u16)animation->count;
    if(blend){u8 fraction=byte(255.0f*(value-(f32)(s16)current));u32 color=(fraction<<24)|(fraction<<16)|(fraction<<8)|fraction;layerWord(0x14f4)=color;layerWord(0x16f8)|=1;layerWord(0x16a8)|=0x10;layerWord(0x17b0)|=1;layerWord(0x1760)|=0x10;particleEngineSetupTexture(1,animation->textures[current+1],0,(flags>>8)&3,(flags&0x10)?2:0,(flags&0x20)?2:0);}
   }else particleEngineSetupTevStages(0,extended,0);
   particleEngineSetupTexture(0,animation->textures[current],0,(flags>>8)&3,(flags&0x10)?2:0,(flags&0x20)?2:0);
  }else{particleEngineSetupTevStages(0,extended,0);particleEngineSetupTexture(0,definition->texture,0,(flags>>8)&3,(flags&0x10)?2:0,(flags&0x20)?2:0);}
  dlDraw__10GSgfxLayerFP7GSgfxDL(g_current_layer,&displayLists[swapIndex]);MarkForSwap();
 }
}
void peParticleStripContainer::Update(f32 dt) {
 if(active){peParticleStripNode *node=(peParticleStripNode*)nodes;
  while(node){peParticleStripNode *next=(peParticleStripNode*)node->next;_peParticleStrip *d=definition;u8 *data=renderData[swapIndex];peEmitterNode *emitter=owner;u8 alive;
   if(!data||(displayLists[swapIndex].flags&1)!=1||!node->peNode::Update(emitter,dt))alive=0;
   else{node->UpdateRenderData(emitter,d,(char*)data,1.0f-node->time/node->life);alive=1;}
   if(!alive){invalidate(node,&displayLists[swapIndex],definition->flags);RemoveNode(node);}node=next;
  }remaining-=dt;RearrangeIndices();
 }
}
u16 peParticleStripContainer::Emit(u16 requested) {
 if(!active)return 0;u16 created=CreateNodes(requested),left=created;_EmitParams *params=g_emitParams;peParticleStripNode *node=(peParticleStripNode*)nodes;
 while(left){peParticleStripNode *next=(peParticleStripNode*)node->next;s16 ordinal=(*(u16*)((u8*)owner+0x4a)+created)-left;_peParticleStrip *d=definition;GSgfxDL *list=&displayLists[swapIndex];f32 progress=emitterFloat(owner,8)*(f32)ordinal;
  if((list->flags&1)==1){node->peNode::Start(owner,params);Vec segment;
   if(d->flags&0x2000000)PSVECScale(&d->direction,&segment,10.0f*(progress*d->speedRange+d->speedMin));else PSVECScale(&d->direction,&segment,10.0f*(d->speedRange*HSD_Randf()+d->speedMin));node->segment=segment;list->flags|=2;
  }node=next;--left;++params;
 }return created;
}
void peParticleStripContainer::Start() {
 if(!active){active=1;u32 flags=definition->flags;InitSwap();if(flags&0x400000)SetLayerVisibility((GSgfxLayerID)1,true);if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)3,true);if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)5,true);
  if((flags&0xc00)==0xc00)frame=byte((f32)(s16)((StripAnimation*)definition->texture)->count*HSD_Randf());else frame=0;remaining=emitterFloat(owner,0x28);
 }
}
peParticleStripContainer::~peParticleStripContainer(){g_particle_debug_stats.node-=0x60;g_particle_debug_stats.total-=0x60;}
peParticleStripContainer::peParticleStripContainer(peEmitterNode *emitter,_peParticleStrip *d,u16 maximum):peRenderContainer(emitter,0x40,maximum,(d->flags&0x40000)?&g_ext_vertex_format:&g_vertex_format,(GSgfxPrimType)0x98,2,(d->flags&0x40000)?0x30:0x2c,(d->flags>>19)&1) {
 definition=d;frame=0xff;peParticleStripNode *node=(peParticleStripNode*)freeNodes;s16 index=0;while(node){node->index=index;node->sortIndex=index;++index;node=(peParticleStripNode*)node->next;}g_particle_debug_stats.node+=0x60;g_particle_debug_stats.total+=0x60;
}
void peParticleStripNode::UpdateRenderData(peEmitterNode *emitter,_peParticleStrip *d,char *data,f32 progress) {
 Mtx matrix;ShapeTransform *parent=(ShapeTransform*)transform;Vec world,segment;
 world.x=position.x*parent->scale.x;world.y=position.y*parent->scale.y;world.z=position.z*parent->scale.z;PSMTXQuat(matrix,&parent->rotation);PSMTXMultVecSR(matrix,&world,&world);PSVECAdd(&world,&parent->position,&world);
 u32 flags=d->flags;char *out=data+index*((flags&0x40000)?0x30:0x2c);
 segment.x=this->segment.x*parent->scale.x;segment.y=this->segment.y*parent->scale.y;segment.z=this->segment.z*parent->scale.z;PSMTXQuat(matrix,&parent->rotation);PSMTXMultVecSR(matrix,&segment,&segment);
 if(flags&0x4000){Vec half;PSVECScale(&segment,&half,0.5f);PSVECSubtract(&world,&half,&world);}
 *(Vec*)out=world;if(g_currentBound)GSboundAddPoint(g_currentBound,world.x,world.y,world.z);PSVECAdd(&world,&segment,&world);*(Vec*)(out+0xc)=world;if(g_currentBound)GSboundAddPoint(g_currentBound,world.x,world.y,world.z);
 u8 color[4];peColorSplineGetValue(color,d->colorSpline,progress);color[0]=byte((f32)color[0]*emitter->color[0]);color[1]=byte((f32)color[1]*emitter->color[1]);color[2]=byte((f32)color[2]*emitter->color[2]);color[3]=byte((255.0f*emitter->color[3])*spline(d->alphaSpline,progress));*(u32*)(out+0x18)=*(u32*)color;
 if(flags&0x40000){peColorSplineGetValue(color,d->secondColorSpline,progress);*(u32*)(out+0x2c)=*(u32*)color;}
}
