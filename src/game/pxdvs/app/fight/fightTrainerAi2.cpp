#include <global.h>
struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightSide;
extern "C" {
u16 HSD_Rand();
u16 wazaDB_GetSeqId(u16);
u8 fightFloorLoopValidFightOutPokemon(void*,s32(*)(FightOutPokemon*,u32,void*),void*,u8);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightTrainerIsAllyFightTargetPtr(FIGHT_TRAINER*,FightOutPokemon*,u32);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*,FightOutPokemon*,u16);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER*,FightOutPokemon*,u16);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u16 fightTrainerDB_GetAiDataId(u16);
u8 fightTrainerAiDB_GetZokuseiCheckFlag(u16);
u8 fightTrainerAiDB_GetPokemonJoutaiFlag(u16);
u8 fightSeqGetTextureZokuseiAry(FightOutPokemon*,u16*);
FightSide* fightTargetGetPtrAsNowFightType(u8,FightOutPokemon*);
u16 fightSeqCondChgActTypeToPokemonStatusId(u8);
s8 fightSeqCondChgActParaIdToValue(u8);
u32 pokemonGetStatus(void*,u32,u16,u16);
u8 fightSideIsJoutaiDataId(FightSide*,u16);
u8 fightSeqIsGuard(FightOutPokemon*,u32);
u16 fightOutPokemon_GetOumuWazaDataId(FightOutPokemon*);
u8 fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(FightOutPokemon*,u16*);
u8 fightTrainerAiCheckGuard(FIGHT_TRAINER*,FightOutPokemon*,u32);

struct AiCheckContext {FIGHT_TRAINER* trainer;u32 value;};
static s32 _fightTrainerAiCheckHorobinoutaSub(FightOutPokemon*,u32,void*);
static s32 _fightTrainerAiSimerikeCheckSub(FightOutPokemon*,u32,void*);
static s32 _fightTrainerAiSawaguCheckSub(FightOutPokemon*,u32,void*);

s32 fightTrainerAiCheckJoutaiKieWazaHitWazaDataId(FIGHT_TRAINER*,u16 state,u16 move) {
    u16 sequence=wazaDB_GetSeqId(move);
    if(state==31 && (sequence==146 || sequence==149 || sequence==152 || sequence==207))return 1;
    if(state==32 && sequence==147)return 1;
    if(state==33 && (move==57 || move==250))return 1;
    if(sequence==94)return 1;
    return 0;
}
u16 fightTrainerAiCheckHorobinouta(FIGHT_TRAINER* trainer) {
    AiCheckContext context;
    context.trainer=trainer;context.value=0;
    fightFloorLoopValidFightOutPokemon(0,_fightTrainerAiCheckHorobinoutaSub,&context,0);
    return context.value;
}
static s32 _fightTrainerAiCheckHorobinoutaSub(FightOutPokemon* pokemon,u32 type,void* data) {
    FIGHT_TRAINER* trainer=((AiCheckContext*)data)->trainer;
    if(fightOutPokemonCheckFightOut(pokemon)==0)return 1;
    if(fightTrainerIsAllyFightTargetPtr(trainer,pokemon,type)==1)return 1;
    if(fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer,pokemon,30)!=1 && fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,43)!=1)++((AiCheckContext*)data)->value;
    return 1;
}
u8 fightTrainerAiCheckTextureZokusei(FIGHT_TRAINER* trainer,FightOutPokemon* pokemon) {
    u16 types[2];
    if(fightTrainerAiDB_GetZokuseiCheckFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer)))==1)return fightSeqGetTextureZokuseiAry(pokemon,types)>=1;
    return 1;
}
s32 fightTrainerAiCheckAbiCnt(FIGHT_TRAINER* trainer,FightOutPokemon* attacker,FightOutPokemon* defender,u32 move,u8 parameter,u8 change,u32 flags) {
    FightOutPokemon* pokemon;
    u16 status;
    u8 ignoreAbility=0;
    u8 ignoreGuard=0;
    if(flags&64)pokemon=attacker;else pokemon=defender;
    FightSide* side=fightTargetGetPtrAsNowFightType(2,pokemon);
    u8 activeFlags=flags;
    u32 abilityFlags=activeFlags&0xBF;
    if(abilityFlags&128)ignoreAbility=1;
    if(activeFlags&32)ignoreGuard=1;
    status=fightSeqCondChgActTypeToPokemonStatusId(change);
    s8 value=pokemonGetStatus(pokemon,0,status,0);
    if(fightSeqCondChgActParaIdToValue(parameter)<0){
        if(fightSideIsJoutaiDataId(side,76)==1 && ignoreAbility==0 && (u16)move!=174)return 0;
        if((u16)move!=174 && ignoreGuard!=1 && fightTrainerAiCheckGuard(trainer,defender,move)==1)return 0;
        if((fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,29)==1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,73)==1) && ignoreAbility==0 && (u16)move!=174)return 0;
        if(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,51)==1 && ignoreAbility==0 && status==235)return 0;
        if(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,52)==1 && ignoreAbility==0 && status==230)return 0;
        if(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,19)==1 && !(activeFlags&31))return 0;
        if(value<=0)return 0;
    }else if(value>=12)return 0;
    return 1;
}
u8 fightTrainerAiCheckGuard(FIGHT_TRAINER* trainer,FightOutPokemon* pokemon,u32 move) {
    if(fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer)))==1 && fightSeqIsGuard(pokemon,move)==1)return 1;
    return 0;
}
u16 fightTrainerAiCheckOumu(FIGHT_TRAINER*,FightOutPokemon* pokemon) {
    u16 moves[4];
    u16 move=fightOutPokemon_GetOumuWazaDataId(pokemon);
    if(move!=0 && move!=374 && move!=0xffff)return move;
    u8 count=fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(pokemon,moves);
    if(count){
        u8 index=HSD_Rand()%count;
        move=moves[index];
        if(move!=0 && move!=374)return move;
    }
    return 0;
}
s32 fightTrainerAiCheckSimerike(FIGHT_TRAINER* trainer) {
    FIGHT_TRAINER* context=trainer;
    return fightFloorLoopValidFightOutPokemon(0,_fightTrainerAiSimerikeCheckSub,&context,0)==1?0:1;
}
static s32 _fightTrainerAiSimerikeCheckSub(FightOutPokemon* pokemon,u32,void* data) {
    FIGHT_TRAINER* trainer=*(FIGHT_TRAINER**)data;
    if(fightOutPokemonCheckFightOut(pokemon)==0)return 1;
    return fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,6)==1?0:1;
}
s32 fightTrainerAiCheckSawagu(FIGHT_TRAINER* trainer,FightOutPokemon* pokemon) {
    struct {FIGHT_TRAINER* trainer;FightOutPokemon* pokemon;} context;
    context.trainer=trainer;context.pokemon=pokemon;
    return fightFloorLoopValidFightOutPokemon(0,_fightTrainerAiSawaguCheckSub,&context,0)==1?0:1;
}
static s32 _fightTrainerAiSawaguCheckSub(FightOutPokemon* pokemon,u32,void* data) {
    FIGHT_TRAINER* trainer=((FIGHT_TRAINER**)data)[0];
    FightOutPokemon* target=((FightOutPokemon**)data)[1];
    if(fightOutPokemonCheckFightOut(pokemon)==0)return 1;
    if(fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer,pokemon,11)==1 && fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,target,43)==0)return 0;
    return 1;
}
}
