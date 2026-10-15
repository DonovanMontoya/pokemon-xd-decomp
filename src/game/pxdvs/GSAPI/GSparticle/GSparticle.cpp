#include <global.h>

struct _GSparticleGen;
struct _GSparticleBank;
enum GenKind { GEN_PS = 0, GEN_BANK = 1 };

struct psGenX {
    u8 reserved0[0x15];
    u8 familyB;
    u8 reserved16[2];
    u16 familyA;
    u8 reserved1a[6];
    f32 x, y, z;
};

struct psCtl {
    u8 reserved0[0x10];
    u16 lifeA;
    u8 reserved12[5];
    u8 flag17;
};

struct peBankX {
    u8 isInfinite0;
    u8 kind1;
    u8 reserved2[2];
    u32 birth;
    psGenX *ps;
    f32 x, y, z;
    u8 reserved18[0x134 - 0x18];
    u32 flags;
    u8 reserved138[0x160 - 0x138];
    void *camera;
};

struct psWrap {
    u8 flag0;
    u8 isFinite;
    u16 id;
    u32 birth;
    psCtl *ps;
};

struct _GSparticleGen {
    u8 isBank;
    u8 f1;
    u8 f2;
    u8 pad3;
    s32 f4;
    s32 part;
    s32 fc;
    f32 px, py, pz;
    u8 reserved1c[0x34 - 0x1c];
    _GSparticleBank *parent;
    peBankX *bank;
};

struct _GSparticleBank {
    u8 reserved0;
    u8 kind;
    u8 loaded;
    u8 count;
    u8 disabled;
    u8 reserved5[3];
    void *file;
    _GSparticleGen *gens;
    void *camera;
};

extern "C" {
void GSmemFree(void *);
void GSgfxRenderWaitForDrawComplete__Fv(void);
void GSparticleDestroyGenerator(_GSparticleGen *, u8);
void GSparticleDestroyAllGenerators(_GSparticleBank *, u8);
void peBankFreeFile(void *);
void psSetParticleVisibility(psGenX *, u8);
void psSetRandomVelocityScaling(psGenX *, u8);
void psSetNodeScaling(psGenX *, u8);
void psSetTornadoScaling(psGenX *, u8, u8);
void psSetParticleTexScaling(psGenX *, u8);
void psSetOffsetRotationInLocal(psGenX *, u8, u8);
void psSetVelocityRotationInLocal(psGenX *, u8);
void psGeneratorSetCamera(psGenX *, void *);
u8 peBankIsInfinite(peBankX *);
void peBankStop(peBankX *);
void peBankStopLoop(peBankX *);
void peBankFree(peBankX *);
void psKillFamily(u16, u8);
void psKillGenerator(void *);
void *GSmemAlloc(u32);
psCtl *psCreateGeneratorID(u8, u8, u32);
peBankX *peBankCreate(void *);
void peBankStart(peBankX *);
u32 GSgfxVideoGetVsyncCount(void);
void GSparticleDetachGeneratorFromGSpart(_GSparticleGen *, u8);
}

void *g_particle_cameras[4];
s32 g_particle_cameras_count;
static void *_particleBankStructList;
static s32 _particleBankStructCount;
static u8 _particlePALFrameCount;
static u8 _invalidateVtx;
static u8 _invalidateTex;

static inline s32 _findFreeGenerator(_GSparticleBank *bank, u8 mode) {
    s32 i;
    _GSparticleGen *g = bank->gens;
    for (i = 0; i < bank->count; i++, g++) {
        if (mode != g->isBank) {
            return -1;
        }
        if (g->bank == 0) {
            return i;
        }
    }
    return -1;
}

static inline void _setBankVisibility(peBankX *b, bool v) {
    if (b) {
        if (v) {
            b->flags |= 4;
        } else {
            b->flags &= ~4;
        }
    }
}

