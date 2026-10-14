#include <game/menuPdaDPMonitorLayout.hpp>
#ifdef __cplusplus
extern "C" {
#endif

void *__nw__FUl(u32);
void __dl__FPv(void *);
void menuModelTerm(DpmModel *);
void menuModelInit(DpmModel *, s16, s16);
void menuModelLoadPokemon(DpmModel *, DpmPokemon *);
u8 menuModelCheck(DpmModel *, s32);
void menuModelAdjustCamera(DpmModel *);
void menuModelSetAngle(DpmModel *, f32 *);
void menuModelSetSize(DpmModel *, s16, s16, s16, s16);
void menuModelSetZoom(DpmModel *, f32);
DpmTexture *menuModelRender(DpmModel *);
DpmLayer *GSgfxLayerFindByID(s32);
void *GSgfxVFGetPredef(s32);
void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(DpmLayer *, void *);
void beginSurface__10GSgfxLayerFUs(DpmLayer *, u16);
void endSurface__10GSgfxLayerFv(DpmLayer *);
DpmItem *menuItemBiosGetPtr(s32, s16);
s32 menuOpenCustom(s32, s32, ...);
s32 windowGetActiveID(void);
void menuClose(s32);
void menuCloseSync(s32, s32);
DpmKey *windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
u8 winSeqCheckMove(s32);
void winSeqSetMenu(s32, s32);
void GSsndPlayNow(u32);
void menuPlaySe(s32, s32);
void menuPdaSetSubres(s32, s32);
void menuDrawReliveUpdate(void);
s32 menuPdaDPMListGetDPNum(void);
DpmDarkPokemon *darkPokemonGetDarkPokemon(u16);
u32 menuPdaDPMListGetDarkPokemonID(s32);
s32 menuPdaDPMListGetDarkpokemonID(s32);
s32 menuPdaDPMListGetPokemonID(s32);
DpmDarkPokemon *menuPdaDPMListGetDPointer(s32);
u32 menuPdaDPMListGetPokemonName(s32);
u32 menuPdaDPMListGetDarkPokemonPlaceMsgID(s32, u8 *);
void menuPdaDPMListDispRelive(DpmWindow *, DpmSprite *, s32, s32, s32, u8, s32);
u8 isUpdate__11DarkPokemonCFv(DpmDarkPokemon *);
void setUpdate__11DarkPokemonFb(DpmDarkPokemon *, u8);
s32 getStatus__11DarkPokemonCFv(DpmDarkPokemon *);
u16 getCatchFloorId__11DarkPokemonCFv(DpmDarkPokemon *);
u16 getPokemonID__11DarkPokemonCFv(DpmDarkPokemon *);
u32 getOrgTrainer__11DarkPokemonCFv(DpmDarkPokemon *);
u32 getTrainerName__11DarkPokemonCFv(DpmDarkPokemon *);
s32 getRnd__11DarkPokemonCFv(DpmDarkPokemon *);
u8 isSnach__11DarkPokemonCFv(DpmDarkPokemon *);
u8 isRelive__11DarkPokemonCFv(DpmDarkPokemon *);
u16 getCatchBallID__11DarkPokemonCFv(DpmDarkPokemon *);
u32 getDarkPointDirect__11DarkPokemonCFv(DpmDarkPokemon *);
s32 winSpriteGetLayerID(DpmWindow *, DpmSprite *);
void windowDrawSprite(s16, s16, DpmWindow *, u16, s32, s32);
u32 GSmsgGetGSchar(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void msgctrlSetValue(s32, u32);
u32 floorGetPlaceName(u16);
u16 mballBiosGetSpriteID(u16);
void pokemonBiosSetRnd(DpmPokemon *, u32);
void pokemonBiosSetDarkpokemonDataId(DpmPokemon *, s32);
u8 pokemonGetSex(DpmPokemon *);
void pokemonCreate(DpmPokemon *, s32, s32, s32);
s32 pokemonCreateRndFit(DpmPokemon *, s32, s32, s32, s32);
s32 gamedataGetStatus(s32, s32);

static inline void dpmPosition(s16 x, s16 y) {
    volatile DpmFifo *fifo = (volatile DpmFifo *)0xcc008000;
    fifo->shortValue = x;
    fifo->shortValue = y;
}
static inline void dpmColor(u8 alpha) {
    volatile DpmFifo *fifo = (volatile DpmFifo *)0xcc008000;
    fifo->byte = 255;
    fifo->byte = 255;
    fifo->byte = 255;
    fifo->byte = alpha;
}
static inline void dpmTexcoord(f32 u, f32 v) {
    volatile DpmFifo *fifo = (volatile DpmFifo *)0xcc008000;
    fifo->floatValue = u;
    fifo->floatValue = v;
}

static DpmCursor _cursor;
DpmWork *_pDPM;
s32 menuPdaDPMCallBack(DpmWindow *arg0, DpmSprite *arg1);
void menuPdaDPMButton(DpmWindow *arg0);
s32 menuPdaDPMCursor(DpmWindow *arg0);
s32 menuPdaDPMCtrl(DpmWindow *arg0);
DpmCursor *menuPdaDPMon(DpmCursor *arg0);
DpmWork *__dt__10menuPdaDPMFv(DpmWork *arg0, s16 arg1);
DpmWork *__ct__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1);
void Release__10menuPdaDPMFv(DpmWork *arg0);
void LoadPokemon__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1);
void Init__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1);
DpmCursor *Main__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1);
void Button__10menuPdaDPMFP14tagWINDOW_WORK(DpmWork *arg0, DpmWindow *arg1);
void Ctrl__10menuPdaDPMFP14tagWINDOW_WORK(DpmWork *arg0, DpmWindow *arg1);
void Cursor__10menuPdaDPMFP14tagWINDOW_WORK(DpmWork *arg0, DpmWindow *arg1);
void SetViewFlag__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1);
void DispPokemonModel__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3);
void DarkPokemonRelive__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3);
void DarkPokemonRibbon__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3);
void DarkPokemonInfo__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3);
void DarkPokemonPlace__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3);
void PokemonName__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(DpmWork *arg0,
                                                                                 DpmWindow *arg1,
                                                                                 DpmSprite *arg2,
                                                                                 DpmContents *arg3);
