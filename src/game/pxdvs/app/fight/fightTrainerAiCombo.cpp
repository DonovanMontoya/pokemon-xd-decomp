#include <game/pxdvs/app/fight/fightTrainerAiComboPrivate.hpp>
extern "C" {
u8 fixAct_v05_1[]={1,3,2,3,3,3,4,3,6};
u8 fixAct_v35_1[]={4,4,3,5,2,5,4,5,4,5,6};
u8 fixAct_v35_2[]={1,5,3,4,3,3,3,3,3,3,6};
u8 fixAct_v18_1[]={1,5,1,5,1,5,1,5,2,5,6};
u8 fixAct_v02_1[]={1,3,2,3,7};
u8 fixAct_v04_1[]={1,5,1,5,6};
u8 fixAct_v04_2[]={1,5,2,5,6};
u8 fixAct_v07_1[]={1,5,2,3,3,3,6};
u8 fixAct_v09_1[]={1,4,2,3,6};
u8 fixAct_v10_1[]={1,3,7};
u8 fixAct_v12_1[]={1,3,2,5,6};
u8 fixAct_v24_1[]={1,5,2,5,7};
u8 fixAct_v25_1[]={1,5,2,5,3,5,6};
u8 fixAct_v25_2[]={1,5,2,5,2,5,6};
u8 fixAct_v26_1[]={1,5,2,5,7};
u8 fixAct_v27_1[]={1,5,2,5,6};
u8 fixAct_v30_1[]={1,5,2,5,3,5,7};
u8 fixAct_t01_1[]={1,5,2,5,3,5,7};
u8 fixAct_oore1[]={1,2,6};
FixedActionShell fixAiShell[]={
{0,{0,0,0},{0,0}},
{0,{0,0,0},{fixAct_v02_1,0}},
{0,{0,0,0},{fixAct_v04_1,fixAct_v04_2}},
{0,{0,0,0},{fixAct_v05_1,0}},
{0,{0,0,0},{fixAct_v07_1,0}},
{0,{0,0,0},{fixAct_v10_1,0}},
{0,{0,0,0},{fixAct_v12_1,0}},
{1,{0,0,0},{fixAct_v24_1,fixAct_v24_1}},
{0,{0,0,0},{fixAct_v25_1,fixAct_v25_2}},
{1,{0,0,0},{fixAct_v26_1,fixAct_v26_1}},
{0,{0,0,0},{fixAct_v27_1,fixAct_v27_1}},
{0,{0,0,0},{fixAct_v30_1,fixAct_v30_1}},
{1,{0,0,0},{fixAct_v35_1,fixAct_v35_2}},
{0,{0,0,0},{fixAct_v18_1,0}},
{0,{0,0,0},{fixAct_t01_1,0}},
{0,{0,0,0},{fixAct_oore1,0}},
{0,{0,0,0},{fixAct_v09_1,0}}
};
void fightAi_FixedActIrekaeInit(FightOutPokemon *pokemon){
    void *deck=getDeckTrainerObj__11DeckTrainerFUl(deckDataVirtualDB_GetEnemyDeck__FUs(fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0)))));
    if(fixAiShell[getFixedActionID__11DeckTrainerCFv(deck)].reset==0)fightOutPokemon_SetFixAiWaza(pokemon,6);
}
bool fightAi_FixedActCheck(FIGHT_TRAINER *trainer,FightOutPokemon *attacker,u16 move,FightOutPokemon *defender){
    ComboHit hit=wazaDB_GetFightTrainerAiWazaHitFuncPtr(move);
    if(!trainer)return 0;if(!attacker)return 0;if(!defender)return 0;
    if(hit(trainer,attacker,move,defender)==0)return 0;
    if(fightOutPokemonIsHinsi(defender)==1)return 0;
    return fightAi_CanMoveAppointWaza(trainer,attacker,move)!=0;
}
FightOutPokemon *fightAi_GetWazaDataIDFromFixActDef(FIGHT_TRAINER*,FightOutPokemon *pokemon,u8 target){
    u8 fightType=fightFloor_GetFightType(0);
    switch(target){case 1:return pokemon;case 2:return fightTargetGetPtr(0xE,pokemon,fightType);case 3:return fightTargetGetPtr(0xF,pokemon,fightType);case 4:return fightTargetGetPtr(0x10,pokemon,fightType);default:return 0;}
}
u16 fightAi_GetWazaDataIDFromFixActWaza(FIGHT_TRAINER*,FightOutPokemon *pokemon,u8 slot){
    s32 value=slot;
    switch(value){case 1:case 2:case 3:case 4:return pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(pokemon),(u16)(value-1));default:return 0;}
}

