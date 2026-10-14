#include <dolphin/os.h>
#include <game/agbCommunicationPrivate.hpp>

static AgbWork _gba_wk[4];
static char gba_filenames[0x100];
static u8 gba_pokemon_buf[4][0x278];
static OSAlarm _alarm;
static u8 gbainit_function_flag = 1;
static u8 *jbBuf1;
static u32 jbSize1;
static u32 _gameName;
static OSThread *_thread;

static void _AGB_Work_Clear(s32);
static void _job_type_clear(s32, const char *);
static void _timer_set(s32, u32);
static u32 SwapEndian(u32);
static u32 _PKJBUpGenerateKeyA();
static u32 _PKJBUpValidateKeyB(u32);
static void _AdjustGbaImageRegistry(u8 *, char *);
static void _ReadJBCode(const char *, u8 *, u32 *);
static u32 _PKJBUpCalcCrc(u32, u32);
static u32 _PKJBUpFindBootKey(u32, u32);
static s32 _AGB_SendWazaText(s32, u8 *);
static s32 _AGB_EntryRequest(s32, u32);
static s32 _AGB_BattleRequest(s32, const u8 *, int);
static s32 _AGB_EntryGetStatus(s32, u32 *);
static s32 _AGB_ReturnTitle(s32);
static s32 _AGB_ExchangeStart(s32, u8 *);
static s32 _AGB_ExchangeIsPrepared(s32);
static s32 _AGB_ExchangeEnd(s32);
static void _sleep_thread(int);
static void _alarm_handler(OSAlarm *, OSContext *);
static s32 _InitialExchange(s32);
static s32 _SendRecv(s32, u32, u32 *);
static s32 _GBATimerRead(s32, u8 *, u8 *, int);
static s32 _BulkSend(s32, const u8 *, int);
static s32 _BulkSend2(s32, const u8 *, int);
static void _upload_01(s32, s32);
static void _upload_02(s32, s32);
static void _upload_03(s32, s32);
static void _upload_04(s32, s32);
static void _upload_05(s32, s32);
static void _upload_06(s32, s32);
static void _upload_07(s32, s32);
static void _upload_08(s32, s32);
static void _upload_09(s32, s32);
static void _upload_10(s32, s32);
static void _upload_11(s32, s32);
static void _upload_11s(s32, s32);
static void _upload_12(s32, s32);
static void _upload_12s(s32, s32);
static void _upload_13(s32, s32);
static void _upload_13s(s32, s32);
static void _upload_14(s32, s32);
static void _upload_15(s32, s32);
static void _upload_16(s32, s32);
static void _upload_17(s32, s32);
static void _upload_17s(s32, s32);
static void _upload_18(s32, s32);
static void _upload_19(s32, s32);
static void _upload_20(s32, s32);
static void _upload_21(s32, s32);
static void _upload_21s(s32, s32);
static void _upload_22(s32, s32);
static void _upload_23(s32, s32);
static void _upload_23s(s32, s32);
static void _upload_24(s32, s32);
static void _upload_25(s32, s32);
static void _getpokemon_01(s32, s32);
static void _getpokemon_01s(s32, s32);
static void _getpokemon_02(s32, s32);
static void _getpokemon_03(s32, s32);
static void _getpokemon_04(s32, s32);
static void _getpokemon_05(s32, s32);
static void _getpokemon_05s(s32, s32);
static void _getpokemon_06(s32, s32);
static void _getpokemon_07(s32, s32);
static void _getpokemon_07s(s32, s32);
static void _getpokemon_08(s32, s32);
static void _getpokemon_09(s32, s32);
static void _getpokemon_10(s32, s32);
static void _upload_00s(s32, s32);
static void _upload_16s(s32, s32);
static void _upload_16s0(s32, s32);
static void _getpokemon_11(s32, s32);
static void _getpokemon_09s(s32, s32);

static s32 AGB_Initialize(s32 chan) {
    if (chan < 0 || chan > 3) return 0;
    if (_gba_wk[chan].active != 0) return 0;
    _AGB_Work_Clear(chan);
    _gba_wk[chan].active = 0;
    return 1;
}

extern "C" {
void AGB_Terminate_init() {
    s32 i = 0;
    for (; i < 4; ++i) {
        _AGB_Work_Clear(i);
        _job_type_clear(i, __FUNCTION__);
    }
}

s32 AGB_Terminate(s32 chan) {
    if (chan < 0 || chan > 3) return 0;
    _gba_wk[chan].busy = 0;
    _gba_wk[chan].status = 0;
    _gba_wk[chan].job = 0;
    if (_gba_wk[chan].active != 0) _gba_wk[chan].status = 4;
    _job_type_clear(chan, __FUNCTION__);
    return 1;
}

s32 AGB_GetStatus(s32 chan) {
    if (chan < 0 || chan > 3) return 1;
    return _gba_wk[chan].status;
}

u8 AGB_IsComplete(s32 chan) {
    if (chan < 0 || chan > 3) return 0;
    if (_gba_wk[chan].active != 0) {
        switch (_gba_wk[chan].job) {
        case 1:
            _upload_00s(chan, 0);
            break;
        case 2:
            _upload_16s0(chan, 0);
            break;
        case 3:
            _upload_16s(chan, 0);
            break;
        }
    }
    return _gba_wk[chan].active == 0;
}
}

