#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonStatusDispatch.hpp>

//TODO this is simply a first pass through this class many things might need changed and or cleaned up even if the function already matches
const f32 zero = 0.0f;
const f32 oneHundred = 100.0f;
const f32 nintyNinePointNine = 99.9f;
const f32 eighty = 80.0f;
const f32 sixty = 60.0f;
const f32 fourty = 40.0f;
const f32 twenty = 20.0f;
const f64 unkDouble = 4503599627370496.0;
const f32 negOne = -1.0f;
const f32 negThree = -3.0f;
const f64 unkDouble2 = 4503601774854144.0;

void pokemonSetTokuseiFlag(Pokemon* param_1, u32 param_2)
{
  u32 uVar1;
  u8 cVar2;

  if (param_1 != 0) {
    uVar1 = pokemon_GetPokemonDataId(param_1);
    cVar2 = pokemonDB_GetTokuseiDataId(uVar1,1);
    if (cVar2 == '\0') {
      param_2 = 0;
    }
    pokemon_SetTokuseiFlag(param_1,param_2);
  }
  return;
}

void pokemonInitAry(u32 param_1, u16 param_2)
{
  if (param_1 != 0) {
    for (u16 uVar1 = 0; uVar1 < param_2; uVar1++) {
      pokemonInit(param_1 + uVar1 * 0xc4);
    }
  }
}

//TODO later needs a decent number of functions defined
//void pokemonInit(u32 param_1){}

//sdata2 mismatch 99.76% match as a result
void pokemonInitDarkPokemon(Pokemon* poke)
{
	pokemon_SetDarkpokemonDataId(poke,0);
	pokemonSetDp(poke, negOne);
	pokemon_SetPoolExp(poke,0);
	pokemon_SetPoolFriend(poke,0);
}

void pokemonInitJoutai(Pokemon* param_1)
{
	param_1->initCondition();
}

void pokemonWazaInitAry(Pokemon* poke, u16 wazaCount)
{
  if (poke) {
    for (u32 wazaNum = 0; (u16)wazaNum < wazaCount; wazaNum = wazaNum + 1) {
      pokemonWazaInit(poke, wazaNum);
    }
  }
}

void pokemonWazaInit(Pokemon* poke, u32 wazaNum)
{
  if (poke) {
    pokemon_SetPokemonWazaDataId(poke,wazaNum,0);
    pokemon_SetPokemonWazaPp(poke,wazaNum,0);
    pokemon_SetPokemonWazaPpCount(poke,wazaNum,0);
  }
}

u32 pokemonCheckRare(Pokemon* param_1)
{
  u32 uVar1;
  u32 uVar2;

  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = pokemon_GetCatchTrainerRnd(param_1);
    uVar2 = pokemon_GetRnd(param_1);
    uVar1 = _pokemonCheckRare(uVar1,uVar2);
  }
  return uVar1;
}

void pokemonGrowBasisStatus(Pokemon* poke, u32 exp)
{
  if (poke) {
    pokemon_SetExp(poke, exp);
    pokemonResetBasisStatus(poke);
  }
}

void pokemonResetBasisStatus(Pokemon* param_1)
{
  u8 uVar1;

  if (param_1 != 0) {
    uVar1 = pokemon_GetNowExpToLevel(param_1);
    _pokemonSetLevelBasisStatus(param_1, uVar1);
  }
}

//TODO much later needs a ton of functions defined
//void pokemonSetStatus(Pokemon*, u32, u16, u32, u32){}

//TODO much later needs a ton of functions defined
//u16 pokemonGetStatus(Pokemon*, u32, u16, u32){}

u32 pokemonAdjustValueBySeikaku(u32 param1, u16 param2, u32 baseValue)
{
    PokemonSeikakuDataBios* seikakuPtr;
    PokemonSeikakuRateBios* ratePtr;
    u32 rateId;
    s32 result;
    u32 stat;
    u32 kake;
    u32 waru;

    seikakuPtr = pokemonSeikakuDataBiosGetPtr(param1);

    if (seikakuPtr == NULL)
        return baseValue;

    stat = param2;

    switch (stat)
    {
		case STATUS_POKEMON_PHY_ATK:
			rateId = pokemonSeikakuDataBiosGetPhyAtkRateDataId(seikakuPtr);
			break;
		case STATUS_POKEMON_PHY_DEF:
			rateId = pokemonSeikakuDataBiosGetPhyDefRateDataId(seikakuPtr);
			break;
		case 0x8A:
			rateId = pokemonSeikakuDataBiosGetSpeAtkRateDataId(seikakuPtr);
			break;
		case 0x8B:
			rateId = pokemonSeikakuDataBiosGetSpeDefRateDataId(seikakuPtr);
			break;
		case 0x8C:
			rateId = pokemonSeikakuDataBiosGetNimblenessRateDataId(seikakuPtr);
			break;
		default:
			return baseValue;
    }

    ratePtr = pokemonSeikakuRateDataBiosGetPtr(rateId);
    if (ratePtr == NULL)
        return 0;

    kake = pokemonSeikakuRateDataBiosGetKake(ratePtr);
    waru = pokemonSeikakuRateDataBiosGetWaru(ratePtr);

    result = baseValue * (u8)kake;

    if ((u8)waru != 0)
        result = result / (u8)waru;

    return result;
}

u8 _pokemonGetSeikaku(Pokemon* a)
{
	return pokemonGetSeikakuAsRnd(pokemon_GetRnd(a));
}

u8 pokemonGetSeikakuAsRnd(u32 a)
{
  return a % 25;
}

u8 _pokemonGetHinsi(Pokemon* a)
{
	return pokemon_GetHp(a) == 0;
}

void _pokemonSetLevelBasisStatus(Pokemon* a , u8 b)
{
	u16 sVar1;
	u32 sVar2;
	u16 sVar3;
	u16 sVar4;
	u16 sVar5;

	sVar2 = pokemon_GetPokemonDataId(a);
	sVar3 = pokemon_GetMaxHp(a);
	pokemon_SetLevel(a,b);
	if ((u16)sVar2 == 0x12f)
	{
		sVar4 = 1;
		pokemon_SetMaxHp(a,1);
	}
	else
	{
		sVar4 = _pokemonGetLevelOneStatus(a,b,0x87,3,0x93,0x8d,(b & 0xff) + 10);
	}
	_pokemonGetLevelOneStatus(a,b,0x88,4,0x94,0x8e,5);
	_pokemonGetLevelOneStatus(a,b,0x89,5,0x95,0x8f,5);
	_pokemonGetLevelOneStatus(a,b,0x8c,8,0x98,0x92,5);
	_pokemonGetLevelOneStatus(a,b,0x8a,6,0x96,0x90,5);
	_pokemonGetLevelOneStatus(a,b,0x8b,7,0x97,0x91,5);
	sVar5 = pokemon_GetHp(a);
	if ((sVar5 != 0) || (sVar3 == 0))
	{
		sVar1 = 1;
		if ((u16)sVar2 != 0x12f)
		{
			sVar1 = sVar5 + (sVar4 - sVar3);
		}
		pokemon_SetHp(a,sVar1);
	}
}

