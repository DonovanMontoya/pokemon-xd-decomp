#include <game/pxdvs/app/wazaSequence/wazaSequenceSysPrivate.hpp>

Sequence* g_Sequences;
WazaSequence* g_LastStartedWaza;
u32 g_SleepParticle;
u32 g_IceParticle;
s32 _resource_id_count;
s8 g_EnableModelLayerChange;
u32 _modelShadowLight;
s32 _modelShadowCount;
u32 _modelShadowList[16];
u32 g_SoundListener;
s32 gCameraShakeModel;
u32 gCameraShakeModels[9];
extern u32 waza_resource_data[];

inline u32 loadResourceInline(unsigned long group, unsigned long id) {
    u32 r = (u32)GSresGetResource(group, id);
    if (r != 0) {
        return r;
    }
    GSfsysReadWait(group);
    return (u32)GSresGetResource(group, id);
}

static u32 _wazaSequenceSysLoadModel(u32 res) {
    u32 model;
    if (res == 0) {
        return 0;
    }
    model = GSmodelLoad(res, 0);
    if (model == 0) {
        GSlogWrite("%s: couldn't load model", __FUNCTION__);
    } else {
        GSmodelSetVisibility(model, 1);
        if (GSmodelCanAnimate(model)) {
            GSmodelSetAnimIndex(model, 0);
            GSmodelSetAnimRate(model, 0.5f);
            GSmodelStartAnimation(model);
        }
        if (GSmodelCanTexAnimate(model)) {
            GSmodelSetTexAnimIndex((_GSmodel*)model, 0);
            GSmodelSetTexAnimRate((_GSmodel*)model, 0.5f);
            GSmodelStartTexAnimation((_GSmodel*)model);
        }
    }
    return model;
}

extern "C" {

void Sequence_SetCamera(Sequence* seq, s32 camera) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            seq->camera = camera;
        }
    }
}

void Sequence_GetScale(Sequence* seq, GSvec* out) {
    if (seq != 0) {
        if (!Sequence_IsValid(seq)) {
            out->z = 1.0f;
            out->y = 1.0f;
            out->x = 1.0f;
            return;
        }
        seq->GetScale(out);
    }
}

void Sequence_GetRotation(Sequence* seq, GSvec* out) {
    if (seq != 0) {
        if (!Sequence_IsValid(seq)) {
            out->x = 0.0f;
            out->y = 0.0f;
            out->z = 0.0f;
            return;
        }
        seq->GetRotation(out);
    }
}

void Sequence_GetPosition(Sequence* seq, GSvec* out) {
    if (seq != 0) {
        if (!Sequence_IsValid(seq)) {
            out->x = 0.0f;
            out->y = 0.0f;
            out->z = 0.0f;
            return;
        }
        seq->GetPosition(out);
    }
}

void Sequence_SetScale(Sequence* seq, const GSvec* v) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            seq->SetScale(v);
        }
    }
}

void Sequence_SetRotation(Sequence* seq, const GSvec* v) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            seq->SetRotation(v);
        }
    }
}

void Sequence_SetPosition(Sequence* seq, const GSvec* v) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            seq->SetPosition(v);
        }
    }
}

u32 Sequence_GetPokemonRndVal(Sequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!Sequence_IsValid(seq)) {
        return 0;
    }
    ModelSequence* model = Sequence_AsModel(seq);
    if (model == 0) {
        return 0;
    }
    return model->rnd;
}

u8 Sequence_IsFlipped(Sequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!Sequence_IsValid(seq)) {
        return 0;
    }
    ModelSequence* model = Sequence_AsModel(seq);
    if (model == 0) {
        return 0;
    }
    return model->flipped;
}


void Sequence_SetFlipped(Sequence* seq, s8 flipped) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                model->flipped = flipped;
            }
        }
    }
}

u8 Sequence_IsRare(Sequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!Sequence_IsValid(seq)) {
        return 0;
    }
    ModelSequence* model = Sequence_AsModel(seq);
    if (model == 0) {
        return 0;
    }
    return model->rare;
}

u8 Sequence_GetFlags(Sequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!Sequence_IsValid(seq)) {
        return 0;
    }
    ModelSequence* model = Sequence_AsModel(seq);
    if (model == 0) {
        return 0;
    }
    return model->flags;
}

