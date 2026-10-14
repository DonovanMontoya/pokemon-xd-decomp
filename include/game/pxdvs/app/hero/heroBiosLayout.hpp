#ifndef GAME_PXDVS_APP_HERO_HERO_BIOS_LAYOUT_HPP
#define GAME_PXDVS_APP_HERO_HERO_BIOS_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct HeroBiosLayout {
    u8 prefix[0x2c]; u32 rnd; u8 toSex[0x8e0-0x30];
    u8 sex, home; u8 pad8e2[2]; u32 pokedoru, pokecoupon, pokecouponAll;
    u8 badges[8]; u8 hizukiFlag;
    u8 pad8f9[0x922-0x8f9]; u8 hizukiName[0x16];
    u8 rest[0x978-0x938];
};
typedef char HeroLayoutAssert_rnd[(offsetof(HeroBiosLayout, rnd)==0x2c) ? 1 : -1];
typedef char HeroLayoutAssert_sex[(offsetof(HeroBiosLayout, sex)==0x8e0) ? 1 : -1];
typedef char HeroLayoutAssert_home[(offsetof(HeroBiosLayout, home)==0x8e1) ? 1 : -1];
typedef char HeroLayoutAssert_pokedoru[(offsetof(HeroBiosLayout, pokedoru)==0x8e4) ? 1 : -1];
typedef char HeroLayoutAssert_pokecoupon[(offsetof(HeroBiosLayout, pokecoupon)==0x8e8) ? 1 : -1];
typedef char HeroLayoutAssert_pokecouponAll[(offsetof(HeroBiosLayout, pokecouponAll)==0x8ec) ? 1 : -1];
typedef char HeroLayoutAssert_badges[(offsetof(HeroBiosLayout, badges)==0x8f0) ? 1 : -1];
typedef char HeroLayoutAssert_hizukiFlag[(offsetof(HeroBiosLayout, hizukiFlag)==0x8f8) ? 1 : -1];
typedef char HeroLayoutAssert_hizukiName[(offsetof(HeroBiosLayout, hizukiName)==0x922) ? 1 : -1];
typedef char HeroLayoutAssert_HeroBiosLayout_size[(sizeof(HeroBiosLayout)==0x978) ? 1 : -1];
#endif
