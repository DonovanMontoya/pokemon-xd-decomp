#include <global.h>
struct WazaSequenceEntry {u16 unk0,unk2;};
struct FloorParameter {u32 flags;s32 unk4;FloorParameter(){}};
struct EvoInfo {u8 kind,pad;u16 buff;};
struct StatWindow {s8 mode;u8 pad;s16 hp,attack,defense,speed,specialAttack,specialDefense;u16 tailPad;};
extern "C" {
s32 GSfloorGetCurrentFloorGroupID();s32 GSfloorPop();void GSfloorPush(s32);
void *GSparticleCreateGenerator(void*,s32,s32);void GSparticleDestroyGenerator(void*,s32);void GSparticleSetGeneratorPosition(void*,const f32*);
void *GSresGetResource(s32,u32);void GSthreadClose(u32);u8 GSthreadIsRunning(u32);void GSthreadSwitch();u32 GSthreadCreate(s32,s32,u32,s32,s32,void(*)());
void Sequence_DoAnimation(s32,u32);void Sequence_Free(s32);void Sequence_GetPosition(s32,f32*);void Sequence_GetRotation(s32,f32*);void Sequence_GetScale(s32,f32*);
s32 Sequence_GetWaza(s32,u16,u16);s32 Sequence_LoadPokemon(u16,u32,s32);void Sequence_LoadWaza(s32,u16,u32,s32);void Sequence_SetPosition(s32,const f32*);void Sequence_SetRotation(s32,const f32*);void Sequence_SetScale(s32,const f32*);void Sequence_SetVisibility(s32,s32);
void WazaSequence_Free(s32);u8 WazaSequence_IsActive(s32);void WazaSequence_Start(s32,s32);
void darkPokemonBiosSetReliveFlag(u16,u8);s32 evolutionWazaLearn(void*,u16,u8*,s32,s8(*)(void*,u16,s32),s32);void exribbonSetNarionalRibbon(void*);
void fadeCheck(u8);void fadeSet(u16,f32);void fadeSetToBlackInIfBlack(f32);void fadeSetToBlackOutIfNotBlack(f32);s32 floorGetCurrentGroupID();void floorSetFadeScript(s32,s32);void floorWaitForChange();
void *getDeckDarkPokemonObj__15DeckDarkPokemonFUl(u32);u16 getBonusExp__15DeckDarkPokemonCFv(void*);u16 getPokemonDataId__7PokemonCFv(void*);void *heroGetStatus(void*,u16,u16);s32 loadSequence(s32*,void*,const WazaSequenceEntry*,s32);
void menuHologramReloadDatas();void menuHologramUnloadDatas();u8 menuModelGetPokemonAnimationIndexByPointer(void*);void menuModelReSetScale();void menuModelSetScale(f32);
void menuNameEntryOpenNoFade(s32,void*);s32 menuPokemonOpen(s32,s32,s32);s32 menuPokemonStatusOpenWazaLearn(void*,u16);void menuPtRestoreSound__FP15MenuPtWorkSound(void*);void menuPtStopSound__FP15MenuPtWorkSound(void*);s8 menuSubOpenYesNoField();void msgctrlSetValue(s32,u32);
void pokemonAllKaihuku(void*);u16 pokemonBiosGetDarkpokemonDataId(void*);u16 pokemonBiosGetFriend(void*);u8 pokemonBiosGetLevel(void*);const u16 *pokemonBiosGetNicknamePtr(void*);u16 pokemonBiosGetPokemonWazaDataId(void*,u16);u32 pokemonBiosGetPoolExp(void*);u32 pokemonBiosGetPoolFriend(void*);u32 pokemonBiosGetRnd(void*);
void pokemonBiosSetExp(void*,u32);void pokemonBiosSetFriend(void*,u16);void pokemonBiosSetPoolFriend(void*,u32);u8 pokemonCheckValid(void*);
s32 pokemonEvolutionAll(void*,u16,u16,EvoInfo*,void*,s32,s32,s32);u16 pokemonEvolutionCheck(void*,s32,void*,u16*,EvoInfo*);s32 pokemonGetFriendFormPokemonFriendFilterId(void*,s32,s32);u32 pokemonGetLevelToExp(void*,u8);u16 pokemonGetOboeWazaDataId(void*,u8,u8*);s32 pokemonGetSoubiItemSoubiDataId(void*);u32 pokemonGetStatus(void*,s32,u16,u32);void pokemonInitJoutaiDataId(void*,u16);u8 pokemonIsJoutaiDataId(void*,u16);void pokemonResetBasisStatus(void*);s8 pokemonSearchWazaDataId(void*,u16);void pokemonSetStatus(void*,s32,u16,u32,u32);void pokemonWazaCreate(void*,u8,u16);
s32 scriptGetDarkPointZeroPokemonNum();void soundOpenPlay(s32,s32,s32);void soundOpenPlayME(s32,s32,s32);f32 timeGetLastFrameSec();void waitTime(f32);void winMsgCloseField(s32);void winMsgCloseLevelUpStatus(s32);void winMsgOpenField(s32,s32,s32);void winMsgOpenLevelUpStatus(StatWindow*,s32);
static WazaSequenceEntry normalReliveWazaSeqTbl[2]={{77,4},{122,4}};
static WazaSequenceEntry hologramReliveWazaSeqTbl={77,4};
static WazaSequenceEntry hologramPigeonReliveWazaSeqTbl={315,4};
static WazaSequenceEntry noWazaSeqTbl={122,4};
static FloorParameter pParameter;static void *mParameter;static u32 lbl_804EB994;static s32 keepRelivePatternIsHologram;static void *hokoraParticleGen;static u8 isHokoraParticleLoaded;
static s8 _cbWazaForget__FP7PokemonUsl(void*,u16,s32);static void _preReliveDisplayHokoraParticleThreadFunc__Fv();static u8 _expRecover__FP7PokemonUl(void*,u32);static s32 reliveCeremonyAll__FlP7PokemonUl(s32,void*,s32);
static s8 _cbWazaForget__FP7PokemonUsl(void *arg0, u16 arg1,s32) {
    s32 sp8;
    f32 var_f30;
    s32 temp_r3;
    s32 var_r30;

    fadeSetToBlackOutIfNotBlack(0.5f);
    fadeCheck(1);
    if ((s32) keepRelivePatternIsHologram != 0) {
        menuHologramUnloadDatas();
    }
    var_r30 = menuPokemonStatusOpenWazaLearn(arg0, arg1);
    if (var_r30 >= 4) {
        var_r30 = -1;
    }
    if ((s32) keepRelivePatternIsHologram != 0) {
        menuHologramReloadDatas();
        fadeSetToBlackInIfBlack(0.5f);
        fadeCheck(1);
    } else {
        loadSequence(&sp8, arg0, &noWazaSeqTbl, 1);
        fadeSetToBlackInIfBlack(0.5f);
        fadeSet(2, 0.5f);
        Sequence_SetVisibility(sp8, 1);
        temp_r3 = Sequence_GetWaza(sp8, noWazaSeqTbl.unk0, noWazaSeqTbl.unk2);
        if (temp_r3 != 0) {
            WazaSequence_Start(temp_r3,1);
            if (getPokemonDataId__7PokemonCFv(arg0) == 0x15C) {
                Sequence_DoAnimation(sp8, menuModelGetPokemonAnimationIndexByPointer(arg0));
            }
            var_f30 = 0.0f;
            while(WazaSequence_IsActive(temp_r3)){
                GSthreadSwitch();
                var_f30+=timeGetLastFrameSec();
                if(var_f30>4.0f)break;
            }
            WazaSequence_Free(temp_r3);
        }
        if (getPokemonDataId__7PokemonCFv(arg0) == 0x15C) {
            Sequence_DoAnimation(sp8, menuModelGetPokemonAnimationIndexByPointer(arg0));
        }
    }
    return var_r30;
}

static void _preReliveDisplayHokoraParticleThreadFunc__Fv(void) {
    f32 position[3];
    u8 loaded;

    position[0] = 0.0f;
    loaded=isHokoraParticleLoaded;
    position[1]=7.0f;position[2]=0.0f;
    if ((loaded == 1) && (loaded == 1)) {
        GSparticleDestroyGenerator(hokoraParticleGen, 1);
        hokoraParticleGen = 0;
        isHokoraParticleLoaded = 0;
    }
    void *resource=GSresGetResource(floorGetCurrentGroupID(),0x0FAE1400);
    hokoraParticleGen = GSparticleCreateGenerator(resource,0,0);
    GSparticleSetGeneratorPosition(hokoraParticleGen,position);
    isHokoraParticleLoaded = 1;
    soundOpenPlay(0x597, 0, 0x7F);
    waitTime(4.0f);
    if ((u8) isHokoraParticleLoaded == 1) {
        GSparticleDestroyGenerator(hokoraParticleGen, 1);
        hokoraParticleGen = 0;
        isHokoraParticleLoaded = 0;
    }
    lbl_804EB994 = 0U;
}

void preReliveDisplayHokoraParticle(void) {
    if (((u16)scriptGetDarkPointZeroPokemonNum() != 0) && ((u8) isHokoraParticleLoaded == 0)) {
        lbl_804EB994 = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 1, _preReliveDisplayHokoraParticleThreadFunc__Fv);
    }
}

