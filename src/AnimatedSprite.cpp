#include "../include/engine/AnimatedSprite.h"

using namespace Engine;

AnimatedSprite::AnimatedSprite() {
  this->vao = std::make_shared<VertexArrayObject>();
  this->vboPos = std::make_shared<Buffer>();
  this->vboUV = std::make_shared<Buffer>();

  this->vboPos->stride = 3 * sizeof(float);
  this->vboUV->stride = 2 * sizeof(float);
  this->vboUV->valuesPerIndex = 2;

  float points[] = {
     0.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f,  0.0f, 0.0f,

     1.0f,  0.0f, 0.0f,
     0.0f,  0.0f, 0.0f,
     0.0f,  1.0f, 0.0f
  };

  float uvs[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
  };

  this->vboPos->pushData(points, sizeof(points));
  this->vboUV->pushData(uvs, sizeof(uvs));

  this->vao->addBuffer(this->vboPos);
  this->vao->addBuffer(this->vboUV);
}

AnimatedSprite::~AnimatedSprite() {
}

void AnimatedSprite::update(double time) {
  this->index = ((int)(time * this->fps)) % textures.size();
}

void AnimatedSprite::render(ShaderProgram& shader) {
  auto vaoUnbindHelper = this->vao->bind();
  auto textureUnbindHelper = this->textures[this->index]->bind();

  glUniform1fv(shader.getUniformLocation("alpha"), 1, &this->alpha);

  glDrawArrays(GL_TRIANGLES, 0, 8);
}
