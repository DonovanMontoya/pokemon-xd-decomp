#include <game/menuPokemonLayout.hpp>

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_NONE,
    MENU_POKEMON_CB_PREV,
    MENU_POKEMON_CB_NEXT
};

struct MENU_POKEMON_STATUS_TBL;

extern "C" {
void *memset(void *, int, u32);
u32 GSflagGet(s32);
void GSfloorPop(void);
void GSfloorPush(s32);
u8 GSgfxVideoGetVsyncRate(void);
void GSthreadSwitch(void);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
Pokemon *fightFloorGetGcHeroFightTrainerPtr(s32);
Hero *fightTrainerGetStatus(FIGHT_TRAINER *, s32, s32, s32);
Pokemon *fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER *, u16);
Pokemon *heroBiosGetPokemonPtr(Hero *, u16);
Hero *menuCBBios_GetRegisteredHero(void);
void menuCloseCustom(s32, s32, s32);
void menuCreateOffScreen(u8, f32, f32);
u8 menuGetOffScreenFlag(void);
void menuOffScreenSetPriority(s32);
void menuReleaseOffScreen(u8, f32);
u8 pokemonCheckValid(Pokemon *);
void msgctrlSetValue(s32, void *);
s32 itemDataBiosGetPtr(u16);
u8 itemDataBiosGetKind(void);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSmsgPrint2(s32, s32, s32, u32, u32);
u8 winSeqCheckMove(s32);
u16 windowGetKeyTrg(void);
u16 menuGetCursorItemID(s32);
void GSsndPlayNow(s32);
void menuButtonNormal(tagWINDOW_WORK *);
s32 menuOpenCustom(s32, s32, s32 *, s32, bool, s32, ...);
void *windowSearchID(s32);
void menuDataBiosGetXY(s16, s16 *, s16 *);
void winSeqSetMenu(s32, s32);
void fadeSet(s32, f32);
void fadeCheck(s32);
void menuPokemonStatusOpenFieldMenu(Pokemon *, Pokemon *(*)(Pokemon *, MENU_POKEMON_CB_TYPE, long), s32);
void menuPokemonStatusOpenFightMenu(FIGHT_TRAINER *, Pokemon *, Pokemon *(*)(Pokemon *, MENU_POKEMON_CB_TYPE, long), s32);
s32 menuOpen(s32, s32);
void menuClose(s32);
u8 menuPokemonCheckPokemonChange(void *, FIGHT_TRAINER *, s32);
void pokemonToMenuPokemonStatus(Pokemon *, s32, MENU_POKEMON_STATUS_TBL *, s32);
u16 pokemonGetJoutaiMenuSpriteId(Pokemon *);
u16 menuPocket2Call(s32, s32, s32);
s32 wazaGetStatus(s32, s32, s32);
void pokemonToMenuWazaStatus(void *);
s32 menuSubOpenSelect2(s32, s32 *, s32, s32, s32, s32, s32, s32);
MENU_POKEMON_STATUS_TBL *windowGetParam(tagWINDOW_WORK *, s32);
void menuItemBiosSetXY(s32, s16, s16, s16);
void menuDataBiosSetXY(s16, s16, s16);
f32 timeGetLastFrameSec(void);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
s32 menuGetCursor(s32);
void pokemonReplace(Pokemon *, Pokemon *);
void menuSubSleep(f32);
u16 windowGetKeyRepeat(u8 *);
u8 menuDataBiosGetDispMax(s32);
extern s32 lbl_804E7EB8;
extern s32 lbl_804E7EBC;
u8 menuPocket2GetLastSlotID(void);
s32 pokemonGetStatus(Pokemon *, s32, s32, s32);
Hero *savedataGetStatus(s32, s32);
}

struct MenuInfoEntry {
    s16 id;
    s16 a;
    s16 b;
    s16 c;
};
struct MenuInfo {
    MenuInfoEntry e[6];
};

