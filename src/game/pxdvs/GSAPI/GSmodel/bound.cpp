#include <game/pxdvs/GSAPI/GSmodel/boundPrivate.hpp>
static void _modelBoundPObj(_HSD_PObj*,GSmtx*,GSmtx*,GSmtx*,void*);
static void _modelBoundVertex(u32,void*,void*);
static void _modelBoundBeginSurface(GSgfxPrimType,u16,u32,void*);
extern "C" void GSmodelRecalculateBound(BoundModel *model) {
 if(!GSboundHasAnimData(model->bound)) {
  GSboundReset(model->bound);
  void *animation=model->animation;
  model->animation=0;
  f32 px=model->position.x,py=model->position.y,pz=model->position.z;
  model->position.x=0.0f;model->position.y=0.0f;model->position.z=0.0f;
  f32 rx=model->rotation.x,ry=model->rotation.y,rz=model->rotation.z;
  model->rotation.x=0.0f;model->rotation.y=0.0f;model->rotation.z=0.0f;
  f32 sx=model->scale.x,sy=model->scale.y,sz=model->scale.z;
  model->scale.x=1.0f;model->scale.y=1.0f;model->scale.z=1.0f;
  GSmodelForceAnimTransformUpdate(model);
  GSmodelParse(model,1,_modelBoundPObj,model);
  model->animation=animation;
  model->position.x=px;model->position.y=py;model->position.z=pz;
  model->rotation.x=rx;model->rotation.y=ry;model->rotation.z=rz;
  model->scale.x=sx;model->scale.y=sy;model->scale.z=sz;
 }
}
static void _modelBoundPObj(_HSD_PObj *pobj,GSmtx *unused,GSmtx *matrix,GSmtx *matrices,void *model) {
 static BoundCallbacks cblist={_modelBoundBeginSurface,0,_modelBoundVertex,0,0};
 BoundCallbacks *callbacks=&cblist;
 BoundContext context;
 context.model=(BoundModel*)model;context.matrices=matrices;context.matrix=matrix;
 GSgfxParseDisplayList(pobj->attributes,pobj->displayList,pobj->displayListSize<<5,callbacks,&context);
}
static inline int initialMatrixIndex() {return 0;}
static void _modelBoundVertex(u32 flags,void *attribute,void *data) {
 BoundContext *context=(BoundContext*)data;
 static int mtxidx=initialMatrixIndex();
 if(flags&1) mtxidx=*(u8*)attribute/3;
 if(flags&2) {
  GSmtx *matrix;
  if(context->mask&1) matrix=context->matrices+mtxidx;
  else matrix=context->matrix;
  Vec *source=(Vec*)attribute;
  BoundPoint point(source->x,source->y,source->z);
  PSMTXMultVec(matrix->m,&point,&point);
  void *bound=GSmodelGetBound(context->model);
  GSboundAddPoint(bound,point.x,point.y,point.z);
 }
}
static void _modelBoundBeginSurface(GSgfxPrimType primitive,u16 count,u32 flags,void *data) {
 ((BoundContext*)data)->mask=flags;
}
