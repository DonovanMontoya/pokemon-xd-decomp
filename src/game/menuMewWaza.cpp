#include <game/menuPcBoxPokemonLayout.hpp>
struct MewWork {s32 message;u32 pad4;s32 state;};struct WazaDataRecord;
extern "C" {void*GSgfxLayerFindByID(s32);u32 GSmsgGetGSchar(u32);void GSmsgMain(s32,s32,s32,bool);void GSmsgPrint2(s32,s16,s16,u32,u32);void menuSubDrawMsgWindow2(s32,s32,s32,s16,s16,u8,s32);u16 mewWazaGet(s32);void msgctrlSetValue(s32,u32);void spriteSetEnv(s32);void spriteSetOffset(s32,s16,s16);u32 wazaDataBiosGetName(WazaDataRecord*);WazaDataRecord*wazaDataBiosGetPtr(u16);s32 winSpriteGetLayerID(tagWINDOW_WORK*,tagSPRITE_WORK*);MewWork*windowGetFreeWork(tagWINDOW_WORK*);}
static u32 _GetMewWazaName(long);
extern "C" s32 menuMewWazaGetMenuDataID(void) {
    return 0x10C;
}

extern "C" s32 menuMewWazaDraw(tagWINDOW_WORK *arg0,tagSPRITE_WORK *arg1) {
    s16 temp_r0;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r6;
    s16 temp_r7;
    s32 temp_r30;
    u8 temp_r0_2;
    MewWork *temp_r31;

    temp_r31 = windowGetFreeWork(arg0);
    temp_r30 = winSpriteGetLayerID(arg0, arg1);
    GSgfxLayerFindByID(temp_r30);
    temp_r28 = arg1->height;
    temp_r7 = arg0->x;
    temp_r6 = arg1->x;
    temp_r27 = arg1->width;
    s32 baseY=arg1->y;
    s32 clipped=temp_r28-4;
    s16 offset=clipped-temp_r28;
    s32 translatedY=baseY+offset;
    spriteSetOffset(temp_r30, (s16) (temp_r7 + temp_r6), (s16) (arg0->y + translatedY));
    spriteSetEnv(temp_r30);
    temp_r0 = arg1->id;
    switch (temp_r0) {                              /* switch 1; irregular */
    case 44:                                        /* switch 1 */
        {u32 name=GSmsgGetGSchar(_GetMewWazaName(0));msgctrlSetValue(0x4D,name);}
        GSmsgPrint2(temp_r30, 0, 0, arg0->alpha | ~0xFF, 0xC72D);
        break;
    case 45:                                        /* switch 1 */
        msgctrlSetValue(0x4D,GSmsgGetGSchar(_GetMewWazaName(1)));
        GSmsgPrint2(temp_r30, 0, 0, arg0->alpha | ~0xFF, 0xC72E);
        break;
    case 46:                                        /* switch 1 */
        msgctrlSetValue(0x4D,GSmsgGetGSchar(_GetMewWazaName(2)));
        GSmsgPrint2(temp_r30, 0, 0, arg0->alpha | ~0xFF, 0xC72F);
        break;
    case 47:                                        /* switch 1 */
        msgctrlSetValue(0x4D,GSmsgGetGSchar(_GetMewWazaName(3)));
        GSmsgPrint2(temp_r30, 0, 0, arg0->alpha | ~0xFF, 0xC730);
        break;
    case 43:                                        /* switch 1 */
        menuSubDrawMsgWindow2(temp_r30, 0, -2, temp_r27, temp_r28, arg0->alpha, 1);
        GSmsgPrint2(temp_r30, 0, 0, arg0->alpha | ~0xFF, 0xC722);
        temp_r0_2 = arg0->phase;
        switch ((s8) temp_r0_2) {                   /* switch 2; irregular */
        case 0:case 1:
            break;
        case 3:                                     /* switch 2 */
        case 5:                                     /* switch 2 */
            break;
        case 2:                                     /* switch 2 */
            if ((s32) arg0->menu != 0x14) {
                GSmsgMain(temp_r30, temp_r31->message, temp_r31->state, ((s8) arg0->flags & 4) == 0);
                temp_r31->state = 0;
            }
            break;
        }
        break;
    }
    return 0;
}

static u32 _GetMewWazaName(long index){return wazaDataBiosGetName(wazaDataBiosGetPtr(mewWazaGet(index)));}
