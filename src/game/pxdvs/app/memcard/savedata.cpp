#include <global.h>
#include <game/pxdvs/app/hero/hero.hpp>

extern "C" {
u32 savedataGetStatus(void*,u16);
void savedataInit(void*);
void* savedataBiosGetNowSavedataPtr();
void* savedataBiosGetGamedataPtr(void*);
void* savedataBiosGetHeroPtr(void*);
void* savedataBiosGetPcboxPtr(void*);
void* savedataBiosGetFlagLevel0Ptr(void*);
void* savedataBiosGetFlagLevel1Ptr(void*);
void* savedataBiosGetFlagLevel2Ptr(void*);
void* savedataBiosGetMailboxPtr(void*);
void* savedataBiosGetSodateyaPtr(void*);
void* savedataBiosGetMemoDataPtr(void*);
void* savedataBiosGetToolPtr(void*);
void* savedataBiosGetDarkpokemonPtr(void*);
void* savedataBiosGetExRibbonPtr(void*);
void* savedataBiosGetAnywaySavePtr(void*);
void* savedataBiosGetYobi1Ptr(void*);
void* savedataBiosGetYobi2Ptr(void*);
void* savedataBiosGetYobi3Ptr(void*);
void* savedataBiosGetYobi4Ptr(void*);
void* savedataBiosGetRelivePtr(void*);
void* savedataBiosGetFlagSavedataPtr(void*);
void gamedataInit(void*);
void heroInit(void*);
void pcboxInit(void*);
void GSflagClear(s32);
void GSflagOn(s32);
void mailInitMailbox(void*);
void sodateyaInit(void*);
void menuCB_RULE_INIT(void*);
void memoInit(void*);
void darkpokemonValInit(void*);
void exribbonInit(void*);
void init__11CReliveHallFv(void*);
s32 pokecoloGetCountryCode();
s32 pokecoloGetLanguage();
s32 pokecoloGetRomVersion();
void gamedataCreate(void*,s32,s32,s32,s32);
void gamedatasaveSetStatus(void*,s32,s32);
void GScharMakeFromSJIS(char16*,const char*);
void heroCreate(Hero*,const char16*,s32);
u8 heroBiosGetSexDataId(Hero*);
u32 heroBiosGetRnd(Hero*);
char16* heroBiosGetNamePtr(Hero*);
void heroSetStatus(Hero*,s32,s32);
void heroItemAddItemDataId(Hero*,u16,u16,s32);
u32 pokemonCreateRndFit(Pokemon*,u8,u8,u8,u32);
void pokemon_SetRnd(Pokemon*,u32);
void pokemonBiosSetTokuseiFlag(Pokemon*,u8);
void pokemonResetBasisStatus(Pokemon*);

u8 pokecolo_savedata[0x287D0] ATTRIBUTE_ALIGN(32);
void* now_savedata_ptr;

void savedataSetBattleDiskSellOut(u32 index) {
    u32* flags=(u32*)savedataGetStatus(0,0x18);
    flags[index/32]|=1<<(index&31);
}
bool savedataGetBattleDiskSellOut(u32 index) {
    u32* flags=(u32*)savedataGetStatus(0,0x18);
    return ((1<<(index&31))&flags[index/32])!=0;
}
}

struct StartingPokemon {
    u8 level,reserved;
    u16 species,shadow,friendship,moves[4];
    u32 floor,experience;
    u8 sex,nature,ability,reserved1B;
};
typedef char StartingPokemonSize[sizeof(StartingPokemon)==0x1C?1:-1];

extern "C" void savedataCreate(void* save,const char16* name) {
    HeroPokemonGetParam param;
    memset(&param,0,sizeof(param));
    savedataInit(save);
    void* game=(void*)savedataGetStatus(save,1);
    switch(pokecoloGetCountryCode()){
    case 0:gamedataCreate(game,11,3,1,1);break;
    case 1:gamedataCreate(game,11,3,2,2);break;
    case 2:gamedataCreate(game,11,3,3,8);break;
    }
    gamedatasaveSetStatus(game,11,pokecoloGetLanguage());
    Hero* hero=(Hero*)savedataGetStatus(save,2);
    char16 defaultName[10];
    if(name==0){GScharMakeFromSJIS(defaultName,"\x81\x40");name=defaultName;}
    heroCreate(hero,name,0);
    if(pokecoloGetRomVersion()==1){
        StartingPokemon party[4]={
            {40,0,47,0,0,{147,202,10,74},0,64000,0,0,0,0},
            {40,0,393,0,0,{93,351,247,347},0,80000,1,18,0,0},
            {40,0,101,0,0,{209,86,129,103},0,64000,0,12,0,0},
            {40,0,341,0,0,{62,57,34,45},0,56660,1,18,0,0}
        };
        gamedatasaveSetStatus(game,5,138);
        gamedatasaveSetStatus(game,7,143);
        gamedatasaveSetStatus(game,8,2);
        int i;
        StartingPokemon* entry=party;
        for(i=0;i<4;++i){
            param.pokemonDataID=entry->species;
            param.shadowPokemonDataID=entry->shadow;
            param.catchLevel=entry->level;
            param.friendLevel=entry->friendship;
            param.move1=entry->moves[0];param.move2=entry->moves[1];
            param.move3=entry->moves[2];param.move4=entry->moves[3];
            param.trainerSexID=heroBiosGetSexDataId(hero);
            param.trainerRnd=heroBiosGetRnd(hero);
            param.trainerNamePtr=heroBiosGetNamePtr(hero);
            param.catchFloorID=entry->floor;
            param.exp=entry->experience;
            ++entry;
            hero->pokemonGet(&param,true);
        }
        Pokemon* pokemon;
        StartingPokemon* randomEntry=party;
        for(s32 j=0;j<4;++j,++randomEntry){
            pokemon=hero->getPokemon(j);
            u32 random=pokemonCreateRndFit(pokemon,randomEntry->sex,randomEntry->nature,0,heroBiosGetRnd(hero));
            pokemon_SetRnd(pokemon,random);
            pokemonBiosSetTokuseiFlag(pokemon,randomEntry->ability);
            pokemonResetBasisStatus(pokemon);
        }
        heroSetStatus(hero,12,0);
        heroItemAddItemDataId(hero,2,20,-1);
        heroItemAddItemDataId(hero,21,20,-1);
        heroItemAddItemDataId(hero,23,10,-1);
        heroItemAddItemDataId(hero,24,5,-1);
        hero->setBattleResumeFloorID(71);hero->setBattleResumeFloorIndex(0);
        hero->setHeroStyle(2,false);hero->setFollowerID(0);
        return;
    }
    gamedatasaveSetStatus(game,5,138);
    gamedatasaveSetStatus(game,7,143);
    gamedatasaveSetStatus(game,8,2);
    param.pokemonDataID=133;param.shadowPokemonDataID=0;param.catchLevel=10;
    param.friendLevel=215;param.move1=33;param.move2=39;param.move3=44;param.move4=28;
    param.trainerSexID=heroBiosGetSexDataId(hero);
    param.trainerRnd=heroBiosGetRnd(hero);param.trainerNamePtr=heroBiosGetNamePtr(hero);
    param.catchFloorID=0;param.exp=1250;
    hero->pokemonGet(&param,true);
    heroSetStatus(hero,12,5000);
    hero->setBattleResumeFloorID(138);hero->setBattleResumeFloorIndex(2);
    hero->setHeroStyle(0,false);hero->setFollowerID(0);
}

