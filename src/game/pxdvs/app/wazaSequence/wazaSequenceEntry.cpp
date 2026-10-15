#include <game/pxdvs/app/wazaSequence/wazaSequenceEntryPrivate.hpp>

extern "C" {
void GSsndFreeEmitter(u32);
void GSsndClose(u32);
void GSlensFlareSetVisible(s32, u32);
void GSlensFlareSetSunPosition(s32, f32 *);
void *GSmodelGetPart(u32, s32);
void GSpartGetTransform(void *, f32 *, f32 *, s32);
void GSpartFree(void *);
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
s32 wazaSequenceSysGetResID();
void loadModel(void *, u32, s32, s32);
void GSresIsUniqueID(u32, s32, s32);
void *GSresGetResource(u32, s32);
void GSmodelGetFrameCount(u32, f32 *, f32 *);
u8 GSgfxVideoGetVsyncRate();
void HSD_ArchiveParse(void *, void *, u32);
u8 GSmodelIsAnimating();
u8 GSmodelHasAnimationEnded(u32);
void PSVECScale(f32 *, f32 *, f32);
u8 GSparticleIsGeneratorAlive(u32);
void GSparticleSetGeneratorPosition(u32, f32 *);
void GSparticleSetGeneratorRotation(u32, f32 *);
void GSparticleSetGeneratorScale(u32, f32 *, s32, s32);
void GSmodelRemoveNull(u32);
void *GSmodelGetBound(u32);
void GSboundGetWorldPosition(void *, f32 *);
void GSboundGetLocalPosition(void *, f32 *);
void GSmodelAttachToGSpart(u32, void *, s32, s32, s32);
void GSmodelSetBoundCheck(u32, u8);
void GSmodelSetRenderLayer(u32, u32, s32 *);
void GSmodelSet60fpsAnimFlag(u32, u8);
u8 GSmodelCanAnimate(u32);
u8 GSmodelCanTexAnimate(u32);
void GSmodelSetTexAnimIndex(u32, s32);
void GSmodelSetTexAnimType(u32, s32);
void GSmodelSetTexAnimRate(u32, f32);
void GSmodelSetTexAnimFrame(u32, f32);
void GSmodelStartTexAnimation(u32);
void GSmodelSetShadowFlags(u32, s32);
void GSmodelSetShadowLight(u32, u32);
void GSmodelSetShadowSurface(u32, s32, u32 *);
u32 GSparticleCreateGenerator(u32, s32, s32);
void GSparticleSetOffsetRotationInLocal(u32, s32, s32);
void GSparticleSetVelocityRotationInLocal(u32, s32);
void GSparticleSetParticleTextureScaling(u32, s32);
void GSparticleSetNodeScaling(u32, s32);
void GSparticleSetRandomVelocityScaling(u32, s32);
void GSparticleSetTornadoScaling(u32, s32, s32);
void GSparticleAttachGeneratorToGSpart(u32, void *, s32, s32, s32, s32);
void battleGridGetNormalisedScale(f32 *);
extern f32 zeroVector[3];
void GSmodelAddNull(u32, f32 *, s32, s32);
void GSmodelDetachFromGSpart(u32, s32);
void GSmodelStopAnimation(u32);
void GSmodelStopTexAnimation(u32);
void GSmodelSetVisibility(u32, s32);
void GSmodelSetPosition(u32, f32 *);
void GSmodelSetRotation(u32, f32 *);
void GSmodelSetScale(u32, f32 *);
bool GSmodelHasTexAnimationEnded(u32);
void PSVECSubtract(f32 *, f32 *, f32 *);
extern f32 unitScaleVector[3];
void GSmodelSetAnimIndex(u32, s16);
void GSmodelSetAnimType(u32, s32);
void GSmodelSetAnimRate(u32, f32);
void GSmodelSetAnimFrame(u32, f32);
void GSmodelStartAnimation(u32);
void GSmodelForceAnimTransformUpdate(u32);
void GSmodelGetPosition(u32, f32 *);
void GSmodelGetRotation(u32, f32 *);
bool GSsndCheckEmitter(u32);
s32 GSsndGetStatus(s32);
u8 GSsndUpdateEmitter(u32, f32 *);
bool GSthreadIsRunning();
u32 GSthreadCreate(s32, s32, s32, s32, s32, void *);
void GSthreadSetArgs(u32, s32, ...);
u32 GSsndCreateEmitterParam(s32, f32 *, f32 *, s32, u8, f32, f32);
u8 GSsndPlay(s32, s32, s32);
void soundOpenPlayME();
extern f32 zeroVector[3];
void cameraSetOffsetPosition(f32 *);
void cameraSetOffsetRotation(f32 *);
extern u32 gCameraShakeModel;
extern u32 gCameraShakeModels[9];
}
class GSgfxLayer;
enum GSgfxLayerPass { GSGFXLAYERPASS_0, GSGFXLAYERPASS_1 };
struct GSeffectBase {
    u8 running;
    u8 reserved1[3];
    u32 field4;
};
class GSeffect : public GSeffectBase {
public:
    GSeffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32);
    virtual void _render(GSgfxLayer *, GSgfxLayerPass);
    virtual void _fastRender();
    virtual ~GSeffect();
    void Stop();
    bool Start();
};
class leafEffect : public GSeffect {
public:
    u8 reserved0c[8];
    f32 sizeScale;                  // 0x14
    u8 reserved18[0x54 - 0x18];
    f32 position[3];                // 0x54
    leafEffect(u8 **, f32);
};
class boneFillEffect : public GSeffect {
public:
    u8 reserved0c[8];
    void *sequence;                 // 0x14
};
class blurEffect : public GSeffect {
public:
    void *model;                    // 0xc
    u8 reserved10[4];
    u8 flag;                        // 0x14
    u8 reserved15[3];
    f32 value;                      // 0x18
};
class envMapEffect : public GSeffect {
public:
    void *model;                    // 0xc
    u32 texture, type;
    f32 value;                      // 0x18
};
class filterEffect : public GSeffect {
public:
    void *target;                   // 0xc
    u8 original[4];
    u8 pe, combine, saved, pad17, modulation;
    u8 color[4];
};
class billboardEffect : public GSeffect {
public:
    u8 reserved[0x1c];
    billboardEffect(u8 **);
};
void *operator new(unsigned long);
void operator delete(void *);
static void _wazaCameraInitShake(WazaSequence *, int);
u32 wazaSequenceSysGetModelShadowLight();
s32 wazaSequenceSysGetModelShadowCount();
u32 *wazaSequenceSysGetModelShadowList();
#define ALIGN32(p) ((u8 *)(((u32)(p) + 0x1f) & ~0x1f))

