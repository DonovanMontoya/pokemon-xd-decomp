#include <global.h>
#pragma force_active on
struct PortraitRecord{u8 flags;u8 reserved[3];u32 texture;};
extern "C" {extern u32* poke_face_number;extern PortraitRecord* poke_face;void GSlogWrite(const char*,...);}
static PortraitRecord* _menuFaceBiosGetPtr(u16);
bool menuFaceBiosGetRareFlag(u16 id){PortraitRecord* data=_menuFaceBiosGetPtr(id);if(data==0)return false;return ((data->flags>>7)&1)!=0;}
u32 menuFaceBiosGetTexID(u16 id){PortraitRecord* data=_menuFaceBiosGetPtr(id);if(data==0)return 0;return data->texture;}
static PortraitRecord* _menuFaceBiosGetPtr(u16 id){if(id>=*poke_face_number){GSlogWrite("\x5B\x25\x73\x5D\x20\x94\xCD\x88\xCD\x8A\x4F\x83\x41\x83\x4E\x83\x5A\x83\x58\x82\xC5\x82\xB7\x0A",__FUNCTION__);return 0;}return &poke_face[id];}

#pragma force_active reset