s16 fightAiCombo_GetAllWazaValueTable(ComboWaza *table,s16 value,FIGHT_TRAINER *trainer,FightOutPokemon **,FightOutPokemon **enemies,s8 weather){return fightAiCombo_GetAllWazaTableDefValue(trainer,enemies,table,value,weather);}
s32 fightAiCombo_Act(FIGHT_TRAINER *trainer,FightOutPokemon **allies,u16 allyCount){
    ComboWaza selected;
    FightOutPokemon *enemies[8];
    void *deck;
    u16 enemyCount;
    ComboAction action;
    u8 active;
    u8 i;
    if(!trainer)return 0;
    enemyCount=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
    for(i=0;i<4;i++){
        deck=getDeckTrainerObj__11DeckTrainerFUl(fightTrainer_GetFightTrainerDataId(trainer));
        ComboDispatch *entry=&comboid[getComboID__11DeckTrainerCFUc(deck,i)];
        action=entry->action;
        active=getComboActive__11DeckTrainerCFUc(deck,i);
        if(active && action && action(trainer,allies,allyCount,enemies,enemyCount,&selected,active)==1){fightAi_CreateAction_FromAllWazaValid(trainer,&selected);return 1;}
    }
    return 0;
}

s32 fightAiCombo_ActContinue(FIGHT_TRAINER *trainer,FightOutPokemon *pokemon){
    FightOutPokemon *enemies[8];
    u16 count=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
    u8 id=getComboFuncId__15FightOutPokemonFv(pokemon);
    ComboContinue action=comboid[id].continuation;
    if(!id)return 0;
    if(!action){setComboFuncId__15FightOutPokemonFUc(pokemon,0);return 0;}
    if(action(trainer,pokemon,enemies,count)==0){setComboFuncId__15FightOutPokemonFUc(pokemon,0);return 0;}
    return 1;
}
}

