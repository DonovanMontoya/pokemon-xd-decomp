#include <game/menuPdaMemoListLayout.hpp>
#ifdef __cplusplus
extern "C" {
#endif

void *__nw__FUl(u32);
void *__nwa__FUl(u32);
void __dl__FPv(void *);
void __dla__FPv(void *);
void *memcpy(void *, const void *, unsigned long);
u32 memoDataGetCount(s32);
u16 memoDataGetPokemonID(s32, u16);
u32 memoDataGetPokemonRndFromID(s32, u16);
u32 memoDataGetPokemonTrainerRndFromID(s32, u16);
s32 GScharCmp(const u16 *, const u16 *);
void GScharCpy(u16 *, const u16 *);
u16 *GSmsgGetGSchar(u32);
u32 pokemonDataBiosGetName(void *);
void *pokemonDataBiosGetPtr(u16);
s32 pokecoloGetCountryCode(void);
void pokemonCreate(MemoPokemon *, u16, s32, s32);
u16 pokemonGetStatus(MemoPokemon *, u16, s32, s32);
void pokemonBiosSetRnd(MemoPokemon *, u32);
void pokemonBiosSetCatchTrainerRnd(MemoPokemon *, u32);
s32 gamedataGetStatus(s32, s32);
void menuModelInit(MemoModel *, s16, s16);
void menuModelTerm(MemoModel *);
u8 menuModelCheck(MemoModel *, s32);
u8 menuModelComparePokemon(MemoModel *, MemoPokemon *);
void menuModelFree(MemoModel *);
void fn_80112AAC(MemoModel *, MemoPokemon *);
void menuModelRenderOffAll(MemoModel *);
void menuModelLoad(MemoModel *, u32);
void menuModelSetMotion(MemoModel *, s32);
void menuModelSetAngle(MemoModel *, f32 *);
void menuModelSetSize(MemoModel *, s16, s16, s16, s16);
void menuModelSetZoom(MemoModel *, f32);
void menuModelAdjustCamera(MemoModel *);
void menuModelAdjustCamera2(MemoModel *, MemoModel *);
void menuModelRender(MemoModel *);
void menuModelRender2(MemoModel *, MemoModel *);
u32 GSthreadCreate(s32, s32, u32, s32, s32, s32 (*)(MemoModel *));
u32 GSthreadGetCurrentThread(void);
u8 GSthreadIsRunning(u32);
void GSthreadClose(u32);
void GSthreadSetArgs(u32, s32, void *);
void GSthreadSwitch(void);
s32 GSfloorGetCurrentFloorGroupID(void);
u32 heroGetObjID(s32);
void *peopleInfoBiosGetPtr(u32);
void peopleInfoBiosGetMotion(void *, s32, s32 *, s32 *);
MemoItem *menuItemBiosGetPtr(s32, s16);
s32 menuOpen(s32, s32);
void menuClose(s32);
void menuCloseSync(s32, s32);
MemoCursor *menuPdaMemoXDMain(MemoCursor *);
s32 menuPdaMemoXDGetItem(void);
void menuPdaSubInitAlpha(f32 *, s32, s16);
void menuPdaSubCalcAlpha(f32 *, s32, s16);
void menuPdaSubCalcPositon(f32 *, f32, f32);
void menuPdaSubCheckUpDownCursor(MemoWindow *, MemoSprite *, MemoCursor *, s32, s32, s32);
void menuPdaSubScrollBar(MemoWindow *, MemoSprite *, s32, s32, u32, s32, s32, MemoCursor *);
u32 cursorBiosGetPos(s32);
void cursorBiosSetPos(s32, MemoCursor *);
MemoKey *windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
u8 winSeqCheckMove(s32);
void winSeqSetMenu(s32, s32);
void winSpriteSetDisp(MemoSprite *, s32);
void GSsndPlayNow(u32);
s32 winSpriteGetLayerID(MemoWindow *, MemoSprite *);
void spriteSetScissor(s32, s32, s32, s16, s16);
void spriteClearScissor(s32);
void msgctrlSetValue(s32, const void *);
void GSmsgPrint2(s32, s32, s32, u32, u32);
u32 zokuseiBiosGetSmallSpriteID(u16);
void windowDrawSprite2(s16, s32, s16, s16, u32, MemoWindow *, u32, s32, s32);
void *GSgfxLayerFindByID(s32);

extern u16 *pdapokemonsortdata;
extern u32 *pdapokemonsortdata_number;
MemoWork *pMemoList;
static f32 _defaultAngle[3] = {0.0f, -0.3f, 0.0f};
static s32 _testMotion = 3;
struct MemoCursorIds {
    s32 a, b, c, d, e, f, g, h;
};
static s32 _menuPdaMemoListThread__FP10MENU_MODEL(MemoModel *arg0);
void menuPdaMemoListSetHeroMotion(void);
u8 menuPdaMemoListIsLoadHero(void);
u8 menuPdaMemoListIsTermModel(void);
void menuPdaMemoListLoadHero(u8 arg0);
f32 menuPdaMemoListGetDefaultAngle(s16 arg0);
void menuPdaMemoListDispPokemonModel(MemoWindow *arg0, MemoSprite *arg1, s32 arg2);
MemoModel *menuPdaMemoListGetMenuModelWork(void);
void menuPdaMemoListLoadPokemon(s32 arg0);
void *menuPdaMemoListGetPokemonDataPointer(s32 arg0);
u16 *menuPdaMemoListGetPokemonName(s32 arg0);
u16 menuPdaMemoListGetPokemonID(s32 arg0);
void menuPdaMemoListHook(MemoWindow *arg0, MemoSprite *arg1);
void menuPdaMemoList(void);
void menuPdaMemoListButton(MemoWindow *arg0);
s32 menuPdaMemoListCursor(MemoWindow *arg0);
s32 menuPdaMemoListCtrl(MemoWindow *arg0);
void Sort__11pdaMemoListF15menuPdaMemoSort(MemoWork *arg0, s32 arg1);
void SortPokemonID__11pdaMemoListFv(MemoWork *arg0);
void SortGojyuon__11pdaMemoListFv(MemoWork *arg0);
void Sort_Small__11pdaMemoListFP12MemoSortBuffl(MemoWork *arg0, MemoSortBuff *arg1, s32 arg2);
void fn_80055C94(MemoWork *arg0, MemoSortBuff *arg1, s32 arg2);
u16 SortGojyuonDataSet__11pdaMemoListFUs(MemoWork *arg0, u16 arg1);
void DispList__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                MemoSprite *arg2);
void DispPokemonModel__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORKUl(MemoWork *arg0,
                                                                          MemoWindow *arg1,
                                                                          MemoSprite *arg2,
                                                                          u32 arg3);
