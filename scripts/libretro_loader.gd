extends Node

@onready var tv_viewport: SubViewport = $CRTTV/SubViewport
@onready var tv_texture_rect: TextureRect = $CRTTV/SubViewport/TextureRect

var current_core = null
var current_rom = null

func load_libretro_core(core_path: String) -> bool:
    current_core = load(core_path)
    if not current_core:
        push_error("Failed to load core: " + core_path)
        return false
    current_core.initialize()
    return true

func load_rom(rom_path: String) -> bool:
    if not FileAccess.file_exists(rom_path):
        push_error("ROM not found: " + rom_path)
        return false

    var file = FileAccess.open(rom_path, FileAccess.READ)
    if not file:
        push_error("Error opening ROM: " + rom_path)
        return false

    var rom_data = file.get_buffer(file.get_length())
    file.close()

    if not current_core.load_game(rom_data):
        push_error("Failed to load ROM: " + rom_path)
        return false

    current_rom = rom_path
    return true

func start_emulation(core_path: String, rom_path: String) -> bool:
    if not load_libretro_core(core_path):
        return false
    if not load_rom(rom_path):
        return false
    current_core.run()
    return true

func _process(delta):
    if current_core:
        var frame_data = current_core.get_frame_buffer()
        if frame_data:
            var image = Image.create_from_data(
                current_core.get_frame_width(),
                current_core.get_frame_height(),
                false,
                Image.FORMAT_RGB8,
                frame_data
            )
            var texture = ImageTexture.create_from_image(image)
            tv_texture_rect.texture = texture
