/* XD shadow texture lifecycle, viewing bounds, and rendering. */
#include "game/maximum/GSAPI/baselib/shadow_base.h"
#include "game/maximum/GSAPI/baselib/jobj.h"
#include "game/maximum/GSAPI/baselib/math_support.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <libc/string.h>
#include "game/maximum/GSAPI/baselib/tev.h"
#include "game/maximum/GSAPI/baselib/mobj.h"
#include "game/maximum/GSAPI/baselib/pobj.h"
#define HSD_ASSERT(line,expr) ((expr)?(void)0:__assert("shadow.c",line,#expr))
double atan2(double,double);
static inline int normalize_check(Vec3* src,Vec3* dst) {
    if(!src || !dst) return -1;
    if(__fabs(src->x)<=__float_min[0] && __fabs(src->y)<=__float_min[0] && __fabs(src->z)<=__float_min[0]) return -1;
    VECNormalize((Vec*)src,(Vec*)dst); return 0;
}
void GSmemFree(void*);
void* GSmemAllocAlignFromEnd(unsigned int,unsigned int);
HSD_TObj* HSD_TObjAlloc(void);
HSD_ImageDesc* HSD_ImageDescAlloc(void);
void HSD_MObjAddShadowTexture(HSD_TObj*);
void HSD_MObjDeleteShadowTexture(HSD_TObj*);
HSD_SList* HSD_SListAlloc(void);
HSD_SList* HSD_SListRemove(HSD_SList*);
void HSD_JObjUnref(HSD_JObj*);
void HSD_LObjGetPosition(HSD_LObj*,Vec3*);
HSD_SList* HSD_SListPrepend(HSD_SList*,void*);
static inline HSD_SList* HSD_SListAllocAndPrepend(HSD_SList* list,void* data) { return HSD_SListPrepend(list,data); }
static inline void HSD_JObjRef(HSD_JObj* jobj) { if (jobj) { jobj->object.ref_count++; if(jobj->object.ref_count==0xffff) __assert("object.h",93,"HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"); } }
HSD_ObjAllocData shadow_alloc_data;
static unsigned char shadow_debug;

static inline HSD_TObj* makeShadowTObj(void)
{
    HSD_TObj* shadowTObj;
    shadowTObj = HSD_TObjAlloc();
    shadowTObj->src = 0;
    shadowTObj->wrap_s = 0;
    shadowTObj->wrap_t = 0;
    shadowTObj->flags = 0x540103;
    shadowTObj->imagedesc = HSD_ImageDescAlloc();
    return shadowTObj;
}

/* Render the normalized background square used for the shadow texture. */
static inline void drawBackgroundRect(HSD_Shadow* shadow)
{
    GXLoadPosMtxImm(HSD_identityMtx,GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    HSD_ClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XY,GX_U8,0);
    HSD_StateSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS,GX_VTXFMT0,4);
    GXPosition2u8(0,1); GXPosition2u8(1,1);
    GXPosition2u8(1,0); GXPosition2u8(0,0);
    GXEnd();
}
void HSD_JObjDispAll(HSD_JObj*,Mtx,unsigned int,unsigned int);

HSD_ObjAllocData* HSD_ShadowGetAllocData(void);
void HSD_ShadowInitAllocData(void);
HSD_Shadow* HSD_ShadowAlloc(void);
void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height);
void HSD_ShadowSetActive(HSD_Shadow* shadow, int active);
void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj);
void HSD_ShadowDeleteObject(HSD_Shadow* shadow, HSD_JObj* jobj);
void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, float top, float bottom,
                              float left, float right);
void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec3* position, Vec3* interest, Vec3* upvector, int perspective);
int HSD_ViewingRectCheck(HSD_ViewingRect* rect);
void HSD_ViewingRectAddRect(HSD_ViewingRect* rect, Vec3* position, float top,
                            float bottom, float left, float right);
