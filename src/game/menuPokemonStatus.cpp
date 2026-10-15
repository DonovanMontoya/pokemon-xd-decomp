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
    u8 reserved0[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};
MenuItemRect* menuItemBiosGetPtr(s32, s32);
u8 pokemonWazaCheckValid(Pokemon*, u16);
void* savedataGetStatus(s32, s32);
u16 zokuseiBiosGetSpriteID(u16);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
tagWINDOW_WORK* windowSearchID(s32);
u32 getRibbonCnt(void);
u8 exribbonGetNo(s32);
u32 getRibbonMsgID(s32);
void msgctrlSetValue(s32, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
void windowDrawSprite(s16, s16, tagWINDOW_WORK*, s32, s32, s32);
u16 windowGetKeyRepeat(void);
void* pokemonDataBiosGetPtr(u16);
u8 pokemonIsDarkPokemon(Pokemon*);
void menuModelSetSize(void*, s16, s16, s16, s16);
u8 menuModelCheck(void*, s32);
void menuModelAdjustCamera(void*);
void menuModelSetAngle(void*, f32*);
void menuModelRender(void*);
u8 pokemonBiosGetCatchBallId(Pokemon*);
u32 mballBiosGetSpriteID(u8);
void windowDrawSprite2(s32, s32, s32, s32, s32, tagWINDOW_WORK*, s32, s32, s32);
s32 menuPokemonGetJoutaiSpriteID(Pokemon*, s32);
u32 pokemonGetSoubiItemDataId(Pokemon*);
u8 pokemonCheckRare(Pokemon*);
u8 menuSubGetPokemonSexForDisp(Pokemon*);
u32 GSmsgGetRect(u32);
u8 wazaDB_GetCompatible(u32);
u16 zokuseiBiosGetWazaJoutai(u16, u16);
u8 pokemonWazaGetMaxPP(Pokemon*, u8);
void GSmsgPrintRight(s32, s32, s32, s32, s32, u32, u32);
u8 pokemonGetDarkPokemonLevel(Pokemon*);
void* pokemonSeikakuDataBiosGetPtr(u32);
u32 pokemonSeikakuDataBiosGetName(void*);
u32 floorGetPlaceName(u16);
u8 fightKind_CheckFightKind(s32);
u32 pokemonGetLevelToExp(Pokemon*, u8);
u16 pokemonGetTokuseiDataId(Pokemon*);
void* pokemonTokuseiDataBiosGetPtr(u16);
void* pokemonTokuseiDataBiosGetDoc(void*);
void* pokemonTokuseiDataBiosGetName(void*);
void menuDrawReliveMeter(Pokemon*, s32, s32, s32);
u8 pokemonDataBiosGetZokuseiDataId(void*, s32);
u32 zokuseiGetPokemonSpriteID(void*, u16);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void menuPlaySe(s32, s32);
u8 menuModelComparePokemon(void*, Pokemon*);
}

