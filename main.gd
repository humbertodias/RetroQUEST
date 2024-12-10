extends Node3D

var xr_interface: XRInterface

func _ready():
	xr_interface = XRServer.find_interface("OpenXR")
	
	if xr_interface and xr_interface.is_initialized():
		print("OpenXR initialized succesfully")
		
		DisplayServer.window_set_vsync_mode(DisplayServer.VSYNC_DISABLED)
		
		get_viewport().use_xr = true
	else:
		print("OpenXR not initialized, please check if your headset is connected")
		
	# Configurazione SubViewport
	$SubViewport.size = Vector2(320, 240)  # Risoluzione tipica retro
	$SubViewport/TextureRect.expand = true
	$SubViewport/TextureRect.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
