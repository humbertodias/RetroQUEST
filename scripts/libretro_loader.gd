extends Node

@onready var sub_viewport = $room/SubViewport
@onready var texture_rect = $room/SubViewport/TextureRect
@onready var retro_host = Engine.get_singleton("RetroHost")  # Get the RetroHost singleton

var current_core : Object = null  # The emulator core (passed dynamically)
var current_rom : String = ""  # Initialize to an empty string

func start_emulation(core_path: String, rom_path: String) -> bool:
	print("[libretro_loader] Starting emulation with core: ", core_path, ", ROM: ", rom_path)

	# Check if RetroHost is available
	if not retro_host:
		push_error("[libretro_loader] RetroHost singleton not found!")
		return false

	if not core_path:
		push_error("[libretro_loader] Core path is missing.")
		return false
	
	if not rom_path:
		push_error("[libretro_loader] ROM path is missing.")
		return false

	# Load the core (via RetroHost)
	print("[libretro_loader] Loading core using RetroHost...")
	var core_loaded = retro_host.load_core(core_path)
	if not core_loaded:
		push_error("[libretro_loader] Failed to load core: " + core_path)
		return false
	print("[libretro_loader] Core loaded successfully.")

	# Check if ROM file exists
	if not FileAccess.file_exists(rom_path):
		push_error("[libretro_loader] ROM not found: " + rom_path)
		return false
	print("[libretro_loader] ROM file exists.")

	# Load the ROM
	print("[libretro_loader] Opening ROM...")
	var file = FileAccess.open(rom_path, FileAccess.READ)
	if not file:
		push_error("[libretro_loader] Failed to open ROM: " + rom_path)
		return false

	var rom_data = file.get_buffer(file.get_length())
	file.close()
	print("[libretro_loader] ROM data loaded successfully.")

	# Pass ROM data to the core
	if not retro_host.core.load_game(rom_data):
		push_error("[libretro_loader] Failed to load ROM into core: " + rom_path)
		return false

	print("[libretro_loader] ROM loaded successfully.")

	current_rom = rom_path
	print("[libretro_loader] Core and ROM loaded successfully.")

	# Ensure SubViewport is ready
	sub_viewport.render_target_update_mode = SubViewport.UPDATE_ALWAYS

	# Wait for the SubViewport to initialize (up to 3 seconds)
	var max_wait_time = 3.0  # Maximum wait time in seconds
	var elapsed_time = 0.0
	while not sub_viewport.get_texture() and elapsed_time < max_wait_time:
		await get_tree().idle_frame  # Waits for the next frame
		elapsed_time += get_process_delta_time()
	if not sub_viewport.get_texture():
		push_error("[libretro_loader] Error: SubViewport texture is not ready after waiting.")
		return false

	texture_rect.texture = sub_viewport.get_texture()
	print("[libretro_loader] SubViewport texture assigned successfully.")
	return true

func _process(delta):
	"""
	Dynamically updates the TextureRect's texture during runtime.
	"""
	if current_core:
		current_core.run()

		var frame_data = current_core.get_frame_buffer()
		if frame_data:
			var frame_width = current_core.get_frame_width()
			var frame_height = current_core.get_frame_height()

			if frame_width > 0 and frame_height > 0:
				var image = Image.create_from_data(
					frame_width,
					frame_height,
					false,
					Image.FORMAT_RGB8,
					frame_data
				)
				var texture = ImageTexture.create_from_image(image)
				texture_rect.texture = texture

func _ready():
	"""
	Initializes the SubViewport and TextureRect.
	"""
	print("[libretro_loader] _ready: Initializing SubViewport and TextureRect.")
	if sub_viewport and texture_rect:
		print("[libretro_loader] SubViewport and TextureRect initialized successfully.")
	else:
		push_error("Error: SubViewport or TextureRect is missing.")
		return

	if not retro_host:
		push_error("[libretro_loader] RetroHost singleton not found! Emulation cannot proceed.")
		return
	print("[libretro_loader] RetroHost singleton initialized successfully.")

	# Ensure SubViewport always renders
	sub_viewport.render_target_update_mode = SubViewport.UPDATE_ALWAYS
	print("[libretro_loader] SubViewport set to always update.")

	# Use await to call the coroutine
	var success = await start_emulation("res://cores/genesis_plus_gx_libretro.so", "res://roms/megadrive/Sonic")
	if success:
		print("[libretro_loader] Emulation started successfully.")
	else:
		print("[libretro_loader] Failed to start emulation.")
