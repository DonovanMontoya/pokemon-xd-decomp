#ifndef MSGCTRL_PRIVATE_HPP
#define MSGCTRL_PRIVATE_HPP
#include <global.h>

struct MsgCtx {
    u8 reserved0;
    u8 skip;
    u8 shadow;
    u8 talkSE;
    f32 f04, f08, f0c, f10;
    u8 reserved14[0xC];
    s16 font;
    u8 reserved22;
    u8 f23;
    u32 color;
    u8 reserved28[4];
    u8* saved;
    u8* cursor;
    u8 reserved34[0xD];
    u8 indentOff;
    s8 lineSpace;
    s8 baseLineBias;
    u8 flags;
    u8 keyFlag;
    u8 keyWaiting;
    u8 checkWaiting;
    u8 reserved48[2];
    s16 wait;
    u8 align;
    u8 ruby;
    u8 reserved4E[0x1A];
    f32 f68;
};
typedef char MsgCtxSizeCheck[sizeof(MsgCtx) >= 0x6C ? 1 : -1];
typedef char MsgCtxWaitCheck[((int)&((MsgCtx*)0)->wait) == 0x4A ? 1 : -1];

struct FightOutPokemon;
struct FightTrainer;

extern "C" {
extern u8* msg_palette;
extern u32* msg_palette_number;
s32 GSsndGetStatus(u32);
void soundOpenPlay(u32, u32, u32);
void GSmsgAdjustAlign(MsgCtx*);
void GSmsgSetColor(MsgCtx*);
void GSmsgSetFontInfo(MsgCtx*);
void GSmsgInitRuby(MsgCtx*);
u16* GSmsgGetGSchar(u32);
u8 menuIsCheck(u32);
void peopleSetTalkKeyWaitCallback();
void peopleSetTalkFlagCallback();
void GSsndPlayNow(u32);
u32 savedataGetStatus(u32, u32);
u16* heroBiosGetHizukiNamePtr(u32);
u16* heroBiosGetNamePtr(u32);
void* pokemonDataBiosGetPtr(u32);
u32 pokemonDataBiosGetName(void*);
void* wazaDataBiosGetPtr(u32);
u32 wazaDataBiosGetName(void*);
void* itemDataBiosGetPtr(u32);
u32 itemDataBiosGetName(void*);
void* fightTrainerKindDataBiosGetPtr(u32);
u32 fightTrainerKindDataBiosGetPrefixName(void*);
s32 pokecoloGetCountryCode();
s32 pokecoloGetLanguage();
u32 fightFloorGetStatus(u32, u32, u32, u32);
void* fightTargetGetPtrAsNowFightType(u32, FightOutPokemon*);
FightTrainer* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(u32, FightOutPokemon*);
FightTrainer* fightSideGetValidFightTrainerPtr(void*, u16);
u8 fightTrainerCheckDoFight(FightTrainer*);
u16* fightTrainerGetNamePtr(FightTrainer*);
u8 fightFloorIsNowEncountTuusinTaisen(u32);
u8 fightTargetIsHostSide(FightOutPokemon*, u32);
u16* fightOutPokemonGetNicknamePtr(FightOutPokemon*);
void msgctrlSetValue(s32, u32);
}
#endif
