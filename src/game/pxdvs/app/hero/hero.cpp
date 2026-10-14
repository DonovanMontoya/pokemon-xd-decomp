#include <game/pxdvs/app/hero/heroPrivate.hpp>

static FloorModuleInterface _floorModuleHero;
static u32 _hModuleHero;

static unsigned long _heroGetUID();
static const char* _heroGetUniqueModuleName();
static unsigned long _heroGetStateSize(FloorStateMode);
static void _heroRestoreStateData(FloorStateMode, void*, unsigned long);
static void _heroMakeStateData(FloorStateMode, void*, unsigned long);
static Hero* _getHero();
static void _heroExitFloor(unsigned int, FloorEnterMode);
static void _heroEnterFloor(unsigned int, FloorEnterMode);

extern "C" {
u32 heroGetStatus(Hero*, u16, u16);
void heroSetStatus(Hero*, u16, u32);
void heroInit(Hero*);
u32 heroCreateRnd();
u8 heroAddPokemon(Hero*, Pokemon*);
void* heroItemGetItemDataIdToItemAryPtr(Hero*, u16, u16*, u16*, u8*, u8*);
void* heroItemGetItemKindToItemAryPtr(Hero*, u8, u16*, u16*, u8*, u8*);
void heroSetFollower(u32, u32, u32);
}

static unsigned long _heroGetUID() {
    static const char* id;
    static s8 init;
    if (init == 0) {
        id = "HERO";
        init = 1;
    }
    return (id[0] << 24) | (id[1] << 16) | (id[2] << 8) | id[3];
}

static const char* _heroGetUniqueModuleName() {
    return "hero";
}

static unsigned long _heroGetStateSize(FloorStateMode) {
    return 0;
}

static void _heroRestoreStateData(FloorStateMode, void*, unsigned long) {
}

static void _heroMakeStateData(FloorStateMode mode, void*, unsigned long) {
    if (mode == 3) {
        Hero* hero = (Hero*)savedataGetStatus(0, 2);
        hero->setRestertPos();
    }
}

extern "C" {

u16 heroGetPokeomCount(Hero* hero) {
    u16 i = 0;
    u16 count = 0;
    for (; i < 6; i++) {
        if (pokemonCheckValid(heroBiosGetPokemonPtr(hero, i)) != 0) {
            count++;
        }
    }
    return count;
}

s32 heroGetEmptySlot(Hero* hero) {
    s32 i = 0;
    do {
        void* p = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(p) == 0) {
            return i;
        }
        pokemonBiosGetDp(p);
        i++;
    } while (i < 6);
    return -1;
}

s32 heroGetLivingPokemonCount(Hero* hero) {
    s32 i = 0;
    void* p;
    s32 count = 0;
    do {
        p = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(p) != 0 && pokemonGetStatus(p, 0, 0x7B, 0) == 0) {
            count++;
        }
        i++;
    } while (i < 6);
    return count;
}

void heroDecPokecoupon(Hero* hero, s32 amount) {
    heroSetStatus(hero, 0xD, (u32)heroGetStatus(hero, 0xD, 0) - amount);
    if (amount <= 0) {
        heroSetStatus(hero, 0xE, (u32)heroGetStatus(hero, 0xE, 0) - amount);
    }
}

void heroAddPokecoupon(Hero* hero, s32 amount) {
    u32 cur = heroGetStatus(hero, 0xD, 0);
    cur += amount;
    heroSetStatus(hero, 0xD, cur);
    if (amount >= 0) {
        cur = heroGetStatus(hero, 0xE, 0);
        cur += amount;
        heroSetStatus(hero, 0xE, cur);
    }
}

void heroDecPokedoru(Hero* hero, s32 amount) {
    heroSetStatus(hero, 0xC, (u32)heroGetStatus(hero, 0xC, 0) - amount);
}

void heroAddPokedoru(Hero* hero, s32 amount) {
    u32 cur = heroGetStatus(hero, 0xC, 0);
    cur += amount;
    heroSetStatus(hero, 0xC, cur);
}

void* heroHizukiItemGetItemAryPtr(Hero* hero, s16* count, s16* max, s8* a, s8* b) {
    if (count != 0) {
        *count = 10;
    }
    if (max != 0) {
        *max = 1;
    }
    if (a != 0) {
        *a = 0;
    }
    if (b != 0) {
        *b = 1;
    }
    return (void*)heroGetStatus(hero, 0xA, 0);
}

