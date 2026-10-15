#include <global.h>
#pragma force_active on
struct TikeiRecord {u8 type;u8 reserved;u16 effect,move;u8 reserved6[6];};
extern "C" {extern TikeiRecord tikei_data[];extern u32 tikei_data_number;}
static inline TikeiRecord* getTikei(u16 id){if(id>tikei_data_number)return 0;return &tikei_data[id];}
extern "C" u16 tikeiDataBiosGetWazaId(u16 id){TikeiRecord* data=getTikei(id);if(data==0)return 0;return data->move;}
extern "C" u8 tikeiDataBiosGetZokuseiDataId(u16 id){TikeiRecord* data=getTikei(id);if(data==0)return 0;return data->type;}
extern "C" u16 tikeiDataBiosGetFightKoukaId(u16 id){TikeiRecord* data=getTikei(id);if(data==0)return 0;return data->effect;}

#pragma force_active reset
