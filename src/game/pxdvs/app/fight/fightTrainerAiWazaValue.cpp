#include <dolphin/types.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct FIGHT_TRAINER FIGHT_TRAINER; typedef struct FightOutPokemon FightOutPokemon; typedef struct FightPokemon FightPokemon; typedef struct Pokemon Pokemon; typedef struct FightWaza FightWaza; typedef struct FightSide FightSide;
s32 fightTrainerAiAddValue(s32, s32);
s32 fightTrainerAiAddValueByAddsubDataId(s32, FIGHT_TRAINER *, u16);
s32 fightTrainerGetStatus(FIGHT_TRAINER *, u16, u16, u16);
u8 fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(void *, FIGHT_TRAINER *, u8, u8, u16, FightOutPokemon *);
u8 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER *, void *, u8);
u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER *, u16, u8);
FightSide * fightTargetGetPtrAsNowFightType(u8, FightOutPokemon *);
u8 fightSideIsJoutaiDataId(FightSide *, u16);
s32 fightTrainerAiCmpFightOutPokemonSubayasa(FIGHT_TRAINER *, FightOutPokemon *, FightOutPokemon *);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon *);
s16 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon *, u16);
u8 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon *, u16);
u8 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon *, u16, u8);
u16 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon *, u16);
u8 fightOutPokemon_GetSuccessCnt(FightOutPokemon *);
s32 fightTrainerAiValueAddsubDB_GetValue(u16);
u16 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER *, u16);
u8 fightTrainerAiGetWazaAddKoukaAvg(FIGHT_TRAINER *, u16);
u8 fightTrainerAiGetWazaPp(FIGHT_TRAINER *, u16);
u8 wazaDB_GetAvg(u16);
u8 fightTrainerAiIsFightOutPokemonNokoriHp(FIGHT_TRAINER *, FightOutPokemon *, f32, s32);
u8 fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_TRAINER *, void *, FightOutPokemon *, FightOutPokemon **);
u8 fightTrainerAiCheckJoutaiKieWazaHitWazaDataId(FIGHT_TRAINER *, u16, u16);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16, u16);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *, u8);
u8 fightTrainerAiWazaDoWazaHitFunc(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaDoWazaValueFunc(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
Pokemon * fightOutPokemonGetPokemonPtr(FightOutPokemon *);
u8 pokemonIsDarkPokemon(Pokemon *);
u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon *);
u8 fightSeqIsDoItemGetWaza(u16);
u8 fightFloor_GetTikeiDataId(void *);
u16 tikeiDataBiosGetWazaId(u8);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER *, u16, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(FIGHT_TRAINER *, FightOutPokemon *, u16 *);
u8 zokuseiBiosGetWazaKind(u16);
u8 itemDataCheckValid(u16);
u16 HSD_Rand(void);
u8 fightFloor_GetFightTypeFightoutPokemonNum(void *);
u32 fightFloor_GetFightType(void *);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void *, FIGHT_TRAINER *, FightOutPokemon **, u8, u8);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER *, FightOutPokemon *, u16 *, u8, u8);
void * fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon *);
u8 fightActionCheckValid(void *);
u16 fightActionGetKindDataId(void *);
u8 fightTrainerAiGetFightOutPokemonAbiCntAvd(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntAvg(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER *, FightOutPokemon *);
s32 fightTrainerAiGetFightOutPokemonNowHpPercentage(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonUsedItemDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonLastUseWazaDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonMaxHp(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonPhyAtk(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonPhyDef(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonPokemonDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSoubiItemDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSpeAtk(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSpeDef(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
s32 fightTrainerAiWazaValueMeromero(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDarkPanic(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDarkMist(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDarkHalf(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDarkEnd(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDarkRemove(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDarkHold(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDarkWeather(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHuuin(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMahi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKonran(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueYumekui(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKawarawari(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTeiryouDameeji(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHikarinokabe(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueRihurekutaa(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueOnibi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDoku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueBatontatti(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHaradaiko(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMarukunaru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMeisou(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueRyuunomai(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueBirudoAppu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKosumopawaa(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKaihirituAppu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDowasure(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTokukouAppu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKousokuidou(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueBougyoAppu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKougekiAppu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValuetorikku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSukirusuwappu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMamoru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTakuwaeru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueJyuuden(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueNemuriKoudou(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMigawari(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSawagu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueOomugaesi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueRandamuSentaku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHurahuradansu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMakibisi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueRisaikuru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSiroikiri(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueJikoanji(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKuroikiri(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTedasuke(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKyouseikoutai(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueYokodori(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKonoyubitomare(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKoukanKinsi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKanasibari(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMitizure(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueUrami(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueOdareru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueIbaru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueAnkooru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueIkarinomaeba(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKusuguruDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKaihiDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMeityuuDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTokubouDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueBougyoDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKougekiDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSubayasaDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueGamusyara(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueItamiwake(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueAkumu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueRokkuon(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueNoroi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueToriaezutukae(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKoraeru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMiyaburu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMajikkukooto(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueMiraakooto(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKauntaa(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueAroma(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueRihuressyu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSunaarasi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueArare(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueNihonbare(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueAmagoi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueNemurare(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueNemuru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKaihuku2(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKaihuku1(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKituke(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueOiuti(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueUezaabooru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSizennotikara(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHimitunotikara(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueItigekihissatu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueZennouryokuappu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikaKougekiAppu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHaganenotubasa(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSaikobuusuto(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueBakadikara(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueOobaahiito(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHatakiotosu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDouguUbau(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSooraabiimu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueToraiatakku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDokudokunokiba(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValuePoizunteeru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikaDoku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHandou(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikaNemuri(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueBakuretuPanti(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDenjihou(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikaMahi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikaKoori(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueBureizukikku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueJikokaitou(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHonoonouzu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueIryokuHonoo(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikouKonran(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueDorokake(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikouMeityuuDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikouTokubouDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikouTokukouDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKogoerukaze(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKanarazuSubayasaDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikouSubayasaDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikouBougyoDaun(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueOororabiimu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueNekodamasi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueGoddobaado(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuikaHirumi(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueJisin(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSokubaku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKorogaru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueJibaku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTobihaneru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSorawotobu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueAbareru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKyuusyuu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueRokettoZutuki(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKamaitati(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKiaipanti(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueAteminage(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueRibenji(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTokubetuYuusen(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueKouPuraioritii(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueSpeKuritikaru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValuePhyKuritikaru(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueHittyuu(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueTuujouIryoku(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
s32 fightTrainerAiWazaValueNull(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);

s32 fightTrainerAiWazaValueMeromero(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xD5U, arg3) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x287U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueDarkPanic(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3) <= 5U) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x284U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueDarkRemove(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r3;
    s32 var_r31;

    var_r31 = 0;
    temp_r3 = fightTargetGetPtrAsNowFightType(2U, arg3);
    if ((fightSideIsJoutaiDataId(temp_r3, 0x49U) == 1) || (fightSideIsJoutaiDataId(temp_r3, 0x48U) == 1) || (fightSideIsJoutaiDataId(temp_r3, 0x4BU) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x26DU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueDarkHold(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 var_r29;
    u16 temp_r30;
    u8 temp_r31;
    u8 var_r26;
    u8 var_r26_10;
    u8 var_r26_2;
    u8 var_r26_3;
    u8 var_r26_4;
    u8 var_r26_5;
    u8 var_r26_6;
    u8 var_r26_7;
    u8 var_r26_8;
    u8 var_r26_9;

    var_r29 = 0;
    temp_r31 = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(arg0, 0, arg3, 0);
    temp_r30 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    var_r26 = 0;
    while ((s32) var_r26 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26 * 4) & 0x3FC)), 3U) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x272U);
        }
        var_r26 += 1;
        continue;
    }
    var_r26_2 = 0;
    while ((s32) var_r26_2 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_2 * 4) & 0x3FC)), 4U) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x273U);
        }
        var_r26_2 += 1;
        continue;
    }
    var_r26_3 = 0;
    while ((s32) var_r26_3 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_3 * 4) & 0x3FC)), 6U) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x274U);
        }
        var_r26_3 += 1;
        continue;
    }
    var_r26_4 = 0;
    while ((s32) var_r26_4 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_4 * 4) & 0x3FC)), 5U) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x275U);
        }
        var_r26_4 += 1;
        continue;
    }
    var_r26_5 = 0;
    while ((s32) var_r26_5 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_5 * 4) & 0x3FC)), 9U) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x276U);
        }
        var_r26_5 += 1;
        continue;
    }
    var_r26_6 = 0;
    while ((s32) var_r26_6 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_6 * 4) & 0x3FC)), 0xAU) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x277U);
        }
        var_r26_6 += 1;
        continue;
    }
    var_r26_7 = 0;
    while ((s32) var_r26_7 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_7 * 4) & 0x3FC)), 0x18U) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x278U);
        }
        var_r26_7 += 1;
        continue;
    }
    var_r26_8 = 0;
    while ((s32) var_r26_8 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_8 * 4) & 0x3FC)), 0x1EU) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x279U);
        }
        var_r26_8 += 1;
        continue;
    }
    var_r26_9 = 0;
    while ((s32) var_r26_9 < (s32) temp_r30) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_9 * 4) & 0x3FC)), 0x1CU) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x27AU);
        }
        var_r26_9 += 1;
        continue;
    }
    if (fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U) == 5) {
        var_r26_10 = 0;
        while ((s32) var_r26_10 < (s32) temp_r30) {
            if (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(*(FightOutPokemon **)((u8 *)sp8 + ((var_r26_10 * 4) & 0x3FC)))) == 0) {
                var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x27BU);
            }
            var_r26_10 += 1;
            continue;
        }
    }
    if (temp_r31 != 0) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x27CU);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueHuuin(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8;
    s32 var_r30;
    u16 temp_r31;

    var_r30 = 0;
    temp_r31 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, &sp8, 0U, 1U);
    if (fightOutPokemon_GetFightoutTurnCount(arg1) != 0) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x285U);
    }
    if (temp_r31 > 0) {
        if (fightOutPokemon_GetFightoutTurnCount(sp8) != 0) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x286U);
        }
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueYumekui(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    s32 var_r31_2;
    u16 temp_r31;

    fightTrainerAiGetFightOutPokemonNowHp(arg0, arg1);
    temp_r31 = fightTrainerAiGetFightOutPokemonMaxHp(arg0, arg1);
    var_r31_2 = (s32) ((fightTrainerAiWazaDoWazaDamageFunc(arg0, arg1, arg2, arg3, 1U) / 2) * 0x64) / (s32) temp_r31;
    if (var_r31_2 > 0x64) {
        var_r31_2 = 0x64;
    }
    var_r31 = fightTrainerAiAddValue(0, var_r31_2 / fightTrainerGetStatus(0, 0x26EU, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x26FU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKawarawari(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r3;
    s32 var_r31;

    var_r31 = 0;
    temp_r3 = fightTargetGetPtrAsNowFightType(2U, arg3);
    if ((fightSideIsJoutaiDataId(temp_r3, 0x49U) == 1) || (fightSideIsJoutaiDataId(temp_r3, 0x48U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x26BU);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x26CU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueTeiryouDameeji(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, arg3) == 0xD5) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x26AU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueHikarinokabe(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r28;
    u16 temp_r29;
    u16 temp_r30;
    u16 temp_r31;

    var_r28 = 0;
    temp_r29 = fightTrainerAiGetFightOutPokemonSpeAtk(arg0, arg3);
    temp_r30 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, arg3);
    temp_r31 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    if (fightTrainerAiWazaDoWazaHitFunc(arg0, arg1, arg2, arg3) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x267U);
    }
    if (temp_r30 < temp_r29) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x268U);
    }
    if (temp_r31 == 0x118) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x269U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueRihurekutaa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r28;
    u16 temp_r29;
    u16 temp_r30;
    u16 temp_r31;

    var_r28 = 0;
    temp_r29 = fightTrainerAiGetFightOutPokemonSpeAtk(arg0, arg3);
    temp_r30 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, arg3);
    temp_r31 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    if (fightTrainerAiWazaDoWazaHitFunc(arg0, arg1, arg2, arg3) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x264U);
    }
    if (temp_r30 > temp_r29) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x265U);
    }
    if (temp_r31 == 0x118) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x266U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueBatontatti(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonAllAbiCntTakai(arg0, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x25CU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValuetorikku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r3;

    var_r31 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, arg1);
    if ((temp_r3 == 0x1D) || (temp_r3 == 0x18)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x22AU);
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x3CU) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x22BU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueSukirusuwappu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x36U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x10U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x228U);
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x36U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x10U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x229U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueTakuwaeru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s16 var_r3;
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x2DU) == 1) {
        var_r3 = fightOutPokemonGetCountAsJoutaiDataId(arg1, 0x2DU);
    } else {
        var_r3 = 0;
    }
    switch (var_r3) {
    case 0:
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x21CU);
        break;
    case 1:
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x21DU);
        break;
    case 2:
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x21EU);
        break;
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueJyuuden(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8[4];
    s32 var_r29;
    u16 temp_r31;
    u16 temp_r4;
    u16 var_r28;

    var_r29 = 0;
    temp_r31 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp8, 0U, 1U);
    var_r28 = 0;
    while (var_r28 < temp_r31) {
        temp_r4 = *(u16 *)((u8 *)sp8 + ((var_r28 * 2) & 0x1FFFE));
        if ((temp_r4 != 0x10C) && (fightTrainerAiGetWazaZokuseiDataId(arg0, temp_r4, arg1) == 0xD)) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x21AU);
        } else {
            var_r28 += 1;
            continue;
        }

        break;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x24U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x21BU);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueRandamuSentaku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;

    temp_r31 = fightTrainerGetStatus(0, 0x210U, 0x3EU, 0U);
    return fightTrainerAiAddValue(0, HSD_Rand() % (temp_r31 + 1));
}

s32 fightTrainerAiWazaValueHurahuradansu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;
    s32 var_r30;
    u16 temp_r31;
    u16 temp_r3;
    u16 var_r25;
    u16 var_r25_2;
    u16 var_r5;

    var_r30 = 0;
    temp_r31 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    if (fightFloor_GetFightTypeFightoutPokemonNum(0) >= 2U) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x20CU);
    }
    var_r25 = 0;
    while (var_r25 < temp_r31) {
        temp_r4 = *(FightOutPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4) && ((temp_r3 = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, temp_r4), ((temp_r3 == 8) != 0)) || (temp_r3 == 9))) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x20DU);
        } else {
            var_r25 += 1;
            continue;
        }

        break;
    }
    var_r25_2 = 0;
    while (var_r25_2 < temp_r31) {
        temp_r4_2 = *(FightOutPokemon **)((u8 *)sp8 + ((var_r25_2 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_2) && (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, temp_r4_2, 0x14U) == 1)) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x20EU);
        } else {
            var_r25_2 += 1;
            continue;
        }

        break;
    }
    var_r5 = 0;
    while (var_r5 < temp_r31) {
        if (arg1 != *(FightOutPokemon **)((u8 *)sp8 + ((var_r5 * 4) & 0x3FFFC))) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x20FU);
        } else {
            var_r5 += 1;
            continue;
        }

        break;
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueRisaikuru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiGetFightOutPokemonUsedItemDataId(arg0, arg1) != 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x208U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueYokodori(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 var_r26;
    u16 temp_r25;
    u16 temp_r27;
    u16 temp_r28;
    u16 temp_r30;
    u16 temp_r3;
    u16 var_r25;

    var_r26 = 0;
    temp_r27 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg1);
    temp_r28 = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(arg0, arg1);
    temp_r25 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    temp_r30 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    if ((temp_r25 != 0) && (temp_r25 != -1U) && (temp_r25 != 0x176) && (temp_r25 != 0x163) && (fightTrainerAiIsWazaTypeId(arg0, temp_r25, 4U) == 1)) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1EEU);
    }
    var_r25 = 0;
    while (var_r25 < temp_r30) {
        temp_r3 = fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FFFC)));
        if ((temp_r3 == 0x12E) || (temp_r3 == 0xD4) || (temp_r3 == 0x177)) {
            var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x1EFU);
        } else {
            var_r25 += 1;
            continue;
        }

        break;
    }
    if ((temp_r27 == 0x121) || (temp_r28 == 0x121)) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x1F0U);
    }
    return var_r26;
}

s32 fightTrainerAiWazaValueKonoyubitomare(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp2C[8];
    FightOutPokemon *spC[8];
    u16 sp8[2];
    FightOutPokemon *temp_r4;
    s32 temp_r26;
    s32 var_r21;
    u16 temp_r23;
    u16 temp_r24;
    u16 temp_r28;
    u16 temp_r29;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 var_r16;
    u16 var_r16_2;
    u16 var_r17;
    u16 var_r18;
    u16 var_r19;
    u8 var_r20;

    var_r21 = 0;
    temp_r23 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp2C, 1U, 1U);
    temp_r3 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, spC, 0U, 1U);
    temp_r24 = temp_r3;
    temp_r29 = temp_r3;
    var_r20 = 0;
    var_r19 = 0;
    while (var_r19 < temp_r29) {
        temp_r28 = fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(arg0, *(FightOutPokemon **)((u8 *)spC + ((var_r19 * 4) & 0x3FFFC)), sp8);
        var_r18 = 0;
        while (var_r18 < temp_r28) {
            var_r17 = 0;
            while (var_r17 < temp_r23) {
                temp_r26 = (var_r17 * 4) & 0x3FFFC;
                if ((arg1 != *(FightOutPokemon **)((u8 *)sp2C + temp_r26)) && (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp2C + temp_r26), *(u16 *)((u8 *)sp8 + ((var_r18 * 2) & 0x1FFFE)), fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x41)) {
                    var_r20 = 1;
                }
                var_r17 += 1;
                continue;
            }
            var_r18 += 1;
            continue;
        }
        var_r19 += 1;
        continue;
    }
    if (var_r20 == 1) {
        var_r21 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1EBU);
    }
    var_r16 = 0;
    while (var_r16 < temp_r23) {
        temp_r4 = *(FightOutPokemon **)((u8 *)sp2C + ((var_r16 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4) && (fightTrainerAiGetFightOutPokemonKeyPlayerFlag(arg0, temp_r4) == 2)) {
            var_r21 = fightTrainerAiAddValueByAddsubDataId(var_r21, arg0, 0x1ECU);
        } else {
            var_r16 += 1;
            continue;
        }

        break;
    }
    var_r16_2 = 0;
    while (var_r16_2 < temp_r24) {
        temp_r3_2 = fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, *(FightOutPokemon **)((u8 *)spC + ((var_r16_2 * 4) & 0x3FFFC)));
        if ((temp_r3_2 == 0x12E) || (temp_r3_2 == 0xD4) || (temp_r3_2 == 0x177)) {
            var_r21 = fightTrainerAiAddValueByAddsubDataId(var_r21, arg0, 0x1EDU);
        } else {
            var_r16_2 += 1;
            continue;
        }

        break;
    }
    return var_r21;
}

