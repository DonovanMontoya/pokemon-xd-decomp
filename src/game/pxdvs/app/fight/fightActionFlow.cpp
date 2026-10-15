#include <dolphin/types.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

class DeckDarkPokemon {
public:
    u8 getWorth() const;
    u8 getUnderTakerFlag() const;
};

class Hero {
public:
    static Hero *getHeroPtr();
    u32 getFootStep() const;
};

struct FightOutPokemon;
struct FIGHT_FLOOR;
struct FightActionCopy {
    u16 kind;
    s32 buff;
    void *data;
    void *buffData;
    s32 buffDataId;
    void *actor;
    void *motoData;
    s32 fifoIndex;
    s32 dispBuff0;
    s32 dispBuff1;
    s32 dispBuff2;
    s32 dispBuff3;
};
struct KeyInfoCopy {
    u16 on, off, trigger, repeat, released;
    u8 reserved[0x10];
};

extern "C" {
u32 fightFloor_GetFightType(void *);
void *fightActionBiosGetActorFightTargetPtr(void *);
void fightSeqSpecificationActionCounterInit(void *);
u8 fightTargetIsHostSide(void *, u8);
u8 fightFloorSetFightResultId(void *, s32);
void fightFloor_SetEscapePokemonPtr(void *, void *);
void fightSeqPokemonSoubiItemCheckAppear(FightOutPokemon *);
void fightSeqFightOutPokemonTokuseiCheckAppear(FightOutPokemon *);
u32 fightGetFightEncountDataId(void);
void *fightEncountDataBiosGetPtr(u32);
void *fightFloorGetStatus(u32, u32, u32, u32);
void fightFloorCreate(void *, u32);
void fightFloorInitFightStart(void *);
u32 fightEncountDataBiosGetFightFloorDataId(void *);
void *fightTargetGetPtr(u32, u32, u32);
u32 fightFloorDB_GetFightSideDataId(u32, u32);
void fightSideCreate(void *, u32);
u32 fightFloor_GetEnvSndId(void *);
u8 soundOpenPlayFadeOutIn(s32, s32, s32, u8);
void fightMainWaitFrame(s16);
void *fightOutPokemon_GetSequencePtr(FightOutPokemon *);
void fightSeqFightOutPokemonDarkCheckAppear(FightOutPokemon *, u8);
void fightFloor_SetAttackPokemonPtr(void *, void *);
void fightSeqCallExec(void *);
void *fightActionBiosGetBuffDataPtr(void *);
void fightSeqExec(void *, void *, void *);
u16 fightGetFightResultId(void);
void fightSeqPost(void *);
void fightFloorInitFightTarget(void *);
u8 fightTrainerSelectFightAction(void *, u16);
void fightFloorSetTuusinErrorFightResult(void *);
void fightFloor_SetIrekaePokemonPtr(void *, void *);
s32 fightActionBiosGetBuffDataId(void *);
void fightOutPokemon_SetIrekaeTargetEntryId(void *, s16);
void fightSeqIrekaeExec(void *);
KeyInfoCopy menuGetKeyInfo(s32);
s8 fadeCheck(s32);
u32 fightFloor_GetFightKind(void *);
u32 GSflagGet(u32);
void fightFloorCreateFightOutPokemonPtrAry(void *);
void fightFloorSortFightOutPokemonPtrAry(void *, s32);
void fightSeqPre(void *);
void *fightFloor_GetFightOutPokemonPtrAry(void *, u16);
u8 fightOutPokemonCheckFightOut(void *);
void fightOutPokemon_SetFightActionFlag(void *, u8);
u8 fightOutPokemon_GetFightActionFlag(void *);
void *fightOutPokemon_GetFightActionBuffPtr(void *);
u8 fightActionCheckValid(void *);
u16 fightActionGetKindDataId(void *);
u8 fightActionFlowFifo(FightActionCopy);
void *fightOutPokemon_GetFightItemPtr(void *);
u16 fightItem_GetItemDataId(void *);
u8 itemDB_GetKind(u16);
u32 fightItem_GetTargetDataId(void *);
void *fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u32, u16);
void fightFloor_SetDefensePokemonPtr(void *, void *);
void fightSeqItemExec(void *, u16);
void fightKoukaDoFightKoukaJoukenAndKouka(void *, s32);
u32 fightFloorGetNowTenkouDataId(void *, u8);
u8 fightFloorLoopValidFightOutPokemon(void *, s32 (*)(void *, u16, void *), void *, u8);
u32 tenkouDataBiosGetFightInitMsgId(u8);
void fightFloor_SetAppointMsgPtr(void *, u32);
void fightSeqInit(void);
void *fightActionBiosGetFightActionDataPtr(void *);
u8 fightSeqFightActionCreateAndFlowFifo(void *, void *, u16, s32, void *, void *);
void fightSeqFightOutPokemonTokuseiCheckIkaku(s8);
void fightSeqFightOutPokemonTokuseiCheckTrace(void);
void fightFloorSetMeetEnemyFightPokemonEnemySideAll(void *);
void fightFloorRegistFightTrainerEnemyPokemonFightSideAll(void *);
void fightFloorCreateFightPokemonEnemyAryEnemySideAll(void *);
s32 HSD_Rand(void);
void fightFloor_SetFisstAttackRnd(void *, u16);
void wazaSequenceSysFreeAllWaza(void);
extern u8 fight_action_data_kaisi[];
extern u8 WAZA_FieldWeather[];
u8 dbgMenuFightGetAllFightTrainerOperateFlag(void);
u32 fightFloor_GetFightTypeTrainerNum(void *);
void *fightFloorGetValidFightSidePtr(void *, u32);
void *fightSideGetValidFightTrainerPtr(void *, u32);
u8 fightMenuFightTrainerGcHeroOpenMenu(void *, u8, u8);
u8 fightFloorLoopValidFightTrainer(void *, s32 (*)(void *, u16, void *), void *, u8);
void *fightOutPokemon_GetFightWazaPtr(void *);
u8 fightWazaCheckValid(void *);
u16 fightWaza_GetTargetDataId(void *);
void *fightOutPokemonGetPokemonPtr(void *);
u16 fightOutPokemon_GetMotoWazaDataId(void *);
u8 fightWaza_GetWazaBanme(void *);
u8 fightWaza_GetAutoMakeFlag(void *);
u16 pokemon_GetPokemonWazaDataId(void *, u16);
void fightWaza_SetMotoWazaDataId(void *, u16);
void fightWazaSetUseWazaStatus(void *, u16);
void *fightSeqSelectDefensePokemonPtr(void *, u16, u8, void *, u8, u8, s16);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(void *, void *);
void fightSeqWazaExec(void *, u16);
u8 fightOutPokemonIsJoutaiDataId(void *, u16);
void fightSeqCheckDarkPokemonJoutaiHyperAct(void *, u8);
}
u32 deckDataVirtualDB_GetFlag(u16);

