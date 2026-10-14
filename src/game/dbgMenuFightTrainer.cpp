/* Debug menu entries for editing fight trainer data (AI add/sub values etc). */
#include <global.h>

typedef struct DbgTrainerAiAddsub {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} DbgTrainerAiAddsub;

extern DbgTrainerAiAddsub* fightTrainerAiValueAddsubDataBiosGetPtr(u16);
extern s32 fightTrainerGetStatus(s32, u16, s32, s32);
extern void fightTrainerSetStatus(s32, u16, s32, s32, s32);
extern void menuCloseCustom(s32, s32, s32);
extern s32 menuGetCursorItemID(s32);
extern s32 menuOpen(s32, s32);
extern s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
extern void menuSubCloseNumberInput(void);
extern u8 menuSubOpenNumberInput(s32, s32*, s32, s32, s32, s32);
extern s32 dbgMenuFightGetWazaTypeId(u8);
extern s32 dbgMenuFightGetZokuseiDataId(u16);
extern void* fightTrainerPokemonPartDataBiosGetPtr(u16);
extern void* fightTrainerAiDataBiosGetPtr(u16);
extern s8 menuSubOpenYesNo(s32, s32, s32, s32);

static DbgTrainerAiAddsub _old_fight_trainer_ai_value_addsub_data[0x2D7];

typedef struct DbgTrainerPokemonPart {
    s32 data[6];
} DbgTrainerPokemonPart;

typedef struct DbgTrainerAi {
    s32 data[8];
} DbgTrainerAi;

void dbgMenuFightTrainerDataStatusInputDigit(u16 a, s32 b, s32 c, s32 max, s32 min);
void dbgMenuFightTrainerDataStatusInputFlag(u16 a, s32 b);

