#include <game/pxdvs/app/evolution/evolutionPrivate.hpp>

struct StepSeqEntry {
    u16 seq;
    s32 useAfter;
};

struct CancelStepEntry {
    u32 time;
    s32 step;
};

static const StepSeqEntry StepSeqTbl[5] = {
    {0x4A, 0}, {0x5E, 1}, {0x5B, 0}, {0x5C, 0}, {0x5D, 0}
};

static const CancelStepEntry CancelStep[3] = {
    {0x1E0, 2}, {0x21C, 3}, {0x1770, 4}
};

static EvolutionParameter Parameter;

static void restoreCamera(CAM_STORE*);
static void storeCamera(CAM_STORE*);
static void restoreSound(WORK*);
static void stopSound(WORK*);
static u32 getPokemonData(Pokemon*);
static u32 playPokemonVoice(Pokemon*);
static int dispMsgYesNo(unsigned long, EVOLUTION_WINDOW_TYPE);
static int getYesNo(EVOLUTION_WINDOW_TYPE);
static void dispMsg(unsigned long, EVOLUTION_WINDOW_TYPE);
static void closeMsgWin(EVOLUTION_WINDOW_TYPE);
static void openMsgWin(unsigned long, EVOLUTION_WINDOW_TYPE);
static void waitTime(float);
static u16 getPkxID(Pokemon*);
static u32 loadSequence(Pokemon*, int);
static u8 loadSequenceAfter(WORK*, Pokemon*);
static u8 loadSequenceBefore(WORK*, Pokemon*);
static void toVisible(WORK*, int, int);
static int loadAll(WORK*, Pokemon*, Pokemon*);
static s8 cbWazaForget(Pokemon*, unsigned short, long);
static int doWazaSequence(WORK*, STEP, int, FADE_CTRL);
static void wazaSeqEnd(WORK*);
static int wazaSeqUpdate(WORK*);
static u32 getStepSeq(WORK*, STEP);
static int wazaSeqStart(WORK*, STEP);
static int evolutionDemo(WORK*, int, Pokemon*, Pokemon*);
static int evolution__Main(WORK*, int, Pokemon*, Pokemon*, unsigned short*, long, unsigned char*);

static void restoreCamera(CAM_STORE* cam) {
    cameraSetType(2);
    cameraSetPosition(cam->pos);
    cameraSetRotation(cam->rot);
    cameraSetTargetPos(cam->targetPos);
    cameraSetTargetOfs(cam->targetOfs);
    cameraSetFov(cam->fov);
}

static void storeCamera(CAM_STORE* cam) {
    f32 pos[3];
    f32 rot[3];
    f32 targetPos[3];
    f32 targetOfs[3];
    f32 fov;
    f32 nearZ;
    f32 farZ;
    f32 aspect;

    cameraGetPosition(pos);
    cameraGetRotation(rot);
    cameraGetTargetPos(targetPos);
    cameraGetTargetOfs(targetOfs);
    GScameraGetPerspective(GScameraGetActiveCamera(), &fov, &nearZ, &farZ, &aspect);
    cam->pos[0] = pos[0];
    cam->pos[1] = pos[1];
    cam->pos[2] = pos[2];
    cam->rot[0] = rot[0];
    cam->rot[1] = rot[1];
    cam->rot[2] = rot[2];
    cam->targetPos[0] = targetPos[0];
    cam->targetPos[1] = targetPos[1];
    cam->targetPos[2] = targetPos[2];
    cam->targetOfs[0] = targetOfs[0];
    cam->targetOfs[1] = targetOfs[1];
    cam->targetOfs[2] = targetOfs[2];
    cam->fov = fov;
}

static void restoreSound(WORK* work) {
    if (work->bgmId != 0) {
        soundOpenPlay(work->bgmId, 0x32, (u8)work->bgmVolume);
        GSsndSetPushVolumeID(work->bgmId, &work->bgmPush);
    }
    if (work->envId != 0) {
        soundOpenPlayEnv(work->envId, 0x32, (u8)work->envVolume);
        GSsndSetPushVolumeID(work->envId, &work->envPush);
    }
}

