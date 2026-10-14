#include <game/pxdvs/app/fight/fightPokemonEnemyRecovery.hpp>
#pragma dont_inline on
extern "C" {
FightOutPokemonEnemy* fightOutPokemonEnemySearchAry(FightOutPokemonEnemy* array, u16 count, FightOutPokemon* target) {
    if (array == 0) return 0;
    FightOutPokemonEnemy* enemy;
    u16 i;
    for (i=0; i<count; ++i) {
        enemy=&array[i];
        if (fightOutPokemonEnemyCheckValid(enemy) && fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(enemy)==target) return enemy;
    }
    return 0;
}
bool fightOutPokemonEnemyCheckValid(FightOutPokemonEnemy* enemy) {
    return (u32)fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(enemy) > 0u;
}
void fightOutPokemonEnemyCreate(FightOutPokemonEnemy* enemy, FightOutPokemon* target) {
    if (enemy != 0 && target != 0) {
    fightOutPokemonEnemyInit(enemy);
    fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(enemy,target);
    u16 hp=pokemon_GetHp(fightOutPokemonGetPokemonPtr(target));
    fightOutPokemonEnemyBiosSetInitHp(enemy,hp);
    }
}
void fightOutPokemonEnemyInitAry(FightOutPokemonEnemy* array, u16 count) {
    if (array == 0) return;
    for (u16 i=0; i<count; ++i) fightOutPokemonEnemyInit(&array[i]);
}
void fightOutPokemonEnemyInit(FightOutPokemonEnemy* enemy) {
    fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(enemy,0);
    fightOutPokemonEnemyBiosSetOumuWazaDataId(enemy,0);
    fightOutPokemonEnemyBiosSetInitHp(enemy,0);
    fightOutPokemonEnemyBiosSetDamage(enemy,0);
}
}