s32 fightTrainerAiWazaValueKoukanKinsi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r29;

    var_r29 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1E1U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1E2U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 6U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1E3U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 5U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1E4U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1E5U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0xAU) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1E6U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x18U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1E7U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1EU) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1E8U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1CU) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1E9U);
    }
    if ((fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U) == 5) && (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(arg3)) == 0)) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1EAU);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueKanasibari(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r30;

    var_r31 = 0;
    temp_r30 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    if ((fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg1, arg3) > 0) && (temp_r30 != 0) && (temp_r30 != -1U) && (temp_r30 != 0x176) && (temp_r30 != 0x163) && (fightTrainerAiIsWazaTypeId(arg0, temp_r30, 1U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1E0U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueUrami(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r3;
    u8 temp_r3_2;

    var_r31 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    if ((temp_r3 != 0) && (temp_r3 != -1U) && (temp_r3 != 0x176) && (temp_r3 != 0x163) && (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg1, arg3) > 0)) {
        temp_r3_2 = fightTrainerAiGetWazaPp(arg0, temp_r3);
        if (temp_r3_2 <= 5U) {
            var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1DBU);
        } else if (temp_r3_2 <= 0xAU) {
            var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1DCU);
        }
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueAnkooru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r30;

    var_r31 = 0;
    temp_r30 = fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(arg0, arg3);
    if ((fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg1, arg3) > 0) && (temp_r30 != 0) && (temp_r30 != -1U) && (temp_r30 != 0x176) && (temp_r30 != 0x163) && (fightTrainerAiIsWazaTypeId(arg0, temp_r30, 1U) == 0)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1D0U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKusuguruDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r28;
    u16 temp_r29;
    u16 temp_r30;
    u16 temp_r31;
    u16 temp_r31_2;

    var_r28 = 0;
    temp_r29 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, arg3);
    temp_r31 = fightTrainerAiGetFightOutPokemonSpeAtk(arg0, arg3);
    temp_r30 = fightTrainerAiGetFightOutPokemonPhyDef(arg0, arg3);
    temp_r31_2 = fightTrainerAiGetFightOutPokemonSpeDef(arg0, arg3);
    if (temp_r29 > temp_r31) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1CCU);
    }
    if (temp_r30 > temp_r31_2) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x1CDU);
    }
    if ((fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg3) <= 4U) && (fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg3) <= 4U)) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x1CEU);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueMeityuuDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiGetFightOutPokemonAbiCntAvg(arg0, arg3) <= 4U) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1C8U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueTokubouDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u16 temp_r31;

    var_r30 = 0;
    temp_r31 = fightTrainerAiGetFightOutPokemonPhyDef(arg0, arg3);
    if (temp_r31 < fightTrainerAiGetFightOutPokemonSpeDef(arg0, arg3)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1C6U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg3) <= 4U) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1C7U);
    }
    return var_r30;
}



s32 fightTrainerAiWazaValueKougekiDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u16 temp_r31;

    var_r30 = 0;
    temp_r31 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, arg3);
    if (temp_r31 > fightTrainerAiGetFightOutPokemonSpeAtk(arg0, arg3)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1C2U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg3) <= 4U) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1C3U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueSubayasaDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    u16 temp_r31;
    u16 var_r28;
    u8 var_r29;

    var_r29 = 0;
    temp_r31 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    var_r28 = 0;
    while (var_r28 < temp_r31) {
        if (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg3, *(FightOutPokemon **)((u8 *)sp8 + ((var_r28 * 4) & 0x3FFFC))) > 0) {
            var_r29 = 1;
        } else {
            var_r28 += 1;
            continue;
        }

        break;
    }
    if (var_r29 == 1) {
        return fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1C0U);
    }
    return fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1C1U);
}

s32 fightTrainerAiWazaValueGamusyara(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;
    u16 temp_r31_2;

    temp_r31_2 = fightTrainerAiGetFightOutPokemonNowHp(arg0, arg1);
    temp_r31 = (s32) fightTrainerAiGetFightOutPokemonNowHp(arg0, arg3) / (s32) temp_r31_2;
    return fightTrainerAiAddValue(0, temp_r31 * fightTrainerGetStatus(0, 0x1BFU, 0x3EU, 0U));
}

s32 fightTrainerAiWazaValueItamiwake(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r3;
    s32 var_r30;
    u8 temp_r31;

    var_r30 = 0;
    temp_r31 = fightTrainerAiGetFightOutPokemonNowHpPercentage(arg0, arg1);
    temp_r3 = fightTrainerAiGetFightOutPokemonNowHpPercentage(arg0, arg3);
    if ((s32) (temp_r31 * 3) <= temp_r3) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1BCU);
    } else if ((s32) (temp_r31 * 2) <= temp_r3) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1BBU);
    } else if ((s32) temp_r31 >= (s32) (temp_r3 * 3)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1BEU);
    } else if ((s32) temp_r31 >= (s32) (temp_r3 * 2)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1BDU);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueAkumu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x17U) == 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1BAU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueToriaezutukae(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1B2U);
}

s32 fightTrainerAiWazaValueMiyaburu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 7U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1A6U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3) >= 8U) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x1A7U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x19U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x1A8U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueMajikkukooto(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightOutPokemon_GetFightoutTurnCount(arg1) != 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1A5U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueMiraakooto(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 temp_r30_2;
    s32 var_r28;
    u16 temp_r27;
    u16 temp_r30;
    u16 temp_r30_3;
    u16 var_r26;

    var_r28 = 0;
    temp_r30 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    temp_r27 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    var_r26 = 0;
    while (var_r26 < temp_r30) {
        temp_r30_2 = (var_r26 * 4) & 0x3FFFC;
        temp_r30_3 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r30_2));
        if (temp_r30_3 < fightTrainerAiGetFightOutPokemonSpeAtk(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r30_2))) {
            var_r28 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1A3U);
        } else {
            var_r26 += 1;
            continue;
        }

        break;
    }
    if ((temp_r27 != 0) && (temp_r27 != -1U) && (temp_r27 != 0x176) && (temp_r27 != 0x163) && (zokuseiBiosGetWazaKind(fightTrainerAiGetWazaZokuseiDataId(arg0, temp_r27, arg3)) == 2)) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x1A4U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueKauntaa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 temp_r30_2;
    s32 var_r28;
    u16 temp_r27;
    u16 temp_r30;
    u16 temp_r30_3;
    u16 var_r26;

    var_r28 = 0;
    temp_r30 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    temp_r27 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    var_r26 = 0;
    while (var_r26 < temp_r30) {
        temp_r30_2 = (var_r26 * 4) & 0x3FFFC;
        temp_r30_3 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r30_2));
        if (temp_r30_3 > fightTrainerAiGetFightOutPokemonSpeAtk(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r30_2))) {
            var_r28 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1A1U);
        } else {
            var_r26 += 1;
            continue;
        }

        break;
    }
    if ((temp_r27 != 0) && (temp_r27 != -1U) && (temp_r27 != 0x176) && (temp_r27 != 0x163) && (zokuseiBiosGetWazaKind(fightTrainerAiGetWazaZokuseiDataId(arg0, temp_r27, arg3)) == 1)) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x1A2U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueRihuressyu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg1) == 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x19FU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKituke(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 5U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x177U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x178U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueUezaabooru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r3;

    var_r30 = 0;
    temp_r3 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    if ((temp_r3 == 1) || (temp_r3 == 2)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x168U);
    }
    if (temp_r3 == 4) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x169U);
    }
    if (temp_r3 == 3) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x16AU);
    }
    if (temp_r3 == 5) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x16BU);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x16CU);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueSizennotikara(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 temp_r3;

    temp_r3 = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    if (temp_r3 != arg2) {
        return fightTrainerAiWazaDoWazaValueFunc(arg0, arg1, temp_r3, arg3);
    }
    return 0;
}

s32 fightTrainerAiWazaValueItigekihissatu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x166U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x167U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueZennouryokuappu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x164U);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x165U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueTuikaKougekiAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r30;
    u8 temp_r31;

    temp_r30 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r30 = fightTrainerAiAddValue(0, (s32) temp_r30 / fightTrainerGetStatus(0, 0x161U, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x162U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1) >= 0xCU) {
        temp_r31 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValue(var_r30, (s32) temp_r31 / fightTrainerGetStatus(0, 0x163U, 0x3EU, 0U));
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueHaganenotubasa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x15EU);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x15FU);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg1) >= 0xCU) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x160U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueSaikobuusuto(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r29;
    s32 var_r29_2;
    u16 temp_r3;
    u8 temp_r3_2;

    var_r29_2 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, arg1);
    if (temp_r3 == 0x17) {
        var_r29_2 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x159U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r29_2 = fightTrainerAiAddValueByAddsubDataId(var_r29_2, arg0, 0x15AU);
    }
    var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29_2, arg0, 0x15CU);
    temp_r3_2 = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(arg0, arg1);
    if (temp_r3_2 < 6U) {
        var_r29 = fightTrainerAiAddValue(var_r29, (6 - temp_r3_2) * fightTrainerGetStatus(0, 0x15DU, 0x3EU, 0U));
    }
    if (temp_r3 == 0x17) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x15BU);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueBakadikara(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r29;
    s32 var_r29_2;
    u16 temp_r3;
    u8 temp_r3_2;

    var_r29_2 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, arg1);
    if (temp_r3 == 0x17) {
        var_r29_2 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x154U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r29_2 = fightTrainerAiAddValueByAddsubDataId(var_r29_2, arg0, 0x155U);
    }
    var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29_2, arg0, 0x157U);
    temp_r3_2 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    if (temp_r3_2 < 6U) {
        var_r29 = fightTrainerAiAddValue(var_r29, (6 - temp_r3_2) * fightTrainerGetStatus(0, 0x158U, 0x3EU, 0U));
    }
    if (temp_r3 == 0x17) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x156U);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueOobaahiito(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r3;

    var_r30 = 0;
    if (fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, arg1) == 0x17) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x150U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x151U);
    }
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(arg0, arg1);
    if (temp_r3 < 6U) {
        var_r30 = fightTrainerAiAddValue(var_r30, (temp_r3 + 6) * fightTrainerGetStatus(0, 0x152U, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 7U) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x153U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueHatakiotosu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x3DU) == 0) && (fightTrainerAiGetFightOutPokemonSoubiItemDataId(arg0, arg3) != 0)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x14EU);
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x3CU) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x14FU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueDouguUbau(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u16 temp_r28;
    u16 temp_r31;
    u8 var_r29;

    var_r30 = 0;
    temp_r31 = fightTrainerAiGetFightOutPokemonSoubiItemDataId(arg0, arg1);
    temp_r28 = fightTrainerAiGetFightOutPokemonSoubiItemDataId(arg0, arg3);
    var_r29 = 1;
    if (fightSeqIsDoItemGetWaza((u16) arg1) == 0) {
        var_r29 = 0;
    }
    if ((temp_r31 != 0) || (temp_r28 == 0xAF) || (temp_r28 == 0) || (itemDataCheckValid(temp_r28) == 0)) {
        var_r29 = 0;
    }
    if (var_r29 == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x14CU);
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x3CU) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x14DU);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueSooraabiimu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r3;

    var_r30 = 0;
    temp_r3 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    if (temp_r3 == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x148U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x149U);
    }
    if ((temp_r3 == 2) || (temp_r3 == 4) || (temp_r3 == 3)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x14AU);
    }
    if (temp_r3 == 0) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x14BU);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueToraiatakku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x143U);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x144U);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x145U);
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 7U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x29U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x28U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x146U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x147U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueDokudokunokiba(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x13FU);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x140U);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x11U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 3U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x141U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x142U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValuePoizunteeru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r31;
    s32 var_r27;
    u8 temp_r3;

    temp_r31 = fightTargetGetPtrAsNowFightType(2U, arg3);
    var_r27 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x139U);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg3);
    if (temp_r3 > 6U) {
        var_r27 = fightTrainerAiAddValue(var_r27, (temp_r3 - 6) * fightTrainerGetStatus(0, 0x13AU, 0x3EU, 0U));
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x13BU);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x11U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 3U) == 1)) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x13DU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x13EU);
    }
    if (fightSideIsJoutaiDataId(temp_r31, 0x48U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x13CU);
    }
    return var_r27;
}

s32 fightTrainerAiWazaValueTuikaDoku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r29;
    u8 temp_r29_2;
    u8 temp_r29_3;

    temp_r29 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r30 = fightTrainerAiAddValue(0, (s32) temp_r29 / fightTrainerGetStatus(0, 0x135U, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x136U);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x11U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 3U) == 1)) {
        temp_r29_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValue(var_r30, (s32) temp_r29_2 / fightTrainerGetStatus(0, 0x137U, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r29_3 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r30, (s32) temp_r29_3 / fightTrainerGetStatus(0, 0x138U, 0x3EU, 0U)), arg0, 0x138U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueHandou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x132U);
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x36U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x133U);
    }
    return fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x134U);
}

