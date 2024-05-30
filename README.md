# Space

Space is a WIP 2D / 3D game engine made for fun.

It is cross platform and uses GLFW, OpenGL and ImGui.

**Please note that there is no official release for the project, and it is unlikely that there will be any in the future**  
I'm mainly doing this to progress in c++ and OpenGL and because I always wanted to develop my own game engine.

## Building from source

### Requirements

- [CMake](https://cmake.org/).
- Make
- a C++ compiler (MSVC, g++, Clang, ...)
- [Python](https://www.python.org/)

### Building

First, get the repo on your computer.
```bash
git clone https://github.com/PottierLoic/Space.git
cd Space
```

Get the submodules too
```bash
git submodule init
git submodule update
```

Space comes in 3 parts: the engine, the editor, and the tests.  
Each part has it's own folder: core, editor and tests respectively.  

You need python to build the project:
```bash
py build.py
```

This compiles the core folder into a library called SpaceEngine that is located in `build/core/`.  
The editor executable can be found in `build/editor/`.  
The tests executable can be found in `build/tests/`.  

## External libraries

Space is using some external libraries :

- [GLFW](https://www.glfw.org/) - Graphic library.
- [Glad](https://glad.dav1d.de/) - OpenGL loader.
- [GLM](https://github.com/g-truc/glm) - Mathematics OpenGL library.
- [ImGui](https://github.com/ocornut/imgui) - C++ GUI.
- [Assimp](https://github.com/assimp/assimp) - 3D model loader.
- [stb](https://github.com/nothings/stb) - Collection of convenient single header libraries.
- [nlohmann/json](https://github.com/nlohmann/json) - JSON for Modern C++.

## License

This project is licensed under the [MIT License](LICENSE).