static u8 _expRecover__FP7PokemonUl(void *arg0, u32 arg1) {
    StatWindow delta,current;
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;

    u8 sp9;
    u8 sp8;
    s16 temp_r10;
    s16 temp_r3_2;
    s16 temp_r5;
    s16 temp_r6;
    s16 temp_r7_2;
    s16 temp_r8;
    s16 temp_r9;
    u16 temp_r3_3;
    u32 temp_r21;
    u32 temp_r7;
    u32 temp_r24;
    u8 temp_r24_2;
    u8 temp_r3;
    u8 var_r23;
    u32 var_r25;

    var_r25 = arg1;
    var_r23 = 0;
    sp8 = 0;
    pokemonGetStatus(arg0,0,0x7A,0);
loop_1:
    if (var_r25 == 0) {
        pokemonSetStatus(arg0, 0, 0xC6, 0, var_r25);
    } else {
        temp_r3 = pokemonGetStatus(arg0, 0, 0x7A, 0);
        if (temp_r3 < 0x64U) {
            temp_r24 = pokemonGetStatus(arg0, 0, 0x79, 0);
            temp_r21 = pokemonGetLevelToExp(arg0, (u8) (temp_r3 + 1));
            temp_r31 = pokemonGetStatus(arg0, 0, 0x87, 0);
            temp_r30 = pokemonGetStatus(arg0, 0, 0x88, 0);
            temp_r29 = pokemonGetStatus(arg0, 0, 0x89, 0);
            temp_r28 = pokemonGetStatus(arg0, 0, 0x8A, 0);
            temp_r27 = pokemonGetStatus(arg0, 0, 0x8B, 0);
            temp_r26 = pokemonGetStatus(arg0, 0, 0x8C, 0);
            temp_r7 = temp_r24 + var_r25;
            if (temp_r7 >= temp_r21) {
                var_r25 = temp_r7 - temp_r21;
                var_r23 = 1;
                pokemonBiosSetExp(arg0, temp_r21);
                pokemonResetBasisStatus(arg0);
                s32 item=pokemonGetSoubiItemSoubiDataId(arg0);
                pokemonGetFriendFormPokemonFriendFilterId(arg0,item,0);
                temp_r24_2 = pokemonBiosGetLevel(arg0);
                soundOpenPlayME(0x3C7, 0, 0xFF);
                msgctrlSetValue(0x2F, temp_r24_2);
                winMsgOpenField(0xC367, 1, 0);
                current.hp = pokemonGetStatus(arg0, 0, 0x87, 0);
                current.attack = pokemonGetStatus(arg0, 0, 0x88, 0);
                current.defense = pokemonGetStatus(arg0, 0, 0x89, 0);
                current.specialAttack = pokemonGetStatus(arg0, 0, 0x8A, 0);
                current.specialDefense = pokemonGetStatus(arg0, 0, 0x8B, 0);
                temp_r3_2 = pokemonGetStatus(arg0, 0, 0x8C, 0);
                temp_r5 = temp_r3_2 - temp_r26;
                temp_r10 = current.hp - temp_r31;
                temp_r9 = current.attack - temp_r30;
                temp_r8 = current.defense - temp_r29;
                temp_r7_2 = current.specialAttack - temp_r28;
                temp_r6 = current.specialDefense - temp_r27;
                current.speed = temp_r3_2;
                delta.hp = temp_r10;
                delta.attack = temp_r9;
                delta.defense = temp_r8;
                delta.specialAttack = temp_r7_2;
                delta.specialDefense = temp_r6;
                delta.speed = temp_r5;
                delta.mode = 1;
                winMsgOpenLevelUpStatus(&delta,1);
                current.mode = 0;
                winMsgOpenLevelUpStatus(&current,1);
                winMsgCloseLevelUpStatus(1);
                sp8 = 0;
                while((temp_r3_3=pokemonGetOboeWazaDataId(arg0,temp_r24_2,&sp8))!=0){
                    if(pokemonSearchWazaDataId(arg0,temp_r3_3)==-1&&evolutionWazaLearn(arg0,temp_r3_3,&sp9,0,_cbWazaForget__FP7PokemonUsl,0)!=0)
                        pokemonWazaCreate(arg0,sp9,temp_r3_3);
                    sp8++;
                }
            } else {
                var_r25 = 0;
                pokemonSetStatus(arg0,0,0x79,0,temp_r7);
            }
            goto loop_1;
        }
    }
    return var_r23;
}

