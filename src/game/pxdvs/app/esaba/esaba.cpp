#include <global.h>
struct EsaPokemon {u16 unk0,id;u32 rate,digest;};
struct EsaList {u32 *count;EsaPokemon *pokemon;};
struct EsaData {s32 amountFlag,appFlag,stepFlag,pokemonFlag,randomFlag,disableFlag;EsaList **list;};
struct EsaApp {u16 first,last,interval,randomDiv,mode,pad;u32 unused,progressIndex; s32 progressFlag;};
struct EsaSpecial {u16 unused,id;u32 rate,digest;};
extern "C" {
extern EsaData *esabadata;extern u32 *esabadata_number;extern EsaApp *esabaappdata;extern EsaSpecial *esabapokemondata_EX;extern u8 *flag_etc;
u32 GSflagGet(s32);void GSflagSet(s32,u32);u8 GSflagTest(s32);s32 HSD_Rand();void GSthreadSwitch();void heroMoveInitEvent();void heroMoveSetColision(s32);void heroMoveTermEvent();void menuScriptInfoEsa();
u32 heroGetStatus(void*,u16,u32);u32 gamedataGetStatus(void*,u16);void *getHeroPtr__4HeroFv();s32 itemQuantity__4HeroFUs(void*,u16);s32 heroMoveAddStepCallback(void(*)(s32,s32,s32),s32);void underTakerCallBackFunc(s32,s32,s32);u32 underTakerGetMiraboPlace();
void pokemonCreate(void*,u16,u8,u32);void pokemonBiosSetCatchTrainerRnd(void*,u32);u32 pokemonCreateRnd();u32 pokemonCreateRndFit(void*,s32,s32,s32,u32);
u8 menuPanelInputNumber(s32,s32*,s32,s32,u8);void msgctrlSetValue(s32,s32);void winMsgOpen(s32,s32,s32,s32);void winMsgClose(s32);void heroItemDecItemDataId(void*,u16,u16,s32);s32 heroItemAddItemDataId(void*,u16,u16,s32);u16 pcboxAddItem(void*,u16,u16);
static void _esabaCallBackFunc__Fl15FootStepCounterl(s32,s32,s32);static void _esabaCallBackAppFunc__FUs15FootStepCounterl(u16,s32,s32);static void _esabaCallBackEsaFunc__FUs15FootStepCounterl(u16,s32,s32);static void _esabaAppearPokemon__FUs(u16);static void _esabaAppearPokemonSub2__FUs(u16);static void _esabaAppearPokemonSub__FUs(u16);
}
static s32 _esabaHandle;
static inline EsaList *getList(u32 area){if(area>=*esabadata_number)return 0;return *esabadata[area].list;}
static inline u16 listPokemon(u32 area,s32 index){EsaList *list=getList(area);if(list)return list->pokemon[index].id;return 0;}
static inline u32 listRate(u32 area,s32 index){EsaList *list=getList(area);if(list)return list->pokemon[index].rate;return 0;}
static inline u32 listDigest(u32 area,s32 index){EsaList *list=getList(area);if(list)return list->pokemon[index].digest;return 0;}
static inline EsaData *recordAt(s32 offset){return (EsaData*)((u8*)esabadata+offset);}
extern "C" {
static inline void appearPokemon(u16 area,u16 id){u32 trainer;u8 pokemon[0xC4];GSflagSet(esabadata[area].pokemonFlag,id);GSflagSet(esabadata[area].stepFlag,0);switch((s32)id){case 413:case 414:trainer=heroGetStatus(0,2,0);pokemonCreate(pokemon,id,10,gamedataGetStatus(0,1));pokemonBiosSetCatchTrainerRnd(pokemon,trainer);GSflagSet(esabadata[area].randomFlag,pokemonCreateRndFit(pokemon,-1,-1,0,trainer));break;default:GSflagSet(esabadata[area].randomFlag,pokemonCreateRnd());break;}heroMoveInitEvent();heroMoveSetColision(1);GSthreadSwitch();menuScriptInfoEsa();heroMoveTermEvent();}

void esabaSetPokemon(u16 area,u16 id){if(id==0){GSflagSet(esabadata[area].pokemonFlag,0);GSflagSet(esabadata[area].appFlag,0);return;}appearPokemon(area,id);}
u16 esabaGetPokemonMax(u16 area){EsaList *list=getList(area);if(list)return *list->count;return 0;}
s32 esabaGetDigestRate(u16 area){u32 station=area;u16 id=GSflagGet(esabadata[station].pokemonFlag);if(id==esabapokemondata_EX[0].id)return esabapokemondata_EX[0].digest;if(id==esabapokemondata_EX[1].id)return esabapokemondata_EX[1].digest;u16 count=esabaGetPokemonMax(station);s32 index=0;for(;;){if(index>=count){index=0;break;}if(listPokemon(station,index)==GSflagGet(esabadata[station].pokemonFlag))break;index++;}return listDigest(station,index);}

s32 esabaGetEsaItemNum(){return itemQuantity__4HeroFUs(getHeroPtr__4HeroFv(),0x1FF);}
s32 esabaGet(s32 arg0) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r31;

    temp_r30 = arg0 * 0x1C;
    temp_r3 = GSflagGet(recordAt(temp_r30)->amountFlag);
    sp8 = temp_r3;
    if (menuPanelInputNumber(0, &sp8, 0, temp_r3, 1) != 0) {
        temp_r31 = GSflagGet(recordAt(temp_r30)->amountFlag) + -sp8;
        GSflagSet(recordAt(temp_r30)->amountFlag, temp_r31);
        if ((s32) temp_r31 == 0) {
            GSflagSet(recordAt(temp_r30)->appFlag, 0U);
            GSflagSet(recordAt(temp_r30)->stepFlag, 0U);
        }
        return sp8;
    }
    return 0;
}

