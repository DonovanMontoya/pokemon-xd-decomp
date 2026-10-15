#include <global.h>
extern "C" {
u16 joutaiDataBiosGetStatus(u32);
s32 joutaiGetUserFightTargetId(void*,u32);
s32 joutaiGetNowKaisuuJoutaiDataId(void*,u32);
s32 joutaiGetKaisuuJoutaiDataId(void*,u32);
s32 joutaiGetCountAsJoutaiDataId(void*,u32);
void joutaiSetNowKaisuuJoutaiDataId(void*,u32,s32);
void joutaiWriteJoutaiDataId(void*,u32,s32);
s32 joutaiCheckWriteJoutaiDataId(void*,u32);
s32 joutaiIsJoutaiDataId(void*,u32);
void joutaiInitJoutaiDataId(void*,u32);
void* fightSide_GetFightTrainerPtr(void*,u16);
u8 fightTrainerCheckValid(void*);
u8 fightTrainerCheckDoFight(void*);
u16 fightGetFightResultId();
u16 fightSide_GetFightSideDataId(void*);
void fightSide_SetFightSideDataId(void*,s32);
void fightSide_SetMakibisiCheckFlag(void*,u8);
void* fightSide_GetJoutaiPtr(void*,u32);
void joutaiInitAry(void*,u16);
void fightTrainerInitAry(void*,u16);
void fightSideInit(void*);
s32 fightTrainerGetHikaeFightPokemonNum(void*,u32,u32);
void* fightTrainerGetValidFightPokemonPtr(void*,u16);
u8 fightPokemonCheckFightOut(void*);
void* fightPokemonGetPokemonPtr(void*);
u16 pokemon_GetHp(void*);
u16 pokemon_GetMaxHp(void*);
s32 fightSideGetFightPokemonNum(void*,u16,u16,u8);
#pragma dont_inline on
s32 fightSideGetJoutaiUserFightTargetId(void* side,u32 id){if(joutaiDataBiosGetStatus(id)!=6)return 0;return joutaiGetUserFightTargetId(side,id);}
void fightSideSetNowKaisuuJoutaiDataId(void* side,u32 id,s32 value){if(joutaiDataBiosGetStatus(id)==6)joutaiSetNowKaisuuJoutaiDataId(side,id,value);}
s32 fightSideGetNowKaisuuJoutaiDataId(void* side,u32 id){if(joutaiDataBiosGetStatus(id)!=6)return -1;return joutaiGetNowKaisuuJoutaiDataId(side,id);}
s32 fightSideGetKaisuuJoutaiDataId(void* side,u32 id){if(joutaiDataBiosGetStatus(id)!=6)return -1;return joutaiGetKaisuuJoutaiDataId(side,id);}
s32 fightSideGetCountAsJoutaiDataId(void* side,u32 id){if(joutaiDataBiosGetStatus(id)!=6)return -1;return joutaiGetCountAsJoutaiDataId(side,id);}
void fightSideWriteJoutaiDataId(void* side,u32 id,s32 value){if(joutaiDataBiosGetStatus(id)==6)joutaiWriteJoutaiDataId(side,id,value);}
s32 fightSideCheckWriteJoutaiDataId(void* side,u32 id){if(joutaiDataBiosGetStatus(id)!=6)return 0;return joutaiCheckWriteJoutaiDataId(side,id);}
s32 fightSideIsJoutaiDataId(void* side,u32 id){if(joutaiDataBiosGetStatus(id)!=6)return 0;return joutaiIsJoutaiDataId(side,id);}
void fightSideInitJoutaiDataId(void* side,u32 id){if(joutaiDataBiosGetStatus(id)==6)joutaiInitJoutaiDataId(side,id);}
s32 fightSideGetHikaeFightPokemonNum(void* side,u16 trainerCount,u32 maxPokemon,u32 mode){
    s32 count=0;
    for(u16 i=0;i<trainerCount;i++){
        void* trainer=fightSide_GetFightTrainerPtr(side,i);
        if(fightTrainerCheckValid(trainer))count+=fightTrainerGetHikaeFightPokemonNum(trainer,maxPokemon,mode);
    }
    return count;
}
s32 fightSideGetNokoriFightPokemonNum(void* side,u16 trainerCount,u16 pokemonCount){return fightSideGetFightPokemonNum(side,trainerCount,pokemonCount,1);}
s32 fightSideGetFightPokemonNum(void* side,u16 trainerCount,u16 pokemonCount,u8 requireLive){
    s32 count=0;
    for(u16 i=0;i<trainerCount;i++){
        void* trainer=fightSide_GetFightTrainerPtr(side,i);
        if(fightTrainerCheckValid(trainer)){
            for(u16 j=0;j<pokemonCount;j++){
                void* pokemon=fightTrainerGetValidFightPokemonPtr(trainer,j);
                if(pokemon && (requireLive!=1 || fightPokemonCheckFightOut(pokemon)))++count;
            }
        }
    }
    return count;
}
u32 fightSideGetFightPokemonMaxHp(void* side,u16 trainerCount,u16 pokemonCount){
    u32 total=0;
    for(u16 i=0;i<trainerCount;i++){
        void* trainer=fightSide_GetFightTrainerPtr(side,i);
        if(fightTrainerCheckValid(trainer)){
            for(u16 j=0;j<pokemonCount;j++){
                void* fightPokemon=fightTrainerGetValidFightPokemonPtr(trainer,j);
                if(fightPokemon){void* pokemon=fightPokemonGetPokemonPtr(fightPokemon);if(pokemon && fightPokemonCheckFightOut(fightPokemon))total+=pokemon_GetMaxHp(pokemon);}
            }
        }
    }
    return total;
}
u32 fightSideGetFightPokemonNokoriHp(void* side,u16 trainerCount,u16 pokemonCount){
    u32 total=0;
    for(u16 i=0;i<trainerCount;i++){
        void* trainer=fightSide_GetFightTrainerPtr(side,i);
        if(fightTrainerCheckValid(trainer)){
            for(u16 j=0;j<pokemonCount;j++){
                void* fightPokemon=fightTrainerGetValidFightPokemonPtr(trainer,j);
                if(fightPokemon){void* pokemon=fightPokemonGetPokemonPtr(fightPokemon);if(pokemon && fightPokemonCheckFightOut(fightPokemon))total+=pokemon_GetHp(pokemon);}
            }
        }
    }
    return total;
}
void* fightSideGetValidFightTrainerPtr(void* side,u16 index){void* trainer=fightSide_GetFightTrainerPtr(side,index);void* result;if(!fightTrainerCheckValid(trainer))result=0;else result=trainer;return result;}
s32 fightSideGetDoFightTrainerCount(void* side){
    s32 count=0;
    for(u8 i=0;i<2;i++)if(fightTrainerCheckDoFight(fightSide_GetFightTrainerPtr(side,i)))++count;
    return count;
}
bool fightSideCheckValid(void* side){if(!side)return 0;if(fightGetFightResultId()==1)return 0;return fightSide_GetFightSideDataId(side)!=0;}
void fightSideCreate(void* side,s32 id){if(side){fightSideInit(side);fightSide_SetFightSideDataId(side,id);}}
void fightSideInitAry(void* data,u16 count){if(data)for(u16 i=0;i<count;i++)fightSideInit((u8*)data+i*0x6ef0);}
void fightSideInit(void* side){
    if(side){
        fightSide_SetFightSideDataId(side,0);
        joutaiInitAry(fightSide_GetJoutaiPtr(side,0),6);
        fightTrainerInitAry(fightSide_GetFightTrainerPtr(side,0),2);
        fightSide_SetMakibisiCheckFlag(side,0);
    }
}

u16 fightSideDB_GetYrot(u16);
u8 fightOutPokemonCheckFightOut(void*);
void* fightTrainer_GetFightoutPokemonPtr(void*,u16);
void* fightOutPokemon_GetMotoFightPokemonPtr(void*);
s16 fightPokemon_GetEntryId(void*);
void fightTrainer_SetEnemyPokemonRegist(void*,s16);
void fightSideRegistFightSideEnemyPokemonFightAll(void* side,void* enemy,u32,u16 trainerCount,u16 pokemonCount){
    for(u16 i=0;i<trainerCount;i++){
        void* trainer=fightSide_GetFightTrainerPtr(side,i);
        if(fightTrainerCheckValid(trainer)){
            for(u16 j=0;j<pokemonCount;j++){
                void* pokemon=fightTrainer_GetFightoutPokemonPtr(trainer,j);
                if(fightOutPokemonCheckFightOut(pokemon)){
                    s16 id=fightPokemon_GetEntryId(fightOutPokemon_GetMotoFightPokemonPtr(pokemon));
                    if(id>=0)fightTrainer_SetEnemyPokemonRegist(enemy,id);
                }
            }
        }
    }
}
void fightSideGetFightTrainerGridParam(u16 side,u16 trainerCount,u16 trainer,u8* reversed,s8* offset){
    if(!reversed || !offset)return;
    *reversed=fightSideDB_GetYrot(side)!=0;
    *offset=0;
    switch(trainerCount){
    case 1:break;
    case 2:
        if(*reversed==1){
            switch(trainer){case 0:*offset=1;break;case 1:*offset=-1;break;}
        }else{
            switch(trainer){case 0:*offset=-1;break;case 1:*offset=1;break;}
        }
        break;
    }
}
void* fightSideDataBiosGetPtr(u16);
void fightSideDataBiosSetYrot(void*,u16);
void fightSideDataBiosSetFightTrainerStatusMenuDataId(void*,u8,u32);
void fightSideDataBiosSetFightoutPokemonStatusMenuDataId(void*,u8,u32);
void fightSideBiosSetFightSideDataId(void*,u16);
void fightSideBiosSetMakibisiCheckFlag(void*,u8);
u16 fightSideDataBiosGetYrot(void*);
u32 fightSideDataBiosGetFightTrainerStatusMenuDataId(void*,u8);
u32 fightSideDataBiosGetFightoutPokemonStatusMenuDataId(void*,u8);
u16 fightSideBiosGetFightSideDataId(void*);
void* fightSideBiosGetJoutaiPtr(void*,u32);
void* fightSideBiosGetFightTrainerPtr(void*,u32);
u8 fightSideBiosGetMakibisiCheckFlag(void*);
void fightSideSetStatus(void* side,u16 data,u16 field,u32 index,u32 value){
    if(field==0 || field>=10)return;
    if(field<4)side=fightSideDataBiosGetPtr(data);
    if(!side)return;
    switch(field){
    case 1:fightSideDataBiosSetYrot(side,value);break;
    case 2:fightSideDataBiosSetFightTrainerStatusMenuDataId(side,index,value);break;
    case 3:fightSideDataBiosSetFightoutPokemonStatusMenuDataId(side,index,value);break;
    case 5:fightSideBiosSetFightSideDataId(side,value);break;
    case 8:fightSideBiosSetMakibisiCheckFlag(side,value!=0);break;
    }
}
u32 fightSideGetStatus(void* side,u16 data,u16 field,u32 index){
    if(field==0 || field>=10)return 0;
    if(field<4)side=fightSideDataBiosGetPtr(data);
    if(!side)return 0;
    switch(field){
    case 1:return fightSideDataBiosGetYrot(side);
    case 2:return fightSideDataBiosGetFightTrainerStatusMenuDataId(side,index);
    case 3:return fightSideDataBiosGetFightoutPokemonStatusMenuDataId(side,index);
    case 5:return fightSideBiosGetFightSideDataId(side);
    case 6:return (u32)fightSideBiosGetJoutaiPtr(side,index);
    case 7:return (u32)fightSideBiosGetFightTrainerPtr(side,index);
    case 8:return fightSideBiosGetMakibisiCheckFlag(side);
    default:return 0;
    }
}
}
