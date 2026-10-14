#include <game/pxdvs/app/fight/fightJoukenBiosLayout.hpp>
#pragma dont_inline on
extern "C" {
extern FightJoukenBiosRecord fight_jouken_data[];
extern u32 fight_jouken_data_number;
extern FightJoukenLinkBiosRecord fight_jouken_link_data[];
extern u32 fight_jouken_link_data_number;
FightJoukenLinkBiosRecord* fightJoukenLinkDataBiosGetDataPtr(u16);
FightJoukenBiosRecord* fightJoukenDataBiosGetDataPtr(u16);
FightJoukenValueBiosRecord* fightJoukenDataBiosGetValuePtr(u16,u16);
u16 fightJoukenLinkDataBiosGetNextLinkDataId(u16 id){FightJoukenLinkBiosRecord* p=fightJoukenLinkDataBiosGetDataPtr(id);if(p==0){return 0;}else{return p->nextLinkDataId;}}
u16 fightJoukenLinkDataBiosGetJoukenDataId(u16 id){FightJoukenLinkBiosRecord* p=fightJoukenLinkDataBiosGetDataPtr(id);if(p==0){return 0;}else{return p->joukenDataId;}}
u8 fightJoukenLinkDataBiosGetJoint(u16 id){FightJoukenLinkBiosRecord* p=fightJoukenLinkDataBiosGetDataPtr(id);if(p==0){return 0;}else{return p->joint;}}
FightJoukenLinkBiosRecord* fightJoukenLinkDataBiosGetDataPtr(u16 id){if(id>=fight_jouken_link_data_number)return 0;return &fight_jouken_link_data[id];}
s16 fightJoukenDataBiosGetValueWaru(u16 id,u16 side){FightJoukenValueBiosRecord* p=(FightJoukenValueBiosRecord*)fightJoukenDataBiosGetValuePtr(id,side);if(p==0){return 0;}else{return p->waru;}}
s16 fightJoukenDataBiosGetValueKake(u16 id,u16 side){FightJoukenValueBiosRecord* p=(FightJoukenValueBiosRecord*)fightJoukenDataBiosGetValuePtr(id,side);if(p==0){return 0;}else{return p->kake;}}
u8 fightJoukenDataBiosGetValueHoseiFlag(u16 id,u16 side){FightJoukenValueBiosRecord* p=(FightJoukenValueBiosRecord*)fightJoukenDataBiosGetValuePtr(id,side);if(p==0){return 0;}else{return p->hoseiFlag > 0u;}}
u16 fightJoukenDataBiosGetValueBuff(u16 id,u16 side){FightJoukenValueBiosRecord* p=(FightJoukenValueBiosRecord*)fightJoukenDataBiosGetValuePtr(id,side);if(p==0){return 0;}else{return p->buff;}}
u16 fightJoukenDataBiosGetValueTarget(u16 id,u16 side){FightJoukenValueBiosRecord* p=(FightJoukenValueBiosRecord*)fightJoukenDataBiosGetValuePtr(id,side);if(p==0){return 0;}else{return p->target;}}
u8 fightJoukenDataBiosGetValueKind(u16 id,u16 side){FightJoukenValueBiosRecord* p=(FightJoukenValueBiosRecord*)fightJoukenDataBiosGetValuePtr(id,side);if(p==0){return 0;}else{return p->kind;}}
u16 fightJoukenDataBiosGetLink(u16 id){FightJoukenBiosRecord* p=fightJoukenDataBiosGetDataPtr(id);if(p==0){return 0;}else{return p->link;}}
u8 fightJoukenDataBiosGetForm(u16 id){FightJoukenBiosRecord* p=fightJoukenDataBiosGetDataPtr(id);if(p==0){return 0;}else{return p->form;}}
FightJoukenValueBiosRecord* fightJoukenDataBiosGetValuePtr(u16 id,u16 side){FightJoukenBiosRecord* p=fightJoukenDataBiosGetDataPtr(id);if(p==0)return 0;if(side>=2)return 0;return &p->value[side];}
FightJoukenBiosRecord* fightJoukenDataBiosGetDataPtr(u16 id){if(id>=fight_jouken_data_number)return 0;return &fight_jouken_data[id];}
}
