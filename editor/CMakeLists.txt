cmake_minimum_required(VERSION 3.21)
project(Space)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE EDITOR_SOURCES
  "editor_gui/*.cpp"
  "editor_camera/*.cpp"
)

file(GLOB IMGUI_SOURCES "${LIBS_ROOT}/imgui/*.cpp" "${LIBS_ROOT}/imgui/*.h")

add_library(SpaceEditor STATIC ${EDITOR_SOURCES} ${IMGUI_SOURCES})
target_compile_options(SpaceEditor PRIVATE -Wall -Wextra -Werror)
target_include_directories(SpaceEditor PUBLIC ${SpaceEngine_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} "${LIBS_ROOT}")
target_link_libraries(SpaceEditor PRIVATE SpaceEngine)

add_executable(Space main.cpp)
target_compile_options(Space PRIVATE -Wall -Wextra -Werror)
target_include_directories(Space PUBLIC ${SpaceEngine_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} "${LIBS_ROOT}")
target_link_libraries(Space PRIVATE SpaceEditor SpaceEngine)
