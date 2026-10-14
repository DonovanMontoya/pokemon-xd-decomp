#include <game/menuNameEntryLayout.hpp>

struct Pokemon;
struct MENU_MODEL {
    u8 data[0xEC];
    MENU_MODEL() {}
};

extern "C" {
void GScharCpy(u16 *, u16 *);
u16 *GSmsgGetGSchar(s32);
void GSsndPlayNow(u32);
void msgctrlSetValue(s32, u16 *);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
u16 windowGetKeyTrg(void);
u16 windowGetKeyRepeat(void);
void winSeqSetMenu(s32, s32);
void GSfloorPush(s32);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
Pokemon *heroGetStatus(s32, s32, u16);
Pokemon *fightFloorGetDefPokemonPtr(s32);
u8 pokemonCheckValid(Pokemon *);
u8 menuIsCheck(s32);
void menuSetDisp(s32, s32);
void menuNameEntry(void);
s32 GSmsgGetLength(u32);
u32 GSmsgGetRect(s32);
void GSmsgPrint2(s32, s32, s32, u32, s32);
f32 HSD_Randf(void);
double sin(double);
void menuSpriteBiosGetPtr(s32);
struct MenuSpriteVal {
    u8 reserved0[4];
    s16 unk4;
    s16 unk6;
};
MenuSpriteVal *menuSpriteBiosGetValPtr(void);
void windowDrawSprite2(s32, s32, s32, s32, u32, tagWINDOW_WORK *, s32, s32, s32);
void heroSetStatus(s32, s32, u16 *);
u16 *pokemonBiosGetNicknamePtr(Pokemon *);
void pokemonBiosSetNicknamePtr(Pokemon *, u16 *);
u16 *pcboxGetPokemonBoxName(s32, s8);
void pcboxSetPokemonBoxName(s32, s8, u16 *);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
void menuClose(s32);
void menuCloseSync(s32, s32);
void FlashSystemSetPlayFrameLabel(u32, const char *, const char *);
void FlashSystemSetLoopFlag(u32, s32);
void FlashSystemSetNowFrameLabel(u32, const char *);
void fadeSet(s32, f32);
void fadeCheck(s32);
void menuModelTerm(MENU_MODEL *);
s32 GScharCmp(u16 *, u16 *);
void menuTitleBattleSelectFree(void);
void dbgMenuSetEnable(s32, s32 *, s32 *, s32 *, s32 *, s32 *, f32 *, s32 *);
void GSfloorPop(void);
struct MenuItemInfo {
    u8 reserved0[0xA];
    s16 a;
    s16 b;
};
MenuItemInfo *menuItemBiosGetPtr(s32, s32);
void menuModelInit(MENU_MODEL *, s16, s16);
void menuModelLoad(MENU_MODEL *, s32);
void *peopleInfoBiosGetPtr(s32);
void peopleInfoBiosGetMotion(void *, s32, s32 *, s32 *);
void menuModelSetMotion(MENU_MODEL *, s32);
void menuModelLoadPokemon(MENU_MODEL *, Pokemon *);
void menuModelCheck(MENU_MODEL *, s32);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void menuSubDrawCursorBackAnimeOnOffAuto(tagWINDOW_WORK *, s32, s32, s32, s16, s16, u8, s32);
void windowDrawSprite(s16, s16, tagWINDOW_WORK *, s32, s32, s32);
}

enum SHEET { SHEET_A, SHEET_B };
enum DAKUON_MODE { DAKUON_NONE, DAKUON_VOICED, DAKUON_HALF };
enum GSgfxLayerID { GSGFX_LAYER_DUMMY };

struct SheetDataT {
    u8 flags[4];
    u32 title;
    u32 rows[8];
    u32 pad;
};

static const SheetDataT SheetData[2] = {
    { { 0x0B, 0x57, 0x02, 0x00 }, 0x3B14, { 0x3AFD, 0x3AFE, 0x3AFF, 0x3B00, 0x3BF4, 0x3BF5, 0, 0 }, 0 },
    { { 0x02, 0x3C, 0x57, 0x00 }, 0x3B15, { 0x3B01, 0x3B02, 0x3B03, 0x3B04, 0x3BF6, 0x3BF7, 0, 0 }, 0 },
};

struct BALL_WORK {
    s32 active;
    f32 x;
    f32 y;
    f32 scale;
    f32 maxScale;
    s32 color;
    u8 alpha;
    u8 reserved19[3];
    f32 t;
    f32 life;
};

static BALL_WORK BallWork[30];
struct ModeDataT {
    u32 msg;
    s32 maxLen;
    const u32 *defNames;
    s32 defCount;
};

static const u32 DefKenName[3] = { 0x3B20, 0x3B21, 0x3B22 };
static const u32 DefHizukiName[3] = { 0x3B20, 0x3B21, 0x3B22 };

