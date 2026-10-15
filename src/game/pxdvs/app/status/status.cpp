#include <dolphin/types.h>
extern "C" {
s32 fightFloorGetStatus(s32, s32, s32, s32);        
s32 fightFloorSetStatus(s32, s32, s32, s32, s32);   
s32 fightSideGetStatus(s32, s32, s32, s32);         
void fightSideSetStatus(s32, s32, s32, s32, s32);      
s32 fightTrainerGetStatus(s32, s32, s32, s32);      
void fightTrainerSetStatus(s32, s32, s32, s32, s32);   
s32 gamedataGetStatus(s32, s32);                    
void gamedataSetStatus(s32, s32, s32);                 
s32 heroGetStatus(s32, s32, s32);                   
void heroSetStatus(s32, s32, s32);                     
s32 itemGetStatus(s32, s32, s32, s32);              
void itemSetStatus(s32, s32, s32, s32, s32);           
s32 pcboxGetStatus(s32, s32, s32);                  
void pcboxSetStatus(s32, s32, s32);                    
s32 pokemonGetStatus(s32, s32, s32, s32);           
void pokemonSetStatus(s32, s32, s32, s32, s32);        
s32 wazaGetStatus(s32, s32, s32, s32);              
void wazaSetStatus(s32, s32, s32, s32, s32);           

}
extern "C" s32 statusSetStatus(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 var_r31;

    var_r31 = 0;
    switch (arg0) {
    case 0:break;
    case 1:
        gamedataSetStatus(arg1, arg3, arg5);
        break;
    case 2:
        pcboxSetStatus(arg1, arg3, arg5);
        break;
    case 3:
        heroSetStatus(arg1, arg3, arg5);
        break;
    case 4:
        itemSetStatus(arg1, arg2, arg3, arg4, arg5);
        break;
    case 5:
        pokemonSetStatus(arg1, arg2, arg3, arg4, arg5);
        break;
    case 6:
        wazaSetStatus(arg1, arg2, arg3, arg4, arg5);
        break;
    case 7:
        var_r31 = fightFloorSetStatus(arg1, arg2, arg3, arg4, arg5);
        break;
    case 8:
        fightSideSetStatus(arg1, arg2, arg3, arg4, arg5);
        break;
    case 9:
        fightTrainerSetStatus(arg1, arg2, arg3, arg4, arg5);
        break;
    }
    return var_r31;
}

extern "C" s32 statusGetStatus(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    switch (arg0) {
    case 0:
        return 0;
    case 1:
        return gamedataGetStatus(arg1, arg3);
    case 2:
        return pcboxGetStatus(arg1, arg3, arg4);
    case 3:
        return heroGetStatus(arg1, arg3, arg4);
    case 4:
        return itemGetStatus(arg1, arg2, arg3, arg4);
    case 5:
        return pokemonGetStatus(arg1, arg2, arg3, arg4);
    case 6:
        return wazaGetStatus(arg1, arg2, arg3, arg4);
    case 7:
        return fightFloorGetStatus(arg1, arg2, arg3, arg4);
    case 8:
        return fightSideGetStatus(arg1, arg2, arg3, arg4);
    case 9:
        return fightTrainerGetStatus(arg1, arg2, arg3, arg4);
    default:
        return 0;
    }
}
