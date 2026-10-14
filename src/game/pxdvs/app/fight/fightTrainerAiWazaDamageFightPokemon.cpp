#include <dolphin/types.h>

#pragma dont_inline on
extern "C" {
struct FIGHT_TRAINER; struct FightOutPokemon; struct FightPokemon;
struct Pokemon; struct FightWaza; struct FightSide;
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
u16 pokemon_GetHp(Pokemon*);
static void _fightTrainerAiWazaDamageFightPokemon203SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon196SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon190SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon135SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon126SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon123SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon122SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon121SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon117SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon104SubPre3__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon104SubPre2__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon104SubPre1__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
static void _fightTrainerAiWazaDamageFightPokemon099SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3);
typedef void (*DamageHook)(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(void *, FIGHT_TRAINER *, FightPokemon **, u8, u8);
u8 fightFloor_GetTikeiDataId(void *);
s16 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon *, u16);
Pokemon * fightOutPokemonGetPokemonPtr(FightOutPokemon *);
FightWaza * fightOutPokemon_GetFightWazaPtr(FightOutPokemon *);
s32 fightSeqGetHukuroDatakiDamage(u16, u16, u8, u16, u8);
u8 fightSeqGetJitabataIryoku(u16, u16);
u16 fightSeqGetKetaguriIryoku(u16);
u16 fightSeqGetOngaesiIryoku(u8);
u16 fightSeqGetYatuatariIryoku(u8);
s32 fightSeqWazaDamageCalcHikaePokemon(FightOutPokemon *, FightPokemon *, FightSide *, u16, u16, s32);
FightSide * fightTargetGetPtrAsNowFightType(u8, void*);
u8 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER *, void *, u8);
u16 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER *, u16);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER *, u16, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiKaragenki(FIGHT_TRAINER *, FightOutPokemon *);
s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(FIGHT_TRAINER *, FightOutPokemon *, u32, FightPokemon *, u8);
u16 fightWaza_GetIryoku(FightWaza *);
void fightWaza_SetIryoku(FightWaza *, u16);
void fightWaza_SetZokusei(FightWaza *, u16);
s32 tikeiDataBiosGetWazaId(u16);
u16 wazaDB_GetSeqId(u32);
u8 joutaiDataBiosGetMaxCount(u16);
u16 pokemonDB_GetWeight(u32);
void pokemonGetMezamerupower(Pokemon *, u16 *, u16 *);
u8 fightTrainerAiGetFightOutPokemonFriend(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonLevel(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonMaxHp(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTrainerAiGetFightOutPokemonPokemonDataId(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightPokemonLevel(FIGHT_TRAINER *, FightPokemon *);
u32 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER *, FightPokemon *);
struct Pokemon; struct FightWaza; struct FightSide;

s32 fightSeqGetWazaDamageHikaePokemon(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*, DamageHook, DamageHook, DamageHook);
s32 fightTrainerAiWazaDamageFightPokemon217(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon216(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon215(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon214(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon213(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon212(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon211(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon210(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon209(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon208(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon207(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon206(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon205(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon204(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon203(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon202(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon201(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon200(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon199(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon198(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon197(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon196(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon195(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon194(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon193(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon192(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon191(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon190(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon189(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon188(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon187(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon186(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon185(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon184(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon183(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon182(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon181(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon180(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon179(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon178(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon177(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon176(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon175(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon174(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon173(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon172(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon171(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon170(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon169(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon168(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon167(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon166(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon165(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon164(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon162(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon161(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon160(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon159(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon158(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon157(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon156(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon155(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon154(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon153(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon152(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon151(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon150(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon149(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon148(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon147(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon146(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon145(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon144(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon143(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon142(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon140(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon139(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon138(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon137(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon136(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon135(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon134(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon133(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon132(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon130(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon129(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon128(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon127(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon126(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon125(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon124(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon123(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon122(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon121(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon120(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon119(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon118(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon117(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon116(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon115(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon114(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon113(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon112(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon111(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon109(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon108(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon107(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon106(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon105(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon104(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon103(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon102(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon101(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon100(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon099(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon098(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon097(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon095(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon094(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon093(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon092(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon091(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon090(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon089(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon088(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon087(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon086(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon085(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon084(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon083(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon082(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon081(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon080(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon079(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon078(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon077(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon076(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon075(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon073(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon072(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon071(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon070(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon069(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon068(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon067(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon066(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon065(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon062(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon060(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon059(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon058(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon057(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon054(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon053(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon052(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon051(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon050(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon049(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon048(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon047(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon046(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon045(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon044(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon043(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon042(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon041(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon040(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon039(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon038(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon037(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon036(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon035(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon034(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon033(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon032(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon031(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon030(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon029(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon028(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon027(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon026(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon025(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon024(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon023(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon020(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon019(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon018(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon017(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon016(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon013(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon011(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon010(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon009(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon008(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon007(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon006(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon005(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon004(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon003(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon002(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon001(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemon000(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
s32 fightTrainerAiWazaDamageFightPokemonNull(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
static s32 _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);

s32 fightTrainerAiWazaDamageFightPokemon217(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon216(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon215(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon214(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon213(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon212(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon211(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon210(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon209(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon002(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon208(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon207(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon206(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon205(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon204(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon202(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon201(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon200(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon004(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon199(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon198(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon197(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon195(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon194(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon193(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon192(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon191(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon188(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon187(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon186(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon185(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon184(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon183(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon182(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon181(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon180(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon179(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon178(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon177(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon176(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon175(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon174(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon172(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon171(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon170(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon168(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon167(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon166(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon165(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon164(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon160(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon159(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon158(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon156(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon155(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon153(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon152(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon151(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon039(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon150(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon149(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon147(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon146(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon145(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon039(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon144(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon143(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon142(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon140(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon139(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon138(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon137(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon136(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon134(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon132(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon133(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon132(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon130(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 20;
}

s32 fightTrainerAiWazaDamageFightPokemon129(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon128(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender) * 2;
}

s32 fightTrainerAiWazaDamageFightPokemon127(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon125(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon124(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon120(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon119(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon118(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon116(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon115(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon114(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon113(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon112(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon111(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon109(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon108(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon107(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon106(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon105(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon103(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon102(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon100(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 5;
}

s32 fightTrainerAiWazaDamageFightPokemon097(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon095(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon094(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon093(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon092(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon090(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon089(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon086(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon085(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon084(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon083(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon082(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon081(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon080(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon079(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon078(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon077(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender) * 2;
}

s32 fightTrainerAiWazaDamageFightPokemon076(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon075(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon039(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon073(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon072(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon071(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon070(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon069(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon068(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon067(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon066(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon065(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon062(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon060(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon059(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon058(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon057(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon054(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon053(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon052(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon051(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon050(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon049(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon048(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon047(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon046(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon045(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon044(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender) * 2;
}

s32 fightTrainerAiWazaDamageFightPokemon043(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon042(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon041(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 40;
}

s32 fightTrainerAiWazaDamageFightPokemon040(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon039(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon036(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon035(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon034(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon033(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon031(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon030(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon029(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender) * 3;
}

s32 fightTrainerAiWazaDamageFightPokemon028(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon027(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon026(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon025(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon024(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon023(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon020(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon019(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon018(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon017(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon016(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon013(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon011(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon010(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon009(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon008(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon007(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon006(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon005(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon004(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon003(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon002(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return fightTrainerAiWazaDamageFightPokemon000(trainer, attacker, move, defender);
}

s32 fightTrainerAiWazaDamageFightPokemon001(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon000(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
}

s32 fightTrainerAiWazaDamageFightPokemonNull(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    return 0;
}

static s32 _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER* trainer, u16 move, FightOutPokemon* attacker, FightPokemon* defender) {
    return fightSeqGetWazaDamageHikaePokemon(trainer, move, attacker, defender, 0, 0, 0);
}

s32 fightTrainerAiWazaDamageFightPokemon203(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    s32 var_r3;
    u8 temp_r31;

    temp_r31 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    var_r3 = fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon203SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
    if (temp_r31 != 0) {
        var_r3 *= 2;
    }
    return var_r3;
}

static void _fightTrainerAiWazaDamageFightPokemon203SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    FightWaza *temp_r3;
    u16 var_r4;
    u8 temp_r31;

    temp_r31 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    temp_r3 = fightOutPokemon_GetFightWazaPtr(arg2);
    switch (temp_r31) {
    case 2:
        var_r4 = 0xB;
        break;
    case 3:
        var_r4 = 5;
        break;
    case 1:
        var_r4 = 0xA;
        break;
    case 4:
        var_r4 = 0xF;
        break;
    default:
        var_r4 = 0;
        break;
    }
    fightWaza_SetZokusei(temp_r3, var_r4);
}

s32 fightTrainerAiWazaDamageFightPokemon196(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon196SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon196SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    FightWaza *temp_r31;

    temp_r31 = fightOutPokemon_GetFightWazaPtr(arg2);
    fightWaza_SetIryoku(temp_r31, fightSeqGetKetaguriIryoku(pokemonDB_GetWeight(fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, arg2))));
}

s32 fightTrainerAiWazaDamageFightPokemon190(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon190SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon190SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    FightWaza *temp_r29;
    u16 temp_r30;
    u16 temp_r31;
    u16 var_r4;

    temp_r29 = fightOutPokemon_GetFightWazaPtr(arg2);
    temp_r30 = fightTrainerAiGetFightOutPokemonNowHp(arg0, arg2);
    temp_r31 = fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg2);
    var_r4 = (u16) ((s32) (fightWaza_GetIryoku(temp_r29) * temp_r30) / (s32) temp_r31);
    if (var_r4 == 0) {
        var_r4 = 1;
    }
    fightWaza_SetIryoku(temp_r29, var_r4);
}

s32 fightTrainerAiWazaDamageFightPokemon173(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    s32 temp_r30;
    u32 temp_r31;

    temp_r30 = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    temp_r31 = (u16)wazaDB_GetSeqId(arg2);
    if (wazaDB_GetSeqId(temp_r30) != temp_r31) {
        return fightTrainerAiWazaDoWazaDamageFightPokemonFunc(arg0, arg1, temp_r30, arg3, 1U);
    }
    return 0;
}

s32 fightTrainerAiWazaDamageFightPokemon169(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    s32 var_r31;

    var_r31 = _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(arg0, arg2, arg1, arg3);
    if (fightTrainerAiIsFightOutPokemonJoutaiKaragenki(arg0, arg1) == 1) {
        var_r31 *= 2;
    }
    return var_r31;
}

s32 fightTrainerAiWazaDamageFightPokemon162(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    s16 var_r0;
    s16 var_r31;

    var_r31 = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x2DU) == 1) {
        var_r31 = fightOutPokemonGetCountAsJoutaiDataId(arg1, 0x2DU);
    }
    var_r0 = joutaiDataBiosGetMaxCount(0x2DU) - var_r31;
    if (var_r0 < 0) {
        var_r0 = 0;
    }
    return -((s32) fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg1) / (s16) (1 << var_r0));
}

s32 fightTrainerAiWazaDamageFightPokemon161(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    s16 var_r31;

    var_r31 = 1;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x2DU) == 1) {
        var_r31 = fightOutPokemonGetCountAsJoutaiDataId(arg1, 0x2DU);
    }
    return var_r31 * _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(arg0, arg2, arg1, arg3);
}

s32 fightTrainerAiWazaDamageFightPokemon157(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return -((fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg1) >> 1U) & 0x7FFF);
}

s32 fightTrainerAiWazaDamageFightPokemon154(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    FightPokemon *sp8[6];
    s32 temp_r30;
    s32 var_r28;
    u32 temp_r25;
    u32 temp_r26;
    u16 temp_r31;
    u16 var_r27;
    u8 temp_r30_2;

    var_r28 = 0;
    temp_r31 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    var_r27 = 0;
    while (var_r27 < temp_r31) {
        temp_r30 = (var_r27 * 4) & 0x3FFFC;
        temp_r26 = fightTrainerAiGetFightPokemonPokemonDataId(arg0, sp8[var_r27]);
        temp_r30_2 = fightTrainerAiGetFightPokemonLevel(arg0, sp8[var_r27]);
        temp_r25 = fightTrainerAiGetFightPokemonPokemonDataId(arg0, arg3);
        var_r28 += fightSeqGetHukuroDatakiDamage(arg2, temp_r26, temp_r30_2, temp_r25, fightTrainerAiGetFightPokemonLevel(arg0, arg3));
        var_r27 += 1;
    }
    return var_r28;
}

s32 fightTrainerAiWazaDamageFightPokemon148(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    s32 var_r31;
    u32 temp_r30;
    u16 temp_r31;

    temp_r30 = (u16)fightTrainerAiGetWazaIryoku(arg0, arg2);
    temp_r31 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    var_r31 = fightSeqWazaDamageCalcHikaePokemon(arg1, arg3, fightTargetGetPtrAsNowFightType(2U, arg3), arg2, temp_r30, temp_r31);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x32U) == 1) {
        var_r31 = (s32) (var_r31 * 0xF) / 10;
    }
    return var_r31;
}

s32 fightTrainerAiWazaDamageFightPokemon135(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon135SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon135SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    u16 spA;
    u16 sp8;
    FightWaza *temp_r31;

    temp_r31 = fightOutPokemon_GetFightWazaPtr(arg2);
    pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(arg2), &spA, &sp8);
    fightWaza_SetIryoku(temp_r31, spA);
    fightWaza_SetZokusei(temp_r31, sp8);
}

s32 fightTrainerAiWazaDamageFightPokemon132(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    s32 var_r0;
    u8 temp_r3;

    temp_r3 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    if (temp_r3 == 0) {
        var_r0 = (fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg1) >> 1U) & 0x7FFF;
    } else if (temp_r3 == 1) {
        var_r0 = (s32) (fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg1) * 0x14) / 30;
    } else {
        var_r0 = (fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg1) >> 2U) & 0x3FFF;
    }
    return -var_r0;
}

s32 fightTrainerAiWazaDamageFightPokemon126(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon126SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon126SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(arg2), 0x46U);
}

s32 fightTrainerAiWazaDamageFightPokemon123(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon123SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon123SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    FightWaza *temp_r3;

    temp_r3 = fightOutPokemon_GetFightWazaPtr(arg2);
    fightWaza_GetIryoku(temp_r3);
    fightWaza_SetIryoku(temp_r3, fightSeqGetYatuatariIryoku(fightTrainerAiGetFightOutPokemonFriend(arg0, arg2)));
}

s32 fightTrainerAiWazaDamageFightPokemon122(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon122SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon122SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(arg2), 0x28U);
}

s32 fightTrainerAiWazaDamageFightPokemon121(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon121SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon121SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    FightWaza *temp_r3;

    temp_r3 = fightOutPokemon_GetFightWazaPtr(arg2);
    fightWaza_GetIryoku(temp_r3);
    fightWaza_SetIryoku(temp_r3, fightSeqGetOngaesiIryoku(fightTrainerAiGetFightOutPokemonFriend(arg0, arg2)));
}

s32 fightTrainerAiWazaDamageFightPokemon117(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon117SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon117SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    FightWaza *temp_r3;
    u16 var_r30;

    temp_r3 = fightOutPokemon_GetFightWazaPtr(arg2);
    var_r30 = fightWaza_GetIryoku(temp_r3);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0x1AU) == 1) {
        var_r30 = (var_r30 * 2) & 0xFFFE;
    }
    fightWaza_SetIryoku(temp_r3, var_r30);
}

s32 fightTrainerAiWazaDamageFightPokemon104(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    s32 temp_r31;
    s32 temp_r31_2;

    temp_r31_2 = fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon104SubPre1__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
    temp_r31 = temp_r31_2 + fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon104SubPre2__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
    return temp_r31 + fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon104SubPre3__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon104SubPre3__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(arg2), 0x1EU);
}

static void _fightTrainerAiWazaDamageFightPokemon104SubPre2__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(arg2), 0x14U);
}

static void _fightTrainerAiWazaDamageFightPokemon104SubPre1__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(arg2), 0xAU);
}

s32 fightTrainerAiWazaDamageFightPokemon099(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return fightSeqGetWazaDamageHikaePokemon(arg0, arg2, arg1, arg3, 0, _fightTrainerAiWazaDamageFightPokemon099SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon, 0);
}

static void _fightTrainerAiWazaDamageFightPokemon099SubPre__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2, FightPokemon *arg3) {
    FightWaza *temp_r31;
    u16 temp_r30;

    temp_r31 = fightOutPokemon_GetFightWazaPtr(arg2);
    temp_r30 = fightTrainerAiGetFightOutPokemonNowHp(arg0, arg2);
    fightWaza_SetIryoku(temp_r31, (u16) fightSeqGetJitabataIryoku(temp_r30, fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg2)));
}

s32 fightTrainerAiWazaDamageFightPokemon098(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return (s32) pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(arg3));
}

s32 fightTrainerAiWazaDamageFightPokemon088(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return (s32) fightTrainerAiGetFightOutPokemonLevel(arg0, arg1);
}

s32 fightTrainerAiWazaDamageFightPokemon087(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return (s32) fightTrainerAiGetFightOutPokemonLevel(arg0, arg1);
}

s32 fightTrainerAiWazaDamageFightPokemon038(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return (s32) pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(arg3));
}

s32 fightTrainerAiWazaDamageFightPokemon037(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return -(s32) fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg1);
}

s32 fightTrainerAiWazaDamageFightPokemon032(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3) {
    return -((fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg1) >> 1U) & 0x7FFF);
}

s32 fightTrainerAiWazaDamageFightPokemon189(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    s32 attackerHp = (u16)fightTrainerAiGetFightOutPokemonNowHp(trainer, attacker);
    u16 defenderHp = pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(defender));
    s32 difference = defenderHp - attackerHp;
    return difference > 0 ? difference : 0;
}
s32 fightTrainerAiWazaDamageFightPokemon101(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    u16 hp = pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(defender));
    s32 damage = _fightTrainerAiWazaDamageFightPokemonNormal__FP13FIGHT_TRAINERUsP15FightOutPokemonP12FightPokemon(trainer, move, attacker, defender);
    if (hp <= damage) damage = hp - 1;
    return damage;
}
s32 fightTrainerAiWazaDamageFightPokemon091(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender) {
    s32 attackerHp = (u16)fightTrainerAiGetFightOutPokemonNowHp(trainer, attacker);
    u16 defenderHp = pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(defender));
    return defenderHp - (s32)(attackerHp + defenderHp) / 2;
}
}
