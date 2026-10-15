#ifndef LIGHT_GFXM_PRIVATE_HPP
#define LIGHT_GFXM_PRIVATE_HPP
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct GSgfxColAu8 {u8 r,g,b,a;};
struct GSvec {f32 x,y,z;};
class GSgfxLight {
public:
 u16 flags,pad; s32 mode; GSgfxColAu8 color; GSvec position,direction;
 union Settings {
  f32 params[6];
  struct {f32 cutoff;GXSpotFn spot;f32 distance,brightness;GXDistAttnFn attenuation;f32 reserved;} spot;
  GSvec half;
 } settings;
 GXLightObj object;u8 index;
 GSgfxLight();
 u32 Load(u8);
 void MakeSpec(GSgfxColAu8*,GSvec*,f32,GSvec*);
 void MakeDiff(GSgfxColAu8*,GSvec*,bool);
};
typedef char LightObjectOffset[offsetof(GSgfxLight,object)==0x3c?1:-1];
typedef char LightIndexOffset[offsetof(GSgfxLight,index)==0x7c?1:-1];
#endif
