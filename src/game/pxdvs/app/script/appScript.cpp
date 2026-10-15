#include <game/pxdvs/app/script/appScriptPrivate.hpp>

using namespace GSscript;

static void _appScriptModelSetVisibility(_GSmodel*, void*);

extern "C" {

void appScriptPlayME_Thread(u8 open, u32 me, u32 time, u8 flag) {
    if (open != 0) {
        soundOpenPlayME(me, time, flag);
    } else {
        soundPlayME(me, time, flag);
    }
}

void appScriptCommonCall(int id) {
    floorGetCommonScript()->runParamsWait(id, 0, 0, 0);
}

}

int AppScript::cmpEsaba(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10:
        GSthreadSwitch();
        appScriptSetInt(result, esabaSet(appScriptGetInt(&args[1])));
        if (appScriptGetInt(result) != 0) {
            soundOpenPlay(0x576, 0, 0xFF);
        }
        break;
    case 0x11:
        appScriptSetInt(result, esabaGetPokemonID(appScriptGetInt(&args[1])));
        break;
    case 0x12: {
        s32 a = appScriptGetInt(&args[1]);
        esabaSetEsaNum(a, appScriptGetInt(&args[2]));
        break;
    }
    case 0x13:
        appScriptSetInt(result, esabaGetEsaNum(appScriptGetInt(&args[1])));
        break;
    case 0x14:
        appScriptSetInt(result, esabaGetPokemonIsRare(appScriptGetInt(&args[1])));
        break;
    }
    return 0;
}

int AppScript::cmpDarkPokemon(int cmd, tigaVariant* args, tigaVariant* result) {
    Hero* hero = (Hero*)savedataGetStatus(0, 2);
    DarkPokemon* dark = darkPokemonGetDarkPokemon((u16)appScriptGetInt(&args[1]));
    if (dark == 0) {
        appScriptSetInt(result, 0);
        return 1;
    }
    switch (cmd) {
    case 0x10:
        if (dark->getStatus() == darkStatus4) {
            appScriptSetInt(result, 1);
        } else {
            appScriptSetInt(result, 0);
        }
        break;
    case 0x11:
        if (dark->getStatus() >= darkStatus3) {
            appScriptSetInt(result, 1);
        } else {
            appScriptSetInt(result, 0);
        }
        break;
    case 0x12:
        dark->setStatus((darkPokemonStatus)appScriptGetInt(&args[2]));
        break;
    case 0x13:
        appScriptSetInt(result, dark->getPokemonID());
        break;
    case 0x14:
        appScriptSetInt(result, dark->getStatus());
        break;
    case 0x15: {
        u8 count = hero->getMeetDarkPokemonCount();
        hero->setMeetDarkPokemonCount(count + 1);
        dark->setSnatchIndex(count);
        dark->addStatus(darkStatus1);
        dark->setCatchFloorId(0xB5);
        dark->setUpdate(true);
        break;
    }
    case 0x16: {
        s32 where = appScriptGetInt(&args[2]);
        dark->setPlace((darkPokemonWhere)where, appScriptGetInt(&args[3]));
        break;
    }
    }
    return 0;
}

int AppScript::cmpWaza(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10: {
        tigaWaza* w = allocWazaPtr();
        if (w != 0) {
            w->sequence = Sequence_CreateNull();
            appScriptSetVar(result, 0x3A, w);
            field934 = field934 + 1;
        }
        break;
    }
    case 0x11: {
        tigaWaza* w = appScriptGetWaza(&args[0]);
        if (w != 0) {
            if (w->wazaSequence == 0) {
                s32 a = appScriptGetInt(&args[1]);
                s32 b = appScriptGetInt(&args[2]);
                s32 c = appScriptGetInt(&args[3]);
                w->wazaSequence = Sequence_LoadWaza(w->sequence, a, b, c);
            }
            WazaSequence_Start(w->wazaSequence, 0);
            if (appScriptGetInt(&args[4]) == 1) {
                while (WazaSequence_IsActive(w->wazaSequence)) {
                    GSthreadSwitch();
                }
            }
        }
        break;
    }
    case 0x12: {
        tigaWaza* w = appScriptGetWaza(&args[0]);
        if (w != 0) {
            Sequence_SetPosition(w->sequence, appScriptGetVec(&args[1]));
        }
        break;
    }
    case 0x13: {
        tigaWaza* w = appScriptGetWaza(&args[0]);
        if (w != 0) {
            GSvec* v = appScriptGetVec(&args[1]);
            v->param1 = 0.017453292f * v->param1;
            v->param2 = 0.017453292f * v->param2;
            v->param3 = 0.017453292f * v->param3;
            Sequence_SetRotation(w->sequence, v);
        }
        break;
    }
    case 0x14: {
        tigaWaza* w = appScriptGetWaza(&args[0]);
        if (w != 0) {
            Sequence_SetScale(w->sequence, appScriptGetVec(&args[1]));
        }
        break;
    }
    case 0x15: {
        tigaWaza* w = appScriptGetWaza(&args[0]);
        if (w != 0) {
            while (WazaSequence_IsActive(w->wazaSequence)) {
                GSthreadSwitch();
            }
        }
        break;
    }
    case 0x16: {
        tigaWaza* w = appScriptGetWaza(&args[0]);
        if (w != 0) {
            if (w->wazaSequence != 0) {
                WazaSequence_Free(w->wazaSequence);
            }
            if (w->sequence != 0) {
                Sequence_Free(w->sequence);
            }
            freeWazaPtr(w);
        }
        field934 = field934 - 1;
        break;
    }
    }
    return 0;
}

