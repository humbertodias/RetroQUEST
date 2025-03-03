#!/bin/bash
set -e  # Exit on error

# TODO: create a proper fork of the gdlibretro when ready and ask for a PR

# Disabled as now we are editing our own "fork"of libretro
# git clone https://github.com/gabrielmedici/gdlibretro

OS=$(uname -s)
ARCH=$(uname -m)
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="build"
echo "Building for ${OS}-${ARCH}"

cd gdlibretro
git submodule update --init --recursive
cmake -DNO_GIT_REVISION=ON -DCMAKE_BUILD_TYPE=Debug -B "${BUILD_DIR}"
cmake --build "${BUILD_DIR}"
find . -name "libLibRetroHost-d.*" -exec mv -v {} "${SCRIPT_DIR}/addons/" \;
rm -rf "${BUILD_DIR}"
cd "${SCRIPT_DIR}"
zip -r -9 "gdlibretro-${OS}-${ARCH}.zip" addons/*LibRetroHost*