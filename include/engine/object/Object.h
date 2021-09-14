#ifndef H_OBJECT
#define H_OBJECT

#include <glm/glm.hpp>
#include "../Buffer.h"

namespace Engine {

    class Mesh {
        public:
            Engine::Buffer<glm::vec3>* verticies;
            Engine::Buffer<glm::vec3>* normals;
            Engine::Buffer<glm::vec2>* textureCoords;
            Engine::Buffer<unsigned int>* facesIndicies;
            Engine::Buffer<unsigned int>* normalsIndicies;
            Engine::Buffer<unsigned int>* textureCoordsIndicies;

            Engine::Buffer<glm::vec2>* tangent;
            Engine::Buffer<glm::vec2>* bitangent;

            Mesh() {}
                
   };

    class Object {
        public:
            Mesh* mesh;

            Object() {}
    };
}

#endif