void HSD_ShadowSetDebug(unsigned char debug);
void HSD_ShadowFreeTexture(HSD_Shadow* shadow);
void HSD_ShadowCopyTex(HSD_Shadow* shadow);
void HSD_ShadowCopyLightPos(HSD_Shadow* shadow,HSD_LObj* lobj,float distance);
void HSD_ShadowRender(HSD_Shadow* shadow);

HSD_ObjAllocData* HSD_ShadowGetAllocData(void)
{
    return &shadow_alloc_data;
}

void HSD_ShadowInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_ShadowGetAllocData(), sizeof(HSD_Shadow), 4);
}

HSD_Shadow* HSD_ShadowAlloc(void)
{
    HSD_Shadow* shadow;

    shadow = HSD_ObjAlloc(HSD_ShadowGetAllocData());
    memset(shadow, 0, sizeof(HSD_Shadow));
    shadow->camera = HSD_CObjAlloc();
    shadow->texture = makeShadowTObj();

    shadow->scaleS = 0.5F;
    shadow->scaleT = -0.5F;
    shadow->transS = 0.5F;
    shadow->transT = 0.5F;
    shadow->intensity = 0;

    ((HSD_ImageDesc*)shadow->texture->imagedesc)->format = 0;
    ((HSD_ImageDesc*)shadow->texture->imagedesc)->width = 256;
    ((HSD_ImageDesc*)shadow->texture->imagedesc)->height = 256;
    ((HSD_ImageDesc*)shadow->texture->imagedesc)->image_ptr = NULL;

    HSD_CObjSetViewportfx4(shadow->camera, 0.0f, 256.f, 0.0f, 256.f);
    HSD_CObjSetScissorx4(shadow->camera, 0, 256, 0, 256);

    return shadow;
}

void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height)
{
    unsigned int size;
    HSD_ImageDesc* idesc;

    HSD_ASSERT(272, shadow);
    HSD_ASSERT(273, width > 0);
    HSD_ASSERT(274, height > 0);

    idesc = shadow->texture->imagedesc;
    if (!idesc->image_ptr || idesc->width != width || idesc->height != height)
    {
        if (idesc->image_ptr) {
            HSD_ShadowFreeTexture(shadow);
        }

        size = GXGetTexBufferSize(width, height, GX_TF_I4, GX_FALSE, 0);
        HSD_ASSERT(283, size > 0);
        idesc->image_ptr = GSmemAllocAlignFromEnd(size,32);
        if (idesc->image_ptr) {
        DCFlushRange(idesc->image_ptr,size);
        idesc->width = width;
        idesc->height = height;

        HSD_CObjSetViewportfx4(shadow->camera, 0, width, 0, height);
        HSD_CObjSetScissorx4(shadow->camera, 0, width, 0, height);
        }
    }
}