struct DarkPokemon {
    u8 isWazaNew(u8) const;
    void setWazaNew(u8, bool);
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

u8 _menuPokemonStatusCheckDanny(Pokemon* pokemon) {
    s32 id = pokemonGetStatus(pokemon, 0, 0x75, 0) & 0xFFFF;
    if (id == 0xA1B8) {
        if (GScharCmp((u8*)pokemonGetStatus(pokemon, 0, 0x76, 0), GSmsgGetGSchar(0x1828)) == 0) {
            return 1;
        }
    }
    return 0;
}

u8 _menuPokemonStatusCheckGinzaru(Pokemon* pokemon) {
    s32 id = pokemonGetStatus(pokemon, 0, 0x75, 0) & 0xFFFF;
    if (id == 0x911D) {
        if (GScharCmp((u8*)pokemonGetStatus(pokemon, 0, 0x76, 0), GSmsgGetGSchar(0x17B9)) == 0) {
            return 1;
        }
    }
    return 0;
}

s32 _menuPokemonStatusCheckWazaItem(tagWINDOW_WORK*, tagSPRITE_WORK* spr) {
    s32 r = 1;
    switch (spr->id) {
    case 0x1E1:
    case 0x1E2:
    case 0x1E3:
    case 0x1E4:
    case 0x1E5:
    case 0x1E6:
    case 0x1E7:
    case 0x1E8:
    case 0x1E9:
    case 0x1EA:
    case 0x1EB:
    case 0x1EC:
    case 0x1ED:
    case 0x1EE:
    case 0x1EF:
    case 0x1F0:
    case 0x1F1:
    case 0x1F2:
    case 0x1F3:
    case 0x1F4:
    case 0x1F5:
    case 0x1F6:
    case 0x1F7:
    case 0x1F8:
    case 0x24C:
        switch (_menuStatus.mode) {
        case 3:
        case 4:
        case 7:
            if (_menuStatus.page >= 0 && _menuStatus.page <= 4) {
                r = 1;
            } else {
                r = 0;
            }
            break;
        default:
            r = 0;
            break;
        }
        winSpriteSetDisp(spr, r);
        break;
    case 0x83D:
    case 0x83E:
    case 0x83F:
    case 0x840:
    case 0x841:
    case 0x842:
        winSpriteSetDisp(spr, 0);
        break;
    case 0x837:
    case 0x83C:
    case 0x846:
    case 0x847:
    case 0x848:
        if (pokemonGetStatus(_menuStatus.pokemon, 0, 0xC2, 0) != 0) {
            r = 0;
        } else {
            r = 1;
        }
        winSpriteSetDisp(spr, r);
        break;
    }
    return r;
}

u8 _menuPokemonStatusCheckOya(Pokemon* pokemon) {
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

static s32 ribbon_id_tbl[32] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6
};
static u32 ex_ribbon_id[64] = {
11026, 11027, 11028, 11029, 11030, 11031, 11032, 11033, 11034, 11035, 11036, 11037, 11038, 11039, 11040, 11041, 11042, 11043, 11044, 11045, 11046, 11047, 11048, 11049, 11050, 11051, 11052, 11053, 11054, 11055, 11056, 11057, 11058, 11059, 11060, 11061, 11062, 11063, 11064, 11065, 11066, 11067, 11068, 11069, 11070, 11071, 11072, 11073, 11074, 11075, 11076, 11077, 11078, 11079, 11080, 11081, 11082, 11083, 11084, 11085, 11086, 11087, 11088, 11089
};

extern "C" void menuPokemonStatusDrawRibbon(tagWINDOW_WORK* win, tagSPRITE_WORK* spr) {
    u32 color;
    u32 msg;
    s32 id;
    s32 i = 0;
    if (windowSearchID(0x5E) == 0) {
        return;
    }
    if (_menuStatus.pokemon == 0) {
        return;
    }
    color = win->alpha | ~0xFF;
    switch (spr->id) {
    case 0x25B:
        msgctrlSetValue(0x34, _menuStatus.ribbon.count);
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x25A:
        if (_menuStatus.mode == 6) {
            s8 cursor = _menuStatus.unk1A;
            i = _menuStatus.ribbon.slots[(cursor % 9) * 4 + cursor / 9];
            if (i < 0 && getRibbonCnt() <= i) {
                break;
            }
            id = ribbon_id_tbl[i];
            switch (id) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6: {
                u32 no = exribbonGetNo(id);
                if (no != 0) {
                    s32 k = no - 1;
                    msg = ex_ribbon_id[k];
                } else {
                    msg = 0;
                }
                break;
            }
            case -1:
                msg = getRibbonMsgID(i);
                break;
            }
            if (msg != 0) {
                GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, msg);
            }
        }
        break;
    case 0x22A:
        i = 1;
    case 0x22B: i++;
    case 0x22C: i++;
    case 0x22D: i++;
    case 0x22E: i++;
    case 0x22F: i++;
    case 0x230: i++;
    case 0x231: i++;
    case 0x232: i++;
    case 0x233: i++;
    case 0x234: i++;
    case 0x235: i++;
    case 0x236: i++;
    case 0x237: i++;
    case 0x238: i++;
    case 0x239: i++;
    case 0x23A: i++;
    case 0x23B: i++;
    case 0x23C: i++;
    case 0x23D: i++;
    case 0x23E: i++;
    case 0x23F: i++;
    case 0x240: i++;
    case 0x241: i++;
    case 0x242: i++;
    case 0x243: i++;
    case 0x244: i++;
    case 0x245: i++;
    case 0x246: i++;
    case 0x247: i++;
    case 0x248: i++;
    case 0x249:
        {
        s32 n = 32 - (i + 1);
        if (n > 0x18) {
            n += 2;
        }
        if (_menuStatus.ribbon.slots[(n % 9) * 4 + n / 9] >= 0) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        }
        break;
    case 0x229: {
        s8 cursor = _menuStatus.unk1A;
        if (cursor >= 0) {
            i = cursor % 9;
            windowDrawSprite(i * 30, (cursor / 9) * 52, win, 0x366, 0, winSpriteGetLayerID(win, spr));
        }
        break;
    }
    case 0x21E:
    case 0x220:
        if (_menuStatus.mode == 6) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    }
}

struct RibbonMap {
    u16 id;
    u8 base;
    u8 max;
};

