#!/bin/bash

# TODO: create a proer fork of the gdlibretro when ready and ask for a PR

# Disabled as now we are editing our own "fork"of libretro
#git clone https://github.com/gabrielmedici/gdlibretro
ARCH=$(uname -m)
OS=$(uname -s)
cd gdlibretro
git submodule update --init --recursive && \
cmake -DNO_GIT_REVISION=ON -DCMAKE_BUILD_TYPE=Debug -DLINUX=true -DCMAKE_CXX_FLAGS="-DLINUX" -Bbuild && \
cmake --build build && \
cd - && \
mv -fv "gdlibretro/build/LibRetroHost/lib/${OS}-${ARCH}/libLibRetroHost*" "addons" && \
rm -rf "gdlibretro/build" && \
zip -r -9 gdlibretro-${OS}-${ARCH}.zip addons/libLibRetroHost*
