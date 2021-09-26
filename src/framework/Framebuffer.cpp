#include "../include/framework/Framebuffer.h"

void GL::createFramebuffers(GLsizei n, GLuint *ids) {
    glGenFramebuffers(n, ids);
}

void GL::bindFramebuffer(GLenum target, GLuint framebuffer) {
    glBindFramebuffer(target, framebuffer);
}
void GL::deleteFramebuffers(GLsizei n, GLuint *framebuffers) {
    glDeleteFramebuffers(n, framebuffers);
}

GLenum GL::checkFramebufferStatus(GLenum target, GLuint framebuffer) {
    if (glCheckNamedFramebufferStatus) {
        return glCheckNamedFramebufferStatus(framebuffer, target);
    }
    return glCheckFramebufferStatus(target);
}

void GL::framebufferTexture(GLenum target, GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) {
    if (glNamedFramebufferTexture) {
        glNamedFramebufferTexture(framebuffer, attachment, texture, level);
        return;
    }
    glFramebufferTexture(target, attachment, texture, level);
}

void GL::framebufferRenderbuffer(GLenum target, GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    if (glNamedFramebufferRenderbuffer) {
        glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
        return;
    }
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}