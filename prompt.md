RetroQUEST is an application mainly written for Meta Quest 3 with Linux non-VR support in Godot 4.3.
In the future will be added supporto for Widnows, Mac and other VRs as well.
The app is working mainly with VR controls but can be used even with desktop controls (mouse, keyboard, controllers).
The app is Quest Native and not PCVR.
The scope of this application is to emulate games and render them on a virtual CRT TV in the VR space, more features will be added later.
The first iteration will be to be able to run the rom roms/megadrive/Sonic
For this scope I am using gdlibretro (https://github.com/gabrielmedici/gdlibretro) with some modifications to make it work on Linux and Android.
Here is my directory structure
.
├── addons
│   ├── godot-xr-tools
│   ├── libLibRetroHost-d.so
│   ├── LibRetroHost.gdextension
│   └── xr-simulator
├── assets
│   ├── Brick Wall Texture.jpg
│   ├── Brick Wall Texture.jpg.import
│   ├── consoles
│   ├── kenney_furniture-kit
│   ├── kenney_mini-arcade
│   ├── kenney_prototype-kit
│   ├── textures
│   └── tv
├── build_gdlibretro.sh
├── cores -> /home/jay/retrodeck_ro_user/share/libretro/cores
├── functions
│   └── run_core.gd
├── gdlibretro
│   ├── addons
│   ├── cmake
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── cmake_install.cmake
│   ├── CMakeLists.txt
│   ├── CMakePresets.json
│   ├── compile_commands.json
│   ├── demo
│   ├── extern
│   ├── gen
│   ├── LibRetroHost
│   ├── Makefile
│   ├── README.md
│   ├── src
│   └── template
├── icon.svg
├── icon.svg.import
├── main.gd
├── main.tscn
├── openxr_action_map.tres
├── project.godot
├── prompt.md
├── prompt.sh
├── README.md
├── roms -> /home/jay/retrodeck/roms
├── SConstruct
├── scripts
│   ├── emulate.gd.old
│   └── libretro_loader.gd
└── xr_origin_3d.tscn

24 directories, 27 files
Now I will cat you the main files for you to understand better the project.
--- project.godot ---
; Engine configuration file.
; It's best edited using the editor UI and not directly,
; since the parameters that go here are not all obvious.
;
; Format:
;   [section] ; section goes between []
;   param=value ; assign values to parameters

config_version=5

[application]

config/name="RetroQUEST"
run/main_scene="res://main.tscn"
config/features=PackedStringArray("4.3", "GL Compatibility")
config/icon="res://icon.svg"

[autoload]

XRToolsUserSettings="*res://addons/godot-xr-tools/user_settings/user_settings.gd"
XRToolsRumbleManager="*res://addons/godot-xr-tools/rumble/rumble_manager.gd"
XrSimulator="*res://addons/xr-simulator/XRSimulator.tscn"

[editor_plugins]

enabled=PackedStringArray("res://addons/godot-xr-tools/plugin.cfg")

[gd_extension]

extensions=PackedStringArray("res://addons/LibRetroHost.gdextension")

[rendering]

renderer/rendering_method="gl_compatibility"
renderer/rendering_method.mobile="gl_compatibility"

[xr]

openxr/enabled=true
shaders/enabled=true
--- end of project.godot ---

--- main.tscn ---
[gd_scene load_steps=22 format=3 uid="uid://8roky2tr13v8"]

[ext_resource type="Script" path="res://main.gd" id="1_36sr1"]
[ext_resource type="ArrayMesh" uid="uid://bggt7a5musnhs" path="res://assets/kenney_furniture-kit/Models/OBJ format/cabinetTelevision.obj" id="2_h1lnb"]
[ext_resource type="Texture2D" uid="uid://rpfpax3cx88g" path="res://assets/textures/close-up-wooden-texture_23-2147625744.jpg" id="2_hgnca"]
[ext_resource type="PackedScene" uid="uid://bkt5sw3j026sx" path="res://xr_origin_3d.tscn" id="2_jdtaa"]
[ext_resource type="PackedScene" uid="uid://diyu06cw06syv" path="res://addons/godot-xr-tools/player/player_body.tscn" id="3_76mo5"]
[ext_resource type="ArrayMesh" uid="uid://12208cv4iusu" path="res://assets/kenney_furniture-kit/Models/OBJ format/bedSingle.obj" id="4_gdp5r"]
[ext_resource type="PackedScene" uid="uid://coocuwjurtlft" path="res://assets/consoles/sega_genesis_model_2__sega_mega_drive.glb" id="5_o8gwv"]
[ext_resource type="PackedScene" uid="uid://c5yymdsb50dia" path="res://assets/tv/crt_tv.glb" id="6_bla35"]
[ext_resource type="Texture2D" uid="uid://cveoss57kakcb" path="res://assets/textures/orange-brick-wall.jpg" id="7_7vxdg"]
[ext_resource type="ArrayMesh" uid="uid://js8c02ef5656" path="res://assets/kenney_furniture-kit/Models/OBJ format/doorway.obj" id="10_b82c5"]
[ext_resource type="ArrayMesh" uid="uid://bqh7jhg02guef" path="res://assets/kenney_furniture-kit/Models/OBJ format/books.obj" id="11_6t3bm"]

[sub_resource type="ProceduralSkyMaterial" id="ProceduralSkyMaterial_odtcn"]
sky_horizon_color = Color(0.64625, 0.65575, 0.67075, 1)
ground_horizon_color = Color(0.64625, 0.65575, 0.67075, 1)

[sub_resource type="Sky" id="Sky_d5n34"]
sky_material = SubResource("ProceduralSkyMaterial_odtcn")

[sub_resource type="Environment" id="Environment_rebsy"]
background_mode = 2
sky = SubResource("Sky_d5n34")
tonemap_mode = 2

[sub_resource type="StandardMaterial3D" id="StandardMaterial3D_022uh"]
albedo_texture = ExtResource("2_hgnca")
uv1_scale = Vector3(10, 10, 10)

[sub_resource type="PlaneMesh" id="PlaneMesh_t6a7n"]
material = SubResource("StandardMaterial3D_022uh")
size = Vector2(7, 9)

[sub_resource type="BoxShape3D" id="BoxShape3D_smmd7"]
size = Vector3(10, 0.1, 10)

[sub_resource type="ViewportTexture" id="ViewportTexture_0ae1f"]
viewport_path = NodePath("room/SubViewport")

[sub_resource type="StandardMaterial3D" id="StandardMaterial3D_p0q3w"]
resource_local_to_scene = true
albedo_texture = SubResource("ViewportTexture_0ae1f")

[sub_resource type="StandardMaterial3D" id="StandardMaterial3D_dneyb"]
resource_local_to_scene = true
albedo_texture = ExtResource("7_7vxdg")
uv1_scale = Vector3(3, 3, 3)

[sub_resource type="StandardMaterial3D" id="StandardMaterial3D_vl1cb"]
albedo_color = Color(1, 0.953959, 0.778434, 1)

[node name="main" type="Node3D"]
script = ExtResource("1_36sr1")

[node name="WorldEnvironment" type="WorldEnvironment" parent="."]
environment = SubResource("Environment_rebsy")

[node name="DirectionalLight3D" type="DirectionalLight3D" parent="."]
transform = Transform3D(-0.866024, -0.433016, 0.250001, 0, 0.499998, 0.866026, -0.500003, 0.749999, -0.43301, 0, 2.75, 0)
directional_shadow_mode = 0

[node name="room" type="Node" parent="."]

[node name="floor" type="StaticBody3D" parent="room"]
transform = Transform3D(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, -0.05, 0)

[node name="MeshInstance3D" type="MeshInstance3D" parent="room/floor"]
mesh = SubResource("PlaneMesh_t6a7n")
skeleton = NodePath("../CollisionShape3D")

[node name="CollisionShape3D" type="CollisionShape3D" parent="room/floor"]
shape = SubResource("BoxShape3D_smmd7")

[node name="BedSingle" type="MeshInstance3D" parent="room"]
transform = Transform3D(3, 0, 0, 0, 3, 0, 0, 0, 3, 0.141, 0, 0.594707)
mesh = ExtResource("4_gdp5r")
skeleton = NodePath("../..")

[node name="CabinetTelevision" type="MeshInstance3D" parent="room"]
transform = Transform3D(-1.92921, 0, 2.29743, 0, 3, 0, -2.29743, 0, -1.92921, 0.849805, -0.0571399, -3.42659)
mesh = ExtResource("2_h1lnb")
skeleton = NodePath("../floor/CollisionShape3D")

[node name="CRTTV" type="CSGBox3D" parent="room"]
transform = Transform3D(0.643068, 0, -0.536066, 0, 0.9, 0, 0.765809, 0, 0.450148, 1.49155, 1.32038, -3.29054)
use_collision = true
material = SubResource("StandardMaterial3D_p0q3w")

[node name="MegaDrive" parent="room" instance=ExtResource("5_o8gwv")]
transform = Transform3D(0.00064082, 0, -0.000767691, 0, 0.001, 0, 0.000767691, 0, 0.00064082, 2.08216, 0.913985, -2.52858)

[node name="CRTTV2" parent="room" instance=ExtResource("6_bla35")]
transform = Transform3D(-1.32944, 0, 1.49418, 0, 2, 0, -1.49418, 0, -1.32944, 1.31505, 0.816899, -3.11279)

[node name="brick wall" type="CSGBox3D" parent="room"]
transform = Transform3D(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 2.53021, -4.14194)
use_collision = true
size = Vector3(6.72745, 6.15861, 0.141602)
material = SubResource("StandardMaterial3D_dneyb")

[node name="wall3" type="CSGBox3D" parent="room"]
transform = Transform3D(1, 0, 0, 0, 1, 0, 0, 0, 1, 0.0828514, 2.48109, 4.14488)
use_collision = true
size = Vector3(6.56174, 6.14909, 0.141602)
material = SubResource("StandardMaterial3D_vl1cb")

[node name="Doorway" type="MeshInstance3D" parent="room/wall3"]
transform = Transform3D(3, 0, 0, 0, 3, 0, 0, 0, 1, 2.53115, -2.52145, -0.14388)
mesh = ExtResource("10_b82c5")
skeleton = NodePath("../../..")

[node name="wall2" type="CSGBox3D" parent="room"]
transform = Transform3D(-4.37114e-08, 0, 1, 0, 1, 0, -1, 0, -4.37114e-08, 3.08915, 2.41665, 0.056199)
use_collision = true
size = Vector3(8.52944, 6.14718, 0.141602)
material = SubResource("StandardMaterial3D_vl1cb")

[node name="wall4" type="CSGBox3D" parent="room"]
transform = Transform3D(-4.37114e-08, 0, 1, 0, 1, 0, -1, 0, -4.37114e-08, -3.03443, 2.56347, -0.053894)
use_collision = true
size = Vector3(8.60897, 5.83376, 0.141602)
material = SubResource("StandardMaterial3D_vl1cb")

[node name="roof" type="StaticBody3D" parent="room"]
transform = Transform3D(0.906308, 0.422618, 0, 0.422618, -0.906308, -8.74228e-08, -3.69465e-08, 7.92319e-08, -1, 0, 3.8, 0)

[node name="MeshInstance3D" type="MeshInstance3D" parent="room/roof"]
mesh = SubResource("PlaneMesh_t6a7n")
skeleton = NodePath("../CollisionShape3D")

[node name="CollisionShape3D" type="CollisionShape3D" parent="room/roof"]
shape = SubResource("BoxShape3D_smmd7")

[node name="SubViewport" type="SubViewport" parent="room"]
transparent_bg = true
size = Vector2i(640, 480)

[node name="ColorRect" type="ColorRect" parent="room/SubViewport"]
visible = false
anchors_preset = 15
anchor_right = 1.0
anchor_bottom = 1.0
grow_horizontal = 2
grow_vertical = 2
color = Color(0.262745, 1, 0, 1)

[node name="TextureRect" type="TextureRect" parent="room/SubViewport"]
offset_right = 40.0
offset_bottom = 40.0

[node name="XROrigin3D" parent="." instance=ExtResource("2_jdtaa")]

[node name="PlayerBody" parent="XROrigin3D" instance=ExtResource("3_76mo5")]

[node name="CollisionShape3D" type="CollisionShape3D" parent="XROrigin3D/PlayerBody"]

[node name="Books" type="MeshInstance3D" parent="."]
transform = Transform3D(-0.617031, -0.0412188, 2.93557, 0.151763, 2.99525, 0.0739558, -2.93193, 0.163714, -0.613967, 2.30079, 0.879317, -2.22938)
mesh = ExtResource("11_6t3bm")
--- end of main.tscn ---

--- scripts/libretro_loader.gd ---
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
--- end of scripts/libretro_loader.gd ---

--- addons/LibRetroHost.gdextension ---
[configuration]

entry_symbol = "GDExtensionInit"
compatibility_minimum = 4.1

[libraries]
windows.release.x86_64 = "lib/Windows-AMD64/LibRetroHost-d.dll"
windows.debug.x86_64 = "lib/Windows-AMD64/LibRetroHost-d.dll"
linux.release.x86_64 = "res://addons/libLibRetroHost-d.so"
linux.debug.x86_64 = "res://addons/libLibRetroHost-d.so"
--- end of addons/LibRetroHost.gdextension ---

--- gdlibretro/src/CoreEnvironment.cpp ---
#include "RetroHost.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <cstdarg> // Required for va_start and va_end

// Logging function for the core
void core_log(enum retro_log_level level, const char *fmt, ...)
{
    char buffer[4096] = {0};
    static const char *levelstr[] = {"DEBUG", "INFO", "WARN", "ERROR"};
    va_list va;

    va_start(va, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    godot::UtilityFunctions::print("[RetroHost Loaded CORE][" +
                                    godot::String(levelstr[level - 1]) + "] " + buffer);
}

// Retrieves a core variable
bool RetroHost::get_variable(retro_variable *variable)
{
    if (!this->core_variables[variable->key].IsDefined())
    {
        godot::UtilityFunctions::printerr("[RetroHost] Core variable ", variable->key, " not defined");
        return false;
    }

    auto var_value = core_variables[variable->key].as<std::string>();
    if (var_value.empty())
    {
        godot::UtilityFunctions::printerr("[RetroHost] Core variable ", variable->key, " was empty ", var_value.c_str());
        return false;
    }

    const std::string::size_type size = var_value.size();
    char *buffer = new char[size + 1];
    memcpy(buffer, var_value.c_str(), size + 1);

    this->please_free_me_str.push_back(buffer);

    variable->value = buffer;
    return true;
}

// Helper function to split strings
std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

// Handles various core environment commands
bool RetroHost::core_environment(unsigned command, void *data)
{
    switch (command)
    {
        case RETRO_ENVIRONMENT_GET_LOG_INTERFACE:
        {
            godot::UtilityFunctions::print("[RetroHost] Core log interface set.");
            struct retro_log_callback *cb = (struct retro_log_callback *)data;
            cb->log = core_log;
        }
        break;

        case RETRO_ENVIRONMENT_GET_CAN_DUPE:
        {
            godot::UtilityFunctions::print("[RetroHost] Core can dupe set.");
            bool *b = (bool *)data;
            *b = true;
        }
        break;

        case RETRO_ENVIRONMENT_GET_VARIABLE:
        {
            auto var = (retro_variable *)data;
            return this->get_variable(var);
        }
        break;

        case RETRO_ENVIRONMENT_SET_VARIABLES:
        {
            auto variables = (const struct retro_variable *)data;
            while (variables->key)
            {
                if (!this->core_variables[variables->key].IsDefined())
                {
                    std::string value = variables->value;
                    auto possible_values_str = split(value, ";")[1].erase(0, 1);
                    auto possible_values = split(possible_values_str, "|");
                    this->core_variables[variables->key] = possible_values[0];

                    godot::UtilityFunctions::print("[RetroHost] Core variable ", variables->key, 
                        " was not present in the config file, now set to the first possible value: ", 
                        possible_values[0].c_str());
                }
                variables++;
            }
        }
        break;

        case RETRO_ENVIRONMENT_GET_VFS_INTERFACE:
        {
            auto vfs_interface = (struct retro_vfs_interface_info *)data;
            godot::UtilityFunctions::print("[RetroHost] Core requested VFS interface");
            if (vfs_interface->required_interface_version > this->vfs.supported_interface_version)
            {
                godot::UtilityFunctions::printerr("[RetroHost] Core requested VFS interface v",
                                                  vfs_interface->required_interface_version, 
                                                  " we only support up to v", 
                                                  this->vfs.supported_interface_version);
                return false;
            }
            vfs_interface->iface = &this->vfs.vfs_interface;
            return true;
        }
        break;

        case RETRO_ENVIRONMENT_SET_PIXEL_FORMAT:
        {
            const enum retro_pixel_format *fmt = (enum retro_pixel_format *)data;
            if (*fmt > RETRO_PIXEL_FORMAT_RGB565)
            {
                return false;
            }

            godot::UtilityFunctions::print("[RetroHost] Core setting pixel format");
            return this->core_video_set_pixel_format(*fmt);
        }
        break;

        case RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY:
        case RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY:
        case RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY:
        case RETRO_ENVIRONMENT_GET_LIBRETRO_PATH:
        {
            godot::UtilityFunctions::print("[RetroHost] Core requested path");
            *(const char **)data = this->cwd.trim_suffix("/").utf8().get_data();
            return true;
        }

        case RETRO_ENVIRONMENT_SHUTDOWN:
        {
            godot::UtilityFunctions::print("[RetroHost] Core shutdown requested");
            break;
        }

        default:
        {
            godot::UtilityFunctions::print("[RetroHost] Core environment command " + 
                                           godot::String::num(command) + " not implemented.");
            return false;
        }
    }

    return true;
}
--- end of gdlibretro/src/CoreEnvironment.cpp ---

--- gdlibretro/src/RetroHost.cpp ---
#include "RetroHost.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/project_settings.hpp>

#include <fstream>
#include <iostream>

// Platform-specific includes
#ifdef _WIN32
#include <windows.h>
#define PLATFORM_WINDOWS
#elif __linux__
#include <dlfcn.h>
#define PLATFORM_LINUX
#elif __ANDROID__
#include <dlfcn.h>
#define PLATFORM_ANDROID
#endif

// Returns the last error message as a string
std::string GetLastErrorAsStr()
{
#ifdef PLATFORM_WINDOWS
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string();
    }

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                     FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                 (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);
    LocalFree(messageBuffer);

    return message;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    return dlerror(); // Linux and Android use dlerror for error reporting.
#else
    return "Error information not available on this platform";
#endif
}

RetroHost::RetroHost()
{
    godot::UtilityFunctions::print("[RetroHost] Constructor");
    singleton = this;
    this->vfs.init_vfs_interface();
}

RetroHost::~RetroHost()
{
    godot::UtilityFunctions::print("[RetroHost] Destructor");
    this->unload_core();
}

RetroHost *RetroHost::singleton = nullptr;

RetroHost *RetroHost::get_singleton()
{
    return singleton;
}

#define load_symbol_return_false_on_err(handle, dest, sym)                                           \
    godot::UtilityFunctions::print("[RetroHost] Loading core symbol \"", #sym, "\"");               \
    dest = (decltype(dest))dlsym(handle, #sym);                                                     \
    if (dest == NULL)                                                                               \
    {                                                                                               \
        godot::UtilityFunctions::printerr("[RetroHost] Could not load symbol \"", #sym,             \
                                           "\": ", dlerror());                                      \
        return false;                                                                               \
    }

bool RetroHost::load_core(godot::String name) {
    this->unload_core();
    godot::UtilityFunctions::print("[RetroHost] Loading core \"", name, "\"");

    godot::String lib_path;
    if (godot::OS::get_singleton()->has_feature("editor")) {
        this->cwd =
            godot::ProjectSettings::get_singleton()->globalize_path("res://") + "libretro-cores/";
        lib_path = cwd + name + ".dll"; // Editor path (Windows assumed default)
    } else {
        this->cwd = godot::OS::get_singleton()->get_executable_path().get_base_dir();
        lib_path = cwd + "/" + name;
    }

#ifdef PLATFORM_WINDOWS
    this->core.handle = LoadLibrary(lib_path.utf8().get_data());
    if (this->core.handle == NULL) {
        godot::UtilityFunctions::printerr("[RetroHost] Failed to load core \"", lib_path, "\"");
        return false;
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    this->core.handle = dlopen(lib_path.utf8().get_data(), RTLD_LAZY);
    if (this->core.handle == nullptr) {
        godot::UtilityFunctions::printerr("[RetroHost] Failed to load core \"" + 
                                   godot::String(lib_path.utf8().get_data()) + 
                                   "\": " + 
                                   godot::String(GetLastErrorAsStr().c_str()));
        return false;
    }
#endif

    // Load RetroArch symbols dynamically
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_init, retro_init);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_deinit, retro_deinit);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_api_version, retro_api_version);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_get_system_info, retro_get_system_info);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_get_system_av_info, retro_get_system_av_info);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_set_controller_port_device, retro_set_controller_port_device);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_reset, retro_reset);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_run, retro_run);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_load_game, retro_load_game);
    load_symbol_return_false_on_err(this->core.handle, this->core.retro_unload_game, retro_unload_game);

    this->core_name = name;
    this->load_core_variables();

    this->core.retro_init();
    this->core.retro_load_game(NULL);

    struct retro_system_av_info av;
    this->core.retro_get_system_av_info(&av);

    this->core_video_init(&av.geometry);
    this->core_audio_init(av);

    this->core.initialized = true;
    return true;
}

