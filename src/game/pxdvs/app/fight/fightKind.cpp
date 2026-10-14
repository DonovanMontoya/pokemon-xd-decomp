#include <game/pxdvs/app/fight/fightKindBiosLayout.hpp>
#pragma dont_inline on
struct FightEncountRecord;
extern "C" {
extern u32* fight_kind_data_number;
extern FightKindBiosLayout* fight_kind_data;
u16 fightGetFightEncountDataId(void);
FightEncountRecord* fightEncountDataBiosGetPtr(u16);
u8 fightEncountDataBiosGetFightKind(FightEncountRecord*);
u8 fightKind_CheckFightKind(u8 kind) {
    return kind == fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));
}
#define FIGHT_KIND_FLAG_GETTER(name, field) u8 fightKindDataBiosGet##name(FightKindBiosLayout* p) { if (p == 0) return 0; return p->field > 0u; }
FIGHT_KIND_FLAG_GETTER(RegulationFlag, regulationFlag)
u32 fightKindDataBiosGetName(FightKindBiosLayout* p) { if (p == 0) return 0; return p->name; }
FIGHT_KIND_FLAG_GETTER(HostEnemyMsgFlag, hostEnemyMsgFlag)
FIGHT_KIND_FLAG_GETTER(PokemonStatusMenuSubbarFlag, pokemonStatusMenuSubbarFlag)
FIGHT_KIND_FLAG_GETTER(DarkpokemonHypermodeFlag, darkpokemonHypermodeFlag)
FIGHT_KIND_FLAG_GETTER(MonohiroiFlag, monohiroiFlag)
FIGHT_KIND_FLAG_GETTER(DorobouFlag, dorobouFlag)
FIGHT_KIND_FLAG_GETTER(BossFlag, bossFlag)
FIGHT_KIND_FLAG_GETTER(KeikentihueruFlag, keikentihueruFlag)
FIGHT_KIND_FLAG_GETTER(DoItemSoubiTokukoutokubouupFlag, doItemSoubiTokukoutokubouupFlag)
FIGHT_KIND_FLAG_GETTER(DoHizukiMiyaburiFlag, doHizukiMiyaburiFlag)
FIGHT_KIND_FLAG_GETTER(DoHizukiAiFlag, doHizukiAiFlag)
FIGHT_KIND_FLAG_GETTER(DoCriticalAttackFlag, doCriticalAttackFlag)
FIGHT_KIND_FLAG_GETTER(GetInfectPokerusFlag, getInfectPokerusFlag)
FIGHT_KIND_FLAG_GETTER(GetFriendFlag, getFriendFlag)
FIGHT_KIND_FLAG_GETTER(GetNekoniKobanFlag, getNekoniKobanFlag)
FIGHT_KIND_FLAG_GETTER(GetOkaneFlag, getOkaneFlag)
FIGHT_KIND_FLAG_GETTER(OkanePoolFlag, okanePoolFlag)
FIGHT_KIND_FLAG_GETTER(GetExpFlag, getExpFlag)
FIGHT_KIND_FLAG_GETTER(DrawFlag, drawFlag)
FIGHT_KIND_FLAG_GETTER(NigeruFlag, nigeruFlag)
FIGHT_KIND_FLAG_GETTER(CallFlag, callFlag)
FIGHT_KIND_FLAG_GETTER(UseItemFlag, useItemFlag)
FIGHT_KIND_FLAG_GETTER(DoZukanTukamaetaFlag, doZukanTukamaetaFlag)
FIGHT_KIND_FLAG_GETTER(DoZukanMitaFlag, doZukanMitaFlag)
FIGHT_KIND_FLAG_GETTER(DoBadgeCheckFlag, doBadgeCheckFlag)
FightKindBiosLayout* fightKindDataBiosGetPtr(u16 index) {
    if (index > *fight_kind_data_number) return 0;
    return (FightKindBiosLayout*)((u8*)fight_kind_data + (u32)index * 0x20);
}
FIGHT_KIND_FLAG_GETTER(BackSaveDataFlag, backSaveDataFlag)
}
