#ifndef WAZA_SEQUENCE_ENTRY_PRIVATE_H
#define WAZA_SEQUENCE_ENTRY_PRIVATE_H

#include <global.h>

struct _GScamera;
class WazaSequence;
class SequenceEntry;
struct GSeffect;

enum enumSequenceEntryDataType {
    SEQENTRY_MAIN = 0,
    SEQENTRY_CAMERA = 1,
    SEQENTRY_MODEL = 2,
    SEQENTRY_EFFECT = 4,
    SEQENTRY_PARTICLE = 3,
    SEQENTRY_SOUND = 5,
    SEQENTRY_EVENT = 6,
    SEQENTRY_LENSFLARE = 7
};

class EntryOwned {
public:
    virtual ~EntryOwned();
};

class SequenceBase {
public:
    virtual ~SequenceBase();
    virtual void Dummy1();
    virtual void GetPosition(f32 *);
    virtual void GetRotation(f32 *);
    virtual void GetScale(f32 *);
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void SetFlag(bool);
    u16 id;                         // 0x4
    u8 visible;                     // 0x6
    u8 failed;                      // 0x7
    s32 type;                       // 0x8
};

enum enumNullJointName { NULL_JOINT_0 };

class ModelSequence : public SequenceBase {
public:
    void Sleep();
    void WakeUp();
    void *GetPart(enumNullJointName);
    f32 GetModelScale(bool) const;
    void Fly(bool);
    void Land();
    void Freeze();
    void UnFreeze();
    void ResetPosition();
    void ResetRotation();
    void ResetScale();
    u8 pad0c[0x58 - 0xc];
    u8 field58;                     // 0x58
    u8 pad59[0x94 - 0x59];
    u32 model;                      // 0x94
};

struct SequenceEntryData {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    f32 times[16];                  // 0x20
    s32 f60;
    s32 f64;
    s32 f68;
    s32 f6c;
};

class SequenceEntry {
public:
    SequenceEntry(enumSequenceEntryDataType, WazaSequence *, u8 **);
    virtual ~SequenceEntry();
    virtual bool Start();
    virtual bool Update(f32);
    virtual void End();
    virtual void Stop(bool);
    virtual void SetRenderCamera(_GScamera *);
    void Link();

    u8 pad04;                       // 0x4
    u8 linkId;                      // 0x5
    u8 startIndex;                  // 0x6
    u8 endIndex;                    // 0x7
    u8 field8;                      // 0x8
    u8 field9;                      // 0x9
    u16 fieldA;                     // 0xA
    s32 dataType;                   // 0xC
    u8 field10;                     // 0x10
    u8 field11;                     // 0x11
    s16 field12;                    // 0x12
    f32 *times;                     // 0x14
    s32 state;                      // 0x18
    f32 startTime;                  // 0x1C
    f32 time;                       // 0x20
    EntryOwned *owned;              // 0x24
    u32 field28;                    // 0x28
    WazaSequence *waza;             // 0x2C
};

class MainSequenceEntry : public SequenceEntry {
public:
    MainSequenceEntry(WazaSequence *, u8 **);
    virtual ~MainSequenceEntry();
};

class EventEntry : public SequenceEntry {
public:
    EventEntry(WazaSequence *, u8 **);
    virtual ~EventEntry();
    virtual bool Start();
    virtual bool Update(f32);
    static bool Load(u8 **);
    static void Unload(u8 **);

    u32 eventType;                  // 0x30
};

class SoundEntry : public SequenceEntry {
public:
    SoundEntry(WazaSequence *, u8 **);
    virtual ~SoundEntry();
    virtual bool Start();
    virtual bool Update(f32);
    virtual void Stop(bool);
    static bool Load(u8 **);
    static void Unload(u8 **);

    u32 handle;                     // 0x30
    u16 flags;                      // 0x34
    u8 field36;                     // 0x36
    f32 volume;                     // 0x38
    u32 emitter;                    // 0x3C
};