static void stopSound(WORK* work) {
    s32 bgm;
    s32 env;
    s32 bgmVolume;
    s32 envVolume;

    bgm = soundGetBGMID();
    if (bgm != 0) {
        GSsndGetPushVolumeID(bgm, &work->bgmPush);
        bgmVolume = soundGetVolume(bgm);
        soundOpenPlay(8, 0x32, 0xFF);
    } else {
        bgmVolume = 0;
    }
    env = soundGetEnvID();
    if (env != 0) {
        GSsndGetPushVolumeID(env, &work->envPush);
        envVolume = soundGetVolume(env);
        soundStopEnv(0x32);
    } else {
        envVolume = 0;
    }
    work->bgmId = bgm;
    work->envId = env;
    work->bgmVolume = bgmVolume;
    work->envVolume = envVolume;
}

static u32 getPokemonData(Pokemon* pokemon) {
    if (pokemon == 0) {
        return 0;
    }
    if (pokemonCheckValid(pokemon) == 0) {
        return 0;
    }
    return pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(pokemon));
}

static u32 playPokemonVoice(Pokemon* pokemon) {
    u32 data = getPokemonData(pokemon);
    u16 voice;
    if (data == 0) {
        return 0;
    }
    voice = pokemonDataBiosGetVoice(data);
    GSsndPlayNow(voice);
    return voice;
}

static int dispMsgYesNo(unsigned long msg, EVOLUTION_WINDOW_TYPE type) {
    s32 answer;
    openMsgWin(msg, type);
    answer = getYesNo(type);
    closeMsgWin(type);
    switch (answer) {
    case 0:
        return 0;
    case 1:
        return 1;
    default:
        return 2;
    }
}

static int getYesNo(EVOLUTION_WINDOW_TYPE type) {
    if (type == EVOLUTION_WINDOW_FIELD) {
        return (s8)menuSubOpenYesNoField();
    }
    return (s8)menuSubOpenYesNo(0, -1, -1, 0);
}

static void dispMsg(unsigned long msg, EVOLUTION_WINDOW_TYPE type) {
    openMsgWin(msg, type);
    closeMsgWin(type);
}

static void closeMsgWin(EVOLUTION_WINDOW_TYPE type) {
    if (type == EVOLUTION_WINDOW_FIELD) {
        winMsgCloseField(1);
        return;
    }
    winMsgClose(1);
}

static void openMsgWin(unsigned long msg, EVOLUTION_WINDOW_TYPE type) {
    if (type == EVOLUTION_WINDOW_FIELD) {
        winMsgOpenField(msg, 1, 0);
        return;
    }
    winMsgOpen(2, msg, 1, 0);
}

static void waitTime(float seconds) {
    float elapsed = 0.0f;
    while (elapsed < 60.0f * seconds) {
        GSthreadSwitch();
        elapsed += (float)timeGetLastFrameTime();
    }
}

static u16 getPkxID(Pokemon* pokemon) {
    u16 id;
    u16 flag = pokemonGetStatus(pokemon, 0, 0x6E, 0);
    if (flag == 0) {
        return 0xFFFF;
    }
    id = pokemonGetStatus(0, flag, 0x66, 0);
    if (id != 0) {
        return id;
    }
    return 0xFFFF;
}

static u32 loadSequence(Pokemon* pokemon, int step) {
    const StepSeqEntry* entry;
    int i;
    u32 seq;
    u32 rnd;
    u16 pkx;

    pkx = getPkxID(pokemon);
    if (pkx == 0xFFFF) {
        return 0;
    }
    rnd = pokemonBiosGetRnd(pokemon);
    seq = Sequence_LoadPokemon(pkx, rnd, pokemonGetStatus(pokemon, 0, 0xC1, 0) != 0);
    if (seq == 0) {
        return 0;
    }
    for (i = 0, entry = StepSeqTbl; i < 5; i++, entry++) {
        if (step == entry->useAfter && Sequence_LoadWaza(seq, entry->seq, 4, 0) == 0) {
            break;
        }
    }
    if (i < 5) {
        return 0;
    }
    return seq;
}

