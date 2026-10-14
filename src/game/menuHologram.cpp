#include <game/menuHologramLayout.hpp>

extern "C" {
void *GSmemAllocClr(u32);
void GSmemFree(void *);
void GSmodelSetAnimIndex(void *, s32);
void GSmodelSetAnimType(void *, s32);
void GSmodelStartAnimation(void *);
void *GSresGetResourceAllGroup(u32);
GSgfxLayer *GSgfxLayerFindByID(GSgfxLayerID);
void Sequence_SetVisibility(u32, s32);
void Sequence_Free(u32);
void WazaSequence_Free(u32);
void GSmodelSetVisibility(void *, s32);
void scriptModelClose(s32);
void GSlightFree(s32);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
void cameraSetType(s32);
void GSmodelFree(void *);
void *memset(void *, int, u32);
void Sequence_SetPosition(u32, f32 *);
u32 Sequence_LoadPokemon(u16, u32, s32);
void *Sequence_GetGSmodel(u32);
u32 Sequence_LoadWaza(u32, u16, s32, s32);
void WazaSequence_Start(u32, s32);
void Sequence_DoAnimation(u32, u8);
void GSmodelSetForceUseFractionalFramesFlag(void *, s32);
void GSmodelSetSkipFractionalFramesFlag(void *, s32);
s32 menuModelGetPokemonAnimationIndexByPointer(Pokemon *);
u8 pokemonIsJoutaiDataId(Pokemon *, s32);
s32 pokemonGetStatus(Pokemon *, s32, s32, s32);
void Sequence_SetScale(u32, f32 *);
struct ReliveHallData {
    u8 reserved0[4];
    u16 unk4;
};
extern ReliveHallData *relivehall_data;
void *memcpy(void *, const void *, u32);
void GStextureFree(GStexture *);
GStexture *GStextureCreate(s32, s32, s32, s32, s32);
void *HSD_ArchiveGetPublicAddress(void *, const char *);
u32 soundGetBGMID(void);
void soundStop(u32, s32);
extern GSgfxColAu8 GSgfxColAu8_Black;
extern GSgfxColAu8 relivehallAisyou2ColorTbl[];
}

s32 reliveHallPokemonToAisyou(Pokemon *, Pokemon *);
extern u8 pcReliveHallSoundTbl[];
long relivehallGetLastViewStage(void);
void menuModelGetPkxRndFromPokemonForSeqenceLoad(unsigned long &, unsigned short &, Pokemon *);
f32 menuGetPokemonScale(u32, int);
void menuPtPlayBgm(u32);

inline void *operator new(unsigned long, void *p)
{
    return p;
}

struct GSpart;
enum GSpartMixType { GSPART_MIX_0 };

struct GSvec {
    f32 x;
    f32 y;
    f32 z;
    GSvec(f32 ax, f32 ay, f32 az)
    {
        x = ax;
        y = ay;
        z = az;
    }
};

