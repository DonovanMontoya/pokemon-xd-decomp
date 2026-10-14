#include <game/menuSubLayout.hpp>
#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>
#include <dolphin/gx/GXVert.h>
#include <libc/string.h>

enum GSgfxLayerID { GSGFX_LAYER_ID_DUMMY };
enum menuSubCursorBackColor { MENUSUB_CURSORBACK_COLOR_0, MENUSUB_CURSORBACK_COLOR_1 };

struct MenuSubSpriteVal {
    u8 reserved0[4];
    s16 width;
    s16 height;
};

struct MenuSubCursorAnimeWork {
    f32 x;
    f32 y;
    f32 fromX;
    f32 fromY;
    f32 toX;
    f32 toY;
    u32 color;
    s16 time;
    s16 duration;
    f32 sec;
    u8 cur[4];
    u8 from[4];
    u8 to[4];
};

class Pokemon;
class PokemonData;

extern "C" {
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
s32 GScharCmp(s32, s32);
s32 GSmsgGetGSchar(void);
void GSthreadSwitch(void);
double cos(double);
s32 menuCB_GetDisconnectedGBA(void);
void menuClose(s32);
void menuCloseCustom(s32, s32, s32);
void menuCloseSync(s32, s32);
f32 menuGetTotalTime(void);
void* menuItemBiosGetPtr(s32, s32);
s32 menuOpenCustom(s32, s32, ...);
void menuSetPosition(s16, s16, s16);
s32 menuSpriteBiosGetPtr(u16);
MenuSubSpriteVal* menuSpriteBiosGetValPtr(s32);
u16 pokemonBiosGetPokemonDataId(s32);
u8 pokemonCheckValid(s32);
s32 pokemonDataBiosGetName(void*);
void* pokemonDataBiosGetPtr(u16);
s32 pokemonGetSex(s32);
s32 pokemonGetStatus(s32, s32, s32, s32);
f32 timeGetLastFrameSec(void);
s32 timeGetLastFrameTime(void);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
u8 windowCheckCursor(s32, s32);
s32 windowGetActiveID(void);
s32 windowGetValue(s32);
tagWINDOW_WORK* windowSearchID(s32);
void windowDrawSprite2(s16, s16, s16, s16, u32, void*, u16, s32, s32);
void menuSubCursorAnimeInit(void);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, u8, u8, s32, s32, s32, s32, s32);
}

static s32 _animAlpha(void);
static void _menuSubDrawCursorBackSub(GSgfxLayerID layer, long x, long y, long w, long h, unsigned long color, unsigned char alpha, unsigned char kind, menuSubCursorBackColor col, bool anim);
static void menuSubCheckSelectSub(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, long value);
static u8 menuSubOpenNumberInputSub(unsigned long type, unsigned long* out, unsigned char mode, short x, short y, bool close, unsigned short* (*fn)(unsigned long));

extern "C" {
extern MenuSubCursorAnimeWork _cursorAnimeWork;
}
MenuSubCursorAnimeWork _cursorAnimeWork;
static f32 _cursorTimer;

static f32 _cursorSec = 0.5f;
static f32 _max_alpha = 255.0f;
static f32 _min_alpha = 128.0f;

