add_subdirectory(godot-cpp)
add_subdirectory(yaml-cpp)

target_include_directories(${PROJECT_NAME} PUBLIC libretro-common/include)

# Apply -Werror and -Wshadow ONLY to your project
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wshadow -Wno-documentation)