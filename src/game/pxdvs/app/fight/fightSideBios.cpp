#include <game/pxdvs/app/fight/fightSideBiosLayout.hpp>
#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>
#pragma dont_inline on
extern "C" {
extern FightSideDataBiosRecord* fight_side_data;
extern u32* fight_side_data_number;
void fightSideDataBiosSetFightoutPokemonStatusMenuDataId(FightSideDataBiosRecord* p,u8 side,u32 id){if(!p)return;if(side>=2)return;p->fightoutPokemonStatusMenuDataId[side]=id;}
void fightSideDataBiosSetFightTrainerStatusMenuDataId(FightSideDataBiosRecord* p,u8 side,u32 id){if(!p)return;if(side>=2)return;p->trainerStatusMenuDataId[side]=id;}
void fightSideDataBiosSetYrot(FightSideDataBiosRecord* p,u16 v){if(p)p->yrot=v;}
u32 fightSideDataBiosGetFightoutPokemonStatusMenuDataId(FightSideDataBiosRecord* p,u8 side){if(p==0)return 0;if(side>=2)return 0;return p->fightoutPokemonStatusMenuDataId[side];}
u32 fightSideDataBiosGetFightTrainerStatusMenuDataId(FightSideDataBiosRecord* p,u8 side){if(p==0)return 0;if(side>=2)return 0;return p->trainerStatusMenuDataId[side];}
u16 fightSideDataBiosGetYrot(FightSideDataBiosRecord* p){if(p==0){return 0;}else{return p->yrot;}}
FightSideDataBiosRecord* fightSideDataBiosGetPtr(u16 id){if(id>=*fight_side_data_number)return 0;return &fight_side_data[id];}
void fightSideBiosSetMakibisiCheckFlag(FightSideBiosObject* p,u8 v){if(p)p->makibisiCheckFlag=v;}
void fightSideBiosSetFightSideDataId(FightSideDataBiosRecord* p,u16 v){if(p)p->yrot=v;}
u8 fightSideBiosGetMakibisiCheckFlag(FightSideBiosObject* p){if(p==0){return 0;}else{return p->makibisiCheckFlag;}}
FightOutPokemon* fightSideBiosGetFightTrainerPtr(FightSideBiosObject* p,u16 side){if(p==0)return 0;if(side>=2)return 0;return (FightOutPokemon*)((u8*)p+0x64+side*0x3744);}
FightJoutai* fightSideBiosGetJoutaiPtr(FightSideBiosObject* p,u16 index){if(p==0)return 0;if(index>=6)return 0;return (FightJoutai*)((u8*)p+4+index*0x10);}
u16 fightSideBiosGetFightSideDataId(FightSideDataBiosRecord* p){if(p==0){return 0;}else{return p->yrot;}}
}