u16 *GetPokemonName__11pdaMemoListFl(MemoWork *arg0, s32 arg1);
void ScrollBar__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                 MemoSprite *arg2);
void LoadHero__11pdaMemoListFb(MemoWork *arg0, u8 arg1);
s32 TermThread__11pdaMemoListFP10MENU_MODEL(MemoWork *arg0, MemoModel *arg1);
void SetHeroMotion__11pdaMemoListFv(MemoWork *arg0);
void LoadPokemon__11pdaMemoListFl(MemoWork *arg0, s32 arg1);
MemoPokemon *GetPokemonPointer__11pdaMemoListFl(MemoWork *arg0, s32 arg1);
void ListCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                  MemoSprite *arg2);
s32 GetMenuItemNumber__11pdaMemoListFP14tagSPRITE_WORK(MemoWork *arg0, MemoSprite *arg1);
void DownCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                  MemoSprite *arg2);
void UpCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                MemoSprite *arg2);
void Release__11pdaMemoListFv(MemoWork *arg0);
void InitWork__11pdaMemoListFv(MemoWork *arg0);
s32 Main__11pdaMemoListFP6CURSOR(MemoWork *arg0, MemoCursor *arg1);
void Button__11pdaMemoListFP14tagWINDOW_WORK(MemoWork *arg0, MemoWindow *arg1);
void Cursor__11pdaMemoListFP14tagWINDOW_WORK(MemoWork *arg0, MemoWindow *arg1);
void Ctrl__11pdaMemoListFP14tagWINDOW_WORK(MemoWork *arg0, MemoWindow *arg1);
void ListMain__11pdaMemoListFP14tagWINDOW_WORK(MemoWork *arg0, MemoWindow *arg1);
void ListPosition__11pdaMemoListFv(MemoWork *arg0);
void CalcPosition__11pdaMemoListFP6CURSOR(MemoWork *arg0, MemoCursor *arg1);
void _setCursor__11pdaMemoListF6CURSOR(MemoWork *arg0, const MemoCursor *arg1);
u32 _getCursor__11pdaMemoListFv(MemoWork *arg0);
void _menuClose__11pdaMemoListFl(MemoWork *arg0, s32 arg1);
MemoWork *__ct__11pdaMemoListFv(MemoWork *arg0);
MemoWork *__dt__11pdaMemoListFv(MemoWork *arg0, s16 arg1);
static s32 _menuPdaMemoListThread__FP10MENU_MODEL(MemoModel *arg0) {
    if ((s32 *)pMemoList != 0) {
        return TermThread__11pdaMemoListFP10MENU_MODEL(pMemoList, arg0);
    }
    return 0;
}

void menuPdaMemoListSetHeroMotion(void) {
    if ((s32 *)pMemoList != 0) {
        SetHeroMotion__11pdaMemoListFv(pMemoList);
    }
}

u8 menuPdaMemoListIsLoadHero(void) {
    if ((s32 *)pMemoList != 0) {
        if ((u8)pMemoList->heroLoaded == 0) {
            return 0U;
        }
        return menuModelCheck(&pMemoList->hero, 0);
    }
    return 0U;
}

