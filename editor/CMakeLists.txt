cmake_minimum_required(VERSION 3.21)
project(SpaceEditor)
set(CMAKE_CXX_STANDARD 17)


file(GLOB_RECURSE EDITOR_SOURCES
  "menu/*.cpp"
  "project/*.cpp"
  "editor_camera/*.cpp"
)

file(GLOB IMGUI_SOURCES "${LIBS_ROOT}/imgui/*.cpp" "${LIBS_ROOT}/imgui/*.h")

add_executable(SpaceEditor main.cpp ${EDITOR_SOURCES})

target_compile_options(SpaceEditor PRIVATE -Wall -Wextra -Werror)
target_include_directories(SpaceEditor PRIVATE ${SpaceEngine_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} "${LIBS_ROOT}")
target_link_libraries(SpaceEditor PRIVATE SpaceEngine)
target_sources(SpaceEditor PRIVATE ${IMGUI_SOURCES})
