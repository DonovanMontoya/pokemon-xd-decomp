#include <game/menuPcBoxPokemonLayout.hpp>
struct DebugFlags{u8 terminate:1;u8 other:7;};
struct DebugEntry {union{u8 flags;DebugFlags bits;};u8 pad;s16 link;u32 message;s32(*callback)(s32,s32);};
extern "C" {extern s32 _menu_data_number;extern u32(*debugMenuDataGetNum)();extern DebugEntry*(*debugMenuDataGetPtr)(s32);void*GSgfxLayerFindByID(s32);u32 GSmsgGetRect(u32);s32 dbgMenuGetRootMenu();void menuClose(s32);u8 menuDataBiosGetDispMax(s32);u8 menuIsCheck(s32);s32 menuOpenCustom(s32,s32,s32*,s32,s32,s32);u16*windowGetKeyInfo();tagWINDOW_WORK*windowSearchID(s32);}
static u8 _dbgMenuEnable;static s32*_pCursor;static u8 _dbgMenuMode;static s32 _dbgLayerID=-1;
static s32 _dbgMenuSub(long);static s32 _dbgMenuGetMenuNum(tagWINDOW_WORK*,long*);static s32 _dbgMenuCheckTerminate(tagWINDOW_WORK*,long);static s32 _dbgMenuGetMenuNo(long);static u32 _dbgMenuGetMsgID(tagWINDOW_WORK*,long);static s32 _dbgMenuGetItemNo(tagWINDOW_WORK*,long);static s16 _dbgMenuGetLink(long);static tagWINDOW_WORK*_dbgMenuGetWin(long);static s32 _dbgMenuGetIndex(tagWINDOW_WORK*);
s16 dbgMenuGetLink(long);s32 debugMenuGetNum();DebugEntry*dbgMenuGetPtr(long);
extern "C" s32 dbgMenuGetLayerID(void) {
    return _dbgLayerID;
}

extern "C" void dbgMenuSetLayerID(s32 arg0) {
    _dbgLayerID = arg0;
}

extern "C" void dbgMenuCursor(tagWINDOW_WORK *arg0) {
    s16 temp_r0;
    s16 var_r3;
    s16 var_r4;
    s32 temp_r29;
    s8 temp_r4;
    s8 var_r5;
    u16 temp_r30;

    temp_r30 = windowGetKeyInfo()[3];
    temp_r29 = (s8)_dbgMenuGetMenuNum(arg0, 0);
    var_r5 = (s8)menuDataBiosGetDispMax(arg0->menu);
    if (temp_r29 < var_r5) {
        var_r5 = temp_r29;
    }
    var_r3 = arg0->first;
    var_r4 = arg0->selected;
    if (temp_r30 & 1) {
        var_r4 -= 1;
    } else if (temp_r30 & 2) {
        var_r4 += 1;
    }
    if (var_r4 < 0) {
        var_r3 += var_r4;
        var_r4 = 0;
        if (var_r3 < 0) {
            var_r4 = (s16) (s8) (var_r5 - 1);
            var_r3 = (s16) (s8) (temp_r29 - var_r5);
        }
    } else if (var_r4 >= var_r5) {
        temp_r4 = var_r5 - 1;
        temp_r0 = var_r3 + (var_r4 - temp_r4);
        var_r4 = (s16) temp_r4;
        var_r3 = temp_r0;
        if ((s32) (var_r3 + var_r4) >= temp_r29) {
            var_r3 = 0;
            var_r4 = 0;
        }
    }
    arg0->first = var_r3;
    arg0->selected = var_r4;
}

extern "C" u8 dbgMenuGetEnable(void) {
    return _dbgMenuEnable;
}

extern "C" void dbgMenuSetEnable(u8 arg0) {
    _dbgMenuEnable = arg0;
}

extern "C" s32 dbgMenuIsOpen(void) {
    return menuIsCheck(_menu_data_number + 1) != 0;
}

