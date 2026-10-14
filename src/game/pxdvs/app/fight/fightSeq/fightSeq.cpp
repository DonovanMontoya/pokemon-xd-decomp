#include <game/pxdvs/app/fight/fightSeq/fightSeq.hpp>
#undef NULL
#define NULL 0

extern "C" {
typedef struct FIGHT_TRAINER FIGHT_TRAINER; typedef FIGHT_TRAINER FightTrainer;
typedef struct FightOutPokemon FightOutPokemon;
typedef struct FightPokemon FightPokemon;
typedef struct FightSide FightSide;
typedef struct FightTarget FightTarget;
typedef struct FightWaza FightWaza;
typedef struct Hero Hero;
typedef struct HeroPokemonGetParam HeroPokemonGetParam;
typedef struct Pokemon Pokemon;
typedef struct WazaSequence WazaSequence;
char * GSmsgGetGSchar(u32);
void GSthreadSwitch();
u16 HSD_Rand(void);
WazaSequence* Sequence_GetWaza(void*, u16, u32);
void * Sequence_LoadTrainer(u8);
void Sequence_LoadWaza(void*, u16, u32, u8);
void Sequence_SetPosition(void *,f32 *);
void Sequence_SetRotation(void *,f32 *);
void Sequence_SetVisibility(u32, s32);
void WazaSequence_Free(WazaSequence*);
u8 WazaSequence_IsActive(WazaSequence*);
void WazaSequence_Start(WazaSequence*, u32);
void battleGridStoreModelVisibilityFlags();
u32 fightAbicntDoKakeWaru(u8, u32);
void fightAi_FixedActIrekaeInit(u8 *);
u16 fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(void *, s32);
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(void *,u16,u8,FightOutPokemon *);
u8 fightFloorCheckHuuinWazaFightOutPokemon(void*, FightOutPokemon*, u32);
u8 fightFloorCheckWriteJoutaiDataId(void *, s32);
void fightFloorCreateFightOutPokemonPtrAry(void *);
FightOutPokemon * fightFloorGetFightOutPokemonPtrRandom(void *,u8,u8,FightOutPokemon *);
FightTrainer* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*, FightOutPokemon*);
void * fightFloorGetFightOutPokemonPtrToHeroPtr(void *,FightOutPokemon *);
FIGHT_TRAINER * fightFloorGetFightPokemonPtrToFightTrainerPtr(void *, FightPokemon *);
s8 fightFloorGetKaisuuJoutaiDataId(void *, s32);
s8 fightFloorGetNowKaisuuJoutaiDataId(void *, s32);
u8 fightFloorGetNowTenkouDataId(void *, u8);
u16 fightFloorGetValidFightOutPokemonCount(void *,u8,FightOutPokemon *,u8);
FightSide * fightFloorGetValidFightSidePtr(void *,u8);
void fightFloorInitJoutaiDataId(void *, s32);
u8 fightFloorIsJoutaiDataId(void *, s32);
void fightFloorLoopValidFightOutPokemon(void *,s32 (*)(void *,u16,void *),void *,u8);
void fightFloorSetNowKaisuuJoutaiDataId(void *, s32);
void fightFloorSortFightOutPokemonPtrAry(void *, s32);
void fightFloorWriteJoutaiDataId(void *, s32, s32);
FightOutPokemon * fightFloor_GetAttackPokemonPtr(void *);
u8 fightFloor_GetFightKindDarkpokemonHypermodeFlag(void *);
u8 fightFloor_GetFightKindDoBadgeCheckFlag(void *);
s32 fightFloor_GetFightKindDoItemSoubiTokukoutokubouupFlag(void *);
u16 fightFloor_GetFightSideFightOutPokemonSideMax(void *);
u32 fightFloor_GetFightType(void*);
s32 fightFloor_SetAppointItemDataId(void *, u16);
void fightFloor_SetAppointPokemonPtr(void *,FightOutPokemon *);
void fightFloor_SetAttackPokemonPtr(void *, u8 *);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(void *,FightOutPokemon *);
void fightFloor_SetDefensePokemonPtr(void *, u8 *);
void fightFloor_SetItemPokemonPtr(void *,FightOutPokemon *);
void fightFloor_SetKizetuPokemonPtr(void *,FightOutPokemon *);
void fightFloor_SetTuikakoukaPokemonPtr(void *,FightOutPokemon *);
u16 fightGetFightResultId();
void fightMainAllCamera(u32, u32);
void fightMainSetAllDispFlag(s32);
void fightMenuCloseMsg();
void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon*, u8, u32);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(s32, FightOutPokemon*, u8, u32, u32);
void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon*, u8, u32);
void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon*, u8, u32);
void fightMenuOpenMsg(void*);
void fightMsgctrlSetValue(u32,u32);
u8 fightOutPokemonCheckFightOut(FightOutPokemon *);
u8 fightOutPokemonCheckNoAttackFlag(FightOutPokemon *);
u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonCopyAllAbiCnt(FightOutPokemon*, FightOutPokemon*);
void fightOutPokemonCopyJoutaiDataId(FightOutPokemon*, FightOutPokemon*, u16);
void fightOutPokemonDarkPokemonEffect(FightOutPokemon*, u8, u8, u8);
void fightOutPokemonDarkPokemonKaijoEffect(FightOutPokemon*, u8, u8, u8, void*, u8);
u32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon *,u16);
u32 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon*, u16);
u32 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon*, u16);
u32 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon*, u16);
char * fightOutPokemonGetNicknamePtr(FightOutPokemon *);
s8 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon *,u16);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u8 fightOutPokemonGetSex(FightOutPokemon *);
u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon *);
u32 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon*);
s8 fightOutPokemonGetTasteLike(FightOutPokemon *, s32);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon *);
u32 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon*, u16);
u16 fightOutPokemonGetWazaZokuseiDataId(FightOutPokemon *);
void fightOutPokemonInitFightPokemonEnemyAry(FightOutPokemon *, u8 *);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon*);
u8 fightOutPokemonIsAlly(FightOutPokemon *,FightOutPokemon *);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon*);
u8 fightOutPokemonIsHpMantan(FightOutPokemon *);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u8 fightOutPokemonIsJoutaiNormal(FightOutPokemon *);
u32 fightOutPokemonIsNokoriHpFollowing(FightOutPokemon *, u16);
u8 fightOutPokemonIsUseHensinBuff(FightOutPokemon *);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon *, u16);
u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon *,u16);
void fightOutPokemonResetSeqStatus(FightOutPokemon*, u16);
void fightOutPokemonSetHensinFightPokemonStatusId(FightOutPokemon*, u16, u8);
void fightOutPokemonSetHensinPokemonStatusId(FightOutPokemon *,u16,s8,s32);
void fightOutPokemonSetNowKaisuuJoutaiDataId(FightOutPokemon*, u16, s8);
void fightOutPokemonSetOumuWazaDataId(FightOutPokemon *,FightOutPokemon *,u16);
void fightOutPokemonSetTokuseiDataId(FightOutPokemon *, u16);
void fightOutPokemonSetZokuseiDataId(FightOutPokemon *, u8, u16);
void fightOutPokemonWriteJoutaiDataId(FightOutPokemon*, u16, u16);
u8 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntPhyDef(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntSpeAtk(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntSpeDef(FightOutPokemon*);
u8 fightOutPokemon_GetDoIkakuFlag(FightOutPokemon*);
u8 fightOutPokemon_GetDoTraceFlag(FightOutPokemon*);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon*);
u16 fightOutPokemon_GetGamanDamageTargetId(FightOutPokemon*);
int fightOutPokemon_GetGamanDamageValue(FightOutPokemon*);
s32 fightOutPokemon_GetKaigaraDamageValue(FightOutPokemon*);
u8 fightOutPokemon_GetKizetuFlag(FightOutPokemon*);
u8 fightOutPokemon_GetKonranMyselfAttackFlag(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon*);
int fightOutPokemon_GetMyselfDamageAtkValue(FightOutPokemon*);
int fightOutPokemon_GetMyselfDamageSpeValue(FightOutPokemon*);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon*);
u8 fightOutPokemon_GetPassPpdecFlag(FightOutPokemon*);
void* fightOutPokemon_GetSequencePtr(FightOutPokemon*);
u16 fightOutPokemon_GetUseWazaDataId(FightOutPokemon*);
void fightOutPokemon_SetChouhatsuNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetComboFuncId(FightOutPokemon*, u8);
void fightOutPokemon_SetDoIkakuFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetDoTraceFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetHirumuNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetHuuinNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon*, s32);
void fightOutPokemon_SetKanashibariNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetKonranMyselfAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetMahiNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetMeroMeroNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetNamakeFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetOumuWazaAllyDataId(FightOutPokemon*, u16);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
u16 fightSeqCondChgActTypeToPokemonStatusId(u8);
void fightSeqExec(void *,u8 *,void *);
void fightSeqPpdecMonomane(FightOutPokemon *,u8,s32);
u8 fightSeqRegulationOverTwoCheck(u16, FightOutPokemon *);
u8 fightSeqSawaguCheck(u8 *);
FightOutPokemon * fightSeqSelectDefensePokemonPtr(FightOutPokemon *, u16, u8, void *, u8, u8, s16);
void fightSeqTuikaAct(u8,u8);
s8 fightSideGetKaisuuJoutaiDataId(u8 *, s32);
s8 fightSideGetNowKaisuuJoutaiDataId(u8 *, s32);
void fightSideInitJoutaiDataId(u8 *, s32);
u8 fightSideIsJoutaiDataId(FightSide *, u16);
void fightSideSetNowKaisuuJoutaiDataId(u8 *, s32);
FightOutPokemon * fightTargetGetPtr(u8,FightOutPokemon *);
void * fightTargetGetPtrAsNowFightType(u8, FightOutPokemon *);
FightOutPokemon* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u32, u16);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u8);
Hero * fightTrainer_GetHeroPtr(FIGHT_TRAINER *);
void fightTrainer_SetOkaneBai(FIGHT_TRAINER *, s32);
s32 fightWazaBiosCopy(void *, void *);
u8 fightWazaCheckWriteJoutaiDataId(FightWaza*, u16);
void fightWazaCreate(void *, s32, u16, u8, s32);
u8 fightWazaIsHit(FightWaza*);
void fightWazaSetUseWazaStatus(void *, s32);
void fightWazaWriteJoutaiDataId(FightWaza*, u16, u32);
u8 fightWaza_GetCritical(FightWaza*);
u32 fightWaza_GetDamage(FightWaza*);
void fightWaza_SetDamage(FightWaza*, u32);
u8 figthOutPokemonGetLevel(FightOutPokemon *);
u16 figthOutPokemonGetPokemonDataId(FightOutPokemon *);
u32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon*);
u32 heroGetStatus(Hero*, u32, u32);
u32 joutaiDataBiosGetName(u16);
u8 pokemonDB_GetTokuseiDataId(u16, u8);
u8 pokemonGetDarkPokemonHyperJoutaiKakuritu();
u32 pokemonGetJoutaiMsgId(Pokemon *);
void pokemonGetSoubiItemBuff();
u16 pokemonGetSoubiItemSoubiDataId();
s32 pokemonGetStatus(Pokemon *,u32,u16,u16);
void pokemonInitJoutai(Pokemon *);
u8 pokemonIsDarkPokemon(Pokemon *);
u8 pokemonIsJoutaiNormal(Pokemon *);
s8 pokemonSearchWazaDataId(Pokemon *, u16);
void pokemonSetStatus(Pokemon *,u32,u16,u16,u32);
u32 pokemonTokuseiDataBiosGetName(void *);
void * pokemonTokuseiDataBiosGetPtr(u16);
u8 pokemonWazaCheckValid(Pokemon*, u16);
u8 pokemonWazaGetMaxPP(Pokemon *, u8);
u16 pokemon_GetHp(Pokemon *);
u32 pokemon_GetMaxHp(Pokemon*);
u32 pokemon_GetPhyAtk(Pokemon*);
u32 pokemon_GetPhyDef(Pokemon*);
u16 pokemon_GetPokemonDataId(Pokemon *);
u16 pokemon_GetPokemonWazaDataId(Pokemon *, u8);
u32 pokemon_GetPokemonWazaPp(Pokemon*, u16);
u32 pokemon_GetSpeAtk(Pokemon*);
u32 pokemon_GetSpeDef(Pokemon*);
u8 pokemon_GetTokuseiFlag(Pokemon *);
void pokemon_SetPokemonWazaPp(Pokemon *,u16,u32);
u32 tasteDataGetNigateMsgDataId(void *);
void * tasteDataGetPtr(u16);
u8 tenkouDataBiosGetSolarFlag(u8);
u8 wazaCheckDarkWaza(u16);
u8 wazaDB_GetBouon(u16);
u8 wazaDB_GetDageki(u16);
u32 wazaDB_GetIryoku(u32);
u32 wazaDB_GetName(u16);
u8 wazaDB_GetOujanosirusi(u16);
u8 wazaDB_GetRangeId(u16);
u16 wazaDB_GetSeqId(u16);
u8 wazaDB_GetZokuseiDataId(u16);
void wazaSequenceSysFreeAllWaza(void);
u8 waza_GetZokuseiKindData(u16);
u32 zokuseiBiosGetName(u16);
u8 zokuseiBiosGetWazaKind(u32);
s32 _SideConditionCheck2SubHorobinouta__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _SideConditionCheck2SubMiraiyoti__FPvUsPv(void *arg0, u16 arg1, void *arg2);
u8 _fightSeqCheckFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2, u16 arg3);
s32 _fightSeqFightOutPokemonTokuseiCheckIkakuSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqFightOutPokemonTokuseiCheckTenkiyaSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqFightOutPokemonTokuseiCheckTraceSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAllSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqFloorJoutaiCheckSubGetSeqFightOutPokemonPtr__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqFloorJoutaiCheckSubNegaigoto__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqGetExpCheckSubSoubiItemCheckTurn__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqGetExpCheckSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
u8 _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2, u16 arg3);
s32 _fightSeqIrekaeInitSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqKizetuInitSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqSideJoutaiCheckSubSawagu__FPvUsPv(void *arg0, u16 arg1, void *arg2);
s32 _fightSeqSideJoutaiCheckSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
u8 *_fightSeqSoubiItemCheckTurnSubAbiCntUp__FP15FightOutPokemonUclUcUcUc(FightOutPokemon *arg0, u8 arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5);
u8 *_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(FightOutPokemon *arg0, u16 arg1, u8 *arg2);
u8 *_fightSeqSoubiItemCheckTurnSubTasteHpkaihuku__FP15FightOutPokemonUsUcUsUslP10FIGHT_WAZA(FightOutPokemon *arg0, u16 arg1, u8 arg2, u16 arg3, u16 arg4, s32 arg5, FightWaza *arg6);
s32 _fightSeqSoubiItemCheckWazaHitAfterAllSub__FPvUsPv(void *arg0, u16 arg1, void *arg2);
void fightSeqCheckSetHensinBuffToMotoFightPokemon(FightOutPokemon *arg0, u16 arg1);
void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon *arg0, u16 arg1);
void fightSeqCheckZenmetu(void);
u8 fightSeqFightOutPokemonTokuseiCheckTenkiya(void);
u8 fightSeqTokuseiTenkiyaAct__FP15FightOutPokemon(FightOutPokemon *arg0);
u16 fightSeqWazaDamageCalc(FightOutPokemon *arg0, FightOutPokemon *arg1, u8 arg2, u16 arg3, u32 arg4, u16 arg5);
u8 fightSeqAttackPokemonJoutaiCheck(void);
void fightSeqCheckSetHensinBuffToMotoPokemon2(FightOutPokemon *arg0, u16 arg1, s8 arg2, s32 arg3);
void fightSeqFightOutPokemonTokuseiCheckSinkuroAtk(FightOutPokemon *arg0, FightOutPokemon *arg1);
void fightSeqFightOutPokemonTokuseiCheckSinkuroDef(FightOutPokemon *arg0, FightOutPokemon *arg1);
u8 fightSeqFightOutPokemonTokuseiCheckWazaHit(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2);
u8 fightSeqFightOutPokemonTokuseiCheckWazaHitAfter(FightOutPokemon *arg0, FightOutPokemon *arg1);
void fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAll(void);
u8 fightSeqFightOutPokemonTokuseiCheckWazaHitBefore(FightOutPokemon *arg0, FightOutPokemon *arg1);
void fightSeqKizetuInit(FightOutPokemon *arg0);
void fightSeqPressurePpdecCheck(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2);
void fightSeqSoubiItemCheckWazaHitAfter(FightOutPokemon *arg0, FightOutPokemon *arg1);
void fightSeqSoubiItemCheckWazaHitAfterAll(void);
void fightSeq_CallWazaSeq(u8 *arg0);
u8 *fightSeq_GetWazaSeqPtr_u8(u8 arg0);
void fightSeq_JumpWazaSeq(u8 *arg0);
void fightSeq_NextWazaSeq(u32 arg0);
u8 *fightSeq_GetWazaSeq(void);
void fightSeq_CallWazaSeqCustom(void *arg0, u8 *arg1, void *arg2);
u8 *fightSeq_GetWazaSeqAdr(u32 arg0);
void fightSeq_ClearUserWork(void);
void *fightEvtGetSequence(void);
void fightEvtSetSequence(void *arg0);
extern SeqServerWork ServerWork;
extern u8 *UserWork;
extern void *fight_seq_now_fight_action_ptr;
extern void *kureinSequencePtr;
extern u8 *TSUIKASeqTbl[];
extern const SeqItemTypePower SoubiItemWazaTypePowUpTbl[];
extern const u16 fight_seq_status_id[];
extern s32 ServerStatusFlag;
extern s32 fight_seq_gaman_damage;
extern u8 fight_seq_tuika_param;
extern u8 fightseq_attack_pokemon_joutai_check_buff;
extern u8 WAZA_AbareruEnd[];
extern u8 WAZA_AddNemuri2[];
extern u8 WAZA_Akumu[];
extern u8 WAZA_Amefuri[];
extern u8 WAZA_Amehurashi[];
extern u8 WAZA_Ameukezara[];
extern u8 WAZA_Bouon[];
extern u8 WAZA_Chouhatsu2[];
extern u8 WAZA_Dappi[];
extern u8 WAZA_Dokudoku[];
extern u8 WAZA_EncoreEnd[];
extern u8 WAZA_Gaman[];
extern u8 WAZA_GamanFaild[];
extern u8 WAZA_GamanOff[];
extern u8 WAZA_GetEXP[];
extern u8 WAZA_Handou[];
extern u8 WAZA_Hare[];
extern u8 WAZA_HareEnd[];
extern u8 WAZA_Hensyoku[];
extern u8 WAZA_Hideri[];
extern u8 WAZA_Hirumu[];
extern u8 WAZA_Honoonokarada[];
extern u8 WAZA_Horobinouta[];
extern u8 WAZA_Horobinoutaing[];
extern u8 WAZA_Huuin[];
extern u8 WAZA_Ikaku[];
extern u8 WAZA_IkakuAct[];
extern u8 WAZA_ItemAbiKaifuku[];
extern u8 WAZA_ItemAbiKaifuku2[];
extern u8 WAZA_ItemCondUp[];
extern u8 WAZA_ItemCriticalUp[];
extern u8 WAZA_ItemHPKaifuku[];
extern u8 WAZA_ItemHPKaifukuEveryTurn[];
extern u8 WAZA_ItemHPKaifukuEveryTurn2[];
extern u8 WAZA_ItemHPKaifukuKonran[];
extern u8 WAZA_ItemNoDoku[];
extern u8 WAZA_ItemNoDoku2[];
extern u8 WAZA_ItemNoJoutaiijou[];
extern u8 WAZA_ItemNoJoutaiijou2[];
extern u8 WAZA_ItemNoKonran[];
extern u8 WAZA_ItemNoKonran2[];
extern u8 WAZA_ItemNoKoori[];
extern u8 WAZA_ItemNoKoori2[];
extern u8 WAZA_ItemNoMahi[];
extern u8 WAZA_ItemNoMahi2[];
extern u8 WAZA_ItemNoNemuri[];
extern u8 WAZA_ItemNoNemuri2[];
extern u8 WAZA_ItemNoYakedo[];
extern u8 WAZA_ItemNoYakedo2[];
extern u8 WAZA_ItemPPKaifuku[];
extern u8 WAZA_Kanashibari[];
extern u8 WAZA_KanashibariEnd[];
extern u8 WAZA_Kasokusouti[];
extern u8 WAZA_Konran[];
extern u8 WAZA_KonranEnd[];
extern u8 WAZA_Koori[];
extern u8 WAZA_Mahi[];
extern u8 WAZA_Melt[];
extern u8 WAZA_Meromero[];
extern u8 WAZA_MeromeroBody[];
extern u8 WAZA_MeromeroNext[];
extern u8 WAZA_Mezame[];
extern u8 WAZA_Miraiyochi[];
extern u8 WAZA_Moraibi[];
extern u8 WAZA_MoraibiPPDec[];
extern u8 WAZA_NOKaifuku[];
extern u8 WAZA_NOKaifukuPPDec[];
extern u8 WAZA_Namakeru[];
extern u8 WAZA_Negaigoto[];
extern u8 WAZA_Nemuru[];
extern u8 WAZA_Newoharu[];
extern u8 WAZA_Noroi[];
extern u8 WAZA_Null[];
extern u8 WAZA_ReflecEnd[];
extern u8 WAZA_Revers[];
extern u8 WAZA_Samehada[];
extern u8 WAZA_Sawagu[];
extern u8 WAZA_SawaguMezame[];
extern u8 WAZA_Shime[];
extern u8 WAZA_ShimeEnd[];
extern u8 WAZA_ShinpiEnd[];
extern u8 WAZA_Sinkuro[];
extern u8 WAZA_SpeabiNoJoutaiijou[];
extern u8 WAZA_Sunaokosi[];
extern u8 WAZA_Tenkiya[];
extern u8 WAZA_Trace[];
extern u8 WAZA_Tyosui[];
extern u8 WAZA_TyosuiPPDec[];
extern u8 WAZA_WeatherDamage[];
extern u8 WAZA_WeatherDamageEnd[];
extern u8 WAZA_Yadorigi[];
extern u8 WAZA_Yakedo[];
extern u8 WAZA_Zenmetsu[];
extern u8 WAZA_AddDoku[];
extern u8 WAZA_AddDokudoku[];
extern u8 WAZA_AddHanekaeri[];
extern u8 WAZA_AddKonran[];
extern u8 WAZA_AddKoori[];
extern u8 WAZA_AddMahi[];
extern u8 WAZA_AddNekonikoban[];
extern u8 WAZA_AddNemuri[];
extern u8 WAZA_AddSawagu[];
extern u8 WAZA_AddShime[];
extern u8 WAZA_AddYakedo[];