s32 fightTrainerAiWazaValueTuikaMahi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r29;
    u8 temp_r29_2;
    u8 temp_r29_3;

    temp_r29 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r30 = fightTrainerAiAddValue(0, (s32) temp_r29 / fightTrainerGetStatus(0, 0x121U, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x122U);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 7U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1)) {
        temp_r29_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValue(var_r30, (s32) temp_r29_2 / fightTrainerGetStatus(0, 0x123U, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r29_3 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r30, (s32) temp_r29_3 / fightTrainerGetStatus(0, 0x124U, 0x3EU, 0U)), arg0, 0x124U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueBureizukikku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r31;
    s32 var_r27;
    s32 var_r28;
    u8 temp_r3;

    var_r27 = 0;
    temp_r31 = fightTargetGetPtrAsNowFightType(2U, arg3);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg3);
    if (temp_r3 > 6U) {
        var_r27 = fightTrainerAiAddValue(0, (temp_r3 - 6) * fightTrainerGetStatus(0, 0x115U, 0x3EU, 0U));
    }
    var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x116U);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x117U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 7U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x119U);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x29U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 0xAU) == 1)) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x11AU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x11BU);
    }
    if (fightSideIsJoutaiDataId(temp_r31, 0x49U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x118U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueJikokaitou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r27;
    s32 var_r28;
    u8 temp_r27;
    u8 temp_r28;
    u8 temp_r30;

    var_r27 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 7U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x10FU);
    }
    temp_r28 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r28 = fightTrainerAiAddValue(var_r27, (s32) temp_r28 / fightTrainerGetStatus(0, 0x110U, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x111U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 7U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x112U);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x29U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 0xAU) == 1)) {
        temp_r27 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r27 / fightTrainerGetStatus(0, 0x113U, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r30 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r28, (s32) temp_r30 / fightTrainerGetStatus(0, 0x114U, 0x3EU, 0U)), arg0, 0x114U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueIryokuHonoo(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 temp_r28;
    s32 var_r25_2;
    s32 var_r28;
    u16 temp_r31;
    u8 var_r25;
    u8 var_r26;
    u8 var_r26_2;
    u8 var_r26_3;
    u8 var_r27;
    u8 var_r27_2;
    u8 var_r27_3;

    temp_r31 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    var_r26 = 0;
    var_r25 = 0;
    while ((s32) var_r25 < (s32) temp_r31) {
        if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FC))) == 1) {
            var_r26 = var_r26 + 1;
        }
        var_r25 += 1;
        continue;
    }
    var_r25_2 = fightTrainerAiAddValue(0, var_r26 * fightTrainerGetStatus(0, 0xFFU, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r25_2 = fightTrainerAiAddValueByAddsubDataId(var_r25_2, arg0, 0x100U);
    }
    var_r27 = 0;
    var_r26_2 = 0;
    while ((s32) var_r26_2 < (s32) temp_r31) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_2 * 4) & 0x3FC)), 7U) == 1) {
            var_r27 = var_r27 + 1;
        }
        var_r26_2 += 1;
        continue;
    }
    var_r27_2 = 0;
    temp_r28 = fightTrainerAiAddValue(var_r25_2, var_r27 * fightTrainerGetStatus(0, 0x101U, 0x3EU, 0U));
    var_r26_3 = 0;
    while ((s32) var_r26_3 < (s32) temp_r31) {
        if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x29U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 0xAU) == 1)) {
            var_r27_2 += 1;
        }
        var_r26_3 += 1;
        continue;
    }
    var_r28 = fightTrainerAiAddValue(temp_r28, var_r27_2 * fightTrainerGetStatus(0, 0x102U, 0x3EU, 0U));
    var_r27_3 = 0;
    while ((s32) var_r27_3 < (s32) temp_r31) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r27_3 * 4) & 0x3FC)), 0x14U) == 1) {
            var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x103U);
        }
        var_r27_3 += 1;
        continue;
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueTuikouKonran(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r29;
    u8 temp_r28;
    u8 temp_r28_2;
    u8 temp_r28_3;
    u8 temp_r31;

    temp_r28 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r29 = fightTrainerAiAddValue(0, (s32) temp_r28 / fightTrainerGetStatus(0, 0xFAU, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0xFBU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        temp_r28_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r29 = fightTrainerAiAddValue(var_r29, (s32) temp_r28_2 / fightTrainerGetStatus(0, 0xFCU, 0x3EU, 0U));
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x14U) == 1)) {
        temp_r28_3 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r29 = fightTrainerAiAddValue(var_r29, (s32) temp_r28_3 / fightTrainerGetStatus(0, 0xFDU, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r31 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r29 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r29, (s32) temp_r31 / fightTrainerGetStatus(0, 0xFEU, 0x3EU, 0U)), arg0, 0xFEU);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueDorokake(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0xF5U);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvg(arg0, arg3) == 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xF6U);
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x49U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x33U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xF7U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntAvg(arg0, arg3) <= 4U) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xF8U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xF9U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueTuikouMeityuuDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r28;
    u8 temp_r27;
    u8 temp_r27_2;
    u8 temp_r27_3;
    u8 temp_r30;

    temp_r27 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r28 = fightTrainerAiAddValue(0, (s32) temp_r27 / fightTrainerGetStatus(0, 0xF0U, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xF1U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntAvg(arg0, arg3) == 0) {
        temp_r27_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r27_2 / fightTrainerGetStatus(0, 0xF2U, 0x3EU, 0U));
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x49U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x33U) == 1)) {
        temp_r27_3 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r27_3 / fightTrainerGetStatus(0, 0xF3U, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r30 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r28, (s32) temp_r30 / fightTrainerGetStatus(0, 0xF4U, 0x3EU, 0U)), arg0, 0xF4U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueTuikouTokubouDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r28;
    u8 temp_r27;
    u8 temp_r27_2;
    u8 temp_r27_3;
    u8 temp_r30;

    temp_r27 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r28 = fightTrainerAiAddValue(0, (s32) temp_r27 / fightTrainerGetStatus(0, 0xEBU, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xECU);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg3) == 0) {
        temp_r27_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r27_2 / fightTrainerGetStatus(0, 0xEDU, 0x3EU, 0U));
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x49U) == 1)) {
        temp_r27_3 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r27_3 / fightTrainerGetStatus(0, 0xEEU, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r30 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r28, (s32) temp_r30 / fightTrainerGetStatus(0, 0xEFU, 0x3EU, 0U)), arg0, 0xEFU);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueTuikouTokukouDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0xE6U);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xE7U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(arg0, arg3) == 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xE8U);
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x49U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xE9U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xEAU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKogoerukaze(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp28[8];
    FightOutPokemon *sp8[8];
    FightOutPokemon *temp_r19;
    FightOutPokemon *temp_r5;
    FightOutPokemon *temp_r5_2;
    s32 temp_r28;
    s32 var_r29;
    u16 temp_r25;
    u16 temp_r30;
    u16 temp_r31;
    u16 temp_r3;
    u16 var_r20;
    u16 var_r21;
    u16 var_r22;
    u16 var_r22_2;
    u16 var_r23;

    var_r29 = 0;
    temp_r30 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp28, 1U, 1U);
    temp_r3 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    temp_r31 = temp_r3;
    temp_r25 = temp_r3;
    var_r21 = 0;
    while (var_r21 < temp_r25) {
        temp_r19 = *(FightOutPokemon **)((u8 *)sp8 + ((var_r21 * 4) & 0x3FFFC));
        if (temp_r19 != 0) {
            var_r20 = 0;
            while (var_r20 < temp_r30) {
                temp_r5 = *(FightOutPokemon **)((u8 *)sp28 + ((var_r20 * 4) & 0x3FFFC));
                if ((temp_r5 != 0) && (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, temp_r19, temp_r5) > 0)) {
                    var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0xE0U);
                }
                var_r20 += 1;
                continue;
            }
        }
        var_r21 += 1;
        continue;
    }
    if (temp_r25 >= 2U) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0xE1U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0xE2U);
    }
    var_r22 = 0;
    while (var_r22 < temp_r30) {
        temp_r5_2 = *(FightOutPokemon **)((u8 *)sp28 + ((var_r22 * 4) & 0x3FFFC));
        if ((temp_r5_2 == 0) || (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg3, temp_r5_2) >= 0)) {
            var_r22 += 1;
            continue;
        }

        break;
    }
    if (var_r22 < temp_r30) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0xE3U);
    }
    var_r23 = 0;
    while (var_r23 < temp_r31) {
        temp_r28 = (var_r23 * 4) & 0x3FFFC;
        if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r28), 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r28), 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r28), 0x49U) == 1)) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0xE4U);
        }
        var_r23 += 1;
        continue;
    }
    var_r22_2 = 0;
    while (var_r22_2 < temp_r31) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r22_2 * 4) & 0x3FFFC)), 0x14U) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0xE5U);
        }
        var_r22_2 += 1;
        continue;
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueKanarazuSubayasaDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp28[8];
    FightOutPokemon *sp8;
    FightOutPokemon *temp_r5;
    s32 var_r27;
    u16 temp_r29;
    u16 var_r26;

    var_r27 = 0;
    temp_r29 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp28, 1U, 1U);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, &sp8, 0U, 1U);
    var_r26 = 0;
    while (var_r26 < temp_r29) {
        temp_r5 = *(FightOutPokemon **)((u8 *)sp28 + ((var_r26 * 4) & 0x3FFFC));
        if ((temp_r5 != 0) && (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg3, temp_r5) > 0)) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0xDBU);
        } else {
            var_r26 += 1;
            continue;
        }

        break;
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xDCU);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg3) == 0) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xDDU);
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x49U) == 1)) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xDEU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xDFU);
    }
    return var_r27;
}

s32 fightTrainerAiWazaValueTuikouSubayasaDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    FightOutPokemon *temp_r5;
    s32 var_r30;
    u16 temp_r31;
    u16 var_r24;
    u8 temp_r25;
    u8 temp_r25_2;
    u8 temp_r25_3;
    u8 temp_r25_4;
    u8 temp_r25_5;

    temp_r31 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    temp_r25 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r30 = fightTrainerAiAddValue(0, (s32) temp_r25 / fightTrainerGetStatus(0, 0xD4U, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0xD5U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 5U) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0xD6U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg3) == 0) {
        temp_r25_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValue(var_r30, (s32) temp_r25_2 / fightTrainerGetStatus(0, 0xD7U, 0x3EU, 0U));
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x49U) == 1)) {
        temp_r25_3 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValue(var_r30, (s32) temp_r25_3 / fightTrainerGetStatus(0, 0xD8U, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r25_4 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r30, (s32) temp_r25_4 / fightTrainerGetStatus(0, 0xD9U, 0x3EU, 0U)), arg0, 0xD9U);
    }
    var_r24 = 0;
    while (var_r24 < temp_r31) {
        temp_r5 = *(FightOutPokemon **)((u8 *)sp8 + ((var_r24 * 4) & 0x3FFFC));
        if ((temp_r5 == 0) || (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg3, temp_r5) <= 0)) {
            var_r24 += 1;
            continue;
        }

        break;
    }
    if (var_r24 < temp_r31) {
        temp_r25_5 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r30 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r30, (s32) temp_r25_5 / fightTrainerGetStatus(0, 0xDAU, 0x3EU, 0U)), arg0, 0xDAU);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueTuikouBougyoDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r28;
    u8 temp_r27;
    u8 temp_r27_2;
    u8 temp_r27_3;
    u8 temp_r30;

    temp_r27 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r28 = fightTrainerAiAddValue(0, (s32) temp_r27 / fightTrainerGetStatus(0, 0xCFU, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xD0U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg3) == 0) {
        temp_r27_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r27_2 / fightTrainerGetStatus(0, 0xD1U, 0x3EU, 0U));
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x49U) == 1)) {
        temp_r27_3 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r27_3 / fightTrainerGetStatus(0, 0xD2U, 0x3EU, 0U));
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r30 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r28, (s32) temp_r30 / fightTrainerGetStatus(0, 0xD3U, 0x3EU, 0U)), arg0, 0xD3U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueOororabiimu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u8 temp_r30;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0xCAU);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xCBU);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg3) == 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xCCU);
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x1DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x49U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x34U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xCDU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        temp_r30 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r31 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r31, (s32) temp_r30 / fightTrainerGetStatus(0, 0xCEU, 0x3EU, 0U)), arg0, 0xCEU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueNekodamasi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightOutPokemon_GetFightoutTurnCount(arg1) != 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0xC7U);
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x27U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xC8U);
    } else if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xC8U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xC9U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueGoddobaado(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg1, arg3) > 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0xC4U);
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
            var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xC6U);
        }
    }
    return fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0xC5U);
}

s32 fightTrainerAiWazaValueTuikaHirumi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r27;
    u8 temp_r27;
    u8 temp_r30;

    var_r27 = 0;
    if (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg1, arg3) > 0) {
        temp_r27 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r27 = fightTrainerAiAddValue(0, (s32) temp_r27 / fightTrainerGetStatus(0, 0xB8U, 0x3EU, 0U));
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xB9U);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xBAU);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 6U) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xBBU);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1CU) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xBCU);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x18U) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xBDU);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 5U) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xBEU);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xBFU);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0xAU) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xC0U);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1EU) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xC1U);
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
            temp_r30 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
            var_r27 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r27, (s32) temp_r30 / fightTrainerGetStatus(0, 0xC6U, 0x3EU, 0U)), arg0, 0xC3U);
        }
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0xC2U);
    }
    return var_r27;
}

s32 fightTrainerAiWazaValueKorogaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r31;

    var_r30 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1AU) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0xA3U);
    }
    temp_r31 = fightTrainerAiGetFightOutPokemonNowHpPercentage(arg0, arg1);
    return fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(var_r30, (s32) temp_r31 / fightTrainerGetStatus(0, 0xA4U, 0x3EU, 0U)), arg0, 0xA5U);
}

s32 fightTrainerAiWazaValueTobihaneru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    s32 var_r24;
    s32 var_r27;
    u16 temp_r28;
    u16 temp_r3;
    u16 var_r22;
    u16 var_r23;
    u8 var_r21;

    var_r24 = 0;
    temp_r28 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 0U, 1U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x83U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x84U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 6U) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x85U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 5U) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x86U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x87U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0xAU) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x88U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x18U) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x89U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1EU) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x8AU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1CU) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x8BU);
    }
    if (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg1, arg3) > 0) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x8CU);
    }
    var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x8DU);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 3U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x8FU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 4U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x90U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 6U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x91U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 5U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x92U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 9U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x93U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0xAU) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x94U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x18U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x95U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1EU) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x96U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1CU) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x97U);
    }
    var_r23 = 0;
    while (var_r23 < temp_r28) {
        temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, *(FightOutPokemon **)((u8 *)sp18 + ((var_r23 * 4) & 0x3FFFC)), sp8, 0U, 0U);
        if (temp_r3 != 0) {
            var_r21 = 0;
            var_r22 = 0;
            while (var_r22 < temp_r3) {
                if (fightTrainerAiCheckJoutaiKieWazaHitWazaDataId(arg0, 0x1F, *(u16 *)((u8 *)sp8 + ((var_r22 * 2) & 0x1FFFE))) == 1) {
                    var_r21 = 1;
                    var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x98U);
                } else {
                    var_r22 += 1;
                    continue;
                }

                break;
            }
            if (var_r21 != 1) {
                goto block_46;
            }
        } else {
block_46:
            var_r23 += 1;
            continue;
        }

        break;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1DU) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x99U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x8EU);
    }
    return var_r27;
}

