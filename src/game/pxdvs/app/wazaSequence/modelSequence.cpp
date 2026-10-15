#include <game/pxdvs/app/wazaSequence/modelSequence.hpp>

extern "C" f32 GSmodelGetAnimFrame(_GSmodel*);


struct PkxEntry {
    u32 group;
    u32 resource;
};

struct RarePkxEntry {
    u16 id;
    u32 group;
    u32 resource;
};

extern "C" {
extern PkxEntry trainer_pkx_data[];
extern u32 trainer_pkx_data_number;
extern PkxEntry pokemon_pkx_data[];
extern u32 pokemon_pkx_data_number;
extern PkxEntry unknown_pokemon_pkx_data[];
extern u32 unknown_pokemon_pkx_data_number;
extern PkxEntry deoxys_pokemon_pkx_data[];
extern u32 deoxys_pokemon_pkx_data_number;
extern PkxEntry rare_deoxys_pokemon_pkx_data[];
extern u32 rare_deoxys_pokemon_pkx_data_number;
extern RarePkxEntry rare_pokemon_pkx_data[];
extern u32 rare_pokemon_pkx_data_number;
u8 pachiruEffectCreate(void*, _GSmodel*, u32);
void GSmodelEnableColorSwap(_GSmodel*, u8*);
void GSmodelEnableModulation(_GSmodel*, u8*);
}

u32 wazaSequenceSysLoadResource(unsigned long, unsigned long);

#define MODELSEQ_ZERO_INIT(POKE)       \
    field3C = 0;                      \
    rnd = 0;                          \
    resourceGroup = 0;                \
    field46 = 0;                      \
    talkCount = 0;                    \
    field4A = 0;                      \
    animState = 0;                    \
    modelSize = 0;                    \
    field51 = 0;                      \
    wazaIndex = 0;                    \
    field53 = 0;                      \
    flags = 0;                        \
    flipped = 0;                      \
    isPokemon = POKE;                 \
    rare = 0;                         \
    noSync = 0;                       \
    field5C = 0;                      \
    field5D = 0;                      \
    colorSwap = 0;                    \
    modulation = 0;                   \
    modulationApplied = 0;            \
    lookEnabled = 0;                  \
    field62 = 0;                      \
    field64 = 0;                      \
    lookVec.param1 = 0.0f;            \
    lookVec.param2 = 0.0f;            \
    lookVec.param3 = 0.0f;            \
    lookTarget = 0;                   \
    lookSource = 0;                   \
    field80 = 0;                      \
    sleepAnim = 0;                    \
    wakeAnim = 0;                     \
    field8C = 0;                      \
    talkAnim = 0;                     \
    model = 0;                        \
    particleBank = 0;                 \
    records = 0;                      \
    fieldA8 = 0;                      \
    fieldAC = 0;                      \
    fieldB0 = 0;                      \
    iceGenerator = 0;                 \
    sleepGenerator = 0;               \
    type = 1;                         \
    fieldA4 = 0;                      \
    fieldA0 = 0;


ModelSequence::ModelSequence(unsigned short modelId) {
    MODELSEQ_ZERO_INIT(0)
    if (modelId == 0 || modelId >= trainer_pkx_data_number) {
        failed = 1;
        return;
    }
    u32 group = trainer_pkx_data[modelId].group;
    u32 resource = trainer_pkx_data[modelId].resource;
    if (group == 0 || resource == 0) {
        group = trainer_pkx_data[1].group;
        resource = trainer_pkx_data[1].resource;
        if (group == 0 || resource == 0) {
            failed = 1;
            return;
        }
    }
    u8* data = (u8*)wazaSequenceSysLoadResource(group, resource);
    resourceGroup = group;
    if (data == 0) {
        failed = 1;
        return;
    }
    id = modelId;
    if (!LoadData(data)) {
        FreeData();
        failed = 1;
    }
}

ModelSequence::ModelSequence(unsigned short modelId, unsigned long seed, bool isRare) {
    MODELSEQ_ZERO_INIT(1)
    u32 group;
    u32 resource;
    u8 rareVariant = 0;
    if (modelId == 0 || modelId >= pokemon_pkx_data_number) {
        failed = 1;
        return;
    }
    if (modelId == 0xc9) {
        seed %= unknown_pokemon_pkx_data_number;
        group = unknown_pokemon_pkx_data[seed].group;
        resource = unknown_pokemon_pkx_data[seed].resource;
    } else if (modelId == 0x19a) {
        seed %= deoxys_pokemon_pkx_data_number;
        group = deoxys_pokemon_pkx_data[seed].group;
        resource = deoxys_pokemon_pkx_data[seed].resource;
    } else {
        group = pokemon_pkx_data[modelId].group;
        resource = pokemon_pkx_data[modelId].resource;
    }
    if (group == 0 || resource == 0) {
        failed = 1;
        return;
    }
    if (isRare) {
        u32 rareGroup = 0;
        u32 rareResource = 0;
        if (modelId == 0x19a) {
            seed %= rare_deoxys_pokemon_pkx_data_number;
            group = rare_deoxys_pokemon_pkx_data[seed].group;
            resource = rare_deoxys_pokemon_pkx_data[seed].resource;
        } else {
            for (u32 i = 0; i < rare_pokemon_pkx_data_number; i++) {
                if (modelId == rare_pokemon_pkx_data[i].id) {
                    rareGroup = rare_pokemon_pkx_data[i].group;
                    rareResource = rare_pokemon_pkx_data[i].resource;
                    break;
                }
            }
        }
        if (rareGroup != 0 && rareResource != 0) {
            group = rareGroup;
            resource = rareResource;
            rareVariant = 1;
        }
    }
    u8* data = (u8*)wazaSequenceSysLoadResource(group, resource);
    resourceGroup = group;
    if (data == 0) {
        failed = 1;
        return;
    }
    id = modelId;
    rare = isRare;
    rnd = seed;
    if (!LoadData(data)) {
        FreeData();
        failed = 1;
        return;
    }
    if (isRare && !rareVariant && !modulationApplied) {
        s32* swap = (s32*)field80;
        _GSmodel* m = model;
        u8 color[4];
        color[0] = swap[0];
        color[1] = swap[1];
        color[2] = swap[2];
        color[3] = swap[3];
        if (colorSwap) {
            GSmodelEnableColorSwap(m, color);
        }
        if (modulation) {
            ((u8*)swap)[0x13] = 0xff;
            GSmodelEnableModulation(m, (u8*)swap + 0x10);
        }
        modulationApplied = 1;
    }
    if (modelId == 0x134) {
        pachiruEffectCreate(&fieldA0, model, seed);
    }
}

