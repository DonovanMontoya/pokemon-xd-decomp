#include <game/menuPokemonChangeLayout.hpp>

extern "C" {
void floorMapSetDisp(s32);
void scriptModelStopMotion(u32);
void GSthreadSwitch(void);
u8 winSeqCheckMove(s32);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
void menuSetDisp(s32, bool);
tagWINDOW_WORK *windowSearchID(s32);
tagSPRITE_WORK *windowSearchItemID(tagWINDOW_WORK *, u16);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
s32 floorGetCurrentGroupID(void);
void *scriptModelOpen(u32);
void *GSresGetResource(s32, void *);
void cameraPlayAnime(s32, u32, s32, f32);
void cameraSetType(s32);
void GSmodelSetVisibility(void *, s32);
void fadeSet(s32, f32);
void GSfsysReadWait(s32);
void *memcardMemAllocForSavedata(void);
void menuGBACSetRomVer(s32, s32);
u8 menuFaceCheckLoading(void);
void GSfsysFree(s32);
void GSresFreeGroup(s32);
u8 GSfloorIsFloorPushed(void);
void GSfloorPop(void);
s32 floorGetPrevFloorID(void);
void floorLink(s32, s32);
u8 pokemonBiosGetFuseiFlag(Pokemon *);
u8 pokemonCheckValid(Pokemon *);
u8 pokemonBiosGetTamagoFlag(Pokemon *);
u8 menuCBRule_CheckPokemonEventFlag(Pokemon *);
u8 menuCBRule_CheckPokemonError(Pokemon *, s32);
void *itemDataBiosGetPtr(u16);
u8 itemDataBiosCheckExportable(void *);
u8 itemDataBiosCheckImportable(void *);
void msgctrlSetValue(s32, u32);
u32 pokemonBiosGetNicknamePtr(Pokemon *);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
void winMsgOpenWithSE(s32, s32, s32, s32, s32);
void winMsgClose(s32);
void windowCheckCursor(s32, s32);
s32 windowGetValue(s32);
s32 menuGetLastError(void);
void menuClose(s32);
u8 heroGetStatus(Hero *, s32, s32);
void memoDataSet(s32, Pokemon *);
void pokemonBiosSetFriend(Pokemon *, s32);
void pokemonBiosCopy(Pokemon *, Pokemon *);
void pokemonInit(Pokemon *);
void scriptModelSetMotion(u32, s32, s32, s32);
void cameraWaitSyncAnime(s32);
void winSeqSetMenu(s32, s32);
void menuCloseCustom(s32, s32, s32);
void scriptModelClose(void *);
void fadeSetToBlackOutIfNotBlack(f32);
void fadeSetToBlackInIfBlack(f32);
f32 timeGetLastFrameSec(void);
u8 gbaCommandIsConnected(s32);
void menuSetEnablePort(s32);
void GSsndPlayNow(u32);
void winMsgOpen(s32, s32, s32, s32);
void fadeCheck(s32);
void *memset(void *, int, u32);
}

struct MenuItemSimple {
    u8 pad[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};
MenuItemSimple *menuPtItemGetByMenuIdAndItemId(long, u32, long);
struct MENU_MODEL;
extern "C" {
void menuModelInit(MENU_MODEL *, long, long);
void menuModelLoadPokemon(MENU_MODEL *, Pokemon *);
void menuModelCheck(MENU_MODEL *, s32);
void menuModelFree(MENU_MODEL *);
void menuModelTerm(MENU_MODEL *);
}

namespace {

enum enumPlayerIndex { PLAYER_0, PLAYER_1 };
enum enumMenuState { MENU_STATE_0, MENU_STATE_1, MENU_STATE_2, MENU_STATE_3 };

void _menuSetMsg(long, u16, u32);
long _getPokemonState(Pokemon *, enumPlayerIndex);
bool _isPokemonBattleAble(Pokemon *, enumPlayerIndex);

bool _isPokemonValid(Pokemon *, enumPlayerIndex);
bool _isPokemonExchangeAble(Pokemon *, enumPlayerIndex);
void _setInfo(u32);
long _actionSelect2or3(u32, u32, u32);
void _menuWait(f32);
void _pokemonChangeFadeOut(f32);
void _pokemonChangeFadeIn(f32);

class CMenuPokemonChange {
public:
    u8 pad0[0x24];
    Hero *hero0;
    Hero hero1;
    u8 pad29[0x9A0 - 0x29];
    s32 currentPlayer;
    CState cstate;
    s32 menuId;
    void *saveData;
    u8 padA54[4];
    s32 bgModelId;
    void *bgModel;
    s32 selectIndex[2];
    u8 padA68[4];
    MENU_MODEL models[2];
    u8 padC44[0xC50 - 0xC44];
    u8 flagC50;
    u8 flagC51;
    u8 padC52[6];

