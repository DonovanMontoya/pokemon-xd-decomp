#include <game/pxdvs/app/wazaSequence/wazaSequencePrivate.hpp>

static f32 distmtx[2][3] = {{0,0,0},{0,0,0}};
static inline ModelSequence *AsModel(NullSequence *sequence) {
    if (sequence->type == 1) return (ModelSequence *)sequence;
    return 0;
}
static inline u8 *AlignData(u8 *data) { return (u8 *)(((u32)data + 31) & ~31U); }
static inline f32 WazaTime(WazaSequence *waza,u8 phase) {
    NullSequence *owner = waza->sequence;
    if (owner->type == 1) return wazaSequenceSysGetWazaTime((ModelSequence *)owner,waza,phase);
    return wazaSequenceSysNullGetWazaTime(waza,phase);
}
static inline void ResetDistortion(f32 scale) {
    distmtx[1][1] = scale;
    distmtx[0][1] = scale;
    for (GSgfxLayer *layer=GSgfxLayerGetLayerList();layer!=0;layer=layer->next) {
        if (layer->kind == 1) layer->SetDistortionParams(distmtx,0);
    }
}

void WazaSequence::ApplyStop() {
    stopped = 0;
    if (active != 0) {
        if (g_LastStartedWaza == this) g_LastStartedWaza = 0;
        ModelSequence *model = AsModel(sequence);
        if (model != 0) {
            u32 handle = model->model;
            if (flags & 0x08000000) GSmodelLinkToGSparticleBank(handle,model->particleBank);
            if (model->isPokemon == 0) model->DoDefaultAnimation(ANIM_TYPE_1,false);
            if ((flags & 2) && g_EnableModelLayerChange != 0) {
                s32 layer[] = {2};
                GSmodelSetRenderLayer(handle,1,layer);
            }
        }
        for (SequenceEntry *entry=entries;entry!=0;entry=entry->next) entry->Stop(true);
        ResetDistortion(0.5f);
        active = 0;
        ended = 0;
    }
}
WazaSequence::~WazaSequence() {
    if (active != 0) ApplyStop();
    if (entries != 0) delete entries;
    if (cameraResource != 0) GSresFreeResource(20000,cameraResource);
    wazaSequenceSysFreeWazaResource(this);
    if (sequence != 0) sequence->Remove(this);
}
extern "C" {
s32 WazaSequence_IsActive(WazaSequence *waza) {
    if (waza == 0) return 0;
    if (wazaSequenceSysIsValidWaza(waza)) {
        s32 result = 0;
        if (waza->active != 0 && waza->stopped == 0) result = 1;
        return result;
    }
    return 0;
}
WazaSequence *Sequence_LoadWaza(NullSequence *sequence,u16 id,u8 kind,u8 variant) {
    WazaSequence *waza = new WazaSequence(sequence,id,kind,variant);
    if (waza == 0) waza = 0;
    else if (waza->failed != 0) {
        delete waza;
        waza = 0;
    }
    return waza;
}
void WazaSequence_Free(WazaSequence *waza) {
    if (waza != 0 && wazaSequenceSysIsValidWaza(waza)) delete waza;
}
void WazaSequence_Stop(WazaSequence *waza) {
    if (waza != 0 && wazaSequenceSysIsValidWaza(waza)) waza->stopped=1;
}
void WazaSequence_Start(WazaSequence *waza,bool camera) {
    if (waza != 0 && wazaSequenceSysIsValidWaza(waza)) waza->Start(camera);
}
}

