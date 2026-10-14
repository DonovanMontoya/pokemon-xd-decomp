#include <game/pxdvs/app/wazaSequence/wazaSequenceEntryPrivate.hpp>

extern "C" {
void GSsndFreeEmitter(u32);
void GSsndClose(u32);
void GSlensFlareSetVisible(s32, u32);
s32 GSlensFlareLoad(void *);
void GSlensFlareFree(s32);
void GSlogWrite(const char *, ...);
void GSparticleStopGenerator(u32);
void GSparticleBankSetCamera(u32, _GScamera *);
void GSparticleDestroyGenerator(u32, u32);
void GSparticleDestroyAllGenerators(u32, u32);
u32 GSparticleLoad(void *);
void GSparticleFree(u32);
void GSmodelSetRenderCamera(u32, _GScamera *);
void GSresFreeResource(u32, u32);
void GSmodelStopAnimation(u32);
void wazaSequenceSysGetResID(u8 **);
void HSD_ArchiveParse(void *, void *, u32);
void cameraSetOffsetPosition(f32 *);
void cameraSetOffsetRotation(f32 *);
extern u32 gCameraShakeModel;
}
struct GSeffect {
    void Stop();
};
void *operator new(unsigned long);
void operator delete(void *);
static void _wazaCameraInitShake(WazaSequence *, s32);
#define ALIGN32(p) ((u8 *)(((u32)(p) + 0x1f) & ~0x1f))

u32 gSoundThread;

bool EventEntry::Update(f32) {
    return false;
}

void SoundEntry::Stop(bool force) {
    if (state != 2) {
        if (force || state == 1) {
            state = 2;
            if (flags & 1) {
                gSoundThread = 0;
            } else if (emitter != 0) {
                GSsndFreeEmitter(emitter);
                emitter = 0;
            }
            GSsndClose(handle);
        }
    }
}

void SequenceEntry::Stop(bool force) {
    if (state != 2) {
        if (force || state == 1) {
            state = 2;
        }
    }
}

void SequenceEntry::End() {
}

bool SequenceEntry::Update(f32 dt) {
    time += dt;
    return true;
}

bool SequenceEntry::Start() {
    state = 1;
    time = startTime;
    return true;
}

void SequenceEntry::SetRenderCamera(_GScamera *) {
}

SequenceEntry::~SequenceEntry() {
    if (owned != 0) {
        delete owned;
    }
}

SequenceEntry::SequenceEntry(enumSequenceEntryDataType type, WazaSequence *w, u8 **data) {
    SequenceEntryData *d;
    dataType = type;
    waza = w;
    d = (SequenceEntryData *)*data;
    field9 = d->f6c;
    pad04 = d->f00;
    if (d->f10 >= 0) {
        linkId = d->f10;
    } else {
        linkId = 0xFF;
    }
    if (d->f14 >= 0) {
        startIndex = d->f14;
    } else {
        startIndex = 0;
    }
    if (d->f18 >= 0) {
        endIndex = d->f18;
    } else {
        endIndex = 0;
    }
    field8 = d->f1c;
    fieldA = d->f60;
    field12 = d->f64;
    field10 = d->f08;
    field11 = d->f0c;
    times = d->times;
    owned = 0;
    field28 = 0;
    time = 0.0f;
    startTime = 0.0f;
    state = 0;
    *data += 0x70;
}

SoundEntry::~SoundEntry() {
}

SoundEntry::SoundEntry(WazaSequence *waza, u8 **data) : SequenceEntry(SEQENTRY_SOUND, waza, data) {
    SequenceEntryData *d = (SequenceEntryData *)*data;
    emitter = 0;
    flags = d->f08;
    field36 = d->f10;
    volume = *(f32 *)&d->f0c;
    handle = d->f00;
    *data += 0x14;
}

void SoundEntry::Unload(u8 **data) {
    *data += 0x70;
    *data += 0x14;
}

bool SoundEntry::Load(u8 **data) {
    *data += 0x70;
    *data += 0x14;
    return true;
}

EventEntry::~EventEntry() {
}

