#include <global.h>
extern u8 sex_data[];
extern "C" u8 sexGetPokemonSexRaitoKotei(u32 id) {
    return sex_data[(id << 3) & 0x7FFF8];
}
