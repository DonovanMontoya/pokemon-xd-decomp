#include <game/pxdvs/app/floor/floorScriptPrivate.hpp>
static s32 _floorScriputResult;
extern "C" {
int floorGetScriptMode(int id){if((id&0xFFFF0000)==0x05960000)return 2;if(floorGetCurentScriptMode()==1)return 3;return 0;}
s32 floorExecScriptIntegerThread(int,s32,s32,s32,s32);
s32 floorExecScriptInteger(int,s32,s32,s32,s32);
s32 floorExecScriptIntegerByNameThread(const char *name,s32 a,s32 b,s32 c,s32 d){GSscript::Tiga *p=floorGetCurentScript();if(!p)return 0;if(!p->isMapping())return 0;int id=p->getNameToFuncId(name);if(id)return floorExecScriptIntegerThread(id,a,b,c,d);return 0;}
u8 floorExecScriptIntegerByName(const char *name,s32 a,s32 b,s32 c,s32 d){GSscript::Tiga *p=floorGetCurentScript();if(!p)return 0;if(!p->isMapping())return 0;int id=p->getNameToFuncId(name);if(id)return floorExecScriptInteger(id,a,b,c,d);return 0;}
s32 floorExecScriptRes(int id,u32 group,u32 res){GSscript::tigaVariant v;if(!floorGetCurentScript())return 0;int mode=floorGetScriptMode(id);GSresID *p=floorGetCurentScript()->searchResID(group,res);if(!p)return 0;v.setPeople(p);s32 result;if(mode==2){result=floorGetCommonScript()->runParamsWait(id,&v,1,0);_floorScriputResult=floorGetCommonScript()->getResultValue(result);}else{result=floorGetCurentScript()->runParamsWait(id,&v,1,0);_floorScriputResult=floorGetCurentScript()->getResultValue(result);}return result;}
s32 floorExecScriptResThread(int id,u32 group,u32 res){GSscript::tigaVariant v;if(!floorGetCurentScript())return 0;int mode=floorGetScriptMode(id);GSresID *p=floorGetCurentScript()->searchResID(group,res);if(!p)return 0;v.setPeople(p);if(mode==2)return floorGetCommonScript()->runParams(id,&v,1,true);return floorGetCurentScript()->runParams(id,&v,1,true);}
s32 floorGetScriptResult(){return _floorScriputResult;}
s32 floorExecScriptInteger(int id,s32 a,s32 b,s32 c,s32 d){GSscript::tigaVariant v[4];if(!floorGetCurentScript())return 0;int mode=floorGetScriptMode(id);v[0].setInteger(a);v[1].setInteger(b);v[2].setInteger(c);v[3].setInteger(d);s32 result;if(mode==2){result=floorGetCommonScript()->runParamsWait(id,v,4,0);_floorScriputResult=floorGetCommonScript()->getResultValue(result);}else{result=floorGetCurentScript()->runParamsWait(id,v,4,0);_floorScriputResult=floorGetCurentScript()->getResultValue(result);}return result;}
s32 floorExecScriptIntegerThread(int id,s32 a,s32 b,s32 c,s32 d){GSscript::tigaVariant v[4];int mode=floorGetScriptMode(id);if(!floorGetCurentScript())return 0;v[0].setInteger(a);v[1].setInteger(b);v[2].setInteger(c);v[3].setInteger(d);if(mode==2)return floorGetCommonScript()->runParams(id,v,4,true);return floorGetCurentScript()->runParams(id,v,4,true);}
s32 floorIsRunningThread(s32 id){GSscript::Tiga *p=floorGetCurentScript();if(p)return p->isRunningThread(id);return 0;}
void floorBlockScriptThread(s32 id){if(floorGetCurentScript())floorGetCurentScript()->blockThread(id);}
void floorUnblockScriptThread(s32 id){if(floorGetCurentScript())floorGetCurentScript()->unblockThread(id);}
}