static void _AGB_Work_Clear(s32 chan) {
    _gba_wk[chan].w1c = 0;
    _gba_wk[chan].w20 = 0;
    _gba_wk[chan].w24 = 0;
    _gba_wk[chan].w28 = 0;
    _gba_wk[chan].w2c = 0;
    _gba_wk[chan].w30 = 0;
    _gba_wk[chan].w34 = 0;
    _gba_wk[chan].w38 = 0;
    _gba_wk[chan].w3c = 0;
    _gba_wk[chan].w40 = 0;
    _gba_wk[chan].w44 = 0;
    _gba_wk[chan].w48 = 0;
    _gba_wk[chan].w4c = 0;
    _gba_wk[chan].w50 = 0;
    _gba_wk[chan].w54 = 0;
    _gba_wk[chan].w58 = 0;
    _gba_wk[chan].t0 = 0;
    _gba_wk[chan].len0 = 0;
    _gba_wk[chan].t1 = 0;
    _gba_wk[chan].len1 = 0;
    _gba_wk[chan].t2 = 0;
    _gba_wk[chan].len2 = 0;
    _gba_wk[chan].w84 = 0;
    _gba_wk[chan].w88 = 0;
    _gba_wk[chan].idx = 0;
    _gba_wk[chan].w60 = 0;
    _gba_wk[chan].w64 = 0;
    _gba_wk[chan].w68 = 0;
    _gba_wk[chan].busy = 0;
    _gba_wk[chan].status = 0;
    _gba_wk[chan].job = 0;
}

static void _job_type_clear(s32 chan, const char *) {
    _gba_wk[chan].busy = 0;
    _gba_wk[chan].active = 0;
    _gba_wk[chan].job = 0;
}

static void _timer_set(s32 chan, u32 ms) {
    _gba_wk[chan].len0 = ms * (AGB_TIMER_CLOCK / 1000);
    _gba_wk[chan].t0 = OSGetTick();
}

static u32 SwapEndian(u32 v) {
    return (v >> 24) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 24);
}

static u32 _PKJBUpGenerateKeyA() {
    u32 tries = 0;
    u32 key;
    u32 k;
    s32 j;
    u32 cnt;
    do {
        if (tries > 0x20) {
            key = 0xDD654321;
        } else {
            key = (OSGetTick() & 0xFFFFFF) | 0xDD000000;
        }
        k = key;
        cnt = 0;
        for (j = 0; j < 32; ++j) {
            if (k & 1) ++cnt;
            k >>= 1;
        }
        ++tries;
    } while (cnt < 10 || cnt > 24);
    return key;
}

static u32 _PKJBUpValidateKeyB(u32 key) {
    u32 masked;
    s32 j;
    u32 cnt;
    if ((key & 0xFF) != 0xEE) {
        OSReport("_PKJBUpValidateKeyB: invalid key (d7-d0): 0x%x\n", key);
        return 0;
    }
    masked = key & 0xFFFFFF00;
    cnt = 0;
    for (j = 0; j < 24; ++j) {
        if (key & 0x80000000) ++cnt;
        key <<= 1;
    }
    if (cnt < 7 || cnt > 14) {
        OSReport("_PKJBUpValidateKeyB: invalid key (d31-d8): 0x%x\n", masked);
        return 0;
    }
    return masked;
}

static void _AdjustGbaImageRegistry(u8 *img, char *name) {
    s32 i;
    s32 sum;
    img[0xAC] = name[0];
    img[0xAD] = name[1];
    img[0xAE] = name[2];
    img[0xAF] = name[3];
    sum = 0xE7;
    for (i = 0xA0; i < 0xBD; ++i) sum -= img[i];
    img[i] = sum;
}

static void _ReadJBCode(const char *name, u8 *buf, u32 *size) {
    GSdvdWork *file = GSdvdOpen(name);
    if (file == 0) return;
    *size = GSdvdGetLength(file);
    if (*size == 0 || *size > 0x20000) return;
    *size = (*size + 0x1F) & ~0x1F;
    if (GSdvdReadAsync(file, buf, *size, 0, 0) != 0) {
        do {
            GSthreadSwitch();
        } while (GSdvdGetFileInfoStatus(file) != 0);
        GSdvdClose(file);
        _AdjustGbaImageRegistry(buf, (char *)&_gameName);
    }
}


static u32 _PKJBUpCalcCrc(u32 a, u32 b) {
    s32 i;
    a ^= b;
    for (i = 32; i > 0; --i) {
        if (a & 1) {
            a >>= 1;
            a ^= 0xA1C1;
        } else {
            a >>= 1;
        }
    }
    return a;
}

static u32 _PKJBUpFindBootKey(u32 recv, u32 seed) {
    u32 i; u32 k;
    OSReport("from GBA recvData = 0x%08x, GC resultCrc = 0x%08x\n", recv, seed);
    for (i = 0; i < 0x100; ++i) {
        k = (i << 24) - 1;
        if ((recv >> 8) == _PKJBUpCalcCrc(k, seed)) {
            u32 boot = _PKJBUpCalcCrc(k, 0xBB) | 0xBB000000;
            OSReport("KeyC found! 0x%08x, return bootKey = 0x%08x\n", k, boot);
            return boot;
        }
    }
    OSReport("*************** ERROR: KeyC NOT FOUND 0x%08x, 0x%08x ***************\n", recv, seed);
    return 0;
}





extern "C" {
s32 PKJB_GetKey(s32 chan, u16 *key) {
    u32 recv;
    s32 ret = _InitialExchange(chan);
    if (ret != 0) return ret;
    ret = _SendRecv(chan, 0xAA, &recv);
    if (ret != 0) return ret;
    if ((recv >> 24) != 0xAA) return 0xF;
    *key = SwapEndian(recv) >> 16;
    return 0;
}

s32 PKJB_IdleSend(s32 chan) {
    u8 status;
    u32 cmd;
    if (gba_SIProbe(chan) != 0x40000) return 1;
    cmd = 0x11;
    if (GBAWrite(chan, (u8 *)&cmd, &status) != 0) return 2;
    return 0;
}

s32 PKJB_SendWazaText(s32 chan, u8 *text) {
    s32 ret;
    s32 key = chan + 1;
    gbaCommandSetKeyState(key, 2);
    ret = _AGB_SendWazaText(chan, text);
    gbaCommandSetKeyState(key, 1);
    return ret;
}
}

