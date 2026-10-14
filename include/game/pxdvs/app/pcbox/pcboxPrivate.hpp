#ifndef PCBOX_PRIVATE_H
#define PCBOX_PRIVATE_H

#include <global.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

extern "C" {
void* savedataGetStatus(u32, u32);
void msgctrlSetValue(u32, s32);
void GSmsgMakeGScharStr(void*, u32, u32);
void GScharCpy(void*, const u16*);
void itemInitAry(void*, u32);
void itemReplace(void*);
u8 itemCheckValid(void*);
u32 itemDataBiosGetPtr(u16);
u32 itemGetStatus(void*, u32, u32, u32);
u16 itemDecItemDataIdAry(void*, u32, u16, u16, u32, u32);
u16 itemAddItemDataIdAry(void*, u32, u16, u16, s16, u32, u32, u32);
u8 pokemonCheckValid(Pokemon*);
void pokemonAllKaihuku(Pokemon*);
void* memcpy(void*, const void*, unsigned long);
}

s8 menuPcBoxGetLastViewBox();
void menuPocketDebugMakePokemonBySN(Pokemon&, u16, bool, f32);

struct PCBOXItem {
    u32 raw;
};

struct PCBOXBox {
    char16 name[10];            // 0x0
    Pokemon pokemon[30];        // 0x14
};

class PCBOX {
public:
    PCBOXBox boxes[8];          // 0x0
    PCBOXItem items[0xEB];      // 0xB860
    u32 lastItemSlot;           // 0xBC0C

    static s8 lastWatchBoxID;
    static PCBOX* getPointer();
    static s32 isPokemonFull();

    s8 getPokemonBoxNbEmptySlot(s8);
    s8 getPokemonBoxNbUsedSlot(s8);
    char16* getPokemonBoxName(s8);
    s32 delPokemon(s8, s8);
    s32 addPokemonLastWatchBox(Pokemon*);
    s32 addPokemon(Pokemon*, s8);
    s32 setPokemon(Pokemon*, s8, s8);
    Pokemon* getPokemon(s8, s8);
    void init();

    PCBOXItem* getItem(s16);
    s16 searchItem(u16);
};

#endif
