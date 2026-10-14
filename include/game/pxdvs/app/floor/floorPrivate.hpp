#ifndef FLOOR_PRIVATE_HPP
#define FLOOR_PRIVATE_HPP
#include <dolphin/types.h>

struct GSthread;
struct _GSmodel;
struct _GSlight;
struct GSfloor_dd_;

enum FloorStateMode { FloorStateModeNone };
enum FloorEnterMode { FloorEnterModeNone };

struct FloorModuleInterface {
    void (*create)(unsigned int, FloorEnterMode);
    void (*pre)(unsigned int, FloorEnterMode);
    void (*normal)(unsigned int, FloorEnterMode);
    void (*thread)();
    void (*post)(unsigned int, FloorEnterMode);
    void (*free)(unsigned int, FloorEnterMode);
    const char *(*getName)();
    void (*saveState)(FloorStateMode, void *, u32);
    void (*loadState)(FloorStateMode, void *, u32);
    u32 (*getStateSize)(FloorStateMode);
    u32 (*getStateID)();
};

struct GSvec {
    f32 x, y, z;
    GSvec();
    void set(f32 a, f32 b, f32 c) {
        x = a;
        y = b;
        z = c;
    }
    void clear() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
};

extern "C" void PSMTXIdentity(f32 (*)[4]);
struct GSmtx {
    f32 m[3][4];
    GSmtx();
    static GSmtx makeIdentity() {
        GSmtx t;
        PSMTXIdentity(t.m);
        return t;
    }
};

struct GSgfxColAu8 {
    u8 r, g, b, a;
};

enum GSgfxFogType { GSgfxFogNone = 0 };

struct GSsizeS16 {
    u16 w, h;
};

struct GSgfxLayer {
    u8 pad0[0x1678];
    s32 fogType;
    f32 fogStart;
    f32 fogEnd;
    u8 pad1[0x168c - 0x1684];
    u32 fogColor;
    u8 pad2[0x16a4 - 0x1690];
    u16 fogRange;
    u8 fogRangeOn;
    u8 fogOn;
    u32 flags16a8;
    u8 pad3[0x170c - 0x16ac];
    u32 flags170c;
    u8 pad4[0x1760 - 0x1710];
    u32 flags1760;
    u8 pad5[0x17c4 - 0x1764];
    u32 flags17c4;
    void fog(bool on);
    void setFogRange(bool on, u16 range);
    void setFog(GSgfxFogType type, f32 start, f32 end, GSgfxColAu8 color);
};

inline void GSgfxLayer::fog(bool on) {
    fogOn = on;
    flags170c |= 0x40;
    flags17c4 |= 0x40;
    if (on) {
        flags170c |= 0x200;
        flags17c4 |= 0x200;
        if (fogRangeOn) {
            flags170c |= 0x100;
            flags17c4 |= 0x100;
        }
    }
    flags16a8 |= 0x40;
    flags1760 |= 0x40;
}

extern "C" void GSgfxVideoGetEFBSize(GSsizeS16 *, s32);

inline void GSgfxLayer::setFogRange(bool on, u16 range) {
    fogRangeOn = on;
    if (range != 0xFFFF) {
        fogRange = range;
    } else {
        GSsizeS16 size;
        GSgfxVideoGetEFBSize(&size, 0);
        fogRange = size.w >> 1;
    }
    if (fogOn) {
        flags170c |= 0x200;
        flags17c4 |= 0x200;
        if (on) {
            flags170c |= 0x100;
            flags17c4 |= 0x100;
        }
        flags16a8 |= 0x40;
        flags1760 |= 0x40;
    }
}

inline void GSgfxLayer::setFog(GSgfxFogType type, f32 start, f32 end, GSgfxColAu8 color) {
    fogType = type;
    fogStart = start;
    fogEnd = end;
    fogColor = *(u32 *)&color;
    if (fogOn) {
        flags170c |= 0x40;
        flags16a8 |= 0x40;
        flags17c4 |= 0x40;
        flags1760 |= 0x40;
    }
}

struct FLOOR_CHANGE_INFO {
    u32 prevFloorID;
    u32 nextFloorID;
    u8 useInitPosition;
    u32 nextPosIndex;
    GSvec position;
    GSvec rotation;
    u32 fadeInScript;
    u32 fadeOutScript;
    u8 fadeInRequest;
    u8 pad31[0x4c - 0x31];
    u32 returnFloorID;
    u32 returnPrevFloorID;
    u8 returnPosIndex;
    u8 returnValid;
    u8 continueMode;
    u8 dispScriptInfo;
    u32 lightA;
    u32 lightB;
    u8 humanCollision;
    u8 playBgm;
    u8 playEnv;
    u8 pad63;
};

struct FloorRenderData {
    u32 sunID, shadowLightID, shadowReceiverIDs[8], secondaryRenderIDs[3], noFogModelIDs[3];
};
struct FloorPosition {
    s16 rotation;
    u16 reserved2;
    f32 x, y, z;
};
struct FloorPositionList {
    u32 *count;
    FloorPosition *entries;
};
struct GSfloor_dd_ {
    u8 area, kind;
    u16 floorID;
    u32 mapResourceID;
    u32 pad8[14];
};

struct floorCharacter_dd_ {
    u8 visibility : 1, loadInit : 1, isHit : 1, neckTarget : 1, rest : 4;
    u8 pad[0x23];
};

struct FloorTresureEntry {
    u8 kind : 3, rest : 5;
    u8 pad1;
    s16 rotation;
    u16 floorID;
    u16 flagA;
    u16 flagB;
    u16 pad0A;
    u32 pad0C;
    f32 x, y, z;
};
struct FloorDoorEntry {
    u8 pad0[7];
    u8 type;
    u8 pad8[4];
    u16 floorID;
    u16 flag;
    u32 pad10[2];
};

struct SceneData {
    void **models;
    void *pad;
    void **lights;
};

struct FloorBgmMask {
    void initialize();
    void finalize();
    void update(f32);
};
struct FIGHT_ENCOUNT {
    void setDirtyFlag(bool);
};
struct AppScript {
    void unload();
};
namespace GSscript {
struct Tiga : AppScript {
    void debugDump();
    s32 getNameToFuncId(const char *);
};
}
struct Hero {
    static Hero *getHeroPtr();
    void getRestertPos(GSvec *, s16 &) const;
};

struct FogRange {
    u16 pad0, pad2, range;
};
struct FogData {
    u32 type;
    FogRange *range;
    f32 start, end;
    GSgfxColAu8 color;
};

struct EvLogEntry {
    s8 type;
    u32 value;
};

#endif
