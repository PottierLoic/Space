cmake_minimum_required(VERSION 3.21)
project(Space)

set(CMAKE_CXX_STANDARD 17)

# Include the core library
add_subdirectory(core)

# TODO: Add the CMakeLists to the editor
# If you have an editor that depends on the core library
# add_subdirectory(editor)

# Include the tests directory
add_subdirectory(tests)