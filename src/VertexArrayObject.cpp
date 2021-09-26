#include "../include/engine/VertexArrayObject.h"
#include "../include/framework/Buffer.h"

using namespace Engine;

VertexArrayObject::VertexArrayObject() {
  GL::createVertexArrays(1, &this->_vaoId);
}

VertexArrayObject::~VertexArrayObject() {
  GL::deleteVertexArrays(1, &this->_vaoId);
}

void VertexArrayObject::setBuffer(int location, BufferBase& buffer) {
  if (buffer._target == GL_UNIFORM_BUFFER) {
    GL::bindBufferBase(GL_UNIFORM_BUFFER, location, buffer._bufferId);
    return;
  }
  GL::vertexArrayAttrib(this->_vaoId, location, buffer._bufferId, buffer._itemSize, 3, buffer._dataType, buffer._target);
}

void VertexArrayObject::bind() {
  glBindVertexArray(this->_vaoId);
}

void VertexArrayObject::unbind() {
  glBindVertexArray(0);
}
