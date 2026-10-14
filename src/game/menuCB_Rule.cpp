#include <game/menuCB_RuleLayout.hpp>

extern "C" {

void *memcpy(void *, const void *, u32);
void *memset(void *, int, u32);
int memcmp(const void *, const void *, u32);
u16 *GSmsgGetGSchar(s32);
MenuCBRule *menuCBBios_CurrentRule(void);
u8 menuCBBios_CurrentlyWorkingToolBattle(void);
Pokemon *heroBiosGetPokemonPtr(Hero *, u16);
bool itemDataCheckValid(u16);
void pokemonBiosCopy(Pokemon *, Pokemon *);
u8 pokemonBiosGetEventGetFlag(Pokemon *);
u16 pokemonBiosGetItemDataId(Pokemon *);
u8 pokemonBiosGetLevel(Pokemon *);
u16 pokemonBiosGetMaxHp(Pokemon *);
u16 pokemonBiosGetMaxHpEffort(Pokemon *);
u16 pokemonBiosGetNimbleness(Pokemon *);
u16 pokemonBiosGetNimblenessEffort(Pokemon *);
u16 pokemonBiosGetPhyAtk(Pokemon *);
u16 pokemonBiosGetPhyAtkEffort(Pokemon *);
u16 pokemonBiosGetPhyDef(Pokemon *);
u16 pokemonBiosGetPhyDefEffort(Pokemon *);
u16 pokemonBiosGetPokemonDataId(Pokemon *);
u16 pokemonBiosGetSpeAtk(Pokemon *);
u16 pokemonBiosGetSpeAtkEffort(Pokemon *);
u16 pokemonBiosGetSpeDef(Pokemon *);
u16 pokemonBiosGetSpeDefEffort(Pokemon *);
u8 pokemonBiosGetTamagoFlag(Pokemon *);
bool pokemonCheckValid(Pokemon *);
s32 pokemonGetStatus(Pokemon *, s32, s32, u16);
u8 pokemonIsDarkPokemon(Pokemon *);
void pokemonResetBasisStatus(Pokemon *);
void toolBattleRuleErrorFlagClear(s32, s32);
void *wazaDataBiosGetPtr(u16);

u8 menuCBRule_CheckLegendPokemon(Pokemon *, MenuCBRule *);
bool menuCBRule_CheckPokemonError(Pokemon *, s32);
u8 menuCBRule_CheckPokemonErrorAll(Pokemon *);
bool menuCBRule_CheckPokemonRegulation(Pokemon *, MenuCBRule *, s32);
u8 menuCBRule_CheckPokemonRegulationAll(Pokemon *, MenuCBRule *);
bool menuCBRule_CheckRegulationItem(u16);
u8 menuCBRule_CheckTrainerError(Hero *, s32);
u8 menuCBRule_CheckTrainerErrorAll(Hero *);
bool menuCBRule_CheckTrainerRegulation(Hero *, MenuCBRule *, s32);
u8 menuCBRule_CheckTrainerRegulationAll(Hero *, MenuCBRule *);
bool menuCBRule_CheckTrainerRegulationAt(Hero *, Pokemon *, MenuCBRule *, s32);
bool menuCBRule_CheckValidItem(u16);
u8 menuCBRule_IsBlankPokemon(Pokemon *);
u32 menuCBRule_RegulationItems(void);
u8 menuCBRule_CheckErrorAll(Hero *);
s16 menuCBRule_ParticipationPokemonMax(void);
u8 menuCBRule_CheckRegulationAll(Hero *, MenuCBRule *);
u8 menuCBRule_CheckPokemonEventFlag(Pokemon *);
s16 menuCBRule_ParticipationPokemonMax2(void);
u16 menuCBRule_RegulationItemID(s32);
MenuCBRule *menuCBRule_ConstantRule2(s32);
MenuCBRule *menuCBRule_ConstantRule(s32);
}
static u8 _menuCBRule_IsTamagoPokemon(Pokemon *);
extern "C" {

static const MenuCBRule oreRule = { 1, 100, 600, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, -60, -20, 1, 1, 6, 1 };
static const MenuCBRule staRule[3] = {
    { 1, 100, 600, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, -60, -20, 1, 1, 6, 1 },
    { 1, 50, 300, 6, 2, 0, 0, 0, 0, 1, 1, 0, 1, -60, -20, 1, 1, 6, 1 },
    { 1, 100, 600, 6, 2, 0, 0, 0, 0, 1, 1, 0, 1, -60, -20, 1, 1, 6, 1 },
};
static MenuCBRule ruleTempBuff;

void menuCBRule_ErrorFlagSetOkPushTiming(Hero *hero)
{
    MenuCBRule *rule = menuCBBios_CurrentRule();
    u32 i;
    for (i = 0; i < 6; i++) {
        _CB.flags[0][i].f1.trainerCount = menuCBRule_CheckTrainerRegulation(hero, rule, 3) == 0;
    }
}

void menuCBRule_ErrorFlagSetItemGetTiming(Hero *hero, Pokemon *pokemon, s32 idx)
{
    MenuCBRule *rule = menuCBBios_CurrentRule();
    pokemonBiosGetItemDataId(pokemon);
    if (menuCBRule_CheckPokemonRegulation(pokemon, rule, 2) == 0) {
        switch (rule->unk8) {
        case 0:
            break;
        case 1:
            _CB.flags[0][idx].f1.item1 = 1;
            break;
        case 2:
            _CB.flags[0][idx].f1.item2 = 1;
            break;
        }
    }
    _CB.flags[0][idx].f1.errItem = menuCBRule_CheckPokemonError(pokemon, 3) == 0;
    _CB.flags[0][idx].f1.itemAt = menuCBRule_CheckTrainerRegulationAt(hero, pokemon, rule, 2) == 0;
}

void menuCBRule_ErrorFlagSetPokemonGetTiming(Hero *hero, Pokemon *pokemon, s32 idx)
{
    MenuCBRule *rule = menuCBBios_CurrentRule();
    _CB.flags[0][idx].f0.levelMin = menuCBRule_CheckPokemonRegulation(pokemon, rule, 0) == 0;
    _CB.flags[0][idx].f0.levelMax = menuCBRule_CheckPokemonRegulation(pokemon, rule, 1) == 0;
    _CB.flags[0][idx].f0.errStatus = menuCBRule_CheckPokemonError(pokemon, 0) == 0;
    _CB.flags[0][idx].f0.errDark = menuCBRule_CheckPokemonError(pokemon, 1) == 0;
    _CB.flags[0][idx].f0.errTamago = menuCBRule_CheckPokemonError(pokemon, 2) == 0;
    _CB.flags[0][idx].f1.errValid = menuCBRule_CheckPokemonError(pokemon, 5) == 0;
    _CB.flags[0][idx].f0.errWaza = menuCBRule_CheckPokemonError(pokemon, 4) == 0;
    _CB.flags[0][idx].f1.trainerLevel = menuCBRule_CheckTrainerRegulation(hero, rule, 0) == 0;
    _CB.flags[0][idx].f0.legend = menuCBRule_CheckLegendPokemon(pokemon, rule) == 0;
    _CB.flags[0][idx].f0.sameAt = menuCBRule_CheckTrainerRegulationAt(hero, pokemon, rule, 1) == 0;
}

u8 menuCBRule_CheckLegendPokemon(Pokemon *pokemon, MenuCBRule *rule)
{
    u16 id;
    u32 i;
    u16 *data;
    if (rule->unk18 == 1) {
        return 1;
    }
    id = pokemonBiosGetPokemonDataId(pokemon);
    data = legendPokemonData;
    for (i = 0; i < *legendPokemonData_number; i++) {
        if (id == data[i]) {
            return 0;
        }
    }
    return 1;
}

void menuCBRule_ErrorFlagSet(Hero *hero, s32 idx)
{
    MenuCBRule *rule = menuCBBios_CurrentRule();
    u32 i;
    Pokemon *pokemon;
    for (i = 0; i < 6; i++) {
        pokemon = heroBiosGetPokemonPtr(hero, i);
        pokemonBiosGetItemDataId(pokemon);
        toolBattleRuleErrorFlagClear(idx, i);
        _CB.flags[idx][i].f0.levelMin = menuCBRule_CheckPokemonRegulation(pokemon, rule, 0) == 0;
        _CB.flags[idx][i].f0.levelMax = menuCBRule_CheckPokemonRegulation(pokemon, rule, 1) == 0;
        if (menuCBRule_CheckPokemonRegulation(pokemon, rule, 2) == 0) {
            switch (rule->unk8) {
            case 0:
                break;
            case 1:
                _CB.flags[idx][i].f1.item1 = 1;
                break;
            case 2:
                _CB.flags[idx][i].f1.item2 = 1;
                break;
            }
        }
        _CB.flags[idx][i].f0.errStatus = menuCBRule_CheckPokemonError(pokemon, 0) == 0;
        _CB.flags[idx][i].f0.errDark = menuCBRule_CheckPokemonError(pokemon, 1) == 0;
        _CB.flags[idx][i].f0.errTamago = menuCBRule_CheckPokemonError(pokemon, 2) == 0;
        _CB.flags[idx][i].f1.errItem = menuCBRule_CheckPokemonError(pokemon, 3) == 0;
        _CB.flags[idx][i].f0.errWaza = menuCBRule_CheckPokemonError(pokemon, 4) == 0;
        _CB.flags[idx][i].f1.errValid = menuCBRule_CheckPokemonError(pokemon, 5) == 0;
        _CB.flags[idx][i].f1.trainerLevel = menuCBRule_CheckTrainerRegulation(hero, rule, 0) == 0;
        _CB.flags[idx][i].f0.sameAt = menuCBRule_CheckTrainerRegulationAt(hero, pokemon, rule, 1) == 0;
        _CB.flags[idx][i].f1.itemAt = menuCBRule_CheckTrainerRegulationAt(hero, pokemon, rule, 2) == 0;
        _CB.flags[idx][i].f1.trainerCount = menuCBRule_CheckTrainerRegulation(hero, rule, 3) == 0;
        _CB.flags[idx][i].f0.legend = menuCBRule_CheckLegendPokemon(pokemon, rule) == 0;
    }
}

u8 menuCBRule_CheckPokemonEventFlag(Pokemon *pokemon)
{
    switch (pokemonBiosGetPokemonDataId(pokemon)) {
    case 0x97:
    case 0x19A:
        if (pokemonBiosGetEventGetFlag(pokemon) == 0) {
            return 0;
        }
    }
    return 1;
}

u8 menuCBRule_CheckErrorAll(Hero *hero)
{
    u16 i;
    if (menuCBRule_CheckTrainerErrorAll(hero) == 0) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        if (menuCBRule_CheckPokemonErrorAll(heroBiosGetPokemonPtr(hero, i)) == 0) {
            return 0;
        }
    }
    return 1;
}