extern "C" void dbgMenuClose(void) {
    _dbgMenuMode = 0;
    menuClose(_menu_data_number + 1);
}

extern "C" void dbgMenuMain(u8 arg0) {
    u32 var_r3;
    u8 temp_r3;
    u8 temp_r3_2;

    if (((s32) _dbgLayerID == -1) || (GSgfxLayerFindByID(_dbgLayerID) == 0U)) {
        temp_r3 = menuIsCheck(_menu_data_number + 1);
        if (((u32) (-(s32) temp_r3 | temp_r3) >> 0x1FU) != 0) {
            _dbgMenuMode = 0;
            menuClose(_menu_data_number + 1);
        }
    } else {
        if (debugMenuDataGetNum == 0) {
            var_r3 = 0U;
        } else {
            var_r3 = debugMenuDataGetNum();
        }
        if ((var_r3 != 0U) && ((u8) _dbgMenuEnable != 0)) {
            temp_r3_2 = menuIsCheck(_menu_data_number + 1);
            if (((u32) (-(s32) temp_r3_2 | temp_r3_2) >> 0x1FU) == 0) {
                _dbgMenuMode = arg0;
loop_11:
                if (_dbgMenuSub(0) >= 0) {
                    if ((u8) _dbgMenuMode == 1) {
                        goto loop_11;
                    }
                }
            }
        }
    }
}

static s32 _dbgMenuSub(long arg0) {
    s32 (*var_r12_2)(s32,s32);
    s16 var_r26;
    s32 (*var_r12)(s32, s32);
    s32 *temp_r30;
    s32 temp_r26;
    s32 temp_r26_2;
    s32 temp_r28;
    s32 temp_r3_2;
    s32 var_r27;
    s32 var_r3_5;
    u32 var_r3;
    u32 var_r3_3;
    DebugEntry *var_r3_2;
    DebugEntry *var_r3_4;
    DebugEntry *var_r3_6;
    tagWINDOW_WORK *temp_r3;

    var_r27 = 0;
    temp_r28 = _menu_data_number + arg0 + 1;
loop_1:
    temp_r26 = (_menu_data_number + arg0) & ~(arg0 >> 0x1F);
    temp_r30 = _pCursor+_dbgMenuGetMenuNo(temp_r26);
    temp_r26_2 = menuOpenCustom(temp_r28, temp_r26, temp_r30, 0, 1, 0);
    temp_r3 = windowSearchID(temp_r28);
    if (temp_r3 != 0) {
        *temp_r30 = temp_r3->first + temp_r3->selected;
    } else {
        *temp_r30 = 0;
    }
    if (temp_r26_2 == -1) {
        if (arg0 == 0) {
            var_r27 = -1;
        }
        menuClose(temp_r28);
        return var_r27;
    }
    temp_r3_2 = _dbgMenuGetItemNo(temp_r3, temp_r3->first + temp_r3->selected);
    if (temp_r3_2 > 0) {
        if (debugMenuDataGetNum == 0) {
            var_r3 = 0U;
        } else {
            var_r3 = debugMenuDataGetNum();
        }
        if ((s32) var_r3 <= temp_r3_2) {
            goto block_12;
        }
        if (debugMenuDataGetPtr == 0) {
            var_r3_2 = 0;
        } else {
            var_r3_2 = debugMenuDataGetPtr(temp_r3_2);
        }
        if (var_r3_2 == 0) {
            var_r26 = 0;
        } else {
            var_r26 = var_r3_2->link;
        }
        if (var_r26 > 0) {
            if (debugMenuDataGetNum == 0) {
                var_r3_3 = 0U;
            } else {
                var_r3_3 = debugMenuDataGetNum();
            }
            if ((s32) var_r3_3 <= var_r26) {
                goto block_24;
            }
        } else {
block_24:
            var_r26 = 0;
        }
    } else {
block_12:
        var_r26 = 0;
    }
    if (var_r26 != 0) {
        if (debugMenuDataGetPtr == 0) {
            var_r3_4 = 0;
        } else {
            var_r3_4 = debugMenuDataGetPtr(temp_r3_2);
        }
        if (var_r3_4 == 0) {
            var_r12 = 0;
        } else {
            var_r12 = var_r3_4->callback;
        }
        if (var_r12 != 0) {
            var_r3_5 = var_r12(temp_r3_2, temp_r3->first + temp_r3->selected);
        } else {
            var_r3_5 = 1;
        }
        if (var_r3_5 == 0) {
            menuClose(_menu_data_number + 1);
            return 1;
        }
        if ((var_r3_5 != -1) && (var_r26 != 1) && (_dbgMenuSub(arg0 + 1) == 1)) {
            return 1;
        }
        goto loop_1;
    }
    menuClose(_menu_data_number + 1);
    if (debugMenuDataGetPtr == 0) {
        var_r3_6 = 0;
    } else {
        var_r3_6 = debugMenuDataGetPtr(temp_r3_2);
    }
    if (var_r3_6 == 0) {
        var_r12_2 = 0;
    } else {
        var_r12_2 = var_r3_6->callback;
    }
    if (var_r12_2 != 0) {
        var_r12_2(temp_r3_2, temp_r3->first + temp_r3->selected);
    }
    return 1;
}

