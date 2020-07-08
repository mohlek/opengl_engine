#ifndef _H_SHADERPROGRAMM
#define _H_SHADERPROGRAMM

#include <GL/glew.h>

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "Shader.h"

namespace Engine {
    
    class ShaderProgram {
        private:
            GLuint programId = 0;
        
        public:
            std::vector<std::shared_ptr<Shader>> shaders;
            std::map<std::string, GLuint> uniforms;

            ShaderProgram();
            virtual ~ShaderProgram();

            GLint getUniformLocation(std::string&& name);

            void link();
            void use();
            void end();
    };
}

#endif