u8 menuCBRule_CheckTrainerErrorAll(Hero *arg)
{
    s32 i;
    for (i = 0; i < 0; i++) {
        if (menuCBRule_CheckTrainerError(arg, i) == 0) {
            return 0;
        }
    }
    return 1;
}

u8 menuCBRule_CheckTrainerError(Hero *a, s32 b)
{
    return 0;
}

u8 menuCBRule_CheckPokemonErrorAll(Pokemon *pokemon)
{
    s32 i;
    for (i = 0; i < 6; i++) {
        if (menuCBRule_CheckPokemonError(pokemon, i) == 0) {
            return 0;
        }
    }
    return 1;
}


bool menuCBRule_CheckPokemonError(Pokemon *pokemon, s32 kind)
{
    Pokemon copy;
    u32 hp;
    u32 total;
    if (menuCBRule_IsBlankPokemon(pokemon) != 0) {
        return 1;
    }
    switch (kind) {
    case 0: {
        u32 a;
        if (menuCBRule_CheckPokemonError(pokemon, 2) == 0) {
            return 1;
        }
        if (menuCBRule_CheckPokemonEventFlag(pokemon) == 0) {
            return 0;
        }
        pokemonBiosCopy(&copy, pokemon);
        pokemonResetBasisStatus(&copy);
        if (pokemonBiosGetMaxHp(&copy) < pokemonBiosGetMaxHp(pokemon) || pokemonBiosGetPhyAtk(&copy) < pokemonBiosGetPhyAtk(pokemon)
            || pokemonBiosGetPhyDef(&copy) < pokemonBiosGetPhyDef(pokemon) || pokemonBiosGetSpeAtk(&copy) < pokemonBiosGetSpeAtk(pokemon)
            || pokemonBiosGetSpeDef(&copy) < pokemonBiosGetSpeDef(pokemon)
            || pokemonBiosGetNimbleness(&copy) < pokemonBiosGetNimbleness(pokemon)) {
            return 0;
        }
        total = pokemonBiosGetMaxHpEffort(pokemon);
        total += pokemonBiosGetPhyAtkEffort(pokemon);
        total += pokemonBiosGetPhyDefEffort(pokemon);
        total += pokemonBiosGetSpeAtkEffort(pokemon);
        total += pokemonBiosGetSpeDefEffort(pokemon);
        total += pokemonBiosGetNimblenessEffort(pokemon);
        if (total > 0x1FE) {
            return 0;
        }
        if (pokemonBiosGetMaxHpEffort(pokemon) > 0xFF || pokemonBiosGetPhyAtkEffort(pokemon) > 0xFF
            || pokemonBiosGetPhyDefEffort(pokemon) > 0xFF || pokemonBiosGetSpeAtkEffort(pokemon) > 0xFF
            || pokemonBiosGetSpeDefEffort(pokemon) > 0xFF || pokemonBiosGetNimblenessEffort(pokemon) > 0xFF) {
            return 0;
        }
        return 1;
    }
    case 1:
        return pokemonIsDarkPokemon(pokemon) == 0;
    case 2:
        return pokemonBiosGetTamagoFlag(pokemon) == 0;
    case 3:
        return menuCBRule_CheckValidItem(pokemonBiosGetItemDataId(pokemon));
    case 4: {
        int i;
        for (i = 0; i < 4; i++) {
            u16 w = pokemonGetStatus(pokemon, 0, 0x7F, i);
            if (w != 0) {
                void *none = wazaDataBiosGetPtr(0);
                if (wazaDataBiosGetPtr(w) == none) {
                    return 0;
                }
            }
        }
        return 1;
    }
    case 5:
        pokemonGetStatus(pokemon, 0, 0x6E, 0);
        return pokemonCheckValid(pokemon);
    }
    return 0;
}