s32 fightTrainerAiWazaValueSorawotobu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    u16 var_r29;
    s32 var_r26;
    u16 temp_r27;
    u16 temp_r3;
    u16 var_r22;
    u16 var_r23;
    u8 var_r21;

    var_r26 = 0;
    var_r29 = 0;
    temp_r27 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 0U, 1U);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x6EU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x6FU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 6U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x70U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 5U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x71U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x72U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0xAU) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x73U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x18U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x74U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1EU) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x75U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1CU) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x76U);
    }
    if (fightTrainerAiCmpFightOutPokemonSubayasa(arg0, arg1, arg3) > 0) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x77U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 3U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x78U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 4U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x79U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 6U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x7AU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 5U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x7BU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 9U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x7CU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0xAU) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x7DU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x18U) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x7EU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1EU) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x7FU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1CU) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x80U);
    }
    switch (arg2) {
    case 0x13:
    case 0x154:
        var_r29 = 0x1F;
        break;
    case 0x5B:
        var_r29 = 0x20;
        break;
    case 0x123:
        var_r29 = 0x21;
        break;
    }
    var_r23 = 0;
    while (var_r23 < temp_r27) {
        temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, *(FightOutPokemon **)((u8 *)sp18 + ((var_r23 * 4) & 0x3FFFC)), sp8, 0U, 0U);
        if (temp_r3 != 0) {
            var_r21 = 0;
            var_r22 = 0;
            while (var_r22 < temp_r3) {
                if (fightTrainerAiCheckJoutaiKieWazaHitWazaDataId(arg0, var_r29, *(u16 *)((u8 *)sp8 + ((var_r22 * 2) & 0x1FFFE))) == 1) {
                    var_r21 = 1;
                    var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x81U);
                } else {
                    var_r22 += 1;
                    continue;
                }

                break;
            }
            if (var_r21 != 1) {
                goto block_53;
            }
        } else {
block_53:
            var_r23 += 1;
            continue;
        }

        break;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1DU) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x82U);
    }
    return var_r26;
}

s32 fightTrainerAiWazaValueAbareru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    s32 var_r31_2;
    u16 temp_r3;

    var_r31_2 = 0;
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x14U) == 1) {
        var_r31_2 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x6AU);
    }
    temp_r3 = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, arg1);
    if ((temp_r3 == 8) || (temp_r3 == 9)) {
        var_r31_2 = fightTrainerAiAddValueByAddsubDataId(var_r31_2, arg0, 0x6BU);
    }
    var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31_2, arg0, 0x6DU);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x6CU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKyuusyuu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 temp_r31;
    s32 var_r30;
    u16 temp_r30;

    temp_r30 = fightTrainerAiGetFightOutPokemonNowHp(arg0, arg1);
    temp_r31 = fightTrainerAiWazaDoWazaDamageFunc(arg0, arg1, arg2, arg3, 1U);
    var_r30 = fightTrainerAiAddValue(0, (s32) ((s32) ((temp_r31 / 2) * 0x64) / (s32) temp_r30) / fightTrainerGetStatus(0, 0x67U, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x68U);
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x40U) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x69U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueRokettoZutuki(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x65U), arg0, 0x66U);
}

s32 fightTrainerAiWazaValueKamaitati(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r29;
    s32 var_r30;
    s32 var_r31;
    u8 temp_r3;

    var_r30 = 0;
    temp_r29 = fightTargetGetPtrAsNowFightType(2U, arg3);
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg3);
    if (temp_r3 > 6U) {
        var_r30 = fightTrainerAiAddValue(0, (temp_r3 - 6) * fightTrainerGetStatus(0, 0x62U, 0x3EU, 0U));
    }
    var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x64U);
    if (fightSideIsJoutaiDataId(temp_r29, 0x48U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x63U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKiaipanti(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 var_r25;
    s32 var_r26;
    u16 temp_r26;
    u16 var_r24;
    u16 var_r26_2;
    u8 temp_r31;

    var_r25 = 0;
    temp_r31 = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(arg0, 0, arg3, 0);
    temp_r26 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    if (fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg1) == 0x117) {
        var_r25 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x5DU);
    }
    var_r24 = 0;
    while (var_r24 < temp_r26) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r24 * 4) & 0x3FFFC)), 8U) == 1) {
            var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0x5EU);
        } else {
            var_r24 += 1;
            continue;
        }

        break;
    }
    var_r26_2 = 0;
    while (var_r26_2 < temp_r26) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_2 * 4) & 0x3FFFC)), 7U) == 1) {
            var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0x5FU);
        } else {
            var_r26_2 += 1;
            continue;
        }

        break;
    }
    var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0x61U);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x26U) == 1) && (temp_r31 != 0)) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x60U);
    }
    return var_r26;
}

s32 fightTrainerAiWazaValueAteminage(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r3;
    u8 temp_r3_2;

    var_r30 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3);
    if (temp_r3 > 6U) {
        var_r30 = fightTrainerAiAddValue(0, (temp_r3 - 6) * fightTrainerGetStatus(0, 0x5AU, 0x3EU, 0U));
    }
    temp_r3_2 = fightTrainerAiGetFightOutPokemonAbiCntAvg(arg0, arg1);
    if (temp_r3_2 < 6U) {
        var_r30 = fightTrainerAiAddValue(var_r30, (6 - temp_r3_2) * fightTrainerGetStatus(0, 0x5BU, 0x3EU, 0U));
    }
    return fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x5CU);
}

s32 fightTrainerAiWazaValueRibenji(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r3;

    var_r31 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    if ((temp_r3 != 0) && (temp_r3 != -1U) && (temp_r3 != 0x176) && (temp_r3 != 0x163) && (fightTrainerAiIsWazaTypeId(arg0, temp_r3, 1U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x58U);
    }
    return fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x59U);
}

s32 fightTrainerAiWazaValueTokubetuYuusen(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x57U);
}

s32 fightTrainerAiWazaValueKouPuraioritii(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x55U);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x56U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueSpeKuritikaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r29;
    s32 var_r30;
    u8 temp_r3;

    temp_r29 = fightTargetGetPtrAsNowFightType(2U, arg3);
    var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x51U);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x52U);
    }
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg3);
    if (temp_r3 > 6U) {
        var_r30 = fightTrainerAiAddValue(var_r30, (temp_r3 - 6) * fightTrainerGetStatus(0, 0x53U, 0x3EU, 0U));
    }
    if (fightSideIsJoutaiDataId(temp_r29, 0x49U) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x54U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValuePhyKuritikaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r29;
    s32 var_r30;
    u8 temp_r3;

    temp_r29 = fightTargetGetPtrAsNowFightType(2U, arg3);
    var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x4DU);
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x4EU);
    }
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg3);
    if (temp_r3 > 6U) {
        var_r30 = fightTrainerAiAddValue(var_r30, (temp_r3 - 6) * fightTrainerGetStatus(0, 0x4FU, 0x3EU, 0U));
    }
    if (fightSideIsJoutaiDataId(temp_r29, 0x48U) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x50U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueHittyuu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r3;
    u8 temp_r3_2;

    var_r30 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3);
    if (temp_r3 > 6U) {
        var_r30 = fightTrainerAiAddValue(0, (temp_r3 - 6) * fightTrainerGetStatus(0, 0x4AU, 0x3EU, 0U));
    }
    temp_r3_2 = fightTrainerAiGetFightOutPokemonAbiCntAvg(arg0, arg1);
    if (temp_r3_2 < 6U) {
        var_r30 = fightTrainerAiAddValue(var_r30, (6 - temp_r3_2) * fightTrainerGetStatus(0, 0x4BU, 0x3EU, 0U));
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x4CU);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueTuujouIryoku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x49U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueNull(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    return 0;
}






u32 fightOutPokemonMaxHpWaruValue(FightOutPokemon *, u16);
u32 fightOutPokemonNowHpWaruValue(FightOutPokemon *, u16);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER *);
s32 fightTrainerAiDB_GetWazaAvgValue(u16);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(void *, FIGHT_TRAINER *, FightPokemon **, u8, u8);
Pokemon *fightPokemonGetPokemonPtr(FightPokemon *);
u16 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiIsFightPokemonJoutaiNormal(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiIsFightPokemonJoutaiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
FightPokemon *fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon *);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon *);
s16 fightSideGetCountAsJoutaiDataId(FightSide *, u16);
u16 fightTrainerAiCheckOumu(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon *, u8);
FIGHT_TRAINER *fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void *, FightOutPokemon *);
FightPokemon *fightTrainerSearchIrekaeFightPokemon(FIGHT_TRAINER *, u16 *);
u16 tikeiDataBiosGetFightKoukaId(u32);
u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER *, FightOutPokemon *, u16);
Pokemon *fightOutPokemonGetPokemonPtr(FightOutPokemon *);
u8 pokemonIsDarkPokemon(Pokemon *);
u8 wazaCheckDarkWaza(u16);
FightPokemon *getFightPokemonPtr__15FightOutPokemonFv(FightOutPokemon *);
u8 _fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(FIGHT_TRAINER *, FightOutPokemon *, u8, u8);
u8 _fightTrainerAiWazaValueIsFightOutPokemonNeoki__FP13FIGHT_TRAINERP15FightOutPokemon(FIGHT_TRAINER *, FightOutPokemon *);
u8 _fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(FIGHT_TRAINER *, FightOutPokemon **, u16, u8, u8);
u8 _fightTrainerAiWazaValueIsAllyHaveWazaDataId__FP13FIGHT_TRAINERP15FightOutPokemonUs(FIGHT_TRAINER *, FightOutPokemon *, u16);

s32 fightTrainerAiWazaValueDarkMist(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    s32 temp_r24;
    s32 var_r23;
    u16 temp_r26;
    u16 temp_r3;
    u16 var_r21;
    u16 var_r22;
    u8 var_r20;

    var_r23 = 0;
    temp_r26 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 1U, 1U);
    temp_r24 = fightTrainerAiDB_GetWazaAvgValue(fightTrainer_GetFightTrainerDataId(arg0));
    var_r20 = 0;
    var_r22 = 0;
    while (var_r22 < temp_r26) {
        temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, *(FightOutPokemon **)((u8 *)sp18 + ((var_r22 * 4) & 0x3FFFC)), sp8, 0U, 1U);
        if (temp_r3 != 0) {
            var_r21 = 0;
            while (var_r21 < temp_r3) {
                if (wazaDB_GetAvg(*(u16 *)((u8 *)sp8 + ((var_r21 * 2) & 0x1FFFE))) < (u8) temp_r24) {
                    var_r20 = 1;
                } else {
                    var_r21 += 1;
                    continue;
                }

                break;
            }
        }
        var_r22 += 1;
        continue;

        break;
    }
    if (var_r20 != 0) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x282U);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3) <= 5U) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x283U);
    }
    return var_r23;
}

s32 fightTrainerAiWazaValueDarkHalf(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp28[8];
    FightOutPokemon *sp8[8];
    s32 temp_r26;
    s32 temp_r28;
    s32 var_r23;
    u16 temp_r24;
    u16 temp_r25;
    u16 var_r22_2;
    u16 var_r31;
    u32 temp_r27;
    u32 temp_r27_2;
    u8 var_r22;
    u8 var_r25;

    temp_r25 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp28, 1U, 1U);
    temp_r24 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    var_r31 = 0;
    var_r22 = 0;
    while ((s32) var_r22 < (s32) temp_r24) {
        temp_r28 = (var_r22 * 4) & 0x3FC;
        temp_r27 = fightOutPokemonMaxHpWaruValue(*(FightOutPokemon **)((u8 *)sp8 + temp_r28), 1U);
        var_r22 += 1;
        var_r31 += (s32) ((u16) temp_r27 * fightOutPokemonNowHpWaruValue(*(FightOutPokemon **)((u8 *)sp8 + temp_r28), 2U)) / 100;
        continue;

        break;
    }
    var_r22_2 = 0;
    var_r25 = 0;
    while ((s32) var_r25 < (s32) temp_r25) {
        temp_r26 = (var_r25 * 4) & 0x3FC;
        temp_r27_2 = fightOutPokemonMaxHpWaruValue(*(FightOutPokemon **)((u8 *)sp28 + temp_r26), 1U);
        var_r25 += 1;
        var_r22_2 += (s32) ((u16) temp_r27_2 * fightOutPokemonNowHpWaruValue(*(FightOutPokemon **)((u8 *)sp28 + temp_r26), 2U)) / 100;
        continue;

        break;
    }
    var_r23 = fightTrainerAiAddValueByAddsubDataId(fightTrainerAiAddValue(0, (((s32) var_r31 / (s32) var_r22_2) - 1) * fightTrainerGetStatus(0, 0x27FU, 0x3EU, 0U)), arg0, 0x280U);
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3) <= 5U) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x281U);
    }
    return var_r23;
}

s32 fightTrainerAiWazaValueDarkEnd(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r28;
    u16 temp_r27;
    u16 temp_r28;
    u32 temp_r29;
    u32 temp_r29_2;

    temp_r29 = fightOutPokemonMaxHpWaruValue(arg3, 1U);
    temp_r27 = (u16) ((s32) ((u16) temp_r29 * fightTrainerAiWazaDoWazaDamageFunc(arg0, arg1, arg2, arg3, 1U)) / 100);
    temp_r29_2 = fightOutPokemonMaxHpWaruValue(arg1, 1U);
    temp_r28 = fightOutPokemonNowHpWaruValue(arg1, 2U);
    var_r28 = fightTrainerAiAddValue(0, (((s32) temp_r27 / (s32) (u16) ((s32) ((u16) temp_r29_2 * temp_r28) / 100)) - 1) * fightTrainerGetStatus(0, 0x27DU, 0x3EU, 0U));
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3) <= 5U) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x27EU);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueDarkWeather(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp8[8];
    s32 var_r30;
    u16 temp_r26;
    u16 var_r25;
    u16 var_r26;
    u8 temp_r31;

    var_r30 = 0;
    temp_r31 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 0U);
    temp_r26 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    if (temp_r31 != 5) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x19AU);
    }
    var_r25 = 0;
    while (var_r25 < temp_r26) {
        if (pokemonIsDarkPokemon(fightPokemonGetPokemonPtr(*(FightPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FFFC)))) == 1) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x19BU);
        } else {
            var_r25 += 1;
            continue;
        }

        break;
    }
    var_r26 = 0;
    while (var_r26 < temp_r26) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(arg0, *(FightPokemon **)((u8 *)sp8 + ((var_r26 * 4) & 0x3FFFC))) == 0x181) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x19CU);
        } else {
            var_r26 += 1;
            continue;
        }

        break;
    }
    if (temp_r31 == 5) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x19DU);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x16FU, 0) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x19EU);
    }
    return var_r30;
}

u8 _fightTrainerAiWazaValueIsAllyHaveWazaDataId__FP13FIGHT_TRAINERP15FightOutPokemonUs(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    FightOutPokemon *temp_r4;
    u16 temp_r31;
    u16 temp_r3;
    u16 var_r29;
    u16 var_r6;

    temp_r31 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 1U, 1U);
    var_r29 = 0;
loop_9:
    if (var_r29 >= temp_r31) {
        return 0U;
    }
    temp_r4 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r29 * 4) & 0x3FFFC));
    if (arg1 != temp_r4) {
        temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r4, sp8, 0U, 1U);
        if (temp_r3 != 0) {
            var_r6 = 0;
loop_7:
            if (var_r6 >= temp_r3) {
                goto block_8;
            }
            if (arg2 == (u16) *(u16 *)((u8 *)sp8 + ((var_r6 * 2) & 0x1FFFE))) {
                return 1U;
            }
            var_r6 += 1;
            goto loop_7;
        }
    }
block_8:
    var_r29 += 1;
    goto loop_9;
}

