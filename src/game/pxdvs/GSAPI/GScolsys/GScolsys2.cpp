#include <game/pxdvs/GSAPI/GScolsys/GScolsys2Private.hpp>
#include <libc/string.h>
extern "C" {
GSCOLSYS2_STATE GScolsys2;
FloorModuleInterface _floorModuleColsys;
static u8 _colsysVF[0x440];
s32 _hModuleField;
extern Mtx mtxIdent;
void GSgfxDLFree(void *);
void GSgfxVFInit(void *);
void GSgfxVFCreate(void *);
void GSgfxVFSetElement(void *, s32, s32, s32, u8);
void FloorModuleInterface_clear(FloorModuleInterface *);
s32 floorRegisterModule(u32, u32, FloorModuleInterface *);

f32 GScolsy2UtilGetSidePlanePoint(const f32 *normal, const f32 *origin, const f32 *point) {
    return normal[2] * (point[2] - origin[2]) + (normal[0] * (point[0] - origin[0]) + normal[1] * (point[1] - origin[1]));
}
static inline s32 getObject(s32 index, GSCOLSYS2_OBJ **object) {
    if (!GScolsys2.head) return 1;
    if (index < 0 || (u32)index >= GScolsys2.head->count) return 2;
    GSCOLSYS2_OBJ *value = reinterpret_cast<GSCOLSYS2_OBJ *>(reinterpret_cast<u8 *>(&GScolsys2) + GScolsys2.currentFloor * sizeof(GSCOLSYS2_FLOOR) + offsetof(GSCOLSYS2_STATE, floor));
    value += index;
    *object = value;
    return 0;
}
s32 GScolsys2GetObjEnable(s32 index, u8 *enabled) {
    GSCOLSYS2_OBJ *object;
    s32 result = getObject(index, &object);
    if (result == 0) {
        if (object->flags & 1) *enabled = 0;
        else *enabled = 1;
        return 0;
    }
    return result;
}
s32 GScolsys2SetObjEnable(s32 index, u8 enabled) {
    GSCOLSYS2_OBJ *object;
    s32 result = getObject(index, &object);
    if (result == 0) {
        if (enabled) object->flags &= ~1;
        else object->flags |= 1;
        return 0;
    }
    return result;
}
s32 GScolsys2GetObjRotMatrix(Mtx output, u32 index) {
    Mtx x, y, z;
    if (!GScolsys2.head) return 0;
    if (index >= GScolsys2.head->count) return 0;
    GSCOLSYS2_OBJ *object = reinterpret_cast<GSCOLSYS2_OBJ *>(reinterpret_cast<u8 *>(&GScolsys2) + GScolsys2.currentFloor * sizeof(GSCOLSYS2_FLOOR) + offsetof(GSCOLSYS2_STATE, floor));
    object += index;
    memcpy(output, mtxIdent, sizeof(Mtx));
    if (object->flags & 1) {
        PSMTXRotRad(x, 'X', object->rotation[0]);
        PSMTXRotRad(y, 'Y', object->rotation[1]);
        PSMTXConcat(y, x, x);
        PSMTXRotRad(z, 'Z', object->rotation[2]);
        PSMTXConcat(z, x, x);
        PSMTXConcat(x, output, output);
    }
    return 1;
}
s32 GScolsys2GetObjMatrix(Mtx output, u32 index) {
    Mtx x, y, z;
    if (!GScolsys2.head) return 0;
    if (index >= GScolsys2.head->count) return 0;
    GSCOLSYS2_OBJ *object = reinterpret_cast<GSCOLSYS2_OBJ *>(reinterpret_cast<u8 *>(&GScolsys2) + GScolsys2.currentFloor * sizeof(GSCOLSYS2_FLOOR) + offsetof(GSCOLSYS2_STATE, floor));
    object += index;
    memcpy(output, mtxIdent, sizeof(Mtx));
    if (object->flags & 1) {
        PSMTXScaleApply(output, output, object->scale[0], object->scale[1], object->scale[2]);
        PSMTXRotRad(x, 'X', object->rotation[0]);
        PSMTXRotRad(y, 'Y', object->rotation[1]);
        PSMTXConcat(y, x, x);
        PSMTXRotRad(z, 'Z', object->rotation[2]);
        PSMTXConcat(z, x, x);
        PSMTXConcat(x, output, output);
        PSMTXTransApply(output, output, object->position[0], object->position[1], object->position[2]);
    }
    return 1;
}
CCD_FILEHEAD *GScolsys2GetCCDFileHead(void) { return GScolsys2.head; }
GSCOLSYS2_FLOOR *GScolsys2GetCurFloor(void) {
    if (GScolsys2.currentFloor < 0 || GScolsys2.currentFloor >= 1) return 0;
    return &GScolsys2.floor[GScolsys2.currentFloor];
}
s32 GScolsys2UnloadCCD(void) {
    GScolsys2.head = 0;
    if (GScolsys2.displayList) {
        GSgfxDLFree(GScolsys2.displayList);
        GScolsys2.displayList = 0;
    }
    return 1;
}
static inline void offsetGeometry(CCDGeometry *&geometry, u8 *base) {
    if (geometry) {
        geometry = reinterpret_cast<CCDGeometry *>((u32)geometry + (u32)base);
        CCDGeometry *value = geometry;
        if (value->vertices) value->vertices = reinterpret_cast<void *>((u32)value->vertices + (u32)base);
        if (value->indices) value->indices = reinterpret_cast<void *>((u32)value->indices + (u32)base);
        if (value->planes) value->planes = reinterpret_cast<void *>((u32)value->planes + (u32)base);
    }
}
static inline void offsetReference(CCDReference *&reference, u8 *base) {
    if (reference) {
        reference = reinterpret_cast<CCDReference *>((u32)reference + (u32)base);
        CCDReference *value = reference;
        if (value->entries) value->entries = reinterpret_cast<void *>((u32)value->entries + (u32)base);
    }
}
static void _offsetCCD__FP12CCD_FILEHEAD(CCD_FILEHEAD *head) {
    if (head) {
        u8 *base = reinterpret_cast<u8 *>(head);
        head->objects = reinterpret_cast<CCDObject *>((u32)head->objects + (u32)base);
        CCDObject *object = head->objects;
        for (u32 i = 0; i < head->count; ++i, ++object) {
            offsetGeometry(object->geometry[0], base);
            offsetGeometry(object->geometry[1], base);
            offsetGeometry(object->geometry[2], base);
            offsetReference(object->references, base);
            offsetGeometry(object->auxGeometry, base);
            offsetReference(object->auxReferences, base);
        }
    }
}
s32 GScolsys2LoadCCD(CCD_FILEHEAD *head) {
    if (GScolsys2.currentFloor < 0) return 0;
    GSCOLSYS2_FLOOR *floor = &GScolsys2.floor[GScolsys2.currentFloor];
    for (u32 i = 0; i < 48; ++i) floor->auxiliary[i].flags &= ~1;
    _offsetCCD__FP12CCD_FILEHEAD(head);
    GScolsys2.head = head;
    if (head) {
        CCDObject *source = head->objects;
        GSCOLSYS2_OBJ *object = GScolsys2.floor[GScolsys2.currentFloor].objects;
        for (u32 i = 0; i < head->count; ++i, ++object, ++source) {
            object->position[0] = source->position[0];
            object->position[1] = source->position[1];
            object->position[2] = source->position[2];
            object->rotation[0] = source->rotation[0];
            object->rotation[1] = source->rotation[1];
            object->rotation[2] = source->rotation[2];
            object->scale[0] = source->scale[0];
            object->scale[1] = source->scale[1];
            object->scale[2] = source->scale[2];
            object->flags = 0;
        }
    }
    return 1;
}
static const char *_gscolsysGetModuleName__Fv(void) { return "GScolsys"; }
static u32 _gscolsysGetUID__Fv(void) { return 20; }
static u32 _gscolsysGetStateSize__F14FloorStateMode(FloorStateMode mode) {
    if (mode == 1 || mode == 2) return sizeof(GSCOLSYS2_FLOOR);
    if (mode == 3) return sizeof(GSCOLSYS2_FLAGS);
    return 0;
}
static void _gscolsysRestoreStateData__F14FloorStateModePvUl(FloorStateMode mode, void *data, u32 size) {
    if (mode == 1 || mode == 2) {
        if (size == sizeof(GSCOLSYS2_FLOOR)) memcpy(GScolsys2.floor, data, sizeof(GSCOLSYS2_FLOOR));
        return;
    }
    if (mode == 3) {
        GSCOLSYS2_FLAGS *flags = static_cast<GSCOLSYS2_FLAGS *>(data);
        u16 *input = flags->objects;
        for (u32 i = 0; i < 64; ++i) GScolsys2.floor[0].objects[i].flags = *input++;
    }
}
static void _gscolsysMakeStateData__F14FloorStateModePvUl(FloorStateMode mode, void *data, u32 size) {
    if (mode == 1 || mode == 2) {
        if (size == sizeof(GSCOLSYS2_FLOOR)) memcpy(data, GScolsys2.floor, sizeof(GSCOLSYS2_FLOOR));
        return;
    }
    if (mode == 3) {
        GSCOLSYS2_FLAGS *flags = static_cast<GSCOLSYS2_FLAGS *>(data);
        flags->magic = 0xaa55;
        flags->reserved = 0;
        u16 *output = flags->objects;
        for (u32 i = 0; i < 64; ++i) *output++ = GScolsys2.floor[0].objects[i].flags;
    }
}
void GScolsys2Init(void) {
    GScolsys2.currentFloor = 0;
    GScolsys2.displayList = 0;
    GSgfxVFInit(_colsysVF);
    GSgfxVFCreate(_colsysVF);
    GScolsys2.format = _colsysVF;
    GSgfxVFSetElement(GScolsys2.format, 9, 1, 4, 0);
    GSgfxVFSetElement(GScolsys2.format, 11, 1, 5, 0);
    FloorModuleInterface_clear(&_floorModuleColsys);
    _floorModuleColsys.saveState = _gscolsysMakeStateData__F14FloorStateModePvUl;
    _floorModuleColsys.loadState = _gscolsysRestoreStateData__F14FloorStateModePvUl;
    _floorModuleColsys.getStateSize = _gscolsysGetStateSize__F14FloorStateMode;
    _floorModuleColsys.getStateID = _gscolsysGetUID__Fv;
    _floorModuleColsys.getName = _gscolsysGetModuleName__Fv;
    _hModuleField = floorRegisterModule(20, 0, &_floorModuleColsys);
}
}
