#include <global.h>
struct UndertakerPlace {u16 unused,flagValue;u32 message;};
struct UndertakerData {u8 pad[0x18];u32 flag;u8 pad1c[0x18];UndertakerPlace places[7];};
extern "C" {extern UndertakerData* undertakerdata;u32 GSflagGet(u32);}
class underTakerBios {public: u32 getPlaceMsg();};
u32 underTakerBios::getPlaceMsg(){u32 value=GSflagGet(undertakerdata->flag);
if(undertakerdata->places[0].flagValue==value)return undertakerdata->places[0].message;
if(undertakerdata->places[1].flagValue==value)return undertakerdata->places[1].message;
if(undertakerdata->places[2].flagValue==value)return undertakerdata->places[2].message;
if(undertakerdata->places[3].flagValue==value)return undertakerdata->places[3].message;
if(undertakerdata->places[4].flagValue==value)return undertakerdata->places[4].message;
if(undertakerdata->places[5].flagValue==value)return undertakerdata->places[5].message;
if(undertakerdata->places[6].flagValue==value)return undertakerdata->places[6].message;
return 1;}
