#ifndef FIGHT_FLOOR_DB_LAYOUT_HPP
#define FIGHT_FLOOR_DB_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct Pokemon; struct FightSide; struct FightOutPokemon; struct FightEncountData; struct FightKindData; struct FightTypeData;
struct StockPokemon { u8 pokemon[0xc4]; u8 ballId; u8 reserved[3]; };
struct FIGHT_FLOOR {
    u8 reserved0[0x10];
    u16 turnCount;
    u16 encountDataId;
    u8 reserved14[0xdde0];
    void* attackPokemonPtr;
    void* defensePokemonPtr;
    void* escapePokemonPtr;
    void* irekaePokemonPtr;
    void* kizetuPokemonPtr;
    void* tuikakoukaPokemonPtr;
    void* tokuseiPokemonPtr;
    void* itemPokemonPtr;
    void* appointPokemonPtr;
    void* appointTrainerPtr;
    void* appointWazaPtr;
    void* appointSidePtr;
    void* appointItemPtr;
    u32 attackMsgId, criticalMsgId, wazaEffectMsgId;
    s32 appointMsgId;
    u16 appointPokemonDataId, appointWazaDataId, appointItemDataId, appointTokuseiDataId;
    s16 fightPokemonEntryCnt;
    u8 reservedDE42[0x2];
    void* fightOutPokemon[8];
    u16 firstAttackRnd;
    u8 stockPokemonNum;
    u8 reservedDE67[0x1];
    StockPokemon stockPokemon[6];
};
typedef char FloorDBOffset_turnCount[offsetof(FIGHT_FLOOR, turnCount) == 0x10 ? 1 : -1];
typedef char FloorDBOffset_encountDataId[offsetof(FIGHT_FLOOR, encountDataId) == 0x12 ? 1 : -1];
typedef char FloorDBOffset_attackPokemonPtr[offsetof(FIGHT_FLOOR, attackPokemonPtr) == 0xddf4 ? 1 : -1];
typedef char FloorDBOffset_defensePokemonPtr[offsetof(FIGHT_FLOOR, defensePokemonPtr) == 0xddf8 ? 1 : -1];
typedef char FloorDBOffset_escapePokemonPtr[offsetof(FIGHT_FLOOR, escapePokemonPtr) == 0xddfc ? 1 : -1];
typedef char FloorDBOffset_irekaePokemonPtr[offsetof(FIGHT_FLOOR, irekaePokemonPtr) == 0xde00 ? 1 : -1];
typedef char FloorDBOffset_kizetuPokemonPtr[offsetof(FIGHT_FLOOR, kizetuPokemonPtr) == 0xde04 ? 1 : -1];
typedef char FloorDBOffset_tuikakoukaPokemonPtr[offsetof(FIGHT_FLOOR, tuikakoukaPokemonPtr) == 0xde08 ? 1 : -1];
typedef char FloorDBOffset_tokuseiPokemonPtr[offsetof(FIGHT_FLOOR, tokuseiPokemonPtr) == 0xde0c ? 1 : -1];
typedef char FloorDBOffset_itemPokemonPtr[offsetof(FIGHT_FLOOR, itemPokemonPtr) == 0xde10 ? 1 : -1];
typedef char FloorDBOffset_appointPokemonPtr[offsetof(FIGHT_FLOOR, appointPokemonPtr) == 0xde14 ? 1 : -1];
typedef char FloorDBOffset_appointTrainerPtr[offsetof(FIGHT_FLOOR, appointTrainerPtr) == 0xde18 ? 1 : -1];
typedef char FloorDBOffset_appointWazaPtr[offsetof(FIGHT_FLOOR, appointWazaPtr) == 0xde1c ? 1 : -1];
typedef char FloorDBOffset_appointSidePtr[offsetof(FIGHT_FLOOR, appointSidePtr) == 0xde20 ? 1 : -1];
typedef char FloorDBOffset_appointItemPtr[offsetof(FIGHT_FLOOR, appointItemPtr) == 0xde24 ? 1 : -1];
typedef char FloorDBOffset_appointMsgId[offsetof(FIGHT_FLOOR, appointMsgId) == 0xde34 ? 1 : -1];
typedef char FloorDBOffset_fightPokemonEntryCnt[offsetof(FIGHT_FLOOR, fightPokemonEntryCnt) == 0xde40 ? 1 : -1];
typedef char FloorDBOffset_fightOutPokemon[offsetof(FIGHT_FLOOR, fightOutPokemon) == 0xde44 ? 1 : -1];
typedef char FloorDBOffset_firstAttackRnd[offsetof(FIGHT_FLOOR, firstAttackRnd) == 0xde64 ? 1 : -1];
typedef char FloorDBOffset_stockPokemonNum[offsetof(FIGHT_FLOOR, stockPokemonNum) == 0xde66 ? 1 : -1];
typedef char FloorDBOffset_stockPokemon[offsetof(FIGHT_FLOOR, stockPokemon) == 0xde68 ? 1 : -1];
struct FloorData { u8 terrain, reserved1; u16 floor; u32 name, introSequence, bgm, environmentSound; u16 sides[2]; };
typedef char FloorDBStockSize[sizeof(StockPokemon) == 0xc8 ? 1 : -1];
typedef char FloorDBOffset_attackMsgId[offsetof(FIGHT_FLOOR, attackMsgId) == 0xde28 ? 1 : -1];
typedef char FloorDBOffset_criticalMsgId[offsetof(FIGHT_FLOOR, criticalMsgId) == 0xde2c ? 1 : -1];
typedef char FloorDBOffset_wazaEffectMsgId[offsetof(FIGHT_FLOOR, wazaEffectMsgId) == 0xde30 ? 1 : -1];
typedef char FloorDBOffset_appointPokemonDataId[offsetof(FIGHT_FLOOR, appointPokemonDataId) == 0xde38 ? 1 : -1];
typedef char FloorDBOffset_appointWazaDataId[offsetof(FIGHT_FLOOR, appointWazaDataId) == 0xde3a ? 1 : -1];
typedef char FloorDBOffset_appointItemDataId[offsetof(FIGHT_FLOOR, appointItemDataId) == 0xde3c ? 1 : -1];
typedef char FloorDBOffset_appointTokuseiDataId[offsetof(FIGHT_FLOOR, appointTokuseiDataId) == 0xde3e ? 1 : -1];
#endif