static const ModeDataT ModeData[7] = {
    { 0x3B11, 7, DefKenName, 3 },
    { 0x3B11, 7, DefHizukiName, 3 },
    { 0x3B12, 10, 0, 0 },
    { 0x3B13, 8, 0, 0 },
    { 0x3B12, 10, 0, 0 },
    { 0x3B12, 10, 0, 0 },
    { 0x3C33, 10, 0, 0 },
};
static const u32 DakuHanTbl[2] = { 0, 0x3B1B };
static s32 Sheet;
static s32 SheetCurX;
static s32 SheetCurY;
static f32 SheetCurAnimTime;
static s32 NameCurX;
static s32 DefSheetCurPosX;
static s32 DefSheetCurPosY;
static s32 DefNamePokemonCurPosX;
static s32 DefNameBoxCurPosX;
static s32 DefNameTrainerCurPosX;
static NAME_ENTRY_WORK NameEntryWork;
static MENU_MODEL MenuModel;

static void ballMain1(BALL_WORK *ball);
static void generateBall(void);
static void ballMain(void);

static s32 getGScharLen(u16 *str);
static u16 getCharSheet(SHEET sheet, int index, int row);
static void putGScharL(GSgfxLayerID layer, int x, int y, u32 color, u16 ch);
static void drawControlCursor(NAME_ENTRY_ARG *arg, tagSPRITE_WORK *sprite);
static void setDefNameText(tagSPRITE_WORK *sprite, u32 id);
static s32 menuNameEntryDrawNameText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, int a, int b);
static s32 pushNameEntryFloor(int a, int b, int c);
static s32 menuNameEntryDrawNameCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, int a, int b);
static s32 chkParam(int mode, int index);
static s32 getName(u16 *dst, int mode, int arg);
static s32 setName(u16 *name, int mode, int arg);
static s32 selectName(u16 *dst, const u32 *list, int count);
static s32 selectLetter(NAME_ENTRY_ARG *arg);
static s32 inputName(u16 *dst, u16 *backup, int mode, int idx, int flag);
static void loadModel(long layer, MENU_MODEL *model, int mode, int idx);
static u16 exchangeDakuon(u16 ch, DAKUON_MODE mode);

extern "C" {
s32 menuNameEntryDrawBkCur(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s16 idx;
    winSpriteSetDisp(sprite, 0);
    idx = window->unk9E;
    if (idx >= 0) {
        menuSubDrawCursorBackAnimeOnOffAuto(window, winSpriteGetLayerID(window, sprite), 0, idx << 5, sprite->unk54,
                                            sprite->unk56, window->unk93, 1);
    }
    return 0;
}

s32 menuNameEntryDrawNameRuleText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    return menuNameEntryDrawNameText(window, sprite, 10, 6);
}

s32 menuNameEntryDrawNameTrainerText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    return menuNameEntryDrawNameText(window, sprite, 7, 0);
}

s32 menuNameEntryDrawNameBoxText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    return menuNameEntryDrawNameText(window, sprite, 8, 3);
}
}

static void drawControlCursor(NAME_ENTRY_ARG *arg, tagSPRITE_WORK *sprite)
{
    s32 x = *arg->unk28;
    s32 y = *arg->unk2C;
    winSpriteSetDisp(sprite, 0);
    if (y > 5 && x > 6) {
        s32 id;
        if (y == 6) {
            id = 0x305;
        } else {
            id = 0x304;
        }
        if (id == sprite->unk6) {
            winSpriteSetDisp(sprite, 1);
        }
    }
}

extern "C" {
s32 menuNameEntryDrawStartCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    drawControlCursor((NAME_ENTRY_ARG *)window->unk68, sprite);
    return 0;
}

s32 menuNameEntryDrawBCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    drawControlCursor((NAME_ENTRY_ARG *)window->unk68, sprite);
    return 0;
}

s32 menuNameEntryDraw50Cursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    winSpriteSetDisp(sprite, 0);
    if (*arg->unk2C < 6) {
        if (*arg->unk28 < 11) {
            windowDrawSprite(*arg->unk28 * 26, *arg->unk2C * 30, window, 0x153, 0, winSpriteGetLayerID(window, sprite));
        }
    } else if (*arg->unk28 < 7) {
        windowDrawSprite(*arg->unk28 * 26, *arg->unk2C * 30, window, 0x153, 0, winSpriteGetLayerID(window, sprite));
    }
    return 0;
}
}

static u16 getCharSheet(SHEET sheet, int index, int row)
{
    u32 id;
    s32 len;
    u16 *p;
    if (sheet < 0 || sheet >= 2) {
        return 0;
    }
    if (row < 0 || row >= 8) {
        return 0;
    }
    id = SheetData[sheet].rows[row];
    if (id == 0) {
        return 0;
    }
    len = GSmsgGetLength(id);
    if (index < 0 || index >= len) {
        return 0;
    }
    p = GSmsgGetGSchar(id);
    if (*p == 0xFFFF) {
        p += 2;
    }
    return p[index];
}

