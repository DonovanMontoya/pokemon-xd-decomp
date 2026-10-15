#include <global.h>
struct RibbonData {u32 flags,message;};
extern "C" {extern u32* ribbon_data_number;extern RibbonData* ribbon_data;
u32 getRibbonMsgID(u32 index){if(*ribbon_data_number<=index)return 0;return ribbon_data[index].message;}
u32 getRibbonCnt(){return *ribbon_data_number;}
}
