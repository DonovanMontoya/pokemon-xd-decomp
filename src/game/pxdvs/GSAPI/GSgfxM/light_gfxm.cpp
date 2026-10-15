#include <game/pxdvs/GSAPI/GSgfxM/light_gfxmPrivate.hpp>
static inline void initShininess(GXLightObj *object,f32 shininess) {
 f32 coefficient=shininess/2.0f;
 GXInitLightAttn(object,0.0f,0.0f,1.0f,coefficient,0.0f,1.0f-coefficient);
}
u32 GSgfxLight::Load(u8 slot) {
 if(flags&1) {GXColor c=*(GXColor*)&color;GXInitLightColor(&object,c);}
 switch(mode) {
 case 0:
  if(flags&0x20) GXInitSpecularDirHA(&object,direction.x,direction.y,direction.z,settings.half.x,settings.half.y,settings.half.z);
  else if(flags&4) GXInitSpecularDir(&object,direction.x,direction.y,direction.z);
  if(flags&0x40) {
   initShininess(&object,settings.params[3]);
  }
  break;
 case 1:
  if(flags&4) GXInitLightDir(&object,direction.x,direction.y,direction.z);
  if(flags&0x10) {
   GXInitLightSpot(&object,settings.spot.cutoff,settings.spot.spot);
   GXInitLightDistAttn(&object,settings.spot.distance,settings.spot.brightness,settings.spot.attenuation);
  } else if(flags&8) GXInitLightAttn(&object,settings.params[0],settings.params[1],settings.params[2],settings.params[3],settings.params[4],settings.params[5]);
 case 2:
  if(flags&2) GXInitLightPos(&object,position.x,position.y,position.z);
  break;
 }
 flags=0;
 index=slot;
 u32 id=1<<slot;
 GXLoadLightObjImm(&object,(GXLightID)id);
 return id;
}
void GSgfxLight::MakeSpec(GSgfxColAu8 *c,GSvec *dir,f32 shininess,GSvec *half) {
 flags=0;mode=0;
 color.r=c->r;color.g=c->g;color.b=c->b;color.a=c->a;flags|=1;
 direction.x=dir->x;direction.y=dir->y;direction.z=dir->z;flags|=4;
 settings.params[3]=shininess;flags|=0x40;
 if(half) {settings.half.x=half->x;settings.half.y=half->y;settings.half.z=half->z;flags|=0x20;}
}
void GSgfxLight::MakeDiff(GSgfxColAu8 *c,GSvec *pos,bool directional) {
 flags=0;mode=2;
 color.r=c->r;color.g=c->g;color.b=c->b;color.a=c->a;flags|=1;
 if(directional) {
  Vec normalized;PSVECNormalize((Vec*)pos,&normalized);
  f32 y=normalized.y,z=normalized.z,x=normalized.x;
  position.x=x;position.y=y;position.z=z;
  PSVECScale((Vec*)&position,(Vec*)&position,-1.0e18f);
 } else {position.x=pos->x;position.y=pos->y;position.z=pos->z;}
 flags|=2;
}
GSgfxLight::GSgfxLight() {
 color.r=255;color.g=255;color.b=255;color.a=255;
 position.x=0.0f;position.y=0.0f;position.z=0.0f;
 GXColor c=*(GXColor*)&color;GXInitLightColor(&object,c);
 GXInitLightPos(&object,0.0f,0.0f,0.0f);
 mode=2;flags=0;
}
