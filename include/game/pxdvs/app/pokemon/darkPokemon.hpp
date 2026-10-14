#ifndef DARK_POKEMON_H
#define DARK_POKEMON_H
#include <global.h>
enum darkPokemonWhere { place0, place1, place2, place3, place4, place5, place6 };
enum darkPokemonStatus { darkStatus0, darkStatus1, darkStatus2, darkStatus3, darkStatus4 };
enum darkPokemonSnatchWho { snatchWho0, snatchWho1, snatchWho2, snatchWho3 };
struct DarkPokemon {
    union {
        struct { u8 status:3; u8 reserved:1; u8 infoLevel:3; u8 whoHigh:1; } statusFlags;
        struct { u16 reserved:7; u16 who:2; u16 remainder:7; } snatchFlags;
        struct { u32 reserved:14; u32 place:3; u32 remainder:15; } placeFlags;
        u8 unk0x0[4];
    };
    union {
        struct { u32 poolExp:20; u32 remainder:12; } experience;
        struct { u8 reserved[2]; u8 upper:4; u8 catchBall:4; u8 information:1; u8 remainder:7; } capture;
    };
    u8 reserved08[3];
    u8 statusRnd[6]; // 0x0b
    u8 placeIndex; // 0x11
    u8 reserved12;
    u8 snatchIndex;
    u16 orgTrainer;
    u16 catchFloorId;
    u16 poolFriendLevel;
    u16 pokemonID;
    u32 rnd;
    u32 escapeOrSnatchTime;
    s32 darkPoint;
    u16 trainerName[11];
    u16 darkPokemonID;
    u8 reversPattern;
    u8 reserved41[3];
    u32 walkCount;
    void setPlace(darkPokemonWhere, u8);
    void getPlace(darkPokemonWhere&, u8&) const;
    void setReversMode(bool);
    bool isReversMode() const;
    void setDarkPoint(f32);
    f32 getDarkPoint() const;
    s32 getInitDarkPointDirect() const;
    s32 getDarkPointDirect() const;
    void setDarkPointDirect(s32);
    void setPoolFriendLevel(u16);
    u16 getPoolFriendLevel() const;
    void setPoolExp(u32);
    u32 getPoolExp() const;
    void setTrainerName(const u16*);
    const u16* getTrainerName() const;
    void setStatusRnd(u8,u8);
    u8 getStatusRnd(u8) const;
    void setInformation(bool);
    bool isInformation() const;
    void setUpdate(bool);
    bool isUpdate() const;
    void setWazaNew(u8,bool);
    bool isWazaNew(u8) const;
    void setEscapeTime(u32);
    u32 getEscapeTime() const;
    void setSnatchTime(u32);
    darkPokemonStatus getStatus() const;
    void setStatus(darkPokemonStatus);
    void addStatus(darkPokemonStatus);
    void setSnatchFromWho(darkPokemonSnatchWho);
    darkPokemonSnatchWho getSnatchFromWho() const;
    void setSnatchInfoLevel(u8);
    bool isSnach() const;
    bool isRelive() const;
    void init();
    void setWalkCount(u32);
    u32 getWalkCount() const;
    void setReversPattern(u8);
    u8 getReversPattern() const;
    void setCatchBallID(u16);
    u16 getCatchBallID() const;
    void setDarkPokemonID(u16);
    u16 getDarkPokemonID() const;
    void setPokemonID(u16);
    u16 getPokemonID() const;
    void setRnd(u32);
    u32 getRnd() const;
    void setCatchFloorId(u16);
    u16 getCatchFloorId() const;
    void setOrgTrainer(u16);
    u16 getOrgTrainer() const;
    void setSnatchIndex(u8);
    u8 getSnatchIndex() const;
    struct ModeFlags { u8 reserved:1; u8 revers:1; u8 update:1; u8 wazaNew:3; u8 remainder:2; };
};
extern "C" DarkPokemon* darkPokemonGetDarkPokemon(u32);
extern "C" u8 darkPokemonBiosGetReliveFlag(u16);
extern "C" u16 darkPokemonBiosGetDarkPoint(u16);
#endif
