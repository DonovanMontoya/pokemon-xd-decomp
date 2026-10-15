#ifndef WAZA_SEQUENCE_MODEL_SEQUENCE_HPP
#define WAZA_SEQUENCE_MODEL_SEQUENCE_HPP
#include <global.h>
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>

struct _GSmodel;
struct _GSmodelAnimCBData;
struct GSpart;
struct PartAnimData;
struct _GScamera;
class NullSequence;
class WazaSequence {
public:
    u8 pad00[4];
    f32 time;                   // 0x04
    u8 pad08[4];
    u16 move;                  // 0x0c
    u8 category;               // 0x0e
    u8 pad0f[4];
    u8 index;                  // 0x13
    u8 active;                 // 0x14
    u8 pad15[2];
    u8 finished;               // 0x17
    u8 pad18[0x0c];
    NullSequence* owner;        // 0x24
    WazaSequence* next;         // 0x28
    WazaSequence* previous;     // 0x2c
    ~WazaSequence();
    bool Update(f32);
    void SetRenderCamera(_GScamera*);
    inline bool IsActive() const { return active && !finished; }
};
class NullSequence;
class ModelSequence;

enum enumNullJointName { NULL_JOINT_0, NULL_JOINT_16 = 16 };
enum enumSectionMotionType { SECTION_MOTION_0 };
enum GSmodelAnimType { GSMODEL_ANIM_TYPE_0, GSMODEL_ANIM_TYPE_1 };
enum GSpartMixType { GSPART_MIX_0 };

struct ModelAnimEntry {
    s32 kind;
    s32 anim;
};

struct ModelRecord {
    u8 pad00[4];
    s32 count;                  // 0x04
    u8 pad08[0x44];
    s32 joints[16];             // 0x4c
    ModelAnimEntry entries[8];  // 0x8c
    s32 pad[1];
};

class NullSequence {
public:
    NullSequence();
    virtual ~NullSequence();
    virtual void Update(f32);
    virtual void GetPosition(GSvec*);
    virtual void GetRotation(GSvec*);
    virtual void GetScale(GSvec*);
    virtual void SetPosition(GSvec*);
    virtual void SetRotation(GSvec*);
    virtual void SetScale(GSvec*);
    virtual void SetVisibility(bool);

    bool IsActive() const;
    void FreeAllWaza();
    void Remove(WazaSequence*);
    void Add(WazaSequence*);
    WazaSequence* GetWaza(u16, u16) const;

    u16 id;                     // 0x04
    u8 visible;                 // 0x06
    u8 failed;                  // 0x07
    s32 type;                   // 0x08
    GSvec position;             // 0x0c
    GSvec rotation;             // 0x18
    GSvec scale;                // 0x24
    WazaSequence* wazaList;     // 0x30
    s32 camera;                 // 0x34
    NullSequence* next;         // 0x38
};

class ModelSequence : public NullSequence {
public:
    s32 field3C;                // 0x3c
    u32 rnd;                    // 0x40
    u16 resourceGroup;          // 0x44
    u16 field46;                // 0x46
    u16 talkCount;              // 0x48
    u16 field4A;                // 0x4a
    u8 pad4C[2];
    u8 animState;               // 0x4e
    u8 pad4F;
    s8 modelSize;               // 0x50
    u8 field51;                 // 0x51
    u8 wazaIndex;               // 0x52
    u8 field53;                 // 0x53
    u8 flags;                   // 0x54
    u8 flipped;                 // 0x55
    u8 isPokemon;               // 0x56
    u8 rare;                    // 0x57
    u8 noSync;                  // 0x58
    u8 pad59[3];
    u8 field5C;                 // 0x5c
    u8 field5D;                 // 0x5d
    u8 colorSwap;               // 0x5e
    u8 modulation;              // 0x5f
    u8 modulationApplied;       // 0x60
    u8 lookEnabled;             // 0x61
    u16 field62;                // 0x62
    s32 field64;                // 0x64
    s32 pad68;
    GSvec lookVec;              // 0x6c
    ModelSequence* lookTarget;  // 0x78
    ModelSequence* lookSource;  // 0x7c
    s32 field80;                // 0x80
    PartAnimData* sleepAnim;    // 0x84
    PartAnimData* wakeAnim;     // 0x88
    PartAnimData* field8C;      // 0x8c
    PartAnimData* talkAnim;     // 0x90
    _GSmodel* model;            // 0x94
    void* particleBank;         // 0x98
    ModelRecord* records;       // 0x9c
    s32 fieldA0;                // 0xa0
    s32 fieldA4;                // 0xa4
    s32 fieldA8;                // 0xa8
    s32 fieldAC;                // 0xac
    s32 fieldB0;                // 0xb0
    void* iceGenerator;           // 0xb4
    void* sleepGenerator;         // 0xb8

