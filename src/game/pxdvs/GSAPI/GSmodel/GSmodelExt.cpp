#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>

extern "C" void GSmodelResetTextureChange(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialResetTexture(material);
}
extern "C" void GSmodelResetPEdescr(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialResetPEdescr(material);
}
extern "C" void GSmodelResetMaterialAlpha(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialResetAlpha(material);
}
extern "C" void GSmodelInitMaterialAlpha(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) GSmaterialStoreAlpha(material);
}
extern "C" void GSmodelResetRenderFlags(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialResetFlags(material);
}
extern "C" void GSmodelSetTextureChange(GSmodel* model, GStexture* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetTexture(material, value); }
}
extern "C" void GSmodelSetModulationColor(GSmodel* model, GXColor* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetModulate(material, value); }
}
extern "C" void GSmodelEnableModulation(GSmodel* model, GXColor* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetModulate(material, value); GSmaterialEnableExtension(material, 1); }
}
extern "C" void GSmodelEnableColorSwap(GSmodel* model, u8* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetColorChannels(material, value); GSmaterialEnableExtension(material, 2); }
}
extern "C" void GSmodelSetPEdescr(GSmodel* model, void* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetPEdescr(material, value); }
}
extern "C" void GSmodelSetRenderFlags(GSmodel* model, u32 value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetFlags(material, value | GSmaterialGetFlags(material)); }
}
extern "C" void GSmodelDisableModulation(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialDisableExtension(material, 1);
}
extern "C" void GSmodelDisableColorSwap(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialDisableExtension(material, 2);
}
extern "C" u8 GSmodelIsModulationEnabled(GSmodel* model) {
    if (!model->materialCount) return 0;
    GSmaterial* material = model->materials;
    if (!material) return 0;
    if (GSmaterialGetEnabledExtensions(material) & 1) return 1;
    return 0;
}
extern "C" u8 GSmodelIsEnvMapEnabled(GSmodel* model) {
    if (!model->materialCount) return 0;
    GSmaterial* material = model->materials;
    if (!material) return 0;
    if (GSmaterialGetEnabledExtensions(material) & 4) return 1;
    return 0;
}
extern "C" void GSmodelGetModulationColor(GSmodel* model, GXColor* color) {
    if (GSmodelIsModulationEnabled(model)) GSmaterialGetModulate(model->materials, color);
    else { color->r = color->g = color->b = 127; color->a = 255; }
}
extern "C" void GSmodelSetEnvMapBlendValue(GSmodel* model, f32 value) {
    if (GSmodelIsEnvMapEnabled(model)) {
        u32 i = 0;
        u32 count = model->materialCount;
        GSmaterial* material = model->materials;
        for (; i < count; ++i, ++material) GSmaterialSetEnvMapBlendValue(material, value);
    }
}
extern "C" void GSmodelSetMaterialAlpha(GSmodel* model, f32 alpha) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) GSmaterialSetAlpha(material, (f32)material->alpha * alpha / 255.0f);
}
extern "C" u8 GSmodelIsRootNullAdded(GSmodel* model) { return (model->flags >> 17) & 1; }
extern "C" void modelMaterialFree__FP10GSmaterial(GSmaterial* material) {
    GSmaterialResetPEdescr(material); GSmaterialResetTexture(material); GSmaterialDisableExtension(material, 0xffff);
}
extern "C" void modelMaterialInit__FP10GSmaterial(GSmaterial* material) {
    if (material) {
        material->savedPE = (void*)0xfefefefe;
        material->extensions = 0;
        material->channels[0] = 0; material->channels[1] = 1; material->channels[2] = 2; material->channels[3] = 3;
        material->environmentTexture = 0; material->environment = 0; material->environmentImage = 0;
        material->savedImage = (GSimageDesc*)0xfefefefe;
    }
}

struct GSgfxLayer;
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32);
void SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(GSgfxLayer*, GStexture*, bool, u8*);
GStexture* GetTextureCopy__10GSgfxLayerFv(GSgfxLayer*);
static u8 g_envmap_tex_ref_count;
}
extern "C" void GSmodelDisableEnvMap(GSmodel* model) {
    if (GSmodelIsEnvMapEnabled(model)) {
        u32 i = 0;
        u32 count;
        GSmaterial* material;
        material = model->materials; count = model->materialCount;
        for (; i < count; ++i, ++material) GSmaterialDisableExtension(material, 4);
        GSgfxLayer* layer = GSgfxLayerFindByID(0);
        if (layer && --g_envmap_tex_ref_count == 0) SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(layer, 0, false, 0);
    }
}
extern "C" void GSmodelEnableEnvMap(GSmodel* model, s32 source, s32 mode, f32 blend) {
    if (!GSmodelIsEnvMapEnabled(model)) {
        GSgfxLayer* layer = GSgfxLayerFindByID(0);
        if (layer) {
            ++g_envmap_tex_ref_count;
            SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(layer, (GStexture*)0xfefefefe, false, 0);
            GStexture* texture = GetTextureCopy__10GSgfxLayerFv(layer);
            if (texture) {
                u32 i = 0;
                u32 count = model->materialCount;
                GSmaterial* material = model->materials;
                for (; i < count; ++i, ++material) {
                    GSmaterialSetEnvMapParams(material, source, mode, texture, blend);
                    GSmaterialEnableExtension(material, 4);
                }
            }
        }
    }
}
