#include <global.h>
#pragma force_active on
struct FightEffectRecord {u16 condition,target,effect;};
extern "C" {
extern FightEffectRecord fight_kouka_data[];extern u32 fight_kouka_data_number;
u16 fightKoukaDataBiosGetKoukaDataId(FightEffectRecord* data){if(data==0)return 0;return data->effect;}
u16 fightKoukaDataBiosGetFightTargetDataId(FightEffectRecord* data){if(data==0)return 0;return data->target;}
u16 fightKoukaDataBiosGetFightJoukenDataId(FightEffectRecord* data){if(data==0)return 0;return data->condition;}
FightEffectRecord* fightKoukaDataBiosGetPtr(u16 id){if(id>=fight_kouka_data_number)return 0;return &fight_kouka_data[id];}
}

#pragma force_active reset
