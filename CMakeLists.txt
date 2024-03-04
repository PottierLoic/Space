cmake_minimum_required(VERSION 3.21)
project(Space)
set(CMAKE_CXX_STANDARD 17)

set(LIBS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/libs")
option(BUILD_EDITOR "Build the SpaceEditor application" ON)

add_subdirectory(core)
if(BUILD_EDITOR)
  add_subdirectory(editor)
endif()

add_subdirectory(tests)
