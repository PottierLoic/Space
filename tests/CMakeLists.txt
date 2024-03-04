cmake_minimum_required(VERSION 3.21)
project(SpaceTests)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE TEST_SOURCES "./*.cpp")

add_executable(SpaceTests ${TEST_SOURCES})

target_link_libraries(SpaceTests SpaceEngine)
