#include <global.h>
extern "C" {
void *gamedatasaveBiosGetPtr(void*);void gamedatasaveBiosSetPtr(void*,void*);
s32 gamedatasaveBiosGetSavernd(void*);void gamedatasaveBiosSetSavernd(void*,s32);
s32 gamedatasaveBiosGetSavecount(void*);void gamedatasaveBiosSetSavecount(void*,s32);
s32 gamedatasaveBiosGetFloorid(void*);void gamedatasaveBiosSetFloorid(void*,s32);
f32 gamedatasaveBiosGetPlaytime(void*);void gamedatasaveBiosSetPlaytime(void*,f32);
s32 gamedatasaveBiosGetPrevfloorid(void*);void gamedatasaveBiosSetPrevfloorid(void*,s32);
u8 gamedatasaveBiosGetFloorposindex(void*);void gamedatasaveBiosSetFloorposindex(void*,u8);
u8 gamedatasaveBiosGetOptionNoVibration(void*);void gamedatasaveBiosSetOptionNoVibration(void*,u8);
u8 gamedatasaveBiosGetOptionAudio(void*);void gamedatasaveBiosSetOptionAudio(void*,u8);
u8 fn_801577C4(void*);void fn_801577B4(void*,u8);
s32 gamedatasaveBiosGetParChecksum(void*);void gamedatasaveBiosSetParChecksum(void*,s32);
s32 gamedatasaveBiosGetSysHeadChecksum(void*);void gamedatasaveBiosSetSysHeadChecksum(void*,s32);

void *savedataGetStatus(void *,u16); void *gamedataBiosGetGamedataAtttestPtr(void *); void gamedataBiosSetGamedataAtttestPtr(void*,void*);
u8 gamedataAttestBiosGetVerId(void*);u8 gamedataAttestBiosGetGenId(void*);u8 gamedataAttestBiosGetAreaId(void*);u8 gamedataAttestBiosGetLangareaId(void*);
void gamedataAttestBiosSetVerId(void*,u8);void gamedataAttestBiosSetGenId(void*,u8);void gamedataAttestBiosSetAreaId(void*,u8);void gamedataAttestBiosSetLangareaId(void*,u8);
void *gamedatasaveBiosGetplaydata(void*);void gamedatasaveInit(void*);s32 gamedataBiosGetZukanFlag(void*,u32);void gamedataBiosSetZukanFLag(void*,u16,s32);
void gamedataAttestInit(void*);void gamedataInit(void*);void gamedataAttestCreate(void*,u8,u8,u8,u8);
u32 gamedataGetStatus(void *data,u16 id) {
 if(id==0 || id>=7)return 0;
 if(data==0){data=savedataGetStatus(0,0);if(!data)return 0;data=savedataGetStatus(data,1);if(!data)return 0;}
 void *attest=gamedataBiosGetGamedataAtttestPtr(data);if(!attest)return 0;
 switch(id){case 1:return (u32)attest;case 2:return gamedataAttestBiosGetVerId(attest);case 3:return gamedataAttestBiosGetGenId(attest);case 4:return gamedataAttestBiosGetAreaId(attest);case 5:return gamedataAttestBiosGetLangareaId(attest);default:return 0;}
}
void gamedataSetStatus(void *data,u16 id,u32 value) {
 if(id!=0){if(id>=7)return;
 if(data==0){data=savedataGetStatus(0,0);if(!data)return;data=savedataGetStatus(data,1);if(!data)return;}
 void *attest=gamedataBiosGetGamedataAtttestPtr(data);if(!attest)return;
 switch(id){case 1:gamedataBiosSetGamedataAtttestPtr(data,(void*)value);return;case 2:gamedataAttestBiosSetVerId(attest,value);return;case 3:gamedataAttestBiosSetGenId(attest,value);return;case 4:gamedataAttestBiosSetAreaId(attest,value);return;case 5:gamedataAttestBiosSetLangareaId(attest,value);return;}
}}



s32 gamedataAttestCheckValid(void *data){if(!data)return 0;if((s32)gamedataGetStatus(data,2)==0)return 0;if((s32)gamedataGetStatus(data,3)==0)return 0;if((s32)gamedataGetStatus(data,4)==0)return 0;return (s32)gamedataGetStatus(data,5)!=0;}
void gamedataCreate(void *data,u8 ver,u8 gen,u8 area,u8 lang){if(data){gamedataInit(data);void *attest=(void*)gamedataGetStatus(data,1);if(attest)gamedataAttestCreate(attest,ver,gen,area,lang);}}
void gamedataAttestCreate(void *data,u8 ver,u8 gen,u8 area,u8 lang){if(data && ver && gen && area && lang){gamedataAttestInit(data);gamedataSetStatus(data,2,ver);gamedataSetStatus(data,3,gen);gamedataSetStatus(data,4,area);gamedataSetStatus(data,5,lang);}}
s32 gamedataBiosGetFlag(void *data,u16 id,u32 value){if(id==0 || id>=16)return 0;if(!data){data=savedataGetStatus(0,0);if(!data)return 0;data=savedataGetStatus(data,1);if(!data)return 0;}void *play=gamedatasaveBiosGetplaydata(data);if(!play)return 0;switch((s32)id){case 14:return gamedataBiosGetZukanFlag(play,value);default:return 0;}}
static void setFlag(void *data,u16 id,s32 value){if(!data){data=savedataGetStatus(0,0);if(!data)return;data=savedataGetStatus(data,1);if(!data)return;}void *play=gamedatasaveBiosGetplaydata(data);if(play)gamedataBiosSetZukanFLag(play,id,value);}
void gamedataInit(void *data){void *attest=(void*)gamedataGetStatus(data,1);if(attest){gamedataAttestInit(attest);gamedatasaveInit(data);for(u16 i=0;i<16;i++)setFlag(data,i,0);}}


void gamedataAttestInit(void *data){if(data){gamedataSetStatus(data,2,0);gamedataSetStatus(data,3,0);gamedataSetStatus(data,4,0);gamedataSetStatus(data,5,0);}}
void gamedatasaveSetStatus(void *data,u16 id,s32 value){if(id!=0){if(id>=16)return;if(!data){data=savedataGetStatus(0,0);if(!data)return;data=savedataGetStatus(data,1);if(!data)return;}void *save=gamedatasaveBiosGetPtr(data);if(!save)return;switch(id){
case 1:gamedatasaveBiosSetPtr(data,(void*)value);break;
case 2:gamedatasaveBiosSetSavernd(save,value);break;
case 4:gamedatasaveBiosSetSavecount(save,value);break;
case 5:gamedatasaveBiosSetFloorid(save,value);break;
case 6:gamedatasaveBiosSetPlaytime(save,value);break;
case 7:gamedatasaveBiosSetPrevfloorid(save,value);break;
case 8:gamedatasaveBiosSetFloorposindex(save,value);break;
case 9:gamedatasaveBiosSetOptionNoVibration(save,value);break;
case 10:gamedatasaveBiosSetOptionAudio(save,value);break;
case 12:gamedatasaveBiosSetParChecksum(save,value);break;
case 13:gamedatasaveBiosSetSysHeadChecksum(save,value);break;
case 11:fn_801577B4(save,value);break;
}}}

s32 gamedatasaveGetStatus(void *data,u16 id){void *savedata=0;if(id==0 || id>=16)return 0;if(!data){savedata=savedataGetStatus(0,0);if(!savedata)return 0;data=savedataGetStatus(savedata,1);if(!data)return 0;}void *save=gamedatasaveBiosGetPtr(data);if(!save)return 0;switch(id){case 1:return (s32)savedata;
case 2:return (s32)gamedatasaveBiosGetSavernd(save);
case 4:return (s32)gamedatasaveBiosGetSavecount(save);
case 5:return (s32)gamedatasaveBiosGetFloorid(save);
case 6:return (s32)gamedatasaveBiosGetPlaytime(save);
case 7:return (s32)gamedatasaveBiosGetPrevfloorid(save);
case 8:return (s32)gamedatasaveBiosGetFloorposindex(save);
case 9:return (s32)gamedatasaveBiosGetOptionNoVibration(save);
case 10:return (s32)gamedatasaveBiosGetOptionAudio(save);
case 12:return (s32)gamedatasaveBiosGetParChecksum(save);
case 13:return (s32)gamedatasaveBiosGetSysHeadChecksum(save);
case 11:return (s32)fn_801577C4(save);
default:return 0;}}
}
