#include "../include/engine/Buffer.h"

#include <cstring>
#include <algorithm>

using namespace Engine;

Buffer::Buffer(GLenum bufferType, int size = 0) : bufferType(bufferType), size(size) {
    glGenBuffers(1, &this->bufferId);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &this->bufferId);
}

ExitScopeHelper Buffer::bind() {
    glBindBuffer(this->bufferType, this->bufferId);
    auto bufferType = this->bufferType;
    return ExitScopeHelper([bufferType](){
          glBindBuffer(bufferType, 0);
        });
}

void* Buffer::map(GLenum access = GL_READ_WRITE) {
    if (glMapNamedBuffer) {
        if (access != GL_READ_ONLY) {
            glNamedBufferData(this->bufferId, this->size, NULL, GL_STATIC_DRAW);
        } 
        return glMapNamedBuffer(this->bufferId, access);
    }

    auto unbindHelper = bind();
    if (access != GL_READ_ONLY) {
        glBufferData(this->bufferType, this->size, NULL, GL_STATIC_DRAW);
    }
    return glMapBuffer(this->bufferType, access);
}

void Buffer::pushData(const void* data, unsigned int size, unsigned int offset) {
    this->size = std::max(GLint(offset + size), this->size);

    #ifdef MEMCPY
        void* addr = map(GL_WRITE_ONLY);
        std::memcpy((char*)addr + offset, data, size);
        unmap();
    #else
        if (glNamedBufferSubData) {
            if (offset == 0) {
              glNamedBufferData(this->bufferId, size, NULL, GL_STATIC_DRAW);
            }
            glNamedBufferSubData(this->bufferId, offset, size, data);
            return;
        }

        auto unbindHelper = bind();
        if (offset == 0) {
          glBufferData(this->bufferType, size, NULL, GL_STATIC_DRAW);
        }
        glBufferSubData(this->bufferType, offset, size, data);
    #endif
}

bool Buffer::unmap() {
    if (glUnmapNamedBuffer) {
        return glUnmapNamedBuffer(this->bufferId);
    }

    auto unbindHelper = bind();
    return glUnmapBuffer(this->bufferType);
}
