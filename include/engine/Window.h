#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL.h>

namespace Engine {

    class Window {
        private:
            SDL_Window* window;
            GLFWmonitor* monitor;
            const GLFWvidmode* mode;
            
            int width;
            int height;
            const char* title;
            bool fullscreen;

            static void errorCallback(int error, const char* desc);
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            
            static void openGLDebugOutput(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);
        public:
            void create();
            bool loop();
            void close();

            int getWidth();
            int getHeight();

            GLFWwindow* getWindowPtr() { return NULL; }

            Window(const char* title, int width, int height, bool fullscreen = false);
    };
}