extern "C" {
void *fightFloorGetGcHeroFightTrainerPtr(void *);
void *fightTrainer_GetHeroPtr(void *);
void fightTrainerBackFightPokemonToTemotiPokemon(void *, u8);
u8 fightFloor_GetFightKindGetExpFlag(void *);
u8 fightTrainerCheckCanGetExp(void *);
void *heroGetStatus(void *, u32, u32);
u8 pokemonCheckFightOut(void *);
u8 pokemonIsDarkPokemon(void *);
void *fightTrainerCheckTemotiPokemonFightEntry(void *, void *);
u8 fightPokemonCheckFightOut(void *);
u8 fightPokemon_GetLevelUpFlag(void *);
u16 pokemonEvolutionCheck(void *, u32, u32, u16 *, u16 *);
void pokemonEvolutionAll(void *, u16, u16, u16 *, void *, u8, u8, u8);
void fightMainWaitFrameEffect(u32);
u8 fightFloor_GetFightKindMonohiroiFlag(void *);
void heroCheckSetMonohiroiAllTemotiPokemon(void *);
u8 fightFloor_GetFightKindGetInfectPokerusFlag(void *);
u8 fightFloor_GetFightKindBackSaveDataFlag(void *);
void *savedataGetStatus(u32, u32);
u8 heroBiosGetMeetDarkPokemonCount(void *);
void heroBiosCopy(void *, void *);
void heroBiosSetMeetDarkPokemonCount(void *, u8);
u8 menuCBBios_CurrentlyWorkingToolBattle(void);
void *menuCBBios_GetHeroImmediately(u8);
u8 fightTrainerIsGcHero(void *);
void *fightGetMenuCtrlHero(void);
void WazaSequence_Free(u32);
extern u32 fightEnemyTrainerWazaSeqHdl;
}

