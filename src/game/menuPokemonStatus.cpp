#include <game/menuPokemonStatusLayout.hpp>

extern "C" {
s32 GScharCmp(u8*, u8*);
u32 GSflagGet(s32);
u8* GSmsgGetGSchar(s32);
u32 fightFloorGetGcHeroFightTrainerPtr(s32);
Hero* fightTrainerBiosGetHeroPtr(FIGHT_TRAINER*);
u8 gamedataGetStatus(s32, s32);
u8* heroBiosGetNamePtr(Hero*);
u32 heroBiosGetRnd(Hero*);
Hero* menuCBBios_GetRegisteredHero(void);
s32 pokemonGetStatus(Pokemon*, u16, u16, u16);
u8 pokemonCheckValid(Pokemon*);
u16 windowGetKeyTrg(void);
void pokemonWazaReplace(Pokemon*, s32, s32);
u8 menuIsCheck(s32);
void menuSetDisp(s32, s32);
u8 menuFaceCheckLoading(void);
void GSthreadSwitch(void);
void GSfloorPush(s32);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void menuOpen(s32, s32);
void menuClose(s32);
void* memset(void*, int, u32);
void menuDrawReliveUpdate(void);
Pokemon* heroBiosGetPokemonPtr(Hero*, u16);
void fadeCheck(s32);
void fadeSet(s32, f32);
void GSfloorPop(void);
void GSsndPlayNow(s32);
void menuModelInit(void*, s16, s16);
void menuModelFree(void*);
void menuModelTerm(void*);
void menuModelLoadPokemon(void*, Pokemon*);
void menuOffScreenSetPriority(s32);
s32 menuOpenCustom(s32, s32, ...);
void menuCloseCustom(s32, s32, s32);
s32 wazaGetStatus(s32, u16, s32, s32);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
struct MenuItemRect {
    u8 reserved0[0xA];
    s16 width;
    s16 height;
};
MenuItemRect* menuItemBiosGetPtr(s32, s32);
u8 pokemonWazaCheckValid(Pokemon*, u16);
void* savedataGetStatus(s32, s32);
u16 zokuseiBiosGetSpriteID(u16);
}

struct DarkPokemon {
    u8 isWazaNew(u8) const;
};
struct Pokemon {
    u8 isDarkPokemon() const;
    DarkPokemon* getDarkPokemon();
};

static MenuPokemonStatus _menuStatus;
static u8 _menuModel[0x1D8];

void _menuPokemonStatusMakeRibbon(Pokemon*, RIBBON_WORK*);
static s32 _menuPokemonStatusSub(u8, FIGHT_TRAINER*, Pokemon*, u16, MenuPokemonStatusCb, long);
static s32 _menuPokemonStatusChangeSubMenu(CURSOR);
static s32 _menuPokemonStatusOpen(u8, FIGHT_TRAINER*, Pokemon*, u16, MenuPokemonStatusCb, long);
extern "C" void menuPokemonStatusClose(void);

static s32 NotDarkWaza(long id) {
    if (id < 0x176 && id >= 0x164) {
        return 0;
    }
    return id;
}

static u16 _menuPokemonStatusGetZokuseiSpriteID(u16 id) {
    return zokuseiBiosGetSpriteID(id);
}

extern "C" void menuPokemonStatusChangeColor(void) {}

u16 _menuPokemonStatusGetWazaDataID(Pokemon* pokemon, u16 index) {
    u16 id;
    if (index == 4) {
        id = _menuStatus.wazaId;
    } else {
        id = pokemonGetStatus(pokemon, 0, 0x7F, index);
        if (pokemonWazaCheckValid(pokemon, index) == 0) {
            return 0;
        }
    }
    return id;
}

s32 _menuPokemonStatusCheckDanny(Pokemon* pokemon) {
    if ((u16)pokemonGetStatus(pokemon, 0, 0x75, 0) == 0xA1B8) {
        u8* name = GSmsgGetGSchar(0x1828);
        if (GScharCmp((u8*)pokemonGetStatus(pokemon, 0, 0x76, 0), name) == 0) {
            return 1;
        }
    }
    return 0;
}

s32 _menuPokemonStatusCheckGinzaru(Pokemon* pokemon) {
    if ((u16)pokemonGetStatus(pokemon, 0, 0x75, 0) == 0x911D) {
        u8* name = GSmsgGetGSchar(0x17B9);
        if (GScharCmp((u8*)pokemonGetStatus(pokemon, 0, 0x76, 0), name) == 0) {
            return 1;
        }
    }
    return 0;
}

