#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonBios.hpp>
#include <game/pxdvs/app/pokemon/pokemonDB.hpp>
#include <game/relglobal.h>

extern "C" bool pokemonCheckValid(const Pokemon*);
extern "C" u8 pokemonGetSex(const Pokemon*);
extern "C" const char16* pokemonDB_GetName(u16);

extern u32* legendPokemonData_number;
extern u16* legendPokemonData;

extern "C" void GScharLenCpy(u16*,const u16*,u32);

void Pokemon::setReversMode(bool mode) {
    DarkPokemon* p = getDarkPokemon();
    if (p) p->setReversMode(mode);
}

bool Pokemon::isReversMode() const {
    const DarkPokemon* p = getDarkPokemon();
    if (p == nullptr) {
        return false;
    } else {
        return p->isReversMode();
    }
}

bool Pokemon::isLegend() const {
    if (getPokemonDataId() == 0) {
        return false;
    }

    u16 legendId;
    for (u32 i = 0; i < *legendPokemonData_number; i++) {
        legendId = legendPokemonData[i];
        if (legendId == 0) {
            return false;
        }
        if (legendId == getPokemonDataId()) {
            return true;
        }
    }
    return false;
}

bool Pokemon::isHatena() const {
    u16 pokemonId = getPokemonDataId();
    if (pokemonId == 0) {
        return true;
    }
    if (pokemonDB_GetName(pokemonId) == nullptr) {
        return true;
    }
    return static_cast<u8>(pokemonId >= *pokemon_data_number);
}

bool Pokemon::checkValid() const {
    return pokemonCheckValid(this);
}

void Pokemon::setPoolFriendLevel(u16 value) {
    DarkPokemon* p = getDarkPokemon();
    if (p) {
        u16 limit = 255;
        if (value<limit) limit = value;
        p->setPoolFriendLevel(limit);
    }
}

void Pokemon::setPoolExp(u32 value) {
    DarkPokemon* p = getDarkPokemon();
    if (p) p->setPoolExp(value);
}

void Pokemon::setDarkPoint(f32 value) {
    DarkPokemon* p = getDarkPokemon();
    if (p) {
        f32 limit = 6553500.0f;
        if (value<limit) limit = value;
        p->setDarkPoint(limit);
    }
}

void Pokemon::setDarkPointDirect(s32 value) {
    DarkPokemon* p = getDarkPokemon();
    if (p) {
        s32 limit = 6553500;
        if (value<limit) limit = value;
        p->setDarkPointDirect(limit);
    }
}

u16 Pokemon::getPoolFriendLevel() const {
    const DarkPokemon* p = getDarkPokemon();
    if (p == nullptr) {
        return 0;
    } else {
        return p->getPoolFriendLevel();
    }
}

u32 Pokemon::getPoolExp() const {
    const DarkPokemon* p = getDarkPokemon();
    if (p == nullptr) {
        return 0;
    } else {
        return p->getPoolExp();
    }
}

f32 Pokemon::getDarkPoint() const {
    const DarkPokemon* p = getDarkPokemon();
    if (p == nullptr) {
        return -1.0f;
    } else {
        return p->getDarkPoint();
    }
}

s32 Pokemon::getDarkPointDirect() const {
    const DarkPokemon* p = getDarkPokemon();
    if (p == nullptr) {
        return -1;
    } else {
        return p->getDarkPointDirect();
    }
}

const DarkPokemon* Pokemon::getDarkPokemon() const {
    return darkPokemonGetDarkPokemon(getDarkpokemonDataID());
}

DarkPokemon* Pokemon::getDarkPokemon() {
    return darkPokemonGetDarkPokemon(getDarkpokemonDataID());
}

bool Pokemon::isDarkPokemon() const {
    u16 id = getDarkpokemonDataID();
    if (id == 0) {
        return false;
    } else {
        return !darkPokemonBiosGetReliveFlag(id);
    }
}

u8 Pokemon::getSex() const {
    return pokemonGetSex(this);
}

bool Pokemon::isTokuseiFlag() const {
    PokemonData* data = static_cast<PokemonData*>(getPokemonDataPtr());
    if (pokemonDataBiosGetTokuseiDataId(data, 1) == 0) {
        return false;
    }
    return static_cast<u8>(flags.bits.tokusei != 0);
}

bool Pokemon::isRareParam(u32 trainerRnd, u32 pokemonRnd) {
    return ((trainerRnd >> 16) ^ (trainerRnd & 0xFFFF) ^
            (pokemonRnd >> 16) ^ (pokemonRnd & 0xFFFF)) < 8;
}

u32 DarkPokemon::getWalkCount() const {
    return walkCount;
}

void DarkPokemon::setWalkCount(u32 value) {
    walkCount = value;
}

void DarkPokemon::setReversPattern(u8 value) {
    reversPattern = value;
}

