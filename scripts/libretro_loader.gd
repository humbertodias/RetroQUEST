# libretro_loader.gd
extends Node

# Configurazione SubViewport TV
@onready var tv_viewport: SubViewport = $CRTTV/SubViewport
@onready var tv_texture_rect: TextureRect = $CRTTV/SubViewport/TextureRect

# Stato dell'emulazione
var current_core = null
var current_rom = null

# Funzione per caricare un core
func load_libretro_core(core_path: String):
    # Caricamento dinamico del core
    current_core = load(core_path)

    if not current_core:
        push_error("Impossibile caricare il core: " + core_path)
        return false

    # Inizializzazione base del core
    current_core.initialize()
    return true

# Funzione per caricare una ROM
func load_rom(rom_path: String):
    # Verifica esistenza ROM
    if not FileAccess.file_exists(rom_path):
        push_error("ROM non trovata: " + rom_path)
        return false

    # Caricamento dati ROM
    var rom_data = FileAccess.get_file_as_bytes(rom_path)

    # Caricamento ROM nel core
    var load_result = current_core.load_game(rom_data)

    if load_result:
        current_rom = rom_path

        return load_result

    # Funzione per avviare l'emulazione
    func start_emulation(core_path: String, rom_path: String):
        # Caricamento core
        if not load_libretro_core(core_path):
            return false

        # Caricamento ROM
        if not load_rom(rom_path):
            return false

        # Avvio emulazione
        current_core.run()
        return true

    # Processo di rendering
    func _process(delta):
        if current_core:
            # Recupero frame corrente
            var frame_data = current_core.get_frame_buffer()

            if frame_data:
                # Conversione in texture
                var image = Image.create_from_data(
                    current_core.get_frame_width(),
                    current_core.get_frame_height(),
                    false,
                    Image.FORMAT_RGB8,
                    frame_data
                    )

                var texture = ImageTexture.create_from_image(image)

                # Applicazione texture alla TV
                tv_texture_rect.texture = texture

                # Esempio di utilizzo
                func _ready():
                    # Percorsi di esempio
                    var CORE_PATH = "res://cores/genesis_plus_gx_libretro.so"
                    var ROM_PATH = "res://roms/megadrive/Sonic.bin"

                    # Avvio emulazione
                    start_emulation(CORE_PATH, ROM_PATH)

                    # Gestione input
                    func _input(event):
                        if current_core:
                            # Conversione input Godot in input Libretro
                            current_core.handle_input(event)