s32 _menuPokemonStatusCheckOya(Pokemon* pokemon) {
    FIGHT_TRAINER* trainer = _menuStatus.trainer;
    Hero* hero;
    u8* name;
    u32 rnd;
    if (pokemon == 0) {
        return 0;
    }
    if (gamedataGetStatus(pokemonGetStatus(pokemon, 0, 0x70, 0), 2) != 0xB) {
        return 0;
    }
    if (_menuStatus.flags & 0x20) {
        if (trainer == 0) {
            trainer = (FIGHT_TRAINER*)fightFloorGetGcHeroFightTrainerPtr(0);
        }
        if (trainer == 0) {
            return 0;
        }
        hero = fightTrainerBiosGetHeroPtr(trainer);
    } else if (GSflagGet(0x30D) == 0) {
        hero = (Hero*)savedataGetStatus(0, 2);
    } else {
        hero = menuCBBios_GetRegisteredHero();
    }
    name = heroBiosGetNamePtr(hero);
    rnd = heroBiosGetRnd(hero);
    if (rnd == pokemonGetStatus(pokemon, 0, 0x75, 0)) {
        if (GScharCmp(name, (u8*)pokemonGetStatus(pokemon, 0, 0x76, 0)) == 0) {
            return 1;
        }
    }
    return 0;
}

extern "C" {

void menuPokemonStatusCtrlRibbon(void) {
    if (_menuStatus.pokemon != 0) {
        _menuPokemonStatusMakeRibbon(_menuStatus.pokemon, &_menuStatus.ribbon);
    }
}

}

static s32 _menuPokemonStatusSub(u8, FIGHT_TRAINER*, Pokemon* pokemon, u16, MenuPokemonStatusCb, long) {
    s32 sp8;
    s32 res;
    u16 wazaId;
    MenuItemRect* item = menuItemBiosGetPtr(0x5E, 0x81F);
    menuModelInit(_menuModel, item->width, item->height);
    menuModelFree(_menuModel);
    menuModelLoadPokemon(_menuModel, pokemon);
    if (_menuStatus.flags & 8) {
        fadeCheck(1);
        if (_menuStatus.flags & 0x80) {
            fadeSet(2, 0.25f);
        } else {
            fadeSet(2, 0.5f);
        }
    }
    sp8 = 0;
    menuOffScreenSetPriority(0);
    for (;;) {
        res = menuOpenCustom(0x5E, 0, &sp8, 0, 1, 0);
        if (res == -1) {
            _menuStatus.result = res;
            break;
        }
        _menuStatus.result = _menuStatus.page;
        if (_menuStatus.flags & 0x40) {
            wazaId = _menuPokemonStatusGetWazaDataID(_menuStatus.pokemon, _menuStatus.page);
            if (wazaGetStatus(0, wazaId, 0x19, 0) != 0) {
                GSsndPlayNow(0x13);
                winMsgOpen(2, 0x3AFC, 1, 0);
                winMsgClose(1);
                sp8 = _menuStatus.page;
                continue;
            }
        }
        break;
    }
    if (_menuStatus.flags & 8) {
        fadeCheck(1);
        if (_menuStatus.flags & 0x80) {
            fadeSet(3, 0.25f);
        } else {
            fadeSet(3, 0.5f);
        }
        fadeCheck(1);
    }
    menuPokemonStatusClose();
    menuModelTerm(_menuModel);
    menuOffScreenSetPriority(1);
    GSthreadSwitch();
    return _menuStatus.result;
}

extern "C" void menuPokemonStatusClose(void) {
    u8 flags = _menuStatus.flags;
    if (flags & 1) {
        if (!(flags & 8)) {
            fadeCheck(1);
            fadeSet(3, 0.5f);
            fadeCheck(1);
        }
    }
    if (menuIsCheck(0x5F)) {
        menuCloseCustom(0x5F, 0, 0);
    }
    if (menuIsCheck(0x60)) {
        menuCloseCustom(0x60, 0, 0);
    }
    if (menuIsCheck(0x62)) {
        menuCloseCustom(0x62, 0, 0);
    }
    if (menuIsCheck(0x63)) {
        menuCloseCustom(0x63, 0, 0);
    }
    menuCloseCustom(0x5E, 0, 1);
    if (_menuStatus.flags & 1) {
        GSfloorPop();
        if (_menuStatus.flags & 8) {
            floorSetFadeScript(0, 0);
        }
    }
}