u8 menuPdaMemoListIsTermModel(void) {
    if ((s32 *)pMemoList != 0) {
        return pMemoList->terminating;
    }
    return 0U;
}

void menuPdaMemoListLoadHero(u8 arg0) {
    if ((s32 *)pMemoList != 0) {
        LoadHero__11pdaMemoListFb(pMemoList, arg0);
    }
}

f32 menuPdaMemoListGetDefaultAngle(s16 arg0) { return _defaultAngle[arg0]; }

void menuPdaMemoListDispPokemonModel(MemoWindow *arg0, MemoSprite *arg1, s32 arg2) {
    s16 var_r6;

    if ((s32 *)pMemoList != 0) {
        switch (arg2) { /* irregular */
        case 0:
            var_r6 = 0xB9;
            break;
        case 1:
            var_r6 = 0xBB;
            break;
        case 2:
            var_r6 = 0xBA;
            break;
        default:
            var_r6 = 0x1C7;
            break;
        }
        DispPokemonModel__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORKUl(pMemoList, arg0, arg1,
                                                                             var_r6);
    }
}

MemoModel *menuPdaMemoListGetMenuModelWork(void) {
    if ((s32 *)pMemoList == 0) {
        return 0;
    }
    return &pMemoList->model;
}

void menuPdaMemoListLoadPokemon(s32 arg0) {
    if ((s32 *)pMemoList != 0) {
        LoadPokemon__11pdaMemoListFl(pMemoList, arg0);
    }
}

void *menuPdaMemoListGetPokemonDataPointer(s32 arg0) {
    if (pMemoList == 0)
        return 0;
    return pokemonDataBiosGetPtr(menuPdaMemoListGetPokemonID(arg0));
}

u16 *menuPdaMemoListGetPokemonName(s32 arg0) {
    if ((s32 *)pMemoList == 0) {
        return 0;
    }
    return GetPokemonName__11pdaMemoListFl(pMemoList, arg0);
}

u16 menuPdaMemoListGetPokemonID(s32 arg0) {
    MemoWork *temp_r31;

    temp_r31 = pMemoList;
    if (temp_r31 == 0) {
        return 0U;
    }
    if ((arg0 <= (s32)(u16)memoDataGetCount(0)) && (arg0 >= 0)) {
        return temp_r31->ids[arg0];
    }
    return 0U;
}

void menuPdaMemoListHook(MemoWindow *arg0, MemoSprite *arg1) {
    s16 temp_r3;

    temp_r3 = arg1->id;
    switch (temp_r3) {
    case 0xDE:
    case 0xE0:
    case 0xE2:
    case 0xE4:
    case 0xE6:
    case 0xE8:
    case 0xEA:
    case 0xEC:
        ListCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(pMemoList, arg0, arg1);
        return;
    case 0xDC:
        UpCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(pMemoList, arg0, arg1);
        return;
    case 0xDD:
        DownCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(pMemoList, arg0, arg1);
        return;
    case 0xDB:
        ScrollBar__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(pMemoList, arg0, arg1);
        return;
    case 0xF1:
        DispList__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(pMemoList, arg0, arg1);
        /* fallthrough */
    default:
        return;
    }
}

void menuPdaMemoList(void) {
    MemoCursor cursor;
    MemoWork *work = (MemoWork *)__nw__FUl(sizeof(MemoWork));
    if (work != 0)
        work = __ct__11pdaMemoListFv(work);
    pMemoList = work;
    cursor.pos.selected = 0;
    cursor.pos.first = 0;
    menuOpen(0x7f, 0);
    menuOpen(0x77, 0);
    while (Main__11pdaMemoListFP6CURSOR(pMemoList, &cursor) >= 0) {
        MemoCursor *returned = menuPdaMemoXDMain(&cursor);
        cursor.pos.selected = returned->pos.selected;
        cursor.pos.first = returned->pos.first;
        menuPdaSubInitAlpha(pMemoList->alpha, 8, cursor.pos.selected);
        CalcPosition__11pdaMemoListFP6CURSOR(pMemoList, &cursor);
        pMemoList->y = pMemoList->targetY;
    }
    while (pMemoList->thread != 0) {
        if (GSthreadIsRunning(pMemoList->thread) == 0) {
            GSthreadClose(pMemoList->thread);
            break;
        }
        GSthreadSwitch();
    }
    _menuClose__11pdaMemoListFl(pMemoList, 0x77);
    _menuClose__11pdaMemoListFl(pMemoList, 0x7f);
    __dt__11pdaMemoListFv(pMemoList, 1);
    pMemoList = 0;
}

void menuPdaMemoListButton(MemoWindow *arg0) {
    if ((s32 *)pMemoList != 0) {
        Button__11pdaMemoListFP14tagWINDOW_WORK(pMemoList, arg0);
    }
}

s32 menuPdaMemoListCursor(MemoWindow *arg0) {
    if ((s32 *)pMemoList == 0) {
        return 0;
    }
    Cursor__11pdaMemoListFP14tagWINDOW_WORK(pMemoList, arg0);
    return 0;
}

