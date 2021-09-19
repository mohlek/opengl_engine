#include "../include/engine/Window.h"
#include <exception>

#include <string>
#include <iostream>
#include <signal.h>

using namespace Engine;

static void GlewInfo() {
  printf("----------------------OpenGL Info----------------------------\n");
  printf("     Version: %s\n", glGetString(GL_VERSION));
  printf("      Vendor: %s\n", glGetString(GL_VENDOR));
  printf("    Renderer: %s\n", glGetString(GL_RENDERER));
  printf("     Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
  printf("----------------------------------------------------------------\n");
}

void DebugCallbackAMD(GLuint id, GLenum category, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam) {
  printf("\nAn OGL AMD error has occured: %s\n", message);
}

void DebugCallbackARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam) {
  printf("\nAn OGL ARB error has occured: %s\n", message);
}

void printOutKhrDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
  printf("\nAn OGL KHR error has occured: %s\n", message);
}

void CheckGL() {
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("\n A general  OGL error has occured: %i\n", err);
  }
}

void MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ) {
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message );
}

Window::Window(const char* title, int width, int height, bool fullscreen) : title(title), width(width), height(height), fullscreen(fullscreen) {
  int error;
  error = SDL_Init(SDL_INIT_VIDEO);  
  if (error < 0) {
    fprintf(stderr, "Unable to initialize SDL");
    SDL_Quit();
    return;
  }

  //SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  //SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

bool Window::create() {
  this->window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
  if (!this->window) {
    fprintf(stderr, "Could not create window");
    SDL_Quit();
    return false;
  }

  this->context = SDL_GL_CreateContext(this->window);
  if (!this->context) {
    fprintf(stderr, "Could not create context: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  SDL_assert(gl3wInit() == GL3W_OK);
  glGetError();

  glEnable(GL_DEPTH_TEST);

  GlewInfo();
  CheckGL();

  if (GL_DEBUG_OUTPUT) {
    printf("Supporting Arb output\n");
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback((GLDEBUGPROC)DebugCallbackARB, 0);
    CheckGL();
  }

  if (GL_KHR_debug) {
    printf("Supporting KHR output\n");
    glDebugMessageCallback((GLDEBUGPROC)printOutKhrDebugMessage, 0);
    CheckGL();
  }

  SDL_GL_SetSwapInterval(1);

  return true;
}

bool Window::loop() {
  if (!this->window)
    return false;

  SDL_GL_SwapWindow(this->window);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  return true;
}

void Window::close() {
  if (this->window) {
    SDL_DestroyWindow(this->window);
    window = NULL;
  }
  SDL_Quit();
}

int Window::getWidth() {
  return this->width;
}

int Window::getHeight() {
  return this->height;
}