static s32 getGScharLen(u16 *str)
{
    s32 n = 0;
    while (*str != 0) {
        str++;
        n++;
    }
    return n;
}

static s32 confirmName(u16 *name)
{
    s32 answer;
    GSsndPlayNow(0x1D);
    msgctrlSetValue(0x4D, name);
    winMsgOpen(2, 0x3B1A, 1, 0);
    answer = menuSubOpenYesNo(0, 0x2C, 0xC0, 0);
    winMsgClose(1);
    if (answer == 1 || answer == -1) {
        return 0;
    }
    return 1;
}

static u8 backNameCursor(NAME_ENTRY_ARG *arg)
{
    s32 cur = *arg->unk34;
    s32 prev;
    if (cur <= 0) {
        return 0;
    }
    prev = cur - 1;
    arg->unk18[prev] = 0;
    *arg->unk34 = prev;
    return 1;
}

static s32 getSpchar(u16 c)
{
    u16 *p = GSmsgGetGSchar(0x3B1E);
    if (c == *p) {
        return 0;
    }
    return 6;
}

static void change50Sheet(NAME_ENTRY_ARG *arg)
{
    s32 *sheet = arg->unk24;
    s32 next = *sheet;
    next++;
    if (next >= 2) {
        next = 0;
    }
    *sheet = next;
}

extern "C" {
void menuNameEntryButton(void)
{
}
}

static s32 chkValidName(u16 *name)
{
    s32 len = getGScharLen(name);
    s32 count;
    s32 i;
    u16 *blank;
    if (len <= 0) {
        return 0;
    }
    blank = GSmsgGetGSchar(0x3B1D);
    count = 0;
    for (i = 0; i < len; i++) {
        if (*name != *blank) {
            break;
        }
        count++;
        name++;
    }
    if (count >= len) {
        return 0;
    }
    return 1;
}

static void setDefNameText(tagSPRITE_WORK *sprite, u32 id)
{
    msgctrlSetValue(0x37, GSmsgGetGSchar(id));
    sprite->unk4C = 0x4276;
}

extern "C" {
s32 menuNameEntrySelectDrawSelText3(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 **p = (s32 **)window->unk68;
    setDefNameText(sprite, (*p)[2]);
    return 0;
}

s32 menuNameEntrySelectDrawSelText2(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 **p = (s32 **)window->unk68;
    setDefNameText(sprite, (*p)[1]);
    return 0;
}

s32 menuNameEntrySelectDrawSelText1(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 **p = (s32 **)window->unk68;
    setDefNameText(sprite, (*p)[0]);
    return 0;
}

void menuNameEntrySelectButton(tagWINDOW_WORK *window)
{
    u16 key = windowGetKeyTrg();
    if ((key & 0x20) != 0) {
        window->unkA5 = 1;
        window->unkA4 = 1;
    }
    if ((key & 0x10) != 0) {
        window->unkA4 = 1;
    }
}

s32 menuNameEntrySelectCtrl(tagWINDOW_WORK *window)
{
    switch (window->unk1) {
    case 0:
        if (window->unk2 == 0) {
            winSeqSetMenu(window->unk4, 0x58);
            window->unk2 = 1;
        }
        break;
    case 3:
        if (window->unk2 == 0) {
            winSeqSetMenu(window->unk4, 0x5C);
            window->unk2 = 1;
        }
        break;
    }
    return 0;
}

void menuNameEntryGetLastName(u16 *dst)
{
    GScharCpy(dst, NameEntryWork.name);
}

s32 menuNameEntryOpenNoFade(int a, int b)
{
    return pushNameEntryFloor(a, b, 0);
}
}

static s32 chkParam(int mode, int index)
{
    s32 ok = 1;
    switch (mode) {
    case 0:
    case 1:
    case 5:
    case 6:
        break;
    case 2:
        if (pokemonCheckValid(heroGetStatus(0, 3, index)) == 0) {
            ok = 0;
        }
        break;
    case 3:
        if (index < 0 || index >= 8) {
            ok = 0;
        }
        break;
    case 4:
        if (pokemonCheckValid(fightFloorGetDefPokemonPtr(0)) == 0) {
            ok = 0;
        }
        break;
    default:
        ok = 0;
        break;
    }
    return ok;
}

extern "C" {
s32 menuNameEntryCall(int mode, int index)
{
    if (chkParam(mode, index) == 0) {
        return 0;
    }
    NameEntryWork.name[0] = 0;
    NameEntryWork.unk18 = mode;
    NameEntryWork.unk1C = index;
    NameEntryWork.unk20 = 0;
    NameEntryWork.unk28 = 0;
    menuNameEntry();
    return NameEntryWork.unk20;
}
}

