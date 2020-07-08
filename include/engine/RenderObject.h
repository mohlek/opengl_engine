#ifndef __RENDEROBJECT_H
#define __RENDEROBJECT_H

#include "shader/ShaderProgram.h"

namespace Engine {

  class RenderObject {
    public:
      virtual void update(double time) = 0;
      virtual void render(ShaderProgram& shader) = 0;
  };
}

#endif
