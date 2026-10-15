#include <global.h>
static void* _fightTargetGetTargetPtrToFightSidePtr(void*,u16);


extern "C" {
extern u8 fight_target_data[];
extern u32 fight_target_data_number;

u8 fightTargetDataBiosGetRelativeFlag(void* data) {
    if (data == 0) return 0;
    return *((u8*)data + 1);
}

u32 fightTargetDataBiosGetBuff(void* data) {
    if (data == 0) return 0;
    return *(u32*)((u8*)data + 4);
}

u8 fightTargetDataBiosGetStatusKid(u8* data) {
    if (data == 0) return 0;
    return *data;
}

void* fightTargetDataBiosGetPtr(u16 id) {
    if (id >= fight_target_data_number) return 0;
    return fight_target_data + id * 8;
}

void *fightTargetGetPtr(u16,void*,u16);
u8 fightFloor_GetFightType(void*);
s32 fightTargetIsHostSide(void *target,u16 type) {
 void *host=fightTargetGetPtr(4,0,type); if(!host)return 0;
 void *side=fightTargetGetPtr(2,target,type); if(!side)return 0; return side==host;
}
void *fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u16 id,u16 type) {
 void *host=fightTargetGetPtr(4,0,type); if(!host)return 0;
 void *result=fightTargetGetPtr(id,host,type); if(!result)result=0; return result;
}
u16 fightTargetGetTragetPtrToRelativeFightTargetId(void *base,void *target,u16 type) {
 for(u16 i=0;i<fight_target_data_number;i++) {
  if(i!=0) {void *data=fightTargetDataBiosGetPtr(i); if(data && fightTargetDataBiosGetRelativeFlag(data)!=0 && fightTargetGetPtr(i,base,type)==target) return i;}
 }return 0;
}
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void *target,u16 type) {
 void *host=fightTargetGetPtr(4,0,type);if(!host)return 0;
 return fightTargetGetTragetPtrToRelativeFightTargetId(host,target,type);
}
void *fightTargetGetPtrAsNowFightType(u16 id,void *base) {return fightTargetGetPtr(id,base,fightFloor_GetFightType(0));}
}
extern "C" {
void* fightFloorGetNowPtr();
void* fightFloorGetStatus(void*,u32,u32,u32);
void* fightFloor_GetFightSidePtr(void*,u16);
void* fightSide_GetFightTrainerPtr(void*,u16);
void* fightTrainer_GetFightPokemonPtr(void*,u16);
void* fightTrainer_GetFightoutPokemonPtr(void*,u16);
void* fightTypeDataBiosGetPtr(u16);
u8 fightTypeDataBiosGetTrainerNum(void*);
u8 fightTypeDataBiosGetFightoutPokemonNum(void*);
u8 fightTypeDataBiosGetEntryPokemonNum(void*);
void* fightFloor_GetAttackPokemonPtr(void*);
void* fightFloor_GetDefensePokemonPtr(void*);
void* fightFloor_GetEscapePokemonPtr(void*);
void* fightFloor_GetIrekaePokemonPtr(void*);
void* fightFloor_GetKizetuPokemonPtr(void*);
void* fightFloor_GetTuikakoukaPokemonPtr(void*);
void* fightFloor_GetTokuseiPokemonPtr(void*);
void* fightFloor_GetItemPokemonPtr(void*);
void* fightFloor_GetAppointPokemonPtr(void*);
void* fightFloor_GetAppointTrainerPtr(void*);
void* fightFloor_GetAppointWazaPtr(void*);
void* fightFloor_GetAppointSidePtr(void*);
void* fightFloor_GetAppointItemPtr(void*);
void* fightTargetGetPtr(u16 id,void* base,u16 type){
    u16 trainerIndex;
    u16 sideIndex;
    u16 trainerCount;
    u16 pokemonIndex;
    u16 pokemonCount;
    u16 sidePokemonIndex;
    void* original;
    void* sides[2];
    void* trainers[4];
    void* pokemon[8];
    if(id==0)return 0;
    void* floor=fightFloorGetNowPtr();
    if(id==1)return floor;
    switch(id){
    case 17:return fightFloor_GetAttackPokemonPtr(floor);
    case 18:return fightFloor_GetDefensePokemonPtr(floor);
    case 19:return fightFloor_GetEscapePokemonPtr(floor);
    case 20:return fightFloor_GetIrekaePokemonPtr(floor);
    case 21:return fightFloor_GetKizetuPokemonPtr(floor);
    case 22:return fightFloor_GetTuikakoukaPokemonPtr(floor);
    case 23:return fightFloor_GetTokuseiPokemonPtr(floor);
    case 24:return fightFloor_GetItemPokemonPtr(floor);
    case 25:return fightFloor_GetAppointPokemonPtr(floor);
    case 26:return fightFloor_GetAppointTrainerPtr(floor);
    case 27:return fightFloor_GetAppointWazaPtr(floor);
    case 28:return fightFloor_GetAppointSidePtr(floor);
    case 29:return fightFloor_GetAppointItemPtr(floor);
    }
    void* typeData=fightTypeDataBiosGetPtr(type);
    if(!typeData)return 0;
    if(base){original=base;base=_fightTargetGetTargetPtrToFightSidePtr(base,type);if(!base)return 0;}
    trainerCount=0;
    pokemonCount=0;
    u8 trainersPerSide=fightTypeDataBiosGetTrainerNum(typeData);
    u8 pokemonPerTrainer=fightTypeDataBiosGetFightoutPokemonNum(typeData);
    for(sideIndex=0;sideIndex<2;++sideIndex){
        sides[sideIndex]=fightFloor_GetFightSidePtr(floor,sideIndex);
        if(id==4 && sideIndex==0)return sides[sideIndex];
        if(id==5 && sideIndex==1)return sides[sideIndex];
        u8 same;
        if(sides[sideIndex]==base){same=1;if(id==2)return sides[sideIndex];}
        else{same=0;if(id==3)return sides[sideIndex];}
        sidePokemonIndex=0;
        for(trainerIndex=0;trainerIndex<trainersPerSide;++trainerIndex){
            trainers[trainerCount]=fightSide_GetFightTrainerPtr(sides[sideIndex],trainerIndex);
            if(id==11 && sideIndex==0 && trainerIndex==0)return trainers[trainerCount];
            if(same==1){
                if(id==6 && trainerIndex==0)return trainers[trainerCount];
                if(id==7 && trainerIndex==1)return trainers[trainerCount];
                if(id==8 && original!=trainers[trainerCount])return trainers[trainerCount];
            }else{
                if(id==9 && trainerIndex==0)return trainers[trainerCount];
                if(id==10 && trainerIndex==1)return trainers[trainerCount];
            }
            for(pokemonIndex=0;pokemonIndex<pokemonPerTrainer;++pokemonIndex){
                pokemon[pokemonCount]=fightTrainer_GetFightoutPokemonPtr(trainers[trainerCount],pokemonIndex);
                if(same==1){
                    if(id==12 && sidePokemonIndex==0)return pokemon[pokemonCount];
                    if(id==13 && sidePokemonIndex==1)return pokemon[pokemonCount];
                    if(id==14 && original!=pokemon[pokemonCount])return pokemon[pokemonCount];
                }else{
                    if(id==15 && sidePokemonIndex==0)return pokemon[pokemonCount];
                    if(id==16 && sidePokemonIndex==1)return pokemon[pokemonCount];
                }
                ++pokemonCount;++sidePokemonIndex;
            }
            ++trainerCount;
        }
    }
    return 0;
}
}
static void* _fightTargetGetTargetPtrToFightSidePtr(void* target,u16 type){
    void* floor=fightFloorGetStatus(0,0,0,0);
    void* data=fightTypeDataBiosGetPtr(type);
    if(!data)return 0;
    u8 trainers=fightTypeDataBiosGetTrainerNum(data);
    u8 active=fightTypeDataBiosGetFightoutPokemonNum(data);
    u8 entry=fightTypeDataBiosGetEntryPokemonNum(data);
    for(u16 s=0;s<2;++s){
        u16 t;
        void* side=fightFloor_GetFightSidePtr(floor,s);
        if(side==target)return side;
        for(t=0;t<trainers;++t){
            void* trainer=fightSide_GetFightTrainerPtr(side,t);
            if(trainer==target)return side;
            u16 p;
            for(p=0;p<entry;++p)if(fightTrainer_GetFightPokemonPtr(trainer,p)==target)return side;
            for(p=0;p<active;++p)if(fightTrainer_GetFightoutPokemonPtr(trainer,p)==target)return side;
        }
    }
    return 0;
}