static s32 pushNameEntryFloor(int mode, int index, int fade)
{
    if (chkParam(mode, index) == 0) {
        return 0;
    }
    NameEntryWork.name[0] = 0;
    NameEntryWork.unk18 = mode;
    NameEntryWork.unk1C = index;
    NameEntryWork.unk20 = 0;
    NameEntryWork.unk24 = fade;
    NameEntryWork.unk28 = 1;
    GSfloorPush(0x390);
    if (fade == 0) {
        floorSetFadeScript(0, 0x05960008);
    }
    floorWaitForChange();
    return NameEntryWork.unk20;
}

extern "C" {
s32 menuNameEntryOpen(int mode, int index)
{
    s32 ids[4] = { 0x37, 0x40, 0x38, 0x41 };
    s32 *p;
    s32 *base;
    int i;
    s32 result;
    base = ids;
    for (p = base, i = 0; i < 4; p++, i++) {
        if (menuIsCheck(*p) != 0) {
            menuSetDisp(*p, 0);
        }
    }
    result = pushNameEntryFloor(mode, index, 1);
    for (int j = 0; j < 4; base++, j++) {
        if (menuIsCheck(*base) != 0) {
            menuSetDisp(*base, 1);
        }
    }
    return result;
}

s32 menuNameEntryCtrl(tagWINDOW_WORK *window)
{
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    switch (window->unk1) {
    case 0:
        if (window->unk2 == 0) {
            winSeqSetMenu(window->unk4, 0x58);
            *arg->unk30 = 0.0f;
            window->unk2 = 1;
        }
        break;
    case 2:
    {
        f32 *fp = arg->unk30;
        f32 v = 0.033333335f;
        v = *fp + v;
        *fp = v;
        if (v >= 1.0f) {
            fp = arg->unk30;
            *fp -= 1.0f;
        }
        break;
    }
    case 3:
        if (window->unk2 == 0) {
            winSeqSetMenu(window->unk4, 0x5C);
            window->unk2 = 1;
        }
        break;
    }
    return 0;
}
}

static void putGScharL(GSgfxLayerID layer, int x, int y, u32 color, u16 ch)
{
    u16 buf[2];
    buf[0] = ch;
    buf[1] = 0;
    msgctrlSetValue(0x37, buf);
    {
        s32 w = 0x1B - (s16)(GSmsgGetRect(0x4275) >> 16);
        GSmsgPrint2(layer, x + w / 2, y, color, 0x4275);
    }
}

extern "C" {
s32 menuNameEntryDrawXButtonText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 next = *((NAME_ENTRY_ARG *)window->unk68)->unk24 + 1;
    if (next >= 2) {
        next -= 2;
    }
    if (next >= 0 && next < 2) {
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, window->unk93 | 0xFFFFFF00, SheetData[next].title);
    }
    return 0;
}

s32 menuNameEntryDraw50Text(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    int x;
    int y;
    int col;
    int row;
    s32 sheet;
    u16 ch;
    row = 0;
    y = 0;
    sheet = *((NAME_ENTRY_ARG *)window->unk68)->unk24;
    do {
        col = 0;
        x = -2;
        while ((ch = getCharSheet((SHEET)sheet, col, row)) != 0) {
            putGScharL((GSgfxLayerID)winSpriteGetLayerID(window, sprite), x, y, window->unk93 | 0xFFFFFF00, ch);
            x += 26;
            col++;
        }
        y += 30;
        row++;
    } while (row < 8);
    return 0;
}
}

static void ballMain1(BALL_WORK *ball)
{
    if (ball->active != 0) {
        f32 r;
        f32 t = ball->t;
        t += 1.0f;
        ball->t = t;
        if (t >= ball->life) {
            ball->active = 0;
        }
        r = ball->t / ball->life;
        ball->scale = ball->maxScale * r;
        ball->alpha = 128.0f * (1.0f - r);
    }
}

static void generateBall(void)
{
    if (!(HSD_Randf() > 0.1f)) {
        int i;
        for (i = 0; i < 30; i++) {
            if (BallWork[i].active == 0) {
                break;
            }
        }
        if (i < 30) {
            BallWork[i].active = 1;
            BallWork[i].x = 640.0f * HSD_Randf();
            BallWork[i].y = 480.0f * HSD_Randf();
            BallWork[i].scale = 0.001f;
            BallWork[i].maxScale = 1.999f * HSD_Randf() + 0.001f;
            BallWork[i].color = -256;
            BallWork[i].alpha = 0x80;
            BallWork[i].t = 0.0f;
            BallWork[i].life = 60.0f * HSD_Randf() + 120.0f;
        }
    }
}

static void ballMain(void)
{
    int i;
    generateBall();
    for (i = 0; i < 30; i++) {
        if (BallWork[i].active != 0) {
            ballMain1(&BallWork[i]);
        }
    }
}

