# AGENTS.md

This file provides guidance to coding agents working with code in this repository.

## What this is

A matching decompilation of Pokémon XD: Gale of Darkness (GameCube), built on decomp-toolkit (dtk) + objdiff with Metrowerks CodeWarrior (MWCC). A function only counts when it compiles to exactly the original bytes, and every build must reproduce the retail DOL (`GXXE01` SHA1 `ff9e752ead9914af0b363ae6c831a34ccce189d2`). Versions: `GXXE01` (USA, primary) and `NXXJ01` (JP demo).

Never commit the ROM/ISO, anything under `orig/`, extracted assets, or stray `*.d` dependency files in the repo root.

## Build and progress

```sh
python configure.py            # regenerate build.ninja (rerun after editing configure.py)
ninja                          # full build + DOL hash check
ninja all_source progress build/GXXE01/report.json
python3 tools/update_readme_progress.py build/GXXE01/report.json   # refresh README badges
```

Progress is `matched_code` in `build/GXXE01/report.json` (out of 3,042,576 code bytes). On a laptop, prefer `nice -n 19 ninja -j4`. If `main.dol: OK` doesn't print because the DOL was up to date, verify with `sha1sum build/GXXE01/main.dol`. CI only checks configuration; full builds need the private disc image.

## Layout

- `configure.py` — the source of truth for every unit: its `Object(...)` entry, matching status, and compiler flags. Units are `NonMatching` until fully exact, then `Matching` / `MatchingFor("GXXE01")`. Only flip a unit to matching after a full build still hashes correctly (a linked unit can break the DOL even when objdiff says 100%).
- `config/<VERSION>/symbols.txt`, `splits.txt` — dtk symbol and split definitions. For symbols shared between versions, prefer the demo map names from `NXXJ01`.
- `src/game/pxdvs/...` — game code (C++). `src/dolphin`, `src/musyx`, `src/PowerPC_EABI_Support`, `src/runtime_libs` — SDK/library code (mostly C).
- `include/` — reconstructed headers; units may have private `<unit>Private.hpp` / `<unit>Layout.hpp` headers.
- `build/GXXE01/asm/<UNIT>.s` — original disassembly per unit (generated).

## Compiler flag recipes (set per unit in configure.py)

Flag groups like `cflags_xd_app_balanced`, `cflags_xd_app_fight` (-O4 instead of -O4,p, plus `-inline noauto`), `cflags_xd_app_pokemon` and `cflags_xd_gimmick` are defined near the top of `configure.py`; units add `extra_cflags`. Common findings:

- Menu units (C++): `-inline noauto -opt nopeephole`, plus `-str reuse,nopool,readonly` when small strings sit 4-byte aligned or in .sdata2.
- Battle (`fight*`) and script units: `cflags_xd_app_fight`; script `obj*` units also add `-opt nopeephole -str reuse,nopool,readonly`.
- gimmick: `-O0,p -inline off -fp_contract off`.
- MetroTRK pieces that were originally assembly may be `asm` functions or `.s` files; elsewhere use real C/C++ only.

Find a new unit's recipe early using its trivial functions.

## Local per-unit tooling

`build/xd40/` (gitignored, local only) contains `xd.py`, which compiles and diffs a single unit without touching ninja state, and `WORKER_RULES.md`, a fuller list of matching patterns and known blockers. If present:

```sh
nice -n 19 python3 build/xd40/xd.py compile game/menuFight [--flags "-extra"] [--replace-flags "full set"] [--src F --out O]
nice -n 19 python3 build/xd40/xd.py score   game/menuFight [--obj O]    # does NOT recompile; compile first
nice -n 19 python3 build/xd40/xd.py diff    game/menuFight SYMBOL       # left column is the target
nice -n 19 python3 build/xd40/xd.py asm     game/menuFight SYMBOL
```

`UNIT` is the objdiff unit name without the `main/` prefix or extension. When testing variant sources via `--src`, keep the original file base name, because anonymous-namespace mangling depends on it.

## Matching notes

- Symbol names must match exactly. Mangled names imply the exact C++ signature; use `extern "C"` for plain names. Function-local statics must match the `name$NNNN` symbols.
- Off-by-N `.rodata`/`.sdata2` offsets usually come from string-pool layout. The original may keep literals from functions the linker stripped; re-add a plausible function at the right source position.
- Known blockers: register-allocation-only diffs, `$NNNN` static numbering, `psq_l`/`psq_st` quantized conversions, `ServerWork` accessed via r13 without a relocation, and `dolphin_trk` (matches, but linking it breaks the DOL hash).
- Writing functions that have no code yet gives far more progress than polishing near-misses.

## Contribution conventions

Follow `CONTRIBUTING.md`: work happens through PRs (not direct commits to `main`), one purpose per PR, and use names from symbol maps or descriptive technical names, not speculative lore names. Ask before adding new source files or restructuring. The "AI-assisted" note in README/CONTRIBUTING is intentional.