static s32 _AGB_SendWazaText(s32 chan, u8 *text) {
    u32 recv;
    s32 ret;
    s32 timedout;
    u32 limit = AGB_MSEC_TO_TICKS(5);
    u32 start = OSGetTick();
    do {
        timedout = (OSGetTick() - start) > limit;
        ret = _InitialExchange(chan);
    } while (ret == 1 && !timedout);
    if (ret != 0) return ret;
    ret = _SendRecv(chan, 0x88, &recv);
    if (ret != 0) return ret;
    if ((recv >> 24) != 0x88) return 0xF;
    return _BulkSend2(chan, text, 0x780);
}

extern "C" {
s32 PKJB_EntryRequest(s32 chan, u32 value) {
    s32 timedout;
    u32 start;
    s32 key = chan + 1;
    s32 ret;
    u32 limit;
    gbaCommandSetKeyState(key, 2);
    limit = AGB_MSEC_TO_TICKS(100);
    start = OSGetTick();
    do {
        timedout = (OSGetTick() - start) > limit;
        ret = _AGB_EntryRequest(chan, value);
    } while (ret == 1 && !timedout);
    gbaCommandSetKeyState(key, ret != 0 ? 1 : 3);
    return ret;
}
}

static s32 _AGB_EntryRequest(s32 chan, u32 value) {
    u8 status;
    u32 recv;
    u32 data;
    u32 limit;
    u32 start;
    s32 ret = _InitialExchange(chan);
    if (ret != 0) return ret;
    data = 0x77;
    ret = _SendRecv(chan, data, &recv);
    if (ret != 0) return ret;
    if ((recv >> 24) != 0x77) return 0xF;
    data = SwapEndian(value);
    GBAWrite(chan, (u8 *)&data, &status);
    limit = AGB_MSEC_TO_TICKS(100);
    start = OSGetTick();
    do {
        if (OSGetTick() - start > limit) return 0x10;
        if (GBAGetStatus(chan, &status) != 0) return 0x11;
    } while (status & 2);
    return 0;
}

extern "C" {
s32 PKJB_BattleRequest(s32 chan, const u8 *data, int len) {
    s32 timedout;
    u32 start;
    s32 key = chan + 1;
    s32 ret;
    u32 limit;
    gbaCommandSetKeyState(key, 2);
    limit = AGB_MSEC_TO_TICKS(100);
    start = OSGetTick();
    do {
        timedout = (OSGetTick() - start) > limit;
        ret = _AGB_BattleRequest(chan, data, len);
    } while (ret == 1 && !timedout);
    gbaCommandSetKeyState(key, ret != 0 ? 1 : 3);
    return ret;
}


}

static s32 _AGB_BattleRequest(s32 chan, const u8 *data, int len) {
    u32 recv;
    s32 ret = _InitialExchange(chan);
    if (ret != 0) return ret;
    ret = _SendRecv(chan, 0x66, &recv);
    if (ret != 0) return ret;
    if ((recv >> 24) != 0x66) return 0xF;
    return _BulkSend2(chan, data, len);
}

extern "C" {
s32 PKJB_EntryGetStatus(s32 chan, u32 *out) {
    return _AGB_EntryGetStatus(chan, out);
}
}

static s32 _AGB_EntryGetStatus(s32 chan, u32 *out) {
    u8 status;
    u32 cmd;
    u32 recv;
    if (gba_SIProbe(chan) != 0x40000) return 1;
    if (GBAGetStatus(chan, &status) != 0) return 2;
    if ((status & 8) == 0) {
        cmd = 0x11;
        GBAWrite(chan, (u8 *)&cmd, &status);
        return -1;
    }
    if (GBARead(chan, (u8 *)&recv, &status) != 0) return 3;
    *out = recv;
    return 0;
}

extern "C" {
s32 PKJB_BattleGetStatus(s32 chan, u32 *out) {
    s32 ret = _AGB_EntryGetStatus(chan, out);
    if (ret >= 0) gbaCommandSetKeyState(chan + 1, 1);
    return ret;
}

s32 PKJB_ReturnTitle(s32 chan) {
    s32 ret;
    s32 key = chan + 1;
    gbaCommandSetKeyState(key, 2);
    ret = _AGB_ReturnTitle(chan);
    gbaCommandSetKeyState(key, 1);
    return ret;
}
}

static s32 _AGB_ReturnTitle(s32 chan) {
    u8 status;
    u16 key;
    u32 cmd;
    u32 limit;
    u32 start;
    s32 ret;
    s32 keyRet;
    ret = _InitialExchange(chan);
    if (ret != 0) return ret;
    cmd = 0x60;
    ret = GBAWrite(chan, (u8 *)&cmd, &status);
    if (ret != 0) return 0xB;
    limit = AGB_SEC_TO_TICKS(3);
    start = OSGetTick();
    do {
        if (OSGetTick() - start > limit) return 0x10;
        keyRet = PKJB_GetKey(chan, &key);
        GSthreadSwitch();
    } while (keyRet != 0);
    return ret;
}

