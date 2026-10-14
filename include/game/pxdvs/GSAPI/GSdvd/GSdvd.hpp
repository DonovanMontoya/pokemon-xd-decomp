#ifndef GSDVD_HPP
#define GSDVD_HPP
#include <dolphin/dvd.h>
struct GSdvdWork;
typedef void (*GSdvdCallback)(s32, GSdvdWork*);
struct GSdvdWork { u8 inUse, reserved[3]; DVDFileInfo info; GSdvdCallback callback; void* buffer; u32 length; };
typedef char GSdvdWorkSizeCheck[sizeof(GSdvdWork) == 0x4c ? 1 : -1];
extern "C" {
GSdvdWork* GSdvdOpen(const char*);
u32 GSdvdOpenTest(const char*);
s32 GSdvdRead(GSdvdWork*, void*, s32, s32);
u8 GSdvdReadAsync(GSdvdWork*, void*, s32, s32, GSdvdCallback);
u8 GSdvdSeekAsync(GSdvdWork*, s32, GSdvdCallback);
s32 GSdvdClose(GSdvdWork*);
u32 GSdvdGetLength(GSdvdWork*);
s32 GSdvdGetDriveStatus();
s32 GSdvdGetFileInfoStatus(GSdvdWork*);
s32 GSdvdInit(u32);
void GSdvdSetErrorMsg(u32, u32, u32, u32, u32);
void GSdvdSetGCClient(const char*, const char*, const char*, u8);
void GSdvdSetReportServer(const char*, u16, u8);
void GSdvdSetDVDServer(const char*, u16);
s32 GSdvdFstRefresh();
}
#endif
