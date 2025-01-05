extends Node3D

func _ready():
	"""
	Main entry point for the application.
	"""
	print("[main] Entering _ready function")
	if not RetroHost:
		push_error("[main] RetroHost singleton not found!")
		return

	var rom_path = "res://roms/megadrive/Sonic the Hedgehog.bin"
	var core_path = "genesis_plus_gx_libretro"

	print("[main] Starting emulation with core: ", core_path, ", ROM: ", rom_path)
	var success = RetroHost.load_core(core_path)
	if success:
		print("[main] Core loaded successfully.")
	else:
		print("[main] Failed to load core.")
		return

	var rom_file = FileAccess.open(rom_path, FileAccess.READ)
	if not rom_file:
		print("[main] Failed to open ROM file.")
		return

	var rom_data = rom_file.get_buffer(rom_file.get_length())
	rom_file.close()

	if RetroHost.load_game(rom_data):
		print("[main] ROM loaded successfully.")
	else:
		print("[main] Failed to load ROM.")