u8 DarkPokemon::getReversPattern() const {
    return reversPattern;
}

s32 DarkPokemon::getInitDarkPointDirect() const {
    return darkPokemonBiosGetDarkPoint(darkPokemonID);
}

void DarkPokemon::setCatchBallID(u16 value) {
    capture.catchBall = value;
}

u16 DarkPokemon::getCatchBallID() const {
    return capture.catchBall;
}

void DarkPokemon::setDarkPokemonID(u16 value) {
    darkPokemonID = value;
}

u16 DarkPokemon::getDarkPokemonID() const {
    return darkPokemonID;
}

void DarkPokemon::setPokemonID(u16 value) {
    pokemonID = value;
}

u16 DarkPokemon::getPokemonID() const {
    return pokemonID;
}

bool DarkPokemon::isSnach() const {
    return getStatus() >= 3;
}

bool DarkPokemon::isRelive() const {
    return getStatus() == 4;
}

void DarkPokemon::setTrainerName(const u16* name) {
    for (int i = 0;i<10;i++) trainerName[i] = name[i];
    trainerName[10] = 0;
}

const u16* DarkPokemon::getTrainerName() const {
    return trainerName;
}

void DarkPokemon::setStatusRnd(u8 index, u8 value) {
    if (index<6) statusRnd[index] = value;
}

u8 DarkPokemon::getStatusRnd(u8 index) const {
    if (index<6) return statusRnd[index];
    return 0;
}

void DarkPokemon::setInformation(bool value) {
    capture.information = value;
}

bool DarkPokemon::isInformation() const {
    return capture.information!=0;
}

void DarkPokemon::setUpdate(bool value) {
    reinterpret_cast<ModeFlags*>(&unk0x0[1])->update = value;
}

bool DarkPokemon::isUpdate() const {
    return reinterpret_cast<const ModeFlags*>(&unk0x0[1])->update!=0;
}

void DarkPokemon::setEscapeTime(u32 value) {
    if (statusFlags.status<3) escapeOrSnatchTime = value;
}

u32 DarkPokemon::getEscapeTime() const {
    if (statusFlags.status<3) return escapeOrSnatchTime;
    return 0;
}

void DarkPokemon::setSnatchTime(u32 value) {
    if (statusFlags.status>=3) escapeOrSnatchTime = value;
}

void DarkPokemon::setRnd(u32 value) {
    rnd = value;
}

u32 DarkPokemon::getRnd() const {
    return rnd;
}

void DarkPokemon::setCatchFloorId(u16 value) {
    catchFloorId = value;
}

u16 DarkPokemon::getCatchFloorId() const {
    return catchFloorId;
}

void DarkPokemon::setOrgTrainer(u16 value) {
    orgTrainer = value;
}

u16 DarkPokemon::getOrgTrainer() const {
    return orgTrainer;
}

void DarkPokemon::setSnatchIndex(u8 value) {
    snatchIndex = value;
}

u8 DarkPokemon::getSnatchIndex() const {
    return snatchIndex;
}

void DarkPokemon::getPlace(darkPokemonWhere& place, u8& index) const {
    place = static_cast<darkPokemonWhere>(placeFlags.place);
    index = placeIndex;
}

void DarkPokemon::setWazaNew(u8 index, bool value) {
    if (index>=3) return;
    ModeFlags* flags = reinterpret_cast<ModeFlags*>(&unk0x0[1]);
    if (value) flags->wazaNew |= 1<<index;
    else flags->wazaNew &= ~(1<<index);
}

bool DarkPokemon::isWazaNew(u8 index) const {
    if (index>=3) return false;
    return (reinterpret_cast<const ModeFlags*>(&unk0x0[1])->wazaNew & (1<<index)) != 0;
}

void DarkPokemon::setPoolFriendLevel(u16 value) {
    poolFriendLevel = value;
}

u16 DarkPokemon::getPoolFriendLevel() const {
    return poolFriendLevel;
}

void DarkPokemon::setPoolExp(u32 value) {
    experience.poolExp = value;
}

u32 DarkPokemon::getPoolExp() const {
    return experience.poolExp;
}

void DarkPokemon::setDarkPointDirect(s32 value) {
    darkPoint = value;
}

s32 DarkPokemon::getDarkPointDirect() const {
    return darkPoint;
}

void DarkPokemon::setReversMode(bool value) {
    reinterpret_cast<ModeFlags*>(&unk0x0[1])->revers = value;
}

bool DarkPokemon::isReversMode() const {
    return reinterpret_cast<const ModeFlags*>(&unk0x0[1])->revers!=0;
}

void DarkPokemon::setSnatchFromWho(darkPokemonSnatchWho value) {
    snatchFlags.who = value;
}

