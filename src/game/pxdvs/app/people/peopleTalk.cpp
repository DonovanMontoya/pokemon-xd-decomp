#include <game/pxdvs/app/people/runtime.hpp>
struct FloorData;struct FloorCharacter;struct FloorBgmMask {u8 pad[4];u8 enabled;void endMask();void startMask();void setVolumeRate(f32);void setFadeInTime(f32);void setFadeOutTime(f32);};struct TalkResource {u32 group,resource;};
TalkResource _peopleTalkRes;f32 _talkWindowCloseDelay;
extern "C" {tagPeopleWork*peopleGet(u32,u32);u32 peopleGetFlags(u32,u32);void peopleRotateToAngle(u32,u32,f32,f32);s8 peopleSetNeckLimitHold(u32,u32,u8);void peopleSpeakStart(u32,u32);void peopleRotateToTarget(u32,u32,u32,u32,f32);void peopleRotateCheck(u32,u32,s32);void fn_8029CD20(u32,u32,u32,u32,f32);void peopleCheckNeckRotate(u32,u32,s32);void GSthreadSwitch();void GSflagOn(s32);u8 GSflagTest(s32);FloorData*floorDataBiosGetCurrentPtr();u8 floorDataBiosGetFloorKind(FloorData*);FloorBgmMask*floorSound_getBgmMaskObj();f32 timeGetLastFrameSec();s32 winMsgCheckField();void winMsgClose(s32);void winMsgOpenFieldWithSE(s32,s32,s32,s32);void msgctrlSetValue(s32,u32);FloorCharacter*floorCharacterBiosFindByResID(u32,u32);u32 floorCharacterBiosGetNameID(FloorCharacter*);u16 charNameBiosGetHearFlag(u32);u32 charNameBiosGetNameID(u32);s32 peopleInfoBiosGetTalkSe(PeopleInfo*);}
extern "C" void peopleSetTalkDistance(u32 group,u32 resource,f32 farg0) {
    tagPeopleWork *temp_r3;

    temp_r3 = peopleGet(group,resource);
    if (temp_r3 != NULL) {
        temp_r3->treasureSearchDistance = farg0;
    }
}

extern "C" f32 peopleGetTalkDistance(u32 group,u32 resource) {
    tagPeopleWork *temp_r3;

    temp_r3 = peopleGet(group,resource);
    if (temp_r3 == NULL) {
        return 0.0f;
    }
    return temp_r3->treasureSearchDistance;
}

extern "C" void peopleTalkLeaveFloor(void) {

}

extern "C" void peopleTalkEnterFloor(void) {
    _talkWindowCloseDelay = 0.0f;
}

extern "C" void peopleTalkMessageDaemon(void) {
    FloorData*data=floorDataBiosGetCurrentPtr();
    if ((floorDataBiosGetFloorKind(data) == 1) && (_talkWindowCloseDelay > 0.0f)) {
        _talkWindowCloseDelay -= timeGetLastFrameSec();
    }
}

extern "C" void peopleTalkMessageBgmStop(void) {
    FloorBgmMask*mask=floorSound_getBgmMaskObj();
    if (mask != NULL) {
        mask->endMask();
    }
}

extern "C" void peopleTalkMessageBgmStart(void) {
    FloorBgmMask*mask=floorSound_getBgmMaskObj();
    if (mask != NULL) {
        mask->startMask();
    }
}

extern "C" void peopleTalkMessageBgmSetVolumeRate(f32 farg0) {
    FloorBgmMask*mask=floorSound_getBgmMaskObj();
    if (mask != NULL) {
        mask->setVolumeRate(farg0);
    }
}

extern "C" void peopleTalkMessageBgmSetFadeSpeed(f32 farg0, f32 farg1) {
    FloorBgmMask *temp_r3;

    temp_r3 = floorSound_getBgmMaskObj();
    if (temp_r3 != NULL) {
        temp_r3->setFadeInTime(farg0);
        temp_r3->setFadeOutTime(farg1);
    }
}

extern "C" void peopleTalkMessageBgmMask(u8 arg0) {
    FloorBgmMask *temp_r3;

    temp_r3 = floorSound_getBgmMaskObj();
    if (temp_r3 != NULL) {
        if (arg0 != 0) {
            temp_r3->enabled = 1;
            return;
        }
        temp_r3->enabled = 0;
    }
}

