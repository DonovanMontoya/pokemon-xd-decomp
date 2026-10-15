#include <game/sysvarsPrivate.hpp>
#include <libc/string.h>
extern "C" {
int stricmp(const char *, const char *);
int atoi(const char *);
double atof(const char *);
void GSgfxGPUSetMode(s32);
void GSgfxRender();
void GSprimDraw2DQuad(const void *, f32, f32, f32, f32);
void GSprimSetTextColor(const void *);
void GSprimSetTextWidth(f32);
void GSprimSetTextSize(f32, f32);
void GSprimWriteStr(const char *, f32, f32, ...);
}
struct GSgfxLayer;
void GSprimSetup2DRender(GSgfxLayer *);
static void _sysvarsProcess(char *);
static void _sysvarsProcessData(sysvarsFuncEntry *, char *);
static sysvarsFuncEntry *_sysvarsFindEntry(char *);
static void _sysvarsPerfbar(void *, char *);
static void _sysvarsGSmemSize(void *, char *);

SystemVars systemVars = {
    0,
    24,
    0,
    1,
    0,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    0,
    0,
    -1,
    -1,
    {0},
    {0},
    0,
    0,
    {0},
    {0},
    0,
};

static sysvarsFuncEntry _sysvarsFuncList[] = {
    {"debugsysvars", 0, 0, &systemVars.debugsysvars},
    {"gsmemsize", _sysvarsGSmemSize, 1, &systemVars.gsmemsize},
    {"perfbar", _sysvarsPerfbar, 1, &systemVars.perfbar},
    {"errortrap", 0, 0, &systemVars.errortrap},
    {"dispmemsize", 0, 0, &systemVars.dispmemsize},
    {"btldbg_menuflag", 0, 0, &systemVars.btldbg_menuflag},
    {"btldbg_deckgrp", 0, 1, &systemVars.btldbg_deckgrp},
    {"btldbg_encountid", 0, 1, &systemVars.btldbg_encountid},
    {"btldbg_story_encountid", 0, 1, &systemVars.btldbg_story_encountid},
    {"btldbg_hundred_encountid", 0, 1, &systemVars.btldbg_hundred_encountid},
    {"btldbg_imasugu_encountid", 0, 1, &systemVars.btldbg_imasugu_encountid},
    {"btldbg_virtual_encountid", 0, 1, &systemVars.btldbg_virtual_encountid},
    {"btldbg_bingo_encountid", 0, 1, &systemVars.btldbg_bingo_encountid},
    {"btldbg_colosseum_encountid", 0, 1, &systemVars.btldbg_colosseum_encountid},
    {"btldbg_itemset1", 0, 0, &systemVars.btldbg_itemset1},
    {"btldbg_auto_encount", 0, 0, &systemVars.btldbg_auto_encount},
    {"flddbg_pokedoru", 0, 1, &systemVars.flddbg_pokedoru},
    {"flddbg_pokecoupon", 0, 1, &systemVars.flddbg_pokecoupon},
    {"localip", 0, 3, &systemVars.localip},
    {"gamecubeip", 0, 3, &systemVars.gamecubeip},
    {"serverport", 0, 1, &systemVars.serverport},
    {"outputport", 0, 1, &systemVars.outputport},
    {"netmask", 0, 3, &systemVars.netmask},
    {"gateway", 0, 3, &systemVars.gateway},
    {"hero_coli_disable_but", 0, 0, &systemVars.hero_coli_disable_but},
    {0, 0, 0, 0}
};

extern "C" void sysvarsShowDebug() {
    struct Color { u8 r, g, b, a; };
    Color background = {0, 0, 0, 255};
    Color text = {255, 255, 255, 255};
    GSgfxGPUSetMode(1);
    u32 frames = 899;
    do {
        GSprimSetup2DRender(0);
        Color color = background;
        GSprimDraw2DQuad(&color, 0.0f, 0.0f, 640.0f, 480.0f);
        Color textColor = text;
        GSprimSetTextColor(&textColor);
        GSprimSetTextWidth(2.0f);
        GSprimSetTextSize(12.0f, 12.0f);
        f32 y = 40.0f;
        for (sysvarsFuncEntry *entry = _sysvarsFuncList; entry->name; entry++) {
            switch (entry->type) {
            case 0: case 1:
                GSprimWriteStr("%s=%d", 100.0f, y, entry->name, *(s32 *)entry->data);
                break;
            case 2:
                GSprimWriteStr("%s=%f", 100.0f, y, entry->name, *(f32 *)entry->data);
                break;
            case 3:
                GSprimWriteStr("%s=%s", 100.0f, y, entry->name, (char *)entry->data);
                break;
            }
            y += 14.0f;
        }
        GSprimWriteStr("%d", 500.0f, 400.0f, frames / 60);
        GSgfxRender();
    } while (frames-- != 0);
    GSgfxGPUSetMode(2);
}

extern "C" void sysvarsReadSettings(int *argc, char ***argv) {
    if (*argc >= 2) {
        _sysvarsProcess((*argv)[1]);
        for (int i = 1; i < *argc; i++) (*argv)[i] = (*argv)[i + 1];
        (*argc)--;
    }
}

static void _sysvarsProcess(char *cursor) {
    while (*cursor) {
        char *name = cursor;
        while (*cursor && *cursor != '-') cursor++;
        if (*cursor == '-') {
            *cursor = 0;
            sysvarsFuncEntry *entry = _sysvarsFindEntry(name);
            cursor++;
            char *value = cursor;
            while (*cursor && *cursor != ':') cursor++;
            if (*cursor == ':') *cursor++ = 0;
            if (entry) _sysvarsProcessData(entry, value);
        }
    }
}

static void _sysvarsProcessData(sysvarsFuncEntry *entry, char *value) {
    if (entry->callback == 0) {
        switch (entry->type) {
        case 0: {
            s32 *destination = (s32 *)entry->data;
            if (!stricmp(value, "off") || !stricmp(value, "false") || !stricmp(value, "0"))
                *destination = 0;
            else if (!stricmp(value, "on") || !stricmp(value, "true") || !stricmp(value, "1"))
                *destination = 1;
            break;
        }
        case 1: {
            s32 *destination = (s32 *)entry->data;
            *destination = atoi(value);
            break;
        }
        case 2: {
            f32 *destination = (f32 *)entry->data;
            *destination = atof(value);
            break;
        }
        case 3: strcpy((char *)entry->data, value); break;
        }
    } else {
        entry->callback(entry->data, value);
    }
}

static sysvarsFuncEntry *_sysvarsFindEntry(char *name) {
    for (sysvarsFuncEntry *entry = _sysvarsFuncList; entry->name; entry++) {
        if (!stricmp(name, entry->name)) return entry;
    }
    return 0;
}

static void _sysvarsPerfbar(void *data, char *value) {
    if (!stricmp(value, "off")) *(s32 *)data = 0;
    else if (!stricmp(value, "simple")) *(s32 *)data = 1;
    else if (!stricmp(value, "detail")) *(s32 *)data = 2;
}

static void _sysvarsGSmemSize(void *data, char *value) {
    if (!stricmp(value, "24")) *(s32 *)data = 24;
    else if (!stricmp(value, "48")) *(s32 *)data = 48;
}
