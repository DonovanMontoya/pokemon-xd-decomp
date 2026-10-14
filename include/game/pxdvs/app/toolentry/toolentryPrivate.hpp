#ifndef TOOLENTRY_PRIVATE_H
#define TOOLENTRY_PRIVATE_H

#include <global.h>

extern "C" void* memcpy(void*, const void*, unsigned long);

class Pokemon {
public:
    u8 raw[0xC4];
    Pokemon& operator=(const Pokemon& o) {
        memcpy(this, &o, sizeof(Pokemon));
        return *this;
    }
};

class Hero {
public:
    u8 raw[0x978];
    Hero& operator=(const Hero& o) {
        memcpy(this, &o, sizeof(Hero));
        return *this;
    }
};

struct ToolentryCBTrainer {
    u16 trainerDataId;      // 0x0
    u8 pad02[6];            // 0x2
    s32 order[6];           // 0x8
    s32 orderNum;           // 0x20
    s32 controllerType;     // 0x24
};

struct ToolentryCBWork {
    u32 x0;
    s32 battleMode;         // 0x4
    s32 battleType;         // 0x8
    u32 xc;
    u32 x10;
    s32 battleVersus;       // 0x14
};

struct ToolentryTrainerFace {
    u16 trainerId;          // 0x0
    u32 bigFaceBoy;         // 0x4
    u32 bigFaceGirl;        // 0x8
    u32 smallFaceBoy;       // 0xC
    u32 smallFaceGirl;      // 0x10
};

extern "C" {
void* GSmemAllocAlign(unsigned long, unsigned short);
void GSmemFree(void*);
ToolentryCBWork* menuCBBios_WorkContext();
ToolentryCBTrainer* menuCBBios_GetTrainerImmediately(long);
s16 menuCBBios_ParticipationPokemonMax();
u32 menuCBTrainerBios_GetPlayerID(ToolentryCBTrainer*);
u32 menuCBTrainerBios_GetHomePlace(ToolentryCBTrainer*);
Pokemon* heroBiosGetPokemonPtr(Hero*, u16);
void heroInit(Hero*);
void pokemonInit(Pokemon*);
u8 pokemonCheckValid(Pokemon*);
void* savedataGetStatus(u32, u32);
u32 fightTrainerDB_GetPkxDataId(u16);
void pokemonCreate(Pokemon*, u16, u8, s32);
void pokemonSetCatchStatus(Pokemon*, u32, u32, u32, u32, u32, s32);
void pokemonAllKaihuku(Pokemon*);
s32 gamedataGetStatus(u32, u32);
s32 GSmsgGetGSchar(s32);
extern ToolentryTrainerFace* trainer_face_data;
extern u32* trainer_face_data_number;
}

#endif
