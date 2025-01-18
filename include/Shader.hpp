#pragma once

#include <string>
#include <glad/glad.h>

GLuint createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    GLuint getID() const { return m_ID; }

private:
    GLuint m_ID;

    static std::string readFile(const std::string& filePath);
    GLuint compileShader(GLenum type, const std::string& source);
    // static GLuint createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
};
