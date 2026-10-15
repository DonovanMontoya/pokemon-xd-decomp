#include <game/pxdvs/app/fade/fadeFluidPrivate.hpp>

static FluidWork _fadeFluidWork;
static s32 _fadeFluidSw;
static void _fadeFluidDoFree(void *);
static void *_fadeFluidDoMalloc(unsigned long);
static void _fadeFluidSetShockSub(unsigned long,unsigned long,f32);

extern "C" f32 __float_nan;
static inline f32 FluidSqrt(f32 x) {
    if (x > 0.0f) {
        f64 guess=__frsqrte((f64)x);
        guess=0.5*guess*(3.0-guess*guess*x);
        guess=0.5*guess*(3.0-guess*guess*x);
        guess=0.5*guess*(3.0-guess*guess*x);
        return (f32)(x*guess);
    } else if (x < 0.0) return __float_nan;
    else {
        union {f32 f;u32 u;} value;
        value.f=x;
        s32 category;
        switch (value.u & 0x7F800000) {
        case 0x7F800000:category=(value.u & 0x7FFFFF)!=0?1:2;break;
        case 0:category=(value.u & 0x7FFFFF)!=0?5:3;break;
        default:category=4;break;
        }
        if (category == 1) return __float_nan;
    }
    return x;
}

static inline void FluidVertex(FluidVec *vertex,FluidUV *uv,f32 sx,f32 sy,u8 alpha) {
    *(volatile f32 *)0xCC008000=vertex->x*sx;
    *(volatile f32 *)0xCC008000=vertex->y*sy;
    *(volatile f32 *)0xCC008000=vertex->z*sx;
    *(volatile u8 *)0xCC008000=255;
    *(volatile u8 *)0xCC008000=255;
    *(volatile u8 *)0xCC008000=255;
    *(volatile u8 *)0xCC008000=alpha;
    *(volatile f32 *)0xCC008000=uv->u;
    *(volatile f32 *)0xCC008000=uv->v;
}