static s32 _InitialExchange(s32 chan) {
    u8 status;
    u32 data;
    u32 limit;
    u32 start;
    s32 ret;
    if (gba_SIProbe(chan) != 0x40000) return 1;
    if (GBAReset(chan, &status) != 0) return 2;
    ret = _GBATimerRead(chan, (u8 *)&data, &status, 100);
    if (ret != 0) return ret + 2;
    if (data != _gameName) return 6;
    if (GBAGetStatus(chan, &status) != 0) return 7;
    if (GBAWrite(chan, (u8 *)&data, &status) != 0) return 8;
    limit = AGB_MSEC_TO_TICKS(100);
    start = OSGetTick();
    do {
        if (OSGetTick() - start > limit) return 9;
        if (GBAGetStatus(chan, &status) != 0) return 10;
    } while (status & 2);
    return 0;
}

static s32 _GBATimerRead(s32 chan, u8 *dst, u8 *status, int ms) {
    u8 st;
    u32 limit = AGB_MSEC_TO_TICKS(ms);
    u32 start = OSGetTick();
    for (;;) {
        if (OSGetTick() - start > limit) return 1;
        if (GBAGetStatus(chan, &st) != 0) return 2;
        if ((st & 0xA) == 8) break;
    }
    if (GBARead(chan, dst, status) != 0) return 3;
    return 0;
}

static s32 _SendRecv(s32 chan, u32 send, u32 *recv) {
    u8 status;
    s32 ret;
    if (GBAWrite(chan, (u8 *)&send, &status) != 0) return 0xB;
    ret = _GBATimerRead(chan, (u8 *)recv, &status, 100);
    if (ret != 0) return ret + 0xB;
    return 0;
}

static s32 _BulkSend(s32 chan, const u8 *data, int len) {
    u8 status;
    u32 word;
    u32 limit;
    s32 i;
    u32 start;
    for (i = 0; i < len; i += 4) {
        word = *(const u32 *)(data + i);
        if (GBAWrite(chan, (u8 *)&word, &status) != 0) return 0x10;
        limit = AGB_MSEC_TO_TICKS(100);
        start = OSGetTick();
        do {
            if (OSGetTick() - start > limit) return 0x11;
            if (GBAGetStatus(chan, &status) != 0) return 0x12;
        } while (status & 2);
    }
    return 0;
}




static s32 _BulkSend2(s32 chan, const u8 *data, int len) {
    u8 status;
    u32 word;
    s32 i;
    u32 limit;
    u32 start;
    for (i = 0; i < len; i += 4) {
        word = *(const u32 *)(data + i);
        if (GBAWrite(chan, (u8 *)&word, &status) != 0) return 0x10;
        limit = AGB_MSEC_TO_TICKS(100);
        start = OSGetTick();
        do {
            if (OSGetTick() - start > limit) return 0x11;
            if (GBAGetStatus(chan, &status) != 0) return 0x12;
        } while (status & 2);
        if (i % 64 == 0) GSthreadSwitch();
    }
    return 0;
}


extern "C" {
s32 PKJB_ExchangeStart(s32 chan, u8 *data) {
    s32 timedout;
    u32 start;
    s32 key = chan + 1;
    s32 ret;
    u32 limit;
    gbaCommandSetKeyState(key, 2);
    limit = AGB_MSEC_TO_TICKS(100);
    start = OSGetTick();
    do {
        timedout = (OSGetTick() - start) > limit;
        ret = _AGB_ExchangeStart(chan, data);
    } while (ret == 1 && !timedout);
    gbaCommandSetKeyState(key, ret != 0 ? 1 : 3);
    return ret;
}
}

static s32 _AGB_ExchangeStart(s32 chan, u8 *data) {
    u32 recv;
    s32 ret;
    u32 limit = AGB_MSEC_TO_TICKS(100);
    u32 start = OSGetTick();
    for (;;) {
        if (OSGetTick() - start > limit) return 1;
        if (gba_SIProbe(chan) == 0x40000) break;
    }
    ret = _InitialExchange(chan);
    if (ret != 0) return ret;
    ret = _SendRecv(chan, 0x55, &recv);
    if (ret != 0) return ret;
    if ((recv >> 24) != 0x55) return 0xF;
    _BulkSend(chan, data, 0x78);
    return 0;
}

static void _alarm_handler(OSAlarm *, OSContext *) {
    OSResumeThread(_thread);
}

static void _sleep_thread(int ms) {
    BOOL enabled;
    _thread = OSGetCurrentThread();
    OSCreateAlarm(&_alarm);
    enabled = OSDisableInterrupts();
    OSSetAlarm(&_alarm, AGB_MSEC_TO_TICKS(ms), _alarm_handler);
    OSSuspendThread(_thread);
    OSRestoreInterrupts(enabled);
}

extern "C" {
s32 PKJB_ExchangeIsPrepared(s32 chan) {
    s32 ret = _AGB_ExchangeIsPrepared(chan);
    if (ret == 0 || ret >= 3) gbaCommandSetKeyState(chan + 1, 1);
    return ret;
}
}

static s32 _AGB_ExchangeIsPrepared(s32 chan) {
    u8 status;
    u32 recv;
    _sleep_thread(1);
    if (gba_SIProbe(chan) != 0x40000) return 1;
    if (GBAGetStatus(chan, &status) != 0) return 2;
    if ((status & 8) == 0) return -1;
    if (GBARead(chan, (u8 *)&recv, &status) != 0) return 3;
    if (recv != 0) return 4;
    return 0;
}

extern "C" {
s32 PKJB_ExchangeEnd(s32 chan) {
    s32 ret;
    s32 key = chan + 1;
    gbaCommandSetKeyState(key, 2);
    ret = _AGB_ExchangeEnd(chan);
    gbaCommandSetKeyState(key, 1);
    return ret;
}
}