u16 Sequence_GetID(Sequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (Sequence_IsValid(seq)) {
        return seq->id;
    }
    return 0;
}

u32 Sequence_GetGSmodel(Sequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!Sequence_IsValid(seq)) {
        return 0;
    }
    ModelSequence* model = Sequence_AsModel(seq);
    if (model == 0) {
        return 0;
    }
    return model->model;
}

s8 Sequence_GetModelSize(Sequence* seq) {
    if (seq == 0) {
        return 0;
    }
    if (!Sequence_IsValid(seq)) {
        return 0;
    }
    ModelSequence* model = Sequence_AsModel(seq);
    if (model == 0) {
        return 0;
    }
    return (s8)model->modelSize;
}

void Sequence_SetDownFlag(Sequence* seq, u8 down) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                model->flags = model->flags & ~8;
                if (down != 0) {
                    model->flags = model->flags | 0x10;
                } else {
                    model->flags = model->flags & 0x10;
                }
            }
        }
    }
}

void Sequence_SetLookTarget(Sequence* seq, Sequence* target) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                ModelSequence* t;
                if (model->isPokemon != 0) {
                    return;
                } else {
                    if (Sequence_IsValid(target) && target != 0) {
                        t = Sequence_AsModel(target);
                    } else {
                        t = 0;
                    }
                    if (t != 0 && t->isPokemon == 0) {
                        t = 0;
                    }
                    if (model->lookEnabled != 0) {
                        model->lookTarget = t;
                    }
                }
            }
        }
    }
}

void Sequence_CopyState(Sequence* dst, Sequence* src) {
    if (dst != 0) {
        if (Sequence_IsValid(dst)) {
            ModelSequence* model = Sequence_AsModel(dst);
            if (model != 0) {
                ModelSequence* from;
                if (!Sequence_IsValid(src)) {
                    from = 0;
                } else {
                    from = Sequence_AsModel(src);
                }
                model->CopyState(from);
            }
        }
    }
}

WazaSequence* Sequence_GetWaza(Sequence* seq, u16 a, u16 b) {
    if (seq == 0) {
        return 0;
    }
    if (Sequence_IsValid(seq)) {
        return ((NullSequence*)seq)->GetWaza(a, b);
    }
    return 0;
}

void Sequence_FreeAllWaza(Sequence* seq) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ((NullSequence*)seq)->FreeAllWaza();
        }
    }
}

void Sequence_Free(Sequence* seq) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            delete seq;
        }
    }
}

void Sequence_DoAnimation(Sequence* seq, int anim) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                model->DoModelAnimation(anim);
            }
        }
    }
}

void Sequence_Talk(Sequence* seq) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                model->Talk();
            }
        }
    }
}

void Sequence_SetFlags(Sequence* seq, u8 flags) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                model->SetFlags(flags);
            }
        }
    }
}

void Sequence_SetDefaultFlags(Sequence* seq) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                model->SetDefaultFlags();
            }
        }
    }
}

void Sequence_ResetStatus(Sequence* seq, u8 status) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                model->ResetStatus(status);
            }
        }
    }
}

void Sequence_SetStatus(Sequence* seq, u8 status) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            ModelSequence* model = Sequence_AsModel(seq);
            if (model != 0) {
                model->SetStatus(status);
            }
        }
    }
}

void Sequence_SetVisibility(Sequence* seq, bool visible) {
    if (seq != 0) {
        if (Sequence_IsValid(seq)) {
            seq->SetVisibility(visible);
        }
    }
}

ModelSequence* Sequence_LoadPokemon(u16 id, u32 rnd, bool rare) {
    return New_ModelSequence(id, rnd, rare);
}

ModelSequence* Sequence_LoadTrainer(u16 id) {
    return New_ModelSequence(id);
}

NullSequence* Sequence_CreateNull() {
    return New_NullSequence();
}

}

u32 wazaSequenceSysGetSleepParticle() {
    return g_SleepParticle;
}

u32 wazaSequenceSysGetIceParticle() {
    return g_IceParticle;
}

u32 wazaSequenceSysGetModelShadowLight() {
    return _modelShadowLight;
}

s32 wazaSequenceSysGetModelShadowCount() {
    return _modelShadowCount;
}