ModelSequence::~ModelSequence() {
    FreeAllWaza();
    FreeData();
}

void ModelSequence::Talk() {
    PartAnimData* anim = talkAnim;
    if (*(u8*)anim != 0 && !(flags & 0x40)) {
        wazaSequenceSysPartAnimationStart(model, anim);
        flags |= 0x40;
    }
}

void ModelSequence::WakeUp() {
    if (flags & 2) {
        if (*(u8*)wakeAnim != 0 && animState == 2) {
            animState = 1;
            GSmodelSetDontResetPartAnimFlag(model, 0);
            wazaSequenceSysPartAnimationStart(model, wakeAnim);
        }
        flags ^= 2;
        if (sleepGenerator != 0) {
            GSparticleDestroyGenerator(sleepGenerator, 1);
            sleepGenerator = 0;
        }
    }
}

static inline s32 GetFirstAnimation(ModelRecord* record) {
    ModelAnimEntry* entry = record->entries;
    for (s32 i = 0; i < record->count; i++, entry++) {
        if (entry->kind != 0) {
            return entry->anim;
        }
    }
    return 0;
}

static inline s32 GetDefaultAnimation(ModelSequence* seq) {
    ModelRecord* base = seq->records;
    ModelRecord* record = base;
    if ((seq->flags & 1) && seq->field51 > 0x10) {
        record = &base[16];
        if (record->entries[0].kind == 0) {
            record = base;
        }
    }
    return GetFirstAnimation(record);
}

inline void ModelSequence::PlayDefaultAnimation(GSmodelAnimType type, bool force) {
    if (!(flags & 8) && !(flags & 4)) {
        GSmodelSetAnimEndedCallback(model, sequenceAnimEndCallback, this);
        if (!(flags & 2)) {
            animState = 0;
            GSmodelLinkTexAnimToAnim(model, 1);
        }
        s32 anim = GetDefaultAnimation(this);
        s32 current;
        GSmodelGetAnimIndex(model, &current, 0);
        GSmodelSetAnimType(model, type);
        GSmodelSetAnimRate(model, 0.5f);
        if (anim != current || force || GSmodelHasAnimationEnded(model)) {
            GSmodelSetAnimIndex(model, anim);
            GSmodelSetAnimFrame(model, 0.0f);
        }
        if (force) {
            wazaIndex = 0;
            field53 = 0;
        }
        GSmodelStartAnimation(model);
    }
}

