#include <global.h>
extern "C" {
u8* savedataGetStatus(void*,u32);
void pokemonBiosSetEarthRibbon(void*,u8);
void pokemonBiosSetNationalRibbon(void*,u8);
u32 exribbonSetEarthRibbon(void* pokemon){pokemonBiosSetEarthRibbon(pokemon,1);u8* data=savedataGetStatus(0,16);if(!data[5])data[5]=45;return 1;}
u32 exribbonSetNarionalRibbon(void* pokemon){pokemonBiosSetNationalRibbon(pokemon,1);u8* data=savedataGetStatus(0,16);if(!data[4])data[4]=44;return 1;}
void exribbonSetNo(u32 index,u8 value){u8* data=savedataGetStatus(0,16);if(!data[index]&&value)data[index]=value;}
u8 exribbonGetNo(u32 index){u8* data=savedataGetStatus(0,16);return data[index];}
void exribbonInit(u8* data){if(!data)data=savedataGetStatus(0,16);for(int i=0;i<11;++i)*data++=0;}
}
