cmake_minimum_required(VERSION 3.21)

# Variables
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(GLFW_DIR "${LIBS_DIR}/glfw")
set(GLM_DIR "${LIBS_DIR}/glm")
set(GLAD_DIR "${LIBS_DIR}/glad")
set(IMGUI_DIR "${LIBS_DIR}/imgui")
set(STB_DIR "${LIBS_DIR}/stb")
set(ASSIMP_DIR "${LIBS_DIR}/assimp")

include_directories("${LIBS_DIR}")
find_package(OpenGL REQUIRED)

# Executable
project(space)
set(CMAKE_CXX_STANDARD 17)
add_executable(space ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# GLAD
add_library(glad "${LIBS_DIR}/glad/src/glad.c")
target_include_directories(glad PRIVATE "${LIBS_DIR}/glad/include")

# GLFW
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(${LIBS_DIR}/glfw)

# DearImGui
file(GLOB IMGUI_SOURCES "${IMGUI_DIR}/*.cpp" "${IMGUI_DIR}/*.h")

# Assimp
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(${ASSIMP_DIR})

# Space
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.hpp")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${SOURCE_DIR}/*.cpp")

# All
target_sources(space PRIVATE ${SOURCE_LIST} ${IMGUI_SOURCES} ${HEADER_LIST} ${GLM_HEADERS})
target_include_directories(space PRIVATE ${INCLUDE_DIR}
  "${GLFW_DIR}/include"
  "${GLAD_DIR}/include"
  "${STB_DIR}/"
  "${GLM_DIR}/"
  "${ASSIMP_DIR}/include"
)
target_link_libraries(space PRIVATE ${OPENGL_gl_LIBRARY} assimp glfw glad)

# Special cases
if (UNIX)
  if (APPLE)
    target_link_libraries(space PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
  else()
    find_package(Threads REQUIRED)
    find_package(X11 REQUIRED)
    target_link_libraries(space PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES} ${CMAKE_DL_LIBS})
  endif()
endif()

# Debug mode
if(FLAGS STREQUAL "--debug")
  target_compile_options(space PRIVATE -Wall -Wextra)
else()
  target_compile_options(space PRIVATE -Wall -Wextra -Werror)
endif()
