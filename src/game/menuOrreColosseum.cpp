#include <game/menuOrreColosseumLayout.hpp>

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_NONE,
    MENU_POKEMON_CB_PREV,
    MENU_POKEMON_CB_NEXT
};

extern "C" {
u8 GSfloorIsPop(void);
u8 GSfloorIsPush(void);
void GSfloorPush(s32);
void floorWaitForChange(void);
void fightFreeResourceID(s32, u32);
void fightReadResourceID(s32, u32);
void *fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetFightTrainerDataId(void *, s32);
void fightTrainerCreateFightTrainerDataIdToHero(u16, s32, Hero *, u16);
Hero *fightGetMenuCtrlHero(void);
Pokemon *heroBiosGetPokemonPtr(Hero *, u16);
s32 menuFaceGetID(Pokemon *);
u8 pokemonBiosGetLevel(Pokemon *);
u16 *pokemonBiosGetNicknamePtr(Pokemon *);
s32 pokemonGetSoubiItemDataId(Pokemon *);
s32 menuSubGetPokemonSexForFightDisp(Pokemon *);
Hero *savedataGetStatus(s32, s32);
void *memcpy(void *, const void *, u32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s32 menuSubOpenSelect2(s32, s32 *, s32, s32, s32, s32, s32, s32);
struct MenuOrreKey {
    u16 unk0;
    u16 unk2;
    u16 unk4;
};
struct MenuOrreItem {
    u8 reserved0[0xA];
    s16 unkA;
};
MenuOrreKey *windowGetKeyInfo(void);
u16 *heroBiosGetNamePtr(Hero *);
void msgctrlSetValue(s32, void *);
MenuOrreItem *menuItemBiosGetPtr(s32, s16);
u32 GSmsgGetRect(s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSmsgPrint2(s32, s16, s16, u32, s32);
s32 fightTrainerDB_GetName(u16);
void *GSmsgGetGSchar(u16);
void windowDrawSprite2(s16, s16, s16, s16, u32, tagWINDOW_WORK *, u16, s32, s32);
}

void *operator new(unsigned long);
void operator delete(void *);

static Hero _orreHero;
static u16 _deckNumber;
static u16 _fightresult;
static menuOrre *pOrre;
static s16 _loadFaceCount;

static Pokemon *_GetTemochiPokemonPtr(u16 index);

extern "C" {
void menuOrreExit(void)
{
    if (pOrre != 0) {
        pOrre->Release();
        if (pOrre != 0) {
            delete pOrre;
        }
        pOrre = 0;
    }
    fightFreeResourceID(0x842, 0x184C3400);
}

void menuOrreMain(void)
{
    if (pOrre != 0) {
        pOrre->Main();
    }
}

void menuOrreInit(void)
{
    if (GSfloorIsPop() == 0) {
        pOrre = new menuOrre;
        if (pOrre != 0) {
            pOrre->Init();
        }
    }
}

u16 menuOrreColosseumGetResult(void)
{
    return _fightresult;
}

void menuOrreColosseum(u16 deck)
{
    _deckNumber = deck;
    _fightresult = 0;
    GSfloorPush(0x38A);
    floorWaitForChange();
}

s32 menuOrreMenuHook(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    if (pOrre != 0) {
        return pOrre->Hook(window, sprite);
    }
    return 0;
}

void menuOrreCtrl(tagWINDOW_WORK *window)
{
    if (pOrre != 0) {
        pOrre->Ctrl(window);
    }
}

void menuOrreButton(tagWINDOW_WORK *window)
{
    if (pOrre != 0) {
        pOrre->Button(window);
    }
}
}

void menuOrre::Release()
{
}

s32 menuOrre::GetDeckPokemonFaceID(u16 index)
{
    return menuFaceGetID(GetDeckPokemonPtr(index));
}

u8 menuOrre::GetDeckPokemonLevel(u16 index)
{
    return pokemonBiosGetLevel(GetDeckPokemonPtr(index));
}

s32 menuOrre::GetDeckPokemonMochimono(u16 index)
{
    return pokemonGetSoubiItemDataId(GetDeckPokemonPtr(index));
}

u16 *menuOrre::GetDeckPokemonName(u16 index)
{
    return pokemonBiosGetNicknamePtr(GetDeckPokemonPtr(index));
}

Pokemon *menuOrre::GetDeckPokemonPtr(u16 index)
{
    return heroBiosGetPokemonPtr(GetHeroPtr(1), index);
}

s32 menuOrre::GetDeckPokemonSex(u16 index)
{
    return menuSubGetPokemonSexForFightDisp(GetDeckPokemonPtr(index));
}

s32 menuOrre::GetTemochiPokemonFaceID(u16 index)
{
    return menuFaceGetID(GetTemochiPokemonPtr(index));
}

u8 menuOrre::GetTemochiPokemonLevel(u16 index)
{
    return pokemonBiosGetLevel(GetTemochiPokemonPtr(index));
}

s32 menuOrre::GetTemochiPokemonMochimono(u16 index)
{
    return pokemonGetSoubiItemDataId(GetTemochiPokemonPtr(index));
}

u16 *menuOrre::GetTemochiPokemonName(u16 index)
{
    return pokemonBiosGetNicknamePtr(GetTemochiPokemonPtr(index));
}

Pokemon *menuOrre::GetTemochiPokemonPtr(u16 index)
{
    return heroBiosGetPokemonPtr(GetHeroPtr(0), index);
}

s32 menuOrre::GetTemochiPokemonSex(u16 index)
{
    return menuSubGetPokemonSexForFightDisp(GetTemochiPokemonPtr(index));
}

static Pokemon *_GetTemochiPokemonPtr(u16 index)
{
    if (pOrre != 0) {
        return pOrre->GetTemochiPokemonPtr(index);
    }
    return 0;
}

static Pokemon *_PokemonStatusDisp_CallBack(Pokemon *pokemon, MENU_POKEMON_CB_TYPE type, long arg)
{
    Pokemon *result = 0;
    switch (type) {
    case MENU_POKEMON_CB_PREV: {
        u32 cur = *(u16 *)arg;
        if (cur == 0) {
            return pokemon;
        }
        (*(u16 *)arg)--;
        result = _GetTemochiPokemonPtr(*(u16 *)arg);
        break;
    }
    case MENU_POKEMON_CB_NEXT: {
        u32 cur = *(u16 *)arg;
        if (cur == 5) {
            return pokemon;
        }
        (*(u16 *)arg)++;
        result = _GetTemochiPokemonPtr(*(u16 *)arg);
        break;
    }
    }
    return result;
}

void menuOrre::Init()
{
    isPush = GSfloorIsPush();
    InitSub();
}

void menuOrre::InitSub()
{
    fightReadResourceID(0x842, 0x184C3400);
    deckNumber = _deckNumber;
    trainerDataId = fightEncountDataBiosGetFightTrainerDataId(fightEncountDataBiosGetPtr(deckNumber), 1);
    fightTrainerCreateFightTrainerDataIdToHero(trainerDataId, 0, &_orreHero, deckNumber);
    Hero *ctrlHero = fightGetMenuCtrlHero();
    memcpy(ctrlHero, GetHeroPtr(0), sizeof(Hero));
    maxLevel = GetTemochiMaxPokemonLevel();
    CreatePokemonList();
}

Hero *menuOrre::GetHeroPtr(u8 flag)
{
    if (flag != 0) {
        return &_orreHero;
    }
    return savedataGetStatus(0, 2);
}

u8 menuOrre::GetTemochiMaxPokemonLevel()
{
    u8 max = 0;
    u16 i;
    for (i = 0; i < 6; i++) {
        u8 level = GetTemochiPokemonLevel(i);
        if (max < level) {
            max = level;
        }
    }
    return max;
}

bool menuOrre::ConfirmPokemon()
{
    bool ok;
    winMsgOpen(2, 0xFFFF - 0x752E, 1, 1);
    if (menuSubOpenYesNo(0, 0x40, 0xC8, 0) == 0) {
        ok = true;
    } else {
        ok = false;
    }
    winMsgClose(1);
    return ok;
}

s32 menuOrre::SelectPokemon(u16 index, bool flag)
{
    s32 a[3] = { 0x8ACE, 0x8ACF, 0x8AD0 };
    s32 b[3] = { 0x8AF1, 0x8ACF, 0x8AD0 };
    if (flag) {
        return menuSubOpenSelect2(0, b, 3, 0x15E, 0xB4, 0, 3, 0);
    }
    return menuSubOpenSelect2(0, a, 3, 0x15E, 0xB4, 0, 3, 0);
}

void menuOrre::CreatePokemonList()
{
    u16 n = 0;
    u16 i;
    u16 j;
    for (i = 0; i < 6; i++) {
        list[n++] = GetTemochiPokemonPtr(i);
    }
    for (j = 0; j < 6; j++) {
        list[n++] = GetDeckPokemonPtr(j);
    }
}

static s32 _loadPokemonCallBack(void *arg)
{
    s32 result = 0;
    if (pOrre != 0) {
        result = (s32)pOrre->list[*(u16 *)arg];
        (*(u16 *)arg)++;
    }
    return result;
}

void menuOrre::Button(tagWINDOW_WORK *window)
{
    MenuOrrePos pos = window->unk9C;
    unkE = pos.b;
    if (window != 0) {
        u16 key = windowGetKeyInfo()->unk4;
        if ((key & 0x10) != 0) {
            window->unkA4 = 1;
        }
        if (unk4 != 0 && (key & 0x20) != 0) {
            window->unkA4 = 1;
            window->unkA5 = 1;
        }
    }
}

void menuOrre::SetNumber(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s16 ids[6] = { 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 };
    u16 nums[4] = { 0x31C, 0x31D, 0x31E, 0x31F };
    u16 i;
    u16 j;
    for (i = 0; i < 6; i++) {
        if (sprite->unk6 == ids[i]) {
            break;
        }
    }
    for (j = 0; j < 4; j++) {
        if (i == slots[j]) {
            windowDrawSprite2(0, 0, sprite->unk54, sprite->unk56, window->unk93 | 0xFFFFFF00, window, nums[j], 0,
                              winSpriteGetLayerID(window, sprite));
            return;
        }
    }
}

s32 menuOrre::Hook(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    switch (sprite->unk6) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        LeftPanel(window, sprite);
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        RightPanel(window, sprite);
        break;
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
        SetNumber(window, sprite);
        break;
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        ControlCursor(window, sprite);
        break;
    case 0x19: {
        MenuOrreItem *item;
        u32 rect;
        msgctrlSetValue(0x37, heroBiosGetNamePtr(GetHeroPtr(0)));
        item = menuItemBiosGetPtr(0xFD, sprite->unk6);
        rect = GSmsgGetRect(0x4276);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), item->unkA - (rect >> 16), 0, window->unk93 | 0xFFFFFF00, 0x4276);
        break;
    }
    case 0x1A:
        msgctrlSetValue(0x37, GSmsgGetGSchar(fightTrainerDB_GetName(trainerDataId)));
        GSmsgGetRect(0x4276);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, window->unk93 | 0xFFFFFF00, 0x4276);
        break;
    }
    return 0;
}
