#include <dolphin/types.h>
struct TrainerFace {void *texture;u32 id;};
struct BattleStartWork {BattleStartWork(){}s32 first,status;u32 field8;TrainerFace faces[4];s32 loadIndex,faceCount;u8 busy,pad35[3];u8 pad38[0xEC];s32 sound;u32 field128;u16 name[12];u32 prefix;};
struct BattleOrder {s32 ids[6];};
struct OrderTables {BattleOrder row[6];};
static const OrderTables orderSingle={{{1,2,0,3,4,5},{2,0,1,3,4,5},{0,1,2,3,4,5},{0,1,2,3,4,5},{0,1,2,3,4,5},{0,1,2,3,4,5}}};
static const OrderTables orderDouble={{{0,1,2,3,4,5},{0,1,2,3,4,5},{0,1,2,3,4,5},{4,0,1,5,2,3},{0,1,2,3,4,5},{0,1,2,3,4,5}}};
static BattleOrder menuCBBattleStartDispWork[4];
BattleStartWork _menuCBBattleStartWork;
u32 menuCBBattleStartResID;
extern "C" {s32 toolentryTaisenGetBattleType();u16 toolentryTaisenGetPokemonNum(s32);u16 toolentryTaisenGetEntryPokemonNum(s32);s32 GSsndGetStatus(s32);void menuCBPokemonEntryTexWorkInit();void menuCBPokemonEntryLoadTex();u16 HSD_Rand();void soundOpenPlay(u32,u32,u32);u32 toolentryGetTrainerBicFaceResID(s32,s32);u32 toolentryGetTrainerSamllFaceResID(s32,s32);void *GSresGetResourceAllGroup(u32);void GSfsysReadIDEX(u32,u32,void(*)(s32,void*,s32),void*,u32);void GSfsysFree(u32);void GSresFreeGroup(u32);void GSresFreeResource(u32,u32);}
extern "C" {void *toolentryTaisenGetHeroPtr(s32);u16 *heroBiosGetNamePtr(void*);void GScharCpy(u16*,u16*);u16 *GSmsgGetGSchar(u32);u16 toolentryTaisenGetTrainerDataID(s32);u8 fightTrainerDB_GetKindDataId(u16);void *fightTrainerKindDataBiosGetPtr(u32);u32 fightTrainerKindDataBiosGetPrefixName(void*);}
static void _menuCBBattleStartSetIndex();
static void _menuCBBattleStartSetIndexDouble(s32 player,u16 count);
static void _menuCBBattleStartSetIndexSingle(s32 player,u16 count);
static void _menuCBBattleStartSetIndexMulti(s32 player,u16 count);
static void _menuCBBattleStartWorkInit();
static void _menuCBBattleStartSetTrainerData();
static u8 _menuCBBattleCheckTrainer(s32,s32 player);
static s32 _menuCBBattleStartGetTrainerFaceSize();
static void _menuCBBattleStartDispTrainerTexCallBack(s32,void *data,s32);
static void _menuCBBattleStartSetIndex(){s32 type=toolentryTaisenGetBattleType();u16 count[4]={6,6,6,6};_menuCBBattleStartWorkInit();switch(_menuCBBattleStartWork.status){case 0:for(s32 i=0;i<4;i++)count[i]=toolentryTaisenGetPokemonNum(i);break;case 1:for(s32 i=0;i<4;i++)count[i]=toolentryTaisenGetEntryPokemonNum(i);break;}switch(type){case 0:for(type=0;type<2;type++)_menuCBBattleStartSetIndexSingle(type,count[type]);break;case 1:for(type=0;type<2;type++)_menuCBBattleStartSetIndexDouble(type,count[type]);break;case 2:for(type=0;type<4;type++)_menuCBBattleStartSetIndexMulti(type,count[type]);break;}}
static void _menuCBBattleStartSetIndexDouble(s32 player,u16 count){BattleOrder *dest=&menuCBBattleStartDispWork[player];OrderTables table=orderDouble;s32 index=count-1;BattleOrder *src=&table.row[index];dest->ids[0]=src->ids[0];dest->ids[1]=src->ids[1];dest->ids[2]=src->ids[2];dest->ids[3]=src->ids[3];dest->ids[4]=src->ids[4];dest->ids[5]=src->ids[5];}
static void _menuCBBattleStartSetIndexSingle(s32 player,u16 count){BattleOrder *dest=&menuCBBattleStartDispWork[player];OrderTables table=orderSingle;s32 index=count-1;BattleOrder *src=&table.row[index];dest->ids[0]=src->ids[0];dest->ids[1]=src->ids[1];dest->ids[2]=src->ids[2];dest->ids[3]=src->ids[3];dest->ids[4]=src->ids[4];dest->ids[5]=src->ids[5];}
static void _menuCBBattleStartSetIndexMulti(s32 player,u16 count){u16 i=0;s32 *dest=menuCBBattleStartDispWork[player].ids;for(;i<count;i++)dest[i]=i;for(i=count;i<6;i++)dest[i]=count++;}
static void _menuCBBattleStartWorkInit(){for(s32 i=0;i<4;i++)for(s32 j=0;j<6;j++)menuCBBattleStartDispWork[i].ids[j]=j;}
extern "C" u32 menuCB_BattleStartSoundCheck(){return GSsndGetStatus(_menuCBBattleStartWork.sound)!=2;}
extern "C" void menuCBBattleStartSetStatus(s32 value){_menuCBBattleStartWork.status=value;}
extern "C" s32 menuCBBattleStartGetStatus(){return _menuCBBattleStartWork.status;}
static void _menuCBBattleStartSetTrainerData(){s32 type=toolentryTaisenGetBattleType();if(_menuCBBattleCheckTrainer(1,type)){u16 *name=heroBiosGetNamePtr(toolentryTaisenGetHeroPtr(1));u16 *dest=_menuCBBattleStartWork.name;if(dest)GScharCpy(dest,name);else GScharCpy(dest,GSmsgGetGSchar(1));_menuCBBattleStartWork.prefix=fightTrainerKindDataBiosGetPrefixName(fightTrainerKindDataBiosGetPtr(fightTrainerDB_GetKindDataId(toolentryTaisenGetTrainerDataID(1))));}}
static u8 _menuCBBattleCheckTrainer(s32,s32 player){u8 yes=1;s32 type=toolentryTaisenGetBattleType();if(player==2){if(type!=2)yes=0;}else if(type==2)yes=0;return yes;}
extern "C" void menuCBBattleStartInit(s32 value,s32 status){_menuCBBattleStartSetTrainerData();_menuCBBattleStartWork.first=value;_menuCBBattleStartWork.status=status;_menuCBBattleStartSetIndex();switch(status){case 0:menuCBPokemonEntryTexWorkInit();menuCBPokemonEntryLoadTex();switch(HSD_Rand()%3){case 0:_menuCBBattleStartWork.sound=0x3D2;break;case 1:_menuCBBattleStartWork.sound=0x3F5;break;case 2:_menuCBBattleStartWork.sound=0x3F6;break;case 3:default:_menuCBBattleStartWork.sound=0x3F7;break;}soundOpenPlay(_menuCBBattleStartWork.sound,0,255);break;case 1:menuCBPokemonEntryTexWorkInit();menuCBPokemonEntryLoadTex();_menuCBBattleStartWork.sound=0x5DB;soundOpenPlay(0x5DB,0,255);break;}}
extern "C" void menuCBBattleStartDispTrainerInit(){BattleStartWork *work=&_menuCBBattleStartWork;work->busy=0;work->loadIndex=0;if(_menuCBBattleStartGetTrainerFaceSize()==0)_menuCBBattleStartWork.faceCount=4;else _menuCBBattleStartWork.faceCount=2;for(s32 i=0;i<4;i++){work->faces[i].id=0;work->faces[i].texture=0;}}
extern "C" void menuCBBattleStartTrainerLoadTex(){_menuCBBattleStartGetTrainerFaceSize();_menuCBBattleStartWork.busy=1;_menuCBBattleStartDispTrainerTexCallBack(0,0,0);}
static s32 _menuCBBattleStartGetTrainerFaceSize(){return toolentryTaisenGetBattleType()!=2;}
static void _menuCBBattleStartDispTrainerTexCallBack(s32,void *data,s32){TrainerFace *f;u32 id;u32 group;s32 more=1;if(data){TrainerFace *f=(TrainerFace*)data;f->texture=GSresGetResourceAllGroup(f->id);}do{if(_menuCBBattleStartWork.loadIndex==_menuCBBattleStartWork.faceCount)more=0;else{if(_menuCBBattleStartGetTrainerFaceSize()){if(_menuCBBattleStartWork.loadIndex%2)id=toolentryGetTrainerBicFaceResID(1,0);else id=toolentryGetTrainerBicFaceResID(0,1);}else if(_menuCBBattleStartWork.loadIndex<2)id=toolentryGetTrainerSamllFaceResID(_menuCBBattleStartWork.loadIndex,1);else id=toolentryGetTrainerSamllFaceResID(_menuCBBattleStartWork.loadIndex,0);if(_menuCBBattleStartGetTrainerFaceSize())group=0x5C3;else group=0x5C4;f=&_menuCBBattleStartWork.faces[_menuCBBattleStartWork.loadIndex];f->id=id;f->texture=GSresGetResourceAllGroup(f->id);if(f->texture)_menuCBBattleStartWork.loadIndex++;else{GSfsysReadIDEX(group,id,_menuCBBattleStartDispTrainerTexCallBack,f,id);more=0;_menuCBBattleStartWork.loadIndex++;}}}while(more);}
extern "C" void menuCBBattleStartTrainerFaceFree(){TrainerFace *f;u32 group;if(_menuCBBattleStartGetTrainerFaceSize())group=0x5C3;else group=0x5C4;GSfsysFree(group);GSresFreeGroup(group);f=_menuCBBattleStartWork.faces;if(_menuCBBattleStartGetTrainerFaceSize()==0)_menuCBBattleStartWork.faceCount=4;else _menuCBBattleStartWork.faceCount=2;for(s32 i=0;i<_menuCBBattleStartWork.faceCount;f++,i++)GSresFreeResource(group,f->id);menuCBBattleStartDispTrainerInit();}