u8 menuCBRule_CheckRegulationAll(Hero *hero, MenuCBRule *rule)
{
    s32 i;
    s32 count = 0;
    if (menuCBRule_CheckTrainerRegulationAll(hero, rule) == 0) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        Pokemon *p = heroBiosGetPokemonPtr(hero, i);
        if (p != 0 && pokemonCheckValid(p) != 0) {
            if (menuCBRule_CheckPokemonRegulationAll(p, rule) == 0) {
                return 0;
            }
            if (menuCBRule_CheckLegendPokemon(p, rule) == 0) {
                return 0;
            }
            count++;
        }
    }
    return count > 0;
}

u8 menuCBRule_CheckTrainerRegulationAll(Hero *hero, MenuCBRule *rule)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        if (menuCBRule_CheckTrainerRegulation(hero, rule, i) == 0) {
            return 0;
        }
    }
    return 1;
}

bool menuCBRule_CheckTrainerRegulationAt(Hero *hero, Pokemon *pokemon, MenuCBRule *rule, s32 kind)
{
    bool r;
    switch (kind) {
    case 0:
        return menuCBRule_CheckTrainerRegulation(hero, rule, kind);
    case 1: {
        u32 id;
        int i;
        Pokemon *q;
        if (rule->unkC != 0) {
            return 1;
        }
        if (menuCBRule_IsBlankPokemon(pokemon) != 0 || _menuCBRule_IsTamagoPokemon(pokemon) != 0) {
            return 1;
        }
        for (i = 0; i < 6; i++) {
            q = heroBiosGetPokemonPtr(hero, i);
            if (q != pokemon && menuCBRule_IsBlankPokemon(q) == 0 && _menuCBRule_IsTamagoPokemon(q) == 0) {
                id = pokemonBiosGetPokemonDataId(pokemon);
                u32 id2 = pokemonBiosGetPokemonDataId(q);
                if (id2 == id) {
                    return 0;
                }
            }
        }
        return 1;
    }
    case 2: {
        Pokemon *q;
        int i;
        u32 id;
        if (rule->unkD != 0) {
            return 1;
        }
        if (menuCBRule_IsBlankPokemon(pokemon) != 0 || _menuCBRule_IsTamagoPokemon(pokemon) != 0) {
            return 1;
        }
        if (pokemonBiosGetItemDataId(pokemon) == 0) {
            return 1;
        }
        for (i = 0; i < 6; i++) {
            q = heroBiosGetPokemonPtr(hero, i);
            if (q != pokemon && menuCBRule_IsBlankPokemon(q) == 0 && _menuCBRule_IsTamagoPokemon(q) == 0) {
                id = pokemonBiosGetItemDataId(pokemon);
                u32 id2 = pokemonBiosGetItemDataId(q);
                if (id2 == id) {
                    return 0;
                }
            }
        }
        return 1;
    }
    case 3: {
        r = 0;
        if (menuCBRule_CheckTrainerRegulation(hero, rule, 3) != 0 || menuCBRule_IsBlankPokemon(pokemon) == 0) {
            r = 1;
        }
        return r;
    }
    }
    return 0;
}