extern "C" {
u8 fightFloorIsGcHeroWin(void *, u16);
void fightMsgctrlSetValue(u32, void *);
u8 fightMenuOpenMsg(u32);
void fightMenuCloseMsg(void);
void *pokemon_GetNicknamePtr(Pokemon *);
u32 fightFloor_GetFightFloorDataId(void *);
void *fightTargetGetPtrAsNowFightType(u32, void *);
void *fightTrainer_GetSequencePtr(void *);
u32 fightTrainer_GetFightTrainerDataId(void *);
u32 fightFloor_GetSyoukaiWzxDataId(void *);
u32 fightFloor_GetEncountDataId(void *);
u32 fightEncountDataBiosGetSyoukaiWzxDataId(void *);
u32 fightTrainerDB_GetSyoukaiWzxDataId(u32);
u32 fightTrainerDB_GetSerihuMsgId(u32, u32);
u8 fightKind_CheckFightKind(u32);
u8 fightFloorIsNowEncountVirtualBattle(void *);
u8 fightFloorIsNowEncountOpeningVirtualBattle(void *);
u8 fightFloorIsNowEncountHostEnemyPokemonKime(void *);
u8 fightTargetIsHostSide(void *, u8);
void *fightTrainerGetValidFightOutPokemonPtr(void *, u8);
void Sequence_LoadWaza(void *, u16, s32, s32);
u8 fightFloor_GetFightKindHostEnemyMsgFlag(void *);
extern u16 _fight_kaisi_pre_trainer_intr_wzx_data_id_ary[5];
extern u8 _fight_kaisi_pre_trainer_intr_wzx_data_id_num;
extern u16 _fight_kaisi_pre_trainer_intr_wzx_data_id;
}

extern "C" s32 fightActionFlowHeijou(void) {
    return 1;
}

static s32 _fightActionFlowKaisiPostSubFightOutPokemonSoubiItemCheckAppear(void *p, u16, void *) {
    fightSeqPokemonSoubiItemCheckAppear((FightOutPokemon *)p);
    return 1;
}

static s32 _fightActionFlowKaisiPostSubFightOutPokemonTokuseiCheckAppear(void *p, u16, void *) {
    fightSeqFightOutPokemonTokuseiCheckAppear((FightOutPokemon *)p);
    return 1;
}

extern "C" s32 fightActionFlowFightNigeru(void *actor) {
    void *target;
    u8 type = fightFloor_GetFightType(0);
    target = fightActionBiosGetActorFightTargetPtr(actor);
    fightSeqSpecificationActionCounterInit(target);
    u8 res;
    if (fightTargetIsHostSide(target, type) == 1) {
        res = fightFloorSetFightResultId(0, 4);
    } else {
        res = fightFloorSetFightResultId(0, 5);
    }
    if (res == 1) {
        fightFloor_SetEscapePokemonPtr(0, target);
    }
    return 1;
}

