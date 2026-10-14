#include <global.h>

struct _GSparticleGen;

struct peBankX {
    u8 isInfinite0;
    u8 kind1;
    u8 reserved2[6];
    void *ps;
    u8 reserved0c[0x134 - 0x0c];
    u32 flags;
    u8 reserved138[0x160 - 0x138];
    void *camera;
};

struct _GSparticleGen {
    u8 isBank;
    u8 reserved1[0x37];
    peBankX *bank;
};

struct _GSparticleBank {
    u8 reserved0;
    u8 reserved1;
    u8 loaded;
    u8 count;
    u8 reserved4[4];
    void *file;
    _GSparticleGen *gens;
};

extern "C" {
void GSmemFree(void *);
void GSgfxRenderWaitForDrawComplete(void);
void GSparticleDestroyGenerator(_GSparticleGen *, u8);
void GSparticleDestroyAllGenerators(_GSparticleBank *, u8);
void peBankFreeFile(void *);
void psSetParticleVisibility(void *, u8);
void psSetRandomVelocityScaling(void *, u8);
void psSetNodeScaling(void *, u8);
void psSetTornadoScaling(void *, u8, u8);
void psSetParticleTexScaling(void *, u8);
void psSetOffsetRotationInLocal(void *, u8, u8);
void psSetVelocityRotationInLocal(void *, u8);
void psGeneratorSetCamera(void *, void *);
u8 peBankIsInfinite(peBankX *);
void peBankStop(peBankX *);
void peBankStopLoop(peBankX *);
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
    GSgfxRenderWaitForDrawComplete();
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
        switch ((u32)g->isBank) {
        case 0:
            psSetVelocityRotationInLocal(b->ps, v);
            break;
        }
    }
}
