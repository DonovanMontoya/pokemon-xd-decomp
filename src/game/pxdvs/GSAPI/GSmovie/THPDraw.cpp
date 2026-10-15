#include <game/pxdvs/GSAPI/GSmovie/THPDrawPrivate.hpp>
#include <libc/string.h>
extern "C" {
void* GSgfxVFGetPredef(s32);
void GSgfxVideoGetEFBSize(u16*, u16*);
void GSmtx44Ortho(f32*, f32, f32, f32, f32, f32, f32);
extern f32 mtxIdent[3][4];
GSgfxLayer* thpLayer;
}
union THPColorS10 { GXColorS10 color; u32 words[2]; };
union THPColor { GXColor color; u32 packed; };
static const THPColorS10 yuvOffset = {{-90, 0, -114, 135}};
static const THPColor yuvKonst0 = {{0, 0, 226, 88}};
static const THPColor yuvKonst1 = {{179, 0, 0, 182}};
static const THPColor yuvKonst2 = {{255, 0, 255, 128}};
template <unsigned Slot>
static inline void bindTexture(GSgfxLayer* layer, GStexture* texture) {
    GStexture** textures = &layer->field1740;
    GStexture** cached = &layer->field17F8;
    if (textures[Slot] != texture || cached[Slot] != texture || texture->dirty) {
        textures[Slot] = texture;
        layer->field173C |= 1 << Slot;
        cached[Slot] = texture;
        layer->field17F4 |= 1 << Slot;
    }
}
extern "C" {
void THPGXYuv2RgbDraw(void* arg0, void* arg1, void* arg2, u16 arg3, u16 arg4, s16 arg5, s16 arg6, u16 arg7, s16 arg_sp8) {
    GStexture sp108;
    GStexture sp88;
    GStexture sp8;
    s16 temp_r6;
    s16 temp_r3;
    s32 temp_r24;
    s32 temp_r31;

    GStextureCreateFromMemory(&sp108, (u16)arg5, (u16)arg6, arg0, 0x42, 0, 0);
    bindTexture<0>(thpLayer, &sp108);
    temp_r31 = (s16) arg5 >> 1;
    temp_r24 = (s16) arg6 >> 1;
    GStextureCreateFromMemory(&sp88, (u16) temp_r31, (u16) temp_r24, arg1, 0x42, 0, 0);
    bindTexture<1>(thpLayer, &sp88);
    GStextureCreateFromMemory(&sp8, (u16) temp_r31, (u16) temp_r24, arg2, 0x42, 0, 0);
    bindTexture<2>(thpLayer, &sp8);
    thpLayer->field199C = GSgfxVFGetPredef(8);
    thpLayer->field1998 = 0x80;
    thpLayer->beginSurface(4);
    GXPosition2s16((s16)arg3, (s16)arg4);
    GXTexCoord2u8(0, 0);
    GXPosition2s16((s16)arg3 + (s16)arg7, (s16)arg4);
    GXTexCoord2u8(1, 0);
    GXPosition2s16((s16)arg3 + (s16)arg7, (s16)arg4 + arg_sp8);
    GXTexCoord2u8(1, 1);
    GXPosition2s16((s16)arg3, (s16)arg4 + arg_sp8);
    GXTexCoord2u8(0, 1);
    thpLayer->endSurface();
    thpLayer->tokenMark();
}

void THPGXYuv2RgbSetup(void) {
    THPColor spC;
    THPColor sp10;
    THPColor sp14;
    THPColorS10 offset;
    f32 projection[4][4];
    u16 spA;
    u16 sp8;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    s32 var_r0_8;
    s32 *temp_r3;
    GSgfxMatrixStack *temp_r30;
    GSgfxLayer *temp_r30_2;
    GSgfxLayer *temp_r31;

    GSgfxVideoGetEFBSize(&spA, &sp8);
    temp_r31 = thpLayer;
    GSmtx44Ortho(&projection[0][0], 0.0f, (f32)(s32)sp8, 0.0f, (f32)(s32)spA, 0.0f, -30000.0f);
    temp_r31->fieldD54 = 1;
    temp_r31->fieldD58 = projection[0][0];
    temp_r31->fieldD5C = projection[0][3];
    temp_r31->fieldD60 = projection[1][1];
    temp_r31->fieldD64 = projection[1][3];
    temp_r31->fieldD68 = projection[2][2];
    temp_r31->fieldD6C = projection[2][3];
    temp_r30 = temp_r31->field19A0;
    memcpy(temp_r30->current->matrix, &mtxIdent, 0x30);
    temp_r3 = (s32*)&temp_r30->current->flags;
    *temp_r3 |= 1;
    temp_r31->field1684 = 0.0f;
    temp_r31->field1688 = 30000.0f;
    if ((u8) temp_r31->field16A7 != 0) {
        if ((u8) temp_r31->field16A6 != 0) {
            temp_r31->field170C = (s32) (temp_r31->field170C | 0x100);
            temp_r31->field17C4 = (s32) (temp_r31->field17C4 | 0x100);
        }
        temp_r31->field170C = (s32) (temp_r31->field170C | 0x40);
        temp_r31->field16A8 = (s32) (temp_r31->field16A8 | 0x40);
        temp_r31->field17C4 = (s32) (temp_r31->field17C4 | 0x40);
        temp_r31->field1760 = (s32) (temp_r31->field1760 | 0x40);
    }
    temp_r31->field16AC = (s32) (temp_r31->field16AC | 0x20);
    temp_r31->field16A8 = (s32) (temp_r31->field16A8 | 1);
    temp_r31->field1764 = (s32) (temp_r31->field1764 | 0x20);
    temp_r31->field1760 = (s32) (temp_r31->field1760 | 1);
    temp_r30_2 = thpLayer;
    temp_r30_2->fieldD70 = 0;
    temp_r30_2->fieldD72 = 0;
    GSgfxVideoGetEFBSize((u16*)&temp_r30_2->fieldD74, (u16*)&temp_r30_2->fieldD76);
    temp_r30_2->field16B8 = (s32) (temp_r30_2->field16B8 | 1);
    temp_r30_2->field16A8 = (s32) (temp_r30_2->field16A8 | 2);
    temp_r30_2->field1770 = (s32) (temp_r30_2->field1770 | 1);
    temp_r30_2->field1760 = (s32) (temp_r30_2->field1760 | 2);
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1656 = 1;
    layer->field1657 = 0;
    layer->field1658 = 0;
    layer->field170C = (s32) (layer->field170C | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 4);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field165C = 1;
    layer->field1660 = 7;
    layer->field170C = (s32) (layer->field170C | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 8);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    }
    {
        GSgfxLayer* layer = thpLayer;
    if ((s32) layer->field1994 != 0) {
        layer->field1994 = 0;
        layer->field1990 = (u8*)layer + layer->field1994 * 0xBC + 0x1818;
    }
    layer->field1644 = 0;
    layer->field1648 = 1;
    layer->field164C = 1;
    layer->field1650 = 5;
    layer->field170C = (s32) (layer->field170C | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 0x40);
    layer->field17C4 = (s32) (layer->field17C4 | 1);
    layer->field1760 = (s32) (layer->field1760 | 0x40);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldDB8 = 0;
    layer->field16BC = (s32) (layer->field16BC | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 4);
    layer->field1774 = (s32) (layer->field1774 | 1);
    layer->field1760 = (s32) (layer->field1760 | 4);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldC70 = 2;
    layer->field16AC = (s32) (layer->field16AC | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 1);
    layer->field1764 = (s32) (layer->field1764 | 1);
    layer->field1760 = (s32) (layer->field1760 | 1);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->tgenFunc(0, THPTexture2x4, THPTextureCoordinate0, 0, false, 0);
    layer->tgenFunc(1, THPTexture2x4, THPTextureCoordinate0, 0, false, 0);
    layer->field4 = (s32) (layer->field4 | 0x10000000);
    layer->fieldEAC = 4;
    layer->field16CC = (s32) (layer->field16CC | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1784 = (s32) (layer->field1784 | 1);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldEB0 = 1;
    layer->fieldEB4 = 1;
    layer->fieldEB8 = 0xFF;
    layer->field16D0 = (s32) (layer->field16D0 | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1788 = (s32) (layer->field1788 | 1);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldF70 = 0xF;
    layer->fieldF74 = 8;
    layer->fieldF78 = 0xE;
    layer->fieldF7C = 2;
    layer->field16D4 = (s32) (layer->field16D4 | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field178C = (s32) (layer->field178C | 1);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1170 = 0;
    layer->field1174 = 0;
    layer->field1178 = 0;
    layer->field117C = 0;
    layer->field1180 = 0;
    layer->field16DC = (s32) (layer->field16DC | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1794 = (s32) (layer->field1794 | 1);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1070 = 7;
    layer->field1074 = 4;
    layer->field1078 = 6;
    layer->field107C = 1;
    layer->field16D8 = (s32) (layer->field16D8 | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1790 = (s32) (layer->field1790 | 1);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field12B0 = 1;
    layer->field12B4 = 0;
    layer->field12B8 = 0;
    layer->field12BC = 0;
    layer->field12C0 = 0;
    layer->field16E0 = (s32) (layer->field16E0 | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1798 = (s32) (layer->field1798 | 1);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->tunitKRegSel(0, (GSgfxTunitKReg)0);
    layer->field1584 = 0;
    layer->field1588 = 0;
    layer->field1704 = (s32) (layer->field1704 | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 0x20);
    layer->field17BC = (s32) (layer->field17BC | 1);
    layer->field1760 = (s32) (layer->field1760 | 0x20);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldEBC = 1;
    layer->fieldEC0 = 2;
    layer->fieldEC4 = 0xFF;
    layer->field16D0 = (s32) (layer->field16D0 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1788 = (s32) (layer->field1788 | 2);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldF80 = 0xF;
    layer->fieldF84 = 8;
    layer->fieldF88 = 0xE;
    layer->fieldF8C = 0;
    layer->field16D4 = (s32) (layer->field16D4 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field178C = (s32) (layer->field178C | 2);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1184 = 0;
    layer->field1188 = 0;
    layer->field118C = 1;
    layer->field1190 = 0;
    layer->field1194 = 0;
    layer->field16DC = (s32) (layer->field16DC | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1794 = (s32) (layer->field1794 | 2);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1080 = 7;
    layer->field1084 = 4;
    layer->field1088 = 6;
    layer->field108C = 0;
    layer->field16D8 = (s32) (layer->field16D8 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1790 = (s32) (layer->field1790 | 2);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field12C4 = 1;
    layer->field12C8 = 0;
    layer->field12CC = 0;
    layer->field12D0 = 0;
    layer->field12D4 = 0;
    layer->field16E0 = (s32) (layer->field16E0 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1798 = (s32) (layer->field1798 | 2);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->tunitKRegSel(1, (GSgfxTunitKReg)1);
    layer->field158C = 0;
    layer->field1590 = 0;
    layer->field1704 = (s32) (layer->field1704 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 0x20);
    layer->field17BC = (s32) (layer->field17BC | 2);
    layer->field1760 = (s32) (layer->field1760 | 0x20);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldEC8 = 0;
    layer->fieldECC = 0;
    layer->fieldED0 = 0xFF;
    layer->field16D0 = (s32) (layer->field16D0 | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1788 = (s32) (layer->field1788 | 4);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldF90 = 0xF;
    layer->fieldF94 = 8;
    layer->fieldF98 = 0xC;
    layer->fieldF9C = 0;
    layer->field16D4 = (s32) (layer->field16D4 | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field178C = (s32) (layer->field178C | 4);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1198 = 0;
    layer->field119C = 0;
    layer->field11A0 = 0;
    layer->field11A4 = 1;
    layer->field11A8 = 0;
    layer->field16DC = (s32) (layer->field16DC | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1794 = (s32) (layer->field1794 | 4);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1090 = 4;
    layer->field1094 = 7;
    layer->field1098 = 7;
    layer->field109C = 0;
    layer->field16D8 = (s32) (layer->field16D8 | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1790 = (s32) (layer->field1790 | 4);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field12D8 = 0;
    layer->field12DC = 0;
    layer->field12E0 = 0;
    layer->field12E4 = 1;
    layer->field12E8 = 0;
    layer->field16E0 = (s32) (layer->field16E0 | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1798 = (s32) (layer->field1798 | 4);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1594 = 0;
    layer->field1598 = 0;
    layer->field1704 = (s32) (layer->field1704 | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 0x20);
    layer->field17BC = (s32) (layer->field17BC | 4);
    layer->field1760 = (s32) (layer->field1760 | 0x20);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldED4 = 0xFF;
    layer->fieldED8 = 0xFF;
    layer->fieldEDC = 0xFF;
    layer->field16D0 = (s32) (layer->field16D0 | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1788 = (s32) (layer->field1788 | 8);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->fieldFA0 = 1;
    layer->fieldFA4 = 0;
    layer->fieldFA8 = 0xE;
    layer->fieldFAC = 0xF;
    layer->field16D4 = (s32) (layer->field16D4 | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field178C = (s32) (layer->field178C | 8);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field11AC = 0;
    layer->field11B0 = 0;
    layer->field11B4 = 0;
    layer->field11B8 = 1;
    layer->field11BC = 0;
    layer->field16DC = (s32) (layer->field16DC | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1794 = (s32) (layer->field1794 | 8);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field10A0 = 7;
    layer->field10A4 = 7;
    layer->field10A8 = 7;
    layer->field10AC = 7;
    layer->field16D8 = (s32) (layer->field16D8 | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1790 = (s32) (layer->field1790 | 8);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field12EC = 0;
    layer->field12F0 = 0;
    layer->field12F4 = 0;
    layer->field12F8 = 1;
    layer->field12FC = 0;
    layer->field16E0 = (s32) (layer->field16E0 | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field1798 = (s32) (layer->field1798 | 8);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field159C = 0;
    layer->field15A0 = 0;
    layer->field1704 = (s32) (layer->field1704 | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 0x20);
    layer->field17BC = (s32) (layer->field17BC | 8);
    layer->field1760 = (s32) (layer->field1760 | 0x20);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1510 = 0xE;
    layer->field16FC = (s32) (layer->field16FC | 8);
    layer->field16A8 = (s32) (layer->field16A8 | 0x10);
    layer->field17B4 = (s32) (layer->field17B4 | 8);
    layer->field1760 = (s32) (layer->field1760 | 0x10);
    }
    offset = yuvOffset;
    var_r0 = offset.color.r;
    {
        GSgfxLayer* layer = thpLayer;
    layer->field13FC = 1;
    if (var_r0 > -0x400) {

    } else {
        var_r0 = -0x400;
    }
    if (var_r0 < 0x3FF) {
        var_r0_2 = offset.color.r;
        if (var_r0_2 > -0x400) {

        } else {
            var_r0_2 = -0x400;
        }
    } else {
        var_r0_2 = 0x3FF;
    }
    layer->field1400 = var_r0_2;
    var_r0_3 = -0x400;
    if (offset.color.g > -0x400) {
        var_r0_3 = offset.color.g;
    }
    if (var_r0_3 < 0x3FF) {
        var_r0_4 = -0x400;
        if (offset.color.g > -0x400) {
            var_r0_4 = offset.color.g;
        }
    } else {
        var_r0_4 = 0x3FF;
    }
    layer->field1402 = var_r0_4;
    var_r0_5 = -0x400;
    if (offset.color.b > -0x400) {
        var_r0_5 = offset.color.b;
    }
    if (var_r0_5 < 0x3FF) {
        var_r0_6 = -0x400;
        if (offset.color.b > -0x400) {
            var_r0_6 = offset.color.b;
        }
    } else {
        var_r0_6 = 0x3FF;
    }
    layer->field1404 = var_r0_6;
    var_r0_7 = -0x400;
    if (offset.color.a > -0x400) {
        var_r0_7 = offset.color.a;
    }
    if (var_r0_7 < 0x3FF) {
        var_r0_8 = -0x400;
        if (offset.color.a > -0x400) {
            var_r0_8 = offset.color.a;
        }
    } else {
        var_r0_8 = 0x3FF;
    }
    layer->field1406 = var_r0_8;
    layer->field16E4 = (s32) (layer->field16E4 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 8);
    layer->field179C = (s32) (layer->field179C | 2);
    layer->field1760 = (s32) (layer->field1760 | 8);
    }
    sp14 = yuvKonst0;
    {
        GSgfxLayer* layer = thpLayer;
    layer->field14F4 = sp14.packed;
    layer->field16F8 = (s32) (layer->field16F8 | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 0x10);
    layer->field17B0 = (s32) (layer->field17B0 | 1);
    layer->field1760 = (s32) (layer->field1760 | 0x10);
    }
    sp10 = yuvKonst1;
    {
        GSgfxLayer* layer = thpLayer;
    layer->field14F8 = sp10.packed;
    layer->field16F8 = (s32) (layer->field16F8 | 2);
    layer->field16A8 = (s32) (layer->field16A8 | 0x10);
    layer->field17B0 = (s32) (layer->field17B0 | 2);
    layer->field1760 = (s32) (layer->field1760 | 0x10);
    }
    spC = yuvKonst2;
    {
        GSgfxLayer* layer = thpLayer;
    layer->field14FC = spC.packed;
    layer->field16F8 = (s32) (layer->field16F8 | 4);
    layer->field16A8 = (s32) (layer->field16A8 | 0x10);
    layer->field17B0 = (s32) (layer->field17B0 | 4);
    layer->field1760 = (s32) (layer->field1760 | 0x10);
    }
    {
        GSgfxLayer* layer = thpLayer;
    layer->field1604 = 0;
    layer->field1608 = 1;
    layer->field160C = 2;
    layer->field1610 = 3;
    layer->field1708 = (s32) (layer->field1708 | 1);
    layer->field16A8 = (s32) (layer->field16A8 | 0x20);
    layer->field17C0 = (s32) (layer->field17C0 | 1);
    layer->field1760 = (s32) (layer->field1760 | 0x20);
    }
}


void THPGXRestore(void) {

}

void THPGXSetRenderLayer(GSgfxLayer *arg0) {
    thpLayer = arg0;
}

}
