#ifndef APP_WAZA_SEQUENCE_PRIVATE_HPP
#define APP_WAZA_SEQUENCE_PRIVATE_HPP
#include <global.h>
class WazaSequence;
struct _GScamera;
class SequenceEntry {
public:
    virtual ~SequenceEntry();
    virtual bool Start();
    virtual bool Update(f32);
    virtual void End();
    virtual void Stop(bool);
    virtual void SetRenderCamera(_GScamera *);
    void Link();
    u8 id,linkId,startIndex,endIndex;
    u8 field8,field9;u16 fieldA;
    s32 dataType;u8 field10,field11;s16 field12;
    f32 *times;s32 state;f32 startTime,time;
    SequenceEntry *next;u32 field28;WazaSequence *waza;
};
#define ENTRY_CLASS(NAME, SIZE) class NAME : public SequenceEntry { public: NAME(WazaSequence *, u8 **); virtual ~NAME(); static bool Load(u8 **); static void Unload(u8 **); u8 extra[SIZE - 0x30]; };
class MainSequenceEntry : public SequenceEntry { public: MainSequenceEntry(WazaSequence *, u8 **); virtual ~MainSequenceEntry(); };
ENTRY_CLASS(CameraEntry,0x38)
ENTRY_CLASS(ModelEntry,0x50)
ENTRY_CLASS(ParticleEntry,0x44)
ENTRY_CLASS(EffectEntry,0x44)
ENTRY_CLASS(SoundEntry,0x40)
ENTRY_CLASS(EventEntry,0x34)
ENTRY_CLASS(LensFlareEntry,0x3C)
#undef ENTRY_CLASS
class NullSequence {
public:
    u8 pad00[8];s32 type;
    void Add(WazaSequence *);
    void Remove(WazaSequence *);
};
enum GSmodelAnimType { ANIM_TYPE_0, ANIM_TYPE_1 };
class ModelSequence : public NullSequence {
public:
    u8 pad0C[0x44];
    u8 modelSize,animationCount,animationActive,pad53;
    u8 flags,flipped,isPokemon,rare;
    u8 pad58[0x3C];
    u32 model,particleBank;
    void DoDefaultAnimation(GSmodelAnimType,bool);
    void LinkWithWazaSequence(WazaSequence *);
    void DestroyParticles(bool,bool);
    void ModelMotionStart();
};
class WazaSequence {
public:
    f32 time,startOffset;u32 flags;u16 wazaId;u8 kind,failed;
    u16 resId;u8 entryCount,index;u8 active,ended; s8 field16;u8 stopped;
    f32 distortion;u32 cameraResource;
    SequenceEntry *entries;NullSequence *sequence;WazaSequence *next,*previous;
    WazaSequence(NullSequence *,u16,u8,u8);
    ~WazaSequence();
    bool LoadData(u8 *);
    s32 IsImpactPoint(u8);
    SequenceEntry *GetEntryFromID(u8);
    bool Update(f32);
    void ApplyStop();
    void Start(bool);
    void SetRenderCamera(_GScamera *);
    static s32 GetNumVariations(u16,u16);
    static void Unload(u8 *);
    static bool Load(u8 *,unsigned long,unsigned long);
};
struct GSgfxLayer {
    GSgfxLayer *next;u8 pad04[0x28];s32 kind;
    void SetDistortionParams(f32 (*)[3],s8);
};
struct WazaResource {u32 group,id;};
struct WazaExtEntry {u8 variant,pad;u16 wazaId;u16 res[3];};
extern WazaSequence *g_LastStartedWaza;
extern u8 g_EnableModelLayerChange;
extern WazaResource waza_resource_data[];
extern u16 waza_generic_wzx_data[];
extern u32 waza_generic_wzx_data_number,waza_wzx_data_number,waza_ext_wzx_data_number;
extern u16 waza_wzx_data[][3];
extern WazaExtEntry waza_ext_wzx_data[];
u16 wazaSequenceSysGetResourceID(ModelSequence *,u16,u16,u8);
u32 wazaSequenceSysLoadResource(unsigned long,unsigned long);
void wazaSequenceSysFreeWazaResource(WazaSequence *);
void wazaSequenceSysApplyStop();
void wazaSequenceSysResetAnimationExcept(ModelSequence *);
f32 wazaSequenceSysGetWazaTime(ModelSequence *,WazaSequence *,u8);
f32 wazaSequenceSysNullGetWazaTime(WazaSequence *,u8);
extern "C" {
u8 wazaSequenceSysIsValidWaza(WazaSequence *);
s32 wazaSequenceSysGetResID();
GSgfxLayer *GSgfxLayerGetLayerList();
void GSmodelLinkToGSparticleBank(u32,u32);
void GSmodelSetRenderLayer(u32,u32,s32 *);
void GSresFreeResource(u32,u32);
void battleCameraStartWaza(WazaSequence *);
void battleGridHideModelsExcept(ModelSequence *);
void loadCamera(void *,u32,u32);
void GSresIsUniqueID(u32,u32,u8);
u32 GSresGetResource(u32,u32);
void HSD_ArchiveParse(void *,u8 *,u32);
}
struct WazaSequenceData {
    u16 distortion;u8 index,pad03;u32 entryCount,flags;s8 fieldC;u8 pad0D[3];
    s32 version;u32 cameraSize,pad18;void *camera;
};
typedef char WazaSequenceSizeCheck[(sizeof(WazaSequence)==0x30)?1:-1];
typedef char SequenceEntrySizeCheck[(sizeof(SequenceEntry)==0x30)?1:-1];
typedef char WazaSequenceDataSizeCheck[(sizeof(WazaSequenceData)==0x20)?1:-1];
#endif
