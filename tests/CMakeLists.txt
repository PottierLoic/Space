cmake_minimum_required(VERSION 3.21)
project(SpaceTests)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE TEST_SOURCES "./*.cpp")

add_executable(SpaceTests ${TEST_SOURCES})
if (MSVC)
    target_compile_options(SpaceTests PRIVATE /W4 /WX)
else()
    target_compile_options(SpaceTests PRIVATE -Wall -Wextra -Werror)
endif()
target_link_libraries(SpaceTests SpaceEngine SpaceEditor)