extern "C" s32 fightActionFlowKaijou(void) {
    void *data;
    u32 floorData;
    void *t;
    u8 type;
    u32 id = fightGetFightEncountDataId();
    data = fightEncountDataBiosGetPtr(id);
    fightFloorCreate(fightFloorGetStatus(0, 0, 0, 0), id);
    fightFloorInitFightStart(0);
    type = fightFloor_GetFightType(0);
    floorData = fightEncountDataBiosGetFightFloorDataId(data);
    t = fightTargetGetPtr(4, 0, type);
    u32 side = fightFloorDB_GetFightSideDataId(floorData, 0);
    fightSideCreate(t, side);
    t = fightTargetGetPtr(5, 0, type);
    fightSideCreate(t, fightFloorDB_GetFightSideDataId(floorData, 1));
    return 1;
}

extern "C" s32 fightActionFlowNullFunc(void) {
    return 1;
}

extern "C" s32 fightActionFlowSyuuryouPre(void) {
    if (fightFloor_GetEnvSndId(0) != 0) {
        soundOpenPlayFadeOutIn(8, 1000, 1000, 255);
        fightMainWaitFrame(60);
    }
    return 1;
}

static s32 _fightActionFlowTenkouInitSubGetSeqFightOutPokemonPtr(void *p, u16, void *out) {
    if (fightOutPokemon_GetSequencePtr((FightOutPokemon *)p) != 0) {
        if (out != 0) {
            *(void **)out = p;
        }
        return 0;
    }
    return 1;
}

static s32 _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear(void *p, u16, void *arg) {
    if (arg != 0) {
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon *)p, *(u8 *)arg);
    } else {
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon *)p, 0);
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon *)p, 1);
    }
    return 1;
}

extern "C" s32 fightActionFlowFightTrainerCall(void *actor) {
    void *target;
    fightFloor_GetFightType(0);
    target = fightActionBiosGetActorFightTargetPtr(actor);
    fightFloor_SetAttackPokemonPtr(0, target);
    fightSeqCallExec(actor);
    return 1;
}

extern "C" s32 fightActionFlowWazaKiaipantiPre(void *actor) {
    fightFloor_SetAttackPokemonPtr(0, fightActionBiosGetActorFightTargetPtr(actor));
    fightSeqExec(actor, fightActionBiosGetBuffDataPtr(actor), 0);
    return 1;
}

extern "C" s32 fightActionFlowOneTurnPost(void *actor) {
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    fightSeqPost(actor);
    fightMainWaitFrame(5);
    fightFloorInitFightTarget(0);
    return 1;
}

static s32 _fightActionFlowFightTrainerSelectFightAction(void *p, u16 q, void *) {
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    if (!fightTrainerSelectFightAction(p, q)) {
        fightFloorSetTuusinErrorFightResult(0);
    }
    return 1;
}

extern "C" s32 fightActionFlowFightOutPokemonIrekae(void *actor) {
    void *target = fightActionBiosGetActorFightTargetPtr(actor);
    fightFloor_SetIrekaePokemonPtr(0, target);
    fightOutPokemon_SetIrekaeTargetEntryId(target, fightActionBiosGetBuffDataId(actor));
    fightSeqIrekaeExec(actor);
    return 1;
}

static u8 _fightActionFlowKaisiPreSubCheckCancel(bool *flag) {
    if (flag == 0) {
        return 0;
    }
    {
        u16 on = menuGetKeyInfo(1).on;
        if (fadeCheck(0) == 0 && (on & 0x20)) {
            *flag = 1;
        }
    }
    return *flag;
}

static bool _fightActionFlowKaisiPreSubCheckVirtualDiskCancel(u16 deck) {
    u8 kind = fightFloor_GetFightKind(0);
    if ((menuGetKeyInfo(1).on & 0x20) && kind == 0xF) {
        if (GSflagGet(0x8F5) == 1 || GSflagGet(deckDataVirtualDB_GetFlag(deck)) == 1) {
            return 1;
        }
    }
    return 0;
}