int AppScript::cmpSodateya(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x11:
        appScriptSetInt(result, sodateyaGetPokemonLevelUpValue());
        break;
    case 0x12:
        appScriptSetInt(result, sodateyaGetPokemonDPValue());
        break;
    case 0x13:
        sodateyaRaise(appScriptGetInt(&args[1]));
        break;
    case 0x14:
        sodateyaReclaim(appScriptGetInt(&args[1]));
        break;
    case 0x15:
        break;
    case 0x16:
        appScriptSetInt(result, sodateyaCalcPrice(appScriptGetInt(&args[1])));
        break;
    case 0x17:
        appScriptSetInt(result, sodateyaeChekcRais());
        break;
    case 0x18:
        appScriptSetVar(result, 0x25, sodateyaGetPokemonPtr(0));
        break;
    }
    return 0;
}

int AppScript::cmpTv(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10:
        appScriptSetInt(result, controlTV(appScriptGetInt(&args[1])));
        break;
    case 0x11:
        appScriptSetInt(result, controlTVScreen());
        break;
    }
    return 0;
}

int AppScript::cmpDirection(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10:
        evolution();
        break;
    case 0x11: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        preReliveSetParameter(a, b, appScriptGetInt(&args[3]) != 0);
        break;
    }
    case 0x12:
        reliveMain();
        break;
    case 0x13:
        preReliveDisplayHokoraParticle();
        break;
    case 0x14: {
        s32 a = appScriptGetInt(&args[1]);
        appScriptSetInt(result, menuUseItemScriptCologn(a, appScriptGetInt(&args[2])));
        break;
    }
    case 0x15:
        appScriptSetInt(result, underTakerGetMiraboPlace());
        break;
    case 0x16:
        underTakerMiraboDisAppear();
        break;
    }
    return 0;
}

int AppScript::cmpMail(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10:
        mailMainSendByScrpt(appScriptGetInt(&args[1]));
        break;
    case 0x11:
        appScriptSetInt(result, scriptSetMemoFlag());
        break;
    case 0x12:
        menuScriptReciveMail();
        break;
    case 0x13:
        menuScriptReadMail(appScriptGetInt(&args[1]));
        break;
    case 0x14:
        menuScriptReciveMail();
        mailMainSendByScrpt(appScriptGetInt(&args[1]));
        menuScriptReadMail(appScriptGetInt(&args[1]));
        break;
    }
    return 0;
}

int AppScript::cmpPad(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10:
        appScriptSetInt(result, scriptIsButtonPush());
        break;
    case 0x11:
        appScriptSetInt(result, scriptIsMoveButtonPush());
        break;
    case 0x12:
        appScriptSetInt(result, scriptIsTrigerPush());
        break;
    case 0x13:
        if (gamedatasaveGetStatus(0, 9) == 0) {
            GSthread* thread = floorCreateThread(0x80, 0, 1, (s32 (*)(GSthread*))motorFun);
            s32 a = appScriptGetInt(&args[1]);
            s32 b = appScriptGetInt(&args[2]);
            s32 c = appScriptGetInt(&args[3]);
            GSthreadSetArgs(thread, 5, a, b, c, appScriptGetInt(&args[4]), 1);
        }
        break;
    case 0x14:
        appScriptSetInt(result, GSinputButtonsPressed(1));
        break;
    }
    return 0;
}

s32 motorFun(u8 a, u8 b, u32 c, u8 d, bool e) {
    u32 n = c;
    if (!e) {
        return 0;
    }
    while (n != 0) {
        GSinputMotorStart(1, a, b, c, d);
        GSthreadSwitch();
        n--;
    }
    return 0;
}

