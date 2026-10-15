// Default flags (no extra cflags needed).
#include <game/pxdvs/app/ant/antPrivate.hpp>
#include <libc/string.h>

extern "C" {
void GSfsysFree(s32);
s32 GSfsysGetStatus(s32);
void GSfsysReadID(s32, u32);
void GSresFreeGroup(s32);
void GSresFreeResource(s32, u32);
void *GSresGetResource(s32, u32);
void GSthreadSwitch();
f32 timeGetLastFrameSec();
}

PokeDanceWork _pokeDance;

f32 CAnt::colorAnimationTimeDark;
f32 CAnt::colorAnimationTimeReliveReady;
extern "C" {
u8 pokemonCheckRare(Pokemon *);
s32 pokemonGetStatus(Pokemon *, s32, s32, s32);
s32 pokemonGetAnnonKatati(s32);
u32 pokemonDB_GetPokebodyId(u16, u8);
}

struct AnnonBody {
    u32 normal;
    u32 rare;
};

static inline s32 pokeDanceIndex(u32 id) {
    s32 idx;
    u32 i;
    for (i = 0; i < 0xF0; i++) {
        u32 cur = _pokeDance.entries[i].id;
        if (cur == 0) {
            break;
        }
        if (cur == id) {
            idx = i;
            goto found;
        }
    }
    idx = -1;
found:
    if (idx == -1) {
        for (i = 0; i < 0xF0; i++) {
            if (_pokeDance.entries[i].id == 0) {
                break;
            }
        }
        idx = i;
        PokeDanceEntry *e = &_pokeDance.entries[idx];
        memset(e, 0, sizeof(PokeDanceEntry));
        e->id = id;
    }
    return idx;
}

static inline void *pokeDanceUse(u32 id) {
    if (id == 0) {
        return 0;
    }
    s32 idx = pokeDanceIndex(id);
    PokeDanceEntry *e = &_pokeDance.entries[idx];
    e->useCount = 1;
    return e->resource;
}

static inline void pokeDanceRegister(u32 id) {
    if (id == 0) {
        return;
    }
    s32 idx = pokeDanceIndex(id);
    PokeDanceEntry *e = &_pokeDance.entries[idx];
    e->useCount = 1;
}

#define ANT_ANNON_TABLE \
    {0x1E4C3200, 0x1E4D3200},\
    {0x1E4E3200, 0x1E4F3200},\
    {0x1E503200, 0x1E513200},\
    {0x1E523200, 0x1E533200},\
    {0x1E543200, 0x1E573200},\
    {0x1E583200, 0x1E593200},\
    {0x1E5A3200, 0x1E5B3200},\
    {0x1E5C3200, 0x1E5D3200},\
    {0x1E5E3200, 0x1E5F3200},\
    {0x1E603200, 0x1E613200},\
    {0x1E623200, 0x1E633200},\
    {0x1E643200, 0x1E653200},\
    {0x1E663200, 0x1E673200},\
    {0x1E683200, 0x1E693200},\
    {0x1E6A3200, 0x1E6B3200},\
    {0x1E6C3200, 0x1E6D3200},\
    {0x1E6E3200, 0x1E713200},\
    {0x1E723200, 0x1E733200},\
    {0x1E743200, 0x1E753200},\
    {0x1E763200, 0x1E773200},\
    {0x1E783200, 0x1E793200},\
    {0x1E7A3200, 0x1E7B3200},\
    {0x1E7C3200, 0x1E7D3200},\
    {0x1E7E3200, 0x1E7F3200},\
    {0x1E803200, 0x1E813200},\
    {0x1E823200, 0x1E833200},\
    {0x1E553200, 0x1E563200},\
    {0x1E6F3200, 0x1E703200}

#define ANT_INIT_BY_POKEMON_BODY(self, pk) \
    memset(self, 0, 0x34); \
    (self)->unkC = 1.0f; \
    (self)->unk10 = 0xFF; \
    if ((pk)->checkValid()) { \
        u16 dataId = (pk)->getPokemonDataId(); \
        if (dataId == 0xC9) { \
            AnnonBody tbl[28] = { ANT_ANNON_TABLE }; \
            s32 k = pokemonGetAnnonKatati(pokemonGetStatus(pk, 0, 0x6F, 0)); \
            u32 body; \
            if (pokemonCheckRare(pk)) { \
                body = tbl[(u8)k].rare; \
            } else { \
                body = tbl[(u8)k].normal; \
            } \
            (self)->unk0 = body; \
        } else if (dataId == 0xF9 && (pk)->isDarkPokemon()) { \
            (self)->unk0 = 0x20083200; \
        } else { \
            u32 rare = (pk)->isRare(); \
            (self)->unk0 = pokemonDB_GetPokebodyId(dataId, rare); \
        } \
        u32 body = (self)->unk0; \
        if (body != 0 && (self)->unk4 == 0) { \
            (self)->unk4 = (u32)pokeDanceUse(body); \
        } \
    }


void CAnt::init() {
    memset(this, 0, 0x34);
    unkC = 1.0f;
    unk10 = 0xFF;
}