u16 _pokemonGetLevelOneStatus(Pokemon* poke, u8 level, u16 stat, u16 basisStat, u16 randomStat, u16 effortStat, long bonus)
{
    u32 speciesId = pokemon_GetPokemonDataId(poke);
    u32 nature = pokemon_GetSeikaku(poke);
    u16 basis = pokemonGetStatus(nullptr, speciesId, basisStat, 0);
    u16 random = pokemonGetStatus(poke, 0, randomStat, 0);
    u16 effort = pokemonGetStatus(poke, 0, effortStat, 0);
    u16 value = pokemonCreateBasisStatus(basis, random, effort, level, bonus);
    u32 adjusted = pokemonAdjustValueBySeikaku(nature, stat, value);
    pokemonSetStatus(poke, 0, stat, 0, adjusted);
    return adjusted;
}

u16 pokemonCreateBasisStatus(u16 a, u8 b, u16 c, u8 d, s32 e)
{
	return e + (s32)((d & 0xff) * ((b & 0xff) + (a & 0xffff) * 2 + (c >> 2 & 0x3fff))) / 100 & 0xffff;
}

u8 _pokemonGetNowExpToLevel(Pokemon* a)
{
  u8 growDataId;
  u32 exp;

  growDataId = pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(a));
  exp = pokemon_GetExp(a);
  return pokemonGetExpToLevel(growDataId,exp);
}

u8 pokemonGetExpToLevel(u8 a, u32 b)
{
    s32 level = 0;

    PokemonGrowDataBios* ptr = pokemonGrowDataBiosGetPtr(a);
    if (!ptr)
        return level;

    for (level = 1; level < 101; level++) {
        if (pokemonGrowDataBiosGetExp(ptr, level) > b)
            break;
    }

    return (level - 1);
}

static int _pokemonGetLevelToExp(u8 a, u8 b)
{
	PokemonGrowDataBios* ptr = pokemonGrowDataBiosGetPtr(a);
    if (ptr == 0) {
        return 0;
    }
    return pokemonGrowDataBiosGetExp(ptr, b);
}

int pokemonCheckRareRnd(unsigned long a, unsigned long b)
{
	return _pokemonCheckRare(a, b);
}

static int _pokemonCheckRare(unsigned long a, unsigned long b)
{
	int x = 8 > (a >> 0x10 ^ a & 0xFFFF ^ b >> 0x10 ^ b & 0xFFFF);
	int y = x ? -1 : 0;
	return -y;
}