extern "C" {

s32 menuSubGetKaiwaCloseWindowID(void) {
    return 0x3DF;
}

s32 menuSubGetKaiwaCsrID(void) {
    return 0xBA;
}


void menuSubDrawMsgWindow2(GSgfxLayerID layer, long x, long y, long w, long h, unsigned char alpha) {
    if (GSgfxLayerFindByID(layer) != 0) {
        MenuSubSpriteVal* corner;
        MenuSubSpriteVal* edge;
        MenuSubSpriteVal* side;
        u32 color;
        short left;
        short right;
        short top;
        short bottom;
        short edgeW;
        short sideH;
        long hw;
        long hh;

        menuSpriteBiosGetPtr(0xB3);
        corner = menuSpriteBiosGetValPtr(0);
        color = alpha | ~0xFF;
        hw = corner->width / 2;
        hh = corner->height / 2;
        left = (x - hw) - 15;
        right = ((x + w) - hw) + 15;
        top = (y - hh) - 10;
        bottom = ((y + h) - hh) + 10;
        windowDrawSprite2(left, top, corner->width, corner->height, color, 0, 0xB3, 0, layer);
        windowDrawSprite2(right, top, corner->width, corner->height, color, 0, 0xB3, 1, layer);
        windowDrawSprite2(left, bottom, corner->width, corner->height, color, 0, 0xB3, 2, layer);
        windowDrawSprite2(right, bottom, corner->width, corner->height, color, 0, 0xB3, 3, layer);
        menuSpriteBiosGetPtr(0xB2);
        edge = menuSpriteBiosGetValPtr(0);
        edgeW = (right - left) - corner->width;
        windowDrawSprite2(left + corner->width, top, edgeW, edge->height, color, 0, 0xB2, 0, layer);
        windowDrawSprite2(left + corner->width, bottom, edgeW, edge->height, color, 0, 0xB2, 2, layer);
        menuSpriteBiosGetPtr(0xB1);
        side = menuSpriteBiosGetValPtr(0);
        sideH = (bottom - top) - corner->height;
        windowDrawSprite2(left, top + corner->height, side->width, sideH, color, 0, 0xB1, 0, layer);
        windowDrawSprite2(right, top + corner->height, side->width, sideH, color, 0, 0xB1, 1, layer);
        menuSpriteBiosGetPtr(0xB0);
        menuSpriteBiosGetValPtr(0);
        windowDrawSprite2(left + corner->width, top + corner->height, edgeW, sideH, color, 0, 0xB0, 0, layer);
    }
}

void menuSubDrawNormalWindow2(GSgfxLayerID layer, long x, long y, long w, long h, unsigned char alpha) {
    if (GSgfxLayerFindByID(layer) != 0) {
        MenuSubSpriteVal* corner;
        MenuSubSpriteVal* bottomCorner;
        MenuSubSpriteVal* edge;
        MenuSubSpriteVal* bottomEdge;
        MenuSubSpriteVal* side;
        u32 color;
        short left;
        short right;
        short top;
        short bottom;
        short edgeW;
        short sideH;

        menuSpriteBiosGetPtr(0x69);
        corner = menuSpriteBiosGetValPtr(0);
        left = (x - corner->width / 2) - 10;
        right = ((x + w) - corner->width / 2) + 10;
        menuSpriteBiosGetPtr(0x67);
        bottomCorner = menuSpriteBiosGetValPtr(0);
        color = alpha | ~0xFF;
        top = (y - corner->height / 2) - 10;
        bottom = ((y + h) - corner->height / 2) + 10;
        windowDrawSprite2(left, top, corner->width, corner->height, color, 0, 0x69, 0, layer);
        windowDrawSprite2(right, top, corner->width, corner->height, color, 0, 0x69, 1, layer);
        windowDrawSprite2(left, bottom, bottomCorner->width, bottomCorner->height, color, 0, 0x67, 0, layer);
        windowDrawSprite2(right, bottom, bottomCorner->width, bottomCorner->height, color, 0, 0x67, 1, layer);
        menuSpriteBiosGetPtr(0x66);
        edge = menuSpriteBiosGetValPtr(0);
        edgeW = (right - left) - corner->width;
        windowDrawSprite2(left + corner->width, top, edgeW, edge->height, color, 0, 0x66, 0, layer);
        menuSpriteBiosGetPtr(0x65);
        bottomEdge = menuSpriteBiosGetValPtr(0);
        windowDrawSprite2(left + corner->width, bottom, edgeW, bottomEdge->height, color, 0, 0x65, 0, layer);
        menuSpriteBiosGetPtr(0x68);
        side = menuSpriteBiosGetValPtr(0);
        sideH = (bottom - top) - corner->height;
        windowDrawSprite2(left, top + corner->height, side->width, sideH, color, 0, 0x68, 0, layer);
        windowDrawSprite2(right, top + corner->height, side->width, sideH, color, 0, 0x68, 1, layer);
        menuSpriteBiosGetPtr(0x64);
        menuSpriteBiosGetValPtr(0);
        windowDrawSprite2(left + corner->width, top + corner->height, edgeW, sideH, color, 0, 0x64, 0, layer);
    }
}

void menuSubDrawCursorBack2(GSgfxLayerID layer, long x, long y, long w, long h, unsigned char alpha, unsigned char kind, menuSubCursorBackColor col) {
    _menuSubDrawCursorBackSub(layer, x, y, w, h, 0xFFFFFF00, alpha, kind, col, true);
}

void menuSubDrawCursorBackAnimeOnOffAuto(unsigned long id, GSgfxLayerID layer, long x, long y, long w, long h, unsigned char alpha, unsigned char kind) {
    if (id == (unsigned long)windowSearchID(windowGetActiveID())) {
        _menuSubDrawCursorBackSub(layer, x, y, w, h, 0xFFFFFF00, alpha, kind, (menuSubCursorBackColor)0, true);
    } else {
        _menuSubDrawCursorBackSub(layer, x, y, w, h, 0xFFFFFF00, alpha, kind, (menuSubCursorBackColor)0, false);
    }
}

void menuSubDrawCursorBackAnimeOnOff(GSgfxLayerID layer, long x, long y, long w, long h, unsigned char alpha, unsigned char kind, bool anim) {
    _menuSubDrawCursorBackSub(layer, x, y, w, h, 0xFFFFFF00, alpha, kind, (menuSubCursorBackColor)0, anim);
}

void menuSubDrawCursorBack(GSgfxLayerID layer, long x, long y, long w, long h, unsigned char alpha, unsigned char kind) {
    _menuSubDrawCursorBackSub(layer, x, y, w, h, 0xFFFFFF00, alpha, kind, (menuSubCursorBackColor)0, true);
}

}

