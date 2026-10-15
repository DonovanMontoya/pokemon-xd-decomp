#include <game/gbaPokemonPrivate.hpp>
#ifdef __cplusplus
extern "C" {
#endif
static u32 _swap32__FUl(u32);
static u16 _swap16__FUs(u16);
static void _rotatepp__FPUcUl(u8 *, u32);
static void _revrotatepp__FPUcUl(u8 *, u32);
u16 gbaPokemonConditonFromGC(void *);
void gbaPokemonConditonToGC(void *, u16);

void gbaPokemonFromGC(void *pokemon, void *buffer) {
    GbaOrigins origins;
    GbaIndividualValues individual;
    GbaRibbons ribbons;
    u32 *words;
    void *attest;
    GbaPokemon *gba = (GbaPokemon *)buffer;
    u16 checksum = 0;
    s32 length;
    s32 moveIndex, checksumIndex;
    u32 wordIndex;
    u16 *half;
    memset(buffer, 0, sizeof(*gba));
    if (!pokemonCheckValid(pokemon)) return;
    gba->personality = _swap32__FUl(pokemonBiosGetRnd(pokemon));
    gba->trainer = _swap32__FUl(pokemonBiosGetCatchTrainerRnd(pokemon));
    attest = pokemonBiosGetAttest(pokemon);
    switch (gamedataAttestBiosGetVerId(attest)) {
    case 8: origins.bits.version = 1; break;
    case 9: origins.bits.version = 2; break;
    case 10: origins.bits.version = 3; break;
    case 1: origins.bits.version = 4; break;
    case 2: origins.bits.version = 5; break;
    case 11: origins.bits.version = 15; break;
    default: origins.bits.version = 0; break;
    }
    switch (gamedataAttestBiosGetLangareaId(attest)) {
    case 1: gba->language = 1; break;
    case 2: gba->language = 2; break;
    case 3: gba->language = 5; break;
    case 4: gba->language = 3; break;
    case 5: gba->language = 4; break;
    case 6: gba->language = 7; break;
    case 8: gba->language = 2; break;
    case 9: gba->language = 2; break;
    default: gba->language = 0; break;
    }
    gba->flags.present = 1;
    gba->flags.egg = pokemonBiosGetTamagoFlag(pokemon) != 0;
    gba->flags.spare = pokemonBiosGetFlagAmari(pokemon);
    gba->flags.invalid = pokemonBiosGetFuseiFlag(pokemon) != 0;
    length = GBAMakeFromGSchar(gba->nickname, pokemonBiosGetNicknameOrgPtr(pokemon), gamedataAttestBiosGetLangareaId(attest));
    if (length < 10) {
        gba->nickname[length] = 255;
        memset(gba->nickname + length + 1, 0, 9 - length);
    }
    length = GBAMakeFromGSchar(gba->trainerName, pokemonBiosGetCatchTrainerNamePtr(pokemon), gamedataAttestBiosGetLangareaId(attest));
    if (length < 7) {
        gba->trainerName[length] = 255;
        memset(gba->trainerName + length + 1, 0, 6 - length);
    }
    gba->markings = pokemonBiosGetPcboxMark(pokemon);
    gba->spare = _swap16__FUs(pokemonBiosGetAmari(pokemon));
    gba->species = _swap16__FUs(pokemonBiosGetPokemonDataId(pokemon));
    gba->item = _swap16__FUs(pokemonBiosGetItemDataId(pokemon));
    gba->experience = _swap32__FUl(pokemonBiosGetExp(pokemon));
    gba->friendship = (u8)pokemonBiosGetFriend(pokemon);
    gba->growthSpare = pokemonBiosGetPara1Amari(pokemon);
    gba->ppBonuses = 0;
    for (moveIndex = 0; moveIndex < 4; moveIndex++) {
        gba->moves[moveIndex] = _swap16__FUs(pokemonBiosGetPokemonWazaDataId(pokemon, moveIndex));
        gba->ppBonuses |= pokemonBiosGetPokemonWazaPpCount(pokemon, moveIndex) << (moveIndex * 2);
        gba->pp[moveIndex] = pokemonBiosGetPokemonWazaPp(pokemon, moveIndex);
    }
    gba->effort[0] = (u8)pokemonBiosGetMaxHpEffort(pokemon);
    gba->effort[1] = (u8)pokemonBiosGetPhyAtkEffort(pokemon);
    gba->effort[2] = (u8)pokemonBiosGetPhyDefEffort(pokemon);
    gba->effort[3] = (u8)pokemonBiosGetNimblenessEffort(pokemon);
    gba->effort[4] = (u8)pokemonBiosGetSpeAtkEffort(pokemon);
    gba->effort[5] = (u8)pokemonBiosGetSpeDefEffort(pokemon);
    gba->condition[0] = pokemonBiosGetStyle(pokemon);
    gba->condition[1] = pokemonBiosGetBeautiful(pokemon);
    gba->condition[2] = pokemonBiosGetCute(pokemon);
    gba->condition[3] = pokemonBiosGetClever(pokemon);
    gba->condition[4] = pokemonBiosGetStrong(pokemon);
    gba->condition[5] = pokemonBiosGetFur(pokemon);
    origins.bits.pokerus = pokemonBiosGetPokerus(pokemon);
    origins.bits.floor = pokemonBiosGetCatchFloorId(pokemon);
    origins.bits.level = pokemonBiosGetCatchLevel(pokemon);
    origins.bits.ball = pokemonBiosGetCatchBallId(pokemon);
    origins.bits.trainerSex = pokemonBiosGetCatchTrainerSex(pokemon);
    individual.bits.hp = (u8)pokemonBiosGetMaxHpRnd(pokemon);
    individual.bits.phyAtk = pokemonBiosGetPhyAtkRnd(pokemon);
    individual.bits.phyDef = (u8)pokemonBiosGetPhyDefRnd(pokemon);
    individual.bits.speed = pokemonBiosGetNimblenessRnd(pokemon);
    individual.bits.speAtk = pokemonBiosGetSpeAtkRnd(pokemon);
    individual.bits.speDef = (u8)pokemonBiosGetSpeDefRnd(pokemon);
    individual.bits.egg = pokemonBiosGetTamagoFlag(pokemon) != 0;
    individual.bits.ability = pokemonBiosGetTokuseiFlag(pokemon) != 0;
    ribbons.bits.style = pokemonBiosGetStyleMedal(pokemon);
    ribbons.bits.beautiful = pokemonBiosGetBeautifulMedal(pokemon);
    ribbons.bits.cute = pokemonBiosGetCuteMedal(pokemon);
    ribbons.bits.clever = pokemonBiosGetCleverMedal(pokemon);
    ribbons.bits.strong = pokemonBiosGetStrongMedal(pokemon);
    ribbons.bits.champion = pokemonBiosGetChampRibbon(pokemon) != 0;
    ribbons.bits.winning = pokemonBiosGetWinningRibbon(pokemon) != 0;
    ribbons.bits.victory = pokemonBiosGetVictoryRibbon(pokemon) != 0;
    ribbons.bits.artist = pokemonBiosGetBromideRibbon(pokemon) != 0;
    ribbons.bits.effort = pokemonBiosGetGanbaRibbon(pokemon) != 0;
    ribbons.bits.marine = pokemonBiosGetMarineRibbon(pokemon) != 0;
    ribbons.bits.land = pokemonBiosGetLandRibbon(pokemon) != 0;
    ribbons.bits.sky = pokemonBiosGetSkyRibbon(pokemon) != 0;
    ribbons.bits.country = pokemonBiosGetCountryRibbon(pokemon) != 0;
    ribbons.bits.national = pokemonBiosGetNationalRibbon(pokemon) != 0;
    ribbons.bits.earth = pokemonBiosGetEarthRibbon(pokemon) != 0;
    ribbons.bits.world = pokemonBiosGetWorldRibbon(pokemon) != 0;
    ribbons.bits.spare = pokemonBiosGetAmariRibbon(pokemon);
    ribbons.bits.event = (u8)pokemonBiosGetEventGetFlag(pokemon);
    gba->status = _swap32__FUl(gbaPokemonConditonFromGC(pokemon)) | (pokemonBiosGetConditionAmari(pokemon) & 0xfffff000);
    gba->level = pokemonBiosGetLevel(pokemon);
    gba->mail = pokemonBiosGetMailId(pokemon);
    gba->maxHp = _swap16__FUs(pokemonBiosGetMaxHp(pokemon));
    gba->hp = _swap16__FUs(pokemonBiosGetHp(pokemon));
    gba->phyAtk = _swap16__FUs(pokemonBiosGetPhyAtk(pokemon));
    gba->phyDef = _swap16__FUs(pokemonBiosGetPhyDef(pokemon));
    gba->speed = _swap16__FUs(pokemonBiosGetNimbleness(pokemon));
    gba->speAtk = _swap16__FUs(pokemonBiosGetSpeAtk(pokemon));
    gba->speDef = _swap16__FUs(pokemonBiosGetSpeDef(pokemon));
    gba->origins = _swap32__FUl(origins.word);
    gba->individual = _swap32__FUl(individual.word);
    gba->ribbons = _swap32__FUl(ribbons.word);
    words = (u32 *)&gba->species;
    half = (u16 *)words;
    for (checksumIndex = 0; checksumIndex < 24; checksumIndex++) {
        checksum += _swap16__FUs(*half);
        half++;
    }
    gba->checksum = _swap16__FUs(checksum);
    for (wordIndex = 0; wordIndex < 12; wordIndex++) {
        *words ^= gba->personality ^ gba->trainer;
        words++;
    }
    _rotatepp__FPUcUl((u8 *)&gba->species, _swap32__FUl(gba->personality));
}

void gbaPokemonToGC(void *pokemon, GbaPokemon *gba) {
    u16 nickname[16];
    GbaOrigins origins;
    GbaIndividualValues individual;
    GbaRibbons ribbons;
    u8 version, area, language;
    u16 *half;
    u16 checksum = 0;
    u32 i;
    u32 *words;
    pokemonInit(pokemon);
    if (!gba->flags.present && !gba->flags.invalid) return;
    half = &gba->species;
    words = (u32 *)half;
    for (i = 0; i < 12; i++) words[i] ^= gba->personality ^ gba->trainer;
    _revrotatepp__FPUcUl((u8 *)&gba->species, _swap32__FUl(gba->personality));
    for (i = 0; (s32)i < 24; i++) {
        checksum += _swap16__FUs(*half);
        half++;
    }
    origins.word = _swap32__FUl(gba->origins);
    individual.word = _swap32__FUl(gba->individual);
    ribbons.word = _swap32__FUl(gba->ribbons);
    pokemonBiosSetRnd(pokemon, _swap32__FUl(gba->personality));
    pokemonBiosSetCatchTrainerRnd(pokemon, _swap32__FUl(gba->trainer));
    switch (origins.bits.version) {
    case 1: version = 8; break;
    case 2: version = 9; break;
    case 3: version = 10; break;
    case 4: version = 1; break;
    case 5: version = 2; break;
    case 15: version = 11; break;
    default: version = 0; break;
    }
    switch (gba->language) {
    case 1: area = 1; language = 1; break;
    case 2: area = 2; language = 2; break;
    case 3: area = 3; language = 4; break;
    case 4: area = 3; language = 5; break;
    case 5: area = 3; language = 3; break;
    case 7: area = 3; language = 6; break;
    default: area = 0; language = 0; break;
    }
    gamedataAttestCreate(pokemonBiosGetAttest(pokemon), version, 3, area, language);
    GScharMakeFromGBA(nickname, gba->nickname, 10, language);
    pokemonBiosSetNicknamePtr(pokemon, nickname);
    if (language == 1) ((GbaGcPokemonName *)pokemon)->nickname[5] = 0;
    pokemonBiosSetFlagAmari(pokemon, gba->flags.spare);
    pokemonBiosSetFuseiFlag(pokemon, gba->flags.invalid != 0);
    GScharMakeFromGBA(pokemonBiosGetCatchTrainerNamePtr(pokemon), gba->trainerName, 7, language);
    pokemonBiosSetPcboxMark(pokemon, gba->markings);
    pokemonBiosSetAmari(pokemon, _swap16__FUs(gba->spare));
    pokemonBiosSetPokemonDataId(pokemon, _swap16__FUs(gba->species));
    pokemonBiosSetItemDataId(pokemon, _swap16__FUs(gba->item));
    pokemonBiosSetExp(pokemon, _swap32__FUl(gba->experience));
    pokemonBiosSetFriend(pokemon, gba->friendship);
    pokemonBiosSetPara1Amari(pokemon, gba->growthSpare);
    for (i = 0; (s32)i < 4; i++) {
        pokemonBiosSetPokemonWazaDataId(pokemon, i, _swap16__FUs(gba->moves[i]));
        pokemonBiosSetPokemonWazaPpCount(pokemon, i, (gba->ppBonuses >> (i * 2)) & 3);
        pokemonBiosSetPokemonWazaPp(pokemon, i, gba->pp[i]);
    }
    pokemonBiosSetMaxHpEffort(pokemon, gba->effort[0]);
    pokemonBiosSetPhyAtkEffort(pokemon, gba->effort[1]);
    pokemonBiosSetPhyDefEffort(pokemon, gba->effort[2]);
    pokemonBiosSetNimblenessEffort(pokemon, gba->effort[3]);
    pokemonBiosSetSpeAtkEffort(pokemon, gba->effort[4]);
    pokemonBiosSetSpeDefEffort(pokemon, gba->effort[5]);
    pokemonBiosSetStyle(pokemon, gba->condition[0]);
    pokemonBiosSetBeautiful(pokemon, gba->condition[1]);
    pokemonBiosSetCute(pokemon, gba->condition[2]);
    pokemonBiosSetClever(pokemon, gba->condition[3]);
    pokemonBiosSetStrong(pokemon, gba->condition[4]);
    pokemonBiosSetFur(pokemon, gba->condition[5]);
    pokemonBiosSetPokerus(pokemon, origins.bits.pokerus);
    pokemonBiosSetCatchFloorId(pokemon, origins.bits.floor);
    pokemonBiosSetCatchLevel(pokemon, origins.bits.level);
    pokemonBiosSetCatchBallId(pokemon, origins.bits.ball);
    pokemonBiosSetCatchTrainerSex(pokemon, origins.bits.trainerSex);
    pokemonBiosSetMaxHpRnd(pokemon, individual.bits.hp);
    pokemonBiosSetPhyAtkRnd(pokemon, individual.bits.phyAtk);
    pokemonBiosSetPhyDefRnd(pokemon, individual.bits.phyDef);
    pokemonBiosSetNimblenessRnd(pokemon, individual.bits.speed);
    pokemonBiosSetSpeAtkRnd(pokemon, individual.bits.speAtk);
    pokemonBiosSetSpeDefRnd(pokemon, individual.bits.speDef);
    pokemonBiosSetTamagoFlag(pokemon, individual.bits.egg != 0);
    pokemonBiosSetTokuseiFlag(pokemon, individual.bits.ability != 0);
    pokemonBiosSetStyleMedal(pokemon, ribbons.bits.style);
    pokemonBiosSetBeautifulMedal(pokemon, ribbons.bits.beautiful);
    pokemonBiosSetCuteMedal(pokemon, ribbons.bits.cute);
    pokemonBiosSetCleverMedal(pokemon, ribbons.bits.clever);
    pokemonBiosSetStrongMedal(pokemon, ribbons.bits.strong);
    pokemonBiosSetChampRibbon(pokemon, ribbons.bits.champion != 0);
    pokemonBiosSetWinningRibbon(pokemon, ribbons.bits.winning != 0);
    pokemonBiosSetVictoryRibbon(pokemon, ribbons.bits.victory != 0);
    pokemonBiosSetBromideRibbon(pokemon, ribbons.bits.artist != 0);
    pokemonBiosSetGanbaRibbon(pokemon, ribbons.bits.effort != 0);
    pokemonBiosSetMarineRibbon(pokemon, ribbons.bits.marine != 0);
    pokemonBiosSetLandRibbon(pokemon, ribbons.bits.land != 0);
    pokemonBiosSetSkyRibbon(pokemon, ribbons.bits.sky != 0);
    pokemonBiosSetCountryRibbon(pokemon, ribbons.bits.country != 0);
    pokemonBiosSetNationalRibbon(pokemon, ribbons.bits.national != 0);
    pokemonBiosSetEarthRibbon(pokemon, ribbons.bits.earth != 0);
    pokemonBiosSetWorldRibbon(pokemon, ribbons.bits.world != 0);
    pokemonBiosSetAmariRibbon(pokemon, ribbons.bits.spare);
    pokemonBiosSetEventGetFlag(pokemon, ribbons.bits.event != 0);
    gbaPokemonConditonToGC(pokemon, _swap32__FUl(gba->status));
    pokemonBiosSetConditionAmari(pokemon, _swap32__FUl(gba->status) & 0xfffff000);
    pokemonBiosSetLevel(pokemon, gba->level);
    pokemonBiosSetMailId(pokemon, gba->mail);
    pokemonBiosSetMaxHp(pokemon, _swap16__FUs(gba->maxHp));
    pokemonBiosSetHp(pokemon, _swap16__FUs(gba->hp));
    pokemonBiosSetPhyAtk(pokemon, _swap16__FUs(gba->phyAtk));
    pokemonBiosSetPhyDef(pokemon, _swap16__FUs(gba->phyDef));
    pokemonBiosSetNimbleness(pokemon, _swap16__FUs(gba->speed));
    pokemonBiosSetSpeAtk(pokemon, _swap16__FUs(gba->speAtk));
    pokemonBiosSetSpeDef(pokemon, _swap16__FUs(gba->speDef));
}

u16 gbaPokemonConditonFromGC(void *arg0) {
    u16 var_r31;

    var_r31 = 0;
    if (pokemonIsJoutaiDataId(arg0, 4) != 0) {
        var_r31 = (pokemonGetCountAsJoutaiDataId(arg0, 4) << 8) | 0x80;
    } else if (pokemonIsJoutaiDataId(arg0, 5) != 0) {
        var_r31 |= 0x40;
    } else if (pokemonIsJoutaiDataId(arg0, 7) != 0) {
        var_r31 |= 0x20;
    } else if (pokemonIsJoutaiDataId(arg0, 6) != 0) {
        var_r31 |= 0x10;
    } else if (pokemonIsJoutaiDataId(arg0, 3) != 0) {
        var_r31 |= 8;
    } else if (pokemonIsJoutaiDataId(arg0, 8) != 0) {
        s32 turns = pokemonGetKaisuuJoutaiDataId(arg0, 8);
        var_r31 |= turns;
    }
    return var_r31;
}

void gbaPokemonConditonToGC(void *arg0, u16 arg1) {
    s32 temp_r31;

    if ((s32) (arg1 & 0x80) != 0) {
        pokemonWriteJoutaiDataId(arg0, 4, 0);
        pokemonSetCountAsJoutaiDataId(arg0, 4, (s16) ((s32) (arg1 & 0xF00) >> 8));
        return;
    }
    if ((s32) (arg1 & 0x40) != 0) {
        pokemonWriteJoutaiDataId(arg0, 5, 0);
        return;
    }
    if ((s32) (arg1 & 0x20) != 0) {
        pokemonWriteJoutaiDataId(arg0, 7, 0);
        return;
    }
    if ((s32) (arg1 & 0x10) != 0) {
        pokemonWriteJoutaiDataId(arg0, 6, 0);
        return;
    }
    if ((s32) (arg1 & 8) != 0) {
        pokemonWriteJoutaiDataId(arg0, 3, 0);
        return;
    }
    temp_r31 = arg1 & 7;
    if (temp_r31 != 0) {
        pokemonWriteJoutaiDataId(arg0, 8, 0);
        pokemonSetKaisuuJoutaiDataId(arg0, 8, (s8)temp_r31);
    }
}

void _rotatepp__FPUcUl(u8 *arg0, u32 arg1) {
    u8 saved[12];
    u32 bytes, offset;
    arg1 %= 24;
    if (arg1 / 6 != 0) {
        bytes = arg1 / 6 * 12;
        memcpy(saved, arg0 + bytes, 12);
        memmove(arg0 + 12, arg0, bytes);
        memcpy(arg0, saved, 12);
    }
    arg1 %= 6;
    if (arg1 / 2 != 0) {
        bytes = arg1 / 2 * 12;
        offset = bytes + 12;
        memcpy(saved, arg0 + offset, 12);
        memmove(arg0 + 24, arg0 + 12, bytes);
        memcpy(arg0 + 12, saved, 12);
    }
    if (arg1 % 2 != 0) {
        memcpy(saved, arg0 + 36, 12);
        memcpy(arg0 + 36, arg0 + 24, 12);
        memcpy(arg0 + 24, saved, 12);
    }
}

void _revrotatepp__FPUcUl(u8 *arg0, u32 arg1) {
    u8 saved[12];
    u32 count, offset;
    if (arg1 % 2 != 0) {
        memcpy(saved, arg0 + 24, 12);
        memcpy(arg0 + 24, arg0 + 36, 12);
        memcpy(arg0 + 36, saved, 12);
    }
    count = (arg1 / 2) % 3;
    if (count != 0) {
        memcpy(saved, arg0 + 12, 12);
        count *= 12;
        memmove(arg0 + 12, arg0 + 24, count);
        offset = count + 12;
        memcpy(arg0 + offset, saved, 12);
    }
    count = (arg1 / 6) % 4;
    if (count != 0) {
        memcpy(saved, arg0, 12);
        count *= 12;
        memmove(arg0, arg0 + 12, count);
        memcpy(arg0 + count, saved, 12);
    }
}

u32 _swap32__FUl(u32 arg0) {
    return (arg0 >> 0x18U) | (((u32) (arg0 & 0xFF0000) >> 8U) | ((arg0 << 0x18) | ((arg0 & 0xFF00) << 8)));
}

u16 _swap16__FUs(u16 arg0) {
    return (u16) ((arg0 << 8) | ((s32) arg0 >> 8));
}

#ifdef __cplusplus
}
#endif
