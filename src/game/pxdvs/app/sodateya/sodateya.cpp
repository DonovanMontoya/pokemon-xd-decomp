#include <global.h>
struct Sodateya {u8 active,level;u16 steps;u32 dp;u8 pokemon[0xC4];};
extern "C" {
void *savedataGetStatus(void*,u16);void *heroBiosGetPokemonPtr(void*,u16);s32 heroGetPokeomCount(void*);u8 pokemonCheckValid(void*);u8 pokemonBiosGetLevel(void*);u8 pokemonBiosGetDarkFlag(void*);u32 pokemonBiosGetDp(void*);u16 pokemonBiosGetDarkpokemonDataId(void*);u16 pokemonBiosGetHp(void*);u32 pokemonBiosGetExp(void*);f32 pokemonGetDp(void*);
void pokemonInit(void*);void pokemonAllKaihuku(void*);u8 pokemonIsJoutaiDataId(void*,u16);void pokemonInitJoutaiDataId(void*,u16);void *getDarkPokemon__7PokemonFv(void*);void setPlace__11DarkPokemonF16darkPokemonWhereUc(void*,s32,u8);
u8 darkPokemonBiosGetReliveFlag(u16);u8 darkPokemonBiosGetInformationFlag(u16);s32 darkPokemonBiosGetSteps(u16);void darkPokemonBiosSetSteps(u16,u16);void pokemonAddDpFormPokemonDpFilterId(void*,s32,s32);void pokemonGrowBasisStatus(void*,u32);void pokemonOboeWaza(void*,u8,s32,u8*);
u32 GSflagGet(s32);void GSflagSet(s32,u32);void GSthreadSwitch();void heroMoveInitEvent();void heroMoveSetColision(s32);void heroMoveTermEvent();void menuScriptInfoRelive(void*,s32);s32 heroMoveAddStepCallback(void(*)(s32,s32,s32),s32);
static void _sodateyaCallBackFunc__Fl15FootStepCounterl(s32,s32,s32);
}
static s32 _sodateyaHandle;
static inline Sodateya *getWork(Sodateya *work){if(!work)work=(Sodateya*)savedataGetStatus(0,11);return work;}
static inline u32 getInitialDP(Sodateya *work){work=getWork(work);if(work->active)return work->dp;return 0xFFFFFFFF;}
static inline u8 getInitialLevel(Sodateya *work){work=getWork(work);if(work->active)return work->level;return 0xFF;}
static inline void setActive(Sodateya *work,u8 active){work=getWork(work);if(work)work->active=active;}
static inline void setLevel(Sodateya *work,u8 level){work=getWork(work);if(work)work->level=level;}
static inline void setSteps(Sodateya *work,u16 steps){work=getWork(work);if(work)work->steps=steps;}
static inline u16 validDark(void *pokemon,s32 mode){u16 id=pokemonBiosGetDarkpokemonDataId(pokemon);if(id){if(mode==1){if(darkPokemonBiosGetReliveFlag(id)||id==73)id=0;else if(pokemonGetDp(pokemon)==0.0f){}else id=0;}else if(darkPokemonBiosGetReliveFlag(id)||pokemonBiosGetHp(pokemon)==0||id==73)id=0;}return id;}
static inline void notifyRelive(void *pokemon,s32 mode){u16 id=validDark(pokemon,mode);if(id&&darkPokemonBiosGetInformationFlag(id)==0){heroMoveInitEvent();heroMoveSetColision(1);GSthreadSwitch();menuScriptInfoRelive(pokemon,1);heroMoveTermEvent();}}
extern "C" {
s32 sodateyaeChekcRais(){Sodateya *work=getWork(0);if(!work)return -1;switch(work->active){case 1:return 1;case 0:return 0;default:return -1;}}
u8 *sodateyaGetPokemonPtr(Sodateya *work){work=getWork(work);return work->pokemon;}
s32 sodateyaGetPokemonDPValue(){sodateyaGetPokemonPtr(0);u32 initial=getInitialDP(0);return (s32)(initial-pokemonBiosGetDp(sodateyaGetPokemonPtr(0)))/100;}
s32 sodateyaGetPokemonLevelUpValue(){u8 initial=getInitialLevel(0);u8 current=pokemonBiosGetLevel(sodateyaGetPokemonPtr(0));s32 result=initial;return current-result;}
s32 sodateyaCalcPrice(s32 levels){s32 dpPrice;if(getInitialDP(0)){s32 gain=sodateyaGetPokemonDPValue();if(gain)dpPrice=gain*100+100;else dpPrice=0;}else dpPrice=0;dpPrice=100*levels+dpPrice;dpPrice+=100;return dpPrice;}
void sodateyaReclaim(s32 slot){void *hero=savedataGetStatus(0,2);void *pokemon=heroBiosGetPokemonPtr(hero,slot);Sodateya *work=getWork(0);if(pokemon){u8 *stored=sodateyaGetPokemonPtr(work);if(stored){memcpy(pokemon,stored,0xC4);if(pokemonBiosGetDarkFlag(stored))pokemonBiosGetDp(stored);void *dark=getDarkPokemon__7PokemonFv(pokemon);if(dark)setPlace__11DarkPokemonF16darkPokemonWhereUc(dark,1,0);setActive(work,0);pokemonInit(stored);}}pokemonAllKaihuku(pokemon);}
void sodateyaRaise(s32 slot){void *pokemon;void *hero=savedataGetStatus(0,2);pokemon=heroBiosGetPokemonPtr(hero,slot);s32 count=heroGetPokeomCount(hero);Sodateya *work=getWork(0);u8 success;if(!pokemon)success=0;else {setLevel(work,pokemonBiosGetLevel(pokemon));u8 *stored=sodateyaGetPokemonPtr(work);if(!stored)success=0;else {if(pokemonIsJoutaiDataId(pokemon,62))pokemonInitJoutaiDataId(pokemon,62);memcpy(stored,pokemon,0xC4);if(pokemonBiosGetDarkFlag(pokemon))work->dp=pokemonBiosGetDp(pokemon);else work->dp=0;void *dark=getDarkPokemon__7PokemonFv(pokemon);if(dark)setPlace__11DarkPokemonF16darkPokemonWhereUc(dark,4,0);setActive(work,1);pokemonInit(pokemon);success=1;}}if(success&&(s32)slot<6){s32 i=slot;while(i<count-1){void *destination=heroBiosGetPokemonPtr(hero,i);pokemon=heroBiosGetPokemonPtr(hero,i+1);if(!pokemonCheckValid(pokemon))break;memcpy(destination,pokemon,0xC4);i++;}pokemonInit(pokemon);}}
void sodateyaInit(Sodateya *work){work=getWork(work);if(work){setSteps(work,0);work->level=0;work->active=0;}}
void sodateyaHeroCallBackInit(){_sodateyaHandle=heroMoveAddStepCallback(_sodateyaCallBackFunc__Fl15FootStepCounterl,0);}
static void _sodateyaCallBackFunc__Fl15FootStepCounterl(s32, s32 arg1, s32 arg2) {
    u8 sp8;
    s32 temp_r0_2;
    s32 var_r3;
    u16 temp_r0;
    u16 temp_r3_2;
    u16 temp_r3_3;
    u16 temp_r3_4;
    u16 temp_r3_5;
    u16 var_r24;
    u16 var_r24_2;
    u16 var_r24_3;
    u16 var_r25;
    s32 var_r28;
    s32 var_r31;
    u32 temp_r3_6;
    u32 temp_r5;
    u32 var_r4;
    u8 *temp_r25;
    u8 *temp_r26;
    u8 *temp_r3;
    u8 *temp_r3_7;

    temp_r3 = (u8*)savedataGetStatus(0, 2);
    if (temp_r3 != NULL) {
        for(var_r28=0;var_r28<6U;var_r28++) {
            temp_r26 = (u8*)heroBiosGetPokemonPtr(temp_r3, var_r28);
            if ((pokemonCheckValid(temp_r26) != 0) && (temp_r26 != NULL)) {
                var_r25 = pokemonBiosGetDarkpokemonDataId(temp_r26);
                if (var_r25 != 0) {
                    if (arg1 == 1) {
                        if ((darkPokemonBiosGetReliveFlag(var_r25) != 0) || (var_r25 == 0x49)) {
                            var_r25 = 0;
                        } else if (pokemonGetDp(temp_r26) == 0.0f) {

                        } else {
                            var_r25 = 0;
                        }
                    } else if ((darkPokemonBiosGetReliveFlag(var_r25) != 0) || (pokemonBiosGetHp(temp_r26) == 0) || (var_r25 == 0x49)) {
                        var_r25 = 0;
                    }
                }
                if (var_r25 != 0) {
                    if (pokemonBiosGetDp(temp_r26) != 0U) {
                        temp_r0 = darkPokemonBiosGetSteps(var_r25) + arg2;
                        if (temp_r0 >= 0x100U) {
                            pokemonAddDpFormPokemonDpFilterId(temp_r26, 0, 1);
                            if (pokemonGetDp(temp_r26) == 0.0f) {
                                var_r24 = pokemonBiosGetDarkpokemonDataId(temp_r26);
                                if (var_r24 != 0) {
                                    if (arg1 == 1) {
                                        if ((darkPokemonBiosGetReliveFlag(var_r24) != 0) || (var_r24 == 0x49)) {
                                            var_r24 = 0;
                                        } else if (pokemonGetDp(temp_r26) == 0.0f) {

                                        } else {
                                            var_r24 = 0;
                                        }
                                    } else if ((darkPokemonBiosGetReliveFlag(var_r24) != 0) || (pokemonBiosGetHp(temp_r26) == 0) || (var_r24 == 0x49)) {
                                        var_r24 = 0;
                                    }
                                }
                                if ((var_r24 != 0) && (darkPokemonBiosGetInformationFlag(var_r24) == 0)) {
                                    heroMoveInitEvent();
                                    heroMoveSetColision(1);
                                    GSthreadSwitch();
                                    menuScriptInfoRelive(temp_r26, 1);
                                    heroMoveTermEvent();
                                }
                                darkPokemonBiosSetSteps(var_r25, 0U);
                            } else {
                                darkPokemonBiosSetSteps(var_r25, (u16) (temp_r0 - 0x100));
                            }
                        } else {
                            darkPokemonBiosSetSteps(var_r25, temp_r0);
                        }
                    } else {
                        var_r24_2 = pokemonBiosGetDarkpokemonDataId(temp_r26);
                        if (var_r24_2 != 0) {
                            if (arg1 == 1) {
                                if ((darkPokemonBiosGetReliveFlag(var_r24_2) != 0) || (var_r24_2 == 0x49)) {
                                    var_r24_2 = 0;
                                } else if (pokemonGetDp(temp_r26) == 0.0f) {

                                } else {
                                    var_r24_2 = 0;
                                }
                            } else if ((darkPokemonBiosGetReliveFlag(var_r24_2) != 0) || (pokemonBiosGetHp(temp_r26) == 0) || (var_r24_2 == 0x49)) {
                                var_r24_2 = 0;
                            }
                        }
                        if ((var_r24_2 != 0) && (darkPokemonBiosGetInformationFlag(var_r24_2) == 0)) {
                            heroMoveInitEvent();
                            heroMoveSetColision(1);
                            GSthreadSwitch();
                            menuScriptInfoRelive(temp_r26, 1);
                            heroMoveTermEvent();
                        }
                    }
                }
            }
        }
    }
    if (GSflagGet(4) != 0) {
        var_r31 = (u16)GSflagGet(5);
        if ((u32)var_r31 < 0x2710U) {
            temp_r0_2 = var_r31 + arg2;
            var_r3 = 0xFFFF;
            if (temp_r0_2 < 0xFFFF) {
                var_r3 = temp_r0_2;
            }
            var_r31 = (u16) var_r3;
        }
        GSflagSet(5, (u16)var_r31);
    }
    if (*(u8*)savedataGetStatus(0, 0xB) != 0) {
        if (arg2 > 0) {
            temp_r25 = (u8*)savedataGetStatus(0, 0xB) + 8;
            var_r24_3 = 0;
            if (temp_r25 != NULL) {
                var_r24_3 = pokemonBiosGetDarkpokemonDataId(temp_r25);
                if (var_r24_3 != 0) {
                    if (arg1 == 1) {
                        if ((darkPokemonBiosGetReliveFlag(var_r24_3) != 0) || (var_r24_3 == 0x49)) {
                            var_r24_3 = 0;
                        } else if (pokemonGetDp(temp_r25) == 0.0f) {

                        } else {
                            var_r24_3 = 0;
                        }
                    } else if ((darkPokemonBiosGetReliveFlag(var_r24_3) != 0) || (pokemonBiosGetHp(temp_r25) == 0) || (var_r24_3 == 0x49)) {
                        var_r24_3 = 0;
                    }
                }
                if ((var_r24_3 != 0) && (darkPokemonBiosGetReliveFlag(var_r24_3) != 0)) {
                    var_r24_3 = 0;
                }
            }
            if ((var_r24_3 == 0) && (pokemonBiosGetLevel(temp_r25) < 0x64U)) {
                temp_r3_6 = pokemonBiosGetExp(temp_r25);
                temp_r5 = temp_r3_6 + arg2;
                var_r4 = -1U;
                if (temp_r3_6 <= temp_r5) {
                    var_r4 = temp_r5;
                }
                pokemonGrowBasisStatus(temp_r25, var_r4);
                sp8 = 0;
                pokemonOboeWaza(temp_r25, pokemonBiosGetLevel(temp_r25), 1, &sp8);
            }
        }
        temp_r3_7 = (u8*)savedataGetStatus(0, 0xB);
        if (temp_r3_7 != NULL) {
            ((Sodateya*)temp_r3_7)->steps = var_r31;
        }
    }
}

}