int AppScript::cmpSound(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, soundOpenPlay(a, b, appScriptGetInt(&args[3])));
        break;
    }
    case 0x11: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, soundOpenPlayEnv(a, b, appScriptGetInt(&args[3])));
        break;
    }
    case 0x12: {
        s32 a = appScriptGetInt(&args[1]);
        appScriptSetInt(result, soundStop(a, appScriptGetInt(&args[2])));
        break;
    }
    case 0x13:
        appScriptSetInt(result, soundStopEnv(appScriptGetInt(&args[1])));
        break;
    case 0x14: {
        s32 a = appScriptGetInt(&args[1]);
        f32 x = appScriptGetFloat(&args[2]);
        f32 y = appScriptGetFloat(&args[3]);
        appScriptSetInt(result, soundCreateEmitter(a, x, y, appScriptGetFloat(&args[4])));
        break;
    }
    case 0x15:
        appScriptSetInt(result, soundCreateListener());
        break;
    case 0x16: {
        s32 a = appScriptGetInt(&args[1]);
        appScriptSetInt(result, soundSetVolume(a, appScriptGetInt(&args[2])));
        break;
    }
    case 0x17: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, scriptSoundOpenPlayME(a, b, appScriptGetInt(&args[3])));
        break;
    }
    case 0x18: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, soundSetVolumeID(a, b, appScriptGetInt(&args[3])));
        break;
    }
    case 0x19: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        appScriptSetInt(result, soundOpenPlayFadeOutIn(a, b, c, appScriptGetInt(&args[4])));
        break;
    }
    case 0x1A: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        appScriptSetInt(result, soundOpenPlayEnvFadeOutIn(a, b, c, appScriptGetInt(&args[4])));
        break;
    }
    case 0x1B:
        appScriptSetInt(result, soundGetBGMID());
        break;
    case 0x1C:
        peopleTalkMessageBgmMask(appScriptGetInt(&args[1]) != 0);
        break;
    case 0x1D: {
        f32 a = appScriptGetFloat(&args[1]);
        peopleTalkMessageBgmSetFadeSpeed(a, appScriptGetFloat(&args[2]));
        break;
    }
    case 0x1E:
        peopleTalkMessageBgmSetVolumeRate(appScriptGetFloat(&args[1]));
        break;
    case 0x1F:
        soundPlayWait(appScriptGetInt(&args[1]));
        break;
    case 0x20: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, soundPlayME(a, b, appScriptGetInt(&args[3])));
        break;
    }
    case 0x21: {
        GSthread* thread = floorCreateThread(0x80, 0, 1, (s32 (*)(GSthread*))appScriptPlayME_Thread);
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        GSthreadSetArgs(thread, 4, a, b, c, appScriptGetInt(&args[4]));
        break;
    }
    }
    return 0;
}

int AppScript::cmpCol(int cmd, tigaVariant* args, tigaVariant*) {
    switch (cmd) {
    case 0x10: {
        s32 col = appScriptGetInt(&args[1]);
        scriptSetCol(col, appScriptGetInt(&args[2]) != 0);
        break;
    }
    case 0x11:
        scriptGetEventColID();
        break;
    case 0x12:
        scriptSetEventCol(appScriptGetInt(&args[1]) != 0);
        break;
    }
    return 0;
}