void _menuPokemonStatusMakeRibbon(Pokemon* pokemon, RIBBON_WORK* ribbon) {
    static RibbonMap ribbon_mapping_tbl[10] = {
        {0xA3, 0x00, 1}, {0xB0, 0x01, 4}, {0xB1, 0x05, 4}, {0xB2, 0x09, 4}, {0xB3, 0x0D, 4},
        {0xB4, 0x11, 4}, {0xA4, 0x15, 1}, {0xA5, 0x16, 1}, {0xA6, 0x17, 1}, {0xA7, 0x18, 1},
    };
    static RibbonMap exribbon_mapping_tbl[7] = {
        {0xA8, 0x19, 1}, {0xA9, 0x1A, 1}, {0xAA, 0x1B, 1}, {0xAB, 0x1C, 1},
        {0xAC, 0x1D, 1}, {0xAD, 0x1E, 1}, {0xAE, 0x1F, 1},
    };
    u32 i;
    s32 count;
    s32 pos;
    s32 n;
    s32 j;
    s32 r;
    for (r = 0; r < 4; r++) {
        for (j = 0; j < 9; j++) {
            ribbon->slots[j * 4 + r] = -1;
        }
    }
    pos = 0;
    for (i = 0; i < 10; i++) {
        n = pokemonGetStatus(pokemon, 0, ribbon_mapping_tbl[i].id, 0);
        if (n > ribbon_mapping_tbl[i].max) {
            n = ribbon_mapping_tbl[i].max;
        }
        if (n != 0) {
            for (j = 0; j < n; j++) {
                s8 v = j + ribbon_mapping_tbl[i].base;
                ribbon->slots[(pos % 9) * 4 + pos / 9] = v;
                pos++;
            }
        } else {
            pos += ribbon_mapping_tbl[i].max;
        }
    }
    pos = 0;
    for (i = 0; i < 7; i++) {
        n = pokemonGetStatus(pokemon, 0, exribbon_mapping_tbl[i].id, 0);
        if (n > exribbon_mapping_tbl[i].max) {
            n = exribbon_mapping_tbl[i].max;
        }
        if (n != 0) {
            for (j = 0; j < n; j++) {
                s8 v = j + exribbon_mapping_tbl[i].base;
                ribbon->slots[pos * 4 + 3] = v;
                pos++;
            }
        } else {
            pos += exribbon_mapping_tbl[i].max;
        }
    }
    count = 0;
    for (r = 0; r < 4; r++) {
        for (j = 0; j < 9; j++) {
            if (ribbon->slots[j * 4 + r] >= 0) {
                count++;
            }
        }
    }
    ribbon->count = count;
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

static inline void _drawWazaSprite(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, s32 id) {
    windowDrawSprite(0, 0, win, id, 0, winSpriteGetLayerID(win, spr));
}

extern "C" void menuPokemonStatusDrawWaza(tagWINDOW_WORK* win, tagSPRITE_WORK* spr) {
    s32 j;
    Pokemon* pokemon;
    s32 w = 0;
    u32 color;
    pokemon = _menuStatus.pokemon;
    if (pokemon == 0) {
        return;
    }
    if ((u8)_menuPokemonStatusCheckWazaItem(win, spr) == 0) {
        return;
    }
    color = win->alpha | 0xFFFFFF00;
    switch (spr->id) {
    case 0x205:
        winSpriteSetDisp(spr, 0);
        switch (_menuStatus.mode) {
        case 4:
            if (_menuStatus.wazaId != 0) {
                windowDrawSprite(0, (s16)(_menuStatus.prevPage * 0x2C), win, 0xF7, 0, winSpriteGetLayerID(win, spr));
                windowDrawSprite(0, (s16)(_menuStatus.page * 0x2C), win, 0xF2, 0, winSpriteGetLayerID(win, spr));
            } else {
                windowDrawSprite(0, (s16)((_menuStatus.prevPage + 1) * 0x2C), win, 0xF7, 0, winSpriteGetLayerID(win, spr));
                windowDrawSprite(0, (s16)((_menuStatus.page + 1) * 0x2C), win, 0xF2, 0, winSpriteGetLayerID(win, spr));
            }
            break;
        case 3:
        case 7:
            if (_menuStatus.wazaId != 0) {
                windowDrawSprite(0, (s16)(_menuStatus.page * 0x2C), win, 0xF2, 0, winSpriteGetLayerID(win, spr));
            } else {
                windowDrawSprite(0, (s16)((_menuStatus.page + 1) * 0x2C), win, 0xF2, 0, winSpriteGetLayerID(win, spr));
            }
            break;
        }
        break;
    case 0x200:
    case 0x201:
    case 0x202:
    case 0x203:
    case 0x204:
        if (_menuStatus.wazaId == 0) {
            switch (spr->id) {
            case 0x204:
                return;
            case 0x202:
                j = 1;
                break;
            case 0x201:
                j = 2;
                break;
            case 0x200:
                j = 3;
                break;
            case 0x203:
                j = 0;
                break;
            }
        } else {
            if (spr->id == 0x200) {
                windowDrawSprite(7, 0x14, win, 0xF8, 0, winSpriteGetLayerID(win, spr));
            }
            switch (spr->id) {
            case 0x202:
                j = 2;
                break;
            case 0x204:
                j = 0;
                break;
            case 0x203:
                j = 1;
                break;
            case 0x200:
                j = 4;
                break;
            case 0x201:
                j = 3;
                break;
            }
        }
        w = _menuPokemonStatusGetWazaDataID(pokemon, j);
        switch (NotDarkWaza((u16)w)) {
        case 0x176:
            w = 0x7B;
            break;
        case 0:
            w = 0;
            break;
        default:
            w = (u16)_menuPokemonStatusGetZokuseiSpriteID(wazaGetStatus(0, w, 3, 0));
            if (_menuStatus.wazaNew[(u16)j] != 0 && (u16)j != 0) {
                windowDrawSprite(7, 0x14, win, 0xF8, 0, winSpriteGetLayerID(win, spr));
                pokemon->getDarkPokemon()->setWazaNew(j - 1, true);
            }
            break;
        }
        if (w != 0) {
            windowDrawSprite(0, 0, win, (u16)w, 0, winSpriteGetLayerID(win, spr));
        }
        break;
    case 0x24F:
    case 0x250:
    case 0x251:
    case 0x252:
    case 0x253:
        if (_menuStatus.wazaId == 0) {
            switch (spr->id) {
            case 0x253:
                return;
            case 0x251:
                j = 1;
                break;
            case 0x250:
                j = 2;
                break;
            case 0x24F:
                j = 3;
                break;
            case 0x252:
                j = 0;
                break;
            }
        } else {
            switch (spr->id) {
            case 0x251:
                j = 2;
                break;
            case 0x253:
                j = 0;
                break;
            case 0x252:
                j = 1;
                break;
            case 0x24F:
                j = 4;
                break;
            case 0x250:
                j = 3;
                break;
            }
        }
        w = _menuPokemonStatusGetWazaDataID(pokemon, j);
        if ((u16)w == 0) {
            GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x3AF4);
        } else {
            u8* name = (u8*)wazaGetStatus(0, w, 1, 0);
            if (name != 0) {
                msgctrlSetValue(0x37, (s32)GSmsgGetGSchar((s32)name));
                GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4277);
            }
        }
        break;
    case 0x254:
    case 0x255:
    case 0x256:
    case 0x257:
    case 0x258: {
        s16 off;
        if (_menuStatus.wazaId == 0) {
            switch (spr->id) {
            case 0x258:
                return;
            case 0x256:
                j = 1;
                break;
            case 0x254:
                j = 3;
                break;
            case 0x255:
                j = 2;
                break;
            case 0x257:
                j = 0;
                break;
            }
        } else {
            switch (spr->id) {
            case 0x256:
                j = 2;
                break;
            case 0x254:
                j = 4;
                break;
            case 0x255:
                j = 3;
                break;
            case 0x258:
                j = 0;
                break;
            case 0x257:
                j = 1;
                break;
            }
        }
        w = _menuPokemonStatusGetWazaDataID(pokemon, j);
        off = (spr->x - (s16)(GSmsgGetRect(0x3AE8) >> 16)) / 2;
        GSmsgPrint2(winSpriteGetLayerID(win, spr), off, 0, color, 0x3AE8);
        switch (NotDarkWaza((u16)w)) {
        case 0x176:
            GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, off, spr->y, color, 0x3AD1);
            GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x3AD1);
            break;
        case 0:
            GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, off, spr->y, color, 0x3AF5);
            GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x3AF5);
            break;
        default:
            if ((u16)j == 4) {
                msgctrlSetValue(0x34, wazaGetStatus(0, w, 2, 0));
            } else {
                msgctrlSetValue(0x34, pokemonGetStatus(pokemon, 0, 0x80, j));
            }
            GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, off, spr->y, color, 0x427B);
            if ((u16)j == 4) {
                msgctrlSetValue(0x34, wazaGetStatus(0, w, 2, 0));
            } else {
                msgctrlSetValue(0x34, pokemonWazaGetMaxPP(pokemon, j));
            }
            GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x427B);
            break;
        }
        break;
    }
    case 0x24C:
        w = wazaGetStatus(0, _menuPokemonStatusGetWazaDataID(pokemon, _menuStatus.page), 0x22, 0);
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, w);
        break;
    case 0x24D:
        switch (_menuStatus.mode) {
        case 3:
        case 4:
        case 7: {
            u32 r = wazaGetStatus(0, _menuPokemonStatusGetWazaDataID(pokemon, _menuStatus.page), 6, 0);
            if (r <= 1) {
                GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x3AF6);
            } else {
                msgctrlSetValue(0x34, r);
                GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4270);
            }
            winSpriteSetDisp(spr, 1);
            break;
        }
        default:
            winSpriteSetDisp(spr, 0);
            break;
        }
        break;
    case 0x24E:
        switch (_menuStatus.mode) {
        case 3:
        case 4:
        case 7: {
            u32 r = wazaGetStatus(0, _menuPokemonStatusGetWazaDataID(pokemon, _menuStatus.page), 7, 0);
            if (r <= 1) {
                GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x3AF6);
            } else {
                msgctrlSetValue(0x34, r);
                GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4270);
            }
            winSpriteSetDisp(spr, 1);
            break;
        }
        default:
            winSpriteSetDisp(spr, 0);
            break;
        }
        break;
    case 0x1FD:
        if (_menuStatus.wazaId == 0) {
            winSpriteSetDisp(spr, 0);
        } else {
            winSpriteSetDisp(spr, 1);
        }
        break;
    case 0x388:
    case 0x389:
    case 0x38A:
    case 0x38B:
        if (_menuStatus.wazaId == 0) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    case 0x1E8:
        w++;
    case 0x1E9:
        w++;
    case 0x1EB:
        w++;
    case 0x1EA:
        w++;
    case 0x1ED:
        w++;
    case 0x1EC:
        w++;
    case 0x1EE:
        w++;
    case 0x1EF:
        w += 2;
    case 0x1F0:
        w++;
    case 0x1F1:
        w++;
    case 0x1F3:
        w++;
    case 0x1F2:
        w++;
    case 0x1F5:
        w++;
    case 0x1F6:
        w++;
    case 0x1F4:
        w++;
    case 0x1F7:
        w++;
    case 0x1F8:
        j = _menuPokemonStatusGetWazaDataID(pokemon, _menuStatus.page);
        switch (wazaDB_GetCompatible(j)) {
        case 1: {
            u16 st = wazaGetStatus(0, j, 3, 0);
            switch (zokuseiBiosGetWazaJoutai(st, w)) {
            case 0x3F:
                color = 0x35D;
                break;
            case 0x41:
                color = 0x35F;
                break;
            case 0x42:
                color = 0x360;
                break;
            case 0x43:
                color = 0x35E;
                break;
            }
            windowDrawSprite(0, 0, win, (u16)color, 0, winSpriteGetLayerID(win, spr));
            break;
        }
        case 4:
            _drawWazaSprite(win, spr, w == 7 ? 0x35E : 0x35D);
            break;
        case 5:
            _drawWazaSprite(win, spr, w == 12 ? 0x35E : 0x35D);
            break;
        case 6:
            if (w == 3 || w == 8) {
                _drawWazaSprite(win, spr, 0x35E);
            } else {
                _drawWazaSprite(win, spr, 0x35D);
            }
            break;
        case 7:
            _drawWazaSprite(win, spr, w == 4 ? 0x35E : 0x35D);
            break;
        case 8:
            _drawWazaSprite(win, spr, w == 2 ? 0x35E : 0x35D);
            break;
        case 9:
            _drawWazaSprite(win, spr, w == 0 ? 0x35E : 0x35D);
            break;
        case 10:
        case 11:
        case 14:
            _drawWazaSprite(win, spr, 0x376);
            break;
        case 12:
            _drawWazaSprite(win, spr, w == 0x11 ? 0x35E : 0x35D);
            break;
        case 13:
            _drawWazaSprite(win, spr, w == 10 ? 0x35E : 0x35D);
            break;
        case 15:
            _drawWazaSprite(win, spr, 0x35D);
            break;
        }
        break;
    }
}

