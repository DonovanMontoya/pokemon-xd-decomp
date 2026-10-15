#include <game/pxdvs/app/people/peopleColisionPrivate.hpp>

extern "C" {
u8 peopleLineCheck(u32 arg0, u32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, u8 arg2) {
    GSvec spA0;
    GSvec sp94;
    GSvec sp88;
    GSvec sp7C;
    GSvec sp70;
    GSvec sp64;
    GSvec sp58;
    GSvec sp4C;
    GSvec sp40;
    GSvec sp34;
    GSvec sp28;
    GSvec sp1C;
    GSvec sp10;
    s32 sp8;
    GSvec *temp_r3_2;
    GSvec *temp_r3_3;
    PeopleInfo *temp_r3_5;
    Resource *temp_r3_4;
    f32 temp_f1;
    f32 var_f1;
    f32 var_f28;
    f32 radius;
    f32 var_f29;
    f32 var_f31;
    tagPeopleWork *temp_r3;

    temp_r3 = peopleGet(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    temp_r3_2 = peopleBiosGetPosPtr(temp_r3);
    sp70.param1 = temp_r3_2->param1;
    sp70.param2 = temp_r3_2->param2;
    sp70.param3 = temp_r3_2->param3;
    temp_r3_3 = peopleBiosGetPrevPosPtr(temp_r3);
    sp7C.param1 = temp_r3_3->param1;
    sp7C.param2 = temp_r3_3->param2;
    sp7C.param3 = temp_r3_3->param3;
    PSVECSubtract(&sp70, &sp7C, &sp64);
    sp94.param1 = farg0;
    sp94.param2 = sp70.param2;
    sp94.param3 = farg1;
    sp88.param1 = farg2;
    sp88.param2 = sp70.param2;
    sp88.param3 = farg3;
    temp_r3_4 = GSresGetResource(0U, 2U);
    if ((temp_r3_4 != 0) && ((u8) temp_r3_4->used != 0)) {
        GSgfxLayerSetActive(2);
        GScameraLoadActiveCameraMatrix(2);
        GSgfxCullMode(0);
        sp8 = 0;
        GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0);
        GSgfxSetupRenderAndSelect();
        GSgfxBlendMode(1, 4, 5);
        GSgfxZCompare(1, 1);
        GSgfxPixelMode(1, 1, 1);
        GSgfxAlphaCompare(0, 7, 0, 0, 7, 0);
        GSgfxSetPrimitiveType(0x98);
        GSgfxBeginSurface(4);
        GSgfxVertex3f(farg0, sp70.param2 - 50.0f, farg1);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg0, 50.0f + sp70.param2, farg1);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg2, sp70.param2 - 50.0f, farg3);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg2, 50.0f + sp70.param2, farg3);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxEndSurface();
    }
    temp_r3_5 = peopleInfoBiosGetPtr(temp_r3->object);
    if (temp_r3_5 != 0) {
        var_f31 = peopleInfoBiosGetColBallSize(temp_r3_5);
    } else {
        var_f31 = 4.0f;
    }
    radius = var_f31;
    temp_f1 = PSVECMag(&sp64);
    if (temp_f1 > 0.0f) {
        var_f29 = var_f31 / temp_f1;
        if (var_f29 > 1.0f) {
            var_f29 = 1.0f;
        }
    } else {
        var_f29 = 1.0f;
    }
    PSVECSubtract(&sp88, &sp94, &sp1C);
    if (PSVECMag(&sp1C) < 0.0001f) {
        return 0U;
    }
    PSVECNormalize(&sp1C, &sp1C);
    PSVECSubtract(&sp7C, &sp94, &sp10);
    PSVECScale(&sp1C, &sp10, PSVECDotProduct(&sp10, &sp1C));
    PSVECAdd(&sp10, &sp94, &sp34);
    PSVECSubtract(&sp7C, &sp34, &sp28);
    for (var_f28 = 0.0f; var_f28 < 1.0f; var_f28 += var_f29) {
    var_f1 = var_f28 + var_f29;
    if (var_f1 > 1.0f) {
        var_f1 = 1.0f;
    }
    PSVECScale(&sp64, &spA0, var_f1);
    PSVECAdd(&sp7C, &spA0, &spA0);
    if (_peopleGetCrossPoint__FP5GSvecP5GSvecfP5GSvecP5GSvecP5GSvec(&sp34, &spA0, radius, &sp94, &sp88, &sp28) != 0) {
        if (arg2 != 0) {
            GScolsy2UtilGetPointExtentionLine(&sp40, &sp34, &spA0, 0.0001f + radius);
            if (GScolsys2HitCollision(&sp7C, &sp40, &sp58, 4.0f) != 0) {
                PSVECSubtract(&sp58, &sp40, &sp4C);
                PSVECAdd(&sp40, &sp4C, &sp40);
            }
            peopleBiosSetPos(temp_r3, &sp40);
            heroMoveSetLockFrame(1);
        }
        return 1U;
    }
    }
    return 0U;
}

