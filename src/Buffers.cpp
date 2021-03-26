#include "headers/Buffers.hpp"
#include <iostream>

BufferManager::BufferManager()
{
    
}

void BufferManager::GenBuffers(int _count, GLenum _bufferType)
{
    if(buffers.count(_bufferType) == 0)
        buffers.insert(newBufferType(_bufferType, std::make_unique<std::vector<GLuint>>(_count)));
    else
        buffers[_bufferType]->push_back(0);
    
    ASSERT(glGenBuffers(_count, &buffers[_bufferType]->back())); 
}

void BufferManager::BindBuffer(GLenum _bufferType, GLuint _bufferIndex)
{
    ASSERT(glBindBuffer(_bufferType, buffers[_bufferType]->at(_bufferIndex)));
}

void BufferManager::UnbindBuffer(GLenum _bufferType)
{
    ASSERT(glBindBuffer(_bufferType, 0));
}
void BufferManager::AllocateData(GLuint _bufferType, GLsizeiptr _sizeOfData, GLenum _usage)
{
    ASSERT(glBufferData(_bufferType, _sizeOfData, NULL, _usage));
}

BufferManager::~BufferManager()
{
    for(buffersMap::iterator It = buffers.begin(); It != buffers.end(); It++)
        for(int i=0; i<It->second->size(); i++)
            glInvalidateBufferData(It->second->at(i));    
}

VBO::VBO(GLsizeiptr _vertexDataSize, GLfloat* _vertexData, GLsizeiptr _colorDataSize, GLfloat* _colorData)
{
    GenBuffers(1, GL_ARRAY_BUFFER);
    this->buffIdx = buffers[GL_ARRAY_BUFFER]->size() - 1; 

    this->Bind();

    if(_colorData == NULL)
        PushData(GL_ARRAY_BUFFER, _vertexDataSize,  &_vertexData);
    else
    {
        AllocateData(GL_ARRAY_BUFFER, _vertexDataSize + _colorDataSize);
        PushSubdata(GL_ARRAY_BUFFER, _vertexDataSize, &_vertexData, GL_STATIC_DRAW, 0);
        PushSubdata(GL_ARRAY_BUFFER, _colorDataSize, &_colorData, GL_STATIC_DRAW, _vertexDataSize);
    }
}

void VBO::Bind()
{
    BindBuffer(GL_ARRAY_BUFFER, this->buffIdx);
}

void VBO::Unbind()
{
    UnbindBuffer(GL_ARRAY_BUFFER);
}

IBO::IBO(GLsizeiptr _size, GLuint* _indicesData)
{
    GenBuffers(1, GL_ELEMENT_ARRAY_BUFFER);
    this->buffIdx = buffers[GL_ELEMENT_ARRAY_BUFFER]->size() - 1; 

    this->Bind();

    PushData(GL_ELEMENT_ARRAY_BUFFER, _size, &_indicesData);
}

void IBO::Bind()
{
    BindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffIdx);
}

void IBO::Unbind()
{
    UnbindBuffer(GL_ELEMENT_ARRAY_BUFFER);
}
