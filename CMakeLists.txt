cmake_minimum_required(VERSION 3.21)
project(SpaceEditor)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)

set(MAIN_SOURCES "main/main.cpp")

add_executable(SpaceEditor ${MAIN_SOURCES} ${EDITOR_SOURCES})
target_link_libraries(SpaceEditor SpaceEngine)

