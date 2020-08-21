#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

#include "ShaderLoader.h"

namespace Engine {
    
    class Shader {
        private:
            GLuint shaderId = 0;
        public:
            const GLenum shaderType;
            const std::string source;

            Shader(const ShaderLoader& loader) : Shader(loader.shaderType, loader.source) {};

            Shader(const GLenum shaderType, const std::string& source) : shaderType(shaderType), source(source) {};
            Shader(const GLenum shaderType, const std::string&& source): shaderType(shaderType), source(std::move(source)) {};
            virtual ~Shader();
    
            void compile();

            GLuint getShaderId() { return this->shaderId; }
    };

    typedef std::shared_ptr<Engine::Shader> ShaderPtr;
}

#endif