static s32 _dbgMenuGetMenuNum(tagWINDOW_WORK *arg0,long *arg1) {
    s32 temp_r4;
    s32 var_r31;
    u32 temp_r3;

    if (arg1 != 0) {
        *arg1 = 0;
    }
    var_r31 = 0;
    do {
        u32 message=_dbgMenuGetMsgID(arg0,var_r31);
        if (arg1 != 0) {
            temp_r3 = GSmsgGetRect(message) >> 0x10U;
            if ((s32) *arg1 < (s32) temp_r3) {
                *arg1 = (s32) temp_r3;
            }
        }
        temp_r4 = var_r31;
        var_r31 += 1;
    } while (_dbgMenuCheckTerminate(arg0, temp_r4) == 0);
    return var_r31;
}

static s32 _dbgMenuCheckTerminate(tagWINDOW_WORK*arg0,long arg1) {
    DebugEntry *var_r3;
    u8 var_r0;

    s32 item=_dbgMenuGetItemNo(arg0,arg1);
    if (debugMenuDataGetPtr == 0) {
        var_r3 = 0;
    } else {
        var_r3 = debugMenuDataGetPtr(item);
    }
    if (var_r3 == 0) {
        var_r0 = 1;
    } else {
        var_r0 = var_r3->bits.terminate != 0;
    }
    return (s32) var_r0;
}

