#ifndef GSSHAPE_HPP
#define GSSHAPE_HPP
#include <global.h>
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct GSmtx { Mtx matrix; };
struct tagGScol4ub { u8 r, g, b, a; };
struct GsShapePair { f32 u, v; };
struct GsShapeCurvePoint { f32 time, value; };
struct tagGsFilePrimKeyFrame {
    u32 reserved00, frame;
    u8 visible, reserved09[3], textureSwapAxes[4];
    Vec scale, position, pivot, rotation;
    tagGScol4ub color;
    f32 radius[2], reserved4C[2], showAngle[2];
    GsShapePair textureScale[4], textureOffset[4];
    tagGScol4ub textureColor[4], textureColorLow[4];
    u8 transformCurveCount[12];
    u8 colorCurveCount[4], radiusCurveCount[4], showAngleCurveCount[2];
    u8 textureScaleCurveCount[8], textureOffsetCurveCount[8];
    u8 textureColorCurveCount[16], textureColorLowCurveCount[16];
    u8 reserved102[2];
    GsShapeCurvePoint* transformCurves[12];
    GsShapeCurvePoint* colorCurves[4];
    GsShapeCurvePoint* radiusCurves[4];
    GsShapeCurvePoint* showAngleCurves[2];
    GsShapeCurvePoint* textureScaleCurves[8];
    GsShapeCurvePoint* textureOffsetCurves[8];
    GsShapeCurvePoint* textureColorCurves[16];
    GsShapeCurvePoint* textureColorLowCurves[16];
    u16 deformCountU, deformCountV;
    f32 *deformU, *deformV;
    u16 twistCount, reserved22A;
    f32* twist;
    u8 reserved230[0xC];
    u8 gradationType, reserved23D[3];
    u16 gradationCountU, gradationCountV;
    tagGScol4ub *gradationU, *gradationV;
};
typedef char GsShapeKeyFrameSizeCheck[sizeof(tagGsFilePrimKeyFrame)==0x24C?1:-1];
struct GsShapeKeyEntry {
    u32 reserved00; u16 objectIndex, frameCount; tagGsFilePrimKeyFrame** frames;
    u8 channelFlags[0x10]; u8 textureColorAnimated[4];
    u8 reserved20[0x18]; f32 transformScales[4]; f32 radiusScale, angleScale, textureOffsetScale, textureScaleScale;
};
struct tagGsFilePrimObjectEntry;
struct GsKeyObject {
    GsShapeKeyEntry* entry;
    tagGsFilePrimKeyFrame** frames;
    u8 visible, reserved09[3];
    GSmtx textureMatrices[4], shapeMatrix, transformMatrix;
    bool GetShapeMatrix(GSmtx*, GSmtx*, const tagGsFilePrimObjectEntry*, u8, const u8*, const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    bool GetFrameInterval(u32, tagGsFilePrimKeyFrame*&, tagGsFilePrimKeyFrame*&, f32&);
    bool GetGradationParameter(u8*, tagGScol4ub*, const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    bool GetTwistParameter(f32*, const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    bool GetDeformParameterU(f32*, const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    bool GetDeformParameterV(f32*, const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    bool GetLinearParameterU(f32*, const tagGsFilePrimKeyFrame*);
    bool GetLinearParameterV(f32*, const tagGsFilePrimKeyFrame*);
    tagGScol4ub GetShapeColor(const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    f32 GetShapeColorAlpha(const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    bool GetShapeRadius(f32*, f32*, const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    bool GetShapeShowAngle(f32*, f32*, const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32) const;
    GsShapePair GetTextureScale(const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32, u32) const;
    GsShapePair GetTextureOffset(const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32, u32) const;
    tagGScol4ub GetTextureColor(const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32, u32) const;
    tagGScol4ub GetTextureColorLow(const tagGsFilePrimKeyFrame*, const tagGsFilePrimKeyFrame*, f32, u32) const;
};
struct tagGsFilePrimObjectEntry {
    u8 reserved00[4]; u8 dynamic, reserved05[3], shapeType, colorMode; u16 segmentsU, segmentsV, vertexCount;
    Vec* vertices; tagGScol4ub* colors; GsShapePair* textureCoords; void* reserved1C;
    u8 reserved20[6]; u16 textureCount; void* textures[4];
    u16 geometryType, reserved3A; f32 width, height;
    u8 reserved44[0x18]; f32 shearAngle; u8 reserved60[0xD], transformEnabled, rotation1Enabled, rotation2Enabled;
    Vec position; u8 reserved7C[0x18]; Vec rotationAxis1, rotationAxis2;
    f32 rotationAngle1, rotationAngle2;
};
struct GsShapeObject {
    tagGsFilePrimObjectEntry* entry;
    u8 vertexFormat[0x440];
    void* vertexArrays[6];
    u8 reserved45C[0x44];
    void* displayList;
    u8* drawBuffers[256];
    u32 GetPolygonCount();
    bool FreeShapeDrawBuffer(s16);
    bool CreateShapeDrawBuffer(s16);
    void FreeDisplayListShape();
    void MakeDisplayListShape();
    void MakeShapeGfxDL();
    bool DeformTextureCoord(u32, bool, const f32*, const f32*, bool, const f32*);
    bool WaveTextureCoord(u32, f32, f32, const GSmtx*, bool);
    bool DeformVertexCoord(bool, const f32*, const f32*, bool, f32, f32, bool, f32, f32, bool, const f32*);
    bool DeformVertexCoordCylinderEx(bool, const f32*, const f32*, bool, f32, f32, bool, f32, bool, const f32*);
    bool DeformVertexCoordSpiral(bool, const f32*, const f32*, bool, f32, f32, bool, f32, f32, bool, const f32*);
    bool DeformVertexCoordSphere(bool, const f32*, const f32*, bool, f32, f32, bool, f32, f32, bool, const f32*);
    bool DeformVertexCoordTorus(bool, const f32*, const f32*, bool, f32, f32, bool, f32, f32, bool, const f32*);
    void SetVertexColorSpecify(const tagGScol4ub&, bool);
    void SetVertexColorAlpha(int, int, f32, bool);
    void SetVertexColorGradation(u8, const tagGScol4ub*, int, f32, bool);
};
typedef char GsShapeObjectSizeCheck[sizeof(GsShapeObject)==0x8A4?1:-1];
enum GSgfxLayerID { GS_SHAPE_LAYER_DEFAULT=2, GS_SHAPE_LAYER_ALTERNATE=4 };
struct GStexture;
struct GsShapeFileAnimation {
    u32 reserved00, frameCount; u32 frameRate; u16 keyCount, reserved0E; u32 keysOffset;
    u8 loop, transformCount, reserved16[2]; u8 transformOrder[5];
};
struct GsShapeRender {
    u8 active, reserved01[3]; u32 frame; s32 instance;
    GSgfxLayerID layer; u32 flags; GsShapeFileAnimation* animation;
    u16 keyCount, reserved1A; GsKeyObject* keys;
    u16 objectCount, reserved22; GsShapeObject* objects;
    u16 textureCount, reserved2A; void* textures;
    u16 deformCountU, deformCountV, twistCount, gradationCount;
    f32 *deformU, *deformV, *twist; tagGScol4ub* gradation;
    GStexture* refractTexture;
    s16 instanceCount, nextInstance;
    u8 instances[256], lastBuffer, currentBuffer;
    u16 tokens[2][256];
    u16 reserved552; u32 polygonCount, usedMemory, instancedMemory;
    s16 freeCount[2], freeInstances[2][256];
    void ExecuteFreeInstance();
    void SwapBuffers();
    GSgfxLayerID GetLayerId() const;
    u32 GetInstancedMemorySizeAll();
    u32 GetUsedMemorySizeAll();
    void FreeShapeRenderDrawBuffer(s16);
    s16 CreateShapeRenderDrawBuffer();
    void Render(s16, GSgfxLayerID);
    void Update(f32, s16);
    bool LoadShapeRender(void*);
    void FreeShapeRender();
    void InitShapeRender();
};
typedef char GsShapeRenderSizeCheck[sizeof(GsShapeRender)==0x964?1:-1];
// Reserved spans describe unrecovered file/runtime fields, not object-file alignment.
typedef char GsKeyObjectSizeCheck[sizeof(GsKeyObject)==0x12C?1:-1];
typedef char GsShapeTransformCurveOffsetCheck[offsetof(tagGsFilePrimKeyFrame,transformCurves)==0x104?1:-1];
typedef char GsShapeDeformCountOffsetCheck[offsetof(tagGsFilePrimKeyFrame,deformCountU)==0x21C?1:-1];
typedef char GsShapeGradationOffsetCheck[offsetof(tagGsFilePrimKeyFrame,gradationType)==0x23C?1:-1];
typedef char GsShapeEntryTextureCountOffsetCheck[offsetof(tagGsFilePrimObjectEntry,textureCount)==0x26?1:-1];
typedef char GsShapeEntryTransformOffsetCheck[offsetof(tagGsFilePrimObjectEntry,transformEnabled)==0x6D?1:-1];
typedef char GsShapeVertexArraysOffsetCheck[offsetof(GsShapeObject,vertexArrays)==0x444?1:-1];
typedef char GsShapeDrawBuffersOffsetCheck[offsetof(GsShapeObject,drawBuffers)==0x4A4?1:-1];
typedef char GsShapeTokenOffsetCheck[offsetof(GsShapeRender,tokens)==0x152?1:-1];
typedef char GsShapeMemoryOffsetCheck[offsetof(GsShapeRender,instancedMemory)==0x55C?1:-1];
typedef char GsShapeFreeQueueOffsetCheck[offsetof(GsShapeRender,freeInstances)==0x564?1:-1];
// Animation Update addresses these fields directly in the original object.
typedef char GsShapeKeyObjectIndexOffsetCheck[offsetof(GsShapeKeyEntry,objectIndex)==0x4?1:-1];
typedef char GsShapeVisibleOffsetCheck[offsetof(GsKeyObject,visible)==0x8?1:-1];
typedef char GsShapeTextureMatricesOffsetCheck[offsetof(GsKeyObject,textureMatrices)==0xC?1:-1];
typedef char GsShapeMatrixOffsetCheck[offsetof(GsKeyObject,shapeMatrix)==0xCC?1:-1];
typedef char GsShapeTransformMatrixOffsetCheck[offsetof(GsKeyObject,transformMatrix)==0xFC?1:-1];
typedef char GsShapeGeometryTypeOffsetCheck[offsetof(tagGsFilePrimObjectEntry,geometryType)==0x38?1:-1];
typedef char GsShapeShearAngleOffsetCheck[offsetof(tagGsFilePrimObjectEntry,shearAngle)==0x5C?1:-1];
typedef char GsShapeAnimationFrameCountOffsetCheck[offsetof(GsShapeFileAnimation,frameCount)==0x4?1:-1];
typedef char GsShapeTransformOrderOffsetCheck[offsetof(GsShapeFileAnimation,transformOrder)==0x18?1:-1];
extern u32 g_instancedMemorySizeAll;
extern "C" {
u32 shapeGetInstancedMemorySizeAll();
u32 shapeGetUsedMemorySize(u16);
void shapeFreePrimitiveInstance(u16,s16);
s16 shapeCreatePrimitiveInstance(u16);
s32 shapeGenerateIndex();
void shapeRelease(u16);
void shapeRender(u16,s16,GSgfxLayerID);
void shapeUpdate(u16,f32,s16);
bool shapeLoad(u16,void*);
bool shapeInit(u16);
void* GSmemAlloc(u32);
void* GSmemAllocClr(u32);
void GSmemFree(void*);
void GSgfxTokenWaitForClear(u16);
void GSgfxVFFree(void*);
void GSgfxDLFree(void*);
void GStextureFree(GStexture*);
}
#endif