bool menuCBRule_CheckTrainerRegulation(Hero *hero, MenuCBRule *rule, s32 kind)
{
    s32 sum = 0;
    u8 diffPoke = 1;
    u8 diffItem = 1;
    u32 i;
    for (i = 0; i < 6; i++) {
        Pokemon *p = heroBiosGetPokemonPtr(hero, i);
        if (menuCBRule_IsBlankPokemon(p) == 0 && _menuCBRule_IsTamagoPokemon(p) == 0) {
            sum += pokemonBiosGetLevel(p);
            u32 j;
            for (j = i + 1; j < 6; j++) {
                Pokemon *q = heroBiosGetPokemonPtr(hero, j);
                if (menuCBRule_IsBlankPokemon(q) == 0 && _menuCBRule_IsTamagoPokemon(q) == 0) {
                    if (pokemonBiosGetItemDataId(p) != 0) {
                        diffItem &= pokemonBiosGetItemDataId(p) != pokemonBiosGetItemDataId(q);
                    }
                    {
                        diffPoke &= pokemonBiosGetPokemonDataId(p) != pokemonBiosGetPokemonDataId(q);
                    }
                }
            }
        }
    }
    switch (kind) {
    case 0:
        return sum <= rule->unk4;
    case 1:
        {
            bool res = 0;
            if (rule->unkC != 0 || diffPoke != 0) {
                res = 1;
            }
            return res;
        }
    case 2:
        {
            bool res = 0;
            if (rule->unkD != 0 || diffItem != 0) {
                res = 1;
            }
            return res;
        }
    case 3: {
        u32 count = 0;
        s16 t;
        u16 k;
        for (k = 0; k < 6; k++) {
            if (menuCBRule_IsBlankPokemon(heroBiosGetPokemonPtr(hero, k)) == 0) {
                count++;
            }
        }
        t = rule->unk1C;
        if (t == 1) {
            return t <= (u16)count;
        }
        return rule->unk1A <= (u16)count;
    }
    }
    return 0;
}