extern "C" void peopleTalkMsgEnd(u32 arg0, u32 arg1) {
    u32 temp_r3_2;
    tagPeopleWork *temp_r3;

    winMsgClose(1);
    _talkWindowCloseDelay = 0.2f;
    temp_r3 = peopleGet(arg0, arg1);
    if (temp_r3 != NULL) {
        temp_r3_2 = peopleGetFlags(arg0, arg1);
        if ((u8) temp_r3->unknownA0[0] != 0) {
            temp_r3->unknownA0[0] = 0U;
            if (temp_r3_2 & 0x20) {
                if (temp_r3_2 & 0x40) {
                    peopleRotateToAngle(arg0, arg1, *(f32*)(temp_r3->unknownA0+4), 1.0f);
                }
            } else if (temp_r3_2 & 0x10) {
                temp_r3->neckTargetPosition.param1 = (f32) temp_r3->unknownEC.param1;
                temp_r3->neckTargetPosition.param2 = (f32) temp_r3->unknownEC.param2;
                temp_r3->neckTargetPosition.param3 = (f32) temp_r3->unknownEC.param3;
                temp_r3->neckEnabled = 1;
                peopleSetNeckLimitHold(arg0, arg1, temp_r3->unknownA0[1]);
            }
        }
    }
    while(winMsgCheckField()!=-1)GSthreadSwitch();
    _peopleTalkRes.group = 0;
    _peopleTalkRes.resource = 0;
    msgctrlSetValue(0x59, 0x1772);
}

extern "C" void peopleSetTalkFlagCallback(void) {
    u32 var_r31;
    u32 temp_r30;
    u16 temp_r3;

    if (((u32) _peopleTalkRes.group == 0U) && ((u32) _peopleTalkRes.resource == 0U)) {
        msgctrlSetValue(0x59, 0x1772);
        return;
    }
    var_r31 = 0x1772;
    FloorCharacter*character=floorCharacterBiosFindByResID(_peopleTalkRes.group,_peopleTalkRes.resource);
    if (character) {
        temp_r30 = floorCharacterBiosGetNameID(character);
        temp_r3 = charNameBiosGetHearFlag(temp_r30);
        if (temp_r3 != 0) {
            GSflagOn(temp_r3);
            var_r31 = charNameBiosGetNameID(temp_r30);
        }
    }
    msgctrlSetValue(0x59, var_r31);
}

extern "C" void peopleSetTalkKeyWaitCallback(void) {
    if (((u32) _peopleTalkRes.group != 0U) || ((u32) _peopleTalkRes.resource != 0U)) {
        peopleSpeakStart(_peopleTalkRes.group,_peopleTalkRes.resource);
    }
}

extern "C" void peopleTalkMsg(u32 arg0, u32 arg1, s32 arg2) {
    u32 var_r28;
    u32 temp_r27;
    u32 temp_r3_2;
    u32 var_r31;
    u16 temp_r3_3;
    tagPeopleWork *temp_r3;
    FloorBgmMask *temp_r3_4;

    var_r31 = 0;
    temp_r3 = peopleGet(arg0,arg1);
    if (temp_r3 != NULL) {
        if (temp_r3 != NULL) {
            temp_r3_2 = peopleGetFlags(arg0, arg1);
            if (temp_r3_2 & 0x20) {
                if ((u8) temp_r3->unknownA0[0] == 0) {
                    *(f32*)(temp_r3->unknownA0+4) = (f32) temp_r3->targetRotation;
                    temp_r3->unknownA0[0] = 1U;
                }
                peopleRotateToTarget(arg0, arg1, 0, 0x64, 1.0f);
                peopleRotateCheck(arg0, arg1, 1);
            } else if ((temp_r3_2 & 0x10) && ((u8) temp_r3->unknownA0[0] == 0)) {
                temp_r3->unknownEC.param1 = (f32) temp_r3->neckTargetPosition.param1;
                temp_r3->unknownEC.param2 = (f32) temp_r3->neckTargetPosition.param2;
                temp_r3->unknownEC.param3 = (f32) temp_r3->neckTargetPosition.param3;
                fn_8029CD20(arg0, arg1, 0, 0x64, 2.0f);
                temp_r3->unknownA0[1] = peopleSetNeckLimitHold(arg0, arg1, 1U);
                peopleCheckNeckRotate(arg0, arg1, 1);
                temp_r3->unknownA0[0] = 1U;
            }
            PeopleInfo*info=peopleInfoBiosGetPtr(temp_r3->object);
            if (info) {
                var_r31 = peopleInfoBiosGetTalkSe(info);
            }
            var_r28 = 0x1772;
            FloorCharacter*character=floorCharacterBiosFindByResID(temp_r3->group,temp_r3->resource);
            if (character) {
                temp_r27 = floorCharacterBiosGetNameID(character);
                temp_r3_3 = charNameBiosGetHearFlag(temp_r27);
                if (temp_r3_3 == 0) {
                    var_r28 = 0x1772;
                } else if (GSflagTest(temp_r3_3) == 1) {
                    var_r28 = charNameBiosGetNameID(temp_r27);
                }
            }
            msgctrlSetValue(0x59, var_r28);
        }
        while(_talkWindowCloseDelay>0.0f)GSthreadSwitch();
        _peopleTalkRes.group = (u32) temp_r3->group;
        _peopleTalkRes.resource = (s32) temp_r3->resource;
        temp_r3_4 = floorSound_getBgmMaskObj();
        if (temp_r3_4 != NULL) {
            temp_r3_4->startMask();
            winMsgOpenFieldWithSE(arg2, 1, 0, var_r31);
            temp_r3_4->endMask();
        }
    }
}

