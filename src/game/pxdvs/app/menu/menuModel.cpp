#include <game/pxdvs/app/menu/menuModelPrivate.hpp>

extern "C" {
s32 pokemonGetStatus(Pokemon *, u16, u16, u16);
u8 pokemonGetAnnonKatati(u32);
u8 pokemonIsJoutaiDataId(Pokemon *, u16);
u32 Sequence_GetGSmodel(u32);
void Sequence_SetCamera(u32, u32);
void Sequence_SetVisibility(u32, u32);
void Sequence_Free(u32);
void Sequence_DoAnimation(u32, u8);
u32 Sequence_LoadPokemon(u16, u32, u8);
u32 Sequence_LoadWaza(u32, u16, u32, u32);
s32 Sequence_GetModelSize(u32);
void WazaSequence_Start(u32, u32);
void WazaSequence_Stop(u32);
void WazaSequence_Free(u32);
u8 WazaSequence_IsActive(u32);
u8 wazaSequenceSysIsValidWaza(u32);
void wazaSequenceSysSetVisibilityAll(u32);
void GSmodelSetRenderCamera(u32, u32);
void GSmodelSetVisibility(u32, u32);
void GSmodelFree(u32);
u8 GSmodelCanAnimate(u32);
void GSmodelSetAnimIndex(u32, u32);
void GSmodelSetAnimRate(u32, f32);
void GSmodelStartAnimation(u32);
void GSmodelSetAnimType(u32, u32);
void GSmodelSetRenderLayer(u32, u32, s32 *);
void GSmodelSetBoundCheck(u32, u32);
void GSlightSetActive(u32, u32);
void GSlightFree(u32);
u32 GSlightCreate();
void GSlightSetType(u32, u32);
void GSlightSetColor(u32, MENU_COLOR);
void GSlightSetPosition(u32, f32 *);
void GSlightSetTarget(u32, f32 *);
u32 GScameraCreate();
void GScameraSetPosition(u32, f32 *);
void GScameraSetRotation(u32, f32 *);
void *memset(void *, int, unsigned long);
void GSthreadSwitch();
u32 GSthreadGetCurrentThread();
u8 GSthreadIsRunning(u32);
void GSthreadClose(u32);
u32 GSthreadCreate(u32, s32, u32, u32, u32, s32 (*)(void *));
void GSthreadSetArgs(u32, u32, ...);
s32 GSfloorGetCurrentFloorGroupID();
void GSlogWrite(const char *, ...);
void GScameraFree(u32);
void GScameraSetScissor(u32, u32, u32, u32, u32);
void GScameraSetViewport(u32, u32, f32, f32, f32, f32);
u32 floorOpenObject(u32);
u8 menuFaceCheckLoading();
}

struct PokemonMenuAnimation {
    u8 anim;
    u8 pad;
    u16 id;
};
extern PokemonMenuAnimation *pokemon_menu_animation;
extern u32 *pokemon_menu_animation_number;

static f32 _menuModelScaleMultiValue = 1.0f;
u8 _modeloff;
static s32 _menuModelRef;
static u8 _litonoff[3] = {1, 1, 1};
static s32 _waitframe = 3;
u8 _checkLarge;

extern "C" void _menuModelMakeLoadInfo__FP15MENU_MODEL_LOADP7PokemonUs(MENU_MODEL_LOAD *, Pokemon *, u16, u8);
#define _menuModelMakeLoadInfo _menuModelMakeLoadInfo__FP15MENU_MODEL_LOADP7PokemonUs
static u8 _menuModelCmpLoadInfo(MENU_MODEL_LOAD *, MENU_MODEL_LOAD *);
static void _menuModelRenderOff(MENU_MODEL *);
static void _menuModelSetupViewport(MENU_MODEL *);
static void _menuModelSetupViewport2(MENU_MODEL *, MENU_MODEL *);
static s32 _menuModelAdjustCamera(MENU_MODEL *, bool);
static s32 _menuModelAdjustCamera2(MENU_MODEL *, MENU_MODEL *);
static s32 _menuModelLoadThread(MENU_MODEL *);
static s32 _menuModelTerm(MENU_MODEL *);