extern "C" {
void fightAi_FixedAct(FIGHT_TRAINER *trainer){
    u8 turn=fightFloor_GetTurnCount(0);
    u8 lengths[2]={0,0};
    void *encounter=fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0));
    u16 deckId;
    if(fightFloorIsNowEncountVirtualBattle(0)==1)deckId=deckDataVirtualDB_GetEnemyDeck__FUs(fightEncountDataBiosGetDiskId(encounter));
    else deckId=fightEncountDataBiosGetFightTrainerDataId(encounter,1);
    void *deck=getDeckTrainerObj__11DeckTrainerFUl(deckId);
    FixedActionShell *shell=&fixAiShell[getFixedActionID__11DeckTrainerCFv(deck)];
    u8 *sequences[2]={0,0};
    sequences[0]=shell->sequence[0];sequences[1]=shell->sequence[1];
    for(u8 i=0;i<2;i++)if(sequences[i])for(u8 j=0;j<10;j++){
        u8 command=sequences[i][j];lengths[i]++;if(command==6 || command==7)break;
    }
    s32 position=(turn-1)*2;
    for(u8 i=0;i<2;i++){
        FightOutPokemon *pokemon=fightTrainer_GetFightoutPokemonPtr(trainer,i);
        if(fightOutPokemon_GetFixAiWaza(pokemon)!=6){
            fightOutPokemon_SetFixAiDef(pokemon,0);
            u8 *sequence=sequences[i];
            if(sequence){
                s32 limit=lengths[i]-1;
                u8 index;
                if(position<limit)index=position;
                else if(position==limit){
                    index=position;
                    if(sequence[index]==6){fightOutPokemon_SetFixAiWaza(pokemon,6);continue;}
                    if(sequence[index]==7)index=position%limit;
                }else index=position%limit;
                u8 move=sequence[index],target=sequence[index+1];
                if(move<6){if(move!=0)fightOutPokemon_SetFixAiWaza(pokemon,move);else fightOutPokemon_SetFixAiWaza(pokemon,6);}
                if(target!=0){if(target<6)fightOutPokemon_SetFixAiDef(pokemon,target);}else fightOutPokemon_SetFixAiWaza(pokemon,6);
            }
        }
    }
}
s16 fightAiCombo_GetValidValue(FightOutPokemon **allies,u16 allyCount,FightOutPokemon **enemies,u16 enemyCount){
    s16 value=50;
    FightOutPokemon *firstAlly=0,*lastAlly=0,*firstEnemy=0,*lastEnemy=0;
    for(u8 i=0;i<allyCount;i++){
        if(!allies[i] && allies[fightAi_getAnotherPokeNo(i)]){firstAlly=allies[fightAi_getAnotherPokeNo(i)];lastAlly=allies[fightAi_getAnotherPokeNo(i)];}
        else if(allies[i] && !allies[fightAi_getAnotherPokeNo(i)]){firstAlly=allies[i];lastAlly=allies[i];}
        else if(fightFloorCmpfightOutPokemonNimbleness(0,allies[i],allies[fightAi_getAnotherPokeNo(i)],0)==1){firstAlly=allies[i];lastAlly=allies[fightAi_getAnotherPokeNo(i)];}
        else{lastAlly=allies[i];firstAlly=allies[fightAi_getAnotherPokeNo(i)];}
    }
    for(u8 i=0;i<enemyCount;i++){
        if(!enemies[i] || enemies[fightAi_getAnotherPokeNo(i)]){firstEnemy=enemies[fightAi_getAnotherPokeNo(i)];lastEnemy=enemies[fightAi_getAnotherPokeNo(i)];}
        else if(enemies[i] || !enemies[fightAi_getAnotherPokeNo(i)]){firstEnemy=enemies[i];lastEnemy=enemies[i];}
        else if(fightFloorCmpfightOutPokemonNimbleness(0,enemies[i],enemies[fightAi_getAnotherPokeNo(i)],0)==1){firstEnemy=enemies[i];lastEnemy=enemies[fightAi_getAnotherPokeNo(i)];}
        else{lastEnemy=enemies[i];firstEnemy=enemies[fightAi_getAnotherPokeNo(i)];}
    }
    if(fightFloorCmpfightOutPokemonNimbleness(0,lastEnemy,lastAlly,0)==0)value=fightTrainerAiAddValueByAddsubDataId(50,fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,lastAlly),0x297);
    if(fightFloorCmpfightOutPokemonNimbleness(0,firstEnemy,firstAlly,0)==1)value=fightTrainerAiAddValueByAddsubDataId(value,fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,lastAlly),0x298);
    fightFloorCmpfightOutPokemonNimbleness(0,lastAlly,firstEnemy,0);
    return value;
}
}