void RetroHost::unload_core()
{
    if (this->core.initialized)
    {
        this->core.retro_deinit();
        this->core.initialized = false;
    }

#ifdef PLATFORM_WINDOWS
    if (this->core.handle != NULL)
    {
        FreeLibrary(this->core.handle);
        this->core.handle = NULL;
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    if (this->core.handle != nullptr)
    {
        dlclose(this->core.handle);
        this->core.handle = nullptr;
    }
#endif
}

void RetroHost::run()
{
    if (!this->core.initialized)
    {
        godot::UtilityFunctions::printerr("[RetroHost] Core not initialized");
        return;
    }
    this->core.retro_run();
}

void RetroHost::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("load_core", "name"), &RetroHost::load_core);
    godot::ClassDB::bind_method(godot::D_METHOD("unload_core"), &RetroHost::unload_core);
    godot::ClassDB::bind_method(godot::D_METHOD("run"), &RetroHost::run);
}
--- end of gdlibretro/src/RetroHost.cpp ---

--- gdlibretro/src/RetroHost.hpp ---
#pragma once

#include "filesystem"
#include "godot_cpp/classes/image.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/object.hpp"
#include "libretro.h"
#include "yaml-cpp/yaml.h"

// Platform-specific includes
#ifdef _WIN32
#include <windows.h>
#define PLATFORM_WINDOWS
#elif __linux__
#include <dlfcn.h>
#define PLATFORM_LINUX
#elif __ANDROID__
#include <dlfcn.h>
#define PLATFORM_ANDROID
#endif