static s32 _menuPokemonStatusChangeSubMenu(CURSOR cursor) {
    static const s32 sub_menu_id[4] = {0x5F, 0x60, 0x62, 0x63};
    u32 i;
    s32 id = 0;
    if (_menuStatus.pokemon == 0) {
        return -1;
    }
    switch (cursor.selected) {
    case 0:
        id = 0x5F;
        break;
    case 1:
        id = 0x60;
        break;
    case 2:
        id = 0x62;
        break;
    case 3:
        id = 0x63;
        break;
    }
    for (i = 0; i < 4; i++) {
        if (id == sub_menu_id[i]) {
            if (!menuIsCheck(id)) {
                menuOpen(id, 0);
            }
        } else if (menuIsCheck(sub_menu_id[i])) {
            menuClose(sub_menu_id[i]);
        }
    }
    return -1;
}

extern "C" s32 menuPokemonStatusCtrl(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
        win->prevCursor = -1;
        _menuStatus.mode = 0;
        _menuStatus.page = win->pos.selected;
        _menuStatus.prevPage = -1;
        _menuStatus.unk1A = -1;
        if (_menuStatus.flags & 4) {
            win->pos.selected = 0;
            _menuStatus.mode = 8;
        } else {
            win->pos.selected = 2;
            _menuStatus.mode = 7;
        }
        _menuPokemonStatusChangeSubMenu(win->pos);
        break;
    case 1:
        break;
    case 2:
        _menuPokemonStatusChangeSubMenu(win->pos);
        menuDrawReliveUpdate();
        break;
    }
    return 0;
}

static s32 _menuPokemonStatusOpen(u8 flags, FIGHT_TRAINER* trainer, Pokemon* pokemon, u16 wazaId, MenuPokemonStatusCb callback, long arg) {
    s32 i;
    DarkPokemon* dark;
    s32 id;
    while (menuFaceCheckLoading()) {
        GSthreadSwitch();
    }
    memset(&_menuStatus, 0, 0x48);
    _menuStatus.flags = flags;
    _menuStatus.trainer = trainer;
    _menuStatus.pokemon = pokemon;
    _menuStatus.wazaId = wazaId;
    _menuStatus.callback = callback;
    _menuStatus.callbackArg = arg;
    _menuStatus.result = -1;
    for (i = 0; i < 4; i++) {
        _menuStatus.wazaNew[i] = 0;
        if (pokemon->isDarkPokemon()) {
            dark = pokemon->getDarkPokemon();
            if (dark != 0) {
                id = (u16)pokemonGetStatus(pokemon, 0, 0x7F, (u8)i);
                if (id < 0x164) {
                    if (id == 0) {
                        continue;
                    }
                } else if (id < 0x177) {
                    continue;
                }
                if (i != 0) {
                    if (!dark->isWazaNew(i - 1)) {
                        _menuStatus.wazaNew[i] = 1;
                    }
                }
            }
        }
    }
    if (flags & 1) {
        GSfloorPush(0x39D);
        if (_menuStatus.flags & 8) {
            floorSetFadeScript(0, 0);
        }
        floorWaitForChange();
    } else {
        _menuPokemonStatusSub(flags, trainer, pokemon, wazaId, callback, arg);
    }
    return _menuStatus.result;
}

extern "C" {

s32 menuPokemonStatusOpenWazaLearn(Pokemon* pokemon, u16 wazaId) {
    s32 ids[4] = {0x37, 0x40, 0x38, 0x41};
    s32 result;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 0);
        }
    }
    result = _menuPokemonStatusOpen(0x59, 0, pokemon, wazaId, 0, 0);
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 1);
        }
    }
    return result;
}

s32 menuPokemonStatusOpenWazaLearnList(Pokemon* pokemon, u16 wazaId) {
    s32 ids[4] = {0x37, 0x40, 0x38, 0x41};
    s32 result;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 0);
        }
    }
    result = _menuPokemonStatusOpen(0x19, 0, pokemon, wazaId, 0, 0);
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 1);
        }
    }
    return result;
}

