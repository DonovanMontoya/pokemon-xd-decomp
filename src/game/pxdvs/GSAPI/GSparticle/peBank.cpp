#include <game/pxdvs/GSAPI/GSparticle/peBankPrivate.hpp>

extern "C" {
ParticleBankState* g_currentBank;
void* g_currentBound;
u16 g_bank_token;
_EmitParams* g_emitParams;
u16 g_maxEmitParams;
ParticleBankState* g_emitParamsBank;
}
extern "C" u8 peBankIsInfinite(ParticleBankState* bank) {
    if (!bank) return 0;
    if (!(bank->flags & 1)) return 0;
    return bank->node.emitter->flags & 1;
}
extern "C" f32 peBankGetLife(ParticleBankState* bank) {
    if (!bank) return 0.0f;
    if (bank->flags & 1) return bank->node.life;
    return 0.0f;
}
extern "C" void peBankStopLoop(ParticleBankState* bank) {
    if (peBankIsInfinite(bank)) bank->node.SetLastLoop();
}
extern "C" void peBankStop(ParticleBankState* bank) {
    if (bank && (bank->flags & 1)) {
        g_currentBank = bank;
        g_currentBound = (bank->flags & 0x10) ? bank->bound : 0;
        bank->node.Stop(bank->data->emitter);
        bank->flags = 0;
    }
}
extern "C" void peBankUpdate(ParticleBankState* bank, f32 delta) {
    if (!bank) return;
    if (!(bank->flags & 1)) return;
    if (bank->flags & 2) return;
    if (bank->token && GSgfxTokenCleared(bank->token)) bank->token = 0;
    if (!particleEnginePrepareUpdate(bank->camera)) return;
    g_currentBank = bank;
    if (bank->flags & 0x10) {
        g_currentBound = bank->bound;
        GSboundReset(g_currentBound);
        GSboundAlwaysInView(g_currentBound, 0);
    } else g_currentBound = 0;
    f32 alive = bank->node.Update(0, bank->data->emitter, delta);
    if (alive <= 0.0f) {
        bank->node.Stop(bank->data->emitter);
        bank->flags = 0;
    } else {
        if (!g_currentBound || GSboundIsInViewFast(g_currentBound)) bank->flags |= 8;
        else bank->flags &= ~8;
    }
}

extern "C" {
extern u16 g_bank_token;
extern void* g_CameraMatrix;
void push__16GSgfxMatrixStackFP5GSmtx(void*,void*);
void pop__16GSgfxMatrixStackFv(void*);
void GSboundDraw__FP7GSboundP10GSgfxLayer(void*,ParticleLayer*);
}
extern "C" void peBankRender(ParticleBankState* bank) {
    if (!bank) return;
    if (!(bank->flags & 1)) return;
    if (!(bank->flags & 4)) return;
    if (!(bank->flags & 8)) return;
    s32 kind = g_current_layer->kind;
    u32 mask = 1 << kind;
    if (g_render_pass == 1) mask <<= 16;
    if (bank->rendered & mask) return;
    g_currentBank = bank;
    g_currentBound = (bank->flags & 0x10) ? bank->bound : 0;
    if (particleEnginePrepareRender(bank->camera)) {
        bank->rendered |= mask;
        push__16GSgfxMatrixStackFP5GSmtx(*(void**)((u8*)g_current_layer + 0x19a0),g_CameraMatrix);
        g_bank_token = 0;
        bank->node.Render(bank->data->emitter);
        if (g_bank_token) bank->token = g_bank_token;
        if ((bank->flags & 0x10) && (bank->flags & 0x20) && g_current_layer->kind == 4 && g_render_pass == 1)
            GSboundDraw__FP7GSboundP10GSgfxLayer(bank->bound,g_current_layer);
        pop__16GSgfxMatrixStackFv(*(void**)((u8*)g_current_layer + 0x19a0));
    }
}