extern "C" void menuPokemonStatusDrawStatus(tagWINDOW_WORK* win, tagSPRITE_WORK* spr) {
    Pokemon* pokemon;
    u32 color;
    s32 v;
    MenuPokemonStatus* st = &_menuStatus;
    pokemon = st->pokemon;
    if (pokemon == 0) {
        return;
    }
    v = (s32)pokemonDataBiosGetPtr(pokemonGetStatus(pokemon, 0, 0x6E, 0));
    if (v == 0) {
        return;
    }
    if ((u8)_menuPokemonStatusCheckWazaItem(win, spr) == 0) {
        return;
    }
    color = win->alpha | 0xFFFFFF00;
    switch (spr->id) {
    case 0x845:
        if (pokemonGetStatus(st->pokemon, 0, 0xC2, 0) != 0) {
            spr->message = 0x3C11;
        } else {
            spr->message = 0x3C10;
        }
        break;
    case 0x21D: {
        v = (u16)zokuseiGetPokemonSpriteID((void*)v, 0);
        if (v != 0) {
            windowDrawSprite(0, 0, win, v, 0, winSpriteGetLayerID(win, spr));
        }
        break;
    }
    case 0x21C: {
        u32 a = pokemonDataBiosGetZokuseiDataId((void*)v, 0);
        if (a != pokemonDataBiosGetZokuseiDataId((void*)v, 1)) {
            u16 sid = zokuseiGetPokemonSpriteID((void*)v, 1);
            windowDrawSprite(0, 0, win, sid, 0, winSpriteGetLayerID(win, spr));
        }
        break;
    }
    case 0x25C: {
        u32 place;
        u32 pl;
        u8 lv;
        if (pokemonGetDarkPokemonLevel(pokemon) < 3) {
            v = 0x945;
        } else {
            v = pokemonSeikakuDataBiosGetName(pokemonSeikakuDataBiosGetPtr((u8)pokemonGetStatus(pokemon, 0, 0xBF, 0)));
        }
        msgctrlSetValue(0x55, v);
        if (v == 0xC96 || v == 0xC86) {
            msgctrlSetValue(0x56, 1);
        } else {
            msgctrlSetValue(0x56, 0x3AEC);
        }
        lv = pokemonGetStatus(pokemon, 0, 0x72, 0);
        if (lv == 0) {
            lv = 5;
        }
        msgctrlSetValue(0x34, lv);
        if (_menuPokemonStatusCheckOya(pokemon) != 0) {
            u16 id = pokemonGetStatus(pokemon, 0, 0x6E, 0);
            if (id < 0xC4) {
                if (id >= 0x89) {
                    v = 0x3AE1;
                } else if (id >= 0x85) {
                    v = 0x3AF7;
                } else {
                    v = 0x3AE1;
                }
            } else if (id >= 0xC6) {
                v = 0x3AE1;
            } else {
                v = 0x3AF7;
            }
        } else {
            v = 0x3AE1;
        }
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, v);
        v = 0x3AFA;
        pl = pokemonGetStatus(pokemon, 0, 0x71, 0);
        place = floorGetPlaceName(pl);
        if (_menuPokemonStatusCheckOya(pokemon) != 0) {
            u16 id = pokemonGetStatus(pokemon, 0, 0x6E, 0);
            if (id < 0xC4) {
                if (id >= 0x89) {
                    goto placeName;
                } else if (id >= 0x85) {
                    goto fightKind;
                } else {
                    goto placeName;
                }
            } else if (id >= 0xC6) {
                goto placeName;
            } else {
            fightKind:
                if (fightKind_CheckFightKind(0xE) == 0) {
                    v = 0x3AF8;
                }
                goto printPlace;
            }
        placeName:
            if (place != 0) {
                msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(place));
                v = 0x3AEB;
            }
        } else {
            switch (gamedataGetStatus(pokemonGetStatus(pokemon, 0, 0x70, 0), 2)) {
            case 0xB:
                if (_menuPokemonStatusCheckGinzaru(pokemon) != 0) {
                    if (place != 0) {
                        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(place));
                        v = 0x3AEB;
                    }
                } else if (_menuPokemonStatusCheckDanny(pokemon) != 0) {
                    if (place != 0) {
                        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(place));
                        v = 0x3AEB;
                    }
                } else if (pl == 0xFF) {
                    v = 0x3AF9;
                }
                break;
            case 8:
            case 9:
            case 10:
                if (pl == 0xFF) {
                    v = 0x3AF9;
                }
                break;
            }
        }
    printPlace:
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0x20, spr->x, spr->y, color, v);
        break;
    }
    case 0x849:
        if (pokemonIsDarkPokemon(pokemon) == 1) {
            switch (pokemonGetDarkPokemonLevel(pokemon)) {
            case 0:
                spr->message = 0x3AED;
                break;
            case 1:
                spr->message = 0x3AEE;
                break;
            case 2:
                spr->message = 0x3AEF;
                break;
            case 3:
                spr->message = 0x3AF0;
                break;
            case 4:
                spr->message = 0x3AF1;
                break;
            case 5:
                spr->message = 0x3AF2;
                break;
            case 6:
                spr->message = 0x3AF3;
                break;
            }
        } else {
            spr->message = 0x3ADF;
        }
        break;
    case 0x846: {
        u32 need = pokemonGetLevelToExp(pokemon, (u8)(((u8)pokemonGetStatus(pokemon, 0, 0x7A, 0)) + 1));
        u32 v;
        if (need == 0) {
            v = 0;
        } else {
            v = need - pokemonGetStatus(pokemon, 0, 0x79, 0);
        }
        msgctrlSetValue(0x34, v);
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    }
    case 0x848:
        msgctrlSetValue(0x34, pokemonGetStatus(pokemon, 0, 0x79, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x84A:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 0x8C, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x84C:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 0x8B, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x84E:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 0x8A, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x850:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 0x89, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x852:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 0x88, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x854:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 0x83, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, 0x37, spr->y, color, 0x4287);
        GSmsgPrint2(winSpriteGetLayerID(win, spr), 0x37, 0, color, 0x3AE8);
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 0x87, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x843:
        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar((s32)pokemonTokuseiDataBiosGetDoc(pokemonTokuseiDataBiosGetPtr(pokemonGetTokuseiDataId(pokemon)))));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4276);
        break;
    case 0x844:
        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar((s32)pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(pokemonGetTokuseiDataId(pokemon)))));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4276);
        break;
    case 0x25F: {
        s16 w = GSmsgGetRect(spr->message) >> 16;
        if (pokemonIsDarkPokemon(pokemon) == 1) {
            GSmsgPrint2(winSpriteGetLayerID(win, spr), w, 0, color, 0x3AD4);
        } else {
            u32 v = (u16)pokemonGetStatus(pokemon, 0, 0x75, 0);
            u32 div = 10000;
            s32 x = w;
            s32 i;
            for (i = 0; i < 5; i++) {
                u32 digit = v / div;
                v -= digit * div;
                div /= 10;
                msgctrlSetValue(0x34, digit);
                GSmsgPrint2(winSpriteGetLayerID(win, spr), x, 0, color, 0x426F);
                x += 13;
            }
        }
        break;
    }
    case 0x261: {
        s16 w;
        if (pokemonIsDarkPokemon(pokemon) == 1) {
            msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(0x3AD4));
        } else {
            msgctrlSetValue(0x37, pokemonGetStatus(pokemon, 0, 0x76, 0));
        }
        w = GSmsgGetRect(spr->message) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(win, spr), w, 0, color, 0x4276);
        break;
    }
    case 0x83B: {
        s16 a = pokemonGetStatus(pokemon, 0, 0x83, 0);
        s16 b = pokemonGetStatus(pokemon, 0, 0x87, 0);
        f32 ratio = (f32)a / (f32)b;
        s32 sid;
        if (ratio < 0.2) {
            sid = 0xF5;
        } else if (ratio < 0.5) {
            sid = 0xF4;
        } else {
            sid = 0xF3;
        }
        windowDrawSprite2(0, 0, (s32)((f32)spr->x * ratio), spr->y, color, win, sid, 0, winSpriteGetLayerID(win, spr));
        break;
    }
    case 0x83C: {
        u8 lv = pokemonGetStatus(pokemon, 0, 0x7A, 0);
        u32 next = pokemonGetLevelToExp(pokemon, (u8)(lv + 1));
        if (next != 0) {
            u32 cur = pokemonGetLevelToExp(pokemon, lv);
            u32 span = next - cur;
            s16 w = (span + (pokemonGetStatus(pokemon, 0, 0x79, 0) - cur) * spr->x - 1) / span;
            windowDrawSprite2(0, 0, w, spr->y, color, win, 0xF6, 0, winSpriteGetLayerID(win, spr));
        }
        break;
    }
    case 0x83E: {
        MenuItemRect* rect = menuItemBiosGetPtr(0x60, 0x83E);
        menuDrawReliveMeter(pokemon, rect->width, rect->height, winSpriteGetLayerID(win, spr));
        break;
    }
    }
}

