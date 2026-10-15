#ifndef LEAFFX_PRIVATE_HPP
#define LEAFFX_PRIVATE_HPP
#include <game/pxdvs/app/wazaSequence/billboardPrivate.hpp>

struct GSmaterial { u8 reserved[0x34]; };
struct GSmodel { u8 reserved[0x5e0]; GSmaterial *materials; u32 materialCount; };
struct LeafQuat { f32 x, y, z, w; };

// Per-leaf state: four bezier control points, two orientations and a live model.
struct leafData {
    GSvec point0;       // 0x00
    GSvec point1;       // 0x0c
    GSvec point2;       // 0x18
    GSvec point3;       // 0x24
    LeafQuat rotFrom;   // 0x30
    LeafQuat rotTo;     // 0x40
    f32 scale;          // 0x50
    f32 progress;       // 0x54
    GSmodel *model;     // 0x58
};

// Parameter block read from the effect stream.
struct leafParams {
    f32 value[10];      // 0x00
    u32 leafCount;      // 0x28
    f32 fallLimit;      // 0x2c
    u32 reserved30;     // 0x30
    u32 trailingSize;   // 0x34
    u32 modelData;      // 0x38
    u32 reserved3C;     // 0x3c
};

class leafEffect : public GSeffect {
public:
    leafData *leaves;   // 0x0c
    GSmodel *model;     // 0x10
    f32 sizeScale;      // 0x14
    f32 sizeBase;       // 0x18
    f32 sizeRange;      // 0x1c
    f32 spreadBase;     // 0x20
    f32 spreadRange;    // 0x24
    f32 driftBase;      // 0x28
    f32 driftRange;     // 0x2c
    f32 liftOffset;     // 0x30
    f32 value34;        // 0x34
    f32 radialBase;     // 0x38
    f32 radialRange;    // 0x3c
    f32 fallLimit;      // 0x40
    f32 elapsed;        // 0x44
    f32 duration;       // 0x48
    u32 leafCount;      // 0x4c
    u32 resourceId;     // 0x50
    GSvec origin;       // 0x54

    leafEffect(u8 **, f32);
    virtual ~leafEffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32);
    bool GenerateLeafData(leafData *);
    void UpdateLeafData(leafData *);
};
#endif
