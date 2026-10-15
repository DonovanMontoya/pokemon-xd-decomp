#include <dolphin/types.h>

extern "C" {

void OSPanic(const char *file, int line, ...)
{
    (void)file;
    (void)line;
}

void GSgfxHalt(s32 exception, void *context, s32 dsisr, s32 dar, ...)
{
    (void)exception;
    (void)context;
    (void)dsisr;
    (void)dar;
}

void OSSetErrorHandler(s32 exception, void (*handler)(s32, void *, s32, s32, ...));
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32 enabled);
extern s32 __OSFpscrEnableBits;

void GSgfxHaltInit__Fv(void)
{
    OSSetErrorHandler(2, GSgfxHalt);
    OSSetErrorHandler(3, GSgfxHalt);
    OSSetErrorHandler(5, GSgfxHalt);
    OSSetErrorHandler(15, GSgfxHalt);
    __OSFpscrEnableBits = 16;
    OSSetErrorHandler(16, GSgfxHalt);
    s32 interrupts = OSDisableInterrupts();
    OSRestoreInterrupts(interrupts);
}

}