s32 esabaPut(s32 arg0) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r31;

    temp_r30 = arg0 * 0x1C;
    temp_r3 = GSflagGet(recordAt(temp_r30)->amountFlag);
    sp8 = temp_r3;
    if (menuPanelInputNumber(0, &sp8, 0, 0xA - temp_r3, 1) != 0) {
        temp_r31 = GSflagGet(recordAt(temp_r30)->amountFlag) + (s16) sp8;
        GSflagSet(recordAt(temp_r30)->amountFlag, temp_r31);
        if ((s32) temp_r31 == 0) {
            GSflagSet(recordAt(temp_r30)->appFlag, 0U);
            GSflagSet(recordAt(temp_r30)->stepFlag, 0U);
        }
        return sp8;
    }
    return 0;
}

s32 esabaSet(s32 arg0) {
    s32 sp8;
    s16 temp_r4;
    s32 temp_r26;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r6;
    u16 temp_r3_3;

    
    
    temp_r30 = arg0 * 0x1C;
    temp_r3 = GSflagGet(recordAt(temp_r30)->amountFlag);
    sp8 = temp_r3;
    temp_r26 = itemQuantity__4HeroFUs(getHeroPtr__4HeroFv(),0x1FF);
    GSthreadSwitch();
    msgctrlSetValue(0x2F, sp8);
    winMsgOpen(2, ((s32) (-sp8 | sp8) >> 0x1F) + 0xC92E, 0, 1);
    var_r6 = sp8 + temp_r26;
    if (var_r6 > 0xA) {
        var_r6 = 0xA;
    }
    if (menuPanelInputNumber(sp8,&sp8,0,var_r6,1) != 0) {
        GSflagSet(recordAt(temp_r30)->amountFlag, (s16) sp8);
        if ((s16) sp8 == 0) {
            GSflagSet(recordAt(temp_r30)->appFlag, 0U);
            GSflagSet(recordAt(temp_r30)->stepFlag, 0U);
        }
        var_r27 = 0;
        var_r28 = 0;
        var_r29 = sp8 - temp_r3;
        if (var_r29 != 0) {
            if (var_r29 > 0) {
                heroItemDecItemDataId(0, 0x1FF, (u16) var_r29, -1);
            } else {
                temp_r3_2 = heroItemAddItemDataId(0, 0x1FF, (u16) (var_r29 * -1), -1);
                if (temp_r3_2 == 0) {
                    var_r28 = -var_r29;
                } else if (temp_r3_2 > 0) {
                    var_r28 = -(var_r29 + temp_r3_2);
                    temp_r3_3 = pcboxAddItem(0, 0x1FF, (u16) temp_r3_2);
                    if (temp_r3_3 != 0) {
                        var_r27 = temp_r3_2 - temp_r3_3;
                    } else {
                        var_r27 = temp_r3_2;
                    }
                }
            }
        }
    } else {
        var_r29 = 0;
        winMsgClose(1);
    }
    if (var_r29 != 0) {
        if (var_r29 >= 0) {
            winMsgClose(1);
            msgctrlSetValue(0x2F, var_r29);
            winMsgOpen(2, 0xC930, 1, 1);
            winMsgClose(1);
        } else {
            winMsgClose(1);
            if ((var_r28 == 0) && (var_r27 == 0)) {
                winMsgOpen(2, 0xC932, 1, 1);
                winMsgClose(1);
                var_r29 = 0;
                GSflagSet(recordAt(temp_r30)->amountFlag, (s16) temp_r3);
                if ((s16) temp_r3 == 0) {
                    GSflagSet(recordAt(temp_r30)->appFlag, 0U);
                    GSflagSet(recordAt(temp_r30)->stepFlag, 0U);
                }
            } else {
                if (var_r28 > 0) {
                    msgctrlSetValue(0x2F, var_r28);
                    winMsgOpen(2, 0xC92F, 1, 1);
                    winMsgClose(1);
                }
                if (var_r27 > 0) {
                    msgctrlSetValue(0x2F, var_r27);
                    winMsgOpen(2, 0xC933, 1, 1);
                    winMsgClose(1);
                }
                temp_r4 = (temp_r3 - var_r28) - var_r27;
                if (temp_r4 != 0) {
                    var_r29 = -(temp_r3 - temp_r4);
                    GSflagSet(recordAt(temp_r30)->amountFlag, (s32)temp_r4);
                    if (temp_r4 == 0) {
                        GSflagSet(recordAt(temp_r30)->appFlag, 0U);
                        GSflagSet(recordAt(temp_r30)->stepFlag, 0U);
                    }
                }
            }
        }
    }
    winMsgClose(1);
    return var_r29;
}