void CAnt::initByPokemon(Pokemon *pk) {
    ANT_INIT_BY_POKEMON_BODY(this, pk)
}

void CAnt::initByPokemonAndSetColorAnimationInAny(Pokemon *pk) {
    ANT_INIT_BY_POKEMON_BODY(this, pk)
    if (pk->isDarkPokemon()) {
        if (pk->getDarkPoint() > 0.0f) {
            unk30 = 1;
        } else {
            unk30 = 2;
        }
    }
}

void CAnt::initByPokemonAndSetColorAnimationInReliveHallVisitor(Pokemon *pk) {
    ANT_INIT_BY_POKEMON_BODY(this, pk)
    if (pk->isDarkPokemon()) {
        if (pk->getDarkPoint() > 0.0f) {
            unk30 = 1;
        } else {
            unk30 = 2;
        }
    }
}

void CAnt::use() {
    u32 id = unk0;
    if (id != 0) {
        pokeDanceRegister(id);
    }
}

void CAnt::systemUsecountReset() {
    u32 i;
    for (i = 0; i < 0xF0; i++) {
        _pokeDance.entries[i].useCount = 0;
    }
}

static inline void pokeDanceRelease() {
    u32 kept = 0;
    s32 off = 0;
    u32 i;
    PokeDanceEntry *src = _pokeDance.entries;
    _pokeDance.entries[_pokeDance.loading].useCount = 2;
    for (i = 0; i < 0xF0; i++, src++) {
        if (src->id == 0) {
            break;
        }
        if (src->useCount != 0) {
            kept++;
            PokeDanceEntry *dst = (PokeDanceEntry *)((u8 *)_pokeDance.entries + off);
            off += 0xC;
            dst->id = src->id;
            dst->resource = src->resource;
            dst->useCount = src->useCount;
        } else if (src->resource != 0) {
            GSresFreeResource(0x825, src->id);
        }
    }
    PokeDanceEntry *clr = &_pokeDance.entries[kept];
    for (; kept < 0xF0; kept++, clr++) {
        memset(clr, 0, 0xC);
    }
    PokeDanceEntry *q = _pokeDance.entries;
    for (u32 j = 0; j < 0xF0; q++, j++) {
        if (q->id == 0) {
            break;
        }
        if (q->useCount == 2) {
            q->useCount = 1;
            _pokeDance.loading = j;
            return;
        }
    }
}

void CAnt::systemUnUseResourceRelease() {
    pokeDanceRelease();
}

void CAnt::allRequestCancel() {
    PokeDanceEntry *entry = _pokeDance.entries;
    for (s32 i = 0; i < 0xF0; i++, entry++) {
        if (i != _pokeDance.loading && entry->id != 0 && entry->resource == 0) {
            entry->useCount = 0;
        }
    }
    pokeDanceRelease();
}

void CAnt::systemUpdate(bool request) {
    if (_pokeDance.loading != -1) {
        PokeDanceEntry *e = &_pokeDance.entries[_pokeDance.loading];
        if (GSfsysGetStatus(0x825) == 0) {
            e->resource = GSresGetResource(0x825, e->id);
            if (e->resource != 0) {
                _pokeDance.loading = -1;
            }
        }
    }
    if (_pokeDance.loading == -1 && request) {
        PokeDanceEntry *e = _pokeDance.entries;
        u32 i;
        for (i = 0; i < 0xF0 && e->id != 0; i++, e++) {
            if (e->resource == 0) {
                GSfsysReadID(0x825, e->id);
                _pokeDance.loading = i;
                break;
            }
        }
    }
    colorAnimationTimeDark += timeGetLastFrameSec();
    colorAnimationTimeReliveReady += timeGetLastFrameSec();
    if (colorAnimationTimeDark > 1.0f) {
        colorAnimationTimeDark -= 1.0f;
    }
    if (colorAnimationTimeReliveReady > 1.0f) {
        colorAnimationTimeReliveReady -= 1.0f;
    }
}

void CAnt::waitEndOfReading() {
    for (;;) {
        if (_pokeDance.loading != -1) {
            PokeDanceEntry *e = &_pokeDance.entries[_pokeDance.loading];
            if (GSfsysGetStatus(0x825) == 0) {
                e->resource = GSresGetResource(0x825, e->id);
                if (e->resource != 0) {
                    _pokeDance.loading = -1;
                }
            }
        }
        if (_pokeDance.loading == -1) {
            break;
        }
        GSthreadSwitch();
    }
}

void CAnt::systemFree() {
    waitEndOfReading();
    GSfsysFree(0x825);
    GSresFreeGroup(0x825);
    memset(&_pokeDance, 0, 0xB44);
}

void CAnt::systemInit() {
    memset(&_pokeDance, 0, 0xB44);
    _pokeDance.loading = -1;
}

void *antGetGStexture(void *p) {
    return (u8 *)p + *(s32 *)((u8 *)p + 0xC);
}

void antReadPostFunc(void *, u32) {
}