// Shared sequence state: pointers, flags, and accumulated damage.
u8 *UserWork;
static u8 *_wazaSeqAdrs;
void *fight_seq_now_fight_action_ptr;
void *kureinSequencePtr;
s32 ServerStatusFlag;
s32 fight_seq_gaman_damage;
u8 fight_seq_tuika_param;
u8 fightseq_attack_pokemon_joutai_check_buff;
SeqServerWork ServerWork = {{0,0,0,0,0,0,0,0}};
const u16 fight_seq_status_id[7] = {0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec};
const SeqItemTypePower SoubiItemWazaTypePowUpTbl[17] = {
 {31,6},{42,8},{46,4},{47,5},{48,12},{49,17},{50,1},{51,13},{52,11},
 {53,2},{54,3},{55,15},{56,7},{57,14},{58,10},{59,16},{60,0}
};

u8 *TSUIKASeqTbl[0x27] = {
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddDoku,
    WAZA_AddYakedo,
    WAZA_AddKoori,
    WAZA_AddMahi,
    WAZA_AddDokudoku,
    WAZA_AddKonran,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddSawagu,
    WAZA_AddNekonikoban,
    WAZA_AddNemuri,
    WAZA_AddShime,
    WAZA_AddHanekaeri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddNemuri,
    WAZA_AddHanekaeri,
};


void fightSeq_ClearUserWork(void) {
    memset(UserWork, 0, 1U);
}

u8 *fightSeq_GetWazaSeqPtr_u8(u8 arg0) {
    return *(u8 **)(_wazaSeqAdrs + arg0);
}

void fightSeq_CallWazaSeqCustom(void *arg0, u8 *arg1, void *arg2) {
    fightSeqExec(arg0, arg1, arg2);
}

void fightSeq_CallWazaSeq(u8 *arg0) {
    fightSeqExec(fight_seq_now_fight_action_ptr, arg0, NULL);
}

void fightSeq_JumpWazaSeq(u8 *arg0) {
    _wazaSeqAdrs = arg0;
}

void fightSeq_NextWazaSeq(u32 arg0) {
    _wazaSeqAdrs = &_wazaSeqAdrs[arg0];
}

u8 *fightSeq_GetWazaSeqAdr(u32 arg0) {
    return &_wazaSeqAdrs[arg0];
}

u8 *fightSeq_GetWazaSeq(void) {
    return _wazaSeqAdrs;
}

void fightSeqSoubiItemCheckWazaHitAfterAll(void) {
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqSoubiItemCheckWazaHitAfterAllSub__FPvUsPv, NULL, 0U);
}

s32 _fightSeqSoubiItemCheckWazaHitAfterAllSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    u8 var_r30;
    Pokemon *temp_r29;
    u8 *var_r28;
    u32 temp_r27;
    s32 temp_r27_2;
    u16 var_r26;
    u16 temp_r26;

    var_r30 = 0;
    temp_r29 = fightOutPokemonGetPokemonPtr(arg0);
    temp_r26 = fightOutPokemonGetSoubiItemDataId(arg0);
    temp_r27 = fightOutPokemonGetSoubiItemSoubiDataId(arg0);
    figthOutPokemonGetSoubiItemBuff(arg0);
    var_r28 = NULL;
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    fightFloor_SetAppointItemDataId(NULL, temp_r26);
    switch ((u16) temp_r27) {
    case 2:
        var_r28 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 5U, WAZA_ItemNoMahi2);
        if (var_r28 != NULL) {
            var_r30 = 1;
        }
        break;
    case 4:
        var_r28 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 3U, WAZA_ItemNoDoku2);
        if (var_r28 != NULL) {
            var_r30 = 1;
        } else {
            var_r28 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 4U, WAZA_ItemNoDoku2);
            if (var_r28 != NULL) {
                var_r30 = 1;
            }
        }
        break;
    case 5:
        var_r28 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 6U, WAZA_ItemNoYakedo2);
        if (var_r28 != NULL) {
            var_r30 = 1;
        }
        break;
    case 6:
        var_r28 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 7U, WAZA_ItemNoKoori2);
        if (var_r28 != NULL) {
            var_r30 = 1;
        }
        break;
    case 3:
        var_r28 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 8U, WAZA_ItemNoNemuri2);
        if (var_r28 != NULL) {
            var_r30 = 1;
        }
        break;
    case 8:
        var_r28 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 9U, WAZA_ItemNoKonran2);
        if (var_r28 != NULL) {
            var_r30 = 2;
        }
        break;
    case 28:
        var_r28 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 0xAU, WAZA_ItemNoJoutaiijou2);
        if (var_r28 != NULL) {
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(0xAU))));
            ServerWork.flags[5] = 0;
            var_r30 = 2;
        }
        break;
    case 9:
        if ((fightOutPokemonIsJoutaiNormal(arg0) == 0) || (fightOutPokemonIsJoutaiDataId(arg0, 9U) == 1)) {
            ServerWork.flags[5] = 0;
            if ((fightOutPokemonIsJoutaiDataId(arg0, 3U) == 1) || (fightOutPokemonIsJoutaiDataId(arg0, 4U) == 1)) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(3U))));
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 8U) == 1) {
                fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(8U))));
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 5U) == 1) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(5U))));
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 6U) == 1) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(6U))));
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 7U) == 1) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(7U))));
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 9U) == 1) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(9U))));
            }
            pokemonInitJoutai((Pokemon *) temp_r29);
            fightOutPokemonInitJoutaiDataId(arg0, 9U);
            fightOutPokemonResetSeqStatus(arg0, 0U);
            var_r30 = 1;
            var_r28 = WAZA_ItemNoJoutaiijou2;
        }
        break;
    case 23:
        var_r26 = 0;
        while (var_r26 < 7U) {
            temp_r27_2 = (var_r26 * 2) & 0x1FFFE;
            if (pokemonGetStatus((Pokemon *) arg0, 0U, *(fight_seq_status_id + temp_r27_2), 0U) < 6) {
                pokemonSetStatus((Pokemon *) arg0, 0U, *(fight_seq_status_id + temp_r27_2), 0U, 6U);
                var_r30 = 5;
            }
            var_r26 += 1;
        }
        if (var_r30 != 0) {
            var_r28 = WAZA_ItemAbiKaifuku2;
        }
        break;
    }
    if (var_r30 != 0) {
        fightFloor_SetAppointPokemonPtr(NULL, arg0);
        fightFloor_SetItemPokemonPtr(NULL, arg0);
        if (var_r30 == 1) {
            fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
        }
        if (var_r28 != NULL) {
            fightSeq_CallWazaSeq(var_r28);
        }
    }
    return 1;
}

void fightSeqSoubiItemCheckWazaHitAfter(FightOutPokemon *arg0, FightOutPokemon *arg1) {
    s32 var_r4;
    u32 temp_r31;
    FightWaza *temp_r30;
    u32 temp_r26;
    s32 temp_r26_2;
    s32 temp_r25;
    s32 temp_r24;
    u16 temp_r23;
    u8 temp_r23_2;
    u8 temp_r22;
    u16 temp_r21;
    u8 *temp_r21_2;

    temp_r30 = fightOutPokemon_GetFightWazaPtr(arg0);
    temp_r21 = fightOutPokemonGetSoubiItemDataId(arg0);
    temp_r26 = fightOutPokemonGetSoubiItemSoubiDataId(arg0);
    temp_r31 = figthOutPokemonGetSoubiItemBuff(arg0);
    fightOutPokemonGetSoubiItemDataId(arg1);
    fightOutPokemonGetSoubiItemSoubiDataId(arg1);
    figthOutPokemonGetSoubiItemBuff(arg1);
    if (fightWaza_GetDamage(temp_r30) == 0) {
        return;
    }
    temp_r23 = fightOutPokemon_GetUseWazaDataId(arg0);
    temp_r22 = fightWazaIsHit(temp_r30);
    temp_r23_2 = wazaDB_GetOujanosirusi(temp_r23);
    temp_r24 = fightOutPokemon_GetMyselfDamageAtkValue(arg1);
    temp_r25 = fightOutPokemon_GetMyselfDamageSpeValue(arg1);
    temp_r26_2 = fightOutPokemon_GetKaigaraDamageValue(arg1);
    switch ((s32) (u16) temp_r26) {                 /* irregular */
    case 0x1E:
        if ((temp_r22 == 1) && (((s16) temp_r24 != 0) || ((s16) temp_r25 != 0)) && (temp_r23_2 == 1) && ((s32) (HSD_Rand() % 100) < (s32) temp_r31) && (fightOutPokemonCheckFightOut(arg1) == 1)) {
            ServerWork.flags[3] = 8;
            temp_r21_2 = fightSeq_GetWazaSeq();
            fightSeqTuikaAct(0U, 0U);
            fightSeq_JumpWazaSeq(temp_r21_2);
        }
        break;
    case 0x3E:
        if ((temp_r22 == 1) && (temp_r26_2 != 0) && ((u32) temp_r26_2 != -1U) && (arg0 != arg1) && (fightOutPokemonIsHpMantan(arg0) == 0) && (fightOutPokemonCheckFightOut(arg0) == 1)) {
            fightFloor_SetAppointItemDataId(NULL, temp_r21);
            fightFloor_SetItemPokemonPtr(NULL, arg0);
            fightFloor_SetAppointPokemonPtr(NULL, arg0);
            var_r4 = -(temp_r26_2 / (s32) temp_r31);
            if (var_r4 == 0) {
                var_r4 = -1;
            }
            fightWaza_SetDamage(temp_r30, (u32) var_r4);
            fightOutPokemon_SetKaigaraDamageValue(arg1, 0);
            fightSeq_CallWazaSeq(WAZA_ItemHPKaifukuEveryTurn2);
        }
        break;
    }
}

u8 fightSeqSoubiItemCheckTurn(FightOutPokemon *arg0, u8 arg1) {
    s32 choices[5] = {-1,-1,-1,-1,-1};
    u8 abilityTypes[5] = {1,2,3,4,5};
    u32 var_r5;
    u8 var_r5_2;
    u16 var_r5_3;
    u16 var_r5_4;
    void *temp_r4;
    s32 temp_r4_2;
    Pokemon *temp_r3;
    u8 var_r30;
    u8 temp_r3_2;
    u8 temp_r3_3;
    u16 temp_r29;
    Pokemon *temp_r29_2;
    u8 var_r28;
    u32 temp_r27;
    u8 *var_r26;
    u16 var_r25;
    u16 temp_r25;
    u16 var_r25_2;
    u32 temp_r25_2;
    u16 var_r24;
    u16 var_r24_2;
    FightWaza *temp_r22;
    s32 temp_r22_2;
    u16 var_r21;
    u16 var_r20;
    u32 temp_r20;
    u8 temp_r20_2;
    SeqServerWork *temp_r20_3;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;

    var_r30 = 0;
    var_r26 = NULL;
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 0U;
    }
    temp_r25 = fightOutPokemonGetSoubiItemDataId(arg0);
    temp_r20 = fightOutPokemonGetSoubiItemSoubiDataId(arg0);
    temp_r27 = figthOutPokemonGetSoubiItemBuff(arg0);
    temp_r22 = fightOutPokemon_GetFightWazaPtr(arg0);
    temp_r3 = fightOutPokemonGetPokemonPtr(arg0);
    temp_r29 = pokemon_GetHp(temp_r3);
    temp_r25_2 = pokemon_GetMaxHp(temp_r3);
    fightFloor_SetAppointItemDataId(NULL, temp_r25);
    switch ((u16) temp_r20) {                       /* switch 1 */
    case 1:                                         /* switch 1 */
        if (((fightOutPokemonIsNokoriHpFollowing(arg0, 2U) != 0) && (arg1 == 0)) || ((fightOutPokemonIsHpMantan(arg0) == 0) && (arg1 == 2))) {
            var_r5 = temp_r27;
            if ((s32) (temp_r29 + temp_r27) > (s32) (u16) temp_r25_2) {
                var_r5 = (u16) temp_r25_2 - temp_r29;
            }
            fightWaza_SetDamage(temp_r22, (u32) -(s32) var_r5);
            var_r30 = 4;
            var_r26 = WAZA_ItemHPKaifuku;
        }
        break;
    case 7:                                         /* switch 1 */
        if ((arg1 == 0) || (arg1 == 2)) {
            var_r25 = 0;
            temp_r29_2 = fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(arg0));
loop_17:
            if (var_r25 < 4U) {
                if ((pokemonWazaCheckValid(temp_r29_2, var_r25) == 0) || (var_r24 = pokemon_GetPokemonWazaDataId(temp_r29_2, (u8) var_r25), temp_r3_2 = pokemon_GetPokemonWazaPp(temp_r29_2, var_r25), var_r28 = temp_r3_2, ((temp_r3_2 == 0) == 0))) {
                    var_r25 += 1;
                    goto loop_17;
                }
            }
            if (var_r25 != 4) {
                temp_r3_3 = pokemonWazaGetMaxPP(temp_r29_2, (u8) var_r25);
                temp_r4_2 = var_r28 + temp_r27;
                var_r5_2 = (u8) temp_r4_2;
                if (temp_r4_2 > (s32) temp_r3_3) {
                    var_r5_2 = temp_r3_3;
                }
                pokemon_SetPokemonWazaPp(temp_r29_2, (s8) var_r25, (u32) var_r5_2);
                fightSeqPpdecMonomane(arg0, (s8) (u8) var_r25, 1);
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(wazaDB_GetName(var_r24))));
                var_r30 = 3;
                var_r26 = WAZA_ItemPPKaifuku;
            }
        }
        break;
    case 23:                                        /* switch 1 */
        var_r20 = 0;
        while (var_r20 < 7U) {
            temp_r22_2 = (var_r20 * 2) & 0x1FFFE;
            if (pokemonGetStatus((Pokemon *) arg0, 0U, *(const u16 *)((const u8 *)fight_seq_status_id + temp_r22_2), 0U) < 6) {
                pokemonSetStatus((Pokemon *) arg0, 0U, *(const u16 *)((const u8 *)fight_seq_status_id + temp_r22_2), 0U, 6U);
                var_r30 = 5;
            }
            var_r20 += 1;
        }
        if (var_r30 != 0) {
            var_r26 = WAZA_ItemAbiKaifuku;
        }
        break;
    case 43:                                        /* switch 1 */
        if (((fightOutPokemonIsHpMantan(arg0) == 0) && (arg1 == 0)) || ((fightOutPokemonIsHpMantan(arg0) == 0) && (arg1 == 2))) {
            var_r5_3 = fightOutPokemonMaxHpWaruValue(arg0, 0x10U);
            if ((s32) (temp_r29 + var_r5_3) > (s32) (u16) temp_r25_2) {
                var_r5_3 = (u16) temp_r25_2 - temp_r29;
            }
            fightWaza_SetDamage(temp_r22, (u32) -(s32) var_r5_3);
            var_r30 = 4;
            var_r26 = WAZA_ItemHPKaifukuEveryTurn;
        }
        break;
    case 10:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku__FP15FightOutPokemonUsUcUsUslP10FIGHT_WAZA(arg0, 0U, arg1, temp_r29, (u16) temp_r25_2, (s32) temp_r27, temp_r22);
        if (var_r26 != NULL) {
            var_r30 = 4;
        }
        break;
    case 11:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku__FP15FightOutPokemonUsUcUsUslP10FIGHT_WAZA(arg0, 1U, arg1, temp_r29, (u16) temp_r25_2, (s32) temp_r27, temp_r22);
        if (var_r26 != NULL) {
            var_r30 = 4;
        }
        break;
    case 12:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku__FP15FightOutPokemonUsUcUsUslP10FIGHT_WAZA(arg0, 2U, arg1, temp_r29, (u16) temp_r25_2, (s32) temp_r27, temp_r22);
        if (var_r26 != NULL) {
            var_r30 = 4;
        }
        break;
    case 13:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku__FP15FightOutPokemonUsUcUsUslP10FIGHT_WAZA(arg0, 3U, arg1, temp_r29, (u16) temp_r25_2, (s32) temp_r27, temp_r22);
        if (var_r26 != NULL) {
            var_r30 = 4;
        }
        break;
    case 14:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubTasteHpkaihuku__FP15FightOutPokemonUsUcUsUslP10FIGHT_WAZA(arg0, 4U, arg1, temp_r29, (u16) temp_r25_2, (s32) temp_r27, temp_r22);
        if (var_r26 != NULL) {
            var_r30 = 4;
        }
        break;
    case 15:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubAbiCntUp__FP15FightOutPokemonUclUcUcUc(arg0, arg1, (s32) temp_r27, 1U, 0x10U, 0xFU);
        if (var_r26 != NULL) {
            var_r30 = 5;
        }
        break;
    case 16:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubAbiCntUp__FP15FightOutPokemonUclUcUcUc(arg0, arg1, (s32) temp_r27, 2U, 0x10U, 0x10U);
        if (var_r26 != NULL) {
            var_r30 = 5;
        }
        break;
    case 17:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubAbiCntUp__FP15FightOutPokemonUclUcUcUc(arg0, arg1, (s32) temp_r27, 3U, 0x10U, 0x11U);
        if (var_r26 != NULL) {
            var_r30 = 5;
        }
        break;
    case 18:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubAbiCntUp__FP15FightOutPokemonUclUcUcUc(arg0, arg1, (s32) temp_r27, 4U, 0x10U, 0x12U);
        if (var_r26 != NULL) {
            var_r30 = 5;
        }
        break;
    case 19:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubAbiCntUp__FP15FightOutPokemonUclUcUcUc(arg0, arg1, (s32) temp_r27, 5U, 0x10U, 0x13U);
        if (var_r26 != NULL) {
            var_r30 = 5;
        }
        break;
    case 20:                                        /* switch 1 */
        if (((arg1 == 0) || (arg1 == 2)) && (fightOutPokemonIsNokoriHpFollowing(arg0, (u16) temp_r27) != 0) && (fightOutPokemonCheckWriteJoutaiDataId(arg0, 0xFU) == 2)) {
            fightOutPokemonWriteJoutaiDataId(arg0, 0xFU, 0U);
            var_r30 = 2;
            var_r26 = WAZA_ItemCriticalUp;
        }
        break;
    case 21:                                        /* switch 1 */
        if (((arg1 == 0) || (arg1 == 2)) && (fightOutPokemonIsNokoriHpFollowing(arg0, (u16) temp_r27) != 0)) {
            var_r24_2 = 0;
            var_r5_4 = 0;
            while (var_r5_4 < 5U) {
                temp_r0 = (var_r5_4 * 4) & 0x3FFFC;
                var_r5_4 += 1;
                *(s32 *)((u8 *)choices + temp_r0) = -1;
            }
            var_r25_2 = 0;
            while (var_r25_2 < 5U) {
                temp_r20_2 = abilityTypes[var_r25_2];
                if (pokemonGetStatus((Pokemon *) arg0, 0U, fightSeqCondChgActTypeToPokemonStatusId(temp_r20_2), 0U) < 0xCU) {
                    temp_r0_2 = (var_r24_2 * 4) & 0x3FFFC;
                    var_r24_2 += 1;
                    *(s32 *)((u8 *)choices + temp_r0_2) = (s32) temp_r20_2;
                }
                var_r25_2 += 1;
            }
            if (var_r24_2 >= 1U) {
                temp_r0_3 = choices[(u16)(HSD_Rand() % var_r24_2)];
                if (temp_r0_3 != -1) {
                    var_r26 = _fightSeqSoubiItemCheckTurnSubAbiCntUp__FP15FightOutPokemonUclUcUcUc(arg0, arg1, (s32) temp_r27, (u8) temp_r0_3, 0x20U, (u8) ((u8) temp_r0_3 + 0x26));
                    if (var_r26 != NULL) {
                        var_r30 = 5;
                    }
                }
            }
        }
        break;
    case 2:                                         /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 5U, WAZA_ItemNoMahi);
        if (var_r26 != NULL) {
            var_r30 = 1;
        }
        break;
    case 4:                                         /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 3U, WAZA_ItemNoDoku);
        if (var_r26 != NULL) {
            var_r30 = 1;
        } else {
            var_r26 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 4U, WAZA_ItemNoDoku);
            if (var_r26 != NULL) {
                var_r30 = 1;
            }
        }
        break;
    case 5:                                         /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 6U, WAZA_ItemNoYakedo);
        if (var_r26 != NULL) {
            var_r30 = 1;
        }
        break;
    case 6:                                         /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 7U, WAZA_ItemNoKoori);
        if (var_r26 != NULL) {
            var_r30 = 1;
        }
        break;
    case 3:                                         /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 8U, WAZA_ItemNoNemuri);
        if (var_r26 != NULL) {
            var_r30 = 1;
        }
        break;
    case 8:                                         /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 9U, WAZA_ItemNoKonran);
        if (var_r26 != NULL) {
            var_r30 = 2;
        }
        break;
    case 9:                                         /* switch 1 */
        if ((fightOutPokemonIsJoutaiNormal(arg0) == 0) || (fightOutPokemonIsJoutaiDataId(arg0, 9U) == 1)) {
            var_r21 = 0;
            temp_r20_3 = &ServerWork;
            temp_r20_3->flags[5] = 0;
            if ((fightOutPokemonIsJoutaiDataId(arg0, 3U) == 1) || (fightOutPokemonIsJoutaiDataId(arg0, 4U) == 1)) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(3U))));
                var_r21 = 1;
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 8U) == 1) {
                fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(8U))));
                var_r21 += 1;
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 5U) == 1) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(5U))));
                var_r21 += 1;
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 6U) == 1) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(6U))));
                var_r21 += 1;
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 7U) == 1) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(7U))));
                var_r21 += 1;
            }
            if (fightOutPokemonIsJoutaiDataId(arg0, 9U) == 1) {
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(9U))));
                var_r21 += 1;
            }
            if (var_r21 >= 2U) {
                temp_r20_3->flags[5] = 1;
            }
            pokemonInitJoutai((Pokemon *) temp_r3);
            fightOutPokemonInitJoutaiDataId(arg0, 9U);
            fightOutPokemonResetSeqStatus(arg0, 0U);
            var_r30 = 1;
            var_r26 = WAZA_ItemNoJoutaiijou;
        }
        break;
    case 28:                                        /* switch 1 */
        var_r26 = _fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(arg0, 0xAU, WAZA_ItemNoJoutaiijou);
        if (var_r26 != NULL) {
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(0xAU))));
            ServerWork.flags[5] = 0;
            var_r30 = 2;
        }
        break;
    }
    if (var_r30 != 0) {
        fightFloor_SetAppointPokemonPtr(NULL, arg0);
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
        fightFloor_SetItemPokemonPtr(NULL, arg0);
        switch ((s32) var_r30) {                    /* switch 2; irregular */
        case 2:                                     /* switch 2 */
            break;
        case 1:                                     /* switch 2 */
            fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
            break;
        }
        if (var_r26 != NULL) {
            fightSeq_CallWazaSeq(var_r26);
        }
    }
    return var_r30;
}