void menuModelGetPkxRndFromPokemonForSeqenceLoad(unsigned long &rnd, unsigned short &id, Pokemon *pokemon) {
    id = pokemonGetStatus(0, pokemonGetStatus(pokemon, 0, 0x6E, 0), 0x66, 0);
    rnd = pokemon->getRnd();
    switch (id) {
    case 0xC9:
        rnd = pokemonGetAnnonKatati(rnd);
        break;
    case 0x19A:
        rnd = 0;
        break;
    case 0xF9:
        if (pokemon->isDarkPokemon()) {
            id = 0x1A1;
        }
        rnd = 0;
        break;
    }
}

extern "C" {

void menuModelReSetScale() {
    _menuModelScaleMultiValue = 1.0f;
}

void menuModelSetScale(f32 scale) {
    _menuModelScaleMultiValue = scale;
}

f32 menuModelGetScale(f32 value) {
    return value * _menuModelScaleMultiValue;
}

u8 menuModelGetPokemonAnimationIndexByID(u16 id) {
    PokemonMenuAnimation *p = pokemon_menu_animation;
    u32 n = *pokemon_menu_animation_number;
    u32 i;
    for (i = 0; i < n; i++, p++) {
        if (p->id == id) {
            return p->anim - 1;
        }
    }
    return 0;
}


u8 menuModelGetPokemonAnimationIndexByPointer(Pokemon *pokemon) {
    return menuModelGetPokemonAnimationIndexByID(pokemon->getPokemonDataId());
}

void menuModelSetCameraRotation(MENU_MODEL *m, f32 *v) {
    m->camRot[0] = v[0];
    m->camRot[1] = v[1];
    m->camRot[2] = v[2];
}

f32 *menuModelGetCameraRotation(MENU_MODEL *m) {
    return m->camRot;
}

u32 menuModelGetModelPtr(MENU_MODEL *m) {
    if (m->cur.isPokemon) {
        return Sequence_GetGSmodel(m->model);
    }
    return m->model;
}

void menuModelSetClip(MENU_MODEL *m, s8 clip) {
    m->clip = clip;
}

void menuModelSetZoom(MENU_MODEL *m, f32 zoom) {
    m->zoom = zoom;
}

void menuModelSetOffset(MENU_MODEL *m, f32 *v) {
    m->offset[0] = v[0];
    m->offset[1] = v[1];
    m->offset[2] = v[2];
}

void menuModelSetAngle(MENU_MODEL *m, f32 *v) {
    m->angle[0] = v[0];
    m->angle[1] = v[1];
    m->angle[2] = v[2];
}

void menuModelAdjustCamera2(MENU_MODEL *a, MENU_MODEL *b) {
    _menuModelAdjustCamera2(a, b);
}

void menuModelAdjustCamera(MENU_MODEL *m) {
    _menuModelAdjustCamera(m, true);
}

}

extern "C" {

s32 menuModelRender2(MENU_MODEL *a, MENU_MODEL *b) {
    u32 modelA;
    u32 modelB;
    s32 i;
    if (a == 0) {
        return 0;
    }
    if (b == 0) {
        return 0;
    }
    if (a->state != 2) {
        return 0;
    }
    if (b->state != 2) {
        return 0;
    }
    if (a->cur.isPokemon) {
        modelA = Sequence_GetGSmodel(a->model);
    } else {
        modelA = a->model;
    }
    if (b->cur.isPokemon) {
        modelB = Sequence_GetGSmodel(b->model);
    } else {
        modelB = b->model;
    }
    if (modelA == 0) {
        return 0;
    }
    if (modelB == 0) {
        return 0;
    }
    if (a->cur.isPokemon) {
        Sequence_SetCamera(a->model, a->camera);
    } else {
        GSmodelSetRenderCamera(a->model, a->camera);
    }
    if (b->cur.isPokemon) {
        Sequence_SetCamera(b->model, a->camera);
    } else {
        GSmodelSetRenderCamera(b->model, a->camera);
    }
    _menuModelSetupViewport2(a, b);
    for (i = 0; i < 3; i++) {
        if (a->light[i] != 0) {
            GSlightSetActive(a->light[i], _litonoff[i]);
        }
    }
    return 0;
}

s32 menuModelRender(MENU_MODEL *m) {
    u32 model;
    s32 i;
    if (_modeloff) {
        return 0;
    }
    if (m->enable == 0) {
        return 0;
    }
    if (m == 0) {
        return 0;
    }
    if (m->state != 2) {
        return 0;
    }
    if (m->cur.isPokemon) {
        if (m->model == 0) {
            return 0;
        }
        model = Sequence_GetGSmodel(m->model);
    } else {
        model = m->model;
    }
    if (model == 0) {
        return 0;
    }
    if (m->cur.isPokemon) {
        Sequence_SetCamera(m->model, m->camera);
    } else {
        GSmodelSetRenderCamera(m->model, m->camera);
    }
    _menuModelSetupViewport(m);
    for (i = 0; i < 3; i++) {
        if (m->light[i] != 0) {
            GSlightSetActive(m->light[i], _litonoff[i]);
        }
    }
    if (m->cur.isPokemon && m->cur.isPokemon && m->waza != 0 && wazaSequenceSysIsValidWaza(m->waza) == 1 && WazaSequence_IsActive(m->waza) == 0) {
        WazaSequence_Start(m->waza, 0);
        Sequence_DoAnimation(m->model, m->cur.anim);
    }
    return 0;
}

}

