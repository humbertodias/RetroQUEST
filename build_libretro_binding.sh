#!/bin/bash

if [ ! -d "godot-cpp" ]; then git clone https://github.com/godotengine/godot-cpp.git; fi
cd godot-cpp
git pull
git submodule update --init --recursive
scons platform=linux generate_bindings=yes -j$(nproc)
cd ..
scons platform=linux -j$(nproc)