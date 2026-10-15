#ifndef GAME_PXDVS_GSAPI_GSGFXM_LAYER_STATE_PRIVATE_HPP
#define GAME_PXDVS_GSAPI_GSGFXM_LAYER_STATE_PRIVATE_HPP
union LayerBlendRegister {
    u32 value;
    struct { u32 address:8, reserved:11, operation:1, subtract:1, source:3, destination:3, alpha:1, color:1, dither:1, logic:1, blend:1; } fields;
};
struct LayerStateBlendRegisters { u8 reserved[0x38]; LayerBlendRegister blend; };
ABI_OFF(LayerStateBlendRegisters, blend, 0x38);
#define LAYER_BLEND_STATE reinterpret_cast<LayerStateBlendRegisters *>(gsgfxState)
struct LayerAmbDirtyRow { u8 reserved[0x4B8]; u8 dirty; };
struct LayerMatDirtyRow { u8 reserved[0x4C2]; u8 dirty; };
#endif
