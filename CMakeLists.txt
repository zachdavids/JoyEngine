cmake_minimum_required(VERSION 2.6)

# Name of project
project(Wolfenstein)

# Specify project files: header files and source files
file(GLOB SOURCES
    Source/Public/*.h
    Source/Private/*.c
    Source/Private/*.cpp
)

# Add executable based on the source files
add_executable(Wolfenstein ${SOURCES})

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(Wolfenstein ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/Libraries/" CACHE PATH "Folder with GLEW, GLFW, GLM, ASSIMP, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include
                    Source/Public)
if(NOT WIN32)
    find_library(GLFW_LIB glfw3)
elseif(WIN32)
    find_library(GLFW_LIB glfw3 HINTS ${LIBRARY_PATH}/lib/GLFW)
endif(NOT WIN32)
target_link_libraries(Wolfenstein ${GLFW_LIB})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(Wolfenstein PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