s32 dbgMenuFightTrainerAiAddsubDataComboEditSub(void) {
    u16 i;
    s32 result;

    for (i = 0; i < 0x2D7; i++) {
        DbgTrainerAiAddsub* src = fightTrainerAiValueAddsubDataBiosGetPtr(i);
        _old_fight_trainer_ai_value_addsub_data[i] = *src;
    }
    for (;;) {
        result = menuOpenCustom(0x1B, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1B, 0, 1);
            for (i = 0; i < 0x2D7; i++) {
                DbgTrainerAiAddsub* dst = fightTrainerAiValueAddsubDataBiosGetPtr(i);
                *dst = _old_fight_trainer_ai_value_addsub_data[i];
            }
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
    }
    menuCloseCustom(0x1B, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiAddsubDataItemEditSub(void) {
    u16 i;
    s32 result;

    for (i = 0; i < 0x2D7; i++) {
        DbgTrainerAiAddsub* src = fightTrainerAiValueAddsubDataBiosGetPtr(i);
        _old_fight_trainer_ai_value_addsub_data[i] = *src;
    }
    for (;;) {
        result = menuOpenCustom(0x1A, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1A, 0, 1);
            for (i = 0; i < 0x2D7; i++) {
                DbgTrainerAiAddsub* dst = fightTrainerAiValueAddsubDataBiosGetPtr(i);
                *dst = _old_fight_trainer_ai_value_addsub_data[i];
            }
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            menuCloseCustom(0x1A, 0, 1);
            return 1;
        }
    }
}

s32 dbgMenuFightTrainerAiAddsubDataWazaUsewazaEditSub(void) {
    u16 i;
    s32 result;

    for (i = 0; i < 0x2D7; i++) {
        DbgTrainerAiAddsub* src = fightTrainerAiValueAddsubDataBiosGetPtr(i);
        _old_fight_trainer_ai_value_addsub_data[i] = *src;
    }
    for (;;) {
        result = menuOpenCustom(0x1E, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1E, 0, 1);
            for (i = 0; i < 0x2D7; i++) {
                DbgTrainerAiAddsub* dst = fightTrainerAiValueAddsubDataBiosGetPtr(i);
                *dst = _old_fight_trainer_ai_value_addsub_data[i];
            }
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x1E)) {
        case 0xe7:
            dbgMenuFightTrainerDataStatusInputDigit(0x38, 0x3E, 0, 200, -200);
            break;
        case 0xe8:
            dbgMenuFightTrainerDataStatusInputDigit(0x39, 0x3E, 0, 200, -200);
            break;
        case 0xe9:
            dbgMenuFightTrainerDataStatusInputDigit(0x3a, 0x3E, 0, 200, -200);
            break;
        case 0xea:
            dbgMenuFightTrainerDataStatusInputDigit(0x3b, 0x3E, 0, 200, -200);
            break;
        case 0xeb:
            dbgMenuFightTrainerDataStatusInputDigit(0x3c, 0x3E, 0, 200, -200);
            break;
        case 0xec:
            dbgMenuFightTrainerDataStatusInputDigit(0x40, 0x3E, 0, 200, -200);
            break;
        case 0xed:
            dbgMenuFightTrainerDataStatusInputDigit(0x44, 0x3E, 0, 200, -200);
            break;
        case 0xee:
            dbgMenuFightTrainerDataStatusInputDigit(0x45, 0x3E, 0, 200, -200);
            break;
        case 0xef:
            dbgMenuFightTrainerDataStatusInputDigit(0x47, 0x3E, 0, 200, -200);
            break;
        case 0xf0:
            dbgMenuFightTrainerDataStatusInputDigit(0x48, 0x3E, 0, 200, -200);
            break;
        case 0xf1:
            dbgMenuFightTrainerDataStatusInputDigit(0x46, 0x3E, 0, 200, -200);
            break;
        case 0xf2:
            dbgMenuFightTrainerDataStatusInputDigit(0x41, 0x3E, 0, 200, -200);
            break;
        case 0xf3:
            dbgMenuFightTrainerDataStatusInputDigit(0x42, 0x3E, 0, 200, -200);
            break;
        case 0xf4:
            dbgMenuFightTrainerDataStatusInputDigit(0x43, 0x3E, 0, 200, -200);
            break;
        case 0xf5:
            dbgMenuFightTrainerDataStatusInputDigit(0x3d, 0x3E, 0, 200, -200);
            break;
        case 0xf6:
            dbgMenuFightTrainerDataStatusInputDigit(0x3e, 0x3E, 0, 200, -200);
            break;
        case 0xf7:
            dbgMenuFightTrainerDataStatusInputDigit(0x3f, 0x3E, 0, 200, -200);
            break;
        }
    }
    menuCloseCustom(0x1E, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiAddsubDataWazaDefpokemonEditSub(void) {
    u16 i;
    s32 result;

    for (i = 0; i < 0x2D7; i++) {
        DbgTrainerAiAddsub* src = fightTrainerAiValueAddsubDataBiosGetPtr(i);
        _old_fight_trainer_ai_value_addsub_data[i] = *src;
    }
    for (;;) {
        result = menuOpenCustom(0x19, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x19, 0, 1);
            for (i = 0; i < 0x2D7; i++) {
                DbgTrainerAiAddsub* dst = fightTrainerAiValueAddsubDataBiosGetPtr(i);
                *dst = _old_fight_trainer_ai_value_addsub_data[i];
            }
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        menuGetCursorItemID(0x19);
    }
    menuCloseCustom(0x19, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiAddsubDataIrekaeDasuEditSub(void) {
    u16 i;
    s32 result;

    for (i = 0; i < 0x2D7; i++) {
        DbgTrainerAiAddsub* src = fightTrainerAiValueAddsubDataBiosGetPtr(i);
        _old_fight_trainer_ai_value_addsub_data[i] = *src;
    }
    for (;;) {
        result = menuOpenCustom(0x1D, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1D, 0, 1);
            for (i = 0; i < 0x2D7; i++) {
                DbgTrainerAiAddsub* dst = fightTrainerAiValueAddsubDataBiosGetPtr(i);
                *dst = _old_fight_trainer_ai_value_addsub_data[i];
            }
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x1D)) {
        case 0xcd:
            dbgMenuFightTrainerDataStatusInputDigit(0x1d, 0x3E, 0, 200, -200);
            break;
        case 0xce:
            dbgMenuFightTrainerDataStatusInputDigit(0x1e, 0x3E, 0, 200, -200);
            break;
        case 0xcf:
            dbgMenuFightTrainerDataStatusInputDigit(0x1f, 0x3E, 0, 200, -200);
            break;
        case 0xd0:
            dbgMenuFightTrainerDataStatusInputDigit(0x21, 0x3E, 0, 200, -200);
            break;
        case 0xd1:
            dbgMenuFightTrainerDataStatusInputDigit(0x22, 0x3E, 0, 200, -200);
            break;
        case 0xd2:
            dbgMenuFightTrainerDataStatusInputDigit(0x23, 0x3E, 0, 200, -200);
            break;
        case 0xd3:
            dbgMenuFightTrainerDataStatusInputDigit(0x24, 0x3E, 0, 200, -200);
            break;
        case 0xd4:
            dbgMenuFightTrainerDataStatusInputDigit(0x25, 0x3E, 0, 200, -200);
            break;
        case 0xd5:
            dbgMenuFightTrainerDataStatusInputDigit(0x26, 0x3E, 0, 200, -200);
            break;
        case 0xd6:
            dbgMenuFightTrainerDataStatusInputDigit(0x27, 0x3E, 0, 200, -200);
            break;
        case 0xd7:
            dbgMenuFightTrainerDataStatusInputDigit(0x20, 0x3E, 0, 200, -200);
            break;
        case 0xd8:
            dbgMenuFightTrainerDataStatusInputDigit(0x30, 0x3E, 0, 200, -200);
            break;
        case 0xd9:
            dbgMenuFightTrainerDataStatusInputDigit(0x28, 0x3E, 0, 200, -200);
            break;
        case 0xda:
            dbgMenuFightTrainerDataStatusInputDigit(0x29, 0x3E, 0, 200, -200);
            break;
        case 0xdb:
            dbgMenuFightTrainerDataStatusInputDigit(0x2a, 0x3E, 0, 200, -200);
            break;
        case 0xdc:
            dbgMenuFightTrainerDataStatusInputDigit(0x2b, 0x3E, 0, 200, -200);
            break;
        }
    }
    menuCloseCustom(0x1D, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiAddsubDataIrekaeModosuEditSub(void) {
    u16 i;
    s32 result;

    for (i = 0; i < 0x2D7; i++) {
        DbgTrainerAiAddsub* src = fightTrainerAiValueAddsubDataBiosGetPtr(i);
        _old_fight_trainer_ai_value_addsub_data[i] = *src;
    }
    for (;;) {
        result = menuOpenCustom(0x1C, 0, 0, 0, 1, 0);
        if (result == -1) {
            menuCloseCustom(0x1C, 0, 1);
            for (i = 0; i < 0x2D7; i++) {
                DbgTrainerAiAddsub* dst = fightTrainerAiValueAddsubDataBiosGetPtr(i);
                *dst = _old_fight_trainer_ai_value_addsub_data[i];
            }
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x1C)) {
        case 0xb3:
            dbgMenuFightTrainerDataStatusInputDigit(0x1, 0x3E, 0, 200, -200);
            break;
        case 0xb4:
            dbgMenuFightTrainerDataStatusInputDigit(0x2, 0x3E, 0, 200, -200);
            break;
        case 0xb5:
            dbgMenuFightTrainerDataStatusInputDigit(0x3, 0x3E, 0, 200, -200);
            break;
        case 0xb6:
            dbgMenuFightTrainerDataStatusInputDigit(0x4, 0x3E, 0, 200, -200);
            break;
        case 0xb7:
            dbgMenuFightTrainerDataStatusInputDigit(0x5, 0x3E, 0, 200, -200);
            break;
        case 0xb8:
            dbgMenuFightTrainerDataStatusInputDigit(0x6, 0x3E, 0, 200, -200);
            break;
        case 0xb9:
            dbgMenuFightTrainerDataStatusInputDigit(0x7, 0x3E, 0, 200, -200);
            break;
        case 0xba:
            dbgMenuFightTrainerDataStatusInputDigit(0x8, 0x3E, 0, 200, -200);
            break;
        case 0xbb:
            dbgMenuFightTrainerDataStatusInputDigit(0x19, 0x3E, 0, 200, -200);
            break;
        case 0xbc:
            dbgMenuFightTrainerDataStatusInputDigit(0x9, 0x3E, 0, 200, -200);
            break;
        case 0xbd:
            dbgMenuFightTrainerDataStatusInputDigit(0xa, 0x3E, 0, 200, -200);
            break;
        case 0xbe:
            dbgMenuFightTrainerDataStatusInputDigit(0xb, 0x3E, 0, 200, -200);
            break;
        case 0xbf:
            dbgMenuFightTrainerDataStatusInputDigit(0xc, 0x3E, 0, 200, -200);
            break;
        case 0xc0:
            dbgMenuFightTrainerDataStatusInputDigit(0xd, 0x3E, 0, 200, -200);
            break;
        case 0xc1:
            dbgMenuFightTrainerDataStatusInputDigit(0xe, 0x3E, 0, 200, -200);
            break;
        case 0xc2:
            dbgMenuFightTrainerDataStatusInputDigit(0xf, 0x3E, 0, 200, -200);
            break;
        case 0xc3:
            dbgMenuFightTrainerDataStatusInputDigit(0x10, 0x3E, 0, 200, -200);
            break;
        case 0xc4:
            dbgMenuFightTrainerDataStatusInputDigit(0x11, 0x3E, 0, 200, -200);
            break;
        case 0xc5:
            dbgMenuFightTrainerDataStatusInputDigit(0x12, 0x3E, 0, 200, -200);
            break;
        case 0xc6:
            dbgMenuFightTrainerDataStatusInputDigit(0x13, 0x3E, 0, 200, -200);
            break;
        case 0xc7:
            dbgMenuFightTrainerDataStatusInputDigit(0x14, 0x3E, 0, 200, -200);
            break;
        case 0xc8:
            dbgMenuFightTrainerDataStatusInputDigit(0x15, 0x3E, 0, 200, -200);
            break;
        case 0xc9:
            dbgMenuFightTrainerDataStatusInputDigit(0x16, 0x3E, 0, 200, -200);
            break;
        case 0xca:
            dbgMenuFightTrainerDataStatusInputDigit(0x17, 0x3E, 0, 200, -200);
            break;
        case 0xcb:
            dbgMenuFightTrainerDataStatusInputDigit(0x18, 0x3E, 0, 200, -200);
            break;
        }
    }
    menuCloseCustom(0x1C, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerPokemonPartDataEditSub(u16 id) {
    DbgTrainerPokemonPart backup;
    DbgTrainerPokemonPart* data;
    s32 result;

    if (id == 0) {
        return 1;
    }
    data = (DbgTrainerPokemonPart*)fightTrainerPokemonPartDataBiosGetPtr(id);
    backup = *data;
    for (;;) {
        result = menuOpenCustom(0x1F, 0, 0, 0, 1, 1, id);
        if (result == -1) {
            menuCloseCustom(0x1F, 0, 1);
            *data = backup;
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x1F)) {
        case 0xfc:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x1, 0x64, 0);
            break;
        case 0xfd:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x2, 0x64, 0);
            break;
        case 0xfe:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x3, 0x64, 0);
            break;
        case 0xff:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x4, 0x64, 0);
            break;
        case 0x100:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x5, 0x64, 0);
            break;
        case 0x101:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x6, 0x64, 0);
            break;
        case 0x102:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x7, 0x64, 0);
            break;
        case 0x103:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x8, 0x64, 0);
            break;
        case 0x104:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0x9, 0x64, 0);
            break;
        case 0x105:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0xa, 0x64, 0);
            break;
        case 0x108:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0xC, 0xd, 0x64, 0);
            break;
        }
    }
    menuCloseCustom(0x1F, 0, 1);
    return 1;
}

