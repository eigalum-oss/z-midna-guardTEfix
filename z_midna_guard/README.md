# Z Midna Guard

Stops the **Z button** from calling Midna. Built to fix the Twilit Essentials Boss Rush
(Normal mode) calling Midna on Z while a Z item slot is in use.

## How it works
It post-hooks `daAlink_c::midnaTalkTrigger()`. If the Midna call was triggered by Z
(`mItemTrigger & BTN_Z`), the result is set back to false. Midna's own button (L / D-Pad Left)
does not set `BTN_Z`, so it keeps working. Z items are untouched.

## Important
- It applies **everywhere**, not only in the Boss Rush (a third-party mod can't reliably tell which
  game mode Twilit Essentials registered). If you ever want Z to call Midna again, disable this mod.
- Keep Midna on her own button (Twilit Essentials > Controls > Midna button).
- Built and compile-checked against Dusklight **v2.0.3** (Linux). Not run in-game.

## Build for Windows
Easiest: push this folder to a new GitHub repo. The included Actions workflow builds every
platform; download the `mod-combined` artifact (a `.dusk`).

Local: install Visual Studio Build Tools (C++ workload), CMake and Git, then in a
"x64 Native Tools" prompt:

    cmake -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
    cmake --build build --config RelWithDebInfo

Result: `build/mods/z_midna_guard.dusk`. Copy it to `%APPDATA%\TwilitRealm\Dusklight\mods`,
then enable it in the in-game Mod Manager.
If your Dusklight is not 2.0.3, change `DUSKLIGHT_VERSION` in CMakeLists.txt.
