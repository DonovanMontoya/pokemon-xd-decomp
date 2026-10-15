#include <game/pxdvs/app/fight/fightTrainerAiWazaPrivate.hpp>
extern "C" {
s32 fightTrainerAiSelectFightActionWaza(void *arg0, void *arg1, u16 arg2) {
    void *sp14;
    void *enemies[8];
    u16 moves[8];
    s16 slots[8];
    s16 sp10;
    s32 var_r23;
    s32 var_r3;
    s32 var_r3_2;
    u16 var_r29;
    void *temp_r3_4;
    void *temp_r3_5;
    void *var_r24;
    void *var_r28;

    s32 temp_r29 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    u8 var_r26 = fightOutPokemon_GetFixAiWaza(arg1);
    u8 temp_r24 = fightOutPokemon_GetFixAiDef(arg1);
    u16 temp_r25 = fightAi_GetWazaDataIDFromFixActWaza(arg0, arg1, var_r26);
    var_r24 = fightAi_GetWazaDataIDFromFixActDef(arg0, arg1, temp_r24);
    u16 temp_r3 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, moves, slots, 1);
    if (temp_r3 == 0) {
        return 0;
    }
    u16 temp_r3_2 = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, arg0, enemies, 0, 1);
    if (temp_r3_2 == 0) {
        return 0;
    }
    if ((var_r26 != 6) && (temp_r25 != 0) && (temp_r25 != 0x176) && (var_r24 != 0U)) {
        if (fightAi_FixedActCheck(arg0, arg1, temp_r25, var_r24) == 1) {
            var_r29 = temp_r25;
            var_r28 = var_r24;
            var_r23 = var_r26 - 1;
            goto block_50;
        }
        fightOutPokemon_SetFixAiWaza(arg1, 6);
        var_r26 = 6;
        goto block_11;
    }
block_11:
    if (fightTrainerAiDB_GetDefensePokemonRndSelectFlag(temp_r29) == 1) {
        var_r3 = HSD_Rand() % temp_r3_2;
    } else {
        sp14 = 0U;
        sp10 = -1;
        var_r3 = _fightTrainerAiWazaSubDefensePokemon__FP13FIGHT_TRAINERP15FightOutPokemonUsPUsUsPP15FightOutPokemonPP15FightOutPokemonPs(arg0, arg1, temp_r3, moves, temp_r3_2, enemies, &sp14, &sp10);
    }
    if (var_r3 < 0) {
        if ((sp14 != 0U) && (sp10 >= 0)) {
            s32 temp_r24_2 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(sp14,arg2);
            u16 temp_r3_3 = fightTrainerAiGetFightOutPokemonWazaDataId(arg0, arg1, (u8) sp10);
            if (temp_r3_3 != 0) {
                fightOutPokemonCreateFightActionAttackWaza(arg1, 0, 0x13, 0, &fight_action_data_waza, temp_r3_3, temp_r24_2, (s8) sp10,0);
                return 1;
            }
            return 0;
        }
        return 0;
    }
    var_r28 = enemies[var_r3];
    if (var_r28 == 0U) {
        return 0;
    }
    if (var_r26 != 6) {
        if ((temp_r25 != 0) && (temp_r25 != 0x176) && (var_r24 == 0U)) {
            var_r24 = var_r28;
            if (wazaDB_GetRangeId(temp_r25) == 5) {
                var_r24 = arg1;
            }
            if (fightAi_FixedActCheck(arg0, arg1, temp_r25, var_r24) == 1) {
                var_r29 = temp_r25;
                var_r28 = var_r24;
                var_r23 = var_r26 - 1;
                goto block_50;
            }
            if (var_r24 == fightTargetGetPtr(8, arg1, arg2)) {
                fightOutPokemon_SetFixAiWaza(arg1, 6);
                goto block_37;
            }
            temp_r3_4 = fightTargetGetPtr(0xE, var_r24, arg2);
            if ((temp_r3_4 != 0U) && (fightAi_FixedActCheck(arg0, arg1, temp_r25, temp_r3_4) == 1)) {
                var_r29 = temp_r25;
                var_r28 = temp_r3_4;
                var_r23 = var_r26 - 1;
                goto block_50;
            }
            fightOutPokemon_SetFixAiWaza(arg1, 6);
            goto block_37;
        }
block_37:
        if (((temp_r25 == 0) || (temp_r25 == 0x176)) && (var_r24 != 0U)) {
            var_r28 = var_r24;
        }
        goto block_41;
    }
