#ifndef FIGHT_SEQ_HPP
#define FIGHT_SEQ_HPP
#include <dolphin/types.h>
struct FightOutPokemon;
// The command server is accessed by fixed SDA offsets in the original.
struct SeqServerWork { u8 flags[8]; };
struct SeqItemTypePower { u8 item; u8 type; };
struct SeqReplacementWork { FightOutPokemon *pokemon; u32 keepConditions; };
struct SeqWazaSave { u32 words[43]; };
typedef char SeqServerSize[(sizeof(SeqServerWork) == 8) ? 1 : -1];
typedef char SeqItemTypePowerSize[(sizeof(SeqItemTypePower) == 2) ? 1 : -1];
typedef char SeqReplacementSize[(sizeof(SeqReplacementWork) == 8) ? 1 : -1];
typedef char SeqReplacementKeepOffset[((u32)&((SeqReplacementWork*)0)->keepConditions == 4) ? 1 : -1];
typedef char SeqWazaSaveSize[(sizeof(SeqWazaSave) == 0xac) ? 1 : -1];
#endif
