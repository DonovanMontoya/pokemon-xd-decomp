#include <game/pxdvs/app/wazaSequence/modelSequence.hpp>


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

f32 ModelSequence::GetModelScale(bool fixed) const {
    f32 scale = GetSizeScale();
    if (!fixed) {
        scale = menuModelGetScale(isPokemon, id);
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
                s32 joint = records[wazaIndex].joints[1];
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
    SetVisibility(isPokemon == 0);
    flags = 0;
}

void ModelSequence::DoDefaultAnimation(GSmodelAnimType type, bool force) {
    PlayDefaultAnimation(type, force);
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

extern "C" u8 ModelSequence_Load(u8* data, unsigned long a, unsigned long b) {
    return ModelSequence::Load(data, a, b);
}

static f32 _getHeadRotationCallback(GSpart*, GSpartMixType, void* user, GSvec* out) {
    ModelSequence* seq = (ModelSequence*)user;
    out->param1 = seq->lookVec.param1;
    out->param2 = seq->lookVec.param2;
    out->param3 = seq->lookVec.param3;
    return 1.0f;
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