s32 fightTrainerAiWazaValueNemuriKoudou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 8U) == 1) {
        if (_fightTrainerAiWazaValueIsFightOutPokemonNeoki__FP13FIGHT_TRAINERP15FightOutPokemon(arg0, arg1) == 0) {
            var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x218U);
        }
        if (_fightTrainerAiWazaValueIsFightOutPokemonNeoki__FP13FIGHT_TRAINERP15FightOutPokemon(arg0, arg1) == 1) {
            var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x219U);
        }
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueSawagu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;
    s32 var_r29;
    u16 temp_r24;
    u16 temp_r30;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 var_r23;
    u16 var_r30;
    u16 var_r31;

    var_r29 = 0;
    temp_r3 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 1U, 1U);
    temp_r30 = temp_r3;
    temp_r24 = temp_r3;
    var_r31 = 0;
    while (var_r31 < temp_r24) {
        temp_r4 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r31 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4) && (_fightTrainerAiWazaValueIsFightOutPokemonNeoki__FP13FIGHT_TRAINERP15FightOutPokemon(arg0, temp_r4) == 0)) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x211U);
        } else {
            var_r31 += 1;
            continue;
        }

        break;
    }
    var_r30 = 0;
    while (var_r30 < temp_r30) {
        temp_r4_2 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r30 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_2) && (temp_r3_2 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r4_2, sp8, 0U, 1U), ((temp_r3_2 == 0) == 0))) {
            var_r23 = 0;
            while (var_r23 < temp_r3_2) {
                if ((u16) *(u16 *)((u8 *)sp8 + ((var_r23 * 2) & 0x1FFFE)) == 0x9C) {
                    var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x212U);
                } else {
                    var_r23 += 1;
                    continue;
                }

                break;
            }
            if (var_r23 >= temp_r3_2) {
                goto block_15;
            }
        } else {
block_15:
            var_r30 += 1;
            continue;
        }

        break;
    }
    if (_fightTrainerAiWazaValueIsFightOutPokemonNeoki__FP13FIGHT_TRAINERP15FightOutPokemon(arg0, arg3) == 0) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x213U);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueOomugaesi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 temp_r3;

    temp_r3 = fightTrainerAiCheckOumu(arg0, arg1);
    if ((temp_r3 != arg2) && (temp_r3 != 0)) {
        return fightTrainerAiWazaDoWazaValueFunc(arg0, arg1, temp_r3, arg3);
    }
    return 0;
}

s32 fightTrainerAiWazaValueMakibisi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r3;
    s16 var_r3;
    s32 var_r31;

    var_r31 = 0;
    temp_r3 = fightTargetGetPtrAsNowFightType(2U, arg3);
    if (fightSideIsJoutaiDataId(temp_r3, 0x4AU) == 1) {
        var_r3 = fightSideGetCountAsJoutaiDataId(temp_r3, 0x4AU);
    } else {
        var_r3 = 0;
    }
    switch (var_r3) {
    case 0:
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x209U);
        break;
    case 1:
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x20AU);
        break;
    case 2:
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x20BU);
        break;
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueJikoanji(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (_fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(arg0, arg3, 8U, 9U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x203U);
    }
    if (_fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(arg0, arg3, 0xAU, 0xCU) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x204U);
    }
    if (_fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(arg0, arg3, 3U, 4U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x205U);
    }
    if (_fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(arg0, arg3, 0U, 2U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x206U);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKuroikiri(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp28[8];
    FightOutPokemon *sp8[8];
    s32 var_r29;
    u16 temp_r28;
    u16 temp_r3;

    var_r29 = 0;
    temp_r28 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp28, 1U, 1U);
    temp_r3 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(arg0, sp8, temp_r3, 8U, 9U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1FBU);
    }
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(arg0, sp28, temp_r28, 3U, 4U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1FCU);
    }
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(arg0, sp8, temp_r3, 0xAU, 0xCU) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1FDU);
    }
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(arg0, sp28, temp_r28, 0U, 2U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1FEU);
    }
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(arg0, sp28, temp_r28, 8U, 9U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x1FFU);
    }
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(arg0, sp8, temp_r3, 3U, 4U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x200U);
    }
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(arg0, sp28, temp_r28, 0xAU, 0xCU) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x201U);
    }
    if (_fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(arg0, sp8, temp_r3, 0U, 2U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x202U);
    }
    return var_r29;
}

u8 _fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, u8 arg3, u8 arg4) {
    u16 var_r30;

    var_r30 = 0;
loop_4:
    if (var_r30 >= arg2) {
        return 0U;
    }
    if (_fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(arg0, *(arg1 + ((var_r30 * 4) & 0x3FFFC)), arg3, arg4) == 1) {
        return 1U;
    }
    var_r30 += 1;
    goto loop_4;
}

u8 _fightTrainerAiWazaValueIsFightOutPokemonNeoki__FP13FIGHT_TRAINERP15FightOutPokemon(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    s8 temp_r31;
    u8 temp_r5;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 8U) == 0) {
        return -1U;
    }
    temp_r5 = fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x30U) == 1;
    temp_r31 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg1, 8U, temp_r5) + (temp_r5 + 1);
    if (temp_r31 >= fightOutPokemonGetKaisuuJoutaiDataId(arg1, 8U)) {
        return 1U;
    }
    return 0U;
}

s32 fightTrainerAiWazaValueKyouseikoutai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightSide *temp_r3;
    s16 var_r31;
    s32 var_r30;

    var_r30 = 0;
    temp_r3 = fightTargetGetPtrAsNowFightType(2U, arg3);
    if (fightSideIsJoutaiDataId(temp_r3, 0x4AU) == 1) {
        var_r31 = fightSideGetCountAsJoutaiDataId(temp_r3, 0x4AU);
    } else {
        var_r31 = 0;
    }
    if (_fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(arg0, arg3, 8U, 0xCU) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1F1U);
    }
    switch (var_r31) {
    case 1:
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1F2U);
        break;
    case 2:
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1F3U);
        break;
    case 3:
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1F4U);
        break;
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueMitizure(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.1f, -1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1DFU);
    } else if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.3f, -1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1DEU);
    } else if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.5f, -1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1DDU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueIkarinomaeba(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg3, 0.5f, 1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1CFU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKaihiDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    s32 temp_r25;
    s32 var_r24;
    u16 temp_r27;
    u16 temp_r3;
    u16 var_r22;
    u16 var_r23;
    u8 var_r21;

    var_r24 = 0;
    temp_r27 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 1U, 1U);
    temp_r25 = fightTrainerAiDB_GetWazaAvgValue(fightTrainer_GetFightTrainerDataId(arg0));
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3) >= 7U) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1CAU);
    }
    if (fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg3) <= 5U) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x1CBU);
    }
    var_r21 = 0;
    var_r23 = 0;
    while (var_r23 < temp_r27) {
        temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, *(FightOutPokemon **)((u8 *)sp18 + ((var_r23 * 4) & 0x3FFFC)), sp8, 0U, 1U);
        if (temp_r3 != 0) {
            var_r22 = 0;
            while (var_r22 < temp_r3) {
                if (wazaDB_GetAvg(*(u16 *)((u8 *)sp8 + ((var_r22 * 2) & 0x1FFFE))) < (u8) temp_r25) {
                    var_r21 = 1;
                } else {
                    var_r22 += 1;
                    continue;
                }

                break;
            }
        }
        var_r23 += 1;
        continue;

        break;
    }
    if (var_r21 != 0) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x1C9U);
    }
    return var_r24;
}

s32 fightTrainerAiWazaValueBougyoDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 temp_r28;
    s32 var_r30;
    u16 temp_r31;
    u16 temp_r3;
    u16 var_r26;
    u16 var_r28;
    u8 var_r24;
    u8 var_r25;
    u8 var_r26_2;
    u8 var_r27;

    var_r30 = 0;
    temp_r31 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    var_r24 = 0;
    var_r25 = 0;
    while ((s32) var_r25 < (s32) temp_r31) {
        temp_r28 = (var_r25 * 4) & 0x3FC;
        var_r26 = fightTrainerAiGetFightOutPokemonPhyDef(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r28));
        temp_r3 = fightTrainerAiGetFightOutPokemonSpeDef(arg0, *(FightOutPokemon **)((u8 *)sp8 + temp_r28));
        var_r28 = temp_r3;
        if (var_r26 > temp_r3) {
            var_r24 = var_r24 + 1;
        }
        var_r25 += 1;
        continue;

        break;
    }
    if (var_r26 > var_r28) {
        var_r30 = fightTrainerAiAddValue(0, var_r24 * fightTrainerGetStatus(0, 0x1C4U, 0x3EU, 0U));
    }
    var_r27 = 0;
    var_r26_2 = 0;
    while ((s32) var_r26_2 < (s32) temp_r31) {
        if (fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r26_2 * 4) & 0x3FC))) <= 4U) {
            var_r27 = var_r27 + 1;
        }
        var_r26_2 += 1;
        continue;

        break;
    }
    return fightTrainerAiAddValue(var_r30, var_r27 * fightTrainerGetStatus(0, 0x1C5U, 0x3EU, 0U));
}

s32 fightTrainerAiWazaValueRokkuon(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u32 temp_r31;

    var_r30 = 0;
    temp_r31 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(arg1, fightFloor_GetFightType(0));
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1DU) == 0) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1B8U);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1DU) == 1) && ((u16) temp_r31 == fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg3, 0x1DU))) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1B9U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueNoroi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r3;

    var_r30 = 0;
    temp_r3 = fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg1, 7U);
    if ((temp_r3 == 1) && (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.5f, 1) == 1)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1B3U);
    } else if ((temp_r3 == 1) && (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.25f, -1) == 1)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1B4U);
    }
    if ((temp_r3 == 0) && (fightTrainerAiIsFightOutPokemonAllAbiCntTakai(arg0, arg1) == 0)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1B5U);
    }
    if (temp_r3 == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1B6U);
    }
    if ((temp_r3 == 0) && (fightTrainerAiIsFightOutPokemonAllAbiCntTakai(arg0, arg1) == 1)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1B7U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueAroma(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp8[8];
    s32 var_r29;
    u16 temp_r31;
    u16 var_r28;

    var_r29 = 0;
    temp_r31 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    var_r28 = 0;
    while (var_r28 < temp_r31) {
        if (fightTrainerAiIsFightPokemonJoutaiNormal(arg0, *(FightPokemon **)((u8 *)sp8 + ((var_r28 * 4) & 0x3FFFC))) == 0) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1A0U);
        } else {
            var_r28 += 1;
            continue;
        }

        break;
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueSunaarasi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp28[8];
    FightOutPokemon *sp8[8];
    s32 temp_r27;
    s32 var_r29;
    u16 temp_r25;
    u16 temp_r31;
    u16 var_r23;
    u16 var_r24;
    u16 var_r24_2;
    u8 temp_r30;

    var_r29 = 0;
    temp_r30 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 0U);
    temp_r31 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp28, 1U, 1U);
    temp_r25 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    if (temp_r30 != 3) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x194U);
    }
    var_r23 = 0;
    while (var_r23 < temp_r31) {
        temp_r27 = (var_r23 * 4) & 0x3FFFC;
        if ((fightTrainerAiIsFightPokemonZokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp28 + temp_r27), 5U) == 1) || (fightTrainerAiIsFightPokemonZokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp28 + temp_r27), 4U) == 1) || (fightTrainerAiIsFightPokemonZokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp28 + temp_r27), 8U) == 1) || (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp28 + temp_r27), 8U) == 1)) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x195U);
        } else {
            var_r23 += 1;
            continue;
        }

        break;
    }
    var_r24 = 0;
    while (var_r24 < temp_r25) {
        if (fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r24 * 4) & 0x3FFFC))) == 0x12F) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x196U);
        } else {
            var_r24 += 1;
            continue;
        }

        break;
    }
    var_r24_2 = 0;
    while (var_r24_2 < temp_r31) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(arg0, *(FightPokemon **)((u8 *)sp28 + ((var_r24_2 * 4) & 0x3FFFC))) == 0x181) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x197U);
        } else {
            var_r24_2 += 1;
            continue;
        }

        break;
    }
    if (temp_r30 == 3) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x198U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xF1U, 0) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x199U);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueArare(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp28[8];
    FightOutPokemon *sp8[8];
    s32 var_r29;
    u16 temp_r25;
    u16 temp_r31;
    u16 var_r24;
    u16 var_r25;
    u16 var_r25_2;
    u8 temp_r30;

    var_r29 = 0;
    temp_r30 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 0U);
    temp_r31 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp28, 1U, 1U);
    temp_r25 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    if (temp_r30 != 4) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x18EU);
    }
    var_r24 = 0;
    while (var_r24 < temp_r31) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp28 + ((var_r24 * 4) & 0x3FFFC)), 0xFU) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x18FU);
        } else {
            var_r24 += 1;
            continue;
        }

        break;
    }
    var_r25 = 0;
    while (var_r25 < temp_r25) {
        if (fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FFFC))) == 0x12F) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x190U);
        } else {
            var_r25 += 1;
            continue;
        }

        break;
    }
    var_r25_2 = 0;
    while (var_r25_2 < temp_r31) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(arg0, *(FightPokemon **)((u8 *)sp28 + ((var_r25_2 * 4) & 0x3FFFC))) == 0x181) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x191U);
        } else {
            var_r25_2 += 1;
            continue;
        }

        break;
    }
    if (temp_r30 == 4) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x192U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xF1U, 0) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x193U);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueNihonbare(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp8[8];
    s32 temp_r28;
    s32 var_r30;
    u16 temp_r26;
    u16 var_r24;
    u16 var_r25;
    u8 temp_r31;

    var_r30 = 0;
    temp_r31 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 0U);
    temp_r26 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    if (temp_r31 != 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x189U);
    }
    var_r24 = 0;
    while (var_r24 < temp_r26) {
        temp_r28 = (var_r24 * 4) & 0x3FFFC;
        if ((fightTrainerAiIsFightPokemonZokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp8 + temp_r28), 0xAU) == 1) || (fightTrainerAiIsFightPokemonZokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp8 + temp_r28), 0xCU) == 1) || (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp8 + temp_r28), 0x22U) == 1)) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x18AU);
        } else {
            var_r24 += 1;
            continue;
        }

        break;
    }
    var_r25 = 0;
    while (var_r25 < temp_r26) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(arg0, *(FightPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FFFC))) == 0x181) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x18BU);
        } else {
            var_r25 += 1;
            continue;
        }

        break;
    }
    if (temp_r31 == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x18CU);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xF1U, 0) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x18DU);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueAmagoi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp8[8];
    s32 temp_r28;
    s32 var_r30;
    u16 temp_r26;
    u16 var_r24;
    u16 var_r25;
    u8 temp_r31;

    var_r30 = 0;
    temp_r31 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 0U);
    temp_r26 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    if (temp_r31 != 2) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x184U);
    }
    var_r24 = 0;
    while (var_r24 < temp_r26) {
        temp_r28 = (var_r24 * 4) & 0x3FFFC;
        if ((fightTrainerAiIsFightPokemonZokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp8 + temp_r28), 0xBU) == 1) || (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp8 + temp_r28), 0x21U) == 1) || (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, *(FightPokemon **)((u8 *)sp8 + temp_r28), 0x2CU) == 1)) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x185U);
        } else {
            var_r24 += 1;
            continue;
        }

        break;
    }
    var_r25 = 0;
    while (var_r25 < temp_r26) {
        if (fightTrainerAiGetFightPokemonPokemonDataId(arg0, *(FightPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FFFC))) == 0x181) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x186U);
        } else {
            var_r25 += 1;
            continue;
        }

        break;
    }
    if (temp_r31 == 2) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x187U);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueNemuru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u16 temp_r3;

    var_r31 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, arg1);
    if ((temp_r3 == 3) || (temp_r3 == 9)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x17DU);
    }
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.55f, -1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x17EU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg1) == 0) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x17FU);
    }
    return fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x180U);
}

