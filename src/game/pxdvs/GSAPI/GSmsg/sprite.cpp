#include <game/pxdvs/GSAPI/GSmsg/spritePrivate.hpp>
#include <libc/math.h>
#include <libc/string.h>
struct _struct__spriteWork_0x10 {f32 unk0,unk4,unk8,unkC;};
static _struct__spriteWork_0x10 _spriteWork[3]={{0,0,1,1},{0,0,1,1},{0,0,1,1}};
extern "C" {
double tan(double);
void spriteClearScissor(s32 layer) {
    GSgfxLayer *temp_r3;

    temp_r3 = GSgfxLayerFindByID(layer);
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        temp_r3->unkD70 = 0;
        temp_r3->unkD72 = 0;
        GSgfxVideoGetEFBSize(&temp_r3->unkD74, &temp_r3->unkD76);
        temp_r3->unk16B8 = (s32) (temp_r3->unk16B8 | 1);
        temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 2);
        temp_r3->unk1770 = (s32) (temp_r3->unk1770 | 1);
        temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 2);
    }
}

void spriteSetScissor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    f32 temp_f5;
    f32 temp_f6;
    s16 var_r0;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    struct _struct__spriteWork_0x10 *temp_r31;
    GSgfxLayer *temp_r3;

    if (arg0 == floorGetMenuLayerID()) {
        var_r0 = 0;
    } else if (arg0 == 7) {
        var_r0 = 1;
    } else {
        var_r0 = 2;
    }
    temp_r31 = &_spriteWork[var_r0];
    temp_r3 = GSgfxLayerFindByID(arg0);
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        temp_f5 = temp_r31->unk8;
        temp_f6 = temp_r31->unkC;
        var_r27 = (s32) ((f32) (s32) (temp_r31->unk0 + (f32) arg1) * temp_f5);
        var_r28 = (s32) ((f32) (s32) (temp_r31->unk4 + (f32) arg2) * temp_f6);
        var_r29 = (s32) ((f32) arg3 * temp_f5);
        var_r30 = (s32) ((f32) arg4 * temp_f6);
        if (var_r27 >= 0x280) {
            var_r27 = 0x280;
        }
        if (var_r28 >= 0x1E0) {
            var_r28 = 0x1E0;
        }
        if (var_r29 >= 0x280) {
            var_r29 = 0x280;
        }
        if (var_r30 >= 0x1E0) {
            var_r30 = 0x1E0;
        }
        if (var_r27 < 0) {
            var_r27 = 0;
        }
        if (var_r28 < 0) {
            var_r28 = 0;
        }
        if (var_r29 < 0) {
            var_r29 = 0;
        }
        if (var_r30 < 0) {
            var_r30 = 0;
        }
        temp_r3->unkD70 = (u16) var_r27;
        temp_r3->unkD72 = (u16) var_r28;
        temp_r3->unkD74 = (u16) var_r29;
        temp_r3->unkD76 = (u16) var_r30;
        temp_r3->unk16B8 = (s32) (temp_r3->unk16B8 | 1);
        temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 2);
        temp_r3->unk1770 = (s32) (temp_r3->unk1770 | 1);
        temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 2);
    }
}

void spriteClearEnv(s32 layer) {
    GSgfxLayer *temp_r3;

    temp_r3 = GSgfxLayerFindByID(layer);
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        if ((s32) temp_r3->unk1994 != 1) {
            temp_r3->unk1994 = 1;
            temp_r3->unk1990 = temp_r3->shaders[temp_r3->unk1994];
        }
        temp_r3->unk1644 = 1;
        temp_r3->unk1648 = 4;
        temp_r3->unk164C = 5;
        temp_r3->unk1650 = 5;
        temp_r3->unk170C = (s32) (temp_r3->unk170C | 1);
        temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 0x40);
        temp_r3->unk17C4 = (s32) (temp_r3->unk17C4 | 1);
        temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 0x40);
    }
}

