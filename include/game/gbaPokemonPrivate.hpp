#ifndef GBA_POKEMON_PRIVATE_HPP
#define GBA_POKEMON_PRIVATE_HPP
#include <global.h>

typedef union GbaOrigins GbaOrigins;
typedef union GbaIndividualValues GbaIndividualValues;
typedef union GbaRibbons GbaRibbons;
typedef struct GbaPokemon GbaPokemon;
typedef struct GbaGcPokemonName GbaGcPokemonName;

/* Native views of the three little-endian words in a GBA miscellaneous block. */
union GbaOrigins {
    u32 word;
    struct { u32 trainerSex:1, ball:4, version:4, level:7, floor:8, pokerus:8; } bits;
};
union GbaIndividualValues {
    u32 word;
    struct { u32 ability:1, egg:1, speDef:5, speAtk:5, speed:5, phyDef:5, phyAtk:5, hp:5; } bits;
};
union GbaRibbons {
    u32 word;
    struct { u32 event:1, spare:4, world:1, earth:1, national:1, country:1, sky:1, land:1,
                 marine:1, effort:1, artist:1, victory:1, winning:1, champion:1,
                 strong:3, clever:3, cute:3, beautiful:3, style:3; } bits;
};
struct GbaPokemon {
    u32 personality, trainer;
    u8 nickname[10], language;
    struct { u8 spare:5, egg:1, present:1, invalid:1; } flags;
    u8 trainerName[7], markings;
    u16 checksum, spare;
    u16 species, item;
    u32 experience;
    u8 ppBonuses, friendship;
    u16 growthSpare;
    u16 moves[4];
    u8 pp[4], effort[6], condition[6];
    u32 origins, individual, ribbons, status;
    u8 level, mail;
    u16 hp, maxHp, phyAtk, phyDef, speed, speAtk, speDef;
};
typedef char GbaPokemonSize[sizeof(GbaPokemon) == 100 ? 1 : -1];
struct GbaGcPokemonName {
    u8 prefix[0x4e];
    u16 nickname[11];
};