s32 menuPdaMemoListCtrl(MemoWindow *arg0) {
    if ((s32 *)pMemoList == 0) {
        return 0;
    }
    Ctrl__11pdaMemoListFP14tagWINDOW_WORK(pMemoList, arg0);
    return 0;
}

void Sort__11pdaMemoListF15menuPdaMemoSort(MemoWork *arg0, s32 arg1) {
    if (arg1 != 1) {
        if (arg1 < 1) {
        }
        SortGojyuon__11pdaMemoListFv(arg0);
        return;
    }
    SortPokemonID__11pdaMemoListFv(arg0);
}

void SortPokemonID__11pdaMemoListFv(MemoWork *arg0) {
    MemoSortBuff *records;
    u16 *copy, id;
    u32 count, i;
    count = (u16)memoDataGetCount(0);
    records = (MemoSortBuff *)__nwa__FUl(0x2bc0);
    copy = (u16 *)__nwa__FUl(0x320);
    for (i = 0; (s32)(u16)i < (s32)count; i++) {
        id = arg0->ids[(u16)i];
        copy[(u16)i] = id;
        records[(u16)i].key = id;
        records[(u16)i].index = i;
    }
    Sort_Small__11pdaMemoListFP12MemoSortBuffl(arg0, records, count);
    for (i = 0; (s32)(u16)i < (s32)count; i++)
        arg0->ids[(u16)i] = copy[records[(u16)i].index];
    if (records != 0)
        __dl__FPv(records);
    if (copy != 0)
        __dl__FPv(copy);
}

void SortGojyuon__11pdaMemoListFv(MemoWork *arg0) {
    MemoSortBuff *records;
    u16 *copy, id;
    u32 count, i;
    count = (u16)memoDataGetCount(0);
    records = (MemoSortBuff *)__nwa__FUl(0x2bc0);
    copy = (u16 *)__nwa__FUl(0x320);
    for (i = 0; (s32)(u16)i < (s32)count; i++) {
        id = arg0->ids[(u16)i];
        copy[(u16)i] = id;
        records[(u16)i].key = SortGojyuonDataSet__11pdaMemoListFUs(arg0, id);
        records[(u16)i].index = i;
        GScharCpy(records[(u16)i].name, GetPokemonName__11pdaMemoListFl(arg0, i));
    }
    if (pokecoloGetCountryCode() == 0)
        Sort_Small__11pdaMemoListFP12MemoSortBuffl(arg0, records, count);
    else
        fn_80055C94(arg0, records, count);
    for (i = 0; (s32)(u16)i < (s32)count; i++)
        arg0->ids[(u16)i] = copy[records[(u16)i].index];
    if (records != 0)
        __dl__FPv(records);
    if (copy != 0)
        __dl__FPv(copy);
}

void Sort_Small__11pdaMemoListFP12MemoSortBuffl(MemoWork *arg0, MemoSortBuff *arg1, s32 arg2) {
    MemoSortBuff saved, *left, *right;
    s32 gap, i, j;
    for (gap = arg2 / 2; gap > 0; gap /= 2) {
        for (i = gap; i < arg2; i++) {
            j = i - gap;
            left = &arg1[j];
            while (j >= 0 && (right = &arg1[j + gap], left->key >= right->key)) {
                memcpy(&saved, left, sizeof(saved));
                memcpy(left, right, sizeof(saved));
                memcpy(right, &saved, sizeof(saved));
                left -= gap;
                j -= gap;
            }
        }
    }
}

void fn_80055C94(MemoWork *arg0, MemoSortBuff *arg1, s32 arg2) {
    MemoSortBuff saved, *left, *right;
    s32 gap, i, j;
    for (gap = arg2 / 2; gap > 0; gap /= 2) {
        for (i = gap; i < arg2; i++) {
            j = i - gap;
            left = &arg1[j];
            while (j >= 0 && (right = &arg1[j + gap], GScharCmp(left->name, right->name) >= 0)) {
                memcpy(&saved, left, sizeof(saved));
                memcpy(left, right, sizeof(saved));
                memcpy(right, &saved, sizeof(saved));
                left -= gap;
                j -= gap;
            }
        }
    }
}

u16 SortGojyuonDataSet__11pdaMemoListFUs(MemoWork *arg0, u16 arg1) {
    u16 *entry = pdapokemonsortdata;
    u16 index = 0;
    if (arg1 >= 0x8000U)
        arg1 &= 0x3fff;
    while (index < *pdapokemonsortdata_number) {
        if (*entry == 0)
            return 0;
        if (arg1 == *entry)
            return index;
        entry++;
        index++;
    }
    return 0;
}

