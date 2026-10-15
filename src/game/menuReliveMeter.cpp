#include <dolphin/types.h>
class DarkPokemon {public:s32 getInitDarkPointDirect()const;s32 getDarkPointDirect()const;};
class Pokemon {public:bool isDarkPokemon()const;DarkPokemon *getDarkPokemon();};
class GSgfxLayer;
static f32 meterCount;
static f32 max_alpha=255.0f;
extern "C" {GSgfxLayer *GSgfxLayerFindByID(s32);f32 timeGetLastFrameSec();}
static void _menuDrawReliveMeterSubDpValue(long,long,long,long,long,long,u8,GSgfxLayer*);
static void _menuDrawReliveMeterSub(DarkPokemon *p,long x,long y,long width,long height,u8 alpha,GSgfxLayer *layer){s32 max=p->getInitDarkPointDirect();_menuDrawReliveMeterSubDpValue(max,p->getDarkPointDirect(),x,y,width,height,alpha,layer);}
extern "C" void menuDrawReliveMeter3(Pokemon *pokemon,u8 alpha,s32 x,s32 y,s32 width,s32 height,s32 layerID){GSgfxLayer *layer=GSgfxLayerFindByID(layerID);if(layer)_menuDrawReliveMeterSub(pokemon->getDarkPokemon(),x,y,width,height,alpha,layer);}
extern "C" void menuDrawReliveMeterByDarkPokemon(DarkPokemon *p,s32 x,s32 y,s32 width,s32 height,u8 alpha,s32 layerID){GSgfxLayer *layer=GSgfxLayerFindByID(layerID);if(layer)_menuDrawReliveMeterSub(p,x,y,width,height,alpha,layer);}
extern "C" void menuDrawReliveMeter(Pokemon *pokemon,s32 width,s32 height,s32 layerID){if(pokemon->isDarkPokemon()){GSgfxLayer *layer=GSgfxLayerFindByID(layerID);if(layer)_menuDrawReliveMeterSub(pokemon->getDarkPokemon(),0,0,width,height,255,layer);}}
extern "C" void menuDrawReliveUpdate(){meterCount+=timeGetLastFrameSec();}
