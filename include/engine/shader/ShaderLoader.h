#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <GL/gl3w.h>
#include <string>
#include <memory>

namespace Engine {
    
    class ShaderLoader {
        private:
        public:
            const GLenum shaderType;
            std::string source;

            ShaderLoader(GLenum shaderType, std::string&& path);
    };
}

#endif