u32* wazaSequenceSysGetModelShadowList() {
    return _modelShadowList;
}

extern "C" {

void wazaSequenceSysEnableLayerChange() {
    g_EnableModelLayerChange = 1;
}

s32 wazaSequenceSysGetResID() {
    if ((u32)(_resource_id_count + 0x10000) == 0xFFFF) {
        _resource_id_count = 0;
    }
    return ++_resource_id_count;
}

s32 wazaSequenceSysIsValidSequence(Sequence* seq) {
    Sequence* p = g_Sequences;
    if (seq == 0) {
        return 0;
    }
    for (; p != 0; p = p->next) {
        if (p == seq) {
            return 1;
        }
    }
    return 0;
}

s32 wazaSequenceSysIsValidWaza(WazaSequence* waza) {
    Sequence* p = g_Sequences;
    if (waza == 0) {
        return 0;
    }
    for (; p != 0; p = p->next) {
        WazaSequence* w = p->wazaList;
        for (; w != 0; w = w->next) {
            if (w == waza) {
                return 1;
            }
        }
    }
    return 0;
}

s32 wazaSequenceSysLastWazaIsImpactPoint(u8 point) {
    if (g_LastStartedWaza != 0) {
        return g_LastStartedWaza->IsImpactPoint(point);
    }
    return 1;
}


void wazaSequenceSysFreeAllWazaExcept(Sequence* seq, WazaSequence* except) {
    if (Sequence_IsValid(seq)) {
        WazaSequence* w = seq->wazaList;
        for (; w != 0; ) {
            WazaSequence* next = w->next;
            if (w != except) {
                delete w;
            }
            w = next;
        }
    }
}

}

static void wazaSequenceSysApplyStop() {
    Sequence* seq = g_Sequences;
    for (; seq != 0; seq = seq->next) {
        WazaSequence* w = seq->wazaList;
        for (; w != 0; w = w->next) {
            bool stop = false;
            if (w->active != 0 && w->stopped != 0) {
                stop = true;
            }
            if (stop) {
                w->ApplyStop();
            }
        }
    }
}

extern "C" {

void wazaSequenceSysFreeAllWaza() {
    Sequence* seq = g_Sequences;
    for (; seq != 0; seq = seq->next) {
        ((NullSequence*)seq)->FreeAllWaza();
    }
}

void wazaSequenceSysSetVisibilityAll(bool visible) {
    Sequence* seq = g_Sequences;
    for (; seq != 0; seq = seq->next) {
        seq->SetVisibility(visible);
    }
}

u16 wazaSequenceSysGetActiveWazaNum() {
    u16 count = 0;
    Sequence* seq = g_Sequences;
    for (; seq != 0; seq = seq->next) {
        WazaSequence* w = seq->wazaList;
        for (; w != 0; w = w->next) {
            u8 running = 0;
            if (w->active != 0 && w->stopped == 0) {
                running = 1;
            }
            if (running) {
                count++;
            }
        }
    }
    return count;
}

}

static u32 wazaSequenceSysLoadResource(unsigned long group, unsigned long id) {
    return loadResourceInline(group, id);
}

static void wazaSequenceSysFreeSequenceResource(ModelSequence* seq) {
    u16 g;
    u16 group = seq->resourceGroup;
    if (group != 0) {
        s32 count = 0;
        Sequence* p = g_Sequences;
        for (; p != 0; p = p->next) {
            ModelSequence* m = Sequence_AsModel(p);
            if (m != 0 && group == m->resourceGroup) {
                count++;
            }
        }
        if (count == 1) {
            g = group;
            while (GSfsysGetStatus(g) == 1) {
                GSthreadSwitch();
            }
            GSresFreeGroup(group);
            GSfsysFree(group);
        }
    }
}

static void wazaSequenceSysFreeWazaResource(WazaSequence* waza) {
    u16 g;
    u16 group = waza->resId;
    if (group != 0) {
        Sequence* p = g_Sequences;
        WazaSequence* w;
        s32 count = 0;
        for (; p != 0; p = p->next) {
            w = p->wazaList;
            for (; w != 0; w = w->next) {
                if (group == w->resId) {
                    count++;
                }
            }
        }
        if (count == 1) {
            g = group;
            while (GSfsysGetStatus(g) == 1) {
                GSthreadSwitch();
            }
            GSresFreeGroup(group);
            GSfsysFree(group);
        }
    }
}

