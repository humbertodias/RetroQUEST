#include "gdextension_interface.h"

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"
#include "godot_cpp/classes/engine.hpp"
//#include "godot_cpp/variant/utility_functions.hpp"

#include "RetroHost.hpp"

static RetroHost *retro_host_singleton = nullptr;

namespace {
    void initialize_extension(godot::ModuleInitializationLevel p_level) {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
        }

        godot::ClassDB::register_class<RetroHost>();

        retro_host_singleton = memnew(RetroHost());
        godot::Engine::get_singleton()->register_singleton("RetroHost", RetroHost::get_singleton());
    }

    void uninitialize_extension(godot::ModuleInitializationLevel p_level) {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
        }
        godot::Engine::get_singleton()->unregister_singleton("RetroHost");
        memdelete(retro_host_singleton);
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT GDExtensionInit(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization) {
        //godot::UtilityFunctions::print("[LibRetroHost] GDExtensionInit called");
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_extension);
        init_obj.register_terminator(uninitialize_extension);
        init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