static void _menuModelRenderOff(MENU_MODEL *m) {
    if (m->cur.isPokemon) {
        if (m->model != 0) {
            Sequence_SetVisibility(m->model, 0);
        }
        if (m->waza != 0 && wazaSequenceSysIsValidWaza(m->waza) == 1 && WazaSequence_IsActive(m->waza) == 1) {
            WazaSequence_Stop(m->waza);
        }
    } else if (m->model != 0) {
        GSmodelSetVisibility(m->model, 0);
    }
}

extern "C" {

void menuModelRenderOffAll(MENU_MODEL *m) {
    _menuModelRenderOff(m);
}

bool menuModelCheck(MENU_MODEL *m, u8 wait) {
    if (m == 0) {
        return 0;
    }
    if (wait) {
        for (;;) {
            if (m->thread != 0 || m->state == 1) {
                GSthreadSwitch();
            } else {
                break;
            }
        }
        return 0;
    }
    if (m->thread == 0) {
        return 0;
    } else {
        return m->state == 1;
    }
}

s32 menuModelFreeNext(MENU_MODEL *m) {
    if (m == 0) {
        return 0;
    }
    m->loading = 0;
    if (m->req.isPokemon) {
        if (m->nextModel != 0) {
            Sequence_SetVisibility(m->nextModel, 0);
            Sequence_Free(m->nextModel);
            m->nextModel = 0;
        }
    } else if (m->nextModel != 0) {
        GSmodelFree(m->nextModel);
        m->nextModel = 0;
    }
    m->state = 0;
    return 1;
}

void menuModelWazaFree(MENU_MODEL *m) {
    if (m != 0 && m->cur.isPokemon && m->waza != 0) {
        WazaSequence_Free(m->waza);
        m->waza = 0;
    }
}

s32 menuModelFree(MENU_MODEL *m) {
    if (m == 0) {
        return 0;
    }
    m->loading = 0;
    if (m->cur.isPokemon) {
        if (m->model != 0) {
            Sequence_SetVisibility(m->model, 0);
            Sequence_Free(m->model);
            m->model = 0;
        }
    } else if (m->model != 0) {
        GSmodelFree(m->model);
        m->model = 0;
    }
    m->state = 0;
    return 1;
}

u8 menuModelComparePokemon(MENU_MODEL *m, Pokemon *pokemon);
u8 menuModelCompareObject(MENU_MODEL *m, u32 id);

s32 fn_80112AAC(MENU_MODEL *m, Pokemon *pokemon) {
    if (m == 0) {
        return 0;
    }
    if (menuModelComparePokemon(m, pokemon)) {
        return 0;
    }
    switch (m->state) { case 0: m->state = 1; break; case 1: break; case 2: break; }
    _menuModelMakeLoadInfo(&m->req, pokemon, 0, 0);
    m->loading = 1;
    if (m->thread != 0) {
        if (GSthreadIsRunning(m->thread)) {
            return 1;
        }
        GSthreadClose(m->thread);
    }
    wazaSequenceSysSetVisibilityAll(0);
    m->thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (s32 (*)(void *))_menuModelLoadThread);
    if (m->thread != 0) {
        GSthreadSetArgs(m->thread, 1, m);
    }
    return 1;
}

