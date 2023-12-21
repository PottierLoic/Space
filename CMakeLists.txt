cmake_minimum_required(VERSION 3.21)

# Variables
set(GLAD_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad" CACHE STRING "Path to glad")
set(GLFW_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw" CACHE STRING "Path to GLFW")
set(DEAR_IMGUI_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui" CACHE STRING "Path to Dear imgui")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libs")

find_package(OpenGL REQUIRED)

if (UNIX)
  if (NOT APPLE)
    find_package(Threads REQUIRED)
    find_package(X11 REQUIRED)
  endif()
endif()

# MAIN EXECUTABLE
project(space)
set(CMAKE_CXX_STANDARD 17)
add_executable(space ${PROJECT_SOURCE_DIR}/src/main.cpp)

# GLAD
add_library(glad "${GLAD_PREFIX}/src/glad.c")
include_directories("${GLAD_PREFIX}/include")
target_link_libraries(space PRIVATE glad)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(${GLFW_PREFIX})
include_directories("${GLFW_PREFIX}/include")

# DearImGui
list(APPEND IMGUI_SOURCES
  ${DEAR_IMGUI_PREFIX}/imgui.cpp
  ${DEAR_IMGUI_PREFIX}/imgui.h
  ${DEAR_IMGUI_PREFIX}/imgui_demo.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_draw.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_tables.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_widgets.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_impl_glfw.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_impl_opengl3.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_stdlib.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_stdlib.h
)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

target_sources(space PRIVATE ${IMGUI_SOURCES} ${SOURCE_LIST} ${HEADER_LIST})
target_link_libraries(space PRIVATE ${OPENGL_gl_LIBRARY} glfw )
target_include_directories(space PRIVATE ${PROJECT_SOURCE_DIR}/include)

if (UNIX)
  if (APPLE)
    target_link_libraries(space PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
  else()
    target_link_libraries(space PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES} ${CMAKE_DL_LIBS})
  endif()
endif()

if(FLAGS STREQUAL "--debug")
  target_compile_options(space PRIVATE -Wall -Wextra)
else()
  target_compile_options(space PRIVATE -Wall -Wextra -Werror)
endif()

# TESTING EXECUTABLE
project(test)
set(CMAKE_CXX_STANDARD 17)
add_executable(test ${PROJECT_SOURCE_DIR}/tests/main.cpp)

# GLAD
target_link_libraries(test PRIVATE glad)

# GLFW
include_directories("${GLFW_PREFIX}/include")

# Project sources and headers
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE TEST_SOURCE_LIST CONFIURE_DEPENDS "${PROJECT_SOURCE_DIR}/tests/*.cpp")
# Remove src/main.cpp
list(REMOVE_ITEM SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/main.cpp")

target_sources(test PRIVATE ${IMGUI_SOURCES} ${SOURCE_LIST} ${TEST_SOURCE_LIST} ${HEADER_LIST})
target_link_libraries(test PRIVATE ${OPENGL_gl_LIBRARY} glfw )
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/include)

if (UNIX)
  if (APPLE)
    target_link_libraries(test PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
  else()
    target_link_libraries(test PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES} ${CMAKE_DL_LIBS})
  endif()
endif()

if(FLAGS STREQUAL "--debug")
  target_compile_options(test PRIVATE -Wall -Wextra)
else()
  target_compile_options(test PRIVATE -Wall -Wextra -Werror)
endif()