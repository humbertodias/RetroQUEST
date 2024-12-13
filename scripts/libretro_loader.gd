extends Node

@onready var sub_viewport = $room/SubViewport
@onready var texture_rect = $room/SubViewport/TextureRect

var current_core : Object = null  # The emulator core (passed dynamically)
var current_rom : String = ""  # Initialize to an empty string

func start_emulation(core_path: String, rom_path: String) -> bool:
	print("Starting emulation with core: ", core_path, ", ROM: ", rom_path)
	
	if not core_path or not rom_path:
		push_error("Core path or ROM path is missing.")
		return false

	# Load the core (emulator)
	print("Loading core...")
	current_core = load(core_path)
	if not current_core:
		push_error("Failed to load core: " + core_path)
		return false
	print("Core loaded successfully.")

	current_core.initialize()

	# Load the ROM
	print("Checking ROM file...")
	if not FileAccess.file_exists(rom_path):
		push_error("ROM not found: " + rom_path)
		return false
	print("ROM file exists.")

	var file = FileAccess.open(rom_path, FileAccess.READ)
	if not file:
		push_error("Error opening ROM: " + rom_path)
		return false
	print("ROM file opened successfully.")

	var rom_data = file.get_buffer(file.get_length())
	file.close()

	if not current_core.load_game(rom_data):
		push_error("Failed to load ROM: " + rom_path)
		return false
	print("ROM loaded successfully.")

	current_rom = rom_path
	print("Core and ROM loaded successfully.")

	# Wait for SubViewport to render at least one frame
	sub_viewport.render_target_update_mode = SubViewport.UPDATE_ALWAYS
	await get_tree().create_timer(0.1).timeout  # Delay ensures rendering starts

	# Assign the SubViewport texture
	var viewport_texture = sub_viewport.get_texture()
	if viewport_texture:
		texture_rect.texture = viewport_texture
		print("SubViewport texture assigned successfully.")
	else:
		push_error("Error: SubViewport texture is not ready.")
		return false

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
	if sub_viewport and texture_rect:
		print("SubViewport and TextureRect initialized successfully.")
	else:
		push_error("Error: SubViewport or TextureRect is missing.")

	# Ensure SubViewport always renders
	sub_viewport.render_target_update_mode = SubViewport.UPDATE_ALWAYS
