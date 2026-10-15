#ifndef APPSCRIPT_PRIVATE_HPP
#define APPSCRIPT_PRIVATE_HPP
#include <global.h>
#include <game/pxdvs/GSAPI/GSScript/tiga.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

struct GSthread;
struct FIGHT_ENCOUNT {
    void clear();
    u8 getDirtyFlag() const;
    void setField(u16);
    u16 getField() const;
    u16 getMsg(u8) const;
    void setMsg(u8, u16);
    s32 getAddMode() const;
    u8 getAddPlace() const;
    u8 getAddID() const;
    void setAddMode(u8);
    void setAddPlace(u8);
    void setAddID(u8);
    s32 getSwapMode() const;
    u16 getSwapDeckNO() const;
    void setSwapMode(u8);
    void setSwapDeckNO(u16);
    void setFightMode(u8);
    s32 getDestroyFlag() const;
    void setDestroyFlag(u8);
    u8 getTrainerKind() const;
    void setTrainerKind(u8);
    s32 getRoundNo() const;
    void setRoundNo(u32);
};
extern "C" FIGHT_ENCOUNT* fightEncountGetStrObj(void);
struct Pokemon {
    u8 isLegend() const;
};
struct Hero {
    u8 getMeetDarkPokemonCount() const;
    void setMeetDarkPokemonCount(u8);
};
extern "C" void* savedataGetStatus(s32, u16);

namespace GSscript {
struct tigaWaza {
    void* sequence;     // 0x00
    void* wazaSequence; // 0x04
};
}  // namespace GSscript

// Scratch area referenced through the pointer at 0x914 of the script object.
struct AppScriptWork {
    u8 reserved0[0x10];
    GSscript::tigaVariant ret;  // 0x10
    u8 reserved18[0x120];
    GSvec vec;                  // 0x138
};

class AppScript : public GSscript::Tiga {
public:
    AppScriptWork* work() { return *(AppScriptWork**)pad914; }

    GSscript::tigaWaza waza[7];     // 0x988

