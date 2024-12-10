// libretro_binding.cpp
#include "libretro_binding.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <dlfcn.h>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/input_event.hpp>


using namespace godot;

// Funzioni richieste dai core libretro
typedef void (*retro_init_t)();
typedef void (*retro_deinit_t)();
typedef bool (*retro_load_game_t)(const char *);
typedef void (*retro_run_t)();
typedef void (*retro_get_system_info_t)(struct retro_system_info *);
typedef void (*retro_get_video_frame_t)(void **frame, unsigned *width, unsigned *height);

class LibretroCoreBinding : public GodotObject {
    GDCLASS(LibretroCoreBinding, Object);

private:
    void *core_handle = nullptr; // Handle del core caricato
    retro_init_t retro_init = nullptr;
    retro_deinit_t retro_deinit = nullptr;
    retro_load_game_t retro_load_game = nullptr;
    retro_run_t retro_run = nullptr;
    retro_get_video_frame_t retro_get_video_frame = nullptr;

    unsigned frame_width = 0;
    unsigned frame_height = 0;
    PackedByteArray frame_buffer;

public:
    bool initialize(const String &core_path) {
        UtilityFunctions::print("Caricamento del core: ", core_path);
        core_handle = dlopen(core_path.utf8().get_data(), RTLD_LAZY);
        if (!core_handle) {
            UtilityFunctions::print("Errore nel caricamento del core: ", dlerror());
            return false;
        }

        // Collegamento delle funzioni
        retro_init = (retro_init_t)dlsym(core_handle, "retro_init");
        retro_deinit = (retro_deinit_t)dlsym(core_handle, "retro_deinit");
        retro_load_game = (retro_load_game_t)dlsym(core_handle, "retro_load_game");
        retro_run = (retro_run_t)dlsym(core_handle, "retro_run");
        retro_get_video_frame = (retro_get_video_frame_t)dlsym(core_handle, "retro_get_video_frame");

        if (!retro_init || !retro_deinit || !retro_load_game || !retro_run || !retro_get_video_frame) {
            UtilityFunctions::print("Errore: funzioni mancanti nel core.");
            dlclose(core_handle);
            core_handle = nullptr;
            return false;
        }

        retro_init();
        UtilityFunctions::print("Core inizializzato con successo.");
        return true;
    }

    bool load_game(const PackedByteArray &rom_data) {
        if (!core_handle || !retro_load_game) {
            UtilityFunctions::print("Errore: Core non inizializzato.");
            return false;
        }

        // Salviamo temporaneamente il file ROM
        String temp_rom_path = "/tmp/libretro_temp.rom";
        File *temp_file = File::open(temp_rom_path, File::WRITE);
        temp_file->store_buffer(rom_data);
        temp_file->close();
        memdelete(temp_file);

        bool result = retro_load_game(temp_rom_path.utf8().get_data());
        if (result) {
            UtilityFunctions::print("ROM caricata con successo: ", temp_rom_path);
        } else {
            UtilityFunctions::print("Errore nel caricamento della ROM.");
        }

        return result;
    }

    void run() {
        if (!core_handle || !retro_run) {
            UtilityFunctions::print("Errore: Core non inizializzato.");
            return;
        }

        retro_run();
    }

    PackedByteArray get_frame_buffer() {
        if (!core_handle || !retro_get_video_frame) {
            UtilityFunctions::print("Errore: Core non inizializzato.");
            return PackedByteArray();
        }

        void *frame = nullptr;
        retro_get_video_frame(&frame, &frame_width, &frame_height);

        frame_buffer.resize(frame_width * frame_height * 4); // Assumiamo formato RGBA
        memcpy(frame_buffer.ptrw(), frame, frame_buffer.size());
        return frame_buffer;
    }

    int get_frame_width() const { return frame_width; }
    int get_frame_height() const { return frame_height; }
};
