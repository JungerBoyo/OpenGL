#include "headers/Uniforms.hpp"

Uniforms::Uniforms(std::string* _names, unsigned int _count,  std::shared_ptr<Shader>& _shader)
{
    for(int i=0; i<_count; i++)
    {
        int location = glGetUniformLocation(_shader->program,  _names[i].c_str());
        if(location == -1)
            std :: cerr << "OpenGL Error :: Uniforms :: Uniforms(..) : invalid uniform name, '" << _names[i] <<"'\n";
        else
            uniforms.push_back(location);
    }
}

void Uniforms::AddUniform(const std::string& _name, std::shared_ptr<Shader>& _shader)
{
    int location = glGetUniformLocation(_shader->program,  _name.c_str());
    if(location == -1)
        std :: cerr << "OpenGL Error :: Uniforms :: Uniforms(..) : invalid uniform name, '" << _name <<"'\n";
    else
        uniforms.push_back(location);
}

void Uniforms::BindUniformMat4(const int& _idx, const int& _count, bool _transpose, GLfloat* _data)
{
    ASSERT(glUniformMatrix4fv(uniforms[_idx], _count, _transpose, _data));
}

void Uniforms::BindUniformMat1x2(const int& _idx, const int& _count, bool _transpose, GLfloat* _data)
{
    ASSERT(glUniformMatrix2fv(uniforms[_idx], _count, _transpose, _data));
}

void Uniforms::BindUniformVec4(const int& _idx, const int& _count, GLfloat* _data)
{
    ASSERT(glUniform4fv(uniforms[_idx], _count, _data));
}

void Uniforms::BindUniformConstUI(const int& _idx, GLuint _data)
{
    ASSERT(glUniform1ui(uniforms[_idx], _data));
}