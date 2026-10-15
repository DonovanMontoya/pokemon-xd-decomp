#include <global.h>
#pragma force_active on
extern "C" {extern u32* table_res_number;extern void** table_res;void GSlogWrite(const char*,...);
void* tableResBiosGetResPtr(u32 id){if(id>=*table_res_number){GSlogWrite("\x5B\x25\x73\x5D\x3A\x20\x83\x65\x81\x5B\x83\x75\x83\x8B\x83\x43\x83\x93\x83\x66\x83\x62\x83\x4E\x83\x58\x82\xAA\x94\xCD\x88\xCD\x8A\x4F\x82\xC5\x82\xB7\x0A",__FUNCTION__);return 0;}return table_res[id];}}

#pragma force_active reset