static s32 reliveCeremonyAll__FlP7PokemonUl(s32 arg0, void *arg1, s32 arg2) {
    f32 sp4C[3];
    f32 sp40[3];
    f32 sp34[3];
    f32 sp28[3];
    u16 sp20[4];
    EvoInfo sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    u16 sp8;
    WazaSequenceEntry *var_r25_3;
    WazaSequenceEntry *var_r27_2;
    f32 var_f30;
    f32 var_f30_2;
    f32 var_f30_3;
    f32 var_f30_4;
    s32 temp_r26;
    s32 temp_r26_2;
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r28_2;
    s32 temp_r29_2;
    s32 temp_r3_5;
    s32 temp_r3_6;
    s32 temp_r3_7;
    s32 temp_r3_9;
    s32 var_r25_2;
    s32 var_r26_2;
    s32 var_r27_3;
    s32 var_r28_2;
    s32 var_r28_3;
    s32 var_r30;
    s8 temp_r25_2;
    u16 *var_r4;
    u16 temp_r29;
    u16 temp_r3_2;
    u16 temp_r3_3;
    u16 temp_r3_4;
    u16 temp_r3_8;
    u16 var_ctr;
    u16 var_r25;
    u16 var_r26;
    u32 temp_r25;
    u8 var_r0;
    u8 var_r5;

    keepRelivePatternIsHologram = 0;
    var_r30 = 0;
    switch (arg0) {                                 /* irregular */
    case 0:{
        WazaSequenceEntry *var_r28;
        s32 var_r27;
        s32 temp_r3;
        if (pokemonCheckValid(arg1) != 1) {
            var_r0 = 0;
        } else if ((u32) (loadSequence(&sp18, arg1, normalReliveWazaSeqTbl, 2) != 0) == 1) {
            fadeSet(2, 0.5f);
            Sequence_SetVisibility(sp18, 1);
            var_r27 = 0;
            var_r28 = normalReliveWazaSeqTbl;
            do {
                temp_r3 = Sequence_GetWaza(sp18, var_r28->unk0, var_r28->unk2);
                if (temp_r3 != 0) {
                    WazaSequence_Start(temp_r3,1);
                    if (getPokemonDataId__7PokemonCFv(arg1) == 0x15C) {
                        Sequence_DoAnimation(sp18, menuModelGetPokemonAnimationIndexByPointer(arg1));
                    }
                    var_f30 = 0.0f;
                    while(WazaSequence_IsActive(temp_r3)){
                        GSthreadSwitch();
                        var_f30+=timeGetLastFrameSec();
                        if(var_f30>4.0f)break;
                    }
                    WazaSequence_Free(temp_r3);
                }
                var_r27 += 1;
                var_r28++;
            } while (var_r27 < 2);
            if (getPokemonDataId__7PokemonCFv(arg1) == 0x15C) {
                Sequence_DoAnimation(sp18, menuModelGetPokemonAnimationIndexByPointer(arg1));
            }
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 == 0) {
            return 0;
        }
    }
    default:
block_44:
        sp8 = 0;
        if (pokemonCheckValid(arg1) != 1) {
            return 0;
        }
        var_r25 = 0;
        var_r28_2 = 0;
loop_47:
        temp_r3_2 = pokemonBiosGetPokemonWazaDataId(arg1, var_r25);
        if (temp_r3_2 != 0) {
            var_r25 += 1;
            *(u16*)((u8*)sp20+var_r28_2) = temp_r3_2;
            var_r28_2 += 2;
            if ((s32) var_r25 < 4) {
                goto loop_47;
            }
        }
        pokemonAllKaihuku(arg1);
        temp_r29 = pokemonBiosGetDarkpokemonDataId(arg1);
        darkPokemonBiosSetReliveFlag(temp_r29,1);
        if (pokemonIsJoutaiDataId(arg1, 0x3E) != 0) {
            pokemonInitJoutaiDataId(arg1, 0x3E);
        }
        soundOpenPlayME(0x3B5, 0, 0xFF);
        var_r28_3 = 0;
        var_r26 = 0;
loop_52:
        temp_r3_3 = pokemonBiosGetPokemonWazaDataId(arg1, var_r26);
        if (temp_r3_3 != 0) {
            var_r4 = sp20;
            var_r5 = 0;
            var_ctr = var_r25;
            if ((s32) var_r25 > 0) {
loop_54:
                if (temp_r3_3 == (u16) *var_r4) {
                    var_r5 = 1;
                } else {
                    var_r4++;
                    var_ctr -= 1;
                    if (var_ctr != 0) {
                        goto loop_54;
                    }
                }
            }
            if (var_r5 == 0) {
                var_r28_3 += 1;
            }
            var_r26 += 1;
            if ((s32) var_r26 < 4) {
                goto loop_52;
            }
        }
        if (var_r28_3 != 0) {
            msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(arg1));
            winMsgOpenField(0xC547, 1, 0);
            var_r25_2 = 0;
loop_63:
            if (var_r25_2 < var_r28_3) {
                soundOpenPlayME(0x3C7, 0, 0xFF);
                msgctrlSetValue(0x39, pokemonBiosGetPokemonWazaDataId(arg1, (u16) var_r25_2));
                winMsgOpenField((var_r25_2 == (var_r28_3 - 1)) + 0xC54E, 1, 0);
                var_r25_2 += 1;
                goto loop_63;
            }
        }
        temp_r28 = pokemonBiosGetPoolExp(arg1);
        void *deck=getDeckDarkPokemonObj__15DeckDarkPokemonFUl(temp_r29);
        temp_r25 = temp_r28 + getBonusExp__15DeckDarkPokemonCFv(deck);
        if (temp_r25 != 0) {
            msgctrlSetValue(0x2F, temp_r25);
            winMsgOpenField(0xC548, 1, 0);
            winMsgCloseField(1);
        }
        temp_r28_2 = pokemonBiosGetFriend(arg1);
        pokemonBiosSetFriend(arg1, (u16) (temp_r28_2 + (pokemonBiosGetPoolFriend(arg1) + 0x46)));
        pokemonBiosSetPoolFriend(arg1, 0);
        if (_expRecover__FP7PokemonUl(arg1, temp_r25) == 1) {
            temp_r3_4 = pokemonEvolutionCheck(arg1, 0, 0, &sp8, &sp1C);
            if ((temp_r3_4 != 0) && (temp_r3_4 != -1U)) {
                fadeSetToBlackOutIfNotBlack(0.5f);
                fadeCheck(1);
                if ((s32) keepRelivePatternIsHologram != 0) {
                    menuHologramUnloadDatas();
                }
                if (pokemonEvolutionAll(arg1, temp_r3_4, sp8, &sp1C, 0, 1, 1, 0) == 0) {
                    if ((s32) keepRelivePatternIsHologram != 0) {
                        menuHologramReloadDatas();
                        fadeSetToBlackInIfBlack(0.5f);
                        fadeCheck(1);
                    } else {
                        loadSequence(&sp14, arg1, &noWazaSeqTbl, 1);
                        fadeSetToBlackInIfBlack(0.5f);
                        fadeSet(2, 0.5f);
                        Sequence_SetVisibility(sp14, 1);
                        temp_r3_5 = Sequence_GetWaza(sp14, noWazaSeqTbl.unk0, noWazaSeqTbl.unk2);
                        if (temp_r3_5 != 0) {
                            WazaSequence_Start(temp_r3_5,1);
                            if (getPokemonDataId__7PokemonCFv(arg1) == 0x15C) {
                                Sequence_DoAnimation(sp14, menuModelGetPokemonAnimationIndexByPointer(arg1));
                            }
                            var_f30_2 = 0.0f;
                            while(WazaSequence_IsActive(temp_r3_5)){
                                GSthreadSwitch();
                                var_f30_2+=timeGetLastFrameSec();
                                if(var_f30_2>4.0f)break;
                            }
                            WazaSequence_Free(temp_r3_5);
                        }
                        if (getPokemonDataId__7PokemonCFv(arg1) == 0x15C) {
                            Sequence_DoAnimation(sp14, menuModelGetPokemonAnimationIndexByPointer(arg1));
                        }
                    }
                    msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(arg1));
                } else {
                    msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(arg1));
                    if ((s32) keepRelivePatternIsHologram != 0) {
                        menuHologramReloadDatas();
                        fadeSetToBlackInIfBlack(0.5f);
                        fadeCheck(1);
                    } else {
                        loadSequence(&sp10, arg1, &noWazaSeqTbl, 1);
                        fadeSetToBlackInIfBlack(0.5f);
                        fadeSet(2, 0.5f);
                        Sequence_SetVisibility(sp10, 1);
                        temp_r3_6 = Sequence_GetWaza(sp10, noWazaSeqTbl.unk0, noWazaSeqTbl.unk2);
                        if (temp_r3_6 != 0) {
                            WazaSequence_Start(temp_r3_6,1);
                            if (getPokemonDataId__7PokemonCFv(arg1) == 0x15C) {
                                Sequence_DoAnimation(sp10, menuModelGetPokemonAnimationIndexByPointer(arg1));
                            }
                            var_f30_3 = 0.0f;
                            while(WazaSequence_IsActive(temp_r3_6)){
                                GSthreadSwitch();
                                var_f30_3+=timeGetLastFrameSec();
                                if(var_f30_3>4.0f)break;
                            }
                            WazaSequence_Free(temp_r3_6);
                        }
                        if (getPokemonDataId__7PokemonCFv(arg1) == 0x15C) {
                            Sequence_DoAnimation(sp10, menuModelGetPokemonAnimationIndexByPointer(arg1));
                        }
                    }
                }
            }
        }
        soundOpenPlayME(0x3CE, 0, 0xFF);
        exribbonSetNarionalRibbon(arg1);
        winMsgOpenField(0xC549, 1, 0);
        winMsgOpenField(0xC54A, 1, 1);
        temp_r25_2 = menuSubOpenYesNoField();
        winMsgCloseField(1);
        if (temp_r25_2 == 0) {
            fadeSetToBlackOutIfNotBlack(0.5f);
            fadeCheck(1);
            if ((s32) keepRelivePatternIsHologram != 0) {
                menuHologramUnloadDatas();
            }
            Sequence_SetVisibility(var_r30, 0);
            Sequence_Free(var_r30);
            var_r30 = 0;
            menuNameEntryOpenNoFade(5, arg1);
            if ((s32) keepRelivePatternIsHologram != 0) {
                menuHologramReloadDatas();
            } else {
                loadSequence(&spC, arg1, &noWazaSeqTbl, 1);
                fadeSetToBlackInIfBlack(0.5f);
                fadeSet(2, 0.5f);
                Sequence_SetVisibility(spC, 1);
                temp_r3_7 = Sequence_GetWaza(spC, noWazaSeqTbl.unk0, noWazaSeqTbl.unk2);
                if (temp_r3_7 != 0) {
                    WazaSequence_Start(temp_r3_7,1);
                    if (getPokemonDataId__7PokemonCFv(arg1) == 0x15C) {
                        Sequence_DoAnimation(spC, menuModelGetPokemonAnimationIndexByPointer(arg1));
                    }
                    var_f30_4 = 0.0f;
                    while(WazaSequence_IsActive(temp_r3_7)){
                        GSthreadSwitch();
                        var_f30_4+=timeGetLastFrameSec();
                        if(var_f30_4>4.0f)break;
                    }
                    WazaSequence_Free(temp_r3_7);
                }
                if (getPokemonDataId__7PokemonCFv(arg1) == 0x15C) {
                    Sequence_DoAnimation(spC, menuModelGetPokemonAnimationIndexByPointer(arg1));
                }
            }
        }
        return var_r30;
    case 1:
        keepRelivePatternIsHologram = 1;
        if (getPokemonDataId__7PokemonCFv(arg1) == 0xF9) {
            Sequence_LoadWaza(arg2, 0x103U, 4U, 0);
            temp_r26 = pokemonGetStatus(arg1, 0, 0xC1, 0) != 0;
            temp_r29_2 = Sequence_LoadPokemon(0xF9, pokemonBiosGetRnd(arg1), temp_r26);
            Sequence_LoadWaza(temp_r29_2,0x104,4,0);
            sp34[0]=sp34[1]=sp34[2]=0.0f;
            sp40[0]=sp40[1]=sp40[2]=0.0f;
            sp4C[0]=sp4C[1]=sp4C[2]=1.0f;
            Sequence_GetPosition(arg2, sp34);
            Sequence_GetRotation(arg2, sp40);
            Sequence_GetScale(arg2, sp4C);
            Sequence_SetPosition(temp_r29_2, sp34);
            Sequence_SetRotation(temp_r29_2, sp40);
            Sequence_SetScale(temp_r29_2, sp4C);
            temp_r27 = Sequence_GetWaza(arg2, 0x103U, 4U);
            temp_r26_2 = Sequence_GetWaza(temp_r29_2, 0x104U, 4U);
            WazaSequence_Start(temp_r27, 0);
            WazaSequence_Start(temp_r26_2, 0);
loop_25:
            if (WazaSequence_IsActive(temp_r27) != 0) {
block_24:
                GSthreadSwitch();
                timeGetLastFrameSec();
                goto loop_25;
            }
            if (WazaSequence_IsActive(temp_r26_2) != 0) {
                goto block_24;
            }
            WazaSequence_Free(temp_r27);
            WazaSequence_Free(temp_r26_2);
            var_r30 = temp_r29_2;
        } else {
            var_r25_3 = &hologramReliveWazaSeqTbl;
            temp_r3_8 = getPokemonDataId__7PokemonCFv(arg1);
            if ((temp_r3_8 == 0x11) || (temp_r3_8 == 0x15C) || (temp_r3_8 == 0x15D)) {
                var_r25_3 = &hologramPigeonReliveWazaSeqTbl;
            }
            Sequence_GetScale(arg2, sp28);
            menuModelSetScale(sp28[0]);
            var_r27_2 = var_r25_3;
            var_r26_2 = 0;
loop_34:
            if (var_r26_2 < 1) {
                Sequence_LoadWaza(arg2, var_r27_2->unk0, (u8) var_r27_2->unk2, 0);
                var_r27_2++;
                var_r26_2 += 1;
                goto loop_34;
            }
            Sequence_SetVisibility(arg2, 1);
            var_r27_3 = 0;
loop_42:
            if (var_r27_3 < 1) {
                temp_r3_9 = Sequence_GetWaza(arg2, var_r25_3->unk0, var_r25_3->unk2);
                if (temp_r3_9 != 0) {
                    WazaSequence_Start(temp_r3_9,0);
loop_39:
                    if (WazaSequence_IsActive(temp_r3_9) != 0) {
                        GSthreadSwitch();
                        goto loop_39;
                    }
                    WazaSequence_Free(temp_r3_9);
                }
                var_r25_3++;
                var_r27_3 += 1;
                goto loop_42;
            }
            menuModelReSetScale();
        }
        goto block_44;
    }
}

