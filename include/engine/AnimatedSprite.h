#ifndef _H_ANIMATEDSPRITE
#define _H_ANIMATEDSPRITE

#include <GL/glew.h>

#include <vector>
#include <memory>

#include "RenderObject.h"

#include "VertexArrayObject.h"
#include "Buffer.h"
#include "Texture.h"
#include "shader/ShaderProgram.h"

#include "ExitScopeHelper.h"

namespace Engine {
  class AnimatedSprite : public RenderObject {
    private:
      VertexArrayObjectPtr vao;
      BufferPtr vboPos;
      BufferPtr vboUV;
    public:
      std::vector<TexturePtr> textures;
      int index = 0;
      double fps = 60;

      float alpha = 1.;

      void update(double time);
      void render(ShaderProgram& shader);

      AnimatedSprite();
      virtual ~AnimatedSprite();
  };

  using AnimatedSpritePtr = std::shared_ptr<Engine::AnimatedSprite>;
}

#endif