void PokemonSex__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(DpmWork *arg0,
                                                                                DpmWindow *arg1,
                                                                                DpmSprite *arg2,
                                                                                DpmContents *arg3);
void PokemonBall__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(DpmWork *arg0,
                                                                                 DpmWindow *arg1,
                                                                                 DpmSprite *arg2,
                                                                                 DpmContents *arg3);
void _menuClose__10menuPdaDPMFl(DpmWork *arg0, s32 arg1);
DpmPokemon *GetPokemonPointer__10menuPdaDPMFl(DpmWork *arg0, s32 arg1);
s32 menuPdaDPMCallBack(DpmWindow *arg0, DpmSprite *arg1) {
    s16 temp_r4;
    DpmContents *content;

    if ((void *)_pDPM == 0) {
        return 0;
    }
    temp_r4 = arg1->id;
    content = arg0->content;
    switch (temp_r4) {
    case 0x68:
        DispPokemonModel__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
            _pDPM, arg0, arg1, content);
        break;
    case 0x62:
        DarkPokemonRibbon__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
            _pDPM, arg0, arg1, content);
        break;
    case 0x69:
        DarkPokemonInfo__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
            _pDPM, arg0, arg1, content);
        break;
    case 0x67:
        DarkPokemonRelive__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
            _pDPM, arg0, arg1, content);
        break;
    case 0x6A:
        DarkPokemonPlace__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
            _pDPM, arg0, arg1, content);
        break;
    case 0x6D:
        PokemonName__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(_pDPM, arg0,
                                                                                    arg1, content);
        break;
    case 0x6C:
        PokemonSex__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(_pDPM, arg0,
                                                                                   arg1, content);
        break;
    case 0x61:
        PokemonBall__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(_pDPM, arg0,
                                                                                    arg1, content);
        break;
    }
    return 0;
}

