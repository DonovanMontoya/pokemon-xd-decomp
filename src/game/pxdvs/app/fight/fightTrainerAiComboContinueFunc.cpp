#include <global.h>
struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;
extern "C" {
u16 HSD_Rand();
u32 fightFloor_GetFightType(void*);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER*,FightOutPokemon*,u16*,s16*,u8);
u16 fightTrainerAiGetFightOutPokemonLastUseWazaDataId(FIGHT_TRAINER*,FightOutPokemon*);
FightOutPokemon* fightTargetGetPtr(u8,void*,u8);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER*,FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER*,FightOutPokemon*);
u8 fightAi_CanMoveAppointWaza(FIGHT_TRAINER*,FightOutPokemon*,u16);
s32 fightAi_CreateFightActionAttckWaza(FightOutPokemon*,FightOutPokemon*,u16,s16);
u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER*,FightOutPokemon*,u16);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER*,FightPokemon*,u16);
FightPokemon* getFightPokemonPtr__15FightOutPokemonFv(FightOutPokemon*);
s16 fightTrainerAiSelectIrekaeDasuFightPokemon(FIGHT_TRAINER*,u8,u8,FightOutPokemon*);
s32 fightAi_CreateFightActionAttckIrekae(FightOutPokemon*,s16);
u8 fightTrainerAiIsFightOutPokemonAvoidCntHikui(FIGHT_TRAINER*,FightOutPokemon*);
FightOutPokemon* fightAi_SelectDefPoke(FIGHT_TRAINER*,FightOutPokemon*,FightOutPokemon**,u16,u16,s8);
}
s8 _getWazaMaxValueIndex(u8*,s16*,u16,u8);