void heroCheckSetMonohiroiAllTemotiPokemon(Hero* hero) {
    void* p;
    u16 i = 0;
    for (; i < 6; i++) {
        p = (void*)heroGetStatus(hero, 3, i);
        if (pokemonCheckValid(p) != 0) {
            pokemonCheckSetMonohiroi(p);
        }
    }
}

s32 heroItemCheckAddItemDataId(Hero* hero, u16 id) {
    u16 count = 0;
    u16 max = 0;
    u8 flag;
    void* ary = heroItemGetItemDataIdToItemAryPtr(hero, id, &count, &max, 0, &flag);
    if (ary == 0) {
        return -1;
    }
    return itemCheckAddItemDataIdAry(ary, count, id, max, flag);
}

s32 heroItemDecItemDataId(Hero* hero, u16 id, s32 a, s32 b) {
    u16 count = 0;
    u16 max = 0;
    u8 flag;
    void* ary = heroItemGetItemDataIdToItemAryPtr(hero, id, &count, &max, &flag, 0);
    if (ary == 0) {
        return -1;
    }
    return itemDecItemDataIdAry(ary, count, id, a, b, max, flag);
}

s32 heroItemAddItemDataId(Hero* hero, u16 id, s32 a, s32 b) {
    u16 count = 0;
    u16 max = 0;
    u8 flagB;
    u8 flagA;
    void* ary = heroItemGetItemDataIdToItemAryPtr(hero, id, &count, &max, &flagB, &flagA);
    if (ary == 0) {
        return -1;
    }
    return itemAddItemDataIdAry(ary, count, id, a, b, max, flagB, flagA);
}

s32 heroItemCheckHaveItemDataId(Hero* hero, u16 id) {
    u16 count = 0;
    u16 max = 0;
    void* ary = heroItemGetItemDataIdToItemAryPtr(hero, id, &count, &max, 0, 0);
    if (ary == 0) {
        return 0;
    }
    return itemSearchItemDataIdAry(ary, count, id, 0, max) != 0;
}

void* heroItemGetItemDataIdToItemAryPtr(Hero* hero, u16 id, u16* count, u16* max, u8* a, u8* b) {
    return heroItemGetItemKindToItemAryPtr(hero, (u8)itemGetStatus(0, id, 2, 0), count, max, a, b);
}

void* heroItemGetItemKindToItemAryPtr(Hero* hero, u8 kind, u16* count, u16* max, u8* a, u8* b) {
    void* ary = 0;
    u16 countVal = 0;
    u16 maxVal = 0;
    u8 aVal = 0;
    u8 bVal;
    switch (kind) {
    case 1:
        ary = (void*)heroGetStatus(hero, 6, 0);
        countVal = 0x10;
        maxVal = 999;
        aVal = 0;
        bVal = 1;
        break;
    case 2:
        ary = (void*)heroGetStatus(hero, 4, 0);
        countVal = 0x1E;
        maxVal = 999;
        aVal = 0;
        bVal = 1;
        break;
    case 3:
        ary = (void*)heroGetStatus(hero, 8, 0);
        countVal = 0x2E;
        maxVal = 999;
        aVal = 1;
        bVal = 1;
        break;
    case 4:
        ary = (void*)heroGetStatus(hero, 7, 0);
        countVal = 0x40;
        maxVal = 999;
        aVal = 1;
        bVal = 0;
        break;
    case 5:
        ary = (void*)heroGetStatus(hero, 5, 0);
        countVal = 0x2B;
        maxVal = 999;
        aVal = 0;
        bVal = 0;
        break;
    case 6:
        ary = (void*)heroGetStatus(hero, 9, 0);
        countVal = 3;
        maxVal = 999;
        aVal = 1;
        bVal = 0;
        break;
    case 7:
        if (hero == 0) {
            hero = _getHero();
        }
        ary = hero->getDisk();
        countVal = 0x3C;
        maxVal = 999;
        aVal = 1;
        bVal = 0;
        break;
    }
    if (count != 0) {
        *count = countVal;
    }
    if (max != 0) {
        *max = maxVal;
    }
    if (a != 0) {
        *a = aVal;
    }
    if (b != 0) {
        *b = bVal;
    }
    return ary;
}