u8 menuCBRule_CheckPokemonRegulationAll(Pokemon *pokemon, MenuCBRule *rule)
{
    s32 i;
    for (i = 0; i < 3; i++) {
        if (menuCBRule_CheckPokemonRegulation(pokemon, rule, i) == 0) {
            return 0;
        }
    }
    return 1;
}

bool menuCBRule_CheckPokemonRegulation(Pokemon *pokemon, MenuCBRule *rule, s32 kind)
{
    if (menuCBRule_IsBlankPokemon(pokemon) != 0) {
        return 1;
    }
    switch (kind) {
    case 0:
        return rule->unk0 <= pokemonBiosGetLevel(pokemon);
    case 1:
        return pokemonBiosGetLevel(pokemon) <= rule->unk2;
    case 2:
        return menuCBRule_CheckRegulationItem(pokemonBiosGetItemDataId(pokemon));
    }
    return 0;
}

s32 menuCBRule_CheckHero(Hero *hero)
{
    s32 r = 0;
    if (menuCBRule_CheckErrorAll(hero) != 0 && menuCBRule_CheckRegulationAll(hero, menuCBBios_CurrentRule()) != 0) {
        r = 1;
    }
    return r;
}

}
static u8 _menuCBRule_IsTamagoPokemon(Pokemon *pokemon)
{
    u8 r;
    if (menuCBRule_IsBlankPokemon(pokemon) != 0) {
        r = 0;
    } else {
        r = 0;
        if (pokemonBiosGetTamagoFlag(pokemon) != 0 || pokemonCheckValid(pokemon) == 0) {
            r = 1;
        }
    }
    return r;
}

