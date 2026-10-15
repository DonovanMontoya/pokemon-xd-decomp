#include "pxdvs/GSAPI/GSgfxM/layer_private.h"

extern "C" {
LayerNode* GSgfxLayerFindByID(s32);
s32 GSgfxLayerFindByName_C(char*);
void SetPassRedirect__10GSgfxLayerF14GSgfxLayerPassbP10GSgfxLayer14GSgfxLayerPass16GSgfxLayerOffset(void*, s32, bool, void*, s32, s32);
void Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(LayerConfigData*);
void dbgMenuSetLayerID(s32);
}

extern "C" s32 _menu_extra_layer_id;

extern "C" char* g_layer_names[8] = {
    "background", "background distortion", "main", "main distortion",
    "secondary", "secondary distortion", "filter", "menu"
};

#define LAYER_ROW(id, name, type, flags, opaque, translucent, matrices) {id, (char*)name, type, (u8)((flags) >> 24), (u8)((flags) >> 16), (u8)((flags) >> 8), (u8)(flags), opaque, translucent, matrices}

static LayerConfigData _empty_layer_config[] = {
    LAYER_ROW(2, 0, 0, 1, 327680, 327680, 16),
    LAYER_ROW(-1, 0, 0, 0, 0, 0, 0),
};
static LayerConfigData _map_layer_config[] = {
    LAYER_ROW(0, 0, 0, 1, 393216, 196608, 16),
    LAYER_ROW(2, 0, 0, 1, 327680, 327680, 16),
    LAYER_ROW(4, 0, 0, 257, 65536, 131072, 16),
    LAYER_ROW(6, 0, 0, 1, 0, 8192, 1),
    LAYER_ROW(7, 0, 0, 1, 0, 98304, 8),
    LAYER_ROW(-1, 0, 0, 0, 0, 0, 0),
};
static LayerConfigData _fight_layer_config[] = {
    LAYER_ROW(0, 0, 0, 1, 262144, 262144, 16),
    LAYER_ROW(1, 0, 1, 0, 0, 131072, 16),
    LAYER_ROW(2, 0, 0, 1, 524288, 327680, 16),
    LAYER_ROW(3, 0, 1, 0, 0, 65536, 16),
    LAYER_ROW(4, 0, 0, 257, 131072, 542720, 16),
    LAYER_ROW(5, 0, 1, 0, 0, 81920, 16),
    LAYER_ROW(6, 0, 0, 1, 0, 16384, 1),
    LAYER_ROW(7, 0, 0, 1, 0, 131072, 16),
    LAYER_ROW(-1, 0, 0, 0, 0, 0, 0),
};
static LayerConfigData _menu_layer_config[] = {
    LAYER_ROW(0, 0, 0, 1, 262144, 262144, 32),
    LAYER_ROW(255, "menu extra", 0, 257, 131072, 262144, 16),
    LAYER_ROW(2, 0, 0, 1, 327680, 327680, 16),
    LAYER_ROW(4, 0, 0, 257, 65536, 262144, 16),
    LAYER_ROW(6, 0, 0, 1, 0, 8192, 1),
    LAYER_ROW(7, 0, 0, 1, 131072, 262144, 16),
    LAYER_ROW(-1, 0, 0, 0, 0, 0, 0),
};
static LayerConfigData _evolution_layer_config[] = {
    LAYER_ROW(0, 0, 0, 1, 262144, 262144, 32),
    LAYER_ROW(2, 0, 0, 1, 327680, 327680, 16),
    LAYER_ROW(4, 0, 0, 257, 262144, 262144, 16),
    LAYER_ROW(6, 0, 0, 1, 0, 8192, 1),
    LAYER_ROW(7, 0, 0, 1, 131072, 262144, 16),
    LAYER_ROW(-1, 0, 0, 0, 0, 0, 0),
};
static LayerConfigData _M6_layer_config[] = {
    LAYER_ROW(0, 0, 0, 1, 458752, 196608, 16),
    LAYER_ROW(2, 0, 0, 1, 327680, 327680, 16),
    LAYER_ROW(4, 0, 0, 257, 65536, 131072, 16),
    LAYER_ROW(6, 0, 0, 1, 0, 8192, 1),
    LAYER_ROW(7, 0, 0, 1, 0, 98304, 8),
    LAYER_ROW(-1, 0, 0, 0, 0, 0, 0),
};
static LayerConfigData _M6_out_bf_layer_config[] = {
    LAYER_ROW(0, 0, 0, 1, 327680, 262144, 16),
    LAYER_ROW(1, 0, 1, 0, 0, 131072, 16),
    LAYER_ROW(2, 0, 0, 1, 524288, 327680, 16),
    LAYER_ROW(3, 0, 1, 0, 0, 65536, 16),
    LAYER_ROW(4, 0, 0, 257, 131072, 542720, 16),
    LAYER_ROW(5, 0, 1, 0, 0, 81920, 16),
    LAYER_ROW(6, 0, 0, 1, 0, 16384, 1),
    LAYER_ROW(7, 0, 0, 1, 0, 131072, 16),
    LAYER_ROW(-1, 0, 0, 0, 0, 0, 0),
};
struct FloorConfig { LayerConfigData* config; u32 id; };
static const FloorConfig _floor_layer_config_list[] = {
    {_M6_layer_config, 0x99}, {_M6_out_bf_layer_config, 0x21E}, {_evolution_layer_config, 0x386}
};
static LayerConfigData* g_empty_layer_config = _empty_layer_config;
static LayerConfigData* g_map_layer_config = _map_layer_config;
static LayerConfigData* g_fight_layer_config = _fight_layer_config;
static LayerConfigData* g_menu_layer_config = _menu_layer_config;
static const FloorConfig* g_floor_layer_config_list = _floor_layer_config_list;
static u32 g_floor_layer_config_count = 3;

