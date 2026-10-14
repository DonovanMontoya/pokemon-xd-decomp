#ifndef GS_PARTICLE_H
#define GS_PARTICLE_H
#include <global.h>
typedef struct PSParticle PSParticle; typedef struct PSGenerator PSGenerator; typedef struct PSAppSRT PSAppSRT;
typedef struct PSVec { f32 x,y,z; } PSVec;
typedef struct PSJObj { u8 prefix[0x14]; u32 flags; u8 prefix18[0x2c]; f32 matrix[3][4]; } PSJObj;
struct PSAppSRT {
    PSAppSRT* next; /* 0x0 */
    PSGenerator* generator; /* 0x4 */
    PSVec translate; /* 0x8 */
    PSVec rotation; /* 0x14 */
    u8 opaque20[4];
    PSVec scale; /* 0x24 */
    u8 status; /* 0x30 */
    u8 frame; /* 0x31 */
    u16 references; /* 0x32 */
    f32 matrix[3][4]; /* 0x34 */
    f32 scaleX; /* 0x64 */
    f32 scaleY; /* 0x68 */
    void (* freefunc)(PSAppSRT*); /* 0x6C */
    u16 id; /* 0x70 */
    u8 generatorOwned; /* 0x72 */
    u8 opaque73[1];
};
struct PSGenerator {
    PSGenerator* next; /* 0x0 */
    u32 kind; /* 0x4 */
    f32 random; /* 0x8 */
    f32 count; /* 0xC */
    u16 life; /* 0x10 */
    u16 type; /* 0x12 */
    u8 bank; /* 0x14 */
    u8 link; /* 0x15 */
    u8 texGroup; /* 0x16 */
    u8 state; /* 0x17 */
    u16 id; /* 0x18 */
    u16 particleLife; /* 0x1A */
    u8* commands; /* 0x1C */
    PSVec position; /* 0x20 */
    PSVec velocity; /* 0x2C */
    f32 gravity; /* 0x38 */
    f32 friction; /* 0x3C */
    f32 size; /* 0x40 */
    f32 radius; /* 0x44 */
    f32 angle; /* 0x48 */
    u32 children; /* 0x4C */
    PSAppSRT* appsrt; /* 0x50 */
    f32 param1; /* 0x54 */
    f32 param2; /* 0x58 */
    f32 param3; /* 0x5C */
    f32 axisXX; /* 0x60 */
    f32 axisXY; /* 0x64 */
    f32 axisXZ; /* 0x68 */
    f32 axisYX; /* 0x6C */
    f32 axisYY; /* 0x70 */
    f32 axisYZ; /* 0x74 */
    f32 axisZX; /* 0x78 */
    f32 axisZY; /* 0x7C */
    f32 axisZZ; /* 0x80 */
    u16 edgeFlags; /* 0x84 */
    u8 opaque86[2];
    s32 camera; /* 0x88 */
    u16 transformFlags; /* 0x8C */
    u16 commandID; /* 0x8E */
    PSVec rotation; /* 0x90 */
    PSVec scale; /* 0x9C */
    PSJObj* jobj; /* 0xA8 */
    PSVec nodeScale; /* 0xAC */
};
struct PSParticle {
    PSParticle* next; /* 0x0 */
    u32 kind; /* 0x4 */
    u8 bank; /* 0x8 */
    u8 texGroup; /* 0x9 */
    u8 pose; /* 0xA */
    u8 palette; /* 0xB */
    u16 sizeCount; /* 0xC */
    u16 primCount; /* 0xE */
    u16 envCount; /* 0x10 */
    u8 primColor[4]; /* 0x12 */
    u8 envColor[4]; /* 0x16 */
    u16 wait; /* 0x1A */
    u8 loopCount; /* 0x1C */
    u8 link; /* 0x1D */
    u16 id; /* 0x1E */
    u8* commands; /* 0x20 */
    u16 commandPtr; /* 0x24 */
    u16 markPtr; /* 0x26 */
    u16 loopPtr; /* 0x28 */
    u16 life; /* 0x2A */
    PSVec velocity; /* 0x2C */
    f32 gravity; /* 0x38 */
    f32 friction; /* 0x3C */
    PSVec position; /* 0x40 */
    f32 size; /* 0x4C */
    f32 rotate; /* 0x50 */
    u16 alphaCount; /* 0x54 */
    u8 alphaMode; /* 0x56 */
    u8 alpha1; /* 0x57 */
    u8 alpha2; /* 0x58 */
    u8 pointOffset; /* 0x59 */
    u16 matCount; /* 0x5A */
    u16 ambCount; /* 0x5C */
    u16 rotateCount; /* 0x5E */
    f32 sizeTarget; /* 0x60 */
    f32 rotateTarget; /* 0x64 */
    f32 trail; /* 0x68 */
    u16 primRemain; /* 0x6C */
    u16 envRemain; /* 0x6E */
    u8 primTarget[4]; /* 0x70 */
    u8 envTarget[4]; /* 0x74 */
    u16 matRemain; /* 0x78 */
    u16 ambRemain; /* 0x7A */
    u16 alphaRemain; /* 0x7C */
    u8 alpha1Target; /* 0x7E */
    u8 alpha2Target; /* 0x7F */
    u8 matRGB; /* 0x80 */
    u8 matAlpha; /* 0x81 */
    u8 ambRGB; /* 0x82 */
    u8 ambAlpha; /* 0x83 */
    u8 matRGBTarget; /* 0x84 */
    u8 matAlphaTarget; /* 0x85 */
    u8 ambRGBTarget; /* 0x86 */
    u8 ambAlphaTarget; /* 0x87 */
    f32 textureScale; /* 0x88 */
    PSGenerator* generator; /* 0x8C */
    PSAppSRT* appsrt; /* 0x90 */
};
typedef struct PSCmd { u16 type,texGroup,genLife,life; u32 kind; f32 gravity,friction; PSVec velocity; f32 radius,angle,random,size,param1,param2,param3; u8 commands[1]; } PSCmd;
typedef struct PSTex { u32 count,format,paletteFormat,width,height; u16 palettes,paletteFlags; void* textures[1]; } PSTex;
void* HSD_Alloc(u32); void HSD_Free(void*); void* memset(void*,int,u32); void __assert(const char*,int,const char*); void OSPanic(const char*,int,const char*,...);
PSParticle* particleSort(s32,PSParticle**,PSParticle**); PSParticle* _psListGetFirst(s32); void _psListDelete(PSParticle*,PSParticle*); PSParticle* _psListNew(PSParticle*,s32); void _psListClear(void); s32 _psLinkInit(s32);
s32 psRemoveGeneratorAppSRT(PSGenerator*); s32 psRemoveParticleAppSRT(PSParticle*); s32 psChangeGeneratorAppSRT(PSGenerator*,PSAppSRT*); s32 psChangeParticleAppSRT(PSParticle*,PSAppSRT*); s32 psAttachGeneratorAppSRT(PSGenerator*,PSAppSRT*); s32 psAttachParticleAppSRT(PSParticle*,PSAppSRT*); void psAddGeneratorAppSRT(PSGenerator*,s8); void psRemoveAppSRT(void); s32 psInitAppSRT(s32,s32);
void psSetToken(s16); void psSetParticleVisibility(PSGenerator*,u8); void psSetGeneratorAngleRadiusScale(PSGenerator*,PSVec*,u8);
void psSetRandomVelocityScaling(PSGenerator*,u8); void psSetNodeScaling(PSGenerator*,u8); void psSetTornadoScaling(PSGenerator*,u8,u8); void psSetParticleTexScaling(PSGenerator*,u8); void psSetOffsetRotationInLocal(PSGenerator*,u8,u8); void psSetVelocityRotationInLocal(PSGenerator*,u8); void psUnlinkChildGensFromJObj(PSGenerator*); void psLinkChildGensToJObj(PSGenerator*,PSJObj*); s32 psGetParticleChildCount(PSGenerator*); u16 psGetGeneratorChildMaxLife(PSGenerator*); void psKillGeneratorChild(PSGenerator*); void psKillFamily(u16,s32); void psDeletePntJObjwithParticle(PSParticle*); void psKillAllParticle(void); void psRemoveParticle(void); void psInitParticle(s32);
PSParticle* psGenerateParticle0(PSParticle*,s32,s32,s32,s32,u32,s32,u8*,f32,f32,f32,f32,f32,f32,f32,f32,s32,f32,s32,PSGenerator*,s32);
PSParticle* psGenerateParticle(s32,s32,s32,u32,s32,u8*,f32,f32,f32,f32,f32,f32,f32,f32,s32,f32,s32,PSGenerator*);
PSParticle* psGenerateParticleID0(PSParticle*,s32,s32,s32,s32); void psInterpretParticle0(PSParticle*,s32);
s32 psGeneratorGetCamera(PSGenerator*); void psGeneratorSetCamera(PSGenerator*,s32); PSGenerator* psCreateGeneratorID(s32,s32,s32); void psExecGenerator(s32); f32 generateParticle(PSGenerator*); void psKillAllGenerator(void); void psKillGeneratorID(u16); void psKillGenerator(PSGenerator*); void psRemoveGenerator(void); void psInitGenerator(s32); void genPosUpdate(PSGenerator*); u16 psGetNewIDNum(void);
void HSD_JObjSetupMatrixSub(PSJObj*); void HSD_JObjUnref(PSJObj*); f32 HSD_Randf(void); void* HSD_SListRemove(void*);
extern u16 numActiveParticles,numPeakParticles,numActiveGenerators,numPeakGenerators,numActivePSAppSRT,numPeakPSAppSRT;
extern PSGenerator *activeGenerator,*freeGenerator,*lastGP; extern void* standbyGenerator;
extern PSCmd** psCmdListArray[64]; extern PSTex** psTexGroupArray[64]; extern s32 psNumCmdList[64]; extern void* psFormGroupArray[64]; extern s32 psNumTexGroup[64]; extern void* ptclref[64];
extern void (*psExtCreateGenFunc)(PSGenerator*); extern void (*psExtExecGenFunc)(PSGenerator*,f32 (*)[4]);

typedef struct PSClass PSClass;
typedef struct PSObject { PSClass* methods; u16 references; } PSObject;
struct PSClass { u8 opaque[0x30]; void (*release)(PSObject*,PSClass*); void (*destroy)(PSObject*,PSClass*); };
typedef struct PSWObj { u8 opaque[0xC]; PSVec position; } PSWObj;
typedef struct PSCamera { PSClass* methods; u16 references; u8 opaque[0x1E]; PSWObj* eye; } PSCamera;
void psSetBillboardCamera(PSCamera*); void psSetPointJObjNodup(PSObject*,s32); void psSetPointJObj(s32,PSObject*);
void HSD_CObjGetUpVector(PSCamera*,PSVec*); void PSMTXConcat(f32 (*)[4],f32 (*)[4],f32 (*)[4]); void PSMTXIdentity(f32 (*)[4]); void PSMTXMultVec(f32 (*)[4],PSVec*,PSVec*); void PSMTXRotRad(f32 (*)[4],char,f32); void PSVECCrossProduct(PSVec*,PSVec*,PSVec*); void PSVECNormalize(PSVec*,PSVec*);
f64 atan2(f64,f64); f64 cos(f64); f64 sin(f64);
extern PSCamera* psCamera;
#endif
