#include "../include/framework/Buffer.h"

void GL::createBuffers(GLenum target, GLsizei n, GLuint* buffers) {
  if (glCreateBuffers) {
    glCreateBuffers(n, buffers);
    return;
  }
  glGenBuffers(n, buffers);
  for (auto i = 0; i < n; ++i) {
    glBindBuffer(target, buffers[i]);
  }
  glBindBuffer(target, 0);
}

void GL::deleteBuffers(GLsizei n, const GLuint* buffers) {
  glDeleteBuffers(n, buffers);
}

void GL::bufferData(GLenum target, GLuint buffer, GLsizeiptr size, const void *data, GLenum usage) {
  if (glNamedBufferData) {
    glNamedBufferData(buffer, size, data, usage);
    return;
  }
  glBindBuffer(target, buffer);
  glBufferData(target, size, data, usage);
  glBindBuffer(target, 0);
}

void GL::bufferSubData(GLenum target, GLuint buffer, GLuint offset, GLsizeiptr size, const void* data) {
  if (glNamedBufferSubData) {
    glNamedBufferSubData(buffer, offset, size, data);
    return;
  }
  glBindBuffer(target, buffer);
  glBufferSubData(target, offset, size, data);
  glBindBuffer(target, 0);
}

void* GL::mapBufferRange(GLenum target, GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) {
  if (glMapNamedBufferRange) {
    return glMapNamedBufferRange(buffer, offset, length, access);
  }
  glBindBuffer(target, buffer);
  auto tmp = glMapBufferRange(target, offset, length, access);
  glBindBuffer(target, 0);
  return tmp;
}

bool GL::unmapBuffer(GLenum target, GLuint buffer) {
  if (glUnmapNamedBuffer) {
    return glUnmapNamedBuffer(buffer);
  }
  glBindBuffer(target, buffer);
  bool result = glUnmapBuffer(target);
  glBindBuffer(target, 0);
  return result;
}

void GL::flushMappedBufferRange(GLenum target, GLuint buffer, GLintptr offset, GLsizei length) {
  if (glFlushMappedNamedBufferRange) {
    glFlushMappedNamedBufferRange(buffer, offset, length);
    return;
  }
  glBindBuffer(target, buffer);
  glFlushMappedBufferRange(target, offset, length);
  glBindBuffer(target, 0);
}

void GL::bufferStorage(GLenum target, GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) {
  if (glNamedBufferStorage) {
    glNamedBufferStorage(buffer, size, data, flags);
    return;
  }

  glBindBuffer(target, buffer);
  if (glBufferStorage) {
    glBufferStorage(target, size, data, flags);
  } else {
    glBufferData(target, size, data, GL_STATIC_DRAW);
  }
  glBindBuffer(target, 0);
}

void GL::bindBuffer(GLenum target, GLuint buffer) {
  glBindBuffer(target, buffer);
}

void GL::unbindBuffer(GLenum target) {
  glBindBuffer(target, 0);
}

void GL::bindBufferBase(GLenum target, GLuint location, GLuint buffer) {
  glBindBufferBase(target, location, buffer);
}
