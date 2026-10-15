// Needs extra cflags: -opt nopeephole
#include <dolphin/types.h>

struct GStexture;
struct GSvec2 {
    f32 x, y;
};
struct FLASHMATRIXF {
    f32 m[6];
};
struct FLASHMATRIX {
    s32 m[6];
};
struct FLASHCXFORM {
    s16 v[8];
};
struct VEC_GRAPH_DATA;
struct GXColor {
    u8 r, g, b, a;
};
struct GXColorS10 {
    s16 r, g, b, a;
};
struct SHAPEMOVE {
    s32 pad;
    s32 x;
    s32 y;
};
struct _SHAPERECORD {
    u8 type;
    u8 pad[3];
    SHAPEMOVE *move;
    _SHAPERECORD *next;
};

extern "C" {
GStexture *FlashSystemGetGStexture(u32 id, long index);
void GSprimDraw2DTexQuad4V(const GSvec2 *, const GSvec2 *, GStexture *, const GXColor *);
void GSprimDraw2DTexQuad4VCA(const GSvec2 *, const GSvec2 *, GStexture *, const GXColor *, const GXColorS10 *);
}

struct SBRow {
    s8 count;
    u8 pad;
    s16 pts[0xA53];
};

typedef char SBRowSize[sizeof(SBRow) == 0x14A8 ? 1 : -1];

s32 bit_value[32] = {
    0x00000001,
    0x00000002,
    0x00000004,
    0x00000008,
    0x00000010,
    0x00000020,
    0x00000040,
    0x00000080,
    0x00000100,
    0x00000200,
    0x00000400,
    0x00000800,
    0x00001000,
    0x00002000,
    0x00004000,
    0x00008000,
    0x00010000,
    0x00020000,
    0x00040000,
    0x00080000,
    0x00100000,
    0x00200000,
    0x00400000,
    0x00800000,
    0x01000000,
    0x02000000,
    0x04000000,
    0x08000000,
    0x10000000,
    0x20000000,
    0x40000000,
    0x80000000
};

u8 gVecDat[0x1464];
u8 scanline_buffer[0x25800];
static u8 vecRect[0x10];
SBRow lPoint[4];
static u32 lList[0x601];

static s32 debugstep = 1;
static s32 _type = 1;
static s32 _src = 4;
static s32 _dst = 5;
static s32 _typemask = 1;
static s32 _srcmask = 4;
static s32 _dstmask = 5;

static void SBdec(u32 bits, s16 idx, u32 n) {
    u32 i;
    if ((bits & 0xFF) != 0) {
        s32 base = idx * 8;
        for (i = 0; i < n; i++) {
            if ((bits & bit_value[i]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base;
            }
            if ((bits & bit_value[i + 4]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 1;
            }
        }
    }
    if ((bits & 0xFF00) != 0) {
        s32 base = idx * 8;
        for (i = 0; i < n; i++) {
            if ((bits & bit_value[i + 8]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 2;
            }
            if ((bits & bit_value[i + 12]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 3;
            }
        }
    }
    if ((bits & 0xFF0000) != 0) {
        s32 base = idx * 8;
        for (i = 0; i < n; i++) {
            if ((bits & bit_value[i + 16]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 4;
            }
            if ((bits & bit_value[i + 20]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 5;
            }
        }
    }
    if ((bits & 0xFF000000) != 0) {
        s32 base = idx * 8;
        for (i = 0; i < n; i++) {
            if ((bits & bit_value[i + 24]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 6;
            }
            if ((bits & bit_value[i + 28]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 7;
            }
        }
    }
}

static void getUV(GSvec2 *, GSvec2 *, GSvec2 *, FLASHMATRIXF *, FLASHMATRIXF *, GStexture *);
static void SpriteDisp(GStexture *, FLASHMATRIXF *, FLASHMATRIX *, GSvec2 *, VEC_GRAPH_DATA *, FLASHCXFORM *);

static _SHAPERECORD *SpriteCode(u32 id, _SHAPERECORD *rec, u16 index, FLASHMATRIXF *m, FLASHMATRIX *fm, long x, long y,
                                VEC_GRAPH_DATA *vg, FLASHCXFORM *cx) {
    GSvec2 pts[4];
    _SHAPERECORD *last = 0;
    s32 n = 0;
    u8 more = 1;
    do {
        if (rec->type == 2) {
            x += rec->move->x;
            y += rec->move->y;
            last = rec;
            GSvec2 *q = (GSvec2 *)((u8 *)pts + n * 8);
            n++;
            q->x = (f32)x / 20.0f;
            q->y = (f32)y / 20.0f;
            rec = rec->next;
        } else {
            more = 0;
        }
    } while (more);
    SpriteDisp(FlashSystemGetGStexture(id, index), m, fm, pts, vg, cx);
    return last;
}

static void SpriteDisp(GStexture *tex, FLASHMATRIXF *m, FLASHMATRIX *fm, GSvec2 *vec, VEC_GRAPH_DATA *vg, FLASHCXFORM *cx) {
    if (tex != 0) {
        FLASHMATRIXF fl;
        GSvec2 uv[4];
        GSvec2 pos[4];
        GXColorS10 add;
        GXColor col;
        fl.m[0] = (f32)fm->m[0] / 1310720.0f;
        fl.m[1] = (f32)fm->m[1] / 1310720.0f;
        fl.m[2] = (f32)fm->m[2] / 1310720.0f;
        fl.m[3] = (f32)fm->m[3] / 1310720.0f;
        fl.m[4] = (f32)fm->m[4] / 20.0f;
        fl.m[5] = (f32)fm->m[5] / 20.0f;
        getUV(pos, uv, vec, m, &fl, tex);
        col.a = (cx->v[0] * 0xff) >> 8;
        col.r = (cx->v[2] * 0xff) >> 8;
        col.g = (cx->v[4] * 0xff) >> 8;
        s32 aa = cx->v[1];
        s32 ar = cx->v[3];
        s32 ag = cx->v[5];
        s32 ab = cx->v[7];
        add.a = aa;
        col.b = (cx->v[6] * 0xff) >> 8;
        add.r = ar;
        add.g = ag;
        add.b = ab;
        if (((s16)aa | (s16)ar | (s16)ag | (s16)ab) == 0) {
            GXColor c = col;
            GSprimDraw2DTexQuad4V(pos, uv, tex, &c);
            return;
        }
        {
            GXColor c = col;
            GXColorS10 a = add;
            GSprimDraw2DTexQuad4VCA(pos, uv, tex, &c, &a);
        }
    }
}

extern "C" void vectroGraphSetBlendMode(s32 src, s32 dst) {
    _src = src;
    _dst = dst;
}
