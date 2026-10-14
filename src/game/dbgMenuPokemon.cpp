#include <game/menuSubLayout.hpp>

struct DbgMenuPokemonKeyInfo {
    u16 held;
    u16 unk2;
    u16 unk4;
    u16 trigger;
};

struct DbgMenuPokemonWindow {
    u8 reserved0[4];
    s32 menu;
    u8 reserved8[0x60];
    u32 pokemon;
    s32* out;
    u8 reserved70[0x18];
    s32 value;
    u8 reserved8C[0x12];
    s16 selected;
    u8 reservedA0[4];
    u8 finished;
};

extern "C" {
void* menuDataBiosGetPtr(s32);
s32 menuGetCursorItemID(s32);
u8 pokemonCheckValid(u32);
s32 pokemonGetStatus(s32, s32, s32, s32);
DbgMenuPokemonKeyInfo* windowGetKeyInfo(void);
}

extern "C" {

void dbgMenuPokemonEditButton(DbgMenuPokemonWindow* win) {
    u32 pokemon = win->pokemon;
    s32* out = win->out;
    if (win != 0) {
        u16 trigger = windowGetKeyInfo()->trigger;
        u16 held = windowGetKeyInfo()->held;
        s32 delta;
        s32 item;
        s32 up;
        s32 down;
        s32 shoulder;
        if ((trigger & 0x20) != 0) {
            win->value = -1;
            win->finished = 1;
            return;
        }
        if ((trigger & 0x10) != 0) {
            win->value = -2;
            win->finished = 1;
            return;
        }
        if (pokemon == 0) {
            win->value = -1;
            win->finished = 1;
            return;
        }
        up = trigger & 0x80;
        delta = 0;
        if (up != 0 && (held & 0x200) != 0 && (held & 0x400) != 0) {
            delta = 100;
        } else {
            down = trigger & 0x40;
            if (down != 0 && (held & 0x200) != 0 && (held & 0x400) != 0) {
                delta = -100;
            } else if (up != 0 && (held & 0x200) != 0) {
                delta = 10;
            } else if (down != 0 && (held & 0x200) != 0) {
                delta = -10;
            } else if (up != 0) {
                delta = 1;
            } else if (down != 0) {
                delta = -1;
            } else {
                shoulder = trigger & 0x100;
                if (shoulder != 0 && (held & 0x200) != 0) {
                    delta = 0xFFFF;
                } else if (shoulder != 0) {
                    delta = -0xFFFF;
                }
            }
        }
        if (pokemonCheckValid(pokemon) == 0) {
            item = 0x16;
            win->selected = 0;
        } else {
            menuDataBiosGetPtr(win->menu);
            item = menuGetCursorItemID(win->menu);
        }
        if (delta != 0) {
            if (out != 0) {
                *out = delta;
            }
            win->value = item;
            win->finished = 1;
        }
    }
}

static s32 dbgMenuPokemonEditSubGetTotalEffort(s32 pokemon) {
    s32 total = pokemonGetStatus(pokemon, 0, 0x8D, 0);
    total += pokemonGetStatus(pokemon, 0, 0x8E, 0);
    total += pokemonGetStatus(pokemon, 0, 0x8F, 0);
    total += pokemonGetStatus(pokemon, 0, 0x90, 0);
    total += pokemonGetStatus(pokemon, 0, 0x91, 0);
    total += pokemonGetStatus(pokemon, 0, 0x92, 0);
    return total;
}

}
