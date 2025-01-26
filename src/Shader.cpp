#include "Shader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "utils/logger.h"

Shader::Shader(const char* vShaderPath, const char* fShaderPath) {
    // Load vertex shader file
    std::ifstream vertexFile(vShaderPath);
    if (!vertexFile.is_open()) {
        std::cerr << "ERROR::SHADER::VERTEX::FILE_NOT_FOUND: " << vShaderPath << std::endl;
        return;
    }
    std::stringstream vShaderStream;
    vShaderStream << vertexFile.rdbuf();
    std::string vertexCode = vShaderStream.str();
    const char* vShaderCode = vertexCode.c_str();
    // std::cout << "Vertex Shader Code Loaded:\n" << vertexCode << std::endl;

    // Load fragment shader file
    std::ifstream fragmentFile(fShaderPath);
    if (!fragmentFile.is_open()) {
        std::cerr << "ERROR::SHADER::FRAGMENT::FILE_NOT_FOUND: " << fShaderPath << std::endl;
        return;
    }
    std::stringstream fShaderStream;
    fShaderStream << fragmentFile.rdbuf();
    std::string fragmentCode = fShaderStream.str();
    const char* fShaderCode = fragmentCode.c_str();
    // std::cout << "Fragment Shader Code Loaded:\n" << fragmentCode << std::endl;

    // Compile vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        // std::cout << "Vertex shader compiled successfully!" << std::endl;
    }

    // Compile fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        // std::cout << "Fragment shader compiled successfully!" << std::endl;
    }

    // Link shaders
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    } else {
        // std::cout << "Shader program linked successfully!" << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    // std::cout << "Deleting shader program: " << programID << std::endl;
    glDeleteProgram(programID);
}

void Shader::setBool(const std::string &name, bool value) const {         
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value); 
} 

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::Use() {
    glUseProgram(programID);
}