void HSD_ShadowRender(HSD_Shadow* shadow)
{
    HSD_CObj* cobj;
    HSD_ImageDesc* idesc;
    HSD_SList* list;
    static HSD_Chan chan = {
        NULL,GX_COLOR0A0,0,{0,0,0,0},{0,0,0,255},GX_FALSE,
        GX_SRC_REG,GX_SRC_REG,GX_LIGHT_NULL,GX_DF_CLAMP,GX_AF_NONE,NULL
    };
    static HSD_TevDesc tev = {
        NULL,TEVCONF_MODE,GX_TEVSTAGE0,GX_TEXCOORD_NULL,GX_TEXMAP_NULL,GX_COLOR0A0,
        { { GX_TEV_ADD,GX_CC_ZERO,GX_CC_ZERO,GX_CC_ZERO,GX_CC_RASC,
            GX_CS_SCALE_1,GX_TB_ZERO,GX_TRUE,GX_TEVPREV,
            GX_TEV_ADD,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_RASA,
            GX_CS_SCALE_1,GX_TB_ZERO,GX_TRUE,GX_TEVPREV,GX_TC_LINEAR,
            GX_TEV_SWAP0,GX_TEV_SWAP0,GX_TEV_KCSEL_1,GX_TEV_KASEL_1,
            GX_CH_RED,GX_CH_GREEN,GX_CH_BLUE,GX_CH_ALPHA } }
    };
    static HSD_PEDesc pedesc={9,0,0,0,GX_BM_NONE,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_SET,
                            GX_ALWAYS,GX_ALWAYS,GX_AOP_AND,GX_ALWAYS};
    HSD_ASSERT(400,shadow);
    HSD_ASSERT(401,shadow->camera);
    HSD_ASSERT(402,shadow->texture);
    HSD_ASSERT(403,shadow->texture->imagedesc);
    if(shadow->objects) {
        Mtx44 projection;
        cobj=shadow->camera;
        idesc=shadow->texture->imagedesc;
        HSD_ASSERT(411,idesc->image_ptr);
        HSD_StateInitTev();
        HSD_SetupTevStageAll(&tev);
        HSD_StateSetNumTexGens();
        HSD_SetupPEMode(0,&pedesc);
        chan.mat_color.r=255; chan.mat_color.g=255; chan.mat_color.b=255;
        HSD_SetupChannelAll(&chan);
        MTXOrtho(projection,1,0,0,1,-1,1);
        GXSetProjection(projection,GX_ORTHOGRAPHIC);
        GXSetViewport(0,0,idesc->width,idesc->height,0,1);
        GXSetScissor(0,0,idesc->width,idesc->height);
        drawBackgroundRect(shadow);
        if(shadow_debug) {
            chan.mat_color.r=0; chan.mat_color.g=0; chan.mat_color.b=0;
            HSD_SetupChannelAll(&chan);
            GXSetScissor(2,2,idesc->width-4,idesc->height-4);
            drawBackgroundRect(shadow);
            chan.mat_color.r=255; chan.mat_color.g=255; chan.mat_color.b=255;
            HSD_SetupChannelAll(&chan);
            GXSetScissor(4,4,idesc->width-8,idesc->height-8);
            drawBackgroundRect(shadow);
        }
        chan.mat_color.r=shadow->intensity;
        chan.mat_color.g=shadow->intensity;
        chan.mat_color.b=shadow->intensity;
        HSD_SetupChannelAll(&chan);
        if(HSD_CObjGetEyeDistance(cobj)>=__float_epsilon[0]) {
            HSD_CObjSetCurrent(cobj);
            GXSetScissor(2,2,idesc->width-4,idesc->height-4);
            for(list=shadow->objects;list;list=list->next) HSD_JObjDispAll(list->data,NULL,5,RENDER_SHADOW);
        }
        if(HSD_CObjGetEyeDistance(shadow->camera)<__float_epsilon[0]) {
            static Mtx m={{0,0,0,0},{0,0,0,0},{0,0,0,1}};
            MTXCopy(m,TOBJ_EXT(shadow->texture)->mtx);
        } else {
            Mtx Mprj;
            switch(HSD_CObjGetProjectionType(shadow->camera)) {
            case PROJ_PERSPECTIVE:
                MTXLightPerspective(Mprj,shadow->camera->projection_param[0],shadow->camera->projection_param[1],
                    shadow->scaleS,shadow->scaleT,shadow->transS,shadow->transT);
                break;
            case PROJ_FRUSTUM:
                MTXLightFrustum(Mprj,shadow->camera->projection_param[0],shadow->camera->projection_param[1],
                    shadow->camera->projection_param[2],shadow->camera->projection_param[3],shadow->camera->near,
                    shadow->scaleS,shadow->scaleT,shadow->transS,shadow->transT);
                break;
            case PROJ_ORTHO:
                MTXLightOrtho(Mprj,shadow->camera->projection_param[0],shadow->camera->projection_param[1],
                    shadow->camera->projection_param[2],shadow->camera->projection_param[3],
                    shadow->scaleS,shadow->scaleT,shadow->transS,shadow->transT);
                break;
            default: HSD_ASSERT(711,0);
            }
            MTXConcat(Mprj,shadow->camera->view_mtx,TOBJ_EXT(shadow->texture)->mtx);
        }
    }
}

