extends Node

@onready var sub_viewport = $room/SubViewport
@onready var texture_rect = $room/SubViewport/TextureRect

func start_emulation(core_name: String, rom_path: String) -> bool:
	print("[libretro_loader] Starting emulation with core: ", core_name, ", ROM: ", rom_path)

	# Load the core
	if not RetroHost.load_core(core_name):
		push_error("[libretro_loader] Failed to load core: " + core_name)
		return false
	print("[libretro_loader] Core path: ", core_name)
	print("[libretro_loader] Core loaded successfully.")

	# Open the ROM file
	var file = FileAccess.open(rom_path, FileAccess.READ)
	if not file:
		push_error("[libretro_loader] Failed to open ROM: " + rom_path)
		return false
	print("[libretro_loader] ROM path: ", rom_path)

	var rom_data = file.get_buffer(file.get_length())
	file.close()
	print("[libretro_loader] ROM data loaded successfully.")

	# Pass ROM data to the core using RetroHost
	var game_info = {}
	game_info["data"] = rom_data
	game_info["size"] = rom_data.size()

	if not RetroHost.load_game(game_info):
		push_error("[libretro_loader] Failed to load ROM into the core.")
		return false

	print("[libretro_loader] Core and ROM loaded successfully.")
	return true

func _process(delta):
	"""
	Run the core and update the framebuffer.
	"""
	RetroHost.run()

	var frame_buffer = RetroHost.get_frame_buffer()
	if frame_buffer:
		var img_tex = ImageTexture.create_from_image(frame_buffer)
		texture_rect.texture = img_tex

func _ready():
	"""
	Initialize and start emulation.
	"""
	print("[libretro_loader] _ready: Initializing...")
	var success = start_emulation("genesis_plus_gx_libretro", "res://roms/megadrive/Sonic the Hedgehog.bin")
	if success:
		print("[libretro_loader] Emulation started successfully.")
	else:
		print("[libretro_loader] Failed to start emulation.")