static u8 _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(FIGHT_FLOOR *floor, u8 flag) {
    u16 i;
    for (i = 0; i < 8; i++) {
        void *p = fightFloor_GetFightOutPokemonPtrAry(floor, i);
        if (p != 0) {
            void *buff;
            if (!fightOutPokemonCheckFightOut(p)) {
                fightOutPokemon_SetFightActionFlag(p, 1);
                continue;
            }
            buff = fightOutPokemon_GetFightActionBuffPtr(p);
            if (buff == 0) {
                fightOutPokemon_SetFightActionFlag(p, 1);
                continue;
            }
            if (!fightActionCheckValid(buff)) {
                fightOutPokemon_SetFightActionFlag(p, 1);
                continue;
            }
            if (!flag) {
                if (fightActionGetKindDataId(buff) != 8) {
                    continue;
                }
            } else {
                if (fightActionGetKindDataId(buff) == 8) {
                    continue;
                }
            }
            if (fightOutPokemon_GetFightActionFlag(p) == 1) {
                continue;
            }
            fightOutPokemon_SetFightActionFlag(p, 1);
            fightActionFlowFifo(*(FightActionCopy *)buff);
            if (flag) {
                fightFloorInitFightTarget(0);
                if (fightGetFightResultId() != 0) {
                    fightGetFightResultId();
                    return 1;
                }
            }
        }
    }
    return 1;
}

extern "C" s32 fightActionFlowAllFightOutPokemonDoFightAction(void *actor) {
    fightFloorCreateFightOutPokemonPtrAry(0);
    fightFloorSortFightOutPokemonPtrAry(0, 1);
    s32 r = _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(0, 0);
    if ((u8)r != 1) {
        return r;
    }
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    fightSeqPre(actor);
    r = _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(0, 1);
    return (u8)r == 1 ? 1 : r;
}

extern "C" s32 fightActionFlowFightTrainerUseItem(void *actor) {
    void *target;
    void *item;
    u16 itemId;
    u8 type;
    void *def;
    type = fightFloor_GetFightType(0);
    target = fightActionBiosGetActorFightTargetPtr(actor);
    fightFloor_SetAttackPokemonPtr(0, target);
    item = fightOutPokemon_GetFightItemPtr(target);
    itemId = fightItem_GetItemDataId(item);
    if (itemDB_GetKind(itemId) == 1) {
        def = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightItem_GetTargetDataId(item), type);
    } else {
        def = target;
    }
    fightFloor_SetDefensePokemonPtr(0, def);
    fightSeqItemExec(actor, itemId);
    return 1;
}

extern "C" s32 fightActionFlowTenkouInit(void *actor) {
    u8 tenkou;
    void *seq;
    fightKoukaDoFightKoukaJoukenAndKouka(0, 1);
    tenkou = fightFloorGetNowTenkouDataId(0, 0);
    seq = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowTenkouInitSubGetSeqFightOutPokemonPtr, &seq, 0);
    if (tenkou != 0) {
        u32 msg;
        fightFloor_SetAttackPokemonPtr(0, seq);
        msg = tenkouDataBiosGetFightInitMsgId(tenkou);
        fightFloor_SetAppointMsgPtr(0, msg);
        fightSeqExec(actor, fightActionBiosGetBuffDataPtr(actor), 0);
    }
    return 1;
}

extern "C" s32 fightActionFlowKaisiPost(void *actor) {
    u8 flag;
    fightFloorCreateFightOutPokemonPtrAry(0);
    fightFloorSortFightOutPokemonPtrAry(0, 0);
    fightSeqInit();
    flag = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear, &flag, 0);
    fightSeqFightActionCreateAndFlowFifo(fightActionBiosGetFightActionDataPtr(actor), 0, 6, 0, fight_action_data_kaisi, WAZA_FieldWeather);
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonTokuseiCheckAppear, 0, 1);
    fightSeqFightOutPokemonTokuseiCheckIkaku(1);
    fightSeqFightOutPokemonTokuseiCheckTrace();
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonSoubiItemCheckAppear, 0, 1);
    flag = 1;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear, &flag, 0);
    fightFloorSetMeetEnemyFightPokemonEnemySideAll(0);
    fightFloorRegistFightTrainerEnemyPokemonFightSideAll(0);
    fightFloorCreateFightPokemonEnemyAryEnemySideAll(0);
    fightFloor_SetFisstAttackRnd(0, HSD_Rand());
    wazaSequenceSysFreeAllWaza();
    return 1;
}