int AppScript::cmpModel(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10:
        appScriptSetInt(result, scriptModelOpen(appScriptGetInt(&args[1])));
        break;
    case 0x11:
        scriptModelClose(appScriptGetInt(&args[1]));
        break;
    case 0x12: {
        s32 a = appScriptGetInt(&args[1]);
        scriptModelSetDisp(a, appScriptGetInt(&args[2]));
        break;
    }
    case 0x13: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        scriptModelSetMotion(a, b, c, appScriptGetInt(&args[4]));
        break;
    }
    case 0x14:
        scriptModelStopMotion(appScriptGetInt(&args[1]));
        break;
    case 0x15: {
        s32 a = appScriptGetInt(&args[1]);
        appScriptSetInt(result, scriptModelWaitMotion(a, appScriptGetInt(&args[2])));
        break;
    }
    case 0x16: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, scriptModelAttach(a, b, appScriptGetInt(&args[3])));
        break;
    }
    case 0x17:
        appScriptSetInt(result, scriptModelDetach(appScriptGetInt(&args[1])));
        break;
    case 0x18: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        scriptModelSetParticle(a, b, appScriptGetInt(&args[3]));
        break;
    }
    case 0x19: {
        s32 a = appScriptGetInt(&args[1]);
        scriptModelDeleteParticle(a, appScriptGetInt(&args[2]) != 0);
        break;
    }
    case 0x1A: {
        void* model;
        void* part;
        f32 pos[3];
        s32 a = appScriptGetInt(&args[1]);
        model = GSresGetResource(floorGetCurrentGroupID(), a);
        if (model == 0) {
            return 0;
        }
        part = GSmodelGetPart(model, appScriptGetInt(&args[2]));
        GSpartGetTransform(part, pos, 0, 0);
        GSpartFree(part);
        appScriptCopyVec(&work()->vec, pos);
        work()->ret.value.vector = &work()->vec;
        work()->ret.type = 4;
        break;
    }
    case 0x1B: {
        void* model;
        s32 a = appScriptGetInt(&args[1]);
        model = GSresGetResource(floorGetCurrentGroupID(), a);
        if (model == 0) {
            return 0;
        }
        GSmodelAddPosition(model, appScriptGetVec(&args[2]));
        break;
    }
    case 0x1C:
        GSmodelIterateList(_appScriptModelSetVisibility, appScriptGetInt(&args[1]));
        break;
    case 0x1D: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        f32 rate = appScriptGetFloat(&args[4]);
        scriptModelSetMotionRate(a, b, c, rate, appScriptGetInt(&args[5]));
        break;
    }
    case 0x1E: {
        void* model;
        s32 a = appScriptGetInt(&args[1]);
        model = GSresGetResource(floorGetCurrentGroupID(), a);
        GSmodelSetBoundCheck(model, appScriptGetInt(&args[2]) != 0);
        break;
    }
    case 0x1F: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, scriptModelSetEndedMotion(a, b, appScriptGetInt(&args[3]) != 0));
        break;
    }
    case 0x20: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        scriptModelPartPaticle(a, b, appScriptGetInt(&args[3]));
        break;
    }
    case 0x21: {
        s32 a = appScriptGetInt(&args[1]);
        scriptModelSetFractionalFramesFlag(a, appScriptGetInt(&args[2]) != 0);
        break;
    }
    case 0x22: {
        s32 a = appScriptGetInt(&args[1]);
        GSmodelRecalculateBound(GSresGetResource(floorGetCurrentGroupID(), a));
        break;
    }
    case 0x23: {
        s32 a = appScriptGetInt(&args[1]);
        GSmodelUseRootJointAnimation(GSresGetResource(floorGetCurrentGroupID(), a), 1);
        break;
    }
    }
    return 0;
}

static void _appScriptModelSetVisibility(_GSmodel* model, void* flag) {
    GSmodelSetVisibility(model, flag != 0);
}

int AppScript::cmpLight(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10: {
        s32 a = appScriptGetInt(&args[1]);
        scriptLightSetDisp(a, appScriptGetInt(&args[2]));
        break;
    }
    case 0x11: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        scriptLightSetMotion(a, b, c, appScriptGetInt(&args[4]));
        break;
    }
    case 0x12:
        scriptLightStopMotion(appScriptGetInt(&args[1]));
        break;
    case 0x13: {
        s32 a = appScriptGetInt(&args[1]);
        appScriptSetInt(result, scriptLighgtWaitMotion(a, appScriptGetInt(&args[2])));
        break;
    }
    case 0x14: {
        GSlight* light = lightGetLight(appScriptGetInt(&args[1]));
        GSlightSetType(light, appScriptGetInt(&args[2]));
        break;
    }
    case 0x15: {
        GSlight* light = lightGetLight(appScriptGetInt(&args[1]));
        GSlightSetPosition(light, appScriptGetVec(&args[2]));
        break;
    }
    case 0x16: {
        GSlight* light = lightGetLight(appScriptGetInt(&args[1]));
        AppScriptColor color = appScriptGetColor(&args[2]);
        GSlightSetColor(light, &color);
        break;
    }
    case 0x17: {
        f32 pos[3];
        GSlightGetPosition(lightGetLight(appScriptGetInt(&args[1])), (GSvec*)pos);
        appScriptCopyVec(&work()->vec, pos);
        work()->ret.value.vector = &work()->vec;
        work()->ret.type = 4;
        break;
    }
    }
    return 0;
}

