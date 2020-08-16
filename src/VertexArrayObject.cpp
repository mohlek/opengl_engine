#include "../include/engine/VertexArrayObject.h"

using namespace Engine;

VertexArrayObject::VertexArrayObject() {
  GL::createVertexArrays(1, &this->_vaoId);
}

VertexArrayObject::~VertexArrayObject() {
  GL::deleteVertexArrays(1, &this->_vaoId);
}

void VertexArrayObject::addBuffer(const BufferBase& buffer) {
  const int index = this->_buffers.size();
  GL::vertexArrayAttrib(this->_vaoId, index, buffer._bufferId, buffer._itemSize, 3, buffer._dataType, buffer._target);
  this->_buffers.push_back(buffer);
}

ExitScopeHelper VertexArrayObject::bind() {
  glBindVertexArray(this->_vaoId);
  return ExitScopeHelper([](){
    glBindVertexArray(0);  
  });
}
