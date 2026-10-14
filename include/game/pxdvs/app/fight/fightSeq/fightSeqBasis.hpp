#ifndef FIGHT_SEQ_BASIS_HPP
#define FIGHT_SEQ_BASIS_HPP
#include <dolphin/types.h>
struct FightOutPokemon;
// ServerWork is the eight-byte command-server record at 0x804e85c0.
// The original accesses its bytes through the fixed SDA base.
struct BasisServerWork { u8 flags[8]; };
struct BasisYokodoriWork {
    FightOutPokemon* attacker;
    FightOutPokemon* result;
};
typedef char BasisServerWorkSize[(sizeof(BasisServerWork) == 8) ? 1 : -1];
typedef char BasisYokodoriWorkSize[(sizeof(BasisYokodoriWork) == 8) ? 1 : -1];
typedef char BasisYokodoriWorkAttackerOffset[(((u32)&((BasisYokodoriWork*)0)->attacker) == 0) ? 1 : -1];
typedef char BasisYokodoriWorkResultOffset[(((u32)&((BasisYokodoriWork*)0)->result) == 4) ? 1 : -1];
// Only the named fields are saved/restored; padding remains untouched.
struct BasisWazaJoutaiBlock { u32 words[36]; };
struct BasisWazaLayout {
    u8 kind; u8 reserved01; u16 move; u16 originalMove; u16 power;
    BasisWazaJoutaiBlock conditions;
    u8 type; u8 critical; u16 reserved9a;
    s32 damage; s32 hitDamage;
    u16 ability; u16 target; u8 slot; u8 count; u16 reservedaA;
};
typedef char BasisWazaLayoutSize[(sizeof(BasisWazaLayout) == 0xac) ? 1 : -1];
typedef char BasisWazaConditionsOffset[((u32)&((BasisWazaLayout*)0)->conditions == 8) ? 1 : -1];
typedef char BasisWazaTypeOffset[((u32)&((BasisWazaLayout*)0)->type == 0x98) ? 1 : -1];
typedef char BasisWazaDamageOffset[((u32)&((BasisWazaLayout*)0)->damage == 0x9c) ? 1 : -1];
typedef char BasisWazaCountOffset[((u32)&((BasisWazaLayout*)0)->count == 0xa9) ? 1 : -1];
typedef char BasisWazaKindOffset[((u32)&((BasisWazaLayout*)0)->kind == 0x0) ? 1 : -1];
typedef char BasisWazaMoveOffset[((u32)&((BasisWazaLayout*)0)->move == 0x2) ? 1 : -1];
typedef char BasisWazaOriginalmoveOffset[((u32)&((BasisWazaLayout*)0)->originalMove == 0x4) ? 1 : -1];
typedef char BasisWazaPowerOffset[((u32)&((BasisWazaLayout*)0)->power == 0x6) ? 1 : -1];
typedef char BasisWazaCriticalOffset[((u32)&((BasisWazaLayout*)0)->critical == 0x99) ? 1 : -1];
typedef char BasisWazaHitdamageOffset[((u32)&((BasisWazaLayout*)0)->hitDamage == 0xa0) ? 1 : -1];
typedef char BasisWazaAbilityOffset[((u32)&((BasisWazaLayout*)0)->ability == 0xa4) ? 1 : -1];
typedef char BasisWazaTargetOffset[((u32)&((BasisWazaLayout*)0)->target == 0xa6) ? 1 : -1];
typedef char BasisWazaSlotOffset[((u32)&((BasisWazaLayout*)0)->slot == 0xa8) ? 1 : -1];
extern "C" {
extern BasisServerWork ServerWork;
extern u16 TSUIKATbl[];
extern u8* TSUIKASeqTbl[];
extern u32 NoHitMsgTbl[];
extern u16 ShimeWazaNo[];
extern u8* WazaEffectTbl[];
}
#endif