class RetroHost : public godot::Object
{
    GDCLASS(RetroHost, godot::Object)

public:
    godot::String cwd;
    static RetroHost *get_singleton();

    RetroHost();
    ~RetroHost();

    bool load_core(godot::String path);
    void unload_core();
    void run();
    void forwarded_input(const godot::Ref<godot::InputEvent> &event);

private:
    static RetroHost *singleton;

    godot::Ref<godot::Image> frame_buffer;
    godot::Ref<godot::Image> get_frame_buffer()
    {
        return frame_buffer;
    }

    std::vector<char *> please_free_me_str;

    YAML::Node core_variables;
    godot::String core_name;

    void load_core_variables();
    void save_core_variables();
    bool get_variable(retro_variable *variable);

    bool core_environment(unsigned cmd, void *data);

    void core_video_init(const struct retro_game_geometry *geometry);
    void core_video_refresh(const void *data, unsigned width, unsigned height, size_t pitch);
    bool core_video_set_pixel_format(unsigned format);
    godot::Image::Format pixel_format;

    void core_input_poll(void);
    int16_t core_input_state(unsigned port, unsigned device, unsigned index, unsigned id);

    void core_audio_init(retro_system_av_info av);
    void core_audio_sample(int16_t left, int16_t right);
    size_t core_audio_sample_batch(const int16_t *data, size_t frames);

