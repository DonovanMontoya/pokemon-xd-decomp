#include <game/pxdvs/app/script/objPeoplePrivate.hpp>
extern "C" {
__declspec(weak) void setRpVec__Q28GSscript4TigaFPC5GSvec(GSscript::Tiga *script,const GSvec *vector) {
    AppScriptWork *work=(AppScriptWork *)script->workBuffer;
    work->vec.param1=vector->param1;
    work->vec.param2=vector->param2;
    work->vec.param3=vector->param3;
    work=(AppScriptWork *)script->workBuffer;
    work->ret.value.vector=&work->vec;
    ((AppScriptWork *)script->workBuffer)->ret.type=4;
}
__declspec(weak) GSscript::tigaArrayFixed *getArray__Q28GSscript11tigaVariantFv(GSscript::tigaVariant *value) {
    if (value->type==7) return (GSscript::tigaArrayFixed *)value->value.pointer;
    GSscript::tigaErrMessage("pokemon not access");
    return 0;
}
__declspec(weak) GSvec *getVector__Q28GSscript11tigaVariantFv(GSscript::tigaVariant *value) {
    if (value->type==4) return value->value.vector;
    return value->getCnvVector();
}
__declspec(weak) f32 getSingle__Q28GSscript11tigaVariantFv(GSscript::tigaVariant *value) {
    if(value->type==1)return (f32)value->value.integer;
    if(value->type==2)return value->value.single;
    return value->getCnvSingle();
}
__declspec(weak) s32 getInteger__Q28GSscript11tigaVariantFv(GSscript::tigaVariant *value) {
    if(value->type==1)return value->value.integer;
    if(value->type==2)return (s32)value->value.single;
    return value->getCnvInteger();
}
__declspec(weak) GSresID *getPeople__Q28GSscript11tigaVariantFv(GSscript::tigaVariant *value) {
    if (value->type==0x23) return (GSresID *)value->value.pointer;
    GSscript::tigaErrMessage("people not access");
    return 0;
}
}

