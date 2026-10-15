#include <game/pxdvs/GSAPI/GSparticle/particleEnginePrivate.hpp>
extern "C" {
u32 g_particle_debug_stats[9];
Vec g_CameraPosition,g_CameraLookDir,g_CameraUpDir,g_CameraSideDir;
GSgfxVF g_vertex_format,g_ext_vertex_format;
EngineBank* g_particleBanks;
u32 g_Camera;
MtxPtr g_CameraMatrix;
GSgfxLayer* g_current_layer;
s32 g_render_pass;
static s8 g_afterZWriteState;
static inline void bindParticleTexture(GSgfxLayer* layer,u32 unit,GStexture* texture) {
    GSgfxLayer* selected;
    u32 bit;
    u32 offset=(unit*4)&0x3fc;
    GSgfxLayer* sub=(GSgfxLayer*)((u8*)layer+offset);
    if(sub->textures[0]!=texture || sub->cachedTextures[0]!=texture || texture->dirty) {
        selected=(GSgfxLayer*)((u8*)layer+offset);
        selected->textures[0]=texture;
        bit=1<<(u8)unit;
        layer->unk173C|=bit;
        selected->cachedTextures[0]=texture;
        layer->unk17F4|=bit;
    }
}
void particleEngineSetupTexture(u32 unit,GStexture* texture,s32 wrapS,s32 wrapT,s32 minFilter,s32 magFilter) {
    GStextureSetWrap(texture,wrapS,wrapT);
    GStextureSetFilter(texture,minFilter,magFilter,0);
    bindParticleTexture(g_current_layer,unit,texture);
}
void particleEngineSetDefaultRenderState(u8 force) {
    { GSgfxLayer* layer=g_current_layer;
    layer->unk1656 = 1;
    layer->unk1657 = 1;
    layer->unk1658 = 0;
    layer->unk170C = (s32) (layer->unk170C | 4);
    layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
    layer->unk17C4 = (s32) (layer->unk17C4 | 4);
    layer->unk1760 = (s32) (layer->unk1760 | 0x40);
    }
    { GSgfxLayer* layer=g_current_layer;
    layer->unk165C = 1;
    layer->unk1660 = 1;
    layer->unk170C = (s32) (layer->unk170C | 8);
    layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
    layer->unk17C4 = (s32) (layer->unk17C4 | 8);
    layer->unk1760 = (s32) (layer->unk1760 | 0x40);
    }
    { GSgfxLayer* layer=g_current_layer;
    layer->unk1664 = 7;
    layer->unk1670 = 0;
    layer->unk1668 = 0;
    layer->unk166C = 7;
    layer->unk1671 = 0;
    layer->unk1672 = 1;
    layer->unk170C = (s32) (layer->unk170C | 0x10);
    layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
    layer->unk17C4 = (s32) (layer->unk17C4 | 0x10);
    layer->unk1760 = (s32) (layer->unk1760 | 0x40);
    }
    { GSgfxLayer* layer=g_current_layer;
    layer->unk1654 = 0;
    layer->unk1655 = 0xFF;
    layer->unk170C = (s32) (layer->unk170C | 2);
    layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
    layer->unk17C4 = (s32) (layer->unk17C4 | 2);
    layer->unk1760 = (s32) (layer->unk1760 | 0x40);
    }
    { GSgfxLayer* layer=g_current_layer;
    layer->unk1674 = 1;
    layer->unk170C = (s32) (layer->unk170C | 0x20);
    layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
    layer->unk17C4 = (s32) (layer->unk17C4 | 0x20);
    layer->unk1760 = (s32) (layer->unk1760 | 0x40);
    }
    { GSgfxLayer* layer=g_current_layer;
    layer->unkD8C = 2;
    layer->unk16B8 = (s32) (layer->unk16B8 | 2);
    layer->unk16A8 = (s32) (layer->unk16A8 | 2);
    layer->unk1770 = (s32) (layer->unk1770 | 2);
    layer->unk1760 = (s32) (layer->unk1760 | 2);
    }
    { GSgfxLayer* layer=g_current_layer;
    layer->unkD90 = 0;
    layer->unk16B8 = (s32) (layer->unk16B8 | 4);
    layer->unk16A8 = (s32) (layer->unk16A8 | 2);
    layer->unk1770 = (s32) (layer->unk1770 | 4);
    layer->unk1760 = (s32) (layer->unk1760 | 2);
    }
    { GSgfxLayer* layer=g_current_layer;
    layer->unkD88 = 0;
    layer->unk16B8 = (s32) (layer->unk16B8 | 8);
    layer->unk16A8 = (s32) (layer->unk16A8 | 2);
    layer->unk1770 = (s32) (layer->unk1770 | 8);
    layer->unk1760 = (s32) (layer->unk1760 | 2);
    }
    particleEngineSetupTevStages(force,0,0);
    g_afterZWriteState = 0;
}


void particleEngineSetupBlendMode(u32 arg0) {
    switch (arg0) {
    case 1: { GSgfxLayer* layer=g_current_layer;
        if ((s32) layer->unk1994 != 1) {
            layer->unk1994 = 1;
            layer->unk1990 = layer->shaders[layer->unk1994];
        }
        layer->unk1644 = 3;
        layer->unk1648 = 4;
        layer->unk164C = 1;
        layer->unk1650 = 5;
        layer->unk170C = (s32) (layer->unk170C | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
        layer->unk17C4 = (s32) (layer->unk17C4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x40);
        return;
    }
    case 2: { GSgfxLayer* layer=g_current_layer;
        if ((s32) layer->unk1994 != 1) {
            layer->unk1994 = 1;
            layer->unk1990 = layer->shaders[layer->unk1994];
        }
        layer->unk1644 = 1;
        layer->unk1648 = 4;
        layer->unk164C = 5;
        layer->unk1650 = 5;
        layer->unk170C = (s32) (layer->unk170C | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
        layer->unk17C4 = (s32) (layer->unk17C4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x40);
        return;
    }
    case 3: { GSgfxLayer* layer=g_current_layer;
        if ((s32) layer->unk1994 != 1) {
            layer->unk1994 = 1;
            layer->unk1990 = layer->shaders[layer->unk1994];
        }
        layer->unk1644 = 1;
        layer->unk1648 = 1;
        layer->unk164C = 0;
        layer->unk1650 = 5;
        layer->unk170C = (s32) (layer->unk170C | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
        layer->unk17C4 = (s32) (layer->unk17C4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x40);
        return;
    }
    case 4: { GSgfxLayer* layer=g_current_layer;
        if ((s32) layer->unk1994 != 1) {
            layer->unk1994 = 1;
            layer->unk1990 = layer->shaders[layer->unk1994];
        }
        layer->unk1644 = 2;
        layer->unk1648 = 1;
        layer->unk164C = 1;
        layer->unk1650 = 4;
        layer->unk170C = (s32) (layer->unk170C | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
        layer->unk17C4 = (s32) (layer->unk17C4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x40);
        return;
    }
    case 5: { GSgfxLayer* layer=g_current_layer;
        if ((s32) layer->unk1994 != 1) {
            layer->unk1994 = 1;
            layer->unk1990 = layer->shaders[layer->unk1994];
        }
        layer->unk1644 = 2;
        layer->unk1648 = 1;
        layer->unk164C = 1;
        layer->unk1650 = 7;
        layer->unk170C = (s32) (layer->unk170C | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
        layer->unk17C4 = (s32) (layer->unk17C4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x40);
        return;
    }
    case 6: { GSgfxLayer* layer=g_current_layer;
        if ((s32) layer->unk1994 != 1) {
            layer->unk1994 = 1;
            layer->unk1990 = layer->shaders[layer->unk1994];
        }
        layer->unk1644 = 2;
        layer->unk1648 = 1;
        layer->unk164C = 1;
        layer->unk1650 = 1;
        layer->unk170C = (s32) (layer->unk170C | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
        layer->unk17C4 = (s32) (layer->unk17C4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x40);
        return;
    }
    case 7: { GSgfxLayer* layer=g_current_layer;
        if ((s32) layer->unk1994 != 1) {
            layer->unk1994 = 1;
            layer->unk1990 = layer->shaders[layer->unk1994];
        }
        layer->unk1644 = 2;
        layer->unk1648 = 1;
        layer->unk164C = 1;
        layer->unk1650 = 6;
        layer->unk170C = (s32) (layer->unk170C | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
        layer->unk17C4 = (s32) (layer->unk17C4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x40);
        return;
    }
    default: { GSgfxLayer* layer=g_current_layer;
        if ((s32) layer->unk1994 != 1) {
            layer->unk1994 = 1;
            layer->unk1990 = layer->shaders[layer->unk1994];
        }
        layer->unk1644 = 1;
        layer->unk1648 = 4;
        layer->unk164C = 1;
        layer->unk1650 = 5;
        layer->unk170C = (s32) (layer->unk170C | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x40);
        layer->unk17C4 = (s32) (layer->unk17C4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x40);
        return;
    }
    }
}

void particleEngineSetupTevStages(u8 arg0, u8 arg1, u8 arg2) {
    s32 sp8;

    static u8 extensionSetup=0;
    static u8 blendedTexturesSetup=0;
    if ((arg0 != 0) || ((u8) extensionSetup != arg1) || ((u8) blendedTexturesSetup != arg2)) {
        extensionSetup = arg1;
        blendedTexturesSetup = arg2;
        { GSgfxLayer* layer=g_current_layer;
        layer->unkC70 = 1;
        layer->unk16AC = (s32) (layer->unk16AC | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 1);
        layer->unk1764 = (s32) (layer->unk1764 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 1);
        }
        tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(g_current_layer, 0, 1, 4, 0, 0, 0);
        { GSgfxLayer* layer=g_current_layer;
        layer->unk14B0 = 0;
        layer->unk16EC = (s32) (layer->unk16EC | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 0x80);
        layer->unk17A4 = (s32) (layer->unk17A4 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 0x80);
        }
        { GSgfxLayer* layer=g_current_layer;
        layer->unk1420 = 0;
        layer->unk16E8 = (s32) (layer->unk16E8 | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 8);
        layer->unk17A0 = (s32) (layer->unk17A0 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 8);
        }
        { GSgfxLayer* layer=g_current_layer;
        layer->unkDB8 = 1;
        layer->unk16BC = (s32) (layer->unk16BC | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 4);
        layer->unk1774 = (s32) (layer->unk1774 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 4);
        }
        sp8 = 0;
        cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(g_current_layer, 0, 2, 1, 1, 0, 0, 2,0);
        if (arg2 != 0) {
            { GSgfxLayer* layer=g_current_layer;
            layer->unkEAC = 3;
            layer->unk16CC = (s32) (layer->unk16CC | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1784 = (s32) (layer->unk1784 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1584 = 0;
            layer->unk1588 = 0;
            layer->unk1704 = (s32) (layer->unk1704 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 0x20);
            layer->unk17BC = (s32) (layer->unk17BC | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 0x20);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkEB0 = 0;
            layer->unkEB4 = 0;
            layer->unkEB8 = 4;
            layer->unk16D0 = (s32) (layer->unk16D0 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1788 = (s32) (layer->unk1788 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1170 = 0;
            layer->unk1174 = 0;
            layer->unk1178 = 0;
            layer->unk117C = 0;
            layer->unk1180 = 1;
            layer->unk16DC = (s32) (layer->unk16DC | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1794 = (s32) (layer->unk1794 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk12B0 = 0;
            layer->unk12B4 = 0;
            layer->unk12B8 = 0;
            layer->unk12BC = 0;
            layer->unk12C0 = 1;
            layer->unk16E0 = (s32) (layer->unk16E0 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1798 = (s32) (layer->unk1798 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkF70 = 0xF;
            layer->unkF74 = 0xA;
            layer->unkF78 = 8;
            layer->unkF7C = 0xF;
            layer->unk16D4 = (s32) (layer->unk16D4 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk178C = (s32) (layer->unk178C | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1070 = 7;
            layer->unk1074 = 5;
            layer->unk1078 = 4;
            layer->unk107C = 7;
            layer->unk16D8 = (s32) (layer->unk16D8 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1790 = (s32) (layer->unk1790 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk158C = 0;
            layer->unk1590 = 0;
            layer->unk1704 = (s32) (layer->unk1704 | 2);
            layer->unk16A8 = (s32) (layer->unk16A8 | 0x20);
            layer->unk17BC = (s32) (layer->unk17BC | 2);
            layer->unk1760 = (s32) (layer->unk1760 | 0x20);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkEBC = 0;
            layer->unkEC0 = 1;
            layer->unkEC4 = 4;
            layer->unk16D0 = (s32) (layer->unk16D0 | 2);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1788 = (s32) (layer->unk1788 | 2);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1184 = 0;
            layer->unk1188 = 0;
            layer->unk118C = 0;
            layer->unk1190 = 0;
            layer->unk1194 = 2;
            layer->unk16DC = (s32) (layer->unk16DC | 2);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1794 = (s32) (layer->unk1794 | 2);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk12C4 = 0;
            layer->unk12C8 = 0;
            layer->unk12CC = 0;
            layer->unk12D0 = 0;
            layer->unk12D4 = 2;
            layer->unk16E0 = (s32) (layer->unk16E0 | 2);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1798 = (s32) (layer->unk1798 | 2);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkF80 = 0xF;
            layer->unkF84 = 0xA;
            layer->unkF88 = 8;
            layer->unkF8C = 0xF;
            layer->unk16D4 = (s32) (layer->unk16D4 | 2);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk178C = (s32) (layer->unk178C | 2);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1080 = 7;
            layer->unk1084 = 5;
            layer->unk1088 = 4;
            layer->unk108C = 7;
            layer->unk16D8 = (s32) (layer->unk16D8 | 2);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1790 = (s32) (layer->unk1790 | 2);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1594 = 0;
            layer->unk1598 = 0;
            layer->unk1704 = (s32) (layer->unk1704 | 4);
            layer->unk16A8 = (s32) (layer->unk16A8 | 0x20);
            layer->unk17BC = (s32) (layer->unk17BC | 4);
            layer->unk1760 = (s32) (layer->unk1760 | 0x20);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkEC8 = 0xFF;
            layer->unkECC = 0xFF;
            layer->unkED0 = 0xFF;
            layer->unk16D0 = (s32) (layer->unk16D0 | 4);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1788 = (s32) (layer->unk1788 | 4);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1198 = 0;
            layer->unk119C = 0;
            layer->unk11A0 = 0;
            layer->unk11A4 = 1;
            layer->unk11A8 = 0;
            layer->unk16DC = (s32) (layer->unk16DC | 4);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1794 = (s32) (layer->unk1794 | 4);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk12D8 = 0;
            layer->unk12DC = 0;
            layer->unk12E0 = 0;
            layer->unk12E4 = 1;
            layer->unk12E8 = 0;
            layer->unk16E0 = (s32) (layer->unk16E0 | 4);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1798 = (s32) (layer->unk1798 | 4);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk150C = 0xC;
            layer->unk16FC = (s32) (layer->unk16FC | 4);
            layer->unk16A8 = (s32) (layer->unk16A8 | 0x10);
            layer->unk17B4 = (s32) (layer->unk17B4 | 4);
            layer->unk1760 = (s32) (layer->unk1760 | 0x10);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk154C = 0x1C;
            layer->unk1700 = (s32) (layer->unk1700 | 4);
            layer->unk16A8 = (s32) (layer->unk16A8 | 0x10);
            layer->unk17B8 = (s32) (layer->unk17B8 | 4);
            layer->unk1760 = (s32) (layer->unk1760 | 0x10);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkF90 = 2;
            layer->unkF94 = 4;
            layer->unkF98 = 0xE;
            layer->unkF9C = 0xF;
            layer->unk16D4 = (s32) (layer->unk16D4 | 4);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk178C = (s32) (layer->unk178C | 4);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1090 = 1;
            layer->unk1094 = 2;
            layer->unk1098 = 6;
            layer->unk109C = 7;
            layer->unk16D8 = (s32) (layer->unk16D8 | 4);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1790 = (s32) (layer->unk1790 | 4);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            if (arg1 != 0) {
                { GSgfxLayer* layer=g_current_layer;
                layer->unk1504 = 0xD;
                layer->unk16FC = (s32) (layer->unk16FC | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 0x10);
                layer->unk17B4 = (s32) (layer->unk17B4 | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 0x10);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unkF70 = 0xE;
                layer->unkF74 = 0xA;
                layer->unkF78 = 8;
                layer->unkF7C = 0xF;
                layer->unk16D4 = (s32) (layer->unk16D4 | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk178C = (s32) (layer->unk178C | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk1508 = 0xD;
                layer->unk16FC = (s32) (layer->unk16FC | 2);
                layer->unk16A8 = (s32) (layer->unk16A8 | 0x10);
                layer->unk17B4 = (s32) (layer->unk17B4 | 2);
                layer->unk1760 = (s32) (layer->unk1760 | 0x10);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unkF80 = 0xE;
                layer->unkF84 = 0xA;
                layer->unkF88 = 8;
                layer->unkF8C = 0xF;
                layer->unk16D4 = (s32) (layer->unk16D4 | 2);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk178C = (s32) (layer->unk178C | 2);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
            }
        } else {
            if (arg1 != 0) {
                { GSgfxLayer* layer=g_current_layer;
                layer->unkDB8 = 2;
                layer->unk16BC = (s32) (layer->unk16BC | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 4);
                layer->unk1774 = (s32) (layer->unk1774 | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 4);
                }
                sp8 = 0;
                cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(g_current_layer, 1, 2, 1, 1, 0, 0, 2,0);
                { GSgfxLayer* layer=g_current_layer;
                layer->unkEAC = 2;
                layer->unk16CC = (s32) (layer->unk16CC | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1784 = (s32) (layer->unk1784 | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk1070 = 7;
                layer->unk1074 = 7;
                layer->unk1078 = 7;
                layer->unk107C = 7;
                layer->unk16D8 = (s32) (layer->unk16D8 | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1790 = (s32) (layer->unk1790 | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk1584 = 0;
                layer->unk1588 = 0;
                layer->unk1704 = (s32) (layer->unk1704 | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 0x20);
                layer->unk17BC = (s32) (layer->unk17BC | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 0x20);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unkEB0 = 0;
                layer->unkEB4 = 0;
                layer->unkEB8 = 4;
                layer->unk16D0 = (s32) (layer->unk16D0 | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1788 = (s32) (layer->unk1788 | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk1170 = 0;
                layer->unk1174 = 0;
                layer->unk1178 = 0;
                layer->unk117C = 0;
                layer->unk1180 = 1;
                layer->unk16DC = (s32) (layer->unk16DC | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1794 = (s32) (layer->unk1794 | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk12B0 = 0;
                layer->unk12B4 = 0;
                layer->unk12B8 = 0;
                layer->unk12BC = 0;
                layer->unk12C0 = 1;
                layer->unk16E0 = (s32) (layer->unk16E0 | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1798 = (s32) (layer->unk1798 | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unkF70 = 0xF;
                layer->unkF74 = 0xA;
                layer->unkF78 = 8;
                layer->unkF7C = 0xF;
                layer->unk16D4 = (s32) (layer->unk16D4 | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk178C = (s32) (layer->unk178C | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk1070 = 7;
                layer->unk1074 = 5;
                layer->unk1078 = 4;
                layer->unk107C = 7;
                layer->unk16D8 = (s32) (layer->unk16D8 | 1);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1790 = (s32) (layer->unk1790 | 1);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk158C = 0;
                layer->unk1590 = 0;
                layer->unk1704 = (s32) (layer->unk1704 | 2);
                layer->unk16A8 = (s32) (layer->unk16A8 | 0x20);
                layer->unk17BC = (s32) (layer->unk17BC | 2);
                layer->unk1760 = (s32) (layer->unk1760 | 0x20);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unkEBC = 0;
                layer->unkEC0 = 0;
                layer->unkEC4 = 5;
                layer->unk16D0 = (s32) (layer->unk16D0 | 2);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1788 = (s32) (layer->unk1788 | 2);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk1184 = 0;
                layer->unk1188 = 0;
                layer->unk118C = 0;
                layer->unk1190 = 1;
                layer->unk1194 = 0;
                layer->unk16DC = (s32) (layer->unk16DC | 2);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1794 = (s32) (layer->unk1794 | 2);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk12C4 = 0;
                layer->unk12C8 = 0;
                layer->unk12CC = 0;
                layer->unk12D0 = 1;
                layer->unk12D4 = 0;
                layer->unk16E0 = (s32) (layer->unk16E0 | 2);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1798 = (s32) (layer->unk1798 | 2);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unkF80 = 0xA;
                layer->unkF84 = 0xF;
                layer->unkF88 = 8;
                layer->unkF8C = 2;
                layer->unk16D4 = (s32) (layer->unk16D4 | 2);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk178C = (s32) (layer->unk178C | 2);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                { GSgfxLayer* layer=g_current_layer;
                layer->unk1080 = 7;
                layer->unk1084 = 5;
                layer->unk1088 = 4;
                layer->unk108C = 7;
                layer->unk16D8 = (s32) (layer->unk16D8 | 2);
                layer->unk16A8 = (s32) (layer->unk16A8 | 8);
                layer->unk1790 = (s32) (layer->unk1790 | 2);
                layer->unk1760 = (s32) (layer->unk1760 | 8);
                }
                return;
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkEAC = 1;
            layer->unk16CC = (s32) (layer->unk16CC | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1784 = (s32) (layer->unk1784 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1584 = 0;
            layer->unk1588 = 0;
            layer->unk1704 = (s32) (layer->unk1704 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 0x20);
            layer->unk17BC = (s32) (layer->unk17BC | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 0x20);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkEB0 = 0;
            layer->unkEB4 = 0;
            layer->unkEB8 = 4;
            layer->unk16D0 = (s32) (layer->unk16D0 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1788 = (s32) (layer->unk1788 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1170 = 0;
            layer->unk1174 = 0;
            layer->unk1178 = 0;
            layer->unk117C = 1;
            layer->unk1180 = 0;
            layer->unk16DC = (s32) (layer->unk16DC | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1794 = (s32) (layer->unk1794 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk12B0 = 0;
            layer->unk12B4 = 0;
            layer->unk12B8 = 0;
            layer->unk12BC = 1;
            layer->unk12C0 = 0;
            layer->unk16E0 = (s32) (layer->unk16E0 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1798 = (s32) (layer->unk1798 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unkF70 = 0xF;
            layer->unkF74 = 0xA;
            layer->unkF78 = 8;
            layer->unkF7C = 0xF;
            layer->unk16D4 = (s32) (layer->unk16D4 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk178C = (s32) (layer->unk178C | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
            { GSgfxLayer* layer=g_current_layer;
            layer->unk1070 = 7;
            layer->unk1074 = 5;
            layer->unk1078 = 4;
            layer->unk107C = 7;
            layer->unk16D8 = (s32) (layer->unk16D8 | 1);
            layer->unk16A8 = (s32) (layer->unk16A8 | 8);
            layer->unk1790 = (s32) (layer->unk1790 | 1);
            layer->unk1760 = (s32) (layer->unk1760 | 8);
            }
        }
    }
}


void particleEngineRender(GSgfxLayer* layer) {
    EngineBank* bank=g_particleBanks;
    if(g_particleBanks) {
        g_current_layer=layer;g_Camera=0;g_render_pass=layer->unk1994;
        particleEngineSetDefaultRenderState(1);
        while(bank){peBankRender(bank);bank=bank->next;}
        if(g_Camera && g_Camera!=GScameraGetActiveCamera())GScameraLoadActiveCameraMatrix(layer->unk28);
    }
}
u8 particleEnginePrepareRender(u32 camera) {
    if(!GScameraIsValid(camera)) {camera=GScameraGetActiveCamera();if(!camera){g_CameraMatrix=0;return 0;}}
    if(g_Camera==camera)return 1;
    g_Camera=camera;g_CameraMatrix=GScameraGetMatrixPtr(camera);
    if(g_current_layer)GScameraLoadCameraMatrix(camera,g_current_layer->unk28);else GScameraLoadCameraMatrix(camera,-1);
    return 1;
}
void particleEnginePostUpdate() {
    EngineBank* bank=g_particleBanks;
    while(bank){if(bank)bank->rendered=0;bank=bank->next;}
    g_Camera=0;
}
void particleEngineUpdate(f32 time) {
    g_Camera=0;
    EngineBank* bank=g_particleBanks;
    while(bank){peBankUpdate(bank,time);bank=bank->next;}
}
u8 particleEnginePrepareUpdate(u32 camera) {
    Vec side;
    struct Matrix {Mtx values;};
    Matrix basis,copy,transpose;
    if(!GScameraIsValid(camera)){camera=GScameraGetActiveCamera();if(!camera){g_CameraMatrix=0;return 0;}}
    if(g_Camera==camera)return 1;
    g_Camera=camera;g_CameraMatrix=GScameraGetMatrixPtr(camera);
    GScameraLoadCameraMatrix(camera,-1);GSgfxProjectSetupCameraParameters(camera);
    GScameraGetPosition(camera,&g_CameraPosition);
    PSMTXTranspose(g_CameraMatrix,transpose.values);copy=transpose;PSMTXCopy(copy.values,basis.values);
    struct CameraAxis:Vec {CameraAxis(f32 a,f32 b,f32 c){x=a;y=b;z=c;}};
    g_CameraSideDir=CameraAxis(basis.values[0][0],basis.values[1][0],basis.values[2][0]);
    g_CameraUpDir=CameraAxis(basis.values[0][1],basis.values[1][1],basis.values[2][1]);
    PSVECNormalize(&g_CameraUpDir,&g_CameraUpDir);PSVECNormalize(&g_CameraSideDir,&g_CameraSideDir);
    g_CameraSideDir.x=-g_CameraSideDir.x;g_CameraSideDir.y=-g_CameraSideDir.y;g_CameraSideDir.z=-g_CameraSideDir.z;
    PSVECCrossProduct(&g_CameraSideDir,&g_CameraUpDir,&side);
    g_CameraLookDir=side;
    return 1;
}
void particleEngineInit(void) {
    GSgfxVFInit(&g_ext_vertex_format);
    GSgfxVFCreate(&g_ext_vertex_format);
    GSgfxVFSetElement(&g_ext_vertex_format, 9, 1, 4, 0);
    GSgfxVFSetElement(&g_ext_vertex_format, 0xB, 1, 5, 0);
    GSgfxVFSetElement(&g_ext_vertex_format, 0xC, 1, 5, 0);
    GSgfxVFSetElement(&g_ext_vertex_format, 0xD, 1, 4, 0);
    GSgfxVFSetArray(&g_ext_vertex_format, 9, 3, 0, 0, -1);
    GSgfxVFSetArray(&g_ext_vertex_format, 0xB, 3, 0, 0, -1);
    GSgfxVFSetArray(&g_ext_vertex_format, 0xC, 3, 0, 0, -1);
    GSgfxVFSetArray(&g_ext_vertex_format, 0xD, 3, 0, 0, -1);
    GSgfxVFInit(&g_vertex_format);
    GSgfxVFCreate(&g_vertex_format);
    GSgfxVFSetElement(&g_vertex_format, 9, 1, 4, 0);
    GSgfxVFSetElement(&g_vertex_format, 0xB, 1, 5, 0);
    GSgfxVFSetElement(&g_vertex_format, 0xD, 1, 4, 0);
    GSgfxVFSetArray(&g_vertex_format, 9, 3, 0, 0, -1);
    GSgfxVFSetArray(&g_vertex_format, 0xB, 3, 0, 0, -1);
    GSgfxVFSetArray(&g_vertex_format, 0xD, 3, 0, 0, -1);
    memset(&g_particle_debug_stats, 0, 0x24);
}

}
