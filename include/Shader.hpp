#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

std::string readFile(const std::string& filePath);
GLuint compileShader(GLenum type, const std::string& source);
GLuint createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);

#endif // SHADER_H