#ifndef SHADERS_HPP
#define SHADERS_HPP

#include "ErrorGL.hpp"
#include "Uniforms.hpp"
#include <fstream>
#include <sstream>

class Shader
{
    friend class Uniforms;

    public:
        Shader(const std::string& verShaderPath, const std::string& fragShaderPath, const std::string& geomShaderPath);

        void Bind();
        void Unbind();

    private:  
        std::stringstream ParseShader(const std::string& shaderPath);
        GLuint CompileShader(GLuint shader, const std::string& path, GLuint shType);

        int program;
};

#endif