static void wazaSequenceSysResetAnimationExcept(ModelSequence* except) {
    Sequence* p = g_Sequences;
    if (except == 0) {
        return;
    }
    for (; p != 0; p = p->next) {
        ModelSequence* m = Sequence_AsModel(p);
        if (except != m && m->isPokemon != 0) {
            m->DoDefaultAnimation(GSMODEL_ANIM_TYPE_1, false);
        }
    }
}

extern "C" {

void wazaSequenceSysRelease() {
    Sequence* p = g_Sequences;
    s32 i;
    u32 zero;
    u32* models;
    while (p != 0) {
        Sequence* next = p->next;
        delete p;
        p = next;
    }
    g_Sequences = 0;
    if (g_IceParticle != 0 || g_SleepParticle != 0) {
        GSresFreeGroup(0x6F7);
        GSfsysFree(0x6F7);
        g_IceParticle = 0;
        g_SleepParticle = 0;
    }
    i = 0;
    zero = i;
    models = gCameraShakeModels;
    do {
        if (*models != 0) {
            GSmodelFree(*models);
            *models = zero;
        }
        i++;
        models++;
    } while (i < 9);
    gCameraShakeModel = 0;
    GSresFreeGroup(0x634);
    GSfsysFree(0x634);
    _modelShadowCount = 0;
    _modelShadowLight = 0;
    memset(_modelShadowList, 0, 0);
    if (g_SoundListener != 0) {
        GSsndFreeListener(g_SoundListener);
        g_SoundListener = 0;
    }
}

void wazaSequenceSysInitExtras() {
    g_IceParticle = loadResourceInline(0x6F7, 0x205D2400);
    g_SleepParticle = loadResourceInline(0x6F7, 0x11052400);
    _wazaSequenceSysCameraShakeInit();
}

u32 wazaSequenceSysGetWazaGroupID(u16 a, u16 b) {
    u16 id = wazaSequenceSysGetResourceID(0, a, b, 0);
    if (id != 0) {
        return waza_resource_data[id * 2];
    }
    return 0;
}

}

extern "C" {

#pragma global_optimizer off
void wazaSequenceSysUpdate() {
    u8 rate = GSgfxVideoGetVsyncRate();
    f32 fr = rate;
    f32 dt = GSgfxVideoGetLastRenderTime(rate) / fr;
    WazaSequence* w;
    Sequence* seq = g_Sequences;
    u32 camera;
    for (; seq != 0; seq = seq->next) {
        w = seq->wazaList;
        for (; w != 0; w = w->next) {
            u8 stop = 0;
            if (w->active != 0 && w->stopped != 0) {
                stop = 1;
            }
            if (stop) {
                w->ApplyStop();
            }
        }
    }
    seq = g_Sequences;
    for (; seq != 0; seq = seq->next) {
        seq->Update(dt);
    }
    camera = GScameraGetActiveCamera();
    if (camera != 0) {
        GSvec pos;
        GSvec look;
        GSvec up;
        GScameraLoadActiveCameraMatrix(-1);
        GScameraGetPosition(camera, &pos);
        GScameraGetLookAt(camera, &up, &look);
        PSVECSubtract(&look, &pos, &look);
        PSVECNormalize(&look, &look);
        if (g_SoundListener != 0) {
            GSsndUpdateListenerParam(g_SoundListener, &pos, &look, &up);
        } else {
            g_SoundListener = GSsndCreateListenerParam(&pos, &zeroVector, &look, &up, 0x7F, 250.0f, 250.0f, 360.0f);
        }
    }
}
#pragma global_optimizer on

}

f32 wazaSequenceSysGetWazaTime(ModelSequence* seq, WazaSequence* waza, u8 phase) {
    f32 t = *(f32*)((u8*)waza + 4);
    u8* rec = *(u8**)((u8*)seq + 0x9C) + waza->index * 0xD0;
    if ((s32)phase == -1) {
        return 0.0f;
    }
    if (phase == 0) {
        return t;
    }
    if (phase == 3 || phase == 4) {
        u8* q = rec + *(s32*)rec * 4;
        return t + *(f32*)(q + 8);
    }
    if (phase == 1) {
        return t + *(f32*)(rec + 0x10);
    }
    if (phase == 2) {
        s32 count = *(s32*)rec;
        u8* q = rec + count * 4;
        if (count > 2) {
            return t + *(f32*)(q + 4);
        }
        return t + *(f32*)(q + 8);
    }
    return 0.0f;
}

