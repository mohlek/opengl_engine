#include "../include/engine/AnimatedSprite.h"

using namespace Engine;

AnimatedSprite::AnimatedSprite() : vboUV(6), vboPos(6) {
  this->vao = std::make_shared<VertexArrayObject>();

  this->vboPos[0] = { 0.0f,  1.0f, 0.0f };
  this->vboPos[1] = { 1.0f,  1.0f, 0.0f };
  this->vboPos[2] = { 1.0f,  0.0f, 0.0f };
  this->vboPos[3] = { 1.0f,  0.0f, 0.0f };
  this->vboPos[4] = { 0.0f,  0.0f, 0.0f };
  this->vboPos[5] = { 0.0f,  1.0f, 0.0f };
  this->vboPos.flush();


  this->vboUV[0] = { 0.0f, 0.0f };
  this->vboUV[1] = { 1.0f, 0.0f };
  this->vboUV[2] = { 1.0f, 1.0f };
  this->vboUV[3] = { 1.0f, 1.0f };
  this->vboUV[4] = { 0.0f, 1.0f };
  this->vboUV[5] = { 0.0f, 0.0f };
  this->vboUV.flush();


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
