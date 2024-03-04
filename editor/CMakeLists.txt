cmake_minimum_required(VERSION 3.21)
project(SpaceEditor)

file(GLOB_RECURSE EDITOR_SOURCES "*.cpp")

add_executable(SpaceEditor ${EDITOR_SOURCES})

target_include_directories(SpaceEditor PRIVATE
  "${LIBS_ROOT}/imgui"
)

# Link the core library
target_link_libraries(SpaceEditor
  SpaceEngine
)