s32 dbgMenuFightTrainerAiDataEditSub(u16 id) {
    DbgTrainerAi backup;
    DbgTrainerAi* data;
    s32 result;
    s32 type;

    if (id == 0) {
        return 1;
    }
    data = (DbgTrainerAi*)fightTrainerAiDataBiosGetPtr(id);
    backup = *data;
    for (;;) {
        result = menuOpenCustom(0x18, 0, 0, 0, 1, 1, id);
        if (result == -1) {
            menuCloseCustom(0x18, 0, 1);
            *data = backup;
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x18)) {
        case 0x8e:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x25, 0, 0x64, 0);
            break;
        case 0x8f:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x26, 0, 0x64, 0);
            break;
        case 0x90:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x27, 0, 0x64, 0);
            break;
        case 0x91:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x2c, 0, 0x64, 0);
            break;
        case 0x92:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x37, 0, 0x64, 0);
            break;
        case 0x93:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x1f);
            break;
        case 0x94:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x20);
            break;
        case 0x95:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x23);
            break;
        case 0x96:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x24);
            break;
        case 0x97:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x28);
            break;
        case 0x98:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x29);
            break;
        case 0x99:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x2a);
            break;
        case 0x9a:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x2b);
            break;
        case 0x9b:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x2d);
            break;
        case 0x9c:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x30);
            break;
        case 0x9d:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x31);
            break;
        case 0x9e:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x32);
            break;
        case 0x9f:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x33);
            break;
        case 0xa0:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x34);
            break;
        case 0xa1:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x36);
            break;
        case 0xa2:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x35, 0, 0x64, 0);
            break;
        case 0xa3:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x2e, 0, 0x54, 0);
            break;
        case 0xa4:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x2f, 0, 0x54, 0);
            break;
        case 0xa6:
            type = dbgMenuFightGetZokuseiDataId(fightTrainerGetStatus(0, id, 0x39, 0));
            if (type >= 0) {
                fightTrainerSetStatus(0, id, 0x39, 0, type);
            }
            break;
        case 0xa7:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3a, 0, 0x64, 0);
            break;
        case 0xa8:
            type = dbgMenuFightGetZokuseiDataId(fightTrainerGetStatus(0, id, 0x39, 1));
            if (type >= 0) {
                fightTrainerSetStatus(0, id, 0x39, 1, type);
            }
            break;
        case 0xa9:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3a, 1, 0x64, 0);
            break;
        case 0xab:
            type = dbgMenuFightGetWazaTypeId(fightTrainerGetStatus(0, id, 0x3b, 0));
            if (type >= 0) {
                fightTrainerSetStatus(0, id, 0x3b, 0, type);
            }
            break;
        case 0xac:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3c, 0, 0x64, 0);
            break;
        case 0xad:
            type = dbgMenuFightGetWazaTypeId(fightTrainerGetStatus(0, id, 0x3b, 1));
            if (type >= 0) {
                fightTrainerSetStatus(0, id, 0x3b, 1, type);
            }
            break;
        case 0xae:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x3c, 1, 0x64, 0);
            break;
        case 0xaf:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x21);
            break;
        case 0xb0:
            dbgMenuFightTrainerDataStatusInputFlag(id, 0x22);
            break;
        case 0xb1:
            dbgMenuFightTrainerDataStatusInputDigit(id, 0x38, 1, 0x64, 0);
            break;
        }
    }
    menuCloseCustom(0x18, 0, 1);
    return 1;
}

void dbgMenuFightTrainerDataStatusInputDigit(u16 a, s32 b, s32 c, s32 max, s32 min) {
    s32 value;

    if (menuSubOpenNumberInput(fightTrainerGetStatus(0, a, b, c), &value, 0, 0x32, 0x32, 0) == 1) {
        if (value > max) {
            value = max;
        }
        if (value < min) {
            value = min;
        }
        fightTrainerSetStatus(0, a, b, c, value);
    }
    menuSubCloseNumberInput();
}

void dbgMenuFightTrainerDataStatusInputFlag(u16 a, s32 b) {
    s8 answer = menuSubOpenYesNo(0x7F, -1, -1, fightTrainerGetStatus(0, a, b, 0) == 0);

    if (answer == 0) {
        fightTrainerSetStatus(0, a, b, 0, 1);
    } else if (answer == 1) {
        fightTrainerSetStatus(0, a, b, 0, 0);
    }
}
