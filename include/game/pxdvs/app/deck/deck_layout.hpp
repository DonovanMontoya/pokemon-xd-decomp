#ifndef GAME_PXDVS_APP_DECK_DECK_LAYOUT_HPP
#define GAME_PXDVS_APP_DECK_DECK_LAYOUT_HPP

#include <dolphin/types.h>
#include <libc/stddef.h>

struct DeckPokemonLayout {
    u16 pokemonId;
    u8 level;
    u8 friendLevel;
    u16 holdItem;
    u8 role;
    u8 keyPlayer;
    u8 statusRnd[6];
    u8 statusEffort[6];
    u16 waza[4];
    u8 reserved1c;
    u8 comboPartnerAll;
    u8 flags;
    u8 randomSetting;
};
struct DeckDarkPokemonLayout {
    u8 worth;
    u8 snatchRatio;
    u8 playerLevel;
    u8 flags;
    u32 pokemonId;
    u16 initDarkPoint;
    u16 bonusExp;
    u16 waza[4];
    u8 revers;
    u8 underTaker;
    u8 reserved16[2];
};
struct DeckTrainerLayout {
    u16 nameStringOffset;
    u16 reserved02;
    u8 darkPokemonMask;
    u8 trainerKind;
    u16 trainerName;
    u16 trainerItem[4];
    u16 trainerPKX;
    u16 introWZX;
    u16 trainerMsg[4];
    u16 pokemonDataID[6];
    u16 aiID;
    u16 fixedActionID;
    u16 comboID[4];
    u8 reserved34[4];
};
struct DeckTrainerAILayout {
    u8 flags0;
    u8 flags1;
    u8 reserved02[2];
    u8 statusDeterm[4];
    u8 reserved08[4];
    u8 statusDetermValTotalMax;
    u8 statusDetermValTotalMin;
    u8 pokeChgRate;
    u8 itemUseRate;
    u8 hitRate;
    u8 annihilateDetermRate;
    u8 lowHPDetermRate;
    u8 lastPPDetermRate;
    u8 attrTypeID;
    u8 reserved15;
    u8 attrTypeParam;
    u16 wazaKindID[2];
    u8 wazaKindParam[2];
    u8 totalCorrection;
};

typedef char DeckPokemonSizeCheck[sizeof(DeckPokemonLayout) == 0x20 ? 1 : -1];
typedef char DeckPokemonRndCheck[offsetof(DeckPokemonLayout, statusRnd) == 0x08 ? 1 : -1];
typedef char DeckPokemonEffortCheck[offsetof(DeckPokemonLayout, statusEffort) == 0x0E ? 1 : -1];
typedef char DeckPokemonMoveCheck[offsetof(DeckPokemonLayout, waza) == 0x14 ? 1 : -1];
typedef char DeckPokemonFlagsCheck[offsetof(DeckPokemonLayout, flags) == 0x1E ? 1 : -1];
typedef char DeckDarkPokemonSizeCheck[sizeof(DeckDarkPokemonLayout) == 0x18 ? 1 : -1];
typedef char DeckDarkPokemonIdCheck[offsetof(DeckDarkPokemonLayout, pokemonId) == 0x04 ? 1 : -1];
typedef char DeckDarkPokemonPointCheck[offsetof(DeckDarkPokemonLayout, initDarkPoint) == 0x08 ? 1 : -1];
typedef char DeckDarkPokemonMovesCheck[offsetof(DeckDarkPokemonLayout, waza) == 0x0C ? 1 : -1];
typedef char DeckDarkPokemonFlagsCheck[offsetof(DeckDarkPokemonLayout, revers) == 0x14 ? 1 : -1];
typedef char DeckTrainerSizeCheck[sizeof(DeckTrainerLayout) == 0x38 ? 1 : -1];
typedef char DeckTrainerKindCheck[offsetof(DeckTrainerLayout, trainerKind) == 0x05 ? 1 : -1];
typedef char DeckTrainerItemsCheck[offsetof(DeckTrainerLayout, trainerItem) == 0x08 ? 1 : -1];
typedef char DeckTrainerPokemonIdsCheck[offsetof(DeckTrainerLayout, pokemonDataID) == 0x1C ? 1 : -1];
typedef char DeckTrainerAISizeCheck[sizeof(DeckTrainerAILayout) == 0x20 ? 1 : -1];
typedef char DeckTrainerAITotalsCheck[offsetof(DeckTrainerAILayout, statusDetermValTotalMax) == 0x0C ? 1 : -1];
typedef char DeckTrainerAIAttrsCheck[offsetof(DeckTrainerAILayout, attrTypeID) == 0x14 ? 1 : -1];
typedef char DeckTrainerAIMovesCheck[offsetof(DeckTrainerAILayout, wazaKindID) == 0x18 ? 1 : -1];
typedef char DeckTrainerAITotalCorrectionCheck[offsetof(DeckTrainerAILayout, totalCorrection) == 0x1E ? 1 : -1];

#endif