    struct VFS
    {
        uint32_t supported_interface_version = 0;

        void init_vfs_interface();
        struct retro_vfs_interface vfs_interface;

        const char *get_path(retro_vfs_file_handle *stream);
        struct retro_vfs_file_handle *open(const char *path, unsigned mode, unsigned hints);
        int close(retro_vfs_file_handle *stream);
        int64_t size(struct retro_vfs_file_handle *stream);
        int64_t tell(struct retro_vfs_file_handle *stream);
        int64_t seek(struct retro_vfs_file_handle *stream, int64_t offset, int seek_position);
        int64_t read(struct retro_vfs_file_handle *stream, void *s, uint64_t len);
        int64_t write(struct retro_vfs_file_handle *stream, const void *s, uint64_t len);
        int flush(retro_vfs_file_handle *stream);
        int remove(const char *path);
        int rename(const char *old_path, const char *new_path);
        int64_t truncate(struct retro_vfs_file_handle *stream, int64_t length);
        int stat(const char *path, int32_t *size);
        int mkdir(const char *dir);
        struct retro_vfs_dir_handle *opendir(const char *dir, bool include_hidden_files);
        bool read_dir(struct retro_vfs_dir_handle *dir_stream);
        const char *dirent_get_name(struct retro_vfs_dir_handle *dir_stream);
        bool dirent_is_dir(struct retro_vfs_dir_handle *dir_stream);
        int closedir(struct retro_vfs_dir_handle *dir_stream);
    } vfs;