int AppScript::cmpFight(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, scriptEncount(a, b != 0, appScriptGetInt(&args[3])));
        break;
    }
    case 0x11:
        appScriptSetInt(result, fightEncount(appScriptGetInt(&args[1])));
        break;
    case 0x12:
        appScriptSetInt(result, fightGetFightResultId());
        break;
    case 0x13:
        fightSoundOpenPlay(appScriptGetInt(&args[1]) != 0);
        break;
    case 0x14:
        fightSoundOpenPlayEnv(appScriptGetInt(&args[1]) != 0);
        break;
    case 0x15:
        if (darkPokemonGetDarkPokemon((u16)appScriptGetInt(&args[1]))->getStatus() > darkStatus2) {
            fightEncount(appScriptGetInt(&args[2]));
        } else {
            fightEncount(appScriptGetInt(&args[3]));
        }
        break;
    case 0x16:
        result->value.pointer = fightEncountGetStrObj();
        break;
    case 0x17:
        appScriptEncountForWrite()->setField(appScriptGetInt(&args[1]));
        break;
    case 0x18:
        appScriptSetInt(result, fightEncountGetStrObj()->getField());
        break;
    case 0x19: {
        FIGHT_ENCOUNT* obj = fightEncountGetStrObj();
        appScriptSetInt(result, obj->getMsg(appScriptGetInt(&args[1])));
        break;
    }
    case 0x1A: {
        s32 a;
        FIGHT_ENCOUNT* obj = appScriptEncountForWrite();
        a = appScriptGetInt(&args[1]);
        obj->setMsg(a, appScriptGetInt(&args[2]));
        break;
    }
    case 0x1B:
        appScriptSetInt(result, fightEncountGetStrObj()->getAddMode());
        break;
    case 0x1C:
        appScriptSetInt(result, fightEncountGetStrObj()->getAddPlace());
        break;
    case 0x1D:
        appScriptSetInt(result, fightEncountGetStrObj()->getAddID());
        break;
    case 0x1E: {
        FIGHT_ENCOUNT* obj = appScriptEncountForWrite();
        obj->setAddMode(appScriptGetInt(&args[1]));
        obj->setAddPlace(appScriptGetInt(&args[2]));
        obj->setAddID(appScriptGetInt(&args[3]));
        break;
    }
    case 0x1F:
        appScriptSetInt(result, fightEncountGetStrObj()->getSwapMode());
        break;
    case 0x20:
        appScriptSetInt(result, fightEncountGetStrObj()->getSwapDeckNO());
        break;
    case 0x21: {
        FIGHT_ENCOUNT* obj = appScriptEncountForWrite();
        obj->setSwapMode(appScriptGetInt(&args[1]));
        obj->setSwapDeckNO((u8)appScriptGetInt(&args[2]));
        break;
    }
    case 0x22:
        appScriptSetInt(result, fightEncountGetStrObj()->getSwapDeckNO());
        break;
    case 0x23:
        appScriptEncountForWrite()->setFightMode(appScriptGetInt(&args[1]));
        break;
    case 0x24:
        appScriptSetInt(result, fightEncountGetStrObj()->getDestroyFlag());
        break;
    case 0x25:
        appScriptEncountForWrite()->setDestroyFlag(appScriptGetInt(&args[1]));
        break;
    case 0x26:
        appScriptSetInt(result, fightEncountGetStrObj()->getTrainerKind());
        break;
    case 0x27:
        appScriptEncountForWrite()->setTrainerKind(appScriptGetInt(&args[1]));
        break;
    case 0x28:
        fightEncountAnnihilationRecovery();
        break;
    case 0x29:
        appScriptSetInt(result, fightEncountGetStrObj()->getRoundNo());
        break;
    case 0x2A:
        appScriptEncountForWrite()->setRoundNo(appScriptGetInt(&args[1]));
        break;
    }
    return 0;
}

int AppScript::cmpFade(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10: {
        s32 id = appScriptGetInt(&args[1]);
        fadeSet(id, appScriptGetFloat(&args[2]));
        break;
    }
    case 0x11:
        appScriptSetInt(result, fadeCheck(appScriptGetInt(&args[1]) != 0));
        break;
    }
    return 0;
}

int AppScript::cmpTask(int cmd, tigaVariant* args, tigaVariant* result) {
    switch (cmd) {
    case 0x10: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        s32 d = appScriptGetInt(&args[4]);
        floorExecScriptInteger(a, b, c, d, appScriptGetInt(&args[5]));
        break;
    }
    case 0x11: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        s32 d = appScriptGetInt(&args[4]);
        floorExecScriptIntegerThread(a, b, c, d, appScriptGetInt(&args[5]));
        break;
    }
    case 0x12: {
        char* name = appScriptGetString(&args[1], (char*)field954);
        s32 a = appScriptGetInt(&args[2]);
        s32 b = appScriptGetInt(&args[3]);
        s32 c = appScriptGetInt(&args[4]);
        floorExecScriptIntegerByName(name, a, b, c, appScriptGetInt(&args[5]));
        break;
    }
    case 0x13: {
        char* name = appScriptGetString(&args[1], (char*)field954);
        s32 a = appScriptGetInt(&args[2]);
        s32 b = appScriptGetInt(&args[3]);
        s32 c = appScriptGetInt(&args[4]);
        floorExecScriptIntegerByNameThread(name, a, b, c, appScriptGetInt(&args[5]));
        break;
    }
    case 0x14:
        appScriptSetInt(result, floorGetScriptResult());
        break;
    case 0x15:
        scriptWaitTime(appScriptGetFloat(&args[1]));
        break;
    }
    return 0;
}