extern "C" void menuPokemonStatusDrawTitle(tagWINDOW_WORK* win, tagSPRITE_WORK* spr) {
    u32 color;
    Pokemon* pokemon = _menuStatus.pokemon;
    u32 name;
    if (pokemon == 0) {
        return;
    }
    if (pokemonDataBiosGetPtr(pokemonGetStatus(pokemon, 0, 0x6E, 0)) == 0) {
        return;
    }
    color = win->alpha | 0xFFFFFF00;
    switch (spr->id) {
    case 0x810:
        break;
    case 0x80F:
        if (win->pos.selected == 0) {
            spr->color = -1;
        } else {
            spr->color = 0x808080FF;
        }
        break;
    case 0x80E:
        if (win->pos.selected == 1) {
            spr->color = -1;
        } else {
            spr->color = 0x808080FF;
        }
        break;
    case 0x80D:
        if (win->pos.selected == 2) {
            spr->color = -1;
        } else {
            spr->color = 0x808080FF;
        }
        break;
    case 0x80C:
        if (win->pos.selected == 3) {
            spr->color = -1;
        } else {
            spr->color = 0x808080FF;
        }
        break;
    case 0x81C:
        winSpriteSetDisp(spr, 1);
        switch (win->pos.selected) {
        case 2:
            switch (_menuStatus.mode) {
            case 3:
            case 4:
                if (_menuStatus.flags & 2) {
                    spr->message = 0x3AE4;
                } else {
                    spr->message = 0x3AE3;
                }
                break;
            case 7:
                spr->message = 0x3C3B;
                break;
            case 9:
                break;
            default:
                spr->message = 0x3AE3;
                break;
            }
            if (_menuStatus.mode == 3) {
                if (pokemonIsDarkPokemon(pokemon) != 0 || (_menuStatus.flags & 2) == 0) {
                    winSpriteSetDisp(spr, 0);
                }
            }
            break;
        case 3:
            if (_menuStatus.ribbon.count != 0) {
                if (_menuStatus.mode == 6) {
                    winSpriteSetDisp(spr, 0);
                } else {
                    spr->message = 0x3AE6;
                }
            } else {
                winSpriteSetDisp(spr, 0);
            }
            break;
        default:
            winSpriteSetDisp(spr, 0);
            break;
        }
        break;
    case 0x811:
    case 0x812:
    case 0x815:
        winSpriteSetDisp(spr, 0);
        switch (win->pos.selected) {
        case 2:
            winSpriteSetDisp(spr, 1);
            if (_menuStatus.mode == 3) {
                if (pokemonIsDarkPokemon(pokemon) != 0 || (_menuStatus.flags & 2) == 0) {
                    winSpriteSetDisp(spr, 0);
                }
            }
            break;
        case 3:
            if (_menuStatus.ribbon.count != 0) {
                if (_menuStatus.mode != 6) {
                    winSpriteSetDisp(spr, 1);
                }
            }
            break;
        }
        break;
    case 0x81F: {
        MenuItemRect* rect = menuItemBiosGetPtr(0x5E, 0x81F);
        f32 angle[3];
        menuModelSetSize(_menuModel, rect->x, rect->y, rect->width, rect->height);
        if (menuModelComparePokemon(_menuModel, pokemon) == 1) {
            if (menuModelCheck(_menuModel, 0) == 0) {
                menuModelAdjustCamera(_menuModel);
            }
            angle[0] = -0.1f;
            angle[1] = 0.3f;
            angle[2] = 0.0f;
            menuModelSetAngle(_menuModel, angle);
            menuModelRender(_menuModel);
        }
        break;
    }
    case 0x817:
    case 0x818:
    case 0x819:
    case 0x81A: {
        u32 mask = 0;
        u8 status = pokemonGetStatus(pokemon, 0, 0xBB, 0);
        switch (spr->id) {
        case 0x817:
            mask = 8;
            break;
        case 0x818:
            mask = 4;
            break;
        case 0x819:
            mask = 2;
            break;
        case 0x81A:
            mask = 1;
            break;
        }
        winSpriteSetDisp(spr, (status & (u8)mask) != 0);
        break;
    }
    case 0x816: {
        u8 ball = pokemonBiosGetCatchBallId(pokemon);
        if (ball != 0) {
            MenuItemRect* rect = menuItemBiosGetPtr(0x5E, 0x816);
            s32 layer = winSpriteGetLayerID(win, spr);
            windowDrawSprite2(0, 0, rect->width, rect->height, -1, win, mballBiosGetSpriteID(ball), 0, layer);
        }
        break;
    }
    case 0x804: {
        u8 v = pokemonGetStatus(pokemon, 0, 0xB5, 0);
        s32 sid;
        if ((v & 0xF) != 0) {
            sid = 0x84;
        } else if (v != 0) {
            sid = 0x1F8;
        } else {
            sid = 0;
        }
        windowDrawSprite(0, 0, win, sid, 0, winSpriteGetLayerID(win, spr));
        break;
    }
    case 0x805: {
        s32 sid = menuPokemonGetJoutaiSpriteID(pokemon, 1);
        windowDrawSprite(0, 0, win, sid, 0, winSpriteGetLayerID(win, spr));
        break;
    }
    case 0x25D: {
        u16 item = pokemonGetSoubiItemDataId(pokemon);
        if (item != 0) {
            msgctrlSetValue(0x2D, item);
            GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x3AE7);
        } else {
            msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(0x3C1A));
            GSmsgPrint2(winSpriteGetLayerID(win, spr), 0, 0, color, 0x4277);
        }
        break;
    }
    case 0x81D: {
        s16 w = GSmsgGetRect(spr->message) >> 16;
        msgctrlSetValue(0x5F, (u8)pokemonGetStatus(pokemon, 0, 0x7A, 0));
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), w + 3, 0, spr->x, spr->y, color, 0x4351);
        break;
    }
    case 0x264:
    case 0x81E: {
        u32 sexMsg;
        if (spr->id == 0x264) {
            name = (u32)GSmsgGetGSchar(pokemonGetStatus(0, (u16)pokemonGetStatus(pokemon, 0, 0x6E, 0), 1, 0));
        } else {
            name = pokemonGetStatus(pokemon, 0, 0x77, 0);
            if (pokemonCheckRare(pokemon) != 0) {
                color = win->alpha | 0xFFDC0000;
            }
        }
        msgctrlSetValue(0x37, name);
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4277);
        GSmsgGetRect(0x4277);
        switch (menuSubGetPokemonSexForDisp(pokemon)) {
        case 0:
            sexMsg = 0x9C5;
            break;
        case 1:
            sexMsg = 0x9C6;
            break;
        case 3:
        default:
            sexMsg = 0;
            break;
        }
        if (sexMsg != 0) {
            msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(sexMsg));
            GSmsgPrint2(winSpriteGetLayerID(win, spr), 0x78, 0, color, 0x4276);
        }
        break;
    }
    }
}

