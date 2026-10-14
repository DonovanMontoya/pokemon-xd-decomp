/* XD joint display traversal and robust billboard transforms. */
#include "game/maximum/GSAPI/baselib/displayfunc.h"
#include "game/maximum/GSAPI/baselib/pobj.h"
#include "game/maximum/GSAPI/baselib/dobj.h"
#include <dolphin/mtx.h>
#include "game/maximum/GSAPI/baselib/math_support.h"
#define HSD_ASSERT(line,expr) ((expr)?(void)0:__assert("displayfunc.c",line,#expr))
#define JOBJ_BILLBOARD_FIELD 0xE00
#define JOBJ_BILLBOARD 0x200
#define JOBJ_VBILLBOARD 0x400
#define JOBJ_HBILLBOARD 0x600
#define JOBJ_RBILLBOARD 0x800
#define JOBJ_PBILLBOARD 0x2000
#define JOBJ_SKELETON 1
#define JOBJ_SKELETON_ROOT 2
#define JOBJ_SPECULAR 0x10000
#define DOBJ_HIDDEN 1
#define DOBJ_TRSP_SHIFT 1
#define RENDER_SHADOW 0x4000000
typedef unsigned int HSD_TrspMask;
void HSD_Panic(const char*,int,const char*);
void HSD_JObjSetCurrent(HSD_JObj*);
void HSD_LObjSetupSpecularInit(Mtx);
HSD_CObj* HSD_CObjGetCurrent(void);
static inline void HSD_MtxColVec(MtxPtr m,int c,Vec* v) { v->x=m[0][c]; v->y=m[1][c]; v->z=m[2][c]; }
static inline void HSD_MtxSetColVec(MtxPtr m,int c,Vec* v) { m[0][c]=v->x; m[1][c]=v->y; m[2][c]=v->z; }
static inline float HSD_MtxColMag(MtxPtr m,int c) { return hsdSqrt(m[0][c]*m[0][c]+m[1][c]*m[1][c]+m[2][c]*m[2][c]); }
static void (*sptcl_callback)(int,int,int,HSD_JObj*);
static void mkVBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst);
static void mkHBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst);
static void mkBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst);
static void mkRBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst);
void HSD_JObjMakePositionMtx(HSD_JObj* jobj, Mtx vmtx, Mtx pmtx);
static inline HSD_JObj* HSD_JObjFindSkeleton(HSD_JObj* jobj);
MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx);
void HSD_JObjDispSub(HSD_JObj* jobj, MtxPtr vmtx, MtxPtr pmtx,
                     HSD_TrspMask trsp_mask, unsigned int rendermode);
