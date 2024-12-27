#include "RetroHost.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/project_settings.hpp>

#include <fstream>
#include <iostream>

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

// Returns the last error message as a string
std::string GetLastErrorAsStr()
{
#ifdef PLATFORM_WINDOWS
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string();
    }

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                     FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                 (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);
    LocalFree(messageBuffer);

    return message;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    return dlerror(); // Linux and Android use dlerror for error reporting.
#else
    return "Error information not available on this platform";
#endif
}

RetroHost::RetroHost()
{
    godot::UtilityFunctions::print("[RetroHost] Constructor");
    singleton = this;
    this->vfs.init_vfs_interface();
}

RetroHost::~RetroHost()
{
    godot::UtilityFunctions::print("[RetroHost] Destructor");
    this->unload_core();
}

RetroHost *RetroHost::singleton = nullptr;

RetroHost *RetroHost::get_singleton()
{
    return singleton;
}

#define load_symbol_return_false_on_err(handle, dest, sym)                                           \
    do {                                                                                            \
        godot::UtilityFunctions::print("[RetroHost] Loading core symbol \"", #sym, "\"");           \
        dest = (decltype(dest))dlsym(handle, #sym);                                                 \
        if (dest == nullptr) {                                                                      \
            godot::String error_msg = "[RetroHost] Could not load symbol \"" + godot::String(#sym) + \
                                      "\": " + godot::String(GetLastErrorAsStr().c_str());           \
            godot::UtilityFunctions::printerr(error_msg);                                           \
            return false;                                                                           \
        }                                                                                           \
    } while (0)

bool RetroHost::load_core(godot::String name) {
    this->unload_core();
    godot::UtilityFunctions::print("[RetroHost] Starting load_core with name: ", name);

    godot::String lib_path;
    if (godot::OS::get_singleton()->has_feature("editor")) {
        this->cwd =
            godot::ProjectSettings::get_singleton()->globalize_path("res://") + "libretro-cores/";
        lib_path = cwd + name + ".dll"; // Editor path (Windows assumed default)
        godot::UtilityFunctions::print("[RetroHost] Editor mode detected. Core path: ", lib_path);
    } else {
        this->cwd = godot::OS::get_singleton()->get_executable_path().get_base_dir();
        lib_path = cwd + "/" + name;
        godot::UtilityFunctions::print("[RetroHost] Runtime mode detected. Core path: ", lib_path);
    }

#ifdef PLATFORM_WINDOWS
    this->core.handle = LoadLibrary(lib_path.utf8().get_data());
    if (this->core.handle == NULL) {
            godot::UtilityFunctions::printerr("[RetroHost] Failed to load core \"", lib_path, "\". Error: ", GetLastErrorAsStr().c_str());
        return false;
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    this->core.handle = dlopen(lib_path.utf8().get_data(), RTLD_LAZY);
    if (this->core.handle == nullptr) {
        godot::UtilityFunctions::printerr("[RetroHost] Failed to load core \"", lib_path, "\". Error: ", GetLastErrorAsStr().c_str());
        return false;
    }
#endif

    godot::UtilityFunctions::print("[RetroHost] Core library loaded successfully.");

    // Load RetroArch symbols dynamically
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_init, retro_init);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_deinit, retro_deinit);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_api_version, retro_api_version);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_get_system_info, retro_get_system_info);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_get_system_av_info, retro_get_system_av_info);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_set_controller_port_device, retro_set_controller_port_device);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_reset, retro_reset);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_run, retro_run);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_load_game, retro_load_game);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_unload_game, retro_unload_game);

    godot::UtilityFunctions::print("[RetroHost] All symbols loaded successfully.");

    this->core_name = name;
    this->load_core_variables();

    godot::UtilityFunctions::print("[RetroHost] Initializing core...");
    this->core.retro_init();
    godot::UtilityFunctions::print("[RetroHost] Core initialized successfully.");

    godot::UtilityFunctions::print("[RetroHost] Attempting to load game...");
    if (!this->core.retro_load_game(nullptr)) {
        godot::UtilityFunctions::printerr("[RetroHost] Failed to load game.");
        return false;
    }
    godot::UtilityFunctions::print("[RetroHost] Game loaded successfully.");

    struct retro_system_av_info av;
    this->core.retro_get_system_av_info(&av);
    godot::UtilityFunctions::print("[RetroHost] Retrieved system AV info.");

    this->core_video_init(&av.geometry);
    godot::UtilityFunctions::print("[RetroHost] Video initialized.");

    this->core_audio_init(av);
    godot::UtilityFunctions::print("[RetroHost] Audio initialized.");

    this->core.initialized = true;
    godot::UtilityFunctions::print("[RetroHost] Core fully initialized and ready.");
    return true;
}

void RetroHost::unload_core()
{
    if (this->core.initialized)
    {
        godot::UtilityFunctions::print("[RetroHost] Deinitializing core...");
        this->core.retro_deinit();
        this->core.initialized = false;
    }

#ifdef PLATFORM_WINDOWS
    if (this->core.handle != NULL)
    {
        FreeLibrary(this->core.handle);
        this->core.handle = NULL;
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    if (this->core.handle != nullptr)
    {
        dlclose(this->core.handle);
        this->core.handle = nullptr;
    }
#endif
    godot::UtilityFunctions::print("[RetroHost] Core unloaded successfully.");
}

void RetroHost::run(){

    godot::UtilityFunctions::print("[RetroHost] Starting core run...");

    if (!this->core.initialized)
    {
        godot::UtilityFunctions::printerr("[RetroHost] Cannot run. Core not initialized.");
        return;
    }
    this->core.retro_run();
    godot::UtilityFunctions::print("[RetroHost] Core ran successfully.");
}

void RetroHost::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("load_core", "name"), &RetroHost::load_core);
    godot::ClassDB::bind_method(godot::D_METHOD("unload_core"), &RetroHost::unload_core);
    godot::ClassDB::bind_method(godot::D_METHOD("run"), &RetroHost::run);
}