struct FloorLayerConfigInitializer {
    FloorLayerConfigInitializer() {
        _empty_layer_config[0].name = g_layer_names[2];
        _map_layer_config[0].name = g_layer_names[0];
        _map_layer_config[1].name = g_layer_names[2];
        _map_layer_config[2].name = g_layer_names[4];
        _map_layer_config[3].name = g_layer_names[6];
        _map_layer_config[4].name = g_layer_names[7];
        _fight_layer_config[0].name = g_layer_names[0];
        _fight_layer_config[1].name = g_layer_names[1];
        _fight_layer_config[2].name = g_layer_names[2];
        _fight_layer_config[3].name = g_layer_names[3];
        _fight_layer_config[4].name = g_layer_names[4];
        _fight_layer_config[5].name = g_layer_names[5];
        _fight_layer_config[6].name = g_layer_names[6];
        _fight_layer_config[7].name = g_layer_names[7];
        _menu_layer_config[0].name = g_layer_names[0];
        _menu_layer_config[2].name = g_layer_names[2];
        _menu_layer_config[3].name = g_layer_names[4];
        _menu_layer_config[4].name = g_layer_names[6];
        _menu_layer_config[5].name = g_layer_names[7];
        _evolution_layer_config[0].name = g_layer_names[0];
        _evolution_layer_config[1].name = g_layer_names[2];
        _evolution_layer_config[2].name = g_layer_names[4];
        _evolution_layer_config[3].name = g_layer_names[6];
        _evolution_layer_config[4].name = g_layer_names[7];
        _M6_layer_config[0].name = g_layer_names[0];
        _M6_layer_config[1].name = g_layer_names[2];
        _M6_layer_config[2].name = g_layer_names[4];
        _M6_layer_config[3].name = g_layer_names[6];
        _M6_layer_config[4].name = g_layer_names[7];
        _M6_out_bf_layer_config[0].name = g_layer_names[0];
        _M6_out_bf_layer_config[1].name = g_layer_names[1];
        _M6_out_bf_layer_config[2].name = g_layer_names[2];
        _M6_out_bf_layer_config[3].name = g_layer_names[3];
        _M6_out_bf_layer_config[4].name = g_layer_names[4];
        _M6_out_bf_layer_config[5].name = g_layer_names[5];
        _M6_out_bf_layer_config[6].name = g_layer_names[6];
        _M6_out_bf_layer_config[7].name = g_layer_names[7];
    }
};
static FloorLayerConfigInitializer g_floorLayerConfigInitializer;
extern "C" void floorLayerConfigLoad(void) {}
extern "C" s32 floorGetMenuLayerID(void) { return _menu_extra_layer_id; }

extern "C" void floorLayerConfig(u32 floorId, u8 rawType) {
    const FloorConfig* list = g_floor_layer_config_list;
    const FloorConfig* current = list;
    u32 index = 0;
    for (; index < g_floor_layer_config_count; ++index) {
        if (floorId == current->id) {
            Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(list[index].config);
            dbgMenuSetLayerID(GSgfxLayerFindByName_C((char*)"debug menu"));
            return;
        }
        ++current;
    }
    if ((s32)rawType != 4) {
        if ((s32)rawType < 4) {
            switch ((s32)rawType) {
            case 1: {
                Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(g_map_layer_config);
                void* first = GSgfxLayerFindByID(0);
                SetPassRedirect__10GSgfxLayerF14GSgfxLayerPassbP10GSgfxLayer14GSgfxLayerPass16GSgfxLayerOffset(
                    first, 1, true, GSgfxLayerFindByID(2), 0, 2);
                break;
            }
            }
        } else if ((s32)rawType != 7) {
            if ((s32)rawType < 7) {
                Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(g_menu_layer_config);
                _menu_extra_layer_id = GSgfxLayerFindByName_C((char*)"menu extra");
            } else {
                Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(g_empty_layer_config);
            }
        } else {
            Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(g_menu_layer_config);
            _menu_extra_layer_id = GSgfxLayerFindByName_C((char*)"menu");
        }
    } else {
        Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(g_fight_layer_config);
    }
    dbgMenuSetLayerID(GSgfxLayerFindByName_C((char*)"debug menu"));
}
