#ifndef MENU_WORLD_MAP_MODEL_PRIVATE_HPP
#define MENU_WORLD_MAP_MODEL_PRIVATE_HPP
#include <dolphin/types.h>
enum GSgfxLayerID{LayerDummy};enum GSattachMode{AttachDummy};enum GSgfxLayerOffset{OffsetDummy};
struct GStexture;struct _GSparticleGen;struct GSmodel;struct GSlight;struct GSpart;
struct WorldMapArchive {void **models;void *animation;void **lights;};
class WorldMapModel {public:GStexture *offscreen;WorldMapModel(){offscreen=0;}~WorldMapModel(){if(offscreen)releaseOffscreenData();}WorldMapArchive *SetModel(unsigned long,unsigned long,bool);void UnloadModel(unsigned long,unsigned long);void ObjectVisibility(unsigned long,bool);void Visibility(unsigned long,bool);s32 ModelDetach(unsigned long);s32 ModelAttach(unsigned long,unsigned long,long,GSattachMode);_GSparticleGen *SetModelPartPaticle(unsigned long,unsigned long,long,GSattachMode,bool,bool,bool);void DetachModelPartPaticle(_GSparticleGen*,bool);WorldMapArchive *makeArchiveHeader(unsigned long);f32 GetAnimeFrameCount(unsigned long,unsigned long);f32 GetAnimeFrame(unsigned long);void StopMotion(unsigned long);s32 CheckMotion(unsigned long);void SetMotion(unsigned long,short,f32,bool);void SetLayerID(unsigned long,long,GSgfxLayerID*);GSmodel *GetModelPtr(unsigned long);void releaseOffscreenData();void initializeOffscreenData();void renderOffscreenData(f32);};
#endif
