#!/bin/bash

# TODO: create a proer fork of the gdlibretro when ready and ask for a PR

# Disabled as now we are editing our own "fork"of libretro
#git clone https://github.com/gabrielmedici/gdlibretro
OS=$(uname -s)
ARCH=$(uname -m)
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
echo "OS: ${OS}"
echo "ARCH: ${ARCH}"
echo "SCRIPT_DIR: ${SCRIPT_DIR}"

cd gdlibretro
git submodule update --init --recursive && \
cmake -DNO_GIT_REVISION=ON -DCMAKE_BUILD_TYPE=Debug -DLINUX=true -DCMAKE_CXX_FLAGS="-DLinux" -Bbuild && \
cmake --build build && \
cd "${SCRIPT_DIR}/gdlibretro" && \
pwd && \
ls -la build/LibRetroHost/lib/${OS}-${ARCH} && \
mv -fv "build/LibRetroHost/lib/${OS}-${ARCH}/libLibRetroHost-d.so" "addons/" && \
rm -rf build && \

zip -r -9 gdlibretro-${OS}-${ARCH}.zip addons