s32 heroIsMinePokemon(Hero* hero, void* pokemon) {
    u32 rnd = (u32)heroGetStatus(hero, 2, 0);
    void* name = (void*)heroGetStatus(hero, 1, 0);
    u32 pokemonRnd = pokemonGetStatus(pokemon, 0, 0x75, 0);
    void* pokemonName = (void*)pokemonGetStatus(pokemon, 0, 0x76, 0);
    if (rnd != pokemonRnd) {
        return 0;
    }
    return (u32)__cntlzw(GScharCmp(name, pokemonName)) >> 5;
}

s32 heroGetPokemon(Hero* hero, Pokemon* src, u8 useBox) {
    u8 buf[0xC4];
    if (src == 0) {
        return 6;
    }
    pokemonBiosCopy(buf, src);
    u32 slot = (u8)heroAddPokemon(hero, (Pokemon*)buf);
    if (slot >= 6) {
        if (useBox == 0) {
            return -2;
        }
        {
            s32 hit = (u32)__cntlzw(1 - pcboxAddPokemon(0, buf, -1)) >> 5;
            return hit - 2;
        }
    }
    return (s16)slot;
}

s32 heroCatchPokemon(Hero* hero, Pokemon* src, u32 a, void* b, u8 useBox) {
    u8 buf[0xC4];
    u8 ball;
    u8 home;
    u32 rnd;
    void* name;
    if (src == 0) {
        return 6;
    }
    ball = pokemonGetStatus(src, 0, 0x7A, 0);
    home = (u32)heroGetStatus(hero, 0xB, 0);
    rnd = (u32)heroGetStatus(hero, 2, 0);
    name = (void*)heroGetStatus(hero, 1, 0);
    pokemonBiosCopy(buf, src);
    pokemonSetCatchStatus(buf, a, ball, (u32)b, home, rnd, name);
    u32 slot = (u8)heroAddPokemon(hero, (Pokemon*)buf);
    if (slot >= 6) {
        if (useBox == 0) {
            return -2;
        }
        {
            s32 hit = (u32)__cntlzw(1 - pcboxAddPokemon(0, buf, -1)) >> 5;
            return hit - 2;
        }
    }
    return (s16)slot;
}

u8 heroAddPokemon(Hero* hero, Pokemon* pokemon) {
    u8 i;
    if (pokemon == 0) {
        return 6;
    }
    for (i = 0; i < 6; i++) {
        if (pokemonCheckValid((void*)heroGetStatus(hero, 3, i)) != 1) {
            if (hero == 0) {
                hero = _getHero();
            }
            hero->setPokemon(pokemon, i);
            return i;
        }
    }
    return 6;
}

u32 heroCheckValid(Hero* hero) {
    u16 empty = 0;
    u32 type;
    if (GScharCmp((void*)heroGetStatus(hero, 1, 0), &empty) == 0) {
        return 0;
    }
    type = heroGetStatus(hero, 0xB, 0);
    return (u32)(((2 - type) | (type - 2))) >> 31;
}

void heroCreate(Hero* hero, void* name, u8 type) {
    u32 rnd;
    heroInit(hero);
    rnd = heroCreateRnd();
    heroSetStatus(hero, 2, rnd);
    heroSetStatus(hero, 1, (u32)name);
    heroSetStatus(hero, 0xB, type);
    heroSetStatus(hero, 0x17, (u32)GSmsgGetGSchar(1));
    if (hero == 0) {
        Hero::getHeroPtr();
    }
}

u32 heroCreateRnd() {
    u16 low = HSD_Rand();
    return (low & ~0xFFFF0000) | (HSD_Rand() << 16);
}