void DispList__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                MemoSprite *arg2) {
    MemoCursor sp10;
    s32 sp8;
    f32 var_f30;
    u16 *temp_r19_2;
    MemoPokemon *temp_r20;
    s32 temp_r31;
    s32 temp_r3_3;
    s32 temp_r3_5;
    s32 var_r22;
    u16 temp_r21;
    u16 temp_r3_2;
    u16 temp_r3_4;
    MemoItem *temp_r19;
    MemoItem *temp_r26;
    MemoItem *temp_r27;
    MemoItem *temp_r28;
    MemoItem *temp_r3;

    sp10.packed = _getCursor__11pdaMemoListFv(arg0);
    temp_r21 = (u16)memoDataGetCount(0);
    temp_r31 = winSpriteGetLayerID(arg1, arg2);
    temp_r26 = menuItemBiosGetPtr(0x78, 0xF1);
    temp_r27 = menuItemBiosGetPtr(0x78, 0xEF);
    temp_r28 = menuItemBiosGetPtr(0x78, 0xF0);
    temp_r19 = menuItemBiosGetPtr(0x78, 0xEE);
    temp_r3 = menuItemBiosGetPtr(0x78, arg2->id);
    spriteSetScissor(temp_r31, temp_r19->x - temp_r3->x, temp_r19->y - temp_r3->y, temp_r19->width,
                     temp_r19->height);
    var_f30 = arg0->y;
    if (pokecoloGetCountryCode() != 0) {
    }
    var_r22 = 0;
    for (var_r22 = 0; var_r22 < (s32)temp_r21; var_r22++) {
        if ((var_r22 >= (s32)(sp10.pos.first - 1)) && (var_r22 < (s32)(sp10.pos.first + 9))) {
            temp_r19_2 = GetPokemonName__11pdaMemoListFl(arg0, (u16)var_r22);
            temp_r20 = GetPokemonPointer__11pdaMemoListFl(arg0, var_r22);
            msgctrlSetValue(0x37, temp_r19_2);
            GSmsgPrint2(temp_r31, 0, (s32)(var_f30 + 0.0f), arg1->alpha | ~0xFF, 0x4277);
            temp_r3_2 = pokemonGetStatus(0, pokemonGetStatus(temp_r20, 0U, 0x6E, 0), 0x16, 0);
            temp_r3_3 = zokuseiBiosGetSmallSpriteID(temp_r3_2);
            sp8 = temp_r31;
            windowDrawSprite2((s16)(temp_r27->x - temp_r26->x), (s32)var_f30, temp_r27->width,
                              temp_r27->height, arg1->alpha | ~0xFF, arg1, temp_r3_3, 0, sp8);
            temp_r3_4 = pokemonGetStatus(0, pokemonGetStatus(temp_r20, 0U, 0x6E, 0), 0x16, 1);
            if ((temp_r3_4 != 0) && (temp_r3_4 != temp_r3_2)) {
                temp_r3_5 = zokuseiBiosGetSmallSpriteID(temp_r3_4);
                sp8 = temp_r31;
                windowDrawSprite2((s16)(temp_r28->x - temp_r26->x), (s32)var_f30, temp_r28->width,
                                  temp_r28->height, arg1->alpha | ~0xFF, arg1, temp_r3_5, 0, sp8);
            }
        }
        var_f30 += 27.0f;
    }
    spriteClearScissor(temp_r31);
}

void DispPokemonModel__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORKUl(MemoWork *arg0,
                                                                          MemoWindow *arg1,
                                                                          MemoSprite *arg2,
                                                                          u32 arg3) {
    s32 temp_r3;
    MemoItem *temp_r31;

    temp_r31 = menuItemBiosGetPtr(0x78, arg3);
    if ((GSgfxLayerFindByID(arg1->layer) != 0U) &&
        (menuModelSetSize(&arg0->model, temp_r31->x, temp_r31->y, temp_r31->width,
                          temp_r31->height),
         ((menuModelCheck(&arg0->model, 0) == 0) != 0))) {
        temp_r3 = menuPdaMemoXDGetItem();
        switch (temp_r3) { /* irregular */
        case 2:
            menuModelAdjustCamera2(&arg0->model, &arg0->hero);
            menuModelRender2(&arg0->model, &arg0->hero);
            return;
        case 1:
            menuModelAdjustCamera(&arg0->model);
            menuModelRender(&arg0->model);
            return;
        default:
            menuModelAdjustCamera(&arg0->model);
            menuModelRender(&arg0->model);
            break;
        }
    }
}

u16 *GetPokemonName__11pdaMemoListFl(MemoWork *arg0, s32 arg1) {
    u16 var_r3;

    if ((arg1 <= (s32)(u16)memoDataGetCount(0)) && (arg1 >= 0)) {
        var_r3 = arg0->ids[arg1];
    } else {
        var_r3 = 0;
    }
    if (pokemonDataBiosGetPtr(var_r3) != 0U) {
        return GSmsgGetGSchar(pokemonDataBiosGetName(pokemonDataBiosGetPtr(var_r3)));
    }
    return 0;
}

