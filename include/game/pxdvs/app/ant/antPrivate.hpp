#ifndef PXDVS_APP_ANT_ANT_PRIVATE_HPP
#define PXDVS_APP_ANT_ANT_PRIVATE_HPP

#include <dolphin/types.h>

template <class T>
struct PocketVec {
    T x;
    T y;
    static const PocketVec zero;
};

class Pokemon {
public:
    u8 reserved[0xC4];
    bool checkValid() const;
    u16 getPokemonDataId() const;
    bool isDarkPokemon() const;
    bool isRare() const;
    f32 getDarkPoint() const;
};

class CAnt {
public:
    u32 unk0;
    u32 unk4;
    s16 x;
    s16 y;
    f32 unkC;
    u8 unk10;
    u32 unk14;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    f32 unk2C;
    u32 unk30;
    static f32 colorAnimationTimeDark;
    static f32 colorAnimationTimeReliveReady;
    void init();
    void initByPokemon(Pokemon *);
    void initByPokemonAndSetColorAnimationInAny(Pokemon *);
    void initByPokemonAndSetColorAnimationInReliveHallVisitor(Pokemon *);
    void setAnimation(long);
    void use();
    void draw(PocketVec<short>);
    void drawAndUpdate();
    void drawAndUpdate(PocketVec<short>);
    void drawAndUpdateWithOffset(PocketVec<short>);
    static void systemInit();
    static void systemFree();
    static void systemUpdate(bool);
    static void systemUsecountReset();
    static void systemUnUseResourceRelease();
    static void allRequestCancel();
    static void waitEndOfReading();
};

typedef char CAntSize[sizeof(CAnt) == 0x34 ? 1 : -1];

struct PokeDanceEntry {
    u32 id;
    void *resource;
    s32 useCount;
};

struct PokeDanceWork {
    PokeDanceEntry entries[0xF0];
    s32 loading;
};

typedef char PokeDanceWorkSize[sizeof(PokeDanceWork) == 0xB44 ? 1 : -1];

#endif
