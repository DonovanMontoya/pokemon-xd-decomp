#include <game/pxdvs/app/effects/blurPrivate.hpp>
void operator delete(void*);
u8 blurEffectRenderFBCallback(GStexture*,unsigned long,void*);
extern "C" {void GScameraLoadActiveCameraMatrix(s32);void GSgfxBeginBackFBCapture(GStexture*,u8(*)(GStexture*,unsigned long,void*),void*);void GSgfxEndBackFBCapture(GStexture*);void GSgfxTokenWaitForClear(u16);GSgfxVF*GSgfxVFGetPredef(u32);void GSmodelAdvanceAnimation(GSmodel*,f32);void GSmodelDrawModel(GSmodel*,GSgfxLayer*,GSgfxLayerPass);void GSmodelForceAnimTransformUpdate(GSmodel*);f32 GSmodelGetAnimFrame(GSmodel*);f32 GSmodelGetAnimRate(GSmodel*);_GSparticleBank*GSmodelGetLinkedGSparticleBank(GSmodel*);void GSmodelInitMaterialAlpha(GSmodel*);u8 GSmodelIsAnimating(GSmodel*);void GSmodelResetMaterialAlpha(GSmodel*);void GSmodelResetPEdescr(GSmodel*);void GSmodelResetRenderFlags(GSmodel*);void GSmodelSetAnimFrame(GSmodel*,f32);void GSmodelSetMaterialAlpha(GSmodel*,f32);void GSmodelSetPEdescr(GSmodel*,void*);void GSmodelSetRenderFlags(GSmodel*,u32);void GSmtx44Ortho(f32*,f32,f32,f32,f32,f32,f32);void GSparticleActivateBank(_GSparticleBank*);void GSparticleDisactivateBank(_GSparticleBank*);void GSparticleSetBankVisibility(_GSparticleBank*,u8);GStexture*GStextureCreate(u16,u16,s32,s32,s32);void GStextureFree(GStexture*);void*memcpy(void*,const void*,u32);extern f32 mtxIdent[12];}
blurEffect::~blurEffect(){Stop();if(framebuffer&&texture){if(token){GSgfxTokenWaitForClear(token);token=0;}GStextureFree(texture);}}
void blurEffect::_stop(){if(framebuffer){GSgfxEndBackFBCapture(texture);ready=0;}}
void blurEffect::_render(GSgfxLayer*layer,GSgfxLayerPass pass){static u8 pedesc[]={0x13,0,0,0xFF,1,4,5,15,1,7,0,7};if(framebuffer){if(layer->unk28==6&&pass==1)RenderFB(layer);}else if(model&&layer->unk28==2&&pass==0&&GSmodelIsAnimating(model)){s32 count=(s32)(20.0f*amount+0.5f);if(count){f32 frame=GSmodelGetAnimFrame(model);f32 rate=GSmodelGetAnimRate(model);f32 current=-(rate*(f32)count-frame);if(current<0){current=0;count=(s32)(frame/rate);}if(count&&!(current>=frame)){GSmodelSetPEdescr(model,pedesc);GSmodelSetRenderFlags(model,32);GSmodelInitMaterialAlpha(model);GScameraLoadActiveCameraMatrix(-1);_GSparticleBank*bank=GSmodelGetLinkedGSparticleBank(model);if(bank){GSparticleDisactivateBank(bank);GSparticleSetBankVisibility(bank,0);}GSmodelSetAnimFrame(model,current);f32 reciprocal=1.0f/(f32)count;s32 index=1;while(current+0.5f*rate<frame){s32 value=index;current+=rate;index++;f32 alpha=(f32)value*reciprocal;GSmodelSetMaterialAlpha(model,0.5f*alpha*alpha);GSmodelForceAnimTransformUpdate(model);GSmodelDrawModel(model,layer,pass);GSmodelAdvanceAnimation(model,1);}GSmodelResetMaterialAlpha(model);GSmodelResetRenderFlags(model);GSmodelResetPEdescr(model);GSmodelSetAnimFrame(model,frame);GSmodelForceAnimTransformUpdate(model);GSmodelDrawModel(model,layer,pass);if(bank){GSparticleActivateBank(bank);GSparticleSetBankVisibility(bank,1);}}}}}
bool blurEffect::_start(){if(framebuffer){if(!texture)return false;ready=0;GSgfxBeginBackFBCapture(texture,blurEffectRenderFBCallback,this);}return true;}
blurEffect::blurEffect(bool fb){model=0;texture=0;token=0;ready=0;framebuffer=fb;amount=0;if(fb)texture=GStextureCreate(0,0,0x44,0,0);}
void blurEffect::RenderFB(GSgfxLayer*arg1) {
    f32 matrix[16];f32 alphaValue=255.0f*amount;u8 alpha;if(alphaValue<0.0f)alpha=0;else if(alphaValue>255.0f)alpha=255;else alpha=(u8)alphaValue;
    BlurMatrix*temp_r3;
    s32 temp_r5;
    BlurMatrixChain*temp_r28;
    GStexture*temp_r3_2;

    if ((u8) ready != 0) {
        GSmtx44Ortho(matrix, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
        arg1->unkD54 = 1;
        arg1->unkD58 = matrix[0];
        arg1->unkD5C = matrix[3];
        arg1->unkD60 = matrix[5];
        arg1->unkD64 = matrix[7];
        arg1->unkD68 = matrix[10];
        arg1->unkD6C = matrix[11];
        temp_r28 = arg1->unk19A0;
        memcpy(temp_r28->matrix->values, &mtxIdent, 0x30);
        temp_r3 = temp_r28->matrix;
        temp_r3->flags |= 1;
        arg1->unk1684 = 0.0f;
        arg1->unk1688 = 30000.0f;
        if ((u8) arg1->unk16A7 != 0) {
            if ((u8) arg1->unk16A6 != 0) {
                arg1->unk170C = (s32) (arg1->unk170C | 0x100);
                arg1->unk17C4 = (s32) (arg1->unk17C4 | 0x100);
            }
            arg1->unk170C = (s32) (arg1->unk170C | 0x40);
            arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
            arg1->unk17C4 = (s32) (arg1->unk17C4 | 0x40);
            arg1->unk1760 = (s32) (arg1->unk1760 | 0x40);
        }
        arg1->unk16AC = (s32) (arg1->unk16AC | 0x20);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 1);
        arg1->unk1764 = (s32) (arg1->unk1764 | 0x20);
        arg1->unk1760 = (s32) (arg1->unk1760 | 1);
        if ((s32) arg1->unk1994 != 1) {
            arg1->unk1994 = 1;
            arg1->unk1990 = &arg1->records[arg1->unk1994];
        }
        arg1->unk1644 = 1;
        arg1->unk1648 = 4;
        arg1->unk164C = 5;
        arg1->unk1650 = 5;
        arg1->unk170C = (s32) (arg1->unk170C | 1);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
        arg1->unk17C4 = (s32) (arg1->unk17C4 | 1);
        temp_r5 = arg1->unk1760 | 0x40;
        arg1->unk1760 = temp_r5;
        arg1->unk165C = 0;
        arg1->unk1660 = 7;
        arg1->unk170C = (s32) (arg1->unk170C | 8);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
        arg1->unk17C4 = (s32) (arg1->unk17C4 | 8);
        arg1->unk1760 = (s32) (arg1->unk1760 | 0x40);
        arg1->unk1656 = 1;
        arg1->unk1657 = 1;
        arg1->unk1658 = 0;
        arg1->unk170C = (s32) (arg1->unk170C | 4);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 0x40);
        arg1->unk17C4 = (s32) (arg1->unk17C4 | 4);
        arg1->unk1760 = (s32) (arg1->unk1760 | 0x40);
        arg1->unkD8C = 0;
        arg1->unk16B8 = (s32) (arg1->unk16B8 | 2);
        arg1->unk16A8 = (s32) (arg1->unk16A8 | 2);
        arg1->unk1770 = (s32) (arg1->unk1770 | 2);
        arg1->unk1760 = (s32) (arg1->unk1760 | 2);
        arg1->setRenderStateAndSelect(GSgfxVFGetPredef(5));
        temp_r3_2 = texture;
        if ((arg1->unk1740 != temp_r3_2) || (arg1->unk17F8 != temp_r3_2) || ((u8) temp_r3_2->unk7 != 0)) {
            arg1->unk1740 = temp_r3_2;
            arg1->unk173C = (s32) (arg1->unk173C | 1);
            arg1->unk17F8 = temp_r3_2;
            arg1->unk17F4 = (s32) (arg1->unk17F4 | 1);
        }
        arg1->unk1998 = 0x98;
        arg1->beginSurface(4);
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 640.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 480.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = 640.0f;
        *(volatile f32 *)0xCC008000 = 480.0f;
        *(volatile f32 *)0xCC008000 = 0.0f;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = 0xFF;
        *(volatile u8 *)0xCC008000 = alpha;
        *(volatile f32 *)0xCC008000 = 1.0f;
        *(volatile f32 *)0xCC008000 = 1.0f;
        arg1->endSurface();
        token = arg1->tokenMark();
    }
}

u8 blurEffectRenderFBCallback(GStexture*texture,unsigned long,void*data){blurEffect*effect=(blurEffect*)data;effect->ready=texture==effect->texture;return effect->ready;}