int AppScript::cmpPokemon(int cmd, tigaVariant* args, tigaVariant* result) {
    Pokemon* p;
    if (cmd != 0x10) {
        if (args->type != 0x25) {
            appScriptSetInt(result, 0);
            return 1;
        }
        p = appScriptGetPokemon(args);
    }
    switch (cmd) {
    case 0x10:
        scriptPlayPokemonNakigoe(appScriptGetInt(&args[1]));
        break;
    case 0x13:
        pokemonPlayVoice(p);
        break;
    case 0x12: {
        s32 a = appScriptGetInt(&args[1]);
        pokemonWazaCopy(p, a, appScriptGetInt(&args[2]));
        break;
    }
    case 0x11:
        pokemonWazaForget(p, appScriptGetInt(&args[1]));
        break;
    case 0x14:
        appScriptSetInt(result, pokemonGetWazaCount(p));
        break;
    case 0x15:
        appScriptSetInt(result, pokemonBiosGetCatchBallId(p));
        break;
    case 0x16:
        appScriptSetVar(result, 8, pokemon_GetNicknamePtr(p));
        break;
    case 0x18:
        appScriptSetInt(result, pokemonBiosGetDarkFlag(p));
        break;
    case 0x19:
        appScriptSetInt(result, pokemonBiosGetPokemonWazaDataId(p, appScriptGetInt(&args[1])));
        break;
    case 0x1A:
        appScriptSetInt(result, pokemonBiosGetHp(p));
        break;
    case 0x1B:
        appScriptSetInt(result, pokemonBiosGetDp(p));
        break;
    case 0x1C:
        appScriptSetInt(result, pokemonBiosGetPokemonDataId(p));
        break;
    case 0x1D:
        appScriptSetInt(result, p->isLegend());
        break;
    case 0x1E:
        appScriptSetInt(result, pokemonBiosGetFriend(p));
        break;
    case 0x1F:
        appScriptSetVar(result, 1, pokemonDB_GetName(pokemonBiosGetPokemonDataId(p)));
        break;
    case 0x20:
        appScriptSetInt(result, pokemonBiosGetItemDataId(p));
        break;
    case 0x21:
        appScriptSetInt(result, pokemonBiosGetCatchTrainerRnd(p));
        break;
    case 0x22: {
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        appScriptSetInt(result, pokemonSetWazaStatus(p, a, b != 0));
        break;
    }
    case 0x23:
        appScriptSetInt(result, scriptPokemonRememberWaza(p, appScriptGetInt(&args[1])));
        break;
    case 0x24:
        appScriptSetInt(result, pokemonDB_GetTeachWaza(pokemonBiosGetPokemonDataId(p), scriptPokemonTeachWazaIndex(appScriptGetInt(&args[1]))));
        break;
    case 0x25:
        appScriptSetInt(result, menuPokemonStatusOpenWazaLearn(p, appScriptGetInt(&args[1])));
        break;
    case 0x26:
        appScriptSetInt(result, menuPokemonStatusOpenWazaLearnList(p, appScriptGetInt(&args[1])));
        break;
    }
    return 0;
}

int AppScript::commonCall(tigaVariant* args, tigaVariant* result) {
    s32 count;
    s32 id;
    id = appScriptGetInt(&args[0]);
    count = appScriptGetInt(&args[1]);
    floorGetCommonScript()->runParamsWait(id, &args[2], count, 0);
    return 1;
}

int AppScript::orFlagTest(tigaVariant* args) {
    u8 result;
    int i;
    char* fmt;
    i = 1;
    result = 0;
    fmt = appScriptGetString(args, (char*)field954);
    for (; *fmt != 0; fmt++) {
        if (*fmt == '0') {
            if (GSflagTest(appScriptGetInt(&args[i])) == 0) {
                result = 1;
            }
            i++;
        } else if (*fmt == '1') {
            if (GSflagTest(appScriptGetInt(&args[i])) == 1) {
                result = 1;
            }
            i++;
        } else {
            return -1;
        }
    }
    return result;
}

int AppScript::andFlagTest(tigaVariant* args) {
    u8 result;
    int i;
    char* fmt;
    i = 1;
    result = 1;
    fmt = appScriptGetString(args, (char*)field954);
    for (; *fmt != 0; fmt++) {
        if (*fmt == '0') {
            if (GSflagTest(appScriptGetInt(&args[i])) == 1) {
                result = 0;
            }
            i++;
        } else if (*fmt == '1') {
            if (GSflagTest(appScriptGetInt(&args[i])) == 0) {
                result = 0;
            }
            i++;
        } else {
            return -1;
        }
    }
    return result;
}

