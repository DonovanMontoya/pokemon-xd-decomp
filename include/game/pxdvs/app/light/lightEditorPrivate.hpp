#pragma once
#include <dolphin/gx/GXVert.h>
#include <dolphin/types.h>

struct GSlight;
struct GSgfxVF;
enum GSgfxPrimType { PrimDummy };
enum GSgfxBlendType { BlendDummy };
enum GSgfxBlendFactor { FactorDummy };
enum GSgfxLayerPass { PassDummy };
enum GSgfxCullType { CullDummy };
enum GSgfxACmpFunc { ACmpDummy };
enum GSgfxAlphaOp { AlphaDummy };
enum GSgfxZCmpFunc { ZCmpDummy };
struct LightBlendRecord { u8 bytes[0xBC]; };

class GSgfxLayer {
public:
    u8 pad0[0x28];
    s32 unk28;
    u8 pad2C[0xD08];
    u8 unkD34;
    u8 padD35[3];
    s32 unkD38;
    u8 padD3C[0x50];
    s32 unkD8C;
    u8 padD90[2228];
    s32 unk1644;
    s32 unk1648;
    s32 unk164C;
    s32 unk1650;
    u8 pad1654[2];
    u8 unk1656;
    u8 unk1657;
    u8 unk1658;
    u8 pad1659[3];
    u8 unk165C;
    u8 pad165D[3];
    s32 unk1660;
    s32 unk1664;
    s32 unk1668;
    s32 unk166C;
    u8 unk1670;
    u8 unk1671;
    u8 unk1672;
    u8 pad1673[53];
    s32 unk16A8;
    s32 unk16AC;
    u8 pad16B0[8];
    s32 unk16B8;
    u8 pad16BC[80];
    s32 unk170C;
    u8 pad1710[80];
    s32 unk1760;
    s32 unk1764;
    u8 pad1768[8];
    s32 unk1770;
    u8 pad1774[80];
    s32 unk17C4;
    u8 pad17C8[80];
    LightBlendRecord records[2];
    void* unk1990;
    s32 unk1994;
    s32 unk1998;

    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

class LightEditor {
public:
    s8 mUnk0;
    s8 mUnk1;
    s8 mUnk2;
    s8 mUnk3;
    s8 mUnk4;
    f32 mUnk8;

    LightEditor();
    void init();
    void editDirection(GSlight*);
    void editPosition(GSlight*);
    void editType(GSlight*);
    void editCommand();
    void dispLightModel(GSlight*, bool);
    void dispInfo(GSlight*, long, long, bool);
    void editUpdate();
};

// MWCC -inline off would not inline these as members, so expand them as macros.
#define LAYER_OR(l, field, bits) ((l)->field = (s32)((l)->field | (bits)))
#define LAYER_PIXELMODE(l, a, b, c) do { \
    if ((a) == 1) { (l)->unk1656 = 1; } else { (l)->unk1656 = 0; } \
    if ((b) == 1) { (l)->unk1657 = 1; } else { (l)->unk1657 = 0; } \
    if ((c) == 1) { (l)->unk1658 = 1; } else { (l)->unk1658 = 0; } \
    LAYER_OR(l, unk170C, 4); LAYER_OR(l, unk16A8, 0x40); LAYER_OR(l, unk17C4, 4); LAYER_OR(l, unk1760, 0x40); \
} while (0)
#define LAYER_ZCOMPARE(l, a, f) do { \
    if ((a) == 1) { (l)->unk165C = 1; } else { (l)->unk165C = 0; } \
    (l)->unk1660 = (f); \
    LAYER_OR(l, unk170C, 8); LAYER_OR(l, unk16A8, 0x40); LAYER_OR(l, unk17C4, 8); LAYER_OR(l, unk1760, 0x40); \
} while (0)
#define LAYER_ALPHACOMPARE_OFF(l) do { \
    (l)->unk1664 = 7; (l)->unk1670 = 0; (l)->unk1668 = 0; (l)->unk166C = 7; (l)->unk1671 = 0; (l)->unk1672 = 1; \
    LAYER_OR(l, unk170C, 0x10); LAYER_OR(l, unk16A8, 0x40); LAYER_OR(l, unk17C4, 0x10); LAYER_OR(l, unk1760, 0x40); \
} while (0)
#define LAYER_CULLMODE(l, m) do { \
    (l)->unkD8C = (m); \
    LAYER_OR(l, unk16B8, 2); LAYER_OR(l, unk16A8, 2); LAYER_OR(l, unk1770, 2); LAYER_OR(l, unk1760, 2); \
} while (0)
#define LAYER_SETRENDERPASS(l, p) do { \
    if ((l)->unk1994 != (p)) { (l)->unk1994 = (p); (l)->unk1990 = &(l)->records[(l)->unk1994]; } \
} while (0)
#define LAYER_BLENDMODE_NORMAL(l, a, b, c) do { \
    LAYER_SETRENDERPASS(l, 1); \
    (l)->unk1644 = (a); (l)->unk1648 = (b); (l)->unk164C = (c); (l)->unk1650 = 5; \
    LAYER_OR(l, unk170C, 1); LAYER_OR(l, unk16A8, 0x40); LAYER_OR(l, unk17C4, 1); LAYER_OR(l, unk1760, 0x40); \
} while (0)
#define LAYER_PRIMITIVETYPE(l, t) ((l)->unk1998 = (t))
#define LAYER_LINESIZE(l, w, o) do { \
    (l)->unkD34 = (w); (l)->unkD38 = (o); \
    LAYER_OR(l, unk16AC, 4); LAYER_OR(l, unk16A8, 1); LAYER_OR(l, unk1764, 4); LAYER_OR(l, unk1760, 1); \
} while (0)
#define LAYER_VERTEX3F(x, y, z) do { \
    f32 vx_ = (x); f32 vy_ = (y); f32 vz_ = (z); \
    GXWGFifo.f32 = vx_; GXWGFifo.f32 = vy_; GXWGFifo.f32 = vz_; \
} while (0)
#define LAYER_COLOR4U8(r, g, b, a) do { \
    u8 cr_ = (r); u8 cg_ = (g); u8 cb_ = (b); u8 ca_ = (a); \
    GXWGFifo.u8 = cr_; GXWGFifo.u8 = cg_; GXWGFifo.u8 = cb_; GXWGFifo.u8 = ca_; \
} while (0)
