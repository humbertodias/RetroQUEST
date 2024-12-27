#include "gdextension_interface.h"

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"
#include "godot_cpp/classes/engine.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

#include "RetroHost.hpp"

// Singleton instance pointer
static RetroHost *retro_host_singleton = nullptr;

namespace {

    // Initialize the extension and register the singleton
    void initialize_extension(godot::ModuleInitializationLevel p_level) {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
        }

        godot::UtilityFunctions::print("[RetroHost] Initializing extension...");

        // Register the RetroHost class
        godot::ClassDB::register_class<RetroHost>();
        godot::UtilityFunctions::print("[RetroHost] RetroHost class registered.");

        // Create the singleton instance
        retro_host_singleton = memnew(RetroHost());
        if (!retro_host_singleton) {
            godot::UtilityFunctions::printerr("[RetroHost] Failed to allocate memory for singleton.");
        } else {
            godot::UtilityFunctions::print("[RetroHost] Singleton created successfully.");
        }

        // Register the singleton with the engine
        godot::Engine::get_singleton()->register_singleton("RetroHost", RetroHost::get_singleton());
        godot::UtilityFunctions::print("[RetroHost] Singleton registered successfully.");
    }

    // Uninitialize the extension and unregister the singleton
    void uninitialize_extension(godot::ModuleInitializationLevel p_level) {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
        }

        godot::UtilityFunctions::print("[RetroHost] Uninitializing extension...");

        // Unregister and delete the singleton instance
        if (retro_host_singleton) {
            godot::Engine::get_singleton()->unregister_singleton("RetroHost");
            memdelete(retro_host_singleton);
            retro_host_singleton = nullptr;
            godot::UtilityFunctions::print("[RetroHost] Singleton unregistered and memory released.");
        } else {
            godot::UtilityFunctions::printerr("[RetroHost] Singleton instance was null during uninitialization.");
        }
    }
}

// Entry point for the GDExtension system
extern "C" {
    GDExtensionBool GDE_EXPORT GDExtensionInit(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization) {
        
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        // Register the initializer and terminator functions
        init_obj.register_initializer(initialize_extension);
        init_obj.register_terminator(uninitialize_extension);
        init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
