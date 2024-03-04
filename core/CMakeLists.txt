cmake_minimum_required(VERSION 3.21)
project(SpaceEngine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CORE_SOURCES
  "vector/*.cpp"
  # "entity/*.cpp"
  # "model/*.cpp"
  # "scene/*.cpp"
  # "camera/*.cpp"
  # "component/*.cpp"
  # "shader/*.cpp"
)

add_library(SpaceEngine STATIC ${CORE_SOURCES})
target_include_directories(SpaceEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