EventEntry::EventEntry(WazaSequence *waza, u8 **data) : SequenceEntry(SEQENTRY_EVENT, waza, data) {
    eventType = *(u32 *)*data;
    *data += 8;
}

void EventEntry::Unload(u8 **data) {
    *data += 0x70;
    *data += 8;
}

bool EventEntry::Load(u8 **data) {
    *data += 0x70;
    *data += 8;
    return true;
}

MainSequenceEntry::~MainSequenceEntry() {
}

MainSequenceEntry::MainSequenceEntry(WazaSequence *waza, u8 **data) : SequenceEntry(SEQENTRY_MAIN, waza, data) {
}


void ParticleEntry::End() {
    if (generator != 0) {
        GSparticleStopGenerator(generator);
    }
}

void ParticleEntry::Stop(bool force) {
    if (state != 2) {
        if (force || state == 1) {
            state = 2;
            if (generator != 0) {
                GSparticleDestroyGenerator(generator, 1);
            }
            generator = 0;
        }
    }
}

void ParticleEntry::SetRenderCamera(_GScamera *camera) {
    if (bank != 0) {
        GSparticleBankSetCamera(bank, camera);
    }
}

void ModelEntry::SetRenderCamera(_GScamera *camera) {
    if (model != 0) {
        GSmodelSetRenderCamera(model, camera);
    }
}

void LensFlareEntry::Stop(bool) {
    GSlensFlareSetVisible(handle, 0);
}

LensFlareEntry::~LensFlareEntry() {
    GSlensFlareSetVisible(handle, 0);
    GSlensFlareFree(handle);
}

LensFlareEntry::LensFlareEntry(WazaSequence *waza, u8 **data) : SequenceEntry(SEQENTRY_LENSFLARE, waza, data) {
    SequenceEntryData *d;
    handle = 0;
    d = (SequenceEntryData *)*data;
    sunScale = *(f32 *)&d->f0c;
    field38 = d->f08;
    *data += 0x14;
    *data = ALIGN32(*data);
    handle = GSlensFlareLoad(*data);
    *data += (d->f00 + 0x1f) & ~0x1f;
    GSlensFlareSetVisible(handle, 0);
}

void LensFlareEntry::Unload(u8 **data) {
    u8 *p;
    *data += 0x70;
    p = *data;
    *data += 0x14;
    *data = ALIGN32(*data);
    *data += (*(u32 *)p + 0x1f) & ~0x1f;
}

bool LensFlareEntry::Load(u8 **data) {
    u8 *p;
    *data += 0x70;
    p = *data;
    *data += 0x14;
    *data = ALIGN32(*data);
    *data += (*(u32 *)p + 0x1f) & ~0x1f;
    return true;
}

void CameraEntry::Stop(bool force) {
    if (state != 2) {
        if (force || state == 1) {
            state = 2;
            switch (cameraType) {
            case 0:
                break;
            case 1: {
                f32 zero[3];
                zero[0] = 0.0f;
                zero[1] = 0.0f;
                zero[2] = 0.0f;
                cameraSetOffsetPosition(zero);
                cameraSetOffsetRotation(zero);
                if (gCameraShakeModel != 0) {
                    GSmodelStopAnimation(gCameraShakeModel);
                    gCameraShakeModel = 0;
                }
                break;
            }
            case 2:
            case 3:
                break;
            }
        }
    }
}

bool CameraEntry::Start() {
    switch (cameraType) {
    case 0:
    case 2:
    case 3:
        break;
    case 1:
        _wazaCameraInitShake(waza, param.i);
        break;
    default:
        return false;
    }
    state = 1;
    time = startTime;
    return true;
}

CameraEntry::~CameraEntry() {
}

CameraEntry::CameraEntry(WazaSequence *w, u8 **data) : SequenceEntry(SEQENTRY_CAMERA, w, data) {
    u32 *p = (u32 *)*data;
    *data += 0xc;
    cameraType = p[0];
    switch (cameraType) {
    case 0:
        param.f = *(f32 *)&p[1];
        break;
    case 1:
        param.i = p[1];
        break;
    case 2:
        param.f = *(f32 *)&p[1];
        break;
    case 3:
        *data += p[1] * 8;
        cameraType = 0;
        param.f = 0.0f;
        break;
    }
}