s32 menuModelLoadPokemon(MENU_MODEL *m, Pokemon *pokemon) {
    if (m == 0) {
        return 0;
    }
    if (menuModelComparePokemon(m, pokemon)) {
        return 0;
    }
    switch (m->state) { case 0: m->state = 1; break; case 1: break; case 2: break; }
    _menuModelMakeLoadInfo(&m->req, pokemon, 0, 1);
    m->loading = 1;
    if (m->thread != 0) {
        if (GSthreadIsRunning(m->thread)) {
            return 1;
        }
        GSthreadClose(m->thread);
    }
    wazaSequenceSysSetVisibilityAll(0);
    m->thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (s32 (*)(void *))_menuModelLoadThread);
    if (m->thread != 0) {
        GSthreadSetArgs(m->thread, 1, m);
    }
    return 1;
}

s32 menuModelLoad(MENU_MODEL *m, u32 id) {
    if (m == 0) {
        return 0;
    }
    if (menuModelCompareObject(m, id)) {
        return 0;
    }
    switch (m->state) { case 0: m->state = 1; break; case 1: break; case 2: break; }
    m->req.isPokemon = 0;
    m->req.u.objectId = id;
    m->loading = 1;
    if (m->thread != 0) {
        if (GSthreadIsRunning(m->thread)) {
            return 1;
        }
        GSthreadClose(m->thread);
    }
    m->thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, (s32 (*)(void *))_menuModelLoadThread);
    if (m->thread != 0) {
        GSthreadSetArgs(m->thread, 1, m);
    }
    return 0;
}

u8 menuModelComparePokemon(MENU_MODEL *m, Pokemon *pokemon) {
    MENU_MODEL_LOAD info;
    if (m == 0) {
        return 0;
    }
    _menuModelMakeLoadInfo(&info, pokemon, 0, 1);
    if (m->loading) {
        return _menuModelCmpLoadInfo(&m->req, &info);
    }
    return _menuModelCmpLoadInfo(&m->cur, &info);
}

u8 menuModelCompareObject(MENU_MODEL *m, u32 id) {
    MENU_MODEL_LOAD info;
    if (m == 0) {
        return 0;
    }
    info.u.objectId = id;
    info.isPokemon = 0;
    info.rnd = 0;
    if (m->loading) {
        return _menuModelCmpLoadInfo(&m->req, &info);
    }
    return _menuModelCmpLoadInfo(&m->cur, &info);
}

}

static u8 _menuModelCmpLoadInfo(MENU_MODEL_LOAD *a, MENU_MODEL_LOAD *b) {
    if (a->isPokemon == b->isPokemon) {
        if (a->isPokemon) {
            if (a->u.p.id == b->u.p.id && a->u.p.waza == b->u.p.waza && a->rnd == b->rnd && a->shiny == b->shiny) {
                return 1;
            }
        } else if (a->u.objectId == b->u.objectId) {
            return 1;
        }
    }
    return 0;
}

extern "C" void _menuModelMakeLoadInfo__FP15MENU_MODEL_LOADP7PokemonUs(MENU_MODEL_LOAD *info, Pokemon *pokemon, u16 waza, u8 withShiny) {
    info->isPokemon = 1;
    if (pokemonGetStatus(pokemon, 0, 0xC2, 0)) {
        if (pokemonIsJoutaiDataId(pokemon, 0x3E) == 1) {
            info->u.p.waza = 0x87;
        } else {
            info->u.p.waza = 0x25;
        }
    } else {
        info->u.p.waza = waza;
    }
    menuModelGetPkxRndFromPokemonForSeqenceLoad(info->rnd, info->u.p.id, pokemon);
    if (withShiny) {
        info->shiny = pokemonGetStatus(pokemon, 0, 0xC1, 0) != 0;
    } else {
        info->shiny = 0;
    }
    info->anim = menuModelGetPokemonAnimationIndexByPointer(pokemon);
}