darkPokemonSnatchWho DarkPokemon::getSnatchFromWho() const {
    return static_cast<darkPokemonSnatchWho>(snatchFlags.who);
}

void DarkPokemon::setSnatchInfoLevel(u8 value) {
    statusFlags.infoLevel = value;
}

darkPokemonStatus DarkPokemon::getStatus() const {
    return static_cast<darkPokemonStatus>(statusFlags.status);
}

void DarkPokemon::addStatus(darkPokemonStatus value) {
    if (statusFlags.status < static_cast<u32>(value)) statusFlags.status = value;
}

void DarkPokemon::setStatus(darkPokemonStatus value) {
    statusFlags.status = value;
}

void DarkPokemon::init() {
    memset(this, 0, sizeof(DarkPokemon));
}

void Pokemon::setConditionTurnNow(u8 data) {
    conditionTurnNow = data;
}

u8 Pokemon::getConditionTurnNow() const {
    return conditionTurnNow;
}

void Pokemon::setConditionTurn(u8 data) {
    conditionTurn = data;
}

u8 Pokemon::getConditionTurn() const {
    return conditionTurn;
}

void Pokemon::setConditionCount(u8 data) {
    conditionCount = data;
}

u8 Pokemon::getConditionCount() const {
    return conditionCount;
}

void Pokemon::setCondition(u8 data) {
    condition = data;
}

u8 Pokemon::getCondition() const {
    return condition;
}

u16 Pokemon::getDarkpokemonDataID() const {
    return darkPokemonDataID;
}

void Pokemon::setPara1Amari(u16 data) {
    para1Amari = data;
}

void Pokemon::setAmari(u16 data) {
    amari = data;
}

void Pokemon::setPcboxMark(u8 data) {
    pcboxMark = data;
}

void Pokemon::setFriendLevel(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    friendLevel = finalData;
}

void Pokemon::setNimblenessRnd(u16 data) {
    statusRnd.setNimbleness(data);
}

void Pokemon::setSpeDefRnd(u16 data) {
    statusRnd.setSpeDef(data);
}

void Pokemon::setSpeAtkRnd(u16 data) {
    statusRnd.setSpeAtk(data);
}

void Pokemon::setPhyDefRnd(u16 data) {
    statusRnd.setPhyDef(data);
}

void Pokemon::setPhyAtkRnd(u16 data) {
    statusRnd.setPhyAtk(data);
}

void Pokemon::setMaxHpRnd(u16 data) {
    statusRnd.setMaxHp(data);
}

void Pokemon::setNimblenessEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    nimblenessEffort = finalData;
}

void Pokemon::setSpeDefEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    speDefEffort = finalData;
}

void Pokemon::setSpeAtkEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    speAtkEffort = finalData;
}

void Pokemon::setPhyDefEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    phyDefEffort = finalData;
}

void Pokemon::setPhyAtkEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    phyAtkEffort = finalData;
}

void Pokemon::setMaxHpEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    maxHpEffort = finalData;
}

void Pokemon::setNimbleness(u16 data) {
    nimbleness = data;
}

void Pokemon::setSpeDef(u16 data) {
    speDef = data;
}

void Pokemon::setSpeAtk(u16 data) {
    speAtk = data;
}

void Pokemon::setPhyDef(u16 data) {
    phyDef = data;
}

void Pokemon::setPhyAtk(u16 data) {
    phyAtk = data;
}

void Pokemon::setMaxHp(u16 data) {
    maxHp = data;
}

void Pokemon::setHp(u16 data) {
    hp = data;
    u16 hpCap = getMaxHp();
    if (hpCap < hp) {
        hp = hpCap;
    }
}

void Pokemon::setItemDataId(u16 data) {
    itemDataID = data;
}

void Pokemon::setExp(u32 data) {
    exp = data;
}

void Pokemon::setNicknameOrgPtr(u16* name) {
    if (name) GScharLenCpy(reinterpret_cast<u16*>(nicknameOrg), name, 11);
}

void Pokemon::setNicknamePtr(u16* name) {
    if (name) {
        GScharLenCpy(reinterpret_cast<u16*>(nickname), name, 11);
        setNicknameOrgPtr(name);
    }
}

void Pokemon::setCatchTrainerNamePtr(u16* name) {
    if (name) GScharLenCpy(reinterpret_cast<u16*>(catchTrainerName), name, 11);
}

void Pokemon::setCatchTrainerRnd(u32 data) {
    catchTrainerRnd = data;
}

void Pokemon::setCatchTrainerSex(u8 data) {
    catchTrainerSex = data;
}

void Pokemon::setCatchBallId(u8 data) {
    catchBallId = data;
}

void Pokemon::setCatchLevel(u8 data) {
    catchLevel = data;
}

void Pokemon::setCatchFloorId(u16 data) {
    catchFloorId = data;
}

void Pokemon::setRnd(u32 data) {
    rnd = data;
}

