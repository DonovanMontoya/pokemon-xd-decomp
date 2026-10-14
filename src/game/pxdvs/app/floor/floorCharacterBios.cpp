#include <game/pxdvs/app/floor/floorBiosPrivate.hpp>
#include <libc/string.h>
extern "C" {
inline void GSvecSet(GSvec *vector, f32 x, f32 y, f32 z) { vector->x=x; vector->y=y; vector->z=z; }
void *peopleInfoBiosGetPtrFromIndex(u16);
floorCharacter_dd_ *floorCharacterBiosGetPtr(u32, u32);
static floorCharacter_dd_ _globalCharacter[3];
void floorCharacterBiosSetVisibility(floorCharacter_dd_ *character, u8 visible) { if (character) { u32 value = visible; character->visibility = value; } }
void floorCharacterBiosSetPos(floorCharacter_dd_ *character, GSvec *position) {
    if (character && position) { character->x=position->x; character->y=position->y; character->z=position->z; }
}
u32 floorCharacterBiosGetTalkSctID(floorCharacter_dd_ *character) { if (character) return character->talkScriptID; return 0; }
u32 floorCharacterBiosGetMoveSctID(floorCharacter_dd_ *character) { if (character) return character->moveScriptID; return 0; }
u16 floorCharacterBiosGetNameID(floorCharacter_dd_ *character) { if (character) return character->nameID; return 0; }
s32 floorCharacterBiosGetTalkWallThrough(floorCharacter_dd_ *character) { if (character) return character->talkWallThrough != 0; return 0; }
s32 floorCharacterBiosGetTalkEndType(floorCharacter_dd_ *character) { if (character) return character->talkEndType; return 0; }
s32 floorCharacterBiosGetTalkStartType(floorCharacter_dd_ *character) { if (character) return character->talkStartType; return 0; }
s32 floorCharacterBiosGetMoveType(floorCharacter_dd_ *character) { if (character) return character->moveType; return 0; }
s32 floorCharacterBiosGetRot(floorCharacter_dd_ *character, GSvec *rotation) {
    if (!character) return 0;
    if (!rotation) return 0;
    GSvecSet(rotation, 0.0f, 0.017453292f * character->rotation, 0.0f);
    return 1;
}
s32 floorCharacterBiosGetPos(floorCharacter_dd_ *character, GSvec *position) {
    if (!character) return 0;
    if (!position) return 0;
    GSvecSet(position, character->x, character->y, character->z);
    return 1;
}
s32 floorCharacterBiosGetIsHit(floorCharacter_dd_ *character) { if (character) return character->isHit != 0; return 0; }
s32 floorCharacterBiosGetLoadInit(floorCharacter_dd_ *character) { if (character) return character->loadInit != 0; return 0; }
s32 floorCharacterBiosGetVisibility(floorCharacter_dd_ *character) { if (character) return character->visibility != 0; return 0; }
void *floorCharacterBiosGetPeopleInfoPtr(floorCharacter_dd_ *character) { if (character) return peopleInfoBiosGetPtrFromIndex(character->peopleIndex); return 0; }
floorCharacter_dd_ *floorCharacterBiosFindByResID(u32 groupID, u32 resourceID) {
    if (!groupID) {
        if (resourceID == 0x65) return &_globalCharacter[0];
        if (resourceID == 0x69) return &_globalCharacter[1];
        if (resourceID == 0x68) return &_globalCharacter[2];
        return 0;
    } else {
        FloorData *floor = floorDataBiosGetPtr(GSfloorGetCurrent());
        if (groupID != floorDataBiosGetGroupID(floor)) return 0;
        return floorDataBiosGetCharInfo(floor, resourceID);
    }
}
floorCharacter_dd_ *floorCharacterBiosGetCurrentPtr(u32 index) { return floorCharacterBiosGetPtr(GSfloorGetCurrent(), index); }
floorCharacter_dd_ *floorCharacterBiosGetPtr(u32 floorID, u32 index) { return floorDataBiosGetCharInfo(floorDataBiosGetPtr(floorID), index); }
void floorCharacterBiosInitGlobalCharacter() {
    memset(_globalCharacter, 0, sizeof(_globalCharacter));
    floorCharacter_dd_ character;
    memset(&character, 0, sizeof(character));
    character.visibility = 1;
    character.isHit = 1;
    character.flag4 = 1;
    character.talkWallThrough = 1;
    character.peopleIndex = 0;
    character.moveType = 0;
    character.talkStartType = 2;
    character.flag2 = 1;
    character.nameID = 0;
    character.talkEndType = 0;
    character.parameter2 = 0;
    character.parameter3 = 0;
    character.rotation = 0;
    character.resourceID = 0;
    character.moveScriptID = 0;
    character.talkScriptID = 0;
    character.x = 0.0f;
    character.y = 0.0f;
    character.z = 0.0f;
    character.nameID = 1;
    character.peopleIndex = 2;
    _globalCharacter[0] = character;
    character.nameID = 3;
    character.peopleIndex = 90;
    _globalCharacter[1] = character;
    character.nameID = 24;
    character.peopleIndex = 45;
    _globalCharacter[2] = character;
}
}
