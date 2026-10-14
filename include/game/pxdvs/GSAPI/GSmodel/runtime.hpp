#ifndef GSMODEL_RUNTIME_HPP
#define GSMODEL_RUNTIME_HPP
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
struct GSlight;
struct GSgfxVF;
struct GSmodelDustPart { f32 height; u8 emissionPart, trackingPart, falling, enabled; };
// Runtime extensions occupy the remainder of each 0x628-byte bank slot.
// The shared GSmodel prefix and all of its recovered offsets remain unchanged.
struct GSmodelRuntime {
    GSmodel model;
    s32 shadowSurfaceCount;
    GSmodel** shadowSurfaces;
    GSlight* shadowLight;
    f32 groundPlane;
    GSparticleBank* dustBank;
    GSmodelDustPart dustParts[2];
    f32 dustScale;
    u16 distortionPart;
    u8 distortionMaterial, distortionStrength;
    HSD_PObj* distortionPolygon;
    GStexture* distortionTexture;
    GSgfxVF* distortionVertexFormat;
    u8 reserved620[8];
};
typedef char GSmodelRuntimeSizeCheck[sizeof(GSmodelRuntime) == 0x628 ? 1 : -1];
static inline GSmodelRuntime* modelRuntime(GSmodel* model) { return (GSmodelRuntime*)model; }
extern "C" {
void modelBankReleaseModel__FP8_GSmodel(GSmodel*);
GSmodel* modelBankGetFreeModel__Fv();
void modelBankInit__Fv();
void GSmodelFreeDistortion(GSmodel*);
void GSmodelCreateDistortion(GSmodel*, u16, u8, u8);
void GSmodelEnableDistortion(GSmodel*);
void modelDustUpdate__FP8_GSmodel(GSmodel*);
void GSmodelSetShadowToCameraHeightCheck(u8);
void GSmodelSetGroundPlane(GSmodel*, f32, u8);
void GSmodelSetMarukageTexture(GStexture*);
void GSmodelSetShadowDistLimits(f32, f32);
void GSmodelFreeAllShadowTextures();
void GSmodelSetShadowBoundExpansion(f32);
void GSmodelSetShadowCutoffDist(f32);
void GSmodelSetShadowDebug(u8);
void GSmodelSetShadowTextureSize(s32, s32);
void GSmodelSetShadowLight(GSmodel*, GSlight*);
void GSmodelSetShadowSurface(GSmodel*, s32, GSmodel**);
void GSmodelClearShadowFlags(GSmodel*, u32);
void GSmodelSetShadowFlags(GSmodel*, u32);
void modelShadowPrepare__FP8_GSmodelb(GSmodel*, bool);
void modelShadowFreeModelList__FP8_GSmodel(GSmodel*);
void modelShadowInit__Fv();
}
#endif