s32 fightTrainerAiWazaValueKaihuku2(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;

    var_r31 = 0;
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.5f, -1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x17CU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueKaihuku1(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 temp_r3;

    var_r30 = 0;
    temp_r3 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    if (temp_r3 == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x179U);
    }
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.5f, -1) == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x17AU);
    }
    if ((temp_r3 == 2) || (temp_r3 == 4) || (temp_r3 == 3)) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x17BU);
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueOiuti(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8;
    FIGHT_TRAINER *temp_r3;
    s32 var_r28;
    u8 var_r31;

    var_r28 = 0;
    var_r31 = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(arg0, 0, arg3, 0);
    temp_r3 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, arg3);
    sp8 = 0;
    if (fightTrainerSearchIrekaeFightPokemon(temp_r3, &sp8) == 0) {
        var_r31 = 1;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x16DU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x16EU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 6U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x16FU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1CU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x170U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x171U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0xAU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x172U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x18U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x173U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1EU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x174U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x26U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x175U);
    }
    if (var_r31 != 0) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x176U);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueTuikaNemuri(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp8[8];
    FightPokemon *temp_r4;
    s32 var_r26;
    u16 temp_r28;
    u16 var_r25;
    u8 temp_r26;
    u8 temp_r27;
    u8 temp_r27_2;

    temp_r28 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    temp_r26 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
    var_r26 = fightTrainerAiAddValue(0, (s32) temp_r26 / fightTrainerGetStatus(0, 0x12FU, 0x3EU, 0U));
    var_r25 = 0;
    while (var_r25 < temp_r28) {
        temp_r4 = *(FightPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FFFC));
        if ((fightOutPokemon_GetMotoFightPokemonPtr(arg3) != temp_r4) && (fightTrainerAiIsFightPokemonJoutaiDataId(arg0, temp_r4, 8U) == 1)) {
            temp_r27 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
            var_r26 = fightTrainerAiAddValue(var_r26, (s32) temp_r27 / fightTrainerGetStatus(0, 0x130U, 0x3EU, 0U));
        } else {
            var_r25 += 1;
            continue;
        }

        break;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0xFU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1)) {
        temp_r27_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r26 = fightTrainerAiAddValue(var_r26, (s32) temp_r27_2 / fightTrainerGetStatus(0, 0x131U, 0x3EU, 0U));
    }
    return var_r26;
}

s32 fightTrainerAiWazaValueBakuretuPanti(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    s32 var_r31;
    u32 temp_r31;

    var_r30 = 0;
    temp_r31 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(arg1, fightFloor_GetFightType(0));
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1DU) == 1) && ((u16) temp_r31 == fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg3, 0x1DU))) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x12AU);
    }
    var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x12BU);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x14U) == 1)) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x12DU);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x12CU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x12EU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueDenjihou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 var_r29;
    u32 temp_r30;

    temp_r30 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(arg1, fightFloor_GetFightType(0));
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 1U, 1U);
    var_r29 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x125U);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1DU) == 1) && ((u16) temp_r30 == fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg3, 0x1DU))) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x126U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x127U);
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 7U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1)) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x128U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x14U) == 1) {
        var_r29 = fightTrainerAiAddValueByAddsubDataId(var_r29, arg0, 0x129U);
    }
    return var_r29;
}

s32 fightTrainerAiWazaValueTuikaKoori(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp28[8];
    FightOutPokemon *sp8[8];
    FightPokemon *temp_r4;
    s32 var_r24;
    s32 var_r28;
    u16 temp_r29;
    u16 temp_r30;
    u16 var_r23;
    u16 var_r26;
    u16 var_r27;
    u16 var_r30;
    u8 temp_r24;
    u8 temp_r24_2;
    u8 var_r22;
    u8 var_r24_2;

    temp_r29 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    temp_r30 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp28, 0U, 1U);
    var_r22 = 0;
    var_r23 = 0;
    while (var_r23 < temp_r29) {
        if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r23 * 4) & 0x3FFFC))) == 1) {
            var_r22 = var_r22 + 1;
        }
        var_r23 += 1;
        continue;

        break;
    }
    var_r28 = fightTrainerAiAddValue(0, var_r22 * fightTrainerGetStatus(0, 0x11CU, 0x3EU, 0U));
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x11DU);
    }
    var_r30 = 0;
    while (var_r30 < temp_r30) {
        temp_r4 = *(FightPokemon **)((u8 *)sp28 + ((var_r30 * 4) & 0x3FFFC));
        if ((fightOutPokemon_GetMotoFightPokemonPtr(arg3) != temp_r4) && (fightTrainerAiIsFightPokemonJoutaiDataId(arg0, temp_r4, 7U) == 1)) {
            temp_r24 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
            var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r24 / fightTrainerGetStatus(0, 0x11EU, 0x3EU, 0U));
        } else {
            var_r30 += 1;
            continue;
        }

        break;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x28U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1)) {
        temp_r24_2 = fightTrainerAiGetWazaAddKoukaAvg(arg0, arg2);
        var_r28 = fightTrainerAiAddValue(var_r28, (s32) temp_r24_2 / fightTrainerGetStatus(0, 0x11FU, 0x3EU, 0U));
    }
    var_r24_2 = 0;
    var_r26 = 0;
    while (var_r26 < temp_r29) {
        if ((fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 0) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x28U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x13U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3, 0xFU) == 1)) {
            var_r24_2 += 1;
        }
        var_r26 += 1;
        continue;

        break;
    }
    var_r24 = fightTrainerAiAddValue(var_r28, var_r24_2 * fightTrainerGetStatus(0, 0x11FU, 0x3EU, 0U));
    var_r27 = 0;
    while (var_r27 < temp_r29) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r27 * 4) & 0x3FFFC)), 0x14U) == 1) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x120U);
        }
        var_r27 += 1;
        continue;

        break;
    }
    return var_r24;
}

s32 fightTrainerAiWazaValueHonoonouzu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8;
    FIGHT_TRAINER *temp_r3;
    s32 var_r28;
    u8 var_r31;

    var_r28 = 0;
    var_r31 = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(arg0, 0, arg3, 0);
    temp_r3 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, arg3);
    sp8 = 0;
    if (fightTrainerSearchIrekaeFightPokemon(temp_r3, &sp8) == 0) {
        var_r31 = 1;
    }
    if (var_r31 == 0) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x104U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x105U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x106U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 6U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x107U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1CU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x108U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x109U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0xAU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x10AU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x18U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x10BU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1EU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x10CU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 7U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x10DU);
    }
    if (var_r31 != 0) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0x10EU);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueJisin(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp58[8];
    FightOutPokemon *sp38[8];
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;
    FightOutPokemon *temp_r4_3;
    FightOutPokemon *temp_r4_4;
    s32 temp_r24;
    s32 temp_r24_2;
    s32 temp_r27;
    s32 var_r25;
    u16 temp_r0;
    u16 temp_r26;
    u16 temp_r27_2;
    u16 temp_r29;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 var_r22;
    u16 var_r22_2;
    u16 var_r22_3;
    u16 var_r23;
    u16 var_r23_2;
    u16 var_r24;
    u16 var_r26;

    var_r25 = 0;
    temp_r26 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp58, 1U, 1U);
    temp_r29 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp38, 1U, 1U);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 0U, 1U);
    var_r22 = 0;
    while (var_r22 < temp_r29) {
        temp_r24 = (var_r22 * 4) & 0x3FFFC;
        if ((arg1 != *(FightOutPokemon **)((u8 *)sp38 + temp_r24)) && (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp38 + temp_r24), temp_r26, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43)) {
            var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB0U);
        }
        var_r22 += 1;
        continue;

        break;
    }
    var_r22_2 = 0;
    while (var_r22_2 < temp_r29) {
        temp_r24_2 = (var_r22_2 * 4) & 0x3FFFC;
        if ((arg1 != *(FightOutPokemon **)((u8 *)sp38 + temp_r24_2)) && (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp38 + temp_r24_2), temp_r26, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x42)) {
            var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB1U);
        }
        var_r22_2 += 1;
        continue;

        break;
    }
    var_r26 = 0;
    while (var_r26 < temp_r29) {
        temp_r4 = *(FightOutPokemon **)((u8 *)sp38 + ((var_r26 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4) && (temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r4, sp8, 0U, 1U), ((temp_r3 == 0) == 0))) {
            var_r22_3 = 0;
            while (var_r22_3 < temp_r3) {
                temp_r0 = *(u16 *)((u8 *)sp8 + ((var_r22_3 * 2) & 0x1FFFE));
                if ((temp_r0 == 0xB6) || (temp_r0 == 0xC5) || (temp_r0 == 0xCB)) {
                    var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB2U);
                } else {
                    var_r22_3 += 1;
                    continue;
                }

                break;
            }
            if (var_r22_3 >= temp_r3) {
                goto block_23;
            }
        } else {
block_23:
            var_r26 += 1;
            continue;
        }

        break;
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xB6U, 0) == 1) {
        var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB3U);
    } else if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xC5U, 0) == 1) {
        var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB3U);
    } else if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xCBU, 0) == 1) {
        var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB3U);
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0x10EU, arg1) == 1) {
        var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB4U);
    }
    var_r23 = 0;
    while (var_r23 < temp_r29) {
        temp_r4_2 = *(FightOutPokemon **)((u8 *)sp38 + ((var_r23 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_2) && ((temp_r3_2 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, temp_r4_2), ((temp_r3_2 == 0xB6) != 0)) || (temp_r3_2 == 0xC5) || (temp_r3_2 == 0xCB))) {
            var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB6U);
        }
        var_r23 += 1;
        continue;

        break;
    }
    var_r24 = 0;
    while (var_r24 < temp_r29) {
        temp_r27 = (var_r24 * 4) & 0x3FFFC;
        temp_r4_3 = *(FightOutPokemon **)((u8 *)sp38 + temp_r27);
        if (arg1 != temp_r4_3) {
            temp_r27_2 = fightTrainerAiGetFightOutPokemonNowHp(arg0, temp_r4_3);
            if ((s32) temp_r27_2 <= fightTrainerAiWazaDoWazaDamageFunc(arg0, arg1, arg2, *(FightOutPokemon **)((u8 *)sp38 + temp_r27), 0U)) {
                var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB7U);
            }
        }
        var_r24 += 1;
        continue;

        break;
    }
    var_r23_2 = 0;
    while (var_r23_2 < temp_r29) {
        temp_r4_4 = *(FightOutPokemon **)((u8 *)sp38 + ((var_r23_2 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_4) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4_4, 0x14U) == 1)) {
            var_r25 = fightTrainerAiAddValueByAddsubDataId(var_r25, arg0, 0xB5U);
        }
        var_r23_2 += 1;
        continue;

        break;
    }
    return var_r25;
}

s32 fightTrainerAiWazaValueSokubaku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8;
    FIGHT_TRAINER *temp_r3;
    s32 var_r28;
    u8 var_r31;

    var_r28 = 0;
    var_r31 = fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(arg0, 0, arg3, 0);
    temp_r3 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, arg3);
    sp8 = 0;
    if (fightTrainerSearchIrekaeFightPokemon(temp_r3, &sp8) == 0) {
        var_r31 = 1;
    }
    if (var_r31 == 0) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0xA6U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 3U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xA7U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 4U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xA8U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 6U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xA9U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xABU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0xAU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xACU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x18U) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xADU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1EU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xAEU);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 0x1CU) == 1) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xAAU);
    }
    if (var_r31 != 0) {
        var_r28 = fightTrainerAiAddValueByAddsubDataId(var_r28, arg0, 0xAFU);
    }
    return var_r28;
}

s32 fightTrainerAiWazaValueJibaku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp58[8];
    FightOutPokemon *sp38[8];
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;
    FightOutPokemon *temp_r4_3;
    FightOutPokemon *temp_r4_4;
    s32 temp_r0_2;
    s32 temp_r23;
    s32 temp_r23_2;
    s32 temp_r26_2;
    s32 var_r24;
    u16 temp_r0;
    u16 temp_r25;
    u16 temp_r26;
    u16 temp_r26_3;
    u16 temp_r29;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 var_r21;
    u16 var_r21_2;
    u16 var_r21_3;
    u16 var_r22;
    u16 var_r22_2;
    u16 var_r22_3;
    u16 var_r23;
    u16 var_r25;

    var_r24 = 0;
    temp_r25 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp58, 1U, 1U);
    temp_r29 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp38, 1U, 1U);
    temp_r26 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 0U, 1U);
    var_r21 = 0;
    while (var_r21 < temp_r29) {
        temp_r23 = (var_r21 * 4) & 0x3FFFC;
        if ((arg1 != *(FightOutPokemon **)((u8 *)sp38 + temp_r23)) && (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp38 + temp_r23), temp_r25, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x43)) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x9AU);
        }
        var_r21 += 1;
        continue;

        break;
    }
    var_r21_2 = 0;
    while (var_r21_2 < temp_r29) {
        temp_r23_2 = (var_r21_2 * 4) & 0x3FFFC;
        if ((arg1 != *(FightOutPokemon **)((u8 *)sp38 + temp_r23_2)) && (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp38 + temp_r23_2), temp_r25, fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x42)) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x9BU);
        }
        var_r21_2 += 1;
        continue;

        break;
    }
    var_r25 = 0;
    while (var_r25 < temp_r29) {
        temp_r4 = *(FightOutPokemon **)((u8 *)sp38 + ((var_r25 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4) && (temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r4, sp8, 0U, 1U), ((temp_r3 == 0) == 0))) {
            var_r21_3 = 0;
            while (var_r21_3 < temp_r3) {
                temp_r0 = *(u16 *)((u8 *)sp8 + ((var_r21_3 * 2) & 0x1FFFE));
                if ((temp_r0 == 0xB6) || (temp_r0 == 0xC5) || (temp_r0 == 0xCB)) {
                    var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x9CU);
                } else {
                    var_r21_3 += 1;
                    continue;
                }

                break;
            }
            if (var_r21_3 >= temp_r3) {
                goto block_23;
            }
        } else {
block_23:
            var_r25 += 1;
            continue;
        }

        break;
    }
    if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xB6U, 0) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x9DU);
    } else if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xC5U, 0) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x9DU);
    } else if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, 0xCBU, 0) == 1) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x9DU);
    }
    var_r22 = 0;
    while (var_r22 < temp_r26) {
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)sp18 + ((var_r22 * 4) & 0x3FFFC)), 0x14U) == 1) {
            temp_r0_2 = var_r22 - 1;
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, (var_r22 == 0 ? 0x9F : 0xA0));
        }
        var_r22 += 1;
        continue;

        break;
    }
    var_r22_2 = 0;
    while (var_r22_2 < temp_r29) {
        temp_r4_2 = *(FightOutPokemon **)((u8 *)sp38 + ((var_r22_2 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_2) && ((temp_r3_2 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, temp_r4_2), ((temp_r3_2 == 0xB6) != 0)) || (temp_r3_2 == 0xC5) || (temp_r3_2 == 0xCB))) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0xA1U);
        }
        var_r22_2 += 1;
        continue;

        break;
    }
    var_r23 = 0;
    while (var_r23 < temp_r29) {
        temp_r26_2 = (var_r23 * 4) & 0x3FFFC;
        temp_r4_3 = *(FightOutPokemon **)((u8 *)sp38 + temp_r26_2);
        if (arg1 != temp_r4_3) {
            temp_r26_3 = fightTrainerAiGetFightOutPokemonNowHp(arg0, temp_r4_3);
            if ((s32) temp_r26_3 <= fightTrainerAiWazaDoWazaDamageFunc(arg0, arg1, arg2, *(FightOutPokemon **)((u8 *)sp38 + temp_r26_2), 0U)) {
                var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0xA2U);
            }
        }
        var_r23 += 1;
        continue;

        break;
    }
    var_r22_3 = 0;
    while (var_r22_3 < temp_r29) {
        temp_r4_4 = *(FightOutPokemon **)((u8 *)sp38 + ((var_r22_3 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_4) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4_4, 0x14U) == 1)) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x9EU);
        }
        var_r22_3 += 1;
        continue;

        break;
    }
    return var_r24;
}

u8 _fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u8 arg2, u8 arg3) {
    u8 stats[7];
    u8 temp_r0;
    u8 var_r6;

    stats[0] = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    stats[1] = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg1);
    stats[2] = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(arg0, arg1);
    stats[3] = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg1);
    stats[4] = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg1);
    stats[5] = fightTrainerAiGetFightOutPokemonAbiCntAvg(arg0, arg1);
    stats[6] = fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg1);
    var_r6 = 0;
