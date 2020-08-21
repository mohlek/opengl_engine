#ifndef _H_VERTEXARRAYOBJECT
#define _H_VERTEXARRAYOBJECT

#include <GL/glew.h>
#include <vector>
#include <memory>

#include <framework/VertexArrayObject.h>

#include "Buffer.h"
#include "ExitScopeHelper.h"

namespace Engine {
    
  class VertexArrayObject {
      private:
          GLuint _vaoId = 0;

          std::vector<BufferBase> _buffers;
      public:
          VertexArrayObject();
          virtual ~VertexArrayObject();

          void setBuffer(int location, BufferBase& buffer);
          
          void bind();
          void unbind();
  };

  using VertexArrayObjectPtr = std::shared_ptr<Engine::VertexArrayObject>;
}

#endif
