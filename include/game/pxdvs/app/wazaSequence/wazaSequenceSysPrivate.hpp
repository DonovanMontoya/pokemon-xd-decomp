#ifndef WAZA_SEQUENCE_SYS_PRIVATE_H
#define WAZA_SEQUENCE_SYS_PRIVATE_H

#include <global.h>

struct GSvec {
    f32 x;
    f32 y;
    f32 z;
};

class WazaSequence {
public:
    u8 pad00[0x10];
    u16 resId;                  // 0x10
    u8 pad12;
    u8 index;                   // 0x13
    u8 active;                  // 0x14
    u8 pad15[2];
    u8 stopped;                 // 0x17
    u8 pad18[0x10];
    WazaSequence* next;         // 0x28

    void ApplyStop();
    s32 IsImpactPoint(u8);
    static s32 GetNumVariations(u16, u16);
    ~WazaSequence();
};

class Sequence {
public:
    virtual ~Sequence() = 0;
    virtual void Update(f32) = 0;
    virtual void GetPosition(GSvec*) = 0;
    virtual void GetRotation(GSvec*) = 0;
    virtual void GetScale(GSvec*) = 0;
    virtual void SetPosition(const GSvec*) = 0;
    virtual void SetRotation(const GSvec*) = 0;
    virtual void SetScale(const GSvec*) = 0;
    virtual void SetVisibility(bool) = 0;

    u16 id;                     // 0x4
    u8 pad06[2];
    s32 type;                   // 0x8
    u8 pad0C[0x24];
    WazaSequence* wazaList;     // 0x30
    s32 camera;                 // 0x34
    Sequence* next;             // 0x38
};

class ModelSequence;

class NullSequence : public Sequence {
public:
    WazaSequence* GetWaza(u16, u16) const;
    void FreeAllWaza();
};

enum GSmodelAnimType { GSMODEL_ANIM_TYPE_0, GSMODEL_ANIM_TYPE_1 };

class ModelSequence : public Sequence {
public:
    u8 pad3C[4];
    u32 rnd;                    // 0x40
    u16 resourceGroup;          // 0x44
    u8 pad46[0xA];
    u8 modelSize;               // 0x50
    u8 pad51[3];
    u8 flags;                   // 0x54
    u8 flipped;                 // 0x55
    u8 isPokemon;               // 0x56
    u8 rare;                    // 0x57
    u8 pad58[9];
    u8 lookEnabled;             // 0x61
    u8 pad62[0x16];
    ModelSequence* lookTarget;  // 0x78
    u8 pad7C[0x18];
    u32 model;                  // 0x94

    void DoModelAnimation(int);
    void Talk();
    void CopyState(ModelSequence*);
    void SetFlags(u8);
    void SetDefaultFlags();
    void ResetStatus(u8);
    void SetStatus(u8);
    void DoDefaultAnimation(GSmodelAnimType, bool);
};

ModelSequence* New_ModelSequence(unsigned short, unsigned long, bool);
ModelSequence* New_ModelSequence(unsigned short);
NullSequence* New_NullSequence();

extern Sequence* g_Sequences;
extern WazaSequence* g_LastStartedWaza;
extern u32 g_SleepParticle;
extern u32 g_IceParticle;
extern s32 _resource_id_count;
extern s8 g_EnableModelLayerChange;
extern u32 _modelShadowLight;
extern s32 _modelShadowCount;
extern u32 _modelShadowList[];
extern u32 waza_resource_data[];
struct PokemonWazaEntry {
    u8 variant;
    u8 pad1;
    u16 pokemonId;
    u16 wazaId;
    u16 resId;
};
struct WazaExtEntry {
    u8 variant;
    u8 pad1;
    u16 wazaId;
    u16 res[4];
};
extern PokemonWazaEntry pokemon_waza_wzx_data[];
extern u16 waza_generic_wzx_data[];
extern u32 waza_generic_wzx_data_number;
extern u16 waza_wzx_data[][3];
extern u32 waza_wzx_data_number;
extern WazaExtEntry waza_ext_wzx_data[];
extern u32 waza_ext_wzx_data_number;
extern u32 g_SoundListener;
extern s32 gCameraShakeModel;
extern u32 gCameraShakeModels[9];
extern GSvec zeroVector;
static void _wazaSequenceSysCameraShakeInit();

struct _GSmodel;
u16 wazaSequenceSysGetResourceID(ModelSequence*, u16, u16, u8);
extern "C" {
u32 GSmodelLoad(u32, u32);
void GSmodelSetVisibility(u32, u32);
u8 GSmodelCanAnimate(u32);
void GSmodelSetAnimIndex(u32, u32);
void GSmodelSetAnimRate(u32, f32);
void GSmodelStartAnimation(u32);
u8 GSmodelCanTexAnimate(u32);
void GSmodelSetTexAnimIndex(_GSmodel*, u8);
void GSmodelSetTexAnimRate(_GSmodel*, f32);
void GSmodelStartTexAnimation(_GSmodel*);
void GSlogWrite(const char*, ...);
void* memset(void*, int, unsigned long);
void GSmodelFree(u32);
void GSsndFreeListener(u32);
u32 GScameraGetActiveCamera();
void GScameraGetPosition(u32, GSvec*);
void GScameraGetLookAt(u32, GSvec*, GSvec*);
void GScameraLoadActiveCameraMatrix(s32);
void PSVECSubtract(GSvec*, GSvec*, GSvec*);
void PSVECNormalize(GSvec*, GSvec*);
u32 GSsndCreateListenerParam(GSvec*, GSvec*, GSvec*, GSvec*, u32, f32, f32, f32);
void GSsndUpdateListenerParam(u32, GSvec*, GSvec*, GSvec*);
f32 GSgfxVideoGetLastRenderTime(u8);
u32 GSgfxVideoGetVsyncRate();
s32 floorDataBiosGetCurrentPtr();
s32 floorDataBiosGetGroupID();
u8 floorDataBiosGetFloorKind(s32);
u32 floorDataBiosGetShadowReciveNum(s32);
s32 floorDataBiosGetShadowReciveID(s32, u32);
s32 floorDataBiosGetShadowLightID(s32);
void* GSresGetResource(u32, u32);
void GSfsysReadWait(u32);
s32 GSfsysGetStatus(u16);
void GSfsysFree(u16);
void GSresFreeGroup(u16);
void GSthreadSwitch();
}

inline bool Sequence_IsValid(Sequence* seq) {
    Sequence* p = g_Sequences;
    if (seq == 0) {
        return false;
    }
    for (; p != 0; p = p->next) {
        if (p == seq) {
            return true;
        }
    }
    return false;
}

inline ModelSequence* Sequence_AsModel(Sequence* seq) {
    if (seq->type == 1) {
        return (ModelSequence*)seq;
    }
    return 0;
}

#endif