static MenuInfo menu_info[2] = {
    { { { 0x4B, 0x15F, 0x12, 0x52 }, { 0x49, 0x15D, 0x113, 0x26 }, { 0x48, 0x15C, 0x113, 0x69 }, { 0x47, 0x15B, 0x113, 0xAC },
        { 0x46, 0x15A, 0x113, 0xEF }, { 0x4D, 0x15A, 0x113, 0x132 } } },
    { { { 0x4B, 0x15F, 0x12, 0x44 }, { 0x4A, 0x15E, 0x12, 0xEA }, { 0x49, 0x15D, 0x113, 0x31 }, { 0x48, 0x15C, 0x113, 0x83 },
        { 0x47, 0x15B, 0x113, 0xD7 }, { 0x46, 0x15A, 0x113, 0x129 } } },
};
static MENU_POKEMON_WORK _menuPokemon;
static s16 _menuPokemonTimer;
static MENU_POKEMON_STATUS_TBL _menuPokemonStatusAll[6];

static Pokemon *_menuPokemonGetPokemonPtr(u16 index);
static Hero *_menuPokemonGetHeroPtr(void);
static void _menuPokemonMakeStatus(MENU_POKEMON_STATUS_TBL *tbl);
static s32 _menuPokemonSub(u8 mode, u32 a, FIGHT_TRAINER *trainer);
static s32 _menuPokemonActionGive(s8 index, short slot, u16 item, u16 *out);
static s32 _menuPokemonActionField(s8 index);
static s32 _menuPokemonActionFieldItem(s8 index);
static s8 _menuPokemonOpenList(bool flag);
static u8 _menuPokemonActionStatus(s8 index, bool flag);
static u8 _menuPokemonMovePanel(long index, u8 mode);
extern "C" u16 menuPokemonGetJoutaiSpriteID(Pokemon *p, u8 mode);

extern "C" {
void menuPokemonInitWork(void)
{
    memset(&_menuPokemon, 0, 0x28);
}

s32 menuPokemonCtrlWaza(void)
{
    return 0;
}

void menuPokemonCloseWazaLight(void)
{
    menuCloseCustom(0x12, 0, 1);
}
}

static Pokemon *_menuPokemonStatusCB(Pokemon *pokemon, MENU_POKEMON_CB_TYPE type, long arg)
{
    int next;
    int cur = _menuPokemon.unk6;
    switch (type) {
    case MENU_POKEMON_CB_PREV:
        next = cur - 1;
        break;
    case MENU_POKEMON_CB_NEXT:
        next = cur + 1;
        break;
    default:
        return pokemon;
    }
    if ((s8)next >= 6) {
        next = 5;
    }
    if ((s8)next < 0) {
        next = 0;
    }
    if ((s8)next != (s8)cur) {
        Pokemon *p = _menuPokemonGetPokemonPtr((s8)next);
        if (p != 0) {
            pokemon = p;
            _menuPokemon.unk6 = next;
        }
    }
    return pokemon;
}

extern "C" {
void menuPokemonClose(void)
{
    menuCloseCustom(0x4C, 0, 1);
    if (_menuPokemon.unk2 != 0) {
        menuOffScreenSetPriority(1);
        GSfloorPop();
        if (_menuPokemon.unk3 != 1) {
            floorSetFadeScript(0, 0);
        }
        floorWaitForChange();
    }
}
}

