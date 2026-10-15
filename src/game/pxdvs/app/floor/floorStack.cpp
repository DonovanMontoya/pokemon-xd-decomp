#include <global.h>
extern "C" {
extern void GSthreadUnblock(void); extern void GSthreadBlock(void); extern void GSthreadSetGroupID(s32);
extern u32 scriptCreateAppScript__Fv(void); extern void* memset(void*,int,u32);
}
class FloorStack {
public:
    u8 raw[0x224];
    void unblock(); void block(); void setGroupID(u32); void setFloorID(u32);
    s32 getObjective(); void clearFlag(); void setPopFlag(); void setPushFlag();
    s32 getScriptModule(); void makeScriptModule(); void setPushState(void*,u32);
};
class GSresID { public: u32 id, value; void set(u32,u32); void clear(); };
void FloorStack::unblock(){if(*(u32*)(raw+0x1c)!=0)GSthreadUnblock();}
void FloorStack::block(){if(*(u32*)(raw+0x1c)!=0)GSthreadBlock();}
void FloorStack::setGroupID(u32 v){*(u32*)(raw)=v;if(*(u32*)(raw+0x1c)!=0)GSthreadSetGroupID(v+0x2000);}
void FloorStack::setFloorID(u32 v){*(u32*)(raw+4)=v;*(u32*)raw=v+0x5001;}
s32 FloorStack::getObjective(){if(raw[0x10])return 1;if(raw[0x11])return 2;return 3;}
void FloorStack::clearFlag(){raw[0x10]=0;raw[0x11]=0;}
void FloorStack::setPopFlag(){raw[0x10]=0;raw[0x11]=1;}
void FloorStack::setPushFlag(){raw[0x10]=1;raw[0x11]=0;}
s32 FloorStack::getScriptModule(){return *(s32*)(raw+0x14);}
void FloorStack::makeScriptModule(){if(*(u32*)(raw+0x14)==0)*(u32*)(raw+0x14)=scriptCreateAppScript__Fv();}
void FloorStack::setPushState(void* p,u32 n){*(u32*)(raw+8)=(u32)p;*(u32*)(raw+0xc)=n;}
void GSresID::set(u32 a,u32 b){id=a;value=b;}
void GSresID::clear(){id=0;value=0;}
