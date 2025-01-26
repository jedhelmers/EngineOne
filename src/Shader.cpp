#include "Shader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "utils/logger.h"


Shader::Shader(const char* fShaderPath, const char* vShaderPath) {
    std::ifstream fragmentFile(fShaderPath);
    std::stringstream fShaderStream;
    fShaderStream << fragmentFile.rdbuf();
    std::string fragmentCode = fShaderStream.str();
    const char* fShaderCode = fragmentCode.c_str();

    std::ifstream vertexFile(vShaderPath);
    std::stringstream vShaderStream;
    vShaderStream << vertexFile.rdbuf();
    std::string vertexCode = vShaderStream.str();
    const char* vShaderCode = vertexCode.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    // check for linking errors
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    // LOG(INFO, (std::string("Setting int: ") + name + " to " + std::to_string(value)).c_str());
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    // LOG(INFO, (std::string("Setting float: ") + name + " to " + std::to_string(value)).c_str());
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value); 
} 

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    // LOG(INFO, (std::string("Setting mat4: ") + name).c_str());
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::Use() {
    glUseProgram(programID);
}