u8 *_fightSeqSoubiItemCheckTurnSubJoutaiKaihuku__FP15FightOutPokemonUsPUc(FightOutPokemon *arg0, u16 arg1, u8 *arg2) {
    u8 *var_r31;

    var_r31 = NULL;
    if (fightOutPokemonIsJoutaiDataId(arg0, arg1) == 1) {
        fightOutPokemonInitJoutaiDataId(arg0, arg1);
        switch (arg1) {                             /* irregular */
        case 8:
            fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
            break;
        case 4:
            fightOutPokemonInitJoutaiDataId(arg0, 3U);
            break;
        case 3:
            fightOutPokemonInitJoutaiDataId(arg0, 4U);
            break;
        }
        var_r31 = arg2;
    }
    return var_r31;
}

u8 *_fightSeqSoubiItemCheckTurnSubAbiCntUp__FP15FightOutPokemonUclUcUcUc(FightOutPokemon *arg0, u8 arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5) {
    u8 *var_r31;
    u8 temp_r30;

    var_r31 = NULL;
    if ((arg1 == 0) || (arg1 == 2)) {
        temp_r30 = pokemonGetStatus((Pokemon *) arg0, 0U, fightSeqCondChgActTypeToPokemonStatusId(arg3), 0U);
        if ((fightOutPokemonIsNokoriHpFollowing(arg0, (u16) arg2) != 0) && (temp_r30 < 0xCU)) {
            UserWork[0x1601E] = (s8) (arg3 + arg4);
            var_r31 = WAZA_ItemCondUp;
            UserWork[0x160A4] = arg5;
            UserWork[0x160A5] = 0;
        }
    }
    return var_r31;
}

u8 *_fightSeqSoubiItemCheckTurnSubTasteHpkaihuku__FP15FightOutPokemonUsUcUsUslP10FIGHT_WAZA(FightOutPokemon *arg0, u16 arg1, u8 arg2, u16 arg3, u16 arg4, s32 arg5, FightWaza *arg6) {
    u16 var_r5;
    u8 *var_r31;

    var_r31 = NULL;
    if (((fightOutPokemonIsNokoriHpFollowing(arg0, 2U) != 0) && (arg2 == 0)) || ((fightOutPokemonIsHpMantan(arg0) == 0) && (arg2 == 2))) {
        fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(tasteDataGetNigateMsgDataId(tasteDataGetPtr(arg1)))));
        var_r5 = fightOutPokemonMaxHpWaruValue(arg0, (u16) arg5);
        if ((s32) (arg3 + var_r5) > (s32) arg4) {
            var_r5 = arg4 - arg3;
        }
        fightWaza_SetDamage(arg6, (u32) -(s32) var_r5);
        if (fightOutPokemonGetTasteLike(arg0, (s32) arg1) == -1) {
            var_r31 = WAZA_ItemHPKaifukuKonran;
        } else {
            var_r31 = WAZA_ItemHPKaifuku;
        }
    }
    return var_r31;
}

u8 fightSeqPokemonSoubiItemCheckAppear(FightOutPokemon *arg0) {
    u16 temp_r31;
    u32 temp_r30;
    s32 temp_r30_2;
    u8 var_r29;
    u8 var_r28;
    FIGHT_TRAINER *temp_r28;

    var_r29 = 0;
    temp_r31 = fightOutPokemonGetSoubiItemDataId(arg0);
    temp_r30 = fightOutPokemonGetSoubiItemSoubiDataId(arg0);
    figthOutPokemonGetSoubiItemBuff(arg0);
    temp_r28 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(NULL, arg0);
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 0U;
    }
    fightFloor_SetAppointItemDataId(NULL, temp_r31);
    switch ((s32) (u16) temp_r30) {                 /* irregular */
    case 32:
        fightTrainer_SetOkaneBai(temp_r28, 2);
        break;
    case 23:
        var_r28 = 0;
        while (var_r28 < 7U) {
            temp_r30_2 = (var_r28 * 2) & 0x1FE;
            if (pokemonGetStatus((Pokemon *) arg0, 0U, *(const u16 *)((const u8 *)fight_seq_status_id + temp_r30_2), 0U) < 6) {
                pokemonSetStatus((Pokemon *) arg0, 0U, *(const u16 *)((const u8 *)fight_seq_status_id + temp_r30_2), 0U, 6U);
                var_r29 = 5;
            }
            var_r28 += 1;
        }
        if (var_r29 != 0) {
            fightFloor_SetAppointPokemonPtr(NULL, arg0);
            fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
            fightFloor_SetItemPokemonPtr(NULL, arg0);
            fightSeq_CallWazaSeq(WAZA_ItemAbiKaifuku);
        }
        break;
    }
    return var_r29;
}

void fightSeqFightOutPokemonTokuseiCheckSinkuroAtk(FightOutPokemon *arg0, FightOutPokemon *arg1) {
    u16 temp_r31;
    u8 temp_r0;

    temp_r31 = fightOutPokemonGetTokuseiDataId(arg0);
    if ((fightOutPokemonCheckFightOut(arg0) != 0) && (temp_r31 == 0x1C) && (ServerStatusFlag & 0x4000)) {
        ServerStatusFlag &= 0xFFFFBFFF;
        temp_r0 = fight_seq_tuika_param & 0x3F;
        fight_seq_tuika_param = temp_r0;
        if (temp_r0 == 6) {
            fight_seq_tuika_param = 2;
        }
        ServerWork.flags[3] = (u8) fight_seq_tuika_param;
        fightFloor_SetAppointPokemonPtr(NULL, arg0);
        ServerStatusFlag |= 0x2000;
        fightSeq_CallWazaSeq(WAZA_Sinkuro);
    }
}

void fightSeqFightOutPokemonTokuseiCheckSinkuroDef(FightOutPokemon *arg0, FightOutPokemon *arg1) {
    u16 temp_r31;
    u8 temp_r0;

    temp_r31 = fightOutPokemonGetTokuseiDataId(arg1);
    if ((fightOutPokemonCheckFightOut(arg1) != 0) && (temp_r31 == 0x1C) && (ServerStatusFlag & 0x4000)) {
        ServerStatusFlag &= 0xFFFFBFFF;
        temp_r0 = fight_seq_tuika_param & 0x3F;
        fight_seq_tuika_param = temp_r0;
        if (temp_r0 == 6) {
            fight_seq_tuika_param = 2;
        }
        ServerWork.flags[3] = (s8) (fight_seq_tuika_param + 0x40);
        fightFloor_SetAppointPokemonPtr(NULL, arg1);
        ServerStatusFlag |= 0x2000;
        fightSeq_CallWazaSeq(WAZA_Sinkuro);
    }
}

void fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAll(void) {
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAllSub__FPvUsPv, NULL, 0U);
}

s32 _fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAllSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    u16 temp_r30;
    Pokemon *temp_r30_2;
    u8 var_r28;

loop_1:
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    temp_r30 = fightOutPokemonGetTokuseiDataId(arg0);
    temp_r30_2 = fightOutPokemonGetPokemonPtr(arg0);
    var_r28 = 0;
    switch ((s32) temp_r30) {                       /* switch 1; irregular */
    case 0x11:                                      /* switch 1 */
        if ((fightOutPokemonIsJoutaiDataId(arg0, 3U) == 1) || (fightOutPokemonIsJoutaiDataId(arg0, 4U) == 1)) {
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(3U))));
            var_r28 = 1;
        }
        break;
    case 0x14:                                      /* switch 1 */
        if (fightOutPokemonIsJoutaiDataId(arg0, 9U) == 1) {
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(9U))));
            var_r28 = 2;
        }
        break;
    case 0x7:                                       /* switch 1 */
        if (fightOutPokemonIsJoutaiDataId(arg0, 5U) == 1) {
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(5U))));
            var_r28 = 1;
        }
        break;
    case 0x48:                                      /* switch 1 */
    case 0xF:                                       /* switch 1 */
        if (fightOutPokemonIsJoutaiDataId(arg0, 8U) == 1) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(8U))));
            var_r28 = 1;
        }
        break;
    case 0x29:                                      /* switch 1 */
        if (fightOutPokemonIsJoutaiDataId(arg0, 6U) == 1) {
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(6U))));
            var_r28 = 1;
        }
        break;
    case 0x28:                                      /* switch 1 */
        if (fightOutPokemonIsJoutaiDataId(arg0, 7U) == 1) {
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(7U))));
            var_r28 = 1;
        }
        break;
    case 0xC:                                       /* switch 1 */
        if (fightOutPokemonIsJoutaiDataId(arg0, 0xAU) == 1) {
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(joutaiDataBiosGetName(0xAU))));
            var_r28 = 3;
        }
        break;
    }
    if (var_r28 != 0) {
        switch ((s32) var_r28) {                    /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            pokemonInitJoutai((Pokemon *) temp_r30_2);
            fightOutPokemonResetSeqStatus(arg0, 0U);
            break;
        case 2:                                     /* switch 2 */
            fightOutPokemonInitJoutaiDataId(arg0, 9U);
            break;
        case 3:                                     /* switch 2 */
            fightOutPokemonInitJoutaiDataId(arg0, 0xAU);
            break;
        }
        fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
        fightFloor_SetAppointPokemonPtr(NULL, arg0);
        fightSeq_CallWazaSeq(WAZA_SpeabiNoJoutaiijou);
        goto loop_1;
    }
    return 1;
}

u8 fightSeqFightOutPokemonTokuseiCheckWazaHitAfter(FightOutPokemon *arg0, FightOutPokemon *arg1) {
    u8 conditions[3] = {1,2,5};
    u16 temp_r6;
    SeqServerWork *temp_r5;
    u32 temp_r4;
    u8 temp_r4_2;
    u32 temp_r3;
    FightWaza *temp_r3_2;
    u8 temp_r29;
    u8 temp_r28;
    u8 temp_r27;
    u8 temp_r26;
    u8 temp_r25;
    u16 temp_r24;
    u32 temp_r24_2;
    s32 temp_r23;
    s32 temp_r22;
    u16 temp_r20;
    u16 temp_r19;
    u8 var_r17;
    u8 var_r16;
    u16 temp_r16;

    temp_r22 = fightOutPokemon_GetMyselfDamageAtkValue(arg1);
    temp_r23 = fightOutPokemon_GetMyselfDamageSpeValue(arg1);
    temp_r16 = fightOutPokemonGetTokuseiDataId(arg0);
    temp_r24 = fightOutPokemonGetTokuseiDataId(arg1);
    temp_r3 = fightOutPokemon_GetUseWazaDataId(arg0);
    temp_r20 = wazaDB_GetIryoku(temp_r3);
    temp_r19 = fightOutPokemonGetWazaZokuseiDataId(arg0);
    temp_r25 = wazaDB_GetDageki((u16) temp_r3);
    temp_r3_2 = fightOutPokemon_GetFightWazaPtr(arg0);
    temp_r26 = fightWazaIsHit(temp_r3_2);
    temp_r27 = fightOutPokemon_GetKonranMyselfAttackFlag(arg0);
    var_r17 = 0;
    temp_r28 = fightOutPokemonGetSex(arg0);
    temp_r29 = fightOutPokemonGetSex(arg1);
    temp_r24_2 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightOutPokemon *) arg1, fightFloor_GetFightType(NULL));
    switch (temp_r24) {
    case 0x10:
        if ((temp_r26 == 1) && ((u16) temp_r3 != 0xA5) && (temp_r20 != 0) && (wazaCheckDarkWaza((u16) temp_r3) == 0) && (((s16) temp_r22 != 0) || ((s16) temp_r23 != 0)) && (fightOutPokemonIsZokuseiDataId(arg1, temp_r19) == 0) && (fightOutPokemonCheckFightOut(arg1) == 1)) {
            var_r16 = 0;
            while (var_r16 < 2U) {
                fightOutPokemonSetZokuseiDataId(arg1, var_r16, temp_r19);
                var_r16 += 1;
            }
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(zokuseiBiosGetName(temp_r19))));
            fightSeq_CallWazaSeq(WAZA_Hensyoku);
            var_r17 = 1;
        }
        break;
    case 0x18:
        if ((temp_r26 == 1) && (fightOutPokemonCheckFightOut(arg0) == 1) && (temp_r27 == 0) && (((s16) temp_r22 != 0) || ((s16) temp_r23 != 0)) && (temp_r25 != 0)) {
            fightWaza_SetDamage(temp_r3_2, (u32) fightOutPokemonMaxHpWaruValue(arg0, 0x10U));
            fightSeq_CallWazaSeq(WAZA_Samehada);
            var_r17 = 1;
        }
        break;
    case 0x1B:
        if ((temp_r26 == 1) && (fightOutPokemonCheckFightOut(arg0) == 1) && (temp_r27 == 0) && (((s16) temp_r22 != 0) || ((s16) temp_r23 != 0)) && (temp_r25 != 0) && ((HSD_Rand() % 10) == 0)) {
            temp_r6 = HSD_Rand();
            temp_r4 = temp_r6 / 3U;
            ServerStatusFlag |= 0x2000;
            temp_r5 = &ServerWork;
            temp_r4_2 = conditions[(u8)(temp_r6 - temp_r4 * 3)];
            temp_r5->flags[3] = temp_r4_2;
            temp_r5->flags[3] = (u8) (temp_r4_2 + 0x40);
            fightSeq_CallWazaSeq(WAZA_Honoonokarada);
            var_r17 = 1;
        }
        break;
    case 0x26:
        if ((temp_r26 == 1) && (fightOutPokemonCheckFightOut(arg0) == 1) && (temp_r27 == 0) && (((s16) temp_r22 != 0) || ((s16) temp_r23 != 0)) && (temp_r25 != 0) && ((HSD_Rand() % 3) == 0)) {
            ServerWork.flags[3] = 0x42;
            ServerStatusFlag |= 0x2000;
            fightSeq_CallWazaSeq(WAZA_Honoonokarada);
            var_r17 = 1;
        }
        break;
    case 0x9:
        if ((temp_r26 == 1) && (fightOutPokemonCheckFightOut(arg0) == 1) && (temp_r27 == 0) && (((s16) temp_r22 != 0) || ((s16) temp_r23 != 0)) && (temp_r25 != 0) && ((HSD_Rand() % 3) == 0)) {
            ServerWork.flags[3] = 0x45;
            ServerStatusFlag |= 0x2000;
            fightSeq_CallWazaSeq(WAZA_Honoonokarada);
            var_r17 = 1;
        }
        break;
    case 0x31:
        if ((temp_r26 == 1) && (fightOutPokemonCheckFightOut(arg0) == 1) && (temp_r27 == 0) && (temp_r25 != 0) && (((s16) temp_r22 != 0) || ((s16) temp_r23 != 0)) && ((HSD_Rand() % 3) == 0)) {
            ServerWork.flags[3] = 0x43;
            ServerStatusFlag |= 0x2000;
            fightSeq_CallWazaSeq(WAZA_Honoonokarada);
            var_r17 = 1;
        }
        break;
    case 0x38:
        if ((temp_r26 == 1) && (fightOutPokemonCheckFightOut(arg0) == 1) && (temp_r27 == 0) && (temp_r25 != 0) && (((s16) temp_r22 != 0) || ((s16) temp_r23 != 0)) && (fightOutPokemonCheckFightOut(arg1) == 1) && ((HSD_Rand() % 3) == 0) && (temp_r16 != 0xC) && (temp_r28 != temp_r29) && (fightOutPokemonCheckWriteJoutaiDataId(arg0, 0xAU) == 2) && (temp_r28 != 2) && (temp_r29 != 2)) {
            fightOutPokemonWriteJoutaiDataId(arg0, 0xAU, (u16) temp_r24_2);
            fightSeq_CallWazaSeq(WAZA_MeromeroBody);
            var_r17 = 1;
        }
        break;
    }
    return var_r17;
}