void menuPdaDPMButton(DpmWindow *arg0) {
    if ((void *)_pDPM != 0) {
        Button__10menuPdaDPMFP14tagWINDOW_WORK(_pDPM, arg0);
    }
}

s32 menuPdaDPMCursor(DpmWindow *arg0) {
    if ((void *)_pDPM == 0) {
        return 0;
    }
    Cursor__10menuPdaDPMFP14tagWINDOW_WORK(_pDPM, arg0);
    return 0;
}

s32 menuPdaDPMCtrl(DpmWindow *arg0) {
    if ((void *)_pDPM == 0) {
        return 0;
    }
    Ctrl__10menuPdaDPMFP14tagWINDOW_WORK(_pDPM, arg0);
    return 0;
}

DpmCursor *menuPdaDPMon(DpmCursor *arg0) {
    DpmWork *var_r0;

    var_r0 = __nw__FUl(0x1B4);
    if (var_r0 != 0) {
        var_r0 = __ct__10menuPdaDPMFP6CURSOR(var_r0, arg0);
    }
    _pDPM = var_r0;
    Main__10menuPdaDPMFP6CURSOR(var_r0, arg0);
    __dt__10menuPdaDPMFv(_pDPM, 1);
    _pDPM = 0;
    return &_cursor;
}

DpmWork *__dt__10menuPdaDPMFv(DpmWork *arg0, s16 arg1) {
    if (arg0 != 0) {
        Release__10menuPdaDPMFv(arg0);
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

DpmWork *__ct__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1) {
    Init__10menuPdaDPMFP6CURSOR(arg0, arg1);
    return arg0;
}

void Release__10menuPdaDPMFv(DpmWork *arg0) { menuModelTerm(&arg0->model); }

void LoadPokemon__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1) {
    s16 temp_r5;

    temp_r5 = arg1->selected;
    menuModelLoadPokemon(&arg0->model,
                         GetPokemonPointer__10menuPdaDPMFl(arg0, temp_r5 + arg1->first));
}

void Init__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1) {
    DpmItem *temp_r3;

    temp_r3 = menuItemBiosGetPtr(0x75, 0x68);
    menuModelInit(&arg0->model, temp_r3->width, temp_r3->height);
    LoadPokemon__10menuPdaDPMFP6CURSOR(arg0, arg1);
}

DpmCursor *Main__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1) {
    DpmCursor *sp8;

    _cursor.selected = (s16)arg1->selected;
    _cursor.first = (s16)arg1->first;
    do {
        sp8 = &_cursor;
    } while (menuOpenCustom(0x75, windowGetActiveID(), 0, 0, 1, 1, &sp8) != -1);
    _menuClose__10menuPdaDPMFl(arg0, 0x75);
    return &_cursor;
}

void Button__10menuPdaDPMFP14tagWINDOW_WORK(DpmWork *arg0, DpmWindow *arg1) {
    if ((arg1 != 0) && (winSeqCheckMove(arg1->menu) == 0) &&
        ((s32)(windowGetKeyInfo()->triggers & 0x20) != 0)) {
        arg1->accepted = 1;
        arg1->cancelled = 1;
    }
}

void Ctrl__10menuPdaDPMFP14tagWINDOW_WORK(DpmWork *arg0, DpmWindow *arg1) {
    u8 temp_r0;

    temp_r0 = arg1->phase;
    switch ((s8)temp_r0) { /* irregular */
    case 0:
        if ((s8)arg1->step == 0) {
            winSeqSetMenu(arg1->menu, 0x132);
            arg1->step = 1U;
            menuPdaSetSubres(0, 2);
        }
        break;
    case 2:
        menuDrawReliveUpdate();
        break;
    case 3:
        if ((s8)arg1->step == 0) {
            winSeqSetMenu(arg1->menu, 0x136);
            arg1->step = 1U;
        }
        break;
    }
}

