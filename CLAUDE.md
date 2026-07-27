# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this project is

HackerOoT is a modding-friendly fork of the [zeldaret/oot](https://github.com/zeldaret/oot) Zelda: Ocarina of Time
decompilation. It builds a working N64/GameCube/iQue ROM from source and is intended as a base for making OoT mods
(it is not a PC port). The build produces byte-for-byte-ish reproductions of multiple retail ROM versions, with
HackerOoT features layered on top and toggled via headers in `include/config/`.

The repo does **not** include game assets. A legally-owned base ROM must be placed under `baseroms/<version>/` before
anything will build (see INSTALLATION.md).

## Build commands

All building goes through the top-level `Makefile`. Key variables (pass as `make VAR=value ...` or set in a
gitignored `.make_options.mk`):

- `VERSION` — target ROM version, default `ntsc-1.2`. Other values: `ntsc-1.0`, `ntsc-1.1`, `pal-1.0`, `pal-1.1`,
  `gc-jp`, `gc-jp-mq`, `gc-us`, `gc-us-mq`, `gc-eu-mq-dbg` (has debug features by default), `gc-eu`, `gc-eu-mq`,
  `gc-jp-ce`, `ique-cn`.
- `DEBUG_FEATURES` — `1`/`0`, force HackerOoT/debug features on or off regardless of ROM version.
- `COMPILER` — must be `gcc` (only supported value currently).
- `CPP_DEFINES` — e.g. `-DENABLE_F3DEX3=0` to disable the F3DEX3 microcode (needed on HLE-only emulators).
- `N_THREADS` / `-jN` — parallelism for setup/build.
- `N64_EMULATOR` — emulator command used by `make run`.

Common targets:

```bash
make setup          # one-time: extract assets from baserom, build tools, set up F3DEX3 (needs baserom.z64 first)
make                # build the ROM (default VERSION=ntsc-1.2); output: build/$(VERSION)/hackeroot-$(VERSION).z64
make run             # build then launch in $(N64_EMULATOR)
make compress        # build + compress the ROM
make wad              # build a Wii VC .wad (see .make_hackeroot.mk)
make iso              # build a GameCube ISO
make patch            # generate a .bps patch against the vanilla ROM (build/$(VERSION)/)
make clean            # remove build/$(VERSION)
make assetclean        # remove extracted/$(VERSION) (forces asset re-extraction)
make distclean          # remove extracted/, build/, tools binaries, F3DEX3 build artifacts
```

Building a non-default version requires its own baserom under `baseroms/<version>/` and `make setup VERSION=<version>`
first.

### Formatting / linting

Formatting is C/C++ via clang-format (`.clang-format`) and clang-tidy (`.clang-tidy`), driven by `format.py`:

```bash
python3 format.py                       # format all tracked source files in place
python3 tools/check_format.py           # CI-equivalent check of all files (no changes made)
python3 tools/check_format.py --verbose --compare-to upstream/develop/2.1.0   # check only files changed vs upstream
```

CI (`.github/workflows/format.yml`) runs `check_format.py` on push/PR against the same baseline.

### Tests

There is no game-logic test suite; `tools/tests/` contains a small standalone Python test
(`test_preprocess_pragmas.py`) for one of the build tools. There is no single "run all tests" command beyond running
that script directly and doing a full `make` build (CI's real correctness signal is that the ROM builds cleanly for
all matrix configs — see `.github/workflows/build.yml`, which builds Debug/Release × F3DEX3 on/off).

### Adding a new actor

`./new_actor.py -name <ActorName>` scaffolds a new actor overlay under `src/overlays/actors/ovl_<ActorName>/`
(and an object under `assets/objects/` unless `--noobject` is passed) from `template_files/`, and registers it in
`include/tables/actor_table.h` and `spec/spec`.

## Architecture

### Source layout (`src/`)

- `boot/` — the small always-resident boot segment (entry point, decompression, DMA of the rest of the game).
- `code/` — the main resident "code" segment: core engine systems (player lib, actor lib, camera, collision,
  interface/HUD, save system, math, etc). Most gameplay-adjacent engine code lives here as `z_*.c` files.
- `overlays/` — code that is DMA'd in/out on demand rather than staying resident:
  - `overlays/actors/ovl_<Name>/` — one directory per actor (enemies, NPCs, props, doors, etc), each with a
    `z_<name>.c`/`.h` pair. This is by far the largest category (400+ actors).
  - `overlays/effects/`, `overlays/gamestates/` (title screen, file select, gameplay, etc), `overlays/misc/`.
- `libultra/`, `libc/`, `libc64/`, `libgcc/`, `libleo/`, `libu64/` — reimplementations of the N64/GameCube SDK and
  libc subsets the game links against.
- `audio/` — the audio driver/sequencer.
- `dmadata/`, `makerom/`, `n64dd/`, `usb/`, `debug/`, `compression/`, `gcc_fix/` — supporting subsystems.

Actors follow a common lifecycle contract: `Init`/`Destroy`/`Update`/`Draw` function pointers plus an `actionFunc`
pattern for internal state machines, declared via an `ActorInit`/`ActorProfile`-style struct — see
`template_files/z_actor.c` for the minimal shape and any existing `ovl_*` for real examples.

### Headers (`include/`)

- `include/config/` — the primary surface for *modding*: `config_debug.h`, `config_debug_features.h`,
  `config_debug_controls.h`, `config_game.h`, `config_graphics.h`, `config_memory.h`, `config_safeguards.h`. These
  are `#define NAME true/false` (or numeric) toggles for individual HackerOoT features; `config_safeguards.h`
  enforces cross-feature compatibility constraints (`#undef`s dependent features when a prerequisite is off).
- `include/tables/` — X-macro-style tables that register content: `actor_table.h`, `object_table.h`,
  `scene_table.h`, `entrance_table.h`, `effect_ss_table.h`, `dmadata_table.h`, `sequence_table.h`, `sfx/`. New
  actors/objects/scenes are registered here (usually automatically by `new_actor.py`).
- Everything else largely mirrors the original game's engine headers (`actor.h`, `play_state.h`, `camera.h`,
  `collision_check.h`, `z_lib.h`, etc).

