#include <global.h>
class FIGHT_ENCOUNT {
public:
    u8 pad00[0x0a]; u8 addMode, addPlace, addID, swapMode; u16 swapDeck; u8 fightMode, trainerKind, destroyFlag, pad13; u32 roundNo; u8 pad18[4];
    void setDirtyFlag(bool); u8 getDirtyFlag() const;
    void setRoundNo(u32); u32 getRoundNo() const;
    void setDestroyFlag(u8); u8 getDestroyFlag() const;
    void setTrainerKind(u8); u8 getTrainerKind() const;
    void setFightMode(u8); u8 getFightMode() const;
    void setSwapDeckNO(u16); u16 getSwapDeckNO() const;
    void setSwapMode(u8); u8 getSwapMode() const;
    void setAddID(u8); u8 getAddID() const;
    void setAddPlace(u8); u8 getAddPlace() const;
    void setAddMode(u8); u8 getAddMode() const;
    void setMsg(u8,u16); u16 getMsg(u8) const;
    void setField(u16); u16 getField() const;
    void clear();
};
void FIGHT_ENCOUNT::setDirtyFlag(bool v){if(this)((u8*)this)[0x18]=v;}
u8 FIGHT_ENCOUNT::getDirtyFlag() const {if(this==0)return false;return *((u8*)this+0x18);}
void FIGHT_ENCOUNT::setRoundNo(u32 v){if(this)*(u32*)((u8*)this+0x14)=v;}
u32 FIGHT_ENCOUNT::getRoundNo() const {if(this==0)return 0;return *(u32*)((u8*)this+0x14);}
void FIGHT_ENCOUNT::setDestroyFlag(u8 v){if(this)((u8*)this)[0x12]=v;}
u8 FIGHT_ENCOUNT::getDestroyFlag() const {if(this==0)return 0;return ((u8*)this)[0x12];}
void FIGHT_ENCOUNT::setTrainerKind(u8 v){if(this)((u8*)this)[0x11]=v;}
u8 FIGHT_ENCOUNT::getTrainerKind() const {if(this==0)return 0;return ((u8*)this)[0x11];}
void FIGHT_ENCOUNT::setFightMode(u8 v){if(this)((u8*)this)[0x10]=v;}
u8 FIGHT_ENCOUNT::getFightMode() const {if(this==0)return 0;return ((u8*)this)[0x10];}
void FIGHT_ENCOUNT::setSwapDeckNO(u16 v){if(this)*(u16*)((u8*)this+0xe)=v;}
u16 FIGHT_ENCOUNT::getSwapDeckNO() const {if(this==0)return 0;return *(u16*)((u8*)this+0xe);}
void FIGHT_ENCOUNT::setSwapMode(u8 v){if(this)((u8*)this)[0xd]=v;}
u8 FIGHT_ENCOUNT::getSwapMode() const {if(this==0)return 0;return ((u8*)this)[0xd];}
void FIGHT_ENCOUNT::setAddID(u8 v){if(this)((u8*)this)[0xc]=v;}
u8 FIGHT_ENCOUNT::getAddID() const {if(this==0)return 0;return ((u8*)this)[0xc];}
void FIGHT_ENCOUNT::setAddPlace(u8 v){if(this)((u8*)this)[0xb]=v;}
u8 FIGHT_ENCOUNT::getAddPlace() const {if(this==0)return 0;return ((u8*)this)[0xb];}
void FIGHT_ENCOUNT::setAddMode(u8 v){if(this)((u8*)this)[0xa]=v;}
u8 FIGHT_ENCOUNT::getAddMode() const {if(this==0)return 0;return ((u8*)this)[0xa];}
void FIGHT_ENCOUNT::setMsg(u8 i,u16 v){if(this)*(u16*)((u8*)this+2+i*2)=v;}
u16 FIGHT_ENCOUNT::getMsg(u8 i) const {if(this==0)return 0;return *(u16*)((u8*)this+2+i*2);}
void FIGHT_ENCOUNT::setField(u16 v){if(this)*(u16*)this=v;}
u16 FIGHT_ENCOUNT::getField() const {if(this==0)return 0;return *(u16*)this;}
void FIGHT_ENCOUNT::clear(){((u8*)this)[0]=0;((u8*)this)[0xa]=0;((u8*)this)[0xb]=0;((u8*)this)[0xc]=0;((u8*)this)[0xd]=0;*(u16*)((u8*)this+0xe)=0;((u8*)this)[0x10]=0;((u8*)this)[0x11]=0;for(u8 i=0;i<4;i++)*(u16*)((u8*)this+2+i*2)=0;((u8*)this)[0x12]=0;*(u32*)((u8*)this+0x14)=0;((u8*)this)[0x18]=0;}
