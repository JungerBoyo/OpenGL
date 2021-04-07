#include "headers/VAOs.hpp"
#include "headers/ErrorGL.hpp"


VAOsManager::VAOsManager() 
{
    
}

void VAOsManager::GenVAO() 
{
    VAOs.push_back(0);
    DEBUG(glGenVertexArrays(1, &VAOs.back()));
}

void VAOsManager::BindVAO(const GLuint& _index) 
{
    DEBUG(glBindVertexArray(VAOs.at(_index)));
}

void VAOsManager::EnableAttPtr(GLuint _location) 
{
    DEBUG(glEnableVertexAttribArray(_location));
}

void VAOsManager::VertexAttPtr(GLuint _location, GLuint _size, GLenum _type, const void* _offset)
{
    DEBUG(glVertexAttribPointer(_location, _size, _type, GL_FALSE, 0, _offset));
    
}

void VAOsManager::VertexAttPtrConst(GLuint _location, glm::vec3 _values)
{
    DEBUG(glVertexAttrib3f(_location, _values.x, _values.y, _values.z));
}