static s32 _menuPokemonOpen(u8 mode, u8 a, u8 b, u16 c, FIGHT_TRAINER *trainer, bool flag)
{
    _menuPokemon.unk0 = mode;
    _menuPokemon.unk14 = a;
    _menuPokemon.unk15 = b;
    _menuPokemon.unk16 = c;
    _menuPokemon.unk10 = trainer;
    _menuPokemon.unk1 = flag;
    _menuPokemon.unk20 = 0;
    _menuPokemon.unk19 = 1;
    _menuPokemon.unk24 = 0;
    switch (mode) {
    case 4:
        _menuPokemon.unkC = 1;
        break;
    case 2:
        _menuPokemon.unkC = 0;
        break;
    case 3:
    default:
        _menuPokemon.unkC = 0;
        break;
    }
    if ((s32)_menuPokemon.unk0 != 2) {
        if ((s32)_menuPokemon.unk0 < 2) {
            if ((s32)_menuPokemon.unk0 < 1) {
                goto offscreen;
            }
            _menuPokemon.unk2 = 1;
            _menuPokemon.unk3 = 0;
        } else if ((s32)_menuPokemon.unk0 < 9 && (s32)_menuPokemon.unk0 < 6) {
            menuOffScreenSetPriority(0);
            _menuPokemon.unk2 = 0;
            _menuPokemon.unk3 = 0;
        } else {
            goto offscreen;
        }
    } else {
        _menuPokemon.unk2 = 1;
        _menuPokemon.unk3 = 1;
        if (c == 0) {
            _menuPokemon.unk19 = 0;
        }
    offscreen: {
        u8 rate = GSgfxVideoGetVsyncRate();
        menuCreateOffScreen(rate, 20.0f / (f32)rate, 50.0f);
        while (menuGetOffScreenFlag() == 0) {
            GSthreadSwitch();
        }
        _menuPokemon.unk2 = 1;
        _menuPokemon.unk3 = 2;
    }
    }
    if (_menuPokemon.unk2 == 1) {
        GSfloorPush(0x3A5);
        if (_menuPokemon.unk3 != 1) {
            floorSetFadeScript(0, 0);
        }
        floorWaitForChange();
        if (_menuPokemon.unk3 == 2) {
            u8 rate = GSgfxVideoGetVsyncRate();
            menuReleaseOffScreen(rate, 20.0f / (f32)rate);
        }
    } else {
        _menuPokemonSub(mode, c, trainer);
    }
    if ((s32)_menuPokemon.unk0 < 6) {
        if ((s32)_menuPokemon.unk0 >= 3) {
            menuOffScreenSetPriority(1);
        }
    }
    _menuPokemon.unk4 = 1;
    return _menuPokemon.unk20;
}

extern "C" {
void menuPokemonOpenItemGive(u8 a, u8 b, u16 c, FIGHT_TRAINER *t)
{
    _menuPokemon.unk4 = 1;
    _menuPokemonOpen(5, a, b, c, t, 1);
}

void menuPokemonOpenItemUse(u8 mode, bool flag, u16 c, FIGHT_TRAINER *t)
{
    _menuPokemon.unk4 = 1;
    _menuPokemonOpen(mode, 0, 0, c, t, flag);
}

void menuPokemonOpenFight(u8 flag, u8 b, FIGHT_TRAINER *c, void *d)
{
    if (flag == 1) {
        _menuPokemon.unk4 = 0;
    } else {
        _menuPokemon.unk4 = 1;
    }
    _menuPokemon.unk1C = d;
    _menuPokemonOpen(2, 0, 0, b, c, 1);
}

void menuPokemonOpen(u8 mode, u16 c, FIGHT_TRAINER *t)
{
    _menuPokemon.unk4 = 1;
    _menuPokemonOpen(mode, 0, 0, c, t, 1);
}

s32 menuPokemonMain(void)
{
    menuOffScreenSetPriority(0);
    _menuPokemonSub(_menuPokemon.unk0, _menuPokemon.unk16, _menuPokemon.unk10);
    menuPokemonClose();
    menuOffScreenSetPriority(1);
    return 0;
}
}

static Pokemon *_menuPokemonCbLoadPokemonList(void *arg)
{
    u16 *counter = (u16 *)arg;
    Pokemon *p = _menuPokemonGetPokemonPtr(*counter);
    *counter += 1;
    return p;
}

extern "C" {
void menuPokemonUpdate(void)
{
    _menuPokemonMakeStatus(_menuPokemonStatusAll);
}
}

static Hero *_menuPokemonGetHeroPtr(void)
{
    FIGHT_TRAINER *trainer = _menuPokemon.unk10;
    switch (_menuPokemon.unkC) {
    case 0:
        if (GSflagGet(0x30D) == 0) {
            return savedataGetStatus(0, 2);
        }
        return menuCBBios_GetRegisteredHero();
    case 1:
        if (trainer == 0) {
            fightFloorGetGcHeroFightTrainerPtr(0);
            return 0;
        }
        return fightTrainerGetStatus(trainer, 0, 0x44, 0);
    default:
        return 0;
    }
}

