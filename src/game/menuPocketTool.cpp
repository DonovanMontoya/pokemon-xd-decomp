#include <game/menuPocketToolLayout.hpp>

extern "C" {
u32 soundGetBGMID(void);
u32 soundGetEnvID(void);
s32 soundGetVolume(void);
void soundOpenPlayEnv(u32, s32, u8);
void GSthreadSwitch(void);
u16 windowGetKeyTrg(void);
void *memset(void *, int, u32);
void *memcpy(void *, const void *, u32);
void pokemonInit(Pokemon *);
f32 timeGetLastFrameSec(void);
DarkPokemon *darkPokemonGetDarkPokemon(u32);
s32 gamedataGetStatus(s32, s32);
void pokemonCreate(Pokemon *, u16, s32, s32);
u16 pokemonBiosGetInitDp(Pokemon *);
void pokemonSetDarkPokemonStatus(Pokemon *, u16);
extern u32 darkPokemonList_number;
s32 GSmsgIsCheck(u32);
void GSmsgExec(u32, s32, s32);
void GSmsgKill(u32);
tagWINDOW_WORK *windowSearchID(s32);
void winMsgDraw(void);
void GSgfxLayerSetActive(s32);
s32 floorGetMenuLayerID(void);
void spriteSetOffset(s32, s32, s32);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void spriteClearEnv(s32);
u32 timeGetLastFrameTime(void);
s8 fadeCheck(s32);
void fadeSetToBlackOutIfNotBlack(f32);
void fadeSetToBlackInIfBlack(f32);
void fadeSet(s32, f32);
void GSprimSetQuadVertexOrder(s32);
void GSprimDraw2DQuad4V(const f32 (*)[2], GSgfxColAu8);
u8 GSgfxVideoGetVsyncRate(void);
s32 windowGetActiveID(void);
u16 windowGetKeyOn(void);
void windowCloseMain(tagWINDOW_WORK *);
void menuSetDisp(s32, s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
s32 menuSubOpenSelect(s32, u32 *, s32, long, long, long);
void *menuDataBiosGetPtr(s32);
void soundOpenPlay(u32, s32, u8);
void GSsndPlayNow(u32);
void winSpriteDraw(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSgfxBlendMode(s32, s32, s32);
MENU_SPRITE_dd_ *menuSpriteBiosGetPtr(u32);
MenuSpriteValue *menuSpriteBiosGetValPtr(MENU_SPRITE_dd_ *);
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, u32);
void winSpriteSetDisp(tagSPRITE_WORK *, bool);
void windowDrawSprite2(s16, s16, s16, s16, u32, s32, u16, s32, s32);
void windowDrawSprite(s16, s16, s32, u16, s32, s32);
double atan2(double, double);
}


static u32 _darkPokemonIndex = 12;

void menuPtRestoreSound(MenuPtWorkSound *work) {
    if (work->bgm != 0 && work->bgm != soundGetBGMID()) {
        soundOpenPlay(work->bgm, 0x32, work->bgmVolume);
    }
    if (work->env != 0 && work->env != soundGetEnvID()) {
        soundOpenPlayEnv(work->env, 0x32, work->envVolume);
    }
}

void menuPtSaveSound(MenuPtWorkSound *work) {
    u32 bgm;
    u8 bgmVolume;
    u32 env;
    u8 envVolume;
    bgm = soundGetBGMID();
    if (bgm != 0) {
        bgmVolume = soundGetVolume();
    } else {
        bgmVolume = 0;
    }
    env = soundGetEnvID();
    if (env != 0) {
        envVolume = soundGetVolume();
    } else {
        envVolume = 0;
    }
    work->bgm = bgm;
    work->env = env;
    work->bgmVolume = bgmVolume;
    work->envVolume = envVolume;
}

void menuPtStopSound(MenuPtWorkSound *work) {
    u32 bgm;
    u8 bgmVolume;
    u32 env;
    u8 envVolume;
    bgm = soundGetBGMID();
    if (bgm != 0) {
        bgmVolume = soundGetVolume();
        soundOpenPlay(8, 0x32, 0xFF);
    } else {
        bgmVolume = 0;
    }
    env = soundGetEnvID();
    if (env != 0) {
        envVolume = soundGetVolume();
    } else {
        envVolume = 0;
    }
    work->bgm = bgm;
    work->env = env;
    work->bgmVolume = bgmVolume;
    work->envVolume = envVolume;
}

void menuPocketButtonWait(void) {
    do {
        GSthreadSwitch();
    } while ((windowGetKeyTrg() & 0x30) == 0);
}

void menuPocketDebugMakeDarkPokemonByID(Pokemon &pokemon, u16 id, f32 rate);
void menuPocketSetDarkPokemon(Pokemon &pokemon, f32 rate, u16 id);
void menuPocketDebugMakePokemonByID(Pokemon &pokemon, u16 id, bool dark, f32 rate);
static u16 pokemonindex(int index);

void menuPocketDebugMakeDarkPokemonByID(Pokemon &pokemon, u16 id, f32 rate) {
    u16 pokemonId = darkPokemonGetDarkPokemon(id)->getPokemonID();
    pokemonCreate(&pokemon, pokemonId, 0x19, gamedataGetStatus(0, 1));
    menuPocketSetDarkPokemon(pokemon, rate, id);
    pokemonBiosGetInitDp(&pokemon);
}

void menuPocketDebugMakePokemonByID(Pokemon &pokemon, u16 id, bool dark, f32 rate) {
    int i;
    pokemonCreate(&pokemon, id, 0x19, gamedataGetStatus(0, 1));
    if (dark) {
        for (i = 0; i < 10; i++) {
            _darkPokemonIndex++;
            if (_darkPokemonIndex >= darkPokemonList_number) {
                _darkPokemonIndex = 1;
            }
            menuPocketSetDarkPokemon(pokemon, rate, _darkPokemonIndex);
            if (pokemonBiosGetInitDp(&pokemon) != 0) {
                break;
            }
        }
    }
}

void makePocketDeubugMakeDarkPokemonReset(void) {
    _darkPokemonIndex = 12;
}

void menuPocketDebugMakePokemonBySN(Pokemon &pokemon, u16 sn, bool dark, f32 rate) {
    menuPocketDebugMakePokemonByID(pokemon, pokemonindex(sn % 386), dark, rate);
}

void menuPocketSetDarkPokemon(Pokemon &pokemon, f32 rate, u16 id) {
    DarkPokemon *dark;
    u16 dp;
    pokemonSetDarkPokemonStatus(&pokemon, id);
    dp = pokemonBiosGetInitDp(&pokemon);
    pokemon.setDarkPoint(dp * rate);
    dark = darkPokemonGetDarkPokemon(id);
    dark->setStatus(DARK_POKEMON_STATUS_3);
    dark->setSnatchIndex(id);
}

static u16 pokemonindex(int index) {
    index++;
    if (index > 0xFB) {
        index += 0x19;
    }
    return index;
}

void CMenuGlobalState::init() {
    memset(this, 0, 0x208);
    cursor.init();
    state.init();
}

bool CMenuPokemonCursor::isCatchPokemon() {
    return pokemon.checkValid();
}

void CMenuPokemonCursor::deletePokemon() {
    pokemonInit(&pokemon);
    beforeAnt = ant;
    ant.init();
}

void CMenuPokemonCursor::setBeforAnt(CAnt &src) {
    beforeAnt = src;
}

void CMenuPokemonCursor::setPokemon(Pokemon *src) {
    beforeAnt = ant;
    if (src == 0) {
        pokemonInit(&pokemon);
        ant.init();
    } else {
        memcpy(&pokemon, src, 0xC4);
        ant.initByPokemonAndSetColorAnimationInAny(&pokemon);
        ant.setAnimation(0);
    }
}

void CMenuPokemonCursor::setPositionTableDummy() {
    PocketVec<short> v = table[index];
    defaultPositionTbl.x = v.x;
    defaultPositionTbl.y = v.y;
    table = &defaultPositionTbl;
    index = 0;
    prevIndex = 0;
}

void CMenuPokemonCursor::setPositionIndex(long newIndex) {
    PocketVec<short> v = table[index];
    x = v.x;
    y = v.y;
    prevIndex = index;
    index = newIndex;
}

void CMenuPokemonCursor::setPositionTable(PocketVec<short> *newTable, long newIndex) {
    setPositionIndex(newIndex);
    prevIndex = 0;
    table = newTable;
}

void CMenuPokemonCursor::setAnimationOff() {
    unk4 = 0;
    unk8 = 0.0f;
    beforeAnt.init();
}

void CMenuPokemonCursor::init() {
    memset(this, 0, 0x150);
    unk0 = 1;
    pokemonInit(&pokemon);
    ant.init();
    beforeAnt.init();
    unk14C = 0;
    defaultPositionTbl.x = 0;
    defaultPositionTbl.y = 0;
    x = 0;
    y = 0;
    table = &defaultPositionTbl;
}

void CState::update() {
    if (unk4 != -1) {
        unk8 = unk0;
        unk0 = unk4;
        unk4 = -1;
        time = 0.0f;
        frames = 0;
        unk98 = 0;
        unk9C = 0;
        unkA0 = 0;
        memcpy(saved2, saved, 0x40);
    } else {
        addTime();
    }
}

void CState::addTime() {
    frames++;
    lastFrame = timeGetLastFrameSec();
    time = time + lastFrame;
}

void CState::init() {
    memset(this, 0, 0xA8);
    unk8 = -1;
    lastFrame = timeGetLastFrameSec();
}

void CInfoWindow::exec(CMetaMenu &menu, u32 message, bool close_) {
    open(message, true);
    do {
        key = windowGetKeyTrg();
        menu.updateAll();
    } while (!isMsgEnd());
    if (close_) {
        close();
    }
}

void CInfoWindow::setMsgCtrlValue(u32 id, u32 value) {
    int i = 0;
    while (keys[i][0] != 0) {
        i++;
    }
    keys[i][0] = id;
    keys[i][1] = value;
}

bool CInfoWindow::isMsgEnd() {
    return !GSmsgIsCheck(msg);
}

void CInfoWindow::open(u32 message, bool waitFlag) {
    wait = waitFlag;
    if (message != 0) {
        msg = message;
        if (wait) {
            GSmsgExec(msg, 0, 0);
        }
    }
    open_ = 1;
}

void CInfoWindow::close() {
    if (wait) {
        GSmsgKill(msg);
    }
    open_ = 0;
    wait = 0;
    msg = 0;
    memset(keys, 0, 0x20);
}

void CInfoWindow::initTutorialTalk() {
    tagSPRITE_WORK *sprite;
    unk4 = 0;
    key = 0;
    open_ = 0;
    wait = 0;
    msg = 0;
    memset(keys, 0, 0x20);
    unk0 = 0xE3;
    sprite = menuPtGetSpriteWorkByHookFunction(windowSearchID(unk0), (void *)winMsgDraw, 0, 0);
    sprite->callback = 0;
    sprite->flags = 0;
    unk4 = sprite->id;
    close();
}

void CInfoWindow::init(long menu, u32 value) {
    unk4 = 0;
    key = 0;
    open_ = 0;
    wait = 0;
    msg = 0;
    memset(keys, 0, 0x20);
    unk0 = menu;
    unk4 = value;
    close();
}

void CMetaMenu::waitAtTime(f32 seconds) {
    f32 elapsed = 0.0f;
    for (;;) {
        updateAll();
        if (elapsed > seconds) {
            break;
        }
        elapsed += timeGetLastFrameSec();
    }
}

long CMetaMenu::calcAnimationTimeRate0toX(f32 rate, long x) {
    f32 value = calcAnimationTimeRate0to1(rate) * (f32)(x + 1);
    if ((f32)x < value) {
        value = (f32)x;
    }
    return (long)value;
}

f32 CMetaMenu::calcAnimationTimeRate0to1to0(f32 rate) {
    f32 r = calcAnimationTimeRate0to1(rate);
    if (r > 0.5f) {
        r = 1.0f - r;
    }
    r *= 2.0f;
    return r;
}

f32 CMetaMenu::calcAnimationTimeRate0to1(f32 rate) {
    u32 period = (u32)(rate * GSgfxVideoGetVsyncRate());
    u32 pos = (u32)(time % period);
    return (f32)pos / (f32)period;
}

void CMetaMenu::drawHook() {
    s32 layer;
    GSgfxLayerSetActive(7);
    layer = floorGetMenuLayerID();
    spriteSetOffset(7, 0, 0);
    spriteClearScissor(7);
    spriteSetEnv(7);
    spriteSetOffset(layer, 0, 0);
    spriteClearScissor(layer);
    spriteSetEnv(layer);
    drawMain();
    time += timeGetLastFrameTime();
    alphaFadeUpdate();
    tutorialManageUpdate();
    spriteSetOffset(7, 0, 0);
    spriteClearScissor(7);
    spriteClearEnv(7);
    spriteSetOffset(layer, 0, 0);
    spriteClearScissor(layer);
    spriteClearEnv(layer);
    GSgfxLayerSetActive(2);
}

bool CMetaMenu::isAnimationStateNone() {
    return true;
}

void CMetaMenu::updateAll() {
    vsyncUpdate();
}

void CMetaMenu::vsyncUpdate() {
    GSthreadSwitch();
}

void CMetaMenu::systemFadeWaitToEnd() {
    while (fadeCheck(0) != 0) {
        updateAll();
    }
}

void CMetaMenu::systemFadeOutSetAndWait(f32 seconds) {
    systemFadeOutKick(seconds);
    systemFadeWaitToEnd();
}

void CMetaMenu::systemFadeOutKick(f32 seconds) {
    if (seconds == -1.0f) {
        seconds = 0.5f;
    }
    fadeSetToBlackOutIfNotBlack(seconds);
}

void CMetaMenu::systemFadeInKick() {
    fadeSetToBlackInIfBlack(0.5f);
}

void CMetaMenu::systemFadeOutKeepAfterFloorPush() {
    GSthreadSwitch();
    fadeSet(3, 0.0f);
}

void CMetaMenu::tutorialExitKick() {
}

static CMetaMenu *_pThis;
static s32 _selectItemQuantity;
CMetaMenu *CMetaMenu::pCurrentMenu;

void CMetaMenu::alphaFadeDraw() {
    static const f32 xy[4][2] = { { 0.0f, 0.0f }, { 640.0f, 0.0f }, { 640.0f, 480.0f }, { 0.0f, 480.0f } };
    GSgfxColAu8 color = { 0, 0, 0, 0xFF };
    GSprimSetQuadVertexOrder(1);
    color.a = 255 - getAlphaFadeAlpha();
    if (color.a != 0) {
        GSprimDraw2DQuad4V(xy, color);
    }
}

u8 CMetaMenu::getAlphaFadeAlpha() const {
    s32 total;
    switch (fadeState) {
    case 0:
        return 0xFF;
    case 1:
        total = (u32)(0.5f * GSgfxVideoGetVsyncRate());
        return ((s32)((u32)(0.5f * GSgfxVideoGetVsyncRate()) - fadeTime) * 255) / total;
    case 3:
        return (fadeTime * 255) / (s32)(u32)(0.5f * GSgfxVideoGetVsyncRate());
    case 2:
        return 0;
    default:
        return 0;
    }
}

void CMetaMenu::alphaFadeOutAndWait() {
    bool end;
    s32 state;
    alphaFadeOutKick();
    do {
        updateAll();
        state = fadeState;
        end = false;
        if (state == 0 || state == 2) {
            end = true;
        }
    } while (!end);
    updateAll();
}

void CMetaMenu::alphaFadeUpdate() {
    if (fadeTime != 0) {
        fadeTime -= timeGetLastFrameTime();
        if (fadeTime <= 0) {
            if (fadeState == 3) {
                fadeState = 0;
            } else if (fadeState == 1) {
                fadeState = 2;
            }
        }
    }
}

void CMetaMenu::alphaFadeOutKick() {
    fadeTime = (u32)(0.5f * GSgfxVideoGetVsyncRate());
    fadeState = 1;
}

void CMetaMenu::alphaFadeInKick() {
    fadeTime = (u32)(0.5f * GSgfxVideoGetVsyncRate());
    fadeState = 3;
}

MetaKeyInfo *CMetaMenu::getKeyInfo() {
    u16 repeat;
    u16 trigger;
    u16 on;
    bool counting;
    u16 tutorialKey;
    if (tutorialActive) {
        memset(&keyInfo, 0, 0x1A);
        tutorialKey = tutorialManage();
        keyInfo.trigger = tutorialKey;
        keyInfo.repeat = tutorialKey;
        return &keyInfo;
    }
    memset(&keyInfo, 0, 0x1A);
    if (windowGetActiveID() != 0xDA) {
        return &keyInfo;
    }
    repeat = 0;
    trigger = windowGetKeyTrg();
    on = windowGetKeyOn();
    counting = false;
    if (trigger != 0) {
        repeat = trigger;
    } else if (on != 0 && on == lastKey) {
        if (repeatCount >= 12) {
            repeat = on;
        } else {
            counting = true;
        }
    }
    if (counting) {
        repeatCount++;
    } else {
        repeatCount = 0;
    }
    lastKey = on;
    keyInfo.repeat = repeat;
    keyInfo.trigger = trigger;
    return &keyInfo;
}

void CMetaMenu::aButtonWait() {
    bool done = false;
    while (!done) {
        switch (getKeyInfo()->trigger) {
        case 0x10:
            done = true;
            menuPtPlaySe(seId);
            break;
        }
        updateAll();
    }
}

static void _tutorialWindowCursorFunc(tagWINDOW_WORK *win) {
    u16 key;
    if (win != 0) {
        menuDataBiosGetPtr(win->menu);
        key = _pThis->tutorialManage();
        if (key & 1) {
            win->value--;
            if (win->value < 0) {
                win->value = (s16)(_selectItemQuantity - 1);
            }
        } else if (key & 2) {
            win->value++;
            if (win->value >= _selectItemQuantity) {
                win->value = 0;
            }
        }
        win->selected = (s16)win->value;
    }
}

static void _tutorialWindowButtonFunc(tagWINDOW_WORK *win) {
    u16 key;
    if (win != 0) {
        key = _pThis->tutorialManage();
        if (key & 0x10) {
            win->finished = 1;
        }
        if (key & 0x20) {
            win->finished = 1;
            win->cancelled = 1;
        }
    }
}

void CMetaMenu::localWindowRemove(long id) {
    int index = localWindowSearch(id);
    if (index != -1) {
        windows[index] = 0;
    }
}

void CMetaMenu::localWindowDrawAll(long first, long last) {
    long i;
    i = first;
    for (; i <= last; i++) {
        if (windows[i] != 0) {
            if (windowFuncs[i] != 0) {
                windowFuncs[i](this, windows[i]);
            } else {
                menuPtWindowWorkDraw(windows[i]);
            }
        }
    }
}

void CMetaMenu::localWindowDrawAll() {
    localWindowDrawAll(0, 63);
}

void CMetaMenu::localWindowEntry(long id, long index, void (*func)(CMetaMenu *, long)) {
    windows[index] = id;
    windowFuncs[index] = func;
}

int CMetaMenu::localWindowSearch(long id) {
    int i;
    for (i = 0; i < 64; i++) {
        if (windows[i] == id) {
            return i;
        }
    }
    return -1;
}

void CMetaMenu::localWindowDeleteAll() {
    int i;
    windowCloseMain(windowSearchID(0xDA));
    pCurrentMenu = 0;
    i = 0;
    for (;;) {
        if (windowTable[i] == 0) {
            break;
        }
        windowCloseMain(windowSearchID(windowTable[i]));
        i++;
    }
}

void CMetaMenu::localWindowCreateAll() {
    int i;
    long id;
    menuOpenCustom(0xDA, windowGetActiveID(), 0, 0, 0, 0);
    i = 0;
    for (;;) {
        id = windowTable[i];
        if (id == 0) {
            break;
        }
        menuPtMenuLoad(id);
        menuSetDisp(id, 0);
        i++;
    }
    pCurrentMenu = this;
}

void CMetaMenu::localWindowSetTable(long *table) {
    windowTable = table;
}

extern "C" long menuPocketToolCMetaButton(tagWINDOW_WORK *) {
    return 0;
}

extern "C" long menuPocketToolCMetaDraw(tagWINDOW_WORK *) {
    if (CMetaMenu::pCurrentMenu != 0) {
        CMetaMenu::pCurrentMenu->drawHook();
    }
    return 0;
}

extern "C" long menuPocketToolCMetaCtrl(tagWINDOW_WORK *) {
    return 0;
}

void menuPtPlayBgm(u32 id) {
    soundOpenPlay(id, 0x32, 0xFF);
}

void menuPtPlaySe(u32 id) {
    GSsndPlayNow(id);
}

void menuPtWindowWorkDraw(long id) {
    menuPtWindowWorkDraw(windowSearchID(id));
}

void menuPtWindowWorkDraw(tagWINDOW_WORK *win) {
    s32 layer;
    s32 menuLayer;
    if (win != 0) {
        menuLayer = floorGetMenuLayerID();
        layer = win->layer;
        spriteSetOffset(layer, win->x, win->y);
        spriteClearScissor(layer);
        spriteSetEnv(layer);
        spriteSetOffset(menuLayer, win->x, win->y);
        spriteClearScissor(menuLayer);
        spriteSetEnv(menuLayer);
        menuPtWindowWorkDrawPrime(win);
        spriteSetOffset(win->layer, 0, 0);
        spriteClearScissor(win->layer);
        spriteSetEnv(win->layer);
    }
}

void menuPtWindowWorkDrawPrime(tagWINDOW_WORK *win) {
    tagSPRITE_WORK *sprite = win->items;
    while (sprite != 0) {
        winSpriteDraw(win, sprite);
        sprite = sprite->next;
    }
    GSgfxBlendMode(1, 4, 5);
}

void menuPtMenuLoad(long menu) {
    menuOpenCustom(menu, windowGetActiveID(), 0, 4, 0, 0);
}

void menuPtSpriteDrawCenterColor(u16 id, long x, long y, u32 color) {
    MenuSpriteValue *value = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    x -= value->width / 2;
    y -= value->height / 2;
    windowDrawSprite2(x, y, value->width, value->height, color, 0, id, 0, 7);
}

void menuPtSpriteDrawColor(u16 id, long x, long y, long width, long height, u32 color) {
    windowDrawSprite2(x, y, width, height, color, 0, id, 0, 7);
}

void menuPtSpriteDrawColor(u16 id, long x, long y, u32 color) {
    MenuSpriteValue *value = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    windowDrawSprite2(x, y, value->width, value->height, color, 0, id, 0, 7);
}

void menuPtSpriteDraw(u16 id, long x, long y) {
    windowDrawSprite(x, y, 0, id, 0, 7);
}

void menuPtItemDrawOffsetXWColor(MENU_ITEM_dd_ *item, long x, long width, u32 color) {
    windowDrawSprite2(item->x + x, item->y, width, item->height, color, 0, item->spriteID, 0, 7);
}

void menuPtItemDrawOffset(MENU_ITEM_dd_ *item, long x, long y) {
    windowDrawSprite2(item->x + x, item->y + y, item->width, item->height, 0xFFFFFFFF, 0, item->spriteID, 0, 7);
}

void menuPtItemDrawAlpha(MENU_ITEM_dd_ *item, u8 alpha) {
    u16 id = item->spriteID;
    windowDrawSprite2(item->x, item->y, item->width, item->height, alpha | 0xFFFFFF00, 0, id, 0, 7);
}

void menuPtSpriteWorkSetWidthRateColor(tagWINDOW_WORK *win, u32 id, long n, f32 rate, GSgfxColAu8 color) {
    tagSPRITE_WORK *sprite = menuPtSpriteWorkGetByItemID(win, id, n);
    MENU_ITEM_dd_ *item = menuPtItemGetBySpriteWork(win, sprite);
    sprite->color.value = GSgfxColAu8To32(color);
    sprite->width = item->width * rate;
    winSpriteSetDisp(sprite, rate != 0.0f);
}

void menuPtSpriteWorkSetSw(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, bool on) {
    winSpriteSetDisp(sprite, on);
}

void menuPtSpriteWorkSetSw(tagWINDOW_WORK *win, u32 id, long n, bool on) {
    winSpriteSetDisp(menuPtSpriteWorkGetByItemID(win, id, n), on);
}

void menuPtSpriteWorkSetSpriteId(tagSPRITE_WORK *sprite, u32 id) {
    MENU_SPRITE_dd_ *menuSprite = menuSpriteBiosGetPtr(id);
    menuPtSpriteWorkSetMenuSprite(sprite, menuSprite);
}

void menuPtSpriteWorkSetMenuSprite(tagSPRITE_WORK *sprite, MENU_SPRITE_dd_ *menuSprite) {
    MenuSpriteValue *value = menuSpriteBiosGetValPtr(menuSprite);
    sprite->resource = value->resource;
    sprite->sourceX = value->x;
    sprite->sourceY = value->y;
    sprite->sourceWidth = value->width;
    sprite->sourceHeight = value->height;
    sprite->width = value->width;
    sprite->height = value->height;
}

void menuPtSpriteWorkSetMenuItem(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, u32 itemId) {
    MENU_ITEM_dd_ *item = menuItemBiosGetPtr(win->menu, itemId);
    MenuSpriteValue *value = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(item->spriteID));
    sprite->resource = value->resource;
    sprite->sourceX = value->x;
    sprite->sourceY = value->y;
    sprite->sourceWidth = value->width;
    sprite->sourceHeight = value->height;
    sprite->x = item->x;
    sprite->y = item->y;
    sprite->width = item->width;
    sprite->height = item->height;
}

