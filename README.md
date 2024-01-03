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

First, get the repo on your machine
```bash
git clone https://github.com/PottierLoic/Space.git
cd Space
```

Get the submodules too
```bash
git submodule init
git submodule update
```

Build using the corresponding file
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

## External libraries

Space is using many libraries

- GLFW - Graphic library
- Glad - OpenGL loader
- ImGui - C++ User interface
- GLM - Mathematics OpenGL library
- Assimp - 3D model loader

## License

This project is licensed under the [MIT License](LICENSE).
