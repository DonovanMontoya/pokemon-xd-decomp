#include <global.h>
struct TypeRecord {u8 kind,reserved1;u16 sprite,smallSprite,reserved6;u32 name;u16 matchup[18];};
typedef char TypeRecordSize[sizeof(TypeRecord)==0x30?1:-1];
extern "C" {
extern u32* zokusei_data_number;
extern TypeRecord* zokusei_data;
u16 zokuseiBiosGetSmallSpriteID(u16 id){if(id>=*zokusei_data_number)return 0;return zokusei_data[id].smallSprite;}
u16 zokuseiBiosGetSpriteID(u16 id){if(id>=*zokusei_data_number)return 0;return zokusei_data[id].sprite;}
u8 zokuseiBiosGetWazaKind(u16 id){if(id>=*zokusei_data_number)return 0;return zokusei_data[id].kind;}
u32 zokuseiBiosGetName(u16 id){if(id>=*zokusei_data_number)return 0;return zokusei_data[id].name;}
u16 zokuseiBiosGetWazaJoutai(u32 attack,u32 defense){if(attack>=*zokusei_data_number)return 0;if(defense>=18)return 0;return zokusei_data[attack].matchup[defense];}
}
