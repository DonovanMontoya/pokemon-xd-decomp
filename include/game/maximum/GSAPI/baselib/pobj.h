#ifndef HSD_POBJ_H
#define HSD_POBJ_H
#include "game/maximum/GSAPI/baselib/dobj.h"
#include <dolphin/gx.h>
typedef struct HSD_VtxDescList { GXAttr attr; GXAttrType attr_type; GXCompCnt comp_cnt; GXCompType comp_type; unsigned char frac; unsigned short stride; unsigned char* vertex; } HSD_VtxDescList;
typedef struct HSD_Envelope { struct HSD_Envelope* next; HSD_JObj* jobj; float weight; } HSD_Envelope;
typedef struct HSD_EnvelopeDesc { HSD_Joint* joint; float weight; } HSD_EnvelopeDesc;
typedef struct HSD_ShapeSetDesc { unsigned short flags, nb_shape; int nb_vertex_index; HSD_VtxDescList* vertex_desc; unsigned char** vertex_idx_list; int nb_normal_index; HSD_VtxDescList* normal_desc; unsigned char** normal_idx_list; } HSD_ShapeSetDesc;
struct HSD_ShapeAnim { struct HSD_ShapeAnim* next; HSD_AObjDesc* aobjdesc; };
typedef struct HSD_PObjDesc { char* class_name; struct HSD_PObjDesc* next; HSD_VtxDescList* verts; unsigned short flags, n_display; unsigned char* display; union { HSD_Joint* joint; HSD_ShapeSetDesc* shape_set; HSD_EnvelopeDesc** envelope_p; } u; } HSD_PObjDesc;
typedef struct HSD_PObjInfo { HSD_ClassInfo parent; void (*disp)(HSD_PObj*, HSD_Mtx, HSD_Mtx, unsigned int); void (*setup_mtx)(HSD_PObj*, HSD_Mtx, HSD_Mtx, unsigned int); int (*load)(HSD_PObj*, HSD_PObjDesc*); HSD_ObjUpdateFunc update; } HSD_PObjInfo;
extern HSD_PObjInfo hsdPObj;
#define HSD_POBJ(o) ((HSD_PObj*)(o))
#define HSD_POBJ_INFO(o) ((HSD_PObjInfo*)(o))
#define HSD_POBJ_METHOD(o) HSD_POBJ_INFO((o)->class_info)
void HSD_PObjDisp(HSD_PObj*,HSD_Mtx,HSD_Mtx,unsigned int);
HSD_PObj* HSD_PObjLoadDesc(HSD_PObjDesc*);
void HSD_PObjClearMtxMark(void*,unsigned int);
void HSD_PObjSetMtxMark(int,void*,unsigned int);
void HSD_PObjGetMtxMark(int,void**,unsigned int*);
void HSD_ClearVtxDesc(void);
void HSD_PObjRemoveAnimAllByFlags(HSD_PObj*,unsigned int);
void HSD_PObjAddAnimAll(HSD_PObj*,HSD_ShapeAnim*);
void HSD_PObjReqAnimAllByFlags(HSD_PObj*,float,unsigned int);
void HSD_PObjAnimAll(HSD_PObj*);
void HSD_PObjRemoveAll(HSD_PObj*);
void HSD_PObjResolveRefsAll(HSD_PObj*,HSD_PObjDesc*);
void HSD_PObjCountVertices(HSD_PObj*,unsigned int*,unsigned int*);
void* HSD_SetVertexBuffer(void*,unsigned int);
void* HSD_SetNormalBuffer(void*,unsigned int);
typedef char HSD_PObjSizeCheck[sizeof(HSD_PObj)==0x1c?1:-1];
typedef char HSD_PObjInfoSizeCheck[sizeof(HSD_PObjInfo)==0x4c?1:-1];
#endif
