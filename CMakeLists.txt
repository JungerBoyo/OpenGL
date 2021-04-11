cmake_minimum_required(VERSION 3.17)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)
include_directories(OpenGL "/usr/include/glm")
include_directories(OpenGL "/usr/include/stb")

set(OpenGL_linkers -lglut -lGLU -lGL -lGLEW)
set(SDL2_linkers -lSDL2)

set(SOURCES
        src/exercises/Textures02.cpp

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

        res/stbimg/stb_image.cpp
        textures/TextureImg.cpp
        textures/TextureImg.hpp
     )

add_executable(OpenGL ${SOURCES} textures/TextureImg.cpp textures/TextureImg.hpp)

target_link_libraries(OpenGL ${OpenGL_linkers})
target_link_libraries(OpenGL ${SDL2_linkers})