static void _menuSubDrawCursorBackSub(GSgfxLayerID layer, long x, long y, long w, long h, unsigned long color, unsigned char alpha, unsigned char kind, menuSubCursorBackColor col, bool anim) {
    u8 a;
    u8 scaled;
    MenuSubSpriteVal* left;
    MenuSubSpriteVal* mid;
    u16 leftId;
    u16 midId;
    u32 c;
    short px;
    short py;
    long midW;

    _animAlpha();
    if (anim) {
        a = _animAlpha();
    } else {
        a = 0xFF;
    }
    scaled = (a * alpha) / 255;
    if (GSgfxLayerFindByID(layer) != 0) {
        if (kind == 0) {
            s32 leftPtr;
            s32 midPtr;
            px = x;
            py = y;
            leftPtr = menuSpriteBiosGetPtr(0xBB);
            midPtr = menuSpriteBiosGetPtr(0xBC);
            left = menuSpriteBiosGetValPtr(leftPtr);
            mid = menuSpriteBiosGetValPtr(midPtr);
            c = color | scaled;
            midW = w - left->width - left->width;
            windowDrawSprite2(px, py, left->width, left->height, c, 0, 0xBB, 0, layer);
            px += left->width;
            windowDrawSprite2(px, py, midW, mid->height, c, 0, 0xBC, 0, layer);
            px += midW;
            windowDrawSprite2(px, py, left->width, left->height, c, 0, 0xBB, 1, layer);
            return;
        }
        {
            s32 leftPtr;
            s32 midPtr;
            px = x;
            py = y;
            if (col == 0) {
                leftId = 0xBF;
                midId = 0xC0;
            } else {
                leftId = 0x1F6;
                midId = 0x1F7;
            }
            leftPtr = menuSpriteBiosGetPtr(leftId);
            midPtr = menuSpriteBiosGetPtr(midId);
            left = menuSpriteBiosGetValPtr(leftPtr);
            mid = menuSpriteBiosGetValPtr(midPtr);
            c = color | scaled;
            midW = w - left->width - left->width;
            windowDrawSprite2(px, py, left->width, left->height, c, 0, leftId, 0, layer);
            px += left->width;
            windowDrawSprite2(px, py, midW, mid->height, c, 0, midId, 0, layer);
            px += midW;
            windowDrawSprite2(px, py, left->width, left->height, c, 0, leftId, 1, layer);
        }
    }
}