extern "C" {
MenuCBRule *menuCB_OreRule(void)
{
    if (menuCBBios_CurrentlyWorkingToolBattle() != 0) {
        return 0;
    }
    return (MenuCBRule *)&oreRule;
}

u8 menuCBRule_IsBlankPokemon(Pokemon *pokemon)
{
    u8 r = 0;
    if (pokemon == 0 || pokemonGetStatus(pokemon, 0, 0x6E, 0) == 0) {
        r = 1;
    }
    return r;
}

u8 menuCBRule_EnableSkill_SonicBoom(void)
{
    return menuCBBios_CurrentRule()->unk13;
}

u8 menuCBRule_EnableSkill_Michidure(void)
{
    return menuCBBios_CurrentRule()->unk12;
}

u8 menuCBRule_ProhibitionSuicide(void)
{
    return menuCBBios_CurrentRule()->unk11;
}

u8 menuCBRule_EnableSkillSwap(void)
{
    return menuCBBios_CurrentRule()->unk10;
}

u8 menuCBRule_EnableSbToIceed(void)
{
    return menuCBBios_CurrentRule()->unkF;
}

u8 menuCBRule_EnableSbToSleep(void)
{
    return menuCBBios_CurrentRule()->unkE;
}

u8 menuCBRule_DEOKISISUCamouflage(void)
{
    return menuCBBios_CurrentRule()->unk19;
}

s16 menuCBRule_GetCommandTimeLimit(void)
{
    return menuCBBios_CurrentRule()->unk16;
}

s32 menuCBRule_GetBattleTimeLimit(void)
{
    return menuCBBios_CurrentRule()->unk14 * 60;
}

bool menuCBRule_CheckValidItem(u16 id)
{
    switch (id) {
    case 0:
        return 1;
    case 0xAF:
        return 0;
    default:
        return itemDataCheckValid(id);
    }
}

bool menuCBRule_CheckRegulationItem(u16 id)
{
    MenuCBRule *rule = menuCBBios_CurrentRule();
    if (menuCBRule_CheckValidItem(id) == 0) {
        return 0;
    }
    switch (rule->unk8) {
    case 0:
        return 1;
    case 1:
        return id == 0;
    case 2: {
        u32 n = menuCBRule_RegulationItems();
        u32 i;
        for (i = 0; i < n; i++) {
            if (id == itemtoolbattle[i]) {
                return rule->itemFlags[i] == 0;
            }
        }
        return 1;
    }
    }
    return 0;
}

u16 menuCBRule_RegulationItemID(s32 i)
{
    if (i < 0 || menuCBRule_RegulationItems() <= (u32)i) {
        return 0;
    }
    return itemtoolbattle[i];
}

u32 menuCBRule_RegulationItems(void)
{
    return itemtoolbattle_number - 1;
}

s16 menuCBRule_ParticipationPokemonMax2(void)
{
    s16 ret = 6;
    switch (_CB.unkC) {
    case 0:
        if (_CB.rules[0].unk1C == 0) {
            ret = _CB.rules[0].unk1A;
        }
        break;
    case 1:
        if (_CB.rules[1].unk1C == 0) {
            ret = _CB.rules[1].unk1A;
        }
        break;
    case 2:
        if (_CB.rules[2].unk1C == 0) {
            ret = _CB.rules[2].unk1A;
        }
        break;
    case 3:
        if (_CB.rules[3].unk1C == 0) {
            ret = _CB.rules[3].unk1A;
        }
        break;
    case 4:
        if (_CB.rules[4].unk1C == 0) {
            ret = _CB.rules[4].unk1A;
        }
        break;
    case 5:
        if (_CB.rules[5].unk1C == 0) {
            ret = _CB.rules[5].unk1A;
        }
        break;
    }
    return ret;
}

s16 menuCBRule_ParticipationPokemonMax(void)
{
    return menuCBRule_ParticipationPokemonMax2();
}

MenuCBRule *menuCBRule_ConstantRule2(s32 idx)
{
    s32 n;
    u32 i;
    int k;
    u16 *p;
    switch (idx) {
    case 0:
    case 1:
    case 2:
        n = idx;
        break;
    case 3:
    case 4:
    case 5:
        n = 2;
        break;
    default:
        n = 0;
        break;
    }
    memset(&ruleTempBuff, 0, sizeof(MenuCBRule));
    memcpy(&ruleTempBuff, &staRule[n], sizeof(MenuCBRule));
    switch (idx) {
    case 3:
    case 4:
    case 5:
        ruleTempBuff.unk1C = 0;
        ruleTempBuff.unk1A = 4;
        break;
    }
    if (idx != 0) {
        for (i = 0; i < itemtoolbattle_number; i++) {
            if (menuCBRule_RegulationItemID(i) == 0xBF) {
                ruleTempBuff.itemFlags[i] = 1;
            }
        }
    }
    switch (idx) {
    case 0:
    case 1:
    case 2:
        p = 0;
        break;
    case 3:
        p = GSmsgGetGSchar(0x438A);
        break;
    case 4:
        p = GSmsgGetGSchar(0x438B);
        break;
    case 5:
        p = GSmsgGetGSchar(0x438C);
        break;
    }
    for (k = 0; k < 21; k++) {
        if (p != 0) {
            if (*p == 0xFFFF) {
                p += 2;
            }
            ruleTempBuff.name[k] = *p;
            if (*p != 0) {
                p++;
            }
        } else {
            ruleTempBuff.name[k] = 0;
        }
    }
    return &ruleTempBuff;
}

MenuCBRule *menuCBRule_ConstantRule(s32 idx)
{
    switch (idx) {
    case 0:
    case 1:
    case 2:
        return (MenuCBRule *)&staRule[idx];
    }
    return 0;
}

void menuCBRule_Copy(void *dst, const void *src)
{
    memcpy(dst, src, 0x90);
}

bool menuCBRule_IsEquals(const void *a, const void *b)
{
    return memcmp(a, b, 0x90) == 0;
}

}