s32 menuPokemonStatusOpenWazaMachine(Pokemon* pokemon, u16 wazaId) {
    return _menuPokemonStatusOpen(0x58, 0, pokemon, wazaId, 0, 0);
}

s32 menuPokemonStatusOpenFromPokemonChange(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg) {
    return _menuPokemonStatusOpen(0xC, 0, pokemon, 0, callback, arg);
}

s32 menuPokemonStatusOpenFromPcBox(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg) {
    return _menuPokemonStatusOpen(0xE, 0, pokemon, 0, callback, arg);
}

s32 menuPokemonStatusOpenFieldMenu(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg) {
    return _menuPokemonStatusOpen(0x8E, 0, pokemon, 0, callback, arg);
}

s32 menuPokemonStatusOpenFightMenu(FIGHT_TRAINER* trainer, Pokemon* pokemon, MenuPokemonStatusCb callback, long arg) {
    return _menuPokemonStatusOpen(0xAC, trainer, pokemon, 0, callback, arg);
}

void menuPokemonStatus(void) {
    _menuStatus.result = _menuPokemonStatusSub(_menuStatus.flags, _menuStatus.trainer, _menuStatus.pokemon,
                                               _menuStatus.wazaId, _menuStatus.callback, _menuStatus.callbackArg);
}

s32 menuPokemonStatusOpenWazaList(u8 index) {
    Pokemon* pokemon = 0;
    Hero* hero;
    if (index < 6) {
        hero = (Hero*)savedataGetStatus(0, 2);
        if (hero != 0) {
            pokemon = heroBiosGetPokemonPtr(hero, index);
            if (!pokemonCheckValid(pokemon)) {
                pokemon = 0;
            }
        }
    }
    if (pokemon == 0) {
        return -1;
    }
    return _menuPokemonStatusOpen(0x11, 0, pokemon, 0, 0, 0);
}

}

extern "C" void menuPokemonStatusButton(tagWINDOW_WORK* win) {
    u16 key = windowGetKeyTrg();
    if (key & 0x10) {
        switch (_menuStatus.mode) {
        case 0:
        case 1:
        case 6:
        case 8:
        case 9:
            break;
        case 2:
            _menuStatus.page = 0;
            _menuStatus.mode = 3;
            GSsndPlayNow(0x11);
            break;
        case 3:
            if (_menuStatus.pokemon != 0) {
                if (pokemonGetStatus(_menuStatus.pokemon, 0, 0xC2, 0) != 0) {
                    GSsndPlayNow(0x13);
                } else if (_menuStatus.flags & 2) {
                    _menuStatus.mode = 4;
                    _menuStatus.prevPage = _menuStatus.page;
                    GSsndPlayNow(0x11);
                } else {
                    GSsndPlayNow(0x13);
                }
            }
            break;
        case 4:
            if (_menuStatus.prevPage != _menuStatus.page) {
                if (_menuStatus.pokemon != 0) {
                    pokemonWazaReplace(_menuStatus.pokemon, _menuStatus.prevPage, _menuStatus.page);
                }
                _menuStatus.prevPage = -1;
                _menuStatus.mode = 3;
                GSsndPlayNow(0x11);
            }
            break;
        case 5:
            if (_menuStatus.ribbon.count > 0) {
                s8 i;
                for (i = 0; i < 36; i++) {
                    if (_menuStatus.ribbon.slots[(i % 9) * 4 + i / 9] >= 0) {
                        break;
                    }
                }
                _menuStatus.mode = 6;
                _menuStatus.unk1A = i;
                GSsndPlayNow(0x11);
            }
            break;
        case 7:
            if (_menuStatus.flags & 0x10) {
                win->finished = 1;
                _menuStatus.result = _menuStatus.page;
            }
            break;
        }
    } else if (key & 0x20) {
        switch (_menuStatus.mode) {
        case 0:
        case 9:
            break;
        case 1:
        case 2:
        case 5:
        case 7:
        case 8:
            win->finished = 1;
            win->cancelled = 1;
            _menuStatus.mode = 9;
            break;
        case 3:
            _menuStatus.mode = 2;
            GSsndPlayNow(0x12);
            break;
        case 4:
            _menuStatus.mode = 3;
            GSsndPlayNow(0x12);
            break;
        case 6:
            _menuStatus.unk1A = -1;
            _menuStatus.mode = 5;
            GSsndPlayNow(0x12);
            break;
        }
    }
}