u32 gSoundThread;

bool EventEntry::Start() {
    SequenceBase *base = waza->sequence;
    ModelSequence *model = (ModelSequence *)(base->type == 1 ? base : 0);
    switch (eventType) {
    case 0:
        if (model != 0) model->Sleep();
        break;
    case 1:
        if (model != 0) model->WakeUp();
        break;
    case 2:
        base->SetFlag(false);
        break;
    case 3:
        base->SetFlag(true);
        break;
    case 4:
        if (model != 0) GSmodelRemoveNull(model->model);
        break;
    case 5:
        if (model != 0) model->Fly(false);
        break;
    case 6:
        if (model != 0) model->Land();
        break;
    case 7:
        if (model != 0) model->Freeze();
        break;
    case 8:
        break;
    case 9:
        if (model != 0) model->UnFreeze();
        break;
    default:
        return false;
    }
    state = 1;
    time = startTime;
    return true;
}

bool EventEntry::Update(f32) {
    return false;
}

bool SoundEntry::Start() {
    f32 pos[3];
    f32 rot[3];
    f32 pan;
    if (flags & 1) {
        if (gSoundThread != 0) {
            return false;
        }
        u32 thread = GSthreadCreate(0x15, 0x4E20, 0x2000, 1, 1, (void *)soundOpenPlayME);
        gSoundThread = thread;
        if (thread != 0) {
            GSthreadSetArgs(thread, 3, handle, 0, 0xFF);
            state = 1;
            time = startTime;
            return true;
        }
    } else if (flags & 2) {
        switch (flags & 0xC) {
        case 4:
            pan = -1.0f;
            break;
        case 12:
            pan = 1.0f;
            break;
        default:
        case 8:
            pan = 0.0f;
            break;
        }
        SequenceBase *seq = waza->sequence;
        seq->GetPosition(pos);
        seq->GetRotation(rot);
        if (fieldA & 1) {
            u8 id = linkId;
            if (id != 0 && id != 0xFF) {
                SequenceEntry *linked = waza->GetEntryFromID(id);
                if (linked->startTime <= startTime && linked->dataType == 2) {
                    u32 model = ((ModelEntry *)linked)->model;
                    if (model != 0) {
                        GSmodelForceAnimTransformUpdate(model);
                        GSmodelGetPosition(model, pos);
                        GSmodelGetRotation(model, rot);
                    }
                }
            }
        }
        f32 vol = volume;
        u8 ch = field36;
        emitter = GSsndCreateEmitterParam(handle, pos, zeroVector, 0x7F, ch, vol, pan);
        if (emitter != 0) {
            state = 1;
            time = startTime;
            return true;
        }
    }
    if (GSsndPlay(handle, 0, 0) != 0) {
        state = 1;
        time = startTime;
        return true;
    }
    return false;
}

