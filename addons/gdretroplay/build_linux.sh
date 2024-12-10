#!/bin/bash

GODOT_CPP_BINDINGS_PATH="$HOME/gits/godot-cpp"

cd "$GODOT_CPP_BINDINGS_PATH"
scons platform=linux target=template_release generate_bindings=yes
cd -

rm -rf build_linux
mkdir build_linux
cd build_linux
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
