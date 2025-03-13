#!/bin/bash
set -e  # Exit on error

# TODO: create a proper fork of the gdlibretro when ready and ask for a PR

# Disabled as now we are editing our own "fork"of libretro
# git clone https://github.com/gabrielmedici/gdlibretro

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

cd gdlibretro
git submodule update --init --recursive
cmake -DNO_GIT_REVISION=ON -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build

cp ./build/LibRetroHost/lib/Linux-x86_64/libLibRetroHost-d.so ${SCRIPT_DIR}/addons/
cp ./build/LibRetroHost/lib/Linux-x86_64/libLibRetroHost-d.so demo/bin/LibRetroHost/
rm -rf build/LibRetroHost
