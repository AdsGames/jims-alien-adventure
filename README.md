# JimsAlienAdventure

A button mashing game with the objective of preventing goat aliens from destroying famous international cities

## Demo

[Web Demo](https://adsgames.github.io/jims-alien-adventure/)

## Setup

### Dependencies

To pull the submodules, run the following command:

```bash
git submodule update --init --recursive
```

### Windows (MSYS2)

```bash
pacman -S mingw-w64-i686-gcc-libs mingw-w64-i686-SDL2 mingw-w64-i686-SDL2_mixer mingw-w64-i686-SDL2_image mingw-w64-i686-SDL2_ttf
```

### Mac OS

```bash
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer
```

### Linux

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

### Build

```bash
cmake .
make
```

### Build Emscripten

```bash
emcmake cmake .
make
```
