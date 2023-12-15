# Space

Space is a WIP 2D / 3D game engine made for educational purposes.
It will be cross-platform.

## Building from source

In case you want to build Space from source, here is the way :

### Requirements

- [CMake](https://cmake.org/).
- Make
- a C++ compiler (MSVC, MinGW, Clang, ...)

### Building

```bash
git clone https://github.com/PottierLoic/Space.git
cd Space
```

```bash
# On Unix, you have to give permission.
chmod +x ./build.sh
./build.sh

# Windows doesn't care.
build.bat
```

The executable is now in the build folder.

```bash
cd build
./space
```