extern "C" void GSparticleGeneratorSetCamera(_GSparticleGen *g, void *cam) {
    peBankX *b = g->bank;
    if (b) {
        if (g->isBank) {
            if (b) {
                b->camera = cam;
            }
        } else {
            psGeneratorSetCamera(b->ps, cam);
        }
    }
}

extern "C" void GSparticleFree(_GSparticleBank *bank) {
    GSgfxRenderWaitForDrawComplete__Fv();
    GSparticleDestroyAllGenerators(bank, 1);
    if (bank->gens) {
        GSmemFree(bank->gens);
        bank->gens = 0;
    }
    bank->gens = 0;
    bank->count = 0;
    if (bank->loaded) {
        peBankFreeFile(bank->file);
    }
    bank->reserved0 = 0;
}

extern "C" void GSparticleDestroyAllGenerators(_GSparticleBank *bank, u8 flag) {
    _GSparticleGen *g = bank->gens;
    for (u32 i = 0; i < bank->count; i++, g = (_GSparticleGen *)((u8 *)g + 0x3C)) {
        if (g->bank) {
            GSparticleDestroyGenerator(g, flag);
        }
    }
}

extern "C" void GSparticleStopGenerator(_GSparticleGen *g) {
    peBankX *b = g->bank;
    if (b && g->isBank) {
        if (peBankIsInfinite(b)) {
            peBankStopLoop(g->bank);
        } else {
            peBankStop(g->bank);
        }
    }
}

extern "C" void GSparticleSetBankVisibility(_GSparticleBank *bank, bool v) {
    _GSparticleGen *g = bank->gens;
    for (u32 i = 0; i < bank->count; i++, g = (_GSparticleGen *)((u8 *)g + 0x3C)) {
        peBankX *b = g->bank;
        if (b) {
            if (g->isBank) {
                _setBankVisibility(b, v);
            } else {
                psSetParticleVisibility(b->ps, v);
            }
        }
    }
}

extern "C" void GSparticleSetGeneratorVisibility(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        if (g->isBank) {
            _setBankVisibility(b, v);
        } else {
            psSetParticleVisibility(b->ps, v);
        }
    }
}

extern "C" void GSparticleSetRandomVelocityScaling(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetRandomVelocityScaling(b->ps, v);
            break;
        }
    }
}

extern "C" void GSparticleSetNodeScaling(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetNodeScaling(b->ps, v);
            break;
        }
    }
}

extern "C" void GSparticleSetTornadoScaling(_GSparticleGen *g, bool a, bool c) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetTornadoScaling(b->ps, a, c);
            break;
        }
    }
}

extern "C" void GSparticleSetParticleTextureScaling(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetParticleTexScaling(b->ps, v);
            break;
        }
    }
}

extern "C" void GSparticleSetOffsetRotationInLocal(_GSparticleGen *g, bool a, bool c) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetOffsetRotationInLocal(b->ps, a, c);
            break;
        }
    }
}

extern "C" void GSparticleSetVelocityRotationInLocal(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        switch (g->isBank) {
        case 0:
            psSetVelocityRotationInLocal(b->ps, v);
            break;
        }
    }
}

extern "C" void GSparticleActivateBank(_GSparticleBank *bank) {
    bank->disabled = 0;
}

extern "C" void GSparticleDisactivateBank(_GSparticleBank *bank) {
    bank->disabled = 1;
}

extern "C" void GSparticleBankSetCamera(_GSparticleBank *bank, void *cam) {
    if (bank != 0) {
        switch (bank->reserved0) {
        case 0:
            break;
        default: {
            _GSparticleGen *g;
            u8 n;
            bank->camera = cam;
            n = bank->count;
            g = bank->gens;
            while (n--) {
                if (g->bank != 0) {
                    GSparticleGeneratorSetCamera(g, cam);
                }
                g++;
            }
            break;
        }
        }
    }
}