extern "C" {

s32 menuModelInit(MENU_MODEL *m, s32 a, s32 b) {
    f32 pos[3];
    f32 rot[3];
    f32 target[3];
    s32 i;
    u32 light;
    pos[0] = 15.0f;
    pos[1] = 15.0f;
    pos[2] = 15.0f;
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 0.0f;
    target[0] = 0.0f;
    target[1] = 0.0f;
    target[2] = 0.0f;
    MENU_COLOR colorA = {0xFF, 0xFF, 0xFF, 0xFF};
    MENU_COLOR colorB = {0x80, 0x80, 0x80, 0xFF};
    if (m == 0) {
        return 0;
    }
    memset(m, 0, 0xEC);
    m->initialized = 1;
    m->enable = 1;
    m->unkC = 0.0f;
    if (_menuModelRef >= 4) {
        GSlogWrite("[%s] 参照回数上限オーバー\n", __FUNCTION__);
        return 0;
    }
    m->sizeW = a;
    m->sizeH = b;
    m->sizeX = 0;
    m->sizeY = 0;
    m->unk84 = 1;
    m->zoom = 1.0f;
    m->clip = 1;
    m->angle[0] = 0.0f;
    m->angle[1] = 0.0f;
    m->angle[2] = 0.0f;
    m->offset[0] = 0.0f;
    m->offset[1] = 0.0f;
    m->offset[2] = 0.0f;
    m->camera = GScameraCreate();
    if (m->camera == 0) {
        GSlogWrite("[%s] カメラの確保に失敗\n", __FUNCTION__);
        return 0;
    }
    GScameraSetPosition(m->camera, pos);
    GScameraSetRotation(m->camera, rot);
    for (i = 0; i < 3; i++) {
        light = GSlightCreate();
        if (light != 0) {
            switch (i) {
            case 0:
                GSlightSetType(light, 0);
                GSlightSetColor(light, colorB);
                break;
            case 1:
                GSlightSetType(light, 1);
                GSlightSetColor(light, colorA);
                GSlightSetPosition(light, pos);
                GSlightSetTarget(light, target);
                break;
            case 2:
                pos[0] = 10.0f;
                pos[1] = 10.0f;
                pos[2] = 10.0f;
                GSlightSetType(light, 2);
                GSlightSetColor(light, colorA);
                GSlightSetPosition(light, pos);
                GSlightSetTarget(light, target);
                break;
            }
            GSlightSetActive(light, 0);
            m->light[i] = light;
        }
    }
    m->camRot[0] = 0.0f;
    m->camRot[1] = 0.0f;
    m->camRot[2] = 0.0f;
    _menuModelRef++;
    return 1;
}

s32 menuModelSetSize(MENU_MODEL *m, s32 x, s32 y, s32 w, s32 h) {
    if (m == 0) {
        return 0;
    }
    m->sizeX = x;
    m->sizeY = y;
    m->sizeW = w;
    m->sizeH = h;
    return 1;
}

}

extern "C" {

s32 menuModelTerm(MENU_MODEL *m) {
    return _menuModelTerm(m);
}

}

static s32 _menuModelTerm(MENU_MODEL *m) {
    s32 i;
    u8 hasNext;
    if (m == 0) {
        return 0;
    }
    if (m->initialized == 0) {
        return 0;
    }
    if (_menuModelRef <= 0) {
        GSlogWrite("[%s] 必要以上に開放しようとしました\n", __FUNCTION__);
        return 0;
    }
    m->loading = 0;
    m->initialized = 0;
    if (GSthreadGetCurrentThread() != 0) {
        for (;;) {
            if (m->thread == 0) {
                break;
            }
            if (GSthreadIsRunning(m->thread) == 0) {
                GSthreadClose(m->thread);
                break;
            }
            GSthreadSwitch();
        }
    } else if (m->thread != 0) {
        GSthreadClose(m->thread);
        m->thread = 0;
    }
    hasNext = 0;
    if (m->model != m->nextModel) {
        hasNext = 1;
    }
    menuModelFree(m);
    if (hasNext) {
        menuModelFreeNext(m);
    }
    for (i = 0; i < 3; i++) {
        if (m->light[i] != 0) {
            GSlightFree(m->light[i]);
            m->light[i] = 0;
        }
    }
    if (m->camera != 0) {
        GScameraFree(m->camera);
        m->camera = 0;
    }
    _menuModelRef--;
    return 1;
}


static s32 _layerID = 2;