bool WazaSequence::LoadData(u8 *data) {
    MainSequenceEntry main(this,&data);
    if (sequence == 0) return false;
    WazaSequenceData *header = (WazaSequenceData *)data;
    data += sizeof(WazaSequenceData);
    entryCount = header->entryCount - 1;
    index = header->index;
    if (header->version >= 6) distortion = (f32)header->distortion / 65535.0f;
    else distortion=1.0f;
    ModelSequence *model = AsModel(sequence);
    if (model != 0) {
        if (index == 11) {
            if (model->animationCount < index) index=0;
        } else if (index >= 11 && index < 16) {
            if (model->animationCount < index) index=1;
        }
    }
    flags=header->flags;
    field16=header->fieldC;
    data=AlignData(data);
    if (header->version <= 3) flags |= 0x78;
    if (header->version <= 5) flags &= 0xFFE07FFF;
    if (header->camera != 0) {
        s32 resource=wazaSequenceSysGetResID();
        loadCamera(header->camera,20000,resource);
        GSresIsUniqueID(20000,resource,0);
        if (GSresGetResource(20000,resource) != 0) cameraResource=resource;
        data += (header->cameraSize+31)&~31U;
    } else cameraResource=0;
    if (entryCount != 0) {
        for (u16 i=0;i<entryCount;++i) {
            SequenceEntry *entry;
            switch (*(u32 *)(data+4)) {
            case 1:entry=new CameraEntry(this,&data);break;
            case 2:entry=new ModelEntry(this,&data);break;
            case 3:entry=new ParticleEntry(this,&data);break;
            case 4:entry=new EffectEntry(this,&data);break;
            case 5:entry=new SoundEntry(this,&data);break;
            case 6:entry=new EventEntry(this,&data);break;
            case 7:entry=new LensFlareEntry(this,&data);break;
            default:return false;
            }
            entry->Link();
        }
        startOffset=0.0f;
        for (SequenceEntry *entry=entries;entry!=0;entry=entry->next) {
            if (entry->startTime < startOffset) startOffset=entry->startTime;
        }
        if (startOffset < 0.0f) {
            startOffset=-startOffset;
            for (SequenceEntry *entry=entries;entry!=0;entry=entry->next) {
                entry->startTime += startOffset;
                entry->time += startOffset;
            }
        }
    }
    return true;
}
s32 WazaSequence::IsImpactPoint(u8 phase) {
    if (phase == 4) return active != 0 ? 0 : 1;
    return time >= WazaTime(this,phase);
}
SequenceEntry *WazaSequence::GetEntryFromID(u8 id) {
    SequenceEntry *entry=entries;
    while (entry!=0) {
        if (entry->id == id) return entry;
        entry=entry->next;
    }
    return entry;
}
bool WazaSequence::Update(f32 delta) {
    SequenceEntry *entry;
    s32 pending=0;
    entry=entries;
    s32 running=0;
    time += delta;
    if (WazaTime(this,3) > time) running=1;
    ModelSequence *model=AsModel(sequence);
    if (model != 0) {
        if ((model->flags & 8) != 8 && (model->flags & 16) == 16) {
            if (WazaTime(this,2) < time) return false;
        }
        if (model->animationActive != 0 && (model->flags & 4) != 4) ++running;
    }
    for (;entry!=0;entry=entry->next) {
        switch (entry->state) {
        case 2:break;
        case 0:
            if (entry->startTime <= 0.00001f+time) {
                if (entry->Start()) ++running;
                else entry->state=-1;
            } else {
                entry->time=entry->startTime;
                ++pending;
            }
            break;
        case 1:
            if (!entry->Update(delta)) entry->Stop(false);
            else ++running;
            break;
        case 3:
            if (!entry->Update(delta)) entry->Stop(false);
            break;
        }
    }
    if (running+pending == 0) return false;
    return ended == 0;
}
void WazaSequence::Start(bool camera) {
    if (active != 0) ApplyStop();
    wazaSequenceSysApplyStop();
    ModelSequence *model=AsModel(sequence);
    SequenceEntry *entry=entries;
    if (model != 0) {
        u32 handle=model->model;
        model->LinkWithWazaSequence(this);
        if (model->isPokemon != 0 && kind == 2) wazaSequenceSysResetAnimationExcept(model);
        if (flags & 0x80000000) model->DestroyParticles((flags & 0x8000)==0,false);
        if (flags & 0x08000000) GSmodelLinkToGSparticleBank(handle,0);
        model->ModelMotionStart();
        if ((flags & 2) && g_EnableModelLayerChange != 0) {
            s32 layer[]={4};
            GSmodelSetRenderLayer(handle,1,layer);
        }
        if (camera) battleCameraStartWaza(this);
        if (flags & 0x04000000) battleGridHideModelsExcept(model);
    }
    active=1;
    for (;entry!=0;entry=entry->next) entry->state=0;
    ResetDistortion(0.5f*distortion);
    time=0.0f;
    ended=0;
    g_LastStartedWaza=Update(0.0f)?this:0;
}
void WazaSequence::SetRenderCamera(_GScamera *camera) {
    for (SequenceEntry *entry=entries;entry!=0;entry=entry->next) {
        s32 state = entry->state;
        bool active=false;
        if (state == 1 || state == 3) active=true;
        if (active) entry->SetRenderCamera(camera);
    }
}
s32 WazaSequence::GetNumVariations(u16 id,u16 kind) {
    s32 count=0;
    if (kind == 0) return 0;
    if (kind == 4) {
        if (id == 0 || id >= waza_generic_wzx_data_number) return 0;
        if (waza_generic_wzx_data[id] != 0) count=1;
    } else {
        WazaExtEntry *ext=waza_ext_wzx_data;
        u16 index=kind-1;
        if (id == 0 || id >= waza_wzx_data_number) return 0;
        if (waza_wzx_data[id][index] != 0) count=1;
        for (u32 i=0;i<waza_ext_wzx_data_number;++i,++ext) {
            if (ext->wazaId == id && ext->res[index] != 0) ++count;
        }
    }
    return count;
}

