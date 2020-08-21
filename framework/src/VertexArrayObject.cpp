#include "../include/framework/VertexArrayObject.h"

void GL::createVertexArrays(GLuint n, GLuint* buffer) {
  if (glCreateVertexArrays) {
    glCreateVertexArrays(n, buffer);
    return;
  }
  glGenVertexArrays(n, buffer);
  for (int i = 0; i < n; ++i) {
    glBindVertexArray(buffer[i]);
  }
  glBindVertexArray(0);
}

void GL::deleteVertexArrays(GLuint n, GLuint* buffer) {
  glDeleteVertexArrays(n, buffer);
}

void GL::vertexArrayAttrib(GLuint vao, GLuint index, GLuint bufferId, GLuint stride, GLuint valuesPerIndex, GLenum dataType, GLenum target) {
  if (glEnableVertexArrayAttrib) {
    glEnableVertexArrayAttrib(vao, index);
    glVertexArrayVertexBuffer(vao, index, bufferId, 0, stride);
    glVertexArrayAttribFormat(vao, index, valuesPerIndex, dataType, GL_FALSE, 0);
  } else {
    glBindVertexArray(vao);
    glEnableVertexAttribArray(index);
    glBindBuffer(target, bufferId);
    glVertexAttribPointer(index, valuesPerIndex, dataType, GL_FALSE, stride, 0);
    glBindVertexArray(0);
    glBindBuffer(target, 0);
  }
}
