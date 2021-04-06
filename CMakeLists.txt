cmake_minimum_required(VERSION 3.17)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)
#include_directories(OpenGL "/usr/include/SDL2")
#include_directories(OpenGL "/usr/include/GL")
include_directories(OpenGL "/usr/include/glm")

set(OpenGL_linkers -lglut -lGLU -lGL -lGLEW)
set(SDL2_linkers -lSDL2)



set(SOURCES
        src/exercises/FrameRenderBuffers.cpp

        src/headers/Buffers.hpp
        src/Buffers.cpp

        src/headers/shaders.hpp
        src/shaders.cpp

        src/headers/VAOs.hpp
        src/VAOs.cpp

        src/headers/Uniforms.hpp
        src/Uniforms.cpp

        src/headers/SDLManager.hpp
        src/SDLManager.cpp

        src/headers/transformations.hpp
        src/transformations.cpp

        src/headers/ErrorGL.hpp
        src/exercises/instancedRendering.cpp)

add_executable(OpenGL ${SOURCES})

target_link_libraries(OpenGL ${OpenGL_linkers})
target_link_libraries(OpenGL ${SDL2_linkers})


#add_executable(OpenGL
#
#        src/main.cpp
#
#        src/headers/Buffers.hpp
#        src/Buffers.cpp
#
#        src/headers/shaders.hpp
#        src/shaders.cpp
#
#        src/headers/VAOs.hpp
#        src/VAOs.cpp
#
#        src/headers/Uniforms.hpp
#        src/Uniforms.cpp
#
#        src/headers/SDLManager.hpp
#        src/SDLManager.cpp
#
#        src/headers/transformations.hpp
#        src/transformations.cpp
#
#        src/headers/ErrorGL.hpp
#        )
#