void _HSD_DispForgetMemory(void* lo,void* hi) { }
void HSD_JObjSetSPtclCallback(void (*func)(int,int,int,HSD_JObj*)) { sptcl_callback=func; }
typedef struct XD_JObjInfo { HSD_ClassInfo parent; void* load; void* make_mtx; void (*make_pmtx)(HSD_JObj*,Mtx,Mtx); void (*disp)(HSD_JObj*,Mtx,Mtx,unsigned int,unsigned int); } XD_JObjInfo;
#define JMETHOD(o) ((XD_JObjInfo*)(o)->object.class_info)
void HSD_JObjDisp(HSD_JObj* jobj,MtxPtr vmtx,unsigned int trsp_mask,unsigned int rendermode) {
    if (jobj==0) return;
    if (union_type_dobj(jobj)) {
        Mtx mtx;
        unsigned int xlu_bits;
        if (jobj->flags & 0x10) return;
        xlu_bits=jobj->flags & (trsp_mask<<18);
        if (xlu_bits==0) return;
        HSD_JObjSetupMatrix(jobj);
        if (vmtx==0) vmtx=HSD_CObjGetCurrent()->view_mtx;
        JMETHOD(jobj)->make_pmtx(jobj,vmtx,mtx);
        if (xlu_bits&0x40000) JMETHOD(jobj)->disp(jobj,vmtx,mtx,1,rendermode);
        if (xlu_bits&0x100000) JMETHOD(jobj)->disp(jobj,vmtx,mtx,4,rendermode);
        if (xlu_bits&0x80000) JMETHOD(jobj)->disp(jobj,vmtx,mtx,2,rendermode);
    } else if ((jobj->flags&JOBJ_PTCL) && sptcl_callback) {
        HSD_SList* list;
        for(list=jobj->u.ptcl;list;list=list->next) {
            unsigned int value=(unsigned int)list->data;
            if(value&0x80000000) sptcl_callback(0,value&63,(value>>6)&0xffffff,jobj);
            list->data=(void*)((unsigned int)list->data&0x7fffffff);
        }
    }
}
/* XD normalizes billboard axes and handles degenerate cross products. */
static void mkVBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec pos, ax, ay, az, ny;
    float sx, sz, mag;
    HSD_MtxColVec(src,3,&pos);
    HSD_MtxColVec(src,1,&ay);
    VECScale(&ay,&ny,1.0f / (__float_epsilon[0] + VECMag(&ay)));
    sx=HSD_MtxColMag(src,0);
    sz=HSD_MtxColMag(src,2);
    if(jobj->flags & JOBJ_PBILLBOARD) {
        VECScale(&pos,&az,-1.0f / (__float_epsilon[0] + VECMag(&pos)));
        VECCrossProduct(&ny,&az,&ax);
    } else {
        const Vec z={0,0,1};
        VECCrossProduct(&ny,&z,&ax);
    }
    mag=VECMag(&ax);
    if(!(mag < __float_epsilon[0])) {
        sx/=mag;
        VECCrossProduct(&ax,&ny,&az);
        sz/=__float_epsilon[0]+VECMag(&az);
        dst[0][0]=sx*ax.x; dst[1][0]=sx*ax.y; dst[2][0]=sx*ax.z;
        HSD_MtxSetColVec(dst,1,&ay);
        dst[0][2]=sz*az.x; dst[1][2]=sz*az.y; dst[2][2]=sz*az.z;
        HSD_MtxSetColVec(dst,3,&pos);
    } else MTXCopy(src,dst);
}
static void mkHBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec pos, ax, ay, az, nx;
    float sy, sz, mag;
    HSD_MtxColVec(src,3,&pos);
    HSD_MtxColVec(src,0,&ax);
    VECScale(&ax,&nx,1.0f / (__float_epsilon[0] + VECMag(&ax)));
    sy=HSD_MtxColMag(src,1);
    sz=HSD_MtxColMag(src,2);
    if(jobj->flags & JOBJ_PBILLBOARD) {
        ay.y=__float_epsilon[0]+hsdSqrt(pos.x*pos.x+pos.z*pos.z);
        ay.x=-pos.y/ay.y*pos.x;
        ay.z=-pos.y/ay.y*pos.z;
        VECNormalize(&ay,&ay);
    } else { ay.x=0; ay.y=1; ay.z=0; }
    VECCrossProduct(&nx,&ay,&az);
    mag=VECMag(&az);
    if(!(mag < __float_epsilon[0])) {
        sz/=mag;
        VECCrossProduct(&az,&nx,&ay);
        sy/=__float_epsilon[0]+VECMag(&ay);
        HSD_MtxSetColVec(dst,0,&ax);
        dst[0][1]=sy*ay.x; dst[1][1]=sy*ay.y; dst[2][1]=sy*ay.z;
        dst[0][2]=sz*az.x; dst[1][2]=sz*az.y; dst[2][2]=sz*az.z;
        HSD_MtxSetColVec(dst,3,&pos);
    } else MTXCopy(src,dst);
}
static void mkBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec ax, ay, az, pos;
    float sx, sy, sz, mag;
    sx=HSD_MtxColMag(src,0);
    sz=HSD_MtxColMag(src,2);
    HSD_MtxColVec(src,1,&ay);
    sy=VECMag(&ay);
    HSD_MtxColVec(src,3,&pos);
    if(jobj->flags & JOBJ_PBILLBOARD) {
        VECScale(&pos,&az,-1.0f / (__float_epsilon[0]+VECMag(&pos)));
    } else { az.x=0; az.y=0; az.z=1; }
    VECScale(&ay,&ay,1.0f / (sy+__float_epsilon[0]));
    VECCrossProduct(&ay,&az,&ax);
    mag=VECMag(&ax);
    if(mag >= __float_epsilon[0]) {
        sx/=mag;
        VECCrossProduct(&az,&ax,&ay);
        sy/=__float_epsilon[0]+VECMag(&ay);
    } else {
        ay.y=__float_epsilon[0]+hsdSqrt(az.x*az.x+az.z*az.z);
        ay.x=-az.y/ay.y*az.x;
        ay.z=-az.y/ay.y*az.z;
        VECCrossProduct(&ay,&az,&ax);
        sx/=__float_epsilon[0]+VECMag(&ax);
    }
    dst[0][0]=sx*ax.x; dst[1][0]=sx*ax.y; dst[2][0]=sx*ax.z;
    dst[0][1]=sy*ay.x; dst[1][1]=sy*ay.y; dst[2][1]=sy*ay.z;
    dst[0][2]=sz*az.x; dst[1][2]=sz*az.y; dst[2][2]=sz*az.z;
    HSD_MtxSetColVec(dst,3,&pos);
}

