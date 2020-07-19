#include <engine/Window.h>

int main() {

  Engine::Window* win = new Engine::Window("", 800, 600);
  win->create();

  do {
    // nothing
  } while (win->loop());

  return 0;
}
