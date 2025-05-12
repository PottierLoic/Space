cmake_minimum_required(VERSION 3.21)
project(SpaceEngine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CORE_SOURCES
  "maths/*.cpp"
  "entity/*.cpp"
  "model/*.cpp"
  "scene/*.cpp"
  "component/*.cpp"
  "shader/*.cpp"
  "log/*.cpp"
  "serializer/*.cpp"
  "space/*.cpp"
  "renderer/*.cpp"
  "time/*.cpp"
)

add_library(SpaceEngine STATIC ${CORE_SOURCES})
if (MSVC)
    target_compile_options(SpaceEngine PRIVATE /W4 /WX)
else()
    target_compile_options(SpaceEngine PRIVATE -Wall -Wextra -Werror)
endif()

# Glad build
add_library(glad "${LIBS_ROOT}/glad/src/glad.c")
target_include_directories(glad PRIVATE "${LIBS_ROOT}/glad/include")

# GLFW build
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(${LIBS_ROOT}/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)

# Assimp build
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_ASSIMP_VIEW OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_NO_EXPORT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
add_subdirectory(${LIBS_ROOT}/assimp ${CMAKE_CURRENT_BINARY_DIR}/assimp)

target_include_directories(SpaceEngine PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${LIBS_ROOT}/glad/include"
  "${LIBS_ROOT}/assimp/include"
  "${LIBS_ROOT}/glfw/include"
  "${LIBS_ROOT}/glm"
  "${LIBS_ROOT}/stb"
  "${LIBS_ROOT}/json/include"
)

target_link_libraries(SpaceEngine
  assimp
  glad
  glfw
  ${OPENGL_gl_LIBRARY}
)
