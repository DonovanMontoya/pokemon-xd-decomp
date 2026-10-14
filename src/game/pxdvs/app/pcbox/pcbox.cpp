#include <game/pxdvs/app/pcbox/pcboxPrivate.hpp>

s8 PCBOX::lastWatchBoxID;

PCBOX* PCBOX::getPointer() {
    return (PCBOX*)savedataGetStatus(0, 3);
}

static inline Pokemon* pokemonSlot(PCBOX* self, s8 box, s8 slot) {
    Pokemon* result;
    if (box < 0 || box >= 8) {
        result = 0;
    } else if (slot < 0 || slot >= 30) {
        result = 0;
    } else {
        result = &self->boxes[box].pokemon[slot];
    }
    return result;
}

Pokemon* PCBOX::getPokemon(s8 box, s8 slot) {
    PCBOX* self = this;
    if (self == 0) {
        self = getPointer();
    }
    return pokemonSlot(self, box, slot);
}

s32 PCBOX::setPokemon(Pokemon* src, s8 box, s8 slot) {
    PCBOX* self = this;
    Pokemon* dst;
    s32 ok;
    if (self == 0) {
        self = getPointer();
    }
    dst = pokemonSlot(self, box, slot);
    if (dst == 0) {
        ok = 0;
    } else {
        DarkPokemon* dark;
        memcpy(dst, src, sizeof(Pokemon));
        pokemonAllKaihuku(dst);
        dark = dst->getDarkPokemon();
        if (dark != 0) {
            dark->setPlace(place2, box);
        }
        ok = 1;
    }
    return ok != 0;
}

s8 PCBOX::getPokemonBoxNbEmptySlot(s8 box) {
    PCBOX* self = this;
    s8 slot;
    s8 used = 0;
    if (self == 0) {
        self = getPointer();
    }
    if (box < 0 || box >= 8) {
        used = -1;
    } else {
        for (slot = 0; slot < 30; slot++) {
            Pokemon* p = pokemonSlot(self, box, slot);
            if (p != 0 && pokemonCheckValid(p) != 0) {
                used++;
            }
        }
    }
    if (used < 0) {
        return -1;
    }
    return 30 - used;
}

s8 PCBOX::getPokemonBoxNbUsedSlot(s8 box) {
    PCBOX* self = this;
    int used = 0;
    s8 slot;
    if (self == 0) {
        self = getPointer();
    }
    if (box < 0 || box >= 8) {
        used = -1;
    } else {
        for (slot = 0; slot < 30; slot++) {
            Pokemon* p = pokemonSlot(self, box, slot);
            if (p != 0 && pokemonCheckValid(p) != 0) {
                used++;
            }
        }
    }
    return used;
}

s32 PCBOX::delPokemon(s8 box, s8 slot) {
    PCBOX* self = this;
    Pokemon* p;
    s32 ok;
    if (self == 0) {
        self = getPointer();
    }
    p = pokemonSlot(self, box, slot);
    if (p == 0) {
        ok = 0;
    } else if (pokemonCheckValid(p) == 0) {
        ok = 0;
    } else {
        pokemonInit((u32)p);
        ok = 1;
    }
    return ok != 0;
}

static inline void initBoxes(PCBOX* self) {
    s32 i;
    for (i = 0; i < 8; i++) {
        msgctrlSetValue(0x34, i + 1);
        GSmsgMakeGScharStr(&self->boxes[i], 9, 0x3B39);
        pokemonInitAry((u32)self->boxes[i].pokemon, 0x1E);
    }
    itemInitAry(self->items, 0xEB);
    self->lastItemSlot = 0;
}

void PCBOX::init() {
    PCBOX* self = this;
    if (self == 0) {
        self = getPointer();
    }
    initBoxes(self);
}

PCBOXItem* PCBOX::getItem(s16 idx) {
    PCBOX* self = this;
    if (self == 0) {
        self = getPointer();
    }
    if (idx < 0 || idx >= 0xEB) {
        return 0;
    }
    return &self->items[idx];
}

char16* PCBOX::getPokemonBoxName(s8 box) {
    PCBOX* self = this;
    if (self == 0) {
        self = getPointer();
    }
    if (box < 0 || box >= 8) {
        return 0;
    }
    return self->boxes[box].name;
}

extern "C" {

s32 pcboxGetNbItemSlot() {
    return 0xEB;
}

s32 pcboxGetNbPokemonBox() {
    return 8;
}

PCBOXItem* pcboxGetItem(PCBOX* pcbox, s16 idx) {
    return pcbox->getItem(idx);
}

char16* pcboxGetPokemonBoxName(PCBOX* pcbox, s8 box) {
    return pcbox->getPokemonBoxName(box);
}

void pcboxInit(PCBOX* pcbox) {
    pcbox->init();
}


s8 pcboxGetPokemonBoxNbEmptySlot(PCBOX* pcbox, s8 box) {
    return pcbox->getPokemonBoxNbEmptySlot(box);
}


void pcboxDebugPokemonSetupFull() {
    Pokemon pokemon;
    PCBOX* pcbox = PCBOX::getPointer();
    u16 n;
    int box;
    int slot;
    initBoxes(pcbox);
    PCBOX::getPointer();
    n = 0;
    box = 0;
    do {
        slot = 0;
        do {
            menuPocketDebugMakePokemonBySN(pokemon, n++, slot == 1, 0.5f);
            PCBOX::getPointer()->setPokemon(&pokemon, box, slot);
            slot++;
        } while (slot < 0x1E);
        box++;
    } while (box < 8);
}


void pcboxDebugPokemonSetup() {
    Pokemon pokemonA;
    Pokemon pokemonB;
    PCBOX* pcbox = PCBOX::getPointer();
    u16 n;
    int box;
    int slot;
    initBoxes(pcbox);
    PCBOX::getPointer();
    n = 0;
    box = 0;
    do {
        if (box == 7) {
            slot = 0;
            do {
                menuPocketDebugMakePokemonBySN(pokemonA, n++, false, 0.0f);
                PCBOX::getPointer()->setPokemon(&pokemonA, box, slot);
                slot++;
            } while (slot < 0x1E);
        } else {
            slot = 0;
            do {
                menuPocketDebugMakePokemonBySN(pokemonB, n++, (slot % 10) == 0, 0.1f);
                PCBOX::getPointer()->setPokemon(&pokemonB, box, slot);
                slot++;
            } while (slot < 3);
        }
        box++;
    } while (box < 8);
}

}