    struct
    {
#ifdef PLATFORM_WINDOWS
        HINSTANCE handle;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
        void *handle;
#endif
        bool initialized = false;

        void (*retro_init)(void);
        void (*retro_deinit)(void);
        unsigned (*retro_api_version)(void);
        void (*retro_get_system_info)(struct retro_system_info *info);
        void (*retro_get_system_av_info)(struct retro_system_av_info *info);
        void (*retro_set_controller_port_device)(unsigned port, unsigned device);
        void (*retro_reset)(void);
        void (*retro_run)(void);
        bool (*retro_load_game)(const struct retro_game_info *game);
        void (*retro_unload_game)(void);

        retro_keyboard_event_t retro_keyboard_event_callback;
    } core;

protected:
    static void _bind_methods();
};
--- end of gdlibretro/src/RetroHost.hpp ---

--- gdlibretro/src/Video.cpp ---
#include "RetroHost.hpp"
#include "godot_cpp/classes/image.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

void RetroHost::core_video_init(const struct retro_game_geometry *geometry)
{
    godot::UtilityFunctions::print("[RetroHost] Video init ", geometry->base_width, " x ",
                                    geometry->base_height);
    this->frame_buffer = godot::Image::create(geometry->base_width, geometry->base_height, false,
                                              this->pixel_format);
}