static Pokemon *_menuPokemonGetPokemonPtr(u16 index)
{
    Pokemon *p = 0;
    FIGHT_TRAINER *trainer = _menuPokemon.unk10;
    switch (_menuPokemon.unkC) {
    case 0: {
        Hero *hero;
        if (index >= 6) {
            return 0;
        }
        hero = _menuPokemonGetHeroPtr();
        if (hero == 0) {
            return 0;
        }
        p = heroBiosGetPokemonPtr(hero, index);
        break;
    }
    case 1: {
        Pokemon *fp;
        if (index >= 6) {
            return 0;
        }
        if (trainer == 0) {
            fightFloorGetGcHeroFightTrainerPtr(0);
            return 0;
        }
        fp = fightTrainerGetValidFightPokemonPtr(trainer, index);
        if (fp == 0) {
            return 0;
        }
        p = (Pokemon *)pokemonGetStatus(fp, 0, 0xCC, 0);
        break;
    }
    case 2:
        if (index >= 30) {
            return 0;
        }
        p = 0;
        break;
    }
    if (pokemonCheckValid(p) == 0) {
        return 0;
    }
    return p;
}

extern "C" {
void menuPokemonDrawHelp(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    u32 msg = 0;
    switch (_menuPokemon.unk18) {
    case 0:
        switch (_menuPokemon.unk0) {
        case 8:
            msg = 0x3AC7;
            break;
        case 3:
        case 4:
            itemDataBiosGetPtr(_menuPokemon.unk16);
            if (itemDataBiosGetKind() == 4) {
                msg = 0x3AC7;
            } else if (_menuPokemon.unk24 != 0) {
                msg = 0x3C3A;
            } else {
                msg = 0x3AC5;
            }
            break;
        case 5:
            msg = 0x3AC6;
            break;
        case 1:
        case 2:
        default:
            msg = 0x3AC1;
            break;
        }
        break;
    case 1:
        msgctrlSetValue(0x32, &_menuPokemonStatusAll[(s8)_menuPokemon.unk6]);
        msg = 0x3AC2;
        break;
    case 2:
        msg = 0x3AC3;
        break;
    case 3:
        msg = 0x3AC4;
        break;
    }
    if (msg != 0) {
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, window->unk93 | 0xFFFFFF00, msg);
    }
}

void menuPokemonButton(tagWINDOW_WORK *window)
{
    u8 flag = 0;
    if (_menuPokemon.unk1 == 0) {
        window->unkA4 = 1;
        return;
    }
    if (winSeqCheckMove(0x4B) == 0) {
        u16 key = windowGetKeyTrg();
        if ((key & 0x10) != 0) {
            if (menuGetCursorItemID(window->unk4) == 0x162) {
                flag = 1;
            }
        } else if ((key & 0x20) != 0) {
            flag = 1;
        }
        if (flag != 0) {
            if (_menuPokemon.unk19 == 0) {
                GSsndPlayNow(0x13);
                return;
            }
            window->unkA4 = 1;
            window->unkA5 = 1;
            return;
        }
        menuButtonNormal(window);
    }
}
}

static s8 _menuPokemonOpenList(bool flag)
{
    s32 sel = (s8)_menuPokemon.unk6;
    s8 r = menuOpenCustom(0x4C, 0, &sel, 0, flag, 1, _menuPokemonStatusAll);
    if (flag == 0) {
        tagWINDOW_WORK *w = (tagWINDOW_WORK *)windowSearchID(0x4C);
        if (w != 0) {
            w->unkA4 = 1;
        }
        r = (s8)sel;
    }
    if (_menuPokemon.unk1 == 0) {
        r = -2;
    }
    return r;
}

static u8 _menuPokemonActionStatus(s8 index, bool flag)
{
    Pokemon *p;
    menuCloseCustom(0x4C, 0, 1);
    p = _menuPokemonGetPokemonPtr(index);
    fadeSet(3, 0.25f);
    fadeCheck(1);
    menuOffScreenSetPriority(0);
    if (flag) {
        menuPokemonStatusOpenFieldMenu(p, _menuPokemonStatusCB, 0);
    } else {
        menuPokemonStatusOpenFightMenu(_menuPokemon.unk10, p, _menuPokemonStatusCB, 0);
    }
    menuOffScreenSetPriority(1);
    _menuPokemonOpenList(0);
    fadeSet(2, 0.25f);
    fadeCheck(1);
    return _menuPokemon.unk6;
}

