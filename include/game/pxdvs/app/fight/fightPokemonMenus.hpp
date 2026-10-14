#ifndef FIGHT_POKEMON_MENUS_HPP
#define FIGHT_POKEMON_MENUS_HPP
#include <game/pxdvs/app/fight/fightPokemon.hpp>

// Only fields touched by the battle conversion are named here. The original
// menu stores the subbar flag at 0x16 and displayed sex at 0x28.
struct FightMenuPokemonStatus {
    u8 reserved00[0x16];
    u8 hideSubbar;
    u8 reserved17[0x11];
    u8 sex;
    u8 reserved29[4];
    u8 reserved2d;
};
struct FightMenuWazaStatus {
    u8 reserved00[0x40];
    FightOutPokemon* fightPokemon;
};
struct FightMenuLvupStatus {
    u8 mode;
    u8 reserved01;
    u16 maxHp;
    u16 physicalAttack;
    u16 physicalDefense;
    u16 speed;
    u16 specialAttack;
    u16 specialDefense;
};
extern "C" {
void pokemon_SetRnd(Pokemon*, u32);
void pokemon_SetCatchTrainerRnd(Pokemon*, u32);
void fightOutPokemonGetRndStatus(FightOutPokemon*, u32*, u32*);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon*);
void pokemonToMenuPokemonStatus(Pokemon*, FightPokemon*, FightMenuPokemonStatus*, s32);
void pokemonToMenuPokemonStatusSubBar(Pokemon*, FightMenuPokemonStatus*);
u32 menuSubGetPokemonSexForFightDisp(Pokemon*);
u8 fightFloor_GetFightKindPokemonStatusMenuSubbarFlag(void*);
void pokemonToMenuWazaStatus(Pokemon*, FightMenuWazaStatus*);
u32 pokemon_GetMaxHp(Pokemon*);
u32 pokemon_GetPhyAtk(Pokemon*);
u32 pokemon_GetPhyDef(Pokemon*);
u32 pokemon_GetSpeAtk(Pokemon*);
u32 pokemon_GetSpeDef(Pokemon*);
void fightOutPokemonToMenuPokemonStatus(FightOutPokemon*, FightMenuPokemonStatus*);
void fightOutPokemonToMenuWazaStatus(FightOutPokemon*, FightMenuWazaStatus*);
void fightPokemonToMenuWazaStatus(FightPokemon*, FightMenuWazaStatus*);
void fightPokemonToMenuLvupStatus(FightPokemon*, FightMenuLvupStatus*);
}
#endif
