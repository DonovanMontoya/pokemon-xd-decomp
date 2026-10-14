#include <game/pxdvs/app/deck/deck_layout.hpp>

class CChank {
    u32 fields[3];
public:
    CChank();
    virtual ~CChank();
    void *searchSubChankID(const char *);
};
class CChankBlock : public CChank {
public:
    CChankBlock() {}
    virtual ~CChankBlock();
    u8 loadFromMemory(char *, char *);
};

inline CChank::~CChank() {}
inline CChankBlock::~CChankBlock() {}

extern "C" {
struct DeckPokemonFlagByte { u8 seikaku:5, sex:2, tokusei:1; };
struct DeckFlagByte {
    u8 bit7:1, bit6:1, bit5:1, bit4:1, bit3:1, bit2:1, bit1:1, bit0:1;
};

static void *_deckTrainer;
static void *_deckPokemon;
static void *_deckDarkPokemon;
static void *_deckTrainerAI;
static u32 _deckTrainerSize;
static u32 _deckPokemonSize;
static u32 _deckDarkPokemonSize;
static u32 _deckTrainerAISize;
static void *_deckIDNameStr;
void *getDeckDarkPokemonObj__15DeckDarkPokemonFUl(u32 index);
void *fightEncountDataBiosGetPtr(void);
u16 fightEncountDataBiosGetFightTrainerDataId(void *, s32);
void *GSresGetResource(s32, s32);
void *savedataGetStatus(s32, s32);
s32 darkPokemonListBiosGetPokemonID(u16);
void init__11DarkPokemonFv(void *);
void setDarkPoint__11DarkPokemonFf(void *, float);
void setPokemonID__11DarkPokemonFUs(void *, s32);
void setDarkPokemonID__11DarkPokemonFUs(void *, u16);
u8 getSex__7PokemonCFv(void *);
s32 getSeikaku__7PokemonCFv(void *);
s8 getLevel__7PokemonCFv(void *);
u16 getFriendLevel__7PokemonCFv(void *);
bool isTokuseiFlag__7PokemonCFv(void *);
u16 *getPokemonWaza__7PokemonFUs(void *, u16);
u32 pokemonGetStatus(void *, u32, u16, u32);

#define DECK_AI_GET_BYTE(name, off) \
    u8 name(void *p) { if (p == 0) return 0; return bytes(p)[off]; }
#define DECK_AI_SET_BYTE(name, off) \
    void name(void *p, u8 value) { if (p != 0) bytes(p)[off] = value; }
#define DECK_AI_GET_FLAG(name, off, mask, shift) \
    bool name(void *p) { if (p == 0) return false; return reinterpret_cast<DeckFlagByte *>(bytes(p) + off)->bit##shift; }
#define DECK_AI_SET_FLAG(name, off, mask, shift) \
    void name(void *p, bool value) { if (p != 0) reinterpret_cast<DeckFlagByte *>(bytes(p) + off)->bit##shift = value; }
#define DECK_GET_U8(name, off) u8 name(void *p) { if (p == 0) return 0; return bytes(p)[off]; }
#define DECK_GET_U16(name, off) u16 name(void *p) { if (p == 0) return 0; return *reinterpret_cast<u16 *>(bytes(p) + off); }
#define DECK_GET_FLAG(name, off, mask, shift) u8 name(void *p) { if (p == 0) return 0; return (bytes(p)[off] >> shift) & mask; }
#define DECK_SET_U16(name, off) void name(void *p, u16 v) { if (p) *reinterpret_cast<u16 *>(bytes(p) + off) = v; }

static inline u8 *bytes(void *p) { return static_cast<u8 *>(p); }

static inline void *deckTrainerObject(u32 index) {
    if (_deckTrainerSize <= index) return 0;
    return bytes(_deckTrainer) + index * 0x38;
}

static inline u16 deckInitialDarkPoint(void *p) {
    if (p == 0) return 0;
    return *reinterpret_cast<u16 *>(bytes(p) + 8);
}

static inline u8 trainerIsDarkPokemon(DeckTrainerLayout *p, u8 index) {
    if (p == 0) return 0;
    if (index >= 6) return 0;
    return (p->darkPokemonMask & (1 << index)) != 0;
}

static inline void deckSetEffort(DeckPokemonLayout *p, u8 value, u8 index) {
    if (p == 0) return; if (index >= 6) return; p->statusEffort[index] = value;
}

static inline void deckSetRandomStatus(DeckPokemonLayout *p, u8 value, u8 index) {
    if (p == 0) return; if (index >= 6) return; p->statusRnd[index] = value;
}

static inline void deckSetWaza(void *p, u8 index, u16 value) {
    if (p != 0 && index < 4) *reinterpret_cast<u16 *>(bytes(p) + 0x14 + index * 2) = value;
}

static inline void deckSetFriendship(DeckPokemonLayout *p, u8 value) { if (p != 0) p->friendLevel = value; }

static inline void deckSetAbility(DeckPokemonLayout *p, u8 value) { if (p != 0) reinterpret_cast<DeckPokemonFlagByte *>(&p->flags)->tokusei = value; }

void *getDeckMsgID(s32 unused, s32 encounter) {
    void *fight = fightEncountDataBiosGetPtr();
    u16 trainerID = fightEncountDataBiosGetFightTrainerDataId(fight, encounter);
    DeckTrainerLayout *trainer = static_cast<DeckTrainerLayout *>(deckTrainerObject(trainerID));
    u16 offset;
    if (trainer == 0) offset = 0;
    else offset = trainer->nameStringOffset;
    return bytes(_deckIDNameStr) + offset;
}

void deckCreate(u16 index, s16 species, void *pokemon) {
    DeckPokemonLayout *deck;
    if (_deckPokemonSize <= index) deck = 0;
    else deck = reinterpret_cast<DeckPokemonLayout *>(bytes(_deckPokemon) + index * 0x20);
    u16 randomStatuses[6] = {0x93, 0x94, 0x95, 0x96, 0x97, 0x98};
    u16 effortStatuses[6] = {0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92};
    if (deck != 0) deck->pokemonId = species;
    getSex__7PokemonCFv(pokemon);
    s32 nature = getSeikaku__7PokemonCFv(pokemon);
    if (deck != 0) reinterpret_cast<DeckPokemonFlagByte *>(&deck->flags)->seikaku = nature;
    s8 level = getLevel__7PokemonCFv(pokemon);
    if (deck != 0) deck->level = level;
    u8 move;
    u8 status;
    for (status = 0; status < 6; ++status) {
        u8 statusIndex = status;
        deckSetEffort(deck, pokemonGetStatus(pokemon, 0, effortStatuses[status], 0), statusIndex);
        deckSetRandomStatus(deck, pokemonGetStatus(pokemon, 0, randomStatuses[status], 0), status);
    }
    deckSetFriendship(deck, getFriendLevel__7PokemonCFv(pokemon));
    deckSetAbility(deck, isTokuseiFlag__7PokemonCFv(pokemon));
    for (move = 0; move < 4; ++move) {
        u16 value = *getPokemonWaza__7PokemonFUs(pokemon, move);
        deckSetWaza(deck, move, value);
    }
}

u32 getDeckResourceID(u32 type) {
    switch ((u8)type) {
    case 1: return 0x18503400;
    case 2: return 0x184E3400;
    case 3: return 0x184F3400;
    case 4: return 0x18513400;
    case 5: return 0x184B3400;
    case 6: return 0x184C3400;
    case 7: return 0x195F3400;
    default: return type;
    }
}

void *getDeckTrainerAIObj__13DeckTrainerAIFUl(u32 index) {
    if (_deckTrainerAISize <= index) return 0;
    return bytes(_deckTrainerAI) + index * 0x20;
}

void *getDeckDarkPokemonObj__15DeckDarkPokemonFUl(u32 index) {
    if (_deckDarkPokemonSize <= index) return 0;
    return bytes(_deckDarkPokemon) + index * 0x18;
}

void *getDeckPokemonObj__11DeckPokemonFUl(u32 index) {
    if (_deckPokemonSize <= index) return 0;
    return bytes(_deckPokemon) + index * 0x20;
}

u32 deckGetTrainerSize(void) { return _deckTrainerSize; }

void *getDeckTrainerObj__11DeckTrainerFUl(u32 index) { return deckTrainerObject(index); }

u32 deckGetDarkPokemonSize(void) { return 0x80; }

void *deckGetDeckDarkPokemon(u32 index) {
    if (index < 0x80) return bytes(_deckDarkPokemon) + index * 0x18;
    return 0;
}

void deckInitDarkPokemon(void) {
    u8 *pokemon;
    DeckDarkPokemonLayout *deck;
    s32 id;
    s32 index;
    deck = static_cast<DeckDarkPokemonLayout *>(_deckDarkPokemon);
    pokemon = static_cast<u8 *>(savedataGetStatus(0, 15));
    if (pokemon != 0) {
        index = 0;
        do {
            id = darkPokemonListBiosGetPokemonID(index);
            init__11DarkPokemonFv(pokemon);
            u16 points = deckInitialDarkPoint(deck);
            setDarkPoint__11DarkPokemonFf(pokemon, points);
            setPokemonID__11DarkPokemonFUs(pokemon, id);
            setDarkPokemonID__11DarkPokemonFUs(pokemon, index);
            ++index;
            ++deck;
            pokemon += 0x48;
        } while (index < 128);
    }
}

static const char deckChankID[] = "DECK";
static const char darkPokemonChankID[] = "DDPK";
static const char trainerChankID[] = "DTNR";
static const char pokemonChankID[] = "DPKM";
static const char trainerAIChankID[] = "DTAI";
static const char nameStringChankID[] = "DSTR";

void deckUnRegister(s32 resourceID, s32 resourceIndex) {
    CChankBlock block;
    char *resource = static_cast<char *>(GSresGetResource(resourceID, resourceIndex));
    if (resource == 0) return;
    if (block.loadFromMemory(resource, const_cast<char *>(deckChankID)) == 0) return;
    if (block.searchSubChankID(darkPokemonChankID)) {
        _deckDarkPokemonSize = 0;
        _deckDarkPokemon = 0;
    }
    if (block.searchSubChankID(trainerChankID)) {
        _deckTrainerSize = 0;
        _deckTrainer = 0;
    }
    if (block.searchSubChankID(pokemonChankID)) {
        _deckPokemonSize = 0;
        _deckPokemon = 0;
    }
    if (block.searchSubChankID(trainerAIChankID)) {
        _deckTrainerAISize = 0;
        _deckTrainerAI = 0;
    }
    if (block.searchSubChankID(nameStringChankID)) _deckIDNameStr = 0;
}

void deckRegister(s32 resourceID, s32 resourceIndex) {
    CChankBlock block;
    char *resource = static_cast<char *>(GSresGetResource(resourceID, resourceIndex));
    if (resource == 0) return;
    if (block.loadFromMemory(resource, const_cast<char *>(deckChankID)) == 0) return;
    void *chank = block.searchSubChankID(darkPokemonChankID);
    if (chank) {
        _deckDarkPokemonSize = reinterpret_cast<u32 *>(chank)[2];
        _deckDarkPokemon = bytes(chank) + 0x10;
    }
    chank = block.searchSubChankID(trainerChankID);
    if (chank) {
        _deckTrainerSize = reinterpret_cast<u32 *>(chank)[2];
        _deckTrainer = bytes(chank) + 0x10;
    }
    chank = block.searchSubChankID(pokemonChankID);
    if (chank) {
        _deckPokemonSize = reinterpret_cast<u32 *>(chank)[2];
        _deckPokemon = bytes(chank) + 0x10;
    }
    chank = block.searchSubChankID(trainerAIChankID);
    if (chank) {
        _deckTrainerAISize = reinterpret_cast<u32 *>(chank)[2];
        _deckTrainerAI = bytes(chank) + 0x10;
    }
    chank = block.searchSubChankID(nameStringChankID);
    if (chank) _deckIDNameStr = bytes(chank) + 0x10;
}

void deckInit(void) {
    _deckTrainer = 0;
    _deckPokemon = 0;
    _deckDarkPokemon = 0;
    _deckTrainerAI = 0;
    _deckIDNameStr = 0;
    _deckTrainerSize = 0;
    _deckPokemonSize = 0;
    _deckDarkPokemonSize = 0;
    _deckTrainerAISize = 0;
}

DECK_AI_SET_BYTE(setTotalCorrection__13DeckTrainerAIFUc, 0x1E)

DECK_AI_GET_BYTE(getTotalCorrection__13DeckTrainerAICFv, 0x1E)

void setWazaKindParam__13DeckTrainerAIFUcUc(void *p, u8 index, u8 value) { if (p) bytes(p)[0x1C + index] = value; }

u8 getWazaKindParam__13DeckTrainerAICFUc(void *p, u8 index) { if (p == 0) return 0; return bytes(p)[0x1C + index]; }

void setWazaKindID__13DeckTrainerAIFUcUs(DeckTrainerAILayout *p, u8 index, u16 value) { if (p) p->wazaKindID[index] = value; }

u16 getWazaKindID__13DeckTrainerAICFUc(DeckTrainerAILayout *p, u8 index) { if (p == 0) return 0; return p->wazaKindID[index]; }

void setAttrTypeParam__13DeckTrainerAIFUcUc(void *p, u8 index, u8 value) { if (p) bytes(p)[0x16 + index] = value; }

u8 getAttrTypeParam__13DeckTrainerAICFUc(void *p, u8 index) { if (p == 0) return 0; return bytes(p)[0x16 + index]; }

void setAttrTypeID__13DeckTrainerAIFUcUc(void *p, u8 index, u8 value) { if (p) bytes(p)[0x14 + index] = value; }

u8 getAttrTypeID__13DeckTrainerAICFUc(void *p, u8 index) { if (p == 0) return 0; return bytes(p)[0x14 + index]; }

DECK_AI_SET_BYTE(setLastPPDetermRate__13DeckTrainerAIFUc, 0x13)

DECK_AI_GET_BYTE(getLastPPDetermRate__13DeckTrainerAICFv, 0x13)

DECK_AI_SET_BYTE(setLowHPDetermRate__13DeckTrainerAIFUc, 0x12)

DECK_AI_GET_BYTE(getLowHPDetermRate__13DeckTrainerAICFv, 0x12)

DECK_AI_GET_BYTE(getAnnihilateDetermRate__13DeckTrainerAICFv, 0x11)

DECK_AI_SET_BYTE(setHitRate__13DeckTrainerAIFUc, 0x10)

DECK_AI_GET_BYTE(getHitRate__13DeckTrainerAICFv, 0x10)

DECK_AI_SET_BYTE(setItemUseRate__13DeckTrainerAIFUc, 0x0F)

DECK_AI_GET_BYTE(getItemUseRate__13DeckTrainerAICFv, 0x0F)

DECK_AI_SET_BYTE(setPokeChgRate__13DeckTrainerAIFUc, 0x0E)

DECK_AI_GET_BYTE(getPokeChgRate__13DeckTrainerAICFv, 0x0E)

DECK_AI_SET_BYTE(setStatusDetermValTotalMin__13DeckTrainerAIFUc, 0x0D)

DECK_AI_GET_BYTE(getStatusDetermValTotalMin__13DeckTrainerAICFv, 0x0D)

DECK_AI_SET_BYTE(setStatusDetermValTotalMax__13DeckTrainerAIFUc, 0x0C)

DECK_AI_GET_BYTE(getStatusDetermValTotalMax__13DeckTrainerAICFv, 0x0C)

u8 getStatusDetermValMin__13DeckTrainerAICFUc(void *p, u8 index) { if (p == 0) { return 0; } else { return static_cast<u8 *>(p)[4 + index] & 0xF; } }

u8 getStatusDetermValMax__13DeckTrainerAICFUc(void *p, u8 index) { if (p == 0) { return 0; } else { return (static_cast<u8 *>(p)[4 + index] >> 4) & 0xF; } }

DECK_AI_SET_FLAG(setRespectPokemonCondJuge__13DeckTrainerAIFb, 1, 0x02, 1)

DECK_AI_GET_FLAG(getRespectPokemonCondJuge__13DeckTrainerAICFv, 1, 0x02, 1)

DECK_AI_SET_FLAG(setRespectWazaRiskJudge__13DeckTrainerAIFb, 1, 0x04, 2)

DECK_AI_GET_FLAG(getRespectWazaRiskJudge__13DeckTrainerAICFv, 1, 0x04, 2)

DECK_AI_SET_FLAG(setRespectWazaHit__13DeckTrainerAIFb, 1, 0x08, 3)

DECK_AI_GET_FLAG(getRespectWazaHit__13DeckTrainerAICFv, 1, 0x08, 3)

DECK_AI_SET_FLAG(setRespectRole__13DeckTrainerAIFb, 1, 0x10, 4)

DECK_AI_GET_FLAG(getRespectRole__13DeckTrainerAICFv, 1, 0x10, 4)

DECK_AI_SET_FLAG(setRespectWazaAssmntVal__13DeckTrainerAIFb, 1, 0x20, 5)

DECK_AI_GET_FLAG(getRespectWazaAssmntVal__13DeckTrainerAICFv, 1, 0x20, 5)

DECK_AI_SET_FLAG(setSelectRandomWaza__13DeckTrainerAIFb, 1, 0x40, 6)

DECK_AI_GET_FLAG(getSelectRandomWaza__13DeckTrainerAICFv, 1, 0x40, 6)

DECK_AI_SET_FLAG(setSelectRandomDefence__13DeckTrainerAIFb, 1, 0x80, 7)

DECK_AI_GET_FLAG(getSelectRandomDefence__13DeckTrainerAICFv, 1, 0x80, 7)

DECK_AI_SET_FLAG(setCalcWazaDamage__13DeckTrainerAIFb, 0, 0x01, 0)

DECK_AI_GET_FLAG(getCalcWazaDamage__13DeckTrainerAICFv, 0, 0x01, 0)

DECK_AI_SET_FLAG(setAbilityDetermination__13DeckTrainerAIFb, 0, 0x02, 1)

DECK_AI_GET_FLAG(getAbilityDetermination__13DeckTrainerAICFv, 0, 0x02, 1)

DECK_AI_SET_FLAG(setAttrDetermination__13DeckTrainerAIFb, 0, 0x04, 2)

DECK_AI_GET_FLAG(getAttrDetermination__13DeckTrainerAICFv, 0, 0x04, 2)

DECK_AI_SET_FLAG(setRespectKeyPlayer__13DeckTrainerAIFb, 0, 0x08, 3)

DECK_AI_GET_FLAG(getRespectKeyPlayer__13DeckTrainerAICFv, 0, 0x08, 3)

DECK_AI_SET_FLAG(setSelectAceBoss__13DeckTrainerAIFb, 0, 0x10, 4)

DECK_AI_GET_FLAG(getSelectAceBoss__13DeckTrainerAICFv, 0, 0x10, 4)

DECK_AI_SET_FLAG(setOrder__13DeckTrainerAIFb, 0, 0x20, 5)

DECK_AI_GET_FLAG(getOrder__13DeckTrainerAICFv, 0, 0x20, 5)

DECK_AI_SET_FLAG(setNotSameWeekPoint__13DeckTrainerAIFb, 0, 0x40, 6)

DECK_AI_GET_FLAG(getNotSameWeekPoint__13DeckTrainerAICFv, 0, 0x40, 6)

DECK_AI_SET_FLAG(setSelectRandomPokemon__13DeckTrainerAIFb, 0, 0x80, 7)

DECK_AI_GET_FLAG(getSelectRandomPokemon__13DeckTrainerAICFv, 0, 0x80, 7)

DECK_GET_U8(getUnderTakerFlag__15DeckDarkPokemonCFv, 0x15)

DECK_GET_U8(getRevers__15DeckDarkPokemonCFv, 0x14)

bool isScenarioPokemon__15DeckDarkPokemonCFv(void *p) { if (p == 0) return false; return reinterpret_cast<DeckFlagByte *>(bytes(p) + 3)->bit7 == 1; }

u16 getDarkWaza__15DeckDarkPokemonCFSc(DeckDarkPokemonLayout *p, s8 index) {
    if (p == 0) return 0;
    if (index < 0 || index >= 4) return 0;
    return p->waza[index];
}

DECK_GET_U16(getBonusExp__15DeckDarkPokemonCFv, 0x0A)

u16 getInitDarkPoint__15DeckDarkPokemonCFv(void *p) { return deckInitialDarkPoint(p); }

u16 getDeckPokemonID__15DeckDarkPokemonCFv(void *p) { if (p == 0) return 0; return static_cast<DeckDarkPokemonLayout *>(p)->pokemonId; }

DECK_GET_U8(getPlayerLevel__15DeckDarkPokemonCFv, 0x02)

DECK_GET_U8(getSnatchRatio__15DeckDarkPokemonCFv, 0x01)

DECK_GET_U8(getWorth__15DeckDarkPokemonCFv, 0x00)

DECK_GET_FLAG(getRandomSetting__11DeckPokemonCFv, 0x1F, 1, 7)

DECK_GET_FLAG(getTokuseiFlag__11DeckPokemonCFv, 0x1E, 1, 0)

DECK_GET_FLAG(getSex__11DeckPokemonCFv, 0x1E, 3, 1)

DECK_GET_FLAG(getSeikakuID__11DeckPokemonCFv, 0x1E, 0x1F, 3)

DECK_GET_U8(getComboPartnerAll__11DeckPokemonCFv, 0x1D)

u16 getWazaID__11DeckPokemonCFUc(DeckPokemonLayout *p, u8 index) {
    if (p == 0) return 0;
    if (index >= 4) return 0;
    return p->waza[index];
}

u8 getStatusEffort__11DeckPokemonCFUc(void *p, u8 index) {
    if (p == 0) return 0;
    if (index >= 6) return 0;
    return bytes(p)[0x0E + index];
}

u8 getStatusRnd__11DeckPokemonCFUc(void *p, u8 index) {
    if (p == 0) return 0;
    if (index >= 6) return 0;
    return bytes(p)[0x08 + index];
}

DECK_GET_U8(getKeyPlayer__11DeckPokemonCFv, 0x07)

DECK_GET_U8(getRole__11DeckPokemonCFv, 0x06)

DECK_GET_U16(getHoldItem__11DeckPokemonCFv, 0x04)

DECK_GET_U8(getFriendLevel__11DeckPokemonCFv, 0x03)

DECK_GET_U8(getLevel__11DeckPokemonCFv, 0x02)

DECK_GET_U16(getPokemonID__11DeckPokemonCFv, 0x00)

u8 getComboActive__11DeckTrainerCFUc(void *p, u8 i) { if (p == 0) return 0; if (i >= 4) return 0; return bytes(p)[0x34 + i]; return 0; }

u16 getComboID__11DeckTrainerCFUc(DeckTrainerLayout *p, u8 i) { if (p == 0) return 0; if (i >= 4) return 0; return p->comboID[i]; }

DECK_GET_U16(getFixedActionID__11DeckTrainerCFv, 0x2A)

DECK_SET_U16(setAIID__11DeckTrainerFUs, 0x28)

DECK_GET_U16(getAIID__11DeckTrainerCFv, 0x28)

void setPokemonDataID__11DeckTrainerFUcUs(DeckTrainerLayout *p, u8 i, u16 v) { if (p == 0) return; if (i >= 6) return; p->pokemonDataID[i] = v; }

u16 getDarkPokemonDataID__11DeckTrainerCFUc(DeckTrainerLayout *p, u8 index) {
    if (p == 0) return 0;
    if (index >= 6) return 0;
    if (trainerIsDarkPokemon(p, index)) return p->pokemonDataID[index];
    return 0;
}

u16 getPokemonDataID__11DeckTrainerCFUc(DeckTrainerLayout *p, u8 index) {
    if (p == 0) return 0;
    if (index >= 6) return 0;
    u16 id = p->pokemonDataID[index];
    if (trainerIsDarkPokemon(p, index)) {
        void *dark;
        if (_deckDarkPokemonSize <= id) dark = 0;
        else dark = bytes(_deckDarkPokemon) + id * 0x18;
        if (dark == 0) return 0;
        return getDeckPokemonID__15DeckDarkPokemonCFv(dark);
    }
    return id;
}

void setTrainerMsg__11DeckTrainerFUcUs(DeckTrainerLayout *p, u8 i, u16 v) { if (p == 0) return; if (i >= 4) return; p->trainerMsg[i] = v; }

u16 getTrainerMsg__11DeckTrainerCFUc(DeckTrainerLayout *p, u8 i) { if (p == 0) return 0; if (i >= 4) return 0; return p->trainerMsg[i]; }

DECK_SET_U16(setIntroWZX__11DeckTrainerFUs, 0x12)

DECK_GET_U16(getIntroWZX__11DeckTrainerCFv, 0x12)

DECK_SET_U16(setTrainerPKX__11DeckTrainerFUs, 0x10)

DECK_GET_U16(getTrainerPKX__11DeckTrainerCFv, 0x10)

void setTrainerItem__11DeckTrainerFUcUs(DeckTrainerLayout *p, u8 i, u16 v) { if (p == 0) return; if (i >= 4) return; p->trainerItem[i] = v; }

u16 getTrainerItem__11DeckTrainerCFUc(DeckTrainerLayout *p, u8 i) { if (p == 0) return 0; if (i >= 4) return 0; return p->trainerItem[i]; }

DECK_SET_U16(setTrainerName__11DeckTrainerFUs, 0x06)

DECK_GET_U16(getTrainerName__11DeckTrainerCFv, 0x06)

void setTrainerKind__11DeckTrainerFUc(void *p, u8 v) { if (p) bytes(p)[5] = v; }

DECK_GET_U8(getTrainerKind__11DeckTrainerCFv, 0x05)

}
