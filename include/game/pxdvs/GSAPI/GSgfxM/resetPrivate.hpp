#ifndef RESET_PRIVATE_HPP
#define RESET_PRIVATE_HPP
#include <global.h>
#include <dolphin/mtx.h>
struct SpriteMatrixFrame {u32 flags; Mtx matrix;};
struct SpriteMatrixStack {u32 reserved; SpriteMatrixFrame* frame;};
struct GSgfxLayer {
    u32 unk0;
    u32 unk4;
    u8 reserved8[0xd4c];
    u32 unkD54;
    f32 unkD58;
    f32 unkD5C;
    f32 unkD60;
    f32 unkD64;
    f32 unkD68;
    f32 unkD6C;
    u16 unkD70;
    u16 unkD72;
    u16 unkD74;
    u16 unkD76;
    u8 reservedd78[0x14];
    u32 unkD8C;
    u32 unkD90;
    u8 reservedd94[0x8b0];
    u32 unk1644;
    u32 unk1648;
    u32 unk164C;
    u32 unk1650;
    u8 reserved1654[0x2];
    u8 unk1656;
    u8 unk1657;
    u8 unk1658;
    u8 reserved1659[0x3];
    u8 unk165C;
    u8 reserved165d[0x3];
    u32 unk1660;
    u32 unk1664;
    u32 unk1668;
    u32 unk166C;
    u8 unk1670;
    u8 unk1671;
    u8 unk1672;
    u8 reserved1673[0x11];
    f32 unk1684;
    f32 unk1688;
    u8 reserved168c[0x1a];
    u8 unk16A6;
    u8 unk16A7;
    u32 unk16A8;
    u32 unk16AC;
    u8 reserved16b0[0x8];
    u32 unk16B8;
    u8 reserved16bc[0x50];
    u32 unk170C;
    u8 reserved1710[0x50];
    u32 unk1760;
    u32 unk1764;
    u8 reserved1768[0x8];
    u32 unk1770;
    u8 reserved1774[0x50];
    u32 unk17C4;
    u8 reserved17c8[0x50];
    u8 shaders[2][0xBC];
    void* unk1990;
    u32 unk1994;
    u32 unk1998;
    u8 reserved199c[4];
    SpriteMatrixStack* unk19A0;
};
extern "C" {
extern GSgfxLayer* _TargetLayer;
GSgfxLayer* GSgfxLayerFindByID(s32);
s32 floorGetMenuLayerID();
void GSgfxVideoGetEFBSize(u16*,u16*);
void GSmtx44Perspective(Mtx44,f32,f32,f32,f32);
extern Mtx mtxIdent;
}
#endif
