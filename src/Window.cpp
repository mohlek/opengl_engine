#include "../include/engine/Window.h"
#include <exception>

#include <string>
#include <iostream>
#include <signal.h>

using namespace Engine;

Window::Window(const char* title, int width, int height, bool fullscreen) : title(title), width(width), height(height), fullscreen(fullscreen) {
  int error;
  error = SDL_Init(SDL_INIT_VIDEO);  
  if (error < 0) {
    fprintf(stderr, "Unable to initialize SDL");
    SDL_Quit();
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

void Window::create() {
  this->window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!this->window) {
    fprintf(stderr, "Could not create window");
    SDL_Quit();
  }

  this->context = SDL_GL_CreateContext(this->window);
  SDL_GL_SetSwapInterval(1);
}

bool Window::loop() {
  SDL_GL_SwapWindow(this->window);
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

void Window::errorCallback(int error, const char* desc) {
    fprintf(stderr, "Error: %s\n", desc);
    return;
}

void Window::openGLDebugOutput(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam) {
	
    // Thanks to Luca :)
    
  if (std::string(message, std::string("Buffer detailed info").size()) == "Buffer detailed info") {
		//filter it
		return;
	}

	std::string error_source, error_type, error_severity;
	switch(source) {
		case GL_DEBUG_SOURCE_API_ARB:
			error_source = "OpenGL";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
			error_source = "Windows";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
			error_source = "Shader Compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
			error_source = "Third Party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION_ARB:
			error_source = "Application";
			break;
		case GL_DEBUG_SOURCE_OTHER_ARB:
			error_source = "Other";
			break;
		default:
			error_source = "UNKNOW";
			break;
	}

	switch (type) {
		case GL_DEBUG_TYPE_ERROR_ARB:
			error_type = "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
			error_type = "Deprecated behavior";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
			error_type = "Undefined behavior";
			break;
		case GL_DEBUG_TYPE_PORTABILITY_ARB:
			error_type = "Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE_ARB:
			error_type = "Performance";
			break;
		case GL_DEBUG_TYPE_OTHER_ARB:
			error_type = "Other";
		default:
			error_type = "UNKNOW";
			break;
	}

	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH_ARB:
			error_severity = "High";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM_ARB:
			error_severity = "Medium";
			break;
		case GL_DEBUG_SEVERITY_LOW_ARB:
			error_severity = "Low";
			break;
		default:
			error_severity = "UNKNOW";
			break;
	}

	std::cout << "Source: " << error_source << "  Type: " << error_type << "  Severity: " << error_severity << "  Message: " << message << std::endl;

	if (severity == GL_DEBUG_SEVERITY_HIGH_ARB) {
		raise(SIGTRAP);
	}
}
