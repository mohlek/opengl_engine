#ifndef _H_TEXTURE
#define _H_TEXTURE

#include <stdio.h>
#include <memory>

#include <GL/glew.h>

#include "stb_image.h"

#include "ExitScopeHelper.h"

namespace Engine {
  class Texture {
    private:
      GLuint textureId;
    public:
      GLenum target;
      
      Texture(GLenum target = GL_TEXTURE_2D);
      Texture(const char* filename, GLenum target = GL_TEXTURE_2D);
      virtual ~Texture();

      void load(const char* path);
      void pushData(GLint format, GLsizei width, GLsizei height, const void* data);
      ExitScopeHelper bind();
  };

  using TexturePtr = std::shared_ptr<Engine::Texture>;
}


#endif
