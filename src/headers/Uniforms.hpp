#ifndef UNIFORMS_HPP
#define UNIFORMS_HPP

#include <GL/glew.h>
#include "shaders.hpp"
#include <string>
#include <vector>
#include <memory>

class Shader;

class Uniforms
{
    public:
        Uniforms(std::string* names, std::shared_ptr<Shader>& shader);
        void AddUniform(const std::string& name, std::shared_ptr<Shader>& shader);
        void BindUniformMat4(const int& idx, const int& count, bool transpose, GLfloat* data);
        void BindUniformVec4(const int& idx, const int& count, GLfloat* data);

    private:
        std::vector<int> uniforms;   
};

#endif