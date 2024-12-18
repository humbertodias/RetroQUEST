extends Node

@onready var loader = preload("res://scripts/libretro_loader.gd").new()

func _ready():
	var core_path = "res://cores/genesis_plus_gx_libretro.so"  # Replace with your actual core path
	if not FileAccess.file_exists(core_path):
		push_error("Core not found at: " + core_path)
	return false

	var rom_path = "res://roms/megadrive/Sonic the Hedgehog.bin"  # Replace with your actual ROM path
	if not FileAccess.file_exists(rom_path):
		push_error("Rom not found at: " + rom_path)
	return false

	print("Core path: ", core_path)
	print("ROM path: ", rom_path)

	var success = await loader.start_emulation(core_path, rom_path)  # Use await to call the coroutine
	if success:
		print("Game started successfully.")
		start_emulation_loop()
	else:
		print("Failed to start the game.")

func start_emulation_loop():
	"""
	Continuously runs the emulation in the `_process` callback.
	"""
	set_process(true)

func _process(delta):
	loader._process(delta)  # Delegate the frame updates to the loader