// AppScript::fncPrintf (0x4AC bytes) is not recovered yet.

int AppScript::setExtendVariable(tigaVariant*, int, int) {
    return 0;
}

int AppScript::getExtendVariable(tigaVariant* var, int id, int) {
    if (id >= 0x80 && id <= 0x120) {
        appScriptSetVar(var, 0x23, (GSresID*)resIdTable + (id - 0x80));
        return 1;
    }
    if (id >= 0x200 && id <= 0x2FF) {
        int idx = id - 0x200;
        if (idx >= 0 && idx < field968) {
            appScriptSetVar(var, 7, (void*)((s32*)field96C)[idx]);
        } else {
            var->type = 1;
            var->value.integer = 0;
        }
        return 1;
    }
    return 0;
}

int AppScript::execExtendGlobalFunction(int cmd, tigaVariant* args, tigaVariant* result) {
    GSresID rid;
    switch (cmd) {
    case 0x81: {
        u32 id = appScriptGetInt(&args[0]);
        if (id != 0 && id <= *flag_data_number) {
            GSflagOn(id);
        }
        break;
    }
    case 0x82: {
        u32 id = appScriptGetInt(&args[0]);
        if (id != 0 && id <= *flag_data_number) {
            GSflagOff(id);
        }
        break;
    }
    case 0x83: {
        u32 id = appScriptGetInt(&args[0]);
        s32 value = appScriptGetInt(&args[1]);
        if (id != 0 && id <= *flag_data_number) {
            GSflagSet(id, value);
        }
        break;
    }
    case 0x84: {
        u32 id = appScriptGetInt(&args[0]);
        if (id != 0 && id <= *flag_data_number) {
            appScriptSetInt(result, GSflagTest(id));
        }
        break;
    }
    case 0x85: {
        u32 id = appScriptGetInt(&args[0]);
        if (id != 0 && id <= *flag_data_number) {
            appScriptSetInt(result, GSflagGet(id));
        }
        break;
    }
    case 0x88:
        fncPrintf(args);
        break;
    case 0x89:
        appScriptSetInt(result, scriptGetRandom(appScriptGetInt(&args[0])));
        break;
    case 0x8A: {
        s32 a = appScriptGetInt(&args[0]);
        darkPokemonBiosSetInfomation(a, appScriptGetInt(&args[1]));
        break;
    }
    case 0x8B:
        appScriptSetInt(result, andFlagTest(args));
        break;
    case 0x8C:
        appScriptSetInt(result, orFlagTest(args));
        break;
    case 0x8E:
        commonCall(args, result);
        break;
    case 0x8F:
        floorSetDispScriptInfo(appScriptGetInt(&args[0]) != 0);
        break;
    case 0x91:
        floorSetHumanColision(appScriptGetInt(&args[0]) != 0);
        break;
    case 0x92:
        appScriptSetInt(result, floorGetHumanColision());
        break;
    case 0x93: {
        s32 a = appScriptGetInt(&args[0]);
        peopleSetTresureSearchDistance(a, appScriptGetFloat(&args[1]));
        break;
    }
    case 0x94:
        appScriptSetVar(result, 8, GSmsgGetGSchar(appScriptGetInt(&args[0])));
        break;
    case 0x95: {
        rid.group = floorGetCurrentGroupID();
        rid.id = floorTresureGetResID(appScriptGetInt(&args[0]));
        appScriptSetResource(result, &rid);
        break;
    }
    case 0x96:
        appScriptSetVar(result, 1, pokemonDB_GetName(appScriptGetInt(&args[0])));
        break;
    case 0x97: {
        tigaArrayFixed* array;
        if (args->type == 7) {
            array = (tigaArrayFixed*)args->value.pointer;
        } else {
            tigaErrMessage("pokemon not access");
            array = 0;
        }
        appScriptSetInt(result, appScriptGetInt(array->get(appScriptGetInt(&args[1]))));
        break;
    }
    case 0x98:
        appScriptSetInt(result, wazaDB_GetHidenFlag(appScriptGetInt(&args[0])));
        break;
    case 0x99: {
        GSvec* a = appScriptGetVec(&args[1]);
        appScriptSetFloat(result, PSVECDistance(appScriptGetVec(&args[0]), a));
        break;
    }
    case 0x9A: {
        if (args->type == 0x23) {
            GSresID* r;
            if (args->type == 0x23) {
                r = (GSresID*)args->value.pointer;
            } else {
                tigaErrMessage("resource not access");
                r = 0;
            }
            GSresFreeResource(floorGetCurrentGroupID(), r->id);
        } else if (args->type == 1) {
            s32 id = appScriptGetInt(args);
            GSresFreeResource(floorGetCurrentGroupID(), id);
        }
        break;
    }
    case 0x9B: {
        f32 scale = appScriptGetFloat(&args[0]);
        s32 a = appScriptGetInt(&args[1]);
        s32 b = appScriptGetInt(&args[2]);
        s32 c = appScriptGetInt(&args[3]);
        s32 d = appScriptGetInt(&args[4]);
        scriptGlowStart(a, b != 0, c != 0, d != 0, appScriptGetInt(&args[5]), scale);
        break;
    }
    case 0x9C:
        scriptGlowEnd();
        break;
    case 0x9D: {
        s32 id = appScriptGetInt(&args[0]);
        f32 visible = appScriptGetFloat(&args[1]);
        f32 x = appScriptGetFloat(&args[2]);
        f32 y = appScriptGetFloat(&args[3]);
        scriptSetLensFlare(id, visible != 0.0f, x, y, appScriptGetFloat(&args[4]));
        break;
    }
    case 0x9E: {
        rid.group = floorGetCurrentGroupID();
        rid.id = appScriptGetInt(&args[0]);
        appScriptSetResource(result, &rid);
        break;
    }
    case 0x9F:
        appScriptSetFloat(result, GSgfxVideoGetVsyncRate());
        break;
    case 0xA0:
        appScriptSetInt(result, pokecoloGetCountryCode());
        break;
    case 0xA1:
        appScriptSetInt(result, pokecoloGetLanguage());
        break;
    }
    return 0;
}

