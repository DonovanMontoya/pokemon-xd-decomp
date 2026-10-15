#include <global.h>
struct EvoInfo {u8 unk0,pad;u16 unk2;};
extern "C" {
void *heroGetStatus(void*,u16,u16);u8 pokemonCheckValid(void*);u16 pokemonBiosGetPokemonDataId(void*);void *pokemonDataBiosGetPtr(u16);u32 pokemonBiosGetRnd(void*);u8 pokemonDataBiosGetSinkaKind(void*,u16);u16 pokemonDataBiosGetSinkaBuff(void*,u16);u16 pokemonDataBiosGetSinkaPokemonDataId(void*,u16);u16 pokemonBiosGetItemDataId(void*);u16 pokemonBiosGetFriend(void*);u8 pokemonBiosGetLevel(void*);u16 pokemonBiosGetPhyAtk(void*);u16 pokemonBiosGetPhyDef(void*);u8 pokemonBiosGetBeautiful(void*);u8 fightIsFight();void *fightFloorGetGcHeroFightTrainerPtr(void*);void *fightTrainerGetStatus(void*,s32,s32,s32);u8 heroItemCheckHaveItemDataId(void*,u16);u16 pokemonGetSoubiItemDataId(void*);void *itemDataBiosGetPtr(u16);u16 itemDataBiosGetItemSoubiDataId(void*);

s32 pokemonEvolutionCreateAddPokemon(void*,void*,u16);s32 pokemonEvolution(void*,void*,u16,EvoInfo*,u16*);
static void *getPokemonData__FP7Pokemon(void*);static s8 getEmptySlotID__FP4Hero(void*);
void pokemonBiosCopy(void*,void*);void pokemonBiosSetPokemonDataId(void*,u16);void pokemonBiosSetNicknamePtr(void*,const u16*);void pokemonBiosSetItemDataId(void*,u16);void pokemonSetStatus(void*,s32,u16,u32,u32);void pokemonInitJoutai(void*);void pokemonResetBasisStatus(void*);u8 pokemonDataCheckValid(void*,u16);void *pokemonBiosGetAttest(void*);u8 gamedataAttestBiosGetLangareaId(void*);u32 pokemonDataBiosGetName(void*);const u16 *GSmsgGetGSchar(u32);const u16 *pokemonBiosGetNicknamePtr(void*);s32 GScharCmp(const u16*,const u16*);void *savedataGetStatus(void*,u16);void *gamedataBiosGetGamedataAtttestPtr(void*);void pokemonDoItemSoubi(void*,s32,s32);u16 pokemonGetOboeWazaDataId(void*,u8,u8*);s8 pokemonSearchWazaDataId(void*,u16);void heroAddPokemon(void*,void*);void memoDataSet(void*,void*);void fadeSet(u16,f32);void fadeCheck(u8);s32 evolutionOpen(void*,void*,s32,u16*,s32,u8*);void pokemonWazaCreate(void*,u8,u16);void heroItemDecItemDataId(void*,u16,u16,s32);

static s8 getEmptySlotID__FP4Hero(void *hero){s32 i=0;do {if(!pokemonCheckValid(heroGetStatus(hero,3,i)))break;i++;}while(i<6);if(i>=6)return -1;return (s8)i;}
static void evolutionAddPokemon__FP7PokemonUsP4Heroi(void *pokemon,u16 id,void *hero,s32 memo){u8 extra[196];if(id&&getEmptySlotID__FP4Hero(hero)>=0){pokemonEvolutionCreateAddPokemon(extra,pokemon,id);heroAddPokemon(hero,extra);if(memo)memoDataSet(0,extra);}}
s32 pokemonEvolutionAll(void *pokemon,u16 id,u16 extra,EvoInfo *info,void *hero,s32 memo,s32 mode,s32 fade){
 s32 i;u8 evolved[196];u16 moves[20];u16 displayMoves[20];u8 choices[20];
 if(!pokemonCheckValid(pokemon))return 2;if(id==0)return 2;
 s32 count=pokemonEvolution(evolved,pokemon,id,info,moves);if(count<0)return 2;
 if(fade){fadeSet(3,0.5f);fadeCheck(1);}for(i=0;i<count;i++)displayMoves[i]=moves[i];
 s32 result=evolutionOpen(pokemon,evolved,mode,displayMoves,count,choices);
 if(fade){fadeSet(2,0.5f);fadeCheck(1);}if(result==2)return 2;if(result==1)return 1;
 if(memo)memoDataSet(0,evolved);pokemonBiosCopy(pokemon,evolved);for(i=0;i<count;i++){if(choices[i]!=255)pokemonWazaCreate(pokemon,choices[i],moves[i]);}
 if(extra)evolutionAddPokemon__FP7PokemonUsP4Heroi(pokemon,extra,hero,memo);
 if(info->unk0==16){void *inventory=0;if(fightIsFight()){void *trainer=fightFloorGetGcHeroFightTrainerPtr(0);if(trainer)inventory=fightTrainerGetStatus(trainer,0,0x44,0);}heroItemDecItemDataId(inventory,info->unk2,1,-1);}return 0;
}
static const u16 shedinjaName[]={0x30CC,0x30B1,0x30CB,0x30F3,0,0};
s32 pokemonEvolutionCreateAddPokemon(void *out,void *source,u16 id){
 s32 clearIndex;void *data;u16 flags[5]={176,177,178,179,180};u16 stats[12]={163,164,165,166,167,168,169,170,171,172,173,174};
 if(!pokemonDataCheckValid(0,id))return 0;if(!getPokemonData__FP7Pokemon(source))return 0;
 pokemonBiosCopy(out,source);pokemonBiosSetPokemonDataId(out,id);data=getPokemonData__FP7Pokemon(out);if(!data)return 0;
 if(id!=303){const u16 *name=GSmsgGetGSchar(pokemonDataBiosGetName(data));pokemonBiosSetNicknamePtr(out,name);}else {switch((s32)gamedataAttestBiosGetLangareaId(pokemonBiosGetAttest(out))){case 1:pokemonBiosSetNicknamePtr(out,shedinjaName);break;default:pokemonBiosSetNicknamePtr(out,GSmsgGetGSchar(pokemonDataBiosGetName(data)));break;}}
 pokemonBiosSetItemDataId(out,0);pokemonSetStatus(out,0,187,0,0);pokemonSetStatus(out,0,190,0,0);
 for(clearIndex=0;clearIndex<5;clearIndex++)pokemonSetStatus(out,0,flags[clearIndex],0,0);for(clearIndex=0;clearIndex<12;clearIndex++)pokemonSetStatus(out,0,stats[clearIndex],0,0);
 pokemonSetStatus(out,0,175,0,0);pokemonInitJoutai(out);pokemonSetStatus(out,0,188,0,0);pokemonResetBasisStatus(out);return 1;
}
s32 pokemonEvolution(void *out,void *source,u16 id,EvoInfo *info,u16 *moves){u8 index; s32 count=0;if(!pokemonCheckValid(source)||!pokemonDataCheckValid(0,id))return -1;void *data=getPokemonData__FP7Pokemon(source);if(!data)return -1;pokemonBiosCopy(out,source);void *attest=pokemonBiosGetAttest(source);u8 language=gamedataAttestBiosGetLangareaId(gamedataBiosGetGamedataAtttestPtr(savedataGetStatus(0,1)));if(gamedataAttestBiosGetLangareaId(attest)==language){const u16 *nickname=pokemonBiosGetNicknamePtr(out);if(GScharCmp(nickname,GSmsgGetGSchar(pokemonDataBiosGetName(data)))==0)pokemonBiosSetNicknamePtr(out,GSmsgGetGSchar(pokemonDataBiosGetName(pokemonDataBiosGetPtr(id))));}pokemonBiosSetPokemonDataId(out,id);pokemonResetBasisStatus(out);if(info->unk0==6)pokemonDoItemSoubi(out,0,0);u8 level=pokemonBiosGetLevel(out);index=0;for(;;){u16 move=pokemonGetOboeWazaDataId(out,level,&index);if(move==0)break;if(pokemonSearchWazaDataId(out,move)==-1){moves[count++]=move;if(count>=20)break;}index++;}return count;}
static s8 getTemotiEmptySlotID__Fv(void) {
    s32 var_r31;

    var_r31 = 0;
loop_1:
    if (pokemonCheckValid(heroGetStatus(0, 3, (u16)var_r31)) != 0) {
        var_r31 += 1;
        if ((s32) var_r31 < 6) {
            goto loop_1;
        }
    }
    if ((s32) var_r31 >= 6) {
        return -1;
    }
    return (s8) var_r31;
}

static u32 getUniqueRandom__FP7Pokemon(void *arg0) {
    return (pokemonBiosGetRnd(arg0) >> 0x10U) % 10;
}

static s32 getNoon__Fv(void) {
    return 2;
}

static void *getPokemonData__FP7Pokemon(void *arg0) {
    u16 id=pokemonBiosGetPokemonDataId(arg0);if(id==0)return 0;return pokemonDataBiosGetPtr(id);
}

static u16 getEvoPokemonCommunication__FP7PokemonP22POKEMON_EVOLUTION_INFO(void *arg0, EvoInfo *arg1) {
    u16 temp_r31;
    u16 temp_r3_2;
    u16 temp_r3_3;
    s32 var_r29;
    u16 var_r28;
    void *temp_r3;
    u8 temp_r30;

    var_r28 = 0;
    temp_r3 = getPokemonData__FP7Pokemon(arg0);
    if (temp_r3 == 0U) {
        return 0xFFFFU;
    }
    var_r29 = 0;
    do {
        temp_r30 = pokemonDataBiosGetSinkaKind(temp_r3, var_r29);
        temp_r31 = pokemonDataBiosGetSinkaBuff(temp_r3, var_r29);
        switch ((s32) temp_r30) {                   /* irregular */
        case 5:
            temp_r3_2 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
            arg1->unk0 = temp_r30;
            var_r28 = temp_r3_2;
            arg1->unk2 = temp_r31;
            break;
        case 6:
            if (temp_r31 == pokemonBiosGetItemDataId(arg0)) {
                temp_r3_3 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                arg1->unk0 = temp_r30;
                var_r28 = temp_r3_3;
                arg1->unk2 = temp_r31;
            }
            break;
        }
        var_r29 += 1;
    } while ((s32) var_r29 < 5);
    return var_r28;
}

static u16 getEvoPokemonItem__FP7PokemonUsP22POKEMON_EVOLUTION_INFO(void *arg0, u32 arg1, EvoInfo *arg2) {
    u16 temp_r31;
    u16 temp_r3_2;
    s32 var_r29;
    u16 var_r28;
    void *temp_r3;
    u8 temp_r30;

    var_r28 = 0;
    temp_r3 = getPokemonData__FP7Pokemon(arg0);
    if (temp_r3 == 0U) {
        return 0xFFFFU;
    }
    var_r29 = 0;
    do {
        temp_r30 = pokemonDataBiosGetSinkaKind(temp_r3, var_r29);
        temp_r31 = pokemonDataBiosGetSinkaBuff(temp_r3, var_r29);
        switch((s32)temp_r30){default:break;case 7: if (temp_r31 == (u16)arg1) {
            temp_r3_2 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
            arg2->unk0 = temp_r30;
            var_r28 = temp_r3_2;
            arg2->unk2 = temp_r31;
        } break; }
        var_r29 += 1;
    } while ((s32) var_r29 < 5);
    return var_r28;
}

static u16 getEvoPokemonLevelUp__FP7PokemonPUsP22POKEMON_EVOLUTION_INFO(void *arg0, u16 *arg1, EvoInfo *arg2) {
    s32 var_r29;
    void *temp_r3;
    u16 var_r27;
    u8 temp_r24;
    u16 var_r23;
    u32 temp_r22,temp_r22_2,temp_r22_3;
    void *var_r22;
    u16 temp_r3_2,temp_r3_3,temp_r3_4,temp_r3_5,temp_r3_6,temp_r3_7,temp_r3_8,temp_r3_9,temp_r3_10,temp_r3_11,temp_r3_12;
    var_r23 = 0;
    var_r27 = 0;
    temp_r3 = getPokemonData__FP7Pokemon(arg0);
    if (temp_r3 == 0U) {
        return 0xFFFFU;
    }
    var_r29 = 0;
    do {
        temp_r24 = pokemonDataBiosGetSinkaKind(temp_r3, var_r29);
        u16 temp_r26 = pokemonDataBiosGetSinkaBuff(temp_r3, var_r29);
        switch (temp_r24) {
        case 1:
            if (pokemonBiosGetFriend(arg0) >= 0xDCU) {
                temp_r3_2 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                arg2->unk0 = temp_r24;
                var_r23 = temp_r3_2;
                arg2->unk2 = temp_r26;
            }
            break;
        case 2:
            if ((pokemonBiosGetFriend(arg0) >= 0xDCU) && (getNoon__Fv() == 1)) {
                temp_r3_3 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                arg2->unk0 = temp_r24;
                var_r23 = temp_r3_3;
                arg2->unk2 = temp_r26;
            }
            break;
        case 3:
            if ((pokemonBiosGetFriend(arg0) >= 0xDCU) && (getNoon__Fv() == 0)) {
                temp_r3_4 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                arg2->unk0 = temp_r24;
                var_r23 = temp_r3_4;
                arg2->unk2 = temp_r26;
            }
            break;
        case 4:
            if ((s32) pokemonBiosGetLevel(arg0) >= (s32)temp_r26) {
                temp_r3_5 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                arg2->unk0 = temp_r24;
                var_r23 = temp_r3_5;
                arg2->unk2 = temp_r26;
            }
            break;
        case 8:
            if ((s32) pokemonBiosGetLevel(arg0) >= (s32)temp_r26) {
                temp_r22 = pokemonBiosGetPhyAtk(arg0);
                if (pokemonBiosGetPhyDef(arg0) < temp_r22) {
                    temp_r3_6 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                    arg2->unk0 = temp_r24;
                    var_r23 = temp_r3_6;
                    arg2->unk2 = temp_r26;
                }
            }
            break;
        case 9:
            if ((s32) pokemonBiosGetLevel(arg0) >= (s32)temp_r26) {
                temp_r22_2 = pokemonBiosGetPhyAtk(arg0);
                if (temp_r22_2 == pokemonBiosGetPhyDef(arg0)) {
                    temp_r3_7 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                    arg2->unk0 = temp_r24;
                    var_r23 = temp_r3_7;
                    arg2->unk2 = temp_r26;
                }
            }
            break;
        case 10:
            if ((s32) pokemonBiosGetLevel(arg0) >= (s32)temp_r26) {
                temp_r22_3 = pokemonBiosGetPhyAtk(arg0);
                if (pokemonBiosGetPhyDef(arg0) > temp_r22_3) {
                    temp_r3_8 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                    arg2->unk0 = temp_r24;
                    var_r23 = temp_r3_8;
                    arg2->unk2 = temp_r26;
                }
            }
            break;
        case 11:
            if (((s32) pokemonBiosGetLevel(arg0) >= (s32)temp_r26) && (getUniqueRandom__FP7Pokemon(arg0) < 5U)) {
                temp_r3_9 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                arg2->unk0 = temp_r24;
                var_r23 = temp_r3_9;
                arg2->unk2 = temp_r26;
            }
            break;
        case 12:
            if (((s32) pokemonBiosGetLevel(arg0) >= (s32)temp_r26) && (getUniqueRandom__FP7Pokemon(arg0) >= 5U)) {
                temp_r3_10 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                arg2->unk0 = temp_r24;
                var_r23 = temp_r3_10;
                arg2->unk2 = temp_r26;
            }
            break;
        case 14:
            if (((s32) pokemonBiosGetLevel(arg0) >= (s32)temp_r26) && (getTemotiEmptySlotID__Fv() >= 0)) {
                var_r27 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
            }
            break;
        case 15:
            if ((s32) pokemonBiosGetBeautiful(arg0) >= (s32)temp_r26) {
                temp_r3_11 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                arg2->unk0 = temp_r24;
                var_r23 = temp_r3_11;
                arg2->unk2 = temp_r26;
            }
            break;
        case 16:
            if (pokemonBiosGetFriend(arg0) >= 0xDCU) {
                var_r22 = 0;
                if (fightIsFight() != 0) {void *trainer=fightFloorGetGcHeroFightTrainerPtr(0);if(trainer)var_r22=fightTrainerGetStatus(trainer,0,0x44,0);}
                if (heroItemCheckHaveItemDataId(var_r22, temp_r26) != 0) {
                    temp_r3_12 = pokemonDataBiosGetSinkaPokemonDataId(temp_r3, var_r29);
                    arg2->unk0 = temp_r24;
                    var_r23 = temp_r3_12;
                    arg2->unk2 = temp_r26;
                }
            }
            break;
        }
        var_r29 += 1;
    } while ((s32) var_r29 < 5);
    *arg1 = var_r27;
    return var_r23;
}

static u16 getItemSoubiDataID__FP7Pokemon(void *arg0) {
    u16 id=pokemonGetSoubiItemDataId(arg0);
    if(id==0)return 0;
    return itemDataBiosGetItemSoubiDataId(itemDataBiosGetPtr(id));
}

u16 pokemonEvolutionCheck(void *arg0, s32 arg1, EvoInfo *arg2, u16 *arg3, EvoInfo *arg4) {
    u16 sp8;
    u16 var_r3;

    sp8 = 0;
    if (pokemonCheckValid(arg0) == 0) {
        return 0xFFFFU;
    }
    if (getItemSoubiDataID__FP7Pokemon(arg0) == 0x26) {
        *arg3 = sp8;
        return 0;
    }
    switch (arg1) {                                 /* irregular */
    case 0:
        var_r3 = getEvoPokemonLevelUp__FP7PokemonPUsP22POKEMON_EVOLUTION_INFO(arg0, &sp8, arg4);
        break;
    case 1:
        var_r3 = getEvoPokemonItem__FP7PokemonUsP22POKEMON_EVOLUTION_INFO(arg0, (u32)arg2, arg4);
        break;
    case 2:
        var_r3 = getEvoPokemonCommunication__FP7PokemonP22POKEMON_EVOLUTION_INFO(arg0, arg4);
        break;
    default:
        var_r3 = 0xFFFF;
        break;
    }
    *arg3 = sp8;
    return var_r3;
}

}