extern "C" {
void ComboStatusUp(FIGHT_TRAINER *trainer,ComboWaza *table,s16 *score){
    s16 value=*score;
    for(u8 i=0;i<2;i++)if(table->attackers[i]){
        for(u8 j=0;j<14;j++){
            ComboStatusMove *entry=&statusUpWazaTbl[j];
            if(table->moves[i]==entry->move && table->attackers[i]){
                u8 current=0;
                switch(entry->stat){case 1:current=fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(trainer,table->attackers[i]);break;case 2:current=fightTrainerAiGetFightOutPokemonAbiCntPhyDef(trainer,table->attackers[i]);break;case 3:current=fightTrainerAiGetFightOutPokemonAbiCntSubayasa(trainer,table->attackers[i]);break;case 4:current=fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(trainer,table->attackers[i]);break;case 5:current=fightTrainerAiGetFightOutPokemonAbiCntSpeDef(trainer,table->attackers[i]);break;case 6:current=fightTrainerAiGetFightOutPokemonAbiCntAvg(trainer,table->attackers[i]);break;case 7:current=fightTrainerAiGetFightOutPokemonAbiCntAvd(trainer,table->attackers[i]);break;}
                if(current+entry->amount>12)value=0;
            }
        }
    }
    *score=value;
}
void ComboStatusDown(FIGHT_TRAINER *trainer,FightOutPokemon **enemies,ComboWaza *table,s16 *score){
    u16 immune[3]={0x1D,0x49,0};
    s16 value=*score;
    for(u8 i=0;i<2;i++)if(table->attackers[i]){
        for(u8 j=0;j<18;j++){
            ComboStatusMove *entry=&statusDownWazaTbl[j];
            if(table->moves[i]==entry->move){
                switch(table->eligible[i]){
                case 0:case 1:
                    if(table->defenders[i]){
                        u8 current=0,immuneCount=0;
                        switch(entry->stat){case 1:current=fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(trainer,table->defenders[i]);immune[2]=0x34;immuneCount=3;break;case 2:current=fightTrainerAiGetFightOutPokemonAbiCntPhyDef(trainer,table->defenders[i]);immuneCount=2;break;case 3:current=fightTrainerAiGetFightOutPokemonAbiCntSubayasa(trainer,table->defenders[i]);immuneCount=2;break;case 4:current=fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(trainer,table->defenders[i]);immuneCount=2;break;case 5:current=fightTrainerAiGetFightOutPokemonAbiCntSpeDef(trainer,table->defenders[i]);immuneCount=2;break;case 6:current=fightTrainerAiGetFightOutPokemonAbiCntAvg(trainer,table->defenders[i]);immune[2]=0x33;immuneCount=3;break;case 7:current=fightTrainerAiGetFightOutPokemonAbiCntAvd(trainer,table->defenders[i]);immuneCount=2;break;}
                        if(current-(entry->amount-1)<=0)value=0;
                        for(u8 k=0;k<immuneCount;k++)if(fightAi_GetTokuseiHaveFlag(trainer,table->defenders[i],immune[k])>=1)value=0;
                    }
                    break;
                case 2:
                    for(u8 k=0;k<2;k++)if(enemies[k]){
                        u8 current=0,immuneCount=0;
                        switch(entry->stat){case 1:current=fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(trainer,enemies[k]);immune[2]=0x34;immuneCount=3;break;case 2:current=fightTrainerAiGetFightOutPokemonAbiCntPhyDef(trainer,enemies[k]);immuneCount=2;break;case 3:current=fightTrainerAiGetFightOutPokemonAbiCntSubayasa(trainer,enemies[k]);immuneCount=2;break;case 4:current=fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(trainer,enemies[k]);immuneCount=2;break;case 5:current=fightTrainerAiGetFightOutPokemonAbiCntSpeDef(trainer,enemies[k]);immuneCount=2;break;case 6:current=fightTrainerAiGetFightOutPokemonAbiCntAvg(trainer,enemies[k]);immune[2]=0x33;immuneCount=3;break;case 7:current=fightTrainerAiGetFightOutPokemonAbiCntAvd(trainer,enemies[k]);immuneCount=2;break;}
                        if(current-(entry->amount-1)<=0)value=0;
                        for(u8 l=0;l<immuneCount;l++)if(fightAi_GetTokuseiHaveFlag(trainer,table->defenders[i],immune[l])>=1)value=0;
                    }
                    break;
                }
            }
        }
    }
    *score=value;
}
void ComboStatusChangeSub(FIGHT_TRAINER *trainer,FightOutPokemon **enemies,ComboWaza *table,s16 *score,u8 status){
    u16 immune[2]={0,0};
    u16 moves[20];
    u8 immuneCount=0,moveCount=0;
    s16 value=*score;
    switch(status){
    case 8:moveCount=6;for(u8 i=0;i<6;i++)moves[i]=NemuraseWazaTbl[i];immune[0]=0xF;immune[1]=0x48;immuneCount=2;break;
    case 5:moveCount=3;for(u8 i=0;i<3;i++)moves[i]=MahiWazaTbl[i];immuneCount=1;immune[0]=7;break;
    case 9:moveCount=5;for(u8 i=0;i<5;i++)moves[i]=KonranWazaTbl[i];immuneCount=1;immune[0]=0x14;break;
    case 3:moveCount=3;for(u8 i=0;i<3;i++)moves[i]=DokuWazaTbl[i];immuneCount=1;immune[0]=0x11;break;
    case 6:moveCount=1;for(u8 i=0;i<1;i++)moves[i]=YakedoWazaTbl[i];immuneCount=1;immune[0]=0x29;break;
    }
    for(u8 i=0;i<2;i++)if(table->attackers[i])for(u8 j=0;j<moveCount;j++)if(table->moves[i]==moves[j]){
        switch(table->eligible[i]){
        case 0:case 1:
            if(table->defenders[i]){
                if(fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer,table->defenders[i],status)==1)value=0;
                for(u8 k=0;k<immuneCount;k++)if(fightAi_GetTokuseiHaveFlag(trainer,table->defenders[i],immune[k])>=1)value=0;
            }
            break;
        case 2:{
            u8 blocked=0;
            for(u8 k=0;k<2;k++)if(enemies[k]){
                if(fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer,enemies[k],status)==1){blocked++;break;}
                else for(u8 l=0;l<immuneCount;l++)if(fightAi_GetTokuseiHaveFlag(trainer,enemies[i],immune[l])>=1){blocked++;break;}
            }
            if(blocked>=2)value=0;else if(blocked==1)value=(s16)((f64)value*0.5);
            break;
        }
        }
    }
    *score=value;
}
void ComboStatusChange(FIGHT_TRAINER *trainer,FightOutPokemon **enemies,ComboWaza *table,s16 *score){
    ComboStatusChangeSub(trainer,enemies,table,score,8);ComboStatusChangeSub(trainer,enemies,table,score,5);ComboStatusChangeSub(trainer,enemies,table,score,9);ComboStatusChangeSub(trainer,enemies,table,score,3);ComboStatusChangeSub(trainer,enemies,table,score,6);
}
void ComboPower(FIGHT_TRAINER *trainer,FightOutPokemon **enemies,ComboWaza *table,s16 *score){
    s16 value=*score;
    for(u8 i=0;i<2;i++)if(table->attackers[i] && wazaIsWazaTypeId(table->moves[i],1)==1){
        switch(table->eligible[i]){
        case 0:case 1:if(table->defenders[i] && fightAi_HitCheckWazaAboutJoutaiAndType(trainer,table->attackers[i],table->defenders[i],table->moves[i])==0)value=0;break;
        case 2:{
            u8 blocked=0;
            for(u8 j=0;j<2;j++)if(enemies[j] && fightAi_HitCheckWazaAboutJoutaiAndType(trainer,table->attackers[i],enemies[j],table->moves[i])==0){blocked=1;break;}
            if(blocked>=2)value=0;else if(blocked==1)value=(s16)((f64)value*0.5);
            break;
        }
        }
    }
    *score=value;
}
s16 fightAiCombo_GetAllWazaTableDefValue(FIGHT_TRAINER *trainer,FightOutPokemon **enemies,ComboWaza *table,s16 base,s16 weather){
    FightOutPokemon *allies[8];
    u16 count=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,allies,0,1);
    s16 value=(u8)(base*((table->probability[0]+table->probability[1])/2)/100);
    ComboPower(trainer,enemies,table,&value);ComboStatusChange(trainer,enemies,table,&value);ComboStatusDown(trainer,enemies,table,&value);ComboStatusUp(trainer,table,&value);
    if(value<=0)return 0;
    for(u8 i=0;i<2;i++){
        if(count>=2){
            if(!table->attackers[i])continue;
            if(wazaIsWazaTypeId(table->moves[i],1)==1){
                s32 first=fightAi_ThreatEnemyValue(trainer,table->attackers[i],allies[0],weather,0,-1,-1);
                s32 second=fightAi_ThreatEnemyValue(trainer,table->attackers[i],allies[1],weather,0,-1,-1);
                switch(table->eligible[i]){case 0:value+=first-second;break;case 1:value+=second-first;break;}
            }
        }
        s32 damage=0;
        for(u8 j=0;j<2;j++)damage+=table->damage[j][i];
        if(table->defenders[i]){
            u16 hp=pokemon_GetHp(fightOutPokemonGetPokemonPtr(table->defenders[i]));
            if(hp)value+=(damage*100/hp)/10;
        }
    }
    if(value<0)value=0;return value;
}
s16 fightAiCombo_GetAllWazaMaxValueTable(ComboWaza *table,u8 count,s16 base,FIGHT_TRAINER *trainer,FightOutPokemon **allies,FightOutPokemon **enemies,ComboWaza *out,s8 weather){
    u8 bestIndexes[64];s16 values[64];
    s16 best=0;
    // Retail leaves this count indeterminate until a positive candidate occurs.
    // Keep its per-iteration choice while skipping the otherwise undefined draw.
    u8 bestCount=0;
    for(u8 i=0;i<count;i++)if(table){
        ComboWaza *entry=&table[i];
        if(((entry->attackers[0]==allies[0] || entry->attackers[0]==allies[1]) && entry->attackers[1]==allies[0]) || entry->attackers[1]==allies[1]){
            values[i]=fightAiCombo_GetAllWazaTableDefValue(trainer,enemies,entry,base,weather);
            if(best<values[i]){bestIndexes[0]=i;best=values[i];bestCount=1;}
            else if(best==values[i] && best>0){bestIndexes[bestCount]=i;bestCount++;}
        }
        if(bestCount)fightAi_CopyAllWazaValidTable(out,&table[bestIndexes[HSD_Rand()%bestCount]]);
    }
    return best;
}
}