static s32 _menuPokemonActionFight(s8 index)
{
    s32 result;
    _menuPokemon.unk18 = 1;
loop:
    if (_menuPokemon.unk19 != 0) {
        result = menuOpen(0x50, 1);
        menuClose(0x50);
    } else {
        result = menuOpen(0x51, 1);
        menuClose(0x51);
    }
    switch (result) {
    case 0:
        if (menuPokemonCheckPokemonChange(_menuPokemon.unk1C, _menuPokemon.unk10, index) != 0) {
            result = -1;
        } else {
            result = 1;
        }
        break;
    case -1:
    case 2:
    default:
        result = 1;
        break;
    case 1:
        index = _menuPokemonActionStatus(index, 0);
        goto loop;
    }
    return result;
}

static s32 _menuPokemonActionField(s8 index)
{
    s32 result;
    do {
        _menuPokemon.unk18 = 1;
        if (GSflagGet(0x30D) == 0) {
            result = menuOpen(0x4F, 1);
            menuClose(0x4F);
        } else {
            result = menuOpen(0x5A, 1);
            menuClose(0x5A);
        }
        switch (result) {
        case 429:
        case 367:
            result = 0;
            index = _menuPokemonActionStatus(index, 1);
            break;
        case 431:
        case 369: {
            s8 other;
            _menuPokemon.unk8 = index;
            _menuPokemon.unk18 = 2;
            other = _menuPokemonOpenList(1);
            _menuPokemon.unk8 = -1;
            if (menuGetCursorItemID(0x4C) != 0x163 && other != -1) {
                Pokemon *a = _menuPokemonGetPokemonPtr(index);
                Pokemon *b = _menuPokemonGetPokemonPtr((s8)(u16)other);
                if (a != 0 && a != 0) {
                    _menuPokemonMovePanel(index, 1);
                    _menuPokemonMovePanel(other, 1);
                    while (_menuPokemonMovePanel(index, 2) != 0) {
                        GSthreadSwitch();
                    }
                    pokemonReplace(a, b);
                    menuPokemonUpdate();
                    menuSubSleep(0.25f);
                    _menuPokemonMovePanel(index, 0);
                    _menuPokemonMovePanel(other, 0);
                    while (_menuPokemonMovePanel(index, 2) != 0) {
                        GSthreadSwitch();
                    }
                }
            }
            result = -1;
            break;
        }
        case 371:
            if (_menuPokemonActionFieldItem(index) == -1) {
                result = 0;
            } else {
                result = -1;
            }
            break;
        case 433:
        case 373:
        case -1:
            result = -1;
            break;
        }
    } while (result != -1);
    return 0;
}

static s32 _menuPokemonActionFieldItem(s8 index)
{
    u16 out;
    s32 result;
    _menuPokemon.unk18 = 3;
    result = menuOpen(0x5D, 1);
    menuClose(0x5D);
    switch (result) {
    case 0: {
        u16 item;
        u8 slot;
        menuClose(0x4C);
        item = menuPocket2Call(2, 0, 0);
        slot = menuPocket2GetLastSlotID();
        _menuPokemonOpenList(0);
        if (item == 0) {
            return -1;
        }
        _menuPokemonActionGive(index, slot, item, &out);
        result = 0;
        break;
    }
    case 1:
        _menuPokemonActionGive(index, -1, 0, &out);
        result = 0;
        break;
    case 2:
    case -1:
        result = -1;
        break;
    }
    return result;
}

static u8 _menuPokemonMovePanel(long index, u8 mode)
{
    s16 x;
    s16 y;
    s16 id = menu_info[(s8)_menuPokemon.unk4].e[index].id;
    menuDataBiosGetXY(id, &x, &y);
    switch (mode) {
    case 0:
        winSeqSetMenu(id, x > 250 ? 0x98 : 0xA0);
        break;
    case 1:
        winSeqSetMenu(id, x > 250 ? 0x9C : 0xA4);
        break;
    case 2:
        return winSeqCheckMove(id);
    }
    return 1;
}

static void _menuPokemonMakeStatus(MENU_POKEMON_STATUS_TBL *tbl)
{
    MENU_POKEMON_STATUS_TBL *e;
    Pokemon *p;
    u16 i;
    memset(tbl, 0, 0x120);
    for (i = 0; i < 6; i++) {
        e = &tbl[i];
        p = _menuPokemonGetPokemonPtr(i);
        if (p == 0) {
            e->unk0 = 0;
        } else {
            pokemonToMenuPokemonStatus(p, 0, e, -1);
            if ((u32)(pokemonGetStatus(p, 0, 0x7B, 0) != 0) == 1) {
                e->unk1A = 0;
            }
            e->unk24 = menuPokemonGetJoutaiSpriteID(p, 0);
        }
    }
}