    void ctrlHook(tagWINDOW_WORK *);
    void selectItemHook(tagWINDOW_WORK *, tagSPRITE_WORK *);
    void selectItemHookPrime(tagWINDOW_WORK *, tagSPRITE_WORK *, u32);
    void selectDrawHook(tagWINDOW_WORK *);
    void bgDrawFadeIn();
    void bgDrawFadeIn(f32);
    void stateFunctionExChangeOK();
    void stateFunctionExChangeMain();
    void stateFunctionExChangeStart();
    bool bgDrawFadeIsLive();
    void bgModelRelease();
    void pokemonStatusCallback(Pokemon *, MENU_POKEMON_CB_TYPE, enumPlayerIndex);
    void main();
    bool gbaConnectionCheckIsError();
    void stateFunctionSelectPokemon2PokeExChange();
    void stateFunctionSelectPokemon1PokeExChange();
    void stateFunctionSelectPokemon1CheckStatus();
    void stateFunctionSelectPokemonStart();
    void stateFunctionSelectPokemon2Reset();
    long getQuantityAllPokemon();
    long getQuantityHeroPokemon(enumPlayerIndex);
    void waitMenuOpen();
    void stateFunctionError(Pokemon *, u32);
    void stateFunctionCheckNext();
    void stateFunctionSelectPokemon2DecideAfterWait();
    void stateFunctionSelectPokemon2CheckStatus();
    void stateFunctionSelectPokemon2Selected();
    void stateFunctionSelectPokemon2Main();
    void stateFunctionSelectPokemon1Chanceld();
    void stateFunctionSelectPokemon1Selected();
    void stateFunctionSelectPokemon1Main();
    bool pokmonSelectCheck(enumPlayerIndex);
    bool isPokemonLookAbleStatus(long);
    inline Pokemon *getPokemonBySelect(long selected) {
        int side = 0;
        long index = selected;
        if (index >= getQuantityHeroPokemon(PLAYER_0)) {
            index -= getQuantityHeroPokemon(PLAYER_0);
            side = 1;
        }
        Hero *hero;
        if (side == 0) {
            hero = hero0;
        } else {
            hero = &hero1;
        }
        return hero->getPokemon(index);
    }
    void loop();
    void init();
    void bgModelLoad();
    void bgDrawFadeOut();
    void oneMenuLoad(long);
    void selectPokemonMenuOpen();
    bool pokemonExchangeCheck(enumPlayerIndex);
    void menuStateChange(enumMenuState);
    void menuPokemonStatusExecute(enumPlayerIndex);
};

CMenuPokemonChange MenuPokemonChange;

void CMenuPokemonChange::selectItemHook(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    selectItemHookPrime(win, sprite, sprite->id);
}

bool CMenuPokemonChange::gbaConnectionCheckIsError() {
    if (!gbaCommandIsConnected(2)) {
        menuSetEnablePort(1);
        GSsndPlayNow(0x13);
        winMsgOpen(2, 0xC4A3, 1, 0);
        cstate.unk4 = 2;
        memset(cstate.saved, 0, 0x40);
        return true;
    }
    return false;
}

void CMenuPokemonChange::stateFunctionSelectPokemon2PokeExChange() {
    if (pokemonExchangeCheck(PLAYER_1)) {
        cstate.unk4 = 0x10;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1PokeExChange() {
    if (pokemonExchangeCheck(PLAYER_0)) {
        cstate.unk4 = 0xC;
        memset(cstate.saved, 0, 0x40);
        stateFunctionSelectPokemon2Reset();
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1CheckStatus() {
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    menuPokemonStatusExecute(PLAYER_0);
    flagC51 = 1;
    menuStateChange(MENU_STATE_3);
    waitMenuOpen();
    _pokemonChangeFadeIn(0.3f);
    fadeCheck(1);
    cstate.unk4 = 8;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionSelectPokemonStart() {
    selectIndex[0] = 0;
    selectIndex[1] = getQuantityHeroPokemon(PLAYER_0);
    cstate.unk4 = cstate.unk0 + 1;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionSelectPokemon2Reset() {
    selectIndex[1] = getQuantityHeroPokemon(PLAYER_0);
}

long CMenuPokemonChange::getQuantityAllPokemon() {
    long a = getQuantityHeroPokemon(PLAYER_1);
    long b = getQuantityHeroPokemon(PLAYER_0);
    return b + a;
}

long CMenuPokemonChange::getQuantityHeroPokemon(enumPlayerIndex player) {
    Hero *hero;
    long i;
    if (player == PLAYER_0) {
        hero = hero0;
    } else {
        hero = &hero1;
    }
    i = 0;
    do {
        if (!_isPokemonValid(hero->getPokemon(i), player)) {
            break;
        }
        i++;
    } while (i < 6);
    return i;
}

void CMenuPokemonChange::waitMenuOpen() {
    while (winSeqCheckMove(menuId)) {
        GSthreadSwitch();
    }
}

void CMenuPokemonChange::oneMenuLoad(long id) {
    menuId = id;
    if (id == 0xD6) {
        selectPokemonMenuOpen();
    } else {
        menuOpenCustom(id, windowGetActiveID(), 0, 4, 0, 0);
        menuSetDisp(id, id == 0xD3);
    }
}

void _pokemonChangeFadeIn(f32 t) {
    fadeSetToBlackInIfBlack(t);
}

void _pokemonChangeFadeOut(f32 t) {
    fadeSetToBlackOutIfNotBlack(t);
    fadeCheck(1);
}

void _menuWait(f32 t) {
    f32 elapsed = 0.0f;
    while (elapsed < t) {
        GSthreadSwitch();
        elapsed += timeGetLastFrameSec();
    }
}

void _setInfo(u32 msg) {
    _menuSetMsg(0xD5, 0x61E, msg);
}

s16 _selectDisplay_2p_offset() {
    MenuItemSimple *a = menuPtItemGetByMenuIdAndItemId(0xD4, 0x60D, 0);
    MenuItemSimple *b = menuPtItemGetByMenuIdAndItemId(0xD4, 0x60E, 0);
    return b->x - a->x;
}

bool _isPokemonExchangeAble(Pokemon *p, enumPlayerIndex player) {
    return _getPokemonState(p, player) == 7;
}

bool _isPokemonValid(Pokemon *p, enumPlayerIndex player) {
    return _getPokemonState(p, player) != 0;
}

bool _pokemonChangeGetHinsi(Pokemon *p) {
    return p->getHp() == 0;
}

long _getQuantityBattleAbleWoIt(Hero *hero, long skip, enumPlayerIndex player) {
    long n = 0;
    long i;
    for (i = 0; i < 6; i++) {
        if (i != skip && _isPokemonBattleAble(hero->getPokemon(i), player)) {
            n++;
        }
    }
    return n;
}

bool _isPokemonItemExchangeOk(Pokemon *p, enumPlayerIndex player) {
    u16 item = p->getItemDataId();
    if (item == 0) {
        return true;
    }
    if (player == PLAYER_0) {
        if (!itemDataBiosCheckExportable(itemDataBiosGetPtr(item))) {
            return false;
        }
    } else {
        if (!itemDataBiosCheckImportable(itemDataBiosGetPtr(item))) {
            return false;
        }
    }
    return true;
}

long _getPokemonState(Pokemon *p, enumPlayerIndex player) {
    if (p == 0) {
        return 0;
    }
    if (pokemonBiosGetFuseiFlag(p)) {
        return 1;
    }
    if (!pokemonCheckValid(p)) {
        return 0;
    }
    if (pokemonBiosGetTamagoFlag(p)) {
        return 2;
    }
    if (p->isDarkPokemon()) {
        return 3;
    }
    if (!menuCBRule_CheckPokemonEventFlag(p)) {
        return 5;
    }
    if (!menuCBRule_CheckPokemonError(p, 0)) {
        return 6;
    }
    if (_isPokemonItemExchangeOk(p, player)) {
        return 7;
    }
    return 4;
}

bool _isPokemonBattleAble(Pokemon *p, enumPlayerIndex player) {
    long state = _getPokemonState(p, player);
    switch (state) {
    case 0:
    case 1:
    case 2:
        return false;
    }
    return !_pokemonChangeGetHinsi(p);
}

void _menuSetMsg(long menu, u16 item, u32 msg) {
    tagWINDOW_WORK *win = windowSearchID(menu);
    tagSPRITE_WORK *sprite = windowSearchItemID(win, item);
    if (msg != 0) {
        if (win != 0 && sprite != 0) {
            winSpriteSetDisp(sprite, 1);
            sprite->message = msg;
        }
    } else if (win != 0 && sprite != 0) {
        sprite->message = 0;
        winSpriteSetDisp(sprite, 0);
    }
}

void CMenuPokemonChange::bgModelLoad() {
    s32 group = floorGetCurrentGroupID();
    bgModelId = (s32)scriptModelOpen(0x5681000);
    bgModel = GSresGetResource(group, (void *)bgModelId);
    cameraPlayAnime(0x37C, 0x5691800, 1, 0.0f);
    cameraSetType(4);
    GSmodelSetVisibility(bgModel, 0);
}

void CMenuPokemonChange::init() {
    memset(this, 0, 0xC58);
    hero0 = Hero::getHeroPtr();
    cstate.init();
    fadeSet(3, 0.0f);
    GSfsysReadWait(0x88C);
    menuStateChange(MENU_STATE_2);
    bgModelLoad();
    _pokemonChangeFadeIn(0.3f);
}

void CMenuPokemonChange::main() {
    init();
    saveData = memcardMemAllocForSavedata();
    cstate.unk4 = 1;
    memset(cstate.saved, 0, 0x40);
    loop();
    menuGBACSetRomVer(0, 0xFFFF);
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    while (menuFaceCheckLoading()) {
        GSthreadSwitch();
    }
    bgModelRelease();
    GSfsysFree(0x88C);
    GSresFreeGroup(0x88C);
    if (GSfloorIsFloorPushed()) {
        GSfloorPop();
    } else {
        floorLink(floorGetPrevFloorID(), 0);
    }
}

bool CMenuPokemonChange::isPokemonLookAbleStatus(long index) {
    Pokemon *p = getPokemonBySelect(index);
    long state;
    state = _getPokemonState(p, index >= getQuantityHeroPokemon(PLAYER_0) ? PLAYER_1 : PLAYER_0);
    switch (state) {
    case 1:
    case 2:
        return false;
    }
    return true;
}

bool CMenuPokemonChange::pokmonSelectCheck(enumPlayerIndex player) {
    Pokemon *p = getPokemonBySelect(selectIndex[player]);
    long state;
    if (isPokemonLookAbleStatus(selectIndex[player])) {
        return true;
    }
    state = _getPokemonState(p, player);
    switch (state) {
    case 2:
        stateFunctionError(p, 0xC492);
        break;
    case 1:
        stateFunctionError(p, 0xC493);
        break;
    }
    return false;
}

bool CMenuPokemonChange::pokemonExchangeCheck(enumPlayerIndex player) {
    long index = selectIndex[player];
    Pokemon *p = getPokemonBySelect(index);
    long state = _getPokemonState(p, player);
    Hero *hero;
    switch (state) {
    case 4:
        stateFunctionError(p, 0xC496);
        return false;
    case 3:
        stateFunctionError(p, 0xC497);
        return false;
    case 5:
    case 6:
        stateFunctionError(p, 0xC4AB);
        return false;
    }
    if (player == PLAYER_0) {
        hero = hero0;
    } else {
        hero = &hero1;
    }
    index = selectIndex[player];
    if (index >= getQuantityHeroPokemon(PLAYER_0)) {
        index -= getQuantityHeroPokemon(PLAYER_0);
    }
    if (_getQuantityBattleAbleWoIt(hero, index, player) == 0) {
        stateFunctionError(p, 0xC498);
        return false;
    }
    return true;
}

void CMenuPokemonChange::stateFunctionError(Pokemon *p, u32 msg) {
    u32 nickname = pokemonBiosGetNicknamePtr(p);
    msgctrlSetValue(0x32, nickname);
    _setInfo(msg);
    GSsndPlayNow(0x13);
    _menuWait(1.5f);
    _setInfo(0);
    if (cstate.unk0 >= 0xC) {
        cstate.unk4 = 0xC;
        memset(cstate.saved, 0, 0x40);
    } else {
        cstate.unk4 = 7;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionCheckNext() {
    long i;
    s8 answer;
    winMsgOpen(2, 0xC4A1, 0, 0);
    answer = menuSubOpenYesNo(0, -1, -1, 0);
    winMsgClose(1);
    _menuWait(0.5f);
    bgDrawFadeOut();
    for (i = 0; i < 2; i++) {
        menuModelFree(&models[i]);
        menuModelTerm(&models[i]);
    }
    if (answer == 0) {
        cstate.unk4 = 6;
        memset(cstate.saved, 0, 0x40);
    } else {
        cstate.unk4 = 2;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon2DecideAfterWait() {
    MenuItemSimple *item;
    long i;
    _menuWait(0.6f);
    item = menuPtItemGetByMenuIdAndItemId(0xDD, 0x63D, 0);
    i = 0;
    do {
        menuModelInit(&models[i], item->width, item->height);
        menuModelLoadPokemon(&models[i], getPokemonBySelect(selectIndex[i]));
        menuModelCheck(&models[i], 1);
        i++;
    } while (i < 2);
    bgDrawFadeOut();
    cstate.unk4 = 0x11;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionSelectPokemon2CheckStatus() {
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    menuSetEnablePort(2);
    menuPokemonStatusExecute(PLAYER_1);
    menuSetEnablePort(1);
    flagC51 = 1;
    menuStateChange((enumMenuState)4);
    waitMenuOpen();
    _pokemonChangeFadeIn(0.3f);
    fadeCheck(1);
    if (menuGetLastError() == 1) {
        GSsndPlayNow(0x13);
        winMsgOpen(2, 0xC4A3, 1, 0);
        cstate.unk4 = 2;
        memset(cstate.saved, 0, 0x40);
    } else {
        cstate.unk4 = 0xD;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon2Selected() {
    if (pokmonSelectCheck(PLAYER_1)) {
        long index;
        long result;
        int player;
        menuSetEnablePort(2);
        index = selectIndex[currentPlayer];
        if (index >= getQuantityHeroPokemon(PLAYER_0)) {
            player = 1;
        } else {
            player = 0;
        }
        if (player == currentPlayer) {
            result = _actionSelect2or3(0xC494, 0xC495, 0xC4AC);
        } else {
            result = _actionSelect2or3(0xC494, 0xC4AC, 0);
        }
        menuSetEnablePort(1);
        if (!gbaConnectionCheckIsError()) {
            switch (result) {
            case 0xC494:
                cstate.unk4 = 0xE;
                memset(cstate.saved, 0, 0x40);
                return;
            case 0xC495:
                cstate.unk4 = 0xF;
                memset(cstate.saved, 0, 0x40);
                return;
            case 0xC4AC:
                cstate.unk4 = 0xC;
                memset(cstate.saved, 0, 0x40);
                break;
            }
        }
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon2Main() {
    long value;
    currentPlayer = 1;
    menuSetEnablePort(2);
    menuStateChange((enumMenuState)4);
    flagC50 = 1;
    windowCheckCursor(0xD6, 1);
    flagC50 = 0;
    menuSetEnablePort(1);
    if (!gbaConnectionCheckIsError()) {
        value = windowGetValue(0xD6);
        if (value == -1 || value >= getQuantityAllPokemon()) {
            cstate.unk4 = 7;
            memset(cstate.saved, 0, 0x40);
            return;
        }
        selectIndex[currentPlayer] = value;
        cstate.unk4 = 0xD;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1Chanceld() {
    long result;
    _setInfo(0xC499);
    result = _actionSelect2or3(0x426A, 0x426B, 0);
    _setInfo(0);
    switch (result) {
    case 0x426A:
        cstate.unk4 = 2;
        memset(cstate.saved, 0, 0x40);
        return;
    case 0x426B:
        cstate.unk4 = 7;
        memset(cstate.saved, 0, 0x40);
        return;
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1Selected() {
    if (pokmonSelectCheck(PLAYER_0)) {
        long index;
        long result;
        int player;
        index = selectIndex[currentPlayer];
        if (index >= getQuantityHeroPokemon(PLAYER_0)) {
            player = 1;
        } else {
            player = 0;
        }
        if (player == currentPlayer) {
            result = _actionSelect2or3(0xC494, 0xC495, 0xC4AC);
        } else {
            result = _actionSelect2or3(0xC494, 0xC4AC, 0);
        }
        switch (result) {
        case 0xC494:
            cstate.unk4 = 0xA;
            memset(cstate.saved, 0, 0x40);
            return;
        case 0xC495:
            cstate.unk4 = 0xB;
            memset(cstate.saved, 0, 0x40);
            return;
        case 0xC4AC:
            cstate.unk4 = 7;
            memset(cstate.saved, 0, 0x40);
            break;
        }
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1Main() {
    long value;
    stateFunctionSelectPokemon2Reset();
    currentPlayer = 0;
    if (bgDrawFadeIsLive()) {
        menuStateChange(MENU_STATE_2);
        bgDrawFadeIn();
    }
    menuStateChange(MENU_STATE_3);
    flagC50 = 1;
    windowCheckCursor(0xD6, 1);
    flagC50 = 0;
    value = windowGetValue(0xD6);
    if (value == -1 || value >= getQuantityAllPokemon()) {
        cstate.unk4 = 9;
        memset(cstate.saved, 0, 0x40);
        return;
    }
    selectIndex[currentPlayer] = value;
    cstate.unk4 = 8;
    memset(cstate.saved, 0, 0x40);
}

long _actionSelect2or3(u32 a, u32 b, u32 c) {
    u32 values[3] = { 0, 0, 0 };
    long menu;
    long result;
    values[0] = a;
    values[1] = b;
    values[2] = c;
    menuOpenCustom(0xD2, windowGetActiveID(), 0, 0, 0, 0);
    if (c == 0) {
        menu = 0x11A;
    } else {
        menu = 0x11B;
    }
    menuOpenCustom(menu, windowGetActiveID(), 0, 0, 0, 0);
    if (c == 0) {
        _menuSetMsg(menu, 0x8C3, a);
        _menuSetMsg(menu, 0x8C4, b);
    } else {
        _menuSetMsg(menu, 0x8CD, a);
        _menuSetMsg(menu, 0x8CC, b);
        _menuSetMsg(menu, 0x8CB, c);
    }
    windowCheckCursor(menu, 1);
    result = windowGetValue(menu);
    menuClose(menu);
    menuClose(0xD2);
    if (result == -1) {
        if (c == 0) {
            result = 1;
        } else {
            result = 2;
        }
    }
    return values[result];
}

bool _isTemochiPokemonCheck() {
    Hero *hero = Hero::getHeroPtr();
    long i = 0;
    long exchangeable = 0;
    long counts[8];
    memset(counts, 0, 0x20);
    do {
        Pokemon *p = hero->getPokemon(i);
        long state;
        if (_isPokemonExchangeAble(p, PLAYER_0)) {
            exchangeable++;
        }
        state = _getPokemonState(p, PLAYER_0);
        counts[state]++;
        if (!_isPokemonValid(p, PLAYER_0)) {
            break;
        }
        i++;
    } while (i < 6);
    if (i <= 1) {
        GSsndPlayNow(0x13);
        winMsgOpenWithSE(3, 0xC482, 1, 0, 2);
        winMsgClose(1);
        return false;
    }
    if (exchangeable == 0) {
        long msg = 0xC4A5;
        if (counts[3] != 0) {
            msg = 0xC483;
        } else if (counts[4] != 0) {
            msg = 0xC484;
        } else if (counts[2] != 0 || counts[1] != 0) {
            msg = 0xC4A7;
        } else if (counts[5] != 0 || counts[6] != 0) {
            msg = 0xC4AA;
        }
        GSsndPlayNow(0x13);
        winMsgOpenWithSE(3, msg, 1, 0, 2);
        winMsgClose(1);
        return false;
    }
    return true;
}

void CMenuPokemonChange::ctrlHook(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            switch (win->menu) {
            case 0xD4:
            case 0xD6:
                winSeqSetMenu(win->menu, 0x1BC);
                break;
            case 0xD5:
                break;
            }
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            win->step = 1;
        }
        break;
    }
}

void CMenuPokemonChange::bgDrawFadeIn(f32 duration) {
    tagWINDOW_WORK *win = windowSearchID(0xDF);
    if (win != 0) {
        f32 t = 0.0f;
        while (t < duration) {
            win->alpha = (u8)(255.0f * (1.0f - t / duration));
            GSthreadSwitch();
            t += timeGetLastFrameSec();
        }
        win->alpha = 0;
        menuCloseCustom(0xDF, 0, 1);
    }
}

void CMenuPokemonChange::bgDrawFadeOut() {
    f32 t;
    tagWINDOW_WORK *win;
    menuOpenCustom(0xDF, windowGetActiveID(), 0, 2, 0, 0);
    menuSetDisp(0xDF, 1);
    win = windowSearchID(0xDF);
    t = 0.0f;
    while (t < 0.3f) {
        win->alpha = (u8)(255.0f * (t / 0.3f));
        GSthreadSwitch();
        t += timeGetLastFrameSec();
    }
    win->alpha = 0xFF;
}

void CMenuPokemonChange::stateFunctionExChangeOK() {
    u8 id0;
    u8 id1;
    u32 nick0;
    u32 nick1;
    pokemonBiosSetFriend(getPokemonBySelect(selectIndex[0]), 0x46);
    pokemonBiosSetFriend(getPokemonBySelect(selectIndex[1]), 0x46);
    memoDataSet(0, getPokemonBySelect(selectIndex[0]));
    id0 = heroGetStatus(hero0, 1, 0);
    id1 = heroGetStatus(&hero1, 1, 0);
    nick0 = pokemonBiosGetNicknamePtr(getPokemonBySelect(selectIndex[0]));
    nick1 = pokemonBiosGetNicknamePtr(getPokemonBySelect(selectIndex[1]));
    msgctrlSetValue(0x4D, id0);
    msgctrlSetValue(0x57, id1);
    msgctrlSetValue(0x32, nick0);
    msgctrlSetValue(0x33, nick1);
    winMsgOpen(2, 0xC49C, 1, 0);
    winMsgClose(1);
    cstate.unk4 = 0x15;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionExChangeMain() {
    static Pokemon pokemon;
    Pokemon *pokemons[2];
    MenuItemSimple *item;
    long i;
    long j;
    pokemonInit(&pokemon);
    for (i = 0; i < 2; i++) {
        pokemons[i] = getPokemonBySelect(selectIndex[i]);
    }
    if (pokemons[0]->getDarkPokemon() != 0) {
        pokemons[0]->getDarkPokemon()->setPlace(DARK_POKEMON_WHERE_0, 0);
    }
    pokemonBiosCopy(&pokemon, pokemons[1]);
    pokemonBiosCopy(pokemons[1], pokemons[0]);
    pokemonBiosCopy(pokemons[0], &pokemon);
    bgDrawFadeIn(2.0f);
    _pokemonChangeFadeOut(0.0f);
    _pokemonChangeFadeIn(1.0f);
    cameraPlayAnime(floorGetCurrentGroupID(), 0xFCD1800, 0, 0.0f);
    GSthreadSwitch();
    GSsndPlayNow(0x462);
    floorMapSetDisp(1);
    scriptModelSetMotion(0xFCC1000, 0, 0, 0);
    _pokemonChangeFadeIn(3.0f);
    cameraWaitSyncAnime(1);
    _pokemonChangeFadeOut(0.7f);
    floorMapSetDisp(0);
    item = menuPtItemGetByMenuIdAndItemId(0xDE, 0x652, 0);
    for (j = 0; j < 2; j++) {
        menuModelInit(&models[j], item->width, item->height);
        menuModelLoadPokemon(&models[j], getPokemonBySelect(selectIndex[j]));
        menuModelCheck(&models[j], 1);
    }
    menuStateChange((enumMenuState)6);
    _pokemonChangeFadeIn(0.15f);
    cstate.unk4 = 0x14;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionExChangeStart() {
    MenuItemSimple *item;
    long i;
    long j;
    u8 id0;
    u8 id1;
    u32 nick0;
    u32 nick1;
    item = menuPtItemGetByMenuIdAndItemId(0xDE, 0x652, 0);
    for (i = 0; i < 2; i++) {
        menuModelInit(&models[i], item->width, item->height);
        menuModelLoadPokemon(&models[i], getPokemonBySelect(selectIndex[i]));
        menuModelCheck(&models[i], 1);
    }
    menuStateChange((enumMenuState)6);
    bgDrawFadeIn();
    _menuWait(1.0f);
    id0 = heroGetStatus(hero0, 1, 0);
    id1 = heroGetStatus(&hero1, 1, 0);
    nick0 = pokemonBiosGetNicknamePtr(getPokemonBySelect(selectIndex[0]));
    nick1 = pokemonBiosGetNicknamePtr(getPokemonBySelect(selectIndex[1]));
    msgctrlSetValue(0x4D, id1);
    msgctrlSetValue(0x57, id0);
    msgctrlSetValue(0x32, nick0);
    msgctrlSetValue(0x33, nick1);
    winMsgOpen(2, 0xC49A, 1, 0);
    winMsgOpen(2, 0xC49B, 1, 0);
    winMsgClose(1);
    bgDrawFadeOut();
    for (j = 0; j < 2; j++) {
        menuModelFree(&models[j]);
        menuModelTerm(&models[j]);
    }
    menuStateChange(MENU_STATE_1);
    cstate.unk4 = 0x13;
    memset(cstate.saved, 0, 0x40);
}

MENU_MODEL::MENU_MODEL() {
}

void _cbMenuPokemonStatus(Pokemon *p, MENU_POKEMON_CB_TYPE type, long player) {
    MenuPokemonChange.pokemonStatusCallback(p, type, (enumPlayerIndex)player);
}

void CMenuPokemonChange::bgDrawFadeIn() {
    bgDrawFadeIn(0.3f);
}

bool CMenuPokemonChange::bgDrawFadeIsLive() {
    return windowSearchID(0xDF) != 0;
}

void CMenuPokemonChange::bgModelRelease() {
    scriptModelClose((void *)bgModelId);
}

}  // namespace

extern "C" s32 menuPokemonChangeCtrl(tagWINDOW_WORK *win) {
    MenuPokemonChange.ctrlHook(win);
    return 0;
}

extern "C" void menuPokemonChangeItemHook(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    MenuPokemonChange.selectItemHook(win, sprite);
}

extern "C" void menuPokemonChangeDraw(tagWINDOW_WORK *win) {
    MenuPokemonChange.selectDrawHook(win);
}

extern "C" void menuPokemonChangeExit(void) {
}

extern "C" void menuPokemonChangeMain(void) {
    MenuPokemonChange.main();
}

extern "C" void menuPokemonChangeInit(void) {
    floorMapSetDisp(0);
    scriptModelStopMotion(0xFCC1000);
}
