#include <game/pxdvs/GSAPI/GScolsys/GScolsys2HumanPrivate.hpp>
static inline s32 getHuman(int index,GSCOLSYS2_HUMAN **out) {
    if(index<0 || index>=48) return 4;
    HumanFloor *floor=GScolsys2GetCurFloor();
    if(!floor) return 1;
    GSCOLSYS2_HUMAN *human=(GSCOLSYS2_HUMAN *)((u8 *)floor+(index*20+0xa00));
    if(!(human->flags&1)) return 4;
    *out=human;
    return 0;
}
extern "C" f32 GScolsys2HumanGetHumanRadius(int index) {
    GSCOLSYS2_HUMAN *human;
    if(getHuman(index,&human)) return 0.0f;
    return human->radius;
}
extern "C" void GScolsys2HumanDispColision() {
    GSvec position;
    HumanFloor *floor=GScolsys2GetCurFloor();
    if(floor) {
        GSgfxLayerSetActive(2);
        GScameraLoadActiveCameraMatrix(2);
        GSgfxCullMode(0);
        GSgfxVFBuildTemp(1,4,0,0,1,5,0,0,0);
        GSgfxSetupRenderAndSelect();
        GSgfxBlendMode(1,4,5);
        GSgfxPixelMode(1,1,1);
        GSgfxSetLineWidth(2.0f);
        s32 i;
        GSCOLSYS2_HUMAN *human=floor->humans;
        for(;human!=floor->humans+48;human++) {
            u16 flags=human->flags;
            if((flags&1) && !(flags&2)) {
                position.z=0.0f;position.y=0.0f;position.x=0.0f;
                peopleGetPos(human->group,human->resource,&position);
                GSgfxSetPrimitiveType(0xa0);
                GSgfxBeginSurface(18);
                GSgfxVertex3f(position.x,0.1f+position.y,position.z);
                GSgfxColor4u8(0,127,127,192);
                f32 angle;
                f32 trig[2];
                for(i=0;i<17;i++) {
                    angle=0.3926991f*(f32)i;
                    trig[0]=(f32)sin(angle);
                    trig[1]=(f32)cos(angle);
                    GSgfxVertex3f(human->radius*trig[1]+position.x,0.1f+position.y,human->radius*trig[0]+position.z);
                    GSgfxColor4u8(0,127,127,192);
                }
                GSgfxEndSurface();
                GSgfxSetPrimitiveType(0xb0);
                GSgfxBeginSurface(17);
                f32 ringAngle;
                f32 radius=human->radius+peopleGetTalkDistance(human->group,human->resource);
                f32 ringTrig[2];
                for(i=0;i<17;i++) {
                    ringAngle=0.3926991f*(f32)i;
                    ringTrig[0]=(f32)sin(ringAngle);
                    ringTrig[1]=(f32)cos(ringAngle);
                    GSgfxVertex3f(radius*ringTrig[1]+position.x,0.15f+position.y,radius*ringTrig[0]+position.z);
                    GSgfxColor4u8(127,127,255,192);
                }
                GSgfxEndSurface();
            }
        }
    }
}
static inline f32 followerCollisionFix() { return 0.99f; }
static u8 checkCollisionHeadToHead(GSCOLSYS2_HUMAN *other,GSCOLSYS2_HUMAN *self,GSvec *point,GSvec *out) {
    GSvec hero;
    f32 radius;
    union {f32 value;s32 bits;} classification;
    GSvec *position;
    bool unadjusted;
    tagPeopleWork *work=peopleSearchID(peopleGetHumanID(other->group,other->resource));
    if(!work) return 0;
    position=peopleBiosGetPosPtr(work);
    if(!position) return 0;
    f32 distance,dx,dz;
    dz=point->z-position->z;
    dx=point->x-position->x;
    distance=dx*dx+dz*dz;
    if(distance>0.0f) {
        f64 guess=__frsqrte(distance);
        guess=0.5*guess*(3.0-(f64)distance*(guess*guess));
        guess=0.5*guess*(3.0-(f64)distance*(guess*guess));
        guess=0.5*guess*(3.0-(f64)distance*(guess*guess));
        distance=(f32)((f64)distance*guess);
    } else if(distance<0.0) distance=__float_nan[0];
    else {
        classification.value=distance;
        s32 exponent=classification.bits&0x7f800000;
        s32 type;
        switch(exponent) {
        case 0x7f800000:if(classification.bits&0x7fffff) type=1;else type=2;break;
        case 0:if(classification.bits&0x7fffff) type=5;else type=3;break;
        default:type=4;break;
        }
        if(type==1) distance=__float_nan[0];
    }
    radius=other->radius+self->radius;
    unadjusted=gimmickBoxFixDistanceForPushBox(&radius,work,dx,dz)==0;
    if(gimmickBoxIsBox(work)) {
        heroMoveGetHeroPos(&hero);
        f32 height=position->y+other->height-hero.y;
        if(height<0.00001f && height>-0.00001f && !unadjusted) return 0;
    } else {
        if(position->y>=point->y+self->height || position->y+other->height<=point->y) return 0;
    }
    if(distance>=radius) return 0;
    if(distance<=0.0f) {dx=1.0f;distance=1.0f;}
    tagPeopleWork *selfWork=peopleSearchID(peopleGetHumanID(self->group,self->resource));
    if(!selfWork) return 0;
    if(gimmickBoxIsBox(work) || gimmickBoxIsBox(work)) {
        f32 selfHeight=peopleBiosGetPosPtr(selfWork)->y;
        if((f32)__fabs(peopleBiosGetPosPtr(work)->y-selfHeight)>2.0f) return 0;
    }
    static f32 fix=followerCollisionFix();
    if(heroGetFollower()) {
        if(selfWork->isHero() && work->isFollower()) radius*=fix;
        else if(work->isHero() && selfWork->isFollower()) radius*=fix;
    }
    if(distance>=radius) return 0;
    f32 scale=(0.0001f+radius)/distance;
    if(gimmickBoxIsBox(work) && unadjusted) {
        f32 absz=(f32)__fabs(dz);
        f32 absx=(f32)__fabs(dx);
        if(absx>absz) dx*=scale;
        else dz*=scale;
    } else {dx*=scale;dz*=scale;}
    GSvec corrected;
    corrected.x=position->x+dx;corrected.y=point->y;corrected.z=position->z+dz;
    if(out) {out->x=corrected.x;out->y=corrected.y;out->z=corrected.z;}
    return 1;
}
static u8 checkCollision(GSCOLSYS2_HUMAN *self,int index,GSvec *start,GSvec *end,GSvec *out) {
    HumanFloor *floor;
    s32 i;
    s32 passes;
    GSCOLSYS2_HUMAN *other;
    GSvec corrected,point;
    GSvec *correction=&corrected;
    point.x=end->x;point.y=end->y;point.z=end->z;
    floor=GScolsys2GetCurFloor();
    passes=0;
    for(;;) {
        other=floor->humans;
        i=0;
        for(;i<48;i++,other++) {
            if(i==index || !(other->flags&1) || (other->flags&2)) continue;
            if(checkCollisionHeadToHead(other,self,&point,correction)) break;
        }
        if(i<48) {
            passes++;
            point.x=correction->x;point.y=correction->y;point.z=correction->z;
            if(passes<10) continue;
        }
        break;
    }
    if(passes<=0) return 0;
    f32 x=point.x,y=point.y,z=point.z;
    if(out) {out->x=x;out->y=y;out->z=z;}
    return 1;
}
extern "C" s32 GScolsys2HumanCollision(int index,GSvec *start,GSvec *end,GSvec *out) {
    GSvec direction,first,last;
    GSCOLSYS2_HUMAN *human;
    s32 result=getHuman(index,&human);
    if(result) return result;
    f32 distance=PSVECDistance((Vec *)start,(Vec *)end);
    f32 step;
    if(distance>0.0f) {step=human->radius/distance;if(step>1.0f) step=1.0f;}
    else step=0.0f;
    PSVECSubtract((Vec *)end,(Vec *)start,(Vec *)&direction);
    f32 progress=0.0f;
    for(;progress<1.0f;) {
        f32 next=progress+step;
        if(next>1.0f) next=1.0f;
        PSVECScale((Vec *)&direction,(Vec *)&first,progress);
        PSVECAdd((Vec *)&first,(Vec *)start,(Vec *)&first);
        PSVECScale((Vec *)&direction,(Vec *)&last,next);
        PSVECAdd((Vec *)&last,(Vec *)start,(Vec *)&last);
        if(checkCollision(human,index,&first,&last,out)) return 6;
        if(step<=0.0f) break;
        progress+=step;
    }
    return 7;
}
extern "C" s32 GScolsys2HumanEnable(int index,u8 enabled) {
    GSCOLSYS2_HUMAN *human;
    s32 result=getHuman(index,&human);
    if(result) return result;
    if(enabled) human->flags&=~2;
    else human->flags|=2;
    return 0;
}
extern "C" s32 GScolsys2HumanAddCurrentFloor(int *index,GSCOLSYS2_HUMAN *input) {
    HumanFloor *floor=GScolsys2GetCurFloor();
    if(!floor) return 1;
    s32 i=0;
    for(;i<48;i++) if(!(floor->humans[i].flags&1)) break;
    if(i>=48) return 5;
    HumanFloor *selected=(HumanFloor *)((u8 *)floor+i*20);
    selected->humans[0].group=input->group;
    selected->humans[0].resource=input->resource;
    u32 resource=input->resource;
    if(resource==101 || resource==104 || resource==105) selected->humans[0].radius=3.0f;
    else selected->humans[0].radius=input->radius;
    selected->humans[0].height=input->height;
    selected->humans[0].flags=0;
    selected->humans[0].flags|=1;
    *index=i;
    return 0;
}
extern "C" f32 GScolsys2HumanGetWalkHeight(GSvec *input) {
    HumanHeight heights[8];
    GSvec point;
    point.x=input->x;point.y=input->y;point.z=input->z;
    s32 count=GScolsys2WalkGetHeight(&point,heights);
    if(count>=2) {
        f32 height,highest,preferred;
        preferred=-1000000.0f;
        u8 found=0;
        highest=-1000000.0f;
        HumanHeight *entry=heights;
        for(s32 i=0;i<count;i++,entry++) {
            height=entry->height;
            if(highest<height) highest=height;
            if(!(height-point.y>=10.0f) && preferred<height) {preferred=height;found=1;}
        }
        if(found) point.y=preferred;else point.y=highest;
        f32 selectedHeight=point.y;
        f32 original=input->y;
        f32 difference=selectedHeight-original;
        if((f32)__fabs(difference)>=10.0f) {
            entry=&heights[1];
            f32 candidate;
            f32 chosen=heights[0].height;
            f64 absolute=__fabs(original-heights[0].height);
            f32 nearest=(f32)absolute;
            for(s32 i=1;i<count;i++,entry++) {
                f32 delta=(f32)__fabs(input->y-entry->height);
                candidate=entry->height;
                if(nearest>=delta) {
                    if(nearest>delta) {nearest=delta;chosen=candidate;}
                    else if(chosen<candidate) chosen=candidate;
                }
            }
            point.y=chosen;
        }
    } else if(count>0) point.y=heights[0].height;
    else point.y=0.0f;
    return point.y;
}
extern "C" f32 GScolsys2HumanGetWalkHighest(GSvec *input) {
    HumanHeight heights[8];
    GSvec point;
    point.x=input->x;point.y=input->y;point.z=input->z;
    s32 count=GScolsys2WalkGetHeight(&point,heights);
    if(count>=2) {
        HumanHeight *entry=heights;
        f32 highest=-1000000.0f;
        for(s32 i=0;i<count;i++,entry++) if(highest<entry->height) highest=entry->height;
        return highest;
    }
    if(count>0) return heights[0].height;
    return 0.0f;
}