    ModelSequence(unsigned short, unsigned long, bool);
    ModelSequence(unsigned short);
    virtual ~ModelSequence();
    virtual void Update(f32);
    virtual void GetPosition(GSvec*);
    virtual void GetRotation(GSvec*);
    virtual void GetScale(GSvec*);
    virtual void SetPosition(GSvec*);
    virtual void SetRotation(GSvec*);
    virtual void SetScale(GSvec*);
    virtual void SetVisibility(bool);

    void UpdateVisibility(bool);
    f32 GetModelScale(bool) const;
    f32 GetSizeScale() const {
        switch (modelSize) {
        case -2:
            return 0.5f;
        case -1:
            return 0.75f;
        case 1:
            return 1.3333f;
        case 2:
            return 2.0f;
        case 3:
            return 3.25f;
        default:
            return 1.0f;
        }
    }
    void* GetPart(enumNullJointName);
    void LinkWithWazaSequence(WazaSequence*);
    void Land();
    void Fly(bool);
    void UnFreeze();
    void Freeze();
    void DoDefaultAnimation(GSmodelAnimType, bool);
    inline void PlayDefaultAnimation(GSmodelAnimType, bool);
    void ResetScale();
    void ResetRotation();
    void ResetPosition();
    void Talk();
    void WakeUp();
    void Sleep();
    static void Unload(u8*);
    static u8 Load(u8*, unsigned long, unsigned long);
    u8 LoadData(u8*);
    void FreeData();
    void SetInitFlags();
    void SetDefaultFlags();
    void SetFlags(u8);
    void SetStatus(u8);
    void ResetStatus(u8);
    void DoModelAnimation(int);
    void ModelMotionStart();
    void CopyState(ModelSequence*);
    void DestroyParticles(bool, bool);
    void UpdateLookAt();
    int DoAnimation(int, enumSectionMotionType, bool);
};

extern NullSequence* g_Sequences;

ModelSequence* New_ModelSequence(unsigned short, unsigned long, bool);
ModelSequence* New_ModelSequence(unsigned short);
extern "C" u8 ModelSequence_Load(u8*, unsigned long, unsigned long);

extern "C" {
void GSmodelSetScale(_GSmodel*, GSvec*);
void GSmodelSetRotation(_GSmodel*, GSvec*);
void GSmodelSetPosition(_GSmodel*, GSvec*);
void GSmodelGetScale(_GSmodel*, GSvec*);
void GSmodelGetRotation(_GSmodel*, GSvec*);
void GSmodelGetPosition(_GSmodel*, GSvec*);
void GSparticleSetGeneratorRotation(void*, GSvec*);
void GSparticleDestroyGenerator(void*, u8);
void GSparticleFree(void*);
void GSmodelSetAnimEndedCallback(_GSmodel*, void (*)(_GSmodel*, _GSmodelAnimCBData*), void*);
void GSmodelLinkTexAnimToAnim(_GSmodel*, s32);
void GSmodelGetAnimIndex(_GSmodel*, s32*, s32);
void GSmodelSetAnimType(_GSmodel*, s32);
void GSmodelSetAnimRate(_GSmodel*, f32);
u8 GSmodelHasAnimationEnded(_GSmodel*);
void GSmodelSetAnimIndex(_GSmodel*, s32);
void GSmodelSetAnimFrame(_GSmodel*, f32);
void GSmodelStartAnimation(_GSmodel*);
void GSmodelStopAnimation(_GSmodel*);
void GSmodelRemoveNull(_GSmodel*);
u16 GSmodelCenterNull(_GSmodel*);
void* GSmodelGetPart(_GSmodel*, s32);
void* GSparticleCreateGenerator(void*, s32, s32);
void GSparticleSetOffsetRotationInLocal(void*, s32, s32);
void GSparticleSetParticleTextureScaling(void*, s32);
void GSparticleSetTornadoScaling(void*, s32, s32);
void GSparticleAttachGeneratorToGSpart(void*, void*, s32, s32, s32, s32);
void GSparticleSetGeneratorScale(void*, GSvec*, s32, s32);
void GSpartFree(void*);
u8 GSgfxVideoGetVsyncRate();
void GSmodelSetVisibility(_GSmodel*, u8);
void GSparticleSetBankVisibility(void*, u8);
void GSparticleSetGeneratorVisibility(void*, u8);
void GSparticleDestroyAllGenerators(void*, bool);
s32 GSmodelGetAnimType(_GSmodel*);
f32 menuModelGetScale(u8, u16);
void GSmodelSetDontResetPartAnimFlag(_GSmodel*, u8);
}
void* wazaSequenceSysGetSleepParticle();
void* wazaSequenceSysGetIceParticle();
void sequenceAnimEndCallback(_GSmodel*, _GSmodelAnimCBData*);
void wazaSequenceSysPartAnimationStart(_GSmodel*, PartAnimData*);
void _sequenceModelAnimEndedCallback(_GSmodel*, _GSmodelAnimCBData*);
void _eyeAnimEnded(_GSmodel*, _GSmodelAnimCBData*);
void _mouthAnimEnded(_GSmodel*, _GSmodelAnimCBData*);

#endif
