#include "emulator_core.h"
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/image.hpp>
#include <dlfcn.h>

namespace EmulatorSystem {

EmulatorCore::EmulatorCore() {
    core = std::make_unique<CoreFunctions>();
    frame_texture.instantiate();
    audio_stream.instantiate();
    input_state.fill(0);
}

EmulatorCore::~EmulatorCore() {
    cleanup();
}

bool EmulatorCore::initialize_core(const godot::String& core_path) {
    cleanup();
    
    core->handle = dlopen(core_path.utf8().get_data(), RTLD_LAZY);
    if (!core->handle) return false;
    
    if (!load_core_functions()) {
        cleanup();
        return false;
    }
    
    core->init();
    setup_av_system();
    
    return true;
}

bool EmulatorCore::load_core_functions() {
    if (!core->handle) return false;

    #define LOAD_SYM(sym) \
        core->sym = (decltype(core->sym))dlsym(core->handle, "retro_" #sym)
        
    LOAD_SYM(init);
    LOAD_SYM(deinit);
    LOAD_SYM(run);
    LOAD_SYM(load_game);
    LOAD_SYM(save_game_state);
    LOAD_SYM(load_game_state);
    LOAD_SYM(get_memory_data);
    LOAD_SYM(set_memory_data);
    LOAD_SYM(set_controller_port_device);
    LOAD_SYM(serialize_size);
    
    #undef LOAD_SYM
    
    return (core->init && core->run && core->load_game);
}

bool EmulatorCore::load_game(const godot::String& game_path) {
    godot::Ref<godot::FileAccess> f = godot::FileAccess::open(game_path, godot::FileAccess::READ);
    if (f.is_null()) return false;
    
    save_path = game_path.get_basename() + ".srm";
    game_data.resize(f->get_length());
    f->get_buffer(game_data.data(), game_data.size());
    
    if (!core->load_game(game_data.data(), game_data.size())) {
        return false;
    }
    
    // Inizializza il buffer per gli states
    if (core->serialize_size) {
        state_buffer.resize(core->serialize_size());
    }
    
    // Carica SRAM se esiste
    load_sram();
    
    return true;
}

void EmulatorCore::process_frame() {
    if (core->run) {
        core->run();
    }
}

bool EmulatorCore::save_state(const godot::String& path) {
    if (!core->save_game_state || state_buffer.empty()) return false;
    
    if (!core->save_game_state(state_buffer.data(), state_buffer.size())) {
        return false;
    }
    
    godot::Ref<godot::FileAccess> f = godot::FileAccess::open(path, godot::FileAccess::WRITE);
    if (f.is_null()) return false;
    
    f->store_buffer(state_buffer.data(), state_buffer.size());
    return true;
}

bool EmulatorCore::load_state(const godot::String& path) {
    if (!core->load_game_state || state_buffer.empty()) return false;
    
    godot::Ref<godot::FileAccess> f = godot::FileAccess::open(path, godot::FileAccess::READ);
    if (f.is_null()) return false;
    
    f->get_buffer(state_buffer.data(), state_buffer.size());
    return core->load_game_state(state_buffer.data(), state_buffer.size());
}

bool EmulatorCore::load_sram() {
    if (!core->get_memory_data) return false;
    
    godot::Ref<godot::FileAccess> f = godot::FileAccess::open(save_path, godot::FileAccess::READ);
    if (f.is_null()) return false;
    
    save_data.resize(f->get_length());
    f->get_buffer(save_data.data(), save_data.size());
    
    return core->set_memory_data(0, save_data.data());
}

bool EmulatorCore::save_sram() {
    if (!core->get_memory_data) return false;
    
    if (!core->get_memory_data(0, save_data.data())) {
        return false;
    }
    
    godot::Ref<godot::FileAccess> f = godot::FileAccess::open(save_path, godot::FileAccess::WRITE);
    if (f.is_null()) return false;
    
    f->store_buffer(save_data.data(), save_data.size());
    return true;
}

void EmulatorCore::set_button_pressed(int port, int button, bool pressed) {
    if (port >= 0 && port < system_info.input_ports && button < 16) {
        if (pressed) {
            input_state[port] |= (1 << button);
        } else {
            input_state[port] &= ~(1 << button);
        }
    }
}

void EmulatorCore::set_axis_value(int port, int axis, float value) {
    // Implementa la gestione degli assi analogici se necessario
}

void EmulatorCore::video_callback(const void* data, unsigned width, 
                                unsigned height, size_t pitch) {
    // Implementa il rendering del frame
    // ...
}

void EmulatorCore::audio_callback(int16_t left, int16_t right) {
    // Implementa la gestione dell'audio
    // ...
}

void EmulatorCore::_bind_methods() {
    using namespace godot;
    
    ClassDB::bind_method(D_METHOD("initialize_core", "core_path"), 
                        &EmulatorCore::initialize_core);
    ClassDB::bind_method(D_METHOD("load_game", "game_path"), 
                        &EmulatorCore::load_game);
    ClassDB::bind_method(D_METHOD("process_frame"), 
                        &EmulatorCore::process_frame);
    ClassDB::bind_method(D_METHOD("save_state", "path"), 
                        &EmulatorCore::save_state);
    ClassDB::bind_method(D_METHOD("load_state", "path"), 
                        &EmulatorCore::load_state);
    ClassDB::bind_method(D_METHOD("set_button_pressed", "port", "button", "pressed"), 
                        &EmulatorCore::set_button_pressed);
    ClassDB::bind_method(D_METHOD("set_axis_value", "port", "axis", "value"), 
                        &EmulatorCore::set_axis_value);
    ClassDB::bind_method(D_METHOD("get_texture"), 
                        &EmulatorCore::get_texture);
    ClassDB::bind_method(D_METHOD("get_audio_stream"), 
                        &EmulatorCore::get_audio_stream);
}

} // namespace EmulatorSystem
