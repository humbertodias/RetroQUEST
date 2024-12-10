# Dichiarazione del progetto
cmake_minimum_required(VERSION 3.15)
project(gdretroplay)

# Imposta il C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Percorsi per Godot C++ bindings
message(STATUS "Godot C++ Bindings Path: $ENV{GODOT_CPP_BINDINGS_PATH}")

include_directories($ENV{GODOT_CPP_BINDINGS_PATH}/include)
include_directories($ENV{GODOT_CPP_BINDINGS_PATH}/include/core)
include_directories($ENV{GODOT_CPP_BINDINGS_PATH}/include/gen)

# File sorgenti
file(GLOB SOURCES "src/*.cpp")
message(STATUS "Sources found: ${SOURCES}")

# Creazione della libreria condivisa
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Configurazioni specifiche per piattaforma
if(UNIX AND NOT ANDROID)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif()

if(ANDROID)
    include_directories(${ANDROID_NDK}/sources/android/native_app_glue)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif()

# Imposta le proprietà del target
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "gdretroplay")

# Linka le librerie di Godot
link_directories($ENV{GODOT_CPP_BINDINGS_PATH}/bin)
target_link_libraries(${PROJECT_NAME} godot-cpp)