static u8 _pokeRareCol[9][8]={
 {0,1,2,3,0x75,0x9D,0x62,255},{1,2,2,3,0x77,0x80,0x9D,255},
 {2,1,2,3,127,127,127,255},{1,2,0,3,0x4E,0xB0,0x28,255},
 {0,1,2,3,0x7D,0xA8,0xA2,255},{1,1,2,3,0x61,0x61,0x61,255},
 {0,2,0,3,127,127,127,255},{2,0,0,3,0x99,0xAA,0x93,255},
 {2,0,2,3,0x91,0x91,0x91,255}
};
#define I(N) getInteger__Q28GSscript11tigaVariantFv(&args[N])
#define F(N) getSingle__Q28GSscript11tigaVariantFv(&args[N])
#define V(N) getVector__Q28GSscript11tigaVariantFv(&args[N])
#define H(N) getPeople__Q28GSscript11tigaVariantFv(&args[N])
#define A(N) getArray__Q28GSscript11tigaVariantFv(&args[N])
#define P person->group,person->id
#define R(E) appScriptSetInt(result,(E))
struct ScriptPeopleVector {f32 param1,param2,param3;};
int AppScript::cmpPeople(int method,GSscript::tigaVariant *args,GSscript::tigaVariant *result) {
    static ScriptPeopleVector Vector;
    static s8 init;
    s32 parts[6],motions[7];
    if(init==0)init=1;
    GSresID *person;
    if(method!=1){
        if(args[0].type!=0x23){R(0);return 1;}
        person=H(0);
    }else return 0;
    switch(method) {
    case 0x10:peopleSetDisp(P,(bool)I(1));break;
    case 0x11:{s32 blend;u8 loop;loop=(bool)I(3);blend=I(2);R(peopleSetMotion(P,I(1),blend,loop));break;}
    case 0x12:{s32 blend;u8 loop;loop=(bool)I(3);blend=I(2);peopleSetMotionForce(P,I(1),blend,loop);break;}
    case 0x13:peopleStopMotion(P);break;
    case 0x14:peopleWaitSyncMotion(P,(bool)I(1));break;
    case 0x15:peopleSpeakStart(P);peopleTalkMsg(P,I(1));if(I(2)!=0)peopleTalkMsgEnd(P);break;
    case 0x16:peopleTalkMsgEnd(P);peopleSpeakStop(P);break;
    case 0x17:R(floorReadCharacter(P,I(1)));break;
    case 0x18:peopleClose(P,1);break;
    case 0x19:{f32 d=F(4),c=F(3),b=F(2);R(peopleRectCheck(P,F(1),b,c,d));break;}
    case 0x1A:{GSvec *a=V(1),*b=V(2);R(peopleRectCheck(P,a->param1,a->param3,b->param1,b->param3));break;}
    case 0x1B:{u8 mode=(bool)I(6);f32 e=F(5),d=F(4),c=F(3),b=F(2);R(peopleLineCheck(P,mode,F(1),b,c,d,e));break;}
    case 0x1C:{GSvec *a=V(1),*b=V(2);R(peopleLineCheck(P,(bool)I(3),a->param1,a->param3,b->param1,b->param3,0.0f));break;}
    case 0x1D:{f32 z=F(3),y=F(2);peopleSetPosXYZ(P,F(1),y,z);break;}
    case 0x1E:{GSvec *v=V(1);peopleSetPosXYZ(P,v->param1,v->param2,v->param3);break;}
    case 0x1F:{f32 z=F(3),y=F(2);peopleSetRotXYZ(P,F(1),y,z);break;}
    case 0x20:peopleSetRot(P,V(1));break;
    case 0x21:Vector.param1=F(1);Vector.param2=F(2);Vector.param3=F(3);peopleGetPos(P,(GSvec *)&Vector);break;
    case 0x22:peopleGetPos(P,V(1));break;
    case 0x24:{f32 z=F(4),y=F(3),x=F(2);peopleWalkToXYZ(P,(bool)I(1),x,y,z);break;}
    case 0x25:{GSvec *v=V(2);peopleWalkToXYZ(P,(bool)I(1),v->param1,v->param2,v->param3);break;}
    case 0x26:{GSresID *p=H(1);u8 mode=(bool)I(3);peopleWalkToTarget(P,p->group,p->id,mode,F(2));break;}
    case 0x27:R(peopleMoveCheck(P,(bool)I(1)));break;
    case 0x28:peopleSetFlagOn(P,I(1));break;
    case 0x29:peopleSetFlagOff(P,I(1));break;
    case 0x2A:peopleSetNeckTargetHero(P);break;
    case 0x2B:{GSresID *p=H(1);peopleSetNeckTarget(P,p->group,p->id);break;}
    case 0x2C:{s32 z=I(3),y=I(2);peopleSetNeckTargetXYZ(P,I(1),y,z);break;}
    case 0x43:{GSvec *v=V(1);peopleSetNeckTargetXYZ(P,v->param1,v->param2,v->param3);break;}
    case 0x2D:peopleRemoveNeckTarget(P,F(1));break;
    case 0x2E:R(peopleCheckNeckRotate(P,(bool)I(1)));break;
    case 0x50:{f32 c=F(3),b=F(2);peopleMoveNeckAngle(P,F(1),b,c);break;}
    case 0x53:{f32 c=F(3),b=F(2);peopleMoveNeckAngleWorld(P,F(1),b,c);break;}
    case 0x2F:peopleRotateTo(P,F(1));break;
    case 0x30:{f32 d=F(4),c=F(3),b=F(2);peopleRotateToXYZ(P,F(1),b,c,d);break;}
    case 0x44:{GSvec *v=V(1);peopleRotateToXYZ(P,v->param1,v->param2,v->param3,F(2));break;}
    case 0x31:{GSresID *p=H(1);peopleRotateToTarget(P,p->group,p->id,F(2));break;}
    case 0x4F:{f32 time=F(2);peopleRotateToAngle(P,0.017453292f*F(1),time);break;}
    case 0x32:peopleSetSpeedRate(P,F(1));break;
    case 0x33:{GSresID *p=H(1);peopleAttach(P,p->group,p->id,I(2));break;}
    case 0x34:peopleDetach(P,(bool)I(1));break;
    case 0x35:peopleTaskSwich(P);break;
    case 0x36:R(peopleInitWalkList(P,I(1)));break;
    case 0x37:{f32 z=F(3),y=F(2);R(peopleAddWalkList(P,F(1),y,z));break;}
    case 0x45:{GSvec *v=V(1);R(peopleAddWalkList(P,v->param1,v->param2,v->param3));break;}
    case 0x38:R(peopleStartWalkList(P,(bool)I(1)));break;
    case 0x39:R(peopleFreeWalkList(P));break;
    case 0x3A:peopleInitEvent(P);break;
    case 0x3B:peopleTermEvent(P);break;
    case 0x3C:peopleFallAppear(P,F(1));break;
    case 0x3D:peopleDispMark(P,I(1));break;
    case 0x3E:peopleSetCollision(P,(bool)I(1));break;
    case 0x3F:R(peopleGazeHeroCheck(P));break;
    case 0x40:{s32 c=I(3),b=I(2);R(peopleSetAnimBlend(P,I(1),b,c));break;}
    case 0x41:R(peopleWaitSyncMotionBlend(P,(bool)I(1)));break;
    case 0x42:R(peopleWalkPause(P,(bool)I(1)));break;
    case 0x65:
        for(u16 i=0;i<6;++i)parts[i]=getInteger__Q28GSscript11tigaVariantFv(A(2)->get(i));
        for(u16 i=0;i<7;++i)motions[i]=getInteger__Q28GSscript11tigaVariantFv(A(3)->get(i));
        recoveryEventPC(P,I(1),parts,motions);break;
    case 0x46:if(peopleGetHumanID(P)==0)floorReadCharacter(P,I(1));else peopleReadObject(P,I(1));break;
    case 0x47:R(peopleRunOrNot(P));break;
    case 0x48:appScriptSetFloat(result,peopleGetSpeed(P));break;
    case 0x49:{
        s32 temp_r27_14,temp_r27_15,temp_r27_16,temp_r27_17,temp_r27_18;
        s8 temp_r27_13;
        GSresID *temp_r3_25;
        s32 temp_r3_24;                                  /* switch 1 */
            temp_r3_24 = I(1);
            switch (temp_r3_24) {                   /* switch 2 */
            case 1:                                 /* switch 2 */
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                break;
            case 2:                                 /* switch 2 */
                peopleSetMotion(P, 0xB, 0, 0U);
                peopleWaitSyncMotion(P, 1U);
                peopleSetMotion(P, 0xC, 0, 1U);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                peopleSetMotion(P, 0xD, 0, 0U);
                peopleWaitSyncMotion(P, 1U);
                peopleSetMotion(P, 3, 0, 1U);
                break;
            case 3:                                 /* switch 2 */
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                if (I(3) == 1) {
                    peopleTalkMsgEnd(P);
                    peopleSpeakStop(P);
                }
                break;
            case 6:                                 /* switch 2 */
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                scriptEncount(I(3), 1, 0);
                break;
            case 7:                                 /* switch 2 */
                peopleSetMotion(P, I(2), 0, 0U);
                peopleWaitSyncMotion(P, 1U);
                peopleSetMotion(P, I(3), 0, 0U);
                peopleWaitSyncMotion(P, 1U);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(4));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                break;
            case 8:                                 /* switch 2 */
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMessageBgmStart();
                temp_r27_13 = menuSubOpenYesNoField();
                winMsgCloseField(1);
                peopleTalkMessageBgmStop();
                peopleSpeakStop(P);
                if (temp_r27_13 == 0) {
                    result->type = 1;
                    result->value.integer = 0;
                } else {
                    result->type = 1;
                    result->value.integer = 1;
                }
                break;
            case 9:                                 /* switch 2 */
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                fightEncount(I(3));
                break;
            case 10:                                /* switch 2 */
                peopleSetMotion(P, I(2), 0, 0U);
                peopleWaitSyncMotion(P, 1U);
                peopleSetMotion(P, I(3), 0, 1U);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(4));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                peopleSetMotion(P, I(5), 0, 0U);
                peopleWaitSyncMotion(P, 1U);
                peopleSetMotion(P, 3, 0, 1U);
                break;
            case 11:                                /* switch 2 */
                peopleDispMark(P, 1);
                scriptWaitTime(1.0f);
                peopleRotateToTarget(P, 0, 0x64, 1.0f);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                break;
            case 12:                                /* switch 2 */
                peopleRotateToTarget(P, 0, 0x64, 1.0f);
                peopleDispMark(P, 1);
                scriptWaitTime(1.0f);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                break;
            case 13:                                /* switch 2 */
                temp_r27_14 = peopleGetFlags(P);
                peopleSetFlagOff(P, 0x20);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                peopleSetFlagOn(P, 0x20);
                peopleRotateToTarget(P, 0, 0x64, 1.0f);
                peopleSetFlags(P, temp_r27_14);
                break;
            case 14:                                /* switch 2 */
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                temp_r27_15 = I(4);
                scriptGetItem(I(3),temp_r27_15);
                break;
            case 15:                                /* switch 2 */
                scriptPlayPokemonNakigoe(I(2));
                peopleTalkMsg(P, I(3));
                peopleTalkMsgEnd(P);
                break;
            case 16:                                /* switch 2 */
                winMsgOpenField(I(2),1,0);
                winMsgCloseField(1);
                break;
            case 17:                                /* switch 2 */
                peopleSetFlagOff(P, 0x20);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                peopleSetFlagOn(P, 0x20);
                break;
            case 18:                                /* switch 2 */
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                peopleManualAnimation(P);
                scriptSetEndedMotion(P, I(3), 0U);
                peopleWaitSyncMotion(P, 1U);
                peopleReadObject(P, I(4));
                peopleManualAnimation(P);
                peopleSetMotionForce(P, I(5), 0, 0U);
                peopleWaitSyncMotion(P, 1U);
                peopleAutoAnimation(P);
                break;
            case 19:                                /* switch 2 */
                temp_r27_16 = peopleGetFlags(P);
                peopleSetFlagOff(P, 0x10);
                peopleSetFlagOff(P, 0x20);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                peopleSetFlags(P, temp_r27_16);
                break;
            case 20:                                /* switch 2 */
                temp_r27_17 = peopleGetFlags(P);
                peopleSetFlagOff(P, 0x10);
                peopleSetFlagOff(P, 0x20);
                temp_r3_25 = H(3);
                peopleSetNeckTarget(P, temp_r3_25->group, temp_r3_25->id);
                peopleCheckNeckRotate(P, 1U);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                if (I(4) == 1) {
                    peopleRemoveNeckTarget(P,F(5));
                    peopleCheckNeckRotate(P, 1U);
                }
                peopleSetFlags(P, temp_r27_17);
                break;
            case 21:                                /* switch 2 */
                temp_r27_18 = peopleGetFlags(P);
                peopleSetFlagOff(P, 0x20);
                peopleSpeakStart(P);
                peopleTalkMsg(P, I(2));
                peopleTalkMsgEnd(P);
                peopleSpeakStop(P);
                peopleSetFlags(P, temp_r27_18);
                break;
            }
            break;
        }
    case 0x4A:{u8 mode=I(3);s32 b=I(2),a=I(1);peopleAttachWithMode(P,floorGetCurrentGroupID(),a,b,mode);break;}
    case 0x4B:{void *model=GSresGetResource(P);if(model)GSmodelGetPosition(model,(GSvec *)&Vector);setRpVec__Q28GSscript4TigaFPC5GSvec(this,(GSvec *)&Vector);break;}
    case 0x4C:{void *model=GSresGetResource(P);if(model)GSmodelGetRotation(model,(GSvec *)&Vector);Vector.param2=57.29578f*Vector.param2;appScriptSetFloat(result,Vector.param2);break;}
    case 0x4D:peopleSetWaitAnimation(P);break;
    case 0x4E:peopleUnsetWaitAnimation(P);break;
    case 0x51:{GSresID *p=H(1);peopleMoveNeckTarget(P,p->group,p->id,F(2));break;}
    case 0x52:peopleMoveNeckTargetHero(P,F(1));break;
    case 0x54:{f32 time=F(4);s32 z=I(3),y=I(2);peopleMoveNeckTargetXYZ(P,I(1),y,z,time);break;}
    case 0x55:peopleGetYDegreeRotation(P);break;
    case 0x57:peopleAutoAnimation(P);break;
    case 0x58:peopleManualAnimation(P);break;
    case 0x59:{s32 source[5],table[5];source[0]=getInteger__Q28GSscript11tigaVariantFv(A(1)->get(0));source[1]=getInteger__Q28GSscript11tigaVariantFv(A(1)->get(1));source[2]=getInteger__Q28GSscript11tigaVariantFv(A(1)->get(2));source[3]=getInteger__Q28GSscript11tigaVariantFv(A(1)->get(3));source[4]=getInteger__Q28GSscript11tigaVariantFv(A(1)->get(4));memcpy(table,source,sizeof(table));peopleSetMotionTable(P,table);break;}
    case 0x5A:peopleSetDefaultMotionTable(P);break;
    case 0x5B:peopleSpeedSlowDownOn(P);break;
    case 0x5C:peopleSpeedSlowDownOff(P);break;
    case 0x5D:peopleBlinkOnce(P);break;
    case 0x5E:peopleBlinkStart(P);break;
    case 0x5F:peopleBlinkStop(P);break;
    case 0x60:peopleSpeakStart(P);break;
    case 0x61:peopleSpeakStop(P);break;
    case 0x62:peopleSetTalkDistance(P,F(1));break;
    case 0x63:peopleGetTalkDistance(P);break;
    case 0x64:R(peopleStartWalkListStrict(P,I(1)));break;
    case 0x66:peopleWalkPauseTalkMode(P,(bool)I(1));break;
    case 0x67:{void *model=GSresGetResource(P);GSmodelSetAnimRate(model,F(1));break;}
    case 0x68:{s32 mode=I(2);peopleSetWalkSpeed(P,mode,F(1));break;}
    case 0x69:{void *model=GSresGetResource(P);GSmodelSetBoundCheck(model,I(1)==0);break;}
    case 0x6A:{u8 flag=(bool)I(2);scriptSetEndedMotion(P,I(1),flag);break;}
    case 0x6B:{s32 type=I(2);scriptModelPartPaticle(person->id,I(1),type);break;}
    case 0x6C:{void *model=GSresGetResource(P);GSmodelSetScale(model,V(1));break;}
    case 0x6D:GSmodelRecalculateBound(GSresGetResource(P));break;
    case 0x6E:peopleGetPos(P,(GSvec *)&Vector);{GSvec *point=V(3);f32 radius=F(2);R(scriptPeopleInsideCheck((GSvec *)&Vector,V(1),point,radius));}break;
    case 0x6F:{s32 index=I(1);void *model=GSresGetResource(floorGetCurrentGroupID(),person->id);void *part=GSmodelGetPart(model,index);GSpartGetTransform(part,&Vector.param1,0,0);GSpartFree(part);setRpVec__Q28GSscript4TigaFPC5GSvec(this,(GSvec *)&Vector);break;}
    case 0x70:{void *model=GSresGetResource(P);if(model){s32 index=I(1);GSmodelEnableColorSwap(model,_pokeRareCol[index]);GSmodelEnableModulation(model,&_pokeRareCol[index][4]);}break;}
    case 0x71:peopleGet(P)->field54=0;break;
    case 0x72:{PersonScriptWork *p=peopleGet(P);peopleRotateStop(P);p->field54=0;break;}
    }
    return 0;
}
#undef I
#undef F
#undef V
#undef H
#undef A
#undef P
#undef R
