#include <global.h>
extern "C" {
extern s32* savedataGetStatus(u32,u32);
extern s32 bingo_data; extern u32* bingo_data_number;
}
struct BINGO_DATA_dd_ { u8 raw[0xb8]; };
class bingo_bios {
public:
 static u8 mStaticBall; static u8 mStaticIdx[2]; static u8 mStaticNo; static u8 mStaticResult;
 u8 isClearPlus(u32); void setClear(u32); void setSelect(u32); u8 isSelect(u32); u8 isClear(u32);
 u16 getScore(BINGO_DATA_dd_*,u8); u8 getGridPos(BINGO_DATA_dd_*,u32); u8 getGridGrid(BINGO_DATA_dd_*,u32);
 u8 getPanelHoseiVal(BINGO_DATA_dd_*,u32); s32 getPanelHoseiKind(BINGO_DATA_dd_*,u32); u16 getPanelWaza(BINGO_DATA_dd_*,u32); u16 getPanelNo(BINGO_DATA_dd_*,u32); u8 getPanelTokusei(BINGO_DATA_dd_*,u32); u8 getPanelType(BINGO_DATA_dd_*,u32);
 u8 getBall(BINGO_DATA_dd_*); u8 getLevel(BINGO_DATA_dd_*); u8 getNo(BINGO_DATA_dd_*);
 static u8 getStaticIdx(u8); static void setStaticIdx(u8,u8); static u8 getStaticResult(); static void setStaticResult(u8); static void decStaticBall(); static u8 getStaticBall(); static void setStaticBall(u8); static s32 getStaticSheet(); static void setStaticNo(u8);
};
u8 bingo_bios::mStaticBall; u8 bingo_bios::mStaticIdx[2]; u8 bingo_bios::mStaticNo; u8 bingo_bios::mStaticResult;
u8 bingo_bios::isClearPlus(u32 i){if(i>=*bingo_data_number)return 0;s32* p=savedataGetStatus(0,0x1b);return (u8)((p[1]&(1<<i))!=0);}
void bingo_bios::setClear(u32 i){if(i<*bingo_data_number){s32* p=savedataGetStatus(0,0x1b);*p|=1<<(i*2);}}
void bingo_bios::setSelect(u32 i){s32* p=savedataGetStatus(0,0x1b);*p|=2<<(i*2);}
u8 bingo_bios::isSelect(u32 i){if(i>=*bingo_data_number)return 0;return (u8)((*savedataGetStatus(0,0x1b)&(2<<(i*2)))!=0);}
u8 bingo_bios::isClear(u32 i){if(i>=*bingo_data_number)return 0;return (u8)((*savedataGetStatus(0,0x1b)&(1<<(i*2)))!=0);}
u16 bingo_bios::getScore(BINGO_DATA_dd_* p,u8 i){if(i>=10)return 0;return *(u16*)(p->raw+0x10+i*2);}
u8 bingo_bios::getGridPos(BINGO_DATA_dd_* p,u32 i){if(i>=3)return 0;return p->raw[0xb1+i*2];}
u8 bingo_bios::getGridGrid(BINGO_DATA_dd_* p,u32 i){if(i>=3)return 0;return p->raw[0xb0+i*2];}
u8 bingo_bios::getPanelHoseiVal(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return p->raw[0x2c+i*0xa];}
s32 bingo_bios::getPanelHoseiKind(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return (*(u16*)(p->raw+0x2c+i*0xa)>>12)&15;}
u16 bingo_bios::getPanelWaza(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return *(u16*)(p->raw+0x2a+i*0xa);}
u16 bingo_bios::getPanelNo(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return *(u16*)(p->raw+0x28+i*0xa);}
u8 bingo_bios::getPanelTokusei(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return p->raw[0x25+i*0xa];}
u8 bingo_bios::getPanelType(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return p->raw[0x24+i*0xa];}
u8 bingo_bios::getBall(BINGO_DATA_dd_* p){if(p)return p->raw[5];return 0;}
u8 bingo_bios::getLevel(BINGO_DATA_dd_* p){if(p)return p->raw[3];return 0;}
u8 bingo_bios::getNo(BINGO_DATA_dd_* p){if(p)return p->raw[0];return 0;}
u8 bingo_bios::getStaticIdx(u8 i){if(i>=2)return 0;return mStaticIdx[i];}
void bingo_bios::setStaticIdx(u8 a,u8 b){mStaticIdx[0]=a;mStaticIdx[1]=b;}
u8 bingo_bios::getStaticResult(){return mStaticResult;}
void bingo_bios::setStaticResult(u8 v){mStaticResult=v;}
void bingo_bios::decStaticBall(){if(mStaticBall!=0)mStaticBall-=1;}
u8 bingo_bios::getStaticBall(){return mStaticBall;}
void bingo_bios::setStaticBall(u8 v){mStaticBall=v;}
s32 bingo_bios::getStaticSheet(){if(*bingo_data_number<=mStaticNo)return 0;return bingo_data+mStaticNo*0xb8;}
void bingo_bios::setStaticNo(u8 v){mStaticNo=v;}