void reliveCeremonyFromHologram__FP7PokemonUl(void *arg0, s32 arg1) {
    u8 sp8[12];

    menuPtStopSound__FP15MenuPtWorkSound(sp8);
    reliveCeremonyAll__FlP7PokemonUl(1, arg0, arg1);
}

void reliveMain(void) {
    reliveCeremonyAll__FlP7PokemonUl(0, mParameter, 0);
    fadeSetToBlackOutIfNotBlack(0.5f);
    fadeCheck(1);
    mParameter = 0;
    pParameter.unk4=-1;
    GSfloorPop();
    floorSetFadeScript(0, 0);
    floorWaitForChange();
}

void preReliveMain(u8 arg0) {
    u8 sp8[12];
    s32 temp_r3;

    if (scriptGetDarkPointZeroPokemonNum() != 0) {
        if ((u8) isHokoraParticleLoaded == 1) {
            GSparticleDestroyGenerator(hokoraParticleGen, 1);
            hokoraParticleGen = 0;
            isHokoraParticleLoaded = 0;
        }
        if ((u16)scriptGetDarkPointZeroPokemonNum() == 0) {
            pParameter.unk4 = -1;
            return;
        }
        winMsgOpenField(0xC546, 1, 0);
        winMsgCloseField(1);
        temp_r3 = menuPokemonOpen(7, 0, 0);
        if (temp_r3 != -1) {
            mParameter = heroGetStatus(0, 3, (u16) temp_r3);
            fadeSetToBlackOutIfNotBlack(0.5f);
            fadeCheck(1);
            menuPtStopSound__FP15MenuPtWorkSound(sp8);
            GSfloorPush(0x385);
            floorSetFadeScript(0, 0);
            floorWaitForChange();
            fadeSetToBlackInIfBlack(1.0f);
            if (arg0 == 1) {
                fadeCheck(1);
            }
            menuPtRestoreSound__FP15MenuPtWorkSound(sp8);
        }
    } else {
        pParameter.unk4 = -1;
    }
}

void preReliveInit(void) {
    pParameter.unk4 = -1;
}

void preReliveSetParameter(s32 arg0, s32 arg1, u8 arg2) {
    pParameter.unk4 = arg1;
    if ((arg0 == 0) || (arg0 == 1)) {
        preReliveMain(arg2);
    }
}

void fn_80233AB4(void) {
    if (((u32) lbl_804EB994 != 0U) && (GSthreadIsRunning(lbl_804EB994) != 0)) {
        GSthreadClose(lbl_804EB994);
        lbl_804EB994 = 0U;
    }
    if ((u8) isHokoraParticleLoaded == 1) {
        GSparticleDestroyGenerator(hokoraParticleGen, 1);
        hokoraParticleGen = 0;
        isHokoraParticleLoaded = 0;
    }
}


}