struct PartAnimData {
    u8 type;
    u8 count;
    u8 parts[8];
    u8 texParts[8];
    u8 index;
};

extern "C" {
void GSmodelLinkTexAnimToAnim(_GSmodel*, u8);
void GSmodelSetTexAnimType(_GSmodel*, s32);
void GSmodelSetTexAnimFrame(_GSmodel*, f32);
void GSmodelSetPartAnimIndex(_GSmodel*, u32, u32, f32, u32);
void GSmodelSetPartTexAnimIndex(_GSmodel*, u32, u32, u32, f32, u32);
}

void wazaSequenceSysPartAnimationStart(_GSmodel* model, PartAnimData* data) {
    u8 i;
    u8 n;
    u8* part;
    u8* tex;
    switch (data->type) {
    case 1:
        GSmodelLinkTexAnimToAnim(model, 0);
        GSmodelSetTexAnimIndex(model, data->index);
        GSmodelSetTexAnimRate(model, 0.5f);
        GSmodelSetTexAnimType(model, 0);
        GSmodelSetTexAnimFrame(model, 0.0f);
        GSmodelStartTexAnimation(model);
        break;
    case 2:
        n = data->count;
        part = data->parts;
        tex = data->texParts;
        for (i = 0; i < n; i++, part++, tex++) {
            if (*part != 0xFF) {
                if (*tex == 0xFF) {
                    GSmodelSetPartAnimIndex(model, *part, data->index, 0.0f, 0);
                } else {
                    GSmodelSetPartTexAnimIndex(model, *part, *tex, data->index, 0.0f, 0);
                }
            }
        }
        break;
    }
}

extern "C" {

void wazaSequenceSysInit() {
    GSvec pos;
    GSvec look;
    GSvec up;
    s32 floor;
    s32 group;
    u32 shadowNum;
    u32 i;
    u32 camera = GScameraGetActiveCamera();
    Sequence* p = g_Sequences;
    s32 n;
    u32 zero;
    u32* models;
    while (p != 0) {
        Sequence* next = p->next;
        delete p;
        p = next;
    }
    g_Sequences = 0;
    if (g_IceParticle != 0 || g_SleepParticle != 0) {
        GSresFreeGroup(0x6F7);
        GSfsysFree(0x6F7);
        g_IceParticle = 0;
        g_SleepParticle = 0;
    }
    n = 0;
    zero = n;
    models = gCameraShakeModels;
    do {
        if (*models != 0) {
            GSmodelFree(*models);
            *models = zero;
        }
        n++;
        models++;
    } while (n < 9);
    gCameraShakeModel = 0;
    GSresFreeGroup(0x634);
    GSfsysFree(0x634);
    _modelShadowCount = 0;
    _modelShadowLight = 0;
    memset(_modelShadowList, 0, 0);
    if (g_SoundListener != 0) {
        GSsndFreeListener(g_SoundListener);
        g_SoundListener = 0;
    }
    if (camera != 0) {
        GScameraGetPosition(camera, &pos);
        GScameraGetLookAt(camera, &up, &look);
        PSVECSubtract(&look, &pos, &look);
        PSVECNormalize(&look, &look);
        g_SoundListener = GSsndCreateListenerParam(&pos, &zeroVector, &look, &up, 0x7F, 250.0f, 250.0f, 360.0f);
    }
    floor = floorDataBiosGetCurrentPtr();
    group = floorDataBiosGetGroupID();
    switch (floorDataBiosGetFloorKind(floor)) {
    case 4:
        g_EnableModelLayerChange = 1;
        break;
    case 3:
    default:
        g_EnableModelLayerChange = 0;
        break;
    }
    shadowNum = floorDataBiosGetShadowReciveNum(floor);
    if (shadowNum > 0x10) {
        shadowNum = 0x10;
    }
    _modelShadowCount = 0;
    for (i = 0; i < shadowNum; i++) {
        u32 res = (u32)GSresGetResource(group, floorDataBiosGetShadowReciveID(floor, i));
        if (res != 0) {
            _modelShadowList[_modelShadowCount++] = res;
        }
    }
    if (floorDataBiosGetShadowLightID(floor) != 0) {
        _modelShadowLight = (u32)GSresGetResource(group, floorDataBiosGetShadowLightID(floor));
    }
}

}