extern "C" s32 fightActionFlowAllFightTrainerSelectFightAction(void) {
    u16 saved;
    u8 operate;
    void *sp;
    u32 num;
    u8 type;
    u32 j;
    u32 side;
    operate = dbgMenuFightGetAllFightTrainerOperateFlag();
    if (operate == 1) {
        type = fightFloor_GetFightType(0);
        num = (u8)fightFloor_GetFightTypeTrainerNum(0);
        for (side = 0; (u16)side < 2; side++) {
        top:
            sp = fightFloorGetValidFightSidePtr(0, side);
            if (sp != 0) {
                saved = side;
                for (j = 0; (u16)j < num; j++) {
                    for (;;) {
                        void *tr = fightSideGetValidFightTrainerPtr(sp, j);
                        if (tr == 0) {
                            break;
                        }
                        if (fightMenuFightTrainerGcHeroOpenMenu(tr, type, operate)) {
                            break;
                        }
                        if (saved != 0) {
                            side--;
                            goto top;
                        }
                    }
                }
            }
        }
    } else {
        fightFloorLoopValidFightTrainer(0, _fightActionFlowFightTrainerSelectFightAction, 0, 1);
    }
    return 1;
}

extern "C" s32 fightActionFlowFightOutPokemonOutWaza(void *actor) {
    u8 type = fightFloor_GetFightType(0);
    void *attacker = fightActionBiosGetActorFightTargetPtr(actor);
    void *waza = fightOutPokemon_GetFightWazaPtr(attacker);
    void *def;
    void *pk;
    void *waza2;
    u16 moto;
    u8 banme;
    if (!fightWazaCheckValid(waza)) {
        return 0;
    }
    def = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightWaza_GetTargetDataId(waza), type);
    fightFloor_SetAttackPokemonPtr(0, attacker);
    fightFloor_SetDefensePokemonPtr(0, def);
    pk = fightOutPokemonGetPokemonPtr(attacker);
    waza2 = fightOutPokemon_GetFightWazaPtr(attacker);
    moto = fightOutPokemon_GetMotoWazaDataId(attacker);
    banme = fightWaza_GetWazaBanme(waza2);
    if (!fightWaza_GetAutoMakeFlag(waza2)) {
        if (moto != pokemon_GetPokemonWazaDataId(pk, banme)) {
            moto = pokemon_GetPokemonWazaDataId(pk, banme);
            fightWaza_SetMotoWazaDataId(waza2, moto);
            fightWazaSetUseWazaStatus(waza2, moto);
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, fightSeqSelectDefensePokemonPtr(attacker, moto, type, 0, 1, 0, -1));
        }
    }
    fightSeqWazaExec(actor, moto);
    if (!fightOutPokemonIsJoutaiDataId(attacker, 0x3E)) {
        fightSeqCheckDarkPokemonJoutaiHyperAct(attacker, 0);
    }
    return 1;
}

void _darkPokemonSetUnderTaker(DeckDarkPokemon *deck, Pokemon *pk, u16 id) {
    DarkPokemon *dp = pk->getDarkPokemon();
    if (deck->getWorth()) {
        u32 steps = Hero::getHeroPtr()->getFootStep();
        if (deck->getUnderTakerFlag() || fightFloorIsGcHeroWin(0, fightGetFightResultId())) {
            if (dp->getStatus() < 2) {
                dp->setStatus(darkStatus2);
                dp->setEscapeTime(steps);
                if (id != 0x17D7) {
                    fightMsgctrlSetValue(0x16, pokemon_GetNicknamePtr(pk));
                    fightMenuOpenMsg(0x500B);
                    fightMenuCloseMsg();
                }
            }
        }
    }
}

u16 _fight_kaisi_pre_trainer_intr_wzx_data_id_ary[5] = {0x90, 0x91, 0x92, 0x93, 0x94};
u8 _fight_kaisi_pre_trainer_intr_wzx_data_id_num = 5;
u16 _fight_kaisi_pre_trainer_intr_wzx_data_id;

