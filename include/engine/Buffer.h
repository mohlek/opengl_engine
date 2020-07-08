#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>

#include <memory>

#include "ExitScopeHelper.h"

namespace Engine {

  class Buffer {
      private:
          GLuint bufferId = 0;
      public:
          const GLenum bufferType;
         
          GLint size;
          GLenum dataType = GL_FLOAT;
          GLsizei stride;
          GLenum valuesPerIndex = 3;

          Buffer(GLenum bufferType, int size);
          Buffer() : Buffer(GL_ARRAY_BUFFER, 0) {};
          virtual ~Buffer();

          ExitScopeHelper bind();
          void unbind();
          
          void pushData(const void* data, unsigned int size, unsigned int offset = 0);

          void* map(GLenum access);
          bool  unmap();
      
          GLuint getId() { return bufferId; }
  
  };
  
  using BufferPtr = std::shared_ptr<Engine::Buffer>;
}


#endif