static s32 _dbgMenuGetMenuNo(long arg0) {
    s16 var_r31_2;
    s32 temp_r3_2;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;
    u32 var_r3;
    u32 var_r3_3;
    DebugEntry *var_r3_2;
    DebugEntry *var_r3_4;
    DebugEntry *var_r3_5;
    u8 var_r0;
    u8 var_r0_2;
    tagWINDOW_WORK *temp_r3;

    temp_r3=windowSearchID(arg0);
    if (temp_r3 != 0) {
        temp_r3_2 = _dbgMenuGetItemNo(temp_r3,temp_r3->first+temp_r3->selected);
        if (temp_r3_2 > 0) {
            if (debugMenuDataGetNum == 0) {
                var_r3 = 0U;
            } else {
                var_r3 = debugMenuDataGetNum();
            }
            if ((s32) var_r3 <= temp_r3_2) {
                goto block_6;
            }
            if (debugMenuDataGetPtr == 0) {
                var_r3_2 = 0;
            } else {
                var_r3_2 = debugMenuDataGetPtr(temp_r3_2);
            }
            if (var_r3_2 == 0) {
                var_r31_2 = 0;
            } else {
                var_r31_2 = var_r3_2->link;
            }
            if (var_r31_2 > 0) {
                if (debugMenuDataGetNum == 0) {
                    var_r3_3 = 0U;
                } else {
                    var_r3_3 = debugMenuDataGetNum();
                }
                if ((s32) var_r3_3 <= var_r31_2) {
                    goto block_18;
                }
            } else {
block_18:
                var_r31_2 = 0;
            }
        } else {
block_6:
            var_r31_2 = 0;
        }
        var_r31 = 0;
        var_r29 = 0;
loop_29:
        if (var_r29 < var_r31_2) {
            if (debugMenuDataGetPtr == 0) {
                var_r3_4 = 0;
            } else {
                var_r3_4 = debugMenuDataGetPtr(var_r29);
            }
            if (var_r3_4 == 0) {
                var_r0 = 1;
            } else {
                var_r0 = var_r3_4->bits.terminate != 0;
            }
            if (var_r0 != 0) {
                var_r31 += 1;
            }
            var_r29 += 1;
            goto loop_29;
        }
    } else {
        var_r31 = 0;
        var_r30 = 0;
loop_41:
        if (var_r30 < dbgMenuGetRootMenu()) {
            if (debugMenuDataGetPtr == 0) {
                var_r3_5 = 0;
            } else {
                var_r3_5 = debugMenuDataGetPtr(var_r30);
            }
            if (var_r3_5 == 0) {
                var_r0_2 = 1;
            } else {
                var_r0_2 = var_r3_5->bits.terminate != 0;
            }
            if (var_r0_2 != 0) {
                var_r31 += 1;
            }
            var_r30 += 1;
            goto loop_41;
        }
    }
    return var_r31;
}

static u32 _dbgMenuGetMsgID(tagWINDOW_WORK*arg0,long arg1) {
    DebugEntry *var_r3;

    s32 item=_dbgMenuGetItemNo(arg0,arg1);
    if (debugMenuDataGetPtr == 0) {
        var_r3 = 0;
    } else {
        var_r3 = debugMenuDataGetPtr(item);
    }
    if (var_r3 == 0) {
        return 0;
    }
    return var_r3->message;
}

