ARCH := $(shell uname -m)

create/dirs:
	mkdir -p roms/megadrive libretro-cores

genesis-core/apple: create/dirs
	cd libretro-cores && \
	curl -L https://buildbot.libretro.com/nightly/apple/osx/${ARCH}/latest/genesis_plus_gx_libretro.dylib.zip | bsdtar -xvf -

genesis-core/linux: create/dirs
	cd libretro-cores && \
	curl -L https://buildbot.libretro.com/nightly/linux/${ARCH}/latest/genesis_plus_gx_libretro.so.zip | bsdtar -xvf -

dosbox_pure-core/linux:
	cd gdlibretro/demo/libretro-cores && \
	curl -L https://buildbot.libretro.com/nightly/linux/${ARCH}/latest/dosbox_pure_libretro.so.zip | bsdtar -xvf -

sonic/download:	create/dirs
	curl -L -o "roms/megadrive/Sonic the Hedgehog.bin" https://archive.org/download/sonic1_bin/sonic1.bin