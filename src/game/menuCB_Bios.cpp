#include <game/menuCB_BiosLayout.hpp>

extern "C" {
void *memcpy(void *, const void *, u32);
void *menuCB_RuleTitleNameGet(s32);
void *memset(void *, int, u32);
u8 heroBiosGetHomePlace(Hero *);
u8 heroBiosGetSexDataId(Hero *);
void heroBiosCopy(Hero *, Hero *);
void heroBiosSetHizukiFlag(Hero *, s32);
Pokemon *heroBiosGetPokemonPtr(Hero *, u16);
void fightTrainerCreateFightTrainerDataIdToHero(u16, s32, Hero *, s32);
void pokemonAllKaihuku(Pokemon *);
u8 menuCBRule_IsBlankPokemon(Pokemon *);
s16 menuCBRule_ParticipationPokemonMax(void);
MenuCBBiosRule *menuCBRule_ConstantRule(s32);
MenuCBBiosRule *menuCBRule_ConstantRule2(s32);
MenuCBBiosRule *menuCB_OreRule(void);
void menuCB_InitMenu(s32);
_TOOL_SAVEDATA *savedataGetStatus(s32, s32);

extern s32 toolbattle_mode_flag;
static s32 staControlerMap[4] = { 1, 2, 3, 4 };
static u8 stbCB_Lock;
u16 *GSmsgGetGSchar(s32);
u16 menuCBRule_RegulationItemID(s32);
extern u32 itemtoolbattle_number;

void menuCBBios_ClearTrainer(MenuCBBiosTrainer *);
void menuCBBios_InitTrainer(MenuCBBiosTrainer *, u16);
void menuCBBios_InitTrainerFromHero(MenuCBBiosTrainer *, Hero *, u16);
s32 menuCBBios_FightTrainerDataIDToHomePlace(u16);
s32 menuCBBios_PortIDtoControlerID(s32);
s32 menuCBBios_ControlerIDtoPortID(s32);
u16 menuCBTrainerBios_GetPlayerID(MenuCBBiosTrainer *);
s32 menuCBBios_CurrentRuleType(void);
MenuCBBiosRule *menuCBBios_GetRule(s32);
u8 menuCBBios_ContextIsLocked(void);
void menuCBBios_UnlockContext(void);
void menuCBBios_InitTrainerFromDataID(MenuCBBiosTrainer *, u16, s32);
void menuCBTrainerBios_SetControlerID(MenuCBBiosTrainer *, s32);
void menuCBBios_CopyTrainer(MenuCBBiosTrainer *, MenuCBBiosTrainer *);
}
static void _menuCBBios_RecoverAllPokemons(Hero *);
static void menuCBBios_InitContextAtFirst(_MENUCBWORK *, _TOOL_SAVEDATA *);

