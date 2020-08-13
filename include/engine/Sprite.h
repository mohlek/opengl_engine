#ifndef _H_SPRITE
#define _H_SPRITE

#include <stdlib.h>
#include <memory>

#include <glm/glm.hpp>

#include "RenderObject.h"

#include "Buffer.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "shader/ShaderProgram.h"

namespace Engine {
  class Sprite : public RenderObject {
    private:
      VertexArrayObjectPtr vao;
      Buffer<glm::vec3> vboPos;
      Buffer<glm::vec2> vboUV;
      const TexturePtr texture;
    public:
      glm::vec2 position;
      float alpha = 1.;

      Sprite(const TexturePtr& texture);
      virtual ~Sprite();

      void update(double time);
      void render(ShaderProgram& shader);
  };
  
  using SpritePtr = std::shared_ptr<Engine::Sprite>;
}


#endif
