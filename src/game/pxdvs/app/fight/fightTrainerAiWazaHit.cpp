#include <dolphin/types.h>

extern "C" {
typedef struct FIGHT_TRAINER FIGHT_TRAINER; typedef struct FightOutPokemon FightOutPokemon; typedef struct FightPokemon FightPokemon; typedef struct Pokemon Pokemon; typedef struct FightWaza FightWaza; typedef struct FightSide FightSide;
u8 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER *, void *, u8);
FightSide * fightTargetGetPtrAsNowFightType(u8, FightOutPokemon *);
u8 fightSideIsJoutaiDataId(FightSide *, u16);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon *);
s16 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon *, u16);
u16 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon *, u16);
u16 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER *, u16);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16, u16);
u8 fightTrainerAiWazaDoWazaHitFunc(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
Pokemon * fightOutPokemonGetPokemonPtr(FightOutPokemon *);
u8 fightSeqIsDoItemGetWaza(u16);
u8 fightFloor_GetTikeiDataId(void *);
u16 tikeiDataBiosGetWazaId(u8);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER *, u16, FightOutPokemon *);
u8 itemDataCheckValid(u16);
u32 fightFloor_GetFightType(void *);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void *, FIGHT_TRAINER *, FightOutPokemon **, u8, u8);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonUsedItemDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSoubiItemDataId(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(void *, FIGHT_TRAINER *, FightPokemon **, u8, u8);
u8 fightTrainerAiIsFightPokemonJoutaiNormal(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
s16 fightSideGetCountAsJoutaiDataId(FightSide *, u16);
u16 fightTrainerAiCheckOumu(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon *, u8);
FIGHT_TRAINER *fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void *, FightOutPokemon *);
FightPokemon *fightTrainerSearchIrekaeFightPokemon(FIGHT_TRAINER *, u16 *);
Pokemon *fightOutPokemonGetPokemonPtr(FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER *, FightOutPokemon *, u16 *, s16 *, u8);
u16 tikeiDataBiosGetZokuseiDataId(u8);
u16 fightFloorGetFightOutPokemonPtrAry(void *, u8, u8, u8, FightOutPokemon **);
void fightFloorSortFightOutPokemonPtrArySub(void *, FightOutPokemon **, u16, u8);
u16 fightFloor_GetFightSideFightOutPokemonSideMax(void *);
u8 fightOutPokemonCheckFightOut(FightOutPokemon *);
u8 fightOutPokemonGetSex(FightOutPokemon *);
s8 fightSeqCondChgActParaIdToValue(u16);
s32 fightSeqGetTemotiPokemonNekonoteWazaDataAry(FIGHT_TRAINER *, u16 *, u16, FightOutPokemon *);
u8 fightSeqIsAllwaysHit(u16);
u8 fightSeqIsEncoreNgWazaDataId(u16);
u8 fightSeqIsSketchNgWazaDataId(u16);
u8 fightSeqIsTenkouHit(u16);
u8 fightSeqMonomaneNGCheck(u16);
u8 fightSeqRegulationCheck(u16, FightOutPokemon *, FightOutPokemon *);
u8 fightSeqRegulationOverTwoCheck(u16, FightOutPokemon *);
u8 fightSeqRegulationZenmetuCheck(u16);
u8 fightSeqRendouWazaCheck(u16);
u8 fightSeqTameWazaCheck(u16);
u8 fightSideCheckWriteJoutaiDataId(FightSide *, u16);
u8 fightTrainerAiCheckAbiCnt(FIGHT_TRAINER *, FightOutPokemon *, FightOutPokemon *, u16, u16, u16, u16);
u8 fightTrainerAiCheckGuard(FIGHT_TRAINER *, FightOutPokemon *, u16);
u16 fightTrainerAiCheckHorobinouta(FIGHT_TRAINER *);
u8 fightTrainerAiCheckSawagu(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiCheckSimerike(FIGHT_TRAINER *);
u8 fightTrainerAiCheckTextureZokusei(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonLevel(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSketchWazaDataId(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonWazaNowPp(FIGHT_TRAINER *, FightOutPokemon *, u8);
u8 fightTrainerAiIsFightOutPokemonJoutaiKaragenki(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiKie(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonNokoriHp(FIGHT_TRAINER *, FightOutPokemon *, s32, f32);
u16 fightTrainerGetIrekaeFightPokemonAry(FIGHT_TRAINER *, FightPokemon **);
u8 joutaiDataBiosGetMaxCount(u16);
void pokemonGetMezamerupower(Pokemon *, u16 *, u16 *);
u16 wazaDB_GetSeqId(u16);
s32 fightTrainerAiWazaHit217(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit216(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit215(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit214(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit213(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit212(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit211(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit210(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit209(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit208(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit207(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit206(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit205(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit204(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit203(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit202(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit201(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit200(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit199(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit198(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit197(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit196(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit195(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit194(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit193(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit192(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit191(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit190(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit189(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit188(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit187(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit186(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit185(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit184(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit183(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit182(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit181(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit180(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit179(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit178(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit177(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit176(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit175(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit174(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit173(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit172(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit171(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit170(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit169(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit168(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit167(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit166(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit165(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit164(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit162(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit161(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit160(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit159(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit158(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit157(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit156(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit155(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit154(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit153(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit152(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit151(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit150(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit149(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit148(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit147(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit146(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit145(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit144(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit143(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit142(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit140(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit139(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit138(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit137(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit136(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit135(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit134(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit133(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit132(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
static s32 _fightTrainerAiWazaHitWeatherKaifuku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit130(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit129(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit128(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit127(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit126(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
static s32 _fightTrainerAiWazaHitJisin(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit125(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit124(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit123(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit122(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit121(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit120(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit119(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit118(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit117(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit116(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit115(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit114(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit113(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit112(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit111(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit109(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit108(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit107(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit106(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit105(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit104(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit103(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit102(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit101(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit100(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit099(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit098(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit097(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit095(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit094(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit093(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit092(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit091(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit090(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit089(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit088(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit087(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit086(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit085(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit084(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit083(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit082(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit081(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit080(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit079(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit078(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit077(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit076(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit075(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit073(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit072(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit071(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit070(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit069(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit068(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit067(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit066(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit065(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit062(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit060(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit059(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit058(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit057(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit054(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit053(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit052(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit051(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit050(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit049(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit048(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit047(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit046(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit045(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit044(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit043(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit042(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit041(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit040(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit039(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit038(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit037(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit036(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit035(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit034(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit033(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit032(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit031(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit030(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit029(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit028(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit027(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit026(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit025(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit024(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit023(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit020(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit019(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit018(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit017(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit016(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit013(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit011(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit010(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
static s32 _fightTrainerAiWazaHitAbicnt(FIGHT_TRAINER *, FightOutPokemon *, FightOutPokemon *, u16, u16, u16, u16);
s32 fightTrainerAiWazaHit009(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit008(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit007(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit006(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit005(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit004(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit003(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit002(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit001(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHit000(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaHitNull(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
static u8 _fightTrainerAiWazaHitCheckTokusei(FIGHT_TRAINER *, FightOutPokemon *, u16);
static s32 _fightTrainerAiWazaHitCheck(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *, u32);


s32 fightTrainerAiWazaHit217(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit216(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r3;

    temp_r3 = fightTargetGetPtrAsNowFightType(2U, arg3);
    if ((fightSideIsJoutaiDataId(temp_r3, 0x48U) == 0) && (fightSideIsJoutaiDataId(temp_r3, 0x49U) == 0) && (fightSideIsJoutaiDataId(temp_r3, 0x4BU) == 0)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit215(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U) == 5) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit214(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x90U, 7U, 1U);
}

s32 fightTrainerAiWazaHit213(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg1, (u8) tikeiDataBiosGetZokuseiDataId(fightFloor_GetTikeiDataId(0))) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit212(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 temp_r31;
    u8 temp_r3;

    temp_r31 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg1);
    if ((temp_r31 >= 0xCU) && (temp_r3 >= 0xCU)) {
        return 0;
    }
    if ((fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 1U, 0x41U) == 0) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 3U, 0x41U) == 0)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit211(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 temp_r31;
    u8 temp_r3;

    temp_r31 = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(arg0, arg1);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg1);
    if ((temp_r31 >= 0xCU) && (temp_r3 >= 0xCU)) {
        return 0;
    }
    if ((fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 4U, 0x41U) == 0) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 5U, 0x41U) == 0)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit210(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x39U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit209(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit002(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit208(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 temp_r31;
    u8 temp_r3;

    temp_r31 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg1);
    if ((temp_r31 >= 0xCU) && (temp_r3 >= 0xCU)) {
        return 0;
    }
    if ((fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 1U, 0x41U) == 0) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 2U, 0x41U) == 0)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit207(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit206(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 temp_r31;
    u8 temp_r3;

    temp_r31 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg1);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg1);
    if ((temp_r31 >= 0xCU) && (temp_r3 >= 0xCU)) {
        return 0;
    }
    if ((fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 2U, 0x41U) == 0) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 5U, 0x41U) == 0)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit205(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 temp_r31;
    u8 temp_r3;

    temp_r31 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg3);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg3);
    if ((temp_r31 == 0) && (temp_r3 == 0)) {
        return 0;
    }
    if ((fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x90U, 1U, 1U) == 0) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x90U, 2U, 1U) == 0)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit204(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit203(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 var_r30;
    u8 temp_r3;

    temp_r3 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    switch (temp_r3) {                              /* irregular */
    case 2:
        var_r30 = 0xB;
        break;
    case 3:
        var_r30 = 5;
        break;
    case 1:
        var_r30 = 0xA;
        break;
    case 4:
        var_r30 = 0xF;
        break;
    default:
        var_r30 = 0;
        break;
    }
    var_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, var_r30, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        var_r31 = 0;
    }
    if (var_r31 == 0) {
        return 0;
    }
    if (var_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit202(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit201(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x38U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit200(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit004(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit199(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r30;
    s32 temp_r31;

    temp_r30 = fightTargetGetPtrAsNowFightType(2U, arg3);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 9U) == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightSideIsJoutaiDataId(temp_r30, 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit198(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit197(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit196(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit195(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit194(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x28U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit193(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiKaragenki(arg0, arg1) != 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit192(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];

    fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp8, 0, 0U);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 0U, 1U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x27U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit191(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0xFFFFU);
    if (fightSeqRegulationCheck(arg2, arg1, arg3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x19U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x19U) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit190(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit189(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r30;
    u16 temp_r31;

    temp_r30 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    temp_r31 = fightTrainerAiGetFightOutPokemonNowHp(arg0, arg1);
    if (fightTrainerAiGetFightOutPokemonNowHp(arg0, arg3) <= temp_r31) {
        return 0;
    }
    var_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r30, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        var_r31 = 0;
    }
    if (var_r31 == 0) {
        return 0;
    }
    if (var_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit188(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit187(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x48U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0xFU) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg3), 0x4BU) == 1) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiCheckSawagu(arg0, arg3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x26U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) {
        return 0;
    }
    if (fightSeqRegulationOverTwoCheck(8U, arg3) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit186(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit185(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit184(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiGetFightOutPokemonUsedItemDataId(arg0, arg1) == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit183(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit182(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit181(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x25U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit180(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8[24];

    return fightSeqGetTemotiPokemonNekonoteWazaDataAry(arg0, sp8, 0x18U, arg1) > 0;
}

s32 fightTrainerAiWazaHit179(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x35U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit178(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0xFFFFU);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x19U) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit177(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 temp_r30;
    u16 temp_r31;

    temp_r31 = fightTrainerAiGetFightOutPokemonSoubiItemDataId(arg0, arg1);
    temp_r30 = fightTrainerAiGetFightOutPokemonSoubiItemDataId(arg0, arg3);
    if (fightSeqIsDoItemGetWaza((u16) arg1) == 0) {
        return 0;
    }
    if (((temp_r31 == 0) && (temp_r30 == 0)) || (temp_r31 == 0xAF) || (temp_r30 == 0xAF) || ((temp_r31 != 0) && (itemDataCheckValid(temp_r31) == 0)) || ((temp_r30 != 0) && (itemDataCheckValid(temp_r30) == 0))) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x3CU) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit176(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r3;

    temp_r3 = fightTargetGetPtrAsNowFightType(0xEU, arg1);
    if (temp_r3 == 0) {
        return 0;
    }
    if ((fightFloor_GetFightSideFightOutPokemonSideMax(0) < 2U) || (fightOutPokemonCheckFightOut((FightOutPokemon *) temp_r3) != 1) || (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x32U) != 0) || (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, (FightOutPokemon *) temp_r3, 0x32U) != 0)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit175(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x30U) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit174(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit173(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 temp_r30;
    u16 temp_r31;

    temp_r30 = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    temp_r31 = wazaDB_GetSeqId(arg2);
    if (wazaDB_GetSeqId(temp_r30) != temp_r31) {
        return fightTrainerAiWazaDoWazaHitFunc(arg0, arg1, temp_r30, arg3);
    }
    return 1;
}

s32 fightTrainerAiWazaHit172(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit171(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit170(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit169(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit168(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 temp_r30;
    u8 temp_r31;

    temp_r30 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg3);
    temp_r31 = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(arg0, arg3);
    if (fightTrainerAiCheckGuard(arg0, arg3, arg2) == 1) {
        return 0;
    }
    if ((temp_r30 == 0) && (temp_r31 == 0)) {
        return 0;
    }
    if ((fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0xA0U, 1U, 1U) == 0) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0xA0U, 4U, 1U) == 0)) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit167(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 6U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 0xAU) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x29U) == 1) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 6U) == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg3), 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit166(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r29;
    s32 temp_r31;
    u8 temp_r30;

    temp_r29 = fightTargetGetPtrAsNowFightType(2U, arg3);
    temp_r30 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg3);
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) && (temp_r30 >= 0xCU) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 4U, 1U) == 0)) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 9U) == 0) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r29, 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit165(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit164(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U) == 4) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit162(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x2DU) == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0, 1.0f) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit161(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r30;

    temp_r30 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    var_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x2DU) == 0) {
        var_r31 = 0;
    }
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r30, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        var_r31 = 0;
    }
    if (var_r31 == 0) {
        return 0;
    }
    if (var_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit160(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s16 var_r31;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x2DU) == 0) {
        var_r31 = 0;
    } else {
        var_r31 = fightOutPokemonGetCountAsJoutaiDataId(arg1, 0x2DU);
    }
    if (var_r31 >= (s32) joutaiDataBiosGetMaxCount(0x2DU)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit159(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit158(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightOutPokemon_GetFightoutTurnCount(arg1) == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 7U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit157(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0, 1.0f) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit156(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 2U, 0x41U) == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit155(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit154(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 hit;
    hit = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (hit == 0) {
        return 0;
    }
    if (hit == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit153(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 0;
}

s32 fightTrainerAiWazaHit152(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit151(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit039(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit150(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit146(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit149(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit148(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x34U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit147(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitJisin(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit146(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit145(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit039(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit144(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit143(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit142(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if ((fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1) >= 0xCU) || (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, -1, 0.5f) != 0)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit140(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit139(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit138(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit137(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit136(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U) == 2) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit135(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 spA;
    u16 sp8;
    s32 var_r31;

    pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(arg1), &spA, &sp8);
    var_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, sp8, (u16) (s16) spA) == 0x43) {
        var_r31 = 0;
    }
    if (var_r31 == 0) {
        return 0;
    }
    if (var_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit134(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitWeatherKaifuku(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit133(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitWeatherKaifuku(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit132(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitWeatherKaifuku(arg0, arg1, arg2, arg3);
}

s32 _fightTrainerAiWazaHitWeatherKaifuku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0, 1.0f) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit130(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit129(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit128(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 temp_r31;

    temp_r31 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r31, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit127(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8;

    sp8 = 0;
    if (fightTrainerSearchIrekaeFightPokemon(arg0, &sp8) == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit126(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitJisin(arg0, arg1, arg2, arg3);
}

s32 _fightTrainerAiWazaHitJisin(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit125(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit124(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightSideCheckWriteJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg1), 0x4BU) != 2) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit123(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit121(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit122(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit121(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit120(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r29;
    u8 temp_r30;
    u8 temp_r31;

    temp_r30 = fightOutPokemonGetSex(arg1);
    temp_r31 = fightOutPokemonGetSex(arg3);
    var_r29 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0xCU) == 1) {
        var_r29 = 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 0xAU) == 0) {
        return 0;
    }
    if ((temp_r30 == temp_r31) || (fightTrainerAiIsFightOutPokemonJoutaiKie(arg0, arg3) == 1) || (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0xAU) == 1) || (temp_r30 == 2) || (temp_r31 == 2)) {
        var_r29 = 0;
    }
    if (var_r29 == 0) {
        return 0;
    }
    if (var_r29 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit119(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit118(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r29;
    s32 temp_r31;
    u8 temp_r30;

    temp_r29 = fightTargetGetPtrAsNowFightType(2U, arg3);
    temp_r30 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg3);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) && (temp_r30 >= 0xCU) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x20U, 1U, 1U) == 0)) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 9U) == 0) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r29, 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit117(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit116(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit111(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit115(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U) == 3) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit114(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightSeqRegulationCheck(arg2, arg1, arg3) == 1) {
        return 0;
    }
    if (fightTrainerAiCheckHorobinouta(arg0) == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit113(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 hit;
    hit = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (hit == 0) {
        return 0;
    }
    if (hit == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit112(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r3;
    s16 var_r30;

    temp_r3 = fightTargetGetPtrAsNowFightType(3U, arg1);
    var_r30 = 0;
    if (fightSideIsJoutaiDataId(temp_r3, 0x4AU) == 1) {
        var_r30 = fightSideGetCountAsJoutaiDataId(temp_r3, 0x4AU);
    }
    if (var_r30 >= (s32) joutaiDataBiosGetMaxCount(0x4AU)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit111(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit109(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 temp_r29;
    u8 temp_r30;
    u8 temp_r31;

    temp_r29 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg3);
    temp_r30 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg3);
    temp_r31 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg3);
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg1, 7U) == 1) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
            return 0;
        }
        if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x18U) == 1) || (fightTrainerAiIsFightOutPokemonJoutaiKie(arg0, arg3) == 1)) {
            return 0;
        }
        goto block_14;
    }
    if ((temp_r31 == 0) && (temp_r29 >= 0xCU) && (temp_r30 >= 0xCU)) {
        return 0;
    }
    if ((fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x90U, 3U, 0x41U) == 0) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 1U, 0x41U) == 0) && (fightTrainerAiCheckAbiCnt(arg0, arg1, arg3, arg2, 0x10U, 2U, 0x41U) == 0)) {
        return 0;
    }
block_14:
    return 1;
}

s32 fightTrainerAiWazaHit108(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x10U, 7U, 0x41U);
}

s32 fightTrainerAiWazaHit107(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x17U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 8U) == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit106(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0xFFFEU);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x16U) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit105(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit104(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit103(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit102(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp8[24];
    FightPokemon *temp_r4;
    s32 temp_r29;
    u16 temp_r31;
    u16 var_r27;
    u8 var_r26;

    temp_r31 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    var_r26 = 0;
    var_r27 = 0;
loop_7:
    if (var_r27 < temp_r31) {
        temp_r29 = (var_r27 * 4) & 0x3FFFC;
        temp_r4 = *(FightPokemon **)((u8 *)sp8 + temp_r29);
        if ((temp_r4 != 0) && ((arg2 != 0xD7) || (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, temp_r4, 0x2BU) != 1)) && (fightTrainerAiIsFightPokemonJoutaiNormal(arg0, *(FightPokemon **)((u8 *)sp8 + temp_r29)) == 0)) {
            var_r26 = 1;
        } else {
            var_r27 += 1;
            goto loop_7;
        }
    }
    if (var_r26 == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit101(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit100(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp18[8];
    s16 sp8[8];
    s16 temp_r9;
    s32 temp_r27;
    s32 temp_r8;
    u16 temp_r28;
    u16 temp_r3;
    u8 var_r10;
    u8 var_r3;

    temp_r27 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0xFFFFU);
    temp_r28 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg3, sp18, sp8, 0U);
    temp_r3 = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(arg0, arg3);
    if ((temp_r3 == 0) || (temp_r3 == 0x176) || (temp_r3 == 0xFFFFU) || (fightTrainerAiIsFightOutPokemonJoutaiKie(arg0, arg3) == 1)) {
        return 0;
    }
    var_r3 = 0;
    var_r10 = 0;
loop_10:
    if ((s32) var_r10 < (s32) temp_r28) {
        temp_r8 = (var_r10 * 2) & 0x1FE;
        temp_r9 = *(s16 *)((u8 *)sp8 + temp_r8);
        if ((temp_r9 >= 0) && (temp_r3 == (u16) *(u16 *)((u8 *)sp18 + temp_r8))) {
            var_r3 = fightTrainerAiGetFightOutPokemonWazaNowPp(arg0, arg3, (u8) temp_r9);
        } else {
            var_r10 += 1;
            goto loop_10;
        }
    }
    if (var_r3 == 0) {
        return 0;
    }
    if (temp_r27 == 0) {
        return 0;
    }
    if (temp_r27 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit099(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit098(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightSeqRegulationCheck(arg2, arg1, arg3) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit097(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8[8];
    u16 temp_r27;
    u16 temp_r29;
    u16 var_r28;

    temp_r29 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp8, 0, 1U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 8U) == 0) {
        return 0;
    }
    var_r28 = 0;
loop_10:
    if (var_r28 < temp_r29) {
        temp_r27 = *(u16 *)((u8 *)sp8 + ((var_r28 * 2) & 0x1FFFE));
        if ((temp_r27 == 0x176) || (temp_r27 == 0x163) || (fightSeqRendouWazaCheck(temp_r27) != 0) || (temp_r27 == 0x108) || (temp_r27 == 0xFD) || (fightSeqTameWazaCheck(temp_r27) != 0)) {
            var_r28 += 1;
            goto loop_10;
        }
    }
    if (var_r28 >= temp_r29) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit095(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8[8];
    u16 temp_r30;
    u16 temp_r31;
    u16 var_r6;

    temp_r31 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp8, 0, 0U);
    temp_r30 = fightTrainerAiGetFightOutPokemonSketchWazaDataId(arg0, arg3);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x10U) == 1) || (fightSeqIsSketchNgWazaDataId(temp_r30) == 1)) {
        return 0;
    }
    var_r6 = 0;
loop_9:
    if (var_r6 >= temp_r31) {
        return 1;
    }
    if (temp_r30 == (u16) *(u16 *)((u8 *)sp8 + ((var_r6 * 2) & 0x1FFFE))) {
        return 0;
    }
    var_r6 += 1;
    goto loop_9;
}

s32 fightTrainerAiWazaHit094(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0xFFFFU);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit093(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit092(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r30;

    temp_r30 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 8U) == 0) {
        return 0;
    }
    var_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r30, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        var_r31 = 0;
    }
    if (var_r31 == 0) {
        return 0;
    }
    if (var_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit091(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0xFFFFU);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit090(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp18[8];
    s16 sp8[8];
    s16 temp_r9;
    s32 temp_r29;
    s32 temp_r8;
    u16 temp_r27;
    u16 temp_r28;
    u16 var_r10;
    u8 var_r3;

    temp_r28 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg3, sp18, sp8, 0U);
    temp_r27 = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(arg0, arg3);
    temp_r29 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightSeqIsEncoreNgWazaDataId(temp_r27) == 1) {
        return 0;
    }
    var_r3 = 0;
    var_r10 = 0;
loop_7:
    if (var_r10 < temp_r28) {
        temp_r8 = (var_r10 * 2) & 0x1FFFE;
        temp_r9 = *(s16 *)((u8 *)sp8 + temp_r8);
        if ((temp_r9 >= 0) && (temp_r27 == (u16) *(u16 *)((u8 *)sp18 + temp_r8))) {
            var_r3 = fightTrainerAiGetFightOutPokemonWazaNowPp(arg0, arg3, (u8) temp_r9);
        } else {
            var_r10 += 1;
            goto loop_7;
        }
    }
    if (var_r3 == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x2AU) == 1) {
        return 0;
    }
    if (temp_r29 == 0) {
        return 0;
    }
    if (temp_r29 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit089(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit088(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit087(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit086(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp18[8];
    s16 sp8[8];
    s16 temp_r9;
    s32 temp_r29;
    s32 temp_r8;
    u16 temp_r27;
    u16 temp_r28;
    u16 var_r10;
    u8 var_r3;

    temp_r27 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg3, sp18, sp8, 0U);
    temp_r28 = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(arg0, arg3);
    temp_r29 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    var_r3 = 0;
    var_r10 = 0;
loop_5:
    if (var_r10 < temp_r27) {
        temp_r8 = (var_r10 * 2) & 0x1FFFE;
        temp_r9 = *(s16 *)((u8 *)sp8 + temp_r8);
        if ((temp_r9 >= 0) && (temp_r28 == (u16) *(u16 *)((u8 *)sp18 + temp_r8))) {
            var_r3 = fightTrainerAiGetFightOutPokemonWazaNowPp(arg0, arg3, (u8) temp_r9);
        } else {
            var_r10 += 1;
            goto loop_5;
        }
    }
    if (var_r3 == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x29U) == 1) {
        return 0;
    }
    if (temp_r29 == 0) {
        return 0;
    }
    if (temp_r29 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit085(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit084(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1CU) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 0xCU) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit083(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit082(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8[8];
    s32 temp_r31;
    u16 temp_r29;
    u16 temp_r30;
    u16 var_r6;

    temp_r30 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp8, 0, 0U);
    temp_r29 = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(arg0, arg3);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0xFFFFU);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x10U) == 1) || (fightSeqMonomaneNGCheck(temp_r29) != 0) || (temp_r29 == 0) || (temp_r29 == 0xFFFFU) || (temp_r29 == 0x176) || (temp_r29 == 0x163)) {
        return 0;
    }
    var_r6 = 0;
loop_13:
    if (var_r6 >= temp_r30) {
        if (temp_r31 == 0) {
            return 0;
        }
        return 1;
    }
    if (temp_r29 == (u16) *(u16 *)((u8 *)sp8 + ((var_r6 * 2) & 0x1FFFE))) {
        return 0;
    }
    var_r6 += 1;
    goto loop_13;
}

s32 fightTrainerAiWazaHit081(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit080(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit079(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, -1, 0.25f) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit078(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit077(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit029(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit076(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit075(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit039(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit073(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit072(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit071(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit070(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit069(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit068(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit067(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r30;
    s32 temp_r31_2;
    u16 temp_r31;

    temp_r30 = fightTargetGetPtrAsNowFightType(2U, arg3);
    temp_r31 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 7U) == 1) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 5U) == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r31, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 5U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) {
        return 0;
    }
    temp_r31_2 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightSideIsJoutaiDataId(temp_r30, 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31_2 == 0) {
        return 0;
    }
    if (temp_r31_2 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit066(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x11U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 3U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 8U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 4U) == 0) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg3), 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit065(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightSideCheckWriteJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg1), 0x48U) != 2) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit062(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0xA0U, 5U, 1U);
}

s32 fightTrainerAiWazaHit060(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0xA0U, 3U, 1U);
}

s32 fightTrainerAiWazaHit059(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0xA0U, 2U, 1U);
}

s32 fightTrainerAiWazaHit058(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0xA0U, 1U, 1U);
}

s32 fightTrainerAiWazaHit057(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x10U) == 1) || (fightTrainerAiIsFightOutPokemonJoutaiKie(arg0, arg3) == 1)) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit054(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x20U, 5U, 0x41U);
}

s32 fightTrainerAiWazaHit053(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x20U, 4U, 0x41U);
}

s32 fightTrainerAiWazaHit052(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x20U, 3U, 0x41U);
}

s32 fightTrainerAiWazaHit051(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x20U, 2U, 0x41U);
}

s32 fightTrainerAiWazaHit050(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x20U, 1U, 0x41U);
}

s32 fightTrainerAiWazaHit049(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r30;
    s32 temp_r31;

    temp_r30 = fightTargetGetPtrAsNowFightType(2U, arg3);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 9U) == 0) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightSideIsJoutaiDataId(temp_r30, 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit048(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit047(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0xFU) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit046(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightSideCheckWriteJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg1), 0x4CU) != 2) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit045(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit044(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit029(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit043(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit042(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit041(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit040(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit039(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit038(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r29;
    u16 temp_r28;
    u8 temp_r30;
    u8 temp_r31;

    temp_r30 = fightTrainerAiGetFightOutPokemonLevel(arg0, arg1);
    temp_r31 = fightTrainerAiGetFightOutPokemonLevel(arg0, arg3);
    temp_r28 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    var_r29 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0xFFFFU);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r28, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        var_r29 = 0;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 5U) == 1) {
        var_r29 = 0;
    }
    if (temp_r30 < temp_r31) {
        var_r29 = 0;
    }
    if (var_r29 == 0) {
        return 0;
    }
    if (var_r29 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit037(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 8U) == 1) {
        return 0;
    }
    if (fightTrainerAiCheckSawagu(arg0, arg1) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0, 1.0f) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit036(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit035(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightSideCheckWriteJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg1), 0x49U) != 2) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit034(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit033(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x11U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 3U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 8U) == 1) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 4U) == 0) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg3), 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit032(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0, 1.0f) == 1) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit031(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit030(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiCheckTextureZokusei(arg0, arg1) == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit029(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit028(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp8[8];
    FIGHT_TRAINER *temp_r31;
    s32 var_r31;

    temp_r31 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, arg3);
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x15U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x25U) == 1) {
        return 0;
    }
    var_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerGetIrekaeFightPokemonAry(temp_r31, sp8) == 0) {
        var_r31 = 0;
    }
    if (var_r31 == 0) {
        return 0;
    }
    if (var_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit027(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit026(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit039(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit025(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

s32 fightTrainerAiWazaHit024(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x90U, 7U, 1U);
}

s32 fightTrainerAiWazaHit023(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x90U, 6U, 1U);
}

s32 fightTrainerAiWazaHit020(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x90U, 3U, 1U);
}

s32 fightTrainerAiWazaHit019(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x90U, 2U, 1U);
}

s32 fightTrainerAiWazaHit018(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x90U, 1U, 1U);
}

s32 fightTrainerAiWazaHit017(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit016(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x10U, 7U, 0x41U);
}

s32 fightTrainerAiWazaHit013(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x10U, 4U, 0x41U);
}

s32 fightTrainerAiWazaHit011(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x10U, 2U, 0x41U);
}

s32 fightTrainerAiWazaHit010(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return _fightTrainerAiWazaHitAbicnt(arg0, arg1, arg3, arg2, 0x10U, 1U, 0x41U);
}

s32 _fightTrainerAiWazaHitAbicnt(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, FightOutPokemon *arg2, u16 arg3, u16 arg4, u16 arg5, u16 arg6) {
    s32 var_r31;

    if (fightSeqCondChgActParaIdToValue(arg4) < 0) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0x14U) == 1) {
            return 0;
        }
        var_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg3, arg2, 0U);
        goto block_4;
    }
block_4:
    if (fightTrainerAiCheckAbiCnt(arg0, arg1, arg2, arg3, arg4, arg5, arg6) == 0) {
        return 0;
    }
    if (fightSeqCondChgActParaIdToValue(arg4) < 0) {
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg2, 0x1DU) == 1) {
            return 0;
        }
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg2, 0x49U) == 1) {
            return 0;
        }
        if (var_r31 == 0) {
            return 0;
        }
        if (var_r31 == -1) {
            return 1;
        }
        goto block_15;
    }
block_15:
    return 1;
}

s32 fightTrainerAiWazaHit009(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    if (fightTrainerAiCheckOumu(arg0, arg1) == 0) {
        return 0;
    }
    return 1;
}

s32 fightTrainerAiWazaHit008(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;
    u16 temp_r30;

    temp_r30 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 8U) == 0) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r30, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit007(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 hit;
    FightPokemon *sp8[24];
    u16 temp_r30;
    u16 temp_r31;

    temp_r30 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    temp_r31 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    if ((fightSeqRegulationZenmetuCheck(arg2) == 1) && (temp_r31 <= 1U)) {
        return 0;
    }
    if (fightTrainerAiCheckSimerike(arg0) == 1) {
        return 0;
    }
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r30, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        return 0;
    }
    hit = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (hit == 0) {
        return 0;
    }
    if (hit == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit006(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit005(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit004(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit003(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit002(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiWazaHit000(arg0, arg1, arg2, arg3);
}

s32 fightTrainerAiWazaHit001(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 8U) == 1) {
        return 0;
    }
    if (fightTrainerAiCheckSawagu(arg0, arg3) == 1) {
        return 0;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) {
        return 0;
    }
    if (_fightTrainerAiWazaHitCheckTokusei(arg0, arg3, 8U) == 0) {
        return 0;
    }
    temp_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightSideIsJoutaiDataId(fightTargetGetPtrAsNowFightType(2U, arg3), 0x4BU) == 1) {
        return 0;
    }
    if (temp_r31 == 0) {
        return 0;
    }
    if (temp_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHit000(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r30;

    temp_r30 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    var_r31 = _fightTrainerAiWazaHitCheck(arg0, arg1, arg2, arg3, 0U);
    if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg3, temp_r30, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43) {
        var_r31 = 0;
    }
    if (var_r31 == 0) {
        return 0;
    }
    if (var_r31 == -1) {
        return 1;
    }
    return 1;
}

s32 fightTrainerAiWazaHitNull(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 1;
}

u8 _fightTrainerAiWazaHitCheckTokusei(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2) {
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x11U) == 1) {
        if ((arg2 == 3) || (arg2 == 4)) {
            return 0U;
        }
        goto block_23;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x14U) == 1) {
        if (arg2 == 9) {
            return 0U;
        }
        goto block_23;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 7U) == 1) {
        if (arg2 == 5) {
            return 0U;
        }
        goto block_23;
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0xFU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x48U) == 1)) {
        if (arg2 == 8) {
            return 0U;
        }
        goto block_23;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x29U) == 1) {
        if (arg2 == 6) {
            return 0U;
        }
        goto block_23;
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x28U) == 1) {
        if (arg2 == 7) {
            return 0U;
        }
        goto block_23;
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0xCU) == 1) && (arg2 == 0xA)) {
        return 0U;
    }
block_23:
    return 1U;
}

s32 _fightTrainerAiWazaHitCheck(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3, u32 arg4) {
    FightOutPokemon *sp8[8];
    s32 var_r3;
    u16 temp_r24;
    u16 temp_r31;
    u16 var_r5;
    u16 var_r6;
    u16 var_r7;
    u32 temp_r24_2;
    u32 temp_r30;
    FightOutPokemon *temp_r3;

    temp_r30 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(arg1, fightFloor_GetFightType(0));
    fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    temp_r31 = wazaDB_GetSeqId(arg2);
    if (arg3 == 0) {
        return 1;
    }
    temp_r24 = fightFloorGetFightOutPokemonPtrAry(0, 1U, 0U, 0U, sp8);
    fightFloorSortFightOutPokemonPtrArySub(0, sp8, 8U, 0U);
    var_r6 = 0;
    var_r7 = 0;
    var_r5 = 0;
loop_9:
    if (var_r5 < temp_r24) {
        temp_r3 = *(FightOutPokemon **)((u8 *)sp8 + ((var_r5 * 4) & 0x3FFFC));
        if (temp_r3 != 0) {
            if (arg1 == temp_r3) {
                var_r6 = var_r5;
            }
            if (arg3 == temp_r3) {
                var_r7 = var_r5;
            }
        }
        var_r5 += 1;
        goto loop_9;
    }
    temp_r24_2 = (u32) (var_r6 - var_r7) >> 0x1FU;
    if ((arg4 == 0xFFFFU) || (arg4 == 0xFFFEU)) {
        if ((arg4 == 0xFFFFU) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1DU) == 1) && ((u16) temp_r30 == fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg3, 0x1DU))) {
            return -1;
        }
        if ((fightTrainerAiIsFightOutPokemonJoutaiKie(arg0, arg1) == 1) && (temp_r24_2 == 1)) {
            return 0;
        }
        if (fightTrainerAiCheckGuard(arg0, arg3, arg2) == 1) {
            return 0;
        }
        return 1;
    }
    if (fightSeqRegulationCheck(arg2, arg1, arg3) == 1) {
        return 0;
    }
    if (fightTrainerAiCheckGuard(arg0, arg3, arg2) == 1) {
        return 0;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1DU) == 1) && (fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg3, 0x1DU) == (u16) temp_r30)) {
        return -1;
    }
    if (temp_r24_2 == 1) {
        if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1FU) == 1) && (temp_r31 != 0x92) && (temp_r31 != 0x95) && (temp_r31 != 0x98) && (temp_r31 != 0xCF)) {
            return 0;
        }
        if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x20U) == 1) && (temp_r31 != 0x93)) {
            return 0;
        }
        if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x21U) == 1) && (arg2 != 0x39) && (arg2 != 0xFA)) {
            return 0;
        }
        goto block_43;
    }
block_43:
    if (fightSeqIsTenkouHit(arg2) == 1) {
        return -1;
    }
    var_r3 = 1;
    if (fightSeqIsAllwaysHit(arg2) == 1) {
        var_r3 = -1;
    }
    return var_r3;
}

}