static void mkRBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Mtx rot, scl;
    float sx, sy, sz;
    sx = HSD_MtxColMag(src, 0);
    sy = HSD_MtxColMag(src, 1);
    sz = HSD_MtxColMag(src, 2);
    MTXScale(scl, sx, sy, sz);
    MTXRotRad(rot, 'z', jobj->rotate.z);
    rot[0][3] = src[0][3];
    rot[1][3] = src[1][3];
    rot[2][3] = src[2][3];
    MTXConcat(rot, scl, dst);
}

void HSD_JObjMakePositionMtx(HSD_JObj* jobj, Mtx vmtx, Mtx pmtx)
{
    Mtx mtx;

    if (jobj->flags & JOBJ_BILLBOARD_FIELD) {
        MTXConcat(vmtx, jobj->mtx, mtx);
        switch (jobj->flags & JOBJ_BILLBOARD_FIELD) {
        case JOBJ_BILLBOARD:
            mkBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_VBILLBOARD:
            mkVBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_HBILLBOARD:
            mkHBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_RBILLBOARD:
            mkRBillBoardMtx(jobj, mtx, pmtx);
            break;
        default:
            HSD_Panic("displayfunc.c", 305, "unkown type of billboard.\n");
        }
    } else {
        MTXConcat(vmtx, jobj->mtx, pmtx);
    }
}

static inline HSD_JObj* HSD_JObjFindSkeleton(HSD_JObj* jobj)
{
    HSD_ASSERT(325, jobj);
    for (; jobj; jobj = jobj->parent) {
        if (jobj->flags & (JOBJ_SKELETON | JOBJ_SKELETON_ROOT)) {
            return jobj;
        }
    }
    return NULL;
}

MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx)
{
    if (m->flags & JOBJ_SKELETON_ROOT) {
        return NULL;
    } else {
        HSD_JObj* x = HSD_JObjFindSkeleton(m);
        HSD_ASSERT(405, x);

        if (x == m) {
            MTXInverse(x->envelopemtx, mtx);
        } else if (x->flags & JOBJ_SKELETON_ROOT) {
            HSD_MtxInverseConcat(x->mtx, m->mtx, mtx);
        } else {
            Mtx n;
            MTXConcat(x->mtx, x->envelopemtx, n);
            HSD_MtxInverseConcat(n, m->mtx, mtx);
        }

        return mtx;
    }
}

void HSD_JObjDispSub(HSD_JObj* jobj, MtxPtr vmtx, MtxPtr pmtx,
                     HSD_TrspMask trsp_mask, unsigned int rendermode)
{
    HSD_DObj* dobj;
    unsigned int dobj_trsp;

    HSD_JObjSetCurrent(jobj);

    dobj_trsp = trsp_mask << DOBJ_TRSP_SHIFT;

    if (!(rendermode & RENDER_SHADOW)) {
        if (jobj->flags & JOBJ_SPECULAR) {
            HSD_LObjSetupSpecularInit(pmtx);
        }
    }

    HSD_PObjClearMtxMark(NULL, 0);
    for (dobj = jobj->u.dobj; dobj; dobj = dobj->next) {
        if (dobj->flags & DOBJ_HIDDEN) {
            continue;
        }

        if (dobj->flags & dobj_trsp) {
            HSD_DObjSetCurrent(dobj);
            HSD_DOBJ_METHOD(dobj)->disp(dobj, vmtx, pmtx, rendermode);
        }
    }
    HSD_DObjSetCurrent(NULL);
    HSD_JObjSetCurrent(NULL);
}
