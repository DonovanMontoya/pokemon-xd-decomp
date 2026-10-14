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
    virtual void Dummy2();
    u8 pad04[4];
    s32 type;                       // 0x8
};

class ModelSequence : public SequenceBase {
public:
    void Sleep();
    void WakeUp();
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
    u16 field12;                    // 0x12
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
    u8 pad34[0x18];
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

    GSeffect *effect;               // 0x30
    EffectTableEntry *table;        // 0x34
    u8 pad38[4];
    u8 count;                       // 0x3C
    u8 index;                       // 0x3D
    u8 pad3E[2];
    u8 active;                      // 0x40
};

class WazaSequence {
public:
    SequenceEntry *GetEntryFromID(u8);

    u8 pad00[0x13];
    u8 index;                       // 0x13
    u8 pad14[0xc];
    SequenceEntry **entries;        // 0x20
    SequenceBase *sequence;         // 0x24
};

#endif