static u8 loadSequenceAfter(WORK* work, Pokemon* pokemon) {
    u32 seq = loadSequence(pokemon, 1);
    if (seq == 0) {
        return 0;
    }
    work->seqAfter = seq;
    return 1;
}

static u8 loadSequenceBefore(WORK* work, Pokemon* pokemon) {
    u32 seq = loadSequence(pokemon, 0);
    if (seq == 0) {
        return 0;
    }
    work->seqBefore = seq;
    return 1;
}

static void toVisible(WORK* work, int after, int visible) {
    u32 seq;
    if (after != 0) {
        seq = work->seqAfter;
    } else {
        seq = work->seqBefore;
    }
    Sequence_SetVisibility(seq, visible != 0);
}

static int loadAll(WORK* work, Pokemon* before, Pokemon* after) {
    void* group = GSresGetResourceAllGroup(0x0FB31000, 0x0FB30000);
    if (group != 0) {
        GSmodelSetForceUseFractionalFramesFlag(group, 1);
        GSmodelSetSkipFractionalFramesFlag(group, 1);
    }
    work->seqBefore = 0;
    work->seqAfter = 0;
    if (loadSequenceBefore(work, before) != 0 && loadSequenceAfter(work, after) != 0) {
        return 1;
    }
    return 0;
}

extern "C" {

s32 evolutionWazaLearn(Pokemon* pokemon, u16 waza, u8* slot, EVOLUTION_WINDOW_TYPE type, s8 (*callback)(Pokemon*, unsigned short, long), WORK* work) {
    s32 idx;
    char* name;
    u16 wazaId;
    idx = 0;
    do {
        if (pokemonBiosGetPokemonWazaDataId(pokemon, idx) == 0) {
            break;
        }
        idx++;
    } while (idx < 4);
    if (idx >= 4) {
        name = pokemonBiosGetNicknamePtr(pokemon);
        msgctrlSetValue(0x32, (u32)name);
        wazaId = waza;
        msgctrlSetValue(0x39, wazaId);
        while (1) {
            if (dispMsgYesNo(0xC36A, type) == 0) {
                if (callback != 0) {
                    idx = callback(pokemon, waza, (long)work);
                } else {
                    idx = 0;
                }
                if (idx >= 0) {
                    goto learn;
                }
            }
            msgctrlSetValue(0x32, (u32)name);
            msgctrlSetValue(0x39, wazaId);
            if (dispMsgYesNo(0xC36B, type) == 0) {
                dispMsg(0xC36C, type);
                return 0;
            }
        }
learn:
        msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(pokemon));
        msgctrlSetValue(0x5D, 0x21);
        msgctrlSetValue(0x39, pokemonBiosGetPokemonWazaDataId(pokemon, idx));
        openMsgWin(0xC36D, type);
    }
    soundOpenPlayME(0x3C7, 0, 0xFF);
    msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(pokemon));
    msgctrlSetValue(0x39, waza);
    dispMsg(0xC36E, type);
    *slot = idx;
    return 1;
}

}

static s8 cbWazaForget(Pokemon* pokemon, unsigned short waza, long workPtr) {
    CAM_STORE cam;
    int slot;
    WORK* work = (WORK*)workPtr;

    fadeSet(3, 0.5f);
    fadeCheck(1);
    storeCamera(&cam);
    slot = menuPokemonStatusOpenWazaLearn(pokemon, waza);
    if (slot >= 4) {
        slot = -1;
    }
    loadSequenceAfter(work, pokemon);
    GSmodelSetAnimType(Sequence_GetGSmodel(work->seqAfter), 1);
    toVisible(work, 1, 1);
    restoreCamera(&cam);
    fadeSet(2, 0.5f);
    fadeCheck(1);
    return slot;
}

