#include <game/pxdvs/app/pokemon/pokemon.hpp>


struct FootStepCounter;
struct FLAGETC {
    u8 pad[0x428];
    u32 value;
};

extern "C" {
u8 pokemonDataBiosGetZokuseiDataId(void *, u16);
u16 zokuseiGetWazaJoutai(u16, u16);
void *memset(void *, int, u32);
void *memcpy(void *, const void *, u32);
int memcmp(const void *, const void *, u32);
u32 GSflagGet(u32);
void *GSmemAllocClr(u32);
void GSmemFree(void *);
void GSthreadSwitch(void);
void *savedataGetStatus(void *, u32);
s32 heroMoveAddStepCallback(void (*)(long, FootStepCounter, long), long);
void heroMoveInitEvent(void);
void heroMoveSetColision(u8);
void heroMoveTermEvent(void);
void menuScriptInfoRelive(Pokemon *, u8, long);
u16 pokemonBiosGetDarkpokemonDataId(Pokemon *);
u8 darkPokemonBiosGetInformationFlag(u16);
u16 darkPokemonBiosGetSteps(u16);
void darkPokemonBiosSetSteps(u16, u16);
u8 pokemonCheckValid(Pokemon *);
void pokemonAddDp(Pokemon *, f32);
void pokemonAllKaihuku(Pokemon *);
void *memmove(void *, const void *, u32);
struct RELIVEHALLDATA { u16 pad; u16 steps; };
extern FLAGETC *flag_etc;
extern RELIVEHALLDATA *relivehall_data;
}

class CReliveStage;

class CReliveHall {
public:
    void debugPokemonSetup(long);
    static bool isOpen();
    static CReliveHall *getPointer();
    CReliveStage *getStageAt(long);
    bool isReliveReadyDarkLugiaExist();
    s32 getReliveReadyVisitorQuantity();
    bool isReliveReadyPokemonExist();
    Pokemon *heroWalkReliveCallBack(long);
    void init();
    CReliveStage *getStage(long);
    void allocMakeBackup();
    void checkWithBackupSet();
    s32 getReliveGiveStageQuantity();
};

class CReliveStage {
public:
    Pokemon dancer[4];
    Pokemon visitor;
    s8 pairIndex;
    u8 pad[3];
    void init();
    void pickupVisitor(Pokemon &);
    void insertDancer(Pokemon &, long);
    void pickupDancer(Pokemon &, long);
    void exchangeVisitor(Pokemon &);
    void exchangeDancer(Pokemon &, long);
    s32 getDancerQuantity();
    Pokemon *getDancerPointer(long);
    void putVisitor(Pokemon &);
    Pokemon *getVisitorPointer();
    s32 getState();
    bool isLugiaReliveReady();
    bool isReliveReady();
    Pokemon *heroWalkReliveCallBack(long, bool);
    bool isPokemonZokuseiAllUnique(bool);
    s32 getTempo();
    s32 getPassionWoBonus();
    bool isBonusGet();
    s32 getPassion();
};


namespace {
s32 _heroCallBackHandle;
void _heroCallBackFunc(long, FootStepCounter, long);
s32 _tempoBase[5] = {0, 5, 14, 27, 48};
s32 _tempoGood[5] = {0, 6, 6, 6, 12};
s32 _tempoNormal[5] = {0, 2, 2, 2, 4};
s32 _bonusStageBonusTbl[10] = {0, 0, 1, 5, 10, 15, 25, 35, 50, 100};
}

s32 reliveHallPokemonToAisyou(Pokemon *a, Pokemon *b) {
    static u16 jyoutai2levelTbl[4] = {0x43, 0x42, 0x3F, 0x41};
    Pokemon *p[2];
    s32 z[2][2];
    p[0] = a;
    p[1] = b;
    if (!a || !b) {
        return -1;
    }
    s32 *zbase = &z[0][0];
    Pokemon **pp = p;
    s32 *zp = zbase;
    s32 i = 0;
    do {
        s32 j = 0;
        s32 *q = zp;
        do {
            *q = pokemonDataBiosGetZokuseiDataId((*pp)->getPokemonDataPtr(), (u16)j);
            j++;
            q++;
        } while (j < 2);
        i++;
        pp++;
        zp += 2;
    } while (i < 2);
    s32 best = 0;
    i = 0;
    s32 *zi = zbase;
    do {
        s32 j = 0;
        s32 *zj = zbase;
        do {
            s32 v;
            s32 x = *zi;
            s32 y = zj[2];
            if (x == 0 && y == 0) {
                v = 2;
            } else {
                s32 r = zokuseiGetWazaJoutai(x, y);
                v = 0x7B;
                for (s32 k = 0; k < 4; k++) {
                    if (r == jyoutai2levelTbl[k]) {
                        s32 m = k - 1;
                        v = m & ~(m >> 31);
                        break;
                    }
                }
            }
            if (best < v) {
                best = v;
            }
            j++;
            zj++;
        } while (j < 2);
        i++;
        zi++;
    } while (i < 2);
    return best;
}

