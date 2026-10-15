#ifndef GBA_PRIVATE_H
#define GBA_PRIVATE_H
#include <dolphin/os.h>
#include <dolphin/si.h>
#include <libc/stddef.h>
#include <libc/string.h>
#define GBA_READY 0
#define GBA_NOT_READY 1
#define GBA_BUSY 2
#define GBA_JSTAT_MASK 0x3a

typedef void (*GBACallback)(s32 chan,s32 result);
typedef void (*GBATransferCallback)(s32 chan);
typedef struct GBASecParam {u8 data[0x40];} GBASecParam;
typedef struct GBAControl {
 u8 output[5],input[5];
 s32 outputBytes,inputBytes;
 u8 *status,*ptr;
 GBACallback callback;
 s32 ret;
 OSThreadQueue threadQueue;
 OSTime delay;
 GBATransferCallback proc;
 u8 bootAndTask[0xbc];
 GBASecParam *param;
} GBAControl;
typedef char GBAControlSize[sizeof(GBAControl)==0x100?1:-1];
typedef char GBAControlProc[offsetof(GBAControl,proc)==0x38?1:-1];
typedef char GBAControlParam[offsetof(GBAControl,param)==0xf8?1:-1];
extern GBAControl __GBA[4];
extern BOOL __GBAReset;
void DSPInit(void);
void __OSReschedule(void);
void __GBASyncCallback(s32,s32);
s32 __GBASync(s32);
s32 __GBATransfer(s32,s32,s32,GBATransferCallback);
s32 GBAGetStatusAsync(s32,u8*,GBACallback);
s32 GBAResetAsync(s32,u8*,GBACallback);
s32 GBAReadAsync(s32,u8*,u8*,GBACallback);
s32 GBAWriteAsync(s32,u8*,u8*,GBACallback);
#endif