tagSPRITE_WORK *menuPtGetSpriteWorkByHookFunction(tagWINDOW_WORK *win, void *func, u32 index, long n) {
    tagSPRITE_WORK *sprite = win->items;
    for (; sprite != 0; sprite = sprite->next) {
        if (sprite->callback == (u32)func) {
            if (index-- == 0) {
                break;
            }
        }
    }
    while (n != 0 && sprite != 0) {
        n--;
        sprite = sprite->next;
    }
    return sprite;
}

MENU_ITEM_dd_ *menuPtItemGetBySpriteWork(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    return menuItemBiosGetPtr(win->menu, sprite->id);
}

long menuPtSpriteWorkGetIndexFromId(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, u32 id) {
    tagSPRITE_WORK *s = menuPtSpriteWorkGetByItemID(win, id, 0);
    long i = 0;
    for (;;) {
        if (s == sprite) {
            break;
        }
        s = s->next;
        i++;
    }
    return i;
}

tagSPRITE_WORK *menuPtSpriteWorkGetByItemID(tagWINDOW_WORK *win, u32 id, long n) {
    tagSPRITE_WORK *sprite = win->items;
    for (; sprite != 0; sprite = sprite->next) {
        if (sprite->id == id) {
            break;
        }
    }
    while (n > 0) {
        sprite = sprite->next;
        n--;
    }
    return sprite;
}

