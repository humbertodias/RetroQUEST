clear
rm "prompt.md"

write(){
    echo "$1" >> ./prompt.md
}

write "RetroQUEST is an application mainly written for Meta Quest 3 with Linux non-VR support in Godot 4.3.
In the future will be added supporto for Widnows, Mac and other VRs as well.
The app is working mainly with VR controls but can be used even with desktop controls (mouse, keyboard, controllers).
The app is Quest Native and not PCVR."

write "The scope of this application is to emulate games and render them on a virtual CRT TV in the VR space, more features will be added later."
write "The first iteration will be to be able to run the rom "roms/megadrive/Sonic the Hedgehog.bin" with the libretro core "cores/genesis_plus_gx_libretro.so", more features will be added later, for now I will be happy to see the game just running."
write "For this scope I am using gdlibretro (https://github.com/gabrielmedici/gdlibretro) with some modifications to make it work on Linux and Android."

write "Here is my directory structure"
write "$(tree . -L 2)"

write "Now I will cat you the main files for you to understand better the project."

files="project.godot main.tscn scripts/emulate.gd scripts/libretro_loader.gd addons/gdlibretro.gdextension addons/LibRetroHost.gdextension gdlibretro/src/CoreEnvironment.cpp gdlibretro/src/RetroHost.cpp gdlibretro/src/RetroHost.hpp gdlibretro/src/Video.cpp gdlibretro/src/RegisterExtension.cpp gdlibretro/src/CMakeLists.txt"

for file in $files; do
    if [ -f "$file" ]; then
        write "--- $file ---"
        write "$(cat $file)"
        write "--- end of $file ---"
        write ""
    fi
done

write ""
write "My issue now is the following, can you help me to fix it?"
write '
My issue is that I am not able to start the emulated game, I am getting the following error:

Godot Engine v4.3.stable.flathub.77dcf97d8 - https://godotengine.org
OpenGL API 4.6 (Core Profile) Mesa 24.2.7 (git-3900828265) - Compatibility - Using Device: Intel - Mesa Intel(R) Graphics (ADL GT2)

[RetroHost] Initializing extension...
[RetroHost] RetroHost class registered.
[RetroHost] Constructor called. Initializing singleton.
[RetroHost] Initialization complete.
[RetroHost] Singleton registered successfully.
[main] Entering _ready function
[main] File res://cores/genesis_plus_gx_libretro.so exists
[main] File res://roms/megadrive/Sonic the Hedgehog.bin exists
[main] Core path: res://cores/genesis_plus_gx_libretro.so
[main] ROM path: res://roms/megadrive/Sonic the Hedgehog.bin
[libretro_loader] Starting emulation with core: res://cores/genesis_plus_gx_libretro.so, ROM: res://roms/megadrive/Sonic the Hedgehog.bin
[libretro_loader] RetroHost status: <null>
[libretro_loader] RetroHost singleton not found!
[main] Failed to start the game
'