extern "C" {
s32 menuNameEntryBackCtrl(tagWINDOW_WORK *window)
{
    int k;
    int i;
    switch (window->unk1) {
    case 0:
        if (window->unk2 == 0) {
            k = 0;
            for (i = 0; i < 30; i++) {
                BallWork[i].active = 0;
            }
            do {
                ballMain();
                k++;
            } while (k < 600);
            window->unk2 = 1;
        }
        break;
    case 2:
        ballMain();
        break;
    case 3:
        if (window->unk2 == 0) {
            window->unk2 = 1;
        }
        break;
    }
    return 0;
}

s32 menuNameEntryBackDrawBall(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    int i;
    MenuSpriteVal *val;
    s16 w;
    s16 h;
    menuSpriteBiosGetPtr(0x1E);
    val = menuSpriteBiosGetValPtr();
    w = val->unk4;
    h = val->unk6;
    for (i = 0; i < 30; i++) {
        if (BallWork[i].active != 0) {
            f32 sx = (f32)w * BallWork[i].scale;
            f32 sy = (f32)h * BallWork[i].scale;
            f32 cx = BallWork[i].x - sx / 2.0f;
            f32 cy = BallWork[i].y - sy / 2.0f;
            u32 color = BallWork[i].color | BallWork[i].alpha;
            windowDrawSprite2((s32)(0.5f + cx), (s32)(0.5f + cy), (s32)(0.5f + sx), (s32)(0.5f + sy), color, window, 0x1E, 0,
                              winSpriteGetLayerID(window, sprite));
        }
    }
    return 0;
}
}

static s32 getName(u16 *dst, int mode, int arg)
{
    switch (mode) {
    case 0:
        arg = (int)GSmsgGetGSchar(DefKenName[0]);
        break;
    case 1:
        arg = (int)GSmsgGetGSchar(DefHizukiName[0]);
        break;
    case 2: {
        Pokemon *p = heroGetStatus(0, 3, arg);
        if (pokemonCheckValid(p) == 0) {
            arg = 0;
        } else {
            arg = (int)pokemonBiosGetNicknamePtr(p);
        }
        break;
    }
    case 5:
        arg = (int)pokemonBiosGetNicknamePtr((Pokemon *)arg);
        break;
    case 3:
        arg = (int)pcboxGetPokemonBoxName(0, arg);
        break;
    case 4: {
        Pokemon *p = fightFloorGetDefPokemonPtr(0);
        if (pokemonCheckValid(p) == 0) {
            arg = 0;
        } else {
            arg = (int)pokemonBiosGetNicknamePtr(p);
        }
        break;
    }
    case 6:
        break;
    default:
        arg = 0;
        break;
    }
    if (arg == 0) {
        return 0;
    }
    GScharCpy(dst, (u16 *)arg);
    return 1;
}

static s32 setName(u16 *name, int mode, int arg)
{
    Pokemon *p;
    s32 ok = 1;
    switch (mode) {
    case 0:
        break;
    case 1:
        heroSetStatus(0, 0x17, name);
        break;
    case 2: {
        p = heroGetStatus(0, 3, arg);
        if (pokemonCheckValid(p) == 0) {
            ok = 0;
        } else {
            pokemonBiosSetNicknamePtr(p, name);
        }
        break;
    }
    case 5:
        pokemonBiosSetNicknamePtr((Pokemon *)arg, name);
        break;
    case 3:
        pcboxSetPokemonBoxName(0, arg, name);
        break;
    case 4: {
        p = fightFloorGetDefPokemonPtr(0);
        if (pokemonCheckValid(p) == 0) {
            ok = 0;
        } else {
            pokemonBiosSetNicknamePtr(p, name);
        }
        break;
    }
    case 6:
        GScharCpy((u16 *)arg, name);
        break;
    default:
        ok = 0;
        break;
    }
    return ok;
}

static s32 selectName(u16 *dst, const u32 *list, int count)
{
    s32 sel;
    s32 ok;
    u16 *chosen;
    s32 args[2];
    s32 *pargs = args;
    for (;;) {
        args[0] = (s32)list;
        args[1] = count;
        sel = menuOpenCustom(0x65, windowGetActiveID(), 0, 0, 1, 1, pargs);
        if (sel == 0) {
            GSsndPlayNow(0x11);
            ok = 0;
            break;
        }
        if (sel == 4 || sel == -1) {
            GSsndPlayNow(0x11);
            ok = 0;
            break;
        }
        chosen = GSmsgGetGSchar(list[sel - 1]);
        if (confirmName(chosen) != 0) {
            ok = 1;
            break;
        }
    }
    menuClose(0x65);
    menuCloseSync(0x65, 1);
    if (ok != 0) {
        GScharCpy(dst, chosen);
        return 0;
    }
    if (sel != 0) {
        return 2;
    }
    return 1;
}

