#include "../headers/Buffers.hpp"
#include <iostream>

BufferManager::BufferManager()
{
    
}

void BufferManager::GenBuffers(int _count, GLenum _bufferType)
{
    buffers.insert(newBufferType(_bufferType, new std::vector<GLuint>(_count)));
    

    ASSERT(glGenBuffers(_count, buffers[_bufferType]->data()));
}

void BufferManager::BindBuffer(GLenum _bufferType, GLuint _bufferIndex)
{
    ASSERT(glBindBuffer(_bufferType, buffers[_bufferType]->at(0)));
}

void BufferManager::UnbindBuffer(GLenum _bufferType)
{
    ASSERT(glBindBuffer(_bufferType, 0));
}
void BufferManager::AllocateData(GLuint _bufferType, GLsizeiptr _sizeOfData, GLenum _usage)
{
    glBufferData(_bufferType, _sizeOfData, NULL, _usage);
}

BufferManager::~BufferManager()
{
    for(buffersMap::iterator It = buffers.begin(); It != buffers.end(); It++)
        for(int i=0; i<It->second->size(); i++)
            glInvalidateBufferData(It->second->at(i));    
}
