#include <dolphin/types.h>
enum darkPokemonWhere {WhereNone,WhereParty,WhereBox,WhereOther};
struct DarkPokemon {
 unsigned int reservedFlags:14;unsigned int where:3;unsigned int restFlags:15;
 u8 pad4[13];u8 slot;u8 pad12[18];s32 darkPoint;u8 pad28[32];
 void setPlace(darkPokemonWhere,u8);f32 getDarkPoint() const;void setDarkPoint(f32);
};
typedef char DarkPokemonSize[sizeof(DarkPokemon)==0x48?1:-1];
class DeckDarkPokemon {public:u8 isScenarioPokemon() const;};
class darkpokemonIterateListener {public:virtual u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon*)=0;};
extern "C" {
DarkPokemon *savedataGetStatus(int,int);void deckInitDarkPokemon(DarkPokemon*);DeckDarkPokemon *deckGetDeckDarkPokemon(u32);u32 deckGetDarkPokemonSize();
DarkPokemon *darkPokemonGetDarkPokemon(u32 index){DarkPokemon *p=savedataGetStatus(0,15);if(index<128)return p+index;return 0;}
void darkpokemonValInit(){deckInitDarkPokemon(savedataGetStatus(0,15));}
}
u8 darkpokemonScenarioPokemonIterate(darkpokemonIterateListener *listener){if(!listener)return 0;for(u32 i=0;i<deckGetDarkPokemonSize();i++){DeckDarkPokemon *deck=deckGetDeckDarkPokemon(i);DarkPokemon *dark=darkPokemonGetDarkPokemon(i);if(deck && dark && deck->isScenarioPokemon()){if(!listener->exec(i,deck,dark))return 0;}}return 1;}
void DarkPokemon::setPlace(darkPokemonWhere p,u8 s){where=p;slot=0;if(p==WhereParty){if(s<=6)slot=s;}else if(p==WhereBox)slot=s;else if(p==WhereOther)slot=s;}
f32 DarkPokemon::getDarkPoint() const{return darkPoint;}
void DarkPokemon::setDarkPoint(f32 f){s32 point=f;f32 limited;if((f32)point<65535.0f)limited=point;else limited=65535.0f;darkPoint=limited;}