extern "C" {
void menuCB_SetToolBattleModeFlag(s32 flag)
{
    toolbattle_mode_flag = flag;
}

s32 menuCB_GetToolBattleModeFlag(void)
{
    return toolbattle_mode_flag;
}

s32 menuCB_GetBattleController2P(void)
{
    return _CB.unkB0E0;
}

void *menuCB_RuleTitleNameGet(s32 idx)
{
    return &_CB.rules[idx].name;
}

u16 menuCBTrainerBios_GetPlayerID(MenuCBBiosTrainer *trainer)
{
    return trainer->unk2;
}

void menuCBTrainerBios_SetHomePlace(MenuCBBiosTrainer *trainer, s32 place)
{
    trainer->unk4 = place;
}

s32 menuCBTrainerBios_GetHomePlace(MenuCBBiosTrainer *trainer)
{
    return trainer->unk4;
}

void menuCBBios_CopyTrainer(MenuCBBiosTrainer *dst, MenuCBBiosTrainer *src)
{
    memcpy(dst, src, sizeof(MenuCBBiosTrainer));
}

s32 menuCBTrainerBios_GetControlerID(MenuCBBiosTrainer *trainer)
{
    return trainer->unk24;
}

void menuCBTrainerBios_SetControlerID(MenuCBBiosTrainer *trainer, s32 id)
{
    trainer->unk24 = id;
}

void menuCBBios_InitVersusTrainer(MenuCBBiosTrainer *trainer, Hero *hero)
{
    u16 id = 0x1388;
    switch (heroBiosGetHomePlace(hero)) {
    case 0:
        id = 0x1388;
        break;
    case 1:
        switch (heroBiosGetSexDataId(hero)) {
        case 0:
            id = 0x1389;
            break;
        case 1:
            id = 0x138A;
            break;
        case 2:
            break;
        }
        break;
    case 2:
        switch (heroBiosGetSexDataId(hero)) {
        case 0:
            id = 0x138B;
            break;
        case 1:
            id = 0x138C;
            break;
        case 2:
            break;
        }
        break;
    case 3:
        switch (heroBiosGetSexDataId(hero)) {
        case 0:
            id = 0x138D;
            break;
        case 1:
            id = 0x138E;
            break;
        case 2:
            break;
        }
        break;
    }
    menuCBBios_InitTrainerFromHero(trainer, hero, id);
}

void menuCBBios_InitTrainerFromHero(MenuCBBiosTrainer *trainer, Hero *hero, u16 id)
{
    Hero copy;
    heroBiosCopy(&copy, hero);
    heroBiosSetHizukiFlag(&copy, 0);
    _menuCBBios_RecoverAllPokemons(&copy);
    menuCBBios_ClearTrainer(trainer);
    heroBiosCopy(&trainer->hero, &copy);
    heroBiosCopy(&trainer->heroCopy, &copy);
    trainer->unk0 = id;
    trainer->unk4 = menuCBBios_FightTrainerDataIDToHomePlace(id);
}

void menuCBBios_InitTrainerFromDataID(MenuCBBiosTrainer *trainer, u16 id, s32 arg)
{
    Hero hero;
    heroBiosCopy(&hero, &trainer->heroCopy);
    fightTrainerCreateFightTrainerDataIdToHero(id, menuCBBios_PortIDtoControlerID(0), &hero, arg);
    heroBiosSetHizukiFlag(&hero, 0);
    _menuCBBios_RecoverAllPokemons(&hero);
    menuCBBios_ClearTrainer(trainer);
    heroBiosCopy(&trainer->hero, &hero);
    heroBiosCopy(&trainer->heroCopy, &hero);
    trainer->unk0 = id;
    trainer->unk4 = menuCBBios_FightTrainerDataIDToHomePlace(id);
}

void menuCBBios_ClearTrainer(MenuCBBiosTrainer *trainer)
{
    u16 playerId = menuCBTrainerBios_GetPlayerID(trainer);
    menuCBBios_InitTrainer(trainer, playerId);
}

void menuCBBios_InitTrainer(MenuCBBiosTrainer *trainer, u16 playerId)
{
    memset(trainer, 0, sizeof(MenuCBBiosTrainer));
    trainer->unk2 = playerId;
}

s32 menuCBBios_FightTrainerDataIDToHomePlace(u16 id)
{
    switch (id) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 0x1389:
    case 0x138A:
        return 1;
    case 0x138B:
    case 0x138C:
        return 2;
    case 0x138D:
    case 0x138E:
        return 3;
    case 0x1388:
        return 0;
    }
    return 0;
}

MenuCBBiosTrainer *menuCBBios_GetTrainerFromVersusBattleID(s32 id)
{
    s32 i;
    switch (_CB.unk8) {
    case 0:
    case 1:
        if (id >= 0 && id <= 1) {
            return &_CB.trainers[id];
        }
        goto none;
    case 2:
        break;
    }
    for (i = 0; i < 4; i++) {
        if (id == _CB.trainers[i].unk28) {
            return &_CB.trainers[i];
        }
    }
none:
    return 0;
}

s32 menuCBBios_GetToolBattleTrainerKind(void)
{
    return 0;
}

s32 menuCBBios_GetRegisteredHero(void)
{
    return 0;
}

MenuCBBiosTrainer *menuCBBios_GetTrainer(s32 controllerId)
{
    s32 port = menuCBBios_ControlerIDtoPortID(controllerId);
    if (port < 0) {
        return 0;
    }
    return &_CB.trainers[port];
}

MenuCBBiosTrainer *menuCBBios_GetTrainerOrgImmediately(s32 port)
{
    if (port < 0 || port >= 4) {
        return 0;
    }
    return &_CB.orgTrainers[port];
}

MenuCBBiosTrainer *menuCBBios_GetTrainerImmediately(s32 port)
{
    if (port < 0 || port >= 4) {
        return 0;
    }
    return &_CB.trainers[port];
}

Hero *menuCBBios_GetHeroImmediately(s32 port)
{
    if (port < 0 || (u32)port >= 4) {
        return 0;
    }
    return &_CB.trainers[port].hero;
}
}

static void _menuCBBios_RecoverAllPokemons(Hero *hero)
{
    u16 i;
    for (i = 0; i < 6; i++) {
        Pokemon *pokemon = heroBiosGetPokemonPtr(hero, i);
        if (menuCBRule_IsBlankPokemon(pokemon) == 0) {
            pokemonAllKaihuku(pokemon);
        }
    }
}

