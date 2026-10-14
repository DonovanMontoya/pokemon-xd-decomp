#include <game/maximum/GSAPI/baselib/class.h>
static void ObjInfoInit(void);
HSD_ClassInfo hsdObj = { ObjInfoInit };
static void ObjInfoInit(void) {
    hsdInitClassInfo(&hsdObj, &hsdClass, "sysdolphin_base_library", "hsd_obj", sizeof(HSD_ClassInfo), 8);
}