static s32 _AGB_ExchangeEnd(s32 chan) {
    u8 status;
    u32 recv;
    s32 ret = _InitialExchange(chan);
    if (ret != 0) return ret;
    ret = _SendRecv(chan, 0x44, &recv);
    if (ret != 0) return ret;
    if ((recv >> 24) != 0x44) return 0xF;
    ret = _GBATimerRead(chan, (u8 *)&recv, &status, 30000);
    if (ret != 0) return ret + 0xF;
    if (recv != 0) return 0x13;
    return 0;
}

extern "C" {
s32 AGB_Prepare(const char *name) {
    if (strlen(name) >= 0x7F) return 0;
    strcpy(gba_filenames, name);
    DVDDiskID *id = DVDGetCurrentDiskID();
    memcpy(&_gameName, id, 4);
    if (gbainit_function_flag) {
        GBAInit();
        gbainit_function_flag = 0;
    }
    _ReadJBCode(name, jbBuf1, &jbSize1);
    return 1;
}


s32 AGB_Upload(s32 chan, s32 flag) {
    if (!AGB_Initialize(chan)) return 0;
    _AGB_Work_Clear(chan);
    _gba_wk[chan].active = 2;
    _gba_wk[chan].status = 3;
    _gba_wk[chan].busy = 1;
    if (flag == 0) {
        _gba_wk[chan].len1 = AGB_SEC_TO_TICKS(7);
    } else {
        _gba_wk[chan].len1 = AGB_SEC_TO_TICKS(7);
    }
    _gba_wk[chan].t1 = OSGetTick();
    _gba_wk[chan].size = jbSize1;
    _gba_wk[chan].buf = jbBuf1;
    gbaCommandSetKeyState(chan + 1, 0);
    _upload_00s(chan, 0);
    return 1;
}
}

#define UP_RETRY(c) _gba_wk[c].job = 1
#define UP_FAIL(c) \
    _job_type_clear(c, __FUNCTION__); \
    _gba_wk[c].status = 1
#define GP_FAIL(c) \
    _job_type_clear(c, __FUNCTION__); \
    _gba_wk[c].status = 1; \
    gbaCommandSetKeyState((c) + 1, 1)

static void _upload_00s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 10000;
        _gba_wk[chan].job = 0;
        _gba_wk[chan].ret = SIProbe(chan);
        if (_gba_wk[chan].ret == 0x40000) {
            _gba_wk[chan].ret = GBAResetAsync(chan, &_gba_wk[chan].gbaStatus, _upload_01);
            if (_gba_wk[chan].ret == 2) _gba_wk[chan].job = 1;
        } else if (OSGetTick() - _gba_wk[chan].t1 >= _gba_wk[chan].len1) {
            _job_type_clear(chan, __FUNCTION__);
            _gba_wk[chan].status = 2;
        } else {
            _gba_wk[chan].job = 1;
        }
    }
}

static void _upload_01(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 1;
        if (ret == 1) {
fail:
            UP_RETRY(chan);
        } else {
            _timer_set(chan, 0x7D);
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_02);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_02(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 2;
        if (ret == 1) {
fail:
            UP_RETRY(chan);
        } else if (_gba_wk[chan].gbaStatus == 0x18) {
            _gba_wk[chan].ret = GBAReadAsync(chan, (u8 *)&_gba_wk[chan].w38, &_gba_wk[chan].gbaStatus, _upload_03);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
            goto fail;
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_02);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_03(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 3;
        if (ret == 1) {
fail:
            UP_RETRY(chan);
        } else if (_gba_wk[chan].w38 != 0x4158564A && _gba_wk[chan].w38 != 0x41585645) {
            if (OSGetTick() - _gba_wk[chan].t1 < _gba_wk[chan].len1) {
                goto fail;
            } else {
                _job_type_clear(chan, __FUNCTION__);
                _gba_wk[chan].status = 2;
            }
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_04);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_04(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 4;
        if (ret == 1) {
fail:
            UP_RETRY(chan);
        } else if (_gba_wk[chan].gbaStatus != 0x10) {
            goto fail;
        } else {
            _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&_gba_wk[chan].w38, &_gba_wk[chan].gbaStatus, _upload_05);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_05(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 5;
        if (ret == 1) {
fail:
            UP_RETRY(chan);
        } else {
            _timer_set(chan, 0x7D);
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_06);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_06(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 6;
        if (ret == 1) {
fail:
            UP_RETRY(chan);
        } else if ((_gba_wk[chan].gbaStatus & 0x30) != 0x10) {
            goto fail;
        } else {
            if ((_gba_wk[chan].gbaStatus & 2) == 0) {
                _gba_wk[chan].w38 = _PKJBUpGenerateKeyA();
                _gba_wk[chan].w1c = SwapEndian(_gba_wk[chan].w38);
                _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&_gba_wk[chan].w1c, &_gba_wk[chan].gbaStatus, _upload_07);
                if (_gba_wk[chan].ret == 2) {
                    UP_FAIL(chan);
                    return;
                }
            }
            if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
                goto fail;
            } else {
                _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_06);
                if (_gba_wk[chan].ret == 2) {
                    goto fail;
                }
            }
        }
    }
}

static void _upload_07(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 7;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else {
            _timer_set(chan, 0x7D);
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_08);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_08(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 8;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else if (_gba_wk[chan].gbaStatus == 0x38) {
            _gba_wk[chan].ret = GBAReadAsync(chan, (u8 *)&_gba_wk[chan].w34, &_gba_wk[chan].gbaStatus, _upload_09);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
            goto fail;
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_08);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_09(s32 chan, s32 ret) {
    u32 size;
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 9;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else {
            _gba_wk[chan].w30 = _PKJBUpValidateKeyB(SwapEndian(_gba_wk[chan].w34));
            if (_gba_wk[chan].w30 == 0) {
                goto fail;
            } else {
                size = (_gba_wk[chan].size + 7) & ~7;
                _gba_wk[chan].size = size;
                size = SwapEndian((size >> 3) - 1);
                _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&size, &_gba_wk[chan].gbaStatus, _upload_10);
                if (_gba_wk[chan].ret == 2) {
                    goto fail;
                }
            }
        }
    }
}

static void _upload_10(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 10;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else {
            _timer_set(chan, 0x7D);
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_11);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_11(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 11;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else if ((_gba_wk[chan].gbaStatus & 0x30) != 0x30) {
            goto fail;
        } else if ((_gba_wk[chan].gbaStatus & 2) == 0) {
            _gba_wk[chan].w28 = _gba_wk[chan].w38 ^ _gba_wk[chan].w30;
            _gba_wk[chan].w24 = (_gba_wk[chan].w38 ^ _gba_wk[chan].w30) * 0x6177614B + 1;
            _gba_wk[chan].w20 = 0x30;
            _gba_wk[chan].idx = 0;
            _upload_11s(chan, ret);
        } else if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
            goto fail;
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_11);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_11s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3F3;
        _gba_wk[chan].w60 = SwapEndian(*(u32 *)(_gba_wk[chan].buf + _gba_wk[chan].idx));
        if (_gba_wk[chan].idx >= 0xA0) {
            _gba_wk[chan].w64 = _gba_wk[chan].w60;
            _gba_wk[chan].w60 = _gba_wk[chan].w60 - _gba_wk[chan].w28;
            _gba_wk[chan].w60 = _gba_wk[chan].w60 ^ _gba_wk[chan].w24;
            _gba_wk[chan].w28 = _PKJBUpCalcCrc(_gba_wk[chan].w28, _gba_wk[chan].w64);
            _gba_wk[chan].w24 = _gba_wk[chan].w24 * 0x6177614B + 1;
        }
        _gba_wk[chan].w2c = SwapEndian(_gba_wk[chan].w60);
        for (;;) {
            _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&_gba_wk[chan].w2c, &_gba_wk[chan].gbaStatus, _upload_12);
            if (_gba_wk[chan].ret != 2) break;
            if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
                UP_FAIL(chan);
                break;
            }
        }
    }
}

