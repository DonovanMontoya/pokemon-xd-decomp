#ifndef HERO_PRIVATE_H
#define HERO_PRIVATE_H

#include <global.h>

struct Pokemon;
struct Item;

enum FloorStateMode { FloorStateModeNone };
enum FloorEnterMode { FloorEnterModeNone };

struct GSthread;

struct FloorModuleInterface {
    void (*create)(unsigned int, FloorEnterMode);
    void (*pre)(unsigned int, FloorEnterMode);
    void (*normal)(unsigned int, FloorEnterMode);
    int (*thread)(GSthread*);
    void (*post)(unsigned int, FloorEnterMode);
    void (*free)(unsigned int, FloorEnterMode);
    const char* (*getName)();
    void (*saveState)(FloorStateMode, void*, unsigned long);
    void (*loadState)(FloorStateMode, void*, unsigned long);
    unsigned long (*getStateSize)(FloorStateMode);
    unsigned long (*getStateID)();
};

class Hero {
public:
    static Hero* getHeroPtr();
    Item** getDisk();
    void setRestertPos();
    void setHeroStyle(u8, bool);
    void setFollowerID(u8);
    void setFollowerModelLevel(u8);
    void setFollowerObjID(unsigned long);
    void setFollowerResID(unsigned long);
    void setFollowerGrpID(unsigned long);
    unsigned long getFollowerGrpID();
    unsigned long getFollowerResID();
    unsigned long getHeroObjID(long, long);
    void setPokemon(const Pokemon*, long);
};

extern "C" {
void FloorModuleInterface_clear(FloorModuleInterface*);
u32 floorRegisterModule(u8, u32, FloorModuleInterface*);
void GSlogWrite(const char*, ...);
s32 GScharCmp(const void*, const void*);
u32 HSD_Rand();
void* GSmsgGetGSchar(u32);
void* savedataGetStatus(void*, u32);

void* heroBiosGetNamePtr(Hero*);
u32 heroBiosGetRnd(Hero*);
void* heroBiosGetPokemonPtr(Hero*, u16);
void* heroBiosGetItemNormalPtr(Hero*, u16);
void* heroBiosGetExtraItemPtr(Hero*, u16);
void* heroBiosGetItemBallPtr(Hero*, u16);
void* heroBiosGetItemSkillPtr(Hero*, u16);
void* heroBiosGetItemSeedPtr(Hero*, u16);
void* heroBiosGetItemKoronPtr(Hero*, u16);
void* heroBiosGetHizukiItemPtr(Hero*, u16);
u8 heroBiosGetSexDataId(Hero*);
u32 heroBiosGetPokedoru(Hero*);
u32 heroBiosGetPokecoupon(Hero*);
u32 heroBiosGetPokecouponAll(Hero*);
u8 heroBiosGetBadge01Flag(Hero*);
u8 heroBiosGetBadge02Flag(Hero*);
u8 heroBiosGetBadge03Flag(Hero*);
u8 heroBiosGetBadge04Flag(Hero*);
u8 heroBiosGetBadge05Flag(Hero*);
u8 heroBiosGetBadge06Flag(Hero*);
u8 heroBiosGetBadge07Flag(Hero*);
u8 heroBiosGetBadge08Flag(Hero*);
void* heroBiosGetHizukiNamePtr(Hero*);
u8 heroBiosGetHizukiFlag(Hero*);
u8 heroBiosGetHomePlace(Hero*);
void heroBiosSetNamePtr(Hero*, const void*);
void heroBiosSetRnd(Hero*, u32);
void heroBiosSetSexDataId(Hero*, u8);
void heroBiosSetPokedoru(Hero*, s32);
void heroBiosSetPokecoupon(Hero*, s32);
void heroBiosSetPokecouponAll(Hero*, s32);
void heroBiosSetBadge01Flag(Hero*, bool);
void heroBiosSetBadge02Flag(Hero*, bool);
void heroBiosSetBadge03Flag(Hero*, bool);
void heroBiosSetBadge04Flag(Hero*, bool);
void heroBiosSetBadge05Flag(Hero*, bool);
void heroBiosSetBadge06Flag(Hero*, bool);
void heroBiosSetBadge07Flag(Hero*, bool);
void heroBiosSetBadge08Flag(Hero*, bool);
void heroBiosSetHizukiNamePtr(Hero*, const void*);
void heroBiosSetHizukiFlag(Hero*, bool);
void heroBiosSetHomePlace(Hero*, u8);

u8 pokemonCheckValid(void*);
void pokemonBiosGetDp(void*);
s32 pokemonGetStatus(void*, u32, u32, u32);
void pokemonCheckSetMonohiroi(void*);
void pokemonInitAry(void*, u32);
void pokemonBiosCopy(void*, void*);
void pokemonSetCatchStatus(void*, u32, u32, u32, u32, u32, void*);
void itemInitAry(void*, u32);
u32 itemGetStatus(void*, u16, u32, u32);
s32 itemCheckAddItemDataIdAry(void*, u16, u16, u16, u8);
s32 itemDecItemDataIdAry(void*, u16, u16, s32, s32, u16, u8);
s32 itemAddItemDataIdAry(void*, u16, u16, s32, s32, u16, u8, u8);
s32 itemSearchItemDataIdAry(void*, u16, u16, u32, u16);
s32 pcboxAddPokemon(void*, void*, s8);
void heroMoveDismissMember(u32);
u8 heroMoveIsSmoothFloorLink();
void peopleChangeFollower(u32);
void* peopleGet(u32, u32);
void peopleSetFollowerPtr(void*);
u8 peopleCheckFlag(u32, u32, u32);
void peopleSetMotion(u32, u32, u32, u32, u32);
}

#endif