while (var_r6 < 7U) {
    temp_r0 = stats[var_r6];
    if ((temp_r0 >= arg2) && (temp_r0 <= arg3)) {
        return 1U;
    }
    var_r6 += 1;
    }
    return 0U;
}






typedef u8 (*StatCheck)(FIGHT_TRAINER *, FightOutPokemon *);
typedef s32 (*WazaValueFunc)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
WazaValueFunc wazaDB_GetFightTrainerAiWazaValueFuncPtr(u16);
extern u16 joutaiIzyouWazaTbl[];
extern u16 KonranWazaTbl[];
extern u16 moukakeiTbl[];
extern u16 statusUpKinomiTbl[];
extern u32 *waza_data_number;
s32 _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *, s32, u8, u16, u16, u16, u16, StatCheck);
u8 fightTrainerAiIsFightOutPokemonPhyAtkCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonPhyDefCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonSpeAtkCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonSpeDefCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonNimblenessCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonAvoidCntTakai(FIGHT_TRAINER *, FightOutPokemon *);

s32 fightTrainerAiWazaValueMahi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 var_r29;

    var_r30 = 0;
    var_r29 = 0;
    while (var_r29 < 0x12U) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, *(u16 *)((u8 *)joutaiIzyouWazaTbl + ((var_r29 * 2) & 0x1FE)), arg3) == 1) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x18DU);
        } else {
            var_r29 += 1;
            continue;
        }

        break;
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueKonran(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r30;
    u8 var_r29;

    var_r30 = 0;
    var_r29 = 0;
    while (var_r29 < 5U) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, *(u16 *)((u8 *)KonranWazaTbl + ((var_r29 * 2) & 0x1FE)), arg3) == 1) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x18DU);
        } else {
            var_r29 += 1;
            continue;
        }

        break;
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueOnibi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 var_r31;
    u16 temp_r24;
    u16 temp_r25;
    u16 temp_r26;
    u16 temp_r28;
    u16 temp_r3;
    u16 var_r23;
    u16 var_r24;

    var_r31 = 0;
    temp_r24 = fightTrainerAiGetFightOutPokemonSpeAtk(arg0, arg3);
    temp_r25 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, arg3);
    temp_r26 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    temp_r28 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    var_r23 = 0;
    while (var_r23 < temp_r28) {
        temp_r3 = fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r23 * 4) & 0x3FFFC)));
        if ((temp_r3 == 0xCA) || (temp_r3 == 0x168) || (temp_r3 == 0x12F) || (temp_r3 == 0xD5)) {
            var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x260U);
        } else {
            var_r23 += 1;
            continue;
        }

        break;
    }
    if (temp_r25 > temp_r24) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x261U);
    }
    if (temp_r26 == 0x11F) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x262U);
    }
    var_r24 = 0;
    while (var_r24 < 0x12U) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, *(u16 *)((u8 *)joutaiIzyouWazaTbl + ((var_r24 * 2) & 0x1FFFE)), arg3) == 1) {
            var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x263U);
        } else {
            var_r24 += 1;
            continue;
        }

        break;
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueDoku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp8[8];
    s32 var_r26;
    u16 temp_r27;
    u16 temp_r29;
    u16 temp_r3;
    u16 var_r25;
    u16 var_r27;

    var_r26 = 0;
    temp_r29 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    temp_r27 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    var_r25 = 0;
    while (var_r25 < temp_r29) {
        temp_r3 = fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, *(FightOutPokemon **)((u8 *)sp8 + ((var_r25 * 4) & 0x3FFFC)));
        if ((temp_r3 == 0xCA) || (temp_r3 == 0x168) || (temp_r3 == 0x12F) || (temp_r3 == 0xD5)) {
            var_r26 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x25DU);
        } else {
            var_r25 += 1;
            continue;
        }

        break;
    }
    if (temp_r27 == 0x11F) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x25EU);
    }
    var_r27 = 0;
    while (var_r27 < 0x12U) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, *(u16 *)((u8 *)joutaiIzyouWazaTbl + ((var_r27 * 2) & 0x1FFFE)), arg3) == 1) {
            var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x18DU);
        } else {
            var_r27 += 1;
            continue;
        }

        break;
    }
    return var_r26;
}

s32 fightTrainerAiWazaValueHaradaiko(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    s32 var_r31;

    sp8 = 0x25A;
    spC = 0;
    sp10 = fightTrainerAiIsFightOutPokemonPhyAtkCntTakai;
    var_r31 = _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, 0U, 0x258U, 0x259U, sp8, spC, sp10);
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.5f, -1) == 1) {
        var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x25BU);
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueMarukunaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp18[8];
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    u16 temp_r30;
    u16 temp_r4;
    u16 var_r6;
    u8 temp_r8;

    temp_r30 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp18, 0U, 1U);
    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg1);
    sp8 = 0x256;
    spC = 0x257;
    sp10 = fightTrainerAiIsFightOutPokemonPhyDefCntTakai;
    temp_r3 = _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8, 0x254U, 0U, sp8, spC, sp10);
    var_r6 = 0;
loop_5:
    if (var_r6 >= temp_r30) {
        return temp_r3;
    }
    temp_r4 = *(u16 *)((u8 *)sp18 + ((var_r6 * 2) & 0x1FFFE));
    if ((temp_r4 == 0xCD) || (temp_r4 == 0x12D)) {
        return fightTrainerAiAddValueByAddsubDataId(temp_r3, arg0, 0x255U);
    }
    var_r6 += 1;
    goto loop_5;
}

s32 fightTrainerAiWazaValueMeisou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    s32 temp_r31;
    u8 temp_r8;
    u8 temp_r8_2;

    temp_r8_2 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg1);
    sp8 = 0x252;
    spC = 0x253;
    sp10 = fightTrainerAiIsFightOutPokemonSpeAtkCntTakai;
    temp_r31 = _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8_2, 0x250U, 0x251U, sp8, spC, sp10);
    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg1);
    sp8 = 0x252;
    spC = 0;
    sp10 = fightTrainerAiIsFightOutPokemonSpeDefCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, temp_r31, temp_r8, 0x250U, 0U, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueRyuunomai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    s32 temp_r31;
    u8 temp_r8;
    u8 temp_r8_2;

    temp_r8_2 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg1);
    sp8 = 0x24E;
    spC = 0x24F;
    sp10 = fightTrainerAiIsFightOutPokemonPhyAtkCntTakai;
    temp_r31 = _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8_2, 0x24CU, 0x24DU, sp8, spC, sp10);
    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg1);
    sp8 = 0x24E;
    spC = 0;
    sp10 = fightTrainerAiIsFightOutPokemonNimblenessCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, temp_r31, temp_r8, 0x24CU, 0U, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueBirudoAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    s32 temp_r31;
    u8 temp_r8;
    u8 temp_r8_2;

    temp_r8_2 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    sp8 = 0x24A;
    spC = 0x24B;
    sp10 = fightTrainerAiIsFightOutPokemonPhyAtkCntTakai;
    temp_r31 = _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8_2, 0x248U, 0x249U, sp8, spC, sp10);
    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    sp8 = 0x24A;
    spC = 0;
    sp10 = fightTrainerAiIsFightOutPokemonPhyDefCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, temp_r31, temp_r8, 0x248U, 0U, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueKosumopawaa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    s32 temp_r31;
    u8 temp_r8;
    u8 temp_r8_2;

    temp_r8_2 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg1);
    sp8 = 0x246;
    spC = 0x247;
    sp10 = fightTrainerAiIsFightOutPokemonPhyDefCntTakai;
    temp_r31 = _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8_2, 0x244U, 0x245U, sp8, spC, sp10);
    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg1);
    sp8 = 0x246;
    spC = 0;
    sp10 = fightTrainerAiIsFightOutPokemonSpeDefCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, temp_r31, temp_r8, 0x244U, 0U, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueKaihirituAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    u8 temp_r8;

    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntAvd(arg0, arg1);
    sp8 = 0x242;
    spC = 0x243;
    sp10 = fightTrainerAiIsFightOutPokemonAvoidCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8, 0x240U, 0x241U, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueDowasure(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    u8 temp_r8;

    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntSpeDef(arg0, arg1);
    sp8 = 0x23E;
    spC = 0x23F;
    sp10 = fightTrainerAiIsFightOutPokemonSpeDefCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8, 0x23CU, 0x23DU, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueTokukouAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    u8 temp_r8;

    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(arg0, arg1);
    sp8 = 0x23A;
    spC = 0x23B;
    sp10 = fightTrainerAiIsFightOutPokemonSpeAtkCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8, 0x238U, 0x239U, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueKousokuidou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    u8 temp_r8;

    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(arg0, arg1);
    sp8 = 0x236;
    spC = 0x237;
    sp10 = fightTrainerAiIsFightOutPokemonNimblenessCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8, 0x234U, 0x235U, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueBougyoAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    u8 temp_r8;

    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntPhyDef(arg0, arg1);
    sp8 = 0x232;
    spC = 0x233;
    sp10 = fightTrainerAiIsFightOutPokemonPhyDefCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8, 0x230U, 0x231U, sp8, spC, sp10);
}

s32 fightTrainerAiWazaValueKougekiAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u8 (*sp10)(FIGHT_TRAINER *, FightOutPokemon *);
    s32 spC;
    s32 sp8;
    u8 temp_r8;

    temp_r8 = fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(arg0, arg1);
    sp8 = 0x22E;
    spC = 0x22F;
    sp10 = fightTrainerAiIsFightOutPokemonPhyAtkCntTakai;
    return _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(arg0, arg1, arg2, arg3, 0, temp_r8, 0x22CU, 0x22DU, sp8, spC, sp10);
}

s32 _fightTrainerAiWazaValueSubNouryokuKyouka__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemonlUcUsUsUsUsPFP13FIGHT_TRAINERP15FightOutPokemon_b(FIGHT_TRAINER *trainer, FightOutPokemon *user, u16 move, FightOutPokemon *target, s32 value, u8 stages, u16 low, u16 ally, u16 high, u16 perStage, StatCheck check) {
    s32 count;
    if (low != 0 && check(trainer, user) == 0) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, low);
    if (ally != 0 && _fightTrainerAiWazaValueIsAllyHaveWazaDataId__FP13FIGHT_TRAINERP15FightOutPokemonUs(trainer, user, 0x10A) == 1) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, ally);
    if (high != 0 && check(trainer, user) == 1) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, high);
    if (perStage != 0) {
        count = stages - 6;
        if (count < 0) count = 0;
        value = fightTrainerAiAddValue(value, count * fightTrainerAiValueAddsubDB_GetValue(perStage));
    }
    return value;
}

s32 fightTrainerAiWazaValueMamoru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;
    s32 (*var_r16)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
    s32 (*var_r3)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
    s32 var_r24;
    u16 temp_r23;
    u16 temp_r28;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 var_r15;
    u16 var_r15_2;
    u16 var_r17;
    u16 var_r18;
    u16 var_r18_2;
    u8 var_r25;
    u8 var_r26;
    u8 var_r27;
    u8 var_r29;

    var_r24 = 0;
    var_r27 = 0;
    var_r26 = 0;
    var_r29 = 0;
    var_r25 = 0;
    temp_r28 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 1U, 1U);
    temp_r23 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg1);
    fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    var_r18 = 0;
    while (var_r18 < temp_r28) {
        temp_r4 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r18 * 4) & 0x3FFFC));
        if (arg1 != temp_r4) {
            temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r4, sp8, 0U, 1U);
            if (temp_r3 != 0) {
                var_r17 = 0;
                while (var_r17 < temp_r3) {
                    var_r3 = wazaDB_GetFightTrainerAiWazaValueFuncPtr(*(u16 *)((u8 *)sp8 + ((var_r17 * 2) & 0x1FFFE)));
                    if (var_r3 == 0) {
                        var_r3 = fightTrainerAiWazaValueNull;
                    }
                    if (var_r3 == fightTrainerAiWazaValueJisin) {
                        var_r27 = 1;
                    }
                    if (var_r3 == fightTrainerAiWazaValueJibaku) {
                        var_r26 = 1;
                    }
                    var_r17 += 1;
                    continue;

                    break;
                }
            }
        }
        var_r18 += 1;
        continue;

        break;
    }
    var_r15 = 0;
    while (var_r15 < (u32) *waza_data_number) {
        var_r16 = wazaDB_GetFightTrainerAiWazaValueFuncPtr(var_r15);
        if (var_r16 == 0) {
            var_r16 = fightTrainerAiWazaValueNull;
        }
        if (((var_r16 == fightTrainerAiWazaValueJisin) || (var_r16 == fightTrainerAiWazaValueJibaku)) && (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, var_r15, 0) == 1)) {
            if (var_r16 == fightTrainerAiWazaValueJisin) {
                var_r29 = 1;
            }
            if (var_r16 == fightTrainerAiWazaValueJibaku) {
                var_r25 = 1;
            }
        }
        var_r15 += 1;
        continue;

        break;
    }
    if ((var_r27 == 1) || (var_r26 == 1)) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x21FU);
    }
    if ((var_r29 == 1) || (var_r25 == 1)) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x220U);
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 3U) == 1) && (fightTrainerAiIsWazaTypeId(arg0, temp_r23, 4U) == 1)) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x221U);
    }
    if (((temp_r23 == 0xB6) || (temp_r23 == 0xC5)) && (fightOutPokemon_GetSuccessCnt(arg1) != 0)) {
        var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x222U);
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg1, 7U) == 1) {
        if (var_r26 == 1) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x223U);
        }
        if (var_r25 == 1) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x224U);
        }
    }
    if ((fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg1, 2U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x1AU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x19U) == 1)) {
        if (var_r27 == 1) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x225U);
        }
        if (var_r29 == 1) {
            var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x226U);
        }
    }
    var_r15_2 = 0;
    while (var_r15_2 < temp_r28) {
        temp_r4_2 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r15_2 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_2) && (temp_r3_2 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r4_2, sp8, 0U, 1U), ((temp_r3_2 == 0) == 0))) {
            var_r18_2 = 0;
            while (var_r18_2 < temp_r3_2) {
                if ((u16) *(u16 *)((u8 *)sp8 + ((var_r18_2 * 2) & 0x1FFFE)) == 0x10A) {
                    var_r24 = fightTrainerAiAddValueByAddsubDataId(var_r24, arg0, 0x227U);
                } else {
                    var_r18_2 += 1;
                    continue;
                }

                break;
            }
            if (var_r18_2 >= temp_r3_2) {
                goto block_60;
            }
        } else {
block_60:
            var_r15_2 += 1;
            continue;
        }

        break;
    }
    return var_r24;
}

s32 fightTrainerAiWazaValueMigawari(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    u16 sp8[8];
    s32 temp_r0;
    s32 temp_r28_2;
    s32 var_r26;
    u16 temp_r0_2;
    u16 temp_r30;
    u16 temp_r31;
    u32 temp_r27;
    u32 temp_r28;
    u32 temp_r29;
    u8 var_r22;
    u8 var_r29;
    u8 var_r5;

    var_r26 = 0;
    temp_r27 = fightOutPokemonMaxHpWaruValue(arg1, 1U);
    temp_r28 = fightOutPokemonNowHpWaruValue(arg1, 1U);
    temp_r29 = fightOutPokemonMaxHpWaruValue(arg1, 4U);
    temp_r30 = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, arg1);
    temp_r31 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp8, 0U, 1U);
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.8f, 1) == 1) {
        var_r26 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x214U);
    }
    var_r22 = 0;
    while (var_r22 < 4U) {
        if (fightAi_GetTokuseiHaveFlag(arg0, arg1, *(u16 *)((u8 *)moukakeiTbl + ((var_r22 * 2) & 0x1FE))) == 1) {
            temp_r0 = (u16) temp_r28 - (u16) temp_r29;
            if ((temp_r0 <= (s32) fightOutPokemonMaxHpWaruValue(arg1, 3U)) && (temp_r0 > 0)) {
                var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x215U);
            }
        } else {
            var_r22 += 1;
            continue;
        }

        break;
    }
    temp_r28_2 = (u16) temp_r28 - (u16) temp_r29;
    if ((temp_r28_2 <= (s32) ((s32) ((u16) temp_r27 * 0x14) / 100)) && (temp_r28_2 > 0)) {
        var_r29 = 0;
        while ((s32) var_r29 < (s32) temp_r31) {
            temp_r0_2 = *(u16 *)((u8 *)sp8 + ((var_r29 * 2) & 0x1FE));
            if ((temp_r0_2 == 0xAF) || (temp_r0_2 == 0xB3)) {
                var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x216U);
            }
            var_r29 += 1;
            continue;

            break;
        }
    }
    if ((temp_r28_2 <= (s32) fightOutPokemonMaxHpWaruValue(arg1, 4U)) && (temp_r28_2 > 0)) {
        var_r5 = 0;
        while (var_r5 < 7U) {
            if (temp_r30 == (u16) *(u16 *)((u8 *)statusUpKinomiTbl + ((var_r5 * 2) & 0x1FE))) {
                var_r26 = fightTrainerAiAddValueByAddsubDataId(var_r26, arg0, 0x217U);
            } else {
                var_r5 += 1;
                continue;
            }

            break;
        }
    }
    return var_r26;
}

