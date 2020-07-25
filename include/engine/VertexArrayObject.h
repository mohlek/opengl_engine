#ifndef _H_VERTEXARRAYOBJECT
#define _H_VERTEXARRAYOBJECT

#include <GL/glew.h>
#include <vector>
#include <memory>

#include "Buffer.h"
#include "ExitScopeHelper.h"

namespace Engine {
    
  class VertexArrayObject {
      private:
          GLuint vaoId = 0;

          std::vector<Buffer*> buffers;
      public:
          VertexArrayObject();
          virtual ~VertexArrayObject();

          void addBuffer(std::shared_ptr<Buffer>& buffer);
          void addBuffer(Buffer& buffer);
          
          ExitScopeHelper bind();
  };

  using VertexArrayObjectPtr = std::shared_ptr<Engine::VertexArrayObject>;
}

#endif
