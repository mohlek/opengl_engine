#include "../include/engine/Texture.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/engine/stb_image.h"

using namespace Engine;

Texture::Texture(GLenum target) : target(target){
  glGenTextures(1, &this->textureId);
  if (!this->textureId) {
    fprintf(stderr, "Could not create texture\n");
  }
  bind();
  unbind();
}

Texture::Texture(const char* filename, GLenum target) : Texture(target) {
  load(filename);
}

Texture::~Texture() {
  glDeleteTextures(1, &this->textureId);
}

void Texture::pushData(GLint format, GLsizei width, GLsizei height, const void* data) {
  bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(this->target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(this->target);

  unbind();
}

void Texture::load(const char* path) {
  stbi_set_flip_vertically_on_load(true);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
  pushData(GL_RGB, width, height, data);

  stbi_image_free(data);
}

void Texture::bind() {
  glBindTexture(this->target, this->textureId);
}

void Texture::unbind() {
  glBindTexture(target, 0);
}
