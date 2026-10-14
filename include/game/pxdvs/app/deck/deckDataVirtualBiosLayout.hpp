#ifndef DECK_DATA_VIRTUAL_BIOS_LAYOUT_HPP
#define DECK_DATA_VIRTUAL_BIOS_LAYOUT_HPP
#include <dolphin/types.h>
struct DeckDataVirtualBiosLayout {
    u8 reserved00;
    u8 turnLimit;
    u8 pokemonNum;
    u8 reserved04[5];
    u32 allyDeck;
    u32 enemyDeck;
    u32 title;
    u32 explanation1;
    u32 explanation2;
    u32 flagData;
    u8 allyJoutai[6];
    u8 enemyJoutai[6];
    struct { u8 count; u8 reserved; u16 id; } items[4];
};
typedef char DeckDataVirtualBiosSize[(sizeof(DeckDataVirtualBiosLayout)==0x3c)?1:-1];
#endif
