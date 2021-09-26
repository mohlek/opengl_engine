#ifndef H_BUFFER
#define H_BUFFER

#include <GL/gl3w.h> 

namespace GL {
  void createBuffers(GLenum target, GLsizei n, GLuint* buffers);
  void deleteBuffers(GLsizei n, const GLuint* buffers);
  void bufferData(GLenum target, GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
  void bufferSubData(GLenum target, GLuint buffer, GLuint offset, GLsizeiptr size, const void* data);
  void* mapBufferRange(GLenum target, GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
  bool unmapBuffer(GLenum target, GLuint buffer);
  void flushMappedBufferRange(GLenum target, GLuint buffer, GLintptr offset, GLsizei length);
  void bufferStorage(GLenum target, GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags);
  void bindBuffer(GLenum target, GLuint buffer);
  void unbindBuffer(GLenum target);
}

#endif