static s32 _dbgMenuGetItemNo(tagWINDOW_WORK *arg0,long arg1) {
    s16 temp_r4_3;
    s16 var_r28_3;
    s16 var_r28_4;
    s16 var_r29_2;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r31;
    s32 temp_r3_4;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 var_r0;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    s32 var_r5;
    s32 var_r5_2;
    u32 var_r3_10;
    u32 var_r3_6;
    u32 var_r3_7;
    u32 var_r3_8;
    DebugEntry *temp_r3_6;
    DebugEntry *var_r3_9;
    tagWINDOW_WORK *temp_r3;
    tagWINDOW_WORK *temp_r3_2;
    tagWINDOW_WORK *temp_r3_3;
    tagWINDOW_WORK *temp_r3_5;

    temp_r0 = arg0->menu;
    var_r3_2 = -1;
    temp_r4 = _menu_data_number + 1;
    if (temp_r0 >= temp_r4) {
        var_r3_2 = temp_r0 - temp_r4;
    }
    if (var_r3_2 < 0) {
        return 0;
    }
    if (var_r3_2 == 0) {
        var_r3 = dbgMenuGetRootMenu();
    } else {
        temp_r4_2 = (s32) (var_r3_2 - 1) >> 0x1F;
        temp_r3 = windowSearchID(((var_r3_2+temp_r4)-1)&~temp_r4_2);
        if (temp_r3 == 0) {
            var_r28 = dbgMenuGetRootMenu();
        } else {
            var_r5 = -1;
            temp_r7 = temp_r3->menu;
            temp_r6 = _menu_data_number + 1;
            temp_r31 = temp_r3->first + temp_r3->selected;
            if (temp_r7 >= temp_r6) {
                var_r5 = temp_r7 - temp_r6;
            }
            if (var_r5 < 0) {
                var_r0 = 0;
            } else {
                if (var_r5 == 0) {
                    var_r3_3 = dbgMenuGetRootMenu();
                } else {
                    temp_r0_2 = var_r5 - 1;
                    temp_r3_2 = windowSearchID((temp_r6 + temp_r0_2) & ~(temp_r0_2 >> 0x1F));
                    if (temp_r3_2 == 0) {
                        var_r29 = dbgMenuGetRootMenu();
                    } else {
                        var_r5_2 = -1;
                        temp_r7_2 = temp_r3_2->menu;
                        temp_r6_2 = _menu_data_number + 1;
                        temp_r29 = temp_r3_2->first + temp_r3_2->selected;
                        if (temp_r7_2 >= temp_r6_2) {
                            var_r5_2 = temp_r7_2 - temp_r6_2;
                        }
                        if (var_r5_2 < 0) {
                            var_r29 = 0;
                        } else {
                            if (var_r5_2 == 0) {
                                var_r3_4 = dbgMenuGetRootMenu();
                            } else {
                                temp_r0_3 = var_r5_2 - 1;
                                temp_r3_3 = windowSearchID((temp_r6_2 + temp_r0_3) & ~(temp_r0_3 >> 0x1F));
                                if (temp_r3_3 == 0) {
                                    var_r28_2 = dbgMenuGetRootMenu();
                                } else {
                                    temp_r4_3 = temp_r3_3->first;
                                    temp_r28 = temp_r4_3 + temp_r3_3->selected;
                                    temp_r3_4 = _dbgMenuGetIndex(temp_r3_3);
                                    if (temp_r3_4 < 0) {
                                        var_r28_2 = 0;
                                    } else {
                                        if (temp_r3_4 == 0) {
                                            var_r3_5 = dbgMenuGetRootMenu();
                                        } else {
                                            temp_r3_5 = _dbgMenuGetWin(temp_r3_4 - 1);
                                            if (temp_r3_5 == 0) {
                                                var_r3_5=dbgMenuGetRootMenu();
                                            } else {
                                                var_r3_5=_dbgMenuGetItemNo(temp_r3_5,temp_r3_5->first+temp_r3_5->selected);
                                            }
                                            var_r3_5 = (s32) _dbgMenuGetLink(var_r3_5);
                                        }
                                        var_r28_2 = var_r3_5 + temp_r28;
                                    }
                                }
                                if ((var_r28_2 <= 0) || (debugMenuGetNum() <= var_r28_2)) {
                                    var_r28_3 = 0;
                                } else {
                                    var_r28_3 = dbgMenuGetLink(var_r28_2);
                                    if ((var_r28_3 <= 0) || (debugMenuGetNum() <= var_r28_3)) {
                                        var_r28_3 = 0;
                                    }
                                }
                                var_r3_4 = (s32) var_r28_3;
                            }
                            var_r29 = var_r3_4 + temp_r29;
                        }
                    }
                    if (var_r29 > 0) {
                        if (debugMenuDataGetNum == 0) {
                            var_r3_6 = 0U;
                        } else {
                            var_r3_6 = debugMenuDataGetNum();
                        }
                        if ((s32) var_r3_6 <= var_r29) {
                            goto block_46;
                        }
                        temp_r3_6 = dbgMenuGetPtr(var_r29);
                        if (temp_r3_6 == 0) {
                            var_r28_4 = 0;
                        } else {
                            var_r28_4 = temp_r3_6->link;
                        }
                        if (var_r28_4 > 0) {
                            if (debugMenuDataGetNum == 0) {
                                var_r3_7 = 0U;
                            } else {
                                var_r3_7 = debugMenuDataGetNum();
                            }
                            if ((s32) var_r3_7 <= var_r28_4) {
                                goto block_55;
                            }
                        } else {
block_55:
                            var_r28_4 = 0;
                        }
                    } else {
block_46:
                        var_r28_4 = 0;
                    }
                    var_r3_3 = (s32) var_r28_4;
                }
                var_r0 = var_r3_3 + temp_r31;
            }
            var_r28 = var_r0;
        }
        if (var_r28 > 0) {
            if (debugMenuDataGetNum == 0) {
                var_r3_8 = 0U;
            } else {
                var_r3_8 = debugMenuDataGetNum();
            }
            if ((s32) var_r3_8 <= var_r28) {
                goto block_64;
            }
            if (debugMenuDataGetPtr == 0) {
                var_r3_9 = 0;
            } else {
                var_r3_9 = debugMenuDataGetPtr(var_r28);
            }
            if (var_r3_9 == 0) {
                var_r29_2 = 0;
            } else {
                var_r29_2 = var_r3_9->link;
            }
            if (var_r29_2 > 0) {
                if (debugMenuDataGetNum == 0) {
                    var_r3_10 = 0U;
                } else {
                    var_r3_10 = debugMenuDataGetNum();
                }
                if ((s32) var_r3_10 <= var_r29_2) {
                    goto block_76;
                }
            } else {
block_76:
                var_r29_2 = 0;
            }
        } else {
block_64:
            var_r29_2 = 0;
        }
        var_r3 = (s32) var_r29_2;
    }
    return var_r3 + arg1;
}

