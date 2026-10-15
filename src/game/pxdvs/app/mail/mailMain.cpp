#include <global.h>
struct MailReceiveWork { s32 active,timer; u32 sound; s32 unkC; };
static MailReceiveWork ReceiveWork;
extern "C" {
s32 mailGetReceiveNumber(s32); void mailAddMailbox(s32); s32 mailGetNbMailData(); void GSsndStop(u32,s32,s32); u16 mailGetSendRate(s32); u8 mailGetSendCntCond(s32); u16 mailGetSendCntCondValue(s32); u16 mailGetSendCnt(); u8 mailGetSendCondType(s32); u32 mailGetSendCondition(s32); u32 GSflagGet(u32); void floorExecScriptInteger(u32,s32,s32,s32,s32); s32 floorGetScriptResult(); f32 HSD_Randf(); void heroMoveAddStepCallback(void(*)(s32,s32,s32),s32);
static s32 chkMailSend__Fif(s32,f32); static void cbStep__Fl15FootStepCounterl(s32,s32,s32);
static inline void beginReceive() { if(ReceiveWork.active==0) {ReceiveWork.active=1; ReceiveWork.timer=0;ReceiveWork.sound=0;ReceiveWork.unkC=0;} }
void mailMainSendByScrpt(u16 id) {s32 mail=id; if(mailGetReceiveNumber(mail)<0) {mailAddMailbox(mail);beginReceive();} }
void mailMainSendAllMail() {s32 count=mailGetNbMailData(); s32 i; s32 sent=0;for(i=1;i<count;i++){if(chkMailSend__Fif(i,-1.0f)){mailAddMailbox(i);sent=1;}} if(sent)beginReceive();}
void mailMainReceiveTerminate(){ReceiveWork.timer=600;if(ReceiveWork.sound)GSsndStop(ReceiveWork.sound,0,0);}
void mailMainReceiveStart(){beginReceive();}

static s32 chkMailSend__Fif(s32 id,f32 random) {
 if(mailGetReceiveNumber(id)>=0)return 0;
 u16 rate=mailGetSendRate(id);if(rate==65535)return 0;
 if(random>= (0.015625f*(u32)rate)/1000.0f)return 0;
 u8 cond=mailGetSendCntCond(id);if(cond==255)return 0;
 u16 value=mailGetSendCntCondValue(id);if(value==65535)return 0;
 u16 count=mailGetSendCnt();s32 pass=0;
 switch(cond) {
 case 0:if(count==value)pass=1;break;
 case 1:if(count>value)pass=1;break;
 case 2:if(count<value)pass=1;break;
 case 3:if(count>=value)pass=1;break;
 case 4:if(count<=value)pass=1;break;
 case 5:if(count!=value)pass=1;break;
 case 6:pass=1;break;
 }
 if(pass==0)return 0;
 u8 type=mailGetSendCondType(id);if(type==255)return 0;
 s32 result=0;
 switch(type){case 0:result=1;break;
 case 1:{u32 condition=mailGetSendCondition(id);if(condition!=0xFFFFFFFF && GSflagGet(condition)!=0)result=1;break;}
 case 2:{u32 condition=mailGetSendCondition(id);if(condition!=0xFFFFFFFF && condition!=0){floorExecScriptInteger(condition,0,0,0,0);if(floorGetScriptResult()!=0)result=1;}break;}}
 return result;
}
static void cbStep__Fl15FootStepCounterl(s32,s32,s32) {f32 random=HSD_Randf();s32 count=mailGetNbMailData();s32 i; s32 sent=0;for(i=0;i<count;i++){if(chkMailSend__Fif(i,random)){mailAddMailbox(i);sent=1;}}if(sent)beginReceive();}
void mailMainInit(){heroMoveAddStepCallback(cbStep__Fl15FootStepCounterl,0);ReceiveWork.active=0;ReceiveWork.sound=0;ReceiveWork.unkC=0;}
}