extern "C" s32 fightAiCombo_Batontatti_Zikoanzi_Continue(FIGHT_TRAINER* trainer,FightOutPokemon* pokemon) {
    u8 scores[4];u16 moves[4];s16 slots[4];
    u8 i;
    u16 count;
    u16 last;
    u16 desired=0;
    FightOutPokemon* partner;
    u8 attack,speed,partnerSpeed;
    u8 fightType;
    fightType=fightFloor_GetFightType(0);
    count=fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,pokemon,moves,slots,1);
    last=fightTrainerAiGetFightOutPokemonLastUseWazaDataId(trainer,pokemon);
    partner=fightTargetGetPtr(14,pokemon,fightType);
    attack=fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(trainer,pokemon);
    speed=fightTrainerAiGetFightOutPokemonAbiCntSubayasa(trainer,pokemon);
    partnerSpeed=fightTrainerAiGetFightOutPokemonAbiCntSubayasa(trainer,partner);
    switch((int)last){
    case 182:if(speed>=7)desired=226;break;
    case 244:if(speed>=7)desired=226;break;
    case 252:if(partnerSpeed>=7)desired=244;break;
    default:if(attack>=7 && speed>=7)desired=182;break;
    }
    for(i=0;i<count;++i){
        scores[slots[i]]=50;
        if(fightAi_CanMoveAppointWaza(trainer,pokemon,moves[i])==0)scores[slots[i]]=0;
        if(desired!=moves[i] || desired==0)scores[slots[i]]=0;
    }
    s8 selected=_getWazaMaxValueIndex(scores,slots,count,0);
    if(selected<0)return 0;
    FightOutPokemon* target;
    if(desired==244)target=partner;else target=pokemon;
    if(target==0)return 0;
    fightAi_CreateFightActionAttckWaza(pokemon,target,moves[selected],slots[selected]);
    return 1;
}
extern "C" s32 fightAiCombo_Batontatti_Nekodamasi_Continue(FIGHT_TRAINER* trainer,FightOutPokemon* pokemon) {
    u8 scores[4];u16 moves[4];s16 slots[4];
    u8 i;
    u16 desired=0;
    u16 last;
    u16 count=fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,pokemon,moves,slots,1);
    last=fightTrainerAiGetFightOutPokemonLastUseWazaDataId(trainer,pokemon);
    u8 attack=fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(trainer,pokemon);
    u8 speed=fightTrainerAiGetFightOutPokemonAbiCntSubayasa(trainer,pokemon);
    if(last==182 && speed>=7)desired=226;
    if(last!=182 && attack>=7 && speed>=7)desired=182;
    for(i=0;i<count;++i){
        scores[slots[i]]=50;
        if(fightAi_CanMoveAppointWaza(trainer,pokemon,moves[i])==0)scores[slots[i]]=0;
        if(desired!=moves[i] || desired==0)scores[slots[i]]=0;
    }
    s8 selected=_getWazaMaxValueIndex(scores,slots,count,0);
    if(selected<0)return 0;
    if(pokemon==0)return 0;
    fightAi_CreateFightActionAttckWaza(pokemon,pokemon,moves[selected],slots[selected]);
    return 1;
}
extern "C" s32 fightAiCombo_Sukirusuwappu_Irekae_Continue(FIGHT_TRAINER* trainer,FightOutPokemon* pokemon) {
    u16 moves[4];s16 slots[4];
    u8 type=fightFloor_GetFightType(0);
    fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,pokemon,moves,slots,1);
    if(fightAi_GetTokuseiHaveFlag(trainer,pokemon,54)!=2)return 0;
    if(fightTrainerAiIsFightPokemonTokuseiDataId(trainer,getFightPokemonPtr__15FightOutPokemonFv(pokemon),54)==1)return 0;
    s16 selected=fightTrainerAiSelectIrekaeDasuFightPokemon(trainer,type,1,pokemon);
    if(selected<0)return 0;
    fightAi_CreateFightActionAttckIrekae(pokemon,selected);
    return 1;
}
extern "C" s32 fightAiCombo_Amaikaori_Hubuki_Continue(FIGHT_TRAINER* trainer,FightOutPokemon* pokemon,FightOutPokemon** defenders,u16 defenderCount) {
    u8 scores[4];u16 moves[4];s16 slots[4];
    u8 i;
    u16 count=fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,pokemon,moves,slots,1);
    FightOutPokemon* target;
    u8 avoidCount=0;
    for(i=0;i<defenderCount;++i){
        if(defenders[i] && fightTrainerAiIsFightOutPokemonAvoidCntHikui(trainer,defenders[i])==1)++avoidCount;
    }
    if(avoidCount==0)return 0;
    for(i=0;i<count;++i){
        scores[slots[i]]=50;
        if(fightAi_CanMoveAppointWaza(trainer,pokemon,moves[i])==0)scores[slots[i]]=0;
        if(moves[i]!=59 && moves[i]!=157)scores[slots[i]]=0;
    }
    s8 selected=_getWazaMaxValueIndex(scores,slots,count,0);
    if(selected<0)return 0;
    if(avoidCount>=2)target=fightAi_SelectDefPoke(trainer,pokemon,defenders,defenderCount,moves[selected],-1);
    else{
        for(i=0;i<defenderCount;++i){
            if(defenders[i] && fightTrainerAiIsFightOutPokemonAvoidCntHikui(trainer,defenders[i])==1){target=defenders[i];break;}
        }
    }
    if(target==0)return 0;
    fightAi_CreateFightActionAttckWaza(pokemon,target,moves[selected],slots[selected]);
    return 1;
}
extern "C" s32 fightAiCombo_null_Continue(){return 0;}
s8 _getWazaMaxValueIndex(u8* scores,s16* slots,u16 count,u8 minimum) {
    u8 candidates[64];
    u8 best=minimum;
    u8 ties;
    for(u8 i=0;i<count;++i){
        u8 value=scores[slots[i]];
        if(value>best){candidates[0]=i;best=value;ties=1;}
        else if(best==value && best>minimum)candidates[ties++]=i;
    }
    // The original performs this random selection even if no move beats minimum.
    s8 selected=candidates[HSD_Rand()%ties];
    s8 result=-1;
    if(best>minimum)result=selected;
    return result;
}