void CameraEntry::Unload(u8 **data) {
    u32 *p;
    *data += 0x70;
    p = (u32 *)*data;
    *data += 0xc;
    switch (p[0]) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        *data += p[1] * 8;
        break;
    }
}

bool CameraEntry::Load(u8 **data) {
    u32 *p;
    *data += 0x70;
    p = (u32 *)*data;
    *data += 0xc;
    switch (p[0]) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        *data += p[1] * 8;
        break;
    }
    return true;
}

bool ParticleEntry::Load(u8 **data) {
    ParticleBlock *b;
    u8 *prev = *data;
    *data += 0x70;
    b = (ParticleBlock *)*data;
    *data += 0x14;
    *data = ALIGN32(*data);
    b->handle = 0;
    if (((SequenceEntryData *)prev)->f6c == 0) {
        b->handle = GSparticleLoad(*data);
    }
    *data += (b->size + 0x1f) & ~0x1f;
    return true;
}

void ParticleEntry::Unload(u8 **data) {
    ParticleBlock *b;
    *data += 0x70;
    b = (ParticleBlock *)*data;
    *data += 0x14;
    *data = ALIGN32(*data);
    if (b->handle != 0) {
        GSparticleFree(b->handle);
        b->handle = 0;
    }
    *data += (b->size + 0x1f) & ~0x1f;
}

void EffectEntry::End() {
    f32 zero;
    if (active == 0) {
        return;
    }
    if (table == 0) {
        return;
    }
    if (count != 0) {
        zero = 0.0f;
        while (table[index].time < zero) {
            index++;
            if (index >= count) {
                break;
            }
        }
    }
}

void EffectEntry::Stop(bool force) {
    if (state != 2) {
        if (force || state == 1) {
            state = 2;
            if (effect != 0) {
                effect->Stop();
            }
        }
    }
}

struct ModelBlock {
    u8 pad00[0x1c];
    s32 size;                       // 0x1C
    void *archive;                  // 0x20
    u8 pad24[4];
};

ParticleEntry::~ParticleEntry() {
    if (field9 == 0) {
        if (bank != 0) {
            GSparticleDestroyAllGenerators(bank, 1);
        }
    }
    generator = 0;
    bank = 0;
}

ParticleEntry::ParticleEntry(WazaSequence *waza, u8 **data) : SequenceEntry(SEQENTRY_PARTICLE, waza, data) {
    ParticleBlock *b;
    generator = 0;
    b = (ParticleBlock *)*data;
    *data += 0x14;
    *data = ALIGN32(*data);
    *data += (b->size + 0x1f) & ~0x1f;
    if (field9 != 0) {
        SequenceEntry *e = this->waza->GetEntryFromID(field9);
        if (e != 0) {
            bank = ((ParticleEntry *)e)->bank;
        } else {
            GSlogWrite("particle waza entry not found");
            bank = 0;
        }
    } else {
        bank = b->handle;
    }
    field30 = b->f00;
    field34 = b->f04;
    generator = 0;
}

ModelEntry::~ModelEntry() {
    if (resource != 0) {
        GSresFreeResource(0x4E20, resource);
    }
}

void ModelEntry::Unload(u8 **data) {
    ModelBlock *b;
    *data += 0x70;
    b = (ModelBlock *)*data;
    *data += 0x28;
    *data = ALIGN32(*data);
    if (b->archive != 0) {
        operator delete(b->archive);
        b->archive = 0;
    }
    if (b->size != 0) {
        *data += (b->size + 0x1f) & ~0x1f;
    }
}

bool ModelEntry::Load(u8 **data) {
    ModelBlock *b;
    wazaSequenceSysGetResID(data);
    *data += 0x70;
    b = (ModelBlock *)*data;
    *data += 0x28;
    *data = ALIGN32(*data);
    b->archive = 0;
    if (b->size != 0) {
        void *a = operator new(0x44);
        if (a != 0) {
            b->archive = a;
            HSD_ArchiveParse(a, *data, b->size);
        }
        *data += (b->size + 0x1f) & ~0x1f;
    }
    return true;
}