void Cursor__10menuPdaDPMFP14tagWINDOW_WORK(DpmWork *arg0, DpmWindow *arg1) {
    s16 temp_r4;
    s16 temp_r5;
    s16 temp_r5_2;
    s32 temp_r29;
    s32 temp_r31;
    s32 var_r28;
    s8 temp_r3_3;
    u16 temp_r3_2;
    DpmContents *temp_r3;
    DpmCursor *temp_r30;

    windowGetKeyInfo();
    temp_r3 = arg1->content;
    temp_r30 = temp_r3->cursor;
    var_r28 = 0xA;
    temp_r29 = menuPdaDPMListGetDPNum();
    temp_r3_2 = windowGetKeyRepeat();
    temp_r5 = temp_r30->selected;
    temp_r4 = temp_r30->first;
    temp_r31 = temp_r5 + temp_r4;
    if (temp_r29 < 0xA) {
        var_r28 = temp_r29;
    }
    if ((s32)(temp_r3_2 & 1) != 0) {
        if (temp_r31 != 0) {
            GSsndPlayNow(0x450);
        }
        temp_r30->selected = (s16)(temp_r30->selected - 1);
    } else if ((s32)(temp_r3_2 & 2) != 0) {
        if ((s32)(temp_r29 - 1) != (s32)(temp_r5 + temp_r4)) {
            GSsndPlayNow(0x450);
        }
        temp_r30->selected = (s16)(temp_r30->selected + 1);
    }
    temp_r5_2 = temp_r30->selected;
    if (temp_r5_2 < 0) {
        temp_r30->first = (s16)(temp_r30->first + temp_r5_2);
        temp_r30->selected = 0;
        if ((s16)temp_r30->first < 0) {
            temp_r30->first = 0;
            temp_r30->selected = 0;
        }
    } else if (temp_r5_2 >= var_r28) {
        temp_r3_3 = var_r28 - 1;
        temp_r30->first = (s16)(temp_r30->first + (temp_r5_2 - temp_r3_3));
        temp_r30->selected = (s16)temp_r3_3;
        if ((s32)(temp_r30->first + temp_r30->selected) >= temp_r29) {
            temp_r30->selected = (s16)temp_r3_3;
            temp_r30->first = (s16)(s8)(temp_r29 - var_r28);
        }
    }
    if (temp_r31 != (s32)(temp_r30->selected + temp_r30->first)) {
        SetViewFlag__10menuPdaDPMFP6CURSOR(arg0, temp_r30);
        LoadPokemon__10menuPdaDPMFP6CURSOR(arg0, temp_r30);
        menuPlaySe(arg1->menu, 1);
    }
}

void SetViewFlag__10menuPdaDPMFP6CURSOR(DpmWork *arg0, DpmCursor *arg1) {
    DpmDarkPokemon *temp_r31;

    temp_r31 = darkPokemonGetDarkPokemon(
        (u16)menuPdaDPMListGetDarkPokemonID(arg1->selected + arg1->first));
    if (isUpdate__11DarkPokemonCFv(temp_r31) != 0) {
        setUpdate__11DarkPokemonFb(temp_r31, 0);
    }
}

void DispPokemonModel__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3) {
    f32 angle[3];
    DpmItem *item;
    DpmTexture *texture;
    DpmLayer *layer;
    angle[0] = 0.0f;
    angle[1] = 0.3f;
    angle[2] = 0.0f;
    if (menuModelCheck(&arg0->model, 0) == 0) {
        item = menuItemBiosGetPtr(0x75, 0x68);
        menuModelAdjustCamera(&arg0->model);
        menuModelSetAngle(&arg0->model, angle);
        menuModelSetSize(&arg0->model, item->x, item->y, item->width, item->height);
        menuModelSetZoom(&arg0->model, 0.85f);
        menuModelRender(&arg0->model);
        texture = menuModelRender(&arg0->model);
        if (texture != 0) {
            layer = GSgfxLayerFindByID(arg1->layer);
            if (layer != 0) {
                layer->primitive = 0x98;
                setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, GSgfxVFGetPredef(7));
                if (layer->textureA != texture || layer->textureB != texture ||
                    texture->dirty != 0) {
                    layer->textureA = texture;
                    layer->dirtyA |= 1;
                    layer->textureB = texture;
                    layer->dirtyB |= 1;
                }
                beginSurface__10GSgfxLayerFUs(layer, 4);
                dpmPosition(0, 0);
                dpmColor(arg1->alpha);
                dpmTexcoord(0.0f, 0.0f);
                dpmPosition(arg2->width, 0);
                dpmColor(arg1->alpha);
                dpmTexcoord(1.0f, 0.0f);
                dpmPosition(0, arg2->height);
                dpmColor(arg1->alpha);
                dpmTexcoord(0.0f, 1.0f);
                dpmPosition(arg2->width, arg2->height);
                dpmColor(arg1->alpha);
                dpmTexcoord(1.0f, 1.0f);
                endSurface__10GSgfxLayerFv(layer);
            }
        }
    }
}

