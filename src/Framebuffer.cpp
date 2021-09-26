#include "../include/engine/Framebuffer.h"
#include <algorithm>

using namespace Engine;

Framebuffer::Framebuffer(GLenum target) : target(target) {
    GL::createFramebuffers(1, &this->framebufferId);
}

Framebuffer::~Framebuffer() {
    GL::deleteFramebuffers(1, &this->framebufferId);
}

void Framebuffer::bind() {
    GL::bindFramebuffer(this->target, this->framebufferId);
}

void Framebuffer::unbind() {
    GL::bindFramebuffer(this->target, 0);
}

void Framebuffer::addTexture(GLenum attachment, Texture& texture) {
    this->textures.push_back(texture);
    bind();
    GL::framebufferTexture(this->target, this->framebufferId, attachment, texture.getTextureId(), texture.getMipmapLevel());
}

void Framebuffer::addBuffer(GLenum attachment, BufferBase& buffer) {
    this->buffer.push_back(buffer);
    GL::framebufferRenderbuffer(this->target, this->framebufferId, attachment,  GL_RENDERBUFFER, buffer._bufferId);
}