CReliveHall *CReliveHall::getPointer() {
    return (CReliveHall *)savedataGetStatus(savedataGetStatus(0, 0), 0x15);
}

extern "C" void reliveHallDebugPokemonSetup(long arg) {
    CReliveHall::getPointer()->debugPokemonSetup(arg);
}

extern "C" void reliveHallCallBackInit(void) {
    _heroCallBackHandle = heroMoveAddStepCallback(_heroCallBackFunc, 0);
}

bool CReliveHall::isOpen() {
    return GSflagGet(0x3C4) >= flag_etc->value;
}

namespace {
void *_pRelivehallCopy;
}

void CReliveHall::allocMakeBackup() {
    _pRelivehallCopy = GSmemAllocClr(0x2298);
    memcpy(_pRelivehallCopy, this, 0x2298);
}

CReliveStage *CReliveHall::getStage(long i) {
    return (CReliveStage *)((u8 *)this + i * 0x3D8);
}

Pokemon *CReliveStage::getVisitorPointer() {
    return pokemonCheckValid(&visitor) ? &visitor : 0;
}

Pokemon *CReliveStage::getDancerPointer(long i) {
    Pokemon *p = &dancer[i];
    return pokemonCheckValid(p) ? p : 0;
}

s32 CReliveStage::getDancerQuantity() {
    s32 n = 0;
    do {
        if (!pokemonCheckValid(&dancer[n])) {
            break;
        }
        n++;
    } while (n < 4);
    return n;
}

s32 CReliveStage::getTempo() {
    s32 n = getDancerQuantity();
    s32 base = _tempoBase[n];
    s32 sum = 0;
    s32 v;
    for (s32 i = 0; i < n; i++) {
        Pokemon *a = getDancerPointer(i);
        Pokemon *b = getDancerPointer((i + 1) % n);
        switch (reliveHallPokemonToAisyou(a, b)) {
        case -1:
        case 0:
            v = 0;
            break;
        case 1:
            v = _tempoNormal[n];
            break;
        case 2:
            v = _tempoGood[n];
            break;
        }
        sum += v;
    }
    return sum + base;
}

static inline void setDancerPlace(CReliveStage *stage, Pokemon *p) {
    pokemonAllKaihuku(p);
    long idx = ((u8 *)stage - (u8 *)CReliveHall::getPointer()) / 0x3D8;
    DarkPokemon *dp = p->getDarkPokemon();
    if (dp) {
        dp->setPlace(place3, idx);
    }
}



void CReliveStage::init() {
    memset(this, 0, 0x3D8);
    pokemonInitAry((u32)dancer, 4);
    pokemonInit((u32)&visitor);
}

void CReliveStage::pickupVisitor(Pokemon &p) {
    memcpy(&p, &visitor, 0xC4);
    pokemonInit((u32)&visitor);
}

void CReliveStage::insertDancer(Pokemon &p, long i) {
    long n = 4 - (i + 1);
    if (n != 0) {
        memmove(&dancer[i + 1], &dancer[i], n * 0xC4);
    }
    Pokemon *d = &dancer[i];
    memcpy(d, &p, 0xC4);
    setDancerPlace(this, d);
    pokemonInit((u32)&p);
}

void CReliveStage::pickupDancer(Pokemon &p, long i) {
    Pokemon *d = &dancer[i];
    memcpy(&p, d, 0xC4);
    long n = 4 - (i + 1);
    if (n != 0) {
        memmove(d, &dancer[i + 1], n * 0xC4);
    }
    pokemonInit((u32)&dancer[3]);
}