void DarkPokemonRelive__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3) {
    DpmCursor *temp_r6;

    temp_r6 = arg3->cursor;
    menuPdaDPMListDispRelive(arg1, arg2, 0, 0, temp_r6->selected + temp_r6->first, arg1->alpha, 1);
}

void DarkPokemonRibbon__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3) {
    DpmCursor *temp_r4;

    temp_r4 = arg3->cursor;
    if (getStatus__11DarkPokemonCFv(
            menuPdaDPMListGetDPointer(temp_r4->selected + temp_r4->first)) >= 4) {
        arg2->flags = (u8)(s8)(arg2->flags | 2);
        return;
    }
    arg2->flags = (u8)(s8)(arg2->flags & 0xFFFFFFFD);
}

void DarkPokemonInfo__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3) {
    s32 temp_r28;
    DpmDarkPokemon *temp_r30;
    s32 temp_r31;
    u16 temp_r29;
    u32 var_r31;
    u32 var_r3;
    DpmCursor *temp_r4;

    temp_r4 = arg3->cursor;
    temp_r30 = menuPdaDPMListGetDPointer(temp_r4->selected + temp_r4->first);
    temp_r29 = getCatchFloorId__11DarkPokemonCFv(temp_r30);
    temp_r31 = getStatus__11DarkPokemonCFv(temp_r30);
    temp_r28 = winSpriteGetLayerID(arg1, arg2);
    if (getPokemonID__11DarkPokemonCFv(temp_r30) == 0xAF) {
        var_r31 = 0x3C2FU;
    } else if (temp_r31 >= 3) {
        var_r31 = 0x3B63U;
    } else {
        var_r31 = 0x3B65U;
    }
    if (temp_r29 == 0xB5) {
        var_r31 = 0x3C30U;
    }
    if (var_r31 != 0U) {
        getOrgTrainer__11DarkPokemonCFv(temp_r30);
        var_r3 = floorGetPlaceName(temp_r29);
        if (var_r3 == 0U) {
            var_r3 = 0x3BA8U;
        }
        msgctrlSetValue(0x4D, GSmsgGetGSchar(var_r3));
        msgctrlSetValue(0x57, getTrainerName__11DarkPokemonCFv(temp_r30));
        GSmsgPrint2(temp_r28, 0, 0, arg1->alpha | ~0xFF, var_r31);
    }
}

void DarkPokemonPlace__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3) {
    u8 sp8;
    u32 temp_r3;
    DpmCursor *temp_r5;

    temp_r5 = arg3->cursor;
    temp_r3 = menuPdaDPMListGetDarkPokemonPlaceMsgID(temp_r5->selected + temp_r5->first, &sp8);
    if (temp_r3 != 0U) {
        msgctrlSetValue(0x2F, sp8 + 1);
        temp_r3 = GSmsgGetGSchar(temp_r3);
        msgctrlSetValue(0x37, temp_r3);
        GSmsgPrint2(arg1->layer, 0, 0, arg1->alpha | ~0xFF, 0x4275U);
    }
}

void PokemonName__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3) {
    u32 var_r3;
    DpmCursor *temp_r4;

    temp_r4 = arg3->cursor;
    var_r3 = menuPdaDPMListGetPokemonName(temp_r4->selected + temp_r4->first);
    if (var_r3 == 0U) {
        var_r3 = GSmsgGetGSchar(1U);
    }
    msgctrlSetValue(0x37, var_r3);
    GSmsgPrint2(arg1->layer, 0, 0, arg1->alpha | ~0xFF, 0x4275U);
}

