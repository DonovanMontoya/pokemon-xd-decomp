#include <game/gbaCommandPrivate.hpp>
#include <libc/string.h>
#pragma dont_inline on
#pragma force_active on
static u32 _swap32(unsigned long value){return (value>>24)|(((value&0xff0000)>>8)|((value<<24)|((value&0xff00)<<8)));}
static u16 _swap16(unsigned short value){return (value<<8)|(value>>8);}
static s32 _SIProbe_Result[4]={0,0,0,0};
static u32 _SIProbe_Counter[4]={0,0,0,0};
static s32 _keyState[4];
static s32 _keyResult[4];
static u8 gba_SIProbe_ErrorCnt[4];
static u16 _keyCounter[4];
static u16 _keyPressed[4];
static u8 _needSelect;
static s32 _dummySelect(FightOutPokemon*,u16,u16){_needSelect=1;return 0;}
extern "C" {
void PKJB_ExchangeEnd(s32);
s32 PKJB_ExchangeIsPrepared(s32);
void PKJB_ExchangeStart(s32,GbaExchangePacket*);
s32 PKJB_EntryGetStatus(s32,u32*);
void PKJB_EntryRequest(s32,u32);
void PKJB_SendWazaText(s32,GbaWazaText*);
s32 PKJB_GetKey(s32,u16*);
s32 PKJB_IdleSend(s32);
u16 pokemonBiosGetPokemonDataId(void*);
u8 pokemonBiosGetTokuseiFlag(void*);
void pokemonBiosSetTokuseiFlag(void*,u8);
void gbaPokemonFromGC(void*,GbaPokemonRecord*);
s8 exribbonGetNo(s32);
void wazaconv(u32,GbaWazaText*);
u32 SIProbe(s32);
s32 menuCB_GetToolBattleModeFlag();
u8 menuCBBios_CurrentlyWorkingToolBattle();
s32 gbaCommandSetKeyState(s32,s32);
void gba_SIProbe_ErrorCntClear(s32 channel){
    if(channel==-1){gba_SIProbe_ErrorCnt[3]=0;gba_SIProbe_ErrorCnt[2]=0;gba_SIProbe_ErrorCnt[1]=0;gba_SIProbe_ErrorCnt[0]=0;}
    else gba_SIProbe_ErrorCnt[channel]=0;
}
s32 gba_SIProbe(s32 channel){return _SIProbe_Result[channel];}
void gbaCommandChangePokemonEnd(s32 channel){PKJB_ExchangeEnd(channel-1);}
s32 gbaCommandChangePokemonIsPrepared(s32 channel){
    s32 state=PKJB_ExchangeIsPrepared(channel-1);
    if(state<0)_keyCounter[channel-1]=0;
    else if(state==1 || state==2){if(++_keyCounter[channel-1]<=10)state=-1;}
    return state;
}
void gbaCommandChangePokemon(s32 channel,void* pokemon,u32 state,s32 id){
    GbaExchangePacket packet;
    packet.status=_swap32(state);
    packet.pokemonId=_swap32((id<<16)|pokemonBiosGetPokemonDataId(pokemon));
    if(pokemonBiosGetPokemonDataId(pokemon)==0x181)pokemonBiosSetTokuseiFlag(pokemon,!pokemonBiosGetTokuseiFlag(pokemon));
    gbaPokemonFromGC(pokemon,&packet.pokemon);
    s8* ribbon=packet.ribbons;
    memset(ribbon,0,sizeof(packet.ribbons));
    s32 i=0;
    do{*ribbon=exribbonGetNo(i);++ribbon;++i;}while(i<11);
    PKJB_ExchangeStart(channel-1,&packet);
    _keyCounter[channel-1]=0;
}
u32 gbaCommandGetGBAChangePokemon(u32 state){return state&0xffff;}
u32 gbaCommandGetWazaTarget(u32 state){return (state>>8)&0xff;}
u32 gbaCommandGetWazaDataId(u32 state){return state&0xff;}
u32 gbaCommandGetAction(u32 state){return state>>16;}
s32 gbaCommandEntryPokemon(u32 selection,u8* positions){
    positions[0]=selection&15;
    positions[1]=(selection>>4)&15;
    positions[2]=(selection>>8)&15;
    positions[3]=(selection>>12)&15;
    positions[4]=(selection>>16)&15;
    positions[5]=(selection>>20)&15;
    return 0;
}
s32 gbaCommandEntryResult(s32 channel,u32* result){
    u32 value;
    s32 index=channel-1;
    *result=0x02000000;
    s32 state=PKJB_EntryGetStatus(index,&value);
    if(state==1){u8* errors=&gba_SIProbe_ErrorCnt[channel-1];++*errors;if(*errors!=2)state=-1;}
    else gba_SIProbe_ErrorCntClear(index);
    if(state<0){value=0x02000000;}
    else {
        if(state!=0){*result=0x03000000;gbaCommandSetKeyState(channel,1);return state;}
        *result=_swap32(value);
        if((*result>>24)==0)gbaCommandSetKeyState(channel,1);
    }
    return 0;
}
void gbaCommandEntryRequest(s32 channel,u32 first,u32 second,u32 mode){PKJB_EntryRequest(channel-1,(second<<8)|((mode<<24)|first));}
void gbaCommandSendWazaText(s32 channel,u32 message){GbaWazaText text;wazaconv(message,&text);PKJB_SendWazaText(channel-1,&text);}
u16 gbaCommandKeyPressed(s32 channel){return _keyPressed[channel-1];}
bool gbaCommandIsConnected(s32 channel){bool connected=false;if(_keyState[channel-1]!=0 && _keyResult[channel-1]==0)connected=true;return connected;}
s32 gbaCommandSetKeyState(s32 channel,s32 state){
    s32 previous=_keyState[channel-1];
    _keyState[channel-1]=state;
    _keyResult[channel-1]=0;
    _keyCounter[channel-1]=0;
    _keyPressed[channel-1]=0;
    return previous;
}
s32 gbaCommandKeyRead(s32 channel){
    u16 key;
    if(channel==2){
        s32 i=0;
        do{
            u32 status=SIProbe(i);
            if(menuCB_GetToolBattleModeFlag()==1 && menuCBBios_CurrentlyWorkingToolBattle())status=0x40000;
            if(status==0x40000){_SIProbe_Result[i]=status;_SIProbe_Counter[i]=2;}
            else if(_SIProbe_Counter[i]==0)_SIProbe_Result[i]=status;
            else --_SIProbe_Counter[i];
            ++i;
        }while(i<4);
    }
    s32 result;
    switch(_keyState[channel-1]){
    case 1:
        result=PKJB_GetKey(channel-1,&key);
        if(result==0){_keyPressed[channel-1]=key;_keyCounter[channel-1]=0;}
        else if(result<=2 && ++_keyCounter[channel-1]<=10)result=0;
        else{_keyPressed[channel-1]=0;gbaCommandSetKeyState(channel,0);}
        break;
    case 3:
        result=PKJB_IdleSend(channel-1);
        if(result==0)_keyCounter[channel-1]=0;
        else if(result<=2 && ++_keyCounter[channel-1]<=10)result=0;
        else{_keyPressed[channel-1]=0;gbaCommandSetKeyState(channel,0);}
        _keyPressed[channel-1]=0;
        break;
    case 2:_keyPressed[channel-1]=0;result=0;break;
    default:_keyPressed[channel-1]=0;result=1;break;
    }
    _keyResult[channel-1]=result;
    return result;
}
}
#pragma force_active reset
