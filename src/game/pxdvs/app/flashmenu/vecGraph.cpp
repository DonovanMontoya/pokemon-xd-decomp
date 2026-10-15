// Needs extra cflags: -opt nopeephole
#include <dolphin/types.h>

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

extern "C" void vectroGraphSetBlendMode(s32 src, s32 dst) {
    _src = src;
    _dst = dst;
}
