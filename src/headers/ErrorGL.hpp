#ifndef ERROR_GL_HPP
#define ERROR_GL_HPP

#include <GL/glew.h>
#include <iostream>

static void ClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static void GetError(const char* func, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "OpenGL Error::" << std::hex << error << std::dec <<
                     "\n At::" << func <<'('<<file<<")\n On line::" << line << std::endl;
    }
}

#define ASSERT(x)\
                    ClearError();\
                    x;\
                    GetError(#x, __FILE__, __LINE__);


#endif