#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    // Load shader source files
    std::string vertexSrc = readFile(vertexPath);
    std::string fragmentSrc = readFile(fragmentPath);

    if (vertexSrc.empty() || fragmentSrc.empty()) {
        std::cerr << "Error: Shader source file(s) could not be loaded." << std::endl;
        return;
    }

    // Compile and link shaders
    m_ID = createShaderProgram(vertexSrc, fragmentSrc);
}

Shader::~Shader()
{
    // Delete the shader program when the object is destroyed
    glDeleteProgram(m_ID);
}

void Shader::use() const
{
    glUseProgram(m_ID);
}

std::string Shader::readFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint compileShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);
    const char* srcPtr = source.c_str();
    glShaderSource(shader, 1, &srcPtr, nullptr);
    glCompileShader(shader);

    // Check for compile errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader compilation failed:\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR: Program linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
