add_executable(SpaceTests main.cpp testVector2.cpp testVector3.cpp testProject.cpp)

target_link_libraries(SpaceTests SpaceEngine)
target_include_directories(SpaceTests PRIVATE ${SpaceEngine_INCLUDE_DIRS})