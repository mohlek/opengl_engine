#include "../include/engine/Window.h"
#include <exception>

#include <string>
#include <iostream>
#include <signal.h>

using namespace Engine;

Window::Window(const char* title, int width, int height, bool fullscreen) : title(title), width(width), height(height), fullscreen(fullscreen) {
    SDL_Init(SDL_INIT_VIDEO);  

}

void Window::create() {
      this->window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
      SDL_Renderer* renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);
}

bool Window::loop() {
  return true;
}

void Window::close() {
    if (this->window) {
        SDL_DestroyWindow(this->window);
        window = NULL;
    }
    SDL_Quit();
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //fprintf(stdout, "Key %s\n", glfwGetKeyName(key, 0));
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
