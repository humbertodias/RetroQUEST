ARCH := $(shell uname -m)

create/dirs:
	mkdir -p roms/megadrive libretro-cores

genesis-core/apple: create/dirs
	cd libretro-cores && \
	curl -L -o core.zip https://buildbot.libretro.com/nightly/apple/osx/${ARCH}/latest/genesis_plus_gx_libretro.dylib.zip && \
	unzip core.zip && rm core.zip

genesis-core/linux: create/dirs
	cd libretro-cores && \
	curl -L -o core.zip https://buildbot.libretro.com/nightly/linux/${ARCH}/latest/genesis_plus_gx_libretro.so.zip && \
	unzip core.zip && rm core.zip

sonic/download:
	curl -L -o "roms/megadrive/Sonic the Hedgehog.bin" https://archive.org/download/sonic1_bin/sonic1.bin