int AppScript::execExtendMethod(int group, int cmd, tigaVariant* args, tigaVariant* result) {
    int ret = 0;
    switch (group) {
    case 0x23:
        ret = cmpPeople(cmd, args, result);
        break;
    case 0x21:
        ret = cmpCamera(cmd, args, result);
        break;
    case 0x25:
        ret = cmpPokemon(cmd, args, result);
        break;
    case 0x26:
        ret = cmpFloor(cmd, args, result);
        break;
    case 0x27:
        ret = cmpTask(cmd, args, result);
        break;
    case 0x28:
        ret = cmpMenu(cmd, args, result);
        break;
    case 0x29:
        ret = cmpFade(cmd, args, result);
        break;
    case 0x2A:
        ret = cmpFight(cmd, args, result);
        break;
    case 0x2B:
        ret = cmpHero(cmd, args, result);
        break;
    case 0x2C:
        ret = cmpLight(cmd, args, result);
        break;
    case 0x2D:
        ret = cmpModel(cmd, args, result);
        break;
    case 0x2E:
        ret = cmpCol(cmd, args, result);
        break;
    case 0x2F:
        ret = cmpSound(cmd, args, result);
        break;
    case 0x30:
        ret = cmpPad(cmd, args, result);
        break;
    case 0x31:
        ret = cmpMail(cmd, args, result);
        break;
    case 0x32:
        ret = cmpDirection(cmd, args, result);
        break;
    case 0x33:
        ret = cmpTv(cmd, args, result);
        break;
    case 0x34:
        ret = cmpSodateya(cmd, args, result);
        break;
    case 0x3A:
        ret = cmpWaza(cmd, args, result);
        break;
    case 0x3B:
        ret = cmpDarkPokemon(cmd, args, result);
        break;
    case 0x3C:
        ret = cmpEsaba(cmd, args, result);
        break;
    }
    return ret;
}

void AppScript::unload() {
    tigaWaza* p;
    for (p = &waza[0]; p != &waza[7]; p++) {
        if (p->wazaSequence != 0 || p->sequence != 0) {
            if (p->wazaSequence != 0) {
                WazaSequence_Stop(p->wazaSequence);
                WazaSequence_Free(p->wazaSequence);
            }
            if (p->sequence != 0) {
                Sequence_Free(p->sequence);
            }
            field934--;
            p->sequence = 0;
            p->wazaSequence = 0;
        }
    }
}

void AppScript::freeWazaPtr(tigaWaza* target) {
    tigaWaza* p;
    if (target == 0) {
        return;
    }
    for (p = &waza[0]; p != &waza[7]; p++) {
        if (p == target) {
            target->sequence = 0;
            target->wazaSequence = 0;
        }
    }
}

tigaWaza* AppScript::allocWazaPtr() {
    tigaWaza* p;
    for (p = &waza[0]; p != &waza[7]; p++) {
        if (p->sequence == 0) {
            p->sequence = 0;
            p->wazaSequence = 0;
            return p;
        }
    }
    return 0;
}

void AppScript::unmapping() {}

void AppScript::mapping() {
    memset(waza, 0, sizeof(waza));
}

AppScript::~AppScript() {}

AppScript::AppScript() {
    memset(waza, 0, sizeof(waza));
}

AppScript* scriptCreateAppScript() {
    return new AppScript;
}
