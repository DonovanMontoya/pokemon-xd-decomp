#include <game/pxdvs/app/deck/deckDataVirtualBiosLayout.hpp>
extern "C" {
extern u32* deckdata_virtual_number;
extern DeckDataVirtualBiosLayout* deckdata_virtual;
void GSflagSet(u32, u32);
bool GSflagTest(u32);
}
static inline DeckDataVirtualBiosLayout* deckVirtualEntry(u16 index) {
    if (index >= *deckdata_virtual_number) return 0;
    return (DeckDataVirtualBiosLayout*)((u8*)deckdata_virtual + (u32)index * 0x3c);
}
void deckDataVirtualDB_SetFlagData(u16 index, bool value) {
    DeckDataVirtualBiosLayout* entry = deckVirtualEntry(index);
    if (entry != 0) GSflagSet(entry->flagData, (u8)value);
}
bool deckDataVirtualDB_GetFlagData(u16 index) {
    DeckDataVirtualBiosLayout* entry = deckVirtualEntry(index);
    if (entry == 0) return false;
    return GSflagTest(entry->flagData);
}
u32 deckDataVirtualDB_GetFlag(u16 index) {
    DeckDataVirtualBiosLayout* entry = deckVirtualEntry(index);
    if (entry == 0) return 0;
    return entry->flagData;
}
u8 deckDataVirtualDB_GetItemNum(u16 index, u8 item) {
    DeckDataVirtualBiosLayout* entry = deckVirtualEntry(index);
    if (entry == 0) return 0;
    if (item >= 4) return 0;
    return entry->items[item].count;
}
u16 deckDataVirtualDB_GetItemID(u16 index, u8 item) {
    DeckDataVirtualBiosLayout* entry = deckVirtualEntry(index);
    if (entry == 0) return 0;
    if (item >= 4) return 0;
    return entry->items[item].id;
}
u8 deckDataVirtualDB_GetEnemyJoutai(u16 index, u8 slot) {
    DeckDataVirtualBiosLayout* entry = deckVirtualEntry(index);
    if (entry == 0) return 0;
    if (slot >= 6) return 0;
    return entry->enemyJoutai[slot];
}
u8 deckDataVirtualDB_GetAllyJoutai(u16 index, u8 slot) {
    DeckDataVirtualBiosLayout* entry = deckVirtualEntry(index);
    if (entry == 0) return 0;
    if (slot >= 6) return 0;
    return entry->allyJoutai[slot];
}
u32 deckDataVirtualDB_GetExplanetion2(u16 index) {
    DeckDataVirtualBiosLayout* entry=deckVirtualEntry(index); if(entry==0)return 0; return entry->explanation2;
}
u32 deckDataVirtualDB_GetExplanetion1(u16 index) {
    DeckDataVirtualBiosLayout* entry=deckVirtualEntry(index); if(entry==0)return 0; return entry->explanation1;
}
u32 deckDataVirtualDB_GetTitle(u16 index) {
    DeckDataVirtualBiosLayout* entry=deckVirtualEntry(index); if(entry==0)return 0; return entry->title;
}
u32 deckDataVirtualDB_GetEnemyDeck(u16 index) {
    DeckDataVirtualBiosLayout* entry=deckVirtualEntry(index); if(entry==0)return 0; return entry->enemyDeck;
}
u32 deckDataVirtualDB_GetAllyDeck(u16 index) {
    DeckDataVirtualBiosLayout* entry=deckVirtualEntry(index); if(entry==0)return 0; return entry->allyDeck;
}
u8 deckDataVirtualDB_GetPokemonNum(u16 index) {
    DeckDataVirtualBiosLayout* entry=deckVirtualEntry(index); if(entry==0)return 0; return entry->pokemonNum;
}
u8 deckDataVirtualDB_GetTurnLimit(u16 index) {
    DeckDataVirtualBiosLayout* entry=deckVirtualEntry(index); if(entry==0)return 0; return entry->turnLimit;
}
DeckDataVirtualBiosLayout* deckDataVirtual_GetPtr(u16 index) { return deckVirtualEntry(index); }
