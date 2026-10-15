# Contributing to the Pokémon XD Decompilation

This document explains how to contribute safely and effectively. It may change as the decomp progresses.

This repository is the decompilation only. Ports and other derived projects are separate and out of scope here.

## General Contribution Rules

### 1. No direct commits to `main`
All work goes through pull requests.

### 2. One purpose per PR
Small, focused PRs are easier to review and maintain.

Examples of good PRs:
- “Add 12 new retail XD symbols”
- “Match the Pokémon evolution functions”
- “Initial split regions for .text segment”
- “Add tool to dump REL files from assets”

### 3. Matching is the bar
A function counts as decompiled only when it compiles to exactly the same bytes as the original. Check with objdiff, and make sure the build still reproduces the retail DOL's SHA1. Mark anything that doesn't fully match as `NonMatching`.

### 4. No game data
Never commit ROMs, ISOs, extracted assets, or other copyrighted material.

### 5. Naming Conventions
- Use names from symbol maps when available.
- Otherwise, use clear, descriptive technical names.
- Avoid lore names unless confirmed by evidence.

## Working on Symbols

Symbols are located in `config/GAMEID/symbols.txt`. The format and attributes are documented [here](https://github.com/encounter/dtk-template/blob/main/docs/symbols.md).

Guidelines:
- For symbols shared between versions, use the demo map symbol names (in `NXXJ01/symbols.txt`).
- Avoid adding speculative names without evidence.

## Working on Splits

Splits go into `config/GAMEID/splits.txt`, defining DOL/REL segment boundaries. The format and attributes are documented [here](https://github.com/encounter/dtk-template/blob/main/docs/splits.md).

Guidelines:
- Keep placeholder splits until confirmed.
- If making changes to splits, verify that they work by building before submitting changes.

## Tools

Scripts go in `tools/`.

Tool guidelines:
- Prefer small, single-purpose tools.
- Document how to use them.
- Avoid tools requiring proprietary software.
- Leave clear instructions for setup if needed.

## Getting Started

1. Follow the build steps in the [README](README.md) and get a clean build of your version.
2. Pick something to work on, or open an issue to discuss it first.
3. Ask before adding new C source files or changing the project structure.
4. For symbols/splits work, open a PR with your proposed changes.

## AI Assistance Policy

This project is AI-assisted, and AI-assisted contributions are welcome. They're held to the same standard as everything else: matching functions must match the original exactly, and the build must still reproduce the retail DOL.
