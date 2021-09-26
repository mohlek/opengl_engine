#ifndef H_FW_FRAMEBUFFER
#define H_FW_FRAMEBUFFER

#include <GL/gl3w.h>

namespace GL {
    void createFramebuffers(GLsizei n, GLuint *ids);
    void bindFramebuffer(GLenum target, GLuint framebuffer);
    void deleteFramebuffers(GLsizei n, GLuint *framebuffers);

    GLenum checkFramebufferStatus(GLenum target, GLuint framebuffer);
    void framebufferTexture(GLenum target, GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
    void framebufferRenderbuffer(GLenum target, GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
}

#endif