static int doWazaSequence(WORK* work, STEP step, int cancelable, FADE_CTRL fade) {
    CAM_STORE cam;
    int elapsed;
    int cancelled;
    u32 seq;
    u32 wazaSeq;

    elapsed = 0;
    cancelled = 0;

    if (step < 0 || step >= 5) {
        return 0;
    }
    if (StepSeqTbl[step].useAfter != 0) {
        seq = work->seqAfter;
    } else {
        seq = work->seqBefore;
    }
    wazaSeq = Sequence_GetWaza(seq, StepSeqTbl[step].seq, 4);
    WazaSequence_Start(wazaSeq, 1);
    while (cancelled == 0) {
        if (fade & 0xA) {
            u32 mode = 4;
            if (fade & 2) {
                mode = 2;
            }
            fadeSet(mode, 0.5f);
            fade = (FADE_CTRL)(fade & ~0xA);
        }
        if (WazaSequence_IsActive(wazaSeq) == 0) {
            break;
        }
        GSthreadSwitch();
        storeCamera(&cam);
        elapsed += timeGetLastFrameTime();
        if (cancelable != 0) {
            s32 changed = GSinputButtonsChanged(1);
            s32 pressed = GSinputButtonsPressed(1);
            if (pressed & changed & 0x200) {
                cancelled = 1;
            }
        }
    }
    restoreCamera(&cam);
    if (fade & 0x14) {
        u32 mode = 5;
        if (fade & 4) {
            mode = 3;
        }
        fadeSet(mode, 0.5f);
        fadeCheck(1);
    }
    WazaSequence_Free(wazaSeq);
    if (cancelled != 0) {
        return elapsed;
    }
    return -1;
}

static void wazaSeqEnd(WORK* work) {
    s32 step = work->step;
    WazaSequence_Free(Sequence_GetWaza(getStepSeq(work, (STEP)step), StepSeqTbl[step].seq, 4));
}

static int wazaSeqUpdate(WORK* work) {
    s32 step = work->step;
    return WazaSequence_IsActive(Sequence_GetWaza(getStepSeq(work, (STEP)step), StepSeqTbl[step].seq, 4)) != 0;
}

static u32 getStepSeq(WORK* work, STEP step) {
    if (StepSeqTbl[step].useAfter != 0) {
        return work->seqAfter;
    }
    return work->seqBefore;
}

static int wazaSeqStart(WORK* work, STEP step) {
    if (step < 0 || step >= 5) {
        return 0;
    }
    WazaSequence_Start(Sequence_GetWaza(getStepSeq(work, step), StepSeqTbl[step].seq, 4), 1);
    work->step = step;
    return 1;
}

static int evolutionDemo(WORK* work, int cancelable, Pokemon* before, Pokemon* after) {
    int firstFrame;
    u32 voice;
    u32 time;
    int cancelled;
    int phase;
    int counter;
    s32 changed;
    s32 pressed;
    char* name;

    toVisible(work, 0, 1);
    name = pokemonBiosGetNicknamePtr(before);
    msgctrlSetValue(0x32, (u32)name);
    openMsgWin(0xC419, EVOLUTION_WINDOW_FIELD);
    voice = playPokemonVoice(before);
    wazaSeqStart(work, STEP_0);
    firstFrame = 1;
    cancelled = 0;
    phase = 0;
    time = 0;
    while (time < 0x23A) {
        if (cancelable != 0 && time >= 0x78 && phase >= 2 && (changed = GSinputButtonsChanged(1), pressed = GSinputButtonsPressed(1), (pressed & changed & 0x200))) {
            cancelled = 1;
            break;
        } else if (wazaSeqUpdate(work) == 0) {
            break;
        }
        switch (phase) {
        case 0:
            if (GSsndGetStatus(voice) != 2) {
                soundOpenPlay(0x3D0, 0, 0xFF);
                counter = 0;
                phase = 1;
            }
            break;
        case 1:
            if (GSsndGetStatus(0x3D0) != 2) {
                counter += timeGetLastFrameTime();
                if (counter >= 0x1E) {
                    soundOpenPlay(0x3D1, 0, 0xFF);
                    phase = 2;
                }
            }
            break;
        }
        if (firstFrame != 0) {
            fadeSet(2, 0.5f);
            firstFrame = 0;
        }
        GSthreadSwitch();
        time += timeGetLastFrameTime();
    }
    fadeSet(5, 0.5f);
    while (fadeCheck(0) != 0) {
        wazaSeqUpdate(work);
        GSthreadSwitch();
    }
    wazaSeqEnd(work);
    waitTime(1.0f);
    if (cancelled != 0) {
        int idx;
        closeMsgWin(EVOLUTION_WINDOW_FIELD);
        soundStop(0x3D1, 0x32);
        idx = 0;
        if (CancelStep[0].time < time) {
            idx = 1;
            if (CancelStep[1].time < time) {
                idx = 2;
            }
        }
        doWazaSequence(work, (STEP)CancelStep[idx].step, 0, (FADE_CTRL)8);
        changed = playPokemonVoice(before);
        while (GSsndGetStatus(changed) == 2) {
            GSthreadSwitch();
        }
        msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(before));
        dispMsg(0xC41B, EVOLUTION_WINDOW_FIELD);
        fadeSet(3, 0.5f);
        fadeCheck(1);
        return 0;
    }
    toVisible(work, 0, 0);
    toVisible(work, 1, 1);
    doWazaSequence(work, STEP_1, 0, (FADE_CTRL)8);
    closeMsgWin(EVOLUTION_WINDOW_FIELD);
    soundStop(0x3D1, 0x32);
    changed = playPokemonVoice(after);
    while (GSsndGetStatus(changed) == 2) {
        GSthreadSwitch();
    }
    msgctrlSetValue(0x32, (u32)pokemonBiosGetNicknamePtr(before));
    u16 afterId = pokemonBiosGetPokemonDataId(after);
    msgctrlSetValue(0x4E, afterId);
    msgctrlSetValue(0x5D, 0x3CF);
    dispMsg(0xC41A, EVOLUTION_WINDOW_FIELD);
    waitTime(0.5f);
    return 1;
}

