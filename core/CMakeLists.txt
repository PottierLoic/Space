cmake_minimum_required(VERSION 3.21)
project(SpaceEngine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CORE_SOURCES
  "vector/*.cpp"
  "entity/*.cpp"
  "model/*.cpp"
  "scene/*.cpp"
  "camera/*.cpp"
  "component/*.cpp"
  "shader/*.cpp"
)

add_library(SpaceEngine STATIC ${CORE_SOURCES})

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
add_subdirectory(${LIBS_ROOT}/assimp ${CMAKE_CURRENT_BINARY_DIR}/assimp)

target_include_directories(SpaceEngine PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${LIBS_ROOT}/glad/include"
  "${LIBS_ROOT}/assimp/include"
  "${LIBS_ROOT}/glfw/include"
  "${LIBS_ROOT}/glm"
  "${LIBS_ROOT}/stb"
)

target_link_libraries(SpaceEngine
  assimp
  glad
  glfw
  ${OPENGL_gl_LIBRARY}
)
