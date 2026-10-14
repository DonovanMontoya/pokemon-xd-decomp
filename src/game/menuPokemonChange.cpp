#include <game/menuPokemonChangeLayout.hpp>

extern "C" {
void floorMapSetDisp(s32);
void scriptModelStopMotion(u32);
void GSthreadSwitch(void);
u8 winSeqCheckMove(s32);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
void menuSetDisp(s32, bool);
void *windowSearchID(s32);
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

namespace {

enum enumPlayerIndex { PLAYER_0, PLAYER_1 };
enum enumMenuState { MENU_STATE_0, MENU_STATE_1, MENU_STATE_2, MENU_STATE_3 };

struct MenuItemSimple {
    u8 pad[6];
    s16 x;
};
MenuItemSimple *menuPtItemGetByMenuIdAndItemId(long, u32, long);
void _menuSetMsg(long, u16, u32);
long _getPokemonState(Pokemon *, enumPlayerIndex);
bool _isPokemonBattleAble(Pokemon *, enumPlayerIndex);

bool _isPokemonValid(Pokemon *, enumPlayerIndex);
void _pokemonChangeFadeOut(f32);
void _pokemonChangeFadeIn(f32);

class CMenuPokemonChange {
public:
    u8 pad0[0x24];
    Hero *hero0;
    Hero hero1;
    u8 pad29[0x9A4 - 0x29];
    s32 stateBase;
    s32 state;
    u8 pad9AC[0x9BC - 0x9AC];
    u8 stateBuf[0x40];
    u8 pad9FC[0xA4C - 0x9FC];
    s32 menuId;
    u8 padA50[0xA60 - 0xA50];
    s32 selectIndex;
    s32 quantity;
    u8 padA68[0xC51 - 0xA68];
    u8 flagC51;

    void ctrlHook(tagWINDOW_WORK *);
    void selectItemHook(tagWINDOW_WORK *, tagSPRITE_WORK *);
    void selectItemHookPrime(tagWINDOW_WORK *, tagSPRITE_WORK *, u32);
    void selectDrawHook(tagWINDOW_WORK *);
    void bgDrawFadeIn();
    void bgDrawFadeIn(f32);
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
        state = 2;
        memset(stateBuf, 0, 0x40);
        return true;
    }
    return false;
}

void CMenuPokemonChange::stateFunctionSelectPokemon2PokeExChange() {
    if (pokemonExchangeCheck(PLAYER_1)) {
        state = 0x10;
        memset(stateBuf, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1PokeExChange() {
    if (pokemonExchangeCheck(PLAYER_0)) {
        state = 0xC;
        memset(stateBuf, 0, 0x40);
        stateFunctionSelectPokemon2Reset();
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1CheckStatus() {
    _pokemonChangeFadeOut(1.0f);
    menuStateChange(MENU_STATE_0);
    menuPokemonStatusExecute(PLAYER_0);
    flagC51 = 1;
    menuStateChange(MENU_STATE_3);
    waitMenuOpen();
    _pokemonChangeFadeIn(1.0f);
    fadeCheck(1);
    state = 8;
    memset(stateBuf, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionSelectPokemonStart() {
    selectIndex = 0;
    quantity = getQuantityHeroPokemon(PLAYER_0);
    state = stateBase + 1;
    memset(stateBuf, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionSelectPokemon2Reset() {
    quantity = getQuantityHeroPokemon(PLAYER_0);
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

void CMenuPokemonChange::bgDrawFadeIn() {
    bgDrawFadeIn(1.0f);
}

bool CMenuPokemonChange::bgDrawFadeIsLive() {
    return windowSearchID(0xDF) != 0;
}

void CMenuPokemonChange::bgModelRelease() {
    scriptModelClose(*(void **)((u8 *)this + 0xA58));
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
