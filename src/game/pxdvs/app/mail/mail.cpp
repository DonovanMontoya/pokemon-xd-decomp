#include <dolphin/types.h>
#include <libc/string.h>
struct MailData { u32 sender,subject,contents,attach,open; };
struct Mailbox { u16 ids[32];u16 count;u8 flags[4];u8 sort;u8 pad;u16 sent; };
typedef char MailDataSize[sizeof(MailData)==0x14?1:-1];
typedef char MailboxSize[sizeof(Mailbox)==0x4A?1:-1];
extern MailData *mailData;
extern u32 *mailData_number;
extern "C" {
Mailbox *savedataGetStatus(s32,s32);
void mailMainInit();
}
static inline MailData *getMailData(s32 id) {
 if (id<=0 || id>*mailData_number) return 0;
 return mailData+id;
}
extern "C" {
s32 mailGetSendCntCondValue(s32) { return 0; }
s32 mailGetSendCntCond(s32) { return 0; }
u32 mailGetOpenFlag(s32 id) { MailData *p=getMailData(id);if(!p)return 0;return p->open; }
s32 mailGetSendCondition(s32) { return 0; }
s32 mailGetSendCondType(s32) { return 0; }
s32 mailGetSendRate(s32) { return 0; }
u32 mailGetAttachFileGroup(s32 id) { MailData *p=getMailData(id);if(!p)return 0;return p->attach; }
u8 mailGetSortMode() { return savedataGetStatus(0,10)->sort; }
u16 mailGetSendCnt() { return savedataGetStatus(0,10)->sent; }
u32 mailGetNbMailData() { return *mailData_number; }
u32 mailGetContents(s32 id) { MailData *p=getMailData(id);if(!p)return 0;return p->contents; }
u32 mailGetSenderName(s32 id) { MailData *p=getMailData(id);if(!p)return 0;return p->sender; }
u32 mailGetSubject(s32 id) { MailData *p=getMailData(id);if(!p)return 0;return p->subject; }
s32 mailChkReceiveMail(s32 id) {
 Mailbox *p=savedataGetStatus(0,10);
 if(id<=0 || id>*mailData_number) return 0;
 s32 n=p->count,i;
 for(i=0;i<n;i++) if(id==p->ids[i])break;
 if(i>=n)return 0;
 return 1;
}
s32 mailAddMailbox(s32 id) {
 Mailbox *p=savedataGetStatus(0,10);
 if(id<=0 || id>*mailData_number)return 0;
 if(p->count>=32)return 0;
 p->ids[p->count]=id;
 p->count++;
 p=savedataGetStatus(0,10);
 u8 mask;
 s32 index;
 if(id<0 || id>=32) index=-1;
 else {mask=1<<(7-id%8);index=id/8;}
 if(index>=0)p->flags[index]&=~mask;
 return 1;
}
s32 mailGetNbMailInMailbox() {return savedataGetStatus(0,10)->count;}
s32 mailGetMailIDInMailbox(s32 index) {
 Mailbox *p=savedataGetStatus(0,10);
 if(index<0 || index>=mailGetNbMailInMailbox())return -1;
 return p->ids[index];
}
s32 mailGetReceiveNumber(s32 id) {
 s32 i;
 s32 found=0;
 i=0;
 for(;i<mailGetNbMailInMailbox() && found==0;i++) if(id==mailGetMailIDInMailbox(i))found=1;
 if(!found)return -1;
 return i;
}
void mailInitMailbox(Mailbox *p) {
 memset(p,0,0x4A);p->sort=0;
 for(s32 i=0;i<32;i++)p->ids[i]=0xFF;
 mailMainInit();
}
}
