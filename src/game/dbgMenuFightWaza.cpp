/* Debug menu entry for editing a waza (move) in the fight debug menu. */
#include <global.h>

typedef struct DbgWazaData {
    s32 data[14];
} DbgWazaData;

extern s32 dbgMenuFightGetWazaTypeId(u8);
extern void menuCloseCustom(s32, s32, s32);
extern s32 menuGetCursorItemID(s32);
extern s32 menuOpen(s32, s32);
extern s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
extern s8 menuSubOpenYesNo(s32, s32, s32, s32);
extern DbgWazaData* wazaDataBiosGetPtr(void);
extern s32 wazaGetStatus(s32, u16, s32, s32);
extern void wazaSetStatus(s32, u16, s32, s32, s32);

s32 dbgMenuFightWazaEditSub(u16 id) {
    DbgWazaData backup;
    DbgWazaData* data;
    s32 result;
    s32 type;
    s8 yesno;

    if (id == 0) {
        return 1;
    }
    if (id >= 0x163) {
        return 1;
    }
    data = wazaDataBiosGetPtr();
    backup = *data;
    for (;;) {
        result = menuOpenCustom(0x20, 0, 0, 0, 1, 1, id);
        if (result == -1) {
            menuCloseCustom(0x20, 0, 1);
            *data = backup;
            return -1;
        }
        if (result == -2) {
            if (menuOpen(0x55, 1) != 0) {
                menuCloseCustom(0x55, 0, 1);
                continue;
            }
            menuCloseCustom(0x55, 0, 1);
            break;
        }
        switch (menuGetCursorItemID(0x20)) {
        case 0x89:
            type = dbgMenuFightGetWazaTypeId(wazaGetStatus(0, id, 0x1A, 0));
            if (type >= 0) {
                wazaSetStatus(0, id, 0x1A, 0, type);
            }
            break;
        case 0x8A:
            type = dbgMenuFightGetWazaTypeId(wazaGetStatus(0, id, 0x1A, 1));
            if (type >= 0) {
                wazaSetStatus(0, id, 0x1A, 1, type);
            }
            break;
        case 0x8B:
            type = dbgMenuFightGetWazaTypeId(wazaGetStatus(0, id, 0x1A, 2));
            if (type >= 0) {
                wazaSetStatus(0, id, 0x1A, 2, type);
            }
            break;
        case 0x8C:
            yesno = menuSubOpenYesNo(0x7F, -1, -1, wazaGetStatus(0, id, 0x1B, 0) == 0);
            if (yesno == 0) {
                wazaSetStatus(0, id, 0x1B, 0, 1);
            } else if (yesno == 1) {
                wazaSetStatus(0, id, 0x1B, 0, 0);
            }
            break;
        }
    }
    menuCloseCustom(0x20, 0, 1);
    return 1;
}