void RetroHost::core_video_refresh(const void *data, unsigned width, unsigned height,
                                   size_t pitch)
{
    if (!data || frame_buffer.is_null() || !frame_buffer.is_valid())
    {
        return;
    }

    if ((unsigned)frame_buffer->get_width() != width ||
        (unsigned)frame_buffer->get_height() != height)
    {
        godot::UtilityFunctions::print("[RetroHost] Resizing frame buffer to ", width, "x",
                                       height);
        auto created_frame_buffer =
            godot::Image::create(width, height, false, frame_buffer->get_format());
        if (created_frame_buffer.is_null() || !created_frame_buffer.is_valid())
        {
            godot::UtilityFunctions::printerr("[RetroHost] Failed to recreate frame buffer");
            return;
        }
        frame_buffer = created_frame_buffer;
    }

    unsigned buffer_size;
    switch (frame_buffer->get_format())
    {
        case godot::Image::FORMAT_RGB565:
            buffer_size = width * height * 2;
            break;
        case godot::Image::FORMAT_RGBA8:
        {
            buffer_size = width * height * 4;

#if defined(_MSC_VER) // MSVC compiler
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

            uint32_t *data32 = (uint32_t *)data;
            for (unsigned i = 0; i < width * height; i++)
            {
                uint32_t pixel = data32[i];
                uint8_t alpha = (pixel & 0xFF000000) >> 24;
                uint8_t red = (pixel & 0x00FF0000) >> 16;
                uint8_t green = (pixel & 0x0000FF00) >> 8;
                uint8_t blue = (pixel & 0x000000FF);
                data32[i] = (alpha << 24) | (blue << 16) | (green << 8) | red;
            }

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
        }
        break;
        default:
            godot::UtilityFunctions::printerr("[RetroHost] Unhandled pixel format: ",
                                              frame_buffer->get_format());
            return;
    }

    godot::PackedByteArray intermediary_buffer;
    intermediary_buffer.resize(buffer_size);
    memcpy((void *)intermediary_buffer.ptr(), data, buffer_size);

    frame_buffer->set_data(width, height, false, frame_buffer->get_format(), intermediary_buffer);
}

