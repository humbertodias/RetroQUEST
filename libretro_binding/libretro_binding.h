#ifndef LIBRETRO_CORE_BINDING_H
#define LIBRETRO_CORE_BINDING_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/object.hpp> // Correct base class

// Typedefs for libretro core functions
typedef void (*retro_init_t)();
typedef void (*retro_deinit_t)();
typedef bool (*retro_load_game_t)(const char *);
typedef void (*retro_run_t)();
typedef void (*retro_get_video_frame_t)(void **, unsigned *, unsigned *);

class LibretroCoreBinding : public godot::Object {
    GDCLASS(LibretroCoreBinding, godot::Object);

private:
    void *core_handle = nullptr;
    retro_init_t retro_init = nullptr;
    retro_deinit_t retro_deinit = nullptr;
    retro_load_game_t retro_load_game = nullptr;
    retro_run_t retro_run = nullptr;
    retro_get_video_frame_t retro_get_video_frame = nullptr;

    unsigned frame_width = 0;
    unsigned frame_height = 0;
    godot::PackedByteArray frame_buffer;

public:
    bool initialize(const godot::String &core_path);
    bool load_game(const godot::PackedByteArray &rom_data);
    void run();
    godot::PackedByteArray get_frame_buffer();
    int get_frame_width() const;
    int get_frame_height() const;
};

#endif // LIBRETRO_CORE_BINDING_H
