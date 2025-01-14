#pragma once

#include "filesystem"
#include "godot_cpp/classes/image.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/object.hpp"
#include "libretro.h"
#include "yaml-cpp/yaml.h"

// Platform-specific includes
#ifdef _WIN32
#include <windows.h>
#define PLATFORM_WINDOWS
#elif __linux__
#include <dlfcn.h>
#define PLATFORM_LINUX
#elif __ANDROID__
#include <dlfcn.h>
#define PLATFORM_ANDROID
#endif

class RetroHost : public godot::Object
{
    GDCLASS(RetroHost, godot::Object)

public:
    godot::String cwd;
    static RetroHost *get_singleton();

    RetroHost();
    ~RetroHost();

    bool load_core(godot::String path);
    void unload_core();
    void run();
    void forwarded_input(const godot::Ref<godot::InputEvent> &event);
    bool load_game(const godot::Dictionary &game_info);

private:
    static RetroHost *singleton;

    godot::Ref<godot::Image> frame_buffer;
    godot::Ref<godot::Image> get_frame_buffer()
    {
        return frame_buffer;
    }

    std::vector<char *> please_free_me_str;

    YAML::Node core_variables;
    godot::String core_name;

    void load_core_variables();
    void save_core_variables();
    bool get_variable(retro_variable *variable);

    bool core_environment(unsigned cmd, void *data);

    void core_video_init(const struct retro_game_geometry *geometry);
    void core_video_refresh(const void *data, unsigned width, unsigned height, size_t pitch);
    bool core_video_set_pixel_format(unsigned format);
    godot::Image::Format pixel_format;

    void core_input_poll(void);
    int16_t core_input_state(unsigned port, unsigned device, unsigned index, unsigned id);

    void core_audio_init(retro_system_av_info av);
    void core_audio_sample(int16_t left, int16_t right);
    size_t core_audio_sample_batch(const int16_t *data, size_t frames);

    struct VFS
    {
        uint32_t supported_interface_version = 0;

        void init_vfs_interface();
        struct retro_vfs_interface vfs_interface;

        const char *get_path(retro_vfs_file_handle *stream);
        struct retro_vfs_file_handle *open(const char *path, unsigned mode, unsigned hints);
        int close(retro_vfs_file_handle *stream);
        int64_t size(struct retro_vfs_file_handle *stream);
        int64_t tell(struct retro_vfs_file_handle *stream);
        int64_t seek(struct retro_vfs_file_handle *stream, int64_t offset, int seek_position);
        int64_t read(struct retro_vfs_file_handle *stream, void *s, uint64_t len);
        int64_t write(struct retro_vfs_file_handle *stream, const void *s, uint64_t len);
        int flush(retro_vfs_file_handle *stream);
        int remove(const char *path);
        int rename(const char *old_path, const char *new_path);
        int64_t truncate(struct retro_vfs_file_handle *stream, int64_t length);
        int stat(const char *path, int32_t *size);
        int mkdir(const char *dir);
        struct retro_vfs_dir_handle *opendir(const char *dir, bool include_hidden_files);
        bool read_dir(struct retro_vfs_dir_handle *dir_stream);
        const char *dirent_get_name(struct retro_vfs_dir_handle *dir_stream);
        bool dirent_is_dir(struct retro_vfs_dir_handle *dir_stream);
        int closedir(struct retro_vfs_dir_handle *dir_stream);
    } vfs;

    struct
    {
#ifdef PLATFORM_WINDOWS
        HINSTANCE handle;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
        void *handle;
#endif
        bool initialized = false;

        void (*retro_init)(void);
        void (*retro_deinit)(void);
        unsigned (*retro_api_version)(void);
        void (*retro_get_system_info)(struct retro_system_info *info);
        void (*retro_get_system_av_info)(struct retro_system_av_info *info);
        void (*retro_set_controller_port_device)(unsigned port, unsigned device);
        void (*retro_reset)(void);
        void (*retro_run)(void);
        bool (*retro_load_game)(const struct retro_game_info *game);
        void (*retro_unload_game)(void);

        retro_keyboard_event_t retro_keyboard_event_callback = nullptr;
    } core;

protected:
    static void _bind_methods();
};