extern "C" void fadeFluidDispSecond(s32 layerId,GStexture *texture,f32 fade,f32 progress) {

    GSgfxLayer *layer=GSgfxLayerFindByID(layerId);
    FluidVec to;
    FluidVec from;
    FluidVec color;
    from.x=1.0f;from.y=1.0f;from.z=1.0f;
    to.x=0.0f;to.y=0.0f;to.z=0.0f;
    GSlerpGetLinearInterpolationVector(&color,&from,&to,progress);
    f32 value=(f32)(s32)(255.0f*color.x);
    s32 alpha=(s32)(value*(1.0f-fade));
    spriteSetEnv(layerId);
    if (layer->shaderIndex != 1) {
        layer->shaderIndex=1;
        layer->shader=layer->shaders[layer->shaderIndex];
    }
    layer->field1644=1;layer->field1648=4;layer->field164C=5;layer->field1650=5;
    layer->field170C|=1;layer->field16A8|=0x40;layer->field17C4|=1;layer->field1760|=0x40;
    layer->field1656=1;layer->field1657=1;layer->field1658=0;
    layer->field170C|=4;layer->field16A8|=0x40;layer->field17C4|=4;layer->field1760|=0x40;
    layer->field165C=0;layer->field1660=1;
    layer->field170C|=8;layer->field16A8|=0x40;layer->field17C4|=8;layer->field1760|=0x40;
    layer->field1664=7;layer->field1670=0;layer->field1668=0;layer->field166C=7;layer->field1671=0;layer->field1672=1;
    layer->field170C|=16;layer->field16A8|=0x40;layer->field17C4|=16;layer->field1760|=0x40;
    layer->fieldD8C=0;
    layer->field16B8|=2;layer->field16A8|=2;layer->field1770|=2;layer->field1760|=2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1,4,0,0,1,5,1,1,4));
    if (layer->texture0 != texture || layer->texture1 != texture || texture->dirty != 0) {
        layer->texture0=texture;layer->field173C|=1;
        layer->texture1=texture;layer->field17F4|=1;
    }
    f32 sx=_fadeFluidWork.screenX,sy=_fadeFluidWork.screenY;
    u32 stride=_fadeFluidWork.width+1;
    u16 count=stride*2;
    for (u32 y=0;y<_fadeFluidWork.height;++y) {
        layer->primitive=0x98;
        layer->beginSurface(count);
        for (u32 x=0;x<stride;++x) {
            u32 i=x+y*stride,j=x+(y+1)*stride;
            FluidVertex(&_fadeFluidWork.vertices[_fadeFluidSw][i],&_fadeFluidWork.uv[i],sx,sy,alpha);
            FluidVertex(&_fadeFluidWork.vertices[_fadeFluidSw][j],&_fadeFluidWork.uv[j],sx,sy,alpha);
        }
        layer->endSurface();
    }
}
extern "C" void fadeFluidDisp(GStexture *texture,f32 fade,f32 progress) {

    GSgfxLayer *layer=GSgfxLayerFindByID(7);
    FluidVec to;
    FluidVec from;
    FluidVec color;
    from.x=1.0f;from.y=1.0f;from.z=1.0f;
    to.x=0.0f;to.y=0.0f;to.z=0.0f;
    GSlerpGetLinearInterpolationVector(&color,&from,&to,progress);
    f32 value=(f32)(s32)(255.0f*color.x);
    s32 alpha=(s32)(value*(1.0f-fade));
    spriteSetEnv(7);
    if (layer->shaderIndex != 1) {
        layer->shaderIndex=1;
        layer->shader=layer->shaders[layer->shaderIndex];
    }
    layer->field1644=1;layer->field1648=4;layer->field164C=5;layer->field1650=5;
    layer->field170C|=1;layer->field16A8|=0x40;layer->field17C4|=1;layer->field1760|=0x40;
    layer->field1656=1;layer->field1657=1;layer->field1658=0;
    layer->field170C|=4;layer->field16A8|=0x40;layer->field17C4|=4;layer->field1760|=0x40;
    layer->field165C=0;layer->field1660=1;
    layer->field170C|=8;layer->field16A8|=0x40;layer->field17C4|=8;layer->field1760|=0x40;
    layer->field1664=7;layer->field1670=0;layer->field1668=0;layer->field166C=7;layer->field1671=0;layer->field1672=1;
    layer->field170C|=16;layer->field16A8|=0x40;layer->field17C4|=16;layer->field1760|=0x40;
    layer->fieldD8C=0;
    layer->field16B8|=2;layer->field16A8|=2;layer->field1770|=2;layer->field1760|=2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1,4,0,0,1,5,1,1,4));
    if (layer->texture0 != texture || layer->texture1 != texture || texture->dirty != 0) {
        layer->texture0=texture;layer->field173C|=1;
        layer->texture1=texture;layer->field17F4|=1;
    }
    layer->primitive=0x98;
    f32 sx=_fadeFluidWork.screenX,sy=_fadeFluidWork.screenY;
    u32 stride=_fadeFluidWork.width+1;
    u16 count=stride*2;
    for (u32 y=0;y<_fadeFluidWork.height;++y) {
        layer->beginSurface(count);
        for (u32 x=0;x<stride;++x) {
            u32 i=x+y*stride,j=x+(y+1)*stride;
            FluidVertex(&_fadeFluidWork.vertices[_fadeFluidSw][i],&_fadeFluidWork.uv[i],sx,sy,alpha);
            FluidVertex(&_fadeFluidWork.vertices[_fadeFluidSw][j],&_fadeFluidWork.uv[j],sx,sy,alpha);
        }
        layer->endSurface();
    }
}
extern "C" void fadeFluidSetShockSecond(FluidVec *point,f32 strength) {
    f32 spacing=_fadeFluidWork.spacing;
    u32 x=(u32)(point->x/spacing),y=(u32)(point->y/spacing);
    _fadeFluidSetShockSub(x,y,strength);
    f32 diagonal=0.25f*strength,adjacent=0.5f*strength;
    _fadeFluidSetShockSub(x-1,y-1,diagonal);
    _fadeFluidSetShockSub(x,y-1,adjacent);
    _fadeFluidSetShockSub(x+1,y-1,diagonal);
    _fadeFluidSetShockSub(x-1,y,adjacent);
    _fadeFluidSetShockSub(x+1,y,adjacent);
    _fadeFluidSetShockSub(x-1,y+1,diagonal);
    _fadeFluidSetShockSub(x,y+1,adjacent);
    _fadeFluidSetShockSub(x+1,y+1,diagonal);
}
extern "C" void fadeFluidEvaluateSecond() {
    f32 a=_fadeFluidWork.a,b=_fadeFluidWork.b,c=_fadeFluidWork.c;
    u32 stride=_fadeFluidWork.width+1;
    for (u32 y=1;y<_fadeFluidWork.height;++y) {
        FluidVec *row=&_fadeFluidWork.vertices[_fadeFluidSw][y*stride];
        FluidVec *current=row+1;
        FluidVec *next=&_fadeFluidWork.vertices[1-_fadeFluidSw][y*stride+1];
        for (u32 x=1;x<_fadeFluidWork.width;++x,++current,++next) {
            f32 sides=current[1].z+current[-1].z;
            next->z=c*(row[(s32)x-(s32)stride].z+(sides+row[x+stride].z))+
                (a*current->z+b*next->z);
        }
    }
    _fadeFluidSw=1-_fadeFluidSw;
}
extern "C" void fadeFluidSetShock(FluidVec *point,f32 strength) {
    f32 spacing=_fadeFluidWork.spacing;
    u32 x=(u32)(point->x/spacing),y=(u32)(point->y/spacing);
    _fadeFluidSetShockSub(x,y,strength);
    strength=strength/2.0f;
    _fadeFluidSetShockSub(x-1,y-1,strength);
    _fadeFluidSetShockSub(x,y-1,strength);
    _fadeFluidSetShockSub(x+1,y-1,strength);
    _fadeFluidSetShockSub(x-1,y,strength);
    _fadeFluidSetShockSub(x+1,y,strength);
    _fadeFluidSetShockSub(x-1,y+1,strength);
    _fadeFluidSetShockSub(x,y+1,strength);
    _fadeFluidSetShockSub(x+1,y+1,strength);
}
static void _fadeFluidSetShockSub(unsigned long x,unsigned long y,f32 strength) {
    if (x<=_fadeFluidWork.width && y<=_fadeFluidWork.height) {
        u8 *base=(u8 *)_fadeFluidWork.vertices[_fadeFluidSw];
        u32 offset=(x+y*(_fadeFluidWork.width+1))*12+8;
        *(f32 *)(base+offset)-=strength;
    }
}
extern "C" void fadeFluidEvaluate() {
    f32 a=_fadeFluidWork.a,b=_fadeFluidWork.b,c=_fadeFluidWork.c;
    u32 stride=_fadeFluidWork.width+1;
    for (u32 y=1;y<_fadeFluidWork.height;++y) {
        FluidVec *row=&_fadeFluidWork.vertices[_fadeFluidSw][y*stride];
        FluidVec *current=row+1;
        FluidVec *next=&_fadeFluidWork.vertices[1-_fadeFluidSw][y*stride+1];
        for (u32 x=1;x<_fadeFluidWork.width;++x,++current,++next) {
            f32 sides=current[1].z+current[-1].z;
            next->z=c*(row[(s32)x-(s32)stride].z+(sides+row[x+stride].z))+
                (a*current->z+b*next->z);
        }
    }
    _fadeFluidSw=1-_fadeFluidSw;
    for (u32 y=1;y<_fadeFluidWork.height;++y) {
        FluidVec *row=&_fadeFluidWork.vertices[_fadeFluidSw][y*stride];
        FluidVec *current=row+1;
        FluidVec *normal=&_fadeFluidWork.normal[y*stride+1];
        FluidVec *tangent=&_fadeFluidWork.tangent[y*stride+1];
        for (u32 x=1;x<_fadeFluidWork.width;++x,++current,++normal,++tangent) {
            normal->x=current[-1].z-current[1].z;
            normal->y=row[(s32)x-(s32)stride].z-row[x+stride].z;
            tangent->z=current[1].z-current[-1].z;
        }
    }
}
extern "C" void fadeFluidCalcParms(f32 delta) {
    f32 speed;
    f32 ratio;
    f32 spacing;
    f32 inverse;
    f32 damping;
    speed=_fadeFluidWork.speed;
    spacing=_fadeFluidWork.spacing;
    damping=_fadeFluidWork.damping*delta;
    inverse=1.0f/(2.0f+damping);
    ratio=(delta*(delta*(speed*speed)))/(spacing*spacing);
    _fadeFluidWork.b=inverse*(damping-2.0f);
    _fadeFluidWork.a=-((8.0f*ratio)-4.0f)*inverse;
    _fadeFluidWork.c=2.0f*ratio*inverse;
}

