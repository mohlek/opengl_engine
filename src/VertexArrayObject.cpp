#include "../include/engine/VertexArrayObject.h"

using namespace Engine;

VertexArrayObject::VertexArrayObject() {
  GL::createVertexArrays(1, &this->_vaoId);
}

VertexArrayObject::~VertexArrayObject() {
  GL::deleteVertexArrays(1, &this->_vaoId);
}

void VertexArrayObject::setBuffer(int location, BufferBase& buffer) {
  GL::vertexArrayAttrib(this->_vaoId, location, buffer._bufferId, buffer._itemSize, 3, buffer._dataType, buffer._target);
}

void VertexArrayObject::bind() {
  glBindVertexArray(this->_vaoId);
}

void VertexArrayObject::unbind() {
  glBindVertexArray(0);
}