static u8 _peopleGetCrossPoint__FP5GSvecP5GSvecfP5GSvecP5GSvecP5GSvec(GSvec *arg0, GSvec *arg1, f32 farg0, GSvec *arg2, GSvec *arg3, GSvec *arg4) {
    GSvec triangle[3];
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f5;

    temp_f5 = arg2->param1;
    triangle[0].param1 = temp_f5;
    temp_f2 = arg0->param2;
    temp_f4 = temp_f2 - 50.0f;
    triangle[0].param2 = temp_f4;
    temp_f3 = arg2->param3;
    triangle[0].param3 = temp_f3;
    triangle[1].param1 = arg3->param1;
    triangle[1].param2 = temp_f4;
    triangle[1].param3 = arg3->param3;
    triangle[2].param1 = temp_f5;
    triangle[2].param2 = 50.0f + temp_f2;
    triangle[2].param3 = temp_f3;
    if (getCpPointPoly__FP5GSvecP5GSvecfP5GSvecP5GSvec(arg0, arg1, farg0, triangle, arg4) != 0) {
        return 1U;
    }
    temp_f4_2 = arg3->param1;
    triangle[0].param1 = temp_f4_2;
    temp_f3_2 = arg0->param2;
    triangle[0].param2 = temp_f3_2 - 50.0f;
    temp_f2_2 = arg3->param3;
    triangle[0].param3 = temp_f2_2;
    triangle[1].param1 = temp_f4_2;
    triangle[1].param2 = 50.0f + temp_f3_2;
    triangle[1].param3 = temp_f2_2;
    if (getCpPointPoly__FP5GSvecP5GSvecfP5GSvecP5GSvec(arg0, arg1, farg0, triangle, arg4) != 0) {
        return 1U;
    }
    triangle[0].param1 = arg3->param1;
    temp_f2_3 = arg0->param2;
    temp_f4_3 = temp_f2_3 - 50.0f;
    triangle[0].param2 = temp_f4_3;
    triangle[0].param3 = arg3->param3;
    temp_f3_3 = arg2->param1;
    triangle[1].param1 = temp_f3_3;
    triangle[1].param2 = temp_f4_3;
    temp_f2_4 = arg2->param3;
    triangle[1].param3 = temp_f2_4;
    triangle[2].param1 = temp_f3_3;
    triangle[2].param2 = 50.0f + temp_f2_3;
    triangle[2].param3 = temp_f2_4;
    if (getCpPointPoly__FP5GSvecP5GSvecfP5GSvecP5GSvec(arg0, arg1, farg0, triangle, arg4) != 0) {
        return 1U;
    }
    triangle[1].param1 = arg2->param1;
    temp_f2_5 = 50.0f + arg0->param2;
    triangle[1].param2 = temp_f2_5;
    triangle[1].param3 = arg2->param3;
    triangle[2].param1 = arg3->param1;
    triangle[2].param2 = temp_f2_5;
    triangle[2].param3 = arg3->param3;
    return getCpPointPoly__FP5GSvecP5GSvecfP5GSvecP5GSvec(arg0, arg1, farg0, triangle, arg4) != 0;
}

static u8 getCpPointPoly__FP5GSvecP5GSvecfP5GSvecP5GSvec(GSvec *arg0, GSvec *arg1, f32 farg0, GSvec *arg2, GSvec *arg3) {
    GSvec sp8;

    if (GScolsy2UtilGetSidePlanePoint(arg3, arg2, arg1) < 0.0f) {
        return 0U;
    }
    GScolsy2UtilGetCpPlanePoint(&sp8, arg3, arg2, arg1);
    if (PSVECSquareDistance(&sp8, arg1) >= (farg0 * farg0)) {
        return 0U;
    }
    if (GScolsy2UtilChkInTri(&sp8, arg2, arg3) == 0) {
        return 0U;
    }
    arg0->param1 = sp8.param1;
    arg0->param2 = sp8.param2;
    arg0->param3 = sp8.param3;
    return 1U;
}

u8 peopleRectCheck(u32 arg0, u32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    s32 sp8;
    GSvec *temp_r3_2;
    Resource *temp_r3_3;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 var_f0;
    f32 var_f1;
    f32 var_f2;
    f32 var_f3;
    tagPeopleWork *temp_r3;

    temp_r3 = peopleGet(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    temp_r3_2 = peopleBiosGetPosPtr(temp_r3);
    temp_f31 = temp_r3_2->param1;
    temp_f30 = temp_r3_2->param2;
    temp_f29 = temp_r3_2->param3;
    temp_r3_3 = GSresGetResource(0U, 2U);
    if ((temp_r3_3 != 0) && ((u8) temp_r3_3->used != 0)) {
        GSgfxLayerSetActive(2);
        GScameraLoadActiveCameraMatrix(2);
        GSgfxCullMode(0);
        sp8 = 0;
        GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0);
        GSgfxSetupRenderAndSelect();
        GSgfxBlendMode(1, 4, 5);
        GSgfxZCompare(1, 1);
        GSgfxPixelMode(1, 1, 1);
        GSgfxAlphaCompare(0, 7, 0, 0, 7, 0);
        GSgfxSetPrimitiveType(0x98);
        GSgfxBeginSurface(0xA);
        GSgfxVertex3f(farg0, temp_f30, farg1);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        temp_f28 = 50.0f + temp_f30;
        GSgfxVertex3f(farg0, temp_f28, farg1);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg0, temp_f30, farg3);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg0, temp_f28, farg3);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg2, temp_f30, farg3);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg2, temp_f28, farg3);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg2, temp_f30, farg1);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg2, temp_f28, farg1);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg0, temp_f30, farg1);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxVertex3f(farg0, temp_f28, farg1);
        GSgfxColor4u8(0U, 0x80U, 0xFFU, 0xC0U);
        GSgfxEndSurface();
    }
    if (farg0 < farg2) {
        var_f0 = farg0;
        var_f1 = farg2;
    } else {
        var_f0 = farg2;
        var_f1 = farg0;
    }
    if (farg1 < farg3) {
        var_f2 = farg1;
        var_f3 = farg3;
    } else {
        var_f2 = farg3;
        var_f3 = farg1;
    }
    if ((var_f0 <= temp_f31) && (temp_f31 <= var_f1) && (var_f2 <= temp_f29) && (temp_f29 <= var_f3)) {
        return 1U;
    }
    return 0U;
}
/* Warning: struct PeopleInfo is not defined (only forward-declared) */
}