### Assets (`assets/`)

Extracted/authored game data as source (XML + generated C), rebuilt into ROM-ready form by the asset pipeline in
`tools/`: `audio/`, `objects/` (actor object files, each `object_<name>/object_<name>.c/.h` plus any exported
skeleton/animation data like `gLinkChildSkel.c/.h`), `scenes/`, `text/`, `textures/`, `xml/`.

### Build/link plumbing

- `spec/spec` — the ROM segment/overlay specification (preprocessed, then consumed by `tools/mkldscript` and
  `tools/mkdmadata`) that defines what goes into which DMA segment and in what order. New overlays must be added
  here (`new_actor.py` does this automatically for actors).
- `tools/` — all bespoke build tooling: asset extraction/compression (`extract_*.py`, `z64compress`), ROM
  packing (`elf2rom`, `makeromfs`, `mkdmadata`, `mkldscript`), the ido-static-recomp toolchain wrapper
  (`ido_recomp`), the ASM-vs-C splicing tool (`asm_processor`), formatting/checking scripts, and misc patchers
  (`patch_ique_*.py`, `set_o32abi_bit.py`).
- `linker_scripts/` — linker script templates used per-version.
- `F3DEX3/` — submodule/vendor copy of the F3DEX3 microcode (LLE graphics microcode; only works on real hardware or
  LLE emulators like Ares/ParaLLEl, not HLE emulators like Project64).
- Non-matching code is expected: the project always builds with `-DNON_MATCHING -DAVOID_UB`, i.e. this is *not* a
  strict-matching decomp — new/modified code doesn't need to match original compiler output byte-for-byte. Compare
  against the original decomp (`docs/retail_versions.md`, `asm-differ`/`diff.py`) only if specifically trying to
  understand original behavior.

### Multiple ROM versions from one source tree

The same source builds many historical ROM versions (see the version table in README.md). Version-conditional code
uses `OOT_VERSION`, `OOT_REGION`, `PLATFORM_N64`/`PLATFORM_GC`/`PLATFORM_IQUE`, and `DEBUG_FEATURES` preprocessor
macros (set per-`VERSION` in the Makefile) rather than runtime checks. When touching engine code, consider whether a
change needs to be guarded for older versions/non-debug builds.

### Compiler

The build auto-detects a MIPS toolchain (`mips-n64-`, `mips64-`, `mips-linux-gnu-`, etc — see
`.make_hackeroot.mk`) and only supports `COMPILER=gcc`, using `ido-static-recomp`-hosted IDO only for the handful of
libultra/libgu functions where GCC's `-mips3` output is unsuitable (see the `MIPS_VERSION_IDO`/`CC_IDO` overrides
near the top of the Makefile's compile section). See `docs/compilers.md` for background on why both IDO and EGCS
existed in the original game.