void PokemonSex__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(DpmWork *arg0,
                                                                                DpmWindow *arg1,
                                                                                DpmSprite *arg2,
                                                                                DpmContents *arg3) {
    s16 temp_r30;
    DpmDarkPokemon *temp_r28;
    u32 var_r29;
    u8 temp_r30_2;
    DpmPokemon *temp_r29;
    DpmCursor *temp_r4;

    temp_r4 = arg3->cursor;
    temp_r30 = temp_r4->selected + temp_r4->first;
    temp_r28 = menuPdaDPMListGetDPointer(temp_r30);
    temp_r29 = GetPokemonPointer__10menuPdaDPMFl(arg0, temp_r30);
    pokemonBiosSetRnd(temp_r29, getRnd__11DarkPokemonCFv(temp_r28));
    temp_r30_2 = pokemonGetSex(temp_r29);
    pokemonBiosSetRnd(temp_r29, arg0->rnd);
    if (temp_r30_2 == 0x80) {
        var_r29 = GSmsgGetGSchar(1U);
    } else {
        switch ((s32)temp_r30_2) { /* irregular */
        case 0:
            var_r29 = GSmsgGetGSchar(0x9C5U);
            break;
        case 1:
            var_r29 = GSmsgGetGSchar(0x9C6U);
            break;
        case 2:
            var_r29 = GSmsgGetGSchar(1U);
            break;
        default:
            var_r29 = GSmsgGetGSchar(0x9C6U);
            break;
        }
    }
    if ((getCatchFloorId__11DarkPokemonCFv(temp_r28) == 0xB5) && (temp_r30_2 != 2)) {
        var_r29 = GSmsgGetGSchar(0x9C7U);
    }
    msgctrlSetValue(0x37, var_r29);
    GSmsgPrint2(arg1->layer, 0, 0, arg1->alpha | ~0xFF, 0x4275U);
}

void PokemonBall__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS(
    DpmWork *arg0, DpmWindow *arg1, DpmSprite *arg2, DpmContents *arg3) {
    DpmDarkPokemon *temp_r31;
    u16 temp_r3;
    DpmCursor *temp_r4;

    temp_r4 = arg3->cursor;
    temp_r31 = menuPdaDPMListGetDPointer(temp_r4->selected + temp_r4->first);
    if (isSnach__11DarkPokemonCFv(temp_r31) != 0) {
        temp_r3 = mballBiosGetSpriteID(getCatchBallID__11DarkPokemonCFv(temp_r31));
        if (temp_r3 != 0) {
            windowDrawSprite(0, 0, arg1, temp_r3, 0, arg1->layer);
        }
    }
}

void _menuClose__10menuPdaDPMFl(DpmWork *arg0, s32 arg1) {
    menuClose(arg1);
    menuCloseSync(arg1, 1);
}

DpmPokemon *GetPokemonPointer__10menuPdaDPMFl(DpmWork *arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r31;
    DpmDarkPokemon *temp_r31_2;

    temp_r31 = menuPdaDPMListGetPokemonID(arg1);
    pokemonCreate(&arg0->pokemon, temp_r31, 0xA, gamedataGetStatus(0, 1));
    temp_r31_2 = menuPdaDPMListGetDPointer(arg1);
    temp_r30 = menuPdaDPMListGetDarkpokemonID(arg1);
    getDarkPointDirect__11DarkPokemonCFv(temp_r31_2);
    arg0->rnd = pokemonCreateRndFit(&arg0->pokemon, -1, -1, 0, 0);
    pokemonBiosSetRnd(&arg0->pokemon, arg0->rnd);
    if (isRelive__11DarkPokemonCFv(temp_r31_2) == 0) {
        pokemonBiosSetDarkpokemonDataId(&arg0->pokemon, temp_r30);
    } else {
        pokemonBiosSetDarkpokemonDataId(&arg0->pokemon, 0);
    }
    return &arg0->pokemon;
}

#ifdef __cplusplus
}
#endif