static void _upload_12(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 12;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else if ((_gba_wk[chan].gbaStatus & 0x30) != _gba_wk[chan].w20) {
            goto fail;
        } else {
            _gba_wk[chan].w20 ^= 0x10;
            _timer_set(chan, 0x7D);
            _upload_12s(chan, ret);
        }
    }
}

static void _upload_12s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3F4;
        do {
            if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
                UP_FAIL(chan);
                break;
            }
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_13);
        } while (_gba_wk[chan].ret == 2);
    }
}

static void _upload_13(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 13;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else if ((_gba_wk[chan].gbaStatus & 0x20) == 0) {
            goto fail;
        } else if ((_gba_wk[chan].gbaStatus & 2) == 0) {
            _gba_wk[chan].idx += 4;
            if (_gba_wk[chan].idx < _gba_wk[chan].size) {
                _upload_11s(chan, ret);
            } else {
                _gba_wk[chan].len0 = AGB_SEC_TO_TICKS(10);
                _gba_wk[chan].t0 = OSGetTick();
                _upload_13s(chan, ret);
            }
        } else {
            _upload_12s(chan, ret);
        }
    }
}

static void _upload_13s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3F5;
        if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
fail:
            UP_FAIL(chan);
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_14);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_14(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 14;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else if ((_gba_wk[chan].gbaStatus & 0x30) != 0x30) {
            goto fail;
        } else if ((_gba_wk[chan].gbaStatus & 0xA) == 8) {
            _gba_wk[chan].ret = GBAReadAsync(chan, (u8 *)&_gba_wk[chan].w2c, &_gba_wk[chan].gbaStatus, _upload_15);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else {
            _upload_13s(chan, ret);
        }
    }
}

static void _upload_15(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 15;
        if (ret == 1) {
fail:
            UP_FAIL(chan);
        } else if ((_gba_wk[chan].w2c >> 24) == 0xFF) {
            _gba_wk[chan].w34 = _PKJBUpFindBootKey(SwapEndian(_gba_wk[chan].w2c), _gba_wk[chan].w28);
            if (_gba_wk[chan].w34 == 0) {
                goto fail;
            } else {
                _gba_wk[chan].w34 = SwapEndian(_gba_wk[chan].w34);
                _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&_gba_wk[chan].w34, &_gba_wk[chan].gbaStatus, _upload_16);
                if (_gba_wk[chan].ret == 2) {
                    goto fail;
                }
            }
        } else if ((_gba_wk[chan].w2c >> 24) == 0xCC) {
            _upload_13s(chan, ret);
        } else {
            goto fail;
        }
    }
}

static void _upload_16(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 16;
        if (ret == 1) {
            UP_FAIL(chan);
        } else {
            _gba_wk[chan].len0 = AGB_TIMER_CLOCK;
            _gba_wk[chan].t0 = OSGetTick();
            _upload_16s0(chan, ret);
        }
    }
}

static void _upload_16s0(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0xD8;
        _gba_wk[chan].job = 0;
        if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
            UP_FAIL(chan);
        } else {
            _gba_wk[chan].ret = SIProbe(chan);
            if (_gba_wk[chan].ret != 0x40000) {
                _gba_wk[chan].len2 = AGB_TIMER_CLOCK << 3;
                _gba_wk[chan].t2 = OSGetTick();
                _gba_wk[chan].ret = GBAResetAsync(chan, &_gba_wk[chan].gbaStatus, _upload_17);
                if (_gba_wk[chan].ret == 2) {
                    _upload_16s(chan, ret);
                }
            } else {
                _gba_wk[chan].job = 2;
            }
        }
    }
}

