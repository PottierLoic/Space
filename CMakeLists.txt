cmake_minimum_required( VERSION 3.5 )

project( Space )

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( GLAD_GL "" )

add_subdirectory( libs/glfw )

option( USE_GLAD "Use GLAD from GLFW" ON )

if( USE_GLAD )
	include_directories("${GLFW_SOURCE_DIR}/deps")
	set( GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" )
endif()

add_executable( Space WIN32 src/main.cpp ${GLAD_GL} )
target_link_libraries( Space ${OPENGL_LIBRARIES} glfw )