void pokemonSetStatus(Pokemon* object, u32 speciesId, u16 property, u16 index, u32 value) {
    if (property == 0 || property >= 0x124) return;
    if (property < 0x6d) {
        pokemonDataBiosGetPtr(speciesId);
        object = reinterpret_cast<Pokemon*>(pokemonDataBiosGetPtr(speciesId));
        if (object == nullptr) return;
    } else if (object == nullptr) {
        return;
    }
    switch (property) {
    case STATUS_SPECIES_NAME: pokemonDataBiosSetName(reinterpret_cast<PokemonData*>(object), reinterpret_cast<const char*>(value)); break;
    case STATUS_SPECIES_BASIS_MAX_HP: pokemonDataBiosSetBasisMaxHp(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_PHY_ATK: pokemonDataBiosSetBasisPhyAtk(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_PHY_DEF: pokemonDataBiosSetBasisPhyDef(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_SPE_ATK: pokemonDataBiosSetBasisSpeAtk(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_SPE_DEF: pokemonDataBiosSetBasisSpeDef(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_NIMBLENESS: pokemonDataBiosSetBasisNimbleness(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_MAX_HP_EFFORT: pokemonDataBiosSetGiveMaxHpEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_PHY_ATK_EFFORT: pokemonDataBiosSetGivePhyAtkEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_PHY_DEF_EFFORT: pokemonDataBiosSetGivePhyDefEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_SPE_ATK_EFFORT: pokemonDataBiosSetGiveSpeAtkEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_SPE_DEF_EFFORT: pokemonDataBiosSetGiveSpeDefEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_NIMBLENESS_EFFORT: pokemonDataBiosSetGiveNimblenessEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_EXP: pokemonDataBiosSetGiveExp(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GROW_DATA_ID: pokemonDataBiosSetGrowDataId(reinterpret_cast<PokemonData*>(object), static_cast<u8>(value)); break;
    case STATUS_SPECIES_: pokemonDataBiosSetGet(reinterpret_cast<PokemonData*>(object), static_cast<u8>(value)); break;
    case STATUS_SPECIES_SEX_RATIO: pokemonDataBiosSetSexRatio(reinterpret_cast<PokemonData*>(object), static_cast<u8>(value)); break;
    case STATUS_SPECIES_INIT_FRIEND: pokemonDataBiosSetInitFriend(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_ITEM_DATA_ID: pokemonDataBiosSetItemDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_SPECIES_ZOKUSEI_DATA_ID: pokemonDataBiosSetZokuseiDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_TOKUSEI_DATA_ID: pokemonDataBiosSetTokuseiDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_SINKA_KIND: pokemonDataBiosSetSinkaKind(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_SINKA_BUFF: pokemonDataBiosSetSinkaBuff(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_SPECIES_SINKA_POKEMON_DATA_ID: pokemonDataBiosSetSinkaPokemonDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_SPECIES_WAZA_LEVEL: pokemonDataBiosSetGetWazaLevel(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_WAZA_DATA_ID: pokemonDataBiosSetGetWazaDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case 0x20: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 0, static_cast<u8>(value != 0)); break;
    case 0x21: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 1, static_cast<u8>(value != 0)); break;
    case 0x22: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 2, static_cast<u8>(value != 0)); break;
    case 0x23: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 3, static_cast<u8>(value != 0)); break;
    case 0x24: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 4, static_cast<u8>(value != 0)); break;
    case 0x25: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 5, static_cast<u8>(value != 0)); break;
    case 0x26: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 6, static_cast<u8>(value != 0)); break;
    case 0x27: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 7, static_cast<u8>(value != 0)); break;
    case 0x28: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 8, static_cast<u8>(value != 0)); break;
    case 0x29: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 9, static_cast<u8>(value != 0)); break;
    case 0x2a: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 10, static_cast<u8>(value != 0)); break;
    case 0x2b: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 11, static_cast<u8>(value != 0)); break;
    case 0x2c: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 12, static_cast<u8>(value != 0)); break;
    case 0x2d: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 13, static_cast<u8>(value != 0)); break;
    case 0x2e: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 14, static_cast<u8>(value != 0)); break;
    case 0x2f: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 15, static_cast<u8>(value != 0)); break;
    case 0x30: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 16, static_cast<u8>(value != 0)); break;
    case 0x31: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 17, static_cast<u8>(value != 0)); break;
    case 0x32: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 18, static_cast<u8>(value != 0)); break;
    case 0x33: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 19, static_cast<u8>(value != 0)); break;
    case 0x34: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 20, static_cast<u8>(value != 0)); break;
    case 0x35: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 21, static_cast<u8>(value != 0)); break;
    case 0x36: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 22, static_cast<u8>(value != 0)); break;
    case 0x37: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 23, static_cast<u8>(value != 0)); break;
    case 0x38: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 24, static_cast<u8>(value != 0)); break;
    case 0x39: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 26, static_cast<u8>(value != 0)); break;
    case 0x3a: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 27, static_cast<u8>(value != 0)); break;
    case 0x3b: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 28, static_cast<u8>(value != 0)); break;
    case 0x3c: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 29, static_cast<u8>(value != 0)); break;
    case 0x3d: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 30, static_cast<u8>(value != 0)); break;
    case 0x3e: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 31, static_cast<u8>(value != 0)); break;
    case 0x3f: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 32, static_cast<u8>(value != 0)); break;
    case 0x40: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 33, static_cast<u8>(value != 0)); break;
    case 0x41: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 34, static_cast<u8>(value != 0)); break;
    case 0x42: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 35, static_cast<u8>(value != 0)); break;
    case 0x43: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 36, static_cast<u8>(value != 0)); break;
    case 0x44: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 37, static_cast<u8>(value != 0)); break;
    case 0x45: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 38, static_cast<u8>(value != 0)); break;
    case 0x46: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 39, static_cast<u8>(value != 0)); break;
    case 0x47: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 40, static_cast<u8>(value != 0)); break;
    case 0x48: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 41, static_cast<u8>(value != 0)); break;
    case 0x49: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 42, static_cast<u8>(value != 0)); break;
    case 0x4a: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 43, static_cast<u8>(value != 0)); break;
    case 0x4b: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 44, static_cast<u8>(value != 0)); break;
    case 0x4c: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 45, static_cast<u8>(value != 0)); break;
    case 0x4d: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 46, static_cast<u8>(value != 0)); break;
    case 0x4e: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 47, static_cast<u8>(value != 0)); break;
    case 0x4f: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 48, static_cast<u8>(value != 0)); break;
    case 0x50: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 49, static_cast<u8>(value != 0)); break;
    case 0x51: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 50, static_cast<u8>(value != 0)); break;
    case 0x52: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 51, static_cast<u8>(value != 0)); break;
    case 0x53: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 52, static_cast<u8>(value != 0)); break;
    case 0x54: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 53, static_cast<u8>(value != 0)); break;
    case 0x55: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 54, static_cast<u8>(value != 0)); break;
    case 0x56: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 55, static_cast<u8>(value != 0)); break;
    case 0x57: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 56, static_cast<u8>(value != 0)); break;
    case 0x58: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 57, static_cast<u8>(value != 0)); break;
    case 0x59: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 58, static_cast<u8>(value != 0)); break;
    case STATUS_SPECIES_POKEBODY_ID: pokemonDataBiosSetPokebodyId(reinterpret_cast<PokemonData*>(object), index, value); break;
    case STATUS_SPECIES_STATUS_FACE_MENU_SPRITE_ID: pokemonDataBiosSetStatusFaceMenuSpriteId(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_SPECIES_COLOR: pokemonDataBiosSetColor(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_TYPE_NAME: pokemonDataBiosSetTypeName(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_HEIGHT: pokemonDataBiosSetHeight(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_WEIGHT: pokemonDataBiosSetWeight(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_DOC: pokemonDataBiosSetDoc(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_VOICE: pokemonDataBiosSetVoice(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_MITA_FLAG: pokemonDataBiosSetMitaFlag(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_TUKAMAETA_FLAG: pokemonDataBiosSetTukamaetaFlag(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_NUM_ZUKAN: pokemonDataBiosSetNumZukan(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_NUM_POKEMON: pokemonDataBiosSetNumPokemon(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_PKX_DATA_ID: pokemonDataBiosSetPkxDataId(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_KOWAZA: pokemonDataBiosSetKowaza(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_POKEMON_POKEMON_DATA_ID: pokemonBiosSetPokemonDataId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_RND: pokemonBiosSetRnd(object, value); break;
    case STATUS_POKEMON_CATCH_FLOOR_ID: pokemonBiosSetCatchFloorId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_CATCH_LEVEL: pokemonBiosSetCatchLevel(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CATCH_BALL_ID: pokemonBiosSetCatchBallId(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CATCH_TRAINER_SEX: pokemonBiosSetCatchTrainerSex(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CATCH_TRAINER_RND: pokemonBiosSetCatchTrainerRnd(object, value); break;
    case STATUS_POKEMON_CATCH_TRAINER_NAME_PTR: pokemonBiosSetCatchTrainerNamePtr(object, reinterpret_cast<u16*>(value)); break;
    case STATUS_POKEMON_NICKNAME_PTR: pokemonBiosSetNicknamePtr(object, reinterpret_cast<u16*>(value)); break;
    case STATUS_POKEMON_NICKNAME_ORG_PTR: pokemonBiosSetNicknameOrgPtr(object, reinterpret_cast<u16*>(value)); break;
    case STATUS_POKEMON_EXP: pokemonBiosSetExp(object, value); break;
    case STATUS_POKEMON_LEVEL: pokemonBiosSetLevel(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CONDITION_AMARI: pokemonBiosSetConditionAmari(object, value); break;
    case STATUS_POKEMON_POKEMON_WAZA_DATA_ID: pokemonBiosSetPokemonWazaDataId(object, index, static_cast<u16>(value)); break;
    case STATUS_POKEMON_POKEMON_WAZA_PP: pokemonBiosSetPokemonWazaPp(object, index, static_cast<u8>(value)); break;
    case STATUS_POKEMON_POKEMON_WAZA_PP_COUNT: pokemonBiosSetPokemonWazaPpCount(object, index, static_cast<u8>(value)); break;
    case STATUS_POKEMON_ITEM_DATA_ID: pokemonBiosSetItemDataId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_HP: pokemonBiosSetHp(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_MAX_HP: pokemonBiosSetMaxHp(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_ATK: pokemonBiosSetPhyAtk(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_DEF: pokemonBiosSetPhyDef(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_ATK: pokemonBiosSetSpeAtk(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_DEF: pokemonBiosSetSpeDef(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_NIMBLENESS: pokemonBiosSetNimbleness(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_MAX_HP_EFFORT: pokemonBiosSetMaxHpEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_ATK_EFFORT: pokemonBiosSetPhyAtkEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_DEF_EFFORT: pokemonBiosSetPhyDefEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_ATK_EFFORT: pokemonBiosSetSpeAtkEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_DEF_EFFORT: pokemonBiosSetSpeDefEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_NIMBLENESS_EFFORT: pokemonBiosSetNimblenessEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_MAX_HP_RND: pokemonBiosSetMaxHpRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_ATK_RND: pokemonBiosSetPhyAtkRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_DEF_RND: pokemonBiosSetPhyDefRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_ATK_RND: pokemonBiosSetSpeAtkRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_DEF_RND: pokemonBiosSetSpeDefRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_NIMBLENESS_RND: pokemonBiosSetNimblenessRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_FRIEND: pokemonBiosSetFriend(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_STYLE: pokemonBiosSetStyle(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_BEAUTIFUL: pokemonBiosSetBeautiful(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CUTE: pokemonBiosSetCute(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CLEVER: pokemonBiosSetClever(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_STRONG: pokemonBiosSetStrong(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_FUR: pokemonBiosSetFur(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CHAMP_RIBBON: pokemonBiosSetChampRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_WINNING_RIBBON: pokemonBiosSetWinningRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_VICTORY_RIBBON: pokemonBiosSetVictoryRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_BROMIDE_RIBBON: pokemonBiosSetBromideRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_GANBA_RIBBON: pokemonBiosSetGanbaRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_MARINE_RIBBON: pokemonBiosSetMarineRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_LAND_RIBBON: pokemonBiosSetLandRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_SKY_RIBBON: pokemonBiosSetSkyRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_COUNTRY_RIBBON: pokemonBiosSetCountryRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_NATIONAL_RIBBON: pokemonBiosSetNationalRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_EARTH_RIBBON: pokemonBiosSetEarthRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_WORLD_RIBBON: pokemonBiosSetWorldRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_AMARI_RIBBON: pokemonBiosSetAmariRibbon(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_STYLE_MEDAL: pokemonBiosSetStyleMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_BEAUTIFUL_MEDAL: pokemonBiosSetBeautifulMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CUTE_MEDAL: pokemonBiosSetCuteMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CLEVER_MEDAL: pokemonBiosSetCleverMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_STRONG_MEDAL: pokemonBiosSetStrongMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_POKERUS: pokemonBiosSetPokerus(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_TAMAGO_FLAG: pokemonBiosSetTamagoFlag(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_TOKUSEI_FLAG: pokemonBiosSetTokuseiFlag(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_FUSEI_FLAG: pokemonBiosSetFuseiFlag(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_FLAG_AMARI: pokemonBiosSetFlagAmari(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_PCBOX_MARK: pokemonBiosSetPcboxMark(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_MAIL_ID: pokemonBiosSetMailId(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_PARA1_AMARI: pokemonBiosSetPara1Amari(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_AMARI: pokemonBiosSetAmari(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_FIGHT_TRAINER_POKEMON_DATA_ID: pokemonBiosSetFightTrainerPokemonDataId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_DARKPOKEMON_DATA_ID: pokemonBiosSetDarkpokemonDataId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_DP: pokemonBiosSetDp(object, value); break;
    case STATUS_POKEMON_POOL_EXP: pokemonBiosSetPoolExp(object, value); break;
    case STATUS_POKEMON_POOL_FRIEND: pokemonBiosSetPoolFriend(object, static_cast<u16>(value)); break;
    case STATUS_FIGHT_MOTO_POKEMON_PTR: fightPokemonBiosSetMotoPokemonPtr(reinterpret_cast<FightPokemon*>(object), value); break;
    case STATUS_FIGHT_CONDITION_COPY: {
        FightJoutai* target = fightPokemon_GetFightJoutaiPtr(reinterpret_cast<FightPokemon*>(object), 0);
        if (target != nullptr) {
            const FightJoutai* source = reinterpret_cast<const FightJoutai*>(value);
            for (u8 i = 0; i < 1; i++) {
                target[i].dataId = source[i].dataId;
                target[i].userFightTargetId = source[i].userFightTargetId;
                target[i].kaisuu = source[i].kaisuu;
                target[i].nowKaisuu = source[i].nowKaisuu;
                target[i].count = source[i].count;
                target[i].reserved07 = source[i].reserved07;
                target[i].buff = source[i].buff;
                target[i].idBuff = source[i].idBuff;
            }
        }
        break;
    }
    case STATUS_FIGHT_ENTRY_ID: fightPokemonBiosSetEntryId(reinterpret_cast<FightPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_CATCH_ENTRY_FLAG: fightPokemonBiosSetCatchEntryFlag(reinterpret_cast<FightPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_LEVEL_UP_FLAG: fightPokemonBiosSetLevelUpFlag(reinterpret_cast<FightPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_DARK_OUT_FLAG: fightPokemonBiosSetDarkOutFlag(reinterpret_cast<FightPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_HOKAKU_FLAG: fightPokemonBiosSetHokakuFlag(reinterpret_cast<FightPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_MOTO_FIGHT_POKEMON_PTR: fightOutPokemonBiosSetMotoFightPokemonPtr(reinterpret_cast<FightOutPokemon*>(object), value); break;
    case STATUS_FIGHT_OUT_FIGHT_POKEMON_PTR: fightOutPokemonBiosSetFightPokemonPtr(reinterpret_cast<FightOutPokemon*>(object), value); break;
    case STATUS_FIGHT_OUT_USE_WAZA_DATA_ID: fightWaza_SetUseWazaDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_MOTO_WAZA_DATA_ID: fightWaza_SetMotoWazaDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_VALUE: fightWaza_SetDamageValue(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_CRITICAL: fightWaza_SetCritical(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_WRITE_MOVE_CONDITION: {
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object));
        if (fightWazaCheckWriteJoutaiDataId(waza, static_cast<u16>(value)) == 2)
            fightWazaWriteJoutaiDataId(waza, static_cast<u16>(value), 0);
        break;
    }
    case STATUS_FIGHT_OUT_INIT_MOVE_CONDITION: {
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object));
        if (static_cast<u16>(value) != 0) {
            if (fightWazaIsJoutaiDataId(waza, static_cast<u16>(value)) == 1)
                fightWazaInitJoutaiDataId(waza, static_cast<u16>(value));
        } else {
            fightWazaInitJoutai(waza);
        }
        break;
    }
    case STATUS_FIGHT_OUT_DAMAGE: fightWaza_SetDamage(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), value); break;
    case STATUS_FIGHT_OUT_IRYOKU: fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_TARGET_DATA_ID: fightWaza_SetTargetDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_HIT_DAMAGE: fightWaza_SetHitDamage(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), value); break;
    case STATUS_FIGHT_OUT_ABICNT_PHY_ATK: fightOutPokemonBiosSetAbicntPhyAtk(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_PHY_DEF: fightOutPokemonBiosSetAbicntPhyDef(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_SPE_ATK: fightOutPokemonBiosSetAbicntSpeAtk(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_SPE_DEF: fightOutPokemonBiosSetAbicntSpeDef(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_NIMBLENESS: fightOutPokemonBiosSetAbicntNimbleness(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_AVERAGE: fightOutPokemonBiosSetAbicntAverage(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_AVOID: fightOutPokemonBiosSetAbicntAvoid(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_FIGHTOUT_TURN_COUNT: fightOutPokemonBiosSetFightoutTurnCount(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_SEQUENCE_PTR: fightOutPokemonBiosSetSequencePtr(reinterpret_cast<FightOutPokemon*>(object), value); break;
    case STATUS_FIGHT_OUT_SKETCH_WAZA_DATA_ID: fightOutPokemonBiosSetSketchWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_LAST_SELECT_WAZA_DATA_ID: fightOutPokemonBiosSetLastSelectWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_LAST_USE_WAZA_DATA_ID: fightOutPokemonBiosSetLastUseWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_LAST_RECEIVE_WAZA_TARGET_DATA_ID: fightOutPokemonBiosSetLastReceiveWazaTargetDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_HIT_WAZA_DATA_ID: fightOutPokemonBiosSetHitWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_HIT_WAZA_ZOKUSEI_DATA_ID: fightOutPokemonBiosSetHitWazaZokuseiDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_GAMAN_DAMAGE_VALUE: fightOutPokemonBiosSetGamanDamageValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_GAMAN_DAMAGE_TARGET_ID: fightOutPokemonBiosSetGamanDamageTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_OUMU_WAZA_DATA_ID: fightOutPokemonBiosSetOumuWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_NAMAKE_FLAG: fightOutPokemonBiosSetNamakeFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_USED_ITEM_DATA_ID: fightOutPokemonBiosSetUsedItemDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_STOCK_ITEM_DATA_ID: fightOutPokemonBiosSetStockItemDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_SUCCESS_CNT: fightOutPokemonBiosSetSuccessCnt(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_MEET_ENEMY_FIGHT_POKEMON_ENTRY_ID: {
        s8 entry = static_cast<s8>(value);
        fightOutPokemonBiosSetMeetEnemyFightPokemonEntryId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(index), entry);
        break;
    }
    case STATUS_FIGHT_OUT_ZOKUSEI_DATA_ID: fightOutPokemonBiosSetZokuseiDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(index), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_TOKUSEI_DATA_ID: fightOutPokemonBiosSetTokuseiDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_ATK_VALUE: fightOutPokemonBiosSetDamageAtkValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_ATK_TARGET_ID: fightOutPokemonBiosSetDamageAtkTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_SPE_VALUE: fightOutPokemonBiosSetDamageSpeValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_SPE_TARGET_ID: fightOutPokemonBiosSetDamageSpeTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_MAHI_NO_ATTACK_FLAG: fightOutPokemonBiosSetMahiNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_KONRAN_MYSELF_ATTACK_FLAG: fightOutPokemonBiosSetKonranMyselfAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_OUT_WAZA_KOUKANAI_FLAG: fightOutPokemonBiosSetOutWazaKoukanaiFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_TAME_WAZA_FLAG: fightOutPokemonBiosSetTameWazaFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_ITEM_NIGERU_FLAG: fightOutPokemonBiosSetItemNigeruFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_HUUIN_NO_ATTACK_FLAG: fightOutPokemonBiosSetHuuinNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_MERO_MERO_NO_ATTACK_FLAG: fightOutPokemonBiosSetMeroMeroNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_KANASHIBARI_NO_ATTACK_FLAG: fightOutPokemonBiosSetKanashibariNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_CHOUHATSU_NO_ATTACK_FLAG: fightOutPokemonBiosSetChouhatsuNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_ICHAMON_NO_ATTACK_FLAG: fightOutPokemonBiosSetIchamonNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_HIRUMU_NO_ATTACK_FLAG: fightOutPokemonBiosSetHirumuNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_PASS_PPDEC_FLAG: fightOutPokemonBiosSetPassPpdecFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_FIGHT_ACTION_FLAG: fightOutPokemonBiosSetFightActionFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_DO_CLEARBODY_FLAG: fightOutPokemonBiosSetDoClearbodyFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_RECEIVES_WAZA_HIRAISHIN_FLAG: fightOutPokemonBiosSetReceivesWazaHiraishinFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_VANISHOFF_FLAG: fightOutPokemonBiosSetVanishoffFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_DO_IKAKU_FLAG: fightOutPokemonBiosSetDoIkakuFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_DO_TRACE_FLAG: fightOutPokemonBiosSetDoTraceFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_NO_PRESSURE_FLAG: fightOutPokemonBiosSetNoPressureFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_IREKAETA_FLAG: fightOutPokemonBiosSetIrekaetaFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_ITEM_KORAETA_FLAG: fightOutPokemonBiosSetItemKoraetaFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_KAIGARA_DAMAGE_VALUE: fightOutPokemonBiosSetKaigaraDamageValue(reinterpret_cast<FightOutPokemon*>(object), value); break;
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_VALUE: fightOutPokemonBiosSetMyselfDamageAtkValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_TARGET_ID: fightOutPokemonBiosSetMyselfDamageAtkTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_VALUE: fightOutPokemonBiosSetMyselfDamageSpeValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_TARGET_ID: fightOutPokemonBiosSetMyselfDamageSpeTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_KIZETU_FLAG: fightOutPokemonBiosSetKizetuFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_IREKAE_TARGET_ENTRY_ID: fightOutPokemonBiosSetIrekaeTargetEntryId(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    default: break;
    }
}

u32 pokemonGetStatus(Pokemon* object, u32 speciesId, u16 property, u16 index) {
    if (property == 0 || property >= 0x124) return 0;
    if (property < 0x6d) {
        object = reinterpret_cast<Pokemon*>(pokemonDataBiosGetPtr(speciesId));
        if (object == nullptr) return 0;
    } else if (object == nullptr) {
        return 0;
    }
    switch (property) {
    case STATUS_SPECIES_NAME: return reinterpret_cast<u32>(pokemonDataBiosGetName(reinterpret_cast<PokemonData*>(object)));
    case STATUS_SPECIES_BASIS_MAX_HP: return pokemonDataBiosGetBasisMaxHp(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_PHY_ATK: return pokemonDataBiosGetBasisPhyAtk(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_PHY_DEF: return pokemonDataBiosGetBasisPhyDef(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_SPE_ATK: return pokemonDataBiosGetBasisSpeAtk(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_SPE_DEF: return pokemonDataBiosGetBasisSpeDef(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_NIMBLENESS: return pokemonDataBiosGetBasisNimbleness(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_MAX_HP_EFFORT: return pokemonDataBiosGetGiveMaxHpEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_PHY_ATK_EFFORT: return pokemonDataBiosGetGivePhyAtkEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_PHY_DEF_EFFORT: return pokemonDataBiosGetGivePhyDefEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_SPE_ATK_EFFORT: return pokemonDataBiosGetGiveSpeAtkEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_SPE_DEF_EFFORT: return pokemonDataBiosGetGiveSpeDefEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_NIMBLENESS_EFFORT: return pokemonDataBiosGetGiveNimblenessEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_EXP: return pokemonDataBiosGetGiveExp(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GROW_DATA_ID: return pokemonDataBiosGetGrowDataId(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_: return pokemonDataBiosGetGet(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_SEX_RATIO: return pokemonDataBiosGetSexRatio(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_INIT_FRIEND: return pokemonDataBiosGetInitFriend(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_ITEM_DATA_ID: return pokemonDataBiosGetItemDataId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_ZOKUSEI_DATA_ID: return pokemonDataBiosGetZokuseiDataId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_TOKUSEI_DATA_ID: return pokemonDataBiosGetTokuseiDataId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_SINKA_KIND: return pokemonDataBiosGetSinkaKind(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_SINKA_BUFF: return pokemonDataBiosGetSinkaBuff(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_SINKA_POKEMON_DATA_ID: return pokemonDataBiosGetSinkaPokemonDataId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_WAZA_LEVEL: return pokemonDataBiosGetGetWazaLevel(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_WAZA_DATA_ID: return pokemonDataBiosGetGetWazaDataId(reinterpret_cast<PokemonData*>(object), index);
    case 0x20: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 0);
    case 0x21: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 1);
    case 0x22: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 2);
    case 0x23: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 3);
    case 0x24: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 4);
    case 0x25: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 5);
    case 0x26: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 6);
    case 0x27: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 7);
    case 0x28: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 8);
    case 0x29: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 9);
    case 0x2a: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 10);
    case 0x2b: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 11);
    case 0x2c: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 12);
    case 0x2d: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 13);
    case 0x2e: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 14);
    case 0x2f: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 15);
    case 0x30: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 16);
    case 0x31: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 17);
    case 0x32: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 18);
    case 0x33: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 19);
    case 0x34: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 20);
    case 0x35: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 21);
    case 0x36: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 22);
    case 0x37: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 23);
    case 0x38: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 24);
    case 0x39: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 26);
    case 0x3a: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 27);
    case 0x3b: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 28);
    case 0x3c: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 29);
    case 0x3d: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 30);
    case 0x3e: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 31);
    case 0x3f: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 32);
    case 0x40: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 33);
    case 0x41: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 34);
    case 0x42: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 35);
    case 0x43: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 36);
    case 0x44: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 37);
    case 0x45: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 38);
    case 0x46: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 39);
    case 0x47: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 40);
    case 0x48: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 41);
    case 0x49: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 42);
    case 0x4a: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 43);
    case 0x4b: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 44);
    case 0x4c: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 45);
    case 0x4d: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 46);
    case 0x4e: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 47);
    case 0x4f: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 48);
    case 0x50: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 49);
    case 0x51: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 50);
    case 0x52: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 51);
    case 0x53: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 52);
    case 0x54: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 53);
    case 0x55: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 54);
    case 0x56: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 55);
    case 0x57: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 56);
    case 0x58: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 57);
    case 0x59: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 58);
    case STATUS_SPECIES_POKEBODY_ID: return pokemonDataBiosGetPokebodyId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_STATUS_FACE_MENU_SPRITE_ID: return pokemonDataBiosGetStatusFaceMenuSpriteId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_COLOR: return pokemonDataBiosGetColor(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_TYPE_NAME: return pokemonDataBiosGetTypeName(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_HEIGHT: return pokemonDataBiosGetHeight(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_WEIGHT: return pokemonDataBiosGetWeight(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_DOC: return pokemonDataBiosGetDoc(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_VOICE: return pokemonDataBiosGetVoice(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_MITA_FLAG: return pokemonDataBiosGetMitaFlag(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_TUKAMAETA_FLAG: return pokemonDataBiosGetTukamaetaFlag(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_NUM_ZUKAN: return pokemonDataBiosGetNumZukan(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_NUM_POKEMON: return pokemonDataBiosGetNumPokemon(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_PKX_DATA_ID: return pokemonDataBiosGetPkxDataId(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_KOWAZA: return pokemonDataBiosGetKowaza(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_POKEMON_DATA_ID:
    case STATUS_SPECIES_POKEMON_DATA_ID_6A:
    case STATUS_SPECIES_POKEMON_DATA_ID_6B:
    case STATUS_SPECIES_POKEMON_DATA_ID_6C:
    case STATUS_POKEMON_POKEMON_DATA_ID: return pokemonBiosGetPokemonDataId(object);
    case STATUS_POKEMON_RND: return pokemonBiosGetRnd(object);
    case STATUS_POKEMON_ATTEST: return reinterpret_cast<u32>(pokemonBiosGetAttest(object));
    case STATUS_POKEMON_CATCH_FLOOR_ID: return pokemonBiosGetCatchFloorId(object);
    case STATUS_POKEMON_CATCH_LEVEL: return pokemonBiosGetCatchLevel(object);
    case STATUS_POKEMON_CATCH_BALL_ID: return pokemonBiosGetCatchBallId(object);
    case STATUS_POKEMON_CATCH_TRAINER_SEX: return pokemonBiosGetCatchTrainerSex(object);
    case STATUS_POKEMON_CATCH_TRAINER_RND: return pokemonBiosGetCatchTrainerRnd(object);
    case STATUS_POKEMON_CATCH_TRAINER_NAME_PTR: return reinterpret_cast<u32>(pokemonBiosGetCatchTrainerNamePtr(object));
    case STATUS_POKEMON_NICKNAME_PTR: return reinterpret_cast<u32>(pokemonBiosGetNicknamePtr(object));
    case STATUS_POKEMON_NICKNAME_ORG_PTR: return reinterpret_cast<u32>(pokemonBiosGetNicknameOrgPtr(object));
    case STATUS_POKEMON_EXP: return pokemonBiosGetExp(object);
    case STATUS_POKEMON_LEVEL: return pokemonBiosGetLevel(object);
    case STATUS_POKEMON_POKEMON_GET_HINSI: return _pokemonGetHinsi(object);
    case 0x7c: return 0;
    case STATUS_POKEMON_CONDITION_AMARI: return pokemonBiosGetConditionAmari(object);
    case STATUS_POKEMON_POKEMON_WAZA_DATA_ID: return pokemonBiosGetPokemonWazaDataId(object, index);
    case STATUS_POKEMON_POKEMON_WAZA_PP: return pokemonBiosGetPokemonWazaPp(object, index);
    case STATUS_POKEMON_POKEMON_WAZA_PP_COUNT: return pokemonBiosGetPokemonWazaPpCount(object, index);
    case STATUS_POKEMON_ITEM_DATA_ID: return pokemonBiosGetItemDataId(object);
    case STATUS_POKEMON_HP: return pokemonBiosGetHp(object);
    case STATUS_POKEMON_MAX_HP: return pokemonBiosGetMaxHp(object);
    case STATUS_POKEMON_PHY_ATK: return pokemonBiosGetPhyAtk(object);
    case STATUS_POKEMON_PHY_DEF: return pokemonBiosGetPhyDef(object);
    case STATUS_POKEMON_SPE_ATK: return pokemonBiosGetSpeAtk(object);
    case STATUS_POKEMON_SPE_DEF: return pokemonBiosGetSpeDef(object);
    case STATUS_POKEMON_NIMBLENESS: return pokemonBiosGetNimbleness(object);
    case STATUS_POKEMON_MAX_HP_EFFORT: return pokemonBiosGetMaxHpEffort(object);
    case STATUS_POKEMON_PHY_ATK_EFFORT: return pokemonBiosGetPhyAtkEffort(object);
    case STATUS_POKEMON_PHY_DEF_EFFORT: return pokemonBiosGetPhyDefEffort(object);
    case STATUS_POKEMON_SPE_ATK_EFFORT: return pokemonBiosGetSpeAtkEffort(object);
    case STATUS_POKEMON_SPE_DEF_EFFORT: return pokemonBiosGetSpeDefEffort(object);
    case STATUS_POKEMON_NIMBLENESS_EFFORT: return pokemonBiosGetNimblenessEffort(object);
    case STATUS_POKEMON_MAX_HP_RND: return pokemonBiosGetMaxHpRnd(object);
    case STATUS_POKEMON_PHY_ATK_RND: return pokemonBiosGetPhyAtkRnd(object);
    case STATUS_POKEMON_PHY_DEF_RND: return pokemonBiosGetPhyDefRnd(object);
    case STATUS_POKEMON_SPE_ATK_RND: return pokemonBiosGetSpeAtkRnd(object);
    case STATUS_POKEMON_SPE_DEF_RND: return pokemonBiosGetSpeDefRnd(object);
    case STATUS_POKEMON_NIMBLENESS_RND: return pokemonBiosGetNimblenessRnd(object);
    case STATUS_POKEMON_FRIEND: return pokemonBiosGetFriend(object);
    case STATUS_POKEMON_STYLE: return pokemonBiosGetStyle(object);
    case STATUS_POKEMON_BEAUTIFUL: return pokemonBiosGetBeautiful(object);
    case STATUS_POKEMON_CUTE: return pokemonBiosGetCute(object);
    case STATUS_POKEMON_CLEVER: return pokemonBiosGetClever(object);
    case STATUS_POKEMON_STRONG: return pokemonBiosGetStrong(object);
    case STATUS_POKEMON_FUR: return pokemonBiosGetFur(object);
    case STATUS_POKEMON_CHAMP_RIBBON: return pokemonBiosGetChampRibbon(object);
    case STATUS_POKEMON_WINNING_RIBBON: return pokemonBiosGetWinningRibbon(object);
    case STATUS_POKEMON_VICTORY_RIBBON: return pokemonBiosGetVictoryRibbon(object);
    case STATUS_POKEMON_BROMIDE_RIBBON: return pokemonBiosGetBromideRibbon(object);
    case STATUS_POKEMON_GANBA_RIBBON: return pokemonBiosGetGanbaRibbon(object);
    case STATUS_POKEMON_MARINE_RIBBON: return pokemonBiosGetMarineRibbon(object);
    case STATUS_POKEMON_LAND_RIBBON: return pokemonBiosGetLandRibbon(object);
    case STATUS_POKEMON_SKY_RIBBON: return pokemonBiosGetSkyRibbon(object);
    case STATUS_POKEMON_COUNTRY_RIBBON: return pokemonBiosGetCountryRibbon(object);
    case STATUS_POKEMON_NATIONAL_RIBBON: return pokemonBiosGetNationalRibbon(object);
    case STATUS_POKEMON_EARTH_RIBBON: return pokemonBiosGetEarthRibbon(object);
    case STATUS_POKEMON_WORLD_RIBBON: return pokemonBiosGetWorldRibbon(object);
    case STATUS_POKEMON_AMARI_RIBBON: return pokemonBiosGetAmariRibbon(object);
    case STATUS_POKEMON_STYLE_MEDAL: return pokemonBiosGetStyleMedal(object);
    case STATUS_POKEMON_BEAUTIFUL_MEDAL: return pokemonBiosGetBeautifulMedal(object);
    case STATUS_POKEMON_CUTE_MEDAL: return pokemonBiosGetCuteMedal(object);
    case STATUS_POKEMON_CLEVER_MEDAL: return pokemonBiosGetCleverMedal(object);
    case STATUS_POKEMON_STRONG_MEDAL: return pokemonBiosGetStrongMedal(object);
    case STATUS_POKEMON_POKERUS: return pokemonBiosGetPokerus(object);
    case STATUS_POKEMON_TAMAGO_FLAG: return pokemonBiosGetTamagoFlag(object);
    case STATUS_POKEMON_TOKUSEI_FLAG: return pokemonBiosGetTokuseiFlag(object);
    case STATUS_POKEMON_FUSEI_FLAG: return pokemonBiosGetFuseiFlag(object);
    case STATUS_POKEMON_FLAG_AMARI: return pokemonBiosGetFlagAmari(object);
    case STATUS_POKEMON_POKEMON_GET_SEX: return pokemonGetSex(object);
    case STATUS_POKEMON_PCBOX_MARK: return pokemonBiosGetPcboxMark(object);
    case STATUS_POKEMON_MAIL_ID: return pokemonBiosGetMailId(object);
    case STATUS_POKEMON_PARA1_AMARI: return pokemonBiosGetPara1Amari(object);
    case STATUS_POKEMON_AMARI: return pokemonBiosGetAmari(object);
    case STATUS_POKEMON_POKEMON_GET_SEIKAKU: return _pokemonGetSeikaku(object);
    case STATUS_POKEMON_POKEMON_GET_NOW_EXP_TO_LEVEL: return _pokemonGetNowExpToLevel(object);
    case STATUS_POKEMON_POKEMON_CHECK_RARE: return static_cast<u8>(pokemonCheckRare(object));
    case STATUS_POKEMON_FIGHT_TRAINER_POKEMON_DATA_ID: return pokemonBiosGetFightTrainerPokemonDataId(object);
    case STATUS_POKEMON_DARKPOKEMON_DATA_ID: return pokemonBiosGetDarkpokemonDataId(object);
    case STATUS_POKEMON_INIT_DP: return pokemonBiosGetInitDp(object);
    case STATUS_POKEMON_DP: return pokemonBiosGetDp(object);
    case STATUS_POKEMON_POOL_EXP: return pokemonBiosGetPoolExp(object);
    case STATUS_POKEMON_POOL_FRIEND: return pokemonBiosGetPoolFriend(object);
    case STATUS_POKEMON_DARK_FLAG: return pokemonBiosGetDarkFlag(object);
    case 0xc8: return 0;
    case STATUS_FIGHT_MOTO_POKEMON_PTR: return reinterpret_cast<u32>(fightPokemonBiosGetMotoPokemonPtr(reinterpret_cast<FightPokemon*>(object)));
    case STATUS_FIGHT_POKEMON_BUFF_PTR: return reinterpret_cast<u32>(fightPokemonBiosGetPokemonBuffPtr(reinterpret_cast<FightPokemon*>(object)));
    case STATUS_FIGHT_CONDITION_COPY: return reinterpret_cast<u32>(fightPokemonBiosGetFightJoutaiPtr(reinterpret_cast<FightPokemon*>(object), index));
    case STATUS_FIGHT_ENTRY_ID: return fightPokemonBiosGetEntryId(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_CATCH_ENTRY_FLAG: return fightPokemonBiosGetCatchEntryFlag(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_LEVEL_UP_FLAG: return fightPokemonBiosGetLevelUpFlag(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_DARK_OUT_FLAG: return fightPokemonBiosGetDarkOutFlag(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_HOKAKU_FLAG: return fightPokemonBiosGetHokakuFlag(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_OUT_MOTO_FIGHT_POKEMON_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetMotoFightPokemonPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_FIGHT_POKEMON_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightPokemonPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_FIGHT_POKEMON_HENSIN_BUFF_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightPokemonHensinBuffPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_FIGHTOUT_JOUTAI_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightoutJoutaiPtr(reinterpret_cast<FightOutPokemon*>(object), index));
    case STATUS_FIGHT_OUT_FIGHT_WAZA_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_USE_WAZA_DATA_ID: return fightOutPokemonGetUseWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MOTO_WAZA_DATA_ID: return fightOutPokemonGetMotoWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DAMAGE_VALUE: return fightWaza_GetDamageValue(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_CRITICAL: return fightWaza_GetCritical(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_WRITE_MOVE_CONDITION: return fightWazaIsJoutaiDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), index);
    case STATUS_FIGHT_OUT_IS_HIT: return fightWazaIsHit(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_DAMAGE: return fightWaza_GetDamage(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_IRYOKU: return fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_TARGET_DATA_ID: return fightWaza_GetTargetDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_HIT_DAMAGE: return fightWaza_GetHitDamage(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_FIGHT_ITEM_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightItemPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_ABICNT_PHY_ATK: return fightOutPokemonBiosGetAbicntPhyAtk(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_PHY_DEF: return fightOutPokemonBiosGetAbicntPhyDef(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_SPE_ATK: return fightOutPokemonBiosGetAbicntSpeAtk(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_SPE_DEF: return fightOutPokemonBiosGetAbicntSpeDef(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_NIMBLENESS: return fightOutPokemonBiosGetAbicntNimbleness(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_AVERAGE: return fightOutPokemonBiosGetAbicntAverage(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_AVOID: return fightOutPokemonBiosGetAbicntAvoid(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_FIGHTOUT_TURN_COUNT: return fightOutPokemonBiosGetFightoutTurnCount(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_SEQUENCE_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetSequencePtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_SKETCH_WAZA_DATA_ID: return fightOutPokemonBiosGetSketchWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_LAST_SELECT_WAZA_DATA_ID: return fightOutPokemonBiosGetLastSelectWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_LAST_USE_WAZA_DATA_ID: return fightOutPokemonBiosGetLastUseWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_LAST_RECEIVE_WAZA_TARGET_DATA_ID: return fightOutPokemonBiosGetLastReceiveWazaTargetDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_HIT_WAZA_DATA_ID: return fightOutPokemonBiosGetHitWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_HIT_WAZA_ZOKUSEI_DATA_ID: return fightOutPokemonBiosGetHitWazaZokuseiDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_GAMAN_DAMAGE_VALUE: return fightOutPokemonBiosGetGamanDamageValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_GAMAN_DAMAGE_TARGET_ID: return fightOutPokemonBiosGetGamanDamageTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_OUMU_WAZA_DATA_ID: return fightOutPokemonBiosGetOumuWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KEEP_FIGHT_WAZA_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetKeepFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_NAMAKE_FLAG: return fightOutPokemonBiosGetNamakeFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_USED_ITEM_DATA_ID: return fightOutPokemonBiosGetUsedItemDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_STOCK_ITEM_DATA_ID: return fightOutPokemonBiosGetStockItemDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_SUCCESS_CNT: return fightOutPokemonBiosGetSuccessCnt(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MEET_ENEMY_FIGHT_POKEMON_ENTRY_ID: return fightOutPokemonBiosGetMeetEnemyFightPokemonEntryId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(index));
    case STATUS_FIGHT_OUT_FIGHT_ACTION_BUFF_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightActionBuffPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_ZOKUSEI_DATA_ID: return fightOutPokemonBiosGetZokuseiDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(index));
    case STATUS_FIGHT_OUT_TOKUSEI_DATA_ID: return fightOutPokemonBiosGetTokuseiDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_WAZA_MENU_CUR_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetWazaMenuCurPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_DAMAGE_ATK_VALUE: return fightOutPokemonBiosGetDamageAtkValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DAMAGE_ATK_TARGET_ID: return fightOutPokemonBiosGetDamageAtkTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DAMAGE_SPE_VALUE: return fightOutPokemonBiosGetDamageSpeValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DAMAGE_SPE_TARGET_ID: return fightOutPokemonBiosGetDamageSpeTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MAHI_NO_ATTACK_FLAG: return fightOutPokemonBiosGetMahiNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KONRAN_MYSELF_ATTACK_FLAG: return fightOutPokemonBiosGetKonranMyselfAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_OUT_WAZA_KOUKANAI_FLAG: return fightOutPokemonBiosGetOutWazaKoukanaiFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_TAME_WAZA_FLAG: return fightOutPokemonBiosGetTameWazaFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ITEM_NIGERU_FLAG: return fightOutPokemonBiosGetItemNigeruFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_HUUIN_NO_ATTACK_FLAG: return fightOutPokemonBiosGetHuuinNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MERO_MERO_NO_ATTACK_FLAG: return fightOutPokemonBiosGetMeroMeroNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KANASHIBARI_NO_ATTACK_FLAG: return fightOutPokemonBiosGetKanashibariNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_CHOUHATSU_NO_ATTACK_FLAG: return fightOutPokemonBiosGetChouhatsuNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ICHAMON_NO_ATTACK_FLAG: return fightOutPokemonBiosGetIchamonNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_HIRUMU_NO_ATTACK_FLAG: return fightOutPokemonBiosGetHirumuNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_PASS_PPDEC_FLAG: return fightOutPokemonBiosGetPassPpdecFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_FIGHT_ACTION_FLAG: return fightOutPokemonBiosGetFightActionFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DO_CLEARBODY_FLAG: return fightOutPokemonBiosGetDoClearbodyFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_RECEIVES_WAZA_HIRAISHIN_FLAG: return fightOutPokemonBiosGetReceivesWazaHiraishinFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_VANISHOFF_FLAG: return fightOutPokemonBiosGetVanishoffFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DO_IKAKU_FLAG: return fightOutPokemonBiosGetDoIkakuFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DO_TRACE_FLAG: return fightOutPokemonBiosGetDoTraceFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_NO_PRESSURE_FLAG: return fightOutPokemonBiosGetNoPressureFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_IREKAETA_FLAG: return fightOutPokemonBiosGetIrekaetaFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ITEM_KORAETA_FLAG: return fightOutPokemonBiosGetItemKoraetaFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KAIGARA_DAMAGE_VALUE: return fightOutPokemonBiosGetKaigaraDamageValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_VALUE: return fightOutPokemonBiosGetMyselfDamageAtkValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_TARGET_ID: return fightOutPokemonBiosGetMyselfDamageAtkTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_VALUE: return fightOutPokemonBiosGetMyselfDamageSpeValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_TARGET_ID: return fightOutPokemonBiosGetMyselfDamageSpeTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KIZETU_FLAG: return fightOutPokemonBiosGetKizetuFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_IREKAE_TARGET_ENTRY_ID: return fightOutPokemonBiosGetIrekaeTargetEntryId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_FIGHT_OUT_POKEMON_ENEMY_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightOutPokemonEnemyPtr(reinterpret_cast<FightOutPokemon*>(object), index));
    case STATUS_FIGHT_OUT_CHECK_FIGHT_OUT: return fightOutPokemonCheckFightOut(reinterpret_cast<FightOutPokemon*>(object));
    default: return 0;
    }
}
