#include "../../include/engine/shader/Shader.h"
#include <iostream>

using namespace Engine;

Shader::~Shader() {
    glDeleteShader(this->shaderId);
}

void Shader::compile() {
    if (shaderId) {
        return;
    }

    this->shaderId = glCreateShader(this->shaderType);
    const char* s = this->source.c_str();
    glShaderSource(this->shaderId, 1, &s, 0);
    glCompileShader(this->shaderId);

    int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
    glGetShaderiv(this->shaderId, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0) {
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(this->shaderId, infologLength, &charsWritten, infoLog);
		std::cout << infoLog << std::endl;
		free(infoLog);
        abort();
	}
}
