# Space

Space is a WIP 2D / 3D game engine made for fun.

It is cross platform and uses GLFW, OpenGL and DearImGui.

**Please note that there is no official release for the project, and it is unlikely that there will be any in the future**  
I'm mainly doing this to progress in c++ and OpenGL and because I always wanted to develop my own game engine.

## Building from source

### Requirements

- [CMake](https://cmake.org/).
- Make
- a C++ compiler (MSVC, g++, Clang, ...)

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

## License

This project is licensed under the [MIT License](LICENSE).
