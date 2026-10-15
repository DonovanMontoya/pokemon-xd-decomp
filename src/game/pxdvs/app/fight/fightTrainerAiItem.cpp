#include <global.h>
struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;
struct ItemUseResult {u8 data[0x100];};
extern "C" {
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u16 fightTrainerDB_GetAiDataId(u16);
u16 fightTrainerGetTemotiNormalItemDataIdAry(FIGHT_TRAINER*,u16*,u16,u8);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*,FIGHT_TRAINER*,FightOutPokemon**,u8,u8);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(void*,FIGHT_TRAINER*,FightPokemon**,u8,u8);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER*,FightOutPokemon*);
u8 itemDataCheckValid(u16);
u8 fightSeqGetItemType(u16,FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER*,FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER*,FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonPartDataId(FIGHT_TRAINER*,FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER*,FightOutPokemon*);
void* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u8 pokemonIsDarkPokemon(void*);
s32 fightTrainerAiAddValueByAddsubDataId(s32,FIGHT_TRAINER*,u16);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
u8 fightPokemonCheckFightOut(FightPokemon*);
s32 fightTrainerAiGetValueAryMaxBanme(s32*,u16,u8);
s32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*,void*);
extern u8 fight_action_data_item[];
void fightOutPokemonCreateFightActionUseItem(FightOutPokemon*,u32,u32,u32,void*,u16,s32,s32,u32);
s16 itemUse2PokemonSimulation(ItemUseResult*,void*,FightPokemon*,u16,u32);
}
static u8 _fightTrainerAiSelectFightActionItemSubCheckUseItem(FIGHT_TRAINER*,FightOutPokemon*,u16);
extern "C" u8 fightTrainerAiSelectFightActionItem(FIGHT_TRAINER* trainer,FightOutPokemon* pokemon,void* target){
    FightOutPokemon* out[8];
    u16 items[30];
    s32 values[30];
    FightPokemon* party[24];
    FightOutPokemon* member;
    u16 i;
    u16 j;
    u16 count;
    u8 allHigh;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    // The retail routine initializes this flag to zero and only clears it.
    allHigh=0;
    count=fightTrainerGetTemotiNormalItemDataIdAry(trainer,items,30,1);
    if(!count)return 0;
    u16 outCount=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,out,1,1);
    u16 partyCount=fightFloorGetFightTrainerFightPokemonPtrAry(0,trainer,party,1,1);
    for(j=0;j<outCount;++j){member=out[j];if(member&&fightOutPokemonCheckFightOut(member)&&fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer,member)==1)allHigh=0;}
    for(u16 k=0;k<30;++k)values[k]=0;
    for(i=0;i<count;++i){
        u16 item=items[i];
        if(!item||!itemDataCheckValid(item))continue;
        u8 type=fightSeqGetItemType(item,pokemon);
        if(type==7||!_fightTrainerAiSelectFightActionItemSubCheckUseItem(trainer,pokemon,item))continue;
        if((type==2||type==1)&&fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer,pokemon)==1&&!pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(pokemon)))values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,50);
        if((type==3||type==1)&&!fightTrainerAiIsFightOutPokemonJoutaiNormal(trainer,pokemon)&&!pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(pokemon)))values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,51);
        if(type==5&&!fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer,pokemon))values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,52);
        if(type==4&&fightTrainerAiGetFightOutPokemonPartDataId(trainer,pokemon)==2)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,53);
        if(type==6&&allHigh==1)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,54);
        if(fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer,pokemon)!=2&&fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer,pokemon)!=3){
            for(j=0;j<partyCount;++j){
                if(fightOutPokemon_GetMotoFightPokemonPtr(pokemon)!=party[j]&&(fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer,pokemon)==2||fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer,pokemon)==3)&&fightPokemonCheckFightOut(party[j])==1){values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,55);break;}
            }
        }
    }
    u16 selected;
    for(selected=0;selected<count;++selected)if(values[selected]>0)break;
    if(selected>=count)return 0;
    if(fightTrainerAiGetValueAryMaxBanme(values,count,1)<0)return 0;
    u16 item=items[selected];
    if(!item)return 0;
    s32 relative=fightTargetGetTragetPtrToRelativeHostSideFightTargetId(pokemon,target);
    fightOutPokemonCreateFightActionUseItem(pokemon,0,18,0,fight_action_data_item,item,relative,-1,0);
    return 1;
}
static u8 _fightTrainerAiSelectFightActionItemSubCheckUseItem(FIGHT_TRAINER*,FightOutPokemon* pokemon,u16 item){
    ItemUseResult result;
    FightPokemon* original=fightOutPokemon_GetMotoFightPokemonPtr(pokemon);
    return itemUse2PokemonSimulation(&result,0,original,item,0)>0;
}
