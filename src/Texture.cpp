#include "../include/engine/Texture.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/engine/stb_image.h"

using namespace Engine;

Texture::Texture(GLenum textureUnit, GLenum target) : textureUnit(textureUnit), target(target){
  glGenTextures(1, &this->textureId);
  if (!this->textureId) {
    fprintf(stderr, "Could not create texture\n");
  }
  bind();
  unbind();
}

Texture::Texture(const char* filename, GLenum textureUnit, GLenum target) : Texture(textureUnit, target) {
  load(filename);
}

Texture::~Texture() {
  glDeleteTextures(1, &this->textureId);
}

void Texture::pushData(GLint internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, const void* data) {
  bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(this->target, 0, internalFormat, width, height, 0, format, type, data);
  glGenerateMipmap(this->target);

  unbind();
}

void Texture::load(const char* path) {
  stbi_set_flip_vertically_on_load(true);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
  
  GLenum format;
  if (nrChannels == 1)
    format = GL_RED;
  else if (nrChannels == 3)
    format = GL_RGB;
  else if (nrChannels == 4)
    format = GL_RGBA;

  pushData(format, format, GL_UNSIGNED_BYTE, width, height, data);

  stbi_image_free(data);
}

void Texture::bind() {
  glActiveTexture(this->textureUnit);
  glBindTexture(this->target, this->textureId);
}

void Texture::unbind() {
  glBindTexture(target, 0);
}
