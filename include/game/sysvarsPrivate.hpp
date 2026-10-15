#ifndef GAME_SYSVARS_PRIVATE_HPP
#define GAME_SYSVARS_PRIVATE_HPP
#include <dolphin/types.h>
struct SystemVars {
    s32 debugsysvars;
    s32 gsmemsize;
    s32 perfbar;
    s32 errortrap;
    s32 dispmemsize;
    s32 btldbg_menuflag;
    s32 btldbg_deckgrp;
    s32 btldbg_encountid;
    s32 btldbg_story_encountid;
    s32 btldbg_hundred_encountid;
    s32 btldbg_imasugu_encountid;
    s32 btldbg_virtual_encountid;
    s32 btldbg_bingo_encountid;
    s32 btldbg_colosseum_encountid;
    s32 btldbg_itemset1;
    s32 btldbg_auto_encount;
    s32 flddbg_pokedoru;
    s32 flddbg_pokecoupon;
    char localip[16];
    char gamecubeip[16];
    s32 serverport;
    s32 outputport;
    char netmask[16];
    char gateway[16];
    s32 hero_coli_disable_but;
};
struct sysvarsFuncEntry {
    const char *name;
    void (*callback)(void *, char *);
    s32 type;
    void *data;
};
typedef char SystemVarsSize[sizeof(SystemVars)==0x94 ? 1 : -1];
#endif
