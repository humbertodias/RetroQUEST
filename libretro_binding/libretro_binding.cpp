#include "libretro_binding.h"
#include <dlfcn.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <fstream>

using namespace godot;

bool LibretroCoreBinding::initialize(const String &core_path) {
    UtilityFunctions::print("Loading core: ", core_path);
    core_handle = dlopen(core_path.utf8().get_data(), RTLD_LAZY);
    if (!core_handle) {
        UtilityFunctions::print("Error loading core: ", dlerror());
        return false;
    }

    // Link functions
    retro_init = (retro_init_t)dlsym(core_handle, "retro_init");
    retro_deinit = (retro_deinit_t)dlsym(core_handle, "retro_deinit");
    retro_load_game = (retro_load_game_t)dlsym(core_handle, "retro_load_game");
    retro_run = (retro_run_t)dlsym(core_handle, "retro_run");
    retro_get_video_frame = (retro_get_video_frame_t)dlsym(core_handle, "retro_get_video_frame");

    if (!retro_init || !retro_deinit || !retro_load_game || !retro_run || !retro_get_video_frame) {
        UtilityFunctions::print("Error: Missing functions in core.");
        dlclose(core_handle);
        core_handle = nullptr;
        return false;
    }

    retro_init();
    UtilityFunctions::print("Core successfully initialized.");
    return true;
}

bool LibretroCoreBinding::load_game(const PackedByteArray &rom_data) {
    if (!core_handle) {
        UtilityFunctions::print("Error: Core not loaded.");
        return false;
    }

    // Save ROM to a temporary file
    std::string temp_rom_path = "/tmp/libretro_temp.rom";
    std::ofstream temp_file(temp_rom_path, std::ios::binary);
    if (!temp_file.is_open()) {
        UtilityFunctions::print("Error: Unable to open temporary ROM file.");
        return false;
    }

    // Write the ROM data to the file
    temp_file.write(reinterpret_cast<const char *>(rom_data.ptr()), rom_data.size());
    temp_file.close();

    bool result = retro_load_game(temp_rom_path.c_str());
    if (result) {
        UtilityFunctions::print("ROM successfully loaded: ", temp_rom_path.c_str());
    } else {
        UtilityFunctions::print("Error: Failed to load ROM.");
    }

    return result;
}

void LibretroCoreBinding::run() {
    if (!core_handle || !retro_run) {
        UtilityFunctions::print("Error: Core not initialized.");
        return;
    }

    retro_run();
}

PackedByteArray LibretroCoreBinding::get_frame_buffer() {
    if (!core_handle || !retro_get_video_frame) {
        UtilityFunctions::print("Error: Core not initialized.");
        return PackedByteArray();
    }

    void *frame = nullptr;
    retro_get_video_frame(&frame, &frame_width, &frame_height);

    frame_buffer.resize(frame_width * frame_height * 4); // Assume RGBA format
    memcpy(frame_buffer.ptrw(), frame, frame_buffer.size());
    return frame_buffer;
}

int LibretroCoreBinding::get_frame_width() const {
    return frame_width;
}

int LibretroCoreBinding::get_frame_height() const {
    return frame_height;
}
