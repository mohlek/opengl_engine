#ifndef H_VERTEXARRAYOBJECT
#define H_VERTEXARRAYOBJECT

#include <GL/gl3w.h>

namespace GL {
  void createVertexArrays(GLuint n, GLuint* buffer);
  void deleteVertexArrays(GLuint n, GLuint* buffer);
  void vertexArrayAttrib(GLuint vao, GLuint index, GLuint bufferId, GLuint stride, GLuint valuesPerIndex, GLenum dataType, GLenum target);
}

#endif