extern "C" {
s32 menuCBBios_ControlerIDtoPortID(s32 id)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        if (id == staControlerMap[i]) {
            return i;
        }
    }
    return -1;
}

s32 menuCBBios_PortIDtoControlerID(s32 port)
{
    return staControlerMap[port];
}

s16 menuCBBios_ParticipationPokemonMax(void)
{
    return menuCBRule_ParticipationPokemonMax();
}

s32 menuCBBios_CurrentRuleType(void)
{
    return _CB.unkC;
}

MenuCBBiosRule *menuCBBios_CurrentRule(void)
{
    MenuCBBiosRule *rule = menuCB_OreRule();
    if (rule != 0) {
        return rule;
    }
    rule = menuCBRule_ConstantRule2(menuCBBios_CurrentRuleType());
    switch (menuCBBios_CurrentRuleType()) {
    case 0:
    case 1:
    case 2:
        if (rule != 0) {
            return rule;
        }
        break;
    case 3:
    case 4:
    case 5:
        break;
    }
    return menuCBBios_GetRule(menuCBBios_CurrentRuleType());
}

MenuCBBiosRule *menuCBBios_GetRule(s32 idx)
{
    if (idx < 0 || (u32)idx >= 6) {
        return 0;
    }
    return &_CB.rules[idx];
}

void menuCBBios_RuleConstRuleSet(void)
{
    _TOOL_SAVEDATA *save = savedataGetStatus(0, 0xE);
    save->rules[0] = *menuCBRule_ConstantRule(0);
    save->rules[1] = *menuCBRule_ConstantRule(1);
    save->rules[2] = *menuCBRule_ConstantRule(2);
    save->rules[0].unk50 = 0x9124;
    save->rules[1].unk50 = 0xA2D4;
    save->rules[2].unk50 = 0xB51C;
}

void menuCBBios_RuleEditSaveON(u8 on)
{
    _TOOL_SAVEDATA *save = savedataGetStatus(0, 0xE);
    if (on == 1) {
        save->rules[0].unk50 = 0x9124;
        save->rules[1].unk50 = 0xA2D4;
        save->rules[2].unk50 = 0xB51C;
        save->rules[3].unk50 = 0x47FD;
        save->rules[4].unk50 = 0x7422;
        save->rules[5].unk50 = 0x5633;
    } else {
        save->rules[5].unk50 = 0;
        save->rules[4].unk50 = 0;
        save->rules[3].unk50 = 0;
        save->rules[2].unk50 = 0;
        save->rules[1].unk50 = 0;
        save->rules[0].unk50 = 0;
    }
}

void menuCBBios_CurrentlyWorkingToolBattleSet(s8 flag)
{
    savedataGetStatus(0, 0xE)->unk360 = flag;
}

u8 menuCBBios_CurrentlyWorkingToolBattle(void)
{
    _TOOL_SAVEDATA *save = savedataGetStatus(0, 0xE);
    if (save == 0) {
        return 0;
    }
    return save->unk360;
}

_MENUCBWORK *menuCBBios_WorkContext(void)
{
    return &_CB;
}

void menuCBBios_InitContext(_MENUCBWORK *ctx)
{
    static const u16 sta[4] = { 1, 2, 3, 4 };
    u32 i;
    pGCB = &_CB;
    if (menuCBBios_ContextIsLocked() == 0) {
        for (i = 0; i < 4; i++) {
            menuCBBios_InitTrainerFromDataID(&ctx->trainers[i], sta[i], 0);
            menuCBTrainerBios_SetControlerID(&ctx->trainers[i], menuCBBios_PortIDtoControlerID(i));
            ctx->trainers[i].unk2 = i;
            menuCBBios_CopyTrainer(&ctx->orgTrainers[i], &ctx->trainers[i]);
        }
        switch (ctx->unk4) {
        case 1:
            menuCB_InitMenu(0xA4);
            ctx->unk14 = 0;
            break;
        default:
            menuCB_InitMenu(0xA9);
            ctx->unk14 = 4;
            break;
        }
    }
    menuCBBios_UnlockContext();
}

