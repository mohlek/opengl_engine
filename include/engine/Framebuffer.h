#ifndef H_FRAMEBUFFER
#define H_FRAMEBUFFER

#include "../framework/Framebuffer.h"
#include "Texture.h"
#include "Buffer.h"

#include <vector>

namespace Engine {
    class Framebuffer {
        private:
            GLuint framebufferId = 0;
            GLenum target;
            std::vector<std::reference_wrapper<Texture>> textures;
            std::vector<std::reference_wrapper<BufferBase>> buffer;
        public:
            Framebuffer(GLenum target);
            virtual ~Framebuffer();

            void addTexture(GLenum attachment, Texture& Texture);
            void addBuffer(GLenum attachment, BufferBase& buffer);

            void bind();
            void unbind();
    };
}

#endif