extern "C" void savedataInit(void* save) {
    u8 game[0x88];
    u8 rules[0x364];
    memcpy(game,(void*)savedataGetStatus(save,1),sizeof(game));
    memcpy(rules,(void*)savedataGetStatus(save,14),sizeof(rules));
    memset((void*)savedataGetStatus(0,0),0,0x27FD0);
    memcpy((void*)savedataGetStatus(save,1),game,sizeof(game));
    memcpy((void*)savedataGetStatus(save,14),rules,sizeof(rules));
    gamedataInit((void*)savedataGetStatus(save,1));
    heroInit((void*)savedataGetStatus(save,2));
    pcboxInit((void*)savedataGetStatus(save,3));
    if(save==0 || save==(void*)savedataGetStatus(0,0)){
        GSflagClear(1);GSflagClear(2);GSflagClear(3);GSflagOn(0x3DE);
    }
    u32 bytes=savedataGetStatus(save,25)*4;
    memset((void*)savedataGetStatus(save,24),0,bytes);
    bytes=savedataGetStatus(save,28)*4;
    memset((void*)savedataGetStatus(save,27),0,bytes);
    mailInitMailbox((void*)savedataGetStatus(save,10));
    sodateyaInit((void*)savedataGetStatus(save,11));
    menuCB_RULE_INIT((void*)savedataGetStatus(save,14));
    memoInit((void*)savedataGetStatus(save,12));
    darkpokemonValInit((void*)savedataGetStatus(save,15));
    exribbonInit((void*)savedataGetStatus(save,16));
    init__11CReliveHallFv((void*)savedataGetStatus(save,21));
}

extern "C" u32 savedataGetStatus(void* save,u16 section) {
    if(section>=29)return 0;
    if(save==0){save=savedataBiosGetNowSavedataPtr();if(save==0)return 0;}
    switch(section){
    case 0:return (u32)save;
    case 1:return (u32)savedataBiosGetGamedataPtr(save);
    case 2:return (u32)savedataBiosGetHeroPtr(save);
    case 3:return (u32)savedataBiosGetPcboxPtr(save);
    case 4:return (u32)savedataBiosGetFlagLevel0Ptr(save);
    case 5:return (u32)savedataBiosGetFlagLevel1Ptr(save);
    case 6:return (u32)savedataBiosGetFlagLevel2Ptr(save);
    case 24:return (u32)((u8*)save+0x10E30);
    case 27:return (u32)((u8*)save+0x10E38);
    case 7:return 8;
    case 8:return 32;
    case 9:return 384;
    case 25:return 2;
    case 28:return 2;
    case 10:return (u32)savedataBiosGetMailboxPtr(save);
    case 11:return (u32)savedataBiosGetSodateyaPtr(save);
    case 12:return (u32)savedataBiosGetMemoDataPtr(save);
    case 14:return (u32)savedataBiosGetToolPtr(save);
    case 15:return (u32)savedataBiosGetDarkpokemonPtr(save);
    case 16:return (u32)savedataBiosGetExRibbonPtr(save);
    case 22:return (u32)savedataBiosGetAnywaySavePtr(save);
    case 26:return 51200;
    case 17:return (u32)savedataBiosGetYobi1Ptr(save);
    case 18:return (u32)savedataBiosGetYobi2Ptr(save);
    case 19:return (u32)savedataBiosGetYobi3Ptr(save);
    case 20:return (u32)savedataBiosGetYobi4Ptr(save);
    case 21:return (u32)savedataBiosGetRelivePtr(save);
    case 23:return (u32)savedataBiosGetFlagSavedataPtr(save);
    default:return 0;
    }
}