tagSPRITE_WORK *menuPtSpriteWorkGetByItemID(long menu, u32 id, long n) {
    return menuPtSpriteWorkGetByItemID(windowSearchID(menu), id, n);
}

void menuPtSpriteWorkSetMsgId(long menu, u32 id, long n, u32 msg) {
    menuPtSpriteWorkGetByItemID(menu, id, n)->message = msg;
}

MENU_ITEM_dd_ *menuPtItemGetByMenuIdAndItemId(long menu, u32 itemId, long n) {
    MENU_ITEM_dd_ *item = menuItemBiosGetPtr(menu, itemId);
    long i;
    for (i = 0; i < n; i++) {
        item = menuItemBiosGetPtr(menu, item->nextItem);
    }
    return item;
}

u32 GSgfxColAu8To32(GSgfxColAu8 color) {
    u32 value;
    memcpy(&value, &color, 4);
    return value;
}

bool isDirRegionIn(f32 a, f32 b, f32 c);
f32 dirSubOne(f32 a, f32 b);
f32 dirRefresh2PI(f32 dir);
f32 dirRefreshPI(f32 dir);
long degreeRefresh180(long degree);

bool isDirRegionIn(f32 a, f32 b, f32 c) {
    f32 limit;
    if (c == b) {
        limit = 6.2831855f;
    } else {
        limit = dirSubOne(c, b);
    }
    return dirSubOne(a, b) <= limit;
}

