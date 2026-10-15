#ifndef PE_BANK_PRIVATE_HPP
#define PE_BANK_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peEmitterPrivate.hpp>
struct ParticleBankFile { u32 flags; u32 reserved04; _peEmitter* emitter; u8 references; };
struct ParticleBankState {
    ParticleBankFile* file; peEmitterNode node; ParticleBankFile* data;
    u8 reserved10c[0x28]; u32 flags, rendered; u16 token, maxParams; u8 bound[0x20]; void* camera; ParticleBankState* next;
};
extern "C" {
extern ParticleBankState* g_currentBank;
extern void* g_currentBound;
u8 peBankIsInfinite(ParticleBankState*);
f32 peBankGetLife(ParticleBankState*);
void peBankStopLoop(ParticleBankState*);
void peBankStop(ParticleBankState*);
u8 particleEnginePrepareUpdate(void*);
u8 particleEnginePrepareRender(void*);
u8 GSgfxTokenCleared(u16);
void GSboundReset(void*); void GSboundAlwaysInView(void*,s32); s32 GSboundIsInViewFast(void*);
}
typedef char ParticleBankFlagsOffsetCheck[offsetof(ParticleBankState, flags) == 0x134 ? 1 : -1];
typedef char ParticleBankCameraOffsetCheck[offsetof(ParticleBankState, camera) == 0x160 ? 1 : -1];
#endif