extern "C" {GSvec*peopleBiosGetPosPtr(tagPeopleWork*);bool peopleBiosCheckFlag(tagPeopleWork*,u32);f32 peopleInfoBiosGetColBallSize(PeopleInfo*);void peopleGetPos(u32,u32,GSvec*);void peopleGetNeckPos(u32,u32,GSvec*);void peopleBiosGetRot(tagPeopleWork*,GSvec*);u8 heroMoveIsMember(s32);void heroMoveGetResID(u32*,u32*,s32);u8 floorCharacterBiosGetTalkStartType(FloorCharacter*);u8 floorCharacterBiosGetTalkWallThrough(FloorCharacter*);u8*floorEventGetTresureList(u32);f32 PSVECDistance(GSvec*,GSvec*);f32 peopleVecCalcRotY(GSvec*,GSvec*,f32);u8 gimmickBoxIsPushBoxFloor();u8 GScolsys2HitCollision(GSvec*,GSvec*,s32,f32);u8 peopleInsideCheck(GSvec*,GSvec*,GSvec*,f32);double fabs(double);void GSlogWritef(const char*,...);}
extern "C" tagPeopleWork*peopleTalkCheck(u32 group,u32 resource,f32 unused,f32 angleLimit){
 GSvec rotation,target,origin,member={0,0,0};u32 memberResource=0,memberGroup=0;tagPeopleWork*best=0;f32 bestScore=10000.0f,bestAngle;f32 radius;
 tagPeopleWork*hero=peopleGet(group,resource);if(!hero)return 0;origin=*peopleBiosGetPosPtr(hero);PeopleInfo*heroInfo=peopleInfoBiosGetPtr(hero->object);if(heroInfo)radius=peopleInfoBiosGetColBallSize(heroInfo);else radius=4.0f;
 u32 hasMember=heroMoveIsMember(1)!=0;heroMoveGetResID(&memberGroup,&memberResource,1);if(hasMember)peopleGetPos(memberGroup,memberResource,&member);
 for(s32 i=0;i<peopleBiosGetMaxNum();i++){
  tagPeopleWork*person=peopleBiosGetWorkPtr(i);if(!person->used||person==hero||!person->visible||peopleBiosCheckFlag(person,1))continue;
  FloorCharacter*character=floorCharacterBiosFindByResID(person->group,person->resource);if(character&&floorCharacterBiosGetTalkStartType(character)==3)continue;
  PeopleInfo*info=peopleInfoBiosGetPtr(person->object);if(!info)continue;peopleGetNeckPos(person->group,person->resource,&target);f32 distance=PSVECDistance(&origin,&target);f32 otherRadius=peopleInfoBiosGetColBallSize(info);if(distance>radius+peopleGetTalkDistance(person->group,person->resource)+otherRadius)continue;
  f32 angle=peopleVecCalcRotY(&origin,&target,hero->targetRotation);if((f32)fabs(angle)>0.017453292f*angleLimit)continue;if(gimmickBoxIsPushBoxFloor()&&(s32)(origin.param2/10.0f)!=(s32)(target.param2/10.0f))continue;
  u8 checkWall;if(character)checkWall=floorCharacterBiosGetTalkWallThrough(character)==0;else{u8*treasure=floorEventGetTresureList(person->resource);if(treasure&&((*treasure>>5)&7)==1){peopleBiosGetRot(person,&rotation);if((f32)fabs(peopleVecCalcRotY(&target,&origin,rotation.param2))>2.0943952f)continue;}checkWall=0;}
  if(checkWall&&GScolsys2HitCollision(&origin,&target,0,radius))continue;if(hasMember&&peopleInsideCheck(&origin,&target,&member,peopleInfoBiosGetColBallSize(info)))continue;
  f32 score=distance*distance*(f32)fabs(angle)*0.5f;GSlogWritef("talk ->  people(%d,%d)  len =%.2f  ang =%.2f  area =%.2f\n",person->group,person->resource,distance,angle,score);
  u8 replace=0;if(score<bestScore)replace=1;else if(score==bestScore){f32 magnitude=(f32)fabs(angle),oldMagnitude=(f32)fabs(bestAngle);if(oldMagnitude<magnitude)replace=1;else if(oldMagnitude==magnitude&&angle>0.0f)replace=1;}if(replace){bestScore=score;best=person;bestAngle=angle;}
 }
 return best;
}