void CReliveStage::exchangeVisitor(Pokemon &p) {
    Pokemon *d = &visitor;
    Pokemon tmp = *d;
    memcpy(d, &p, 0xC4);
    memcpy(&p, &tmp, 0xC4);
    setDancerPlace(this, d);
}

void CReliveStage::exchangeDancer(Pokemon &p, long i) {
    Pokemon *d = &dancer[i];
    Pokemon tmp = *d;
    memcpy(d, &p, 0xC4);
    memcpy(&p, &tmp, 0xC4);
    setDancerPlace(this, d);
}



void CReliveStage::putVisitor(Pokemon &p) {
    memcpy(&visitor, &p, 0xC4);
    setDancerPlace(this, &visitor);
    pokemonInit((u32)&p);
}


void CReliveHall::init() {
    CReliveStage *s = (CReliveStage *)this;
    memset(s, 0, 0x2298);
    u32 i = 0;
    do {
        s->init();
        i++;
        s++;
    } while (i < 9);
}

bool CReliveHall::isReliveReadyDarkLugiaExist() {
    CReliveStage *s = (CReliveStage *)this;
    u32 i = 0;
    do {
        Pokemon *v = s->getVisitorPointer();
        if (v && v->getPokemonDataId() == 0xF9) {
            break;
        }
        i++;
        s++;
        if (i >= 9) {
            return false;
        }
    } while (true);
    s = (CReliveStage *)this;
    u32 j = 0;
    do {
        if (s->getTempo() != 0x60) {
            return false;
        }
        j++;
        s++;
    } while (j < 9);
    return true;
}

s32 CReliveHall::getReliveReadyVisitorQuantity() {
    CReliveStage *s = (CReliveStage *)this;
    s32 n = 0;
    u32 i = 0;
    do {
        if (s->isReliveReady()) {
            n++;
        }
        i++;
        s++;
    } while (i < 9);
    return n;
}

bool CReliveHall::isReliveReadyPokemonExist() {
    CReliveStage *s = (CReliveStage *)this;
    u32 i = 0;
    do {
        if (s->isReliveReady()) {
            return true;
        }
        i++;
        s++;
    } while (i < 9);
    return false;
}

Pokemon *CReliveHall::heroWalkReliveCallBack(long steps) {
    CReliveStage *s = (CReliveStage *)this;
    Pokemon *r = 0;
    u32 i = 0;
    do {
        if (!r) {
            r = s->heroWalkReliveCallBack(steps, true);
        } else {
            s->heroWalkReliveCallBack(steps, false);
        }
        i++;
        s++;
    } while (i < 9);
    return r;
}

s32 CReliveStage::getState() {
    if (isReliveReady()) {
        return 3;
    }
    s32 t = getTempo();
    if (t == 0) {
        return 0;
    }
    s32 r = 1;
    if (t == 0x60) {
        r = 2;
    }
    return r;
}

bool CReliveStage::isReliveReady() {
    Pokemon *v = getVisitorPointer();
    if (!v) {
        return false;
    }
    if (isLugiaReliveReady()) {
        return true;
    }
    return v->getDarkPoint() <= 0.0f && getDancerQuantity() != 0;
}

bool CReliveStage::isLugiaReliveReady() {
    Pokemon *v = getVisitorPointer();
    if (!v) {
        return false;
    }
    bool r = false;
    if (CReliveHall::getPointer()->isReliveReadyDarkLugiaExist() && v->getPokemonDataId() == 0xF9) {
        r = true;
    }
    return r;
}

Pokemon *CReliveStage::heroWalkReliveCallBack(long steps, bool flag) {
    if (getPassion() == 0) {
        return 0;
    }
    Pokemon *v = getVisitorPointer();
    if (v->getPokemonDataId() == 0xF9) {
        return 0;
    }
    u16 id = pokemonBiosGetDarkpokemonDataId(v);
    if (darkPokemonBiosGetReliveFlag(id)) {
        return 0;
    }
    if (v->getDarkPointDirect() == 0) {
        return 0;
    }
    u16 cur = darkPokemonBiosGetSteps(id);
    if (cur >= relivehall_data->steps && flag) {
        pokemonAddDp(v, (f32)-getPassion());
        darkPokemonBiosSetSteps(id, cur - relivehall_data->steps);
        if (v->getDarkPointDirect() != 0) {
            return 0;
        }
        return v;
    }
    darkPokemonBiosSetSteps(id, cur + steps);
    return 0;
}
