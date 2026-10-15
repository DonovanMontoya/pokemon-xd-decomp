#ifndef FLOOR_SCRIPT_PRIVATE_HPP
#define FLOOR_SCRIPT_PRIVATE_HPP
#include <dolphin/types.h>
struct GSresID;
namespace GSscript {
struct tigaVariant {u16 type;u16 flags;union {s32 integer;GSresID *people;}value;void setInteger(s32);void setPeople(GSresID *p){type=0x23;value.people=p;}};
typedef char FloorScriptVariantSize[sizeof(tigaVariant)==8?1:-1];
class Tiga {public:u8 isMapping();int getNameToFuncId(const char *);GSresID *searchResID(unsigned long,unsigned long);u8 runParamsWait(int,tigaVariant*,int,tigaVariant*);s32 runParams(int,tigaVariant*,int,bool);s32 getResultValue(s32);s32 isRunningThread(s32);void blockThread(s32);void unblockThread(s32);};
}
GSscript::Tiga *floorGetCurentScript();GSscript::Tiga *floorGetCommonScript();
extern "C" int floorGetCurentScriptMode();
#endif
