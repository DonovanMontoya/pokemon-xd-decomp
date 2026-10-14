#ifndef GAME_MENUORRECOLOSSEUM_LAYOUT_HPP
#define GAME_MENUORRECOLOSSEUM_LAYOUT_HPP
#include <dolphin/types.h>

struct Pokemon;
struct Hero {
    u8 data[0x978];
    Hero() {}
};
struct MenuOrrePos {
    s16 a;
    s16 b;
};
struct tagWINDOW_WORK {
    u8 reserved0[0x93];
    u8 unk93;
    u8 reserved94[8];
    MenuOrrePos unk9C;
    u8 reservedA0[4];
    u8 unkA4;
    u8 unkA5;
};
struct tagSPRITE_WORK {
    u8 reserved0[6];
    s16 unk6;
    u8 reserved8[0x4C];
    s16 unk54;
    s16 unk56;
};

class menuOrre {
public:
    u8 maxLevel;
    u8 reserved1;
    u16 deckNumber;
    s16 unk4;
    s16 slots[4];
    u16 unkE;
    u16 unk10;
    u8 isPush;
    u8 reserved13;
    u16 trainerDataId;
    u16 unk16;
    f32 unk18;
    Pokemon *list[13];

    menuOrre()
    {
        isPush = 0;
        unk16 = 0;
        unk18 = 0.0f;
        unk10 = 0;
        s32 i;
        for (i = 0; i < 13; i++) {
            list[i] = 0;
        }
        unk4 = 0;
        slots[0] = -1;
        slots[1] = -1;
        slots[2] = -1;
        slots[3] = -1;
    }

    void Button(tagWINDOW_WORK *);
    bool ConfirmPokemon();
    void ControlCursor(tagWINDOW_WORK *, tagSPRITE_WORK *);
    void CreatePokemonList();
    void Ctrl(tagWINDOW_WORK *);
    s32 GetDeckPokemonFaceID(u16);
    u8 GetDeckPokemonLevel(u16);
    s32 GetDeckPokemonMochimono(u16);
    u16 *GetDeckPokemonName(u16);
    Pokemon *GetDeckPokemonPtr(u16);
    s32 GetDeckPokemonSex(u16);
    Hero *GetHeroPtr(u8);
    u8 GetTemochiMaxPokemonLevel();
    s32 GetTemochiPokemonFaceID(u16);
    u8 GetTemochiPokemonLevel(u16);
    s32 GetTemochiPokemonMochimono(u16);
    u16 *GetTemochiPokemonName(u16);
    Pokemon *GetTemochiPokemonPtr(u16);
    s32 GetTemochiPokemonSex(u16);
    s32 Hook(tagWINDOW_WORK *, tagSPRITE_WORK *);
    void Init();
    void InitSub();
    void LeftPanel(tagWINDOW_WORK *, tagSPRITE_WORK *);
    void Main();
    void Release();
    void RightPanel(tagWINDOW_WORK *, tagSPRITE_WORK *);
    s32 SelectPokemon(u16, bool);
    void SetNumber(tagWINDOW_WORK *, tagSPRITE_WORK *);
};

#endif