class LensFlareEntry : public SequenceEntry {
public:
    LensFlareEntry(WazaSequence *, u8 **);
    virtual ~LensFlareEntry();
    virtual bool Start();
    virtual bool Update(f32);
    virtual void Stop(bool);
    static bool Load(u8 **);
    static void Unload(u8 **);

    s32 handle;                     // 0x30
    f32 sunScale;                   // 0x34
    s32 field38;                    // 0x38
};

class CameraEntry : public SequenceEntry {
public:
    CameraEntry(WazaSequence *, u8 **);
    virtual ~CameraEntry();
    virtual bool Start();
    virtual bool Update(f32);
    virtual void Stop(bool);
    static bool Load(u8 **);
    static void Unload(u8 **);

    s32 cameraType;                 // 0x30
    union {
        f32 f;
        s32 i;
    } param;                        // 0x34
};

struct ParticleBlock {
    u32 f00;
    u32 f04;
    u32 size;                       // 0x8
    u32 handle;                     // 0xC
    u32 f10;
};

class ParticleEntry : public SequenceEntry {
public:
    ParticleEntry(WazaSequence *, u8 **);
    virtual ~ParticleEntry();
    virtual bool Start();
    virtual bool Update(f32);
    virtual void End();
    virtual void Stop(bool);
    virtual void SetRenderCamera(_GScamera *);
    static bool Load(u8 **);
    static void Unload(u8 **);

    s32 field30;                    // 0x30
    s32 field34;                    // 0x34
    u32 bank;                       // 0x38
    u32 generator;                  // 0x3C
    s32 field40;                    // 0x40
};

class ModelEntry : public SequenceEntry {
public:
    ModelEntry(WazaSequence *, u8 **);
    virtual ~ModelEntry();
    virtual bool Start();
    virtual bool Update(f32);
    virtual void Stop(bool);
    virtual void SetRenderCamera(_GScamera *);
    static bool Load(u8 **);
    static void Unload(u8 **);

    u32 resource;                   // 0x30
    s32 animMode;                   // 0x34
    s32 animIndex;                  // 0x38
    s32 texAnimMode;                // 0x3C
    s32 texAnimIndex;               // 0x40
    u32 field44;                    // 0x44
    u16 flags;                      // 0x48
    u8 field4A;                     // 0x4A
    u8 field4B;                     // 0x4B
    u32 model;                      // 0x4C
};

struct EffectTableEntry {
    u32 f00;
    u32 f04;
    f32 time;                       // 0x8
    u32 f0c;
};

class EffectEntry : public SequenceEntry {
public:
    EffectEntry(WazaSequence *, u8 **);
    virtual ~EffectEntry();
    virtual bool Start();
    virtual bool Update(f32);
    virtual void End();
    virtual void Stop(bool);
    static bool Load(u8 **);
    static void Unload(u8 **);

    void boneFillEffectLoad(u8 **);
    void blurEffectLoad(u8 **);
    void envMapEffectLoad(u8 **);
    void filterEffectLoad(u8 **);

    GSeffect *effect;               // 0x30
    union {
        EffectTableEntry *table;    // 0x34
        f32 timeValue;
    };
    f32 effectTime;
    u8 count;                       // 0x3C
    u8 index;                       // 0x3D
    u8 pad3E[2];
    u8 active;                      // 0x40
    u8 effectType;                  // 0x41
};

class WazaSequence {
public:
    SequenceEntry *GetEntryFromID(u8);

    f32 clock;                      // 0x0
    u8 pad04[4];
    u32 flags;                      // 0x8
    u8 pad0C[7];
    u8 index;                       // 0x13
    u8 pad14;
    u8 done;                        // 0x15
    u8 pad16[6];
    u32 field1c;                    // 0x1C
    SequenceEntry **entries;        // 0x20
    SequenceBase *sequence;         // 0x24
};

#endif
