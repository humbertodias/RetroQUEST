extends Node

var libretro_core = LibretroCoreBinding.new()  # Use the class directly

func start_game(core_path: String, rom_path: String) -> bool:
	"""
	Inizializza il core libretro e carica la ROM specificata.
	Restituisce true se il gioco è stato caricato correttamente, altrimenti false.
	"""
	# Carica il gestore libretro
	var libretro_handler = preload("res://scripts/libretro_loader.gd").new()

	# Inizializzazione del core
	if not libretro_handler.initialize(core_path):
		print("Errore: impossibile caricare il core libretro:", core_path)
		return false

	print("Core caricato con successo:", core_path)

	# Caricamento della ROM
	var rom_data: PackedByteArray = load_rom_data(rom_path)
	if not libretro_handler.load_game(rom_data):
		print("Errore: impossibile caricare la ROM:", rom_path)
		return false

	print("Gioco caricato con successo:", rom_path)
	return true

func load_rom_data(rom_path: String) -> PackedByteArray:
	"""
	Carica i dati di una ROM da file.
	"""
	var file = FileAccess.open(rom_path, FileAccess.READ)
	if not file:
		push_error("Error opening file: " + rom_path)
		return PackedByteArray()

	var data = file.get_buffer(file.get_length())
	file.close()
	return data

func initialize_core(core_path: String) -> bool:
	if not libretro_core.initialize(core_path):
		print("Errore: impossibile caricare il core libretro")
		return false
	return true
