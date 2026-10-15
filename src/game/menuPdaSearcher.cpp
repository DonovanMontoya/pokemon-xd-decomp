#include <game/menuPcBoxPokemonLayout.hpp>
s32 _esaMeterIndex0[10]={0x198,0x199,0x19A,0x19B,0x19C,0x19D,0x19E,0x19F,0x1A0,0x1A1};
s32 _esaMeterIndex1[10]={0x1A2,0x1A3,0x1A4,0x1A7,0x1A5,0x1A6,0x1A8,0x1A9,0x1AA,0x1AB};
s32 _esaMeterIndex2[10]={0x1AC,0x1AD,0x1AE,0x1AF,0x1B0,0x1B1,0x1B2,0x1B3,0x1B4,0x1B5};
s32 *_esaMeterIndex[3]={_esaMeterIndex0,_esaMeterIndex1,_esaMeterIndex2};
static f32 _esaTimer[3];
extern u32 *esabadata_number;extern u8 *worldmapXD_data;
extern "C" {s32 GSflagGet(u32);u32 GSmsgGetRect(u32);void GSmsgPrintRect(s32,s16,s16,s16,s16,u32,u32);s32 esabaGetDigestRate();s32 esabaGetEsaNum(u16);void menuClose(s32);void menuCloseSync(s32,s32);s32 menuOpen(s32,s32);f32 timeGetLastFrameSec();void winSeqSetMenu(s32,s32);void winSpriteSetDisp(tagSPRITE_WORK*,s32);u16 *windowGetKeyInfo();f64 cos(f64);}
static f32 _gettLastTime(){return timeGetLastFrameSec();}
static void _menuClose(s32 id){menuClose(id);menuCloseSync(id,1);}
static void _esaMonInit(){for(u32 i=0;i<*esabadata_number;i++)_esaTimer[i]=0.0f;}
static s32 _getWorldMapFlag(u16 index){u16 table[3]={15,16,17};if(index>2)return 0;return GSflagGet(*(u32*)(worldmapXD_data+table[index]*0x24+4))!=0;}
static void _updateTimer(u16 index){f32 rate=esabaGetDigestRate();_esaTimer[index]+=(3.1415927f*(2.0f*_gettLastTime()))/(rate/100.0f);f32 time=_esaTimer[index];if(time>6.2831855f)_esaTimer[index]=time-6.2831855f;}
static void _animMojiCursor(tagWINDOW_WORK *w,tagSPRITE_WORK *s,u16 index){f32 alpha=255.0f*(((f32)cos(_esaTimer[index])+1.0f)/2.0f);if(alpha>=255.0f)alpha=255.0f;((u8*)s)[0x67]=(w->alpha*(u8)(s32)alpha)/255;}
static void _esaPrintMsg(tagWINDOW_WORK *w,tagSPRITE_WORK *s,unsigned long msg){u8 alpha=w->alpha;s16 width=s->width;GSmsgPrintRect(w->layer,(s16)((u32)(width-(GSmsgGetRect(msg)>>16))>>1),0,width,s->height,alpha|0xFFFFFF00,msg);}
static void _esaNumSet(tagSPRITE_WORK *s,u16 index){s32 *ids=_esaMeterIndex[index];s32 number=esabaGetEsaNum(index);if(number==0)winSpriteSetDisp(s,0);s32 match=0;for(;match<10;match++)if(s->id==ids[match])break;if(number>=match+1){winSpriteSetDisp(s,1);return;}winSpriteSetDisp(s,0);}
extern "C" {
s32 menuPdaSearcherCtrl(tagWINDOW_WORK *w){switch(w->phase){case 0:if(!w->step){winSeqSetMenu(w->menu,0x132);w->step=1;_esaMonInit();}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x136);w->step=1;}break;}return 0;}
void fn_80042BDC(tagWINDOW_WORK *w){if(w && (windowGetKeyInfo()[2]&0x20)){w->finished=1;w->cancelled=1;}}
void menuPdaSearcher(){menuOpen(0x77,0);do{}while(menuOpen(0x6D,1)>=0);_menuClose(0x6D);_menuClose(0x77);}
}
