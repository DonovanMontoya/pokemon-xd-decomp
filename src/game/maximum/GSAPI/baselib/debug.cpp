#include "game/maximum/GSAPI/baselib/debug.h"

extern void OSReport(const char*, ...);
extern void OSPanic(const char*, unsigned int, const char*, ...);
static unsigned char debug_context[0x2C8];
static void (*panic_func)(void*, ...);
void __assert(const char* file, unsigned int line, const char* expression)
{
    OSReport("assertion \"%s\" failed", expression);
    HSD_Panic(file, line, "");
}
void HSD_Panic(const char* file, unsigned int line, const char* message)
{
    if (panic_func != 0) {
        HSD_SaveContext();
        OSReport("%s in %s on line %d.\n", message, file, line);
        panic_func(debug_context);
    }
    OSPanic(file, line, message);
}
