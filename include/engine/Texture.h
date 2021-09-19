#ifndef _H_TEXTURE
#define _H_TEXTURE

#include <stdio.h>
#include <memory>

#include <GL/gl3w.h>

#include "stb_image.h"

#include "ExitScopeHelper.h"

namespace Engine {
  class Texture {
    private:
      GLuint textureId;
    public:
      GLenum textureUnit;
      GLenum target;
      
      Texture(GLenum textureUnit = GL_TEXTURE0, GLenum target = GL_TEXTURE_2D);
      Texture(const char* filename, GLenum textureUnit = GL_TEXTURE0, GLenum target = GL_TEXTURE_2D);
      virtual ~Texture();

      void load(const char* path);
      void pushData(GLint internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, const void* data);
      
      void bind();
      void unbind();
  };
}


#endif
