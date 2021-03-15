#include "../headers/VAOs.hpp"

#include "../headers/ErrorGL.hpp"


VAOsManager::VAOsManager() 
{
    
}

void VAOsManager::GenVA(int _count) 
{
    VAOs = new std::vector<GLuint>(_count);
    ASSERT(glGenVertexArrays(_count, VAOs->data())); 
}

void VAOsManager::BindVA(unsigned int _index) 
{
    ASSERT(glBindVertexArray(VAOs->at(_index)));
}

void VAOsManager::EnableAttPtr(GLuint _location) 
{
    ASSERT(glEnableVertexAttribArray(_location));
}

void VAOsManager::VertexAttPtr(GLuint _location, GLuint _size, GLenum _type)
{
    ASSERT(glVertexAttribPointer(_location, _size, _type, GL_FALSE, 0, 0));
}


void VAOsManager::VertexAttPtrConst(GLuint _location, glm::vec3 _values)
{
    ASSERT(glVertexAttrib3f(_location, _values.x, _values.y, _values.z));
}