block_41:
    if (fightTrainerAiDB_GetWazaRndSelectFlag(temp_r29) == 1) {
        var_r3_2 = HSD_Rand() % temp_r3;
    } else {
        var_r3_2 = _fightTrainerAiWazaSubWaza__FP13FIGHT_TRAINERP15FightOutPokemonUsPUsPsP15FightOutPokemonUs(arg0, arg1, temp_r3, moves, slots, var_r28, arg2);
    }
    if (var_r3_2 < 0) {
        return 0;
    }
    var_r29 = moves[var_r3_2];
    if (var_r29 == 0) {
        return 0;
    }
    var_r23 = slots[var_r3_2];
    if (var_r23 < 0) {
        return 0;
    }
block_50:
    temp_r3_5 = fightSeqSelectDefensePokemonPtr(arg1, var_r29, arg2, fightTrainerAiWazaSelectDefensePokemon, 1, 0, -1);
    if (temp_r3_5 != 0U) {
        var_r28 = temp_r3_5;
    }
    if (var_r28 == 0U) {
        return 0;
    }
    s32 temp_r3_6 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(var_r28, arg2);
    fightOutPokemonCreateFightActionAttackWaza(arg1, 0, 0x13, 0, &fight_action_data_waza, var_r29, temp_r3_6, (s8) var_r23,0);
    return 1;
}

s32 _fightTrainerAiWazaSubWaza__FP13FIGHT_TRAINERP15FightOutPokemonUsPUsPsP15FightOutPokemonUs(void *trainer,void *pokemon,u16 count,u16 *moves,s16 *slots,void *defender,u16 fightType) {
    s32 scores[8],damageByMove[8],remainingByMove[8],averages[8];
    void *side=fightTargetGetPtrAsNowFightType(3,trainer);
    u8 trainers=fightFloor_GetFightTypeTrainerNum(0);
    u8 entryCount=fightFloor_GetFightTypeEntryPokemonNum(0);
    u8 outCount=fightFloor_GetFightTypeFightoutPokemonNum(0);
    s32 ai=fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    u8 revise=fightTrainerAiDB_GetLastValueRevise();
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,pokemon);
    u8 part=fightTrainerAiGetFightOutPokemonPartDataId(trainer,pokemon);
    fightSideGetHikaeFightPokemonNum(side,trainers,entryCount,outCount);
    for(u16 i=0;i<8;i++){scores[i]=0;damageByMove[i]=0;remainingByMove[i]=0;averages[i]=0;}
    u16 hp=fightTrainerAiGetFightOutPokemonNowHp(trainer,defender);
    s32 bestDamage=-65535;
    s32 bestRemaining=-65535;
    s32 bestAverage=0;
    for(u16 i=0;i<count;i++){
        u16 move=moves[i];
        if(move&&move!=0x176){
            damageByMove[i]=fightTrainerAiWazaDoWazaDamageFunc(trainer,pokemon,move,defender,0);
            s32 damage=damageByMove[i];
            remainingByMove[i]=hp-damage;
            if(fightTrainerAiIsWazaTypeId(trainer,move,1)==1){
                if(bestDamage<damage&&damage!=0)bestDamage=damage;
                s32 remaining=remainingByMove[i];
                if(remaining<=0){
                    if(bestRemaining<remaining)bestRemaining=remaining;
                    averages[i]=fightTrainerAiGetWazaAvg(trainer,move);
                    s32 average=averages[i];
                    if(bestAverage<average)bestAverage=average;
                }
            }
        }
    }
    for(u16 i=0;i<count;i++){
        u16 move=moves[i];
        if(move){
            s16 slot=slots[i];
            if(slot>=0){
                u16 element=fightTrainerAiGetWazaZokuseiDataId(trainer,move,pokemon);
                s32 range=fightTrainerAiGetWazaRangeId(trainer,move);
                AiWazaFunc function=wazaDB_GetFightTrainerAiWazaValueFuncPtr(move);
                scores[i]=fightTrainerAiWazaDoWazaValueFunc(trainer,pokemon,move,defender);
                if(fightTrainerAiWazaDoWazaHitFunc(trainer,pokemon,move,defender)==1){
                    if(function==fightTrainerAiWazaValueToriaezutukae)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,58);
                    else scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,56);
                }else scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,57);
                if(element!=9&&fightTrainerAiIsWazaTypeId(trainer,move,1)==1){
                    if(fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(trainer,defender,element,fightTrainerAiGetWazaIryoku(trainer,move))==0x42)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,59);
                    if(fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(trainer,defender,element,fightTrainerAiGetWazaIryoku(trainer,move))==0x43)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,60);
                }
                for(u16 j=0;j<3;j++){
                    u8 type=fightTrainerAiGetWazaTypeId(trainer,move,(u8)j);
                    if(type)scores[i]=fightTrainerAiReviseValueByAddsubDataId(scores[i],fightTrainerPokemonPartDB_GetWazaTypeRevise(part,type),trainer,61);
                }
                if(element!=9){for(u16 j=0;j<2;j++){
                    u8 preferred=fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(ai,(u8)j);
                    if(preferred!=9&&element==preferred)scores[i]=fightTrainerAiReviseValueByAddsubDataId(scores[i],fightTrainerAiDB_GetZokuseiReviseValue(ai,(u8)j),trainer,62);
                }}
                for(u16 j=0;j<3;j++){
                    u8 type=fightTrainerAiGetWazaTypeId(trainer,move,(u8)j);
                    if(type){for(u16 k=0;k<2;k++){
                        u8 preferred=fightTrainerAiDB_GetWazaTypeReviseTypeDataId(ai,(u8)k);
                        if(preferred&&type==preferred)scores[i]=fightTrainerAiReviseValueByAddsubDataId(scores[i],fightTrainerAiDB_GetWazaTypeReviseValue(ai,(u8)k),trainer,63);
                    }}
                }
                if(fightTrainerAiIsWazaTypeId(trainer,move,1)==1){
                    if(bestDamage<=damageByMove[i])scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,64);
                    s32 remaining=remainingByMove[i];
                    if(remaining<0)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,65);
                    if(remaining<=0)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,66);
                    if(remaining<=0&&bestAverage<=averages[i])scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,67);
                }
                if(fightTrainerAiIsWazaTypeId(trainer,move,2)==1&&fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer,pokemon)==1)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,68);
                if(fightTrainerAiIsWazaAvgTakai(trainer,move)==1)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,69);
                if((u8)range==4&&fightFloorGetValidFightOutPokemonCount(0,1,defender,1)>=2)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,70);
                if(fightTrainerAiIsFightOutPokemonNokoriWazaPpHikui(trainer,pokemon,(u8)slot)==1)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,71);
                if(fightTrainerAiGetWazaRiskFlag(trainer,move)==1)scores[i]=fightTrainerAiAddValueByAddsubDataId(scores[i],trainer,72);
                if(dbgMenuFightGetFightTrainerAiLastValueReviseFlag()==1)scores[i]=fightTrainerAiAddValue(scores[i],(HSD_Rand()%(revise*2+1))-revise);
            }
        }
    }
    s32 selected=fightTrainerAiGetValueAryMaxBanme(scores,count,1);
    s32 result=-1;
    if(selected>=0)result=selected;
    return result;
}

