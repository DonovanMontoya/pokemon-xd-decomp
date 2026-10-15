#include <global.h>

struct GamedataAttest { u8 ver; u8 gen; u8 area; u8 langarea; };
extern "C" {
void gamedataAttestBiosSetLangareaId(GamedataAttest* p, s8 v) { if (p) p->langarea = v; }
void gamedataAttestBiosSetAreaId(GamedataAttest* p, s8 v) { if (p) p->area = v; }
void gamedataAttestBiosSetGenId(GamedataAttest* p, s8 v) { if (p) p->gen = v; }
void gamedataAttestBiosSetVerId(s8* p, s8 v) { if (p) *p = v; }
u8 gamedataAttestBiosGetLangareaId(GamedataAttest* p) { if (p == 0) return 0; return p->langarea; }
u8 gamedataAttestBiosGetAreaId(GamedataAttest* p) { if (p == 0) return 0; return p->area; }
u8 gamedataAttestBiosGetGenId(GamedataAttest* p) { if (p == 0) return 0; return p->gen; }
u8 gamedataAttestBiosGetVerId(u8* p) { if (p == 0) return 0; return *p; }
void gamedataAttestBiosCopy(GamedataAttest* d, GamedataAttest* s) { if (d && s) { d->ver=s->ver; d->gen=s->gen; d->area=s->area; d->langarea=s->langarea; } }
void gamedataBiosSetGamedataAtttestPtr(GamedataAttest* d, GamedataAttest* s) { if (d == 0) return; if (s != 0) { d->ver=s->ver; d->gen=s->gen; d->area=s->area; d->langarea=s->langarea; } }
GamedataAttest* gamedataBiosGetGamedataAtttestPtr(GamedataAttest* p) { if (p != 0) return p; return 0; }
}
