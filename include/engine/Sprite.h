#ifndef _H_SPRITE
#define _H_SPRITE

#include <stdlib.h>
#include <memory>

#include <glm/glm.hpp>

#include "Buffer.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "shader/ShaderProgram.h"

namespace Engine {
  class Sprite {
    private:
      VertexArrayObjectPtr vao;
      BufferPtr vboPos;
      BufferPtr vboUV;
      const TexturePtr texture;
    public:
      glm::vec2 position;
      float alpha = 1.;

      Sprite(const TexturePtr& texture);
      virtual ~Sprite();

      void render(ShaderProgram& shader);
  };
  
  using SpritePtr = std::shared_ptr<Engine::Sprite>;
}


#endif
