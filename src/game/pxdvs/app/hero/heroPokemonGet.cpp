#include <global.h>
extern "C" {
const u16 *GSmsgGetGSchar(u32);void gamedataAttestCreate(void*,u8,u8,u8,u8);u32 gamedataGetStatus(void*,u16);
void heroCatchPokemon(void*,void*,u32,u32,u32);void heroGetPokemon(void*,void*,s32);u32 heroGetStatus(void*,u16,u16);void memoDataSet(void*,void*);
void pokemonCreate(void*,u16,u8,const void*);u32 pokemonCreateRndFit(void*,s32,s32,s32,u32);void pokemonDoItemSoubi(void*,u16,u8);void pokemonResetBasisStatus(void*);
void pokemonSetCatchStatus(void*,u32,u32,u32,u32,u32,const u16*);void pokemonSetStatus(void*,s32,u16,u32,u32);void pokemonWazaCreate(void*,u8,u16);
void heroPokemonGetCelebi(void *arg0) {
    u8 spC[196];
    u8 sp8[4];
    u8 temp_r31;

    temp_r31 = gamedataGetStatus(0, 5);
    gamedataAttestCreate(sp8, 9, 3, gamedataGetStatus(0, 4), temp_r31);
    pokemonCreate(spC, 0xFB, 0xA, sp8);
    pokemonSetStatus(spC, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(spC, 0xFF, 0xA, 4, 1, 0x7991, GSmsgGetGSchar(1));
    u32 random=pokemonCreateRndFit(spC, -1, -1, 0, 0x7991);
    pokemonSetStatus(spC,0,0x6F,0,random);
    pokemonResetBasisStatus(spC);
    memoDataSet(0, spC);
    heroGetPokemon(arg0, spC, 1);
}

void heroPokemonGetPikachu(void *arg0) {
    u8 spC[196];
    u8 sp8[4];
    u8 temp_r31;

    temp_r31 = gamedataGetStatus(0, 5);
    gamedataAttestCreate(sp8, 9, 3, gamedataGetStatus(0, 4), temp_r31);
    pokemonCreate(spC, 0x19, 0xA, sp8);
    pokemonSetStatus(spC, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(spC, 0xFF, 0xA, 4, 0, 0x7991, GSmsgGetGSchar(1));
    u32 random=pokemonCreateRndFit(spC, -1, -1, 0, 0x7991);
    pokemonSetStatus(spC,0,0x6F,0,random);
    pokemonDoItemSoubi(spC, 0xCA, 1);
    pokemonResetBasisStatus(spC);
    memoDataSet(0, spC);
    heroGetPokemon(arg0, spC, 1);
}

void heroPokemonGetHouou(void *arg0) {
    u8 spC[196];
    u8 sp8[4];
    u8 temp_r31;

    temp_r31 = gamedataGetStatus(0, 5);
    gamedataAttestCreate(sp8, 8, 3, gamedataGetStatus(0, 4), temp_r31);
    pokemonCreate(spC, 0xFA, 0x46, sp8);
    pokemonSetStatus(spC, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(spC, 0xFF, 0x46, 4, 0, 0x2740, GSmsgGetGSchar(1));
    u32 random=pokemonCreateRndFit(spC, -1, -1, 0, 0x2740);
    pokemonSetStatus(spC,0,0x6F,0,random);
    pokemonResetBasisStatus(spC);
    memoDataSet(0, spC);
    heroGetPokemon(arg0, spC, 1);
}

void heroPokemonGetPrasle(void *arg0) {
    u8 sp8[196];

    pokemonCreate(sp8, 0x161, 0xD, (void*)gamedataGetStatus(0, 1));
    pokemonSetStatus(sp8, 0, 0x99, 0, 0x46);
    pokemonSetCatchStatus(sp8, 0x259, 0xD, 4, 0, 0x911D, GSmsgGetGSchar(1));
    u32 random=pokemonCreateRndFit(sp8, -1, -1, 0, 0x911D);
    pokemonSetStatus(sp8,0,0x6F,0,random);
    pokemonResetBasisStatus(sp8);
    memoDataSet(0, sp8);
    heroGetPokemon(arg0, sp8, 1);
}

void heroPokemonGetEifie(void *arg0) {
    u8 sp8[196];
    s32 temp_r31;

    temp_r31 = heroGetStatus(arg0,2,0);
    pokemonCreate(sp8, 0x86, 0x1E, (void*)gamedataGetStatus(0, 1));
    pokemonWazaCreate(sp8, 0, 0x10E);
    pokemonWazaCreate(sp8, 1, 0x37);
    pokemonWazaCreate(sp8, 2, 0x62);
    pokemonWazaCreate(sp8, 3, 0x2C);
    u32 random=pokemonCreateRndFit(sp8, 0, -1, 0, temp_r31);
    pokemonSetStatus(sp8,0,0x6F,0,random);
    pokemonSetStatus(sp8, 0, 0x79, 0, 0x7148);
    pokemonSetStatus(sp8, 0, 0x99, 0, 0xDC);
    pokemonResetBasisStatus(sp8);
    heroCatchPokemon(arg0, sp8, 0x259, 4, 0);
}

void heroPokemonGetBlacky(void *arg0) {
    u8 sp8[196];
    s32 temp_r31;

    temp_r31 = heroGetStatus(arg0,2,0);
    pokemonCreate(sp8, 0x87, 0x1A, (void*)gamedataGetStatus(0, 1));
    pokemonWazaCreate(sp8, 0, 0x62);
    pokemonWazaCreate(sp8, 1, 0x1C);
    pokemonWazaCreate(sp8, 2, 0x10E);
    pokemonWazaCreate(sp8, 3, 0x54);
    u32 random=pokemonCreateRndFit(sp8, 0, -1, 0, temp_r31);
    pokemonSetStatus(sp8,0,0x6F,0,random);
    pokemonSetStatus(sp8, 0, 0x79, 0, 0x4A6F);
    pokemonSetStatus(sp8, 0, 0x99, 0, 0xDC);
    pokemonResetBasisStatus(sp8);
    heroCatchPokemon(arg0, sp8, 0x259, 4, 0);
}

}