extern "C" void fightActionFlowKaisiPreSubLoad(void) {
    u16 w3;
    u32 trainerId;
    void *seqB;
    u32 w2;
    void *t0;
    u32 w1;
    void *t1;
    void *seqA;
    u16 msg;
    u16 eid;
    fightFloor_GetFightFloorDataId(0);
    t0 = fightTargetGetPtrAsNowFightType(0xB, 0);
    seqA = fightTrainer_GetSequencePtr(t0);
    t1 = fightTargetGetPtrAsNowFightType(9, t0);
    seqB = fightTrainer_GetSequencePtr(t1);
    trainerId = fightTrainer_GetFightTrainerDataId(t1);
    w1 = fightFloor_GetSyoukaiWzxDataId(0);
    eid = fightFloor_GetEncountDataId(0);
    w2 = fightEncountDataBiosGetSyoukaiWzxDataId(fightEncountDataBiosGetPtr(eid));
    w3 = fightTrainerDB_GetSyoukaiWzxDataId(trainerId);
    if (w3 == 0) {
        w3 = 0x5F;
    }
    msg = fightTrainerDB_GetSerihuMsgId(trainerId, 0);
    if (fightKind_CheckFightKind(0xA)) {
        msg = 0;
    }
    if (fightFloorIsNowEncountVirtualBattle(0) == 1) {
        Sequence_LoadWaza(seqA, 0x54, 4, 0);
        Sequence_LoadWaza(seqB, 0x55, 4, 0);
        Sequence_LoadWaza(seqA, 0x56, 4, 0);
    } else {
        fightFloorIsNowEncountOpeningVirtualBattle(0);
    }
    if (fightFloorIsNowEncountHostEnemyPokemonKime(0) == 1 && !fightTargetIsHostSide(t1, fightFloor_GetFightType(0))) {
        u32 i;
        for (i = 0; (u8)i < 2; i++) {
            void *p = fightTrainerGetValidFightOutPokemonPtr(t1, i);
            if (p != 0) {
                void *seq = fightOutPokemon_GetSequencePtr((FightOutPokemon *)p);
                if (seq != 0) {
                    Sequence_LoadWaza(seq, 0x9F, 4, 0);
                }
            }
        }
    } else {
        if (w1 != 0) {
            if (w2 != 0) {
                Sequence_LoadWaza(seqB, w2, 4, 0);
            }
            Sequence_LoadWaza(seqB, w1, 4, 0);
            if (fightFloor_GetFightKindHostEnemyMsgFlag(0) == 1) {
                _fight_kaisi_pre_trainer_intr_wzx_data_id = (u16)HSD_Rand() % _fight_kaisi_pre_trainer_intr_wzx_data_id_num;
                _fight_kaisi_pre_trainer_intr_wzx_data_id = _fight_kaisi_pre_trainer_intr_wzx_data_id_ary[_fight_kaisi_pre_trainer_intr_wzx_data_id];
                Sequence_LoadWaza(seqB, _fight_kaisi_pre_trainer_intr_wzx_data_id, 4, 0);
            } else {
                _fight_kaisi_pre_trainer_intr_wzx_data_id = 0;
            }
        }
        if (msg != 0) {
            Sequence_LoadWaza(seqB, 0x5F, 4, 0);
        }
        if (fightFloor_GetFightKindHostEnemyMsgFlag(0) == 1) {
            Sequence_LoadWaza(seqB, w3, 4, 0);
        }
    }
}

