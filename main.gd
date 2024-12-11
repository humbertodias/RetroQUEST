extends Node3D

var xr_interface: XRInterface
var emulator_script: Object

func _ready():
	# Inizializzazione OpenXR
	xr_interface = XRServer.find_interface("OpenXR")
	if xr_interface and xr_interface.is_initialized():
		print("OpenXR initialized successfully")
		DisplayServer.window_set_vsync_mode(DisplayServer.VSYNC_DISABLED)
		get_viewport().use_xr = true
	else:
		print("OpenXR not initialized, please check if your headset is connected")

	# Carica lo script dell'emulatore
	emulator_script = preload("res://scripts/emulate.gd").new()

func launch_game():
	var core_path = "res://cores/genesis_plus_gx_libretro.so"
	var rom_path = "res://roms/megadrive/Sonic the Hedgehog.bin"

	if emulator_script.start_game(core_path, rom_path):
		print("Il gioco è stato avviato con successo!")
	else:
		print("Errore durante l'avvio del gioco.")
