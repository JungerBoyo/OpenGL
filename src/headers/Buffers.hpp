#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "ErrorGL.hpp"

#include <GL/glew.h>
#include <vector>
#include <memory>
#include <map>

class BufferManager
{
    protected: 
        BufferManager();
        ~BufferManager();

        void GenBuffers(int count, GLuint bufferType);
        void BindBuffer(GLuint bufferType, GLuint bufferIndex);
        void UnbindBuffer(GLenum bufferType);

        template<typename DataType>
        void PushData(GLenum bufferType, GLsizeiptr sizeOfData, DataType data, GLenum usage = GL_STATIC_DRAW);

        template<typename DataType>
        void PushData(GLuint bufferIndex,  GLuint bufferType, DataType data, GLenum usage = GL_STATIC_DRAW);

        void AllocateData(GLuint bufferType, GLsizeiptr sizeOfData, GLenum usage = GL_STATIC_DRAW);

        template<typename DataType>
        void PushSubdata(GLenum bufferType, GLsizeiptr sizeOfData, DataType data, GLenum usage, GLintptr offset);
   
    protected:
        typedef std::pair<GLenum, std::unique_ptr<std::vector<GLuint>>> newBufferType;
        typedef std::map<GLenum, std::unique_ptr<std::vector<GLuint>>> buffersMap;

        buffersMap buffers;
};

template<typename DataType>
void BufferManager::PushSubdata(GLenum _bufferType, GLsizeiptr sizeOfData, DataType _data, GLenum _usage, GLintptr _offset)
{
    ASSERT(glBufferSubData(_bufferType, _offset, sizeOfData, *_data));
}

template<typename DataType>
void BufferManager::PushData(GLenum _bufferType, GLsizeiptr _sizeOfData, DataType _data, GLenum _usage)
{
    ASSERT(glBufferData(_bufferType, _sizeOfData, *_data, _usage));
}

template<typename DataType>
void BufferManager::PushData(GLuint _bufferIndex, GLuint _bufferType, DataType _data, GLenum _usage)
{
    ASSERT(glNamedBufferData(buffers[_bufferType]->at(_bufferIndex), sizeof(*_data), *_data, _usage));
}
    

class VBO : virtual public BufferManager
{
    public:
        VBO(GLsizeiptr size, GLfloat* vertexData,  GLsizeiptr colorDataSize, GLfloat* colorData);
        VBO(GLsizeiptr rawSize, GLfloat* rawData);
        void Bind();
        void Unbind();
    
    private:
        GLuint buffIdx;
};

class IBO : virtual public BufferManager
{
    public:
        IBO(GLsizeiptr size, GLuint* indicesData);
        void Bind();
        void Unbind();

    private:
        GLuint buffIdx;
};

#endif