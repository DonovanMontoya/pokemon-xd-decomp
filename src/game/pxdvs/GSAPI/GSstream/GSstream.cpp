extern "C" {
#include <libc/stdarg.h>
#include <libc/stdio.h>
}
#include <global.h>
#include <libc/string.h>
extern "C" {
s32 GSdvdWrite(void*,const void*,s32,u32);
u8 GSdvdOpenTest(const char*);
s32 GSdvdRemove(const char*);
void* GSdvdCreate(const char*);
void GSdvdClose(void*);
}
class GSstreamFileOutput {
    void* file;
    u32 position;
public:
    GSstreamFileOutput();
    ~GSstreamFileOutput();
    bool open(const char*);
    bool is_open() const;
    bool write(const char*,long);
    bool writeString(const char*);
    void writePrintf(const char*,...);
};
void GSstreamFileOutput::writePrintf(const char* format,...) {
    char buffer[512];
    va_list args;
    va_start(args,format);
    vsprintf(buffer,format,args);
    writeString(buffer);
    va_end(args);
}
bool GSstreamFileOutput::writeString(const char* text) {
    long size = strlen(text);
    write(text,size);
    return true;
}
bool GSstreamFileOutput::write(const char* data,long size) {
    if (GSdvdWrite(file,data,size,position) < 0) return false;
    position += size;
    return true;
}
#pragma dont_inline on
bool GSstreamFileOutput::is_open() const { return file != 0; }
#pragma dont_inline reset
bool GSstreamFileOutput::open(const char* path) {
    if (file) return false;
    if (GSdvdOpenTest(path)) { if (!GSdvdRemove(path)) return false; }
    file = GSdvdCreate(path);
    position = 0;
    return is_open();
}
GSstreamFileOutput::~GSstreamFileOutput() { if (file) GSdvdClose(file); }
GSstreamFileOutput::GSstreamFileOutput() { file = 0; }