s32 _fightTrainerAiWazaSubDefensePokemon__FP13FIGHT_TRAINERP15FightOutPokemonUsPUsUsPP15FightOutPokemonPP15FightOutPokemonPs(void *trainer,void *pokemon,u16 moveCount,u16 *moves,u16 enemyCount,void **enemies,void **selectedDefense,s16 *selectedSlot) {
    s32 scores[8],damage[8];
    void *allies[8];
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    u8 revise=fightTrainerAiDB_GetLastValueRevise();
    u16 electricMoves[11]={52,83,172,53,126,299,7,315,307,221,237};
    s16 choiceSlots[8];
    u8 canKnockout[8],canHit[8];
    u16 statusMoves[4]={92,261,77,139};
    s16 slot;
    u16 hiddenPower,hiddenElement;
    u8 fixed=fightOutPokemon_GetFixAiWaza(pokemon);
    u16 allyCount=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,allies,1,1);
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,pokemon);
    if(fixed==6){for(u16 i=0;i<allyCount;i++){
        void *ally=allies[i];
        if(!ally||!fightOutPokemonCheckFightOut(ally)||pokemon==ally)continue;
        if(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,ally,18)==1&&fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer,ally,58)==0){
            s16 count=0;
            for(u16 j=0;j<11;j++){
                u16 move=electricMoves[j];
                if(move==237){pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(pokemon),&hiddenPower,&hiddenElement);if(hiddenElement!=10)continue;}
                if(fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer,pokemon,move,&slot,1)!=0&&slot>=0)choiceSlots[count++]=slot;
            }
            if(count>0){slot=choiceSlots[HSD_Rand()%count];if(selectedDefense)*selectedDefense=ally;if(selectedSlot)*selectedSlot=slot;return -1;}
        }
        if((fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,ally,62)==1||fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,ally,63)==1)&&fightTrainerAiIsFightOutPokemonJoutaiNormal(trainer,ally)==1){
            s16 count=0;
            for(u16 j=0;j<4;j++)if(fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer,pokemon,statusMoves[j],&slot,1)!=0&&slot>=0)choiceSlots[count++]=slot;
            if(count>0){slot=choiceSlots[HSD_Rand()%count];if(selectedDefense)*selectedDefense=ally;if(selectedSlot)*selectedSlot=slot;return -1;}
        }
        u8 swap=0;
        if(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,ally,54)==1)swap=1;
        if(fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer,ally)==2&&(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,ally,37)==1||fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,ally,74)==1))swap=1;
        if(fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer,ally)==3&&(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,37)==1||fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,pokemon,74)==1))swap=1;
        if(swap==1&&fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer,pokemon,285,&slot,1)!=0&&slot>=0){if(selectedDefense)*selectedDefense=ally;if(selectedSlot)*selectedSlot=slot;return -1;}
        u8 boost=0;
        if(fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer,ally)==0){
            if(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,ally,20)==1)boost=1;
            u16 item=fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(trainer,ally);
            if(item==8||item==9)boost=1;
        }
        if(boost==1&&fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer,pokemon,207,&slot,1)!=0&&slot>=0){if(selectedDefense)*selectedDefense=ally;if(selectedSlot)*selectedSlot=slot;return -1;}
        if(fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer,ally)==1&&fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer,pokemon)==0&&fightTrainerAiCheckHaveFightOutPokemonWazaDataId(trainer,pokemon,244,&slot,1)!=0&&slot>=0){if(selectedDefense)*selectedDefense=ally;if(selectedSlot)*selectedSlot=slot;return -1;}
    }}
    for(u16 i=0;i<8;i++){scores[i]=0;damage[i]=0;canKnockout[i]=0;canHit[i]=0;}
    s32 bestDamage=0;
    for(u16 i=0;i<enemyCount;i++){
        void *enemy=enemies[i];
        if(enemy&&fightOutPokemonGetFightEntryId(enemy)>=0){
            u16 hp=fightTrainerAiGetFightOutPokemonNowHp(trainer,enemy);
            s32 maximum=0;
            for(u16 j=0;j<moveCount;j++){
                u16 move=moves[j];
                if(move&&move!=0x176){
                    u8 hit=fightTrainerAiWazaDoWazaHitFunc(trainer,pokemon,move,enemy);
                    if(hit==1)canHit[i]=1;
                    if(fightTrainerAiIsWazaTypeId(trainer,move,1)!=0){
                        s32 amount=fightTrainerAiWazaDoWazaDamageFunc(trainer,pokemon,move,enemy,1);
                        if(maximum<amount)maximum=amount;
                        if((s32)hp<fightTrainerAiWazaDoWazaDamageFunc(trainer,pokemon,move,enemy,0)&&hit==1)canKnockout[i]=1;
                    }
                }
            }
            damage[i]=maximum;
            if(bestDamage<damage[i])bestDamage=damage[i];
        }
    }
    for(u16 i=0;i<enemyCount;i++){
        void *enemy=enemies[i];
        if(enemy&&fightOutPokemonGetFightEntryId(enemy)>=0){
            fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,enemy);
            scores[i]=fightAi_ThreatEnemyValue(trainer,pokemon,enemy,-1,1,(s8)canHit[i],(s8)canKnockout[i]);
            if(dbgMenuFightGetFightTrainerAiLastValueReviseFlag()==1)scores[i]=fightTrainerAiAddValue(scores[i],(HSD_Rand()%(revise*2+1))-revise);
        }
    }
    s32 selected=fightTrainerAiGetValueAryMaxBanme(scores,enemyCount,1);
    if(selected<0)return -1;
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,enemies[selected]);
    return selected;
}