void heroInit(Hero* hero) {
    u16 empty = 0;
    if (hero == 0) {
        hero = Hero::getHeroPtr();
    }
    heroSetStatus(hero, 1, (u32)&empty);
    heroSetStatus(hero, 2, 0);
    pokemonInitAry((void*)heroGetStatus(hero, 3, 0), 6);
    itemInitAry((void*)heroGetStatus(hero, 4, 0), 0x1E);
    itemInitAry((void*)heroGetStatus(hero, 5, 0), 0x2B);
    itemInitAry((void*)heroGetStatus(hero, 6, 0), 0x10);
    itemInitAry((void*)heroGetStatus(hero, 7, 0), 0x40);
    itemInitAry((void*)heroGetStatus(hero, 8, 0), 0x2E);
    itemInitAry((void*)heroGetStatus(hero, 9, 0), 3);
    itemInitAry(hero->getDisk(), 0x3C);
    heroSetStatus(hero, 0xB, 2);
    heroSetStatus(hero, 0xC, 0);
    heroSetStatus(hero, 0xD, 0);
    heroSetStatus(hero, 0xE, 0);
    heroSetStatus(hero, 0xF, 1);
    heroSetStatus(hero, 0x10, 1);
    heroSetStatus(hero, 0x11, 1);
    heroSetStatus(hero, 0x12, 1);
    heroSetStatus(hero, 0x13, 1);
    heroSetStatus(hero, 0x14, 1);
    heroSetStatus(hero, 0x15, 1);
    heroSetStatus(hero, 0x16, 1);
    heroSetStatus(hero, 0x17, (u32)&empty);
    heroSetStatus(hero, 0x18, 0);
    itemInitAry((void*)heroGetStatus(hero, 0xA, 0), 0xA);
    heroSetStatus(hero, 0x19, 0);
    hero->setHeroStyle(0, false);
    hero->setFollowerID(0);
    if (_hModuleHero == 0) {
        FloorModuleInterface_clear(&_floorModuleHero);
        _floorModuleHero.pre = _heroEnterFloor;
        _floorModuleHero.post = _heroExitFloor;
        _floorModuleHero.getName = _heroGetUniqueModuleName;
        _floorModuleHero.saveState = _heroMakeStateData;
        _floorModuleHero.loadState = _heroRestoreStateData;
        _floorModuleHero.getStateSize = _heroGetStateSize;
        _floorModuleHero.getStateID = _heroGetUID;
        _hModuleHero = floorRegisterModule(0x19, 0, &_floorModuleHero);
    }
}

void heroSetStatus(Hero* hero, u16 id, u32 value) {
    if (id == 0 || id >= 0x1A) {
        return;
    }
    if (hero == 0) {
        hero = (Hero*)savedataGetStatus(0, 0);
        if (hero == 0) {
            return;
        }
        hero = (Hero*)savedataGetStatus(hero, 2);
        if (hero == 0) {
            return;
        }
    }
    switch (id) {
    case 1:
        heroBiosSetNamePtr(hero, (void*)value);
        break;
    case 2:
        heroBiosSetRnd(hero, value);
        break;
    case 0xB:
        heroBiosSetSexDataId(hero, value);
        break;
    case 0xC:
        heroBiosSetPokedoru(hero, value);
        break;
    case 0xD:
        heroBiosSetPokecoupon(hero, value);
        break;
    case 0xE:
        heroBiosSetPokecouponAll(hero, value);
        break;
    case 0xF:
        heroBiosSetBadge01Flag(hero, value);
        break;
    case 0x10:
        heroBiosSetBadge02Flag(hero, value);
        break;
    case 0x11:
        heroBiosSetBadge03Flag(hero, value);
        break;
    case 0x12:
        heroBiosSetBadge04Flag(hero, value);
        break;
    case 0x13:
        heroBiosSetBadge05Flag(hero, value);
        break;
    case 0x14:
        heroBiosSetBadge06Flag(hero, value);
        break;
    case 0x15:
        heroBiosSetBadge07Flag(hero, value);
        break;
    case 0x16:
        heroBiosSetBadge08Flag(hero, value);
        break;
    case 0x17:
        heroBiosSetHizukiNamePtr(hero, (void*)value);
        break;
    case 0x18:
        heroBiosSetHizukiFlag(hero, value);
        break;
    case 0x19:
        heroBiosSetHomePlace(hero, value);
        break;
    }
}