void ScrollBar__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                 MemoSprite *arg2) {
    s32 sp8;
    u16 temp_r31;

    temp_r31 = (u16)memoDataGetCount(0);
    sp8 = _getCursor__11pdaMemoListFv(arg0);
    menuPdaSubScrollBar(arg1, arg2, 0x78, 0xDB, 0xF2642200, temp_r31, 8, (MemoCursor *)&sp8);
}

void LoadHero__11pdaMemoListFb(MemoWork *arg0, u8 arg1) {
    if (arg1 != 0) {
        if ((u8)arg0->heroLoaded == 0) {
            menuModelInit(&arg0->hero, 0x280, 0x1E0);
            menuModelLoad(&arg0->hero, heroGetObjID(1));
            arg0->heroLoaded = 1U;
            arg0->heroMotion = 0;
        }
    } else if ((u8)arg0->heroLoaded != 0) {
        if (GSthreadGetCurrentThread() != 0U) {
            menuModelTerm(&arg0->hero);
        } else {
            menuModelRenderOffAll(&arg0->hero);
            arg0->terminating = 1;
            arg0->thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1,
                                          _menuPdaMemoListThread__FP10MENU_MODEL);
            if ((u32)arg0->thread != 0U) {
                GSthreadSetArgs(arg0->thread, 1, &arg0->hero);
            }
        }
        arg0->heroLoaded = 0U;
    }
}

s32 TermThread__11pdaMemoListFP10MENU_MODEL(MemoWork *arg0, MemoModel *arg1) {
    menuModelTerm(arg1);
    arg0->thread = 0;
    arg0->terminating = 0;
    return 1;
}

void SetHeroMotion__11pdaMemoListFv(MemoWork *arg0) {
    s32 spC;
    s32 sp8;

    if ((u8)arg0->heroMotion == 0) {
        peopleInfoBiosGetMotion(peopleInfoBiosGetPtr(heroGetObjID(1)), 1, &spC, &sp8);
        spC = _testMotion;
        menuModelSetMotion(&arg0->hero, _testMotion);
        arg0->heroMotion = 1U;
    }
}

void LoadPokemon__11pdaMemoListFl(MemoWork *arg0, s32 arg1) {
    MemoPokemon *temp_r3;

    if ((s32)(u16)memoDataGetCount(0) != 0) {
        temp_r3 = GetPokemonPointer__11pdaMemoListFl(arg0, arg1);
        if (menuModelComparePokemon(&arg0->model, temp_r3) == 0) {
            menuModelFree(&arg0->model);
            fn_80112AAC(&arg0->model, temp_r3);
            menuModelRenderOffAll(&arg0->hero);
        }
    }
}

MemoPokemon *GetPokemonPointer__11pdaMemoListFl(MemoWork *arg0, s32 arg1) {
    s32 temp_r29;
    MemoPokemon *temp_r30;
    s32 temp_r31;
    u16 var_r31;

    if ((arg1 <= (s32)(u16)memoDataGetCount(0)) && (arg1 >= 0)) {
        var_r31 = arg0->ids[arg1];
    } else {
        var_r31 = 0;
    }
    if (var_r31 != 0) {
        temp_r30 = arg0->pokemon;
        pokemonCreate(temp_r30, var_r31, 0xA, gamedataGetStatus(0, 1));
        temp_r31 = memoDataGetPokemonRndFromID(0, var_r31);
        temp_r29 = memoDataGetPokemonTrainerRndFromID(0, var_r31);
        pokemonBiosSetRnd(temp_r30, temp_r31);
        pokemonBiosSetCatchTrainerRnd(temp_r30, temp_r29);
        return temp_r30;
    }
    return 0;
}

void ListCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                  MemoSprite *arg2) {
    s16 temp_r31;
    s32 temp_r3;
    MemoWork *temp_r3_2;

    temp_r31 = arg1->selected;
    temp_r3 = GetMenuItemNumber__11pdaMemoListFP14tagSPRITE_WORK(arg0, arg2);
    temp_r3_2 = (MemoWork *)((u8 *)arg0 + temp_r3 * sizeof(f32));
    arg2->alpha = temp_r3_2->alpha[0];
    if (temp_r31 == temp_r3) {
        winSpriteSetDisp(arg2, 1);
        return;
    }
    if (temp_r3_2->alpha[0] == 0.0f) {
        winSpriteSetDisp(arg2, 0);
    }
}