extern "C" u16 menuPokemonGetJoutaiSpriteID(Pokemon *p, u8 mode)
{
    static u16 top_joutai_tbl[8] = { 0, 0x142, 0x146, 0x143, 0x144, 0x145, 0x148, 0 };
    static u16 status_joutai_tbl[7] = { 0, 0x7E, 0x83, 0x80, 0x81, 0x82, 0x85 };
    u16 id;
    if ((u32)(pokemonGetStatus(p, 0, 0x7B, 0) != 0) == 1) {
        id = 1;
    } else {
        switch (pokemonGetJoutaiMenuSpriteId(p)) {
        case 0x83:
            id = 2;
            break;
        case 0x80:
            id = 3;
            break;
        case 0x81:
            id = 4;
            break;
        case 0x82:
            id = 5;
            break;
        case 0x85:
            id = 6;
            break;
        default:
            id = 0;
            break;
        }
    }
    if (mode == 0) {
        return top_joutai_tbl[id];
    }
    return status_joutai_tbl[id];
}

extern "C" {
s32 menuPokemonOpenWazaLight(s8 index)
{
    static u8 wazaStatus[0x48];
    s32 ids[4];
    s32 *p;
    s32 count;
    Pokemon *pokemon = _menuPokemonGetPokemonPtr(index);
    s32 i;
    s32 result;
    if (pokemon == 0) {
        return -1;
    }
    pokemonToMenuWazaStatus(wazaStatus);
    count = 0;
    p = &ids[count];
    for (i = 0; i < 4; i++) {
        u16 id = pokemonGetStatus(pokemon, 0, 0x7F, i);
        if (id != 0) {
            *p = wazaGetStatus(0, 1, 0);
            count++;
        }
        p++;
    }
    menuOffScreenSetPriority(0);
    _menuPokemon.unk24 = 1;
    result = menuSubOpenSelect2(0, ids, count, 0x1BD - lbl_804E7EB8, lbl_804E7EBC + 0x12C, 0, count, 0);
    _menuPokemon.unk24 = 0;
    menuOffScreenSetPriority(1);
    return result;
}

s32 menuPokemonCtrl(tagWINDOW_WORK *window)
{
    MENU_POKEMON_STATUS_TBL *tbl = windowGetParam(window, 0);
    if (tbl == 0) {
        return 0;
    }
    menuOffScreenSetPriority(0);
    if (window->unk1 == 0) {
        window->unkA2 = -1;
        if (window->unk2 == 0) {
            s32 off = 0;
            MENU_POKEMON_STATUS_TBL *entry = tbl;
            s32 k = 0;
            do {
                MenuInfoEntry *e = (MenuInfoEntry *)((u8 *)&menu_info[(s8)_menuPokemon.unk4] + off);
                menuItemBiosSetXY(window->unk4, e->a, e->b, e->c);
                e = (MenuInfoEntry *)((u8 *)&menu_info[(s8)_menuPokemon.unk4] + off);
                menuDataBiosSetXY(e->id, e->b, e->c);
                menuOpenCustom(*(s16 *)((u8 *)&menu_info[(s8)_menuPokemon.unk4] + off), 0x4C, 0, 0, 0, 2, entry, k);
                _menuPokemonMovePanel(k, 0);
                off += 8;
                entry++;
                k++;
            } while (k < 6);
            winSeqSetMenu(window->unk4, 1);
            window->unk2 = 1;
        }
        menuOffScreenSetPriority(0);
    } else if (window->unk1 == 3 && window->unk2 == 0) {
        s32 k = 0;
        do {
            _menuPokemonMovePanel(k, 1);
            k++;
        } while (k < 6);
        winSeqSetMenu(window->unk4, 7);
        window->unk2 = 1;
    }
    _menuPokemonTimer = (s32)(60.0f * timeGetLastFrameSec() + (f32)_menuPokemonTimer) % 1000;
    return 0;
}
}