    AppScript();
    virtual int execExtendMethod(int, int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    virtual int execExtendGlobalFunction(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    virtual int getExtendVariable(GSscript::tigaVariant*, int, int);
    virtual int setExtendVariable(GSscript::tigaVariant*, int, int);
    virtual void mapping();
    virtual void unmapping();
    virtual ~AppScript();

    int cmpPeople(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpCamera(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpFloor(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpMenu(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpHero(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpEsaba(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpDarkPokemon(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpWaza(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpSodateya(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpTv(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpDirection(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpMail(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpPad(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpSound(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpCol(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpModel(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpLight(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpFight(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpFade(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpTask(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int cmpPokemon(int, GSscript::tigaVariant*, GSscript::tigaVariant*);
    int commonCall(GSscript::tigaVariant*, GSscript::tigaVariant*);
    int orFlagTest(GSscript::tigaVariant*);
    int andFlagTest(GSscript::tigaVariant*);
    int fncPrintf(GSscript::tigaVariant*);
    void unload();
    void freeWazaPtr(GSscript::tigaWaza*);
    GSscript::tigaWaza* allocWazaPtr();
};

// Integer / string accessors that the original script code expanded inline.
static inline s32 appScriptGetInt(GSscript::tigaVariant* v) {
    if (v->type == 1) {
        return v->value.integer;
    }
    if (v->type == 2) {
        return (s32)v->value.single;
    }
    return v->getCnvInteger();
}

static inline f32 appScriptGetFloat(GSscript::tigaVariant* v) {
    if (v->type == 1) {
        return (f32)v->value.integer;
    }
    if (v->type == 2) {
        return v->value.single;
    }
    return v->getCnvSingle();
}

static inline GSvec* appScriptGetVec(GSscript::tigaVariant* v) {
    if (v->type == 4) {
        return v->value.vector;
    }
    return v->getCnvVector();
}

static inline GSscript::tigaWaza* appScriptGetWaza(GSscript::tigaVariant* v) {
    GSscript::tigaWaza* w;
    if (v->type == 0x3A) {
        w = (GSscript::tigaWaza*)v->value.pointer;
    } else {
        GSscript::tigaErrMessage("waza not access");
        w = 0;
    }
    return w;
}

static inline Pokemon* appScriptGetPokemon(GSscript::tigaVariant* v) {
    Pokemon* p;
    if (v->type == 0x25) {
        p = (Pokemon*)v->value.pointer;
    } else {
        GSscript::tigaErrMessage("pokemon not access");
        p = 0;
    }
    return p;
}

struct AppScriptColor {
    u8 r, g, b, a;
};

static inline AppScriptColor appScriptGetColor(GSscript::tigaVariant* v) {
    AppScriptColor c;
    c.r = appScriptGetInt(&v[0]);
    c.g = appScriptGetInt(&v[1]);
    c.b = appScriptGetInt(&v[2]);
    c.a = appScriptGetInt(&v[3]);
    return c;
}

static inline void appScriptCopyVec(GSvec* dst, const f32* src) {
    dst->param1 = src[0];
    dst->param2 = src[1];
    dst->param3 = src[2];
}

static inline FIGHT_ENCOUNT* appScriptEncountForWrite() {
    FIGHT_ENCOUNT* obj = fightEncountGetStrObj();
    if (obj->getDirtyFlag() == 1) {
        obj->clear();
    }
    return obj;
}

static inline void appScriptSetResource(GSscript::tigaVariant* var, GSresID* rid) {
    GSresID* r;
    s32 idx = GSscript::Tiga::m_cpCurrentObject->objManager.getResourceIdx(rid);
    if (idx == -1) {
        r = GSscript::Tiga::m_cpCurrentObject->objManager.newResource();
        if (r != 0) {
            r->group = rid->group;
            r->id = rid->id;
        }
    } else {
        r = GSscript::Tiga::m_cpCurrentObject->objManager.getResource(idx);
    }
    var->type = 0x23;
    var->value.pointer = r;
    if (var->type != 1 && var->type != 2) {
        GSscript::Tiga::m_cpCurrentObject->cellMemory->dupVariant(var);
    }
}

static inline void appScriptSetFloat(GSscript::tigaVariant* v, f32 value) {
    v->type = 2;
    v->value.single = value;
}

static inline void appScriptSetInt(GSscript::tigaVariant* v, s32 value) {
    v->type = 1;
    v->value.integer = value;
}

static inline void appScriptSetVar(GSscript::tigaVariant* v, s16 type, void* value) {
    v->type = type;
    v->value.pointer = value;
}

static inline char* appScriptGetString(GSscript::tigaVariant* v, char* buffer) {
    if (v->type == 3) {
        return v->value.string;
    }
    return v->getCnvString(buffer);
}

struct _GSmodel;
s32 motorFun(u8, u8, u32, u8, bool);
struct GSlight;
extern "C" {
extern u32* flag_data_number;
void GSflagOn(u32);
void GSflagOff(u32);
void GSflagSet(u32, s32);
u32 GSflagGet(u32);
s32 scriptGetRandom(s32);
void darkPokemonBiosSetInfomation(u16, u16);
void floorSetDispScriptInfo(u8);
void floorSetHumanColision(u8);
u8 floorGetHumanColision(void);
void peopleSetTresureSearchDistance(u16, f32);
u8* GSmsgGetGSchar(s32);
u32 floorTresureGetResID(u16);
u8 wazaDB_GetHidenFlag(u16);
f32 PSVECDistance(GSvec*, GSvec*);
void GSresFreeResource(u32, u32);
void scriptGlowStart(u8, u8, u8, u8, u8, f32);
void scriptGlowEnd(void);
void scriptSetLensFlare(u32, u8, f32, f32, f32);
u8 GSgfxVideoGetVsyncRate(void);
s32 pokecoloGetCountryCode(void);
s32 pokecoloGetLanguage(void);
s32 scriptModelOpen(s32);
void scriptModelClose(s32);
void scriptModelSetDisp(s32, s32);
void scriptModelSetMotion(s32, s32, s32, s32);
void scriptModelStopMotion(s32);
s32 scriptModelWaitMotion(s32, s32);
s32 scriptModelAttach(s32, s32, s32);
s32 scriptModelDetach(s32);
void scriptModelSetParticle(s32, s32, u8);
void scriptModelDeleteParticle(s32, u8);
void* GSresGetResource(u32, u32);
u32 floorGetCurrentGroupID(void);
void* GSmodelGetPart(void*, s32);
void GSpartGetTransform(void*, f32*, s32, s32);
void GSpartFree(void*);
void GSmodelAddPosition(void*, GSvec*);
void GSmodelIterateList(void (*)(_GSmodel*, void*), s32);
void scriptModelSetMotionRate(s32, s32, s32, f32, s32);
void GSmodelSetBoundCheck(void*, u8);
s32 scriptModelSetEndedMotion(s32, s32, u8);
void scriptModelPartPaticle(s32, s32, s32);
void scriptModelSetFractionalFramesFlag(s32, u8);
void GSmodelRecalculateBound(void*);
void GSmodelUseRootJointAnimation(void*, s32);
s32 scriptEncount(u16, u8, s32);
u16 fightEncount(u16);
u16 fightGetFightResultId(void);
void fightSoundOpenPlay(u8);
void fightSoundOpenPlayEnv(u8);
void fightEncountAnnihilationRecovery(void);
void floorExecScriptInteger(s32, s32, s32, s32, s32);
void floorExecScriptIntegerThread(s32, s32, s32, s32, s32);
void floorExecScriptIntegerByName(char*, s32, s32, s32, s32);
void floorExecScriptIntegerByNameThread(char*, s32, s32, s32, s32);
s32 floorGetScriptResult(void);
void scriptWaitTime(f32);
void scriptLightSetDisp(s32, s32);
void scriptLightSetMotion(s32, s32, s32, s32);
void scriptLightStopMotion(s32);
s32 scriptLighgtWaitMotion(s32, s32);
GSlight* lightGetLight(s32);
void GSlightSetType(GSlight*, s32);
void GSlightSetPosition(GSlight*, GSvec*);
void GSlightSetColor(GSlight*, void*);
void GSlightGetPosition(GSlight*, GSvec*);
void scriptPlayPokemonNakigoe(u16);
void pokemonPlayVoice(Pokemon*);
void pokemonWazaCopy(Pokemon*, u16, u16);
void pokemonWazaForget(Pokemon*, s32);
s32 pokemonGetWazaCount(Pokemon*);
u8 pokemonBiosGetCatchBallId(Pokemon*);
void* pokemon_GetNicknamePtr(Pokemon*);
u8 pokemonBiosGetDarkFlag(Pokemon*);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon*, u16);
u16 pokemonBiosGetHp(Pokemon*);
s32 pokemonBiosGetDp(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
u16 pokemonBiosGetFriend(Pokemon*);
void* pokemonDB_GetName(u16);
u16 pokemonBiosGetItemDataId(Pokemon*);
s32 pokemonBiosGetCatchTrainerRnd(Pokemon*);
s8 pokemonSetWazaStatus(Pokemon*, u16, u8);
s32 scriptPokemonRememberWaza(Pokemon*, s32);
s32 scriptPokemonTeachWazaIndex(s32);
u8 pokemonDB_GetTeachWaza(u16, u16);
s32 menuPokemonStatusOpenWazaLearn(Pokemon*, u16);
s32 menuPokemonStatusOpenWazaLearnList(Pokemon*, u16);
void* Sequence_CreateNull(void);
void* Sequence_LoadWaza(void*, u16, u8, u8);
void WazaSequence_Start(void*, s32);
u8 WazaSequence_IsActive(void*);
void Sequence_SetPosition(void*, GSvec*);
void Sequence_SetRotation(void*, GSvec*);
void Sequence_SetScale(void*, GSvec*);
s32 esabaSet(s32);
u16 esabaGetPokemonID(s32);
void esabaSetEsaNum(s32, s32);
s32 esabaGetEsaNum(s32);
u8 esabaGetPokemonIsRare(s32);
u8 soundOpenPlay(s32, s32, u8);
u8 soundOpenPlayEnv(s32, s32, u8);
u8 soundStop(s32, s32);
u8 soundStopEnv(s32);
u8 soundCreateEmitter(s32, f32, f32, f32);
u8 soundCreateListener(void);
u8 soundSetVolume(s32, s32);
u8 scriptSoundOpenPlayME(s32, s32, u8);
u8 soundSetVolumeID(s32, s32, s32);
u8 soundOpenPlayFadeOutIn(s32, s32, s32, u8);
u8 soundOpenPlayEnvFadeOutIn(s32, s32, s32, u8);
s32 soundGetBGMID(void);
void peopleTalkMessageBgmMask(u8);
void peopleTalkMessageBgmSetFadeSpeed(f32, f32);
void peopleTalkMessageBgmSetVolumeRate(f32);
void soundPlayWait(s32);
void GSthreadSwitch(void);
void evolution(void);
void preReliveSetParameter(s32, s32, u8);
void reliveMain(void);
void preReliveDisplayHokoraParticle(void);
s32 menuUseItemScriptCologn(s32, s32);
s32 underTakerGetMiraboPlace(void);
void underTakerMiraboDisAppear(void);
s32 scriptIsButtonPush(void);
s32 scriptIsMoveButtonPush(void);
s32 scriptIsTrigerPush(void);
s32 gamedatasaveGetStatus(s32, s32);
GSthread* floorCreateThread(s32, u32, s32, s32 (*)(GSthread*));
void GSthreadSetArgs(GSthread*, s32, ...);
u32 GSinputButtonsPressed(s32);
void mailMainSendByScrpt(u16);
u8 scriptSetMemoFlag(void);
void menuScriptReciveMail(void);
void menuScriptReadMail(s32);
s32 sodateyaGetPokemonLevelUpValue(void);
s32 sodateyaGetPokemonDPValue(void);
void sodateyaRaise(s32);
void sodateyaReclaim(s32);
s32 sodateyaCalcPrice(s32);
s32 sodateyaeChekcRais(void);
void* sodateyaGetPokemonPtr(s32);
void scriptSetCol(s32, u8);
s32 scriptGetEventColID(void);
void scriptSetEventCol(u8);
void fadeSet(u16, f32);
s8 fadeCheck(u8);
void GSinputMotorStart(s32, u8, u8, u32, u8);
void GSmodelSetVisibility(_GSmodel*, u8);
s32 controlTV(s32);
s32 controlTVScreen(void);
u8 GSflagTest(s32);
void* __nw__FUl(unsigned long);
void __dl__FPv(void*);
void WazaSequence_Stop(void*);
void WazaSequence_Free(void*);
void Sequence_Free(void*);
void* memset(void*, int, unsigned long);
u32 soundOpenPlayME(u32, u32, u8);
u8 soundPlayME(u32, u32, u8);
}

GSscript::Tiga* floorGetCommonScript(void);

#endif