namespace {

CMenuHologram *pMenuHologram;

void thisExec(CMenuGlobalState &);
void thisFree();
void thisNew();

void thisExec(CMenuGlobalState &state)
{
    thisNew();
    pMenuHologram->main(state);
    thisFree();
}

void thisFree()
{
    if (pMenuHologram != 0) {
        GSmemFree(pMenuHologram);
        pMenuHologram = 0;
    }
}

void thisNew()
{
    CMenuHologram *p = (CMenuHologram *)GSmemAllocClr(0x418);
    new (p) CMenuHologram;
    pMenuHologram = p;
}

void CMenuHologram::setStage(int index)
{
    stageIndex = index;
    stageIndex2 = index;
    stage = CReliveHall::getPointer()->getStage(stageIndex);
}

void CMenuHologram::setStageToReliveReady()
{
    int i = 0;
    do {
        if (CReliveHall::getPointer()->getStage(i)->isReliveReady()) {
            break;
        }
        i++;
    } while (i < 9);
    if (i == 9) {
        setStage(relivehallGetLastViewStage());
    } else {
        setStage(i);
    }
}

void CMenuHologram::moveStageWait(int index)
{
    systemFadeOutSetAndWait(0.1f);
    unloadDatas();
    setStage(index);
    reloadDatas(true);
    systemFadeInKick();
}

void CMenuHologram::reloadDatas(bool kick)
{
    stageAllModelLoad();
    if (slots[0].model != 0) {
        GSmodelSetAnimIndex(slots[0].model, 2);
        GSmodelSetAnimType(slots[0].model, 1);
        GSmodelStartAnimation(slots[0].model);
    }
    if (slots[1].model != 0) {
        GSmodelSetAnimIndex(slots[1].model, 2);
        GSmodelSetAnimType(slots[1].model, 1);
        GSmodelStartAnimation(slots[1].model);
    }
    localWindowCreateAll();
    if (kick) {
        bgmKick();
    }
}

static long localWindowTable[] = { 0x71, 0x72, 0x88, 0xD0, 0x87, 0 };

void CMenuHologram::init(CMenuGlobalState &gstate)
{
    time1 = 0;
    time0 = 0;
    state.init();
    fadeTime = 0;
    fadeState = 0;
    memset(windows, 0, 0x100);
    memset(windowFuncs, 0, 0x100);
    windowTable = defautlLocalWindowOpenTable;
    if (pcReliveHallSoundTbl != 0) {
        memcpy(sound, pcReliveHallSoundTbl, 0x14);
    }
    tutorialActive = 0;
    unk32C = 0;
    unk32E = 0;
    memset(keyInfo, 0, 0x1A);
    repeatCount = 0;
    lastKey = 0;
    unk375 = 0;
    stageIndex = 0;
    stageIndex2 = 0;
    stage = 0;
    unk344 = 0;
    memset(lights, 0, sizeof(lights));
    lightCount = 0;
    offscreenTexture = 0;
    stageLoaded = 0;
    unk37C = 0;
    unk380 = 0;
    unk384 = 0;
    globalState = &gstate;
    localWindowSetTable(localWindowTable);
    infoWindow.init(0xD0, 0x5DA);
    setStageToReliveReady();
    reloadDatas(true);
}

s32 CMenuHologram::model_z_layer = -1;

void CMenuHologram::releaseOffscreenData()
{
    GSgfxLayer *layer = GSgfxLayerFindByID((GSgfxLayerID)2);
    layer->SetClearFlags(false, false, false);
    layer->SetTextureCopy(0, false, 0);
    if (model_z_layer != -1) {
        GSgfxLayerConfig::Remove((GSgfxLayerID)model_z_layer);
        model_z_layer = -1;
    }
    GSgfxLayerConfig::Move((GSgfxLayerID)2, (GSgfxLayerID)4, (GSgfxLayerOffset)1);
    if (offscreenTexture != 0) {
        GStextureFree(offscreenTexture);
        offscreenTexture = 0;
    }
}

void CMenuHologram::initializeOffscreenData()
{
    offscreenTexture = GStextureCreate(0, 0, 0x45, 0, 0);
    if (offscreenTexture != 0) {
        GSgfxLayer *layer;
        GSgfxLayerConfig::Move((GSgfxLayerID)2, (GSgfxLayerID)0, (GSgfxLayerOffset)1);
        if (model_z_layer == -1) {
            GSgfxLayer *zlayer;
            model_z_layer = GSgfxLayerConfig::Add("model z layer", 0xE000, 0x2000, 8, (GSgfxLayerType)0, false, false, false,
                                                  (GSgfxLayerID)2, (GSgfxLayerOffset)1);
            zlayer = GSgfxLayerFindByID((GSgfxLayerID)model_z_layer);
            if (zlayer != 0) {
                zlayer->SetClearFlags(true, true, false);
            }
        }
        layer = GSgfxLayerFindByID((GSgfxLayerID)2);
        layer->SetTextureCopy(offscreenTexture, false, 0);
        layer->SetClearFlags(true, true, true);
    }
}

void CMenuHologram::stageAllModelUnLoad()
{
    if (stageLoaded != 0) {
        u8 *slot;
        u32 i;
        s32 j;
        u8 *light;
        if (unk384 != 0) {
            Sequence_SetVisibility(unk384, 0);
            Sequence_Free(unk384);
            unk384 = 0;
        }
        if (unk380 != 0) {
            WazaSequence_Free(unk380);
            Sequence_Free(unk37C);
        }
        unk380 = 0;
        unk37C = 0;
        releaseOffscreenData();
        for (slot = (u8 *)this, i = 0; i < 7; slot += 12, i++) {
            void *model = *(void **)(slot + 0x38C);
            if (model != 0) {
                if (*(u32 *)(slot + 0x390) != 0) {
                    Sequence_SetVisibility(*(u32 *)(slot + 0x390), 0);
                    Sequence_Free(*(u32 *)(slot + 0x390));
                } else {
                    GSmodelSetVisibility(model, 0);
                    scriptModelClose(*(s32 *)(slot + 0x388));
                }
            }
        }
        memset(slots, 0, sizeof(slots));
        light = (u8 *)this;
        j = 0;
        while (j < lightCount) {
            GSlightFree(*(s32 *)(light + 0x348));
            light += 4;
            j++;
        }
        memset(lights, 0, sizeof(lights));
        lightCount = 0;
        if (resGroup != 0) {
            GSfsysFree(resGroup);
            GSresFreeGroup(resGroup);
            resGroup = 0;
        }
        cameraSetType(3);
        if (stageModel != 0) {
            GSmodelFree(stageModel);
            stageModel = 0;
        }
        stageLoaded = 0;
    }
}

ModelSlot *CMenuHologram::modelPokemonLoad(long index)
{
    ModelSlot *slot = &slots[index];
    Pokemon *pokemon;
    u16 waza;
    u16 id;
    unsigned long rnd;
    memset(slot, 0, 12);
    if (index == 2) {
        pokemon = stage->getVisitorPointer();
    } else {
        pokemon = stage->getDancerPointer(index - 3);
    }
    if (pokemon == 0) {
        return 0;
    }
    waza = 0;
    if (pokemon->isDarkPokemon() && !stage->isReliveReady()) {
        if (pokemonIsJoutaiDataId(pokemon, 0x3E) == 1) {
            waza = 0x87;
        } else {
            waza = 0x25;
        }
    }
    menuModelGetPkxRndFromPokemonForSeqenceLoad(rnd, id, pokemon);
    slot->sequence = Sequence_LoadPokemon(id, rnd, pokemonGetStatus(pokemon, 0, 0xC1, 0) != 0);
    slot->model = Sequence_GetGSmodel(slot->sequence);
    Sequence_SetVisibility(slot->sequence, 1);
    if (waza != 0) {
        u32 seq = Sequence_LoadWaza(slot->sequence, waza, 4, 0);
        if (seq != 0) {
            WazaSequence_Start(seq, 0);
        }
    }
    Sequence_DoAnimation(slot->sequence, menuModelGetPokemonAnimationIndexByPointer(pokemon));
    GSmodelSetForceUseFractionalFramesFlag(slot->model, 1);
    GSmodelSetSkipFractionalFramesFlag(slot->model, 1);
    return slot;
}

ModelSlot *CMenuHologram::modelPokemonSetScale(long index)
{
    ModelSlot *slot = &slots[index];
    Pokemon *pokemon;
    f32 scale;
    f32 v[3];
    if (index == 2) {
        pokemon = stage->getVisitorPointer();
    } else {
        pokemon = stage->getDancerPointer(index - 3);
    }
    if (pokemon == 0) {
        return 0;
    }
    u16 id = pokemon->getPokemonDataId();
    f32 m = menuGetPokemonScale(slot->sequence, id);
    scale = m * (f32)relivehall_data->unk4 / 100.0f;
    v[0] = scale;
    v[1] = scale;
    v[2] = scale;
    Sequence_SetScale(slot->sequence, v);
    return slot;
}

void CMenuHologram::modelVisitorSetYPosition(long index)
{
    ModelSlot *slot = &slots[index];
    f32 pos[3];
    u16 id = stage->getVisitorPointer()->getPokemonDataId();
    f32 y = 0.0f;
    switch (id) {
    case 0xA5:
        y = -2.0f;
        break;
    case 0xA6:
        y = -10.0f;
        break;
    case 0x14A:
        y = -6.5f;
        break;
    case 0x14B:
        y = -20.0f;
        break;
    case 0x169:
        break;
    case 0x16A:
        break;
    case 0x15:
        y = -2.0f;
        break;
    case 0x16:
        y = -9.0f;
        break;
    case 0xF:
        y = -5.5f;
        break;
    case 0xC:
        y = -8.0f;
        break;
    case 0x31:
        y = -9.0f;
        break;
    case 0x46:
        y = -2.0f;
        break;
    case 0x47:
        y = -6.5f;
        break;
    case 0x52:
        break;
    case 0x15D:
        y = -6.5f;
        break;
    case 0x83:
        y = -6.5f;
        break;
    }
    pos[1] = y;
    pos[0] = 0.0f;
    pos[2] = 0.0f;
    Sequence_SetPosition(slot->sequence, pos);
}

void CMenuHologram::unloadDatas()
{
    localWindowDeleteAll();
    stageAllModelUnLoad();
}

GSgfxColAu8 CMenuHologram::pokemonToAisyouColor(Pokemon *a, Pokemon *b)
{
    GSgfxColAu8 color;
    s32 aisyou = reliveHallPokemonToAisyou(a, b);
    if (aisyou == -1) {
        color = GSgfxColAu8_Black;
    } else {
        color = relivehallAisyou2ColorTbl[aisyou];
    }
    return color;
}

void CMenuHologram::bgmStop()
{
    soundStop(soundGetBGMID(), 50);
}

void CMenuHologram::bgmKick()
{
    u32 bgm;
    s32 tempo;
    stage->getState();
    tempo = stage->getTempo();
    if (tempo <= 0) {
        bgm = 0x5BB;
    } else if (tempo <= 0x35) {
        bgm = 0x510;
    } else if (tempo <= 0x5F) {
        bgm = 0x50F;
    } else {
        bgm = 0x50E;
    }
    if (bgm != soundGetBGMID()) {
        menuPtPlayBgm(bgm);
    }
}

void _getNeckRotationCB(GSpart *, GSpartMixType, void *, GSvec *out)
{
    static GSvec neckRotVec(-0.7853982f, 0.0f, 0.0f);
    *out = neckRotVec;
}

void CMenuHologram::main(CMenuGlobalState &state)
{
    systemFadeOutKeepAfterFloorPush();
    init(state);
    systemFadeInKick();
    loop();
    unloadDatas();
    bgmStop();
}

void *_makeArchiveHeader(u32 group)
{
    return HSD_ArchiveGetPublicAddress(GSresGetResourceAllGroup(group), "");
}

}

extern "C" {
void menuHologramReloadDatas(void)
{
    pMenuHologram->reloadDatas(false);
}

void menuHologramUnloadDatas(void)
{
    pMenuHologram->unloadDatas();
}
}

void menuHologramExecFromPcBox(CMenuGlobalState &state)
{
    thisExec(state);
}
