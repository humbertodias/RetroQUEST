#include "libretro_binding.h"

void register_libretro_core_binding_types() {
    ClassDB::register_class<LibretroCoreBinding>();
}

void unregister_libretro_core_binding_types() {
    // Non necessario per ora
}
