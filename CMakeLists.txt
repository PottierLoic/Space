cmake_minimum_required(VERSION 3.21)

project(space)
set(CMAKE_CXX_STANDARD 17)

# Variables
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(GLFW_DIR "${LIBS_DIR}/glfw")
set(GLM_DIR "${LIBS_DIR}/glm")
set(GLAD_DIR "${LIBS_DIR}/glad")
set(IMGUI_DIR "${LIBS_DIR}/imgui")
set(STB_DIR "${LIBS_DIR}/stb")
set(ASSIMP_DIR "${LIBS_DIR}/assimp")

file(GLOB_RECURSE COMMON_SOURCES "${SOURCE_DIR}/*.cpp" "${TEST_DIR}/*.cpp")
list(REMOVE_ITEM COMMON_SOURCES "${SOURCE_DIR}/main.cpp" "${TEST_DIR}/main.cpp")

find_package(OpenGL REQUIRED)

# Glad library creation
add_library(glad "${LIBS_DIR}/glad/src/glad.c")
target_include_directories(glad PRIVATE "${LIBS_DIR}/glad/include")

# GLFW build
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(${LIBS_DIR}/glfw)

# DearImGui sources
file(GLOB IMGUI_SOURCES "${IMGUI_DIR}/*.cpp" "${IMGUI_DIR}/*.h")

# Assimp build
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_ASSIMP_VIEW OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(${ASSIMP_DIR})

# Specific cases
if (UNIX)
  if (APPLE)
    link_libraries("-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
  else()
    find_package(Threads REQUIRED)
    find_package(X11 REQUIRED)
    link_libraries(${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES} ${CMAKE_DL_LIBS})
  endif()
endif()

# Debug mode
if(FLAGS STREQUAL "--debug")
  add_compile_options(-Wall -Wextra)
else()
  add_compile_options(-Wall -Wextra -Werror)
endif()

# Targets
macro(create_target target sources)
  add_executable(${target} ${sources})
  target_sources(${target} PRIVATE ${COMMON_SOURCES} ${HEADER_LIST} ${IMGUI_SOURCES} ${GLM_HEADERS})
  target_link_libraries(${target} PRIVATE assimp glfw glad ${OPENGL_gl_LIBRARY})
  target_include_directories(${target} PRIVATE ${LIBS_DIR} ${INCLUDE_DIR} ${GLFW_DIR}/include ${GLAD_DIR}/include ${STB_DIR}/ ${GLM_DIR}/ ${ASSIMP_DIR}/include)
endmacro()

# Main and Test targets
create_target(space ${SOURCE_DIR}/main.cpp)
create_target(test ${TEST_DIR}/main.cpp)