#include <global.h>
extern "C" {
extern u8 kouka_data[]; extern u32 kouka_data_number;
extern u8 kouka_link_data[]; extern u32 kouka_link_data_number;
u16 koukaLinkDataBiosGetKouka(u32 id,u32 index){if(id>kouka_link_data_number||index>8)return 0;return *(u16*)(kouka_link_data+id*0x10+index*2);}
u16 koukaDataBiosGetLink(u32 id){if(id>kouka_data_number)return 0;return *(u16*)(kouka_data+id*0xa+4);}
s16 koukaDataBiosGetValue(u32 id,u32 index){if(id>kouka_data_number||index>2)return 0;return *(s16*)(kouka_data+id*0xa+6+index*2);}
u8 koukaDataBiosGetVar(u32 id){if(id>kouka_data_number)return 0;return *(kouka_data+id*0xa+1);}
u16 koukaDataBiosGetStatus(u32 id){if(id>kouka_data_number)return 0;return *(u16*)(kouka_data+id*0xa+2);}
u8 koukaDataBiosGetStatusKind(u32 id){if(id>kouka_data_number)return 0;return kouka_data[id*0xa];}
}
