#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#ifdef __APPLE__
  #include <SDL.h>
  #include <SDL_opengl.h>
#else
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_opengl.h>
#endif

namespace Engine {

  class Window {
    private:
      SDL_Window* window;
      SDL_GLContext context;
      
      int width;
      int height;
      const char* title;
      bool fullscreen;
    public:
      bool create();
      bool loop();
      void close();

      int getWidth();
      int getHeight();

      Window(const char* title, int width, int height, bool fullscreen = false);
  };
}
