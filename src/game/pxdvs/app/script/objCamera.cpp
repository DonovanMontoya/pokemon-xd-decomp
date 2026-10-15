#include <game/pxdvs/app/script/objCameraPrivate.hpp>
#define I(N) appScriptGetInt(&args[N])
#define F(N) appScriptGetFloat(&args[N])
#define V(N) appScriptGetVec(&args[N])
#define R(E) appScriptSetInt(result,(E))
int AppScript::cmpCamera(int method,GSscript::tigaVariant *args,GSscript::tigaVariant *result) {
    GSvec position;f32 fov,aspect,nearPlane,farPlane;
    switch(method) {
    case 0x10:{f32 a=F(1),b=F(2);cameraSetFloorDefault(a,b,F(3));break;}
    case 0x11:if(I(1)==3)floorFieldCameraDisable();cameraSetType(I(1));break;
    case 0x12:{GSresID *p=cameraScriptPeople(&args[1]);cameraSetTarget(p->group,p->id);break;}
    case 0x3D:{s32 id=I(1);cameraSetTarget(floorGetCurrentGroupID(),id);break;}
    case 0x13:{f32 a=F(1),b=F(2);cameraSetTargetPosXYZ(a,b,F(3));break;}
    case 0x14:{GSvec *v=V(1);cameraSetTargetPosXYZ(v->param1,v->param2,v->param3);break;}
    case 0x15:{f32 a=F(1),b=F(2);cameraSetTargetOfsXYZ(a,b,F(3));break;}
    case 0x16:{GSvec *v=V(1);cameraSetTargetOfsXYZ(v->param1,v->param2,v->param3);break;}
    case 0x17:{void *camera=GSresGetResource(0,0);f32 z=F(3),y=F(2);position.param1=F(1);position.param2=y;position.param3=z;cameraSetPosition(&position);GScameraSetPosition(camera,&position);break;}
    case 0x18:{void *camera=GSresGetResource(0,0);cameraSetPosition(V(1));GScameraSetPosition(camera,V(1));break;}
    case 0x19:{f32 a=F(1),b=F(2);cameraSetRotationXYZ(a,b,F(3));break;}
    case 0x1A:{GSvec *v=V(1);cameraSetRotationXYZ(v->param1,v->param2,v->param3);break;}
    case 0x1B:{s32 group=I(1),id=I(2);f32 frame=F(3);cameraPlayAnime(group,id,(bool)I(4),frame);break;}
    case 0x1C:cameraStopAnime();break;
    case 0x1D:cameraPauseAnime();break;
    case 0x1E:cameraResumeAnime();break;
    case 0x1F:R(cameraWaitSyncAnime((bool)I(1)));break;
    case 0x20:cameraSetAnimeRate(F(1));break;
    case 0x21:{GSresID *p=cameraScriptPeople(&args[2]);cameraSetType(I(1));s32 mode=I(1);cameraMoveTarget(mode,p->group,p->id,F(3));break;}
    case 0x22:cameraSetType(I(1));{s32 mode=I(1),x=I(2),y=I(3),z=I(4),time=I(5);cameraMoveTargetXYZ(mode,(f32)x,(f32)y,(f32)z,(f32)time);break;}
    case 0x23:{GSvec *v=V(2);cameraSetType(I(1));s32 mode=I(1);cameraMoveTargetXYZ(mode,v->param1,v->param2,v->param3,F(3));break;}
    case 0x24:cameraSetType(I(1));{s32 mode=I(1);f32 x=F(2),y=F(3),z=F(4);cameraMovePositionXYZ(mode,x,y,z,F(5));break;}
    case 0x25:{GSvec *v=V(2);cameraSetType(I(1));s32 mode=I(1);cameraMovePositionXYZ(mode,v->param1,v->param2,v->param3,F(3));break;}
    case 0x26:cameraSetType(I(1));{f32 mode=F(1),x=F(2),y=F(3),z=F(4);cameraMoveRotationXYZ((s32)mode,x,y,z,F(5));break;}
    case 0x27:{GSvec *v=V(2);cameraSetType(I(1));s32 mode=I(1);cameraMoveRotationXYZ((u8)mode,v->param1,v->param2,v->param3,F(3));break;}
    case 0x28:R(cameraMoveEndCheck((bool)I(1)));break;
    case 0x29:cameraSetHeight(F(1));break;
    case 0x2A:cameraSetDistance(F(1));break;
    case 0x2B:cameraSetRotY(F(1));break;
    case 0x2C:{void *camera=GSresGetResource(0,0);GScameraGetPerspective(camera,&fov,&aspect,&nearPlane,&farPlane);fov=F(1);cameraSetFov(fov);GScameraSetPerspective(camera,fov,aspect,nearPlane,farPlane);break;}
    case 0x2D:cameraUpdate();break;
    case 0x2E:{f32 time=F(1);cameraReturn((bool)I(2),time);break;}
    case 0x2F:cameraSetType(0);floorFieldCameraEnable();break;
    case 0x30:floorFieldCameraDisable();cameraSetType(3);break;
    case 0x31:floorFieldCameraBlend(F(1));break;
    case 0x32:appScriptSetFloat(result,cameraGetFov());break;
    case 0x33:cameraGetPosition(&position);appScriptCopyVec(&work()->vec,&position.param1);work()->ret.value.vector=&work()->vec;work()->ret.type=4;break;
    case 0x34:cameraGetRotation(&position);appScriptCopyVec(&work()->vec,&position.param1);work()->ret.value.vector=&work()->vec;work()->ret.type=4;break;
    case 0x3A:{s32 mode=I(1),x=I(2),y=I(3),z=I(4),time=I(5);cameraMoveTargetXYZ(mode,(f32)x,(f32)y,(f32)z,(f32)time);cameraMoveTargetPosAcc(F(6));break;}
    case 0x39:{GSvec *v=V(2);s32 mode=I(1);cameraMoveTargetXYZ(mode,v->param1,v->param2,v->param3,F(3));cameraMoveTargetPosAcc(F(4));break;}
    case 0x36:{s32 mode=I(1);f32 x=F(2),y=F(3),z=F(4);cameraMovePositionXYZ(mode,x,y,z,F(5));cameraMovePositionAcc(F(6));break;}
    case 0x35:{GSvec *v=V(2);s32 mode=I(1);cameraMovePositionXYZ(mode,v->param1,v->param2,v->param3,F(3));cameraMovePositionAcc(F(4));break;}
    case 0x38:{f32 mode=F(1),x=F(2),y=F(3),z=F(4);cameraMoveRotationXYZ((s32)mode,x,y,z,F(5));cameraMoveRotationAcc(F(6));break;}
    case 0x37:{GSvec *v=V(2);s32 mode=I(1);cameraMoveRotationXYZ((u8)mode,v->param1,v->param2,v->param3,F(3));cameraMoveRotationAcc(F(4));break;}
    case 0x3B:{s32 mode=I(1);f32 fov=F(2);cameraMoveFov(mode,fov,F(3));break;}
    case 0x3C:{s32 mode=I(1);f32 fov=F(2);cameraMoveFov(mode,fov,F(3));cameraMoveFovAcc(F(4));break;}
    case 0x3E:{s32 id=I(1),part=I(2);cameraSetTargetExt(floorGetCurrentGroupID(),id,part);break;}
    case 0x3F:cameraSetPartTargetOffset(V(1));break;
    }
    return 0;
}
#undef I
#undef F
#undef V
#undef R
