#!/bin/bash

# TODO: create a proer fork of the gdlibretro when ready and ask for a PR

# Disabled as now we are editing our own "fork"of libretro
#git clone https://github.com/gabrielmedici/gdlibretro

set -e  # Exit on error

OS=$(uname -s)
ARCH=$(uname -m)
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="build"
LIB_PATH="${BUILD_DIR}/LibRetroHost/lib/${OS}-${ARCH}"
OUTPUT_ZIP="gdlibretro-${OS}-${ARCH}.zip"

echo "Building for ${OS}-${ARCH}"

cd gdlibretro
git submodule update --init --recursive
cmake -DNO_GIT_REVISION=ON -DCMAKE_BUILD_TYPE=Debug -DLINUX=true -DCMAKE_CXX_FLAGS="-DLinux -Wformat-nonliteral -Werror -Wno-shadow" -B "${BUILD_DIR}"
cmake --build "${BUILD_DIR}"

# Move built files
mv -fv "${LIB_PATH}/libLibRetroHost"* "${SCRIPT_DIR}/addons/"

# Clean up and zip
rm -rf "${BUILD_DIR}"

cd "${SCRIPT_DIR}"
zip -r -9 "${OUTPUT_ZIP}" addons/*LibRetroHost*

echo "Build complete: ${OUTPUT_ZIP}"