s32 fightTrainerAiWazaSelectDefensePokemon(void) {
    return 0;
}

s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(void *trainer,void *attacker,u16 move,void *defender,u8 sum) {
    void *enemies[8];
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    AiWazaFunc function;
    if(fightTrainerAiDB_GetWazaDamageFlag()==1){
        function=wazaDB_GetFightTrainerAiWazaDamageFightPokemonFuncPtr(move);
        if(!function)function=fightTrainerAiWazaDamageFightPokemonNull;
    }else{return 0;}
        u16 count=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
        u8 range=wazaDB_GetRangeId(move);
        u16 i;
        s32 result=0;
        if(sum==1){switch(range){
        case 0:case 3:result=function(trainer,attacker,move,defender);break;
        case 2:case 4:case 6:for(i=0;i<count;i++)result+=function(trainer,attacker,move,defender);break;
        case 1:case 5:case 7:result=function(trainer,attacker,move,defender);break;
        }}else result=function(trainer,attacker,move,defender);
        return result;
}

s32 fightTrainerAiWazaDoWazaDamageFunc(void *trainer,void *attacker,u16 move,void *defender,u8 sum) {
    void *enemies[8];
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    AiWazaFunc function;
    if(fightTrainerAiDB_GetWazaDamageFlag()==1){
        function=wazaDB_GetFightTrainerAiWazaDamageFuncPtr(move);
        if(!function)function=fightTrainerAiWazaDamageNull;
    }else{return 0;}
        u16 count=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
        u8 range=wazaDB_GetRangeId(move);
        u16 i;
        s32 result=0;
        if(sum==1){switch(range){
        case 0:case 3:result=function(trainer,attacker,move,defender);break;
        case 2:case 4:case 6:for(i=0;i<count;i++)result+=function(trainer,attacker,move,defender);break;
        case 1:case 5:case 7:result=function(trainer,attacker,move,defender);break;
        }}else result=function(trainer,attacker,move,defender);
        return result;
}

