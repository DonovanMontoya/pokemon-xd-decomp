#include <game/pxdvs/GSAPI/GSmodel/runtime.hpp>
#include <game/pxdvs/GSAPI/GSpart/GSpart.hpp>
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
struct GSgfxLayer { u8 reserved00[0x28]; s32 identifier; };
struct GSmodelVertexDescriptor { s32 attribute, type, components, format; u8 fractionalBits, reserved11; u16 stride; void* data; };
struct GSparticleGenerator;
extern "C" {
char g_distortion_layer_name[] = "model distortion";
static u8 g_distortion_layer_ref_count;
GSgfxLayer* GSgfxLayerFindByName(char*);
GSgfxLayer* GSgfxLayerFindByID(s32);
void SetLayerVisibility__10GSgfxLayerFb(GSgfxLayer*, bool);
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(s32);
s32 Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(char*, u32, u32, u32, s32, bool, bool, bool, s32, s32);
void* GSmemAllocClr(u32);
void GSmemFree(void*);
void* __nw__FUl(u32);
void __dl__FPv(void*);
void GSgfxVFInit(GSgfxVF*);
void GSgfxVFCreate(GSgfxVF*);
void GSgfxVFFree(GSgfxVF*);
void GSgfxVFSetElement(GSgfxVF*, s32, s32, s32, u8);
void GSgfxVFSetArray(GSgfxVF*, s32, s32, void*, u8, u8);
GSpart* GSmodelGetPart(GSmodel*, u32);
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank*, s32, s32);
void GSparticleSetGeneratorPosition(GSparticleGenerator*, Vec*);
void GSparticleSetGeneratorRotation(GSparticleGenerator*, Vec*);
void GSparticleSetGeneratorScale(GSparticleGenerator*, Vec*, void*, void*);
void GSmodelFreeDistortion(GSmodel* model) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if ((model->flags & 0x80000) == 0x80000) {
        model->flags &= ~0x80000;
        GSgfxLayer* layer = GSgfxLayerFindByName(g_distortion_layer_name);
        if (layer) SetLayerVisibility__10GSgfxLayerFb(layer, false);
    }
    runtime->distortionPart = 0; runtime->distortionMaterial = 0; runtime->distortionPolygon = 0;
    if (runtime->distortionTexture) {
        GSmemFree(runtime->distortionTexture); runtime->distortionTexture = 0;
        if (g_distortion_layer_ref_count && --g_distortion_layer_ref_count == 0) {
            GSgfxLayer* layer = GSgfxLayerFindByName(g_distortion_layer_name);
            if (layer) Remove__16GSgfxLayerConfigF12GSgfxLayerID(layer->identifier);
        }
    }
    if (runtime->distortionVertexFormat) {
        GSgfxVFFree(runtime->distortionVertexFormat); __dl__FPv(runtime->distortionVertexFormat); runtime->distortionVertexFormat = 0;
    }
}
void GSmodelCreateDistortion(GSmodel* model, u16 partIndex, u8 materialIndex, u8 strength) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if (!runtime->distortionTexture && partIndex) {
        GSpart* part = GSmodelGetPart(model, partIndex);
        if (part) {
            HSD_JObj* joint = part->joint;
            GSmaterial* material = GSpartGetMaterial(part, materialIndex);
            GSpartFree(part);
            if (material && !(joint->flags & 0x4020)) {
                HSD_DObj* object = joint->u.dobj;
                if (object) {
                    HSD_PObj* polygon = object->pobj;
                    if (polygon && polygon->verts && polygon->n_display && polygon->display && (polygon->flags & 0x3000) != 0x1000) {
                        runtime->distortionPart = partIndex; runtime->distortionMaterial = materialIndex; runtime->distortionPolygon = polygon;
                        runtime->distortionTexture = (GStexture*)GSmemAllocClr(0x80);
                        if (runtime->distortionTexture) {
                            if (!strength) strength = 1;
                            runtime->distortionStrength = strength;
                            GSmaterialGetTexture(material, runtime->distortionTexture);
                            GStextureSetWrap(runtime->distortionTexture, 0, 0); GStextureSetFilter(runtime->distortionTexture, 2, 2, 0);
                            GSgfxLayer* layer = GSgfxLayerFindByName(g_distortion_layer_name);
                            if (!layer) {
                                s32 id = Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(g_distortion_layer_name, 0, 0x1400, 2, 4, false, false, false, 2, 2);
                                layer = GSgfxLayerFindByID(id);
                                if (layer) SetLayerVisibility__10GSgfxLayerFb(layer, false);
                            }
                            ++g_distortion_layer_ref_count;
                            if (!layer) { GStextureFree(runtime->distortionTexture); runtime->distortionTexture = 0; runtime->distortionPolygon = 0; }
                            runtime->distortionVertexFormat = (GSgfxVF*)__nw__FUl(0x440);
                            if (runtime->distortionVertexFormat) {
                                GSgfxVFInit(runtime->distortionVertexFormat); GSgfxVFCreate(runtime->distortionVertexFormat);
                                GSmodelVertexDescriptor* desc = (GSmodelVertexDescriptor*)polygon->verts;
                                while (desc->attribute != 255) {
                                    if (desc->attribute >= 9 || desc->attribute < 0) GSgfxVFSetElement(runtime->distortionVertexFormat, desc->attribute, desc->components, desc->format, desc->fractionalBits);
                                    if (desc->type != 1) GSgfxVFSetArray(runtime->distortionVertexFormat, desc->attribute, desc->type, desc->data, (u8)desc->stride, 0);
                                    ++desc;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void GSmodelEnableDistortion(GSmodel* model) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if ((model->flags & 0x80000) != 0x80000 && runtime->distortionPolygon && runtime->distortionTexture) {
        GSgfxLayer* layer = GSgfxLayerFindByName(g_distortion_layer_name);
        if (layer) { SetLayerVisibility__10GSgfxLayerFb(layer, true); model->flags |= 0x80000; }
    }
}
void modelDustUpdate__FP8_GSmodel(GSmodel* model) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if (runtime->dustBank) {
        GSvec modelPosition;
        Vec position;
        GSvec rotation;
        Vec scale;
        GSmodelGetPosition(model, &modelPosition); GSmodelGetRotation(model, &rotation);
        scale.x = runtime->dustScale; scale.y = runtime->dustScale; scale.z = runtime->dustScale;
        GSmodelDustPart* dust = runtime->dustParts;
        for (s32 i = 0; i < 2; ++i, ++dust) {
            if (dust->enabled) {
                GSpart* part = GSmodelGetPart(model, dust->trackingPart);
                if (part) {
                    GSpartGetTransform(part, &position, 0, 0); GSpartFree(part);
                    f32 height = position.y - modelPosition.param2;
                    if (height < dust->height - 0.00001f) dust->falling = 1;
                    else if (dust->falling) {
                        dust->falling = 0;
                        GSparticleGenerator* generator = GSparticleCreateGenerator(runtime->dustBank, 0, 0);
                        if (generator) {
                            part = GSmodelGetPart(model, dust->emissionPart);
                            if (!part) continue;
                            GSpartGetTransform(part, &position, 0, 0); GSpartFree(part);
                            GSparticleSetGeneratorPosition(generator, &position); GSparticleSetGeneratorRotation(generator, (Vec*)&rotation);
                            GSparticleSetGeneratorScale(generator, &scale, 0, 0);
                        }
                    }
                    dust->height = height;
                }
            }
        }
    }
}
}
