extends Node

@onready var emu = $EmulatorCore
@onready var display = $TextureRect

func _ready():
    if emu.initialize_core("res://cores/genesis_plus_gx_libretro.so"):
        if emu.start_game("res://roms/megadrive/Sonic the Hedgehog.bin"):
            display.texture = emu.get_texture()

func _process(_delta):
    emu.process_frame()