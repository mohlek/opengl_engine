#ifndef __RENDEROBJECT_H
#define __RENDEROBJECT_H

#include "Buffer.h"
#include "shader/ShaderProgram.h"

#include <glm/glm.hpp>

namespace Engine {

  class RenderObject {
    public:
      virtual void update(double time) = 0;
      virtual void render(ShaderProgram& shader) = 0;
  };
}

#endif
