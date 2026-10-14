/* Debug menu entries for the sound test (BGM / SE / ENV / cries). */
#include <global.h>

extern s32 GSsndGetStatus(u16);
extern void GSsndClose(u16);
extern void GSsndSetMasterVolume(s32, s32, s32, s32);
extern void menuClose(s32);
extern s32 menuOpen(s32, s32);
extern void soundOpenPlay(u16, s32, s32);
extern void soundOpenPlayEnv(u16, s32, s32);

extern u16* snd_test_bgm;
extern u32* snd_test_bgm_number;
extern u16* snd_test_env;
extern u32* snd_test_env_number;
extern u16* snd_test_nakigoe;
extern u32* snd_test_nakigoe_number;
extern u16* snd_test_se;
extern u32* snd_test_se_number;

static void sndPlay(u16 id, s32 bgm);

s32 dbgMenuSoundTestChangeSE(s32 id) {
    switch (id) {
    case 0x155:
        GSsndSetMasterVolume(0x7F, 0, 0, 1);
        break;
    case 0x156:
        GSsndSetMasterVolume(0, 0, 0, 1);
        break;
    }
    return 0;
}

s32 dbgMenuSoundTestChangeBGM(s32 id) {
    switch (id) {
    case 0x153:
        GSsndSetMasterVolume(0x7F, 0, 1, 0);
        break;
    case 0x154:
        GSsndSetMasterVolume(0, 0, 1, 0);
        break;
    }
    return 0;
}

s32 dbgMenuSoundTestNAKIGOE(void) {
    s32 result;

    while ((result = menuOpen(2, 1)) != -1) {
        if ((u32)result < *snd_test_nakigoe_number) {
            sndPlay(snd_test_nakigoe[result], 0);
        }
    }
    menuClose(2);
    return -1;
}

s32 dbgMenuSoundTestSE(void) {
    s32 result;

    while ((result = menuOpen(2, 1)) != -1) {
        if ((u32)result < *snd_test_se_number) {
            sndPlay(snd_test_se[result], 0);
        }
    }
    menuClose(2);
    return -1;
}

s32 dbgMenuSoundTestENV(void) {
    s32 result;
    u32 i;
    s32 status;

    while ((result = menuOpen(2, 1)) != -1) {
        if ((u32)result < *snd_test_env_number) {
            for (i = 0; i < *snd_test_env_number; i++) {
                if (result != (s32)i) {
                    status = GSsndGetStatus(snd_test_env[i]);
                    switch (status) {
                    case 1:
                    case 2:
                    case 3:
                        GSsndClose(snd_test_env[i]);
                        break;
                    }
                }
            }
            sndPlay(snd_test_env[result], 0);
        }
    }
    menuClose(2);
    return -1;
}

s32 dbgMenuSoundTestBGM(void) {
    s32 result;
    u32 i;

    while ((result = menuOpen(2, 1)) != -1) {
        if ((u32)result < *snd_test_bgm_number) {
            for (i = 0; i < *snd_test_bgm_number; i++) {
                if (result != (s32)i) {
                    GSsndGetStatus(snd_test_bgm[i]);
                }
            }
            sndPlay(snd_test_bgm[result], 1);
        }
    }
    menuClose(2);
    return -1;
}

static void sndPlay(u16 id, s32 bgm) {
    s32 status = GSsndGetStatus(id);

    if (status != 0 && status >= 0 && status < 4) {
        GSsndClose(id);
    } else if (bgm != 0) {
        soundOpenPlay(id, 0, 0x7F);
    } else {
        soundOpenPlayEnv(id, 0, 0x7F);
    }
}
