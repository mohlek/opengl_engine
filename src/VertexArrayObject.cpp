#include "../include/engine/VertexArrayObject.h"

using namespace Engine;

VertexArrayObject::VertexArrayObject() {
  GL::createVertexArrays(1, &this->_vaoId);
}

VertexArrayObject::~VertexArrayObject() {
  //this->buffers.clear();
  glDeleteVertexArrays(1, &this->_vaoId); 
}

void VertexArrayObject::addBuffer(const BufferBase& buffer) {
  const int index = this->_buffers.size();
  // GL::vertexArrayAttrib(this->_vaoId, index, buffer._bufferId, buffer._itemSize,   

    // if (buffer.bufferType == GL_ELEMENT_ARRAY_BUFFER) {
    //   return;
    // }

    // if (glEnableVertexArrayAttrib) {
    //     glEnableVertexArrayAttrib(this->vaoId, index);
    //     glVertexArrayVertexBuffer(this->vaoId, index, buffer.getId(), 0, buffer.stride);
    //     glVertexArrayAttribFormat(this->vaoId, index, buffer.valuesPerIndex, GL_FLOAT, GL_FALSE, 0);
    // } else {
    //     auto unbindHelper = buffer.bind();
    //     auto unbindHelper2 = bind();
    //     glEnableVertexAttribArray(index);
    //     glVertexAttribPointer(index, buffer->valuesPerIndex, buffer->dataType, GL_FALSE, buffer->stride, 0);
    // }

  this->_buffers.push_back(buffer);
}

ExitScopeHelper VertexArrayObject::bind() {
  glBindVertexArray(this->_vaoId);
  return ExitScopeHelper([](){
    glBindVertexArray(0);  
  });
}
