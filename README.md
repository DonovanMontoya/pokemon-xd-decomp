# Pokémon XD: Gale of Darkness Decompilation

<!-- progress:start -->
![US code matched: 45.22%](https://img.shields.io/static/v1?label=US%20code%20matched&message=45.22%25&color=blue) ![US data matched: 12.37%](https://img.shields.io/static/v1?label=US%20data%20matched&message=12.37%25&color=blue)
<!-- progress:end -->

This is a matching decompilation of **Pokémon XD: Gale of Darkness** for the Nintendo GameCube.

It started as a fork of [TeamOrre/xd-decomp](https://github.com/TeamOrre/xd-decomp) and is now maintained as a separate project. Thanks to everyone who worked on the original.

## Why a separate project?

This is an **AI-assisted decompilation**. TeamOrre's [contributing guidelines](https://github.com/TeamOrre/xd-decomp/blob/main/CONTRIBUTING.md#ai-assistance-policy) ban AI-assisted contributions for now, so this work can't be merged upstream, and it continues here instead.

AI assistance doesn't lower the bar for what counts as decompiled. A function only counts as matching when objdiff confirms it compiles to exactly the same bytes as the original, and every build is checked against the retail DOL's SHA1.

## Progress

The badges above show the percentage of original US (`GXXE01`) code and data
bytes matched by objdiff in the last recorded local build. They are snapshots,
not live CI measurements or estimates of remaining effort. JP demo progress has
not been measured here.

After building the US version, refresh the badges with:

```sh
ninja all_source progress build/GXXE01/report.json
python3 tools/update_readme_progress.py build/GXXE01/report.json
```

Commit the updated README with the corresponding source changes. Full builds
currently require private inputs; public CI checks configuration only.

## Supported Versions

Work in progress:

- `GXXE01`: Rev 0 (USA)
- `NXXJ01`: Rev 0 (JP Demo Disc)

## Project Goals

- Reconstruct the game's code in C/C++.
- Produce a **matching** retail binary.
- Remain legally clean – **no ROMs, ISOs, or copyrighted assets**.

## Repository Organization

- `src/` – Decompiled C/C++ sources
- `include/` – Reconstructed headers
- `config/` – Project configs, splits, and symbols
- `tools/` – Helper scripts and utilities
- `docs/` – Documentation and notes

## Legal Notices

This project does **not** contain game assets or proprietary data.
It is a reverse engineering effort for educational and archival purposes.

An existing copy of the game is required.

## Dependencies

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

## Building

- Clone the repository:

  ```sh
  git clone --recurse-submodules https://github.com/DonovanMontoya/pokemon-xd-decomp.git
  ```

- Copy your game's disc image to `orig/GXXE01`.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python configure.py
  ```

  To use a version other than `GXXE01` (USA), specify it with `--version`.

- Build:

  ```sh
  ninja
  ```

## Diffing

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

## Contributing

Contributions are welcome! Before making a pull request, please read our [contributing guidelines](CONTRIBUTING.md).

Also, consider joining our `#pokemon-xd` discussion channel on Discord.

[![Gamecube/Wii Decompilation Discord](https://discordapp.com/api/guilds/727908905392275526/widget.png?style=banner2)](https://discord.gg/hKx3FJJgrV)