void HSD_ShadowCopyTex(HSD_Shadow* shadow) {
    HSD_ImageDesc* idesc;
    HSD_ASSERT(489,shadow);
    idesc=shadow->texture->imagedesc;
    HSD_ASSERT(493,idesc->image_ptr);
    GXSetTexCopySrc(0,0,idesc->width,idesc->height);
    GXSetTexCopyDst(idesc->width,idesc->height,0x20,0);
    GXCopyTex(idesc->image_ptr,GX_TRUE);
}

void HSD_ShadowCopyLightPos(HSD_Shadow* shadow,HSD_LObj* lobj,float distance) {
    Vec3 pos,interest,direction;
    HSD_ASSERT(522,shadow);
    HSD_ASSERT(523,lobj);
    switch(lobj->flags&3) {
    case 1:
        HSD_CObjGetInterest(shadow->camera,&interest);
        HSD_LObjGetPosition(lobj,&direction);
        VECScale((Vec*)&direction,(Vec*)&direction,distance/(__float_epsilon[0]+VECMag((Vec*)&direction)));
        VECAdd((Vec*)&interest,(Vec*)&direction,(Vec*)&pos);
        HSD_CObjSetEyePosition(shadow->camera,&pos);
        break;
    case 2: case 3:
        HSD_LObjGetPosition(lobj,&pos);
        HSD_CObjSetEyePosition(shadow->camera,&pos);
        break;
    default: HSD_ASSERT(541,0);
    }
}

void HSD_ShadowSetActive(HSD_Shadow* shadow, int active)
{
    HSD_ImageDesc* idesc;

    HSD_ASSERT(563, shadow);

    if ((shadow->active && active) || (!shadow->active && !active)) {
        return;
    }

    shadow->active = active;
    if (active) {
        idesc = shadow->texture->imagedesc;
        if (!idesc->image_ptr) {
            HSD_ShadowSetSize(shadow, idesc->width, idesc->height);
        }

        HSD_MObjAddShadowTexture(shadow->texture);
    } else {
        HSD_MObjDeleteShadowTexture(shadow->texture);
    }
}

void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj)
{
    HSD_SList* list;

    if (!shadow || !jobj) {
        return;
    }

    for (list = shadow->objects; list; list = list->next) {
        if (list->data == jobj) {
            return;
        }
    }
    shadow->objects = HSD_SListAllocAndPrepend(shadow->objects, jobj);
    HSD_JObjRef(jobj);
}

void HSD_ShadowDeleteObject(HSD_Shadow* shadow, HSD_JObj* jobj)
{
    if (!shadow) {
        return;
    }

    if (jobj) {
        HSD_SList** list = &(shadow->objects);
        for (; *list; list = &((*list)->next)) {
            if ((*list)->data == jobj) {
                HSD_JObjUnref(jobj);
                (*list) = HSD_SListRemove(*list);
                return;
            }
        }
    } else {
        while (shadow->objects) {
            HSD_JObjUnref(shadow->objects->data);
            shadow->objects = HSD_SListRemove(shadow->objects);
        }
    }
}

void HSD_ShadowFreeTexture(HSD_Shadow* shadow) {
    HSD_ImageDesc* idesc=shadow->texture->imagedesc;
    if(idesc->image_ptr) { GSmemFree(idesc->image_ptr); idesc->image_ptr=0; }
}

void HSD_ShadowSetDebug(unsigned char debug) { shadow_debug=debug; }

void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, float top, float bottom,
                              float left, float right)
{
    HSD_CObj* cobj;
    float distance;

    HSD_ASSERT(734, shadow);

    cobj = shadow->camera;
    distance = HSD_CObjGetEyeDistance(cobj);
    if (distance < __float_epsilon[0]) return;

    switch (HSD_CObjGetProjectionType(cobj)) {
    case PROJ_PERSPECTIVE: {
        float width, height;

        if (__fabs(top) > __fabs(bottom)) {
            width = __fabs(top);
        } else {
            width = __fabs(bottom);
        }
        if (__fabs(left) > __fabs(right)) {
            height = __fabs(left);
        } else {
            height = __fabs(right);
        }
        HSD_CObjSetAspect(cobj, height / (width+__float_epsilon[0]));
        HSD_CObjSetFov(cobj, 57.295779513f * (float)atan2(width, distance));
    } break;

    case PROJ_ORTHO:
        HSD_CObjSetOrtho(cobj, top, bottom, left, right);
        break;

    case PROJ_FRUSTUM: {
        float scale = HSD_CObjGetNear(cobj) / distance;
        if (scale < __float_epsilon[0]) scale=__float_epsilon[0];
        HSD_CObjSetFrustum(cobj, scale * top, scale * bottom, scale * left,
                           scale * right);
    } break;

    default:
        HSD_ASSERT(779, 0);
    }
}

