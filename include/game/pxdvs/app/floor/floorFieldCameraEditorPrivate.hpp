#ifndef FLOOR_FIELD_CAMERA_EDITOR_PRIVATE_HPP
#define FLOOR_FIELD_CAMERA_EDITOR_PRIVATE_HPP
#include <dolphin/types.h>
struct GSvec {f32 x,y,z;GSvec(){}void clear();};
enum GSgfxPrimType{PrimDummy};enum GSgfxBlendType{BlendDummy};enum GSgfxBlendFactor{FactorDummy};enum GSgfxLayerPass{PassDummy};enum GSgfxCullType{CullDummy};enum GSgfxACmpFunc{ACmpDummy};enum GSgfxAlphaOp{AlphaDummy};enum GSgfxZCmpFunc{ZCmpDummy};
struct GSgfxVF;struct EditorBlendRecord {u8 bytes[0xBC];};
class GSgfxLayer {public:u8 pad0[3468];s32 unkD8C;u8 padD90[2228];s32 unk1644;s32 unk1648;s32 unk164C;s32 unk1650;u8 pad1654[2];u8 unk1656;u8 unk1657;u8 unk1658;u8 pad1659[3];u8 unk165C;u8 pad165D[3];s32 unk1660;s32 unk1664;s32 unk1668;s32 unk166C;u8 unk1670;u8 unk1671;u8 unk1672;u8 pad1673[53];s32 unk16A8;u8 pad16AC[12];s32 unk16B8;u8 pad16BC[80];s32 unk170C;u8 pad1710[80];s32 unk1760;u8 pad1764[12];s32 unk1770;u8 pad1774[80];s32 unk17C4;u8 pad17C8[80];EditorBlendRecord records[2];void* unk1990;s32 unk1994;s32 unk1998;void SetRenderPass(GSgfxLayerPass);void pixelMode(bool,bool,bool);void zCompare(bool,GSgfxZCmpFunc);void alphaCompare(bool,GSgfxACmpFunc,u8,GSgfxAlphaOp,GSgfxACmpFunc,u8);void cullMode(GSgfxCullType);void blendMode(GSgfxBlendType,GSgfxBlendFactor,GSgfxBlendFactor,bool);void setRenderStateAndSelect(GSgfxVF*);void primitiveType(GSgfxPrimType);void beginSurface(u16);void vertex3f(f32,f32,f32);void color4u8(u8,u8,u8,u8);void endSurface();};
struct FieldCamera {u8 rectangular,pad1[3];GSvec position;f32 distance,height,rotation,extent,aspect,angle;u8 pad28[8];f32 fov;};
struct FieldCameraList {u32*count;FieldCamera*cameras;};
struct GSfloor_dd_ {u8 pad[0x14];FieldCameraList*cameras;};
struct FieldCameraEditor {FieldCamera*selected;FieldCameraList*list;u32 count;void*headerAllocation;void*cameraAllocation;u32 floor;FieldCameraList*originalList;u32 application;u8 testing,mode,pad22[2];};
struct ActiveCamera {u8 pad[0xFC];GSvec position;};
namespace std{f32 sinf(f32);f32 cosf(f32);}

