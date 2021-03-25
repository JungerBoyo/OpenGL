#ifndef VAOs_HPP
#define VAOs_HPP

#include "Buffers.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class VAOsManager
{
    public:
        VAOsManager();
        void GenVAO();
        void BindVAO(const GLuint& index);
        void EnableAttPtr(GLuint location);
        void VertexAttPtrConst(GLuint location, glm::vec3 values);

        void VertexAttPtr(GLuint location, GLuint size, GLenum type, const void* _offset);

    public:
        std::vector<GLuint> VAOs;
};


#endif