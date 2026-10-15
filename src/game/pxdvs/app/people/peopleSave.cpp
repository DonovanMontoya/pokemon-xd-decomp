#include <game/pxdvs/app/people/peopleSavePrivate.hpp>

static void _makeAnywaySaveData(GSBinWriteStream*);
static void _peopleRestoreAnywaySaveData(GSBinReadStream*);

extern "C" u32 peopleGetAnywaySaveSize() {
    GSBinWriteSizeStream stream;
    _makeAnywaySaveData(&stream);
    return stream.getWriteSize();
}

static void _peopleRestoreAnywaySaveData(GSBinReadStream* stream) {
    PeopleSaveFlags flags;
    tagPeopleWork* work;
    PeopleSavedState* saved;
    u8 count=stream->readU8();
    u32 records=stream->cur-stream->start;
    for(s32 i=0;i<peopleBiosGetMaxNum();++i) {
        work=peopleBiosGetWorkPtr(i);
        if(work)work->unknown01[0]=0;
    }
    for(s32 i=0;i<count;++i) {
        if(stream->readU8()) {
            u32 start=stream->cur-stream->start;
            u16 size=stream->readU16();
            memcpy(&flags,stream->cur,5);stream->cur+=5;
            stream->cur+=4;
            u32 group=stream->readU32();
            u32 resource=stream->readU32();
            stream->cur+=4;
            for(s32 j=0;j<peopleBiosGetMaxNum();++j) {
                work=peopleBiosGetWorkPtr(j);
                saved=(PeopleSavedState*)&work->state;
                if(work->used && group==saved->group && resource==saved->resource) {
                    work->unknown01[0]|=1;
                    break;
                }
            }
            stream->cur=stream->start+start+size;
        }
    }
    for(s32 i=0;i<peopleBiosGetMaxNum();++i) {
        work=peopleBiosGetWorkPtr(i);
        saved=(PeopleSavedState*)&work->state;
        if(!(work->unknown01[0]&1))peopleClose(saved->group,saved->resource,1);
    }
    stream->cur=stream->start+records;
    for(s32 i=0;i<count;++i) {
        if(stream->readU8()) {
            stream->cur+=2;
            memcpy(&flags,stream->cur,5);stream->cur+=5;
            u32 state=stream->readU32();
            u32 group=stream->readU32();
            u32 resource=stream->readU32();
            u32 object=stream->readU32();
            bool found=false;
            for(s32 j=0;j<peopleBiosGetMaxNum();++j) {
                work=peopleBiosGetWorkPtr(j);
                saved=(PeopleSavedState*)&work->state;
                if(work->used && group==saved->group && resource==saved->resource) {found=true;break;}
            }
            if(!found) {
                peopleOpen(group,resource,object);
                peopleAddCollision(group,resource);
                work=peopleGet(group,resource);
            }
            saved=(PeopleSavedState*)&work->state;
            u32 oldObject=saved->object;
            GSmodel* model=work->model;
            saved->state=flags.state;
            saved->visible=flags.visible;
            saved->unknown0E=flags.unknown0E;
            saved->running=flags.running;
            saved->collisionEnabled=flags.collision;
            saved->walkPaused=flags.paused;
            saved->walkActive=flags.active;
            saved->savedWalkMode=flags.mode;
            saved->walkPhase=flags.phase;
            saved->neckEnabled=flags.neck;
            saved->flags=state;saved->group=group;saved->resource=resource;saved->object=object;
            if(oldObject!=saved->object) {
                GSlogWrite("people %d (%08x) : objID error (%08x, %08x)\n",i,saved->resource,oldObject,saved->object);
                saved->object=oldObject;
            }
            // Both copies of speed are present in the original format.
            saved->moveSpeed=stream->readFloat();
            saved->savedWalkMode=stream->readU8();
            saved->moveSpeed=stream->readFloat();
            memcpy(&saved->walkStartPosition,stream->cur,12);stream->cur+=12;
            memcpy(&saved->walkTarget,stream->cur,12);stream->cur+=12;
            saved->walkPointCount=stream->readU8();
            if(saved->walkPointCount) {
                saved->walkPointIndex=stream->readU8();
                saved->walkPoints=(GSvec*)GSmemAllocClr(saved->walkPointCount*12);
                for(s32 j=0;j<saved->walkPointCount;++j) {
                    memcpy(&saved->walkPoints[j],stream->cur,12);stream->cur+=12;
                }
            }
            switch(saved->neckEnabled) {
            case 1: saved->neckTargetGroup=stream->readU32();saved->neckTargetResource=stream->readU32();break;
            case 2: memcpy(&saved->neckTargetPosition,stream->cur,12);stream->cur+=12;break;
            }
            if(model) {
                memcpy(GSmodelGetPositionPtr(model),stream->cur,12);stream->cur+=12;
                memcpy(&saved->previousPosition,stream->cur,12);stream->cur+=12;
                saved->targetRotation=stream->readFloat();
                saved->rotationProgress=stream->readFloat();
                GSmodelGetRotationPtr(model)->param2=saved->targetRotation;
                GSmodelGetPositionPtr(model);
                GSmodelSetPosition(model,GSmodelGetPositionPtr(model));
                GSmodelSetRotation(model,GSmodelGetRotationPtr(model));
                peopleSetDisp(saved->group,saved->resource,saved->visible);
            } else {
                // Retail consumes four floats here, assigning the same field.
                saved->targetRotation=stream->readFloat();
                saved->targetRotation=stream->readFloat();
                saved->targetRotation=stream->readFloat();
                saved->targetRotation=stream->readFloat();
            }
        }
    }
}
extern "C" void peopleRestoreAnywaySaveData(void* data,u32 size) {
    GSBinReadStream stream(data,size);
    GSBinReadStream* reader=&stream;
    if(reader->readU16()==0x103 && reader->readU8()==4) {
        _peopleRestoreAnywaySaveData(reader);
        heroMoveTermEvent();gimmickBoxPop();
    }
}
extern "C" void peopleMakeAnywaySaveData(void* data,u32 size) {
    GSBinWriteStream stream(data,size);
    _makeAnywaySaveData(&stream);
}
static void _makeAnywaySaveData(GSBinWriteStream* stream) {
    GSmodel* model;
    s32 count=peopleBiosGetMaxNum();
    stream->writeU16(0x103);stream->writeU8(4);stream->writeU8(count);
    for(s32 i=0;i<peopleBiosGetMaxNum();++i) {
        tagPeopleWork* work=peopleBiosGetWorkPtr(i);
        if(!work->used || (work->resource&0xFFFF0000)==0x7FFE0000) {
            stream->writeU8(0);
        } else {
            stream->writeU8(1);
            u32 start=stream->getWriteSize();
            stream->writeU16(0);
            // Spare bits were not initialized by the retail writer.
            PeopleSaveFlags flags;
            model=work->model;
            flags.state=work->state;flags.visible=work->visible;flags.unknown0E=work->unknown0E;
            flags.running=work->running;flags.collision=work->collisionEnabled;flags.paused=work->walkPaused;
            flags.active=work->walkActive;flags.mode=work->savedWalkMode;flags.phase=work->walkPhase;
            flags.neck=work->neckEnabled;
            stream->writeBytes(&flags,5);
            stream->writeU32(work->flags);stream->writeU32(work->group);
            stream->writeU32(work->resource);stream->writeU32(work->object);
            stream->writeFloat(work->moveSpeed);stream->writeU8(work->savedWalkMode);
            stream->writeFloat(work->moveSpeed);
            stream->writeBytes(&work->walkStartPosition,12);stream->writeBytes(&work->walkTarget,12);
            stream->writeU8(work->walkPointCount);
            if(work->walkPointCount) {
                stream->writeU8(work->walkPointIndex);
                for(s32 j=0;j<work->walkPointCount;++j)stream->writeBytes(&work->walkPoints[j],12);
            }
            switch(work->neckEnabled) {
            case 1: stream->writeU32(work->neckTargetGroup);stream->writeU32(work->neckTargetResource);break;
            case 2: stream->writeBytes(&work->neckTargetPosition,12);break;
            }
            if(model) {
                stream->writeBytes(GSmodelGetPositionPtr(model),12);
                stream->writeBytes(&work->previousPosition,12);
                stream->writeFloat(GSmodelGetRotationPtr(model)->param2);
                stream->writeFloat(work->rotationProgress);
            } else {
                for(s32 j=20;j>0;--j)stream->writeU8(0);
            }
            s32 end;
            u16 length;
            end=stream->getWriteSize();
            stream->cur=stream->start+start;
            if(!stream->writing)stream->cur+=2;
            else {
                length=end-start;
                *stream->cur++=length>>8;
                *stream->cur++=length;
            }
            stream->cur=stream->start+end;
            GSmodelGetPositionPtr(model);
        }
    }
}