extern "C" {
s32 menuNameEntryCursor(tagWINDOW_WORK *window)
{
    u16 rep = windowGetKeyRepeat();
    u16 trg = windowGetKeyTrg();
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    if ((trg & 0x40) != 0) {
        change50Sheet(arg);
        GSsndPlayNow(0x14);
        return 0;
    }
    if ((trg & 0x10) != 0) {
        if (selectLetter(arg) != 0) {
            window->unkA4 = 1;
            return 0;
        }
        if (getGScharLen(arg->unk18) >= ModeData[arg->unk1C].maxLen) {
            *arg->unk28 = 10;
            *arg->unk2C = 7;
        }
        return 0;
    }
    if ((trg & 0x20) != 0) {
        if (backNameCursor(arg) != 0) {
            GSsndPlayNow(0x12);
        }
        return 0;
    }
    if ((trg & 0x400) != 0) {
        change50Sheet(arg);
        GSsndPlayNow(0x14);
        return 0;
    }
    if ((trg & 0x800) != 0) {
        window->unkA4 = 1;
        return 0;
    }
    if ((rep & 8) != 0) {
        s32 v = *arg->unk28 + 1;
        if (*arg->unk2C < 6) {
            if (v < 11) {
                GSsndPlayNow(0x10);
            } else {
                v = 10;
            }
        } else if (v > 7) {
            v = 7;
        } else {
            GSsndPlayNow(0x10);
        }
        *arg->unk28 = v;
    }
    if ((rep & 4) != 0) {
        s32 v = *arg->unk28 - 1;
        if (*arg->unk2C > 5 && v > 6) {
            v = 6;
        }
        if (v < 0) {
            v = 0;
        } else {
            GSsndPlayNow(0x10);
        }
        *arg->unk28 = v;
    }
    if ((rep & 2) != 0) {
        s32 v = *arg->unk2C;
        if (*arg->unk28 >= 11) {
            if (v == 1) {
                v = v + 2;
            } else {
                v = v + 1;
            }
        } else {
            v = v + 1;
        }
        if (v >= 8) {
            v = 7;
        } else {
            GSsndPlayNow(0x10);
        }
        *arg->unk2C = v;
    }
    if ((rep & 1) != 0) {
        s32 v = *arg->unk2C;
        if (*arg->unk28 >= 11) {
            if (v == 2) {
                v = v - 2;
            } else {
                v = v - 1;
            }
        } else {
            v = v - 1;
        }
        if (v < 0) {
            v = 0;
        } else {
            GSsndPlayNow(0x10);
        }
        *arg->unk2C = v;
    }
    return 0;
}
}

static u16 exchangeDakuon(u16 ch, DAKUON_MODE mode)
{
    int cur;
    const u32 *t;
    s32 len;
    u16 *p;
    int j;
    for (cur = 0, t = DakuHanTbl; cur < 2; t++, cur++) {
        if (*t != 0) {
            len = GSmsgGetLength(*t);
            p = GSmsgGetGSchar(*t) + 1;
            for (j = 1; j < len; j += 2, p += 2) {
                if (*p == ch) {
                    break;
                }
            }
            if (j < len) {
                break;
            }
        }
    }
    if (cur >= 2) {
        cur = 0;
    }
    if (cur == mode) {
        return ch;
    }
    switch (cur) {
    case 1:
        ch = p[-1];
        break;
    default:
        break;
    }
    if (mode == 0) {
        return ch;
    }
    len = GSmsgGetLength(DakuHanTbl[mode]);
    p = GSmsgGetGSchar(DakuHanTbl[mode]);
    for (j = 0; j < len; j += 2, p += 2) {
        if (*p == ch) {
            break;
        }
    }
    if (j >= len) {
        return 0;
    }
    return p[1];
}

static s32 selectLetter(NAME_ENTRY_ARG *arg)
{
    u16 ch;
    s32 done = 0;
    u32 snd = 0;
    s32 kind;
    s32 x = *arg->unk28;
    s32 y = *arg->unk2C;
    if (y > 5 && x > 6) {
        switch (y) {
        case 7:
            kind = 5;
            break;
        default:
            kind = 4;
            break;
        }
    } else {
        ch = getCharSheet((SHEET)*arg->unk24, x, y);
        if (ch == 0) {
            ch = *GSmsgGetGSchar(0x3B1D);
        }
        kind = getSpchar(ch);
    }
    switch (kind) {
    case 1:
    case 2: {
        DAKUON_MODE dm;
        s32 idx;
        if (kind == 1) {
            dm = (DAKUON_MODE)1;
        } else {
            dm = (DAKUON_MODE)1;
        }
        idx = *arg->unk34 - 1;
        if (idx >= 0) {
            u16 *buf = arg->unk18;
            s32 off = idx * 2;
            u16 r = exchangeDakuon(*(u16 *)((u8 *)buf + off), dm);
            if (r != 0) {
                *(u16 *)((u8 *)buf + off) = r;
            }
        }
        snd = 0x11;
        break;
    }
    case 4:
        if (backNameCursor(arg) != 0) {
            snd = 0x12;
        }
        break;
    case 5:
        done = 1;
        break;
    case 3:
        change50Sheet(arg);
        snd = 0x14;
        break;
    case 0:
        ch = *GSmsgGetGSchar(0x3B1D);
    default: {
        s32 cur;
        s32 maxLen;
        s32 next;
        maxLen = ModeData[arg->unk1C].maxLen;
        cur = *arg->unk34;
        u16 *p;
        if (cur >= maxLen) {
            cur = maxLen - 1;
        }
        next = cur + 1;
        p = (u16 *)((u8 *)arg->unk18 + cur * 2);
        p[0] = ch;
        p[1] = 0;
        if (next >= maxLen + 1) {
            next = maxLen;
        }
        snd = 0x11;
        *arg->unk34 = next;
        break;
    }
    }
    if (snd != 0) {
        GSsndPlayNow(snd);
    }
    return done;
}