u8 fightSeqFightOutPokemonTokuseiCheckWazaHit(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2) {
    u8 temp_r31;
    u8 var_r30;
    FightWaza *temp_r29;
    u16 temp_r27;
    u16 temp_r26;
    u16 temp_r25;

    temp_r26 = fightOutPokemonGetTokuseiDataId(arg1);
    temp_r25 = wazaDB_GetIryoku((u32) arg2);
    temp_r27 = fightOutPokemonGetWazaZokuseiDataId(arg0);
    temp_r31 = fightOutPokemon_GetPassPpdecFlag(arg0);
    var_r30 = 0;
    temp_r29 = fightOutPokemon_GetFightWazaPtr(arg0);
    if (fightOutPokemonCheckFightOut(arg1) == 0) {
        return 0U;
    }
    if ((arg2 != 0) && (arg2 != 0x176)) {
        switch ((s32) temp_r26) {                   /* irregular */
        case 10:
            if ((temp_r27 == 0xD) && (temp_r25 != 0)) {
                if (temp_r31 != 0) {
                    fightSeq_JumpWazaSeq(WAZA_Tyosui);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_TyosuiPPDec);
                }
                var_r30 = 1;
            }
            break;
        case 11:
            if ((temp_r27 == 0xB) && (temp_r25 != 0)) {
                if (temp_r31 != 0) {
                    fightSeq_JumpWazaSeq(WAZA_Tyosui);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_TyosuiPPDec);
                }
                var_r30 = 1;
            }
            break;
        case 18:
            if ((temp_r27 == 0xA) && (fightOutPokemonIsJoutaiDataId(arg1, 7U) == 0)) {
                if (fightOutPokemonCheckWriteJoutaiDataId(arg1, 0x3AU) == 2) {
                    fightOutPokemonWriteJoutaiDataId(arg1, 0x3AU, 0U);
                    ServerWork.flags[5] = 0;
                } else {
                    ServerWork.flags[5] = 1;
                }
                if (temp_r31 != 0) {
                    fightSeq_JumpWazaSeq(WAZA_Moraibi);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_MoraibiPPDec);
                }
                var_r30 = 2;
            }
            break;
        }
        if (var_r30 == 1) {
            if (fightOutPokemonIsHpMantan(arg1) == 1) {
                if (temp_r31 != 0) {
                    fightSeq_JumpWazaSeq(WAZA_NOKaifuku);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_NOKaifukuPPDec);
                }
            } else {
                fightWaza_SetDamage(temp_r29, (u32) -(s32) fightOutPokemonMaxHpWaruValue(arg1, 4U));
            }
        }
    }
    return var_r30;
}

u8 fightSeqFightOutPokemonTokuseiCheckWazaHitBefore(FightOutPokemon *arg0, FightOutPokemon *arg1) {
    u16 temp_r31;
    u8 var_r30;

    fightOutPokemonGetTokuseiDataId(arg0);
    temp_r31 = fightOutPokemon_GetUseWazaDataId(arg0);
    var_r30 = 0;
    if ((s32) fightOutPokemonGetTokuseiDataId(arg1) != 0x2B) {

    } else if ((fightOutPokemonCheckFightOut(arg1) != 0) && (wazaDB_GetBouon(temp_r31) == 1)) {
        if (fightOutPokemonIsJoutaiDataId(arg0, 0x22U) == 1) {
            ServerStatusFlag |= 0x800;
        }
        fightSeq_JumpWazaSeq(WAZA_Bouon);
        var_r30 = 1;
    }
    return var_r30;
}

void fightSeqFightOutPokemonTokuseiCheckTurn__FP15FightOutPokemon(FightOutPokemon *arg0) {
    u16 temp_r3;
    u16 temp_r30;
    FightWaza *temp_r30_2;
    s8 temp_r3_2;
    Pokemon *temp_r29;
    u8 temp_r28;

    temp_r29 = fightOutPokemonGetPokemonPtr(arg0);
    temp_r28 = fightFloorGetNowTenkouDataId(NULL, 1U);
    if ((arg0 != NULL) && (fightOutPokemonCheckFightOut(arg0) != 0)) {
        temp_r30 = fightOutPokemonGetTokuseiDataId(arg0);
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
        temp_r30_2 = fightOutPokemon_GetFightWazaPtr(arg0);
        switch ((s32) temp_r30) {                   /* irregular */
        case 0x2C:
            if ((temp_r28 == 2) && (fightOutPokemonIsHpMantan(arg0) == 0)) {
                fightWaza_SetDamage(temp_r30_2, (u32) -(s32) fightOutPokemonMaxHpWaruValue(arg0, 0x10U));
                fightSeq_CallWazaSeq(WAZA_Ameukezara);
                return;
            }
            break;
        case 0x3D:
            if ((fightOutPokemonIsJoutaiNormal(arg0) == 0) && ((HSD_Rand() % 3) == 0)) {
                fightFloor_SetAppointPokemonPtr(NULL, arg0);
                fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(pokemonGetJoutaiMsgId(temp_r29))));
                pokemonInitJoutai((Pokemon *) temp_r29);
                fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
                fightOutPokemonResetSeqStatus(arg0, 0U);
                fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
                fightSeq_CallWazaSeq(WAZA_Dappi);
                return;
            }
            break;
        case 0x3:
            temp_r3 = fightSeqCondChgActTypeToPokemonStatusId(3U);
            temp_r3_2 = pokemonGetStatus((Pokemon *) arg0, 0U, temp_r3, 0U);
            if ((temp_r3_2 < 0xC) && (fightOutPokemon_GetFightoutTurnCount(arg0) != 2)) {
                fightFloor_SetAppointPokemonPtr(NULL, arg0);
                pokemonSetStatus((Pokemon *) arg0, 0U, temp_r3, 0U, (u32) (s8) (temp_r3_2 + 1));
                UserWork[0x160A4] = 0x11;
                UserWork[0x160A5] = 0;
                fightSeq_CallWazaSeq(WAZA_Kasokusouti);
                return;
            }
            break;
        case 0x36:
            fightOutPokemon_SetNamakeFlag(arg0, fightOutPokemon_GetNamakeFlag(arg0) == 0);
            break;
        }
    }
}

void fightSeqFightOutPokemonTokuseiCheckTrace(void) {
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqFightOutPokemonTokuseiCheckTraceSub__FPvUsPv, NULL, 0U);
}

s32 _fightSeqFightOutPokemonTokuseiCheckTraceSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    u16 temp_r3_2;

    temp_r31 = fightOutPokemonGetTokuseiDataId(arg0);
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    if ((temp_r31 == 0x24) && (fightOutPokemonIsJoutaiDataId(arg0, 0x3CU) == 1)) {
        temp_r3 = fightFloorGetFightOutPokemonPtrRandom(NULL, 1U, 2U, arg0);
        if (fightOutPokemonCheckFightOut(temp_r3) == 1) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x3CU);
            temp_r3_2 = fightOutPokemonGetTokuseiDataId(temp_r3);
            fightOutPokemonSetTokuseiDataId(arg0, temp_r3_2);
            fightFloor_SetAppointPokemonPtr(NULL, arg0);
            fightMsgctrlSetValue(0xDU, (u32)(fightOutPokemonGetNicknamePtr(temp_r3)));
            fightMsgctrlSetValue(0xEU, (u32)(GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(temp_r3_2)))));
            fightSeq_CallWazaSeq(WAZA_Trace);
        }
    }
    return 1;
}

void fightSeqFightOutPokemonTokuseiCheckIkaku(s8 arg0) {
    s8 sp8;

    sp8 = arg0;
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqFightOutPokemonTokuseiCheckIkakuSub__FPvUsPv, &sp8, 0U);
}

s32 _fightSeqFightOutPokemonTokuseiCheckIkakuSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    u8 *var_r31;
    u16 temp_r30;

    temp_r30 = fightOutPokemonGetTokuseiDataId(arg0);
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    var_r31 = WAZA_IkakuAct;
    if (*(u8 *)arg2 == 1) {
        var_r31 = WAZA_Ikaku;
    }
    if ((temp_r30 == 0x16) && (fightOutPokemonIsJoutaiDataId(arg0, 0x3BU) == 1)) {
        fightOutPokemonInitJoutaiDataId(arg0, 0x3BU);
        fightFloor_SetAppointPokemonPtr(NULL, arg0);
        fightSeq_CallWazaSeq(var_r31);
    }
    return 1;
}

void fightSeqFightOutPokemonTokuseiCheckAppear(FightOutPokemon *arg0) {
    u16 temp_r3;
    u8 temp_r3_2;

    if ((arg0 != NULL) && (fightOutPokemonCheckFightOut(arg0) != 0)) {
        temp_r3 = fightOutPokemonGetTokuseiDataId(arg0);
        switch ((s32) temp_r3) {                    /* irregular */
        case 0x2:
            if (fightFloorCheckWriteJoutaiDataId(NULL, 0x50) == 2) {
                fightFloorWriteJoutaiDataId(NULL, 0x50, 0);
                fightFloor_SetAppointPokemonPtr(NULL, arg0);
                fightSeq_CallWazaSeq(WAZA_Amehurashi);
                return;
            }
            break;
        case 0x2D:
            if (fightFloorCheckWriteJoutaiDataId(NULL, 0x51) == 2) {
                fightFloorWriteJoutaiDataId(NULL, 0x51, 0);
                fightFloor_SetAppointPokemonPtr(NULL, arg0);
                fightSeq_CallWazaSeq(WAZA_Sunaokosi);
                return;
            }
            break;
        case 0x46:
            if (fightFloorCheckWriteJoutaiDataId(NULL, 0x4F) == 2) {
                fightFloorWriteJoutaiDataId(NULL, 0x4F, 0);
                fightFloor_SetAppointPokemonPtr(NULL, arg0);
                fightSeq_CallWazaSeq(WAZA_Hideri);
                return;
            }
            break;
        case 0x16:
            if (fightOutPokemon_GetDoIkakuFlag(arg0) == 0) {
                if (fightOutPokemonCheckWriteJoutaiDataId(arg0, 0x3BU) == 2) {
                    fightOutPokemonWriteJoutaiDataId(arg0, 0x3BU, 0U);
                }
                fightOutPokemon_SetDoIkakuFlag(arg0, 1U);
                return;
            }
            break;
        case 0x24:
            if (fightOutPokemon_GetDoTraceFlag(arg0) == 0) {
                if (fightOutPokemonCheckWriteJoutaiDataId(arg0, 0x3CU) == 2) {
                    fightOutPokemonWriteJoutaiDataId(arg0, 0x3CU, 0U);
                }
                fightOutPokemon_SetDoTraceFlag(arg0, 1U);
                return;
            }
            break;
        case 0x3B:
            temp_r3_2 = fightSeqTokuseiTenkiyaAct__FP15FightOutPokemon(arg0);
            if (temp_r3_2 != 0) {
                UserWork[0x1609B] = (s8) (temp_r3_2 - 1);
                fightFloor_SetAppointPokemonPtr(NULL, arg0);
                fightSeq_CallWazaSeq(WAZA_Tenkiya);
                return;
            }
            break;
        case 0x4D:
        case 0xD:
            fightSeqFightOutPokemonTokuseiCheckTenkiya();
            break;
        }
    }
}

void fightSeqEventKurein(u8 arg0) {
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    WazaSequence *temp_r31;
    WazaSequence *temp_r31_2;
    WazaSequence *temp_r31_3;

    switch (arg0) {
    case 0:
        kureinSequencePtr = Sequence_LoadTrainer(0x40U);
        return;
    case 1:
        sp14 = 78.0f;
        sp18 = 0.0f;
        sp1C = 20.0f;
        sp8 = 0.0f;
        spC = -1.5707964f;
        sp10 = 0.0f;
        Sequence_SetPosition(kureinSequencePtr, &sp14);
        Sequence_SetRotation(kureinSequencePtr, &sp8);
        Sequence_SetVisibility((u32) kureinSequencePtr, 1);
        return;
    case 3:
        Sequence_LoadWaza(kureinSequencePtr, 0xF9U, 4U, 0U);
        WazaSequence_Start(Sequence_GetWaza(kureinSequencePtr, 0xF9U, 4U), 1U);
        return;
    case 4:
        temp_r31 = Sequence_GetWaza(kureinSequencePtr, 0xF9U, 4U);
        battleGridStoreModelVisibilityFlags();
        while (WazaSequence_IsActive(temp_r31) != 0) {
            GSthreadSwitch();
        }
        fightMainSetAllDispFlag(1);
        WazaSequence_Free(temp_r31);
        return;
    case 6:
        Sequence_LoadWaza(kureinSequencePtr, 0x13CU, 4U, 0U);
        WazaSequence_Start(Sequence_GetWaza(kureinSequencePtr, 0x13CU, 4U), 1U);
        return;
    case 7:
        temp_r31_2 = Sequence_GetWaza(kureinSequencePtr, 0x13CU, 4U);
        battleGridStoreModelVisibilityFlags();
        while (WazaSequence_IsActive(temp_r31_2) != 0) {
            GSthreadSwitch();
        }
        fightMainSetAllDispFlag(1);
        WazaSequence_Free(temp_r31_2);
        fightMainAllCamera(0U, 0U);
        return;
    case 5:
        Sequence_LoadWaza(kureinSequencePtr, 0x13CU, 4U, 0U);
        temp_r31_3 = Sequence_GetWaza(kureinSequencePtr, 0x13CU, 4U);
        battleGridStoreModelVisibilityFlags();
        WazaSequence_Start(temp_r31_3, 1U);
        fightMenuOpenMsg((void *)0x5004);
        while (WazaSequence_IsActive(temp_r31_3) != 0) {
            GSthreadSwitch();
        }
        fightMenuCloseMsg();
        WazaSequence_Free(temp_r31_3);
        fightMainAllCamera(0U, 0U);
        /* fallthrough */
    default:
        return;
    }
}

void fightEvtSetSequence(void *arg0) {
    kureinSequencePtr = arg0;
}

void *fightEvtGetSequence(void) {
    return kureinSequencePtr;
}

u8 fightSeqFightOutPokemonTokuseiCheckTenkiya(void) {
    u8 sp8;

    sp8 = 0;
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqFightOutPokemonTokuseiCheckTenkiyaSub__FPvUsPv, &sp8, 0U);
    return sp8;
}

s32 _fightSeqFightOutPokemonTokuseiCheckTenkiyaSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    u8 temp_r3;

    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    temp_r3 = fightSeqTokuseiTenkiyaAct__FP15FightOutPokemon(arg0);
    if (temp_r3 != 0) {
        UserWork[0x1609B] = (s8) (temp_r3 - 1);
        fightFloor_SetAppointPokemonPtr(NULL, arg0);
        fightSeq_CallWazaSeq(WAZA_Tenkiya);
        if (arg2 != NULL) {
            *(u8 *)arg2 = 1;
        }
    }
    return 1;
}

u8 fightSeqTokuseiTenkiyaAct__FP15FightOutPokemon(FightOutPokemon *arg0) {
    u16 temp_r3;
    u32 temp_r3_2;
    u8 var_r30;
    u16 temp_r30;

    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 0U;
    }
    temp_r30 = figthOutPokemonGetPokemonDataId(arg0);
    temp_r3 = fightOutPokemonGetTokuseiDataId(arg0);
    if ((temp_r30 != 0x181) || (temp_r3 != 0x3B)) {
        return 0U;
    }
    temp_r3_2 = (u8)fightFloorGetNowTenkouDataId(NULL, 1U);
    var_r30 = 0;
    if (((temp_r3_2 == 0) || (temp_r3_2 == 3) || (temp_r3_2 == 5)) && (fightOutPokemonIsZokuseiDataId(arg0, 0U) == 0)) {
        var_r30 = 0;
        while (var_r30 < 2U) {
            fightOutPokemonSetZokuseiDataId(arg0, var_r30, 0U);
            var_r30 += 1;
        }
        var_r30 = 1;
    }
    if ((temp_r3_2 == 1) && (fightOutPokemonIsZokuseiDataId(arg0, 0xAU) == 0)) {
        var_r30 = 0;
        while (var_r30 < 2U) {
            fightOutPokemonSetZokuseiDataId(arg0, var_r30, 0xAU);
            var_r30 += 1;
        }
        var_r30 = 2;
    }
    if ((temp_r3_2 == 2) && (fightOutPokemonIsZokuseiDataId(arg0, 0xBU) == 0)) {
        var_r30 = 0;
        while (var_r30 < 2U) {
            fightOutPokemonSetZokuseiDataId(arg0, var_r30, 0xBU);
            var_r30 += 1;
        }
        var_r30 = 3;
    }
    if ((temp_r3_2 == 4) && (fightOutPokemonIsZokuseiDataId(arg0, 0xFU) == 0)) {
        var_r30 = 0;
        while (var_r30 < 2U) {
            fightOutPokemonSetZokuseiDataId(arg0, var_r30, 0xFU);
            var_r30 += 1;
        }
        var_r30 = 4;
    }
    return var_r30;
}

s32 fightSeqCheckDarkPokemonJoutaiHyperAct(FightOutPokemon *arg0, u8 arg1) {
    u16 temp_r3;
    u8 temp_r31;
    u32 temp_r3_2;
    u8 temp_r29;
    FightOutPokemon *temp_r29_2;
    FightOutPokemon *temp_r29_3;
    FightOutPokemon *temp_r29_4;
    u32 temp_r0;

    temp_r31 = fightFloor_GetFightType(NULL);
    if (arg0 == NULL) {
        return 0;
    }
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 0;
    }
    if (fightOutPokemonIsGcHeroFightOutPokemon(arg0) == 0) {
        return 0;
    }
    if (fightFloor_GetFightKindDarkpokemonHypermodeFlag(NULL) == 0) {
        return 0;
    }
    if (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(arg0)) == 0) {
        return 0;
    }
    fightOutPokemon_GetSequencePtr(arg0);
    switch (arg1) {                                 /* irregular */
    case 0:
        if (fightOutPokemonIsJoutaiDataId(arg0, 0x3EU) == 1) {
            return 0;
        }
        if (fightOutPokemonIsJoutaiDataId(arg0, 8U) == 1) {
            return 0;
        }
        fightOutPokemonGetPokemonPtr(arg0);
        temp_r29 = pokemonGetDarkPokemonHyperJoutaiKakuritu();
        fightOutPokemon_GetUseWazaDataId(arg0);
        if ((s32) (HSD_Rand() % 100) < (s32) temp_r29) {
            fightOutPokemonDarkPokemonEffect(arg0, 1U, 1U, 0U);
            temp_r29_2 = fightFloor_GetAttackPokemonPtr(NULL);
            fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
            if (fightOutPokemonCheckWriteJoutaiDataId(arg0, 0x3EU) == 2) {
                fightOutPokemonWriteJoutaiDataId(arg0, 0x3EU, 0U);
            }
            fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0xC8U);
            fightOutPokemonDarkPokemonEffect(arg0, 1U, 1U, 1U);
            fightMenuFightOutPokemonRenewStatusMenu(arg0, temp_r31, 1U);
            fightMenuOpenMsg((void *)0x4FE2);
            fightOutPokemonDarkPokemonEffect(arg0, 1U, 1U, 2U);
            fightMenuCloseMsg();
            fightMenuFightOutPokemonCloseStatusMenu(arg0, temp_r31, 0U);
            fightFloor_SetAttackPokemonPtr(NULL, (u8 *) temp_r29_2);
            fightOutPokemonDarkPokemonEffect(arg0, 1U, 1U, 3U);
block_30:
        default:
            return 1;
        }
        return 0;
    case 1:
        if (fightOutPokemonIsJoutaiDataId(arg0, 0x3EU) == 0) {
            return 0;
        }
        fightOutPokemonDarkPokemonEffect(arg0, 0U, 2U, 0U);
        temp_r29_3 = fightFloor_GetAttackPokemonPtr(NULL);
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
        fightOutPokemonDarkPokemonEffect(arg0, 0U, 2U, 1U);
        fightMenuFightOutPokemonOpenStatusMenu(arg0, temp_r31, 1U);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, arg0, temp_r31, 0U, 1U);
        fightMenuOpenMsg((void *)0x4FE3);
        fightOutPokemonDarkPokemonEffect(arg0, 0U, 2U, 2U);
        fightMenuCloseMsg();
        fightMenuFightOutPokemonCloseStatusMenu(arg0, temp_r31, 0U);
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) temp_r29_3);
        fightOutPokemonDarkPokemonEffect(arg0, 0U, 2U, 3U);
        goto block_30;
    case 2:
        if (fightOutPokemonIsJoutaiDataId(arg0, 0x3EU) == 0) {
            return 0;
        }
        temp_r3 = HSD_Rand();
        temp_r3_2 = temp_r3 >> 0x1FU;
        temp_r0 = (temp_r3 << 0x18) - temp_r3_2;
        if ((((temp_r0 << 8) | (temp_r0 >> 0x18U)) + temp_r3_2) != 0) {
            return 0;
        }
        fightOutPokemonIsJoutaiDataId(arg0, 8U);
        fightOutPokemonDarkPokemonKaijoEffect(arg0, 1U, 1U, 0U, NULL, 0U);
        temp_r29_4 = fightFloor_GetAttackPokemonPtr(NULL);
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
        fightOutPokemonInitJoutaiDataId(arg0, 0x3EU);
        fightOutPokemonInitJoutaiDataId(arg0, 8U);
        fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
        fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0xC8U);
        fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
        fightOutPokemonDarkPokemonKaijoEffect(arg0, 1U, 1U, 0U, (void *)0x4FD7, 1U);
        fightOutPokemonDarkPokemonKaijoEffect(arg0, 1U, 1U, 0U, NULL, 2U);
        fightMenuCloseMsg();
        fightMenuFightOutPokemonCloseStatusMenu(arg0, temp_r31, 0U);
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) temp_r29_4);
        fightOutPokemonDarkPokemonKaijoEffect(arg0, 1U, 1U, 0U, NULL, 3U);
        goto block_30;
    }
}