static int evolution__Main(WORK* work, int cancelable, Pokemon* before, Pokemon* after, unsigned short* wazaIds, long wazaCount, unsigned char* wazaSlots) {
    Pokemon copy;
    u8 slot;
    int i;
    int result;
    u16 waza;
    WORK* cbWork;

    stopSound(work);
    result = evolutionDemo(work, cancelable, before, after);
    restoreSound(work);
    if (result == 0) {
        return 0;
    }
    pokemonBiosCopy(&copy, after);
    cbWork = work;
    for (i = 0; i < wazaCount; i++) {
        waza = *wazaIds;
        if (evolutionWazaLearn(&copy, waza, &slot, EVOLUTION_WINDOW_FIELD, cbWazaForget, cbWork) != 0) {
            pokemonWazaCreate(&copy, slot, waza);
        } else {
            slot = -1;
        }
        wazaIds++;
        *wazaSlots = slot;
        wazaSlots++;
    }
    fadeSet(3, 0.5f);
    fadeCheck(1);
    return 1;
}

extern "C" {

s32 evolutionStart(Pokemon* before, Pokemon* after, s32 cancelable, u16* wazaIds, s32 wazaCount, u8* wazaSlots) {
    WORK work;
    wazaSequenceSysEnableLayerChange();
    if (loadAll(&work, before, after) == 0) {
        return 2;
    }
    s32 result = evolution__Main(&work, cancelable, before, after, wazaIds, wazaCount, wazaSlots);
    return (u32)__cntlzw(result) >> 5;
}

void evolution() {
    Parameter.result = evolutionStart(Parameter.before, Parameter.after, Parameter.canCancel, Parameter.wazaIds, Parameter.wazaCount, Parameter.wazaSlots);
    GSfloorPop();
    floorSetFadeScript(0, 0);
}

void evolutionExit() {
}

void evolutionMain() {
    evolution();
}

void evolutionInit() {
}

s32 evolutionOpen(Pokemon* before, Pokemon* after, s32 cancelable, u16* wazaIds, s32 wazaCount, u8* wazaSlots) {
    Parameter.before = before;
    Parameter.after = after;
    Parameter.canCancel = cancelable;
    Parameter.wazaCount = wazaCount;
    Parameter.wazaIds = wazaIds;
    Parameter.wazaSlots = wazaSlots;
    GSfloorPush(0x386);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    return Parameter.result;
}

}