extern "C" {

void menuSubAnimAlpha(void) {
    _animAlpha();
}

}

static s32 _animAlpha(void) {
    f32 t = menuGetTotalTime() * (6.2831855f / _cursorSec);
    f32 range = _max_alpha - _min_alpha;
    f32 v;
    f32 c;
    _cursorTimer = t;
    c = (f32)cos(t);
    v = (range * ((1.0f + c) * 0.5f));
    v += _min_alpha;
    if (v > 255.0f) {
        v = 255.0f;
    }
    return (s32)v;
}

extern "C" {

s32 menuSubCheckSelect(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    switch (sprite->id) {
    case 0x39:
    case 0x4B:
        menuSubCheckSelectSub(win, sprite, 0);
        break;
    case 0x3A:
    case 0x4C:
        menuSubCheckSelectSub(win, sprite, 1);
        break;
    }
    return 0;
}

}

static void menuSubCheckSelectSub(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, long value) {
    if (win->pos.selected == value) {
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}

extern "C" {

void menuSubSleep(f32 seconds) {
    f32 elapsed = 0.0f;
    while (elapsed < seconds) {
        GSthreadSwitch();
        elapsed += timeGetLastFrameSec();
    }
}

void menuSubKeyWait(void) {
    while (((GSinputButtonsPressed(1) & GSinputButtonsChanged(1)) & 0x300) == 0) {
        GSthreadSwitch();
    }
}

u32 menuSubCalcColor(u8* a, u8* b) {
    return (u8)((b[0x67] * a[0x93]) / 255) | (((u8)((b[0x66] * a[0x92]) / 255) << 8) | (((u8)((b[0x64] * a[0x90]) / 255) << 24) | ((u8)((b[0x65] * a[0x91]) / 255) << 16)));
}

}

extern "C" {

s32 menuSubOpenSelect_gba(u8 mode, s32* items, s32 count, long x, long y, s32 arg5, s32 arg6, u8 arg7, u8 arg8) {
    s32 result;
    result = 0;
    menuSubCursorAnimeInit();
    menuOpenCustom(0xAE, windowGetActiveID(), &arg5, 0, 0, 6, mode, items, count, arg6, arg7, arg8);
    menuSetPosition(0xAE, x, y);
    do {
        GSthreadSwitch();
        if (menuCB_GetDisconnectedGBA() != 0) {
            result = -2;
            tagWINDOW_WORK* win = windowSearchID(0xAE);
            win->finished = 1;
            win->cancelled = 1;
        }
    } while (windowCheckCursor(0xAE, 0));
    if (result != -2) {
        result = windowGetValue(0xAE);
    }
    menuCloseCustom(0xAE, 0, 1);
    return result;
}

s32 menuSubOpenSelect3(u8 mode, s32* items, s32 count, long x, long y, s32 arg5, s32 arg6, u8 arg7, u8 arg8) {
    s32 result;
    menuSubCursorAnimeInit();
    menuOpenCustom(0xAE, windowGetActiveID(), &arg5, 0, 0, 6, mode, items, count, arg6, arg7, arg8);
    menuSetPosition(0xAE, x, y);
    windowCheckCursor(0xAE, 1);
    result = windowGetValue(0xAE);
    menuCloseCustom(0xAE, 0, 1);
    return result;
}

s32 menuSubOpenSelect2(u8 mode, s32* items, s32 count, long x, long y, s32 arg5, s32 arg6, u8 arg7) {
    s32 result;
    menuSubCursorAnimeInit();
    menuOpenCustom(0xAE, windowGetActiveID(), &arg5, 0, 0, 6, mode, items, count, arg6, arg7, 1);
    menuSetPosition(0xAE, x, y);
    windowCheckCursor(0xAE, 1);
    result = windowGetValue(0xAE);
    menuCloseCustom(0xAE, 0, 1);
    return result;
}

s32 menuSubOpenSelect(u8 mode, s32* items, s32 count, long x, long y, s32 arg5) {
    s32 result;
    menuSubCursorAnimeInit();
    menuOpenCustom(0x59, windowGetActiveID(), &arg5, 0, 0, 3, mode, items, count);
    menuSetPosition(0x59, x, y);
    windowCheckCursor(0x59, 1);
    result = windowGetValue(0x59);
    menuCloseCustom(0x59, 0, 1);
    return result;
}

void menuSubCursorAnimeValGet(f32* out, s32* color) {
    out[0] = _cursorAnimeWork.x;
    out[1] = _cursorAnimeWork.y;
    *color = _cursorAnimeWork.color;
}

void menuSubCursorAnimeMain(void) {
    if (_cursorAnimeWork.x != 0.0f) {
        s16 t = _cursorAnimeWork.time + timeGetLastFrameTime();
        f32 ratio = (f32)t / (f32)_cursorAnimeWork.duration;
        _cursorAnimeWork.time = t;
        _cursorAnimeWork.x = (f32)(s16)((((f32)t * (f32)t) / (f32)_cursorAnimeWork.duration / (f32)_cursorAnimeWork.duration) * (_cursorAnimeWork.toX - _cursorAnimeWork.fromX) + _cursorAnimeWork.fromX);
        _cursorAnimeWork.cur[0] = (s32)(ratio * (f32)(_cursorAnimeWork.to[0] - _cursorAnimeWork.from[0]) + (f32)_cursorAnimeWork.from[0]);
        _cursorAnimeWork.cur[1] = (s32)(ratio * (f32)(_cursorAnimeWork.to[1] - _cursorAnimeWork.from[1]) + (f32)_cursorAnimeWork.from[1]);
        _cursorAnimeWork.cur[2] = (s32)(ratio * (f32)(_cursorAnimeWork.to[2] - _cursorAnimeWork.from[2]) + (f32)_cursorAnimeWork.from[2]);
        _cursorAnimeWork.cur[3] = (s32)(ratio * (f32)(_cursorAnimeWork.to[3] - _cursorAnimeWork.from[3]) + (f32)_cursorAnimeWork.from[3]);
        if (_cursorAnimeWork.x > 0.0f) {
            _cursorAnimeWork.x = 0.0f;
            _cursorAnimeWork.cur[3] = 0xFF;
            _cursorAnimeWork.cur[2] = 0xFF;
            _cursorAnimeWork.cur[1] = 0xFF;
            _cursorAnimeWork.cur[0] = 0xFF;
        }
        _cursorAnimeWork.color = (_cursorAnimeWork.cur[0] << 24) | (_cursorAnimeWork.cur[1] << 16) | (_cursorAnimeWork.cur[2] << 8) | _cursorAnimeWork.cur[3];
    }
    _cursorAnimeWork.sec = _cursorAnimeWork.sec + timeGetLastFrameSec();
}

void menuSubCursorAnimeStart(void) {
    _cursorAnimeWork.x = -8.0f;
    _cursorAnimeWork.y = 0.0f;
    _cursorAnimeWork.toX = 0.0f;
    _cursorAnimeWork.toY = 0.0f;
    _cursorAnimeWork.fromX = -8.0f;
    _cursorAnimeWork.fromY = 0.0f;
    _cursorAnimeWork.color = -0x100;
    _cursorAnimeWork.to[0] = 0xFF;
    _cursorAnimeWork.to[1] = 0xFF;
    _cursorAnimeWork.to[2] = 0xFF;
    _cursorAnimeWork.to[3] = 0xFF;
    _cursorAnimeWork.from[0] = 0xFF;
    _cursorAnimeWork.from[1] = 0xFF;
    _cursorAnimeWork.from[2] = 0xFF;
    _cursorAnimeWork.from[3] = 0;
    _cursorAnimeWork.cur[0] = 0xFF;
    _cursorAnimeWork.cur[1] = 0xFF;
    _cursorAnimeWork.cur[2] = 0xFF;
    _cursorAnimeWork.cur[3] = 0;
    _cursorAnimeWork.sec = 0.0f;
    _cursorAnimeWork.time = 0;
    _cursorAnimeWork.duration = 5;
}

void menuSubCursorAnimeInit(void) {
    memset(&_cursorAnimeWork, 0, 0x30);
    _cursorAnimeWork.color = -1;
    _cursorAnimeWork.x = 0.0f;
    _cursorAnimeWork.y = 0.0f;
}

s32 menuSubGetPokemonSexForFightDisp(s32 pokemon) {
    s32 name;
    u16 id;
    if (!pokemonCheckValid(pokemon)) {
        return 0xFF;
    }
    id = pokemonBiosGetPokemonDataId(pokemon);
    if (id == 0x1D || id == 0x20) {
        void* data = pokemonDataBiosGetPtr(pokemonGetStatus(pokemon, 0, 0x6E, 0));
        if (data != 0) {
            pokemonDataBiosGetName(data);
            name = GSmsgGetGSchar();
            if (GScharCmp(pokemonGetStatus(pokemon, 0, 0x77, 0), name) == 0) {
                return 2;
            }
        }
    }
    return pokemonGetSex(pokemon);
}

s32 menuSubGetPokemonSexForDisp(s32 pokemon) {
    u16 id;
    if (!pokemonCheckValid(pokemon)) {
        return 0xFF;
    }
    id = pokemonBiosGetPokemonDataId(pokemon);
    if (id == 0x1D || id == 0x20) {
        return 2;
    }
    return pokemonGetSex(pokemon);
}

void menuSubOpenColosseumEnter(void) {
    s32 items[3];
    items[0] = *(s32*)((u8*)menuItemBiosGetPtr(0x13, 0x34) + 0x10);
    items[1] = *(s32*)((u8*)menuItemBiosGetPtr(0x13, 0x35) + 0x10);
    items[2] = *(s32*)((u8*)menuItemBiosGetPtr(0x13, 0x36) + 0x10);
    menuSubOpenSelect2(0, items, 3, 0x32, 0x32, 0, 3, 1);
}

s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 arg3) {
    s16 menu;
    s8 result;
    if (arg3 != 0) {
        arg3 = 1;
    }
    switch (type) {
    case 0:
        menu = 0x35;
        break;
    case 1:
        menu = 0x35;
        break;
    default:
    case 0x7F:
        menu = 0x55;
        break;
    }
    menuOpenCustom(menu, windowGetActiveID(), &arg3, 0, 0, 0);
    if (x >= 0 && y >= 0) {
        menuSetPosition(menu, x, y);
    }
    windowCheckCursor(menu, 1);
    result = windowGetValue(menu);
    menuCloseCustom(menu, 0, 1);
    return result;
}

void menuSubOpenYesNoField(void) {
    menuSubOpenYesNo(1, -1, -1, 0);
}

void menuSubCloseNumberInputWait(void) {
    menuCloseSync(2, 1);
}

void menuSubCloseNumberInput(void) {
    menuClose(2);
}

}