bool SoundEntry::Update(f32 dt) {
    f32 pos[3];
    f32 rot[3];
    time += dt;
    if (flags & 1) {
        u32 thread = gSoundThread;
        if (thread != 0) {
            return GSthreadIsRunning();
        }
        return false;
    }
    if (emitter != 0) {
        SequenceBase *seq = waza->sequence;
        seq->GetPosition(pos);
        seq->GetRotation(rot);
        if (fieldA & 1) {
            u8 id = linkId;
            if (id != 0 && id != 0xFF) {
                SequenceEntry *linked = waza->GetEntryFromID(id);
                if (linked->startTime <= startTime && linked->dataType == 2) {
                    u32 model = ((ModelEntry *)linked)->model;
                    if (model != 0) {
                        GSmodelForceAnimTransformUpdate(model);
                        GSmodelGetPosition(model, pos);
                        GSmodelGetRotation(model, rot);
                    }
                }
            }
        }
        if (GSsndUpdateEmitter(emitter, pos) != 0) {
            return GSsndCheckEmitter(emitter);
        }
        return false;
    }
    u32 status = GSsndGetStatus(handle) - 2;
    return status <= 1;
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

// Finds the model part a lens flare follows (a part of a linked model entry or of the owning sequence).
static inline void *GetLensFlarePart(SequenceEntry *entry) {
    void *part;
    if (entry->fieldA & 1) {
        u8 id = entry->linkId;
        if (id != 0 && id != 0xFF) {
            SequenceEntry *linked = entry->waza->GetEntryFromID(id);
            if (linked->dataType == 2) {
                u32 model = ((ModelEntry *)linked)->model;
                if (linked->startTime > entry->startTime) {
                    part = 0;
                } else if (model != 0) {
                    part = GSmodelGetPart(model, entry->field12);
                } else {
                    part = 0;
                }
            } else {
                part = 0;
            }
        } else {
            part = 0;
        }
    } else {
        SequenceBase *seq = entry->waza->sequence;
        seq = seq->type == 1 ? seq : 0;
        if (seq != 0) {
            part = ((ModelSequence *)seq)->GetPart((enumNullJointName)entry->field10);
        } else {
            part = 0;
        }
    }
    return part;
}

bool LensFlareEntry::Update(f32 dt) {
    f32 position[3];
    time += dt;
    if (time - startTime >= sunScale) {
        return false;
    }
    waza->sequence->GetPosition(position);
    void *part = GetLensFlarePart(this);
    if (part != 0) {
        GSpartGetTransform(part, position, 0, 0);
        GSpartFree(part);
    }
    GSlensFlareSetSunPosition(handle, position);
    return true;
}

bool LensFlareEntry::Start() {
    f32 position[3];
    WazaSequence *w = waza;
    SequenceBase *seq = w->sequence;
    if (!(w->flags & 0x2000) && seq->visible == 0) {
        state = 2;
        time = startTime;
        return true;
    }
    seq->GetPosition(position);
    void *part = GetLensFlarePart(this);
    if (part != 0) {
        GSpartGetTransform(part, position, 0, 0);
        GSpartFree(part);
    }
    GSlensFlareSetSunPosition(handle, position);
    GSlensFlareSetVisible(handle, 1);
    state = 1;
    time = startTime;
    return true;
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

static void _wazaCameraInitShake(WazaSequence *waza, int mask) {
    f32 offset[3];
    f32 rot[3];
    if (waza == 0 || waza->field1c != 0) {
        gCameraShakeModel = 0;
        return;
    }
    offset[0] = 0.0f;
    offset[1] = 0.0f;
    offset[2] = 0.0f;
    cameraSetOffsetPosition(offset);
    cameraSetOffsetRotation(offset);
    if ((mask & 9) == 9) {
        gCameraShakeModel = gCameraShakeModels[0];
    } else if ((mask & 0x11) == 0x11) {
        gCameraShakeModel = gCameraShakeModels[1];
    } else if ((mask & 0x21) == 0x21) {
        gCameraShakeModel = gCameraShakeModels[2];
    } else if ((mask & 0xA) == 0xA) {
        gCameraShakeModel = gCameraShakeModels[3];
    } else if ((mask & 0x12) == 0x12) {
        gCameraShakeModel = gCameraShakeModels[4];
    } else if ((mask & 0x22) == 0x22) {
        gCameraShakeModel = gCameraShakeModels[5];
    } else if ((mask & 0xC) == 0xC) {
        gCameraShakeModel = gCameraShakeModels[6];
    } else if ((mask & 0x14) == 0x14) {
        gCameraShakeModel = gCameraShakeModels[7];
    } else if ((mask & 0x24) == 0x24) {
        gCameraShakeModel = gCameraShakeModels[8];
    } else {
        gCameraShakeModel = 0;
    }
    if (gCameraShakeModel != 0) {
        GSmodelSetAnimIndex(gCameraShakeModel, 0);
        GSmodelSetAnimType(gCameraShakeModel, 0);
        GSmodelSetAnimRate(gCameraShakeModel, 0.5f);
        GSmodelSetAnimFrame(gCameraShakeModel, 0.0f);
        GSmodelStartAnimation(gCameraShakeModel);
        void *part = GSmodelGetPart(gCameraShakeModel, 1);
        if (part != 0) {
            GSpartGetTransform(part, offset, rot, 0);
            PSVECScale(offset, offset, 2.5f);
            cameraSetOffsetPosition(offset);
            cameraSetOffsetRotation(rot);
            GSpartFree(part);
        }
    }
}

bool CameraEntry::Update(f32 dt) {
    f32 rotation[3];
    f32 position[3];
    time += dt;
    switch (cameraType) {
    case 0:
        if (time - startTime >= param.f) {
            waza->done = 1;
            return false;
        }
        break;
    case 1: {
        if (gCameraShakeModel == 0) {
            return false;
        }
        if (GSmodelIsAnimating() == 0 || GSmodelHasAnimationEnded(gCameraShakeModel) != 0) {
            return false;
        }
        void *part = GSmodelGetPart(gCameraShakeModel, 1);
        if (part == 0) {
            return false;
        }
        GSpartGetTransform(part, position, rotation, 0);
        PSVECScale(position, position, 2.5f);
        cameraSetOffsetPosition(position);
        cameraSetOffsetRotation(rotation);
        GSpartFree(part);
        break;
    }
    }
    return true;
}

bool ParticleEntry::Start() {
    f32 pos[3];
    f32 rot[3];
    f32 scale[3];
    s32 mode;
    ModelSequence *ms;
    void *part;
    if (bank == 0) {
        return false;
    }
    u32 wazaFlags = waza->flags;
    SequenceBase *base = waza->sequence;
    if (!(wazaFlags & 0x2000) && base->visible == 0) {
        state = 2;
        time = startTime;
        return true;
    }
    switch (field11) {
    case 1:
        mode = 1;
        break;
    case 2:
        mode = 2;
        break;
    case 3:
        mode = 3;
        break;
    case 4:
        mode = 4;
        break;
    case 5:
        mode = 5;
        break;
    case 6:
        mode = 6;
        break;
    case 7:
        mode = 7;
        break;
    default:
        mode = 0;
        break;
    }
    ms = (ModelSequence *)(base->type == 1 ? base : 0);
    if (ms != 0) {
        base->GetPosition(pos);
        base->GetRotation(rot);
        if (fieldA & 1) {
            u8 id = linkId;
            if (id != 0 && id != 0xFF) {
                SequenceEntry *linked = waza->GetEntryFromID(id);
                if (linked->startTime <= startTime && linked->dataType == 2) {
                    u32 linkedModel = ((ModelEntry *)linked)->model;
                    if (linkedModel != 0) {
                        GSmodelForceAnimTransformUpdate(linkedModel);
                        GSmodelGetPosition(linkedModel, pos);
                        GSmodelGetRotation(linkedModel, rot);
                    }
                }
            }
        }
        f32 modelScale = ms->GetModelScale(!(wazaFlags & 0x10000000));
        scale[0] = modelScale;
        scale[1] = modelScale;
        scale[2] = modelScale;
    } else {
        base->GetPosition(pos);
        base->GetRotation(rot);
        base->GetScale(scale);
    }
    if (fieldA & 0x20) {
        scale[0] = scale[1] = scale[2] = 1.0f;
    }
    generator = GSparticleCreateGenerator(bank, field30, field34 & 1);
    field40 = 0;
    if (generator == 0) {
        return false;
    }
    if (field34 & 4) {
        GSparticleSetOffsetRotationInLocal(generator, 1, (field34 >> 4) & 1);
    }
    if (field34 & 8) {
        GSparticleSetVelocityRotationInLocal(generator, 1);
    }
    if (field34 & 0x80) {
        GSparticleSetParticleTextureScaling(generator, 1);
    }
    if (field34 & 0x800) {
        GSparticleSetNodeScaling(generator, 1);
    }
    if (field34 & 0x1000) {
        GSparticleSetRandomVelocityScaling(generator, 1);
    }
    u32 f34 = field34;
    s32 scaleA = (f34 >> 5) & 1;
    s32 scaleB = (f34 >> 9) & 1;
    GSparticleSetTornadoScaling(generator, (f34 >> 8) & 1, (f34 >> 10) & 1);
    if (fieldA & 4) {
        GSparticleSetGeneratorPosition(generator, zeroVector);
        GSparticleSetGeneratorRotation(generator, zeroVector);
        if (fieldA & 8) {
            battleGridGetNormalisedScale(scale);
            GSparticleSetGeneratorScale(generator, scale, scaleA, scaleB);
        } else {
            scale[0] = 1.0f;
            scale[1] = 1.0f;
            scale[2] = 1.0f;
            GSparticleSetGeneratorScale(generator, scale, scaleA, scaleB);
        }
        state = 1;
        time = startTime;
        return true;
    }
    if (fieldA & 1) {
        u8 id = linkId;
        if (id == 0 || id == 0xFF) goto noPart;
        SequenceEntry *linked = waza->GetEntryFromID(id);
        if (linked->dataType != 2) goto noPart;
        u32 linkedModel = ((ModelEntry *)linked)->model;
        if (linked->startTime > startTime) {
            part = 0;
            goto havePart;
        }
        if (linkedModel == 0) goto noPart;
        part = GSmodelGetPart(linkedModel, field12);
        goto havePart;
    } else {
        SequenceBase *s2 = waza->sequence;
        s2 = s2->type == 1 ? s2 : 0;
        if (s2 == 0) goto noPart;
        part = ((ModelSequence *)s2)->GetPart((enumNullJointName)field10);
        goto havePart;
    }
noPart:
    part = 0;
havePart:
    if (part != 0) {
        if (mode != 0) {
            GSparticleAttachGeneratorToGSpart(generator, part, mode, (fieldA >> 1) & 1, 1, (field34 >> 1) & 1);
            field40 = 1;
            switch (mode) {
            case 1:
                GSparticleSetGeneratorRotation(generator, rot);
            case 4:
                GSparticleSetGeneratorScale(generator, scale, scaleA, scaleB);
                break;
            case 2:
                GSparticleSetGeneratorScale(generator, scale, scaleA, scaleB);
            case 5:
                GSparticleSetGeneratorPosition(generator, pos);
                break;
            case 3:
                GSparticleSetGeneratorPosition(generator, pos);
            case 6:
                GSparticleSetGeneratorRotation(generator, rot);
                break;
            case 0:
            case 7:
                break;
            }
        }
        GSpartFree(part);
    } else {
        GSparticleSetGeneratorPosition(generator, pos);
        GSparticleSetGeneratorRotation(generator, rot);
        GSparticleSetGeneratorScale(generator, scale, scaleA, scaleB);
    }
    state = 1;
    time = startTime;
    return true;
}

bool ParticleEntry::Update(f32 dt) {
    f32 position[3];
    f32 rotation[3];
    f32 scale[3];
    time += dt;
    if (GSparticleIsGeneratorAlive(generator) == 0) {
        generator = 0;
        return false;
    }
    SequenceBase *seq = waza->sequence;
    if (seq->type != 1 && !(fieldA & 4) && field40 == 0) {
        seq->GetPosition(position);
        seq->GetRotation(rotation);
        seq->GetScale(scale);
        u32 flags = field34;
        s32 a = (flags >> 5) & 1;
        s32 b = (flags >> 9) & 1;
        GSparticleSetGeneratorPosition(generator, position);
        GSparticleSetGeneratorRotation(generator, rotation);
        GSparticleSetGeneratorScale(generator, scale, a, b);
    }
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

#define XSWAP(a, b) \
    do {            \
        (a) ^= (b); \
        (b) ^= (a); \
        (a) ^= (b); \
    } while (0)

bool EffectEntry::Load(u8 **data) {
    u8 *prev = *data;
    u32 *header;
    s32 *q;
    *data += 0x70;
    header = (u32 *)*data;
    *data += 0xc;
    switch (header[0]) {
    case 0: {
        q = (s32 *)*data;
        s32 count = q[1];
        *data += 0x10;
        u8 *entry = *data;
        for (s32 i = 0; i < count; i++) {
            XSWAP(entry[0], entry[3]);
            XSWAP(entry[1], entry[2]);
            XSWAP(entry[4], entry[7]);
            XSWAP(entry[5], entry[6]);
            entry += 0x10;
        }
        *data += q[1] * 16;
        break;
    }
    case 5:
        q = (s32 *)*data;
        *data += 0x40;
        *data = ALIGN32(*data);
        q[14] = 0;
        if (q[13] != 0) {
            void *a = operator new(0x44);
            if (a != 0) {
                q[14] = (s32)a;
                HSD_ArchiveParse(a, *data, q[13]);
            }
            *data += (q[13] + 0x1f) & ~0x1f;
        }
        break;
    case 6:
        q = (s32 *)*data;
        *data += 0x10;
        *data += q[2] * 16;
        break;
    case 7:
        q = (s32 *)*data;
        *data += 0xc;
        *data += q[0] * 16;
        break;
    case 1:
        q = (s32 *)*data;
        *data += 0x18;
        *data = ALIGN32(*data);
        q[4] = 0;
        if (((SequenceEntryData *)prev)->f6c == 0) {
            q[4] = GSparticleLoad(*data);
        }
        *data += (q[3] + 0x1f) & ~0x1f;
        break;
    case 9:
        q = (s32 *)*data;
        *data += 0x20;
        *data = ALIGN32(*data);
        q[1] = 0;
        if (q[0] != 0) {
            void *a = operator new(0x44);
            if (a != 0) {
                q[1] = (s32)a;
                HSD_ArchiveParse(a, *data, q[0]);
            }
            *data += (q[0] + 0x1f) & ~0x1f;
        }
        q[3] = 0;
        if (q[2] != 0) {
            q[3] = GSparticleLoad(*data);
            *data += (q[2] + 0x1f) & ~0x1f;
        }
        break;
    default:
        return false;
    }
    return true;
}

void EffectEntry::Unload(u8 **data) {
    u32 *header;
    u32 *q;
    *data += 0x70;
    header = (u32 *)*data;
    *data += 0xc;
    switch (header[0]) {
    case 0:
        q = (u32 *)*data;
        *data += 0x10;
        *data += q[1] * 16;
        break;
    case 5:
        q = (u32 *)*data;
        *data += 0x40;
        *data = ALIGN32(*data);
        if (q[14] != 0) {
            operator delete((void *)q[14]);
            q[14] = 0;
        }
        *data += (q[13] + 0x1f) & ~0x1f;
        break;
    case 6:
        q = (u32 *)*data;
        *data += 0x10;
        *data += q[2] * 16;
        break;
    case 7:
        q = (u32 *)*data;
        *data += 0xc;
        *data += q[0] * 16;
        break;
    case 1:
        q = (u32 *)*data;
        *data += 0x18;
        *data = ALIGN32(*data);
        if (q[4] != 0) {
            GSparticleFree(q[4]);
            q[4] = 0;
        }
        *data += (q[3] + 0x1f) & ~0x1f;
        break;
    case 9:
        q = (u32 *)*data;
        *data += 0x20;
        *data = ALIGN32(*data);
        if (q[1] != 0) {
            operator delete((void *)q[1]);
            q[1] = 0;
        }
        *data += (q[0] + 0x1f) & ~0x1f;
        if (q[3] != 0) {
            GSparticleFree(q[3]);
            q[3] = 0;
        }
        *data += (q[2] + 0x1f) & ~0x1f;
        break;
    case 2:
    case 3:
    case 4:
    case 8:
        break;
    }
}

bool EffectEntry::Update(f32 dt) {
    f32 rate;
    time += dt;
    if (effect == 0) {
        return false;
    }
    if (effect->running == 0) {
        return false;
    }
    if (active != 0) {
        if (table == 0 || count == 0) {
            return false;
        }
        f32 zero = 0.0f;
        effectTime += dt;
        if (table[index].time >= zero) {
            while (effectTime >= table[index].time) {
                effectTime -= table[index].time;
                index++;
                if (index >= count) {
                    effect->Stop();
                    return false;
                }
                if (table[index].time < zero) {
                    effectTime = zero;
                    break;
                }
            }
            if (table[index].time > zero) {
                rate = effectTime / table[index].time;
            } else {
                rate = 1.0f;
            }
        } else {
            state = 3;
        }
    } else {
        timeValue += dt;
        rate = 1.0f;
        if (count != 0) {
            state = 3;
        } else if (index != 0) {
            if (timeValue >= effectTime) {
                return false;
            }
            rate = timeValue / effectTime;
        }
    }
    switch (effectType) {
    case 0: {
        filterEffect *fe = (filterEffect *)effect;
        u8 *c = (u8 *)table + index * 16;
        f32 t = rate;
        bool useAlpha = false;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        u8 out[4];
        for (int i = 0; i < 4; i++) {
            f32 a = c[i];
            f32 b = c[i + 4];
            out[i] = (s32)(a + t * (b - a));
        }
        fe->color[0] = out[0];
        fe->color[1] = out[1];
        fe->color[2] = out[2];
        if (fe->modulation == 0 || fe->pe != 0) {
            useAlpha = true;
        }
        fe->color[3] = useAlpha ? out[3] : 255;
        break;
    }
    case 6: {
        f32 *e = (f32 *)((u8 *)table + index * 16);
        f32 a = e[0];
        ((envMapEffect *)effect)->value = a + rate * (e[1] - a);
        break;
    }
    case 7: {
        f32 *e = (f32 *)((u8 *)table + index * 16);
        f32 a = e[0];
        ((blurEffect *)effect)->value = a + rate * (e[1] - a);
        break;
    }
    case 1:
    case 5:
    case 9:
        break;
    case -1:
    default:
        return false;
    }
    return true;
}

bool EffectEntry::Start() {
    SequenceBase *base = waza->sequence;
    ModelSequence *seq = (ModelSequence *)(base->type == 1 ? base : 0);
    void *model = 0;
    f32 scale = 1.0f;
    if (effect == 0) {
        return false;
    }
    if (active != 0) {
        if (table == 0 || count == 0) {
            return false;
        }
        effectTime = 0.0f;
        index = 0;
    } else {
        timeValue = 0.0f;
    }
    u32 wazaFlags = waza->flags;
    if (!(wazaFlags & 0x2000) && base->visible == 0) {
        state = 2;
        time = startTime;
        return true;
    }
    if (seq != 0) {
        model = (void *)seq->model;
        scale = seq->GetModelScale(!(wazaFlags & 0x10000000));
    }
    switch (effectType) {
    case 0: {
        bool useAlpha;
        filterEffect *fe = (filterEffect *)effect;
        if (fe->modulation == 2) {
            fe->target = model;
        }
        if (seq != 0) {
            u8 visible = *((u8 *)seq + 0x60);
            if (fe->modulation == 2) {
                fe->combine = visible;
            }
        }
        u8 *c = (u8 *)table + index * 16;
        useAlpha = false;
        fe->color[0] = c[0];
        fe->color[1] = c[1];
        fe->color[2] = c[2];
        if (fe->modulation == 0 || fe->pe != 0) {
            useAlpha = true;
        }
        fe->color[3] = useAlpha ? c[3] : 255;
        break;
    }
    case 6: {
        envMapEffect *ee = (envMapEffect *)effect;
        if (seq == 0) {
            return false;
        }
        ee->model = model;
        ee->value = *(f32 *)((u8 *)table + index * 16);
        break;
    }
    case 7: {
        blurEffect *be = (blurEffect *)effect;
        if (be->flag == 0) {
            if (seq == 0) {
                return false;
            }
            if (be->flag == 0) {
                be->model = model;
            }
        }
        be->value = *(f32 *)((u8 *)table + index * 16);
        break;
    }
    case 5: {
        void *part;
        leafEffect *le = (leafEffect *)effect;
        f32 pos[3];
        if (fieldA & 1) {
            u8 id = linkId;
            if (id == 0 || id == 0xFF) goto noPart;
            SequenceEntry *linked = waza->GetEntryFromID(id);
            if (linked->dataType != 2) goto noPart;
            u32 linkedModel = ((ModelEntry *)linked)->model;
            if (linked->startTime > startTime) {
                part = 0;
                goto havePart;
            }
            if (linkedModel == 0) goto noPart;
            part = GSmodelGetPart(linkedModel, field12);
            goto havePart;
        } else {
            SequenceBase *s2 = waza->sequence;
            s2 = s2->type == 1 ? s2 : 0;
            if (s2 == 0) goto noPart;
            part = ((ModelSequence *)s2)->GetPart((enumNullJointName)field10);
            goto havePart;
        }
    noPart:
        part = 0;
    havePart:
        if (part != 0) {
            GSpartGetTransform(part, pos, 0, 0);
            GSpartFree(part);
        } else {
            base->GetPosition(pos);
        }
        le->position[0] = pos[0];
        le->position[1] = pos[1];
        le->position[2] = pos[2];
        le->sizeScale = scale;
        break;
    }
    case 1:
        ((boneFillEffect *)effect)->sequence = seq;
        break;
    case 9:
        break;
    case -1:
    default:
        return false;
    }
    if (!effect->Start()) {
        return false;
    }
    state = 1;
    time = startTime;
    return true;
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

EffectEntry::EffectEntry(WazaSequence *waza, u8 **data) : SequenceEntry(SEQENTRY_EFFECT, waza, data) {
    u32 *header;
    effect = 0;
    table = 0;
    effectTime = 0.0f;
    count = 0;
    index = 0;
    active = 0;
    header = (u32 *)*data;
    effectType = header[0];
    effectTime = *(f32 *)&header[1];
    *data += 0xc;
    switch (header[0]) {
    case 0:
        filterEffectLoad(data);
        break;
    case 6:
        envMapEffectLoad(data);
        break;
    case 7:
        blurEffectLoad(data);
        break;
    case 5:
        effect = new leafEffect(data, *(f32 *)&header[1]);
        index = 1;
        count = 0;
        break;
    case 9:
        effect = new billboardEffect(data);
        index = 0;
        count = 0;
        break;
    case 1:
        boneFillEffectLoad(data);
        index = 0;
        count = 0;
        break;
    }
    if (times[field8 - 1] < 0.0f) {
        times[field8 - 1] = *(f32 *)&header[1];
    }
}

EffectEntry::~EffectEntry() {
    if (effect != 0) {
        delete effect;
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
    s32 animIndex;                  // 0x0
    s32 animMode;                   // 0x4
    s32 texAnimIndex;               // 0x8
    s32 texAnimMode;                // 0xC
    s32 linked;                     // 0x10
    s32 field14;                    // 0x14
    s32 flags;                      // 0x18
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

bool ModelEntry::Start() {
    f32 scale[3];
    f32 rot[3];
    f32 pos[3];
    f32 tmp[3];
    s32 mode;
    ModelSequence *ms;
    if (model == 0) {
        return false;
    }
    u32 wazaFlags = waza->flags;
    SequenceBase *base = waza->sequence;
    if (!(wazaFlags & 0x2000) && base->visible == 0) {
        state = 2;
        time = startTime;
        return true;
    }
    switch (field11) {
    case 1:
        mode = 1;
        break;
    case 2:
        mode = 2;
        break;
    case 3:
        mode = 3;
        break;
    case 4:
        mode = 4;
        break;
    case 5:
        mode = 5;
        break;
    case 6:
        mode = 6;
        break;
    case 7:
        mode = 7;
        break;
    default:
        mode = 0;
        break;
    }
    ms = (ModelSequence *)(base->type == 1 ? base : 0);
    if (ms != 0) {
        base->GetPosition(pos);
        base->GetRotation(rot);
        if (fieldA & 1) {
            u8 id = linkId;
            if (id != 0 && id != 0xFF) {
                SequenceEntry *linked = waza->GetEntryFromID(id);
                if (linked->startTime <= startTime && linked->dataType == 2) {
                    u32 linkedModel = ((ModelEntry *)linked)->model;
                    if (linkedModel != 0) {
                        GSmodelForceAnimTransformUpdate(linkedModel);
                        GSmodelGetPosition(linkedModel, pos);
                        GSmodelGetRotation(linkedModel, rot);
                    }
                }
            }
        }
        f32 modelScale = ms->GetModelScale(!(wazaFlags & 0x10000000));
        scale[0] = modelScale;
        scale[1] = modelScale;
        scale[2] = modelScale;
    } else {
        base->GetPosition(pos);
        base->GetRotation(rot);
        base->GetScale(scale);
    }
    if (fieldA & 0x20) {
        scale[0] = scale[1] = scale[2] = 1.0f;
    }
    u32 seqModel = 0;
    field4B = seqModel;
    if (fieldA & 4) {
        if (fieldA & 8) {
            battleGridGetNormalisedScale(scale);
            if (fieldA & 0x10) {
                scale[1] = 1.0f;
            }
            GSmodelSetScale(model, scale);
        }
    } else {
        void *part;
        if (ms != 0) {
            seqModel = ms->model;
        }
        if (mode != 0) {
            if (field4A != 0) {
                part = GSmodelGetPart(model, field44);
                GSmodelSetPosition(model, pos);
                GSmodelSetRotation(model, rot);
                if (mode != 7 && mode != 3 && mode != 5 && mode != 6) {
                    GSmodelSetScale(model, scale);
                }
                if (seqModel != 0 && ms->field58 == 0 && part != 0) {
                    if (flags & 0x10) {
                        void *bound = GSmodelGetBound(seqModel);
                        GSboundGetWorldPosition(bound, tmp);
                        GSmodelSetPosition(model, tmp);
                        GSboundGetLocalPosition(bound, tmp);
                        tmp[0] = -tmp[0];
                        tmp[1] = -tmp[1];
                        tmp[2] = -tmp[2];
                        GSmodelAddNull(seqModel, tmp, 0, 0);
                    }
                    GSmodelAttachToGSpart(seqModel, part, mode, 0, 1);
                    field4B = 1;
                    ms->field58 = 1;
                    GSpartFree(part);
                    switch (mode) {
                    case 1:
                    case 6:
                        GSmodelSetRotation(seqModel, rot);
                        break;
                    case 2:
                    case 5:
                        GSmodelSetPosition(seqModel, pos);
                        break;
                    case 3:
                        GSmodelSetRotation(seqModel, rot);
                        GSmodelSetPosition(seqModel, pos);
                        break;
                    case 0:
                        GSmodelSetRotation(seqModel, rot);
                        GSmodelSetPosition(seqModel, pos);
                        break;
                    case 4:
                    case 7:
                        break;
                    }
                }
            } else {
                if (fieldA & 1) {
                    u8 id = linkId;
                    if (id == 0 || id == 0xFF) goto noPart;
                    SequenceEntry *linked = waza->GetEntryFromID(id);
                    if (linked->dataType != 2) goto noPart;
                    u32 linkedModel = ((ModelEntry *)linked)->model;
                    if (linked->startTime > startTime) {
                        part = 0;
                        goto havePart;
                    }
                    if (linkedModel == 0) goto noPart;
                    part = GSmodelGetPart(linkedModel, field12);
                    goto havePart;
                } else {
                    SequenceBase *s2 = waza->sequence;
                    s2 = s2->type == 1 ? s2 : 0;
                    if (s2 == 0) goto noPart;
                    part = ((ModelSequence *)s2)->GetPart((enumNullJointName)field10);
                    goto havePart;
                }
            noPart:
                part = 0;
            havePart:
                if (part != 0) {
                    GSmodelAttachToGSpart(model, part, mode, (fieldA >> 1) & 1, 1);
                    field4B = 1;
                    switch (mode) {
                    case 4:
                        GSmodelSetScale(model, scale);
                        break;
                    case 1:
                        GSmodelSetScale(model, scale);
                        GSmodelSetRotation(model, rot);
                        break;
                    case 5:
                        GSmodelSetPosition(model, pos);
                        break;
                    case 2:
                        GSmodelSetScale(model, scale);
                        GSmodelSetPosition(model, pos);
                        break;
                    case 6:
                        GSmodelSetRotation(model, rot);
                        break;
                    case 3:
                        GSmodelSetPosition(model, pos);
                        GSmodelSetRotation(model, rot);
                        break;
                    case 0:
                    case 7:
                        break;
                    }
                    GSpartFree(part);
                }
            }
        }
    }
    GSmodelSetVisibility(model, 1);
    GSmodelSetBoundCheck(model, 0);
    if (flags & 1) {
        s32 layers[1] = {4};
        GSmodelSetRenderLayer(model, 1, layers);
    }
    if (flags & 4) {
        GSmodelSet60fpsAnimFlag(model, 1);
    }
    if (animIndex >= 0) {
        if (GSmodelCanAnimate(model)) {
            GSmodelSetAnimIndex(model, animIndex);
            GSmodelSetAnimType(model, animMode);
            GSmodelSetAnimRate(model, 0.5f);
            GSmodelSetAnimFrame(model, 0.0f);
            GSmodelStartAnimation(model);
        } else {
            animIndex = -1;
        }
    }
    if (animIndex != texAnimIndex && texAnimIndex >= 0) {
        if (GSmodelCanTexAnimate(model)) {
            GSmodelSetTexAnimIndex(model, texAnimIndex);
            GSmodelSetTexAnimType(model, texAnimMode);
            GSmodelSetTexAnimRate(model, 0.5f);
            GSmodelSetTexAnimFrame(model, 0.0f);
            GSmodelStartTexAnimation(model);
        } else {
            texAnimIndex = -1;
        }
    }
    if (flags & 0x20) {
        if (wazaSequenceSysGetModelShadowLight() != 0 && wazaSequenceSysGetModelShadowCount() != 0) {
            GSmodelSetShadowFlags(model, 1);
            GSmodelSetShadowLight(model, wazaSequenceSysGetModelShadowLight());
            u32 *list = wazaSequenceSysGetModelShadowList();
            GSmodelSetShadowSurface(model, wazaSequenceSysGetModelShadowCount(), list);
        }
    }
    state = 1;
    time = startTime;
    return true;
}

void ModelEntry::Stop(bool force) {
    ModelSequence *ms;
    u32 seqModel = 0;
    if (state == 1 || (state != 2 && force)) {
        {
            state = 2;
            if (model != 0) {
                ms = (ModelSequence *)waza->sequence;
                ms = ms->type == 1 ? ms : 0;
                if (ms != 0) {
                    seqModel = ms->model;
                }
                GSmodelStopAnimation(model);
                GSmodelStopTexAnimation(model);
                GSmodelSetVisibility(model, 0);
                if (seqModel != 0 && field4A != 0) {
                    f32 position[3];
                    f32 rotation[3];
                    f32 offset[3];
                    GSmodelGetPosition(model, position);
                    GSmodelGetRotation(model, rotation);
                    GSmodelGetPosition(seqModel, offset);
                    PSVECSubtract(offset, position, offset);
                    ms->field58 = 0;
                    if (field4B != 0) {
                        field4B = 0;
                        GSmodelDetachFromGSpart(seqModel, 0);
                    }
                    ms->ResetPosition();
                    ms->ResetRotation();
                    ms->ResetScale();
                    if (flags & 0x10) {
                        GSmodelRemoveNull(seqModel);
                    }
                    if (flags & 8) {
                        GSmodelAddNull(seqModel, offset, 0, 0);
                    }
                }
                if (field4B != 0) {
                    GSmodelDetachFromGSpart(model, 0);
                }
                GSmodelSetPosition(model, zeroVector);
                GSmodelSetRotation(model, zeroVector);
                GSmodelSetScale(model, unitScaleVector);
            }
        }
    }
}

bool ModelEntry::Update(f32 dt) {
    f32 position[3];
    f32 rotation[3];
    f32 scale[3];
    u8 ended;
    time += dt;
    if (model == 0) {
        return false;
    }
    if (state == 3) {
        return true;
    }
    SequenceBase *seq = waza->sequence;
    if (seq->type != 1 && !(fieldA & 4) && field4A == 0 && field4B == 0) {
        seq->GetPosition(position);
        seq->GetRotation(rotation);
        seq->GetScale(scale);
        GSmodelSetPosition(model, position);
        GSmodelSetRotation(model, rotation);
        GSmodelSetScale(model, scale);
    }
    if (animIndex < 0) {
        ended = 1;
    } else {
        switch (animMode) {
        case 1:
            ended = startTime + times[field8 - 1] >= waza->clock;
            break;
        case 0:
        default:
            ended = GSmodelHasAnimationEnded(model);
            break;
        }
    }
    if (animIndex != texAnimIndex && texAnimIndex >= 0) {
        u8 texEnded;
        switch (texAnimMode) {
        case 1:
            texEnded = startTime + times[field8 - 1] >= waza->clock;
            break;
        case 0:
        default:
            texEnded = GSmodelHasTexAnimationEnded(model);
            break;
        }
        u8 both = 0;
        if (ended != 0 && texEnded != 0) {
            both = 1;
        }
        ended = both;
    }
    if (ended != 0) {
        if (flags & 2) {
            state = 3;
            return true;
        }
        return false;
    }
    return true;
}

ModelEntry::ModelEntry(WazaSequence *waza, u8 **data) : SequenceEntry(SEQENTRY_MODEL, waza, data) {
    ModelBlock *b = (ModelBlock *)*data;
    s32 res = wazaSequenceSysGetResID();
    *data += 0x28;
    *data = ALIGN32(*data);
    resource = 0;
    model = 0;
    if (b->archive != 0) {
        loadModel(b->archive, 0x4E20, 0, res);
        GSresIsUniqueID(0x4E20, res, 0);
        u32 loaded = (u32)GSresGetResource(0x4E20, res);
        model = loaded;
        if (loaded != 0) {
            resource = res;
        }
    }
    if (b->size != 0) {
        *data += (b->size + 0x1f) & ~0x1f;
    }
    animIndex = b->animIndex;
    switch (b->animMode) {
    case 0:
        animMode = 0;
        break;
    case 1:
        animMode = 1;
        break;
    }
    texAnimIndex = b->texAnimIndex;
    switch (b->texAnimMode) {
    case 0:
        texAnimMode = 0;
        break;
    case 1:
        texAnimMode = 1;
        break;
    }
    field4A = b->linked != 0;
    field44 = b->field14;
    flags = b->flags;
    if (times[field8 - 1] < 0.00001f) {
        f32 first = 0.0f;
        f32 second = 0.0f;
        if (model != 0) {
            GSmodelGetFrameCount(model, &first, &second);
        }
        f32 frames = first;
        if (frames >= second) {
        } else {
            frames = second;
        }
        times[field8 - 1] = (f32)(s32)frames / (f32)GSgfxVideoGetVsyncRate();
    }
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
    wazaSequenceSysGetResID();
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