extern "C" void fadeFluidQuit() {
    if (_fadeFluidWork.vertices[0]!=0) _fadeFluidDoFree(_fadeFluidWork.vertices[0]);
    if (_fadeFluidWork.vertices[1]!=0) _fadeFluidDoFree(_fadeFluidWork.vertices[1]);
    if (_fadeFluidWork.normal!=0) _fadeFluidDoFree(_fadeFluidWork.normal);
    if (_fadeFluidWork.tangent!=0) _fadeFluidDoFree(_fadeFluidWork.tangent);
    if (_fadeFluidWork.uv!=0) _fadeFluidDoFree(_fadeFluidWork.uv);
    _fadeFluidWork.vertices[0]=0;_fadeFluidWork.vertices[1]=0;
    _fadeFluidWork.normal=0;_fadeFluidWork.tangent=0;_fadeFluidWork.uv=0;
}
extern "C" void fadeFluidInit(u32 width,u32 height,f32 spacing,f32 delta,f32 speed,f32 damping) {
    u32 count=(width+1)*(height+1);
    u32 bytes=count*sizeof(FluidVec);
    _fadeFluidWork.width=width;_fadeFluidWork.height=height;
    _fadeFluidWork.screenX=640.0f/(f32)width;
    _fadeFluidWork.screenY=480.0f/(f32)height;
    _fadeFluidWork.vertices[0]=(FluidVec *)_fadeFluidDoMalloc(bytes);
    _fadeFluidWork.vertices[1]=(FluidVec *)_fadeFluidDoMalloc(bytes);
    _fadeFluidSw=0;
    _fadeFluidWork.normal=(FluidVec *)_fadeFluidDoMalloc(bytes);
    _fadeFluidWork.tangent=(FluidVec *)_fadeFluidDoMalloc(bytes);
    _fadeFluidWork.uv=(FluidUV *)_fadeFluidDoMalloc(count*sizeof(FluidUV));
    f32 limit=(spacing/(2.0f*delta))*FluidSqrt(2.0f+damping);
    if (!(speed>0.0f) || !(speed<limit)) {
        OSReport("Warning: fadeFluid c parm. Limit Over!! -> 0.0f < %f < %f\n",speed,limit);
        speed=limit-0.000001f;
    }
    _fadeFluidWork.spacing=spacing;_fadeFluidWork.speed=speed;_fadeFluidWork.damping=damping;
    fadeFluidCalcParms(delta);
    for (u32 y=0;y<=height;++y) {
        for (u32 x=0;x<=width;++x) {
            u32 i=x+y*(width+1);
            FluidVec *vertex=&_fadeFluidWork.vertices[0][i];
            vertex->x=spacing*(f32)x;vertex->y=spacing*(f32)y;vertex->z=0.0f;
            _fadeFluidWork.vertices[1][i]=*vertex;
            FluidVec *normal=&_fadeFluidWork.normal[i];
            normal->x=0.0f;normal->y=0.0f;normal->z=2.0f*spacing;
            FluidVec *tangent=&_fadeFluidWork.tangent[i];
            tangent->x=2.0f*spacing;tangent->y=0.0f;tangent->z=0.0f;
            _fadeFluidWork.uv[i].u=(1.0f/(f32)_fadeFluidWork.width)*(f32)x;
            _fadeFluidWork.uv[i].v=(1.0f/(f32)_fadeFluidWork.height)*(f32)y;
        }
    }
}
static void _fadeFluidDoFree(void *data) {GSmemFree(data);}
static void *_fadeFluidDoMalloc(unsigned long size) {
    void *result;
    s32 previous=GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(),3);
    result=GSmemAllocAlign(size,32);
    GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(),previous);
    return result;
}
