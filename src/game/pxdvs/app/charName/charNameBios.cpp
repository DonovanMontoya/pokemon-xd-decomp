#include <global.h>
#pragma force_active on
struct CharacterNameRecord{u16 heard;u16 reserved;u32 name;};
extern "C" {extern u32* char_name_number;extern CharacterNameRecord* char_name;void GSlogWrite(const char*,...);}
extern "C" u16 charNameBiosSearchIndex(u32 name){for(u16 i=0;i<*char_name_number;++i){if(name==char_name[i].name)return i;}return 0;}
static inline CharacterNameRecord* charNameBiosGetPtr(u16 id){if(id>=*char_name_number){GSlogWrite("\x5B\x25\x73\x5D\x3A\x20\x83\x65\x81\x5B\x83\x75\x83\x8B\x83\x43\x83\x93\x83\x66\x83\x62\x83\x4E\x83\x58\x82\xAA\x94\xCD\x88\xCD\x8A\x4F\x82\xC5\x82\xB7\x0A",__FUNCTION__);return 0;}return &char_name[id];}
extern "C" u32 charNameBiosGetNameID(u16 id){CharacterNameRecord* data=charNameBiosGetPtr(id);if(data==0)return 0;return data->name;}
extern "C" u16 charNameBiosGetHearFlag(u16 id){CharacterNameRecord* data=charNameBiosGetPtr(id);if(data==0)return 0;return data->heard;}

#pragma force_active reset
