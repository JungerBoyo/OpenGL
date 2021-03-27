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
        Uniforms(std::string* names, unsigned int count, std::shared_ptr<Shader>& shader);
        void AddUniform(const std::string& name, std::shared_ptr<Shader>& shader);
        void BindUniformMat4(const int& idx, const int& count, bool transpose, GLfloat* data);
        void BindUniformMat1x2(const int& idx, const int& count, bool transpose, GLfloat* data);
        void BindUniformVec4(const int& idx, const int& count, GLfloat* data);
        void BindUniformConstUI(const int& idx, GLuint data);

    private:
        std::vector<int> uniforms;   
};

#endif