u16 Pokemon::getPara1Amari() const {
    return para1Amari;
}

u16 Pokemon::getAmari() const {
    return amari;
}

bool Pokemon::isFuseiFlag() const {
    return flags.bits.fusei;
}

u8 Pokemon::getPcboxMark() const {
    return pcboxMark;
}

u16 Pokemon::getFriendLevel() const {
    return friendLevel;
}

u16 Pokemon::getItemDataId() const {
    return itemDataID;
}

u8 Pokemon::getLevel() const {
    return level;
}

u16 Pokemon::getHp() const {
    return hp;
}

char* Pokemon::getNicknamePtr() {
    return &nickname[0];
}

u8 Pokemon::getNimblenessRnd() const {
    return statusRnd.getNimbleness();
}

u8 Pokemon::getSpeDefRnd() const {
    return statusRnd.getSpeDef();
}

u8 Pokemon::getSpeAtkRnd() const {
    return statusRnd.getSpeAtk();
}

u8 Pokemon::getPhyDefRnd() const {
    return statusRnd.getPhyDef();
}

u8 Pokemon::getPhyAtkRnd() const {
    return statusRnd.getPhyAtk();
}

u8 Pokemon::getMaxHpRnd() const {
    return statusRnd.getMaxHp();
}

u16 Pokemon::getNimblenessEffort() const {
    return nimblenessEffort;
}

u16 Pokemon::getSpeDefEffort() const {
    return speDefEffort;
}

u16 Pokemon::getSpeAtkEffort() const {
    return speAtkEffort;
}

u16 Pokemon::getPhyDefEffort() const {
    return phyDefEffort;
}

u16 Pokemon::getPhyAtkEffort() const {
    return phyAtkEffort;
}

u16 Pokemon::getMaxHpEffort() const {
    return maxHpEffort;
}

u16 Pokemon::getNimbleness() const {
    return nimbleness;
}

u16 Pokemon::getSpeDef() const {
    return speDef;
}

u16 Pokemon::getSpeAtk() const {
    return speAtk;
}

u16 Pokemon::getPhyDef() const {
    return phyDef;
}

u16 Pokemon::getPhyAtk() const {
    return phyAtk;
}

u16 Pokemon::getMaxHp() const {
    return maxHp;
}

Attest* Pokemon::getAttest() {
    return &attest;
}

u32 Pokemon::getRnd() const {
    return rnd;
}

u16 Pokemon::getPokemonDataId() const {
    return dataID;
}

bool Pokemon::isRare() const {
    return isRareParam(getCatchTrainerRnd(), getRnd());
}

u8 Pokemon::getSeikaku() const {
    return getRnd() % 25;
}

void Pokemon::initCondition() {
    condition = 0;
    conditionCount = 0;
    conditionTurn = 0;
    conditionTurnNow = 0;
}

void Pokemon::copyCondition(const Pokemon* poke) {
    condition = poke->condition;
    conditionCount = poke->conditionCount;
    conditionTurn = poke->conditionTurn;
    conditionTurnNow = poke->conditionTurnNow;
}

Ribbon* Pokemon::getRibbon() {
    return &ribbon;
}

PokemonWaza* Pokemon::getPokemonWaza(u16 wazaNum) {
    if (wazaNum < MAX_WAZA)
 {
        return &wazas[wazaNum];
    }
    return nullptr;
}

void* Pokemon::getPokemonDataPtr() const {
    u32 num = getPokemonDataId();
    u32 maxNum = *pokemon_data_number;
    if (num >= maxNum) {
        return nullptr;
    }

    return &pokemon_data[num];
}

u32 Pokemon::getCatchTrainerRnd() const {
    return catchTrainerRnd;
}

void Pokemon::clear() {
    memset(this, 0, sizeof(Pokemon));
}

void PokemonStatusRnd::setNimbleness(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    nimbleness = finalData;
}

void PokemonStatusRnd::setSpeDef(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    speDef = finalData;
}

void PokemonStatusRnd::setSpeAtk(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    speAtk = finalData;
}

void PokemonStatusRnd::setPhyDef(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    phyDef = finalData;
}

void PokemonStatusRnd::setPhyAtk(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    phyAtk = finalData;
}

void PokemonStatusRnd::setMaxHp(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    maxHp = finalData;
}

u32 PokemonStatusRnd::getNimbleness() const {
    return nimbleness;
}

u32 PokemonStatusRnd::getSpeDef() const {
    return speDef;
}

u32 PokemonStatusRnd::getSpeAtk() const {
    return speAtk;
}

u32 PokemonStatusRnd::getPhyDef() const {
    return phyDef;
}

u32 PokemonStatusRnd::getPhyAtk() const {
    return phyAtk;
}

u32 PokemonStatusRnd::getMaxHp() const {
    return maxHp;
}
