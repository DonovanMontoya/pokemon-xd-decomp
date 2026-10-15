#include <global.h>
#pragma force_active on
struct TenkouRecord {u8 solar;u8 reserved[7];u32 initialMessage;u8 reservedC[12];};
extern "C" {extern TenkouRecord tenkou_data[];extern u32 tenkou_data_number;}
static inline TenkouRecord* getTenkou(u16 id){if(id>tenkou_data_number)return 0;return &tenkou_data[id];}
extern "C" u32 tenkouDataBiosGetFightInitMsgId(u16 id){TenkouRecord* data=getTenkou(id);if(data==0)return 0;return data->initialMessage;}
extern "C" u32 tenkouDataBiosGetSolarFlag(u16 id){TenkouRecord* data=getTenkou(id);if(data==0)return 0;return data->solar!=0;}

#pragma force_active reset