static s32 _menuModelLoadThread(MENU_MODEL *m) {
    u32 model;
    if (m == 0) {
        return 0;
    }
    m->unkC = 0.0f;
    if (m->loading == 0) {
        return 0;
    }
    while (menuFaceCheckLoading()) {
        GSthreadSwitch();
    }
    wazaSequenceSysSetVisibilityAll(0);
    _menuModelRenderOff(m);
    if (m->cur.u.p.waza != 0) {
        menuModelWazaFree(m);
    }
    do {
        if (m->model != m->nextModel) {
            menuModelFreeNext(m);
        }
        m->state = 1;
        m->loading = 0;
        m->cur.isPokemon = m->req.isPokemon;
        m->cur.u.objectId = m->req.u.objectId;
        m->cur.rnd = m->req.rnd;
        m->cur.unkC = m->req.unkC;
        m->cur.shiny = m->req.shiny;
        m->cur.anim = m->req.anim;
        if (m->cur.isPokemon) {
            m->nextModel = Sequence_LoadPokemon(m->cur.u.p.id, m->cur.rnd, m->cur.shiny);
            if (m->nextModel == 0) {
                m->state = 0;
                return 0;
            }
            model = Sequence_GetGSmodel(m->nextModel);
            if (model == 0) {
                m->state = 0;
                return 0;
            }
            if (m->cur.u.p.waza != 0) {
                u32 waza = Sequence_LoadWaza(m->nextModel, m->cur.u.p.waza, 4, 0);
                m->nextWaza = waza;
                if (waza != 0) {
                    WazaSequence_Start(m->nextWaza, 0);
                }
            }
            Sequence_DoAnimation(m->nextModel, m->cur.anim);
        } else {
            m->nextModel = floorOpenObject(m->cur.u.objectId);
            if (m->nextModel == 0) {
                return 0;
            }
            if (GSmodelCanAnimate(m->nextModel)) {
                GSmodelSetAnimIndex(m->nextModel, m->cur.rnd);
                GSmodelSetAnimRate(m->nextModel, 0.5f);
                GSmodelStartAnimation(m->nextModel);
            }
            model = m->nextModel;
        }
        GSmodelSetVisibility(model, 0);
        GSmodelSetAnimType(model, 1);
        GSmodelSetRenderLayer(model, 1, &_layerID);
        GSmodelSetBoundCheck(model, 0);
    } while (m->loading == 1);
    menuModelFree(m);
    m->state = 1;
    m->unk80 = 0;
    m->model = m->nextModel;
    m->waza = m->nextWaza;
    _menuModelAdjustCamera(m, false);
    m->boundValid = 0;
    m->nextModel = 0;
    m->nextWaza = 0;
    m->state = 2;
    m->thread = 0;
    return 1;
}

static void _menuModelSetupViewport(MENU_MODEL *m) {
    f32 fx;
    f32 fy;
    f32 w;
    f32 h;
    f32 baseW;
    f32 baseH;
    f32 ox;
    f32 oy;
    s32 sw;
    s32 sh;
    s32 sx;
    s32 sy;
    if (m->camera != 0) {
        sw = m->sizeW;
        sh = m->sizeH;
        sx = m->sizeX;
        sy = m->sizeY;
        w = (f32)sw;
        h = (f32)sh;
        fx = (f32)sx;
        fy = (f32)sy;
        baseW = w;
        baseH = h;
        if (_checkLarge != 0) {
            if (w > h) {
                w = 1.3333334f * h;
            } else {
                h = w / 1.3333334f;
            }
        } else if (w < h) {
            w = 1.3333334f * h;
        } else {
            h = w / 1.3333334f;
        }
        ox = 0.5f * (baseW - w);
        oy = 0.5f * (baseH - h);
        fx = fx + ox;
        fy = fy + oy;
        if (m->clip != 0) {
            GScameraSetScissor(1, (u16)sx, (u16)sy, (u16)sw, (u16)sh);
        } else {
            GScameraSetScissor(0, 0, 0, 0x280, 0x1E0);
        }
        if (fx < 0.0f) {
            fx = 0.0f;
        }
        if (fy < 0.0f) {
            fy = 0.0f;
        }
        GScameraSetViewport(m->camera, 1, fx, fy, 0.5f * w + fx, 0.5f * h + fy);
        if (m->unk80 < _waitframe) {
            m->unk80++;
        }
        if (m->unk80 >= _waitframe) {
            if (m->cur.isPokemon) {
                Sequence_SetVisibility(m->model, 1);
                Sequence_SetCamera(m->model, m->camera);
            } else {
                GSmodelSetVisibility(m->model, 1);
                GSmodelSetRenderCamera(m->model, m->camera);
            }
        }
    }
}
