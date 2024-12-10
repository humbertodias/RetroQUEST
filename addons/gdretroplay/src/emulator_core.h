#ifndef EMULATOR_CORE_H
#define EMULATOR_CORE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/audio_stream_generator.hpp>
#include <godot_cpp/classes/audio_stream_generator_playback.hpp>
#include <memory>
#include <string>
#include <vector>
#include <array>

namespace EmulatorSystem {

class EmulatorCore : public godot::Node {
    GDCLASS(EmulatorCore, godot::Node)

private:
    // Strutture per la gestione del core
    struct CoreFunctions {
        void* handle{nullptr};
        void (*init)();
        void (*deinit)();
        void (*run)();
        bool (*load_game)(const void* data, size_t size);
        bool (*save_game_state)(void* data, size_t size);
        bool (*load_game_state)(const void* data, size_t size);
        bool (*get_memory_data)(unsigned id, void* data);
        bool (*set_memory_data)(unsigned id, const void* data);
        void (*set_controller_port_device)(unsigned port, unsigned device);
        size_t (*serialize_size)();
    };

    // Strutture per la gestione dell'audio/video
    struct SystemInfo {
        unsigned width{0};
        unsigned height{0};
        double fps{60.0};
        double sample_rate{44100.0};
        unsigned input_ports{2};
    };

    // Membri privati
    std::unique_ptr<CoreFunctions> core;
    SystemInfo system_info;
    std::vector<uint8_t> game_data;
    std::vector<uint8_t> save_data;
    std::string save_path;
    
    godot::Ref<godot::ImageTexture> frame_texture;
    godot::Ref<godot::AudioStreamGenerator> audio_stream;
    godot::Ref<godot::AudioStreamGeneratorPlayback> audio_playback;
    
    std::vector<uint8_t> frame_buffer;
    std::array<uint16_t, 16> input_state;
    
    // Buffer per states
    std::vector<uint8_t> state_buffer;

    // Funzioni private
    bool load_core_functions();
    void setup_av_system();
    void cleanup();
    bool load_sram();
    bool save_sram();
    
    // Callback handlers
    static void video_callback(const void* data, unsigned width, 
                             unsigned height, size_t pitch);
    static void audio_callback(int16_t left, int16_t right);
    static void input_poll_callback();
    static int16_t input_state_callback(unsigned port, unsigned device, 
                                      unsigned index, unsigned id);

protected:
    static void _bind_methods();

public:
    EmulatorCore();
    ~EmulatorCore();

    // Funzioni principali
    bool initialize_core(const godot::String& core_path);
    bool load_game(const godot::String& game_path);
    void process_frame();
    void reset();
    void close_game();
    
    // Gestione stati
    bool save_state(const godot::String& path);
    bool load_state(const godot::String& path);
    
    // Input
    void set_button_pressed(int port, int button, bool pressed);
    void set_axis_value(int port, int axis, float value);
    
    // Getters
    godot::Ref<godot::ImageTexture> get_texture() const { return frame_texture; }
    godot::Ref<godot::AudioStreamGenerator> get_audio_stream() const { return audio_stream; }
    
    // Configurazione
    void set_audio_buffer_size(float seconds);
    void set_controller_type(int port, int device_type);
};

} // namespace EmulatorSystem

#endif // EMULATOR_CORE_H