static void _upload_16s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3F8;
        _gba_wk[chan].job = 0;
        if (OSGetTick() - _gba_wk[chan].t2 > _gba_wk[chan].len2) {
            UP_FAIL(chan);
        } else {
            _gba_wk[chan].ret = SIProbe(chan);
            if (_gba_wk[chan].ret != 0x40000) {
                _gba_wk[chan].job = 3;
            } else {
                _gba_wk[chan].ret = GBAResetAsync(chan, &_gba_wk[chan].gbaStatus, _upload_17);
                if (_gba_wk[chan].ret == 2) {
                    _gba_wk[chan].job = 3;
                }
            }
        }
    }
}

static void _upload_17(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 17;
        if (ret == 1) {
            _upload_16s(chan, ret);
        } else {
            _gba_wk[chan].w44 = 5;
            _gba_wk[chan].len1 = (AGB_TIMER_CLOCK / 1000) * _gba_wk[chan].w44;
            _gba_wk[chan].t1 = OSGetTick();
            _upload_17s(chan, ret);
        }
    }
}

static void _upload_17s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3F9;
        if (OSGetTick() - _gba_wk[chan].t1 > _gba_wk[chan].len1) {
fail:
            _upload_16s(chan, ret);
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_18);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_18(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 18;
        if (ret == 1) {
fail:
            _upload_16s(chan, ret);
        } else if ((_gba_wk[chan].gbaStatus & 0xA) == 8) {
            _gba_wk[chan].ret = GBAReadAsync(chan, (u8 *)&_gba_wk[chan].w40, &_gba_wk[chan].gbaStatus, _upload_19);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else {
            _upload_17s(chan, ret);
        }
    }
}

static void _upload_19(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 19;
        if (ret == 1) {
fail:
            _upload_16s(chan, ret);
        } else if (_gameName != _gba_wk[chan].w40) {
            goto fail;
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_20);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_20(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 20;
        if (ret == 1) {
fail:
            _upload_16s(chan, ret);
        } else {
            _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&_gba_wk[chan].w40, &_gba_wk[chan].gbaStatus, _upload_21);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_21(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 21;
        if (ret == 1) {
            _upload_16s(chan, ret);
        } else {
            _timer_set(chan, 0x7D);
            _upload_21s(chan, ret);
        }
    }
}

static void _upload_21s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3FD;
        if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
fail:
            _upload_16s(chan, ret);
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_22);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_22(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 22;
        if (ret == 1) {
fail:
            _upload_16s(chan, ret);
        } else if ((_gba_wk[chan].gbaStatus & 2) == 0) {
            _gba_wk[chan].w3c = 0xAA;
            _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&_gba_wk[chan].w3c, &_gba_wk[chan].gbaStatus, _upload_23);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else {
            _upload_21s(chan, ret);
        }
    }
}

static void _upload_23(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 23;
        if (ret == 1) {
            _upload_16s(chan, ret);
        } else {
            _gba_wk[chan].w44 = 100;
            _gba_wk[chan].len1 = (AGB_TIMER_CLOCK / 1000) * _gba_wk[chan].w44;
            _gba_wk[chan].t1 = OSGetTick();
            _upload_23s(chan, ret);
        }
    }
}

static void _upload_23s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3FF;
        if (OSGetTick() - _gba_wk[chan].t1 > _gba_wk[chan].len1) {
fail:
            _upload_16s(chan, ret);
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _upload_24);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_24(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 24;
        if (ret == 1) {
fail:
            _upload_16s(chan, ret);
        } else if ((_gba_wk[chan].gbaStatus & 0xA) == 8) {
            _gba_wk[chan].ret = GBAReadAsync(chan, (u8 *)&_gba_wk[chan].w40, &_gba_wk[chan].gbaStatus, _upload_25);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else {
            _upload_23s(chan, ret);
        }
    }
}

static void _upload_25(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 25;
        if (ret == 1) {
fail:
            _upload_16s(chan, ret);
        } else if ((_gba_wk[chan].w40 >> 24) != 0xAA) {
            goto fail;
        } else {
            _job_type_clear(chan, __FUNCTION__);
            _gba_wk[chan].status = 0;
            gbaCommandSetKeyState(chan + 1, 1);
        }
    }
}

extern "C" {
s32 AGB_GetPokemon(s32 chan, void *pokemon, u32 *result) {
    s32 key;
    if (!AGB_Initialize(chan)) return 0;
    key = chan + 1;
    gbaCommandSetKeyState(key, 2);
    _AGB_Work_Clear(chan);
    _gba_wk[chan].active = 4;
    _gba_wk[chan].status = 3;
    _gba_wk[chan].busy = 1;
    _gba_wk[chan].pokemon = pokemon;
    _gba_wk[chan].result = result;
    _gba_wk[chan].ret = SIProbe(chan);
    if (_gba_wk[chan].ret != 0x40000) {
fail:
        _job_type_clear(chan, __FUNCTION__);
        _gba_wk[chan].status = 1;
        gbaCommandSetKeyState(key, 1);
        return 0;
    }
    _gba_wk[chan].ret = GBAResetAsync(chan, &_gba_wk[chan].gbaStatus, _getpokemon_01);
    if (_gba_wk[chan].ret == 2) {
        goto fail;
    }
    return 1;
}
}

static void _getpokemon_01(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 1;
        if (ret == 1) {
            GP_FAIL(chan);
        } else {
            _gba_wk[chan].w44 = 5;
            _gba_wk[chan].len1 = (AGB_TIMER_CLOCK / 1000) * _gba_wk[chan].w44;
            _gba_wk[chan].t1 = OSGetTick();
            _getpokemon_01s(chan, ret);
        }
    }
}

