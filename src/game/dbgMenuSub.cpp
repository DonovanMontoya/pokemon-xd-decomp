#include <global.h>

struct Hero {
    static Hero* getHeroPtr();
    void setHeroStyle(u8, bool);
};

struct DbgScreenFilter {
    u8 v[7];
};

extern "C" {
void GScharMakeFromSJIS(char*, const char*);
void GSdvdFstRefresh(void);
void GSflagOff(u32);
u32 GSfloorGetCurrent(void);
s32 GSgfxPerfbarGetRenderMode(void);
void GSgfxPerfbarSetRenderMode(s32);
u8 GSgfxVideoGetLockFrameActive(void);
void GSgfxVideoSetFilter(DbgScreenFilter*);
void GSgfxVideoSetLockFrameActive(bool);
void GSgfxVideoSetLockFrameRate(s32);
void GSgfxVideoSetMode(s32, s32, s32, s32, s32);
void GSlogWrite(const char*, ...);
u8 GSmemCheckHeap(s32);
void GSmemDumpHeap(s32);
void GSmemDumpHeapInfo(void);
void GSmemDumpPool(s32);
void GSmodelSetShadowDebug(u8);
void GSmoviePlay(s32, s32, s32, s32);
u8 GSmoviePlayCheck(s32);
void GSmovieStop(s32);
void GSresDumpAll(void);
u8* GSresGetResource(s32, s32);
void GSthreadSwitch(void);
s32 floorGetActiveOffscreenTexture(void);
u8 floorGetHumanColision(void);
s32 floorGetLocalHeapHandle(void);
u8 floorIsDispScriptInfo(void);
void floorSetDispScriptInfo(s32);
void floorSetHumanColision(s32);
u8 floorSound_getDispSoundVolume(void);
void floorSound_setDispSoundVolume(s32);
s32 gamedataGetStatus(s32, s32);
void heroCatchPokemon(s32, void*, s32, s32, s32);
void heroItemAddItemDataId(s32, s32, s32, s32);
void heroSetFollowerWithID(s32, s32);
u8 lightIsDebugMode(void);
void lightSetDebugMode(s32);
s32 mailAddMailbox(s32);
s32 mailChkReceiveMail(s32);
void mailMainReceiveStart(void);
void mailMainSendAllMail(void);
void memoDataSet(s32, void*);
void menuClose(s32);
u8 menuIsCheck(s32);
s32 menuOpen(s32, s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
void menuSubCloseNumberInput(void);
u8 menuSubOpenNumberInputDigit(u32, u32*);
u8 menuSubOpenNumberInputID(u32, u32*, const char* (*)(u32));
void menuSubOpenYesNoField(void);
s32 pokecoloGetRomVersion(void);
void pokemonCreate(void*, s32, s32, s32);
void pokemonSetDarkPokemonStatus(void*, s32);
s32 savedataGetStatus(s32, s32);
u32 soundGetBGMID(void);
u32 soundGetEnvID(void);
void soundOpenPlay(u32, s32, s32);
void soundStop(u32, s32);
void winMsgClose(s32);
void winMsgOpenField(u32, s32, s32);

extern s8 __pokecolo_renderXluc;
extern u32* flag_data_number;
extern s32 g_hFloorHeap;
}

static s32 _dbgMenuDispAMemInfoFlag;

static const char* _dbgMenuMovieTestGetStr(unsigned long index);

extern "C" {

s32 dbgMenuGetRootMenu(void) {
    switch (pokecoloGetRomVersion()) {
    case 2:
        return 0x1F1;
    case 0:
    case 1:
    default:
        return 2;
    }
}

s32 dbgMenuPeopleViewerRintoOnOff(void) { return 0; }
s32 dbgMenuPeopleViewerMouthOnOff(void) { return 0; }
s32 dbgMenuPeopleViewerEyeOnOff(void) { return 0; }
s32 dbgMenuPeopleViewerAnim(void) { return 0; }
s32 dbgMenuPeopleViewerPlaySpeed(void) { return 0; }
s32 dbgMenuPeopleViewerMotion(void) { return 0; }
s32 dbgMenuPeopleViewerChara(void) { return 0; }

s32 dbgMenuSoundVolumeDisp(void) {
    if (floorSound_getDispSoundVolume() == 1) {
        floorSound_setDispSoundVolume(0);
    } else {
        floorSound_setDispSoundVolume(1);
    }
    return 0;
}

s32 dbgMenuGSresDumpGroup(void) {
    GSresDumpAll();
    return 0;
}

s32 dbgMenuDbgPokemonGet(void) {
    u8 pokemon[0xC4];
    s32 save = savedataGetStatus(0, 2);

    pokemonCreate(pokemon, 0x87, 0x28, gamedataGetStatus(0, 1));
    heroCatchPokemon(save, pokemon, 0, 4, 1);
    memoDataSet(0, pokemon);
    pokemonCreate(pokemon, 0x86, 0x28, gamedataGetStatus(0, 1));
    heroCatchPokemon(save, pokemon, 0, 4, 1);
    memoDataSet(0, pokemon);
    pokemonCreate(pokemon, 0x161, 0x64, gamedataGetStatus(0, 1));
    pokemonSetDarkPokemonStatus(pokemon, 0x40);
    heroCatchPokemon(save, pokemon, 0, 4, 1);
    pokemonCreate(pokemon, 0x162, 0x64, gamedataGetStatus(0, 1));
    pokemonSetDarkPokemonStatus(pokemon, 0x4D);
    heroCatchPokemon(save, pokemon, 0, 4, 1);
    pokemonCreate(pokemon, 0xAC, 0x64, gamedataGetStatus(0, 1));
    pokemonSetDarkPokemonStatus(pokemon, 0x4C);
    heroCatchPokemon(save, pokemon, 0, 4, 1);
    pokemonCreate(pokemon, 0xFA, 0x64, gamedataGetStatus(0, 1));
    pokemonSetDarkPokemonStatus(pokemon, 0x1D);
    heroCatchPokemon(save, pokemon, 0, 4, 1);
    heroItemAddItemDataId(save, 1, 0x63, -1);
    heroItemAddItemDataId(save, 2, 0x63, -1);
    heroItemAddItemDataId(save, 3, 0x63, -1);
    heroItemAddItemDataId(save, 4, 0x63, -1);
    heroItemAddItemDataId(save, 5, 0x63, -1);
    heroItemAddItemDataId(save, 6, 0x63, -1);
    heroItemAddItemDataId(save, 7, 0x63, -1);
    heroItemAddItemDataId(save, 8, 0x63, -1);
    heroItemAddItemDataId(save, 9, 0x63, -1);
    heroItemAddItemDataId(save, 0xA, 0x63, -1);
    heroItemAddItemDataId(save, 0xB, 0x63, -1);
    heroItemAddItemDataId(save, 0xC, 0x63, -1);
    heroItemAddItemDataId(save, 0x15, 0x63, -1);
    heroItemAddItemDataId(save, 0xD, 0x12C, -1);
    heroItemAddItemDataId(save, 0x122, 1, -1);
    heroItemAddItemDataId(save, 0x121, 3, -1);
    heroItemAddItemDataId(save, 0x88, 3, -1);
    heroItemAddItemDataId(save, 0x86, 1, -1);
    heroItemAddItemDataId(save, 0x87, 2, -1);
    heroItemAddItemDataId(save, 0x200, 1, -1);
    heroItemAddItemDataId(save, 0x202, 1, -1);
    heroItemAddItemDataId(save, 0x203, 1, -1);
    heroItemAddItemDataId(save, 0x201, 1, -1);
    heroItemAddItemDataId(save, 0x215, 1, -1);
    heroItemAddItemDataId(save, 0x216, 1, -1);
    heroItemAddItemDataId(save, 0x217, 1, -1);
    heroItemAddItemDataId(save, 0x218, 1, -1);
    heroItemAddItemDataId(save, 0x219, 1, -1);
    heroItemAddItemDataId(save, 0x21A, 1, -1);
    heroItemAddItemDataId(save, 0x21B, 1, -1);
    heroItemAddItemDataId(save, 0x21C, 1, -1);
    heroItemAddItemDataId(save, 0x21D, 1, -1);
    heroItemAddItemDataId(save, 0x21E, 1, -1);
    heroItemAddItemDataId(save, 0x21F, 1, -1);
    heroItemAddItemDataId(save, 0x220, 1, -1);
    heroItemAddItemDataId(save, 0x221, 1, -1);
    heroItemAddItemDataId(save, 0x222, 1, -1);
    heroItemAddItemDataId(save, 0x223, 1, -1);
    heroItemAddItemDataId(save, 0x224, 1, -1);
    heroItemAddItemDataId(save, 0x225, 1, -1);
    heroItemAddItemDataId(save, 0x226, 1, -1);
    heroItemAddItemDataId(save, 0x227, 1, -1);
    heroItemAddItemDataId(save, 0x228, 1, -1);
    heroItemAddItemDataId(save, 0x229, 1, -1);
    heroItemAddItemDataId(save, 0x22A, 1, -1);
    heroItemAddItemDataId(save, 0x22B, 1, -1);
    heroItemAddItemDataId(save, 0x22C, 1, -1);
    heroItemAddItemDataId(save, 0x22D, 1, -1);
    heroItemAddItemDataId(save, 0x22E, 1, -1);
    heroItemAddItemDataId(save, 0x22F, 1, -1);
    heroItemAddItemDataId(save, 0x230, 1, -1);
    heroItemAddItemDataId(save, 0x231, 1, -1);
    heroItemAddItemDataId(save, 0x232, 1, -1);
    heroItemAddItemDataId(save, 0x233, 1, -1);
    heroItemAddItemDataId(save, 0x234, 1, -1);
    heroItemAddItemDataId(save, 0x235, 1, -1);
    heroItemAddItemDataId(save, 0x236, 1, -1);
    heroItemAddItemDataId(save, 0x237, 1, -1);
    heroItemAddItemDataId(save, 0x238, 1, -1);
    heroItemAddItemDataId(save, 0x239, 1, -1);
    heroItemAddItemDataId(save, 0x23A, 1, -1);
    heroItemAddItemDataId(save, 0x23B, 1, -1);
    heroItemAddItemDataId(save, 0x23C, 1, -1);
    heroItemAddItemDataId(save, 0x23D, 1, -1);
    heroItemAddItemDataId(save, 0x23E, 1, -1);
    heroItemAddItemDataId(save, 0x23F, 1, -1);
    heroItemAddItemDataId(save, 0x240, 1, -1);
    heroItemAddItemDataId(save, 0x241, 1, -1);
    heroItemAddItemDataId(save, 0x242, 1, -1);
    heroItemAddItemDataId(save, 0x243, 1, -1);
    heroItemAddItemDataId(save, 0x244, 1, -1);
    heroItemAddItemDataId(save, 0x245, 1, -1);
    heroItemAddItemDataId(save, 0x246, 1, -1);
    heroItemAddItemDataId(save, 0x247, 1, -1);
    heroItemAddItemDataId(save, 0x248, 1, -1);
    heroItemAddItemDataId(save, 0x249, 1, -1);
    heroItemAddItemDataId(save, 0x24A, 1, -1);
    heroItemAddItemDataId(save, 0x24B, 1, -1);
    heroItemAddItemDataId(save, 0x24C, 1, -1);
    heroItemAddItemDataId(save, 0x24D, 1, -1);
    heroItemAddItemDataId(save, 0x24E, 1, -1);
    heroItemAddItemDataId(save, 0x24F, 1, -1);
    heroItemAddItemDataId(save, 0x250, 1, -1);
    heroItemAddItemDataId(save, 0x251, 1, -1);
    return 0;
}

s32 dbgMenuSetHeroStyleSnatch(void) {
    Hero::getHeroPtr()->setHeroStyle(2, true);
    return 0;
}

s32 dbgMenuSetHeroStyleVisor(void) {
    Hero::getHeroPtr()->setHeroStyle(1, true);
    return 0;
}

s32 dbgMenuSetHeroStyleNormal(void) {
    Hero::getHeroPtr()->setHeroStyle(0, true);
    return 0;
}

s32 dbgMenuScriptFlagAllClear(void) {
    u32 i;
    for (i = 1; i < *flag_data_number; i++) {
        GSflagOff(i);
    }
    return 0;
}

s32 dbgMenuKleinPTin(void) {
    heroSetFollowerWithID(3, 0);
    return 0;
}

s32 dbgMenuGirlPTin(void) {
    heroSetFollowerWithID(2, 0);
    return 0;
}

s32 dbgMenuManaPTin(void) {
    heroSetFollowerWithID(1, 0);
    return 0;
}

s32 dbgMenuPTout(void) {
    heroSetFollowerWithID(0, 0);
    return 0;
}

s32 dbgMenuScriptLightEdt(void) {
    if (lightIsDebugMode() == 1) {
        lightSetDebugMode(0);
    } else {
        lightSetDebugMode(1);
    }
    return 0;
}

s32 dbgMenuScriptHumanColision(void) {
    if (floorGetHumanColision() == 1) {
        floorSetHumanColision(0);
    } else {
        floorSetHumanColision(1);
    }
    return 0;
}

s32 dbgMenuScriptSoundTest(void) {
    static u32 snd_id;
    static s8 init;
    if (init == 0) {
        snd_id = 0;
        init = 1;
    }
    while (menuSubOpenNumberInputDigit(snd_id, &snd_id) == 1) {
        if (snd_id == soundGetBGMID() || snd_id == soundGetEnvID()) {
            soundStop(snd_id, 1000);
        } else {
            soundOpenPlay(snd_id, 0, 0x7F);
        }
    }
    return 0;
}

s32 dbgMenuScriptYesNoMsgTest(void) {
    static u32 msg_id;
    static s8 init;
    if (init == 0) {
        msg_id = 0;
        init = 1;
    }
    while (menuSubOpenNumberInputDigit(msg_id, &msg_id) == 1) {
        winMsgOpenField(msg_id, 1, 0);
        menuSubOpenYesNoField();
        winMsgClose(1);
    }
    return 0;
}

s32 dbgMenuScriptMsgTest(void) {
    static u32 msg_id;
    static s8 init;
    if (init == 0) {
        msg_id = 0;
        init = 1;
    }
    while (menuSubOpenNumberInputDigit(msg_id, &msg_id) == 1) {
        winMsgOpenField(msg_id, 1, 0);
        winMsgClose(1);
    }
    return 0;
}

s32 dbgMenuScriptDispLine(void) {
    if (floorIsDispScriptInfo() == 1) {
        floorSetDispScriptInfo(0);
    } else {
        floorSetDispScriptInfo(1);
    }
    return 0;
}

s32 debugMenuChangeAMemInfo(void) {
    static s32 disp;
    static s8 init;
    if (init == 0) {
        disp = 0;
        init = 1;
    }
    switch (disp) {
    case 0:
    case 1:
        _dbgMenuDispAMemInfoFlag = disp;
        menuOpenCustom(0x21, 0, 0, 0, 0, 0);
        disp++;
        break;
    default:
        if (menuIsCheck(0x21)) {
            menuClose(0x21);
        }
        disp = 0;
        break;
    }
    return 0;
}

s32 dbgMenuMovieTest(void) {
    static s32 test_movie[16] = {
        0x8ED, 0x8EE, 0x8EF, 0x8F0, 0x8F1, 0x8F2, 0x8F3, 0x9F4,
        0xA17, 0x7D9, 0x7DA, 0x7DC, 0x8EB, 0x7DD, 0x8EC, 0x814,
    };
    static u16 test_movie_wh[32] = {
        0xC0, 0x90, 0xC0, 0x90, 0xC0, 0x90, 0xC0, 0x90, 0xC0, 0x90, 0xC0, 0x90, 0xC0, 0x90, 0xC0, 0x90,
        0xC0, 0x90, 0x280, 0x1E0, 0x280, 0x1E0, 0x280, 0x1E0, 0x280, 0x1E0, 0x280, 0x1E0, 0x280, 0x1E0, 0xC0, 0x90,
    };
    static u32 test_movie_index;
    static s8 init;
    u32 index;
    s32 texture;
    u32 i;

    if (init == 0) {
        test_movie_index = 0;
        init = 1;
    }
    for (i = 0; i < 16; i++) {
        while (GSmoviePlayCheck(test_movie[i]) == 1) {
            GSmovieStop(test_movie[i]);
            GSthreadSwitch();
        }
    }
    if (!menuSubOpenNumberInputID(test_movie_index, &index, _dbgMenuMovieTestGetStr)) {
        return 0;
    }
    if (index >= 16) {
        index = 15;
    }
    menuSubCloseNumberInput();
    if (GSfloorGetCurrent() == 0x196 && test_movie_wh[index * 2] == 0xC0 && test_movie_wh[index * 2 + 1] == 0x90) {
        texture = floorGetActiveOffscreenTexture();
    } else {
        texture = 0;
    }
    GSdvdFstRefresh();
    GSmoviePlay(test_movie[index], 0, 1, texture);
    test_movie_index = index;
    return 0;
}

}

static const char* _dbgMenuMovieTestGetStr(unsigned long index) {
    static const char* test_movie_str[16] = {
        "tv_news_common",
        "tv_news_ren",
        "tv_music_chiril",
        "tv_deathgold_appear",
        "tv_agent_report",
        "tv_cyobin_comments",
        "tv_battle_demo",
        "tv_colosseum_demo",
        "tv_colosseum_demo_lugia",
        "tpc_logo",
        "gs_logo",
        "auto_demo",
        "ending",
        "staffroll",
        "relive_complete",
        "event_battle_192x144",
    };
    static char strbuf[64];
    if (index >= 16) {
        index = 15;
    }
    GScharMakeFromSJIS(strbuf, test_movie_str[index]);
    return strbuf;
}

extern "C" {

s32 dbgMenuSetPAL60(void) {
    GSgfxVideoSetMode(2, 1, 0, 1, 0);
    return 0;
}

s32 dbgMenuSetPAL50(void) {
    GSgfxVideoSetMode(1, 1, 0, 1, 0);
    return 0;
}

s32 dbgMenuGSmemOptimize(void) {
    return 0;
}

s32 dbgMenuGSmemDispMap(void) {
    GSmemDumpHeapInfo();
    GSmemDumpHeap(g_hFloorHeap);
    GSmemDumpHeap(0);
    GSmemDumpPool(0);
    return 0;
}

s32 dbgMenuGSmemCheck(void) {
    GSlogWrite("check fsys heap\n");
    u8 ok = GSmemCheckHeap(0);
    GSlogWrite("%s\n", ok ? "ok" : "error");
    GSlogWrite("check floor heap\n");
    ok = GSmemCheckHeap(floorGetLocalHeapHandle());
    GSlogWrite("%s\n", ok ? "ok" : "error");
    GSlogWrite("check system heap\n");
    ok = GSmemCheckHeap(g_hFloorHeap);
    GSlogWrite("%s\n", ok ? "ok" : "error");
    return 0;
}

s32 dbgMenuScreenFilterHi(void) {
    const DbgScreenFilter filter = {{0x0D, 0x09, 0x07, 0x06, 0x07, 0x09, 0x0D}};
    DbgScreenFilter copy = filter;
    GSgfxVideoSetFilter(&copy);
    return 0;
}

s32 dbgMenuScreenFilterMed(void) {
    const DbgScreenFilter filter = {{9, 9, 9, 10, 9, 9, 9}};
    DbgScreenFilter copy = filter;
    GSgfxVideoSetFilter(&copy);
    return 0;
}

s32 dbgMenuScreenFilterLow(void) {
    const DbgScreenFilter filter = {{0x04, 0x06, 0x0E, 0x10, 0x0E, 0x06, 0x04}};
    DbgScreenFilter copy = filter;
    GSgfxVideoSetFilter(&copy);
    return 0;
}

s32 dbgMenuScreenFilterDefault(void) {
    const DbgScreenFilter filter = {{0x08, 0x08, 0x0A, 0x0C, 0x0A, 0x08, 0x08}};
    DbgScreenFilter copy = filter;
    GSgfxVideoSetFilter(&copy);
    return 0;
}

s32 dbgMenuScreenFilterOff(void) {
    const DbgScreenFilter filter = {{0, 0, 0x15, 0x16, 0x15, 0, 0}};
    DbgScreenFilter copy = filter;
    GSgfxVideoSetFilter(&copy);
    return 0;
}

s32 dbgMenuFrameLockToggle(void) {
    GSgfxVideoSetLockFrameActive(GSgfxVideoGetLockFrameActive() == 0);
    return 0;
}

s32 dbgMenuFrameRate15(void) {
    GSgfxVideoSetLockFrameRate(3);
    return 0;
}

s32 dbgMenuFrameRate20(void) {
    GSgfxVideoSetLockFrameRate(2);
    return 0;
}

s32 dbgMenuFrameRate30(void) {
    GSgfxVideoSetLockFrameRate(1);
    return 0;
}

s32 dbgMenuFrameRate60(void) {
    GSgfxVideoSetLockFrameRate(0);
    return 0;
}

s32 dbgMenuSendAllMail(void) {
    mailMainSendAllMail();
    return 0;
}

s32 dbgMenuSendMail(void) {
    s32 mail;
    while ((mail = menuOpen(2, 1)) != -1) {
        if (mailChkReceiveMail(mail) == 0 && mailAddMailbox(mail) != 0) {
            mailMainReceiveStart();
        }
    }
    return 0;
}

s32 dbgMenuColisionDisp(s32 id) {
    u8* res = GSresGetResource(0, 2);
    if (res == 0) {
        return 0;
    }
    switch (id) {
    case 0x131:
        if (res[0] != 0) {
            res[0] = 0;
        } else {
            res[0] = 1;
        }
        break;
    case 0x132:
        if (res[1] != 0) {
            res[1] = 0;
        } else {
            res[1] = 1;
        }
        break;
    }
    return 0;
}

s32 debugMenuColorBarDisp(void) {
    __pokecolo_renderXluc = 0;
    menuOpenCustom(5, 0, 0, 0, 1, 0);
    menuClose(5);
    __pokecolo_renderXluc = 1;
    return 0;
}

s32 debugMenuShadowBorderDisp(void) {
    static bool borderDisp;
    static s8 init;
    if (init == 0) {
        borderDisp = 0;
        init = 1;
    }
    borderDisp = !borderDisp;
    GSmodelSetShadowDebug(borderDisp);
    return 0;
}

s32 debugMenuNodrawArea(void) {
    if (menuIsCheck(7)) {
        menuClose(7);
    } else {
        menuOpenCustom(7, 0, 0, 0, 0, 0);
    }
    return 0;
}

s32 debugMenuChangeMemInfo(void) {
    if (menuIsCheck(4)) {
        menuClose(4);
    } else {
        menuOpenCustom(4, 0, 0, 0, 0, 0);
    }
    return 0;
}

s32 debugMenuChangePerfBar(void) {
    s32 mode = GSgfxPerfbarGetRenderMode();
    switch (mode) {
    case 0:
        mode = 2;
        break;
    case 2:
        mode = 1;
        break;
    case 1:
        mode = 0;
        break;
    }
    GSgfxPerfbarSetRenderMode(mode);
    return 0;
}

}
