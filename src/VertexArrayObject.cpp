#include "../include/engine/VertexArrayObject.h"

using namespace Engine;

VertexArrayObject::VertexArrayObject() {
  GL::createVertexArrays(1, &this->_vaoId);
}

VertexArrayObject::~VertexArrayObject() {
  GL::deleteVertexArrays(1, &this->_vaoId);
}

void VertexArrayObject::setBuffer(int location, BufferBase& buffer) {
  bind();
  buffer.bind();

  if (buffer._target != GL_ELEMENT_ARRAY_BUFFER) {
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, buffer._itemSize, 0);
  }
  
  unbind();
  buffer.unbind();
}

void VertexArrayObject::bind() {
  glBindVertexArray(this->_vaoId);
}

void VertexArrayObject::unbind() {
  glBindVertexArray(0);
}
