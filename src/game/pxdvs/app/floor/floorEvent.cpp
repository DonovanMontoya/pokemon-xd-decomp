#include <game/pxdvs/app/floor/floorEventPrivate.hpp>
static FloorEventME _playMEParam;
void _floorEventWaitMotion(_GSmodel *);
void _floorEventSetMotion(_GSmodel *, s16, f32);
static void _floorEventWaitME();
static s32 _floorEventPlayMEThread(GSthread *);
extern "C" {
FloorEventTreasure *floorEventGetTresureList(u32 resourceID) {
    FloorEventTreasure *treasure;
    u32 index;
    u32 localIndex;
    u32 wantedIndex;
    treasure = 0;
    localIndex = 0;
    if ((resourceID & 0x7FFF0000) != 0x7FFF0000) return 0;
    wantedIndex = resourceID & 0x1FF;
    index = 0;
    for (; index < *floor_tresure_list_number; ++index) {
        treasure = &floor_tresure_list[index];
        if (treasure->floorID == GSfloorGetCurrent() && wantedIndex == localIndex++) break;
    }
    if (index == *floor_tresure_list_number) return 0;
    return treasure;
}
void floorEventSetTresureDisp(u32 index, s32 display) {
    FloorEventTreasure *treasure;
    u32 i;
    u32 localIndex;
    u32 resourceID;
    localIndex = 0;
    i = 0;
    for (; i < *floor_tresure_list_number; ++i) {
        treasure = &floor_tresure_list[i];
        if (treasure->floorID == GSfloorGetCurrent()) {
            if (i == index) { resourceID = localIndex | 0x7FFF0000; break; }
            ++localIndex;
        }
    }
    if (i != *floor_tresure_list_number) peopleSetDisp(floorGetCurrentGroupID(), resourceID, display);
}
s32 floorEventChangeTresure(u32 index, u16 reward, s8 quantity) {
    if (index >= *floor_tresure_list_number) {
        GSlogWrite("[%s] Range Over!!\n", __FUNCTION__);
        return -1;
    }
    FloorEventTreasure *treasure = &floor_tresure_list[index];
    treasure->rewardID = reward;
    treasure->signedQuantity = quantity;
    return 0;
}
s32 floorEventGetTresureEx(u8 type, s32 reward, s32 quantity, u8 playME) {
    s32 remaining;
    u32 message = 0;
    u8 overflow = 0;
    for (;;) {
        if (GSsndGetStatus(0x3CE) != 2) break;
        GSthreadSwitch();
    }
    if (playME == 1) {
        soundPlayWait(0x3CE);
        _playMEParam.soundID = 0x3CE;
        _playMEParam.playing = 1;
        floorCreateThread(0x80, 0, 1, _floorEventPlayMEThread);
    }
    switch (type) {
    case 3: break;
    case 2:
        msgctrlSetValue(0x4B, reward);
        winMsgOpen(3, 0xD2F1, 1, 0);
        winMsgClose(1);
        heroAddPokedoru(0, reward);
        winMsgOpen(3, 0xD2F4, 1, 0);
        _floorEventWaitME();
        winMsgClose(1);
        break;
    case 4:
    case 1:
        if (quantity > 0) {
            msgctrlSetValue(0x2D, reward);
            msgctrlSetValue(0x2F, quantity);
            if (type == 1) {
                if (quantity == 1) message = 0xD2F2; else message = 0xD2F3;
                winMsgOpen(3, message, 1, 0);
                winMsgClose(1);
            }
            remaining = heroItemAddItemDataId(0, reward, quantity, -1);
            if (remaining == 0) {
                if (quantity == 1) message = 0xD2F5; else message = 0xD2F6;
            } else if (remaining > 0) {
                remaining = pcboxAddItem(0, reward, remaining);
                if (remaining != 0) overflow = 1;
                if (quantity == 1) message = 0xD2F7; else message = 0xD2F8;
            }
            winMsgOpen(3, message, 1, 0);
            if (overflow == 1) winMsgOpen(3, 0xD2F9, 1, 0);
            _floorEventWaitME();
            winMsgClose(1);
        }
        break;
    }
    _floorEventWaitME();
    return remaining;
}
s32 floorEventGetTresure(u8 type, s32 reward, s32 quantity) {
    s32 remaining;
    s32 added;
    u32 message;
    s32 stored = 0;
    soundPlayWait(0x3CE);
    _playMEParam.soundID = 0x3CE;
    _playMEParam.playing = 1;
    floorCreateThread(0x80, 0, 1, _floorEventPlayMEThread);
    switch (type) {
    case 3: break;
    case 2:
        msgctrlSetValue(0x4B, reward);
        winMsgOpen(3, 0xD2F1, 1, 0);
        winMsgClose(1);
        heroAddPokedoru(0, reward);
        winMsgOpen(3, 0xD2F4, 1, 0);
        _floorEventWaitME();
        winMsgClose(1);
        break;
    case 4:
    case 1:
        if (quantity > 0) {
            msgctrlSetValue(0x2D, reward);
            msgctrlSetValue(0x2F, quantity);
            if (type == 1) {
                if (quantity == 1) message = 0xD2F2; else message = 0xD2F3;
                winMsgOpen(3, message, 1, 0);
                winMsgClose(1);
            }
            remaining = heroItemAddItemDataId(0, reward, quantity, -1);
            added = quantity - remaining;
            if (remaining > 0) {
                remaining = pcboxAddItem(0, reward, remaining);
                stored = (quantity - remaining) - added;
            }
            if (added > 0) {
                if (quantity == 1) message = 0xD2F5; else message = 0xD2F6;
                msgctrlSetValue(0x2F, added);
                winMsgOpen(3, message, 1, 1);
                winMsgClose(1);
            }
            if (quantity - added > 0) {
                if (stored != 0) {
                    if (quantity == 1) { message = 0xD2F7; msgctrlSetValue(0x2F, stored); }
                    else if (added == 0) { message = 0xD2F8; msgctrlSetValue(0x2F, quantity); }
                    else { message = 0xD2FA; msgctrlSetValue(0x2F, quantity - added); }
                } else { message = 0xD2FA; msgctrlSetValue(0x2F, quantity - added); }
                winMsgOpen(3, message, 1, 1);
                winMsgClose(1);
            }
            if (quantity - added - stored > 0) {
                msgctrlSetValue(0x2F, quantity - added - stored);
                if (quantity == 1) message = 0xD2F9; else message = 0xD2FB;
                winMsgOpen(3, message, 1, 1);
                winMsgClose(1);
            }
            _floorEventWaitME();
        }
        break;
    }
    _floorEventWaitME();
    return remaining;
}
s32 floorEventCtrlTresure(u32 group, u32 resourceID, u8 control) {
    FloorEventTreasure *treasure = floorEventGetTresureList(resourceID);
    if (treasure == 0) return -1;
    switch (control) {
    case 0:
        switch (treasure->displayType) {
        case 1: peopleSetMotion(group, resourceID, 2, 0, 1); peopleSetFlagOn(group, resourceID, 1); break;
        case 2: case 3: peopleSetDisp(group, resourceID, 0); break;
        }
        break;
    case 1:
        switch (treasure->displayType) {
        case 1: peopleSetMotion(group, resourceID, 0, 0, 1);
        case 2: case 3: peopleSetMotion(group, resourceID, 0, 0, 1); break;
        }
        break;
    case 2:
        if (treasure->flagID != 0 && GSflagTest(treasure->flagID) != 0) return 0;
        switch (treasure->displayType) {
        case 1:
            peopleSetMotion(group, resourceID, 1, 0, 0);
            GSsndPlayNow(0x461);
            peopleWaitSyncMotion(group, resourceID, 1);
            break;
        case 2: case 3: break;
        }
        floorEventCtrlTresure(group, resourceID, 0);
        GSflagOn(treasure->flagID);
        floorEventGetTresure(treasure->rewardType, treasure->rewardID, treasure->quantity);
        break;
    }
    return 0;
}
s32 floorEventCtrlElevator(u32 floorID, u32 index, u16 control, u32 group, u32 person) {
    FloorEventDoor *door;
    _GSmodel *model;
    s8 motion = -1;
    f32 frame = 0.0f;
    GSvec position;
    __ct__5GSvecFv(&position);
    if (index >= *floor_door_list_number) return -1;
    door = &floor_door_list[index];
    if (door->resourceID == 0) return -1;
    model = floorGetResource(floorID);
    if (model == 0) return -1;
    u32 modelGroup = floorDataBiosGetGroupID(floorDataBiosGetPtr(floorID));
    switch (control) {
    case 1: case 2: case 0x81: case 0x82: {
        if (door->openMotion >= 0) _floorEventSetMotion(model, door->openMotion, frame);
        s32 sound = control & 0x80;
        if (sound != 0) GSsndPlayNow(0x27);
        _floorEventWaitMotion(model);
        GSpart *part = GSmodelGetPart(model, door->partIndex);
        GSpartGetTransform(part, &position, 0, 0);
        GSpartFree(part);
        if ((control & 1) != 0) {
            peopleWalkTo(group, person, 1, &position);
            peopleMoveCheck(group, person, 1);
            peopleRotateToAngle(group, person, 0.0f, 0.5f);
            peopleMoveCheck(group, person, 1);
        } else {
            peopleDetach(group, person, 0);
            peopleGetPos(group, person, &position);
            position.z += 25.0f;
            peopleWalkTo(group, person, 1, &position);
            peopleMoveCheck(group, person, 1);
        }
        if (door->closeMotion >= 0) _floorEventSetMotion(model, door->closeMotion, frame);
        if (sound != 0) GSsndPlayNow(0x27);
        _floorEventWaitMotion(model);
        break;
    }
    case 0xC0:
        _floorEventWaitMotion(model);
        if ((control & 0x80) != 0) { GSsndStopNow(0x29); GSsndPlayNow(0x2A); }
        break;
    default:
        if ((control & 4) != 0) motion = door->ascendMotion;
        else if ((control & 8) != 0) motion = door->descendMotion;
        if (motion < 0) return -1;
        if (GSmodelCanAnimate(model) == 0) return -1;
        if ((control & 0x20) != 0) {
            peopleAttach(group, person, modelGroup, door->resourceID, door->partIndex);
            peopleSetPosXYZ(group, person, 0.0f, 0.0f, 0.0f);
        }
        if ((control & 0x10) != 0) {
            GSmodelSetAnimIndex(model, motion);
            GSmodelGetFrameCount(model, &frame, 0);
            frame -= 1.0f;
        }
        _floorEventSetMotion(model, motion, frame);
        if ((control & 0x40) != 0) floorEventCtrlElevator(floorID, index, 0xC0, group, person);
        else if ((control & 0x80) != 0) GSsndPlayNow(0x29);
        break;
    }
    GSmodelGetFrameCount(model, &frame, 0);
    return static_cast<s32>(100.0f * ((2.0f * frame) / static_cast<f32>(GSgfxVideoGetVsyncRate())));
}
s32 floorEventCtrlDoor(u32 floorID, u32 index, u8 control) {
    s8 motion = -1;
    u32 soundID = 0;
    f32 frame = 0.0f;
    if (index >= *floor_door_list_number) return -1;
    FloorEventDoor *door = &floor_door_list[index];
    switch (control) {
    case 0:
        if (door->openFlag != 0 && GSflagTest(door->openFlag) != 0) return 0;
        if (door->requiredFlag != 0 && GSflagTest(door->requiredFlag) == 0) return 1;
    case 1:
        if (door->openFlag != 0) GSflagOn(door->openFlag);
        scriptSetCol(door->collisionID, 0);
        break;
    case 2:
        if (door->openFlag != 0 && GSflagTest(door->openFlag) == 0) return 0;
    case 3:
        if (door->openFlag != 0) GSflagOff(door->openFlag);
        scriptSetCol(door->collisionID, 1);
        break;
    }
    if (door->resourceID == 0) return -1;
    _GSmodel *model = floorGetResource(floorID);
    if (model == 0) return -1;
    switch (control) {
    case 0:
        motion = door->openMotion;
        switch (door->soundType) {
        case 1: soundID = 0x27; break;
        case 2: soundID = 0x27; break;
        case 3: soundID = 0x2B; break;
        case 4: soundID = 0x463; break;
        case 5: soundID = 0x52D; break;
        case 6: soundID = 0x561; break;
        }
        break;
    case 1:
        motion = door->openedMotion;
        if (motion < 0) {
            motion = door->openMotion;
            if (motion >= 0) { GSmodelSetAnimIndex(model, motion); GSmodelGetFrameCount(model, &frame, 0); frame -= 1.0f; }
        }
        break;
    case 2:
        motion = door->closeMotion;
        switch (door->soundType) {
        case 1: soundID = 0x27; break;
        case 2: soundID = 0x27; break;
        case 3: soundID = 0x2B; break;
        case 4: soundID = 0x26; break;
        case 5: soundID = 0x52D; break;
        case 6: soundID = 0x561; break;
        }
        break;
    case 3:
        motion = door->closedMotion;
        if (motion < 0) {
            motion = door->closeMotion;
            if (motion >= 0) { GSmodelSetAnimIndex(model, motion); GSmodelGetFrameCount(model, &frame, 0); frame -= 1.0f; }
        }
        break;
    }
    if (motion < 0) return -1;
    if (GSmodelCanAnimate(model) == 0) return -1;
    _floorEventSetMotion(model, motion, frame);
    if (soundID != 0) GSsndPlayNow(soundID);
    switch (control) {
    case 1: break;
    case 2: {
        u32 heroFlags = peopleGetFlags(0, 0x64);
        u32 partnerFlags = peopleGetFlags(0, 0x65);
        u32 secondFlags = peopleGetFlags(0, 0x69);
        u32 thirdFlags = peopleGetFlags(0, 0x68);
        heroMoveInitEvent();
        _floorEventWaitMotion(model);
        heroMoveTermEvent();
        peopleSetFlags(0, 0x64, heroFlags);
        peopleSetFlags(0, 0x65, partnerFlags);
        peopleSetFlags(0, 0x69, secondFlags);
        peopleSetFlags(0, 0x68, thirdFlags);
        break;
    }
    }
    return 0;
}
s32 floorEventExecScript(s8 type, u32 collisionID) {
    s32 count;
    u32 i;
    FloorEventScript *event;
    u32 floorID;
    s32 promotedType;
    count = 0;
    EvlogSet(type, collisionID);
    floorID = GSfloorGetCurrent();
    promotedType = type;
    for (i = 0; i < *floor_event_list_number; ++i) {
        event = &floor_event_list[i];
        if (event->floorID == floorID && event->type == promotedType && event->collisionID == collisionID && event->scriptID != 0) {
            scriptSetEventColID(collisionID);
            floorExecScriptInteger(event->scriptID, event->parameters[0], event->parameters[1], event->parameters[2], event->parameters[3]);
            ++count;
        }
    }
    return count;
}
}
void _floorEventWaitMotion(_GSmodel *model) {
    if (model == 0) return;
    while (GSmodelIsAnimating(model) != 0) GSthreadSwitch();
}
void _floorEventSetMotion(_GSmodel *model, s16 motion, f32 frame) {
    if (model != 0) {
        GSmodelSetAnimIndex(model, motion);
        GSmodelSetAnimFrame(model, frame);
        GSmodelSetAnimRate(model, 0.5f);
        GSmodelSetAnimType(model, 0);
        GSmodelStartAnimation(model);
    }
}
static void _floorEventWaitME() {
    while (_playMEParam.playing != 0) GSthreadSwitch();
    GSthreadSwitch();
}
static s32 _floorEventPlayMEThread(GSthread *) {
    scriptSoundOpenPlayME(_playMEParam.soundID, 0, 0xFF);
    _playMEParam.playing = 0;
    return 0;
}