bool RetroHost::core_video_set_pixel_format(unsigned format)
{
    switch (format)
    {
        case RETRO_PIXEL_FORMAT_0RGB1555:
            godot::UtilityFunctions::print("[RetroHost] Pixel format: 0RGB1555");
            this->pixel_format = godot::Image::Format::FORMAT_RGB565;
            return true;
        case RETRO_PIXEL_FORMAT_XRGB8888:
            godot::UtilityFunctions::print("[RetroHost] Pixel format: XRGB8888");
            this->pixel_format = godot::Image::Format::FORMAT_RGBA8;
            return true;
        case RETRO_PIXEL_FORMAT_RGB565:
            godot::UtilityFunctions::print("[RetroHost] Pixel format: RGB565");
            this->pixel_format = godot::Image::Format::FORMAT_RGB565;
            return true;
        default:
            return false;
    }
}
--- end of gdlibretro/src/Video.cpp ---

--- gdlibretro/src/RegisterExtension.cpp ---
#include "gdextension_interface.h"

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"
#include "godot_cpp/classes/engine.hpp"

#include "RetroHost.hpp"

static RetroHost *retro_host_singleton = nullptr;

namespace {
    void initialize_extension(godot::ModuleInitializationLevel p_level) {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
        }

        godot::ClassDB::register_class<RetroHost>();

