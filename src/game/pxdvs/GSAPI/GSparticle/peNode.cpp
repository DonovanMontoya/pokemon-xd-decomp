#include <game/pxdvs/GSAPI/GSparticle/peNodePrivate.hpp>

extern "C" void peNodeTransformsConcat(NodeTransform *out, NodeTransform *parent, NodeTransform *local, u8 billboard) {
 Mtx matrix;
 Quaternion rotation;
 f32 px=local->position.x*parent->scale.x, py=local->position.y*parent->scale.y, pz=local->position.z*parent->scale.z;
 out->position.x=px; out->position.y=py; out->position.z=pz;
 PSMTXQuat(matrix,&parent->rotation);
 PSMTXMultVecSR(matrix,&out->position,&out->position);
 PSVECAdd(&out->position,&parent->position,&out->position);
 if(billboard) C_QUATMtx(&out->rotation,*GSgfxMatrixGetPtr(3));
 else {
  PSQUATMultiply(&parent->rotation,&local->rotation,&rotation);
  f32 y=rotation.y,z=rotation.z,w=rotation.w,x=rotation.x;
  out->rotation.x=x; out->rotation.y=y; out->rotation.z=z; out->rotation.w=w;
 }
 f32 sx=local->scale.x*parent->scale.x, sy=local->scale.y*parent->scale.y, sz=local->scale.z*parent->scale.z;
 out->scale.x=sx; out->scale.y=sy; out->scale.z=sz;
}

static inline void copyVec(Vec *out,const Vec *in) {out->x=in->x;out->y=in->y;out->z=in->z;}
static inline void copyQuat(Quaternion *out,const Quaternion *in) {out->x=in->x;out->y=in->y;out->z=in->z;out->w=in->w;}
static inline void unscale(Vec *v,NodeTransform *transform) {
 if(0.0f!=transform->scale.x) v->x/=transform->scale.x;
 if(0.0f!=transform->scale.y) v->y/=transform->scale.y;
 if(0.0f!=transform->scale.z) v->z/=transform->scale.z;
}

u8 peNode::Update(peEmitterNode *owner,f32 delta) {
 Mtx forceMatrix,positionMatrix,inversePositionMatrix,velocityMatrix,inverseVelocityMatrix;
 Vec change,force;
 Quaternion forceRotation,positionRotation,velocityRotation;
 Quaternion forceInverse;
 Vec relativeForce,scaledForce,displacement;
 Quaternion positionInverse,velocityInverse;
 _peEmitter *emitter;
 f32 magnitude=forceFactor;
 if(magnitude<0.0f) magnitude=-magnitude;
 bool accelerated=magnitude>0.00001f;
 time-=delta;
 if(time<=0.0f) return 0;
 if(!owner) return 1;
 emitter=owner->emitter;
 if(accelerated) {
  copyVec(&force,&owner->force);
  if(!(emitter->flags&0x100)) {
   PSQUATInverse(&transform->rotation,&forceInverse);
   copyQuat(&forceRotation,&forceInverse);
   PSMTXQuat(forceMatrix,&forceRotation);
   PSMTXMultVecSR(forceMatrix,&force,&force);
  }
  if(emitter->flags&0x10000) {
   PSVECSubtract(&force,&position,&relativeForce);
   copyVec(&change,&relativeForce);
   f32 distance=PSVECMag(&change);
   if(distance>0.00001f) PSVECScale(&change,&change,(delta*(emitter->attraction*forceFactor))/distance);
  } else {
   PSVECScale(&force,&scaledForce,forceFactor*delta);
   copyVec(&change,&scaledForce);
  }
  PSVECAdd(&velocity,&change,&velocity);
  f32 friction=emitter->friction;
  if(friction) PSVECScale(&velocity,&velocity,1.0f-friction);
 }
 PSVECScale(&velocity,&displacement,delta);
 copyVec(&change,&displacement);
 PSVECAdd(&position,&change,&position);
 if(accelerated&&(emitter->flags&0x200)) {
  f32 x=position.x*transform->scale.x,y=position.y*transform->scale.y,z=position.z*transform->scale.z;
  change.x=x; change.y=y; change.z=z;
  PSMTXQuat(positionMatrix,&transform->rotation);
  PSMTXMultVecSR(positionMatrix,&change,&change);
  PSVECAdd(&change,&transform->position,&change);
  if(change.y<0.0f) {
   if(change.y<0.0f) {
    change.y=0.0f;
    PSVECSubtract(&change,&transform->position,&change);
    PSQUATInverse(&transform->rotation,&positionInverse);
    copyQuat(&positionRotation,&positionInverse);
    PSMTXQuat(inversePositionMatrix,&positionRotation);
    PSMTXMultVecSR(inversePositionMatrix,&change,&change);
    unscale(&change,transform);
    copyVec(&position,&change);
    f32 x=velocity.x*transform->scale.x,y=velocity.y*transform->scale.y,z=velocity.z*transform->scale.z;
    change.x=x; change.y=y; change.z=z;
    PSMTXQuat(velocityMatrix,&transform->rotation);
    PSMTXMultVecSR(velocityMatrix,&change,&change);
    change.y=change.y*emitter->bounce;
    PSQUATInverse(&transform->rotation,&velocityInverse);
    copyQuat(&velocityRotation,&velocityInverse);
    PSMTXQuat(inverseVelocityMatrix,&velocityRotation);
    PSMTXMultVecSR(inverseVelocityMatrix,&change,&change);
    unscale(&change,transform);
    copyVec(&velocity,&change);
   }
  }
 }
 return 1;
}

void peNode::Start(peEmitterNode *owner,_EmitParams *params) {
 life=time=params->life;
 forceFactor=params->forceFactor;
 copyVec(&position,&params->position);
 copyVec(&velocity,&params->velocity);
 if(owner&&(owner->emitter->flags&0x40)) {
  copyVec(&transform->position,&params->transform.position);
  copyQuat(&transform->rotation,&params->transform.rotation);
  copyVec(&transform->scale,&params->transform.scale);
 }
}
