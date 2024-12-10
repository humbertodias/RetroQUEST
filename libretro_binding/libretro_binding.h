// libretro_binding.h
class LibretroCoreBinding : public GodotObject {
public:
    // Metodi da esporre a GDScript
    bool initialize();
    bool load_game(const PackedByteArray& rom_data);
    void run();
    PackedByteArray get_frame_buffer();
    int get_frame_width();
    int get_frame_height();
    void handle_input(const Ref<InputEvent>& event);
};