extern "C" s32 menuPokemonStatusCursor(tagWINDOW_WORK* win) {
    s32 dir = 0;
    s8 maxPage;
    u16 key;
    if (_menuStatus.wazaId != 0) {
        maxPage = 5;
    } else {
        maxPage = 4;
    }
    key = windowGetKeyRepeat();
    switch (_menuStatus.mode) {
    case 0:
    case 9:
        break;
    case 1:
    case 2:
    case 5:
    case 8: {
        s8 page = win->pos.selected;
        if (key & 8) {
            page++;
        } else if (key & 4) {
            page--;
        }
        if (page > 3) {
            page = 3;
        }
        if (page < 0) {
            page = 0;
        }
        win->pos.selected = page;
        switch (page) {
        case 0:
            _menuStatus.mode = 8;
            break;
        case 1:
            _menuStatus.mode = 1;
            break;
        case 2:
            _menuStatus.mode = 2;
            break;
        case 3:
            _menuStatus.mode = 5;
            break;
        }
        if (key & 1) {
            dir = 1;
        } else if (key & 2) {
            dir = 2;
        }
        if (dir != 0) {
            if (_menuStatus.callback != 0) {
                Pokemon* p = _menuStatus.callback(_menuStatus.pokemon, (MENU_POKEMON_CB_TYPE)dir, _menuStatus.callbackArg);
                if (_menuStatus.pokemon != p) {
                    s32 i;
                    if (p != 0) {
                        menuPlaySe(win->menu, 1);
                        if (menuModelComparePokemon(_menuModel, p) == 0) {
                            menuModelLoadPokemon(_menuModel, p);
                        }
                    }
                    _menuStatus.pokemon = p;
                    for (i = 0; i < 4; i++) {
                        _menuStatus.wazaNew[i] = 0;
                        if (p->isDarkPokemon()) {
                            DarkPokemon* dark = p->getDarkPokemon();
                            if (dark != 0) {
                                s32 id = (u16)pokemonGetStatus(p, 0, 0x7F, (u8)i);
                                if (id < 0x164) {
                                    if (id == 0) {
                                        continue;
                                    }
                                } else if (id < 0x177) {
                                    continue;
                                }
                                if (!dark->isWazaNew(i - 1)) {
                                    _menuStatus.wazaNew[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    case 3:
    case 4:
    case 7: {
        s8 page = _menuStatus.page;
        if (key & 1) {
            page--;
        } else if (key & 2) {
            page++;
        }
        if (page >= maxPage) {
            page = maxPage - 1;
        }
        if (page < 0) {
            page = 0;
        }
        if (_menuPokemonStatusGetWazaDataID(_menuStatus.pokemon, page) != 0) {
            if (page != _menuStatus.page) {
                menuPlaySe(win->menu, 1);
                _menuStatus.page = page;
            }
        }
        break;
    }
    case 6: {
        s8 old = _menuStatus.unk1A;
        s32 col = old % 9;
        s32 row = old / 9;
        s32 r;
        s32 c;
        s8 idx;
        if (key & 1) {
            r = row;
            while (r-- > 0) {
                c = col;
                do {
                    if (_menuStatus.ribbon.slots[c * 4 + r] >= 0) {
                        row = r;
                        col = c;
                        r = -1;
                        break;
                    }
                } while (c-- > 0);
            }
        } else if (key & 2) {
            r = row;
            while (++r < 4) {
                c = col;
                do {
                    if (_menuStatus.ribbon.slots[c * 4 + r] >= 0) {
                        row = r;
                        col = c;
                        r = 5;
                        break;
                    }
                } while (c-- > 0);
            }
        } else if (key & 8) {
            s32 found = 0;
            for (r = row; r < 4; r++) {
                c = (r == row) ? col + 1 : 0;
                for (; c < 9; c++) {
                    if (_menuStatus.ribbon.slots[c * 4 + r] >= 0) {
                        col = c;
                        row = r;
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        } else if (key & 4) {
            s32 found = 0;
            for (r = row; r >= 0; r--) {
                c = (r == row) ? col - 1 : 8;
                for (; c >= 0; c--) {
                    if (_menuStatus.ribbon.slots[c * 4 + r] >= 0) {
                        col = c;
                        row = r;
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
        idx = row * 9 + col;
        if (idx != old) {
            menuPlaySe(win->menu, 1);
            _menuStatus.unk1A = idx;
        }
        break;
    }
    }
    return 0;
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
