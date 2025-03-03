ARCH := $(shell uname -m)

create/dirs:
	mkdir -p roms/megadrive libretro-cores

genesis-core/apple: create/dirs
	cd libretro-cores
	curl -L -o genesis_plus_gx_libretro.dylib.zip https://buildbot.libretro.com/nightly/apple/osx/${ARCH}/latest/genesis_plus_gx_libretro.dylib.zip
	unzip genesis_plus_gx_libretro.dylib.zip
	rm genesis_plus_gx_libretro.dylib.zip