struct _gpdHeader { u32 magic, version; u16 reserved08, count; u8 references, reserved0d[3]; };
struct _gpdResourceItem { u8 reserved00, flags; u16 reserved02; s32 kind; void* data; };
struct _particleData { u32 flags; s32 kind; void* data; _particleData* next; };
struct BankModel { u32 flags; u8 reserved04[0x48]; void* model; };
struct BankDistortion { u8 reserved00[0x78]; u8* first; u8* second; };
extern "C" {
extern u32 g_particle_debug_stats[6];
void HSD_JObjUnref(void*);
void GStextureFree(void*);
u32 shapeGetUsedMemorySize(u16);
void shapeRelease(u16);
}
static void _peFreeInternalBankData(_particleData* data) {
    void* object = data->data;
    if (object) {
        switch (data->kind) {
        case 0: {
            _peEmitter* emitter = (_peEmitter*)object;
            if (emitter) {
                _particleData* child = (_particleData*)emitter->resources;
                while (child) { _peFreeInternalBankData(child); child = child->next; }
            }
            break;
        }
        case 2: {
            BankModel* model = (BankModel*)object;
            if (model && !(model->flags & 0x40)) {
                if (!model->model) return;
                HSD_JObjUnref(model->model);
            }
            break;
        }
        case 4: {
            BankDistortion* distortion = (BankDistortion*)object;
            if (distortion->first) {
                g_particle_debug_stats[1] -= 128;
                g_particle_debug_stats[5] -= 128;
                delete distortion->first;
                distortion->first = 0;
            }
            if (distortion->second) {
                g_particle_debug_stats[1] -= 128;
                g_particle_debug_stats[5] -= 128;
                delete distortion->second;
                distortion->second = 0;
            }
            break;
        }
        }
    }
}

extern "C" void peBankFreeFile(_gpdHeader* file) {
    if (file->magic == 0x01f056da) {
        switch(file->version - 0x30000) {
        case 2:
            if (file->references == 0) {
                _peFreeInternalBankData((_particleData*)((u8*)(file + 1) + file->count * 12));
                u32 remaining = file->count;
                _gpdResourceItem* resource = (_gpdResourceItem*)(file + 1);
                while (remaining) {
                    if ((resource->flags & 0x40) == 0x40) {
                        switch(resource->kind) {
                        case 0: GStextureFree(resource->data); break;
                        case 3: {
                            u16 shape = (u32)resource->data - 1;
                            u32 size = shapeGetUsedMemorySize(shape);
                            g_particle_debug_stats[4] -= size;
                            g_particle_debug_stats[5] -= size;
                            shapeRelease(shape);
                            break;
                        }
                        case 2: {
                            u32* textures = (u32*)resource->data;
                            u32 count = *textures++;
                            for(u32 i = 0; i < count; ++i, ++textures) {
                                if (*textures) GStextureFree((void*)*textures);
                            }
                            break;
                        }
                        }
                    }
                    ++resource; --remaining;
                }
            }
            break;
        }
    }
}
extern bool _peConvertFileData(_gpdHeader*,_gpdResourceItem*,_particleData*,const char*);
extern "C" _gpdHeader* peBankLoadFile(_gpdHeader* file) {
    _gpdResourceItem* items = (_gpdResourceItem*)(file + 1);
    if (_peConvertFileData(file,items,(_particleData*)(items+file->count),(const char*)file)) return file;
    return 0;
}

extern "C" {
extern u16 g_maxEmitParams;
extern ParticleBankState* g_emitParamsBank;
extern ParticleBankState* g_particleBanks;
void GSgfxTokenWaitForClear(u16);
void GSboundFree(void*);
u32 GSmemGetSize(void*);
}
extern "C" void peBankFree(ParticleBankState* bank) {
    if (bank) {
        peBankStop(bank);
        if (bank->token) {
            GSgfxTokenWaitForClear(bank->token);
            bank->token = 0;
        }
        bank->node.Release();
        --bank->file->references;
        GSboundFree(bank->bound);
        if (bank && g_maxEmitParams && g_emitParamsBank == bank) {
            u32 previous = g_particle_debug_stats[0];
            g_particle_debug_stats[0] = 0;
            g_particle_debug_stats[5] -= previous;
            delete[] g_emitParams;
            g_emitParams = 0;
            g_emitParamsBank = 0;
            g_maxEmitParams = 0;
            ParticleBankState* current = g_particleBanks;
            while (current) {
                if (current != bank && current->maxParams > g_maxEmitParams) {
                    g_maxEmitParams = (current->maxParams + 9) & ~9;
                    g_emitParamsBank = current;
                }
                current = current->next;
            }
            u16 count = g_maxEmitParams;
            if (count) {
                g_emitParams = new _EmitParams[count];
                u32 bytes = g_maxEmitParams * sizeof(_EmitParams);
                g_particle_debug_stats[0] += bytes;
                g_particle_debug_stats[5] += bytes;
            }
        }
        ParticleBankState* previous = 0;
        ParticleBankState* current = g_particleBanks;
        while (current) {
            if (current == bank) break;
            previous = current;
            current = current->next;
        }
        if (previous) previous->next = current->next;
        else g_particleBanks = current->next;
        current->next = 0;
        u32 bytes = GSmemGetSize(bank);
        g_particle_debug_stats[1] -= bytes;
        g_particle_debug_stats[5] -= bytes;
        delete bank;
    }
}
