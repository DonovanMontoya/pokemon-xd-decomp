#include <game/pxdvs/app/light/lightEditorPrivate.hpp>

struct LightVec { f32 x, y, z; };
struct LightColor { u8 r, g, b, a; };
struct LightMtx { f32 m[3][4]; };
struct LightMtxBits { u32 w[12]; };

extern "C" {
s32 floorDataBiosGetCurrentPtr();
s32 floorDataBiosGetShadowLightID(s32);
void* GSresGetResourceAllGroup(u32);
s32 GSlightGetType(GSlight*);
void GSlightSetType(GSlight*, s32);
u32 GSinputButtonsChanged(u32);
u32 GSinputButtonsPressed(u32);
GSlight* lightGetLight(int);
int lightGetLightSize();
void GSlightGetPosition(GSlight*, LightVec*);
void GSlightGetTarget(GSlight*, LightVec*);
void GSlightGetColor(GSlight*, LightColor*);
bool GSlightGetActive(GSlight*);
bool GSlightCanAnimate(GSlight*);
void GSlightSetColor(GSlight*, LightColor*);
f64 sin(f64);
void* peopleBiosGetPosPtr(void*);
void GScameraLoadActiveCameraMatrix(s32);
GSgfxVF* GSgfxVFGetPredef(s32);
u32 cameraGetType();
void cameraSetType(s32);
s32 dbgMenuGetLayerID();
void floorGetLightInfo(s32*, s32*);
GSgfxLayer* GSgfxLayerFindByID(s32);
void GSprint(s32, s32, s32, s32, const char*, ...);
void GSlightSetPosition(GSlight*, LightVec*);
f32 GSgfxVideoGetLastRenderTime();
s32 peopleBiosGetMaxNum();
void* peopleBiosGetWorkPtr(s32);
u32 peopleBiosGetState(void*);
void PSVECNormalize(LightVec*, LightVec*);
void PSVECCrossProduct(LightVec*, LightVec*, LightVec*);
void PSVECScale(LightVec*, LightVec*, f32);
void PSVECAdd(LightVec*, LightVec*, LightVec*);
void PSMTXRotAxisRad(LightMtx*, LightVec*, f32);
void PSMTXRotRad(LightMtx*, s8, f32);
void PSMTXCopy(LightMtx*, LightMtx*);
void PSMTXConcat(LightMtx*, LightMtx*, LightMtx*);
void PSMTXMultVec(LightMtx*, LightVec*, LightVec*);
s8 GSinputGetLeftStickXData(s32, s32);
s8 GSinputGetLeftStickYData(s32, s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
u32 GSinputButtonsRepeat(u32);
void peopleGetPos(s32, s32, LightVec*);
void* GScameraGetActiveCamera();
void GScameraGetPosition(void*, LightVec*);
void GScameraGetFrontVector(void*, LightVec*);
}

class GSstreamFileOutput {
    void* file;
    u32 position;
public:
    GSstreamFileOutput();
    ~GSstreamFileOutput();
    bool open(const char*);
    bool is_open() const;
    bool write(const char*, long);
    bool writeString(const char*);
    void writePrintf(const char*, ...);
};

// Stripped from the DOL; its constants still occupy .sdata2.
void lightEditorStripped(f32* a, f32* b) {
    *a = 0.1f;
    *b = 1.0f;
}

void LightEditor::editDirection(GSlight* light) {
    f32 dt = GSgfxVideoGetLastRenderTime();
    f32 scale = 1000.0f;
    u32 trig = GSinputButtonsChanged(1);
    trig = GSinputButtonsPressed(1) & trig;
    s32 max = peopleBiosGetMaxNum();
    s32 idx = mUnk4;
    LightVec pos;
    LightVec dir;
    LightVec up;
    LightVec right;
    LightMtx rot;
    LightMtx rotCopy;
    LightMtx yaw;
    LightMtx result;
    if (trig & 0x20) {
        for (s32 i = 0; i < max; i++) {
            idx++;
            if (idx >= max) {
                idx = 0;
            }
            if (peopleBiosGetState(peopleBiosGetWorkPtr(idx)) == 3) {
                mUnk4 = idx;
                break;
            }
        }
    }
    GSlightGetPosition(light, &pos);
    dir.x = pos.x; dir.y = pos.y; dir.z = pos.z;
    PSVECNormalize(&dir, &dir);
    f32 lx = dt * GSinputGetLeftStickXData(1, 0);
    f32 ly = dt * GSinputGetLeftStickYData(1, 0);
    GSinputGetRightStickXData(1, 0);
    GSinputGetRightStickYData(1, 0);
    if (!(GSinputButtonsPressed(1) & 0x40)) {
        scale *= 4.0f;
    }
    f32 yawAmt = lx / scale;
    f32 pitchAmt = ly / scale;
    dir.x = pos.x; dir.y = pos.y; dir.z = pos.z;
    PSVECNormalize(&dir, &dir);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    if (dir.x < 0.00001f && dir.x > -0.00001f && dir.z < 0.00001f && dir.z > -0.00001f) {
        if (dir.y > 0.0f) {
            up.x = 1.0f;
            up.y = 0.0f;
            up.z = 0.0f;
        } else {
            up.x = 1.0f;
            up.y = 0.0f;
            up.z = 0.0f;
        }
    }
    PSVECCrossProduct(&dir, &up, &right);
    PSMTXRotAxisRad(&rot, &right, -pitchAmt);
    *(LightMtxBits*)&rotCopy = *(LightMtxBits*)&rot;
    PSMTXCopy(&rotCopy, &result);
    PSMTXRotRad(&yaw, 'Y', yawAmt);
    PSMTXConcat(&yaw, &result, &result);
    PSMTXMultVec(&result, &pos, &pos);
    GSlightSetPosition(light, &pos);
}

void LightEditor::editPosition(GSlight* light) {
    f32 dt = GSgfxVideoGetLastRenderTime();
    f32 scale = 64.0f;
    f32 step;
    void* cam = GScameraGetActiveCamera();
    LightVec pos;
    LightVec sum;
    LightVec mvR;
    LightVec mvU;
    LightVec mvF;
    LightVec front;
    LightVec up;
    LightVec right;
    GScameraGetPosition(cam, &pos);
    GScameraGetFrontVector(cam, &front);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    PSVECCrossProduct(&front, &up, &right);
    PSVECCrossProduct(&front, &right, &up);
    mvR.x = 0.0f;
    mvR.y = 0.0f;
    mvR.z = 0.0f;
    mvU.x = 0.0f;
    mvU.y = 0.0f;
    mvU.z = 0.0f;
    mvF.x = 0.0f;
    mvF.y = 0.0f;
    mvF.z = 0.0f;
    GSlightGetPosition(light, &pos);
    f32 lx = dt * GSinputGetLeftStickXData(1, 0);
    f32 ly = dt * GSinputGetLeftStickYData(1, 0);
    f32 rx = dt * GSinputGetRightStickXData(1, 0);
    f32 ry = dt * GSinputGetRightStickYData(1, 0);
    f32 arx = rx < 0.0f ? -rx : rx;
    f32 alx = lx < 0.0f ? -lx : lx;
    if (alx < arx) {
        lx = rx;
    }
    if (GSinputButtonsPressed(1) & 0x40) {
        scale *= 0.25;
    }
    mvR.x = right.x; mvR.y = right.y; mvR.z = right.z;
    PSVECScale(&mvR, &mvR, lx / scale);
    mvU.x = up.x; mvU.y = up.y; mvU.z = up.z;
    PSVECScale(&mvU, &mvU, ly / scale);
    mvF.x = front.x; mvF.y = front.y; mvF.z = front.z;
    PSVECScale(&mvF, &mvF, -ry / scale);
    PSVECAdd(&mvR, &mvU, &sum);
    PSVECAdd(&sum, &mvF, &sum);
    PSVECAdd(&pos, &sum, &pos);
    if (mUnk1 == 2) {
        f32* p = 0;
        step = 0.1f;
        switch (mUnk2) {
        case 0: p = &pos.x; break;
        case 1: p = &pos.y; break;
        case 2: p = &pos.z; break;
        }
        if (p != 0) {
            if (GSinputButtonsPressed(1) & 0x40) {
                step = 1.0f;
            }
            if (GSinputButtonsRepeat(1) & 0x400) {
                *p -= step;
            }
            if (GSinputButtonsRepeat(1) & 0x800) {
                *p += step;
            }
        }
    }
    if (GSinputButtonsRepeat(1) & 0x10) {
        mUnk3 = !mUnk3;
        if (mUnk3) {
            peopleGetPos(0, 100, &pos);
            pos.y += 18.0f;
        } else {
            void* c2 = GScameraGetActiveCamera();
            LightVec f2;
            GScameraGetPosition(c2, &pos);
            GScameraGetFrontVector(c2, &f2);
            PSVECScale(&f2, &f2, 50.0f);
            PSVECAdd(&pos, &f2, &pos);
        }
    }
    GSlightSetPosition(light, &pos);
}

void LightEditor::editType(GSlight* light) {
    if (mUnk1 != 0) {
        return;
    }
    if ((GSlight*)GSresGetResourceAllGroup(floorDataBiosGetShadowLightID(floorDataBiosGetCurrentPtr())) == light) {
        return;
    }
    s32 type = GSlightGetType(light);
    s32 newType = 0xff;
    u32 changed = GSinputButtonsChanged(1);
    u32 pressed = GSinputButtonsPressed(1);
    if (pressed & changed & 0x400) {
        if (type == 0) { newType = 3; } else if (type == 1) { newType = 0; } else if (type == 2) { newType = 1; } else if (type == 3) { newType = 2; }
    }
    changed = GSinputButtonsChanged(1);
    pressed = GSinputButtonsPressed(1);
    if (pressed & changed & 0x800) {
        if (type == 0) { newType = 1; } else if (type == 1) { newType = 2; } else if (type == 2) { newType = 3; } else if (type == 3) { newType = 0; }
    }
    if (newType != 0xff) {
        GSlightSetType(light, newType);
    }
}

void LightEditor::editCommand() {
    LightColor color;
    LightVec target;
    LightVec pos;
    bool isShadow;
    const char* name;
    bool hasVec;
    int i;
    GSstreamFileOutput out;
    u32 changed = GSinputButtonsChanged(1);
    u32 pressed = GSinputButtonsPressed(1);
    if (!(pressed & changed & 0x100)) {
        return;
    }
    if (!out.open("lightinfo.txt")) {
        return;
    }
    out.writePrintf("//type, color, pos/dir\n");
    for (i = 0; i < lightGetLightSize(); i++) {
        GSlight* light = lightGetLight(i);
        isShadow = (GSlight*)GSresGetResourceAllGroup(floorDataBiosGetShadowLightID(floorDataBiosGetCurrentPtr())) == light;
        hasVec = false;
        switch (GSlightGetType(light)) {
        case 0: name = "Amb"; break;
        case 1: name = "Dir"; hasVec = true; break;
        case 2: name = "Pnt"; hasVec = true; break;
        case 3: name = "Spt"; hasVec = true; break;
        default: name = "???"; break;
        }
        GSlightGetPosition(light, &pos);
        GSlightGetTarget(light, &target);
        GSlightGetColor(light, &color);
        out.writePrintf("%s: ", name);
        out.writePrintf("(%d,%d,%d) ", color.r, color.b, color.g);
        if (hasVec) {
            out.writePrintf("(%.2f,%.2f,%.2f)", pos.x, pos.y, pos.z);
        }
        if (isShadow) {
            out.writePrintf("\t// shadow light");
        }
        out.writePrintf("\n");
    }
}

// Stripped from the DOL; its strings still occupy .sdata2.
void lightEditorSave() {
    GSprint(0, 0, 0, 0, "save");
}

void LightEditor::dispLightModel(GSlight* light, bool selected) {
    LightVec pos;
    LightVec dir;
    LightVec tgt;
    LightVec peoplePos;
    LightVec scaled;
    LightColor col;
    static f32 widthArray[8] = { -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f };
    f32 size = 0.5f;
    if (GSlightGetActive(light)) {
        if (selected) {
            f32 delta;
            if ((f32)sin(mUnk8) / 2.0f < 0.0f) {
                delta = -((f32)sin(mUnk8) / 2.0f);
            } else {
                delta = (f32)sin(mUnk8) / 2.0f;
            }
            size += delta;
            mUnk8 += 0.1f;
            if (mUnk8 > 6.2831855f) {
                mUnk8 = 0.0f;
            }
        }
        if (GSlightGetType(light) == 0) {
            return;
        }
        GSlightGetPosition(light, &pos);
        GSlightGetTarget(light, &tgt);
        GSlightGetColor(light, &col);
        if (GSlightGetType(light) == 1) {
            void* work = peopleBiosGetWorkPtr(mUnk4);
            if (work != 0) {
                LightVec* pp = (LightVec*)peopleBiosGetPosPtr(work);
                peoplePos.x = pp->x;
                peoplePos.y = pp->y;
                peoplePos.z = pp->z;
                dir.x = pos.x;
                dir.y = pos.y;
                dir.z = pos.z;
                PSVECNormalize(&dir, &dir);
                scaled.x = dir.x;
                scaled.y = dir.y;
                scaled.z = dir.z;
                PSVECScale(&scaled, &scaled, 20.0f);
                PSVECAdd(&scaled, &peoplePos, &pos);
                pos.y += 5.0f;
            }
        }
        GSgfxLayer* layer = GSgfxLayerFindByID(2);
        if (layer == 0) {
            return;
        }
        GScameraLoadActiveCameraMatrix(layer->unk28);
        LAYER_PIXELMODE(layer, true, true, true);
        LAYER_ZCOMPARE(layer, true, 1);
        LAYER_ALPHACOMPARE_OFF(layer);
        LAYER_CULLMODE(layer, 0);
        LAYER_BLENDMODE_NORMAL(layer, 1, 4, 5);
        layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
        LAYER_PRIMITIVETYPE(layer, 0x80);
        layer->beginSurface(0x18);
        s32 i;
        for (i = 0; i < 4; i++) {
            LAYER_VERTEX3F(pos.x + size, pos.y + size * widthArray[i * 2], pos.z + size * widthArray[i * 2 + 1]);
            LAYER_COLOR4U8(col.r, col.g, col.b, 255);
        }
        for (i = 0; i < 4; i++) {
            s32 k = 3 - i;
            LAYER_VERTEX3F(pos.x - size, pos.y + size * widthArray[k * 2], pos.z + size * widthArray[k * 2 + 1]);
            LAYER_COLOR4U8(col.r, col.g, col.b, 255);
        }
        for (i = 0; i < 4; i++) {
            LAYER_VERTEX3F(pos.x + size * widthArray[i * 2], pos.y + size, pos.z + size * widthArray[i * 2 + 1]);
            LAYER_COLOR4U8(col.r, col.g, col.b, 255);
        }
        for (i = 0; i < 4; i++) {
            s32 k = 3 - i;
            LAYER_VERTEX3F(pos.x + size * widthArray[k * 2], pos.y - size, pos.z + size * widthArray[k * 2 + 1]);
            LAYER_COLOR4U8(col.r, col.g, col.b, 255);
        }
        for (i = 0; i < 4; i++) {
            LAYER_VERTEX3F(pos.x + size * widthArray[i * 2], pos.y + size * widthArray[i * 2 + 1], pos.z + size);
            LAYER_COLOR4U8(col.r, col.g, col.b, 255);
        }
        for (i = 0; i < 4; i++) {
            s32 k = 3 - i;
            LAYER_VERTEX3F(pos.x + size * widthArray[k * 2], pos.y + size * widthArray[k * 2 + 1], pos.z - size);
            LAYER_COLOR4U8(col.r, col.g, col.b, 255);
        }
        layer->endSurface();
        if (selected) {
            LAYER_PRIMITIVETYPE(layer, 0xa8);
            LAYER_LINESIZE(layer, 12, 0);
            layer->beginSurface(6);
            LAYER_VERTEX3F(pos.x, pos.y - 100.0f, pos.z);
            LAYER_COLOR4U8(255, 0, 0, 255);
            LAYER_VERTEX3F(pos.x, pos.y + 100.0f, pos.z);
            LAYER_COLOR4U8(255, 0, 0, 255);
            LAYER_VERTEX3F(pos.x - 100.0f, pos.y, pos.z);
            LAYER_COLOR4U8(0, 255, 0, 255);
            LAYER_VERTEX3F(pos.x + 100.0f, pos.y, pos.z);
            LAYER_COLOR4U8(0, 255, 0, 255);
            LAYER_VERTEX3F(pos.x, pos.y, pos.z - 100.0f);
            LAYER_COLOR4U8(0, 0, 255, 255);
            LAYER_VERTEX3F(pos.x, pos.y, pos.z + 100.0f);
            LAYER_COLOR4U8(0, 0, 255, 255);
            layer->endSurface();
        }
        if (GSlightGetType(light) == 1) {
            PSVECScale(&dir, &dir, 10.0f);
            LAYER_PRIMITIVETYPE(layer, 0xb0);
            LAYER_LINESIZE(layer, 12, 0);
            layer->beginSurface(2);
            LAYER_VERTEX3F(pos.x, pos.y, pos.z);
            LAYER_COLOR4U8(col.r, col.g, col.b, 255);
            LAYER_VERTEX3F(pos.x - dir.x, pos.y - dir.y, pos.z - dir.z);
            LAYER_COLOR4U8(col.r, col.g, col.b, 255);
            layer->endSurface();
        }
    }
}

void LightEditor::dispInfo(GSlight* light, long x, long y, bool selected) {
    LightVec pos;
    LightVec tgt;
    LightColor col;
    const char* name;
    bool isShadow;
    bool hasVec = false;
    isShadow = (GSlight*)GSresGetResourceAllGroup(floorDataBiosGetShadowLightID(floorDataBiosGetCurrentPtr())) == light;
    s32 layer;
    s32 color;
    layer = dbgMenuGetLayerID();
    if (layer != -1) {
        color = selected ? -0x7f01 : -1;
        GSlightGetActive(light);
        GSlightGetPosition(light, &pos);
        GSlightGetTarget(light, &tgt);
        GSlightGetColor(light, &col);
        GSlightCanAnimate(light);
        switch (GSlightGetType(light)) {
        case 0: name = "Amb"; break;
        case 1: name = "Dir"; hasVec = true; break;
        case 2: name = "Pnt"; hasVec = true; break;
        case 3: name = "Spt"; hasVec = true; break;
        default: name = "???"; break;
        }
        s32 l2 = layer;
        GSprint(layer, x, y, mUnk1 == 0 ? color : -1, "%s:", name);
        bool on = false;
        if (mUnk2 == 0 && mUnk1 == 1) { on = true; }
        GSprint(layer, x + 0x34, y, on ? color : -1, "(%02x,", col.r);
        on = false;
        if (mUnk2 == 1 && mUnk1 == 1) { on = true; }
        GSprint(l2, x + 0x5b, y, on ? color : -1, "%02x,", col.g);
        on = false;
        if (mUnk2 == 2 && mUnk1 == 1) { on = true; }
        s32 lastColor = on ? color : -1;
        GSprint(l2, x + 0x7a, y, lastColor, "%02x)", col.b);
        if (hasVec) {
            on = false;
            if (mUnk2 == 0 && mUnk1 == 2) { on = true; }
            GSprint(l2, x + 0xb6, y, on ? color : -1, "(%.2f,", pos.x);
            on = false;
            if (mUnk2 == 1 && mUnk1 == 2) { on = true; }
            GSprint(l2, x + 0xf7, y, on ? color : -1, " %.2f,", pos.y);
            on = false;
            if (mUnk2 == 2 && mUnk1 == 2) { on = true; }
            lastColor = on ? color : -1;
            GSprint(l2, x + 0x130, y, lastColor, " %.2f)", pos.z);
        }
        if (isShadow) {
            GSprint(l2, x + 0x17e, y, lastColor, "(shadow)");
        }
    }
}

void GSprimSetup3DRender(GSgfxLayer*);

void LightEditor::editUpdate() {
    s32 i;
    GSgfxVideoGetLastRenderTime();
    s32 rep = GSinputButtonsRepeat(1);
    if (rep & 0x1000) {
        if ((u8)cameraGetType() == 6) {
            cameraSetType(3);
        } else {
            cameraSetType(6);
        }
    }
    if ((u8)cameraGetType() != 6) {
        if (rep & 4) {
            mUnk0++;
        }
        if (mUnk0 >= lightGetLightSize()) {
            mUnk0 = -1;
        }
        if (rep & 8) {
            mUnk0--;
        }
        if (mUnk0 < -1) {
            mUnk0 = lightGetLightSize() - 1;
        }
        if (mUnk0 < 0) {
            editCommand();
        } else {
            GSlight* light = lightGetLight(mUnk0);
            if (light == 0) {
                return;
            }
            s32 type = GSlightGetType(light);
            if (rep & 2) {
                if (mUnk1 == 0) {
                    mUnk1 = 1;
                    mUnk2 = 0;
                } else if (mUnk1 == 1) {
                    mUnk2++;
                    if (mUnk2 > 2) {
                        if (type == 0) {
                            mUnk1 = 0;
                        } else {
                            mUnk1 = 2;
                        }
                        mUnk2 = 0;
                    }
                } else if (mUnk1 == 2) {
                    mUnk2++;
                    if (mUnk2 > 2) {
                        mUnk1 = 0;
                        mUnk2 = 0;
                    }
                }
            }
            if (rep & 1) {
                if (mUnk1 == 0) {
                    if (type == 0) {
                        mUnk1 = 1;
                        mUnk2 = 2;
                    } else {
                        mUnk1 = 2;
                    }
                    mUnk2 = 2;
                } else if (mUnk1 == 1) {
                    mUnk2--;
                    if (mUnk2 < 0) {
                        mUnk1 = 0;
                        mUnk2 = 0;
                    }
                } else if (mUnk1 == 2) {
                    mUnk2--;
                    if (mUnk2 < 0) {
                        mUnk1 = 1;
                        mUnk2 = 2;
                    }
                }
            }
            editType(light);
            u8* p = 0;
            if (mUnk1 == 1) {
                LightColor col2;
                LightColor col;
                GSlightGetColor(light, &col);
                switch (mUnk2) {
                case 0: p = &col.r; break;
                case 1: p = &col.g; break;
                case 2: p = &col.b; break;
                }
                if (p != 0) {
                    if (GSinputButtonsRepeat(1) & 0x400) {
                        (*p)--;
                    }
                    if (GSinputButtonsRepeat(1) & 0x800) {
                        (*p)++;
                    }
                    *(u32*)&col2 = *(u32*)&col;
                    GSlightSetColor(light, &col2);
                }
            }
            if (type == 1) {
                editDirection(light);
            } else {
                editPosition(light);
            }
        }
    }
    s32 n;
    s32 a;
    rep = dbgMenuGetLayerID();
    floorGetLightInfo(&a, &n);
    n = lightGetLightSize();
    GSgfxLayer* gl = GSgfxLayerFindByID(2);
    if (gl != 0) {
        GSprimSetup3DRender(gl);
    }
    for (i = 0; i < n; i++) {
        dispLightModel(lightGetLight(i), mUnk0 == i);
    }
    s32 y = 30;
    for (i = 0; i < n; i++) {
        dispInfo(lightGetLight(i), 20, y, mUnk0 == i);
        y += 13;
    }
    if (rep != -1) {
        GSprint(rep, 20, y, mUnk0 < 0 ? -0x7f01 : -1, "save");
    }
    s32 layer2 = dbgMenuGetLayerID();
    if (layer2 != -1) {
        if ((u8)cameraGetType() == 6) {
            GSprint(layer2, 500, 32, -1, "camera mode");
        } else {
            GSprint(layer2, 500, 32, -1, "light mode");
        }
    }
}

LightEditor::LightEditor() {
    mUnk4 = 0;
    mUnk0 = 0;
    mUnk1 = 0;
    mUnk8 = 1.0f;
    mUnk3 = 0;
}

void LightEditor::init() {
    mUnk4 = 0;
    mUnk0 = 0;
    mUnk1 = 0;
    mUnk8 = 1.0f;
    mUnk3 = 0;
}
