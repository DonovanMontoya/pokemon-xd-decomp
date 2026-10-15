#include <dolphin/types.h>
#pragma dont_inline on
#include <game/gbaCommandPrivate.hpp>

extern "C" {
void *heroBiosGetPokemonPtr(void *, u16);
u16 pokemonBiosGetPokemonWazaDataId(void *, u16);
u32 wazaDataBiosGetPtr(u32);
void wazaDataBiosGetDoc(u32);
u16 *GSmsgGetGSchar();
s32 GBAMakeFromGSchar(u8 *, const u16 *, s32);
s32 gamedataGetStatus(s32, s32, s32);
void *memset(void *, int, unsigned long);
}

static s32 convline(u8 *dst, const u16 **src) {
    u16 text[0x51];
    s32 count = 0;
    while (**src != 0 && **src != 0xFFFF) {
        if (count < 0x50) text[count++] = **src;
        ++*src;
    }
    text[count] = 0;
    return GBAMakeFromGSchar(dst, text, gamedataGetStatus(0, 5, 0));
}

extern "C" s32 GetWazaDocGBA(u8 *dst, s32 id) {
    u32 data = wazaDataBiosGetPtr(id);
    memset(dst, 0, 0x50);
    if (data != 0) {
        wazaDataBiosGetDoc(data);
        const u16 *src = GSmsgGetGSchar();
        u8 *out = dst + convline(dst, &src);
        if (*src == 0xFFFF) {
            *out++ = 0xFE;
            src += 3;
            out += convline(out, &src);
        }
        *out = 0xFF;
    }
    return 0;
}

extern "C" s32 wazaconv(u32 trainer, GbaWazaText *dst) {
    u16 i = 0;
    do {
        void *pokemon = heroBiosGetPokemonPtr((void *)trainer, i);
        u16 j = 0;
        do {
            s32 result = GetWazaDocGBA(dst->text, pokemonBiosGetPokemonWazaDataId(pokemon, j));
            if (result != 0) return result;
            dst = (GbaWazaText *)((u8 *)dst + 0x50);
            ++j;
        } while (j < 4);
        ++i;
    } while (i < 6);
    return 0;
}