WazaSequence::WazaSequence(NullSequence *owner,u16 id,u8 moveKind,u8 variant) {
    ModelSequence *model=0;
    time=0.0f;startOffset=0.0f;flags=0;wazaId=0;kind=0;failed=0;resId=0;
    entryCount=0;index=0;active=0;ended=0;field16=0;stopped=0;
    cameraResource=0;entries=0;sequence=0;next=0;previous=0;
    if (owner == 0) {failed=1;return;}
    if (moveKind == 0) {failed=1;return;}
    if (owner->type == 1) model=(ModelSequence *)owner;
    u16 resource=wazaSequenceSysGetResourceID(model,id,moveKind,variant);
    if (resource == 0) {failed=1;return;}
    u32 group=waza_resource_data[resource].group;
    u32 resourceId=waza_resource_data[resource].id;
    if (group == 0 || resourceId == 0) {failed=1;return;}
    u8 *data=(u8 *)wazaSequenceSysLoadResource(group,resourceId);
    resId=group;
    if (data == 0) {failed=1;return;}
    wazaId=id;kind=moveKind;
    owner->Add(this);
    if (!LoadData(data)) failed=2;
}
void WazaSequence::Unload(u8 *data) {
    MainSequenceEntry main(0,&data);
    WazaSequenceData *header=(WazaSequenceData *)data;
    data=AlignData(data+sizeof(WazaSequenceData));
    u16 count=header->entryCount-1;
    if (header->camera != 0) {
        ::operator delete(header->camera);
        header->camera=0;
    }
    if (header->cameraSize != 0) data += (header->cameraSize+31)&~31U;
    if (count != 0) {
        for (u16 i=0;i<count;++i) {
            switch (*(u32 *)(data+4)) {
            case 1:CameraEntry::Unload(&data);break;
            case 2:ModelEntry::Unload(&data);break;
            case 3:ParticleEntry::Unload(&data);break;
            case 4:EffectEntry::Unload(&data);break;
            case 5:SoundEntry::Unload(&data);break;
            case 6:EventEntry::Unload(&data);break;
            case 7:LensFlareEntry::Unload(&data);break;
            }
        }
    }
}
bool WazaSequence::Load(u8 *data,unsigned long group,unsigned long id) {
    MainSequenceEntry main(0,&data);
    wazaSequenceSysGetResID();
    WazaSequenceData *header=(WazaSequenceData *)data;
    data=AlignData(data+sizeof(WazaSequenceData));
    u16 count=header->entryCount-1;
    header->camera=0;
    if (header->cameraSize != 0) {
        void *archive=::operator new(0x44);
        if (archive != 0) {
            header->camera=archive;
            HSD_ArchiveParse(archive,data,header->cameraSize);
        }
        data += (header->cameraSize+31)&~31U;
    }
    if (count != 0) {
        for (u16 i=0;i<count;++i) {
            switch (*(u32 *)(data+4)) {
            case 1:if (!CameraEntry::Load(&data)) return false;break;
            case 2:if (!ModelEntry::Load(&data)) return false;break;
            case 3:if (!ParticleEntry::Load(&data)) return false;break;
            case 4:if (!EffectEntry::Load(&data)) return false;break;
            case 5:if (!SoundEntry::Load(&data)) return false;break;
            case 6:if (!EventEntry::Load(&data)) return false;break;
            case 7:if (!LensFlareEntry::Load(&data)) return false;break;
            default:return false;
            }
        }
    }
    return true;
}
