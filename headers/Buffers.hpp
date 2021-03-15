#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "ErrorGL.hpp"

#include <GL/glew.h>
#include <vector>
#include <map>

class BufferManager
{
    public: 
        BufferManager();
        ~BufferManager();

        void GenBuffers(int count, GLuint bufferType);
        void BindBuffer(GLuint bufferType, GLuint bufferIndex);
        void UnbindBuffer(GLenum bufferType);

        template<typename DataType>
        void PushData(GLenum bufferType, DataType data, GLenum usage = GL_STATIC_DRAW);

        template<typename DataType>
        void PushData(GLuint bufferIndex, GLuint bufferType, DataType data, GLenum usage = GL_STATIC_DRAW);

        void AllocateData(GLuint bufferType, GLsizeiptr sizeOfData, GLenum usage = GL_STATIC_DRAW);

        template<typename DataType>
        void PushSubdata(GLenum bufferType, DataType data, GLenum usage, GLintptr offset);
   
    public:
        typedef std::pair<GLenum, std::vector<GLuint>*> newBufferType;
        typedef std::map<GLenum, std::vector<GLuint>*> buffersMap;

        buffersMap buffers;
};

template<typename DataType>
void BufferManager::PushSubdata(GLenum _bufferType, DataType _data, GLenum _usage, GLintptr _offset)
{
    ASSERT(glBufferSubData(_bufferType, _offset, sizeof(*_data), *_data));
}

template<typename DataType>
void BufferManager::PushData(GLenum _bufferType, DataType _data, GLenum _usage)
{
    ASSERT(glBufferData(_bufferType, sizeof(*_data), *_data, _usage));
}

template<typename DataType>
void BufferManager::PushData(GLuint _bufferIndex, GLuint _bufferType, DataType _data, GLenum _usage)
{
    ASSERT(glNamedBufferData(buffers[_bufferType]->at(_bufferIndex), sizeof(*_data), *_data, _usage));
}
    

#endif