void spriteSetEnv(s32 arg0) {
    Mtx view;
    Mtx44 projection;
    Vec eye, center, up;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f4;
    s16 var_r0;
    SpriteMatrixFrame *temp_r3_2;
    SpriteMatrixFrame *temp_r3_4;
    f32 (*temp_r3_3)[4];
    struct _struct__spriteWork_0x10 *temp_r31;
    GSgfxLayer *temp_r31_2;
    SpriteMatrixStack *temp_r31_3;
    SpriteMatrixStack *temp_r31_4;
    GSgfxLayer *temp_r3;

    if (arg0 == floorGetMenuLayerID()) {
        var_r0 = 0;
    } else if (arg0 == 7) {
        var_r0 = 1;
    } else {
        var_r0 = 2;
    }
    temp_r31 = &_spriteWork[var_r0];
    temp_r3 = GSgfxLayerFindByID(arg0);
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        temp_f2 = temp_r31->unkC;
        temp_f29 = 640.0f / temp_r31->unk8;
        temp_f28 = 480.0f / temp_f2;
        temp_f31 = temp_f29 * 0.5f;
        temp_f30 = temp_f28 * 0.5f;
        temp_f3 = temp_r31->unk0;
        temp_f2_2 = temp_f30 / (f32) tan(0.2617994f);
        center.z = 0.0f;
        up.x = 0.0f;
        temp_f4 = temp_f30 - temp_r31->unk4;
        eye.z = temp_f2_2;
        temp_f2_3 = temp_f31 - temp_f3;
        up.y = -1.0f;
        eye.x = temp_f2_3;
        eye.y = temp_f4;
        center.x = temp_f2_3;
        center.y = temp_f4;
        up.z = 0.0f;
        C_MTXLookAt(view, &eye, &up, &center);
        temp_r31_2 = _TargetLayer;
        GSmtx44Perspective(projection, 30.0f, -(temp_f29 / temp_f28), 0.1f, 30000.0f);
        temp_r31_2->unkD54 = 0;
        temp_r31_2->unkD58 = projection[0][0];
        temp_r31_2->unkD5C = projection[0][2];
        temp_r31_2->unkD60 = projection[1][1];
        temp_r31_2->unkD64 = projection[1][2];
        temp_r31_2->unkD68 = projection[2][2];
        temp_r31_2->unkD6C = projection[2][3];
        temp_r31_2->unk1684 = 0.1f;
        temp_r31_2->unk1688 = 30000.0f;
        if ((u8) temp_r31_2->unk16A7 != 0) {
            if ((u8) temp_r31_2->unk16A6 != 0) {
                temp_r31_2->unk170C = (s32) (temp_r31_2->unk170C | 0x100);
                temp_r31_2->unk17C4 = (s32) (temp_r31_2->unk17C4 | 0x100);
            }
            temp_r31_2->unk170C = (s32) (temp_r31_2->unk170C | 0x40);
            temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 0x40);
            temp_r31_2->unk17C4 = (s32) (temp_r31_2->unk17C4 | 0x40);
            temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 0x40);
        }
        temp_r31_2->unk16AC = (s32) (temp_r31_2->unk16AC | 0x20);
        temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 1);
        temp_r31_2->unk1764 = (s32) (temp_r31_2->unk1764 | 0x20);
        temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 1);
        temp_r31_3 = _TargetLayer->unk19A0;
        memcpy(temp_r31_3->frame->matrix, mtxIdent, 0x30);
        temp_r3_2 = temp_r31_3->frame;
        temp_r3_2->flags |= 1;
        temp_r31_4 = _TargetLayer->unk19A0;
        temp_r3_3 = temp_r31_4->frame->matrix;
        PSMTXConcat(temp_r3_3, view, temp_r3_3);
        temp_r3_4 = temp_r31_4->frame;
        temp_r3_4->flags |= 1;
        if ((s32) _TargetLayer->unk1994 != 1) {
            _TargetLayer->unk1994 = 1;
            _TargetLayer->unk1990 = (void *) ((u8*)_TargetLayer + ((_TargetLayer->unk1994 * 0xBC) + 0x1818));
        }
        _TargetLayer->unk1644 = 1;
        _TargetLayer->unk1648 = 4;
        _TargetLayer->unk164C = 5;
        _TargetLayer->unk1650 = 5;
        _TargetLayer->unk170C = (s32) (_TargetLayer->unk170C | 1);
        _TargetLayer->unk16A8 = (s32) (_TargetLayer->unk16A8 | 0x40);
        _TargetLayer->unk17C4 = (s32) (_TargetLayer->unk17C4 | 1);
        _TargetLayer->unk1760 = (s32) (_TargetLayer->unk1760 | 0x40);
        _TargetLayer->unk1656 = 1;
        _TargetLayer->unk1657 = 0;
        _TargetLayer->unk1658 = 1;
        _TargetLayer->unk170C = (s32) (_TargetLayer->unk170C | 4);
        _TargetLayer->unk16A8 = (s32) (_TargetLayer->unk16A8 | 0x40);
        _TargetLayer->unk17C4 = (s32) (_TargetLayer->unk17C4 | 4);
        _TargetLayer->unk1760 = (s32) (_TargetLayer->unk1760 | 0x40);
        _TargetLayer->unk1664 = 7;
        _TargetLayer->unk1670 = 0;
        _TargetLayer->unk1668 = 0;
        _TargetLayer->unk166C = 7;
        _TargetLayer->unk1671 = 0;
        _TargetLayer->unk1672 = 1;
        _TargetLayer->unk170C = (s32) (_TargetLayer->unk170C | 0x10);
        _TargetLayer->unk16A8 = (s32) (_TargetLayer->unk16A8 | 0x40);
        _TargetLayer->unk17C4 = (s32) (_TargetLayer->unk17C4 | 0x10);
        _TargetLayer->unk1760 = (s32) (_TargetLayer->unk1760 | 0x40);
        _TargetLayer->unk165C = 0;
        _TargetLayer->unk1660 = 3;
        _TargetLayer->unk170C = (s32) (_TargetLayer->unk170C | 8);
        _TargetLayer->unk16A8 = (s32) (_TargetLayer->unk16A8 | 0x40);
        _TargetLayer->unk17C4 = (s32) (_TargetLayer->unk17C4 | 8);
        _TargetLayer->unk1760 = (s32) (_TargetLayer->unk1760 | 0x40);
        _TargetLayer->unkD8C = 0;
        _TargetLayer->unk16B8 = (s32) (_TargetLayer->unk16B8 | 2);
        _TargetLayer->unk16A8 = (s32) (_TargetLayer->unk16A8 | 2);
        _TargetLayer->unk1770 = (s32) (_TargetLayer->unk1770 | 2);
        _TargetLayer->unk1760 = (s32) (_TargetLayer->unk1760 | 2);
    }
}

void spriteGetOffset(s32 arg0, s16 *arg1, s16 *arg2) {
    s16 var_r0;
    struct _struct__spriteWork_0x10 *temp_r3;

    if (arg0 == floorGetMenuLayerID()) {
        var_r0 = 0;
    } else if (arg0 == 7) {
        var_r0 = 1;
    } else {
        var_r0 = 2;
    }
    temp_r3 = &_spriteWork[var_r0];
    if (arg1 != NULL) {
        *arg1 = (s16) temp_r3->unk0;
    }
    if (arg2 != NULL) {
        *arg2 = (s16) temp_r3->unk4;
    }
}

void spriteSetOffset(s32 arg0, s16 arg1, s16 arg2) {
    s16 var_r5;
    struct _struct__spriteWork_0x10 *temp_r4;

    if (arg0 == floorGetMenuLayerID()) {
        var_r5 = 0;
    } else if (arg0 == 7) {
        var_r5 = 1;
    } else {
        var_r5 = 2;
    }
    temp_r4 = &_spriteWork[var_r5];
    temp_r4->unk0 = (f32) arg1;
    temp_r4->unk4 = (f32) arg2;
}

}
