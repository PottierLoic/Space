cmake_minimum_required(VERSION 3.21)
project(project_template)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIBS_ROOT "../libs")

# TODO: Use a good path like the location where the final lib will be.
add_subdirectory(../core ${CMAKE_CURRENT_BINARY_DIR}/core_build)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} SpaceEngine)
