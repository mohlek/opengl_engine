#include "../include/engine/Sprite.h"

using namespace Engine;

Sprite::Sprite(const std::shared_ptr<Texture>& texture) : vboPos(6), vboUV(6), texture(texture) {
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

Sprite::~Sprite() {
}

void Sprite::update(double time) {
}

void Sprite::render(ShaderProgram& shader) {
  auto unbindHelper = vao->bind();
  auto textureBindHelper = this->texture->bind();

  glUniform1fv(shader.getUniformLocation("alpha"), 1, &this->alpha);

  glDrawArrays(GL_TRIANGLES, 0, 8);
}
