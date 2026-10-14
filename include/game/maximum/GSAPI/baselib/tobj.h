#ifndef HSD_TOBJ_H
#define HSD_TOBJ_H
#include "game/maximum/GSAPI/baselib/aobj.h"
#include "game/maximum/GSAPI/baselib/class.h"
#include "game/maximum/GSAPI/baselib/mtx_base.h"
typedef struct HSD_ImageDesc { void* image_ptr; unsigned short width, height; unsigned int format, mipmap; float minLOD, maxLOD; } HSD_ImageDesc;
typedef struct HSD_Tlut { void* lut; int fmt; unsigned int tlut_name; unsigned short n_entries; } HSD_Tlut;
typedef HSD_Tlut HSD_TlutDesc;
typedef struct HSD_TexLODDesc { int minFilt; float LODBias; unsigned char bias_clamp, edgeLODEnable; int max_anisotropy; } HSD_TexLODDesc;
typedef struct HSD_TObjTev { unsigned char color_op, alpha_op, color_bias, alpha_bias, color_scale, alpha_scale, color_clamp, alpha_clamp; unsigned char color_a, color_b, color_c, color_d, alpha_a, alpha_b, alpha_c, alpha_d; struct { unsigned char r,g,b,a; } konst, tev0, tev1; unsigned int active; } HSD_TObjTev;
typedef HSD_TObjTev HSD_TObjTevDesc;
/* Shared prefix size 0x68, full XD texture runtime size 0xAC. */
typedef struct HSD_TObjRuntime { HSD_TObj base; HSD_ImageDesc** imagetbl; HSD_Tlut** tluttbl; unsigned char tlut_no; HSD_Mtx mtx; int coord; HSD_TObjTev* tev; } HSD_TObjRuntime;
#define TOBJ_EXT(o) ((HSD_TObjRuntime*)(o))
typedef struct HSD_TObjDesc { char* class_name; struct HSD_TObjDesc* next; int id, src; HSD_Vec3 rotate, scale, translate; int wrap_s,wrap_t; unsigned char repeat_s,repeat_t; unsigned int blend_flags; float blending; int magFilt; HSD_ImageDesc* imagedesc; HSD_TlutDesc* tlutdesc; HSD_TexLODDesc* lod; HSD_TObjTevDesc* tev; } HSD_TObjDesc;
typedef struct HSD_TexAnim { struct HSD_TexAnim* next; int id; HSD_AObjDesc* aobjdesc; HSD_ImageDesc** imagetbl; HSD_TlutDesc** tluttbl; unsigned short n_imagetbl, n_tluttbl; } HSD_TexAnim;
typedef union HSD_TExp HSD_TExp;
typedef struct HSD_TObjInfo { HSD_ClassInfo parent; void (*make_mtx)(HSD_TObj*); int (*load)(HSD_TObj*,HSD_TObjDesc*); void (*make_texp)(HSD_TObj*,unsigned long,unsigned long,HSD_TExp**,HSD_TExp**,HSD_TExp**); HSD_ObjUpdateFunc update; } HSD_TObjInfo;
#define HSD_TOBJ_METHOD(o) ((HSD_TObjInfo*)(o)->parent.class_info)
#endif