static s16 _dbgMenuGetLink(long arg0) {
    s16 var_r31;
    u32 var_r3;
    u32 var_r3_3;
    DebugEntry *var_r3_2;

    if (arg0 > 0) {
        if (debugMenuDataGetNum == 0) {
            var_r3 = 0U;
        } else {
            var_r3 = debugMenuDataGetNum();
        }
        if ((s32) var_r3 <= arg0) {
            goto block_5;
        }
        if (debugMenuDataGetPtr == 0) {
            var_r3_2 = 0;
        } else {
            var_r3_2 = debugMenuDataGetPtr(arg0);
        }
        if (var_r3_2 == 0) {
            var_r31 = 0;
        } else {
            var_r31 = var_r3_2->link;
        }
        if (var_r31 > 0) {
            if (debugMenuDataGetNum == 0) {
                var_r3_3 = 0U;
            } else {
                var_r3_3 = debugMenuDataGetNum();
            }
            if ((s32) var_r3_3 <= var_r31) {
                goto block_17;
            }
        } else {
block_17:
            var_r31 = 0;
        }
        return var_r31;
    }
block_5:
    return 0;
}

tagWINDOW_WORK*_dbgMenuGetWin(long arg0) {
    s32 temp_r4;

    temp_r4 = arg0 >> 0x1F;
    return windowSearchID((_menu_data_number+arg0+1)&~temp_r4);
}

static s32 _dbgMenuGetIndex(tagWINDOW_WORK *arg0) {
    s32 temp_r3;
    s32 temp_r5;
    s32 var_r0;

    var_r0 = -1;
    temp_r5 = arg0->menu;
    temp_r3 = _menu_data_number + 1;
    if (temp_r5 >= temp_r3) {
        var_r0 = temp_r5 - temp_r3;
    }
    return var_r0;
}

s16 dbgMenuGetLink(long arg0) {
    DebugEntry *var_r3;

    if (debugMenuDataGetPtr == 0) {
        var_r3 = 0;
    } else {
        var_r3 = debugMenuDataGetPtr(arg0);
    }
    if (var_r3 == 0) {
        return 0;
    }
    return var_r3->link;
}

s32 debugMenuGetNum(void) {
    if (debugMenuDataGetNum == 0) {
        return 0;
    }
    return debugMenuDataGetNum();
}

DebugEntry*dbgMenuGetPtr(long arg0) {
    if (debugMenuDataGetPtr == 0) {
        return 0;
    }
    return debugMenuDataGetPtr(arg0);
}