u32 heroGetStatus(Hero* hero, u16 id, u16 index) {
    if (id == 0 || id >= 0x1A) {
        return 0;
    }
    if (hero == 0) {
        hero = _getHero();
    }
    switch (id) {
    case 1:
        return (u32)heroBiosGetNamePtr(hero);
    case 2:
        return (u32)heroBiosGetRnd(hero);
    case 3:
        return (u32)heroBiosGetPokemonPtr(hero, index);
    case 4:
        return (u32)heroBiosGetItemNormalPtr(hero, index);
    case 5:
        return (u32)heroBiosGetExtraItemPtr(hero, index);
    case 6:
        return (u32)heroBiosGetItemBallPtr(hero, index);
    case 7:
        return (u32)heroBiosGetItemSkillPtr(hero, index);
    case 8:
        return (u32)heroBiosGetItemSeedPtr(hero, index);
    case 9:
        return (u32)heroBiosGetItemKoronPtr(hero, index);
    case 0xA:
        return (u32)heroBiosGetHizukiItemPtr(hero, index);
    case 0xB:
        return (u32)heroBiosGetSexDataId(hero);
    case 0xC:
        return (u32)heroBiosGetPokedoru(hero);
    case 0xD:
        return (u32)heroBiosGetPokecoupon(hero);
    case 0xE:
        return (u32)heroBiosGetPokecouponAll(hero);
    case 0xF:
        return (u32)heroBiosGetBadge01Flag(hero);
    case 0x10:
        return (u32)heroBiosGetBadge02Flag(hero);
    case 0x11:
        return (u32)heroBiosGetBadge03Flag(hero);
    case 0x12:
        return (u32)heroBiosGetBadge04Flag(hero);
    case 0x13:
        return (u32)heroBiosGetBadge05Flag(hero);
    case 0x14:
        return (u32)heroBiosGetBadge06Flag(hero);
    case 0x15:
        return (u32)heroBiosGetBadge07Flag(hero);
    case 0x16:
        return (u32)heroBiosGetBadge08Flag(hero);
    case 0x17:
        return (u32)heroBiosGetHizukiNamePtr(hero);
    case 0x18:
        return (u32)heroBiosGetHizukiFlag(hero);
    case 0x19:
        return (u32)heroBiosGetHomePlace(hero);
    }
    return 0;
}

u32 heroGetObjID(u8 level) {
    Hero* p = Hero::getHeroPtr();
    if (p == 0) {
        return 0x16C90400;
    }
    return p->getHeroObjID(level, -1);
}

}

static Hero* _getHero() {
    Hero* hero = (Hero*)savedataGetStatus(0, 0);
    if (hero == 0) {
        return 0;
    }
    hero = (Hero*)savedataGetStatus(hero, 2);
    if (hero == 0) {
        return 0;
    }
    return hero;
}

static void _heroExitFloor(unsigned int, FloorEnterMode mode) {
    if (mode != 1 && heroMoveIsSmoothFloorLink() == 0) {
        if (peopleCheckFlag(0, 0x64, 0x80000000) == 0) {
            peopleSetMotion(0, 0x64, 3, 0, 1);
        }
        peopleSetMotion(0, 0x65, 3, 0, 1);
        peopleSetMotion(0, 0x68, 3, 0, 1);
        peopleSetMotion(0, 0x69, 3, 0, 1);
    }
}

static void _heroEnterFloor(unsigned int, FloorEnterMode) {
}

extern "C" {

void heroSetFollowerWithID(u8 id, u8 variant) {
    Hero* hero = Hero::getHeroPtr();
    hero->setFollowerID(id);
    hero->setFollowerModelLevel(0);
    switch (id) {
    case 0:
        heroMoveDismissMember(1);
        heroMoveDismissMember(2);
        heroMoveDismissMember(3);
        break;
    case 1:
        switch (variant) {
        case 0:
            heroSetFollower(0, 0x65, 0x16C70400);
            return;
        case 1:
            heroSetFollower(0, 0x65, 0x16C80400);
            hero->setFollowerModelLevel(1);
            return;
        }
    case 2:
        heroSetFollower(0, 0x68, 0x195B0400);
        break;
    case 3:
        heroSetFollower(0, 0x69, 0x19540400);
        break;
    }
}

void heroSetFollower(u32 grp, u32 res, u32 obj) {
    Hero* hero = Hero::getHeroPtr();
    hero->setFollowerGrpID(grp);
    hero->setFollowerResID(res);
    hero->setFollowerObjID(obj);
    peopleChangeFollower(obj);
    void* person = peopleGet(grp, res);
    if (person == 0) {
        GSlogWrite("Illegal ID!\n");
        return;
    }
    peopleSetFollowerPtr(person);
    if (obj - 0x16C80000 == 0x400) {
        hero->setFollowerModelLevel(1);
    } else {
        hero->setFollowerModelLevel(0);
    }
}

s32 heroIsPlayerPeople(u32 grp, u32 res) {
    Hero* hero;
    if (grp == 0 && res == 0x64) {
        return 1;
    }
    hero = Hero::getHeroPtr();
    if (grp == hero->getFollowerGrpID() && res == hero->getFollowerResID()) {
        return 1;
    }
    return 0;
}

}