s32 fightTrainerAiWazaValueSiroikiri(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 (*var_r3)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
    s32 var_r31;
    u16 temp_r3;

    var_r31 = 0;
    temp_r3 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg3);
    if ((temp_r3 != 0) && (temp_r3 != -1U) && (temp_r3 != 0x176) && (temp_r3 != 0x163)) {
        var_r3 = wazaDB_GetFightTrainerAiWazaValueFuncPtr(temp_r3);
        if (var_r3 == 0) {
            var_r3 = fightTrainerAiWazaValueNull;
        }
        if ((var_r3 == fightTrainerAiWazaValueSubayasaDaun) || (var_r3 == fightTrainerAiWazaValueKougekiDaun) || (var_r3 == fightTrainerAiWazaValueBougyoDaun) || (var_r3 == fightTrainerAiWazaValueTokubouDaun) || (var_r3 == fightTrainerAiWazaValueMeityuuDaun) || (var_r3 == fightTrainerAiWazaValueKaihiDaun) || (var_r3 == fightTrainerAiWazaValueKusuguruDaun)) {
            var_r31 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x207U);
        }
    }
    return var_r31;
}

s32 fightTrainerAiWazaValueTedasuke(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp18[8];
    u16 sp8[8];
    FightOutPokemon *temp_r3_2;
    FightOutPokemon *temp_r3_4;
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;
    FightOutPokemon *temp_r4_3;
    s32 temp_r27;
    s32 var_r30;
    u16 temp_r31;
    u16 temp_r3;
    u16 var_r22_2;
    u16 var_r23;
    u16 var_r23_2;
    u16 var_r23_3;
    u16 var_r24;
    u16 var_r24_2;
    u16 var_r24_3;
    u8 var_r22;
    u8 var_r25;
    void *temp_r3_3;

    var_r30 = 0;
    temp_r31 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp18, 1U, 1U);
    var_r22 = 0;
    var_r23 = 0;
    while (var_r23 < (u32) *waza_data_number) {
        if ((var_r23 != 0) && (var_r23 != 0x176) && (var_r23 != 0x163) && (fightTrainerAiIsWazaTypeId(arg0, var_r23, 1U) != 0) && (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, var_r23, 0) == 1)) {
            var_r22 = 1;
        }
        var_r23 += 1;
        continue;

        break;
    }
    if (var_r22 == 1) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1F5U);
    }
    var_r23_2 = 0;
    while (var_r23_2 < temp_r31) {
        temp_r4 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r23_2 * 4) & 0x3FFFC));
        if (arg1 != temp_r4) {
            temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r4, sp8, 0U, 1U);
            if (temp_r3 != 0) {
                var_r22_2 = 0;
                while (var_r22_2 < temp_r3) {
                    if (fightTrainerAiIsWazaTypeId(arg0, *(u16 *)((u8 *)sp8 + ((var_r22_2 * 2) & 0x1FFFE)), 1U) != 0) {
                        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1F6U);
                    } else {
                        var_r22_2 += 1;
                        continue;
                    }

                    break;
                }
            }
        }
        var_r23_2 += 1;
        continue;

        break;
    }
    var_r25 = 1;
    var_r23_3 = 0;
    while (var_r23_3 < temp_r31) {
        temp_r27 = (var_r23_3 * 4) & 0x3FFFC;
        temp_r3_2 = *(FightOutPokemon **)((u8 *)sp18 + temp_r27);
        if ((arg1 != temp_r3_2) && (temp_r3_3 = fightOutPokemon_GetFightActionBuffPtr(temp_r3_2), ((temp_r3_3 == 0) == 0)) && (fightActionCheckValid(temp_r3_3) != 0)) {
            if (fightActionGetKindDataId(temp_r3_3) != 0x13) {
                var_r25 = 0;
            } else if (fightTrainerAiIsWazaTypeId(arg0, fightOutPokemonGetUseWazaDataId(*(FightOutPokemon **)((u8 *)sp18 + temp_r27)), 1U) == 0) {
                var_r25 = 0;
            } else {
                goto block_29;
            }
        } else {
block_29:
            var_r23_3 += 1;
            continue;
        }

        break;
    }
    if (var_r25 == 0) {
        var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1F7U);
    }
    var_r24 = 0;
    while (var_r24 < temp_r31) {
        temp_r4_2 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r24 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_2) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4_2, 0x12U) == 1)) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1F8U);
        } else {
            var_r24 += 1;
            continue;
        }

        break;
    }
    var_r24_2 = 0;
    while (var_r24_2 < temp_r31) {
        temp_r3_4 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r24_2 * 4) & 0x3FFFC));
        if ((arg1 != temp_r3_4) && (fightOutPokemon_GetNamakeFlag(temp_r3_4) != 0)) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1F9U);
        } else {
            var_r24_2 += 1;
            continue;
        }

        break;
    }
    var_r24_3 = 0;
    while (var_r24_3 < temp_r31) {
        temp_r4_3 = *(FightOutPokemon **)((u8 *)sp18 + ((var_r24_3 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4_3) && (_fightTrainerAiWazaValueIsFightOutPokemonNeoki__FP13FIGHT_TRAINERP15FightOutPokemon(arg0, temp_r4_3) == 0)) {
            var_r30 = fightTrainerAiAddValueByAddsubDataId(var_r30, arg0, 0x1FAU);
        } else {
            var_r24_3 += 1;
            continue;
        }

        break;
    }
    return var_r30;
}

s32 fightTrainerAiWazaValueOdareru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r27;
    u16 temp_r28;
    u16 temp_r29;
    u16 temp_r29_2;
    u8 var_r28;

    var_r27 = 0;
    temp_r29 = fightTrainerAiGetFightOutPokemonSpeAtk(arg0, arg3);
    temp_r28 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, arg3);
    temp_r29_2 = fightTrainerAiGetFightOutPokemonPhyDef(arg0, arg3);
    if (temp_r28 > temp_r29) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1D6U);
    }
    if (temp_r28 > temp_r29_2) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x1D7U);
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x14U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x1D8U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x1D9U);
    }
    var_r28 = 0;
    while (var_r28 < 5U) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, *(u16 *)((u8 *)KonranWazaTbl + ((var_r28 * 2) & 0x1FE)), arg3) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x1DAU);
        } else {
            var_r28 += 1;
            continue;
        }

        break;
    }
    return var_r27;
}

s32 fightTrainerAiWazaValueIbaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r27;
    u16 temp_r28;
    u16 temp_r29;
    u16 temp_r29_2;
    u8 var_r28;

    var_r27 = 0;
    temp_r29 = fightTrainerAiGetFightOutPokemonSpeAtk(arg0, arg3);
    temp_r28 = fightTrainerAiGetFightOutPokemonPhyAtk(arg0, arg3);
    temp_r29_2 = fightTrainerAiGetFightOutPokemonPhyDef(arg0, arg3);
    if (temp_r29 > temp_r28) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1D1U);
    }
    if (temp_r28 > temp_r29_2) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x1D2U);
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x14U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x1D3U);
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 9U) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x1D4U);
    }
    var_r28 = 0;
    while (var_r28 < 5U) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, *(u16 *)((u8 *)KonranWazaTbl + ((var_r28 * 2) & 0x1FE)), arg3) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x1D5U);
        } else {
            var_r28 += 1;
            continue;
        }

        break;
    }
    return var_r27;
}

s32 fightTrainerAiWazaValueKoraeru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightOutPokemon *sp1C[8];
    u16 spC[8];
    u16 sp8[8];
    FightOutPokemon *temp_r4;
    s32 (*var_r3)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
    s32 (*var_r3_2)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
    s32 var_r23;
    u16 temp_r16;
    u16 temp_r18;
    u16 temp_r27;
    u16 temp_r28;
    u16 temp_r3;
    u16 var_r16;
    u16 var_r21;
    u16 var_r22;
    u16 var_r24;
    u8 temp_r30;
    u8 var_r16_2;
    u8 var_r20;

    var_r23 = 0;
    temp_r30 = fightTrainerAiGetFightFloorNowTenkouDataId(arg0, 0, 1U);
    temp_r16 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, sp1C, 1U, 1U);
    temp_r18 = fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(arg0, arg3, sp8);
    temp_r27 = fightTrainerAiGetFightOutPokemonLastUseWazaDataId(arg0, arg1);
    temp_r28 = fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, arg1);
    var_r20 = 0;
    var_r21 = 0;
    while (var_r21 < temp_r18) {
        if (fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(arg0, arg1, *(u16 *)((u8 *)sp8 + ((var_r21 * 2) & 0x1FFFE)), fightTrainerAiGetWazaIryoku(arg0, arg2)) == 0x41) {
            var_r20 = 1;
        } else {
            var_r21 += 1;
            continue;
        }

        break;
    }
    if (var_r20 == 1) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x1A9U);
    }
    if (fightTrainerAiIsFightOutPokemonNokoriHp(arg0, arg1, 0.5f, -1) == 1) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x1AAU);
    }
    var_r24 = 0;
    while (var_r24 < temp_r16) {
        temp_r4 = *(FightOutPokemon **)((u8 *)sp1C + ((var_r24 * 4) & 0x3FFFC));
        if ((arg1 != temp_r4) && (temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r4, spC, 0U, 1U), ((temp_r3 == 0) == 0))) {
            var_r22 = 0;
            while (var_r22 < temp_r3) {
                var_r3 = wazaDB_GetFightTrainerAiWazaValueFuncPtr(*(u16 *)((u8 *)spC + ((var_r22 * 2) & 0x1FFFE)));
                if (var_r3 == 0) {
                    var_r3 = fightTrainerAiWazaValueNull;
                }
                if ((var_r3 == fightTrainerAiWazaValueJisin) || (var_r3 == fightTrainerAiWazaValueJibaku)) {
                    var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x1ABU);
                } else {
                    var_r22 += 1;
                    continue;
                }

                break;
            }
            if (var_r22 >= temp_r3) {
                goto block_21;
            }
        } else {
block_21:
            var_r24 += 1;
            continue;
        }

        break;
    }
    var_r16 = 0;
    while (var_r16 < (u32) *waza_data_number) {
        var_r3_2 = wazaDB_GetFightTrainerAiWazaValueFuncPtr(var_r16);
        if (var_r3_2 == 0) {
            var_r3_2 = fightTrainerAiWazaValueNull;
        }
        if (((var_r3_2 == fightTrainerAiWazaValueJisin) || (var_r3_2 == fightTrainerAiWazaValueJibaku)) && (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, var_r16, 0) == 1)) {
            var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x1ACU);
        } else {
            var_r16 += 1;
            continue;
        }

        break;
    }
    var_r16_2 = 0;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 6U) == 1) {
        var_r16_2 = 1;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 3U) == 1) {
        var_r16_2 = 1;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 4U) == 1) {
        var_r16_2 = 1;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 5U) == 1) {
        var_r16_2 = 1;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x18U) == 1) {
        var_r16_2 = 1;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1CU) == 1) {
        var_r16_2 = 1;
    }
    if (var_r16_2 == 1) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x1ADU);
    }
    if ((temp_r27 == 0xCB) && (fightOutPokemon_GetSuccessCnt(arg1) != 0)) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x1AEU);
    }
    if ((temp_r28 != 0x11) && (temp_r28 != 0xF)) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x1AFU);
    }
    if (fightTrainerAiGetFightOutPokemonNowHp(arg0, arg1) == 1) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x1B0U);
    }
    if ((temp_r30 == 4) || (temp_r30 == 3)) {
        var_r23 = fightTrainerAiAddValueByAddsubDataId(var_r23, arg0, 0x1B1U);
    }
    return var_r23;
}

s32 fightTrainerAiWazaValueNemurare(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    FightPokemon *sp8[8];
    FightPokemon *temp_r4;
    s32 var_r27;
    u16 temp_r29;
    u16 var_r26;
    u16 var_r28;

    var_r27 = 0;
    temp_r29 = fightFloorGetFightTrainerFightPokemonPtrAry(0, arg0, sp8, 0U, 1U);
    if (fightTrainerAiIsFightOutPokemonJoutaiNormal(arg0, arg3) == 1) {
        var_r27 = fightTrainerAiAddValueByAddsubDataId(0, arg0, 0x181U);
    }
    var_r26 = 0;
    while (var_r26 < temp_r29) {
        temp_r4 = *(FightPokemon **)((u8 *)sp8 + ((var_r26 * 4) & 0x3FFFC));
        if ((fightOutPokemon_GetMotoFightPokemonPtr(arg3) != temp_r4) && (fightTrainerAiIsFightPokemonJoutaiDataId(arg0, temp_r4, 8U) == 1)) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x182U);
        } else {
            var_r26 += 1;
            continue;
        }

        break;
    }
    var_r28 = 0;
    while (var_r28 < 0x12U) {
        if (fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(0, arg0, 1U, 1U, *(u16 *)((u8 *)joutaiIzyouWazaTbl + ((var_r28 * 2) & 0x1FFFE)), arg3) == 1) {
            var_r27 = fightTrainerAiAddValueByAddsubDataId(var_r27, arg0, 0x183U);
        } else {
            var_r28 += 1;
            continue;
        }

        break;
    }
    return var_r27;
}




s32 fightTrainerAiWazaValueHimitunotikara(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3) {
    s32 var_r31;
    u8 temp_r3;

    var_r31 = 0;
    temp_r3 = tikeiDataBiosGetFightKoukaId(fightFloor_GetTikeiDataId(0));
    switch (temp_r3) {
    case 2:
        var_r31 = fightTrainerAiWazaValueTuikaDoku(arg0, arg1, arg2, arg3);
        break;
    case 1:
        var_r31 = fightTrainerAiWazaValueTuikaNemuri(arg0, arg1, arg2, arg3);
        break;
    case 27:
        var_r31 = fightTrainerAiWazaValueTuikouMeityuuDaun(arg0, arg1, arg2, arg3);
        break;
    case 23:
        var_r31 = fightTrainerAiWazaValueTuikouBougyoDaun(arg0, arg1, arg2, arg3);
        break;
    case 22:
        var_r31 = fightTrainerAiWazaValueOororabiimu(arg0, arg1, arg2, arg3);
        break;
    case 24:
        var_r31 = fightTrainerAiWazaValueTuikouSubayasaDaun(arg0, arg1, arg2, arg3);
        break;
    case 7:
        var_r31 = fightTrainerAiWazaValueTuikouKonran(arg0, arg1, arg2, arg3);
        break;
    case 8:
        var_r31 = fightTrainerAiWazaValueTuikaHirumi(arg0, arg1, arg2, arg3);
        break;
    case 5:
        var_r31 = fightTrainerAiWazaValueTuikaMahi(arg0, arg1, arg2, arg3);
        break;
    }
    return var_r31;
}



#ifdef __cplusplus
}
#endif