        retro_host_singleton = memnew(RetroHost());
        godot::Engine::get_singleton()->register_singleton("RetroHost", RetroHost::get_singleton());
    }

    void uninitialize_extension(godot::ModuleInitializationLevel p_level) {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
        }
        godot::Engine::get_singleton()->unregister_singleton("RetroHost");
        memdelete(retro_host_singleton);
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT GDExtensionInit(
        GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_extension);
        init_obj.register_terminator(uninitialize_extension);
        init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
--- end of gdlibretro/src/RegisterExtension.cpp ---

--- gdlibretro/src/CMakeLists.txt ---
# SPDX-License-Identifier: Unlicense

# Platform-specific settings
if (ANDROID)
    target_link_libraries(${PROJECT_NAME} PUBLIC dl log)
    add_definitions(-DPLATFORM_ANDROID)
elseif (UNIX AND NOT APPLE) # Linux
    target_link_libraries(${PROJECT_NAME} PUBLIC dl)
    add_definitions(-DPLATFORM_LINUX)
elseif (WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
endif()

# Add sources
target_sources(${PROJECT_NAME}
    PRIVATE
        RegisterExtension.cpp
        RetroHost.hpp
        RetroHost.cpp
        CoreEnvironment.cpp
        CoreVariables.cpp
        Audio.cpp
        Input.cpp
        Video.cpp
        KeyboardMap.hpp
        VFS.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "src"
)
--- end of gdlibretro/src/CMakeLists.txt ---


My issue now is the following, can you help me to fix it?
Godot says:
[RetroHost] Constructor
  core/extension/gdextension.cpp:1011 - No GDExtension library found for current OS and architecture (linux.x86_64) in configuration file: res://gdlibretro/LibRetroHost/LibRetroHost.gdextension
  Failed loading resource: res://gdlibretro/LibRetroHost/LibRetroHost.gdextension. Make sure resources have been imported by opening the project in the editor at least once.
Core path: res://cores/genesis_plus_gx_libretro.so
ROM path: res://roms/megadrive/Sonic the Hedgehog.bin
Starting emulation with core: res://cores/genesis_plus_gx_libretro.so, ROM: res://roms/megadrive/Sonic the Hedgehog.bin
Loading core...
Failed to start the game.
--- Debugging process stopped ---
  core/extension/gdextension.cpp:1011 - No GDExtension library found for current OS and architecture (linux.x86_64) in configuration file: res://gdlibretro/LibRetroHost/LibRetroHost.gdextension
  Failed loading resource: res://gdlibretro/LibRetroHost/LibRetroHost.gdextension. Make sure resources have been imported by opening the project in the editor at least once.
  core/extension/gdextension.cpp:1011 - No GDExtension library found for current OS and architecture (linux.x86_64) in configuration file: res://gdlibretro/LibRetroHost/LibRetroHost.gdextension
  Failed loading resource: res://gdlibretro/LibRetroHost/LibRetroHost.gdextension. Make sure resources have been imported by opening the project in the editor at least once.