s32 GetMenuItemNumber__11pdaMemoListFP14tagSPRITE_WORK(MemoWork *arg0, MemoSprite *arg1) {
    struct MemoCursorIds ids = {0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec};
    s32 i0 = ids.a, i1 = ids.b, i2 = ids.c, i3 = ids.d, i4 = ids.e, i5 = ids.f, i6 = ids.g,
        i7 = ids.h;
    s32 result = 0;
    s16 id;
    (u16) memoDataGetCount(0);
    id = arg1->id;
    if (id != i0) {
        result = 1;
        if (id != i1) {
            result = 2;
            if (id != i2) {
                result = 3;
                if (id != i3) {
                    result = 4;
                    if (id != i4) {
                        result = 5;
                        if (id != i5) {
                            result = 6;
                            if (id != i6) {
                                result = 7;
                                if (id != i7)
                                    result = 8;
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

void DownCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                  MemoSprite *arg2) {
    MemoCursor cursor;
    cursor.packed = _getCursor__11pdaMemoListFv(arg0);
    menuPdaSubCheckUpDownCursor(arg1, arg2, &cursor, (u16)memoDataGetCount(0), 8, 0);
}

void UpCursor__11pdaMemoListFP14tagWINDOW_WORKP14tagSPRITE_WORK(MemoWork *arg0, MemoWindow *arg1,
                                                                MemoSprite *arg2) {
    MemoCursor cursor;
    cursor.packed = _getCursor__11pdaMemoListFv(arg0);
    menuPdaSubCheckUpDownCursor(arg1, arg2, &cursor, (u16)memoDataGetCount(0), 8, 1);
}

void Release__11pdaMemoListFv(MemoWork *arg0) {
    menuModelTerm(&arg0->model);
    menuModelTerm(&arg0->hero);
    if ((u32)arg0->ids != 0U) {
        __dla__FPv(arg0->ids);
        arg0->ids = 0U;
    }
    if ((u32)arg0->pokemon != 0U) {
        __dl__FPv(arg0->pokemon);
        arg0->pokemon = 0U;
    }
}

void InitWork__11pdaMemoListFv(MemoWork *arg0) {
    u16 count = (u16)memoDataGetCount(0);
    s32 index;
    MemoItem *item;
    arg0->cursor.pos.selected = 0;
    arg0->cursor.pos.first = 0;
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->targetX = 0.0f;
    arg0->targetY = 0.0f;
    arg0->sort = 0;
    arg0->thread = 0;
    arg0->state = 0;
    if (count >= 8)
        arg0->visible = 8;
    else
        arg0->visible = count;
    if (count != 0) {
        arg0->ids = (u16 *)__nwa__FUl(count * 2);
        arg0->pokemon = (MemoPokemon *)__nw__FUl(sizeof(MemoPokemon));
    }
    item = menuItemBiosGetPtr(0x78, 0xbb);
    menuModelInit(&arg0->model, item->width, item->height);
    menuModelInit(&arg0->hero, 0x280, 0x1e0);
    menuModelTerm(&arg0->hero);
    for (index = 0; index < (u16)memoDataGetCount(0); index++)
        arg0->ids[index] = memoDataGetPokemonID(0, index) & 0x3fff;
    Sort__11pdaMemoListF15menuPdaMemoSort(arg0, 0);
    menuPdaSubInitAlpha(arg0->alpha, 8, 0);
    LoadPokemon__11pdaMemoListFl(arg0, 0);
    arg0->heroLoaded = 0;
    arg0->heroMotion = 0;
    arg0->terminating = 0;
}

s32 Main__11pdaMemoListFP6CURSOR(MemoWork *arg0, MemoCursor *arg1) {
    MemoCursor cursor, copy, returned;
    s32 result;
    u16 count = (u16)memoDataGetCount(0);
    cursor.pos.first = arg1->pos.first;
    cursor.pos.selected = arg1->pos.selected;
    copy.packed = cursor.packed;
    _setCursor__11pdaMemoListF6CURSOR(arg0, &copy);
    menuModelSetZoom(&arg0->model, 1.0f);
    do {
        result = menuOpen(0x78, 1);
        returned.packed = _getCursor__11pdaMemoListFv(arg0);
        cursor.pos.first = returned.pos.first;
        cursor.pos.selected = returned.pos.selected;
    } while (result != -1 && cursor.pos.selected >= 8);
    _menuClose__11pdaMemoListFl(arg0, 0x78);
    if (result == -1 || count == 0)
        return -1;
    arg1->pos.selected = cursor.pos.selected;
    arg1->pos.first = cursor.pos.first;
    return cursor.pos.first + cursor.pos.selected;
}

void Button__11pdaMemoListFP14tagWINDOW_WORK(MemoWork *arg0, MemoWindow *arg1) {
    u16 temp_r31;
    u16 temp_r3;

    if (arg1 != 0) {
        temp_r31 = (u16)memoDataGetCount(0);
        if (winSeqCheckMove(arg1->menu) == 0) {
            temp_r3 = windowGetKeyInfo()->triggers;
            if (((s32)temp_r31 != 0) && ((s32)(temp_r3 & 0x10) != 0)) {
                arg1->accepted = 1;
            }
            if ((s32)(temp_r3 & 0x20) != 0) {
                arg1->accepted = 1;
                arg1->cancelled = 1;
            }
        }
    }
}

void Cursor__11pdaMemoListFP14tagWINDOW_WORK(MemoWork *arg0, MemoWindow *arg1) {
    MemoCursor cursor, copy;
    s32 before;
    u16 count, visible = 8, repeat;
    s16 selected, last;
    windowGetKeyInfo();
    cursor.packed = _getCursor__11pdaMemoListFv(arg0);
    cursor.pos.first = arg1->first;
    cursor.pos.selected = arg1->selected;
    count = (u16)memoDataGetCount(0);
    if (count < 8)
        visible = count;
    before = cursor.pos.first + cursor.pos.selected;
    repeat = windowGetKeyRepeat();
    if (repeat & 1) {
        if (before != 0)
            GSsndPlayNow(0x450);
        cursor.pos.selected--;
    } else if (repeat & 2) {
        if (count - 1 != before)
            GSsndPlayNow(0x450);
        cursor.pos.selected++;
    } else if (repeat & 8) {
        if (count - 1 != before)
            GSsndPlayNow(0x453);
        cursor.pos.selected += visible;
    } else if (repeat & 4) {
        if (before != 0)
            GSsndPlayNow(0x453);
        cursor.pos.selected -= visible;
    }
    selected = cursor.pos.selected;
    if (selected < 0) {
        cursor.pos.selected = 0;
        cursor.pos.first += selected;
        if (cursor.pos.first < 0) {
            cursor.pos.first = 0;
            cursor.pos.selected = 0;
        }
    } else if (selected >= visible) {
        last = visible - 1;
        cursor.pos.first += selected - last;
        cursor.pos.selected = last;
        if (cursor.pos.first + last >= count) {
            cursor.pos.selected = last;
            cursor.pos.first = count - visible;
        }
    }
    copy.packed = cursor.packed;
    _setCursor__11pdaMemoListF6CURSOR(arg0, &copy);
    arg1->first = cursor.pos.first;
    arg1->selected = cursor.pos.selected;
    if (before != cursor.pos.first + cursor.pos.selected)
        LoadPokemon__11pdaMemoListFl(arg0, cursor.pos.first + cursor.pos.selected);
}

void Ctrl__11pdaMemoListFP14tagWINDOW_WORK(MemoWork *arg0, MemoWindow *arg1) {
    f32 angle[3];
    f32 temp_f30;
    f32 temp_f31;
    u8 temp_r0;

    temp_r0 = arg1->phase;
    switch ((s8)temp_r0) { /* irregular */
    case 0:
        if ((s8)arg1->step == 0) {
            winSeqSetMenu(arg1->menu, 0x132);
            arg1->step = 1U;
            temp_f30 = menuPdaMemoListGetDefaultAngle(2);
            temp_f31 = menuPdaMemoListGetDefaultAngle(1);
            angle[0] = menuPdaMemoListGetDefaultAngle(0);
            angle[1] = temp_f31;
            angle[2] = temp_f30;
            menuModelSetAngle(menuPdaMemoListGetMenuModelWork(), angle);
        }
        break;
    case 2:
        ListMain__11pdaMemoListFP14tagWINDOW_WORK(arg0, arg1);
        break;
    case 3:
        if ((s8)arg1->step == 0) {
            winSeqSetMenu(arg1->menu, 0x136);
            arg1->step = 1U;
        }
        break;
    }
}

void ListMain__11pdaMemoListFP14tagWINDOW_WORK(MemoWork *arg0, MemoWindow *arg1) {
    MemoCursor cursor;
    cursor.packed = _getCursor__11pdaMemoListFv(arg0);
    ListPosition__11pdaMemoListFv(arg0);
    CalcPosition__11pdaMemoListFP6CURSOR(arg0, &cursor);
    menuPdaSubCalcAlpha(arg0->alpha, 8, cursor.pos.selected);
}

void ListPosition__11pdaMemoListFv(MemoWork *arg0) {
    if (arg0->x != arg0->targetX)
        menuPdaSubCalcPositon(&arg0->x, arg0->targetX, 10.0f);
    if (arg0->y != arg0->targetY)
        menuPdaSubCalcPositon(&arg0->y, arg0->targetY, 10.0f);
}

void CalcPosition__11pdaMemoListFP6CURSOR(MemoWork *arg0, MemoCursor *arg1) {
    arg0->targetY = (f32)(-arg1->pos.first * 27);
}

void _setCursor__11pdaMemoListF6CURSOR(MemoWork *arg0, const MemoCursor *arg1) {
    MemoCursor copy;
    copy.packed = arg1->packed;
    cursorBiosSetPos(13, &copy);
}

u32 _getCursor__11pdaMemoListFv(MemoWork *arg0) { return cursorBiosGetPos(13); }

void _menuClose__11pdaMemoListFl(MemoWork *arg0, s32 arg1) {
    menuClose(arg1);
    menuCloseSync(arg1, 1);
}

MemoWork *__ct__11pdaMemoListFv(MemoWork *arg0) {
    arg0->ids = 0;
    arg0->pokemon = 0;
    InitWork__11pdaMemoListFv(arg0);
    return arg0;
}

MemoWork *__dt__11pdaMemoListFv(MemoWork *arg0, s16 arg1) {
    if (arg0 != 0) {
        Release__11pdaMemoListFv(arg0);
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

#ifdef __cplusplus
}
#endif
