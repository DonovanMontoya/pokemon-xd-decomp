/* Debug menu entries for editing the hero (money, coupons, party Pokemon). */
#include <global.h>

typedef struct Pokemon {
    u8 data[0xC4];
} Pokemon;

void pokemonInit(Pokemon*);
s32 dbgMenuPokemonEditSub(Pokemon*, s32, s32, s32, s32, s32);
u8 fightIsFight(void);
void heroAddPokecoupon(s32, s32);
void heroAddPokedoru(s32, s32);
void heroCatchPokemon(s32, Pokemon*, s32, s32, s32);
Pokemon* heroGetStatus(s32, s32, s32);
void menuDbgItemCreate(void);
s32 menuOpen(s32, s32);

s32 dbgMenuHeroCreateItem(void) {
    menuDbgItemCreate();
    return 0;
}

s32 dbgMenuHeroIncCoupon(void) {
    s32 value = menuOpen(2, 1);

    if (value == -1) {
        return 0;
    }
    heroAddPokecoupon(0, value);
    return 0;
}

s32 dbgMenuHeroIncMoney(void) {
    s32 value = menuOpen(2, 1);

    if (value == -1) {
        return 0;
    }
    heroAddPokedoru(0, value);
    return 0;
}

s32 dbgMenuHeroPokemonAdd(void) {
    static Pokemon pokemon;
    static u8 firstFlag = 1;

    if (fightIsFight() == 1) {
        return -1;
    }
    if (firstFlag) {
        pokemonInit(&pokemon);
        firstFlag = 0;
    }
    if (dbgMenuPokemonEditSub(&pokemon, 0, 0, 0, 0, 0) < 0) {
        return -1;
    }
    heroCatchPokemon(0, &pokemon, 0, 4, 1);
    return -1;
}

#define DBG_HERO_SELECT(n)                                           \
    s32 dbgMenuHeroPokemonSelect##n(void) {                          \
        Pokemon* pokemon;                                            \
        if (fightIsFight() == 1) {                                   \
            return -1;                                               \
        }                                                            \
        pokemon = heroGetStatus(0, 3, n);                            \
        if (pokemon == 0) {                                       \
            return -1;                                               \
        }                                                            \
        return dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);        \
    }

DBG_HERO_SELECT(5)
DBG_HERO_SELECT(4)
DBG_HERO_SELECT(3)
DBG_HERO_SELECT(2)
DBG_HERO_SELECT(1)
DBG_HERO_SELECT(0)