u8 fightSeqAttackPokemonJoutaiCheck(void) {
    u16 temp_r4;
    FightOutPokemon *temp_r3;
    u16 var_r30;
    u16 temp_r3_2;
    u16 temp_r3_3;
    u32 temp_r3_4;
    s8 temp_r3_5;
    FightOutPokemon *temp_r3_6;
    SeqServerWork *temp_r29;
    FightWaza *temp_r28;
    u8 temp_r27;
    u16 temp_r26;
    u16 temp_r25;
    u16 temp_r24;
    void *temp_r23;
    u8 var_r22;
    s8 temp_r22;
    s8 temp_r22_2;
    s32 temp_r22_3;
    FightOutPokemon *var_r21;
    s8 temp_r21;
    u32 temp_r0;

    temp_r3 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r28 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r23 = fightTargetGetPtrAsNowFightType(2U, temp_r3);
    temp_r25 = fightOutPokemonGetTokuseiDataId(temp_r3);
    temp_r3_2 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    var_r30 = temp_r3_2;
    temp_r24 = wazaDB_GetIryoku((u32) temp_r3_2);
    temp_r26 = wazaDB_GetSeqId(var_r30);
    var_r22 = 0;
    temp_r27 = fightFloor_GetFightType(NULL);
    temp_r29 = &ServerWork;
loop_1:
    switch (fightseq_attack_pokemon_joutai_check_buff) {
    case 0:
        fightOutPokemonInitJoutaiDataId(temp_r3, 0x15U);
        fightOutPokemonInitJoutaiDataId(temp_r3, 0x28U);
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 1:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 8U) == 1) {
            if (fightSeqSawaguCheck((u8 *) temp_r3) != 0) {
                fightOutPokemonInitJoutaiDataId(temp_r3, 8U);
                fightOutPokemonInitJoutaiDataId(temp_r3, 0x17U);
                temp_r29->flags[5] = 1;
                fightSeq_CallWazaSeq(WAZA_Mezame);
                var_r22 = 2;
            } else {
                temp_r21 = fightOutPokemonGetNowKaisuuJoutaiDataId(temp_r3, 8U) + ((temp_r25 == 0x30) + 1);
                if (temp_r21 >= fightOutPokemonGetKaisuuJoutaiDataId(temp_r3, 8U)) {
                    fightOutPokemonInitJoutaiDataId(temp_r3, 8U);
                    fightOutPokemonInitJoutaiDataId(temp_r3, 0x17U);
                } else {
                    fightOutPokemonSetNowKaisuuJoutaiDataId(temp_r3, 8U, temp_r21);
                }
                if (fightOutPokemonIsJoutaiDataId(temp_r3, 8U) == 1) {
                    if ((var_r30 != 0xAD) && (var_r30 != 0xD6)) {
                        ServerStatusFlag |= 0x80000;
                        fightSeq_JumpWazaSeq(WAZA_Nemuru);
                        var_r22 = 2;
                    }
                } else {
                    temp_r29->flags[5] = 0;
                    fightSeq_CallWazaSeq(WAZA_Mezame);
                    var_r22 = 2;
                }
            }
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 2:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 7U) == 1) {
            if ((HSD_Rand() % 5) != 0) {
                if (temp_r26 != 0x7D) {
                    ServerStatusFlag |= 0x80000;
                    fightSeq_JumpWazaSeq(WAZA_Koori);
                    goto block_22;
                }
                fightseq_attack_pokemon_joutai_check_buff += 1;
            } else {
                fightOutPokemonInitJoutaiDataId(temp_r3, 7U);
                temp_r29->flags[5] = 0;
                fightSeq_CallWazaSeq(WAZA_Melt);
block_22:
                var_r22 = 2;
                goto block_23;
            }
        } else {
block_23:
            fightseq_attack_pokemon_joutai_check_buff += 1;
        }
        break;
    case 3:
        if ((temp_r25 == 0x36) && (fightOutPokemon_GetNamakeFlag(temp_r3) != 0)) {
            if (fightWazaCheckWriteJoutaiDataId(temp_r28, 0x40U) == 2) {
                fightWazaWriteJoutaiDataId(temp_r28, 0x40U, 0U);
            }
            fightOutPokemonInitJoutaiKeep(temp_r3);
            temp_r29->flags[5] = 0;
            ServerStatusFlag |= 0x80000;
            fightSeq_JumpWazaSeq(WAZA_Namakeru);
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 4:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x12U) == 1) {
            fightOutPokemonInitJoutaiDataId(temp_r3, 0x12U);
            fightOutPokemonInitJoutaiKeep(temp_r3);
            ServerStatusFlag |= 0x80000;
            fightSeq_JumpWazaSeq(WAZA_Handou);
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 5:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x11U) == 1) {
            fightOutPokemonInitJoutaiDataId(temp_r3, 0x11U);
            fightOutPokemon_SetHirumuNoAttackFlag(temp_r3, 1U);
            fightOutPokemonInitJoutaiKeep(temp_r3);
            ServerStatusFlag |= 0x80000;
            fightSeq_JumpWazaSeq(WAZA_Hirumu);
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 6:
        if ((fightOutPokemonIsJoutaiDataId(temp_r3, 0x29U) == 1) && (fightOutPokemonGetIdBuffJoutaiDataId(temp_r3, 0x29U) == var_r30) && (var_r30 != 0) && (var_r30 != 0x176)) {
            fightOutPokemonInitJoutaiKeep(temp_r3);
            fightOutPokemon_SetKanashibariNoAttackFlag(temp_r3, 1U);
            ServerStatusFlag |= 0x80000;
            fightMsgctrlSetValue(0x11U, (u32)((u32) temp_r3));
            fightSeq_JumpWazaSeq(WAZA_Kanashibari);
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 7:
        if ((fightOutPokemonIsJoutaiDataId(temp_r3, 0x30U) == 1) && (temp_r24 == 0)) {
            fightOutPokemonInitJoutaiKeep(temp_r3);
            fightOutPokemon_SetChouhatsuNoAttackFlag(temp_r3, 1U);
            ServerStatusFlag |= 0x80000;
            fightMsgctrlSetValue(0x11U, (u32)((u32) temp_r3));
            fightSeq_JumpWazaSeq(WAZA_Chouhatsu2);
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 8:
        if (fightFloorCheckHuuinWazaFightOutPokemon(NULL, temp_r3, (u32) var_r30) == 1) {
            fightOutPokemonInitJoutaiKeep(temp_r3);
            fightOutPokemon_SetHuuinNoAttackFlag(temp_r3, 1U);
            ServerStatusFlag |= 0x80000;
            fightMsgctrlSetValue(0x11U, (u32)((u32) temp_r3));
            fightSeq_JumpWazaSeq(WAZA_Huuin);
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 9:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 9U) == 1) {
            temp_r22 = fightOutPokemonGetNowKaisuuJoutaiDataId(temp_r3, 9U);
            if (temp_r22 >= fightOutPokemonGetKaisuuJoutaiDataId(temp_r3, 9U)) {
                fightOutPokemonInitJoutaiDataId(temp_r3, 9U);
                fightSeq_CallWazaSeq(WAZA_KonranEnd);
            } else {
                fightOutPokemonSetNowKaisuuJoutaiDataId(temp_r3, 9U, (s8) (temp_r22 + 1));
                if (HSD_Rand() & 1) {
                    temp_r29->flags[5] = 0;
                    fightSeq_CallWazaSeq(WAZA_Konran);
                } else {
                    temp_r29->flags[5] = 1;
                    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(NULL, temp_r3);
                    fightWaza_SetDamage(temp_r28, fightSeqWazaDamageCalc(temp_r3, temp_r3, (u8) temp_r23, 1U, 0x28U, -1U));
                    fightOutPokemon_SetKonranMyselfAttackFlag(temp_r3, 1U);
                    ServerStatusFlag |= 0x80000;
                    fightSeq_JumpWazaSeq(WAZA_Konran);
                }
            }
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 10:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 5U) == 1) {
            temp_r3_3 = HSD_Rand();
            temp_r3_4 = temp_r3_3 >> 0x1FU;
            temp_r0 = (temp_r3_3 << 0x1E) - temp_r3_4;
            if ((((temp_r0 << 2) | (temp_r0 >> 0x1EU)) + temp_r3_4) == 0) {
                fightOutPokemon_SetMahiNoAttackFlag(temp_r3, 1U);
                fightOutPokemonInitJoutaiKeep(temp_r3);
                ServerStatusFlag |= 0x80000;
                fightSeq_JumpWazaSeq(WAZA_Mahi);
                var_r22 = 1;
            }
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 11:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0xAU) == 1) {
            fightFloor_SetAppointPokemonPtr(NULL, fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightOutPokemonGetUserFightTargetIdJoutaiDataId(temp_r3, 0xAU), (u16) temp_r27));
            if (HSD_Rand() & 1) {
                fightSeq_CallWazaSeq(WAZA_Meromero);
            } else {
                fightOutPokemonInitJoutaiKeep(temp_r3);
                fightOutPokemon_SetMeroMeroNoAttackFlag(temp_r3, 1U);
                ServerStatusFlag |= 0x80000;
                fightSeq_CallWazaSeq(WAZA_Meromero);
                fightSeq_JumpWazaSeq(WAZA_MeromeroNext);
            }
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 12:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0xCU) == 1) {
            temp_r22_2 = fightOutPokemonGetNowKaisuuJoutaiDataId(temp_r3, 0xCU);
            temp_r3_5 = temp_r22_2 + 1;
            if (temp_r3_5 >= fightOutPokemonGetKaisuuJoutaiDataId(temp_r3, 0xCU)) {
                fightOutPokemonInitJoutaiDataId(temp_r3, 0xCU);
                fightOutPokemonInitJoutaiDataId(temp_r3, 0x22U);
                ServerStatusFlag |= 0x02000000;
                temp_r22_3 = fightOutPokemon_GetGamanDamageValue(temp_r3);
                var_r21 = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightOutPokemon_GetGamanDamageTargetId(temp_r3), (u16) temp_r27);
                if (((s16) temp_r22_3 != 0) && ((fightWazaSetUseWazaStatus(temp_r28, 0x75), temp_r4 = fightOutPokemon_GetUseWazaDataId(temp_r3), fight_seq_gaman_damage = (s16) temp_r22_3 * 2, var_r30 = temp_r4, ((fightOutPokemonCheckFightOut((FightOutPokemon *) var_r21) == 0) == 0)) || (temp_r3_6 = fightSeqSelectDefensePokemonPtr(temp_r3, var_r30, temp_r27, NULL, 1U, 1U, 0), var_r21 = temp_r3_6, ((fightOutPokemonCheckFightOut((FightOutPokemon *) temp_r3_6) == 0) == 0)))) {
                    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(NULL, (FightOutPokemon *) var_r21);
                    fightSeq_JumpWazaSeq(WAZA_GamanOff);
                } else {
                    fightSeq_JumpWazaSeq(WAZA_GamanFaild);
                }
            } else {
                fightOutPokemonSetNowKaisuuJoutaiDataId(temp_r3, 0xCU, temp_r3_5);
                fightSeq_JumpWazaSeq(WAZA_Gaman);
            }
            var_r22 = 1;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 13:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 7U) == 1) {
            if (temp_r26 == 0x7D) {
                fightOutPokemonInitJoutaiDataId(temp_r3, 7U);
                temp_r29->flags[5] = 1;
                fightSeq_CallWazaSeq(WAZA_Melt);
            }
            var_r22 = 2;
        }
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    case 14:
        fightseq_attack_pokemon_joutai_check_buff += 1;
        break;
    }
    if (((u8) fightseq_attack_pokemon_joutai_check_buff != 0xF) && (var_r22 == 0)) {
        goto loop_1;
    }
    if (var_r22 == 2) {
        fightSeqCheckSetHensinBuffToMotoPokemon(temp_r3, 0x7CU);
    }
    return var_r22;
}

s32 fightSeqWazaOutBeforeCheckSub(FightOutPokemon *arg0) {
    if ((fightOutPokemonIsJoutaiDataId(arg0, 0x13U) == 1) && (fightOutPokemon_GetMotoWazaDataId(arg0) != 0x63)) {
        fightOutPokemonInitJoutaiDataId(arg0, 0x13U);
    }
    return 1;
}

void fightSeqGetExpCheck(void) {
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqGetExpCheckSub__FPvUsPv, NULL, 0U);
    fightSeqCheckZenmetu();
}

void fightSeqCheckZenmetu(void) {
    fightSeq_CallWazaSeq(WAZA_Zenmetsu);
    fightSeqFightOutPokemonTokuseiCheckIkaku(1);
    fightSeqFightOutPokemonTokuseiCheckTrace();
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqGetExpCheckSubSoubiItemCheckTurn__FPvUsPv, NULL, 0U);
    fightSeqFightOutPokemonTokuseiCheckTenkiya();
}

s32 _fightSeqGetExpCheckSubSoubiItemCheckTurn__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    FightOutPokemon *temp_r30;

    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    temp_r30 = fightFloor_GetAttackPokemonPtr(NULL);
    fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
    fightSeqSoubiItemCheckTurn(arg0, 1U);
    fightFloor_SetAttackPokemonPtr(NULL, (u8 *) temp_r30);
    return 1;
}

s32 _fightSeqGetExpCheckSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    if (fightOutPokemon_GetKizetuFlag(arg0) == 1) {
        fightFloor_SetKizetuPokemonPtr(NULL, arg0);
        fightFloor_SetDefensePokemonPtr(NULL, (u8 *) arg0);
        fightSeq_CallWazaSeq(WAZA_GetEXP);
    }
    return 1;
}

void fightSeqSideJoutaiCheck2(void) {
    fightFloorLoopValidFightOutPokemon(NULL, _SideConditionCheck2SubMiraiyoti__FPvUsPv, NULL, 0U);
    wazaSequenceSysFreeAllWaza();
    fightFloorLoopValidFightOutPokemon(NULL, _SideConditionCheck2SubHorobinouta__FPvUsPv, NULL, 1U);
    wazaSequenceSysFreeAllWaza();
}

s32 _SideConditionCheck2SubHorobinouta__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    u8 *var_r3;
    s8 temp_r31;
    u32 temp_r30;
    FightWaza *temp_r27;

    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x1EU) == 1) {
        temp_r30 = fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x1EU);
        temp_r31 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x1EU);
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
        temp_r27 = fightOutPokemon_GetFightWazaPtr(arg0);
        fightMsgctrlSetValue(0x2FU, (u32)((s8) temp_r30 - temp_r31));
        if (temp_r31 >= (s8) temp_r30) {
            fightWaza_SetDamage(temp_r27, (u32) pokemon_GetHp(fightOutPokemonGetPokemonPtr(arg0)));
            fightOutPokemonInitJoutaiDataId(arg0, 0x1EU);
            var_r3 = WAZA_Horobinouta;
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x1EU, (s8) (temp_r31 + 1));
            var_r3 = WAZA_Horobinoutaing;
        }
        fightSeq_CallWazaSeq(var_r3);
        fightSeqGetExpCheck();
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    return 1;
}

s32 _SideConditionCheck2SubMiraiyoti__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    SeqWazaSave sp8;
    s8 temp_r3;
    u32 temp_r30;
    FightOutPokemon *temp_r3_2;
    FightWaza *temp_r3_3;
    FightOutPokemon *var_r29;
    u32 temp_r29;
    u32 temp_r28;
    u32 temp_r27;

    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x34U) == 1) {
        temp_r29 = fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x34U);
        temp_r3 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x34U);
        if (temp_r3 >= (s8) temp_r29) {
            temp_r28 = fightOutPokemonGetBuffJoutaiDataId(arg0, 0x34U);
            temp_r27 = fightOutPokemonGetIdBuffJoutaiDataId(arg0, 0x34U);
            temp_r3_2 = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg0, 0x34U), arg1);
            var_r29 = temp_r3_2;
            if (fightOutPokemonCheckFightOut((FightOutPokemon *) temp_r3_2) == 0) {
                var_r29 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xEU, (FightOutPokemon *) var_r29);
            }
            if ((u16) temp_r27 == 0xF8) {
                ServerWork.flags[5] = 0;
            } else {
                ServerWork.flags[5] = 1;
            }
            fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(wazaDB_GetName((u16) temp_r27))));
            fightFloor_SetDefensePokemonPtr(NULL, (u8 *) arg0);
            temp_r30 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightOutPokemon *) arg0, (u8) arg1);
            fightFloor_SetAttackPokemonPtr(NULL, (u8 *) var_r29);
            temp_r3_3 = fightOutPokemon_GetFightWazaPtr((FightOutPokemon *) var_r29);
            fightWazaBiosCopy((FightWaza *)&sp8, temp_r3_3);
            fightWazaCreate(temp_r3_3, -1, (u16) temp_r27, (u8) temp_r30, 0);
            fightWaza_SetDamage(temp_r3_3, temp_r28);
            fightOutPokemon_SetKaigaraDamageValue(arg0, 0xFFFF);
            fightOutPokemonInitJoutaiDataId(arg0, 0x34U);
            fightSeq_CallWazaSeq(WAZA_Miraiyochi);
            fightWazaBiosCopy(temp_r3_3, (FightWaza *)&sp8);
            fightSeqGetExpCheck();
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x34U, (s8) (temp_r3 + 1));
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    return 1;
}

void fightSeqSideJoutaiCheck(void) {
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqSideJoutaiCheckSub__FPvUsPv, NULL, 1U);
}

s32 _fightSeqSideJoutaiCheckSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    u8 *var_r3;
    u16 temp_r3;
    FightWaza *temp_r30;
    FightOutPokemon *temp_r3_2;
    u16 temp_r3_3;
    u16 temp_r3_4;
    Pokemon *temp_r29;
    u16 temp_r28;
    s8 temp_r27;
    u8 *temp_r27_2;
    s8 temp_r27_3;
    u16 temp_r27_4;
    s8 temp_r27_5;
    s8 temp_r27_6;
    s8 temp_r27_7;
    s8 temp_r27_8;
    u32 temp_r26;
    s8 temp_r26_2;
    s8 temp_r26_3;
    s8 temp_r26_4;
    u32 temp_r26_5;
    s32 var_r25;
    u16 temp_r25;
    u8 *temp_r25_2;
    u32 temp_r25_3;
    s8 temp_r0;
    s8 temp_r0_2;
    s8 temp_r0_3;
    s8 temp_r0_4;
    s8 temp_r0_5;
    s8 temp_r0_6;

    if (fightGetFightResultId() != 0) {
        return 0;
    }
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
    temp_r29 = fightOutPokemonGetPokemonPtr(arg0);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(arg0);
    temp_r28 = fightOutPokemonGetTokuseiDataId(arg0);
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if ((fightOutPokemonIsJoutaiDataId(arg0, 0x25U) == 1) && (fightOutPokemonIsHpMantan(arg0) == 0)) {
        fightWaza_SetDamage(temp_r30, (u32) -(s32) fightOutPokemonMaxHpWaruValue(arg0, 0x10U));
        fightSeq_CallWazaSeq(WAZA_Newoharu);
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    fightSeqFightOutPokemonTokuseiCheckTurn__FP15FightOutPokemon(arg0);
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    fightSeqSoubiItemCheckTurn(arg0, 0U);
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    fightSeqSoubiItemCheckTurn(arg0, 1U);
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x1CU) == 1) {
        temp_r3 = fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg0, 0x1CU);
        if (temp_r3 != 0) {
            temp_r3_2 = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr((u32) temp_r3, arg1);
            if ((temp_r3_2 != NULL) && (fightOutPokemonCheckFightOut((FightOutPokemon *) temp_r3_2) == 1)) {
                fightFloor_SetDefPokemonAndAtkFightWazaTargetId(NULL, (FightOutPokemon *) temp_r3_2);
                fightWaza_SetDamage(temp_r30, (u32) fightOutPokemonMaxHpWaruValue(arg0, 8U));
                UserWork[0x160A4] = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(temp_r3_2, (u8) arg1);
                UserWork[0x160A5] = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightOutPokemon *) arg0, (u8) arg1);
                fightSeq_CallWazaSeq(WAZA_Yadorigi);
            }
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 3U) == 1) {
        fightWaza_SetDamage(temp_r30, (u32) fightOutPokemonMaxHpWaruValue(arg0, 8U));
        fightSeq_CallWazaSeq(WAZA_Dokudoku);
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 4U) == 1) {
        temp_r26 = fightOutPokemonGetCountAsJoutaiDataId(arg0, 4U);
        fightWaza_SetDamage(temp_r30, fightOutPokemonMaxHpWaruValue(arg0, 0x10U) * (s16) temp_r26);
        fightOutPokemonWriteJoutaiDataId(arg0, 4U, 0U);
        fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
        fightSeq_CallWazaSeq(WAZA_Dokudoku);
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 6U) == 1) {
        fightWaza_SetDamage(temp_r30, (u32) fightOutPokemonMaxHpWaruValue(arg0, 8U));
        fightSeq_CallWazaSeq(WAZA_Yakedo);
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x17U) == 1) {
        if (fightOutPokemonIsJoutaiDataId(arg0, 8U) == 1) {
            fightWaza_SetDamage(temp_r30, (u32) fightOutPokemonMaxHpWaruValue(arg0, 4U));
            fightSeq_CallWazaSeq(WAZA_Akumu);
        } else {
            fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x18U) == 1) {
        fightWaza_SetDamage(temp_r30, (u32) fightOutPokemonMaxHpWaruValue(arg0, 4U));
        fightSeq_CallWazaSeq(WAZA_Noroi);
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0xEU) == 1) {
        temp_r27 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0xEU);
        temp_r3_3 = fightOutPokemonGetIdBuffJoutaiDataId(arg0, 0xEU);
        fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(wazaDB_GetName(temp_r3_3))));
        if (temp_r27 >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0xEU)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0xEU);
            var_r3 = WAZA_ShimeEnd;
        } else {
            UserWork[0x160A4] = (s8) temp_r3_3;
            UserWork[0x160A5] = (u8) (temp_r3_3 >> 8U);
            fightWaza_SetDamage(temp_r30, (u32) fightOutPokemonMaxHpWaruValue(arg0, 0x10U));
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0xEU, (s8) (temp_r27 + 1));
            var_r3 = WAZA_Shime;
        }
        fightSeq_CallWazaSeq(var_r3);
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x3EU) == 1) {
        temp_r25 = fightOutPokemonMaxHpWaruValue(arg0, 0x10U);
        var_r25 = ((HSD_Rand() % 3) + temp_r25) - 1;
        if (var_r25 <= 0) {
            var_r25 = 1;
        }
        fightWaza_SetDamage(temp_r30, (u32) var_r25);
        fightSeq_CallWazaSeq(WAZA_Revers);
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0xBU) == 1) {
        fightFloorLoopValidFightOutPokemon(NULL, _fightSeqSideJoutaiCheckSubSawagu__FPvUsPv, NULL, 0U);
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
        temp_r26_2 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0xBU);
        temp_r0 = temp_r26_2 + 1;
        if (temp_r0 >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0xBU)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0xBU);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0xBU, temp_r0);
        }
        if (fightOutPokemonCheckNoAttackFlag(arg0) == 1) {
            goto block_64;
        }
        if (fightOutPokemonIsJoutaiDataId(arg0, 0xBU) == 1) {
            fightOutPokemonWriteJoutaiDataId(arg0, 0x22U, 0U);
            ServerWork.flags[5] = 0;
        } else {
block_64:
            fightOutPokemonInitJoutaiKeep(arg0);
            ServerWork.flags[5] = 1;
        }
        fightSeq_CallWazaSeq(WAZA_Sawagu);
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0xDU) == 1) {
        temp_r26_3 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0xDU);
        temp_r0_2 = temp_r26_3 + 1;
        if (temp_r0_2 >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0xDU)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0xDU);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0xDU, temp_r0_2);
        }
        if (fightOutPokemonCheckNoAttackFlag(arg0) == 1) {
            fightOutPokemonInitJoutaiKeep(arg0);
        } else if ((fightOutPokemonIsJoutaiDataId(arg0, 0xDU) == 0) && (fightOutPokemonIsJoutaiDataId(arg0, 0x22U) == 1)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x22U);
            if (fightOutPokemonIsJoutaiDataId(arg0, 9U) == 0) {
                temp_r25_2 = TSUIKASeqTbl[7];
                ServerWork.flags[3] = 0x47;
                TSUIKASeqTbl[7] = WAZA_Null;
                temp_r27_2 = fightSeq_GetWazaSeq();
                fightSeqTuikaAct(1U, 0U);
                fightSeq_JumpWazaSeq(temp_r27_2);
                TSUIKASeqTbl[7] = temp_r25_2;
                if (fightOutPokemonIsJoutaiDataId(arg0, 9U) == 1) {
                    fightSeq_CallWazaSeq(WAZA_AbareruEnd);
                }
            }
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x29U) == 1) {
        temp_r26_4 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x29U);
        temp_r25_3 = fightOutPokemonGetIdBuffJoutaiDataId(arg0, 0x29U);
        fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x29U, (s8) (temp_r26_4 + 1));
        if (pokemonSearchWazaDataId(temp_r29, (u16) temp_r25_3) < 0) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x29U);
        } else if ((s8) (temp_r26_4 + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x29U)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x29U);
            fightSeq_CallWazaSeq(WAZA_KanashibariEnd);
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x2AU) == 1) {
        temp_r27_3 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x2AU);
        temp_r26_5 = fightOutPokemonGetIdBuffJoutaiDataId(arg0, 0x2AU);
        temp_r3_4 = fightOutPokemonGetBuffJoutaiDataId(arg0, 0x2AU);
        temp_r27_4 = pokemon_GetPokemonWazaDataId(temp_r29, (u8) temp_r3_4);
        fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x2AU, (s8) (temp_r27_3 + 1));
        if (temp_r27_4 != (u16) temp_r26_5) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x2AU);
        } else if (((s8) (temp_r27_3 + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x2AU)) || (pokemon_GetPokemonWazaPp(temp_r29, temp_r3_4) == 0)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x2AU);
            fightSeq_CallWazaSeq(WAZA_EncoreEnd);
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x1DU) == 1) {
        temp_r27_5 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x1DU);
        temp_r0_3 = temp_r27_5 + 1;
        if (temp_r0_3 >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x1DU)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x1DU);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x1DU, temp_r0_3);
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x24U) == 1) {
        temp_r27_6 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x24U);
        temp_r0_4 = temp_r27_6 + 1;
        if (temp_r0_4 >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x24U)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x24U);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x24U, temp_r0_4);
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x30U) == 1) {
        temp_r27_7 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x30U);
        temp_r0_5 = temp_r27_7 + 1;
        if (temp_r0_5 >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x30U)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x30U);
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x30U, temp_r0_5);
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x26U) == 1) {
        temp_r27_8 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x26U);
        temp_r0_6 = temp_r27_8 + 1;
        if (temp_r0_6 >= fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x26U)) {
            fightOutPokemonInitJoutaiDataId(arg0, 0x26U);
            if ((fightOutPokemonIsJoutaiNormal(arg0) == 1) && (temp_r28 != 0x48) && (temp_r28 != 0xF) && (fightSeqSawaguCheck((u8 *) arg0) == 0) && (fightSeqRegulationOverTwoCheck(8U, arg0) != 1) && (fightOutPokemonCheckWriteJoutaiDataId(arg0, 8U) == 2)) {
                fightOutPokemonWriteJoutaiDataId(arg0, 8U, 0U);
                fightOutPokemonInitJoutaiKeep(arg0);
                fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
                fightFloor_SetTuikakoukaPokemonPtr(NULL, arg0);
                fightSeq_CallWazaSeq(WAZA_AddNemuri2);
            }
        } else {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x26U, temp_r0_6);
        }
    }
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    ServerStatusFlag = ServerStatusFlag | 0x01000000 | 0x20;
    fightSeqCheckDarkPokemonJoutaiHyperAct(arg0, 1U);
    ServerStatusFlag &= 0xFEFFFFDF;
    wazaSequenceSysFreeAllWaza();
    return 1;
}

s32 _fightSeqSideJoutaiCheckSubSawagu__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    u16 temp_r31;

    temp_r31 = fightOutPokemonGetTokuseiDataId(arg0);
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    if ((fightOutPokemonIsJoutaiDataId(arg0, 8U) == 1) && (temp_r31 != 0x2B)) {
        fightOutPokemonInitJoutaiDataId(arg0, 8U);
        fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
        ServerWork.flags[5] = 1;
        fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
        fightSeq_CallWazaSeq(WAZA_SawaguMezame);
        fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
    }
    return 1;
}

void fightSeqFloorJoutaiCheck(void) {
    u8 *sp8;
    u8 *var_r3;
    FightSide *temp_r3;
    u8 var_r31;
    SeqServerWork *temp_r31;
    u8 temp_r30;
    s8 temp_r30_2;
    u8 *var_r3_2;
    u8 *var_r3_3;
    u8 *var_r3_4;
    FightOutPokemon *temp_r3_2;
    FightSide *temp_r3_3;
    FightOutPokemon *temp_r3_4;
    FightSide *temp_r3_5;
    FightOutPokemon *temp_r3_6;
    FightSide *temp_r3_7;
    FightOutPokemon *temp_r3_8;
    FightOutPokemon *var_r29;
    s8 temp_r29;
    FightOutPokemon *var_r29_2;
    FightOutPokemon *var_r29_3;
    s8 temp_r29_2;
    s8 temp_r29_3;
    s8 temp_r29_4;
    s8 temp_r29_5;
    s8 temp_r29_6;
    s8 temp_r29_7;
    s8 temp_r29_8;
    u8 var_r28;
    u8 var_r28_2;
    u8 var_r28_3;
    FightOutPokemon *var_r27;

    if (fightGetFightResultId() == 0) {
        temp_r30 = fightFloorGetNowTenkouDataId(NULL, 0U);
        fightFloorCreateFightOutPokemonPtrAry(NULL);
        fightFloorSortFightOutPokemonPtrAry(NULL, 1);
        sp8 = NULL;
        fightFloorLoopValidFightOutPokemon(NULL, _fightSeqFloorJoutaiCheckSubGetSeqFightOutPokemonPtr__FPvUsPv, &sp8, 0U);
        var_r31 = 0;
        while (var_r31 < 2U) {
            temp_r3 = fightFloorGetValidFightSidePtr(NULL, var_r31);
            if (temp_r3 != NULL) {
                temp_r3_2 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xCU, (FightOutPokemon *) temp_r3);
                var_r27 = temp_r3_2;
                if (fightOutPokemonCheckFightOut(temp_r3_2) == 0) {
                    var_r27 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xDU, (FightOutPokemon *) temp_r3);
                }
                fightFloor_SetAttackPokemonPtr(NULL, (u8 *) var_r27);
                if (fightSideIsJoutaiDataId(temp_r3, 0x48U) == 1) {
                    temp_r29 = fightSideGetKaisuuJoutaiDataId((u8 *) temp_r3, 0x48);
                    if ((s8) (fightSideGetNowKaisuuJoutaiDataId((u8 *) temp_r3, 0x48) + 1) < temp_r29) {
                        fightSideSetNowKaisuuJoutaiDataId((u8 *) temp_r3, 0x48);
                    } else {
                        fightSideInitJoutaiDataId((u8 *) temp_r3, 0x48);
                        fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(wazaDB_GetName(0x73U))));
                        fightSeq_CallWazaSeq(WAZA_ReflecEnd);
                    }
                }
            }
            var_r31 += 1;
        }
        wazaSequenceSysFreeAllWaza();
        var_r28 = 0;
        temp_r31 = &ServerWork;
        while (var_r28 < 2U) {
            temp_r3_3 = fightFloorGetValidFightSidePtr(NULL, var_r28);
            if (temp_r3_3 != NULL) {
                temp_r3_4 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xCU, (FightOutPokemon *) temp_r3_3);
                var_r29 = temp_r3_4;
                if (fightOutPokemonCheckFightOut(temp_r3_4) == 0) {
                    var_r29 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xDU, (FightOutPokemon *) temp_r3_3);
                }
                fightFloor_SetAttackPokemonPtr(NULL, (u8 *) var_r29);
                if (fightSideIsJoutaiDataId(temp_r3_3, 0x49U) == 1) {
                    temp_r29_2 = fightSideGetKaisuuJoutaiDataId((u8 *) temp_r3_3, 0x49);
                    if ((s8) (fightSideGetNowKaisuuJoutaiDataId((u8 *) temp_r3_3, 0x49) + 1) < temp_r29_2) {
                        fightSideSetNowKaisuuJoutaiDataId((u8 *) temp_r3_3, 0x49);
                    } else {
                        fightSideInitJoutaiDataId((u8 *) temp_r3_3, 0x49);
                        fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(wazaDB_GetName(0x71U))));
                        temp_r31->flags[5] = var_r28;
                        fightSeq_CallWazaSeq(WAZA_ReflecEnd);
                    }
                }
            }
            var_r28 += 1;
        }
        wazaSequenceSysFreeAllWaza();
        var_r28_2 = 0;
        while (var_r28_2 < 2U) {
            temp_r3_5 = fightFloorGetValidFightSidePtr(NULL, var_r28_2);
            if (temp_r3_5 != NULL) {
                temp_r3_6 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xCU, (FightOutPokemon *) temp_r3_5);
                var_r29_2 = temp_r3_6;
                if (fightOutPokemonCheckFightOut(temp_r3_6) == 0) {
                    var_r29_2 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xDU, (FightOutPokemon *) temp_r3_5);
                }
                fightFloor_SetAttackPokemonPtr(NULL, (u8 *) var_r29_2);
                if (fightSideIsJoutaiDataId(temp_r3_5, 0x4CU) == 1) {
                    temp_r29_3 = fightSideGetKaisuuJoutaiDataId((u8 *) temp_r3_5, 0x4C);
                    if ((s8) (fightSideGetNowKaisuuJoutaiDataId((u8 *) temp_r3_5, 0x4C) + 1) < temp_r29_3) {
                        fightSideSetNowKaisuuJoutaiDataId((u8 *) temp_r3_5, 0x4C);
                    } else {
                        fightSideInitJoutaiDataId((u8 *) temp_r3_5, 0x4C);
                        fightMsgctrlSetValue(0xDU, (u32)(GSmsgGetGSchar(wazaDB_GetName(0x36U))));
                        fightSeq_CallWazaSeq(WAZA_ReflecEnd);
                    }
                }
            }
            var_r28_2 += 1;
        }
        wazaSequenceSysFreeAllWaza();
        var_r28_3 = 0;
        while (var_r28_3 < 2U) {
            temp_r3_7 = fightFloorGetValidFightSidePtr(NULL, var_r28_3);
            if (temp_r3_7 != NULL) {
                temp_r3_8 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xCU, (FightOutPokemon *) temp_r3_7);
                var_r29_3 = temp_r3_8;
                if (fightOutPokemonCheckFightOut(temp_r3_8) == 0) {
                    var_r29_3 = (FightOutPokemon *)fightTargetGetPtrAsNowFightType(0xDU, (FightOutPokemon *) temp_r3_7);
                }
                fightFloor_SetAttackPokemonPtr(NULL, (u8 *) var_r29_3);
                if (fightSideIsJoutaiDataId(temp_r3_7, 0x4BU) == 1) {
                    temp_r29_4 = fightSideGetKaisuuJoutaiDataId((u8 *) temp_r3_7, 0x4B);
                    if ((s8) (fightSideGetNowKaisuuJoutaiDataId((u8 *) temp_r3_7, 0x4B) + 1) < temp_r29_4) {
                        fightSideSetNowKaisuuJoutaiDataId((u8 *) temp_r3_7, 0x4B);
                    } else {
                        fightSideInitJoutaiDataId((u8 *) temp_r3_7, 0x4B);
                        fightSeq_CallWazaSeq(WAZA_ShinpiEnd);
                    }
                }
            }
            var_r28_3 += 1;
        }
        wazaSequenceSysFreeAllWaza();
        fightFloorLoopValidFightOutPokemon(NULL, _fightSeqFloorJoutaiCheckSubNegaigoto__FPvUsPv, NULL, 1U);
        wazaSequenceSysFreeAllWaza();
        if (temp_r30 == 2) {
            fightFloor_SetAttackPokemonPtr(NULL, sp8);
            if (fightFloorIsJoutaiDataId(NULL, 0x50) == 0) {
                temp_r29_5 = fightFloorGetKaisuuJoutaiDataId(NULL, 0x55);
                if ((s8) (fightFloorGetNowKaisuuJoutaiDataId(NULL, 0x55) + 1) < temp_r29_5) {
                    fightFloorSetNowKaisuuJoutaiDataId(NULL, 0x55);
                    temp_r31->flags[5] = 0U;
                } else {
                    fightFloorInitJoutaiDataId(NULL, 0x55);
                    temp_r31->flags[5] = 2U;
                }
            } else {
                temp_r31->flags[5] = 0U;
            }
            fightSeq_CallWazaSeq(WAZA_Amefuri);
        }
        wazaSequenceSysFreeAllWaza();
        if (fightGetFightResultId() == 0) {
            if (temp_r30 == 3) {
                fightFloor_SetAttackPokemonPtr(NULL, sp8);
                if (fightFloorIsJoutaiDataId(NULL, 0x51) == 1) {
                    var_r3 = WAZA_WeatherDamage;
                } else {
                    temp_r29_6 = fightFloorGetKaisuuJoutaiDataId(NULL, 0x56);
                    if ((s8) (fightFloorGetNowKaisuuJoutaiDataId(NULL, 0x56) + 1) < temp_r29_6) {
                        fightFloorSetNowKaisuuJoutaiDataId(NULL, 0x56);
                        var_r3 = WAZA_WeatherDamage;
                    } else {
                        fightFloorInitJoutaiDataId(NULL, 0x56);
                        var_r3 = WAZA_WeatherDamageEnd;
                    }
                }
                UserWork[0x160A4] = 0xC;
                temp_r31->flags[5] = 0U;
                fightSeq_CallWazaSeq(var_r3);
            }
            wazaSequenceSysFreeAllWaza();
            if (fightGetFightResultId() == 0) {
                if (temp_r30 == 1) {
                    fightFloor_SetAttackPokemonPtr(NULL, sp8);
                    if (fightFloorIsJoutaiDataId(NULL, 0x4F) == 1) {
                        var_r3_2 = WAZA_Hare;
                    } else {
                        temp_r29_7 = fightFloorGetKaisuuJoutaiDataId(NULL, 0x54);
                        if ((s8) (fightFloorGetNowKaisuuJoutaiDataId(NULL, 0x54) + 1) < temp_r29_7) {
                            fightFloorSetNowKaisuuJoutaiDataId(NULL, 0x54);
                            var_r3_2 = WAZA_Hare;
                        } else {
                            fightFloorInitJoutaiDataId(NULL, 0x54);
                            var_r3_2 = WAZA_HareEnd;
                        }
                    }
                    fightSeq_CallWazaSeq(var_r3_2);
                }
                wazaSequenceSysFreeAllWaza();
                if (fightGetFightResultId() == 0) {
                    if (temp_r30 == 4) {
                        fightFloor_SetAttackPokemonPtr(NULL, sp8);
                        temp_r29_8 = fightFloorGetKaisuuJoutaiDataId(NULL, 0x53);
                        if ((s8) (fightFloorGetNowKaisuuJoutaiDataId(NULL, 0x53) + 1) < temp_r29_8) {
                            fightFloorSetNowKaisuuJoutaiDataId(NULL, 0x53);
                            var_r3_3 = WAZA_WeatherDamage;
                        } else {
                            fightFloorInitJoutaiDataId(NULL, 0x53);
                            var_r3_3 = WAZA_WeatherDamageEnd;
                        }
                        UserWork[0x160A4] = 0xD;
                        temp_r31->flags[5] = 1U;
                        fightSeq_CallWazaSeq(var_r3_3);
                    }
                    wazaSequenceSysFreeAllWaza();
                    if (fightGetFightResultId() == 0) {
                        if (temp_r30 == 5) {
                            fightFloor_SetAttackPokemonPtr(NULL, sp8);
                            temp_r30_2 = fightFloorGetKaisuuJoutaiDataId(NULL, 0x52);
                            if ((s8) (fightFloorGetNowKaisuuJoutaiDataId(NULL, 0x52) + 1) < temp_r30_2) {
                                fightFloorSetNowKaisuuJoutaiDataId(NULL, 0x52);
                                var_r3_4 = WAZA_WeatherDamage;
                            } else {
                                fightFloorInitJoutaiDataId(NULL, 0x52);
                                var_r3_4 = WAZA_WeatherDamageEnd;
                            }
                            UserWork[0x160A4] = 0x25;
                            temp_r31->flags[5] = 2U;
                            fightSeq_CallWazaSeq(var_r3_4);
                        }
                        wazaSequenceSysFreeAllWaza();
                        fightGetFightResultId();
                    }
                }
            }
        }
    }
}