static u8 menuSubOpenNumberInputSub(unsigned long type, unsigned long* out, unsigned char mode, short x, short y, bool close, unsigned short* (*fn)(unsigned long)) {
    u8 result = 0;
    tagWINDOW_WORK* win;
    menuOpenCustom(2, windowGetActiveID(), 0, 0, 0, 3, type, mode, fn);
    menuSetPosition(2, x, y);
    windowCheckCursor(2, 1);
    windowGetValue(2);
    win = windowSearchID(2);
    if (win != 0) {
        if (out != 0) {
            *out = win->value;
        }
        if (win->cancelled == 0) {
            result = 1;
        }
        if (close) {
            menuSubCloseNumberInput();
        }
    }
    return result;
}

extern "C" {

u8 menuSubOpenNumberInput(unsigned long type, unsigned long* out, unsigned char mode, short x, short y, bool close) {
    return menuSubOpenNumberInputSub(type, out, mode, x, y, close, 0);
}

u8 menuSubOpenNumberInputID(unsigned long type, unsigned long* out, unsigned short* (*fn)(unsigned long)) {
    return menuSubOpenNumberInputSub(type, out, 1, 0x32, 0x3C, true, fn);
}

u8 menuSubOpenNumberInputDigit(unsigned long type, unsigned long* out) {
    return menuSubOpenNumberInputSub(type, out, 1, 0x32, 0x3C, true, 0);
}

void menuSubDrawTriangle(GSgfxLayerID layer, long x0, long y0, long x1, long y1, long x2, long y2) {
    GSgfxLayer* l = GSgfxLayerFindByID(layer);
    if (l != 0) {
        l->primitive = 0x90;
        l->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
        l->beginSurface(3);
        GXPosition2s16(x0, y0);
        GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
        GXPosition2s16(x1, y1);
        GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
        GXPosition2s16(x2, y2);
        GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
        l->endSurface();
    }
}

void menuSubDrawTile(GSgfxLayerID layer, long x, long y, long w, long h, const u8* color) {
    GSgfxLayer* l = GSgfxLayerFindByID(layer);
    if (l != 0) {
        l->primitive = 0x98;
        l->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
        w += x;
        h += y;
        l->beginSurface(4);
        GXPosition2s16(x, y);
        GXWGFifo.u8 = color[0];
        GXWGFifo.u8 = color[1];
        GXWGFifo.u8 = color[2];
        GXWGFifo.u8 = color[3];
        GXPosition2s16(w, y);
        GXWGFifo.u8 = color[0];
        GXWGFifo.u8 = color[1];
        GXWGFifo.u8 = color[2];
        GXWGFifo.u8 = color[3];
        GXPosition2s16(x, h);
        GXWGFifo.u8 = color[0];
        GXWGFifo.u8 = color[1];
        GXWGFifo.u8 = color[2];
        GXWGFifo.u8 = color[3];
        GXPosition2s16(w, h);
        GXWGFifo.u8 = color[0];
        GXWGFifo.u8 = color[1];
        GXWGFifo.u8 = color[2];
        GXWGFifo.u8 = color[3];
        l->endSurface();
    }
}

void menuSubDrawSimpleWindow(GSgfxLayerID layer, long x, long y, long w, long h) {
    GSgfxLayer* l = GSgfxLayerFindByID(layer);
    if (l != 0) {
        short x0;
        short y0;
        short x1;
        short y1;
        l->primitive = 0x98;
        l->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
        l->beginSurface(4);
        x0 = x - 10;
        y0 = y - 10;
        GXPosition2s16(x0, y0);
        GXParam1s32(0xC0);
        x1 = x + (w + 10);
        y1 = y + (h + 10);
        GXPosition2s16(x1, y0);
        GXParam1s32(0xC0);
        GXPosition2s16(x0, y1);
        GXParam1s32(0xC0);
        GXPosition2s16(x1, y1);
        GXParam1s32(0xC0);
        l->endSurface();
        l->setLineWidth(6, 0);
        l->primitive = 0xB0;
        l->beginSurface(5);
        x0 = x - 10;
        y0 = y - 10;
        GXPosition2s16(x0, y0);
        GXParam1s32(-1);
        GXPosition2s16(x1, y0);
        GXParam1s32(-1);
        GXPosition2s16(x1, y1);
        GXParam1s32(-1);
        GXPosition2s16(x0, y1);
        GXParam1s32(-1);
        GXPosition2s16(x0, y0);
        GXParam1s32(-1);
        l->endSurface();
    }
}

}