f32 xy2dir(f32 x, f32 y) {
    return atan2(x, -y);
}

f32 xyxy2dir(const PocketVec<short> &a, const PocketVec<short> &b) {
    return atan2((f32)(a.x - b.x), (f32)-(a.y - b.y));
}

long xyxy2dirDegree(const PocketVec<short> &a, const PocketVec<short> &b) {
    f32 dir = atan2((f32)(a.x - b.x), (f32)-(a.y - b.y));
    return degreeRefresh180((long)(0.5f + 180.0f * dir / 3.1415927f));
}

f32 dirSubOne(f32 a, f32 b) {
    return dirRefresh2PI(a - b);
}

f32 dirSubHalf(f32 a, f32 b) {
    return dirRefreshPI(a - b);
}

long degreeSubHalf(long a, long b) {
    return degreeRefresh180(a - b);
}

long degreeRefresh180(long degree) {
    degree = degree % 360;
    if (degree >= 180) {
        degree -= 360;
    } else if (degree <= -180) {
        degree += 360;
    }
    return degree;
}

long degreeRefresh360(long degree) {
    degree = degree % 360;
    if (degree < 0) {
        degree += 360;
    }
    return degree;
}

f32 dirRefresh2PI(f32 dir) {
    dir -= 6.2831855f * (long)(0.15915494f * dir);
    if (dir < 0.0f) {
        dir += 6.2831855f;
    }
    return dir;
}

f32 dirRefreshPI(f32 dir) {
    dir -= 6.2831855f * (long)(0.15915494f * dir);
    if (dir > 3.1415927f) {
        dir -= 6.2831855f;
    } else if (dir < -3.1415927f) {
        dir += 6.2831855f;
    }
    return dir;
}

void menuPocketToolFloatToZero(f32 &value, f32 step) {
    if (value > 0.0f) {
        if ((value -= step) < 0.0f) {
            value = 0.0f;
        }
    } else if (value < 0.0f) {
        if ((value += step) > 0.0f) {
            value = 0.0f;
        }
    }
}

void setBitTable(u32 *table, long bit, bool on) {
    long index = bit / 32;
    long shift = bit % 32;
    if (on) {
        table[index] |= 1 << shift;
    }
}

bool getBitTable(u32 *table, long bit) {
    return (table[bit / 32] & (1 << (bit % 32))) != 0;
}
