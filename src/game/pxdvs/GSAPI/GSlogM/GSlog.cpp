extern "C" {
#include <libc/stdarg.h>
#include <libc/stdio.h>
}
#include <global.h>
#include <libc/string.h>
static char* _logBuffer;
static u16* _lenBuffer;
static u32 _logBufSize,_logLineCount,_logMaxLines,_logStampMode;
static void* _mainThread;
#pragma force_active on
static const char logDigits[]="0123456789ABCDEF";
static const char logNoBuffer[28]="GSlog: Init OK, no buffer\n";
static const char logFailed[20]="GSlog: Init FAILED\n";
static const char logInitialized[44]="GSlog: Init OK, log buffer size %d bytes\n";
static const char logStamp[23]="%d/%02d %d:%02d:%02d] ";
#pragma force_active reset
static const char* _inthexTable=logDigits;
extern "C" { void* GSmemAlloc(u32); void GSmemFree(void*); void* OSGetCurrentThread(); }
void logStrRev(char*);
extern "C" {
char* GSlogGetLine(u32 line) {
    char* buffer=_logBuffer;
    if(!buffer) return 0;
    if(line>_logLineCount) return 0;
    u16* lengths=_lenBuffer;
    u32 offset=0;
    for(u32 i=0;i<line;++i) offset+=lengths[i];
    return buffer+offset;
}
u32 GSlogGetLineCount() { if(_logBuffer==0) return 0; return _logLineCount; }
// Logging output is disabled in the original release build; its variadic entry points remain.
void GSlogWritef(const char*,...) {}
void GSlogWrite(const char*,...) {}
void GSlogSetIP(u32) {}
u8 GSlogInit(u32 bytes,u32 mode) {
    const char* strings=logDigits;
    _logStampMode=mode; _logBufSize=bytes;
    if(!bytes) { GSlogWrite(strings+20); return 1; }
    _logBuffer=(char*)GSmemAlloc(bytes);
    if(!_logBuffer) { GSlogWrite(strings+48); return 0; }
    _logMaxLines=bytes>>7;
    _lenBuffer=(u16*)GSmemAlloc(_logMaxLines*2);
    if(!_lenBuffer) { GSmemFree(_logBuffer); GSlogWrite(strings+48); return 0; }
    _mainThread=OSGetCurrentThread();
    GSlogWrite(strings+68,_logBufSize);
    return 1;
}
}
void logHex2Str(u32 value,char* text,bool uppercase) {
    char* out=text;
    do {
        *out=_inthexTable[value&15];
        if(!uppercase && *out>='A') *out+=32;
        value>>=4; ++out;
    } while(value);
    *out=0;
    logStrRev(text);
}
void logInt2Str(int value,char* text) {
    char* out=text;
    u8 negative=0;
    if(value<0) { negative=1; value=-value; }
    do { *out++=_inthexTable[value%10]; value/=10; } while(value);
    if(negative==1) *out++='-';
    *out=0;
    logStrRev(text);
}
int logStr2Int(char* text) {
    int value=0;
    while(*text) {
        if(*text<'0' || *text>'9') break;
        value*=10;
        int digit=*text++;
        value=digit+value;
        value-=48;
    }
    return value;
}
void logStrRev(char* text) {
    u32 length=strlen(text);
    char* end=(char*)(length+(u32)text);
    --end;
    while(text<end) { *text^=*end; *end^=*text; *text^=*end--; ++text; }
}