void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec3* position, Vec3* interest, Vec3* upvector, int perspective)
{
    HSD_ASSERT(810,rect);
    rect->invalid=0;
    rect->origin=*position;
    VECSubtract((Vec*)interest,(Vec*)position,(Vec*)&rect->eye_v);
    if(normalize_check(&rect->eye_v,&rect->eye_vn)<0) { rect->invalid=1; return; }
    else {
        VECCrossProduct((Vec*)&rect->eye_vn,(Vec*)upvector,(Vec*)&rect->right_v);
        if(normalize_check(&rect->right_v,&rect->right_v)<0) {
            HSD_VecGetOrthogonal(&rect->eye_vn,&rect->right_v);
            VECNormalize((Vec*)&rect->right_v,(Vec*)&rect->right_v);
        }
        VECCrossProduct((Vec*)&rect->right_v,(Vec*)&rect->eye_vn,(Vec*)&rect->up_v);
    }
    rect->distance=VECMag((Vec*)&rect->eye_v);
    rect->top=rect->right=-3.402823466e+38F;
    rect->bottom=rect->left=3.402823466e+38F;
    rect->perspective=perspective!=0;
}

int HSD_ViewingRectCheck(HSD_ViewingRect* rect)
{
    HSD_ASSERT(840, rect);
    return !rect->invalid && rect->top > rect->bottom && rect->right > rect->left;
}

/* Stripped from the DOL; its assertion string still occupies .rodata. */
void HSD_ViewingRectScale(HSD_ViewingRect* rect, float a)
{
    HSD_ASSERT(860, a > 0.0F);
    rect->top *= a;
}

void HSD_ViewingRectAddRect(HSD_ViewingRect* rect, Vec3* position, float top,
                            float bottom, float left, float right)
{
    float x, y, dot, scale;
    Vec3 o2p, e2p;

    HSD_ASSERT(878, rect);
    HSD_ASSERT(879, position);
    if(rect->invalid) return;

    VECSubtract((Vec*)position, (Vec*)&rect->origin, (Vec*)&o2p);
    dot = VECDotProduct((Vec*)&o2p, (Vec*)&rect->eye_vn);
    if (rect->perspective) {
        if (dot <= 0.0F) {
            return;
        }
        scale = rect->distance / dot;
        VECScale((Vec*)&o2p, (Vec*)&o2p, scale);
        VECSubtract((Vec*)&o2p, (Vec*)&rect->eye_v, (Vec*)&e2p);
        x = VECDotProduct((Vec*)&rect->right_v, (Vec*)&e2p);
        y = VECDotProduct((Vec*)&rect->up_v, (Vec*)&e2p);

        top *= scale;
        bottom *= scale;
        left *= scale;
        right *= scale;
    } else {
        Vec3 tmp;
        VECScale((Vec*)&rect->eye_vn, (Vec*)&tmp, dot);
        VECSubtract((Vec*)&o2p, (Vec*)&tmp, (Vec*)&e2p);
        x = VECDotProduct((Vec*)&rect->right_v, (Vec*)&e2p);
        y = VECDotProduct((Vec*)&rect->up_v, (Vec*)&e2p);
    }

    if (x + right > rect->right) {
        rect->right = x + right;
    }
    if (x + left < rect->left) {
        rect->left = x + left;
    }
    if (y + top > rect->top) {
        rect->top = y + top;
    }
    if (y + bottom < rect->bottom) {
        rect->bottom = y + bottom;
    }
}