void menuCB_RULE_INIT(_TOOL_SAVEDATA *save)
{
    u32 i;
    int k;
    u16 *p;
    if (save->rules[0].unk50 == 0x9124 && save->rules[1].unk50 == 0xA2D4 && save->rules[2].unk50 == 0xB51C
        && save->rules[3].unk50 == 0x47FD && save->rules[4].unk50 == 0x7422 && save->rules[5].unk50 == 0x5633) {
        menuCBBios_RuleConstRuleSet();
        return;
    }
    memset(save, 0, 0x364);
    save->rules[0] = *menuCBRule_ConstantRule(0);
    save->rules[1] = *menuCBRule_ConstantRule(1);
    save->rules[2] = *menuCBRule_ConstantRule(2);
    save->rules[3] = *menuCBRule_ConstantRule(2);
    save->rules[4] = *menuCBRule_ConstantRule(2);
    save->rules[5] = *menuCBRule_ConstantRule(2);
    save->rules[3].unk1C = 0;
    save->rules[4].unk1C = 0;
    save->rules[5].unk1C = 0;
    save->rules[3].unk1A = 4;
    save->rules[4].unk1A = 4;
    save->rules[5].unk1A = 4;
    for (i = 0; i < itemtoolbattle_number; i++) {
        if (menuCBRule_RegulationItemID(i) == 0xBF) {
            save->rules[1].itemFlags[i] = 1;
            save->rules[2].itemFlags[i] = 1;
            save->rules[3].itemFlags[i] = 1;
            save->rules[4].itemFlags[i] = 1;
            save->rules[5].itemFlags[i] = 1;
        }
    }
    p = GSmsgGetGSchar(0x438A);
    for (k = 0; k < 21; k++) {
        if (p != 0) {
            if (*p == 0xFFFF) {
                p += 2;
            }
            save->rules[3].name[k] = *p;
            if (*p != 0) {
                p++;
            }
        } else {
            save->rules[3].name[k] = 0;
        }
    }
    p = GSmsgGetGSchar(0x438B);
    for (k = 0; k < 21; k++) {
        if (p != 0) {
            if (*p == 0xFFFF) {
                p += 2;
            }
            save->rules[4].name[k] = *p;
            if (*p != 0) {
                p++;
            }
        } else {
            save->rules[4].name[k] = 0;
        }
    }
    p = GSmsgGetGSchar(0x438C);
    for (k = 0; k < 21; k++) {
        if (p != 0) {
            if (*p == 0xFFFF) {
                p += 2;
            }
            save->rules[5].name[k] = *p;
            if (*p != 0) {
                p++;
            }
        } else {
            save->rules[5].name[k] = 0;
        }
    }
    menuCBBios_InitContextAtFirst(&_CB, save);
    save->unk360 = 0;
}
}

static void menuCBBios_InitContextAtFirst(_MENUCBWORK *work, _TOOL_SAVEDATA *save)
{
    u32 i;
    menuCBBios_UnlockContext();
    memset(work, 0, sizeof(_MENUCBWORK));
    MenuCBBiosRule *r;
    MenuCBBiosRule *d;
    r = menuCBRule_ConstantRule(0);
    d = &work->rules[0];
    *d = *r;
    r = menuCBRule_ConstantRule(1);
    d = &work->rules[1];
    *d = *r;
    r = menuCBRule_ConstantRule(2);
    d = &work->rules[2];
    *d = *r;
    r = menuCBRule_ConstantRule(2);
    d = &work->rules[3];
    *d = *r;
    r = menuCBRule_ConstantRule(2);
    d = &work->rules[4];
    *d = *r;
    r = menuCBRule_ConstantRule(2);
    d = &work->rules[5];
    *d = *r;
    work->rules[3].unk1C = 0;
    work->rules[4].unk1C = 0;
    work->rules[5].unk1C = 0;
    work->rules[3].unk1A = 4;
    work->rules[4].unk1A = 4;
    work->rules[5].unk1A = 4;
    for (i = 0; i < itemtoolbattle_number; i++) {
        if (menuCBRule_RegulationItemID(i) == 0xBF) {
            work->rules[1].itemFlags[i] = 1;
            work->rules[2].itemFlags[i] = 1;
            work->rules[3].itemFlags[i] = 1;
            work->rules[4].itemFlags[i] = 1;
            work->rules[5].itemFlags[i] = 1;
        }
    }
    memcpy(menuCB_RuleTitleNameGet(3), save->rules[3].name, 0x2A);
    memcpy(menuCB_RuleTitleNameGet(4), save->rules[4].name, 0x2A);
    memcpy(menuCB_RuleTitleNameGet(5), save->rules[5].name, 0x2A);
}

extern "C" {
u8 menuCBBios_ContextIsLocked(void)
{
    return stbCB_Lock;
}

void menuCBBios_UnlockContext(void)
{
    stbCB_Lock = 0;
}

void menuCBBios_LockContext(void)
{
    stbCB_Lock = 1;
}
}