u8 fightTrainerAiWazaDoWazaHitFunc(void *trainer,void *attacker,u16 move,void *defender) {
    void *enemies[8];
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    AiWazaHitFunc function;
    if(fightTrainerAiDB_GetWazaHitFlag()==1){function=wazaDB_GetFightTrainerAiWazaHitFuncPtr(move);if(!function)function=fightTrainerAiWazaHitNull;}else{return 1;}
    u16 count=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
    u8 range=wazaDB_GetRangeId(move);
    u8 result=0;
    switch(range){
    case 0:case 3:
        if(_fightTrainerAiWazaDoWazaHitFuncPre__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemon(trainer,attacker,move,defender)==0)return 0;
        return function(trainer,attacker,move,defender);
    case 2:case 4:case 6:
        for(u16 i=0;i<count;i++){
            if(_fightTrainerAiWazaDoWazaHitFuncPre__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemon(trainer,attacker,move,defender)==0)result=0;
            else result=function(trainer,attacker,move,enemies[i]);
            if(result==1)return result;
        }
        return result;
    case 1:case 5:case 7:
        if(_fightTrainerAiWazaDoWazaHitFuncPre__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemon(trainer,attacker,move,defender)==0)return 0;
        result=function(trainer,attacker,move,defender);
    default:return result;
    }
}

u8 _fightTrainerAiWazaDoWazaHitFuncPre__FP13FIGHT_TRAINERP15FightOutPokemonUsP15FightOutPokemon(void *arg0, void *arg1, u16 arg2, void *arg3) {
    s16 temp_r25;
    s32 temp_r27;
    u16 temp_r26;
    u8 var_r31;

    temp_r25 = fightTrainerAiGetWazaIryoku(arg0,arg2);
    temp_r26 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg2, arg1);
    temp_r27 = fightTrainerAiGetWazaRangeId(arg0, arg2);
    var_r31 = 1;
    if (fightOutPokemonCheckFightOut(arg3) == 0) {
        return 0U;
    }
    if ((arg2 != 0) && (arg2 != 0x176) && ((u8) temp_r27 != 7) && ((u8) temp_r27 != 5)) {
        if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0xA) == 1) && (temp_r26 == 0xD) && (temp_r25 != 0)) {
            var_r31 = 0;
        }
        if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0xB) == 1) && (temp_r26 == 0xB) && (temp_r25 != 0)) {
            var_r31 = 0;
        }
        if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x12) == 1) && (temp_r26 == 0xA) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3, 7) == 0)) {
            var_r31 = 0;
        }
        if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg3, 0x2B) == 1) && (wazaDB_GetBouon(arg2) == 1)) {
            var_r31 = 0;
        }
    }
    return var_r31;
}

s32 fightTrainerAiWazaDoWazaValueFunc(void *arg0, void *arg1, u16 arg2, void *arg3) {
    s32 (*var_r3)(void*,void*,u16,void*);

    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    if (fightTrainerAiDB_GetWazaInitValueFlag() == 1) {
        var_r3 = wazaDB_GetFightTrainerAiWazaValueFuncPtr(arg2);
        if (var_r3 == NULL) {
            var_r3 = fightTrainerAiWazaValueNull;
        }
    }else{return 0;}
    return var_r3(arg0,arg1,arg2,arg3);
}

}