s32 _fightSeqFloorJoutaiCheckSubGetSeqFightOutPokemonPtr__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    if (fightOutPokemon_GetSequencePtr(arg0) != NULL) {
        if (arg2 != NULL) {
            *(FightOutPokemon **)arg2 = arg0;
        }
        return 0;
    }
    return 1;
}

s32 _fightSeqFloorJoutaiCheckSubNegaigoto__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    s8 temp_r3;
    u32 temp_r31;

    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x35U) == 1) {
        temp_r31 = fightOutPokemonGetKaisuuJoutaiDataId(arg0, 0x35U);
        temp_r3 = (s32)(s8)fightOutPokemonGetNowKaisuuJoutaiDataId(arg0, 0x35U) + 1;
        if (temp_r3 < (s8) temp_r31) {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x35U, temp_r3);
        } else {
            fightFloor_SetAttackPokemonPtr(NULL, (u8 *) arg0);
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(NULL, arg0);
            fightSeq_CallWazaSeq(WAZA_Negaigoto);
            fightOutPokemonInitJoutaiDataId(arg0, 0x35U);
        }
    }
    return 1;
}

void fightSeqPressurePpdecCheckHorobinouta(FightOutPokemon *arg0) {
    s32 temp_r4;
    u8 temp_r3;
    Pokemon *temp_r3_2;
    s8 temp_r3_3;
    u8 temp_r3_4;

    if (arg0 != NULL) {
        temp_r3 = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x2EU, 0U, arg0);
        if (temp_r3 != 0) {
            temp_r3_2 = fightOutPokemonGetPokemonPtr(arg0);
            temp_r3_3 = pokemonSearchWazaDataId(temp_r3_2, 0xC3U);
            if (temp_r3_3 >= 0) {
                temp_r3_4 = pokemon_GetPokemonWazaPp(temp_r3_2, (u16) temp_r3_3);
                temp_r4 = temp_r3 - temp_r3_4;
                pokemon_SetPokemonWazaPp(temp_r3_2, temp_r3_3, (temp_r3_4 >= temp_r3 ? (u8)(temp_r3_4 - temp_r3) : 0));
                fightSeqPpdecMonomane(arg0, (s8) (u8) temp_r3_3, 0);
            }
        }
    }
}

void fightSeqPressurePpdecCheckHuuin(FightOutPokemon *arg0) {
    s32 temp_r4;
    u8 temp_r3;
    Pokemon *temp_r3_2;
    s8 temp_r3_3;
    u8 temp_r3_4;

    if (arg0 != NULL) {
        temp_r3 = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x2EU, 2U, arg0);
        if (temp_r3 != 0) {
            temp_r3_2 = fightOutPokemonGetPokemonPtr(arg0);
            temp_r3_3 = pokemonSearchWazaDataId(temp_r3_2, 0x11EU);
            if (temp_r3_3 >= 0) {
                temp_r3_4 = pokemon_GetPokemonWazaPp(temp_r3_2, (u16) temp_r3_3);
                temp_r4 = temp_r3 - temp_r3_4;
                pokemon_SetPokemonWazaPp(temp_r3_2, temp_r3_3, (temp_r3_4 >= temp_r3 ? (u8)(temp_r3_4 - temp_r3) : 0));
                fightSeqPpdecMonomane(arg0, (s8) (u8) temp_r3_3, 0);
            }
        }
    }
}

void fightSeqPressurePpdecCheck(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2) {
    u32 var_r5;
    Pokemon *temp_r3;
    s8 temp_r3_2;
    u32 temp_r3_3;

    if ((arg0 != NULL) && (arg1 != NULL) && (fightOutPokemonGetTokuseiDataId(arg0) == 0x2E)) {
        temp_r3 = fightOutPokemonGetPokemonPtr(arg1);
        temp_r3_2 = pokemonSearchWazaDataId(temp_r3, arg2);
        if (temp_r3_2 >= 0) {
            temp_r3_3 = pokemon_GetPokemonWazaPp(temp_r3, (u16) temp_r3_2);
            var_r5 = temp_r3_3;
            if ((u8) temp_r3_3 != 0) {
                var_r5 = (u32) (u8) ((u8) temp_r3_3 - 1);
            }
            pokemon_SetPokemonWazaPp(temp_r3, temp_r3_2, var_r5);
            fightSeqPpdecMonomane(arg1, (s8) (u8) temp_r3_2, 0);
        }
    }
}

s32 fightSeqWazaDamageCalcHikaePokemon(FightOutPokemon *arg0, FightPokemon *arg1, FightSide *arg2, u32 arg3, u16 arg4, s32 arg5) {
    s32 sp28;
    s32 sp24;
    s32 sp20;
    u32 sp1C;
    s32 sp18;
    s32 sp14;
    u16 sp10;
    Hero *spC;
    FightSide *sp8;
    const SeqItemTypePower *temp_r6;
    s32 var_r5;
    u16 var_r3;
    Pokemon *temp_r3;
    u16 temp_r31;
    u32 temp_r30;
    u16 var_r3_2;
    u16 temp_r29;
    u8 temp_r28;
    u8 var_r27;
    u8 temp_r26;
    Hero *temp_r25;
    u8 temp_r24;
    u16 var_r23;
    u32 var_r22;
    u32 var_r21;
    u32 var_r20;
    u32 var_r19;
    u16 temp_r18;
    s32 var_r14;
    u16 temp_r14;
    u32 var_r14_2;
    u32 var_r14_3;
    s32 temp_r14_2;
    s32 temp_r14_3;
    u16 var_r0;
    s32 var_ctr;

    sp8 = arg2;
    temp_r26 = fightFloorGetNowTenkouDataId(NULL, 1U);
    temp_r24 = fightFloor_GetFightKindDoBadgeCheckFlag(NULL);
    sp14 = fightFloor_GetFightKindDoItemSoubiTokukoutokubouupFlag(NULL);
    if (arg4 == 0) {
        var_r0 = wazaDB_GetIryoku(arg3);
    } else {
        var_r0 = arg4;
    }
    var_r23 = var_r0;
    if (arg5 < 0) {
        var_r27 = wazaDB_GetZokuseiDataId((u16) arg3);
    } else {
        var_r27 = (u8) (u16) arg5;
    }
    if (wazaCheckDarkWaza((u16) arg3) == 1) {
        sp18 = waza_GetZokuseiKindData((u16) arg3);
    } else {
        sp18 = zokuseiBiosGetWazaKind((u32) var_r27);
    }
    wazaDB_GetRangeId((u16) arg3);
    temp_r28 = fightWaza_GetCritical(fightOutPokemon_GetFightWazaPtr(arg0));
    temp_r29 = fightOutPokemonGetTokuseiDataId(arg0);
    temp_r30 = fightOutPokemonGetSoubiItemSoubiDataId(arg0);
    sp1C = figthOutPokemonGetSoubiItemBuff(arg0);
    temp_r31 = figthOutPokemonGetPokemonDataId(arg0);
    temp_r3 = fightOutPokemonGetPokemonPtr(arg0);
    var_r22 = pokemon_GetPhyAtk(temp_r3);
    var_r20 = pokemon_GetSpeAtk(temp_r3);
    spC = (Hero *)fightFloorGetFightOutPokemonPtrToHeroPtr(NULL, arg0);
    sp20 = fightOutPokemon_GetAbicntPhyAtk(arg0);
    sp24 = fightOutPokemon_GetAbicntSpeAtk(arg0);
    sp28 = figthOutPokemonGetLevel(arg0);
    temp_r18 = pokemon_GetPokemonDataId(fightPokemon_GetPokemonBuffPtr(arg1));
    sp10 = (u16) pokemonDB_GetTokuseiDataId(temp_r18, pokemon_GetTokuseiFlag(fightPokemon_GetPokemonBuffPtr(arg1)));
    fightPokemon_GetPokemonBuffPtr(arg1);
    temp_r14 = pokemonGetSoubiItemSoubiDataId();
    fightPokemon_GetPokemonBuffPtr(arg1);
    pokemonGetSoubiItemBuff();
    var_r21 = pokemon_GetPhyDef(fightPokemon_GetPokemonBuffPtr(arg1));
    var_r19 = pokemon_GetSpeDef(fightPokemon_GetPokemonBuffPtr(arg1));
    temp_r25 = fightTrainer_GetHeroPtr(fightFloorGetFightPokemonPtrToFightTrainerPtr(NULL, arg1));
    if ((temp_r29 == 0x25) || (temp_r29 == 0x4A)) {
        var_r22 = (var_r22 * 2) & 0xFFFE;
    }
    if ((temp_r24 == 1) && ((u8) (heroGetStatus(spC, 0xFU, 0U) != 0) == 1)) {
        var_r22 = (u32) (u16) ((s32) ((u16) var_r22 * 0x6E) / 100);
    }
    if ((temp_r24 == 1) && ((u8) (heroGetStatus(temp_r25, 0x13U, 0U) != 0) == 1)) {
        var_r21 = (u32) (u16) ((s32) ((u16) var_r21 * 0x6E) / 100);
    }
    if ((temp_r24 == 1) && ((u8) (heroGetStatus(spC, 0x15U, 0U) != 0) == 1)) {
        var_r20 = (u32) (u16) ((s32) ((u16) var_r20 * 0x6E) / 100);
    }
    if ((temp_r24 == 1) && ((u8) (heroGetStatus(temp_r25, 0x15U, 0U) != 0) == 1)) {
        var_r19 = (u32) (u16) ((s32) ((u16) var_r19 * 0x6E) / 100);
    }
    var_r5 = 0;
    var_ctr = 0x11;
    do {
        temp_r6 = (const SeqItemTypePower *)((const u8 *)SoubiItemWazaTypePowUpTbl + var_r5);
        if (((s32) (u16) temp_r30 == (s32) temp_r6->item) && ((s32) (u16) var_r27 == (s32) temp_r6->type)) {
            switch ((s32) (u8) sp18) {              /* switch 1; irregular */
            case 1:                                 /* switch 1 */
                var_r22 = (u32) (u16) ((s32) ((u16) var_r22 * (sp1C + 0x64)) / 100);
                break;
            case 2:                                 /* switch 1 */
                var_r20 = (u32) (u16) ((s32) ((u16) var_r20 * (sp1C + 0x64)) / 100);
                break;
            }
        }
        var_r5 += 2;
        var_ctr -= 1;
    } while (var_ctr != 0);
    if ((u16) temp_r30 == 0x1D) {
        var_r22 = (u32) (u16) ((s32) ((u16) var_r22 * 0x96) / 100);
    }
    if (((u8) sp14 == 1) && ((u16) temp_r30 == 0x22) && ((temp_r31 == 0x198) || (temp_r31 == 0x197))) {
        var_r20 = (u32) (u16) ((s32) ((u16) var_r20 * 0x96) / 100);
    }
    if (((u8) sp14 == 1) && (temp_r14 == 0x22) && ((temp_r18 == 0x198) || (temp_r18 == 0x197))) {
        var_r19 = (u32) (u16) ((s32) ((u16) var_r19 * 0x96) / 100);
    }
    if (((u16) temp_r30 == 0x23) && (temp_r31 == 0x175)) {
        var_r20 = (var_r20 * 2) & 0xFFFE;
    }
    if ((temp_r14 == 0x24) && (temp_r18 == 0x175)) {
        var_r19 = (var_r19 * 2) & 0xFFFE;
    }
    if (((u16) temp_r30 == 0x2D) && (temp_r31 == 0x19)) {
        var_r20 = (var_r20 * 2) & 0xFFFE;
    }
    if ((temp_r14 == 0x40) && (temp_r18 == 0x84)) {
        var_r21 = (var_r21 * 2) & 0xFFFE;
    }
    if (((u16) temp_r30 == 0x41) && ((temp_r31 == 0x68) || (temp_r31 == 0x69))) {
        var_r22 = (var_r22 * 2) & 0xFFFE;
    }
    if ((sp10 == 0x2F) && (((u16) var_r27 == 0xA) || ((u16) var_r27 == 0xF))) {
        var_r20 = (u32) (u16) ((s32) (u16) var_r20 / 2);
    }
    if (temp_r29 == 0x37) {
        var_r22 = (u32) (u16) ((s32) ((u16) var_r22 * 0x96) / 100);
    }
    if ((temp_r29 == 0x39) && (fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x3AU, 0U, NULL) != 0)) {
        var_r20 = (u32) (u16) ((s32) ((u16) var_r20 * 0x96) / 100);
    }
    if ((temp_r29 == 0x3A) && (fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x39U, 0U, NULL) != 0)) {
        var_r20 = (u32) (u16) ((s32) ((u16) var_r20 * 0x96) / 100);
    }
    if ((temp_r29 == 0x3E) && (fightOutPokemonIsJoutaiNormal(arg0) == 0)) {
        var_r22 = (u32) (u16) ((s32) ((u16) var_r22 * 0x96) / 100);
    }
    if ((sp10 == 0x3F) && (pokemonIsJoutaiNormal(fightPokemon_GetPokemonBuffPtr(arg1)) == 0)) {
        var_r21 = (u32) (u16) ((s32) ((u16) var_r21 * 0x96) / 100);
    }
    if (((u16) var_r27 == 0xD) && (fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(NULL, 0x38) != 0)) {
        var_r23 = (u16) ((s32) var_r23 / 2);
    }
    if (((u16) var_r27 == 0xA) && (fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(NULL, 0x39) != 0)) {
        var_r23 = (u16) ((s32) var_r23 / 2);
    }
    if (((u16) var_r27 == 0xC) && (temp_r29 == 0x41) && (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) != 0)) {
        var_r23 = (u16) ((s32) (var_r23 * 0x96) / 100);
    }
    if (((u16) var_r27 == 0xA) && (temp_r29 == 0x42) && (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) != 0)) {
        var_r23 = (u16) ((s32) (var_r23 * 0x96) / 100);
    }
    if (((u16) var_r27 == 0xB) && (temp_r29 == 0x43) && (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) != 0)) {
        var_r23 = (u16) ((s32) (var_r23 * 0x96) / 100);
    }
    if (((u16) var_r27 == 6) && (temp_r29 == 0x44) && (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) != 0)) {
        var_r23 = (u16) ((s32) (var_r23 * 0x96) / 100);
    }
    if (wazaDB_GetSeqId((u16) arg3) == 7) {
        var_r21 = (var_r21 >> 1U) & 0x7FFF;
    }
    switch ((s32) (u8) sp18) {                      /* switch 2; irregular */
    case 1:                                         /* switch 2 */
        if (temp_r28 == 2) {
            if ((u8) sp20 > 6U) {
                var_r14_2 = fightAbicntDoKakeWaru((u8) sp20, (u32) (u16) var_r22);
            } else {
                var_r14_2 = (u32) (u16) var_r22;
            }
        } else {
            var_r14_2 = fightAbicntDoKakeWaru((u8) sp20, (u32) (u16) var_r22);
        }
        if (temp_r28 == 2) {
            var_r3 = (u16) var_r21;
        } else {
            var_r3 = fightAbicntDoKakeWaru(6U, (u32) (u16) var_r21);
        }
        temp_r14_2 = (s32) (var_r14_2 * var_r23 * (((s32) ((sp28 * 2) & 0x1FE) / 5) + 2)) / (s32) var_r3;
        var_r14 = temp_r14_2 / 50;
        if ((fightOutPokemonIsJoutaiDataId(arg0, 6U) == 1) && (temp_r29 != 0x3E)) {
            var_r14 = (temp_r14_2 / 50) / 2;
        }
        if ((fightSideIsJoutaiDataId(sp8, 0x48U) == 1) && (temp_r28 == 1)) {
            fightFloor_GetFightSideFightOutPokemonSideMax(NULL);
            var_r14 = var_r14 / 2;
        }
        fightFloor_GetFightSideFightOutPokemonSideMax(NULL);
        if (var_r14 == 0) {
            var_r14 = 1;
        }
        break;
    case 2:                                         /* switch 2 */
        if (temp_r28 == 2) {
            if ((u8) sp24 > 6U) {
                var_r14_3 = fightAbicntDoKakeWaru((u8) sp24, (u32) (u16) var_r20);
            } else {
                var_r14_3 = (u32) (u16) var_r20;
            }
        } else {
            var_r14_3 = fightAbicntDoKakeWaru((u8) sp24, (u32) (u16) var_r20);
        }
        if (temp_r28 == 2) {
            var_r3_2 = (u16) var_r19;
        } else {
            var_r3_2 = fightAbicntDoKakeWaru(6U, (u32) (u16) var_r19);
        }
        temp_r14_3 = (s32) (var_r14_3 * var_r23 * (((s32) ((sp28 * 2) & 0x1FE) / 5) + 2)) / (s32) var_r3_2;
        var_r14 = temp_r14_3 / 50;
        if ((fightSideIsJoutaiDataId(sp8, 0x49U) == 1) && (temp_r28 == 1)) {
            fightFloor_GetFightSideFightOutPokemonSideMax(NULL);
            var_r14 = (temp_r14_3 / 50) / 2;
        }
        fightFloor_GetFightSideFightOutPokemonSideMax(NULL);
        if (temp_r26 == 2) {
            switch ((s32) (u16) var_r27) {          /* switch 3; irregular */
            case 10:                                /* switch 3 */
                var_r14 = var_r14 / 2;
                break;
            case 11:                                /* switch 3 */
                var_r14 = (s32) (var_r14 * 0xF) / 10;
                break;
            }
        }
        if ((tenkouDataBiosGetSolarFlag(temp_r26) == 0) && ((u16) arg3 == 0x4C)) {
            var_r14 = var_r14 / 2;
        }
        if (temp_r26 == 1) {
            switch ((s32) (u16) var_r27) {          /* switch 4; irregular */
            case 10:                                /* switch 4 */
                var_r14 = (s32) (var_r14 * 0xF) / 10;
                break;
            case 11:                                /* switch 4 */
                var_r14 = var_r14 / 2;
                break;
            }
        }
        if ((fightOutPokemonIsJoutaiDataId(arg0, 0x3AU) == 1) && ((u16) var_r27 == 0xA)) {
            var_r14 = (s32) (var_r14 * 0xF) / 10;
        }
        break;
    default:                                        /* switch 2 */
        var_r14 = 0;
        break;
    }
    return var_r14 + 2;
}