extern "C" {
s32 menuNameEntryDrawNamePokemonText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 mode = ((NAME_ENTRY_ARG *)window->unk68)->unk1C;
    if (mode == 6) {
        return 0;
    }
    if (mode == 3) {
        return 0;
    }
    if (mode == 0) {
        return 0;
    }
    return menuNameEntryDrawNameText(window, sprite, 10, mode);
}

void menuNameEntryDrawNameTrainerCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 mode = ((NAME_ENTRY_ARG *)window->unk68)->unk1C;
    if (mode == 6) {
        menuNameEntryDrawNameCursor(window, sprite, 10, 6);
    } else if (mode == 3) {
        menuNameEntryDrawNameCursor(window, sprite, 8, 3);
    } else if (mode == 2) {
        menuNameEntryDrawNameCursor(window, sprite, 10, 2);
    } else if (mode == 4) {
        menuNameEntryDrawNameCursor(window, sprite, 10, 4);
    } else if (mode == 5) {
        menuNameEntryDrawNameCursor(window, sprite, 10, 5);
    } else {
        menuNameEntryDrawNameCursor(window, sprite, 7, 0);
    }
}
}

static s32 menuNameEntryDrawNameText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, int a, int b)
{
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    s32 mode = arg->unk1C;
    if (mode == 1) {
        if (b == 0) {
            sprite->unk67 = 0xFF;
        } else {
            sprite->unk67 = 0;
        }
    } else if (mode != b) {
        sprite->unk67 = 0;
    } else {
        sprite->unk67 = 0xFF;
    }
    if (sprite->unk67 != 0) {
        int n = 0;
        int x = 0;
        u16 ch;
        u16 *p = arg->unk18;
        while ((ch = *p) != 0) {
            putGScharL((GSgfxLayerID)winSpriteGetLayerID(window, sprite), x, 0, window->unk93 | 0xFFFFFF00, ch);
            x += 26;
            n++;
            p++;
        }
        if (n < ModeData[arg->unk1C].maxLen && window->unkA4 == 0) {
            u16 ch2 = getCharSheet((SHEET)*arg->unk24, *arg->unk28, *arg->unk2C);
            if (ch2 != 0 && getSpchar(ch2) == 6) {
                f32 *fp = arg->unk30;
                f32 sv = sin(2.0f * (3.14f * *fp));
                putGScharL((GSgfxLayerID)winSpriteGetLayerID(window, sprite), n * 26, 0, (u8)(128.0f * (1.0f + sv)) | 0xFFFFFF00, ch2);
            }
        }
        sprite->unk67 = 0xFF;
    }
    return 0;
}

static s32 inputName(u16 *dst, u16 *backup, int mode, int idx, int flag)
{
    NAME_ENTRY_ARG arg;
    s32 done = 0;
    s32 ok;
    u16 *chosen;
    GScharCpy(arg.name, backup);
    *dst = 0;
    arg.unk18 = dst;
    arg.unk1C = mode;
    arg.unk20 = idx;
    Sheet = 0;
    arg.unk24 = &Sheet;
    SheetCurX = 0;
    arg.unk28 = &SheetCurX;
    SheetCurY = 0;
    arg.unk2C = &SheetCurY;
    SheetCurAnimTime = 0.0f;
    arg.unk30 = &SheetCurAnimTime;
    NameCurX = 0;
    arg.unk34 = &NameCurX;
    arg.unk38 = &DefSheetCurPosX;
    arg.unk3C = &DefSheetCurPosY;
    arg.unk40 = &DefNamePokemonCurPosX;
    arg.unk44 = &DefNameBoxCurPosX;
    arg.unk48 = &DefNameTrainerCurPosX;
    dbgMenuSetEnable(0, &DefNameBoxCurPosX, &DefNamePokemonCurPosX, &DefSheetCurPosY, &DefSheetCurPosX, &NameCurX,
                     &SheetCurAnimTime, &SheetCurY);
    while (done == 0) {
        menuOpenCustom(0x66, windowGetActiveID(), 0, 0, 1, 1, &arg);
        if (chkValidName(arg.unk18) != 0) {
            chosen = arg.unk18;
        } else {
            chosen = arg.name;
        }
        ok = confirmName(chosen);
        if (flag == 0) {
            done = 1;
            if (ok == 0) {
                NameEntryWork.name[0] = 0;
            }
        } else if (ok != 0) {
            done = 1;
        }
    }
    dbgMenuSetEnable(1, 0, 0, 0, 0, 0, 0, 0);
    menuClose(0x66);
    menuCloseSync(0x66, 1);
    if (ok != 0) {
        GScharCpy(NameEntryWork.name, chosen);
        return 1;
    }
    return 0;
}