static void _wazaSequenceSysCameraShakeInit() {
    u32* out = gCameraShakeModels;
    u32 res;
    u32 model;
    res = loadResourceInline(0x634, 0x102E1000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (model != 0) {
            GSmodelSetVisibility(model, 0);
        }
        out++;
    }
    res = loadResourceInline(0x634, 0x102B1000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (*out != 0) {
            GSmodelSetVisibility(*out, 0);
        }
        out++;
    }
    res = loadResourceInline(0x634, 0x10271000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (*out != 0) {
            GSmodelSetVisibility(*out, 0);
        }
        out++;
    }
    res = loadResourceInline(0x634, 0x102C1000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (*out != 0) {
            GSmodelSetVisibility(*out, 0);
        }
        out++;
    }
    res = loadResourceInline(0x634, 0x10281000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (*out != 0) {
            GSmodelSetVisibility(*out, 0);
        }
        out++;
    }
    res = loadResourceInline(0x634, 0x10251000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (*out != 0) {
            GSmodelSetVisibility(*out, 0);
        }
        out++;
    }
    res = loadResourceInline(0x634, 0x102D1000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (*out != 0) {
            GSmodelSetVisibility(*out, 0);
        }
        out++;
    }
    res = loadResourceInline(0x634, 0x10291000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (*out != 0) {
            GSmodelSetVisibility(*out, 0);
        }
        out++;
    }
    res = loadResourceInline(0x634, 0x10261000);
    if (res != 0) {
        model = _wazaSequenceSysLoadModel(res);
        *out = model;
        if (*out != 0) {
            GSmodelSetVisibility(*out, 0);
        }
    }
}

u16 wazaSequenceSysGetResourceID(ModelSequence* seq, u16 waza, u16 kind, u8 variant) {
    u16 end;
    u16 begin;
    int pokemon;
    PokemonWazaEntry* e;
    u16 i;
    if (kind == 0 || kind > 4) {
        return 0;
    }
    if (seq != 0 && seq->isPokemon != 0) {
        pokemon = seq->id;
        if (variant != 0 && variant < WazaSequence::GetNumVariations(waza, kind)) {
            switch (kind) {
            case 1:
                begin = 0x33C;
                end = 0x359;
                break;
            case 2:
                begin = 0x35B;
                end = 0x35B;
                break;
            case 3:
                begin = 0x35D;
                end = 0x361;
                break;
            case 4:
                begin = 0x33A;
                end = 0x33A;
                variant = 0;
                break;
            }
        } else {
            switch (kind) {
            case 1:
                begin = 1;
                end = 0x236;
                break;
            case 2:
                begin = 0x238;
                end = 0x2AB;
                break;
            case 3:
                begin = 0x2AD;
                end = 0x338;
                break;
            case 4:
                begin = 0x33A;
                end = 0x33A;
                break;
            }
        }
        i = begin;
        e = &pokemon_waza_wzx_data[begin];
        for (; i < end; i++, e++) {
            if (e->pokemonId == pokemon && e->wazaId == waza && e->variant == variant) {
                return e->resId;
            }
        }
    }
    if (kind == 4) {
        if (waza == 0 || waza >= waza_generic_wzx_data_number) {
            return 0;
        }
        return waza_generic_wzx_data[waza];
    }
    if (waza == 0 || waza >= waza_wzx_data_number) {
        return 0;
    }
    if (variant != 0) {
        u16 j = 0;
        WazaExtEntry* x = waza_ext_wzx_data;
        for (; j < waza_ext_wzx_data_number; j++, x++) {
            if (x->wazaId == waza && x->variant == variant) {
                u16 r = x->res[(u16)(kind - 1)];
                if (r != 0) {
                    return r;
                }
                return waza_wzx_data[waza][(u16)(kind - 1)];
            }
        }
    }
    return waza_wzx_data[waza][(u16)(kind - 1)];
}