extern "C" {static void GXParam1u8(u8 value){*(u8*)0xCC008000=value;}
static void GXParam1f32(f32 value){*(volatile f32*)0xCC008000=value;}}
inline void GSgfxLayer::color4u8(u8 r,u8 g,u8 b,u8 a){GXParam1u8(r);GXParam1u8(g);GXParam1u8(b);GXParam1u8(a);}
inline void GSgfxLayer::vertex3f(f32 x,f32 y,f32 z){GXParam1f32(x);GXParam1f32(y);GXParam1f32(z);}
inline void GSgfxLayer::primitiveType(GSgfxPrimType type){unk1998=type;}
extern "C" inline void GSvecCopy(GSvec*to,const GSvec*from){to->x=from->x;to->y=from->y;to->z=from->z;}
inline void GSgfxLayer::blendMode(GSgfxBlendType arg1,GSgfxBlendFactor arg2,GSgfxBlendFactor arg3,bool arg4){
    if (arg1 == 0) {
        if (arg4 == 1) {
            SetRenderPass((GSgfxLayerPass)0);
        }
        this->unk1644 = 0;
        this->unk1648 = 1;
        this->unk164C = 1;
        this->unk1650 = 5;
    } else {
        if (arg4 == 1) {
            SetRenderPass((GSgfxLayerPass)1);
        }
        this->unk1644 = arg1;
        this->unk1648 = arg2;
        this->unk164C = arg3;
        this->unk1650 = 5;
    }
    this->unk170C = (s32) (this->unk170C | 1);
    this->unk16A8 = (s32) (this->unk16A8 | 0x40);
    this->unk17C4 = (s32) (this->unk17C4 | 1);
    this->unk1760 = (s32) (this->unk1760 | 0x40);
}

inline void GSgfxLayer::SetRenderPass(GSgfxLayerPass arg1){
    if ((s32) this->unk1994 != arg1) {
        this->unk1994 = arg1;
        this->unk1990=&records[this->unk1994];
    }
}

inline void GSgfxLayer::cullMode(GSgfxCullType arg1){
    this->unkD8C = arg1;
    this->unk16B8 = (s32) (this->unk16B8 | 2);
    this->unk16A8 = (s32) (this->unk16A8 | 2);
    this->unk1770 = (s32) (this->unk1770 | 2);
    this->unk1760 = (s32) (this->unk1760 | 2);
}

inline void GSgfxLayer::alphaCompare(bool arg1,GSgfxACmpFunc arg2,u8 arg3,GSgfxAlphaOp arg4,GSgfxACmpFunc arg5,u8 arg6){
    if (arg1 == 1) {
        this->unk1664 = arg2;
        this->unk1670 = arg3;
        this->unk1668 = arg4;
        this->unk166C = arg5;
        this->unk1671 = arg6;
        this->unk1672 = 0;
    } else {
        this->unk1664 = 7;
        this->unk1670 = 0;
        this->unk1668 = 0;
        this->unk166C = 7;
        this->unk1671 = 0;
        this->unk1672 = 1;
    }
    this->unk170C = (s32) (this->unk170C | 0x10);
    this->unk16A8 = (s32) (this->unk16A8 | 0x40);
    this->unk17C4 = (s32) (this->unk17C4 | 0x10);
    this->unk1760 = (s32) (this->unk1760 | 0x40);
}

inline void GSgfxLayer::zCompare(bool arg1,GSgfxZCmpFunc arg2){
    if (arg1 == 1) {
        this->unk165C = 1;
    } else {
        this->unk165C = 0;
    }
    this->unk1660 = arg2;
    this->unk170C = (s32) (this->unk170C | 8);
    this->unk16A8 = (s32) (this->unk16A8 | 0x40);
    this->unk17C4 = (s32) (this->unk17C4 | 8);
    this->unk1760 = (s32) (this->unk1760 | 0x40);
}

inline void GSgfxLayer::pixelMode(bool arg1,bool arg2,bool arg3){
    if (arg1 == 1) {
        this->unk1656 = 1;
    } else {
        this->unk1656 = 0;
    }
    if (arg2 == 1) {
        this->unk1657 = 1;
    } else {
        this->unk1657 = 0;
    }
    if (arg3 == 1) {
        this->unk1658 = 1;
    } else {
        this->unk1658 = 0;
    }
    this->unk170C = (s32) (this->unk170C | 4);
    this->unk16A8 = (s32) (this->unk16A8 | 0x40);
    this->unk17C4 = (s32) (this->unk17C4 | 4);
    this->unk1760 = (s32) (this->unk1760 | 0x40);
}


#endif