u16 fightSeqWazaDamageCalc(FightOutPokemon *arg0, FightOutPokemon *arg1, u8 arg2, u16 arg3, u32 arg4, u16 arg5) {
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    u32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    Hero *spC;
    FightSide *sp8;
    const SeqItemTypePower *temp_r6;
    s32 var_r5;
    u32 var_r3;
    Pokemon *temp_r3;
    u16 temp_r31;
    u32 temp_r30;
    u32 var_r3_2;
    Pokemon *temp_r3_2;
    u16 temp_r29;
    u32 temp_r28;
    u16 temp_r27;
    u8 temp_r26;
    u8 var_r25;
    Hero *temp_r24;
    u8 temp_r23;
    u16 var_r22;
    u32 var_r21;
    u32 var_r20;
    u32 var_r19;
    u32 var_r18;
    s32 var_r14;
    u16 temp_r14;
    u32 var_r14_2;
    u32 var_r14_3;
    s32 temp_r14_2;
    s32 temp_r14_3;
    u16 var_r0;
    s32 var_ctr;

    sp8 = (FightSide *) arg2;
    sp10 = fightFloorGetNowTenkouDataId(NULL, 1U);
    temp_r23 = fightFloor_GetFightKindDoBadgeCheckFlag(NULL);
    sp14 = fightFloor_GetFightKindDoItemSoubiTokukoutokubouupFlag(NULL);
    if ((u16) arg4 == 0) {
        var_r0 = wazaDB_GetIryoku((u32) arg3);
    } else {
        var_r0 = (u16) arg4;
    }
    var_r22 = var_r0;
    if ((s32) arg5 < 0) {
        var_r25 = wazaDB_GetZokuseiDataId(arg3);
    } else {
        var_r25 = (u8) arg5;
    }
    if (wazaCheckDarkWaza(arg3) == 1) {
        sp18 = waza_GetZokuseiKindData(arg3);
    } else {
        sp18 = zokuseiBiosGetWazaKind((u32) var_r25);
    }
    sp1C = wazaDB_GetRangeId(arg3);
    temp_r26 = fightWaza_GetCritical(fightOutPokemon_GetFightWazaPtr(arg0));
    temp_r27 = fightOutPokemonGetTokuseiDataId(arg0);
    temp_r28 = fightOutPokemonGetSoubiItemSoubiDataId(arg0);
    sp20 = figthOutPokemonGetSoubiItemBuff(arg0);
    temp_r29 = figthOutPokemonGetPokemonDataId(arg0);
    temp_r3 = fightOutPokemonGetPokemonPtr(arg0);
    var_r21 = pokemon_GetPhyAtk(temp_r3);
    var_r19 = pokemon_GetSpeAtk(temp_r3);
    spC = (Hero *)fightFloorGetFightOutPokemonPtrToHeroPtr(NULL, arg0);
    sp24 = fightOutPokemon_GetAbicntPhyAtk(arg0);
    sp28 = fightOutPokemon_GetAbicntSpeAtk(arg0);
    sp2C = figthOutPokemonGetLevel(arg0);
    sp30 = fightOutPokemonGetTokuseiDataId(arg1);
    temp_r30 = fightOutPokemonGetSoubiItemSoubiDataId(arg1);
    figthOutPokemonGetSoubiItemBuff(arg1);
    temp_r14 = figthOutPokemonGetPokemonDataId(arg1);
    temp_r3_2 = fightOutPokemonGetPokemonPtr(arg1);
    var_r20 = pokemon_GetPhyDef(temp_r3_2);
    var_r18 = pokemon_GetSpeDef(temp_r3_2);
    temp_r24 = (Hero *)fightFloorGetFightOutPokemonPtrToHeroPtr(NULL, arg1);
    sp34 = fightOutPokemon_GetAbicntPhyDef(arg1);
    sp38 = fightOutPokemon_GetAbicntSpeDef(arg1);
    temp_r31 = fightFloorGetValidFightOutPokemonCount(NULL, 1U, arg1, 0U);
    if ((temp_r27 == 0x25) || (temp_r27 == 0x4A)) {
        var_r21 = (var_r21 * 2) & 0xFFFE;
    }
    if ((temp_r23 == 1) && ((u8) (heroGetStatus(spC, 0xFU, 0U) != 0) == 1)) {
        var_r21 = (u32) (u16) ((s32) ((u16) var_r21 * 0x6E) / 100);
    }
    if ((temp_r23 == 1) && ((u8) (heroGetStatus(temp_r24, 0x13U, 0U) != 0) == 1)) {
        var_r20 = (u32) (u16) ((s32) ((u16) var_r20 * 0x6E) / 100);
    }
    if ((temp_r23 == 1) && ((u8) (heroGetStatus(spC, 0x15U, 0U) != 0) == 1)) {
        var_r19 = (u32) (u16) ((s32) ((u16) var_r19 * 0x6E) / 100);
    }
    if ((temp_r23 == 1) && ((u8) (heroGetStatus(temp_r24, 0x15U, 0U) != 0) == 1)) {
        var_r18 = (u32) (u16) ((s32) ((u16) var_r18 * 0x6E) / 100);
    }
    var_r5 = 0;
    var_ctr = 0x11;
    do {
        temp_r6 = (const SeqItemTypePower *)((const u8 *)SoubiItemWazaTypePowUpTbl + var_r5);
        if (((s32) (u16) temp_r28 == (s32) temp_r6->item) && ((s32) (u16) var_r25 == (s32) temp_r6->type)) {
            switch ((s32) (u8) sp18) {              /* switch 1; irregular */
            case 1:                                 /* switch 1 */
                var_r21 = (u32) (u16) ((s32) ((u16) var_r21 * (sp20 + 0x64)) / 100);
                break;
            case 2:                                 /* switch 1 */
                var_r19 = (u32) (u16) ((s32) ((u16) var_r19 * (sp20 + 0x64)) / 100);
                break;
            }
        }
        var_r5 += 2;
        var_ctr -= 1;
    } while (var_ctr != 0);
    if ((u16) temp_r28 == 0x1D) {
        var_r21 = (u32) (u16) ((s32) ((u16) var_r21 * 0x96) / 100);
    }
    if (((u8) sp14 == 1) && ((u16) temp_r28 == 0x22) && ((temp_r29 == 0x198) || (temp_r29 == 0x197))) {
        var_r19 = (u32) (u16) ((s32) ((u16) var_r19 * 0x96) / 100);
    }
    if (((u8) sp14 == 1) && ((u16) temp_r30 == 0x22) && ((temp_r14 == 0x198) || (temp_r14 == 0x197))) {
        var_r18 = (u32) (u16) ((s32) ((u16) var_r18 * 0x96) / 100);
    }
    if (((u16) temp_r28 == 0x23) && (temp_r29 == 0x175)) {
        var_r19 = (var_r19 * 2) & 0xFFFE;
    }
    if (((u16) temp_r30 == 0x24) && (temp_r14 == 0x175)) {
        var_r18 = (var_r18 * 2) & 0xFFFE;
    }
    if (((u16) temp_r28 == 0x2D) && (temp_r29 == 0x19)) {
        var_r19 = (var_r19 * 2) & 0xFFFE;
    }
    if (((u16) temp_r30 == 0x40) && (temp_r14 == 0x84)) {
        var_r20 = (var_r20 * 2) & 0xFFFE;
    }
    if (((u16) temp_r28 == 0x41) && ((temp_r29 == 0x68) || (temp_r29 == 0x69))) {
        var_r21 = (var_r21 * 2) & 0xFFFE;
    }
    if (((u16) sp30 == 0x2F) && (((u16) var_r25 == 0xA) || ((u16) var_r25 == 0xF))) {
        var_r19 = (u32) (u16) ((s32) (u16) var_r19 / 2);
    }
    if (temp_r27 == 0x37) {
        var_r21 = (u32) (u16) ((s32) ((u16) var_r21 * 0x96) / 100);
    }
    if ((temp_r27 == 0x39) && (fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x3AU, 0U, NULL) != 0)) {
        var_r19 = (u32) (u16) ((s32) ((u16) var_r19 * 0x96) / 100);
    }
    if ((temp_r27 == 0x3A) && (fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x39U, 0U, NULL) != 0)) {
        var_r19 = (u32) (u16) ((s32) ((u16) var_r19 * 0x96) / 100);
    }
    if ((temp_r27 == 0x3E) && (fightOutPokemonIsJoutaiNormal(arg0) == 0)) {
        var_r21 = (u32) (u16) ((s32) ((u16) var_r21 * 0x96) / 100);
    }
    if (((u16) sp30 == 0x3F) && (fightOutPokemonIsJoutaiNormal(arg1) == 0)) {
        var_r20 = (u32) (u16) ((s32) ((u16) var_r20 * 0x96) / 100);
    }
    if (((u16) var_r25 == 0xD) && (fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(NULL, 0x38) != 0)) {
        var_r22 = (u16) ((s32) var_r22 / 2);
    }
    if (((u16) var_r25 == 0xA) && (fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(NULL, 0x39) != 0)) {
        var_r22 = (u16) ((s32) var_r22 / 2);
    }
    if (((u16) var_r25 == 0xC) && (temp_r27 == 0x41) && (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) != 0)) {
        var_r22 = (u16) ((s32) (var_r22 * 0x96) / 100);
    }
    if (((u16) var_r25 == 0xA) && (temp_r27 == 0x42) && (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) != 0)) {
        var_r22 = (u16) ((s32) (var_r22 * 0x96) / 100);
    }
    if (((u16) var_r25 == 0xB) && (temp_r27 == 0x43) && (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) != 0)) {
        var_r22 = (u16) ((s32) (var_r22 * 0x96) / 100);
    }
    if (((u16) var_r25 == 6) && (temp_r27 == 0x44) && (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) != 0)) {
        var_r22 = (u16) ((s32) (var_r22 * 0x96) / 100);
    }
    if (wazaDB_GetSeqId(arg3) == 7) {
        var_r20 = (var_r20 >> 1U) & 0x7FFF;
    }
    switch ((s32) (u8) sp18) {                      /* switch 2; irregular */
    case 1:                                         /* switch 2 */
        if (temp_r26 == 2) {
            if ((u8) sp24 > 6U) {
                var_r14_2 = fightAbicntDoKakeWaru((u8) sp24, (u32) (u16) var_r21);
            } else {
                var_r14_2 = (u32) (u16) var_r21;
            }
        } else {
            var_r14_2 = fightAbicntDoKakeWaru((u8) sp24, (u32) (u16) var_r21);
        }
        if (temp_r26 == 2) {
            if ((u8) sp34 < 6U) {
                var_r3 = fightAbicntDoKakeWaru((u8) sp34, (u32) (u16) var_r20);
            } else {
                var_r3 = (u32) (u16) var_r20;
            }
        } else {
            var_r3 = fightAbicntDoKakeWaru((u8) sp34, (u32) (u16) var_r20);
        }
        temp_r14_2 = (s32) (var_r14_2 * var_r22 * (((s32) ((sp2C * 2) & 0x1FE) / 5) + 2)) / (s32) var_r3;
        var_r14 = temp_r14_2 / 50;
        if ((fightOutPokemonIsJoutaiDataId(arg0, 6U) == 1) && (temp_r27 != 0x3E)) {
            var_r14 = (temp_r14_2 / 50) / 2;
        }
        if ((fightSideIsJoutaiDataId(sp8, 0x48U) == 1) && (temp_r26 == 1)) {
            if ((fightFloor_GetFightSideFightOutPokemonSideMax(NULL) >= 2U) && (temp_r31 >= 2U)) {
                var_r14 = (var_r14 / 3) * 2;
            } else {
                var_r14 = var_r14 / 2;
            }
        }
        if ((fightFloor_GetFightSideFightOutPokemonSideMax(NULL) >= 2U) && ((u8) sp1C == 4) && (temp_r31 >= 2U)) {
            var_r14 = var_r14 / 2;
        }
        if (var_r14 == 0) {
            var_r14 = 1;
        }
        break;
    case 2:                                         /* switch 2 */
        if (temp_r26 == 2) {
            if ((u8) sp28 > 6U) {
                var_r14_3 = fightAbicntDoKakeWaru((u8) sp28, (u32) (u16) var_r19);
            } else {
                var_r14_3 = (u32) (u16) var_r19;
            }
        } else {
            var_r14_3 = fightAbicntDoKakeWaru((u8) sp28, (u32) (u16) var_r19);
        }
        if (temp_r26 == 2) {
            if ((u8) sp38 < 6U) {
                var_r3_2 = fightAbicntDoKakeWaru((u8) sp38, (u32) (u16) var_r18);
            } else {
                var_r3_2 = (u32) (u16) var_r18;
            }
        } else {
            var_r3_2 = fightAbicntDoKakeWaru((u8) sp38, (u32) (u16) var_r18);
        }
        temp_r14_3 = (s32) (var_r14_3 * var_r22 * (((s32) ((sp2C * 2) & 0x1FE) / 5) + 2)) / (s32) var_r3_2;
        var_r14 = temp_r14_3 / 50;
        if ((fightSideIsJoutaiDataId(sp8, 0x49U) == 1) && (temp_r26 == 1)) {
            if ((fightFloor_GetFightSideFightOutPokemonSideMax(NULL) >= 2U) && (temp_r31 >= 2U)) {
                var_r14 = (var_r14 / 3) * 2;
            } else {
                var_r14 = (temp_r14_3 / 50) / 2;
            }
        }
        if ((fightFloor_GetFightSideFightOutPokemonSideMax(NULL) >= 2U) && ((u8) sp1C == 4) && (temp_r31 >= 2U)) {
            var_r14 = var_r14 / 2;
        }
        if ((u8) sp10 == 2) {
            switch ((s32) (u16) var_r25) {          /* switch 3; irregular */
            case 10:                                /* switch 3 */
                var_r14 = var_r14 / 2;
                break;
            case 11:                                /* switch 3 */
                var_r14 = (s32) (var_r14 * 0xF) / 10;
                break;
            }
        }
        if ((tenkouDataBiosGetSolarFlag((u8) sp10) == 0) && (arg3 == 0x4C)) {
            var_r14 = var_r14 / 2;
        }
        if ((u8) sp10 == 1) {
            switch ((s32) (u16) var_r25) {          /* switch 4; irregular */
            case 10:                                /* switch 4 */
                var_r14 = (s32) (var_r14 * 0xF) / 10;
                break;
            case 11:                                /* switch 4 */
                var_r14 = var_r14 / 2;
                break;
            }
        }
        if ((fightOutPokemonIsJoutaiDataId(arg0, 0x3AU) == 1) && ((u16) var_r25 == 0xA)) {
            var_r14 = (s32) (var_r14 * 0xF) / 10;
        }
        break;
    default:                                        /* switch 2 */
        var_r14 = 0;
        break;
    }
    if (((u8) sp10 == 5) && (wazaCheckDarkWaza(arg3) == 1)) {
        var_r14 = (s32) (var_r14 * 0xF) / 10;
    }
    return var_r14 + 2;
}

void fightSeqIrekaeInit(FightOutPokemon *arg0, FightOutPokemon *arg1, u8 arg2) {
    u16 conditions[11] = {15,22,9,24,20,28,29,30,37,56,57};
    SeqReplacementWork work;
    void *temp_r7;
    void *temp_r4;
    void *temp_r4_2;
    u16 temp_r28;
    u8 var_r27;
    u16 var_r26;

    var_r26 = 0;
    if (arg2 == 1) {
        var_r26 = 0x7F;
    }
    if (var_r26 == 0x7F) {
        fightOutPokemonCopyAllAbiCnt(arg0, arg1);
        for (var_r27 = 0; var_r27 < 0xBU; var_r27 += 1) {
            temp_r28 = conditions[var_r27];
            if (fightOutPokemonIsJoutaiDataId(arg1, temp_r28) == 1) {
                fightOutPokemonCopyJoutaiDataId(arg0, arg1, temp_r28);
            }
        }
    }
    work.pokemon = arg0;
    work.keepConditions = var_r26;
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqIrekaeInitSub__FPvUsPv, &work, 0U);
    if (fightOutPokemonIsJoutaiDataId(arg1, 0x34U) == 1) {
        fightOutPokemonCopyJoutaiDataId(arg0, arg1, 0x34U);
    }
    if (fightOutPokemonIsJoutaiDataId(arg1, 0x35U) == 1) {
        fightOutPokemonCopyJoutaiDataId(arg0, arg1, 0x35U);
    }
}

s32 _fightSeqIrekaeInitSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r30;
    u16 temp_r29;

    temp_r30 = ((SeqReplacementWork *)arg2)->pokemon;
    temp_r29 = (u16) ((SeqReplacementWork *)arg2)->keepConditions;
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    if (arg0 == temp_r30) {
        return 1;
    }
    if (temp_r29 == 0x7F) {
        if ((fightOutPokemonIsAlly(temp_r30, arg0) == 0) && (_fightSeqCheckFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, temp_r30, 0x1DU, arg1) == 1)) {
            fightOutPokemonSetNowKaisuuJoutaiDataId(arg0, 0x1DU, 0U);
        }
    } else {
        _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, temp_r30, 0x16U, arg1);
        _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, temp_r30, 0x1DU, arg1);
    }
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, temp_r30, 0xAU, arg1);
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, temp_r30, 0xEU, arg1);
    if (fightOutPokemonIsAlly(arg0, temp_r30) == 0) {
        fightOutPokemonSetOumuWazaDataId(arg0, temp_r30, 0U);
        fightOutPokemonInitFightPokemonEnemyAry(arg0, (u8 *) temp_r30);
    }
    temp_r3 = fightTargetGetPtr(0xEU, temp_r30);
    if (temp_r3 != NULL) {
        fightOutPokemon_SetOumuWazaAllyDataId(temp_r3, 0U);
    }
    fightOutPokemon_SetComboFuncId(temp_r30, 0U);
    fightAi_FixedActIrekaeInit((u8 *) temp_r30);
    return 1;
}

void fightSeqKizetuInit(FightOutPokemon *arg0) {
    fightFloorLoopValidFightOutPokemon(NULL, _fightSeqKizetuInitSub__FPvUsPv, arg0, 0U);
    pokemonInitJoutai(fightOutPokemonGetPokemonPtr(arg0));
    fightOutPokemonResetSeqStatus(arg0, 0U);
    fightOutPokemonInitJoutaiDataId(arg0, 0x17U);
    fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x7CU);
    if (fightOutPokemonIsJoutaiDataId(arg0, 0x3EU) == 1) {
        fightOutPokemonInitJoutaiDataId(arg0, 0x3EU);
        fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0xC8U);
    }
    fightOutPokemon_SetComboFuncId(arg0, 0U);
    fightAi_FixedActIrekaeInit((u8 *) arg0);
}

s32 _fightSeqKizetuInitSub__FPvUsPv(void *rawPokemon, u16 arg1, void *arg2) {
    FightOutPokemon *arg0 = (FightOutPokemon *)rawPokemon;
    FightOutPokemon *temp_r3;

    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    if (arg0 == arg2) {
        return 1;
    }
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, (FightOutPokemon *) arg2, 0x16U, arg1);
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, (FightOutPokemon *) arg2, 0xAU, arg1);
    _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, (FightOutPokemon *) arg2, 0xEU, arg1);
    if (fightOutPokemonIsAlly(arg0, (FightOutPokemon *) arg2) == 0) {
        fightOutPokemonSetOumuWazaDataId(arg0, (FightOutPokemon *) arg2, 0U);
        fightOutPokemonInitFightPokemonEnemyAry(arg0, (u8 *) arg2);
    }
    temp_r3 = fightTargetGetPtr(0xEU, (FightOutPokemon *) arg2);
    if (temp_r3 != NULL) {
        fightOutPokemon_SetOumuWazaAllyDataId(temp_r3, 0U);
    }
    return 1;
}

u8 _fightSeqInitFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2, u16 arg3) {
    u8 temp_r3;

    temp_r3 = _fightSeqCheckFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(arg0, arg1, arg2, arg3);
    if (temp_r3 == 1) {
        fightOutPokemonInitJoutaiDataId(arg0, arg2);
    }
    return temp_r3;
}

u8 _fightSeqCheckFightOutPokemonJoutaiUserFightTargetId__FP15FightOutPokemonP15FightOutPokemonUsUs(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2, u16 arg3) {
    u32 temp_r3;
    FightOutPokemon *temp_r3_2;

    if (fightOutPokemonIsJoutaiDataId(arg0, arg2) == 1) {
        temp_r3 = fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg0, arg2);
        if ((u16)temp_r3 != 0) {
            temp_r3_2 = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr((u32) temp_r3, arg3);
            if ((temp_r3_2 != NULL) && (temp_r3_2 == arg1)) {
                return 1U;
            }
        }
    }
    return 0U;
}

void fightSeqCheckSetHensinBuffToMotoFightPokemon(FightOutPokemon *arg0, u16 arg1) {
    if (fightOutPokemonIsUseHensinBuff(arg0) == 1) {
        fightOutPokemonSetHensinFightPokemonStatusId(arg0, arg1, 0U);
    }
}

void fightSeqCheckSetHensinBuffToMotoPokemon2(FightOutPokemon *arg0, u16 arg1, s8 arg2, s32 arg3) {
    if (fightOutPokemonIsUseHensinBuff(arg0) == 1) {
        fightOutPokemonSetHensinPokemonStatusId(arg0, arg1, arg2, arg3);
    }
}

void fightSeqCheckSetMotoPokemonToHensinBuff(FightOutPokemon *arg0, u16 arg1) {
    if (fightOutPokemonIsUseHensinBuff(arg0) == 1) {
        fightOutPokemonSetHensinPokemonStatusId(arg0, arg1, 0, 1);
    }
}

void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon *arg0, u16 arg1) {
    if (fightOutPokemonIsUseHensinBuff(arg0) == 1) {
        fightOutPokemonSetHensinPokemonStatusId(arg0, arg1, 0, 0);
    }
}
}
