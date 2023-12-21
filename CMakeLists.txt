cmake_minimum_required(VERSION 3.21)

project(space)

set(CMAKE_CXX_STANDARD 17)

add_executable(space src/main.cpp)

# Variables
set(GLAD_PREFIX
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad"
  CACHE STRING "Path to glad"
)
set(GLFW_PREFIX
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw"
  CACHE STRING "Path to GLFW"
)
set(DEAR_IMGUI_PREFIX
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui"
  CACHE STRING "Path to Dear imgui"
)

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/libs"
)

find_package(OpenGL REQUIRED)

if (UNIX)
  if (NOT APPLE)
    find_package(Threads REQUIRED)
    find_package(X11 REQUIRED)
  endif()
endif()

# GLAD
add_library(glad "${GLAD_PREFIX}/src/glad.c")
include_directories("${GLAD_PREFIX}/include")
target_link_libraries(space PRIVATE glad)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(${GLFW_PREFIX})
include_directories(
  "${GLFW_PREFIX}/include"
)

# DearImGui
list(APPEND sources
  ${DEAR_IMGUI_PREFIX}/imgui.cpp
  ${DEAR_IMGUI_PREFIX}/imgui.h
  ${DEAR_IMGUI_PREFIX}/imgui_demo.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_draw.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_tables.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_widgets.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_impl_glfw.cpp
  ${DEAR_IMGUI_PREFIX}/imgui_impl_opengl3.cpp
)

target_sources(space
  PRIVATE
    ${sources}
)

target_link_libraries(space
  PRIVATE
  ${OPENGL_gl_LIBRARY}
  glfw
)

if (UNIX)
  if (APPLE)
    target_link_libraries(space
      PRIVATE
      "-framework Cocoa"
      "-framework IOKit"
      "-framework CoreVideo"
    )
  else()
    target_link_libraries(space
      PRIVATE
      ${CMAKE_THREAD_LIBS_INIT}
      ${X11_LIBRARIES}
      ${CMAKE_DL_LIBS}
    )
  endif()
endif()

set_target_properties(space
  PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
)

# --- installation
include(GNUInstallDirs)

install(TARGETS space
  COMPONENT space
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/space
)
install(FILES
  ${resource_files}
  DESTINATION ${CMAKE_INSTALL_BINDIR}/space
  COMPONENT space
)