void esabaSetEsaNum(s32 area,s32 number){GSflagSet(esabadata[area].amountFlag,number);if(number==0){GSflagSet(esabadata[area].appFlag,0);GSflagSet(esabadata[area].stepFlag,0);}}
void esabaHeroCallBackInit(){_esabaHandle=heroMoveAddStepCallback(_esabaCallBackFunc__Fl15FootStepCounterl,0);}
s32 esabaGetPokemonIsRare(s32 area){if(GSflagGet(esabadata[area].pokemonFlag)){u32 trainer=heroGetStatus(0,2,0);u32 random=GSflagGet(esabadata[area].randomFlag);u32 trainerHigh=trainer>>16;u32 trainerLow=(u16)trainer;u32 randomHigh=random>>16;u32 randomLow=(u16)random;return (randomLow^(randomHigh^(trainerHigh^trainerLow)))<8;}return 0;}
void esabaSetPokemonRnd(s32 area,u32 random){GSflagSet(esabadata[area].randomFlag,random);}
u32 esabaGetPokemonRnd(s32 area){return GSflagGet(esabadata[area].randomFlag);}
u16 esabaGetPokemonID(s32 area){return GSflagGet(esabadata[area].pokemonFlag);}
u32 esabaGetEsaNum(s32 area){return GSflagGet(esabadata[area].amountFlag);}
static void _esabaCallBackFunc__Fl15FootStepCounterl(s32 id,s32 kind,s32 steps){underTakerCallBackFunc(id,kind,steps);for(u16 area=0;area<(u16)*esabadata_number;area++){if(GSflagGet(esabadata[area].amountFlag)){if(GSflagGet(esabadata[area].pokemonFlag))_esabaCallBackEsaFunc__FUs15FootStepCounterl(area,kind,steps);else _esabaCallBackAppFunc__FUs15FootStepCounterl(area,kind,steps);}}}
static void _esabaCallBackAppFunc__FUs15FootStepCounterl(u16 area,s32,s32 steps){u32 station;u16 divisor;u16 interval;u32 count;u32 current=underTakerGetMiraboPlace();station=area;const s32 places[3]={90,91,92};if(current!=(u32)places[area]){if(!GSflagTest(esabadata[station].disableFlag)){u32 elapsed=GSflagGet(esabadata[station].appFlag);elapsed+=steps;if(elapsed>=esabaappdata->first){if(elapsed>=esabaappdata->last)_esabaAppearPokemon__FUs(area);else {interval=esabaappdata->interval;count=GSflagGet(esabadata[station].stepFlag);count+=steps;if(count>=interval){divisor=esabaappdata->randomDiv;if((u16)HSD_Rand()%divisor==0)_esabaAppearPokemon__FUs(area);else GSflagSet(esabadata[station].stepFlag,count-interval);}else GSflagSet(esabadata[station].stepFlag,count);}}GSflagSet(esabadata[station].appFlag,elapsed);}}}
static void _esabaCallBackEsaFunc__FUs15FootStepCounterl(u16 area,s32,s32 steps){u16 id=GSflagGet(esabadata[area].pokemonFlag);if(!GSflagTest(esabadata[area].disableFlag)){u32 digest;if(id==esabapokemondata_EX[0].id)digest=esabapokemondata_EX[0].digest;else if(id==esabapokemondata_EX[1].id)digest=esabapokemondata_EX[1].digest;else {u16 count=esabaGetPokemonMax(area);s32 index=0;for(;;){if(index>=count){index=0;break;}if(listPokemon(area,index)==GSflagGet(esabadata[area].pokemonFlag))break;index++;}digest=listDigest(area,index);}u32 elapsed=GSflagGet(esabadata[area].stepFlag)+steps;if(elapsed>=digest){elapsed-=digest;s32 food=GSflagGet(esabadata[area].amountFlag)-1;if(food==0){GSflagSet(esabadata[area].pokemonFlag,0);GSflagSet(esabadata[area].appFlag,0);}GSflagSet(esabadata[area].amountFlag,food);}GSflagSet(esabadata[area].stepFlag,elapsed);}}
static void _esabaAppearPokemon__FUs(u16 area){s32 progressIndex=esabaappdata->progressIndex;u32 progress=GSflagGet(0x3C4);if(progress>=*(u32*)(flag_etc+(progressIndex<<5)+8)){u16 mode=esabaappdata->mode;if(GSflagGet(esabaappdata->progressFlag)==mode){_esabaAppearPokemonSub__FUs(area);return;}}_esabaAppearPokemonSub2__FUs(area);}
static void _esabaAppearPokemonSub2__FUs(u16 area){u16 cumulative;u16 i;u8 exists;u16 count=esabaGetPokemonMax(area);exists=0;cumulative=0;for(i=exists;i<(u16)*esabadata_number;i++){if((u16)GSflagGet(esabadata[i].pokemonFlag)==esabapokemondata_EX[1].id){exists=1;break;}}if(!exists&&(u16)((u16)HSD_Rand()%100)<(u16)esabapokemondata_EX[1].rate){appearPokemon(area,esabapokemondata_EX[1].id);return;}u16 random=(u16)HSD_Rand()%100;for(s32 i=0;i<count;i++){cumulative+=listRate(area,i);if(cumulative>=random){appearPokemon(area,listPokemon(area,i));return;}}}
static void _esabaAppearPokemonSub__FUs(u16 area){u16 firstIndex,secondIndex;u16 count=esabaGetPokemonMax(area);HSD_Rand();u8 firstExists=0;u16 cumulative=0;u16 first=esabapokemondata_EX[0].rate;u16 second=esabapokemondata_EX[1].rate;for(firstIndex=0;firstIndex<(u16)*esabadata_number;firstIndex++){if((u16)GSflagGet(esabadata[firstIndex].pokemonFlag)==esabapokemondata_EX[0].id){firstExists=1;break;}}if(firstExists)first=0;u8 secondExists=0;for(secondIndex=0;secondIndex<(u16)*esabadata_number;secondIndex++){if((u16)GSflagGet(esabadata[secondIndex].pokemonFlag)==esabapokemondata_EX[1].id){secondExists=1;break;}}if(secondExists)second=0;u16 random=(u16)HSD_Rand()%100;if(random<first){appearPokemon(area,esabapokemondata_EX[0].id);return;}u16 both=first+second;if(first==0)both=second;if(random<both){appearPokemon(area,esabapokemondata_EX[1].id);return;}u16 ordinary=(u16)HSD_Rand()%100;for(s32 i=0;i<count;i++){cumulative+=listRate(area,i);if(cumulative>=ordinary){appearPokemon(area,listPokemon(area,i));return;}}}
}