extern "C" {
void menuNameEntry(void)
{
    u16 backup[12];
    s32 again;
    s32 args[2];
    if (getName(backup, NameEntryWork.unk18, NameEntryWork.unk1C) == 0) {
        backup[0] = 0;
    }
    loadModel(0x68, &MenuModel, NameEntryWork.unk18, NameEntryWork.unk1C);
    FlashSystemSetPlayFrameLabel(0x22063000, "start", "end");
    FlashSystemSetLoopFlag(0x22063000, 0);
    FlashSystemSetNowFrameLabel(0x22063000, "start");
    args[0] = NameEntryWork.unk18;
    args[1] = NameEntryWork.unk1C;
    menuOpenCustom(0x68, windowGetActiveID(), 0, 0, 1, 1, args);
    if (NameEntryWork.unk28 == 0) {
        fadeSet(2, 0.5f);
        fadeCheck(1);
    }
    if (ModeData[NameEntryWork.unk18].defCount > 0) {
        again = 1;
        while (again != 0) {
            const ModeDataT *md = &ModeData[NameEntryWork.unk18];
            switch (selectName(NameEntryWork.name, md->defNames, md->defCount)) {
            case 1:
                if (inputName(NameEntryWork.name, backup, NameEntryWork.unk18, NameEntryWork.unk1C, 0) != 0) {
                    again = 0;
                }
                break;
            case 2:
                again = 0;
                break;
            default:
                again = 0;
                break;
            }
        }
    } else {
        inputName(NameEntryWork.name, backup, NameEntryWork.unk18, NameEntryWork.unk1C, 1);
    }
    fadeSet(3, 0.5f);
    fadeCheck(1);
    menuModelTerm(&MenuModel);
    menuClose(0x68);
    menuCloseSync(0x68, 1);
    setName(NameEntryWork.name, NameEntryWork.unk18, NameEntryWork.unk1C);
    if (GScharCmp(NameEntryWork.name, backup) == 0) {
        NameEntryWork.unk20 = 0;
    } else {
        NameEntryWork.unk20 = 1;
    }
    if (NameEntryWork.unk18 == 0) {
        menuTitleBattleSelectFree();
    }
    if (NameEntryWork.unk28 != 0) {
        GSfloorPop();
        if (NameEntryWork.unk24 != 0) {
            floorSetFadeScript(0, 0x05960008);
        } else {
            floorSetFadeScript(0, 0);
        }
    }
}
}

static void loadModel(long layer, MENU_MODEL *model, int mode, int idx)
{
    s32 tbl[4] = { 0x16C90400, 0x16C70400, 0, 0x10560400 };
    s32 motion;
    s32 dummy;
    s32 itemId;
    MenuItemInfo *info;
    switch (mode) {
    case 2:
    case 4:
    case 5:
        itemId = 0x280;
        break;
    case 3:
    case 6:
    default:
        itemId = 0x27F;
        break;
    }
    info = menuItemBiosGetPtr(layer, itemId);
    menuModelInit(model, info->a, info->b);
    switch (mode) {
    case 0:
    case 1: {
        s32 id = tbl[mode];
        menuModelLoad(model, id);
        peopleInfoBiosGetMotion(peopleInfoBiosGetPtr(id), 1, &motion, &dummy);
        menuModelSetMotion(model, motion);
        break;
    }
    case 2: {
        Pokemon *p = heroGetStatus(0, 3, idx);
        if (pokemonCheckValid(p) != 0) {
            menuModelLoadPokemon(model, p);
        }
        break;
    }
    case 5:
        menuModelLoadPokemon(model, (Pokemon *)idx);
        break;
    case 3:
        menuModelLoad(model, tbl[mode]);
        break;
    case 4: {
        Pokemon *p = fightFloorGetDefPokemonPtr(0);
        if (pokemonCheckValid(p) != 0) {
            menuModelLoadPokemon(model, p);
        }
        break;
    }
    case 6:
        break;
    }
    menuModelCheck(model, 1);
}
