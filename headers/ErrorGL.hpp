#ifndef ERROR_GL_HPP
#define ERROR_GL_HPP

#include <GL/glew.h>
#include <iostream>

static void ClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static void GetError()
{
    while(GLenum error = glGetError())
        std::cout << "OpenGL Error :: " << std::hex << error << std::endl;
}



#define ASSERT(x)\
                    ClearError();\
                    x;\
                    GetError();


#endif