static void _getpokemon_01s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3E9;
        if (OSGetTick() - _gba_wk[chan].t1 > _gba_wk[chan].len1) {
fail:
            GP_FAIL(chan);
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _getpokemon_02);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}


static void _getpokemon_02(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 2;
        if (ret == 1) {
fail:
            GP_FAIL(chan);
        } else if ((_gba_wk[chan].gbaStatus & 0xA) == 8) {
            _gba_wk[chan].ret = GBAReadAsync(chan, (u8 *)&_gba_wk[chan].w40, &_gba_wk[chan].gbaStatus, _getpokemon_03);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else {
            _getpokemon_01s(chan, ret);
        }
    }
}

static void _getpokemon_03(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 3;
        if (ret == 1) {
fail:
            GP_FAIL(chan);
        } else if (_gameName != _gba_wk[chan].w40) {
            goto fail;
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _getpokemon_04);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_04(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 4;
        if (ret == 1) {
fail:
            GP_FAIL(chan);
        } else {
            _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&_gba_wk[chan].w40, &_gba_wk[chan].gbaStatus, _getpokemon_05);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_05(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 5;
        if (ret == 1) {
            GP_FAIL(chan);
        } else {
            _timer_set(chan, 0x7D);
            _getpokemon_05s(chan, ret);
        }
    }
}

static void _getpokemon_05s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3ED;
        if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
fail:
            GP_FAIL(chan);
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _getpokemon_06);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_06(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 6;
        if (ret == 1) {
fail:
            GP_FAIL(chan);
        } else if ((_gba_wk[chan].gbaStatus & 2) == 0) {
            _gba_wk[chan].w3c = 0x99;
            _gba_wk[chan].ret = GBAWriteAsync(chan, (u8 *)&_gba_wk[chan].w3c, &_gba_wk[chan].gbaStatus, _getpokemon_07);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else {
            _getpokemon_05s(chan, ret);
        }
    }
}

static void _getpokemon_07(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 7;
        if (ret == 1) {
            GP_FAIL(chan);
        } else {
            _gba_wk[chan].w44 = 100;
            _gba_wk[chan].len1 = (AGB_TIMER_CLOCK / 1000) * _gba_wk[chan].w44;
            _gba_wk[chan].t1 = OSGetTick();
            _getpokemon_07s(chan, ret);
        }
    }
}

static void _getpokemon_07s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3EF;
        if (OSGetTick() - _gba_wk[chan].t1 > _gba_wk[chan].len1) {
fail:
            GP_FAIL(chan);
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _getpokemon_08);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_08(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 8;
        if (ret == 1) {
fail:
            GP_FAIL(chan);
        } else if ((_gba_wk[chan].gbaStatus & 0xA) == 8) {
            _gba_wk[chan].ret = GBAReadAsync(chan, (u8 *)&_gba_wk[chan].w40, &_gba_wk[chan].gbaStatus, _getpokemon_09);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else {
            _getpokemon_07s(chan, ret);
        }
    }
}

static void _getpokemon_09(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 9;
        if (ret == 1) {
fail:
            GP_FAIL(chan);
        } else if ((_gba_wk[chan].w40 >> 24) != 0x99) {
            goto fail;
        } else {
            _gba_wk[chan].idx = 0;
            _gba_wk[chan].buf = gba_pokemon_buf[chan];
            _timer_set(chan, 0x7D);
            _getpokemon_09s(chan, ret);
        }
    }
}

static void _getpokemon_09s(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 0x3F1;
        if (OSGetTick() - _gba_wk[chan].t0 > _gba_wk[chan].len0) {
fail:
            GP_FAIL(chan);
        } else {
            _gba_wk[chan].ret = GBAGetStatusAsync(chan, &_gba_wk[chan].gbaStatus, _getpokemon_10);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_10(s32 chan, s32 ret) {
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 10;
        if (ret == 1) {
fail:
            GP_FAIL(chan);
        } else if (_gba_wk[chan].gbaStatus & 8) {
            _gba_wk[chan].ret = GBAReadAsync(chan, (u8 *)&_gba_wk[chan].w1c, &_gba_wk[chan].gbaStatus, _getpokemon_11);
            if (_gba_wk[chan].ret == 2) {
                goto fail;
            }
        } else {
            _getpokemon_09s(chan, ret);
        }
    }
}

static void _getpokemon_11(s32 chan, s32 ret) {
    u8 *b;
    if (_gba_wk[chan].busy != 0) {
        _gba_wk[chan].step = 11;
        if (ret == 1) {
            GP_FAIL(chan);
        } else {
            *(u32 *)(_gba_wk[chan].buf + _gba_wk[chan].idx) = _gba_wk[chan].w1c;
            _gba_wk[chan].idx += 4;
            if (_gba_wk[chan].idx < 0x278) {
                _timer_set(chan, 0x7D);
                _getpokemon_09s(chan, ret);
            } else {
                pokeconv(_gba_wk[chan].pokemon, _gba_wk[chan].buf);
                b = _gba_wk[chan].buf;
                *_gba_wk[chan].result = (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0];
                _job_type_clear(chan, __FUNCTION__);
                _gba_wk[chan].status = 0;
                gbaCommandSetKeyState(chan + 1, 1);
            }
        }
    }
}

extern "C" {
void AGB_FileBuffAlloc() {
    jbBuf1 = (u8 *)GSmemAllocAlign(0x20000, 0x20);
}

void AGB_FileBuffFree() {
    GSmemFree(jbBuf1);
    jbBuf1 = 0;
}
}
