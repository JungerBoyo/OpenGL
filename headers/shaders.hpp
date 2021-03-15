#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <GL/glew.h>
#include <fstream>
#include <sstream>

class Shaders
{
    public:
        Shaders(const std::string& verShaderPath, const std::string& fragShaderPath, const std::string& geomShaderPath, GLuint* program);

    private:  
        std::stringstream ParseShader(const std::string& shaderPath);
        GLuint CompileShader(GLuint shader, const std::string& path, GLuint shType);
        void BindShaders();
};

#endif