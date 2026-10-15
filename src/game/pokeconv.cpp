#include <dolphin/types.h>
#pragma dont_inline on

extern "C" {
void heroBiosSetHomePlace(void *, u8);
void GScharMakeFromGBA(u16 *, u8 *, s32, s32);
s32 gamedataGetStatus(s32, s32);
void heroBiosSetNamePtr(void *, const void *);
void heroBiosSetSexDataId(void *, u8);
void heroBiosSetRnd(void *, u32);
void *heroBiosGetPokemonPtr(void *, u16);
void gbaPokemonToGC(void *, void *);
void pokemonBiosSetFightTrainerPokemonDataId(void *, u16);
void exribbonSetNo(s32, u8);
}

static u32 _swap32(unsigned long value) {
    return (value >> 24) | (((value & 0x00FF0000) >> 8) | ((value << 24) | ((value & 0x0000FF00) << 8)));
}

extern "C" void pokeconv(void *hero, u8 *data) {
    u8 *bytes = data;
    u32 high = bytes[3];
    high <<= 24;
    u32 middleHigh = bytes[2];
    middleHigh <<= 16;
    u32 middleLow = bytes[1];
    middleLow <<= 8;
    u32 low = bytes[0];
    u32 packed = high | middleHigh | middleLow | low;
    u32 region = (packed >> 10) & 0xF;
    switch (region) {
    case 1: heroBiosSetHomePlace(hero, 1); break;
    case 2: heroBiosSetHomePlace(hero, 1); break;
    case 3: heroBiosSetHomePlace(hero, 2); break;
    case 4: heroBiosSetHomePlace(hero, 2); break;
    case 5: heroBiosSetHomePlace(hero, 3); break;
    default: heroBiosSetHomePlace(hero, 1); break;
    }
    u16 name[7];
    GScharMakeFromGBA(name, data + 4, 7, gamedataGetStatus(0, 5));
    heroBiosSetNamePtr(hero, name);
    heroBiosSetSexDataId(hero, data[0xC]);
    heroBiosSetRnd(hero, _swap32(*(u32 *)(data + 0x10)));
    u8 *entry = data;
    for (u16 i = 0; i < 6; ++i) {
        void *pokemon = heroBiosGetPokemonPtr(hero, i);
        gbaPokemonToGC(pokemon, entry + 0x14);
        pokemonBiosSetFightTrainerPokemonDataId(pokemon, i);
        entry += 0x64;
    }
    for (s32 i = 0; i < 0xB; ++i) exribbonSetNo(i, data[0x26C + i]);
}
