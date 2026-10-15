#include <game/pxdvs/app/effects/glowPrivate.hpp>
#include <libc/string.h>
void operator delete(void*);
s32 glowEffect::texture_layer_id=-1;
u16 glowEffect::token;
u8 glowEffect::layer_reference;
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32);
void GSgfxTokenWaitForClear(u16);
GSgfxVF* GSgfxVFBuildTemp(s32,s32,u8,s32,u8,s32,u8,s32,s32);
void GSmtx44Ortho(Mtx44,f32,f32,f32,f32,f32,f32);
extern Mtx mtxIdent;
s32 Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(char*,u32,u32,u32,s32,bool,bool,bool,s32,s32);
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(s32);
void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(GSgfxLayer*,u8,s32,s32,Mtx,bool,Mtx);
void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(GSgfxLayer*,u8,s32,s32,s32,u32,void**,s32,s32);
}
static inline u8 glowAlpha(f32 value){if(value<0.0f)return 0;if(value>255.0f)return 255;return (u8)value;}
glowEffect::~glowEffect(){
    Stop();
    if(layer_reference && --layer_reference==0){
        GSgfxLayer*layer=GSgfxLayerFindByID(texture_layer_id);
        if(token){GSgfxTokenWaitForClear(token);token=0;}
        if(layer)layer->SetTextureCopy(0,false,0);
        Remove__16GSgfxLayerConfigF12GSgfxLayerID(texture_layer_id);
        texture_layer_id=-1;
    }
}
glowEffect::glowEffect(){
    strength=1.0f;radius=12;alphaBlend=1;subtract=0;mode=1;count=1;
    if(texture_layer_id==-1){
        texture_layer_id=Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset("glow effect",0,0x400,1,0,false,false,false,6,1);
        GSgfxLayer*layer=GSgfxLayerFindByID(texture_layer_id);
        if(layer)layer->SetTextureCopy((GStexture*)0xFEFEFEFE,false,0);
    }
    ++layer_reference;
}
void glowEffect::_render(GSgfxLayer *arg1, GSgfxLayerPass arg2) {
    Mtx44 projection;
    GlowMatrixFrame *temp_r3_2;
    s32 var_r8;
    u8 temp_r0;
    GlowMatrixStack *temp_r28;
    GStexture *temp_r3;
    GSgfxLayer* capture;

    if (((s32) texture_layer_id != -1) && ((s32) arg1->unk28 == 6) && (arg2 == 1) ) {
        capture=GSgfxLayerFindByID(texture_layer_id);
        if(!capture)return;
        temp_r3 = capture->GetTextureCopy();
        if (temp_r3 != 0) {
            GSmtx44Ortho(projection, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
            arg1->unkD54 = 1;
            arg1->unkD58 = projection[0][0];
            arg1->unkD5C = projection[0][3];
            arg1->unkD60 = projection[1][1];
            arg1->unkD64 = projection[1][3];
            arg1->unkD68 = projection[2][2];
            arg1->unkD6C = projection[2][3];
            temp_r28 = arg1->unk19A0;
            memcpy(temp_r28->frame->matrix, &mtxIdent, 0x30);
            temp_r3_2 = temp_r28->frame;
            temp_r3_2->flags |= 1;
            arg1->unk1684 = 0.0f;
            arg1->unk1688 = 30000.0f;
            if ((u8) arg1->unk16A7 != 0) {
                if ((u8) arg1->unk16A6 != 0) {
                    arg1->unk170C = (s32) (arg1->unk170C | 0x100);
                    arg1->unk17C4 = (s32) (arg1->unk17C4 | 0x100);
                }
                arg1->unk170C = (s32) (arg1->unk170C | 0x40);
                arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
                arg1->unk17C4 = (s32) (arg1->unk17C4 | 0x40);
                arg1->unk1760 = (s32) (arg1->unk1760 | 0x40);
            }
            var_r8 = 1;
            arg1->unk16AC = (s32) (arg1->unk16AC | 0x20);
            arg1->unk16A8 = (s32) (arg1->unk16A8 | 1);
            arg1->unk1764 = (s32) (arg1->unk1764 | 0x20);
            arg1->unk1760 = (s32) (arg1->unk1760 | 1);
            if ((u8) alphaBlend != 0) {
                var_r8 = 5;
            }
            if ((s32) arg1->unk1994 != 1) {
                arg1->unk1994 = 1;
                arg1->unk1990 = &arg1->records[arg1->unk1994];
            }
            arg1->unk1644 = 1;
            arg1->unk1648 = 4;
            arg1->unk164C = var_r8;
            arg1->unk1650 = 5;
            arg1->unk170C = (s32) (arg1->unk170C | 1);
            arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
            arg1->unk17C4 = (s32) (arg1->unk17C4 | 1);
            arg1->unk1760 = (s32) (arg1->unk1760 | 0x40);
            arg1->unk1656 = 1;
            arg1->unk1657 = 1;
            arg1->unk1658 = 0;
            arg1->unk170C = (s32) (arg1->unk170C | 4);
            arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
            arg1->unk17C4 = (s32) (arg1->unk17C4 | 4);
            arg1->unk1760 = (s32) (arg1->unk1760 | 0x40);
            arg1->unk1664 = 7;
            arg1->unk1670 = 0;
            arg1->unk1668 = 0;
            arg1->unk166C = 7;
            arg1->unk1671 = 0;
            arg1->unk1672 = 1;
            arg1->unk170C = (s32) (arg1->unk170C | 0x10);
            arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
            arg1->unk17C4 = (s32) (arg1->unk17C4 | 0x10);
            arg1->unk1760 = (s32) (arg1->unk1760 | 0x40);
            arg1->unk165C = 0;
            arg1->unk1660 = 3;
            arg1->unk170C = (s32) (arg1->unk170C | 8);
            arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
            arg1->unk17C4 = (s32) (arg1->unk17C4 | 8);
            arg1->unk1760 = (s32) (arg1->unk1760 | 0x40);
            arg1->unkD8C = 2;
            arg1->unk16B8 = (s32) (arg1->unk16B8 | 2);
            arg1->unk16A8 = (s32) (arg1->unk16A8 | 2);
            arg1->unk1770 = (s32) (arg1->unk1770 | 2);
            arg1->unk1760 = (s32) (arg1->unk1760 | 2);
            if ((arg1->unk1740 != temp_r3) || (arg1->unk17F8 != temp_r3) || ((u8) temp_r3->dirty != 0)) {
                arg1->unk1740 = temp_r3;
                arg1->unk173C = (s32) (arg1->unk173C | 1);
                arg1->unk17F8 = temp_r3;
                arg1->unk17F4 = (s32) (arg1->unk17F4 | 1);
            }
            arg1->unk1998 = 0x80;
            temp_r0 = mode;
            if ((s32) temp_r0 != 1) {
                if ((s32) temp_r0 < 1) {

                }
                _renderOffset(arg1);
            } else {
                _renderScale(arg1);
            }
            token = arg1->tokenMark();
        }
    }
}

void glowEffect::_renderOffset(GSgfxLayer *arg1) {
    f32 weights[2]={0.24197073f,0.053990968f};
    u8 alpha,diagonalAlpha;
    u8 sp13;
    s8 sp12;
    s8 sp11;
    s8 sp10;
    f32 temp_f0;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f1;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f5_3;
    f32 temp_f6;
    s32 temp_r0;
    s32 var_r11;
    s32 var_r6;
    s32 var_r7;
    s32 var_r8_2;
    s8 temp_r0_2;
    u8 temp_r31;
    u8 temp_r4;
    u8 temp_r5;
    u8 var_r10;
    u8 var_r11_2;
    u8 var_r30;
    u8 var_r3;
    u8 var_r8;
    GSgfxLayer *temp_r3;
    GSgfxLayer *temp_r6;
    GSgfxLayer *temp_r7;

    sp13 = radius;
    temp_f1 = (f32)(u8)radius;
    temp_f29 = 0.25f * temp_f1;
    arg1->unk199C = GSgfxVFBuildTemp(0,2,0,0,1,5,4,1,4);
    arg1->unkDB8 = 1;
    arg1->unk16BC = (s32) (arg1->unk16BC | 1);
    arg1->unk16A8 = (s32) (arg1->unk16A8 | 4);
    arg1->unk1774 = (s32) (arg1->unk1774 | 1);
    arg1->unk1760 = (s32) (arg1->unk1760 | 4);
    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(arg1,0,1,1,1,0,0,2,0);
    var_r30 = 0;
    arg1->unkC70 = 4;
    arg1->unk16AC = (s32) (arg1->unk16AC | 1);
    arg1->unk16A8 = (s32) (arg1->unk16A8 | 1);
    arg1->unk1764 = (s32) (arg1->unk1764 | 1);
    arg1->unk1760 = (s32) (arg1->unk1760 | 1);
    arg1->unkEAC = 4;
    arg1->unk16CC = (s32) (arg1->unk16CC | 1);
    arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
    arg1->unk1784 = (s32) (arg1->unk1784 | 1);
    arg1->unk1760 = (s32) (arg1->unk1760 | 8);
loop_16:
    if (var_r30 < 4U) {
        temp_r31 = var_r30;
        tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(arg1, var_r30, 1, temp_r31 + 4, 0, 0, 0);
        var_r3 = 0;
        if (((u8) subtract != 0) && (temp_r31 == 3)) {
            var_r3 = 1;
        }
        var_r6 = 0;
        if (var_r3 != 0) {
            var_r6 = 3;
        }
        var_r8 = 0;
        temp_r0 = 1 << temp_r31;
        temp_r3 = (GSgfxLayer*)((u8*)arg1 + (var_r30 * 0x14));
        temp_r3->unk1170 = 0;
        temp_r4 = var_r30 == 3;
        temp_r3->unk1174 = 0;
        temp_r3->unk1178 = var_r6;
        temp_r3->unk117C = temp_r4;
        temp_r3->unk1180 = 0;
        arg1->unk16DC = (s32) (arg1->unk16DC | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk1794 = (s32) (arg1->unk1794 | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        if (((u8) subtract != 0) && (var_r30 == 3)) {
            var_r8 = 1;
        }
        var_r11 = 0;
        if (var_r8 != 0) {
            var_r11 = 3;
        }
        temp_r3->unk12B0 = 0;
        temp_r6 = (GSgfxLayer*)((u8*)arg1 + (var_r30 * 0x10));
        var_r8_2 = 0xF;
        temp_r3->unk12B4 = 0;
        temp_r3->unk12B8 = var_r11;
        temp_r3->unk12BC = temp_r4;
        temp_r3->unk12C0 = 0;
        arg1->unk16E0 = (s32) (arg1->unk16E0 | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk1798 = (s32) (arg1->unk1798 | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        temp_r6->unkF70 = 8;
        temp_r6->unkF74 = 0xF;
        temp_r6->unkF78 = 0xF;
        if (var_r30 != 0) {
            var_r8_2 = 0;
        }
        temp_r6->unkF7C = var_r8_2;
        var_r7 = 7;
        arg1->unk16D4 = (s32) (arg1->unk16D4 | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk178C = (s32) (arg1->unk178C | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        temp_r6->unk1070 = 7;
        temp_r6->unk1074 = 5;
        temp_r6->unk1078 = 4;
        if (var_r30 != 0) {
            var_r7 = 0;
        }
        temp_r6->unk107C = var_r7;
        temp_r7 = (GSgfxLayer*)((u8*)arg1 + (var_r30 * 0xC));
        var_r30 += 1;
        arg1->unk16D8 = (s32) (arg1->unk16D8 | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk1790 = (s32) (arg1->unk1790 | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        temp_r7->unkEB0 = (s32) temp_r31;
        temp_r7->unkEB4 = 0;
        temp_r7->unkEB8 = 4;
        arg1->unk16D0 = (s32) (arg1->unk16D0 | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk1788 = (s32) (arg1->unk1788 | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        goto loop_16;
    }
    temp_r5 = count;
    arg1->beginSurface((u16) (temp_r5 * 4 * (temp_r5 + 1)));
    var_r10 = 0;
loop_22:
    if (var_r10 < (u8) count) {
        temp_r0_2 = var_r10 + 1;
        sp12 = temp_r0_2;
        sp11 = temp_r0_2;
        temp_f0 = 0.0015625f * (temp_f29 * (f32)(u8)sp12);
        temp_f6 = 0.0020833334f * (temp_f29 * (f32)(u8)sp11);
        alpha=glowAlpha(0.25f*(255.0f*(strength*weights[var_r10]))+0.5f);
        temp_f13 = -temp_f0;
        *(volatile s16 *)0xCC008000 = 0;
        temp_f2 = -temp_f6;
        *(volatile s16 *)0xCC008000 = 0;
        temp_f11 = 1.0f - temp_f0;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = temp_f13;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = temp_f2;
        *(volatile f32 *)0xCC008000 = temp_f0;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = temp_f6;
        *(volatile s16 *)0xCC008000 = 0x280;
        *(volatile s16 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = temp_f11;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = temp_f2;
        temp_f12 = 1.0f + temp_f0;
        temp_f2_2 = 1.0f - temp_f6;
        var_r11_2 = 0;
        temp_f5 = 1.0f + temp_f6;
        *(volatile f32 *)0xCC008000 = temp_f12;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = temp_f6;
        *(volatile s16 *)0xCC008000 = 0x280;
        *(volatile s16 *)0xCC008000 = 0x1E0;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = temp_f11;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = temp_f2_2;
        *(volatile f32 *)0xCC008000 = temp_f12;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = temp_f5;
        *(volatile s16 *)0xCC008000 = 0;
        *(volatile s16 *)0xCC008000 = 0x1E0;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = temp_f13;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = temp_f2_2;
        *(volatile f32 *)0xCC008000 = temp_f0;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = temp_f5;
loop_20:
        if (var_r11_2 < (u8) count) {
            diagonalAlpha=glowAlpha(0.25f*(255.0f*((strength*weights[var_r10])*weights[var_r11_2]))+0.5f);
            sp10 = var_r11_2 + 1;
            *(volatile s16 *)0xCC008000 = 0;
            *(volatile s16 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            temp_f5_2 = 0.0020833334f * (temp_f29 * (f32)(u8)sp10);
            *(volatile u8 *)0xCC008000 = 0xFF;
            temp_f2_3 = -temp_f5_2;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = diagonalAlpha;
            *(volatile f32 *)0xCC008000 = temp_f13;
            *(volatile f32 *)0xCC008000 = temp_f2_3;
            *(volatile f32 *)0xCC008000 = temp_f13;
            *(volatile f32 *)0xCC008000 = temp_f5_2;
            *(volatile f32 *)0xCC008000 = temp_f0;
            *(volatile f32 *)0xCC008000 = temp_f2_3;
            *(volatile f32 *)0xCC008000 = temp_f0;
            *(volatile f32 *)0xCC008000 = temp_f5_2;
            *(volatile s16 *)0xCC008000 = 0x280;
            *(volatile s16 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = diagonalAlpha;
            *(volatile f32 *)0xCC008000 = temp_f11;
            *(volatile f32 *)0xCC008000 = temp_f2_3;
            *(volatile f32 *)0xCC008000 = temp_f11;
            *(volatile f32 *)0xCC008000 = temp_f5_2;
            *(volatile f32 *)0xCC008000 = temp_f12;
            *(volatile f32 *)0xCC008000 = temp_f2_3;
            *(volatile f32 *)0xCC008000 = temp_f12;
            *(volatile f32 *)0xCC008000 = temp_f5_2;
            *(volatile s16 *)0xCC008000 = 0x280;
            *(volatile s16 *)0xCC008000 = 0x1E0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0xFF;
            temp_f2_4 = 1.0f - temp_f5_2;
            temp_f5_3 = 1.0f + temp_f5_2;
            var_r11_2 += 1;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = diagonalAlpha;
            *(volatile f32 *)0xCC008000 = temp_f11;
            *(volatile f32 *)0xCC008000 = temp_f2_4;
            *(volatile f32 *)0xCC008000 = temp_f11;
            *(volatile f32 *)0xCC008000 = temp_f5_3;
            *(volatile f32 *)0xCC008000 = temp_f12;
            *(volatile f32 *)0xCC008000 = temp_f2_4;
            *(volatile f32 *)0xCC008000 = temp_f12;
            *(volatile f32 *)0xCC008000 = temp_f5_3;
            *(volatile s16 *)0xCC008000 = 0;
            *(volatile s16 *)0xCC008000 = 0x1E0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = diagonalAlpha;
            *(volatile f32 *)0xCC008000 = temp_f13;
            *(volatile f32 *)0xCC008000 = temp_f2_4;
            *(volatile f32 *)0xCC008000 = temp_f13;
            *(volatile f32 *)0xCC008000 = temp_f5_3;
            *(volatile f32 *)0xCC008000 = temp_f0;
            *(volatile f32 *)0xCC008000 = temp_f2_4;
            *(volatile f32 *)0xCC008000 = temp_f0;
            *(volatile f32 *)0xCC008000 = temp_f5_3;
            goto loop_20;
        }
        var_r10 += 1;
        goto loop_22;
    }
    arg1->endSurface();
}

void glowEffect::_renderScale(GSgfxLayer *arg1) {
    f32 weights[4]={0.17603268f,0.12098537f,0.0647588f,0.026995484f};
    u8 alpha;
    u8 sp12;
    s8 sp11;
    s8 sp10;
    f32 temp_f10;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f5;
    f32 temp_f8;
    f32 temp_f9;
    f32 temp_f9_2;
    s32 temp_r0;
    s32 var_r11;
    s32 var_r6;
    s32 var_r7;
    s32 var_r8_2;
    s8 temp_r0_2;
    u8 temp_r31;
    u8 temp_r4;
    u8 var_r30;
    u8 var_r3;
    u8 var_r8;
    u8 var_r9;
    GSgfxLayer *temp_r3;
    GSgfxLayer *temp_r6;
    GSgfxLayer *temp_r7;

    sp12 = radius;
    temp_f1 = (f32)(u8)radius;
    temp_f31 = 0.25f * temp_f1;
    arg1->unk199C = GSgfxVFBuildTemp(0,2,0,0,1,5,2,1,4);
    arg1->unkDB8 = 1;
    arg1->unk16BC = (s32) (arg1->unk16BC | 1);
    arg1->unk16A8 = (s32) (arg1->unk16A8 | 4);
    arg1->unk1774 = (s32) (arg1->unk1774 | 1);
    arg1->unk1760 = (s32) (arg1->unk1760 | 4);
    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(arg1,0,1,1,1,0,0,2,0);
    var_r30 = 0;
    arg1->unkC70 = 2;
    arg1->unk16AC = (s32) (arg1->unk16AC | 1);
    arg1->unk16A8 = (s32) (arg1->unk16A8 | 1);
    arg1->unk1764 = (s32) (arg1->unk1764 | 1);
    arg1->unk1760 = (s32) (arg1->unk1760 | 1);
    arg1->unkEAC = 2;
    arg1->unk16CC = (s32) (arg1->unk16CC | 1);
    arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
    arg1->unk1784 = (s32) (arg1->unk1784 | 1);
    arg1->unk1760 = (s32) (arg1->unk1760 | 8);
loop_16:
    if (var_r30 < 2U) {
        temp_r31 = var_r30;
        tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(arg1, var_r30, 1, temp_r31 + 4, 0, 0, 0);
        var_r3 = 0;
        if (((u8) subtract != 0) && (temp_r31 == 1)) {
            var_r3 = 1;
        }
        var_r6 = 0;
        if (var_r3 != 0) {
            var_r6 = 3;
        }
        var_r8 = 0;
        temp_r0 = 1 << temp_r31;
        temp_r3 = (GSgfxLayer*)((u8*)arg1 + (var_r30 * 0x14));
        temp_r3->unk1170 = 0;
        temp_r4 = var_r30 == 1;
        temp_r3->unk1174 = 0;
        temp_r3->unk1178 = var_r6;
        temp_r3->unk117C = temp_r4;
        temp_r3->unk1180 = 0;
        arg1->unk16DC = (s32) (arg1->unk16DC | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk1794 = (s32) (arg1->unk1794 | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        if (((u8) subtract != 0) && (var_r30 == 1)) {
            var_r8 = 1;
        }
        var_r11 = 0;
        if (var_r8 != 0) {
            var_r11 = 3;
        }
        temp_r3->unk12B0 = 0;
        temp_r6 = (GSgfxLayer*)((u8*)arg1 + (var_r30 * 0x10));
        var_r8_2 = 0xF;
        temp_r3->unk12B4 = 0;
        temp_r3->unk12B8 = var_r11;
        temp_r3->unk12BC = temp_r4;
        temp_r3->unk12C0 = 0;
        arg1->unk16E0 = (s32) (arg1->unk16E0 | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk1798 = (s32) (arg1->unk1798 | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        temp_r6->unkF70 = 8;
        temp_r6->unkF74 = 0xF;
        temp_r6->unkF78 = 0xF;
        if (var_r30 != 0) {
            var_r8_2 = 0;
        }
        temp_r6->unkF7C = var_r8_2;
        var_r7 = 7;
        arg1->unk16D4 = (s32) (arg1->unk16D4 | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk178C = (s32) (arg1->unk178C | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        temp_r6->unk1070 = 7;
        temp_r6->unk1074 = 5;
        temp_r6->unk1078 = 4;
        if (var_r30 != 0) {
            var_r7 = 0;
        }
        temp_r6->unk107C = var_r7;
        temp_r7 = (GSgfxLayer*)((u8*)arg1 + (var_r30 * 0xC));
        var_r30 += 1;
        arg1->unk16D8 = (s32) (arg1->unk16D8 | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk1790 = (s32) (arg1->unk1790 | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        temp_r7->unkEB0 = (s32) temp_r31;
        temp_r7->unkEB4 = 0;
        temp_r7->unkEB8 = 4;
        arg1->unk16D0 = (s32) (arg1->unk16D0 | temp_r0);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 8);
        arg1->unk1788 = (s32) (arg1->unk1788 | temp_r0);
        arg1->unk1760 = (s32) (arg1->unk1760 | 8);
        goto loop_16;
    }
    arg1->beginSurface((count * 8) & 0xFFF8);
    var_r9 = 0;
loop_19:
    if ((s32) var_r9 < (s32) (count * 2)) {
        temp_r0_2 = var_r9 + 1;
        sp11 = temp_r0_2;
        sp10 = temp_r0_2;
        temp_f10 = 0.0015625f * (temp_f31 * (f32)(u8)sp11);
        temp_f9 = 0.0020833334f * (temp_f31 * (f32)(u8)sp10);
        alpha=glowAlpha(255.0f*(strength*weights[var_r9])+0.5f);
        temp_f8 = -temp_f10;
        *(volatile s16 *)0xCC008000 = 0;
        temp_f2 = -temp_f9;
        *(volatile s16 *)0xCC008000 = 0;
        temp_f3 = 1.0f + temp_f10;
        *(volatile u8 *)0xCC008000 = 0xFF;
        temp_f5 = 1.0f - temp_f10;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = temp_f8;
        *(volatile f32 *)0xCC008000 = temp_f2;
        *(volatile f32 *)0xCC008000 = temp_f10;
        *(volatile f32 *)0xCC008000 = temp_f9;
        *(volatile s16 *)0xCC008000 = 0x280;
        *(volatile s16 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = temp_f3;
        *(volatile f32 *)0xCC008000 = temp_f2;
        *(volatile f32 *)0xCC008000 = temp_f5;
        *(volatile f32 *)0xCC008000 = temp_f9;
        *(volatile s16 *)0xCC008000 = 0x280;
        *(volatile s16 *)0xCC008000 = 0x1E0;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        temp_f2_2 = 1.0f + temp_f9;
        temp_f9_2 = 1.0f - temp_f9;
        var_r9 += 1;
        *(volatile f32 *)0xCC008000 = temp_f3;
        *(volatile f32 *)0xCC008000 = temp_f2_2;
        *(volatile f32 *)0xCC008000 = temp_f5;
        *(volatile f32 *)0xCC008000 = temp_f9_2;
        *(volatile s16 *)0xCC008000 = 0;
        *(volatile s16 *)0xCC008000 = 0x1E0;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = temp_f8;
        *(volatile f32 *)0xCC008000 = temp_f2_2;
        *(volatile f32 *)0xCC008000 = temp_f10;
        *(volatile f32 *)0xCC008000 = temp_f9_2;
        goto loop_19;
    }
    arg1->endSurface();
}