#ifdef __cplusplus
extern "C" {
#endif
void *memcpy(void *, const void *, unsigned long);
void *memmove(void *, const void *, unsigned long);
void *memset(void *, int, unsigned long);
/* Scalar widths here follow the original transfer-unit call boundaries. */
u8 pokemonCheckValid(void *);
void pokemonInit(void *);
u8 pokemonIsJoutaiDataId(void *, u16);
s16 pokemonGetCountAsJoutaiDataId(void *, u16);
s8 pokemonGetKaisuuJoutaiDataId(void *, u16);
void pokemonWriteJoutaiDataId(void *, u16, s32);
void pokemonSetCountAsJoutaiDataId(void *, u16, s16);
void pokemonSetKaisuuJoutaiDataId(void *, u16, s8);
u8 gamedataAttestBiosGetVerId(void *);
u8 gamedataAttestBiosGetLangareaId(void *);
void gamedataAttestCreate(void *, u8, u8, u8, u8);
s32 GBAMakeFromGSchar(u8 *, const u16 *, s32);
s32 GScharMakeFromGBA(u16 *, u8 *, s32, s32);
u16 pokemonBiosGetAmari(void*);
u8 pokemonBiosGetAmariRibbon(void*);
void* pokemonBiosGetAttest(void*);
u8 pokemonBiosGetBeautiful(void*);
u8 pokemonBiosGetBeautifulMedal(void*);
u8 pokemonBiosGetBromideRibbon(void*);
u8 pokemonBiosGetCatchBallId(void*);
u16 pokemonBiosGetCatchFloorId(void*);
u8 pokemonBiosGetCatchLevel(void*);
u16* pokemonBiosGetCatchTrainerNamePtr(void*);
u32 pokemonBiosGetCatchTrainerRnd(void*);
u8 pokemonBiosGetCatchTrainerSex(void*);
u8 pokemonBiosGetChampRibbon(void*);
u8 pokemonBiosGetClever(void*);
u8 pokemonBiosGetCleverMedal(void*);
u32 pokemonBiosGetConditionAmari(void*);
u8 pokemonBiosGetCountryRibbon(void*);
u8 pokemonBiosGetCute(void*);
u8 pokemonBiosGetCuteMedal(void*);
u8 pokemonBiosGetEarthRibbon(void*);
u32 pokemonBiosGetEventGetFlag(void*);
u32 pokemonBiosGetExp(void*);
u8 pokemonBiosGetFlagAmari(void*);
u16 pokemonBiosGetFriend(void*);
u8 pokemonBiosGetFur(void*);
u8 pokemonBiosGetFuseiFlag(void*);
u8 pokemonBiosGetGanbaRibbon(void*);
u16 pokemonBiosGetHp(void*);
u16 pokemonBiosGetItemDataId(void*);
u8 pokemonBiosGetLandRibbon(void*);
u8 pokemonBiosGetLevel(void*);
u8 pokemonBiosGetMailId(void*);
u8 pokemonBiosGetMarineRibbon(void*);
u16 pokemonBiosGetMaxHp(void*);
u16 pokemonBiosGetMaxHpEffort(void*);
u32 pokemonBiosGetMaxHpRnd(void*);
u8 pokemonBiosGetNationalRibbon(void*);
u16* pokemonBiosGetNicknameOrgPtr(void*);
u16 pokemonBiosGetNimbleness(void*);
u16 pokemonBiosGetNimblenessEffort(void*);
u16 pokemonBiosGetNimblenessRnd(void*);
u16 pokemonBiosGetPara1Amari(void*);
u8 pokemonBiosGetPcboxMark(void*);
u16 pokemonBiosGetPhyAtk(void*);
u16 pokemonBiosGetPhyAtkEffort(void*);
u16 pokemonBiosGetPhyAtkRnd(void*);
u16 pokemonBiosGetPhyDef(void*);
u16 pokemonBiosGetPhyDefEffort(void*);
u32 pokemonBiosGetPhyDefRnd(void*);
u16 pokemonBiosGetPokemonDataId(void*);
u16 pokemonBiosGetPokemonWazaDataId(void*, u16);
u8 pokemonBiosGetPokemonWazaPp(void*, u16);
u8 pokemonBiosGetPokemonWazaPpCount(void*, u16);
u8 pokemonBiosGetPokerus(void*);
u32 pokemonBiosGetRnd(void*);
u8 pokemonBiosGetSkyRibbon(void*);
u16 pokemonBiosGetSpeAtk(void*);
u16 pokemonBiosGetSpeAtkEffort(void*);
u16 pokemonBiosGetSpeAtkRnd(void*);
u16 pokemonBiosGetSpeDef(void*);
u16 pokemonBiosGetSpeDefEffort(void*);
u32 pokemonBiosGetSpeDefRnd(void*);
u8 pokemonBiosGetStrong(void*);
u8 pokemonBiosGetStrongMedal(void*);
u8 pokemonBiosGetStyle(void*);
u8 pokemonBiosGetStyleMedal(void*);
u8 pokemonBiosGetTamagoFlag(void*);
u8 pokemonBiosGetTokuseiFlag(void*);
u8 pokemonBiosGetVictoryRibbon(void*);
u8 pokemonBiosGetWinningRibbon(void*);
u8 pokemonBiosGetWorldRibbon(void*);
void pokemonBiosSetAmari(void*, u16);
void pokemonBiosSetAmariRibbon(void*, u8);
void pokemonBiosSetBeautiful(void*, u8);
void pokemonBiosSetBeautifulMedal(void*, u8);
void pokemonBiosSetBromideRibbon(void*, u8);
void pokemonBiosSetCatchBallId(void*, u8);
void pokemonBiosSetCatchFloorId(void*, u16);
void pokemonBiosSetCatchLevel(void*, u8);
void pokemonBiosSetCatchTrainerRnd(void*, u32);
void pokemonBiosSetCatchTrainerSex(void*, u8);
void pokemonBiosSetChampRibbon(void*, u8);
void pokemonBiosSetClever(void*, u8);
void pokemonBiosSetCleverMedal(void*, u8);
void pokemonBiosSetConditionAmari(void*, u32);
void pokemonBiosSetCountryRibbon(void*, u8);
void pokemonBiosSetCute(void*, u8);
void pokemonBiosSetCuteMedal(void*, u8);
void pokemonBiosSetEarthRibbon(void*, u8);
void pokemonBiosSetEventGetFlag(void*, u32);
void pokemonBiosSetExp(void*, u32);
void pokemonBiosSetFlagAmari(void*, u8);
void pokemonBiosSetFriend(void*, u16);
void pokemonBiosSetFur(void*, u8);
void pokemonBiosSetFuseiFlag(void*, u8);
void pokemonBiosSetGanbaRibbon(void*, u8);
void pokemonBiosSetHp(void*, u16);
void pokemonBiosSetItemDataId(void*, u16);
void pokemonBiosSetLandRibbon(void*, u8);
void pokemonBiosSetLevel(void*, u8);
void pokemonBiosSetMailId(void*, u8);
void pokemonBiosSetMarineRibbon(void*, u8);
void pokemonBiosSetMaxHp(void*, u16);
void pokemonBiosSetMaxHpEffort(void*, u16);
void pokemonBiosSetMaxHpRnd(void*, u16);
void pokemonBiosSetNationalRibbon(void*, u8);
void pokemonBiosSetNicknamePtr(void*, u16*);
void pokemonBiosSetNimbleness(void*, u16);
void pokemonBiosSetNimblenessEffort(void*, u16);
void pokemonBiosSetNimblenessRnd(void*, u16);
void pokemonBiosSetPara1Amari(void*, u16);
void pokemonBiosSetPcboxMark(void*, u8);
void pokemonBiosSetPhyAtk(void*, u16);
void pokemonBiosSetPhyAtkEffort(void*, u16);
void pokemonBiosSetPhyAtkRnd(void*, u16);
void pokemonBiosSetPhyDef(void*, u16);
void pokemonBiosSetPhyDefEffort(void*, u16);
void pokemonBiosSetPhyDefRnd(void*, u16);
void pokemonBiosSetPokemonDataId(void*, u16);
void pokemonBiosSetPokemonWazaDataId(void*, u16, u16);
void pokemonBiosSetPokemonWazaPp(void*, u16, u8);
void pokemonBiosSetPokemonWazaPpCount(void*, u16, u8);
void pokemonBiosSetPokerus(void*, u8);
void pokemonBiosSetRnd(void*, u32);
void pokemonBiosSetSkyRibbon(void*, u8);
void pokemonBiosSetSpeAtk(void*, u16);
void pokemonBiosSetSpeAtkEffort(void*, u16);
void pokemonBiosSetSpeAtkRnd(void*, u16);
void pokemonBiosSetSpeDef(void*, u16);
void pokemonBiosSetSpeDefEffort(void*, u16);
void pokemonBiosSetSpeDefRnd(void*, u16);
void pokemonBiosSetStrong(void*, u8);
void pokemonBiosSetStrongMedal(void*, u8);
void pokemonBiosSetStyle(void*, u8);
void pokemonBiosSetStyleMedal(void*, u8);
void pokemonBiosSetTamagoFlag(void*, u8);
void pokemonBiosSetTokuseiFlag(void*, u8);
void pokemonBiosSetVictoryRibbon(void*, u8);
void pokemonBiosSetWinningRibbon(void*, u8);
void pokemonBiosSetWorldRibbon(void*, u8);
#ifdef __cplusplus
}
#endif
#endif
