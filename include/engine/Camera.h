#include <GL/gl3w.h>

#include <glm/glm.hpp>

namespace Engine {
    
    class Camera {
        public:
            glm::vec3 position;
            glm::vec3 direction;
            glm::vec3 up;
            
            Camera() : position(glm::vec3(0.0f, 0.0f, 0.0f)), direction(glm::vec3(1.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)){
            }
            ~Camera() {}

            glm::mat4 getView() {
                return glm::lookAt(position, position + direction, up);
            }
    };
}