extern "C" {
void menuPokemonCursor(tagWINDOW_WORK *window)
{
    u8 enabled[8];
    u8 *p;
    s8 cur;
    s8 dir;
    int i;
    u16 keys;
    dir = 0;
    cur = window->unk9E;
    for (p = enabled, i = 0; i < 6; p++, i++) {
        if (_menuPokemonGetPokemonPtr(i) != 0) {
            *p = 1;
        } else {
            *p = 0;
        }
    }
    enabled[i] = 1;
    keys = windowGetKeyRepeat(enabled);
    if ((keys & 8) != 0) {
        dir = 1;
        if (_menuPokemon.unk4 == 0) {
            if (cur == 0) {
                if (_menuPokemon.unk5 == 3) {
                    cur = _menuPokemon.unk5;
                } else {
                    cur = 2;
                }
            }
        } else if (cur == 0) {
            if (_menuPokemon.unk5 == 3) {
                cur = _menuPokemon.unk5;
            } else {
                cur = 2;
            }
        } else if (cur == 1) {
            if (_menuPokemon.unk5 == 5) {
                cur = _menuPokemon.unk5;
            } else {
                cur = 4;
            }
        }
    } else if ((keys & 4) != 0) {
        dir = -1;
        if (_menuPokemon.unk4 == 0) {
            if (cur < 6) {
                if (cur < 1) {
                    (void)0;
                } else {
                    cur = 0;
                }
            }
        } else if (_menuPokemon.unk4 == 1) {
            if (cur < 4) {
                if (cur < 2) {
                    (void)0;
                } else {
                    cur = 0;
                }
            } else if (cur < 6) {
                cur = 1;
            }
        }
    }
    if ((keys & 1) != 0) {
        cur -= 1;
        dir = -1;
        if (cur < 0) {
            cur = 6;
        }
    } else if ((keys & 2) != 0) {
        dir = 1;
        cur += 1;
        if (cur >= menuDataBiosGetDispMax(window->unk4)) {
            cur = 0;
        }
    }
    if (dir != 0) {
        u8 *q = &enabled[cur];
        while (*q == 0) {
            cur += dir;
            q += dir;
            if (cur < 0 || cur >= 7) {
                cur = 7;
                break;
            }
        }
    }
    if (window->unk9E != cur) {
        _menuPokemon.unk5 = (s8)window->unk9E;
        _menuPokemon.unk6 = cur;
        _menuPokemon.unk7 = cur;
        window->unk9E = cur;
    }
}
}

extern "C" {
void menuPokemonDrawCur(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    winSpriteSetDisp(sprite, 0);
    switch (menuGetCursor(window->unk4)) {
    case 0:
        switch (sprite->unk6) {
        case 0x16E:
        case 0x191:
        case 0x1A8:
        case 0x1AC:
        case 0x1BB:
            winSpriteSetDisp(sprite, 1);
            return;
        }
        break;
    case 1:
        switch (sprite->unk6) {
        case 0x170:
        case 0x183:
        case 0x193:
        case 0x1AE:
        case 0x1BD:
            winSpriteSetDisp(sprite, 1);
            return;
        }
        break;
    case 2:
        switch (sprite->unk6) {
        case 0x172:
        case 0x195:
        case 0x1AA:
        case 0x1B0:
        case 0x1BF:
            winSpriteSetDisp(sprite, 1);
            return;
        }
        break;
    case 3:
        switch (sprite->unk6) {
        case 0x174:
            winSpriteSetDisp(sprite, 1);
            return;
        }
        break;
    }
}
}

static int _menuPokemonCheckItem(tagSPRITE_WORK *sprite, s8 kind)
{
    int enable = 1;
    s32 color = -1;
    if (kind == -1) {
        switch (sprite->unk6) {
        case 0x131:
        case 0x133:
        case 0x135:
        case 0x136:
        case 0x137:
        case 0x138:
        case 0x139:
        case 0x13A:
        case 0x13B:
        case 0x13E:
        case 0x140:
        case 0x141:
        case 0x142:
        case 0x143:
        case 0x144:
        case 0x145:
        case 0x146:
        case 0x2DD:
            enable = 0;
            break;
        }
    } else if (kind == 1) {
        switch (sprite->unk6) {
        case 0x131:
        case 0x132:
        case 0x13C:
        case 0x13D:
        case 0x1C4:
        case 0x2CF:
        case 0x2D0:
        case 0x2DD:
            color = 0x808080FF;
            break;
        }
    }
    winSpriteSetDisp(sprite, enable);
    sprite->unk64 = color;
    return enable;
}
