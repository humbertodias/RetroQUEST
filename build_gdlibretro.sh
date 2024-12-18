#!/bin/bash

git clone https://github.com/gabrielmedici/gdlibretro
cd gdlibretro
git submodule update --init --recursive && \
cmake -DNO_GIT_REVISION=ON -DCMAKE_BUILD_TYPE=Debug -DLINUX=true -DCMAKE_CXX_FLAGS="-DLINUX" . && \
cmake --build . && \
cd - && \
mv -fv "gdlibretro/LibRetroHost/lib/Linux-x86_64/libLibRetroHost-d.so" "addons" && \
rm -rf "gdlibretro/LibRetroHost"