extern "C" void GSparticleSetGeneratorPosition(_GSparticleGen *g, f32 *pos) {
    peBankX *b = g->bank;
    if (b == 0) {
        return;
    }
    if (g->part == 0) {
        if (g->isBank) {
            if (b != 0) {
                f32 *p = (f32 *)((u8 *)b + 0x10C);
                p[0] = pos[0];
                p[1] = pos[1];
                p[2] = pos[2];
            }
        } else {
            b->x = pos[0];
            b->y = pos[1];
            b->z = pos[2];
            b->ps->x = pos[0];
            b->ps->y = pos[1];
            b->ps->z = pos[2];
        }
    } else {
        g->px = pos[0];
        g->py = pos[1];
        g->pz = pos[2];
    }
}

extern "C" void GSparticleDestroyGenerator(_GSparticleGen *g, u8 flag) {
    if (g->bank != 0) {
        if (g->part != 0) {
            GSparticleDetachGeneratorFromGSpart(g, 0);
        }
        if (g->isBank) {
            peBankFree(g->bank);
            g->bank = 0;
        } else {
            if (flag == 1) {
                psGenX *ps = g->bank->ps;
                psKillFamily(ps->familyA, ps->familyB);
            }
            psKillGenerator(g->bank->ps);
            if (g->bank != 0) {
                GSmemFree(g->bank);
                g->bank = 0;
            }
        }
    }
}

static void _particleBankDestroyOldestGenerator(_GSparticleBank *bank);

extern "C" bool GSparticleCreateGenerator(_GSparticleBank *bank, u32 id, u8 flag) {
    _GSparticleGen *g;
    if (bank->reserved0 == 0) {
        return 0;
    }
    if (bank->disabled != 0) {
        return 0;
    }
    if (bank->loaded != 0) {
        peBankX *b;
        s32 idx = _findFreeGenerator(bank, bank->loaded);
        if (idx < 0) {
            return 0;
        }
        b = peBankCreate(bank->file);
        if (b == 0) {
            return 0;
        }
        g = &bank->gens[idx];
        if (g->isBank == 0) {
            return 0;
        }
        if (b != 0) {
            b->camera = bank->camera;
        }
        peBankStart(b);
        g->bank = b;
        _invalidateVtx = 1;
    } else {
        s32 idx = _findFreeGenerator(bank, bank->loaded);
        psWrap *w;
        if (idx < 0) {
            _particleBankDestroyOldestGenerator(bank);
            idx = _findFreeGenerator(bank, bank->loaded);
            if (idx < 0) {
                return 0;
            }
        }
        w = (psWrap *)GSmemAlloc(0x30);
        if (w == 0) {
            return 0;
        }
        w->ps = psCreateGeneratorID(flag == 1 ? 1 : 0, bank->kind, id);
        if (w->ps == 0) {
            GSmemFree(w);
            return 0;
        }
        w->ps->flag17 = 1;
        psGeneratorSetCamera((psGenX *)w->ps, bank->camera);
        w->id = id;
        w->flag0 = flag;
        w->birth = GSgfxVideoGetVsyncCount();
        if (w->ps->lifeA == 0) {
            w->isFinite = 1;
        } else {
            w->isFinite = 0;
        }
        g = &bank->gens[idx];
        if (g->isBank != 0) {
            return 0;
        }
        g->bank = (peBankX *)w;
    }
    _invalidateTex = 1;
    g->part = 0;
    g->fc = 0;
    g->f4 = 0;
    g->f1 = 0;
    g->f2 = 0;
    g->parent = bank;
    return 1;
}

static void _particleBankDestroyOldestGenerator(_GSparticleBank *bank) {
    s32 oldest = -1;
    u32 best = -1;
    s32 i;
    _GSparticleGen *gens = bank->gens;
    for (i = 0; i < bank->count; i++) {
        _GSparticleGen *g = &gens[i];
        if (g->bank != 0) {
            u32 t = g->bank->birth;
            if (t < best) {
                best = t;
                oldest = i;
            }
        }
    }
    if (oldest != -1) {
        GSparticleDestroyGenerator(&gens[oldest], 1);
    }
}