static inline f32 SizeScaleOf(const ModelSequence* seq) {
    switch (seq->modelSize) {
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

f32 ModelSequence::GetModelScale(bool fixed) const {
    f32 scale = SizeScaleOf(this);
    if (!fixed) {
        return menuModelGetScale(isPokemon, id);
    }
    return scale;
}

void* ModelSequence::GetPart(enumNullJointName name) {
    ModelRecord* record = &records[wazaIndex];
    s32 joint;
    if (name == NULL_JOINT_16) {
        joint = GSmodelCenterNull(model);
        if (joint == 0) {
            joint = record->joints[2];
        }
    } else {
        joint = record->joints[name];
    }
    if (joint >= 0) {
        return GSmodelGetPart(model, joint);
    }
    return 0;
}

void ModelSequence::LinkWithWazaSequence(WazaSequence* waza) {
    if (waza == 0) {
        wazaIndex = 0;
        field53 = 0;
        talkCount = 0;
        field5D = 0;
        if (lookSource != 0 && lookSource->lookEnabled != 0) {
            lookSource->lookTarget = 0;
        }
    } else {
        wazaIndex = waza->index;
        field53 = 0;
        f32 seconds = waza->time;
        talkCount = (u32)(seconds * GSgfxVideoGetVsyncRate());
        field5D = 0;
    }
}

void ModelSequence::Land() {
    if (flags & 1) {
        flags &= 0xFE;
        GSmodelRemoveNull(model);
        PlayDefaultAnimation(GSMODEL_ANIM_TYPE_1, false);
    }
}

void ModelSequence::Fly(bool) {
    if (!(flags & 1)) {
        flags |= 1;
        PlayDefaultAnimation(GSMODEL_ANIM_TYPE_1, false);
    }
}

void ModelSequence::UnFreeze() {
    if (flags & 4) {
        flags ^= 4;
        PlayDefaultAnimation(GSMODEL_ANIM_TYPE_1, false);
        if (iceGenerator != 0) {
            GSparticleDestroyGenerator(iceGenerator, 1);
            iceGenerator = 0;
        }
    }
}

void ModelSequence::Freeze() {
    if (!(flags & 4)) {
        flags |= 4;
        GSmodelStopAnimation(model);
    }
    if (iceGenerator == 0) {
        void* particle = wazaSequenceSysGetIceParticle();
        if (particle != 0) {
            iceGenerator = GSparticleCreateGenerator(particle, 0, 0);
            if (iceGenerator != 0) {
                void* part = GetPart(NULL_JOINT_16);
                if (part != 0) {
                    f32 s = GetSizeScale();
                    GSvec v;
                    v.param1 = s;
                    v.param2 = s;
                    v.param3 = s;
                    GSparticleSetOffsetRotationInLocal(iceGenerator, 1, 0);
                    GSparticleSetParticleTextureScaling(iceGenerator, 1);
                    GSparticleSetTornadoScaling(iceGenerator, 0, 0);
                    GSparticleAttachGeneratorToGSpart(iceGenerator, part, 1, 0, 1, 0);
                    GSparticleSetGeneratorRotation(iceGenerator, &rotation);
                    GSparticleSetGeneratorScale(iceGenerator, &v, 1, 0);
                    GSpartFree(part);
                }
            }
        }
    }
}

void ModelSequence::Sleep() {
    if (!(flags & 2)) {
        if (*(u8*)sleepAnim != 0 && animState != 2) {
            animState = 2;
            GSmodelSetDontResetPartAnimFlag(model, 1);
            wazaSequenceSysPartAnimationStart(model, sleepAnim);
        }
        flags |= 2;
    }
    if (sleepGenerator == 0) {
        void* particle = wazaSequenceSysGetSleepParticle();
        if (particle != 0) {
            sleepGenerator = GSparticleCreateGenerator(particle, 0, 0);
            if (sleepGenerator != 0) {
                s32 joint = *(s32*)((u8*)records + wazaIndex * 0xd0 + 0x50);
                void* part;
                if (joint >= 0) {
                    part = GSmodelGetPart(model, joint);
                } else {
                    part = 0;
                }
                if (part != 0) {
                    f32 s = GetSizeScale();
                    GSvec v;
                    v.param1 = s;
                    v.param2 = s;
                    v.param3 = s;
                    GSparticleSetOffsetRotationInLocal(sleepGenerator, 1, 0);
                    GSparticleSetParticleTextureScaling(sleepGenerator, 1);
                    GSparticleSetTornadoScaling(sleepGenerator, 0, 0);
                    GSparticleAttachGeneratorToGSpart(sleepGenerator, part, 1, 0, 1, 0);
                    GSparticleSetGeneratorRotation(sleepGenerator, &rotation);
                    GSparticleSetGeneratorScale(sleepGenerator, &v, 1, 0);
                    GSpartFree(part);
                }
            }
        }
    }
}

extern "C" {
void GSpartUnregisterAnimMix(void*, s32);
void GSmodelDisableColorSwap(_GSmodel*);
void GSmodelDisableModulation(_GSmodel*);
void pachiruEffectFree(void*);
void GSmemFree(void*);
void GSresFreeResource(u32, void*);
}
void wazaSequenceSysFreeSequenceResource(ModelSequence*);

void ModelSequence::FreeData() {
    if (lookSource != 0 && lookSource->lookEnabled != 0) {
        lookSource->lookTarget = 0;
    }
    if (lookTarget != 0) {
        lookTarget->lookSource = 0;
    }
    if (lookEnabled != 0 && model != 0 && isPokemon == 0 && field46 != 0) {
        void* part = GSmodelGetPart(model, field46);
        if (part != 0) {
            GSpartUnregisterAnimMix(part, 2);
            lookEnabled = 0;
            lookVec.param1 = 0.0f;
            lookVec.param2 = 0.0f;
            lookVec.param3 = 0.0f;
            GSpartFree(part);
        }
    }
    if (modulationApplied != 0) {
        if (modulationApplied != 0) {
            _GSmodel* m = model;
            if (m != 0) {
                if (colorSwap != 0) {
                    GSmodelDisableColorSwap(m);
                }
                if (modulation != 0) {
                    GSmodelDisableModulation(m);
                }
            }
            modulationApplied = 0;
        }
    }
    if (model != 0) {
        GSmodelSetAnimEndedCallback(model, 0, 0);
    }
    SetVisibility(false);
    if (particleBank != 0) {
        if (particleBank != 0) {
            GSparticleDestroyAllGenerators(particleBank, 1);
        }
        GSparticleFree(particleBank);
        particleBank = 0;
    }
    WakeUp();
    UnFreeze();
    Land();
    pachiruEffectFree(&fieldA0);
    if ((u32)fieldB0 != 0) {
        GSmemFree((void*)fieldB0);
        fieldB0 = 0;
    }
    if ((u32)field3C != 0) {
        GSresFreeResource(0x4e20, (void*)field3C);
        field3C = 0;
    }
    if ((u32)fieldA8 != 0) {
        GSmemFree((void*)fieldA8);
        fieldA8 = 0;
    }
    if ((u32)fieldAC != 0) {
        ::operator delete((void*)fieldAC);
        fieldAC = 0;
    }
    wazaSequenceSysFreeSequenceResource(this);
    resourceGroup = 0;
    model = 0;
}

void ModelSequence::ResetStatus(u8 status) {
    switch (status) {
    case 1:
        WakeUp();
        break;
    case 2:
        UnFreeze();
        break;
    case 3:
        Land();
        break;
    }
}

void ModelSequence::SetStatus(u8 status) {
    switch (status) {
    case 1:
        Sleep();
        break;
    case 2:
        Freeze();
        break;
    case 3:
        Fly(false);
        break;
    }
}

extern "C" void GSmodelGetFrameCount(_GSmodel*, f32*, f32*);

u8 ModelSequence::ModelMotionStart() {
    if (flags & 8) {
        return 0;
    }
    if (isPokemon != 0 && (wazaIndex == 10 || wazaIndex == 9)) {
        WakeUp();
        UnFreeze();
        Land();
    }
    ModelAnimEntry* entry = &records[wazaIndex].entries[0];
    if (flags & 4) {
        return 1;
    }
    u16 count = talkCount;
    if (count == 0) {
        field53 = 0;
        field5D = 0;
        DoAnimation(entry->anim, (enumSectionMotionType)entry->kind, false);
    } else {
        field53 = 0;
        s32 anim = GetDefaultAnimation(this);
        if (!(flags & 2)) {
            animState = 0;
            GSmodelLinkTexAnimToAnim(model, 1);
        }
        GSmodelSetAnimIndex(model, anim);
        GSmodelSetAnimType(model, 0);
        GSmodelSetAnimRate(model, 0.5f);
        f32 frames;
        GSmodelGetFrameCount(model, &frames, 0);
        frames -= 1.0f;
        if (frames < 1.0f) {
            frames = 1.0f;
        }
        u16 half = count >> 1;
        u16 t = half;
        if (half != 0) {
            t = half - 1;
        }
        talkCount = t / (u16)frames;
        u16 rem = t % (u16)(0.5f + frames);
        if (rem == 0 && talkCount != 0) {
            rem = (u16)(0.5f + frames);
            talkCount--;
        }
        field5D = 1;
        GSmodelSetAnimFrame(model, frames - (f32)rem);
        GSmodelStartAnimation(model);
    }
    return 1;
}

extern "C" {
u8 GSmodelIsRootNullAdded(_GSmodel*);
void GSmodelGetRootPosition(_GSmodel*, GSvec*);
void GSmodelAddNull(_GSmodel*, GSvec*, s32, s32);
}

void ModelSequence::CopyState(ModelSequence* from) {
    SetInitFlags();
    if (from != 0) {
        SetVisibility(*(bool*)&from->visible);
        if ((from->flags & 1) == 1) {
            if (GSmodelIsRootNullAdded(from->model)) {
                GSvec root;
                GSmodelGetRootPosition(from->model, &root);
                GSmodelAddNull(model, &root, 0, 0);
            }
            Fly(false);
        }
        if ((from->flags & 2) == 2) {
            Sleep();
        }
        if ((from->flags & 4) == 4) {
            Freeze();
        }
    }
}

void ModelSequence::SetFlags(u8 newFlags) {
    if (newFlags & 2) {
        Sleep();
    } else {
        WakeUp();
    }
    if (newFlags & 4) {
        Freeze();
    } else {
        UnFreeze();
    }
    if (newFlags & 1) {
        Fly(false);
    } else {
        Land();
    }
    flags = newFlags;
}

void ModelSequence::SetDefaultFlags() {
    WakeUp();
    UnFreeze();
    Land();
    SetVisibility(true);
}

void ModelSequence::SetInitFlags() {
    WakeUp();
    UnFreeze();
    Land();
    SetVisibility(!isPokemon);
    flags = 0;
}

void ModelSequence::DoDefaultAnimation(GSmodelAnimType type, bool force) {
    PlayDefaultAnimation(type, force);
}

extern "C" {
void* GScameraGetActiveCamera();
void GScameraGetRotation(void*, GSvec*);
void GSpartGetTransform(void*, GSvec*, GSvec*, GSvec*);
f32 HSD_Randf();
void GSmodelSetRenderCamera(_GSmodel*, void*);
void GSparticleBankSetCamera(void*, void*);
void GSparticleGeneratorSetCamera(void*, void*);
}

void ModelSequence::Update(f32 dt) {
    void* part;
    void* cam;
    if ((u32)field64 != 0 && field62 != 0) {
        cam = (void*)camera;
        if (cam == 0) {
            cam = GScameraGetActiveCamera();
        }
        if (cam != 0) {
            part = GSmodelGetPart((_GSmodel*)field64, field62);
            if (part != 0) {
                GSvec rot;
                GSvec position;
                GSpartGetTransform(part, &position, 0, 0);
                SetPosition(&position);
                GScameraGetRotation(cam, &rot);
                rot.param1 = 0.0f;
                rot.param3 = 0.0f;
                rot.param2 = rot.param2 + *(f32*)&pad68;
                SetRotation(&rot);
                GSpartFree(part);
            }
        }
    }
    UpdateLookAt();
    UpdateVisibility(false);
    NullSequence::Update(dt);
    if (!NullSequence::IsActive() && !(flags & 4)) {
        if (animState != 0) {
            field4A = 0;
        } else if (*(u8*)field8C != 0) {
            u8 rate = GSgfxVideoGetVsyncRate();
            field4A += (u16)(u32)(dt * (f32)rate);
            if (field4A >= 10) {
                f32 chance;
                if (field4A >= 60) {
                    if (field4A >= 180) {
                        chance = 1.0f;
                    } else {
                        chance = 0.016666668f;
                    }
                } else {
                    f32 t = (f32)(s32)(field4A - 10) / 50.0f;
                    chance = t * (2.0f - t) * 0.016666668f;
                }
                if (chance >= HSD_Randf()) {
                    animState = 1;
                    wazaSequenceSysPartAnimationStart(model, field8C);
                }
            }
        }
    }
    if (model != 0) {
        GSmodelSetRenderCamera(model, (void*)camera);
    }
    if (particleBank != 0) {
        GSparticleBankSetCamera(particleBank, (void*)camera);
    }
    if (iceGenerator != 0) {
        GSparticleGeneratorSetCamera(iceGenerator, (void*)camera);
    }
    if (sleepGenerator != 0) {
        GSparticleGeneratorSetCamera(sleepGenerator, (void*)camera);
    }
}

void ModelSequence::UpdateVisibility(bool changed) {
    if (model != 0) {
        GSmodelSetVisibility(model, visible);
        if (particleBank != 0) {
            GSparticleSetBankVisibility(particleBank, visible);
        }
        if (iceGenerator != 0) {
            GSparticleSetGeneratorVisibility(iceGenerator, visible);
        }
        if (sleepGenerator != 0) {
            GSparticleSetGeneratorVisibility(sleepGenerator, visible);
        }
        if (changed && visible != 0 && particleBank != 0) {
            GSparticleDestroyAllGenerators(particleBank, 1);
            s32 current;
            GSmodelGetAnimIndex(model, &current, 0);
            if (current == GetDefaultAnimation(this)) {
                PlayDefaultAnimation((GSmodelAnimType)GSmodelGetAnimType(model), true);
            }
        }
    }
}

void ModelSequence::DestroyParticles(bool arg, bool restart) {
    if (particleBank != 0) {
        GSparticleDestroyAllGenerators(particleBank, arg);
        if (restart) {
            s32 current;
            GSmodelGetAnimIndex(model, &current, 0);
            if (current == GetDefaultAnimation(this)) {
                PlayDefaultAnimation((GSmodelAnimType)GSmodelGetAnimType(model), true);
            }
        }
    }
}

#pragma dont_inline on
void ModelSequence::SetVisibility(bool v) {
    bool changed = visible != v;
    visible = v;
    UpdateVisibility(changed);
}
#pragma dont_inline reset

void ModelSequence::SetScale(GSvec* v) {
    scale.param1 = v->param1;
    scale.param2 = v->param2;
    scale.param3 = v->param3;
    if (model != 0 && !noSync) {
        GSmodelSetScale(model, v);
    }
}

void ModelSequence::ResetScale() {
    if (model != 0) {
        GSmodelSetScale(model, &scale);
    }
}

void ModelSequence::SetRotation(GSvec* v) {
    rotation.param1 = v->param1;
    rotation.param2 = v->param2;
    rotation.param3 = v->param3;
    if (model != 0 && !noSync) {
        GSmodelSetRotation(model, v);
        if (iceGenerator != 0) {
            GSparticleSetGeneratorRotation(iceGenerator, v);
        }
        if (sleepGenerator != 0) {
            GSparticleSetGeneratorRotation(sleepGenerator, v);
        }
    }
}

void ModelSequence::ResetRotation() {
    if (model != 0) {
        GSmodelSetRotation(model, &rotation);
    }
}

void ModelSequence::SetPosition(GSvec* v) {
    position.param1 = v->param1;
    position.param2 = v->param2;
    position.param3 = v->param3;
    if (model != 0 && !noSync) {
        GSmodelSetPosition(model, &position);
    }
}

void ModelSequence::ResetPosition() {
    if (model != 0) {
        GSmodelSetPosition(model, &position);
    }
}

void ModelSequence::GetScale(GSvec* out) {
    if (model != 0) {
        GSmodelGetScale(model, out);
    } else {
        out->param1 = scale.param1;
        out->param2 = scale.param2;
        out->param3 = scale.param3;
    }
}

void ModelSequence::GetRotation(GSvec* out) {
    if (model != 0) {
        GSmodelGetRotation(model, out);
    } else {
        out->param1 = rotation.param1;
        out->param2 = rotation.param2;
        out->param3 = rotation.param3;
    }
}

void ModelSequence::GetPosition(GSvec* out) {
    if (model != 0) {
        GSmodelGetPosition(model, out);
    } else {
        out->param1 = position.param1;
        out->param2 = position.param2;
        out->param3 = position.param3;
    }
}

void ModelSequence::Unload(u8* data) {
    void** d = (void**)data;
    if (d[1] != 0) {
        delete (u8*)d[1];
        d[1] = 0;
    }
    if (d[3] != 0) {
        GSparticleFree(d[3]);
        d[3] = 0;
    }
}

struct ModelSequenceArchiveHeader {
    s32 size;            // 0x00
    void* archive;       // 0x04
    s32 dataSize;        // 0x08
    u32 field0C;         // 0x0c
    s32 count;           // 0x10
    u8 pad14[6];
    u16 type;            // 0x1a
};

extern "C" void HSD_ArchiveParse(void*, void*, u32);

#pragma dont_inline on
u8 ModelSequence::Load(u8* data, unsigned long a, unsigned long b) {
    ModelSequenceArchiveHeader* h = (ModelSequenceArchiveHeader*)data;
    if (h->type == 0xc && h->size != 0) {
        data += 0x84;
        data += h->count * 0xd0;
        data = (u8*)(((u32)data + 0x1f) & ~0x1f);
        if (h->dataSize != 0) {
            h->field0C = 0;
            data += (h->dataSize + 0x1f) & ~0x1f;
        } else {
            h->field0C = 0;
        }
        if ((a == 0xdd && b == 0x3001e00) || (a == 0x13f && b == 0x3641e00) || (a == 0x387 && b == 0x6691e00)) {
            h->archive = 0;
        } else {
            void* p = ::operator new(0x44);
            if (p != 0) {
                h->archive = p;
                HSD_ArchiveParse(p, data, h->size);
            } else {
                h->archive = 0;
                return 0;
            }
        }
        return 1;
    }
    h->archive = 0;
    h->field0C = 0;
    return 0;
}

#pragma dont_inline reset

extern "C" u8 ModelSequence_Load(u8* data, unsigned long a, unsigned long b) {
    return ModelSequence::Load(data, a, b);
}

extern "C" {
void PSVECScale(GSvec*, GSvec*, f32);
void PSVECSubtract(GSvec*, GSvec*, GSvec*);
void PSVECNormalize(GSvec*, GSvec*);
f32 PSVECDotProduct(GSvec*, GSvec*);
f32* GSmodelGetMatrixPtr(_GSmodel*);
f64 asin(f64);
}

void ModelSequence::UpdateLookAt() {
    GSvec targetPos;
    GSvec axisX;
    GSvec axisY;
    GSvec direction;
    GSvec copy;
    GSvec copy2;
    GSvec scaled;
    GSvec delta;
    GSvec scaled2;
    if (lookEnabled != 0) {
        if (lookTarget == 0) {
            PSVECScale(&lookVec, &scaled, 0.25f);
            copy = scaled;
            PSVECSubtract(&lookVec, &copy, &lookVec);
        } else {
            void* targetPart = GSmodelGetPart(lookTarget->model, lookTarget->field46);
            if (targetPart != 0) {
                void* part = GSmodelGetPart(model, field46);
                if (part == 0) {
                    GSpartFree(targetPart);
                } else {
                    f32* matrix = GSmodelGetMatrixPtr(model);
                    f32 xa = matrix[0];
                    f32 xb = matrix[4];
                    f32 xc = matrix[8];
                    axisX.param1 = xa;
                    axisX.param2 = xb;
                    axisX.param3 = xc;
                    PSVECNormalize(&axisX, &axisX);
                    f32 ya = matrix[1];
                    f32 yb = matrix[5];
                    f32 yc = matrix[9];
                    axisY.param1 = ya;
                    axisY.param2 = yb;
                    axisY.param3 = yc;
                    PSVECNormalize(&axisY, &axisY);
                    GSpartGetTransform(part, &direction, 0, 0);
                    GSpartGetTransform(targetPart, &targetPos, 0, 0);
                    PSVECSubtract(&targetPos, &direction, &delta);
                    direction = delta;
                    PSVECNormalize(&direction, &direction);
                    f32 dot = PSVECDotProduct(&axisY, &direction);
                    f32 pitch = -(f32)asin(dot);
                    PSVECScale(&axisY, &scaled2, dot);
                    copy2 = scaled2;
                    PSVECSubtract(&direction, &copy2, &direction);
                    PSVECNormalize(&direction, &direction);
                    f32 yaw = (f32)asin(PSVECDotProduct(&axisX, &direction));
                    f32 x = 0.25f * (pitch - lookVec.param1) + lookVec.param1;
                    f32 y = 0.25f * (yaw - lookVec.param2) + lookVec.param2;
                    if (x > 3.1415927f) {
                        x = 6.2831855f - x;
                    }
                    if (x < -0.2617994f) {
                        x = -0.2617994f;
                    }
                    if (x > 0.2617994f) {
                        x = 0.2617994f;
                    }
                    if (y > 3.1415927f) {
                        y = 6.2831855f - y;
                    }
                    if (y < -0.5235988f) {
                        y = -0.5235988f;
                    }
                    if (y > 0.5235988f) {
                        y = 0.5235988f;
                    }
                    lookVec.param1 = x;
                    lookVec.param2 = y;
                    lookVec.param3 = 0.0f;
                    GSpartFree(part);
                    GSpartFree(targetPart);
                }
            }
        }
    }
}

static f32 _getHeadRotationCallback(GSpart*, GSpartMixType, void* user, GSvec* out) {
    ModelSequence* seq = (ModelSequence*)user;
    out->param1 = seq->lookVec.param1;
    out->param2 = seq->lookVec.param2;
    out->param3 = seq->lookVec.param3;
    return 1.0f;
}

struct _GSmodelAnimCBData {
    u32 flags;
    s32 index;
    ModelSequence* seq;
};

extern "C" {
u8 GSmodelIsAnimating(_GSmodel*);
f32 GSmodelGetAnimFrame(_GSmodel*);
f32 GSmodelGetAnimRate(_GSmodel*);
void GSmodelSetTexAnimIndex(_GSmodel*, s32);
void GSmodelSetTexAnimRate(_GSmodel*, f32);
void GSmodelSetTexAnimFrame(_GSmodel*, f32);
void GSmodelSetTexAnimType(_GSmodel*, s32);
void GSmodelStartTexAnimation(_GSmodel*);
void GSmodelSetKeepPartAnimFlag(_GSmodel*, u8);
}

void ModelSequence::DoAnimation(int anim, enumSectionMotionType type, bool force) {
    f32 frame = 0.0f;
    s32 animType;
    switch (type) {
    case 2:
        animType = 1;
        break;
    case 1:
        animType = 0;
        break;
    default:
        PlayDefaultAnimation(GSMODEL_ANIM_TYPE_1, force);
        return;
    }
    flags &= ~0x10;
    if (isPokemon != 0) {
        if (wazaIndex == 10) {
            flags |= 8;
        } else {
            if (flags & 4) {
                return;
            }
            if (!(flags & 2)) {
                animState = 0;
                GSmodelLinkTexAnimToAnim(model, 1);
            }
        }
    } else {
        if (wazaIndex == 5 || wazaIndex == 10) {
            flags |= 8;
        }
    }
    if (anim == GetFirstAnimation(records)) {
        anim = GetDefaultAnimation(this);
        if (!force) {
            s32 current;
            GSmodelGetAnimIndex(model, &current, 0);
            if (anim == current) {
                frame = GSmodelGetAnimFrame(model);
            }
        }
    }
    GSmodelSetAnimEndedCallback(model, sequenceAnimEndCallback, this);
    GSmodelSetAnimIndex(model, anim);
    GSmodelSetAnimType(model, animType);
    GSmodelSetAnimRate(model, 0.5f);
    GSmodelSetAnimFrame(model, frame);
    GSmodelStartAnimation(model);
}

void ModelSequence::DoModelAnimation(int index) {
    if (index == 0) {
        PlayDefaultAnimation(GSMODEL_ANIM_TYPE_1, false);
    } else {
        wazaIndex = index;
        field53 = 0;
        talkCount = 0;
        field5D = 0;
        s32 i = 0;
        ModelRecord* record = &records[index];
        ModelAnimEntry* entry = record->entries;
        s32 count = record->count;
        for (; i < count; i++, entry++) {
            if (entry->kind != 0) {
                break;
            }
        }
        if (i == count) {
            PlayDefaultAnimation(GSMODEL_ANIM_TYPE_1, false);
        } else {
            field53 = i;
            DoAnimation(entry->anim, (enumSectionMotionType)entry->kind, false);
        }
    }
}

void _sequenceModelAnimEndedCallback(_GSmodel* m, _GSmodelAnimCBData* d) {
    u32 cbFlags = d->flags;
    if (cbFlags & 1) {
        if (!(cbFlags & 8)) {
            if (!(cbFlags & 4)) {
                ModelSequence* seq = d->seq;
                {
                    if (seq == 0 || seq->failed != 0) return;
                    if (m == seq->model) {
                        if ((seq->flags & 4) != 4) {
                            ModelRecord* record = &seq->records[seq->wazaIndex];
                            if (seq->talkCount != 0) {
                                seq->talkCount--;
                                seq->PlayDefaultAnimation(GSMODEL_ANIM_TYPE_0, false);
                            } else {
                                if (seq->field5D != 0) {
                                    seq->field53 = 0;
                                    seq->field5D = 0;
                                } else {
                                    seq->field53++;
                                }
                                if (seq->field53 >= record->count) {
                                    seq->PlayDefaultAnimation(GSMODEL_ANIM_TYPE_1, false);
                                    seq->wazaIndex = 0;
                                    seq->field53 = 0;
                                    seq->talkCount = 0;
                                    seq->field5D = 0;
                                    if (seq->lookSource != 0 && seq->lookSource->lookEnabled != 0) {
                                        seq->lookSource->lookTarget = 0;
                                    }
                                } else {
                                    ModelAnimEntry* e = &record->entries[seq->field53];
                                    seq->DoAnimation(e->anim, (enumSectionMotionType)e->kind, true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void _mouthAnimEnded(_GSmodel* m, _GSmodelAnimCBData* d) {
    if ((d->flags & 8) || (d->flags & 2)) {
        if (!(d->flags & 4)) {
            ModelSequence* seq = d->seq;
            {
                if (seq == 0 || seq->failed != 0) return;
                if ((seq->flags & 4) == 4) {
                    return;
                }
                if (m == seq->model) {
                    s32 index = d->index;
                    PartAnimData* anim = seq->talkAnim;
                    if (*(u8*)anim == 0 || index != ((u8*)anim)[0x12]) return;
                    {
                        {
                            seq->flags &= ~0x40;
                            GSmodelLinkTexAnimToAnim(m, 1);
                            if (GSmodelIsAnimating(m)) {
                                f32 frame = GSmodelGetAnimFrame(m);
                                f32 rate = GSmodelGetAnimRate(m);
                                s32 type = GSmodelGetAnimType(m);
                                GSmodelGetAnimIndex(m, &index, 0);
                                if (d->flags & 2) {
                                    GSmodelSetTexAnimIndex(m, index);
                                    GSmodelSetTexAnimRate(m, rate);
                                    GSmodelSetTexAnimFrame(m, frame);
                                    GSmodelSetTexAnimType(m, type);
                                    GSmodelStartTexAnimation(m);
                                } else {
                                    GSmodelSetKeepPartAnimFlag(m, 0);
                                    GSmodelSetAnimIndex(m, index);
                                    GSmodelSetAnimRate(m, rate);
                                    GSmodelSetAnimFrame(m, frame);
                                    GSmodelSetAnimType(m, type);
                                    GSmodelStartAnimation(m);
                                    GSmodelSetKeepPartAnimFlag(m, 1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void _eyeAnimEnded(_GSmodel* m, _GSmodelAnimCBData* d) {
    u8 match = 0;
    if ((d->flags & 8) || (d->flags & 2)) {
        if (!(d->flags & 4)) {
            ModelSequence* seq = d->seq;
            {
                if (seq == 0 || seq->failed != 0) return;
                if ((seq->flags & 4) == 4) {
                    return;
                }
                if (m == seq->model) {
                    s32 index = d->index;
                    PartAnimData* anim = seq->sleepAnim;
                    if (*(u8*)anim != 0 && index == ((u8*)anim)[0x12]) {
                        match = 1;
                    } else {
                        anim = seq->wakeAnim;
                        if (*(u8*)anim != 0 && index == ((u8*)anim)[0x12]) {
                            match = 1;
                        } else {
                            anim = seq->field8C;
                            if (*(u8*)anim != 0 && index == ((u8*)anim)[0x12]) {
                                match = 1;
                            }
                        }
                    }
                    if (!match || (s32)seq->animState != 1) return;
                    {
                        {
                            GSmodelLinkTexAnimToAnim(m, 1);
                            if (GSmodelIsAnimating(m)) {
                                f32 frame = GSmodelGetAnimFrame(m);
                                f32 rate = GSmodelGetAnimRate(m);
                                s32 type = GSmodelGetAnimType(m);
                                GSmodelGetAnimIndex(m, &index, 0);
                                if (d->flags & 2) {
                                    GSmodelSetTexAnimIndex(m, index);
                                    GSmodelSetTexAnimRate(m, rate);
                                    GSmodelSetTexAnimFrame(m, frame);
                                    GSmodelSetTexAnimType(m, type);
                                    GSmodelStartTexAnimation(m);
                                } else {
                                    GSmodelSetKeepPartAnimFlag(m, 0);
                                    GSmodelSetAnimIndex(m, index);
                                    GSmodelSetAnimRate(m, rate);
                                    GSmodelSetAnimFrame(m, frame);
                                    GSmodelSetAnimType(m, type);
                                    GSmodelStartAnimation(m);
                                    GSmodelSetKeepPartAnimFlag(m, 1);
                                }
                            }
                            seq->animState = 0;
                        }
                    }
                }
            }
        }
    }
}

struct ModelSequenceDataHeader {
    s32 size;            // 0x00
    void* archive;       // 0x04
    s32 dataSize;        // 0x08
    u32 field0C;         // 0x0c
    s32 count;           // 0x10
    s32 modelSize;       // 0x14
    u16 id;              // 0x18
    u16 type;            // 0x1a
};

extern "C" {
u32 wazaSequenceSysGetResID(ModelSequence*);
void* GSmemAllocAlign(u32, u32);
void* memcpy(void*, const void*, u32);
void DCFlushRange(void*, u32);
void loadModel(void*, u32, u32, u32);
void GSresIsUniqueID(u32, u32, u32);
void* GSresGetResource(u32, u32);
void GSmodelSetGroundPlane(_GSmodel*, s32, f32);
void GSmodelRemoveRootJointAnimation(_GSmodel*);
void GSmodelSetKeepPartAnimFlag(_GSmodel*, u8);
void GSmodelSetSkipFractionalFramesFlag(_GSmodel*, u8);
void* GSparticleLoad(void*);
void GSmodelRecalculateBound(_GSmodel*);
void GSmodelLinkToGSparticleBank(_GSmodel*, void*);
void GSmodelSetGSparticleLinkAttachMode(_GSmodel*, s32);
void GSmodelCreateDistortion(_GSmodel*, u16, u8);
void GSmodelEnableDistortion(_GSmodel*);
void GSmodelSetBoundCheck(_GSmodel*, u8);
void GSmodelSetShadowFlags(_GSmodel*, u32);
void GSmodelSetShadowLight(_GSmodel*, void*);
void GSmodelSetShadowSurface(_GSmodel*, s32, void*);
void GSpartRegisterAnimMix(void*, s32, u32, void*, void*);
extern GSvec zeroVector;
extern GSvec unitScaleVector;
}
void* wazaSequenceSysGetModelShadowLight();
s32 wazaSequenceSysGetModelShadowCount();
void* wazaSequenceSysGetModelShadowList();

u8 ModelSequence::LoadData(u8* data) {
    ModelSequenceDataHeader* h;
    u32 resId = wazaSequenceSysGetResID(this);
    h = (ModelSequenceDataHeader*)data;
    if (h->size == 0) {
        return 0;
    }
    if (h->type != 0xc) {
        return 0;
    }
    if (id == 0) {
        id = h->id;
    }
    sleepAnim = (PartAnimData*)((u8*)h + 0x1c);
    wakeAnim = (PartAnimData*)((u8*)h + 0x2f);
    field8C = (PartAnimData*)((u8*)h + 0x42);
    talkAnim = (PartAnimData*)((u8*)h + 0x55);
    *(u16*)&pad4C[0] = *(u16*)((u8*)h + 0x6a);
    pad4F = ((u8*)h)[0x6c];
    field5C = ((u8*)h)[0x68];
    if (*(u16*)&pad4C[0] == 0) {
        field5C &= 0xFE;
    }
    field46 = *(u16*)((u8*)h + 0x6e);
    data += 0x84;
    modelSize = h->modelSize;
    wazaIndex = 0;
    field53 = 0;
    talkCount = 0;
    field5D = 0;
    records = (ModelRecord*)data;
    field51 = h->count;
    {
        u16 i;
        ModelRecord* rec = (ModelRecord*)data;
        for (i = 0; i < field51; i++, rec++) {
            ModelAnimEntry* e = rec->entries;
            s32 n = rec->count;
            for (s32 j = 0; j < n; j++, e++) {
                if (e->kind == 0) {
                    e->anim = 1;
                }
            }
        }
    }
    data += field51 * 0xd0;
    data = (u8*)(((u32)data + 0x1f) & ~0x1f);
    if (h->dataSize != 0) {
        fieldB0 = (s32)GSmemAllocAlign((h->dataSize + 0x1f) & ~0x1f, 0x20);
        if ((u32)fieldB0 != 0) {
            memcpy((void*)fieldB0, data, (h->dataSize + 0x1f) & ~0x1f);
        }
        data += (h->dataSize + 0x1f) & ~0x1f;
    }
    field80 = (s32)((u8*)h + 0x70);
    {
        s32* p = (s32*)field80;
        if (p[0] >= 4 || p[0] < 0) p[0] = 0;
        p = (s32*)field80;
        if (p[1] >= 4 || p[1] < 0) p[1] = 1;
        p = (s32*)field80;
        if (p[2] >= 4 || p[2] < 0) p[2] = 2;
        p = (s32*)field80;
        if (p[3] >= 4 || p[3] < 0) p[3] = 3;
        p = (s32*)field80;
        if (p[0] != 0 || p[1] != 1 || p[2] != 2 || p[3] != 3) {
            colorSwap = 1;
        }
        u8* q = (u8*)field80;
        if (q[0x10] != 0x7f || q[0x11] != 0x7f || q[0x12] != 0x7f || q[0x13] != 0x7f) {
            modulation = 1;
        }
    }
    void* archive;
    if (h->archive == 0) {
        archive = ::operator new(0x44);
        if (archive == 0) {
            return 0;
        }
        fieldA8 = (s32)GSmemAllocAlign((h->size + 0x1f) & ~0x1f, 0x20);
        if ((u32)fieldA8 == 0) {
            ::operator delete(archive);
            return 0;
        }
        fieldAC = (s32)archive;
        memcpy((void*)fieldA8, data, (h->size + 0x1f) & ~0x1f);
        DCFlushRange((void*)fieldA8, (h->size + 0x1f) & ~0x1f);
        HSD_ArchiveParse(archive, (void*)fieldA8, h->size);
    } else {
        archive = h->archive;
    }
    loadModel(archive, 0x4e20, 0, resId);
    GSresIsUniqueID(0x4e20, resId, 0);
    void* res = GSresGetResource(0x4e20, resId);
    model = (_GSmodel*)res;
    if (res == 0) {
        return 0;
    }
    GSmodelSetGroundPlane(model, 0, 0.0f);
    if (field5C & 0x40) {
        GSmodelRemoveRootJointAnimation(model);
    }
    GSmodelSetKeepPartAnimFlag(model, 1);
    if (field5C & 0x80) {
        GSmodelSetSkipFractionalFramesFlag(model, 1);
    }
    field3C = resId;
    if ((u32)fieldB0 != 0) {
        particleBank = GSparticleLoad((void*)fieldB0);
    }
    GSmodelSetAnimIndex(model, GetDefaultAnimation(this));
    GSmodelRecalculateBound(model);
    if (particleBank != 0) {
        GSmodelLinkToGSparticleBank(model, particleBank);
        if (field5C & 0x20) {
            GSmodelSetGSparticleLinkAttachMode(model, 1);
        } else {
            GSmodelSetGSparticleLinkAttachMode(model, 6);
        }
    }
    GSmodelLinkTexAnimToAnim(model, 1);
    GSmodelSetAnimEndedCallback(model, sequenceAnimEndCallback, this);
    PlayDefaultAnimation(GSMODEL_ANIM_TYPE_1, true);
    SetVisibility(false);
    u8 c = field5C;
    if (c & 1) {
        u8 mask = 0;
        if (c & 2) {
            mask |= 1;
            if (c & 8) {
                mask |= 4;
            }
        }
        if (c & 4) {
            mask |= 2;
            if (c & 0x10) {
                mask |= 8;
            }
        }
        if (mask != 0) {
            GSmodelCreateDistortion(model, *(u16*)&pad4C[0], pad4F);
            GSmodelEnableDistortion(model);
        }
    }
    GSmodelSetPosition(model, &zeroVector);
    GSmodelSetRotation(model, &zeroVector);
    GSmodelSetScale(model, &unitScaleVector);
    GSmodelSetBoundCheck(model, 1);
    if (wazaSequenceSysGetModelShadowLight() != 0 && (u32)wazaSequenceSysGetModelShadowCount() != 0) {
        GSmodelSetShadowFlags(model, 1);
        GSmodelSetShadowLight(model, wazaSequenceSysGetModelShadowLight());
        void* list = wazaSequenceSysGetModelShadowList();
        GSmodelSetShadowSurface(model, wazaSequenceSysGetModelShadowCount(), list);
    }
    if (model != 0 && isPokemon == 0 && field46 != 0) {
        void* part = GSmodelGetPart(model, field46);
        if (part != 0) {
            GSpartRegisterAnimMix(part, 2, 0x202, (void*)_getHeadRotationCallback, this);
            lookEnabled = 1;
            lookVec.param1 = 0.0f;
            lookVec.param2 = 0.0f;
            lookVec.param3 = 0.0f;
            GSpartFree(part);
        }
    }
    return 1;
}

void sequenceAnimEndCallback(_GSmodel* m, _GSmodelAnimCBData* d) {
    _sequenceModelAnimEndedCallback(m, d);
    _eyeAnimEnded(m, d);
    _mouthAnimEnded(m, d);
}

ModelSequence* New_ModelSequence(unsigned short id, unsigned long rnd, bool rare) {
    ModelSequence* s = new ModelSequence(id, rnd, rare);
    if (s == 0) {
        return 0;
    }
    s->next = g_Sequences;
    g_Sequences = s;
    if (s->failed != 0) {
        delete s;
        return 0;
    }
    return s;
}

ModelSequence* New_ModelSequence(unsigned short id) {
    ModelSequence* s = new ModelSequence(id);
    if (s == 0) {
        return 0;
    }
    s->next = g_Sequences;
    g_Sequences = s;
    if (s->failed != 0) {
        delete s;
        return 0;
    }
    return s;
}