extern "C" s32 fightActionFlowSyuuryouPost(void) {
    u32 num = (u8)fightFloor_GetFightTypeTrainerNum(0);
    if (fightGetFightResultId() == 1) {
        return 1;
    }
    {
        void *gc = fightFloorGetGcHeroFightTrainerPtr(0);
        if (gc != 0) {
            void *hero = fightTrainer_GetHeroPtr(gc);
            if (hero != 0) {
                fightTrainerBackFightPokemonToTemotiPokemon(gc, 0);
                if (fightFloorIsGcHeroWin(0, fightGetFightResultId()) == 1) {
                    if (fightFloor_GetFightKindGetExpFlag(0) == 1 && fightTrainerCheckCanGetExp(gc) == 1) {
                        u32 i;
                        for (i = 0; (u16)i < 6; i++) {
                            void *pk = heroGetStatus(hero, 3, i);
                            if (pokemonCheckFightOut(pk) && pokemonIsDarkPokemon(pk) != 1) {
                                void *fp = fightTrainerCheckTemotiPokemonFightEntry(gc, pk);
                                if (fp != 0 && fightPokemonCheckFightOut(fp) && fightPokemon_GetLevelUpFlag(fp)) {
                                    u32 evoB;
                                    u16 evoA;
                                    u16 evo = pokemonEvolutionCheck(pk, 0, 0, &evoA, (u16 *)&evoB);
                                    if (evo != 0) {
                                        pokemonEvolutionAll(pk, evo, evoA, (u16 *)&evoB, hero, 1, 1, 0);
                                        fightMainWaitFrameEffect(10);
                                    }
                                }
                            }
                        }
                    }
                    if (fightFloor_GetFightKindMonohiroiFlag(0) == 1) {
                        heroCheckSetMonohiroiAllTemotiPokemon(hero);
                    }
                    fightFloor_GetFightKindGetInfectPokerusFlag(0);
                }
                if (fightFloor_GetFightKindBackSaveDataFlag(0) == 1) {
                    void *save = savedataGetStatus(0, 2);
                    if (save != 0) {
                        u8 cnt = heroBiosGetMeetDarkPokemonCount(save);
                        heroBiosCopy(save, hero);
                        heroBiosSetMeetDarkPokemonCount(save, cnt);
                    }
                }
            }
        }
    }
    if (menuCBBios_CurrentlyWorkingToolBattle() == 1) {
        u32 side;
        for (side = 0; (u16)side < 2; side++) {
            void *sp = fightFloorGetValidFightSidePtr(0, side);
            if (sp != 0) {
                u32 j;
                u32 base = (u16)side * num;
                for (j = 0; (u16)j < num; j++) {
                    void *tr = fightSideGetValidFightTrainerPtr(sp, j);
                    if (tr != 0) {
                        void *h;
                        fightTrainerBackFightPokemonToTemotiPokemon(tr, 0);
                        h = menuCBBios_GetHeroImmediately(j + base);
                        if (h != 0) {
                            void *h2 = fightTrainer_GetHeroPtr(tr);
                            if (h2 != 0) {
                                heroBiosCopy(h, h2);
                            }
                        }
                    }
                }
            }
        }
    }
    if ((u8)fightFloor_GetFightKind(0) == 6 || (u8)fightFloor_GetFightKind(0) == 7) {
        u32 side;
        for (side = 0; (u16)side < 2; side++) {
            void *sp = fightFloorGetValidFightSidePtr(0, side);
            if (sp != 0) {
                u32 j;
                for (j = 0; (u16)j < num; j++) {
                    void *tr = fightSideGetValidFightTrainerPtr(sp, j);
                    if (tr != 0) {
                        if ((u8)fightFloor_GetFightKind(0) == 6 || (u8)fightFloor_GetFightKind(0) == 7) {
                            if (!fightTrainerIsGcHero(tr)) {
                                continue;
                            }
                        }
                        {
                            void *h;
                            fightTrainerBackFightPokemonToTemotiPokemon(tr, 0);
                            h = fightGetMenuCtrlHero();
                            if (h != 0) {
                                void *h2 = fightTrainer_GetHeroPtr(tr);
                                if (h2 != 0) {
                                    heroBiosCopy(h, h2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (fightEnemyTrainerWazaSeqHdl != 0) {
        WazaSequence_Free(fightEnemyTrainerWazaSeqHdl);
    }
    return 1;
}

u32 fightEnemyTrainerWazaSeqHdl;
